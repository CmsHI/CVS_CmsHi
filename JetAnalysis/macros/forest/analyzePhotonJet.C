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
   int cBin;
   int nG;
   int nJ;
   int nT;
   int trig;
   int offlSel;
   int noiseFilt;
   float vz;
};

static const int MAXTRK = 10000;

class GammaJet{
public:
   GammaJet() :
   photonEt(-99),photonEta(0),photonPhi(0),
   jetEt(-99),jetEta(0),jetPhi(0),
   deta(-99),dphi(-99), Aj(-99),
   sigmaIetaIeta(-99)
   {}
   float photonEt;
   float photonEta;
   float photonPhi;
   float jetEt;
   float jetEta;
   float jetPhi;
   float deta;
   float dphi;
   float Aj;
   float sigmaIetaIeta;
   float isol;
   void clear() {
      photonEt=-99; photonEta=0; photonPhi=0;
      jetEt=-99; jetEta=0; jetPhi=0;
      deta=-99; dphi=-99; Aj=-99;
      sigmaIetaIeta=-99;
   }
};

void analyzePhotonJet(
                      //TString inname="/d100/velicanu/forest/merged/HiForestPhoton_v1.root"
                      TString inname="/mnt/hadoop/cms/store/user/yinglu/MC_Production/photon50_50k/HiForest_Tree/photon50_50k.root"
                      
    )
{
   double cutphotonEt = 60;
   double cutphotonEta = 1.44;
   double cutjetEta = 2;
   
   // Define the input file and HiForest
   HiForest *c = new HiForest(inname);
   c->hasHltTree = 0;
   c->hasTrackTree=0;
   
   // Output file
   TFile *output = new TFile(Form("output-%.0f.root",cutphotonEt),"recreate");
   TTree * tgj = new TTree("tgj","gamma jet tree");
   
   EvtSel evt;
   GammaJet gj;
   tgj->Branch("evt",&evt.run,"run/I:evt:cBin:nG:nJ:nT:trig:offlSel:noiseFilt:vz/F");
   tgj->Branch("jet",&gj.photonEt,"photonEt/F:photonEta:photonPhi:jetEt:jetEta:jetPhi:deta:dphi:Agj:sigmaIetaIeta:isol");
   
   // Main loop
   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      
      // Event Info
      evt.run = c->evt.run;
      evt.evt = c->evt.evt;
      evt.cBin = c->evt.hiBin;
      evt.nG = c->photon.nPhotons;
      evt.nJ = c->icPu5.nref;
      evt.nT = c->track.nTrk;
      evt.trig = c->hlt.HLT_HIJet80_v1;
      evt.offlSel = c->skim.pcollisionEventSelection;
      evt.noiseFilt = c->skim.pHBHENoiseFilter;
      evt.vz = c->track.vz[1];
      if (i%1000==0) cout <<i<<" / "<<c->GetEntries() << " " << evt.run << " " << evt.evt << " " << evt.cBin << " " << c->track.nTrk <<endl;
      
      // initialize
      int leadingIndex=-1;
      int awayIndex=-1;
      float leadingAwayPt = 0;
      gj.clear();
      
      // Loop over jets to look for leading jet candidate in the event
      for (int j=0;j<c->photon.nPhotons;j++) {
         if (c->photon.pt[j]<cutphotonEt) break;          // photon pT cut, assuming that et is sorted
         if (fabs(c->photon.eta[j])>cutphotonEta) continue; // |eta|<1.44
         if (c->isSpike(j)) continue;               // spike removal
         if (!c->isGoodPhoton(j)) continue;         // hiGoodPhoton cut
         leadingIndex = j;
         break;
      }
      
      // Found a leading jet which passed basic quality cut!
      if (leadingIndex!=-1) {
         // set leading photon
         gj.photonEt=c->photon.pt[leadingIndex];
         gj.photonEta=c->photon.eta[leadingIndex];
         gj.photonPhi=c->photon.phi[leadingIndex];
         gj.sigmaIetaIeta=c->photon.sigmaIetaIeta[leadingIndex];
         gj.isol=(c->photon.cr4[leadingIndex]+c->photon.cc4[leadingIndex]+c->photon.ct4PtCut20[leadingIndex]);
         
         // intialize jet variables
//         int nJets=c->akPu3PF.nref;
//         float *jet_pt  = c->akPu3PF.jtpt;
//         float *jet_eta = c->akPu3PF.jteta;
//         float *jet_phi = c->akPu3PF.jtphi;
         int nJets=c->icPu5.nref;
         float *jet_pt  = c->icPu5.jtpt;
         float *jet_eta = c->icPu5.jteta;
         float *jet_phi = c->icPu5.jtphi;
         // Loop over jet tree to find a away side leading jet
         for (int j=0;j<nJets;j++) {
            if (jet_pt[j]<40) break;
            if (fabs(jet_eta[j])>cutjetEta) continue;
            if (fabs(deltaPhi(jet_phi[j],c->photon.phi[leadingIndex]))<0.3) continue;
            if (jet_pt[j]>leadingAwayPt) {
               leadingAwayPt = jet_pt[j];
               awayIndex = j;
            }
            break;
         }	 
         
         // Found an away jet!
         if (awayIndex !=-1) {
            double photonEt = c->photon.pt[leadingIndex];
            double jetEt = jet_pt[awayIndex];
            double Agj = (photonEt-jetEt)/(photonEt+jetEt);
            gj.jetEt  = jetEt;
            gj.jetEta = jet_eta[awayIndex];
            gj.jetPhi = jet_phi[awayIndex];
            gj.deta = jet_eta[awayIndex] - c->photon.eta[leadingIndex];
            gj.dphi = deltaPhi(jet_phi[awayIndex],c->photon.phi[leadingIndex]);
            gj.Aj   = Agj;
         }
      }
      
      // All done
      tgj->Fill();
   }
   
   output->Write();
   output->Close();
   delete c;
}
