# subset of Validation.Configuration.globalValidation_cff.py
# that is known to work on HI out of the box
# or with minor changes to configuration parameters

import FWCore.ParameterSet.Config as cms

from Validation.TrackerHits.trackerHitsValidation_cff import *
from Validation.TrackerDigis.trackerDigisValidation_cff import *
from Validation.TrackerRecHits.trackerRecHitsValidation_cff import *
from Validation.TrackingMCTruth.trackingTruthValidation_cfi import *
from Validation.RecoTrack.SiTrackingRecHitsValid_cff import *
from CmsHi.TrackAnalysis.TrackValidationHeavyIons_cff import *

# change track label
hiTracks = 'hiSelectedTracks'
PixelTrackingRecHitsValid.src = hiTracks
StripTrackingRecHitsValid.trajectoryInput = hiTracks


globalValidationHI = cms.Sequence(
    trackerHitsValidation       # tracker g4SimHits
    #+ trackerDigisValidation   # tracker simDigis (not in GEN-SIM-RAW)
    + trackerRecHitsValidation  # tracker recHits
    + trackingTruthValid        # trackingParticles 
    + trackingRecHitsValid      # recHits on tracks   
    + hiTrackValidation         # validation of 'hiSelectedTracks'
    )

