// -*- C++ -*-
//
// Package:    RecHitTreeProducer
// Class:      RecHitTreeProducer
// 
/**\class RecHitTreeProducer RecHitTreeProducer.cc CmsHi/RecHitTreeProducer/src/RecHitTreeProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Yetkin Yilmaz
//         Created:  Tue Sep  7 11:38:19 EDT 2010
// $Id: RecHitTreeProducer.cc,v 1.3 2010/10/20 15:01:11 nart Exp $
//
//


// system include files
#include <memory>
#include <vector>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/DetId/interface/DetId.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/EcalDetId/interface/EcalDetIdCollections.h"
#include "DataFormats/DetId/interface/DetId.h"


#include "TNtuple.h"

using namespace std;

#define MAXHITS 1000000

struct MyRecHit{

  int n;

  float e[MAXHITS];
  float et[MAXHITS];
  float eta[MAXHITS];
  float phi[MAXHITS];
  bool isjet[MAXHITS];

};



//
// class declaration
//

class RecHitTreeProducer : public edm::EDAnalyzer {
   public:
      explicit RecHitTreeProducer(const edm::ParameterSet&);
      ~RecHitTreeProducer();
  double       getEt(const DetId &id, double energy);
  double       getEta(const DetId &id);
  double       getPhi(const DetId &id);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------

   edm::Handle<reco::Centrality> cent;
   edm::Handle<vector<double> > ktRhos;
   edm::Handle<vector<double> > akRhos;

  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > ebHits;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > eeHits;

  edm::Handle<HFRecHitCollection> hfHits;
  edm::Handle<HBHERecHitCollection> hbheHits;

  typedef vector<EcalRecHit>::const_iterator EcalIterator;
  
  edm::Handle<reco::CaloJetCollection> jets;
  
  MyRecHit hbheRecHit;
  MyRecHit hfRecHit;
  MyRecHit ebRecHit;
  MyRecHit eeRecHit;

  TTree* hbheTree;
  TTree* hfTree;
  TTree* ebTree;
  TTree* eeTree;
  double cone;

   edm::Service<TFileService> fs;
   const CentralityBins * cbins_;
   const CaloGeometry *geo;

  edm::InputTag HcalRecHitHFSrc_;
  edm::InputTag HcalRecHitHBHESrc_;
  edm::InputTag EBSrc_;
  edm::InputTag EESrc_;
  edm::InputTag JetSrc_;
  bool excludeJets_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
RecHitTreeProducer::RecHitTreeProducer(const edm::ParameterSet& iConfig) :
   cbins_(0),
   geo(0),
   cone(0.5)
{
   //now do what ever initialization is needed

  EBSrc_ = iConfig.getUntrackedParameter<edm::InputTag>("EBRecHitSrc",edm::InputTag("ecalRecHit","EcalRecHitsEB"));
  EESrc_ = iConfig.getUntrackedParameter<edm::InputTag>("EERecHitSrc",edm::InputTag("ecalRecHit","EcalRecHitsEE"));
  HcalRecHitHFSrc_ = iConfig.getUntrackedParameter<edm::InputTag>("hcalHFRecHitSrc",edm::InputTag("hfreco"));
  HcalRecHitHBHESrc_ = iConfig.getUntrackedParameter<edm::InputTag>("hcalHBHERecHitSrc",edm::InputTag("hbhereco"));
  JetSrc_ = iConfig.getUntrackedParameter<edm::InputTag>("JetSrc",edm::InputTag("iterativeCone5CaloJets"));
  excludeJets_ = iConfig.getUntrackedParameter<bool>("excludeJets",false);
}


RecHitTreeProducer::~RecHitTreeProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
RecHitTreeProducer::analyze(const edm::Event& ev, const edm::EventSetup& iSetup)
{

  hfRecHit.n = 0;
  hbheRecHit.n = 0;
  ebRecHit.n = 0;
  eeRecHit.n = 0;

  ev.getByLabel(EBSrc_,ebHits);
  ev.getByLabel(EESrc_,eeHits);

  ev.getByLabel(HcalRecHitHFSrc_,hfHits);
  ev.getByLabel(HcalRecHitHBHESrc_,hbheHits);


  if(!excludeJets_) {
    ev.getByLabel(JetSrc_,jets);
  }
  
   if(0 && !cbins_) cbins_ = getCentralityBinsFromDB(iSetup);

   if(!geo){
      edm::ESHandle<CaloGeometry> pGeo;
      iSetup.get<CaloGeometryRecord>().get(pGeo);
      geo = pGeo.product();
   }
   
   for(unsigned int i = 0; i < hfHits->size(); ++i){
     const HFRecHit & hit= (*hfHits)[i];
     hfRecHit.e[hfRecHit.n] = hit.energy();
     hfRecHit.et[hfRecHit.n] = getEt(hit.id(),hit.energy());
     hfRecHit.eta[hfRecHit.n] = getEta(hit.id());
     hfRecHit.phi[hfRecHit.n] = getPhi(hit.id());
     hfRecHit.isjet[hfRecHit.n] = false;
     if(!excludeJets_){
       for(unsigned int j = 0 ; j < jets->size(); ++j){
	 const reco::Jet& jet = (*jets)[j];
	 double dr = reco::deltaR(hfRecHit.eta[hfRecHit.n],hfRecHit.phi[hfRecHit.n],jet.eta(),jet.phi());
	 if(dr < cone){ hfRecHit.isjet[hfRecHit.n] = true; }
       }
     }
     hfRecHit.n++;
   }
   
   for(unsigned int i = 0; i < hbheHits->size(); ++i){
     const HBHERecHit & hit= (*hbheHits)[i];
     hbheRecHit.e[hbheRecHit.n] = hit.energy();
     hbheRecHit.et[hbheRecHit.n] = getEt(hit.id(),hit.energy());
     hbheRecHit.eta[hbheRecHit.n] = getEta(hit.id());
     hbheRecHit.phi[hbheRecHit.n] = getPhi(hit.id());
     hbheRecHit.isjet[hbheRecHit.n] = false; 
     if(!excludeJets_){
       for(unsigned int j = 0 ; j < jets->size(); ++j){
	 const reco::Jet& jet = (*jets)[j];
	 double dr = reco::deltaR(hbheRecHit.eta[hbheRecHit.n],hbheRecHit.phi[hbheRecHit.n],jet.eta(),jet.phi());
	 if(dr < cone){ hbheRecHit.isjet[hbheRecHit.n] = true; }
       }
     }
     hbheRecHit.n++;
   }
   
   for(unsigned int i = 0; i < ebHits->size(); ++i){
     const EcalRecHit & hit= (*ebHits)[i];
     ebRecHit.e[ebRecHit.n] = hit.energy();
     ebRecHit.et[ebRecHit.n] = getEt(hit.id(),hit.energy());
     ebRecHit.eta[ebRecHit.n] = getEta(hit.id());
     ebRecHit.phi[ebRecHit.n] = getPhi(hit.id());
     ebRecHit.isjet[ebRecHit.n] = false;
     if(!excludeJets_){
       for(unsigned int j = 0 ; j < jets->size(); ++j){
	 const reco::Jet& jet = (*jets)[j];
	 double dr = reco::deltaR(ebRecHit.eta[ebRecHit.n],ebRecHit.phi[ebRecHit.n],jet.eta(),jet.phi());
	 if(dr < cone){ ebRecHit.isjet[ebRecHit.n] = true; }
       }
     }
     ebRecHit.n++;
   }
   
   for(unsigned int i = 0; i < eeHits->size(); ++i){
     const EcalRecHit & hit= (*eeHits)[i];
     eeRecHit.e[eeRecHit.n] = hit.energy();
     eeRecHit.et[eeRecHit.n] = getEt(hit.id(),hit.energy());
     eeRecHit.eta[eeRecHit.n] = getEta(hit.id());
     eeRecHit.phi[eeRecHit.n] = getPhi(hit.id());
     eeRecHit.isjet[eeRecHit.n] = false;
     if(!excludeJets_){
       for(unsigned int j = 0 ; j < jets->size(); ++j){
	 const reco::Jet& jet = (*jets)[j];
	 double dr = reco::deltaR(eeRecHit.eta[eeRecHit.n],eeRecHit.phi[eeRecHit.n],jet.eta(),jet.phi());
	 if(dr < cone){ eeRecHit.isjet[eeRecHit.n] = true; }
       }
     }
     eeRecHit.n++;
   }
   
   eeTree->Fill();
   ebTree->Fill();
   
   hbheTree->Fill();
   hfTree->Fill();
   
}


// ------------ method called once each job just before starting event loop  ------------
void 
RecHitTreeProducer::beginJob()
{
  
  hbheTree = fs->make<TTree>("hbhe","");
  hbheTree->Branch("n",&hbheRecHit.n,"n/I");
  hbheTree->Branch("e",hbheRecHit.e,"e[n]/F");
  hbheTree->Branch("et",hbheRecHit.et,"et[n]/F");
  hbheTree->Branch("eta",hbheRecHit.eta,"eta[n]/F");
  hbheTree->Branch("phi",hbheRecHit.phi,"phi[n]/F");
  hbheTree->Branch("isjet",hbheRecHit.isjet,"isjet[n]/I");
  
  hfTree = fs->make<TTree>("hf","");
  hfTree->Branch("n",&hfRecHit.n,"n/I");
  hfTree->Branch("e",hfRecHit.e,"e[n]/F");
  hfTree->Branch("et",hfRecHit.et,"et[n]/F");
  hfTree->Branch("eta",hfRecHit.eta,"eta[n]/F");
  hfTree->Branch("phi",hfRecHit.phi,"phi[n]/F");
  hfTree->Branch("isjet",hfRecHit.isjet,"isjet[n]/I");

  eeTree = fs->make<TTree>("ee","");
  eeTree->Branch("n",&eeRecHit.n,"n/I");
  eeTree->Branch("e",eeRecHit.e,"e[n]/F");
  eeTree->Branch("et",eeRecHit.et,"et[n]/F");
  eeTree->Branch("eta",eeRecHit.eta,"eta[n]/F");
  eeTree->Branch("phi",eeRecHit.phi,"phi[n]/F");
  eeTree->Branch("isjet",eeRecHit.isjet,"isjet[n]/I");
 
  ebTree = fs->make<TTree>("eb","");
  ebTree->Branch("n",&ebRecHit.n,"n/I");
  ebTree->Branch("e",ebRecHit.e,"e[n]/F");
  ebTree->Branch("et",ebRecHit.et,"et[n]/F");
  ebTree->Branch("eta",ebRecHit.eta,"eta[n]/F");
  ebTree->Branch("phi",ebRecHit.phi,"phi[n]/F");
  ebTree->Branch("isjet",ebRecHit.isjet,"isjet[n]/O");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
RecHitTreeProducer::endJob() {
}

double RecHitTreeProducer::getEt(const DetId &id, double energy){
  const GlobalPoint& pos=geo->getPosition(id);
  double et = energy*sin(pos.theta());
  return et;
}

double RecHitTreeProducer::getEta(const DetId &id){
  const GlobalPoint& pos=geo->getPosition(id);
  double et = pos.eta();
  return et;
}

double RecHitTreeProducer::getPhi(const DetId &id){
  const GlobalPoint& pos=geo->getPosition(id);
  double et = pos.phi();
  return et;
}



//define this as a plug-in
DEFINE_FWK_MODULE(RecHitTreeProducer);
