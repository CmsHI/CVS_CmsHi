#ifndef HiEventTuner_h
#define HiEventTuner_h

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

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
template<typename Tune>
class HiEventTuner : public edm::EDProducer
{
public:

    //! Contructor
    explicit HiEventTuner(edm::ParameterSet const &);

    //! Destructor
    ~HiEventTuner() {};

private:

    static std::string MessageCategory_;

    virtual void produce(edm::Event&, const edm::EventSetup&);

    Tune tune_;

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

};


template<typename Tune>
std::string HiEventTuner<Tune>::MessageCategory_ = "HiEventTuner";


template<typename Tune>
HiEventTuner<Tune>::HiEventTuner(const edm::ParameterSet& config) : tune_(config)
{
    // Initialize global parameters
    useMultipleHepMCLabels_ = config.getParameter<bool>("useMultipleHepMCLabels");
    hepMCLabels_ = config.getParameter<std::vector<std::string> >("hepMCLabels");
    simHitLabel_ = config.getParameter<std::string>("simHitLabel");

    // Declaration of the products
    produces<edm::SimTrackContainer>();
    produces<edm::SimVertexContainer>();
}


template<typename Tune>
void HiEventTuner<Tune>::produce(edm::Event& event, const edm::EventSetup& setup)
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
    event.getByLabel(simHitLabel_, simTracks_);

    // Collect all the simvertex from the crossing frame
    event.getByLabel(simHitLabel_, simVertexes_);
    std::cout<<"Got products from event."<<std::endl;

    // Create collections of things we will put in event
    tunedSimTracks_ = std::auto_ptr<edm::SimTrackContainer>( new edm::SimTrackContainer );
    tunedSimVertexes_ = std::auto_ptr<edm::SimVertexContainer>( new edm::SimVertexContainer );

    // Create a map between trackId and vertex (decay) index
    mapTrackIdToDecayTrackIndexes();
    std::cout<<"Map of track IDs ready."<<std::endl;

    // Create the actual tuned collection
    createTunedCollections();
    std::cout<<"Tuned collections produced"<<std::endl;

    // Put TrackingParticles and TrackingVertices in event
    event.put(tunedSimTracks_);
    event.put(tunedSimVertexes_);
}


template<typename Tune>
void HiEventTuner<Tune>::mapTrackIdToDecayTrackIndexes()
{
    std::size_t index = 0;

    // Clear the association map
    trackIndexToDecayTrackIndexes_.clear();

    // Loop over the track collection

    std::cout<<"Number of input simtracks : "<<simTracks_->size()<<std::endl;

    for (edm::SimTrackContainer::const_iterator simTrack = simTracks_->begin(); simTrack != simTracks_->end(); ++simTrack, ++index)
    {

      //      std::cout<<"Evaluating track "<<index<<std::endl;
        // Check for a source vertex
        if (simTrack->noVertex()) continue;

        // Get the source vertex
        SimVertex const & sourceVertex = simVertexes_->at( simTrack->vertIndex() );

        // Check if the source vertex has a parent track
        if (sourceVertex.noParent()) continue;

        // Get the source vertex

	if( (int)(sourceVertex.parentIndex())  > (int)(simTracks_->size()) ){
	  std::cout<<"What the hell??"<<std::endl;
	  std::cout<<"Screwed track "<<index<<std::endl;
	  std::cout<<"sourceVertex.parentIndex() "<<sourceVertex.parentIndex()<<std::endl;
	  std::cout<<"simTracks_->size() "<<simTracks_->size()<<std::endl;
   }

        SimTrack const & parentTrack = simTracks_->at( sourceVertex.parentIndex() );

        // Making the association between parentSimTrack and decay index
        trackIndexToDecayTrackIndexes_.insert( std::make_pair(parentTrack.trackId(), index) );
    }
}


template<typename Tune>
void HiEventTuner<Tune>::createTunedCollections()
{
    // Loop over the tracks looking for the seeding tracks
    for (edm::SimTrackContainer::const_iterator simTrack = simTracks_->begin(); simTrack != simTracks_->end(); ++simTrack)
        if ( selectSimulatedTrack(*simTrack) ) addSimulatedHistory(*simTrack);
}


template<typename Tune>
void HiEventTuner<Tune>::addSimulatedHistory(SimTrack const & simTrack, int parentSimTrackIndex)
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


template<typename Tune>
bool HiEventTuner<Tune>::selectSimulatedTrack(SimTrack const & simTrack)
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
        return tune_.select(*(hepmc->GetEvent()->barcode_to_particle(genParticleIndex)));
    }

    return false;
}

#endif
