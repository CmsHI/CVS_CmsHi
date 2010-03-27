// -*- C++ -*-
//
// Package:    HiEventTruncator
// Class:      HiEventTruncator
// 
/**\class HiEventTruncator HiEventTruncator.cc GeneratorInterface/HiEventTruncator/src/HiEventTruncator.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Yetkin Yilmaz,32 4-A08,+41227673039,
//         Created:  Sat Mar 27 18:18:33 CET 2010
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
using namespace edm;

//
// class declaration
//

class HiEventTruncator : public edm::EDProducer {
   public:
      explicit HiEventTruncator(const edm::ParameterSet&);
      ~HiEventTruncator();

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
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
HiEventTruncator::HiEventTruncator(const edm::ParameterSet& iConfig)
{

   produces<SimTrackContainer>();
   produces<SimVertexContainer>();

   produces<PSimHitContainer>("TrackerHitsTOBHighTof");
   //... preferably not hardcoded
   produces<PCaloHitContainer>("EcalHitsES");
   //... preferably not hardcoded


   //now do what ever other initialization is needed
  
}


HiEventTruncator::~HiEventTruncator()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
HiEventTruncator::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   Handle<SimTrackContainer> simtrackHandle;
   iEvent.getByLabel("g4SimHits",simtrackHandle);

   Handle<SimVertexContainer> simvertexHandle;
   iEvent.getByLabel("g4SimHits",simvertexHandle);

   Handle<PSimHitContainer> simhitHandle;
   iEvent.getByLabel(InputTag("g4SimHits","TrackerHitsTOBHighTof"),simhitHandle);
   
   Handle<PCaloHitContainer> calohitHandle;
   iEvent.getByLabel(InputTag("g4SimHits","EcalHitsES"),calohitHandle);

   std::auto_ptr<SimTrackContainer> simtrackOut(new SimTrackContainer);
   std::auto_ptr<SimVertexContainer> simvertexOut(new SimVertexContainer);
   std::auto_ptr<PSimHitContainer> simhitOut(new PSimHitContainer);
   std::auto_ptr<PCaloHitContainer> calohitOut(new PCaloHitContainer);

   // DO THE STUFF!
   // ...
   // ...

   iEvent.put(simtrackOut);
   iEvent.put(simvertexOut);
   iEvent.put(simhitOut);
   iEvent.put(calohitOut);

}

// ------------ method called once each job just before starting event loop  ------------
void 
HiEventTruncator::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HiEventTruncator::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HiEventTruncator);
