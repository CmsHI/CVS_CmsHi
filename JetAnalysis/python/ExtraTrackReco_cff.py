import FWCore.ParameterSet.Config as cms

# pixel triplet tracking (HI Tracking)
from RecoLocalTracker.Configuration.RecoLocalTracker_cff import *
from RecoHI.Configuration.Reconstruction_HI_cff import *

#Track Reco
rechits = cms.Sequence(siPixelRecHits * siStripMatchedRecHits)
hiTrackReReco = cms.Sequence(rechits * heavyIonTracking)

# good track selection
from edwenger.HiTrkEffAnalyzer.TrackSelections_cff import *

hiextraTrackReco = cms.Sequence(
		hiPostGlobalPrimTracks *
    hiGoodTightTracksSelection
    )



from Appeltel.PixelTracksRun2010.HiLowPtPixelTracksFromReco_cff import *
from Appeltel.PixelTracksRun2010.HiMultipleMergedTracks_cff import *

hiMergedTracks = hiGoodMergedTracks.clone(
    TrackProducer1  = "hiTracks",
    TrackProducer2  = "hiConformalPixelTracks")


hiTracks = cms.EDFilter("TrackSelector",
                                src = cms.InputTag("hiGeneralCaloMatchedTracks"),
                                cut = cms.string(
    'quality("highPurity")')
                                )

rechits = cms.Sequence(siPixelRecHits * siStripMatchedRecHits)
hiTrackReco = cms.Sequence(hiTracks * hiMergedTracks)
