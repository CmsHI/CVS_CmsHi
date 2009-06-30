// -*- C++ -*-
//
// Package:    VtxAnalyzer
// Class:      VtxAnalyzer
// 
/**\class VtxAnalyzer VtxAnalyzer.cc RecoHI/VtxAnalyzer/src/VtxAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Edward Wenger
//         Created:  Fri May 22 08:11:00 EDT 2009
// $Id: VtxAnalyzer.cc,v 1.1 2009/06/23 13:26:13 edwenger Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "HepMC/HeavyIon.h"
#include "HepMC/GenEvent.h"

#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

// root include file
#include "TFile.h"  
#include "TNtuple.h"
#include "TH1F.h"


//
// class declaration
//

class VtxAnalyzer : public edm::EDAnalyzer {
   public:
      explicit VtxAnalyzer(const edm::ParameterSet&);
      ~VtxAnalyzer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
	

	TNtuple *nt;
	edm::Service<TFileService> f;
	
	int evtno;
	float b;       // impact parameter
	float vzr_avf; // reco z-vertex (adaptive vertex finder)
	float vzr_med; // reco z-vertex (median vertex finder)
	float vz_true; // true simulated z-vertex
	int vs_avf;    // vertex collection sizes
	int vs_med;
	
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
VtxAnalyzer::VtxAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


VtxAnalyzer::~VtxAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
VtxAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	using namespace HepMC;
	using namespace reco;

	evtno=iEvent.id().event();
	
	// Get generated info
	edm::Handle<edm::HepMCProduct> hepEv;
	iEvent.getByLabel("generator",hepEv);
	const HepMC::GenEvent * inev = hepEv->GetEvent();
	HepMC::HeavyIon* hi = inev->heavy_ion();
	b=hi->impact_parameter();
	
	// Get reconstructed vertices
	edm::Handle<reco::VertexCollection> vertexCollection;
	iEvent.getByLabel("pixel3Vertices",vertexCollection);
	const reco::VertexCollection * vertices = vertexCollection.product();
	vs_med=vertices->size();
	if(vs_med>0) vzr_med=vertices->begin()->position().z();
	else vzr_med=-999.9;
	
	edm::Handle<reco::VertexCollection> vertexCollection2;
	iEvent.getByLabel("heavyIonPrimaryVertices",vertexCollection2);
	const reco::VertexCollection * vertices2 = vertexCollection2.product();
	vs_avf=vertices2->size();
	if(vs_avf>0) vzr_avf=vertices2->begin()->position().z();
	else vzr_avf=-999.9;
	
	// Get signal process vertex
	HepMC::GenVertex* genvtx = inev->signal_process_vertex();
	HepMC::FourVector* vtx_;
	
	if(!genvtx){
		HepMC::GenEvent::particle_const_iterator pt=inev->particles_begin();
		HepMC::GenEvent::particle_const_iterator ptend=inev->particles_end();
		while(!genvtx || ( genvtx->particles_in_size() == 1 && pt != ptend ) ){
			++pt;
			genvtx = (*pt)->production_vertex();
		}
	}
	
	vtx_ = &(genvtx->position());
	vz_true = 0.1 * vtx_->z(); // hepMC gen vtx is in mm.  everything else is cm so we divide by 10 ;)
	
	nt->Fill(evtno,b,vzr_avf,vzr_med,vz_true,vs_avf,vs_med);

   
}


// ------------ method called once each job just before starting event loop  ------------
void 
VtxAnalyzer::beginJob(const edm::EventSetup&)
{
	
	nt = f->make<TNtuple>("nt","Vertex Testing","evtno:b:vzr_avf:vzr_med:vz_true:vs_avf:vs_med");
	
}

// ------------ method called once each job just after ending the event loop  ------------
void 
VtxAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(VtxAnalyzer);
