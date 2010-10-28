import FWCore.ParameterSet.Config as cms

hiEcalSpikeFilter = cms.EDFilter("HiEcalSpikeFilter",
                                 photonProducer = cms.InputTag("photons"),
                                 ebReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
                                 eeReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsEE")
                                 )




