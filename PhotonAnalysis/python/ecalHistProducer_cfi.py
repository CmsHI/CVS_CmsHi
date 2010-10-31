import FWCore.ParameterSet.Config as cms

ecalHistProducer = cms.EDAnalyzer("EcalHistProducer",
                                  photonProducer = cms.InputTag("photons"),
                                  ebReducedRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
                                  eeReducedRecHitCollection = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
                                  basicClusterBarrel        = cms.InputTag("islandBasicClusters","islandBarrelBasicClusters"),
                                  basicClusterEndcap        = cms.InputTag("islandBasicClusters","islandEndcapBasicClusters")
                                  )

