import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Validation_cff import *
from CmsHi.TrackAnalysis.hiBasicGenTest_cfi import *
from CmsHi.TrackAnalysis.globalValidationHeavyIons_cff import *
from CmsHi.TrackAnalysis.HLTValidationHeavyIons_cff import *

validationHeavyIons = cms.Sequence(cms.SequencePlaceholder("mix")
                                   +hiBasicGenTest
                                   *globaldigisanalyze
                                   *globalhitsanalyze
                                   *globalrechitsanalyze
                                   *globalValidationHI
                                   *hltValidationHI
                                   )
