import FWCore.ParameterSet.Config as cms

hiEcalRecHitSpikeFilter = cms.EDFilter("HiEcalRecHitSpikeFilter",
                                 ebReducedRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
                                 minEt = cms.double("50.0"),
                                 swissThreshold = cms.double("0.95")
                                 )
