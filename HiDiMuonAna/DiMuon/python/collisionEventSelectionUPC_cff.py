import FWCore.ParameterSet.Config as cms
# Coincidence of HF towers above threshold
#from HeavyIonsAnalysis.Configuration.hfCoincFilterUPC_cff import *
from HiDiMuonAna.DiMuon.hfCoincFilterUPC_cff import *

# Reject BSC beam halo L1 technical bits
from L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff import *
from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import hltLevel1GTSeed
noBSChalo = hltLevel1GTSeed.clone(
    L1TechTriggerSeeding = cms.bool(True),
    L1SeedsLogicalExpression = cms.string('NOT (36 OR 37 OR 38 OR 39)')
)

collisionEventSelection = cms.Sequence(noBSChalo*hfCoincFilter3)
                                       
