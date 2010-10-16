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
// $Id: RecHitTreeProducer.cc,v 1.1 2010/09/23 13:28:28 yilmaz Exp $
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

#define MAXHITS 100000

struct MyRecHit{

  int n;

  float e[MAXHITS];
  float et[MAXHITS];
  float eta[MAXHITS];
  float phi[MAXHITS];

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

   edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > jets1;
   edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > jets2;

   //   typedef edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > >::const_iterator EcalIterator;
   typedef vector<EcalRecHit>::const_iterator EcalIterator;

   edm::Handle<reco::CaloJetCollection> signalJets;

  MyRecHit hbheRecHit;
  MyRecHit hfRecHit;

  TTree* hbheTree;
  TTree* hfTree;

   double cone;

   edm::Service<TFileService> fs;
   const CentralityBins * cbins_;
   const CaloGeometry *geo;

  edm::InputTag HcalRecHitHFSrc_;
  edm::InputTag HcalRecHitHBHESrc_;


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
  HcalRecHitHFSrc_ = iConfig.getUntrackedParameter<edm::InputTag>("hcalHFRecHitSrc",edm::InputTag("hfreco"));
  HcalRecHitHBHESrc_ = iConfig.getUntrackedParameter<edm::InputTag>("hcalHBHERecHitSrc",edm::InputTag("hbhereco"));
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

  edm::Handle<HFRecHitCollection> hfHits;
  edm::Handle<HBHERecHitCollection> hbheHits;

  ev.getByLabel(HcalRecHitHFSrc_,hfHits);
  ev.getByLabel(HcalRecHitHBHESrc_,hbheHits);


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
     //     hfRecHit.ieta[hfRecHit.n] = hit.id().ieta();
     //     hfRecHit.iphi[hfRecHit.n] = hit.id().iphi();
     
     hfRecHit.n++;
   }

   for(unsigned int i = 0; i < hbheHits->size(); ++i){
     const HBHERecHit & hit= (*hbheHits)[i];
     hbheRecHit.e[hfRecHit.n] = hit.energy();
     hbheRecHit.et[hfRecHit.n] = getEt(hit.id(),hit.energy());
     hbheRecHit.eta[hfRecHit.n] = getEta(hit.id());
     hbheRecHit.phi[hfRecHit.n] = getPhi(hit.id());
     //     hbheRecHit.ieta[hfRecHit.n] = hit.id().ieta();
     //     hbheRecHit.iphi[hfRecHit.n] = hit.id().iphi();

     hbheRecHit.n++;
   }

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

  hfTree = fs->make<TTree>("hf","");
  hfTree->Branch("n",&hfRecHit.n,"n/I");
  hfTree->Branch("e",hfRecHit.e,"e[n]/F");
  hfTree->Branch("et",hfRecHit.et,"et[n]/F");
  hfTree->Branch("eta",hfRecHit.eta,"eta[n]/F");
  hfTree->Branch("phi",hfRecHit.phi,"phi[n]/F");

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
