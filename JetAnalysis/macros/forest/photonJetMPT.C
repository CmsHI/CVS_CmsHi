#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>

// MPT Classes and functions
const int nptrange = 8;
float ptranges[nptrange+1] = {0.5,1,2,4,8,16,32,64,128};

class MPT {
public:
   TString name;
   float dRMin;
   float dRMax;
   float ptMin;
   float etaMax;
   
   float mptx;
   float mpty;
   float mptx_pt[nptrange];
   float mpty_pt[nptrange];
   
   MPT(TString s, float drmin=0, float drmax=1e3, float ptmin=0.5, float etamax=2.4) :
   name(s), dRMin(drmin), dRMax(drmax),ptMin(ptmin), etaMax(etamax) {
      clear();
   }
   void clear() {
      mptx = 0; mpty = 0;
      for (int i=0; i<nptrange; ++i) {
         mptx_pt[i] =0; mpty_pt[i] = 0;
      }      
   }
};

void CalcMPT(const HiForest * c, int iphoton, int ijet, MPT & m)
{
   m.clear();
   for (int it=0; it<c->track.nTrk; ++it) {
      float trkPt = c->track.trkPt[it];
      float trkEta = c->track.trkEta[it];
      float trkPhi = c->track.trkPhi[it];
      if (trkPt < m.ptMin) continue;
      if (fabs(trkEta) > m.etaMax) continue;
      float drG = deltaR(trkEta,trkPhi,c->photon.eta[iphoton],c->photon.phi[iphoton]);
      if (drG<m.dRMin || drG>m.dRMax) continue;
      float drJ = deltaR(trkEta,trkPhi,c->akPu3PF.jteta[ijet],c->akPu3PF.jtphi[ijet]);
      if (drJ<m.dRMin || drJ>m.dRMax) continue;
      float ptx = trkPt * cos(deltaPhi(trkPhi,c->photon.phi[iphoton]));
      float pty = trkPt * sin(deltaPhi(trkPhi,c->photon.phi[iphoton]));
      m.mptx += ptx;
      m.mpty += pty;
      for (int k=0; k<nptrange; ++k) {
         if (trkPt> ptranges[k] && trkPt<ptranges[k+1]) {
            m.mptx_pt[k]+= ptx;
            m.mpty_pt[k]+= pty;
         }
      }
   }  
}

void SetMPTBranches(TTree * t, MPT & m)
{
   t->Branch("mptx"+m.name,&m.mptx,"mptx"+m.name+"/F");
   t->Branch("mpty"+m.name,&m.mpty,"mpty"+m.name+"/F");
   TString sbrxpt = Form("mptx_pt%s[%d]/F",m.name.Data(),nptrange);
   TString sbrypt = Form("mpty_pt%s[%d]/F",m.name.Data(),nptrange);
   cout << sbrxpt << ", " << sbrypt << endl;
   t->Branch("mptx_pt"+m.name,m.mptx_pt,sbrxpt);
   t->Branch("mpty_pt"+m.name,m.mpty_pt,sbrypt);
}

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
   
   // Output
   TTree * tgj = new TTree("tgj","gammajet");

   EvtSel evt;
   GammaJet gj;
   tgj->Branch("evt",&evt.run,"run/I:evt:cbin:vz/F");
   tgj->Branch("jet",&gj.gpt,"gpt/F:geta:gphi:jpt:jeta:jphi:deta:dphi:Aj");
   vector<MPT> vmpt;
   vmpt.push_back(MPT("AllEta"));
   vmpt.push_back(MPT("InCone",0,0.8));
   vmpt.push_back(MPT("OutCone",0.8,1e3));
   for (int m=0; m<vmpt.size(); ++m) { SetMPTBranches(tgj,vmpt[m]); }
   
   // Main loop
   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<endl;
      
      // Event Info
      evt.run = c->hlt.Run;
      evt.evt = c->hlt.Event;
      evt.cbin = c->photon.cBin;
      evt.vz = c->track.vz[1];
      //cout << evt.run << " " << evt.evt << " " << evt.cbin << " " << evt.vz << endl;
      
      int leadingPhoton=-1;
      int leadingJet=-1;
      gj.clear();
      
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
         }
      }
      tgj->Fill();
   }
   
   output->Write();
   output->Close();
   delete c;
}
