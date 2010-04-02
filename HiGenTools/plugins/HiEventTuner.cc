
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "DataFormats/Common/interface/Handle.h"

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

//! Producer to reduce the number of charge in simulation
class HiEventTuner : public edm::EDProducer
{
public:
   
    //! Contructor
    explicit HiEventTuner(const edm::ParameterSet&);

    //! Destructor
    ~HiEventTuner(){};

private:
  
    static std::string MessageCategory_;
  
    virtual void produce(edm::Event&, const edm::EventSetup&);

    bool useMultipleHepMCLabels_;
    std::vector<std::string> hepMCLabels_;
    std::vector<edm::Handle<edm::HepMCProduct> > hepMCProducts_;
    
    std::string simHitLabel_;
    
    edm::Handle<edm::SimTrackContainer> simTracks_;
    edm::Handle<edm::SimVertexContainer> simVertexes_;

    std::auto_ptr<edm::SimTrackContainer> tunedSimTracks_;
    std::auto_ptr<edm::SimVertexContainer> tunedSimVertexes_;   

    typedef std::multimap<std::size_t, std::size_t> IndexToIndexes;

    IndexToIndexes trackIndexToDecayTrackIndexes_;

    void mapTrackIdToDecayTrackIndexes();

    void createTunedCollections();
    
    void addSimulatedHistory(SimTrack const &, int parentSimTrackIndex = -1);
    
    bool selectSimulatedTrack(SimTrack const &);
 
    HepMC::GenParticle * getGeneratorParticle(SimTrack const &);
};


std::string HiEventTuner::MessageCategory_ = "HiEventTuner";


HiEventTuner::HiEventTuner(const edm::ParameterSet& config)
{
	// Initialize global parameters
    useMultipleHepMCLabels_ = config.getParameter<bool>("useMultipleHepMCLabels");
    hepMCLabels_ = config.getParameter<std::vector<std::string> >("hepMCLabels");
    simHitLabel_ = config.getParameter<std::string>("simHitLabel");
    
    // Declaration of the products
    produces<edm::SimTrackContainer>();
    produces<edm::SimVertexContainer>();
}


void HiEventTuner::produce(edm::Event& event, const edm::EventSetup& setup)
{
	// Clean the list of hepmc products
    hepMCProducts_.clear();

    // Collect all the HepMCProducts
    edm::Handle<edm::HepMCProduct> hepMCHandle;

    for (std::vector<std::string>::const_iterator source = hepMCLabels_.begin(); source != hepMCLabels_.end(); ++source)
    {
        if ( event.getByLabel(*source, hepMCHandle) )
        {
            hepMCProducts_.push_back(hepMCHandle);
            edm::LogInfo (MessageCategory_) << "Using HepMC source " << *source;
            if (!useMultipleHepMCLabels_) break;
        }
    }

    // Warning and checking preconditions
    if ( hepMCProducts_.empty() )
    {
        edm::LogWarning (MessageCategory_) << "No HepMC source found";
        return;
    }
    else if ( hepMCProducts_.size() > 1 || useMultipleHepMCLabels_ )
    {
        edm::LogInfo (MessageCategory_) << "You are using more than one HepMC source.";
        edm::LogInfo (MessageCategory_) << "If the labels are not in the same order as the events in the crossing frame (i.e. signal, pileup(s) ) ";
        edm::LogInfo (MessageCategory_) << "or there are fewer labels than events in the crossing frame";
        edm::LogInfo (MessageCategory_) << MessageCategory_ << " may try to access data in the wrong HepMCProduct and crash.";
    }
    
    // Collect all the SimTracks
    event.getByLabel("mix", simHitLabel_, simTracks_);

    // Collect all the simvertex from the crossing frame
    event.getByLabel("mix", simHitLabel_, simVertexes_);

    // Create collections of things we will put in event
    tunedSimTracks_ = std::auto_ptr<edm::SimTrackContainer>( new edm::SimTrackContainer );
    tunedSimVertexes_ = std::auto_ptr<edm::SimVertexContainer>( new edm::SimVertexContainer );    
    
    // Create a map between trackId and vertex (decay) index
    mapTrackIdToDecayTrackIndexes();

    // Create the actual tuned collection    
    createTunedCollections();
    
    // Put TrackingParticles and TrackingVertices in event
    event.put(tunedSimTracks_);
    event.put(tunedSimVertexes_);
}


