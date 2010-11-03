// -*- C++ -*-
//
// Package:    EcalHistProducer
// Class:      EcalHistProducer
// 
/**\class EcalHistProducer EcalHistProducer.cc CmsHi/EcalHistProducer/src/EcalHistProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Yong Kim,32 4-A08,+41227673039,
//         Created:  Fri Oct 29 12:18:14 CEST 2010
// $Id: EcalHistProducer.cc,v 1.2 2010/11/03 18:28:45 kimy Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "CondFormats/DataRecord/interface/EcalChannelStatusRcd.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "CondFormats/EcalObjects/interface/EcalChannelStatus.h"

#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "RecoCaloTools/MetaCollections/interface/CaloRecHitMetaCollectionV.h"
#include "RecoCaloTools/MetaCollections/interface/CaloRecHitMetaCollections.h"
#include <Math/VectorUtil.h>
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"

//
// class declaration
//

class EcalHistProducer : public edm::EDAnalyzer {
   public:
      explicit EcalHistProducer(const edm::ParameterSet&);
      ~EcalHistProducer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------

   edm::Service<TFileService> fs;

   edm::InputTag photonSrc_;
   edm::InputTag ebReducedRecHitCollection_;
   edm::InputTag eeReducedRecHitCollection_;
   
   edm::InputTag basicClusterBarrel_;
   edm::InputTag basicClusterEndcap_;
   
   edm::InputTag superClusterBarrel_;
   edm::InputTag superClusterEndcap_;


   bool doSpikeClean_;
   TH1D*  NoE ;
   TH1D*  rhEE ;
   TH1D*  rhEB ;
   
   TTree* theTree;
   int nPho, nBC, nRH, nSC; 
   float energy[5000];
   float et[5000];
   float eta[5000];
   float phi[5000];
   
   float SCenergy[1000];
   float SCet[1000];
   float SCeta[1000];
   float SCphi[1000];
   

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
EcalHistProducer::EcalHistProducer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   //now do what ever initialization is needed                                                                                                         
   superClusterBarrel_                       = iConfig.getParameter<edm::InputTag>("superClusterBarrel"); // superclusters
   superClusterEndcap_                       = iConfig.getParameter<edm::InputTag>("superClusterEndcap"); // superclusters
   
   ebReducedRecHitCollection_       = iConfig.getParameter<edm::InputTag>("ebReducedRecHitCollection"); //,"reducedEcalRecHitsEB");            
   eeReducedRecHitCollection_       = iConfig.getParameter<edm::InputTag>("eeReducedRecHitCollection"); //,"reducedEcalRecHitsEE");        
   basicClusterBarrel_              = iConfig.getParameter<edm::InputTag>("basicClusterBarrel");
   basicClusterEndcap_              = iConfig.getParameter<edm::InputTag>("basicClusterEndcap");
   
   doSpikeClean_                    = iConfig.getUntrackedParameter<bool>("doSpikeClean",false);
   
}


EcalHistProducer::~EcalHistProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
EcalHistProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   //grab the photon collection                                                                                                                        
   NoE->Fill(0);
   
   //grab rechits                                                                               
   edm::Handle<EcalRecHitCollection> EBReducedRecHits;
   iEvent.getByLabel(ebReducedRecHitCollection_, EBReducedRecHits);
   const EcalRecHitCollection* rechitsCollectionBarrel = EBReducedRecHits.product();
   edm::Handle<EcalRecHitCollection> EEReducedRecHits;
   iEvent.getByLabel(eeReducedRecHitCollection_, EEReducedRecHits);
   const EcalRecHitCollection* rechitsCollectionEndcap = EEReducedRecHits.product();
   
   //Barrel 
   EcalRecHitCollection::const_iterator rh;
   for (rh = (*rechitsCollectionBarrel).begin(); rh!= (*rechitsCollectionBarrel).end(); rh++){
      rhEB->Fill(rh->energy());
   }
   //Endcap
   for (rh = (*rechitsCollectionEndcap).begin(); rh!= (*rechitsCollectionEndcap).end(); rh++){
      rhEE->Fill(rh->energy());
   }
   
   
   //lazy tool                                                                                             
   EcalClusterLazyTools lazyTool(iEvent, iSetup, ebReducedRecHitCollection_, eeReducedRecHitCollection_ );
   //grab basicClusters
   Handle<reco::CaloClusterCollection> basicClusterB;
   iEvent.getByLabel(basicClusterBarrel_, basicClusterB);
   Handle<reco::CaloClusterCollection> basicClusterE;
   iEvent.getByLabel(basicClusterEndcap_, basicClusterE);
  
   reco::CaloClusterCollection myBCs;
   for (reco::CaloClusterCollection::const_iterator bcItr = basicClusterB->begin(); bcItr != basicClusterB->end(); ++bcItr) {
      myBCs.push_back(*bcItr);
   }
   for (reco::CaloClusterCollection::const_iterator bcItr = basicClusterE->begin(); bcItr != basicClusterE->end(); ++bcItr) {
      myBCs.push_back(*bcItr);
   }

   
   nBC=0;
   for (reco::CaloClusterCollection::const_iterator bcItr = myBCs.begin(); bcItr != myBCs.end(); ++bcItr) {
      energy[nBC] = bcItr->energy();
      eta[nBC]    = bcItr->eta();
      phi[nBC]    = bcItr->phi();
      et[nBC]     = energy[nBC]/cosh(eta[nBC]);
      
      nBC++;
   }
   
   

   //grab superClusters                                                                                                                      
   Handle<reco::SuperClusterCollection> superClusterB;
   iEvent.getByLabel(superClusterBarrel_, superClusterB);
   Handle<reco::SuperClusterCollection> superClusterE;
   iEvent.getByLabel(superClusterEndcap_, superClusterE);

   reco::SuperClusterCollection mySCs;
   for (reco::SuperClusterCollection::const_iterator scItr = superClusterB->begin(); scItr != superClusterB->end(); ++scItr) {
      mySCs.push_back(*scItr);
   }
   for (reco::SuperClusterCollection::const_iterator scItr = superClusterE->begin(); scItr != superClusterE->end(); ++scItr) {
      mySCs.push_back(*scItr);
   }
   
   
   nSC=0;
   for (reco::SuperClusterCollection::const_iterator scItr = mySCs.begin(); scItr != mySCs.end(); ++scItr) {
      SCenergy[nSC] = scItr->energy();
      SCeta[nSC]    = scItr->eta();
      SCphi[nSC]    = scItr->phi();
      SCet[nSC]     = SCenergy[nSC]/cosh(SCeta[nSC]);
      
      nSC++;
   }
   
   theTree->Fill();

   /* how to remove the spikes? `
      const reco::CaloClusterPtr  seed = leadingPho->superCluster()->seed();
      DetId id = lazyTool.getMaximum(*seed).first;
      const EcalRecHitCollection & rechits = ( leadingPho->isEB() ? *EBReducedRecHits : *EEReducedRecHits);
      EcalRecHitCollection::const_iterator it = rechits.find( id );
      
      int severity(-100), recoFlag(-100);
      
      if( it != rechits.end() ) {
      severity = EcalSeverityLevelAlgo::severityLevel( id, rechits, *chStatus );
      recoFlag = it->recoFlag();
      }
      bool finalFlag = true;
      if ( (severity==3) || (severity==4) || (recoFlag ==2) )
      finalFlag = false;
      else
      finalFlag = true;
   */
   
   
   
   
}


