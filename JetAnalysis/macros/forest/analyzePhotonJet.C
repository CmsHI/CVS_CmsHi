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
    void clear() {
      photonEt=-99; photonEta=0; photonPhi=0;
      jetEt=-99; jetEta=0; jetPhi=0;
      deta=-99; dphi=-99; Aj=-99;
      sigmaIetaIeta=-99;
    }
};

void analyzePhotonJet(TString inname="/d00/yjlee/hiForest/PromptReco2011/HIHighPt/skim_icPu5Jet80/merged_HIData2011_HIHighPt_highPtExercise_icPu5JetSkim80GeVjetEta.root")
{
  double cutphotonEt = 70;
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
  tgj->Branch("evt",&evt.run,"run/I:evt:cbin:nG:nJ:nT:trig:offlSel:noiseFilt:vz/F");
  tgj->Branch("jet",&gj.photonEt,"photonEt/F:photonEta:photonPhi:jetEt:jetEta:jetPhi:deta:dphi:Aj:sigmaIetaIeta");

  // Main loop
  for (int i=0;i<c->GetEntries();i++)
  {
    c->GetEntry(i);

    // Event Info
    evt.run = c->evt.run;
    evt.evt = c->evt.evt;
    evt.cbin = c->evt.hiBin;
    evt.nG = c->photon.nPhotons;
    evt.nJ = c->icPu5.nref;
    evt.nT = c->track.nTrk;
    evt.trig = c->hlt.HLT_HIJet80_v1;
    evt.offlSel = c->skim.pcollisionEventSelection;
    evt.noiseFilt = c->skim.pHBHENoiseFilter;
    evt.vz = c->track.vz[1];
    if (i%1000==0) cout <<i<<" / "<<c->GetEntries() << " " << evt.run << " " << evt.evt << " " << evt.cbin << " " << c->track.nTrk <<endl;

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
      // set leading jet
      gj.photonEt=c->photon.pt[leadingIndex];
      gj.photonEta=c->photon.eta[leadingIndex];
      gj.photonPhi=c->photon.phi[leadingIndex];
      gj.sigmaIetaIeta=c->photon.sigmaIetaIeta[leadingIndex];

      // Loop over jet tree to find a away side leading jet
      for (int j=0;j<c->akPu3PF.nref;j++) {
	if (c->akPu3PF.jtpt[j]<40) break;
	if (fabs(c->akPu3PF.jteta[j])>cutjetEta) continue;
	if (fabs(deltaPhi(c->akPu3PF.jtphi[j],c->photon.phi[leadingIndex]))<0.3) continue;
	if (c->akPu3PF.jtpt[j]>leadingAwayPt) {
	  leadingAwayPt = c->akPu3PF.jtpt[j];
	  awayIndex = j;
	}
	break;
      }	 

      // Found an away jet!
      if (awayIndex !=-1) {
	double photonEt = c->photon.pt[leadingIndex];
	double jetEt = c->akPu3PF.jtpt[awayIndex];
	double Agj = (photonEt-jetEt)/(photonEt+jetEt);
	gj.jetEt  = jetEt;
	gj.jetEta = c->akPu3PF.jteta[awayIndex];
	gj.jetPhi = c->akPu3PF.jtphi[awayIndex];
	gj.deta = c->akPu3PF.jteta[awayIndex] - c->photon.eta[leadingIndex];
	gj.dphi = deltaPhi(c->akPu3PF.jtphi[awayIndex],c->photon.phi[leadingIndex]);
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
