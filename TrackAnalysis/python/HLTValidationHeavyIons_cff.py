import FWCore.ParameterSet.Config as cms

from CmsHi.TrackAnalysis.SingleJetValidationHI_cfi import *
#from CmsHi.TrackAnalysis.EgammaValidationHI_cff import *

hltValidationHI = cms.Sequence(hiSingleJetValidation
                               #+ hiEgammaValidationSequence
                               )
