import FWCore.ParameterSet.Config as cms

hiGenParticles = cms.EDProducer('GenParticleProducer',
                                srcVector = cms.vstring("hiSignal","generator"),
                                doSubEvent = cms.untracked.bool(True),
                                useCrossingFrame = cms.untracked.bool(False),
                                saveBarCodes = cms.untracked.bool(True)
                                )

