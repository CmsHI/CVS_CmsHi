// -*- C++ -*-
//
// Package:    MCVtxFilter
// Class:      MCVtxFilter
// 
/**\class VtxFilter VtxFilter.cc CmsHi/TrackAnalysis/plugins/MCVtxFilter.cc

 Description: filter based on difference between MC truth vertex position and reconstructed vertex position!

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Andre Sungho Yoon
//         Created:  Wed Aug 26 10:41:44 EDT 2009
// $Id: MCVtxFilter.cc,v 1.2 2010/03/03 11:23:17 edwenger Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "HepMC/HeavyIon.h"
#include "HepMC/GenEvent.h"

#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

//
// class declaration
//

class MCVtxFilter : public edm::EDFilter {
   public:
      explicit MCVtxFilter(const edm::ParameterSet&);
      ~MCVtxFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
   int evtno;
   float b;       // impact parameter                                                   
   float vzr_avf; // reco z-vertex (adaptive vertex finder)                      
   float vzr_med; // reco z-vertex (median vertex finder)                        
   float vz_true; // true simulated z-vertex 
   int vs_avf;    // vertex collection sizes    
   int vs_med;
   float dvz;  // vz_true - vz_med  
   double max_dvz;

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
MCVtxFilter::MCVtxFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   max_dvz = iConfig.getUntrackedParameter<double>("max_dvz",0.2);
}


MCVtxFilter::~MCVtxFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
MCVtxFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace HepMC;
   using namespace reco;

   ///                                                                                                           
   evtno=iEvent.id().event();

   // Get generated info                                                                                          
   edm::Handle<edm::HepMCProduct> hepEv;
   iEvent.getByLabel("generator",hepEv);
   const HepMC::GenEvent * inev = hepEv->GetEvent();
   const HepMC::HeavyIon* hi = inev->heavy_ion();
   b=hi->impact_parameter();

   // Get reconstructed vertices                                                                                  
   edm::Handle<reco::VertexCollection> vertexCollection;
   iEvent.getByLabel("hiPixelMedianVertex",vertexCollection);
   const reco::VertexCollection * vertices = vertexCollection.product();
   vs_med=vertices->size();
   if(vs_med>0) {
      vzr_med=vertices->begin()->z();
   } else
      vzr_med=-999.9;


   // Get signal process vertex                                                                                   
   HepMC::GenVertex* genvtx = inev->signal_process_vertex();

   if(!genvtx){
      HepMC::GenEvent::particle_const_iterator pt=inev->particles_begin();
      HepMC::GenEvent::particle_const_iterator ptend=inev->particles_end();
      while(!genvtx || ( genvtx->particles_in_size() == 1 && pt != ptend ) ){
	 ++pt;
	 genvtx = (*pt)->production_vertex();
      }
   }

   vz_true = 0.1 * genvtx->position().z(); // hepMC gen vtx is in mm.  everything else is cm so we divide by 10 ;)             

   dvz = vz_true - vzr_med;

   std::cout<<"#########################################################################"<<std::endl; 
   if(fabs(dvz) <= (float) max_dvz){
      std::cout<<"[MCVtxFilter] |dvz| = "<<fabs(dvz)<<" less than "<<max_dvz
	       <<" and so will be processed!"<<std::endl;
      std::cout<<"#########################################################################"<<std::endl;
      return true;
   }else{
      std::cout<<"[MCVtxFilter] |dvz| = "<<fabs(dvz)<<" greater than "<<max_dvz
	       <<" and so will NOT be processed!"<<std::endl;
      std::cout<<"#########################################################################"<<std::endl;
      return false;
   }

}

// ------------ method called once each job just before starting event loop  ------------
void 
MCVtxFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MCVtxFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MCVtxFilter);
