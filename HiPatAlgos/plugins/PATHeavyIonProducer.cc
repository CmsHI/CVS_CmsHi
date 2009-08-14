// -*- C++ -*-
//
// Package:    PATHeavyIonProducer
// Class:      PATHeavyIonProducer
// 
/**\class PATHeavyIonProducer PATHeavyIonProducer.cc yetkin/PATHeavyIonProducer/src/PATHeavyIonProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yetkin Yilmaz
//         Created:  Thu Aug 13 08:39:51 EDT 2009
// $Id$
//
//


// system include files
#include <memory>
#include <string>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"

#include "DataFormats/PatCandidates/interface/HeavyIon.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "HepMC/HeavyIon.h"

//
// class decleration
//

class PATHeavyIonProducer : public edm::EDProducer {
   public:
      explicit PATHeavyIonProducer(const edm::ParameterSet&);
      ~PATHeavyIonProducer();

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------

   bool doMC_;
   std::vector<std::string> hepmcSrc_;
   edm::InputTag centSrc_;
   edm::InputTag evtPlaneSrc_;

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
PATHeavyIonProducer::PATHeavyIonProducer(const edm::ParameterSet& iConfig)
{
   //register your products
   produces<pat::HeavyIon>();

   //now do what ever other initialization is needed
   centSrc_ = iConfig.getParameter<edm::InputTag>("centrality");
   evtPlaneSrc_ = iConfig.getParameter<edm::InputTag>("evtPlane");
   doMC_ = iConfig.getParameter<bool>("doMC");
   if(doMC_) iConfig.getParameter<std::vector<std::string> >("generators");

  
}


PATHeavyIonProducer::~PATHeavyIonProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
PATHeavyIonProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   Handle<reco::Centrality> cent;
   iEvent.getByLabel(centSrc_,cent);   

   Handle<reco::EvtPlane> evtplane;
   iEvent.getByLabel(evtPlaneSrc_,evtplane);
   
   double b = 0;
   int npart = 0;
   int ncoll = 0;
   int nhard = 0;
   double phi = 0;

   std::vector<Handle<edm::HepMCProduct> > hepmc;
   if(doMC_){
      for(size_t ihep; ihep < hepmcSrc_.size(); ++ihep){
	 iEvent.getByLabel(hepmcSrc_[ihep],hepmc[ihep]);
	 const HepMC::HeavyIon* hi = hepmc[ihep]->GetEvent()->heavy_ion();
	 if(hi){
	    ncoll = ncoll + hi->Ncoll();
	    nhard = nhard + hi->Ncoll_hard();
	    int np = hi->Npart_proj() + hi->Npart_targ();
	    if(np > 0){
	       npart = hi->Npart_proj();
	       b = hi->impact_parameter();
	       phi = hi->event_plane_angle();
	    }
	 }
      }
   }
   
   if(doMC_){
      std::auto_ptr<pat::HeavyIon> pOut(new pat::HeavyIon(
							  *(cent.product()),
							  *(evtplane.product()),
							  b,
							  npart,
							  ncoll,
							  nhard,
							  phi
							  ));

      iEvent.put(pOut);
   }else{
      std::auto_ptr<pat::HeavyIon> pOut(new pat::HeavyIon(
							  *(cent.product()),
							  *(evtplane.product())
							  ));
      iEvent.put(pOut);
   }
}

// ------------ method called once each job just before starting event loop  ------------
void 
PATHeavyIonProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PATHeavyIonProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(PATHeavyIonProducer);
