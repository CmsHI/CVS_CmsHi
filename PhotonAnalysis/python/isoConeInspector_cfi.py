import FWCore.ParameterSet.Config as cms

isoConeInspector = cms.EDAnalyzer("IsoConeInspector",
                                  photonProducer = cms.InputTag("photons"),
                                  ebReducedRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
                                  eeReducedRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
                                  doSpikeClean              = cms.untracked.bool(False),
                                  etCut                     = cms.untracked.double(15),
                                  etaCut                    = cms.untracked.double(1.479)
                                  )

