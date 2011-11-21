#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>

// Convinient Output Classes
class EvtSel {
public:
   int run;
   int evt;
   int cbin;
   int nG;
   int nJ;
   int nT;
   int trig;
   int offlSel;
   float vz;
};

static const int MAXTRK = 10000;

class GammaJet{
public:
   GammaJet() :
   pt1(-99),eta1(0),phi1(0),
   pt2(-99),eta2(0),phi2(0),
   deta(-99),dphi(-99), Aj(-99),
   nTrk(0)
   {}
   float pt1;
   float eta1;
   float phi1;
   float pt2;
   float eta2;
   float phi2;
   float deta;
   float dphi;
   float Aj;
   int nTrk;
   float trkPt[MAXTRK];
   float trkEta[MAXTRK];
   float trkPhi[MAXTRK];
   void clear() {
      pt1=-99; eta1=0; phi1=0;
      pt2=-99; eta2=0; phi2=0;
      deta=-99; dphi=-99; Aj=-99;
      nTrk=0;
   }
};

void dijetMPT(TString inname="/d100/velicanu/forest/PromptHiForestDiJet.root")
{
	double cutPtJet = 100;
   double cutEtaJet = 2;
	double cutPtTrk = -1;
	double cutEtaTrk = 2.4;	
   
   // Define the input file and HiForest
   HiForest *c = new HiForest(inname.Data());
   c->hasHltTree = 0;
   
   // Output file
   TFile *output = new TFile(Form("output-dj%.0f.root",cutPtJet),"recreate");
   
   // trk monitoring
   TH1D * hTrkPt = new TH1D("hTrkPt","",nptrange,ptranges);
   TH1D * hTrkEta = new TH1D("hTrkEta","",40,-2.4,2.4);
   TH1D * hTrkPhi = new TH1D("hTrkPhi","",40,-3.14,3.14);
   
   // Output
   TTree * tjt = new TTree("tjt","jet trk");

   EvtSel evt;
   GammaJet gj;
   tjt->Branch("evt",&evt.run,"run/I:evt:cbin:nG:nJ:nT:trig:offlSel:vz/F");
   tjt->Branch("jet",&gj.pt1,"pt1/F:eta1:phi1:pt2:eta2:phi2:deta:dphi:Aj");
   tjt->Branch("nTrk",&gj.nTrk,"nTrk/I");
   tjt->Branch("trkPt",gj.trkPt,"trkPt[nTrk]/F");
   tjt->Branch("trkEta",gj.trkEta,"trkEta[nTrk]/F");
   tjt->Branch("trkPhi",gj.trkPhi,"trkPhi[nTrk]/F");
   vector<MPT> vmpt;
   vmpt.push_back(MPT("AllAcc",0,-1,cutPtTrk,cutEtaTrk));
   vmpt.push_back(MPT("InCone",1,0.8,cutPtTrk,cutEtaTrk));
   vmpt.push_back(MPT("OutCone",2,0.8,cutPtTrk,cutEtaTrk));
   for (unsigned m=0; m<vmpt.size(); ++m) { 
      cout << "CalcMPT for " << vmpt[m].name << " dRCone: " << vmpt[m].dRCone << endl;
      SetMPTBranches(tjt,vmpt[m]);
   }
   
   // Main loop
   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      
      // Event Info
      evt.run = c->hlt.Run;
      evt.evt = c->hlt.Event;
      evt.cbin = c->evt.hiBin;
      evt.nG = c->photon.nPhotons;
      evt.nJ = c->icPu5.nref;
      evt.nT = c->track.nTrk;
      evt.trig = c->hlt.HLT_HIJet80_v1;
      evt.offlSel = c->skim.pcollisionEventSelection;
      evt.vz = c->track.vz[1];
      if (i%1000==0) cout <<i<<" / "<<c->GetEntries() << " " << evt.run << " " << evt.evt << " " << evt.cbin << " " << c->track.nTrk <<endl;
      
      // initialize
      int leadingIndex=-1;
      int awayIndex=-1;
      gj.clear();
      for (unsigned m=0; m<vmpt.size(); ++m) vmpt[m].clear();
      
      // Loop over jets to look for leading jet candidate in the event
      for(int j = 0; j < c->icPu5.nref; ++j){
			if(c->icPu5.jtpt[j] < cutPtJet) continue;
			if(fabs(c->icPu5.jteta[j]) > cutEtaJet) continue;
			leadingIndex = j;
         break;  
		}
      
      // Found a leading jet which passed basic quality cut!
      if (leadingIndex!=-1) {
         // set leading jet
         gj.pt1=c->icPu5.jtpt[leadingIndex];
         gj.eta1=c->icPu5.jteta[leadingIndex];
         gj.phi1=c->icPu5.jtphi[leadingIndex];
         // Trk Monitoring
         for (int it=0; it<c->track.nTrk; ++it) {
            hTrkPt->Fill(c->track.trkPt[it]);
            hTrkEta->Fill(c->track.trkEta[it]);
            hTrkPhi->Fill(c->track.trkPhi[it]);
         }
         
         // Loop over jet tree to find a away side leading jet
         for (int j=leadingIndex+1;j<c->icPu5.nref;j++) {
            if (c->icPu5.jtpt[j]<40) break;
            if (fabs(c->icPu5.jteta[j])>cutEtaJet) continue;
            awayIndex = j;
            break;
         }	 
         
         // Found an away jet!
         if (awayIndex !=-1) {
            double pt1 = c->icPu5.jtpt[leadingIndex];
            double pt2 = c->icPu5.jtpt[awayIndex];
            double Agj = (pt1-pt2)/(pt1+pt2);
            gj.pt2  = pt2;
            gj.eta2 = c->icPu5.jteta[awayIndex];
            gj.phi2 = c->icPu5.jtphi[awayIndex];
            gj.deta = c->icPu5.jteta[awayIndex] - c->icPu5.jteta[leadingIndex];
            gj.dphi = deltaPhi(c->icPu5.jtphi[awayIndex],c->icPu5.jtphi[leadingIndex]);
            gj.Aj   = Agj;
            // MPT
            for (unsigned m=0; m<vmpt.size(); ++m) {
               CalcMPT(c,gj.eta1,gj.phi1,gj.eta2,gj.phi2,vmpt[m]);
            }
         }
      }
      
      // loop over tracks
      gj.nTrk=0;
      for (int it=0; it<c->track.nTrk; ++it) {
         if (c->track.trkPt[it] < 7) continue;
         if (fabs(c->track.trkEta[it]) > cutEtaTrk) continue;
         gj.trkPt[gj.nTrk] = c->track.trkPt[it];
         gj.trkEta[gj.nTrk] = c->track.trkEta[it];
         gj.trkPhi[gj.nTrk] = c->track.trkPhi[it];
         ++gj.nTrk;
      }
      
      // All done
      tjt->Fill();
   }
   
   output->Write();
   output->Close();
   delete c;
}
