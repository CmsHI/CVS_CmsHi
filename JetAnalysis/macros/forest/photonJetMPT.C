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
   float vz;
};

class GammaJet{
public:
   GammaJet() :
   gpt(-99),geta(0),gphi(0),
   jpt(-99),jeta(0),jphi(0),
   deta(-99),dphi(-99), Aj(-99)
   {}
   float gpt;
   float geta;
   float gphi;
   float jpt;
   float jeta;
   float jphi;
   float deta;
   float dphi;
   float Aj;
   void clear() {
      gpt=-99; geta=0; gphi=0;
      jpt=-99; jeta=0; jphi=0;
      deta=-99; dphi=-99; Aj=-99;
   }
};

void photonJetMPT(double etCut=40)
{
   // Define the input file and HiForest
   HiForest *c = new HiForest("../trees/merged_HI2010_SD_Photon40_prod02-spikeRemoved.root");
   
   // Output file
   TFile *output = new TFile(Form("output-%.0f.root",etCut),"recreate");
   
   // Agj histograms for different centralities
   TH1D *h1 = new TH1D("h1","",100,-1,1);
   TH1D *h2 = new TH1D("h2","",100,-1,1);
   TH1D *h3 = new TH1D("h3","",100,-1,1);
   TH1D *h4 = new TH1D("h4","",100,-1,1);
   // trk monitoring
   TH1D * hTrkPt = new TH1D("hTrkPt","",nptrange,ptranges);
   TH1D * hTrkEta = new TH1D("hTrkEta","",40,-2.4,2.4);
   TH1D * hTrkPhi = new TH1D("hTrkPhi","",40,-3.14,3.14);
   
   // Output
   TTree * tgj = new TTree("tgj","gammajet");

   EvtSel evt;
   GammaJet gj;
   tgj->Branch("evt",&evt.run,"run/I:evt:cbin:vz/F");
   tgj->Branch("jet",&gj.gpt,"gpt/F:geta:gphi:jpt:jeta:jphi:deta:dphi:Aj");
   vector<MPT> vmpt;
   vmpt.push_back(MPT("AllAcc"));
   vmpt.push_back(MPT("InCone",1,0.8));
   vmpt.push_back(MPT("OutCone",2,0.8));
   for (unsigned m=0; m<vmpt.size(); ++m) { 
      cout << "CalcMPT for " << vmpt[m].name << " dRCone: " << vmpt[m].dRCone << endl;
      SetMPTBranches(tgj,vmpt[m]);
   }
   
   // Main loop
   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      
      // Event Info
      evt.run = c->hlt.Run;
      evt.evt = c->hlt.Event;
      evt.cbin = c->photon.cBin;
      evt.vz = c->track.vz[1];
      if (i%1==0) cout <<i<<" / "<<c->GetEntries() << " " << evt.run << " " << evt.evt << " " << evt.cbin << " " << c->track.nTrk <<endl;
      
      int leadingPhoton=-1;
      int leadingJet=-1;
      gj.clear();
      for (unsigned m=0; m<vmpt.size(); ++m) vmpt[m].clear();
      
      // Loop over photons to look for leading photon candidate in the event
      for (int j=0;j<c->photon.nPhotons;j++) {
         if (c->photon.et[j]<etCut) break;          // photon pT cut, assuming that et is sorted
         if (fabs(c->photon.eta[j])>1.44) continue; // |eta|<1.44
         if (c->isSpike(j)) continue;               // spike removal
         if (!c->isGoodPhoton(j)) continue;         // hiGoodPhoton cut
         leadingPhoton=j;  
         break;  
      }	 
      
      // Found a leading photon which passed basic quality cut!
      if (leadingPhoton!=-1) {
         gj.gpt=c->photon.et[leadingPhoton];
         gj.geta=c->photon.eta[leadingPhoton];
         gj.gphi=c->photon.phi[leadingPhoton];
         
         // Loop over jet tree to find a away side leading jet
         for (int j=0;j<c->akPu3PF.nref;j++) {
            if (c->akPu3PF.jtpt[j]<25) break;
            if (fabs(c->akPu3PF.jteta[j])>2) continue;
            if (fabs(deltaPhi(c->akPu3PF.jtphi[j],c->photon.phi[leadingPhoton]))<2.5) continue;
            leadingJet = j;
            break;
         }	 
         // Trk Monitoring
         for (int it=0; it<c->track.nTrk; ++it) {
            hTrkPt->Fill(c->track.trkPt[it]);
            hTrkEta->Fill(c->track.trkEta[it]);
            hTrkPhi->Fill(c->track.trkPhi[it]);
         }
         
         // Found a leading jet!
         if (leadingJet !=-1) {
            double photonEt = c->photon.et[leadingPhoton];
            double jetPt = c->akPu3PF.jtpt[leadingJet];
            double Agj = (photonEt-jetPt)/(photonEt+jetPt);
            if (c->photon.cBin<4) h1->Fill(Agj);
            if (c->photon.cBin>=4&&c->photon.cBin<12) h2->Fill(Agj);
            if (c->photon.cBin>=12&&c->photon.cBin<20) h3->Fill(Agj);
            if (c->photon.cBin>=20) h4->Fill(Agj);
            gj.jpt  = jetPt;
            gj.jeta = c->akPu3PF.jteta[leadingJet];
            gj.jphi = c->akPu3PF.jtphi[leadingJet];
            gj.deta = c->akPu3PF.jteta[leadingJet] - c->photon.eta[leadingPhoton];
            gj.dphi = deltaPhi(c->akPu3PF.jtphi[leadingJet],c->photon.phi[leadingPhoton]);
            gj.Aj   = Agj;
            // MPT
            for (unsigned m=0; m<vmpt.size(); ++m) {
               CalcMPT(c,gj.geta,gj.gphi,gj.jeta,gj.jphi,vmpt[m]);
            }
         }
      }
      tgj->Fill();
   }
   
   output->Write();
   output->Close();
   delete c;
}
