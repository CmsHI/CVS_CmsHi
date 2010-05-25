
import FWCore.ParameterSet.Config as cms

hiTunedG4SimHits = cms.EDProducer("HiTrivialTuner",
                                useMultipleHepMCLabels = cms.bool(False),
                                hepMCLabels = cms.vstring("generator"),
                                simHitLabel = cms.string("g4SimHits")
                                )


                



