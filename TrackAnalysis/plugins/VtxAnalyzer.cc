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
// $Id: VtxAnalyzer.cc,v 1.8 2009/10/20 12:06:35 edwenger Exp $
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
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "HepMC/HeavyIon.h"
#include "HepMC/GenEvent.h"

#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"

#include "Geometry/TrackerGeometryBuilder/interface/TrackerLayerIdAccessor.h" 	 
#include "DataFormats/Common/interface/DetSetAlgorithm.h"

#include "DataFormats/Common/interface/DetSetVector.h"    
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHitCollection.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"

// root include file
#include "TFile.h"  
#include "TNtuple.h"
#include "TH1F.h"

using namespace std;

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
	float vzr_sel;
	float vzErr_sel;
	float vzr_avf;     // reco z-vertex (adaptive vertex finder)
	float vzErr_avf;   // reco z-vertex error (adaptive vertex finder)
	float vzr_med;     // reco z-vertex (median vertex finder)
	float vzErr_med;   // reco z-vertex error (med vertex finder)
	float vz_true;     // true simulated z-vertex
	int vs_sel;
	int vs_avf;        // vertex collection sizes
	int vs_med;
        float nEstTracks; // estimated tracks from polynomial function
        int nSelectSimTracks; // sim tracks that pass selection (pt>1, primary)
	int nProtoTracks;  // number of proto-tracks
	int nProtoTracks1000; // above 1 GeV
	int nProtoTracks700; // above 700 MeV
	int nProtoTracks500; // above 500 MeV
	int nProtoTracksSelect; // selected prototracks
        int nPixelHits; // first layer pixel hits
	
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
	const HepMC::HeavyIon* hi = inev->heavy_ion();
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
	
	// Get selected prototracks
	nProtoTracksSelect=0;
	edm::Handle<reco::TrackCollection> selectedProtoTracks;
	iEvent.getByLabel("hiSelectedProtoTracks",selectedProtoTracks);
	nProtoTracksSelect=selectedProtoTracks.product()->size();
	cout << nProtoTracksSelect << " selected prototracks out of " << nProtoTracks << endl;
	
	// Get reconstructed vertices
	
	edm::Handle<reco::VertexCollection> vertexCollection3;
	iEvent.getByLabel("hiSelectedVertex",vertexCollection3);
	const reco::VertexCollection * vertices3 = vertexCollection3.product();
	vs_sel=vertices3->size();
	if(vs_sel>0) {
		vzr_sel=vertices3->begin()->z();
		vzErr_sel=vertices3->begin()->zError();
	} else 
		vzr_sel=-999.9;
	
	edm::Handle<reco::VertexCollection> vertexCollection2;
	iEvent.getByLabel("hiPixelAdaptiveVertex",vertexCollection2);
	const reco::VertexCollection * vertices2 = vertexCollection2.product();
	vs_avf=vertices2->size();
	if(vs_avf>0) {
		vzr_avf=vertices2->begin()->z();
		vzErr_avf=vertices2->begin()->zError();
	} else 
		vzr_avf=-999.9;
	
	edm::Handle<reco::VertexCollection> vertexCollection;
	iEvent.getByLabel("hiPixelMedianVertex",vertexCollection);
	const reco::VertexCollection * vertices = vertexCollection.product();
	vs_med=vertices->size();
	if(vs_med>0) {
		vzr_med=vertices->begin()->z();
		vzErr_med=vertices->begin()->zError();
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


	// number of first layer pixel hits
	edm::Handle<SiPixelRecHitCollection> recHitColl;
	iEvent.getByLabel("siPixelRecHits", recHitColl);
	
	std::vector<const TrackingRecHit*> theChosenHits; 	 
	TrackerLayerIdAccessor acc; 	 
	edmNew::copyDetSetRange(*recHitColl,theChosenHits,acc.pixelBarrelLayer(1)); 	 
	nPixelHits = theChosenHits.size(); 

	// fit from MC information
	float aa = 1.90935e-04;
	float bb = -2.90167e-01;
	float cc = 3.86125e+02;
	nEstTracks = aa*nPixelHits*nPixelHits+bb*nPixelHits+cc;

	// get the number of primary tracking particles with pt > 1 GeV
	edm::Handle<TrackingParticleCollection> simCollection;
	iEvent.getByLabel("findableSimTracks",simCollection);
	nSelectSimTracks = simCollection.product()->size();


	
	nt->Fill(evtno,b,vzr_sel,vzErr_sel,vzr_med,vzErr_med,vz_true,vs_avf,vs_med,nEstTracks,nSelectSimTracks,nProtoTracks,nProtoTracksSelect,nPixelHits);
	
	
}


// ------------ method called once each job just before starting event loop  ------------
void 
VtxAnalyzer::beginJob(const edm::EventSetup&)
{
	
	nt = f->make<TNtuple>("nt","Vertex Testing","evtno:b:vzr_sel:vzErr_sel:vzr_med:vzErr_med:vz_true:vs_avf:vs_med:nEstTracks:nSelectSimTracks:nProtoTracks:nProtoTracksSelect:nPixelHits");
	
}

// ------------ method called once each job just after ending the event loop  ------------
void 
VtxAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(VtxAnalyzer);
