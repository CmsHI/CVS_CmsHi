import FWCore.ParameterSet.Config as cms

hiTrackMCMatch = cms.EDFilter("HiMCTrackMatcher",
    trackingParticles = cms.InputTag("mergedtruth","MergedTrackTruth"),
    tracks = cms.InputTag("hiGlobalPrimTracks"),
    genParticles = cms.InputTag("hiGenParticles"),
    associator = cms.string('TrackAssociatorByHits')
)