// ------------ method called once each job just before starting event loop  ------------
void 
EcalHistProducer::beginJob() 
{
   NoE      = fs->make<TH1D>( "NoE"  , "", 1,  -100., 100. );
   rhEB     = fs->make<TH1D>( "rhEB"  , "", 10100,  -1., 100. );
   rhEE     = fs->make<TH1D>( "rhEE"  , "", 10100,  -1., 100. );
   theTree  = fs->make<TTree>("clusters","Tree of Basic Clusters");
   theTree->Branch("nSC",&nSC,"nSC/I");
   theTree->Branch("nBC",&nBC,"nBC/I");
 
   theTree->Branch("BCe",energy,"BCe[nBC]/F");
   theTree->Branch("BCet",et,"BCet[nBC]/F");
   theTree->Branch("BCeta",eta,"BCeta[nBC]/F");
   theTree->Branch("BCphi",phi,"BCphi[nBC]/F");

   theTree->Branch("SCe",SCenergy,"SCe[nSC]/F");
   theTree->Branch("SCet",SCet,"SCet[nSC]/F");
   theTree->Branch("SCeta",SCeta,"SCeta[nSC]/F");
   theTree->Branch("SCphi",SCphi,"SCphi[nSC]/F");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
EcalHistProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(EcalHistProducer);