void HiEventTuner::mapTrackIdToDecayTrackIndexes()
{
    std::size_t index = 0;

    // Clear the association map
    trackIndexToDecayTrackIndexes_.clear();

    // Loop over the track collection
    for (edm::SimTrackContainer::const_iterator simTrack = simTracks_->begin(); simTrack != simTracks_->end(); ++simTrack, ++index)
    {
        // Check for a source vertex
    	if (simTrack->noVertex()) continue;
    	
    	// Get the source vertex
    	SimVertex const & sourceVertex = simVertexes_->at( simTrack->vertIndex() );
    	
    	// Check if the source vertex has a parent track
    	if (sourceVertex.noParent()) continue;

    	// Get the source vertex
    	SimTrack const & parentTrack = simTracks_->at( sourceVertex.parentIndex() );
          
        // Making the association between parentSimTrack and decay index
        trackIndexToDecayTrackIndexes_.insert( std::make_pair(parentTrack.trackId(), index) );
    }
}


void HiEventTuner::createTunedCollections()
{
    // Loop over the tracks looking for the seeding tracks
    for (edm::SimTrackContainer::const_iterator simTrack = simTracks_->begin(); simTrack != simTracks_->end(); ++simTrack)
        if ( selectSimulatedTrack(*simTrack) ) addSimulatedHistory(*simTrack);
}


void HiEventTuner::addSimulatedHistory(SimTrack const & simTrack, int parentSimTrackIndex)
{
    // Add the simTrack to the tuned collection
    tunedSimTracks_->push_back(simTrack);

    // Reference to the tunedSimTrack
    SimTrack & tunedSimTrack = tunedSimTracks_->back();

    // Add the origin vertex of a selected track
    if ( !simTrack.noVertex() )
    {        
        // Add the parent simVertex to the tunedSimVertexes collection 
        tunedSimVertexes_->push_back(
            SimVertex(simVertexes_->at(simTrack.vertIndex()), parentSimTrackIndex)
        );
        
        // Update the tunedSimTrack vertex index
        tunedSimTrack.setVertexIndex((int)tunedSimVertexes_->size());       
    }
    
    // Define trackId
    std::size_t simTrackIndex = simTrack.trackId();
    
    // Loop over the decay tracks
    for (
        IndexToIndexes::const_iterator decaySimTrackIndex = trackIndexToDecayTrackIndexes_.lower_bound(simTrackIndex);
        decaySimTrackIndex != trackIndexToDecayTrackIndexes_.upper_bound(simTrackIndex);
        ++decaySimTrackIndex
    )
    	addSimulatedHistory(simTracks_->at(decaySimTrackIndex->second), (int)tunedSimTracks_->size());
}


bool HiEventTuner::selectSimulatedTrack(SimTrack const & simTrack)
{
	// This is the basic rule, select SimTracks associate with a GenParticle
   	if (getGeneratorParticle(simTrack)) return true;
   	return false;
}


HepMC::GenParticle * HiEventTuner::getGeneratorParticle(SimTrack const & simTrack)
{
	// HepMC holder
    edm::Handle<edm::HepMCProduct> hepmc;    

    // Index to the generator particle
    int genParticleIndex = simTrack.genpartIndex();

    // Check in case there is a GenParticle associated to SimTrack
    if (genParticleIndex >= 0)
    {
        // Get the correct HepMC product (for signal and pileup if any)
        hepmc = (useMultipleHepMCLabels_) ? hepMCProducts_.at(simTrack.eventId().rawId()) : hepmc = hepMCProducts_.at(0);

        // Return the pointer to the GenParticle if there is any
        return hepmc->GetEvent()->barcode_to_particle(genParticleIndex);
    }
    
    return 0;
}


//define this as a plug-in
DEFINE_FWK_MODULE(HiEventTuner);
