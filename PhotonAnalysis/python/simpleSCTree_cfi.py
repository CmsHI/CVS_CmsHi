import FWCore.ParameterSet.Config as cms

simpleSCTree = cms.EDAnalyzer("ClusterTreeMaker",
                              scTagB = cms.untracked.string("correctedIslandBarrelSuperClusters"),
                              scTagE = cms.untracked.string("correctedEndcapSuperClustersWithPreshower"),
                              ebRecHitCollection = cms.untracked.InputTag( 'ecalRecHit','EcalRecHitsEB'),
                              eeRecHitCollection = cms.untracked.InputTag( 'ecalRecHit','EcalRecHitsEE'),
                              etCut              = cms.untracked.double(8),
                              
                              basicClusterBarrel        = cms.InputTag("islandBasicClusters","islandBarrelBasicClusters"),
                              basicClusterEndcap        = cms.InputTag("islandBasicClusters","islandEndcapBasicClusters"),
                              
                              doRecHit          = cms.untracked.bool(True),
                              doBasicCluster    = cms.untracked.bool(False)
                              
                              )
