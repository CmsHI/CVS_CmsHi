import FWCore.ParameterSet.Config as cms

from Validation.Configuration.globalValidation_cff import *
from CmsHi.TrackAnalysis.TrackValidationHeavyIons_cff import *
from CmsHi.TrackAnalysis.JetValidationHeavyIons_cff import *
from CmsHi.TrackAnalysis.muonValidationHeavyIons_cff import *

# change track label for rechits
hiTracks = 'hiSelectedTracks'
PixelTrackingRecHitsValid.src = hiTracks
StripTrackingRecHitsValid.trajectoryInput = hiTracks


globalValidationHI = cms.Sequence(
    trackerHitsValidation      
    #+ trackerDigisValidation   # simSiDigis not in RAWDEBUG
    + trackerRecHitsValidation 
    + trackingTruthValid        
    + trackingRecHitsValid        

    + ecalSimHitsValidationSequence 
    #+ ecalDigisValidationSequence  # simEcalDigis not in RAWDEBUG
    + ecalRecHitsValidationSequence 
    + ecalClustersValidationSequence

    + hcalSimHitStudy
    #+ hcalDigisValidationSequence  # simHcalDigis not in RAWDEBUG
    + hcalRecHitsValidationSequence
    + calotowersValidationSequence
    
    + hiTrackValidation         # validation of 'hiSelectedTracks'
    + hiJetValidation           # validation of pileup jet finders
    + hiRecoMuonValidation      # validation of offline muon reco
   
    )

