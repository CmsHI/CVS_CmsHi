import FWCore.ParameterSet.Config as cms

from Validation.Configuration.globalValidation_cff import *
from CmsHi.TrackAnalysis.TrackValidationHeavyIons_cff import *

# change track label
hiTracks = 'hiSelectedTracks'
PixelTrackingRecHitsValid.src = hiTracks
StripTrackingRecHitsValid.trajectoryInput = hiTracks


globalValidationHI = cms.Sequence(
    trackerHitsValidation      
    #+ trackerDigisValidation   # tracker simDigis (not in RAWDEBUG)
    + trackerRecHitsValidation 
    + trackingTruthValid        
    + trackingRecHitsValid        
    + hiTrackValidation         # validation of 'hiSelectedTracks'

    + ecalSimHitsValidationSequence 
    + ecalDigisValidationSequence 
    + ecalRecHitsValidationSequence 
    + ecalClustersValidationSequence

    #+ hcalSimHitStudy
    #+ hcalDigisValidationSequence
    + hcalRecHitsValidationSequence
    + calotowersValidationSequence

    # add jet validation with HiGenJetCleaning?
   
    )

