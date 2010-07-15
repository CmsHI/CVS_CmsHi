#include <string>
#include <vector>
#include <iostream>

#include <TH2D.h>
#include <TH1D.h>
#include <TFile.h>
#include <TSystem.h>
#include <TNtuple.h>

#if !defined(__CINT__) && !defined(__MAKECINT__)

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#endif

using namespace std;


void analyzeMC(){

   TFile * centFile = new TFile("~/cvs/UserCode/CmsHi/JulyExercise/data/CentralityTables.root");
   TFile* infile = new TFile("./JulyExerciseGEN_runs101to200.root");

  fwlite::Event event(infile);
  TFile* outFile = new TFile("test.root","recreate");

  TH1D::SetDefaultSumw2();
  TH2D* hNpart = new TH2D("hNpart",";Npart Truth;Npart RECO",50,0,500,50,0,500);
  TH1D* hBins = new TH1D("hBins",";bins;events",44,-1,21);

  TNtuple * nt = new TNtuple("nt","nt","pt:eta:phi:id");
  TNtuple * hi = new TNtuple("hi","hi","npart:ncoll:nhard:b");
  TNtuple * ntp = new TNtuple("ntp","nt","pt:eta:phi:pdg:id");
  TNtuple * ntsub = new TNtuple("ntsub","nt","pt:eta:phi:pdg:id:nsub");

  CentralityBins::RunMap HFhitBinMap = getCentralityFromFile(centFile,"HFhits20_MXS0_Hydjet4TeV_MC_3XY_V21_v0",0,20);

  // loop the events
  unsigned int iEvent=0;
  for(event.toBegin(); !event.atEnd(); ++event, ++iEvent){
     edm::EventBase const & ev = event;
    if( iEvent % 10 == 0 ) cout<<"Processing event : "<<iEvent<<endl;

    edm::Handle<reco::GenParticleCollection> parts;
    edm::Handle<edm::GenHIEvent> mc;
    ev.getByLabel(edm::InputTag("heavyIon"),mc);


    edm::Handle<reco::Centrality> cent;
    ev.getByLabel(edm::InputTag("hiCentrality"),cent);

    double b = mc->b();
    double npart = mc->Npart();
    double ncoll = mc->Ncoll();
    double nhard = mc->Nhard();
    int nsubs = -1;

    if(iEvent < 100){
       ev.getByLabel(edm::InputTag("hiGenParticles"),parts);
       mc->setGenParticles(parts.product());
       nsubs = mc->getNsubs();
    }


    hi->Fill(npart,ncoll,nhard,b,nsubs);

    if(0){

    edm::Handle<reco::Centrality> cent;
    ev.getByLabel(edm::InputTag("hiCentrality"),cent);


    double hf = cent->EtHFhitSum();
    double hftp = cent->EtHFtowerSumPlus();
    double hftm = cent->EtHFtowerSumMinus();
    double eb = cent->EtEBSum();
    double eep = cent->EtEESumPlus();
    double eem = cent->EtEESumMinus();

    int run = ev.id().run();

    int bin = HFhitBinMap[run]->getBin(hf);
    hBins->Fill(bin);

    double npartMean = HFhitBinMap[run]->NpartMean(hf);
    double npartSigma = HFhitBinMap[run]->NpartSigma(hf);
    hNpart->Fill(npart,npartMean);
    }

    edm::InputTag jetTag("iterativeCone5HiGenJets");
    edm::Handle<reco::GenJetCollection> jets;
    ev.getByLabel(jetTag,jets);
    for(int j = 0 ; j < jets->size(); ++j){
       const reco::GenJet & jet = (*jets)[j];
       const reco::GenParticle* constit = jet.getGenConstituent(0);
       int subid = constit->collisionId();

       double pt = jet.pt();
       double phi = jet.phi();
       double eta = jet.eta();

       nt->Fill(pt,eta,phi,subid);
    }


    if(iEvent < 100){       
       for(int j = 0 ; j < parts->size(); ++j){
	  const reco::GenParticle & p = (*parts)[j];
	  
	  double pt = p.pt();
	  double phi = p.phi();
	  double eta = p.eta();
          double pdg = p.pdgId();
	  int subid = p.collisionId();
	  
	  ntp->Fill(pt,eta,phi,pdg,subid);
       }
       for(int i = 0; i < nsubs; ++i){
	  const std::vector<reco::GenParticleRef>  sparts = mc->getSubEvent(i);
	  for(int j = 0; j < sparts.size(); ++j){
	     reco::GenParticleRef p = sparts[j];
	     double pt = p->pt();
	     double phi = p->phi();
	     double eta = p->eta();
	     double pdg = p->pdgId();
	     int subid = p->collisionId();

	     ntsub->Fill(pt,eta,phi,pdg,subid);

	  }

       }
    }



  }

  outFile->cd();
  nt->Write();
  hBins->Write();
  hNpart->Write();
  outFile->Write();
  
}
