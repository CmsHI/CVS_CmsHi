// -*- C++ -*-
//
// Package:    RecHitComparison
// Class:      RecHitComparison
// 
/**\class RecHitComparison RecHitComparison.cc CmsHi/RecHitComparison/src/RecHitComparison.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Yetkin Yilmaz
//         Created:  Tue Sep  7 11:38:19 EDT 2010
// $Id$
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

#include "TNtuple.h"

using namespace std;

//
// class declaration
//

class RecHitComparison : public edm::EDAnalyzer {
   public:
      explicit RecHitComparison(const edm::ParameterSet&);
      ~RecHitComparison();


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

   TNtuple* nthit;
   TNtuple* ntjet;

   double cone;

   edm::Service<TFileService> fs;
   const CentralityBins * cbins_;
   const CaloGeometry *geo;
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
RecHitComparison::RecHitComparison(const edm::ParameterSet& iConfig) :
   cbins_(0),
   geo(0),
   cone(0.5)
{
   //now do what ever initialization is needed

}


RecHitComparison::~RecHitComparison()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
RecHitComparison::analyze(const edm::Event& ev, const edm::EventSetup& iSetup)
{

   if(!cbins_) cbins_ = getCentralityBinsFromDB(iSetup);
   if(!geo){
      edm::ESHandle<CaloGeometry> pGeo;
      iSetup.get<CaloGeometryRecord>().get(pGeo);
      geo = pGeo.product();
   }

   edm::InputTag jetTag1("ecalRecHit","EcalRecHitsEB","SIGNALONLY");
   edm::InputTag jetTag2("ecalRecHit","EcalRecHitsEB","RECO");

   edm::InputTag signalTag("iterativeConePu5CaloJets","","SIGNALONLY");
   edm::InputTag centTag("hiCentrality","","RECO");

   using namespace edm;

   ev.getByLabel(centTag,cent);
   ev.getByLabel(jetTag1,jets1);
   ev.getByLabel(jetTag2,jets2);
   ev.getByLabel(signalTag,signalJets);

   double hf = cent->EtHFhitSum();
   double sumet = cent->EtMidRapiditySum();
   int run = ev.id().run();
   run = 1;
   int bin = cbins_->getBin(hf);
   int margin = 0;

   vector<double> fFull;
   vector<double> f05;
   vector<double> f1;
   vector<double> f15;
   vector<double> f2;
   vector<double> f25;
   vector<double> f3;

   int njets = signalJets->size();
   fFull.reserve(njets);
   f05.reserve(njets);
   f1.reserve(njets);
   f15.reserve(njets);
   f2.reserve(njets);
   f25.reserve(njets);
   f3.reserve(njets);

   for(unsigned int j1 = 0 ; j1 < signalJets->size(); ++j1){
      fFull.push_back(0);
      f05.push_back(0);
      f1.push_back(0);
      f15.push_back(0);
      f2.push_back(0);
      f25.push_back(0);
      f3.push_back(0);
   }

   for(unsigned int j1 = 0 ; j1 < jets1->size(); ++j1){

      const EcalRecHit& jet1 = (*jets1)[j1];
      double e1 = jet1.energy();

      const GlobalPoint& pos1=geo->getPosition(jet1.id());
      double eta1 = pos1.eta();
      double phi1 = pos1.phi();
      double et1 = e1*sin(pos1.theta());

      double drjet = -1;
      double jetpt = -1;
      bool isjet = false;
      int matchedJet = -1;

      for(unsigned int j = 0 ; j < signalJets->size(); ++j){
	 const reco::CaloJet & jet = (*signalJets)[j];
	 double dr = reco::deltaR(eta1,phi1,jet.eta(),jet.phi());
	 if(dr < cone){
	    jetpt = jet.pt();
	    drjet = dr;
	    isjet = true;
	    matchedJet = j;
	    fFull[j] += et1;

	    if(et1 > 0.5){
	       f05[j] += et1;
	    }
	    if(et1 > 1.){
               f1[j] += et1;
            }
	    if(et1 > 1.5){
               f15[j] += et1;
            }
	    if(et1 > 2){
               f2[j] += et1;
            }
	    if(et1 > 2.5){
               f25[j] += et1;
            }
	    if(et1 > 3.){
               f3[j] += et1;
            }
	 }
      }
      
      GlobalPoint pos2;
      double e2 = -1;
      int siz = jets2->size();

      EcalIterator hitit = jets2->find(jet1.id());
      if(hitit != jets2->end()){
	 e2 = hitit->energy();
	 pos2=geo->getPosition(hitit->id());
      }else{
	 e2 = 0;
	 pos2 = pos1; 
      }

      double eta2 = pos2.eta();
      double phi2 = pos2.eta();
      double et2 = e2*sin(pos2.theta());
      
      if(isjet) nthit->Fill(e1,et1,e2,et2,eta2,phi2,sumet,hf,bin,jetpt,drjet);
      
   }

   for(unsigned int j1 = 0 ; j1 < signalJets->size(); ++j1){
      const reco::CaloJet & jet = (*signalJets)[j1];
      double em = (jet.emEnergyInEB() + jet.emEnergyInEE()) * sin(jet.theta());
      double emf = jet.emEnergyFraction(); 
      double pt = jet.pt();
      double eta = jet.eta();
      ntjet->Fill(bin,pt,eta,fFull[j1],f05[j1],f1[j1],f15[j1],f2[j1],f25[j1],f3[j1],em,emf);
   }

}


// ------------ method called once each job just before starting event loop  ------------
void 
RecHitComparison::beginJob()
{
   nthit = fs->make<TNtuple>("nthit","","e1:et1:e2:et2:eta:phi:sumet:hf:bin:ptjet:drjet");
   ntjet = fs->make<TNtuple>("ntjet","","bin:pt:eta:ethit:f05:f1:f15:f2:f25:f3:em:emf");
   
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RecHitComparison::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(RecHitComparison);
