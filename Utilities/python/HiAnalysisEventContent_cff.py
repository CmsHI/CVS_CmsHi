import FWCore.ParameterSet.Config as cms

HIAnalysisObjects = cms.PSet(
        outputCommands = cms.untracked.vstring('keep *',
                                               'keep *_source_*_*',
                                               'keep *_signal_*_*',
                                               'drop *CrossingFrame*_*_*_*',
                                               'keep *HepMCProduct*_*_*_*',
                                               'drop *_si*RecHits_*_*',
                                               'drop *_*Digis_*_*',
                                               'drop *_g4SimHits_*_*',
                                               'drop *_signalSIM_*_*',
                                               'drop *_si*Clusters_*_*',
                                               'drop *_pixelTracks_*_*',
                                               'drop *_*TrackCandidates_*_*',
                                               'drop *_*TrackSeeds_*_*',
                                               'drop *_hybridSuperClusters_*_*',
                                               'drop *_islandSuperClusters_*_*',
                                               'drop *_pixelTracksWithVertices_*_*',
                                               'keep *Jets*_*_*_*')
        )

HITrackerSimDigiObjects = cms.PSet(
    outputCommands = cms.untracked.vstring('keep *_mergedtruth_*_*',
                                           'keep PSimHitCrossingFrame_*_g4SimHitsTracker*_*',
                                           'keep *_*PixelDigis_*_*',
                                           'keep *_*StripDigis_*_*')
    )

HIEcalHcalSimDigiObjects = cms.PSet(
    outputCommands = cms.untracked.vstring('keep *_ecalDigis_*_*',
                                           'keep *_hcalDigis_*_*')
    )

HITrackAnalysisObjects = HIAnalysisObjects.clone()
HITrackAnalysisObjects.outputCommands.extend(HITrackerSimDigiObjects.outputCommands)
HITrackAnalysisObjects.outputCommands.extend(HIEcalHcalSimDigiObjects.outputCommands)


HIRecoObjects = cms.PSet(
    outputCommands = cms.untracked.vstring('keep *', 
        'keep *_source_*_*', 
        'keep *_signal_*_*',                                           
        'drop *CrossingFrame*_*_*_*', 
        'keep *HepMCProduct*_*_*_*',                                           
        'drop *_si*RecHits_*_*', 
        'drop *_*Digis_*_*', 
        'drop *_g4SimHits_*_*', 
        'drop *_signalSIM_*_*',                                          
        'drop *_si*Clusters_*_*', 
        'drop *_pixelTracks_*_*', 
        'drop *_*TrackCandidates_*_*', 
        'drop *_*TrackSeeds_*_*', 
        'drop *_hybridSuperClusters_*_*', 
        'drop *_islandSuperClusters_*_*', 
        'drop *_pixelTracksWithVertices_*_*',
        'keep *Jets*_*_*_*')
)

