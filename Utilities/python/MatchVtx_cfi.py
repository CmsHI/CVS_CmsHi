import FWCore.ParameterSet.Config as cms
 
from IOMC.EventVertexGenerators.VtxSmearedParameters_cfi import *
matchVtx = cms.EDFilter("MixEvtVtxGenerator",
signalLabel = cms.InputTag("signal"), 
heavyIonLabel = cms.InputTag("source")
#heavyIonLabel = cms.InputTag("generator") # for 3_1_X
)
