#include <string>
#include <vector>
#include <iostream>
#include <TH2D.h>
#include <TH1D.h>
#include <TFile.h>
#include <TSystem.h>
#include <TTree.h>

#include "DataFormats/Math/interface/deltaR.h"

#if !defined(__CINT__) && !defined(__MAKECINT__)

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"

#endif

using namespace std;

static const int MAXJETS = 500;

void analyzeJetsAndTracks(const char* inf = "rfio:/castor/cern.ch/user/y/yilmaz/pat/CMSSW_3_6_0/UnquenchedDijet80to120_runs1to500.root", const char* outf = "output.root", double weight = 1){

  int maxEvents = 1000;

   bool doFastJet = false;

   string algo = "icPu5";
   const char* name = Form("%scalo",algo.data());
   const char* jetTag = Form("patJets",algo.data());
   const char* rhoTag = "iterativeConePu5CaloJets";
   const char* trackTag = "allTracks";

   double cone = 0.5;
   double genJetPtMin = 20.;
   const int nEtaBins = 4;
   double etaMin[nEtaBins] = {0.,0.,1.,2.};
   double etaMax[nEtaBins] = {5.,1.,2.,3.};

   TFile * centFile = new TFile("$CMSSW_BASE/src/RecoHI/HiCentralityAlgos/data/CentralityTables.root");
   TFile* infile = TFile::Open(inf);
   TFile* outFile = new TFile(outf,"recreate");

   infile->cd();
   fwlite::Event event(infile);
   outFile->cd();

   int nevents = event.size();
   weight = weight/nevents;

   TDirectory* dir = outFile->mkdir(name);
   dir->cd();

   TH1D* h1 = new TH1D("h1","histogram",100,0,100);

   TH1D::SetDefaultSumw2();

   CentralityBins::RunMap HFhitBinMap = getCentralityFromFile(centFile,"HFhits10_MC_Hydjet2760GeV_MC_3XY_V24_v0",0,2);
   double etMax[10] = {350,250,150,120,60,40,20,10,10,10};
   double histDrMax = 6;

   // loop the events
   unsigned int iEvent=0;
   for(event.toBegin(); !event.atEnd() && (maxEvents < 0 || iEvent < maxEvents); ++event, ++iEvent){
      edm::EventBase const & ev = event;
      if( iEvent % 100 == 0 ) cout<<"Processing event : "<<iEvent<<endl;

      edm::Handle<edm::GenHIEvent> mc;
      ev.getByLabel(edm::InputTag("heavyIon"),mc);
      edm::Handle<reco::Centrality> cent;
      ev.getByLabel(edm::InputTag("hiCentrality"),cent);

      double b = mc->b();
      double npart = mc->Npart();
      double ncoll = mc->Ncoll();
      double nhard = mc->Nhard();
      double phi0 = mc->evtPlane();

      double hf = cent->EtHFhitSum();

      int run = ev.id().run();
      run = 1;
      int bin = HFhitBinMap[run]->getBin(hf);

      edm::Handle<pat::JetCollection> jets;
      ev.getByLabel(edm::InputTag(jetTag),jets);

      edm::Handle<reco::RecoChargedCandidateCollection> tracks;
      ev.getByLabel(edm::InputTag(trackTag),tracks);

      edm::Handle<double> rho;
      if(doFastJet) ev.getByLabel(edm::InputTag(rhoTag,"rho"),rho);
    
      // LOOP OVER JETS
      for(int j = 0 ; j < jets->size(); ++j){
	 const pat::Jet& jet = (*jets)[j];
	 
	 if(jet.genJet() != 0){
	   double pt = jet.pt();

	    if(jet.genJet()->pt() < genJetPtMin) continue;

	    double genpt = jet.genJet()->pt();
	    double geneta = jet.genJet()->eta();

	    if(doFastJet){
	       // Fast jet PU subtraction - please check
	       // note that corrfactor is applied to background
	       // which should be equivalent to : [(raw pt) - (background)] -> correct
	       // good ???
	       pt = jet.pt() - (*rho)*jet.jetArea()*jet.corrFactor("abs");
	    }
	    h1->Fill(pt);
	 }
      }

      // LOOP OVER TRACKS
      for(int i = 0 ; i < tracks->size(); ++i){
	const reco::RecoChargedCandidate& track = (*tracks)[i];
	double pt = track.pt();
      }

   }
  
   dir->cd();
   h1->Write();
   dir->Write();
   outFile->Write();
   outFile->Close();
  
}
