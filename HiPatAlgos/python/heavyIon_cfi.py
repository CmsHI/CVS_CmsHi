# To go to PhysicsTools/PatAlgos/python/producersLayer1/

import FWCore.ParameterSet.Config as cms

heavyIon = cms.EDProducer("PATHeavyIonProducer",
                          doMC = cms.bool(True),
                          centrality = cms.InputTag("hiCentrality","recoBased"),
                          evtPlane = cms.InputTag("hiEvtPlane","caloLevel"),
                          generators = cms.vstring("signal","generator")
                          )



