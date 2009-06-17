
//
// Package:    CentFilter
// Class:      CentFilter
// 
/**\class CentFilter CentFilter.cc simplaAnlzer/CentFilter/src/CentFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yongsun Kim
//         Created:  Fri May 22 12:57:09 EDT 2009
// $Id: CentFilter.cc,v 1.1 2009/05/29 13:46:17 edwenger Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"


//
// class declaration
//

class CentFilter : public edm::EDFilter {
   public:
      explicit CentFilter(const edm::ParameterSet&);
      ~CentFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
  double bmin;
  double bmax;

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
CentFilter::CentFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  bmin  = iConfig.getUntrackedParameter<double>("bmin",0);
  bmax  = iConfig.getUntrackedParameter<double>("bmax",30);
  
} 


CentFilter::~CentFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
CentFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace HepMC;
   
   const GenEvent *evt;

   Handle<HepMCProduct> mc;
   iEvent.getByLabel("generator",mc);
   evt = mc->GetEvent();

   const HeavyIon* hi = evt->heavy_ion();
   //int nPart = hi->Npart_proj()+hi->Npart_targ();
   double impactP = hi->impact_parameter();

   if ( impactP > bmin && impactP < bmax)
     { return true;}
   
   else
     return false;

}

// ------------ method called once each job just before starting event loop  ------------
void 
CentFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CentFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentFilter);
