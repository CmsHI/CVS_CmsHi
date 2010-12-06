import FWCore.ParameterSet.Config as cms

hiEcalRecHitSpikeFilter = cms.EDFilter("HiEcalRecHitSpikeFilter",
                                 ebReducedRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
                                 minEt = cms.double("20.0"),
                                 swissThreshold = cms.double("0.85"),
                                 timeThreshold = cms.double("4.0"),
                                 avoidIeta85 = cms.bool(False)
                                 #useE2E9 = cms.bool(True),
                                 #e2e9Threshold = cms.double("0.98")
                                 )
