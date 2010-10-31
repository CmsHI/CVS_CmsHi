import FWCore.ParameterSet.Config as cms

isoConeMap = cms.EDAnalyzer("IsoConeInspector",
                                  photonProducer = cms.InputTag("photons"),
                                  ebReducedRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
                                  eeReducedRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEE")
                                  )

