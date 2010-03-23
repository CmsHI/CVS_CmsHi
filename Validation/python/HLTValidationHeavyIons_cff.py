import FWCore.ParameterSet.Config as cms

from CmsHi.Validation.SingleJetValidationHI_cfi import *
from CmsHi.Validation.EgammaValidationHI_cff import *

hltValidationHI = cms.Sequence(hiSingleJetValidation
                               + hiEgammaValidationSequence
                               )
