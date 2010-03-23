import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Validation_cff import *
from CmsHi.Validation.hiBasicGenTest_cfi import *
from CmsHi.Validation.globalValidationHeavyIons_cff import *
from CmsHi.Validation.HLTValidationHeavyIons_cff import *

validationHeavyIons = cms.Sequence(cms.SequencePlaceholder("mix")
                                   +hiBasicGenTest
                                   *globaldigisanalyze
                                   *globalhitsanalyze
                                   *globalrechitsanalyze
                                   *globalValidationHI
                                   *hltValidationHI
                                   )
