import FWCore.ParameterSet.Config as cms

hiGenParticles = cms.EDProducer('HiGenParticleProducer',
src = cms.vstring("signal","generator"),
saveBarCodes = cms.untracked.bool(True),
useCrossingFrame = cms.untracked.bool(False)
)
