#include <map>
#include <string>
//#include <vector>
//#include <sstream>
//#include <fstream>
//#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
//#include <TROOT.h>
//#include <TFile.h>
//#include <TSystem.h>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"


class HiPatBasicAnalyzer : public edm::EDAnalyzer {

public:
  explicit HiPatBasicAnalyzer(const edm::ParameterSet&);
  ~HiPatBasicAnalyzer();
  
private:

  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  // simple map to contain all 1D histograms; 
  // histograms are booked in the beginJob() 
  // method
  std::map<std::string,TH1F*> histContainer_; 
  // compare muons, jets to genParticles and genJets 
  TH2F* jetPtGenPt_;
  TH2F* muonPtGenPt_;

  // input tags  
  edm::InputTag photonSrc_;
  edm::InputTag muonSrc_;
  edm::InputTag jetSrc_;

};
 
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"

HiPatBasicAnalyzer::HiPatBasicAnalyzer(const edm::ParameterSet& iConfig):
  histContainer_(),
  photonSrc_(iConfig.getUntrackedParameter<edm::InputTag>("photonSrc")),
  muonSrc_(iConfig.getUntrackedParameter<edm::InputTag>("muonSrc")),
  jetSrc_(iConfig.getUntrackedParameter<edm::InputTag>("jetSrc" ))
{
}

HiPatBasicAnalyzer::~HiPatBasicAnalyzer()
{
}

void 
HiPatBasicAnalyzer::beginJob(const edm::EventSetup&)
{
  // register to the TFileService
  edm::Service<TFileService> fs;

  // book  histograms
  histContainer_["muonPt"] = fs->make<TH1F>("muonPt", "muon pt",    100,  0.,100.);
  histContainer_["muonEta"] = fs->make<TH1F>("muonEta","muon eta",   100, -3.,  3.);
  histContainer_["muonPhi"] = fs->make<TH1F>("muonPhi","muon phi",   100, -5.,  5.);  

  histContainer_["photonPt"] = fs->make<TH1F>("photonPt", "photon pt",    100,  0.,100.);
  histContainer_["photonEta"] = fs->make<TH1F>("photonEta","photon eta",   100, -3.,  3.);
  histContainer_["photonPhi"] = fs->make<TH1F>("photonPhi","photon phi",   100, -5.,  5.);
  histContainer_["photonIsolationCC3"] = fs->make<TH1F>("photonIsolationCC3",
                                                        "photon isolation variable CC3",
                                                        100, -10., 10.);

  histContainer_["jetPt"] = fs->make<TH1F>("jetPt", "jet pt",    100,  0.,300.);
  histContainer_["jetEta"] = fs->make<TH1F>("jetEta","jet eta",   100, -3.,  3.);
  histContainer_["jetPhi"] = fs->make<TH1F>("jetPhi","jet phi",   100, -5.,  5.);

  muonPtGenPt_ = fs->make<TH2F>("muonPtGenPt",
                                "matched MC muon pt vs reco muon pt",
                                100, 0.,100.,100,0.,100.);

  jetPtGenPt_ = fs->make<TH2F>("jetPtGenPt", 
                               "genJet pt vs matched IC5 jet pt",
                               100, 0.,100.,100,0.,100);
}

void
HiPatBasicAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // get muon collection
  edm::Handle<edm::View<pat::Muon> > muons;
  iEvent.getByLabel(muonSrc_,muons);

  // get jet collection
  edm::Handle<edm::View<pat::Jet> > jets;
  iEvent.getByLabel(jetSrc_,jets);

  // get photon collection  
  edm::Handle<edm::View<pat::Photon> > photons;
  iEvent.getByLabel(photonSrc_,photons);


    
  // loop muon collection and fill histograms
  for(edm::View<pat::Muon>::const_iterator muon=muons->begin(); muon!=muons->end(); ++muon){
    histContainer_["muonPt"]->Fill( muon->pt() );
    histContainer_["muonEta"]->Fill( muon->eta() );
    histContainer_["muonPhi"]->Fill( muon->phi() );

    // If there is a matched genParticle to the muon, 
    // get the pt 
    if( muon->genLepton() != NULL )
      muonPtGenPt_->Fill( muon->genLepton()->pt(), muon->pt() );
  }

  // loop photon collection and fill histograms
  for(edm::View<pat::Photon>::const_iterator photon=photons->begin(); photon!=photons->end(); ++photon){
    histContainer_["photonPt"]->Fill( photon->pt() );
    histContainer_["photonEta"]->Fill( photon->eta() );
    histContainer_["photonPhi"]->Fill( photon->phi() );
    histContainer_["photonIsolationCC3"]->Fill( photon->userFloat("isoCC3") );
  }

  // loop jet collection and fill histograms
  for(edm::View<pat::Jet>::const_iterator jet=jets->begin(); jet!=jets->end(); ++jet){
    histContainer_["jetPt"]->Fill( jet->pt() );
    histContainer_["jetEta"]->Fill( jet->eta() );
    histContainer_["jetPhi"]->Fill( jet->phi() );

    // If there is a matched genJet to the jet, 
    // get the pt 
    if( jet->genJet() != NULL )
      jetPtGenPt_->Fill( jet->genJet()->pt(), jet->pt() );
  }

}


void 
HiPatBasicAnalyzer::endJob() 
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(HiPatBasicAnalyzer);
