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
// $Id: VtxAnalyzer.cc,v 1.3 2009/08/26 09:57:45 edwenger Exp $
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

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

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
	float b;           // impact parameter
	float vzr_avf;     // reco z-vertex (adaptive vertex finder)
	float vzErr_avf;   // reco z-vertex error (adaptive vertex finder)
	float vzr_med;     // reco z-vertex (median vertex finder)
	float vzErr_med;   // reco z-vertex error (med vertex finder)
	float vz_true;     // true simulated z-vertex
	int vs_avf;        // vertex collection sizes
	int vs_med;
	int nProtoTracks;  // number of proto-tracks
	int nProtoTracks1000; // above 1 GeV
	int nProtoTracks700; // above 700 MeV
	int nProtoTracks500; // above 500 MeV
	
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
	//evtno=inev->event_number();
	HepMC::HeavyIon* hi = inev->heavy_ion();
	b=hi->impact_parameter();
	
	// Get pixel prototracks
	edm::Handle<reco::TrackCollection> protoTracks;
	iEvent.getByLabel("hiPixel3ProtoTracks",protoTracks);
	nProtoTracks=protoTracks.product()->size();
	nProtoTracks1000=0;
	nProtoTracks700=0;
	nProtoTracks500=0;
	float trackpt = -999.9;

	for( TrackCollection::const_iterator track = protoTracks->begin(); 
		track != protoTracks->end(); ++ track ) {
		trackpt=track->pt();
		if(trackpt>1.0) nProtoTracks1000++;
		if(trackpt>0.7) nProtoTracks700++;
		if(trackpt>0.5) nProtoTracks500++;
	}
	
	// Get reconstructed vertices
	edm::Handle<reco::VertexCollection> vertexCollection;
	iEvent.getByLabel("hiPixelMedianVertex",vertexCollection);
	const reco::VertexCollection * vertices = vertexCollection.product();
	vs_med=vertices->size();
	if(vs_med>0) {
		vzr_med=vertices->begin()->z();
		vzErr_med=vertices->begin()->zError();
	} else 
		vzr_med=-999.9;
	
	edm::Handle<reco::VertexCollection> vertexCollection2;
	iEvent.getByLabel("hiPixelAdaptiveVertex",vertexCollection2);
	const reco::VertexCollection * vertices2 = vertexCollection2.product();
	vs_avf=vertices2->size();
	if(vs_avf>0) {
		vzr_avf=vertices2->begin()->z();
		vzErr_avf=vertices2->begin()->zError();
	} else 
		vzr_avf=-999.9;
	
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
	
	nt->Fill(evtno,b,vzr_avf,vzErr_avf,vzr_med,vzErr_med,vz_true,vs_avf,vs_med,nProtoTracks,nProtoTracks1000,nProtoTracks700,nProtoTracks500);

   
}


// ------------ method called once each job just before starting event loop  ------------
void 
VtxAnalyzer::beginJob(const edm::EventSetup&)
{
	
	nt = f->make<TNtuple>("nt","Vertex Testing","evtno:b:vzr_avf:vzErr_avf:vzr_med:vzErr_med:vz_true:vs_avf:vs_med:nProtoTracks:nProtoTracks1000:nProtoTracks700:nProtoTracks500");
	
}

// ------------ method called once each job just after ending the event loop  ------------
void 
VtxAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(VtxAnalyzer);
