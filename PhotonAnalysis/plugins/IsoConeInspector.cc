// -*- C++ -*-
//
// Package:    IsoConeInspector
// Class:      IsoConeInspector
// 
/**\class IsoConeInspector IsoConeInspector.cc CmsHi/IsoConeInspector/src/IsoConeInspector.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Yong Kim,32 4-A08,+41227673039,
//         Created:  Fri Oct 29 12:18:14 CEST 2010
// $Id: IsoConeInspector.cc,v 1.1 2010/10/31 16:17:00 kimy Exp $
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

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "RecoCaloTools/MetaCollections/interface/CaloRecHitMetaCollectionV.h"
#include "RecoCaloTools/MetaCollections/interface/CaloRecHitMetaCollections.h"
#include <Math/VectorUtil.h>
#include "DataFormats/Math/interface/deltaPhi.h"
//
// class declaration
//

class IsoConeInspector : public edm::EDAnalyzer {
   public:
      explicit IsoConeInspector(const edm::ParameterSet&);
      ~IsoConeInspector();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------

   edm::Service<TFileService> fs;

   edm::InputTag photonSrc_;
   edm::InputTag ebReducedRecHitCollection_;
   edm::InputTag eeReducedRecHitCollection_;
   bool doSpikeClean_;
   double etCut_;
   double etaCut_;
   TH1D*  NoE ;
   TTree* theTree;
   int nPho, nBC, nRH; 
   float et;
   float eta;
   float phi;
   float BCet[1000];
   float BCeta[1000];
   float BCphi[1000];
   float RHet[5000];
   float RHdEta[5000];
   float RHdPhi[5000];



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
IsoConeInspector::IsoConeInspector(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   //now do what ever initialization is needed                                                                                                         
   photonSrc_                       = iConfig.getParameter<edm::InputTag>("photonProducer"); // photons                                 
   ebReducedRecHitCollection_       = iConfig.getParameter<edm::InputTag>("ebReducedRecHitCollection"); //,"reducedEcalRecHitsEB");            
   eeReducedRecHitCollection_       = iConfig.getParameter<edm::InputTag>("eeReducedRecHitCollection"); //,"reducedEcalRecHitsEE");        
   doSpikeClean_                    = iConfig.getUntrackedParameter<bool>("doSpikeClean",false);
   etCut_                           = iConfig.getUntrackedParameter<double>("etCut",15);
   etaCut_                           = iConfig.getUntrackedParameter<double>("etaCut",1.479);
   
}


IsoConeInspector::~IsoConeInspector()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
IsoConeInspector::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   //grab the photon collection                                                                                                                        
   Handle<reco::PhotonCollection> photonColl;
   iEvent.getByLabel(photonSrc_, photonColl);
   const reco::PhotonCollection *photons = photonColl.product();
   reco::PhotonCollection::const_iterator pho;
   reco::PhotonCollection::const_iterator leadingPho;

   //grab rechits                                                                                                                                      
   edm::Handle<EcalRecHitCollection> EBReducedRecHits;
   iEvent.getByLabel(ebReducedRecHitCollection_, EBReducedRecHits);
   const EcalRecHitCollection* rechitsCollectionBarrel = EBReducedRecHits.product();
   
   edm::Handle<EcalRecHitCollection> EEReducedRecHits;
   iEvent.getByLabel(eeReducedRecHitCollection_, EEReducedRecHits);
   const EcalRecHitCollection* rechitsCollectionEndcap = EEReducedRecHits.product();
  //lazy tool                                                                                                                                     
   EcalClusterLazyTools lazyTool(iEvent, iSetup, ebReducedRecHitCollection_, eeReducedRecHitCollection_ );
   // get the channel status from the DB                                                                                                     
   edm::ESHandle<EcalChannelStatus> chStatus;
   iSetup.get<EcalChannelStatusRcd>().get(chStatus);

   // get the RecHit geometry
   edm::ESHandle<CaloGeometry> theCaloGeom;
   iSetup.get<CaloGeometryRecord>().get(theCaloGeom);
   const CaloGeometry* caloGeom = theCaloGeom.product();
   const CaloSubdetectorGeometry* subdet_[2];
   subdet_[0] = caloGeom->getSubdetectorGeometry(DetId::Ecal,EcalBarrel);
   subdet_[1] = caloGeom->getSubdetectorGeometry(DetId::Ecal,EcalEndcap);


   
   std::vector< std::pair<DetId, float> >::const_iterator rhIt;

   std::auto_ptr<CaloRecHitMetaCollectionV> RecHitsBarrel(0); 
   RecHitsBarrel = std::auto_ptr<CaloRecHitMetaCollectionV>(new EcalRecHitMetaCollection(*rechitsCollectionBarrel));
   std::auto_ptr<CaloRecHitMetaCollectionV> RecHitsEndcap(0);
   RecHitsEndcap = std::auto_ptr<CaloRecHitMetaCollectionV>(new EcalRecHitMetaCollection(*rechitsCollectionEndcap));

   
   double extRadius_ = 0.4;
   
   nPho = 0;
   nRH  = 0;
   nBC  = 0;
   
   for (pho = (*photons).begin(); pho!= (*photons).end(); pho++){
      et       = (float)pho->et();
      eta      = (float)pho->superCluster()->eta();
      phi      = (float)pho->superCluster()->phi();
      if ( et < etCut_ )  continue;
      if ( fabs(eta) > etaCut_ ) continue;
      
      math::XYZPoint theCaloPosition = pho->superCluster()->position();
      GlobalPoint pclu (theCaloPosition.x () , theCaloPosition.y () , theCaloPosition.z () );
      
      int subdetnr(0);
      subdetnr = 0;  // barrel
      CaloSubdetectorGeometry::DetIdSet chosen = subdet_[subdetnr]->getCells(pclu,extRadius_);// select cells around cluster
      CaloRecHitMetaCollectionV::const_iterator j=RecHitsBarrel->end();
    

      nRH = 0;
      for (CaloSubdetectorGeometry::DetIdSet::const_iterator  i = chosen.begin ();i!= chosen.end ();++i){//loop selected cells
	 j=RecHitsBarrel->find(*i); // find selected cell among rechits
	 if( j!=RecHitsBarrel->end()){ // add rechit only if available 
	    const  GlobalPoint & position = theCaloGeom.product()->getPosition(*i);
	    double etarh = position.eta();
	    double phirh = position.phi();
	    double etaDiff = etarh - eta;
	    double phiDiff= deltaPhi(phirh,phi);
	    double energyrh = j->energy();
	    double etrh    = energyrh/cosh(etarh);
	    
	    RHet[nRH]   = etrh;
	    RHdEta[nRH] = etaDiff;
	    RHdPhi[nRH] = phiDiff;
	    nRH++;
	 }
      }
      theTree->Fill();
      
   }
   
   /* how to remove the spikes? 
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
IsoConeInspector::beginJob() 
{
   NoE      = fs->make<TH1D>( "NoE"  , "", 1,  -1., 1. );
   theTree  = fs->make<TTree>("photon","Tree of Rechits around photon");
   //   theTree->Branch("nPho",&nPho,"nPho/I");
   theTree->Branch("nBC",&nBC,"nBC/I");
   theTree->Branch("nRH",&nRH,"nRH/I");

   theTree->Branch("et",&et,"et/F");
   theTree->Branch("eta",&eta,"eta/F");
   theTree->Branch("phi",&phi,"phi/F");

   //   theTree->Branch("BCet",BCet,"BCet[nBC]/F");
   //  theTree->Branch("BCeta",BCeta,"BCeta[nBC]/F");
   //  theTree->Branch("BCphi",BCphi,"BCphi[nBC]/F");

   theTree->Branch("RHet",RHet,"RHet[nRH]/F");
   theTree->Branch("RHdEta",RHdEta,"RHdEta[nRH]/F");
   theTree->Branch("RHdPhi",RHdPhi,"RHdPhi[nRH]/F");

    
}

// ------------ method called once each job just after ending the event loop  ------------
void 
IsoConeInspector::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(IsoConeInspector);
