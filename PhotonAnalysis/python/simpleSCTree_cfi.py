import FWCore.ParameterSet.Config as cms

scAnaUC = cms.EDAnalyzer("ClusterTreeMaker",
                         scTagB = cms.untracked.string("correctedIslandBarrelSuperClusters"), #cleanedBarrelSC"),
                         scTagE = cms.untracked.string("correctedIslandEndcapSuperClusters"),
                         ebRecHitCollection = cms.untracked.InputTag( 'hltEcalRecHitAll','EcalRecHitsEB' ),
                         eeRecHitCollection = cms.untracked.InputTag( 'hltEcalRecHitAll','EcalRecHitsEE' ),
                         etCut              = cms.untracked.double(8)
                         )
