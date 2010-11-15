
import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

## Magnet, geometry, detector condition ( needed for patTuple )
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load("RecoHI.HiEgammaAlgos.HiEgamma_cff")
## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
#process.Tracer = cms.Service("Tracer")

# Centrality
process.load("RecoHI.HiCentralityAlgos.HiCentrality_cfi")
process.HeavyIonGlobalParameters = cms.PSet(
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("")
    )
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('GR10_P_V12::All')  # for data global run.
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    'file:Hydjet_Quenched_MinBias_2760GeV_cfi_py_REHLT_RECO_9_1_lWm.root'
    # lumisToProcess =  cms.untracked.VLuminosityBlockRange(
    # '150431:1-150431:1000'
    )
                            )



## Standard Heavy Ion PAT Configuration File
process.load('PhysicsTools.PatAlgos.patHeavyIonSequences_cff')
from PhysicsTools.PatAlgos.tools.heavyIonTools import *
configureHeavyIons(process)
from PhysicsTools.PatAlgos.tools.coreTools import *
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)

# Modification for HI
process.load("CmsHi.PhotonAnalysis.MultiPhotonAnalyzer_cfi")
process.multiPhotonAnalyzer.GenParticleProducer = cms.InputTag("hiGenParticles")
process.multiPhotonAnalyzer.PhotonProducer = cms.InputTag("selectedPatPhotons")
process.multiPhotonAnalyzer.VertexProducer = cms.InputTag("hiSelectedVertex")
process.multiPhotonAnalyzer.doStoreMET = cms.untracked.bool(False)
process.multiPhotonAnalyzer.doStoreJets = cms.untracked.bool(False)
process.multiPhotonAnalyzer.OutputFile = cms.string('mpa.root')

#  Not embedding sample..
process.multiPhotonAnalyzer.GenEventScale = cms.InputTag("generator")   
process.cleanPhotons.maxHoverEBarrel = cms.double(5)

#
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('ecalRechit_photon15trig.root'),
                                   closeFileFast = cms.untracked.bool(True)
                                   )


# Comp Cone Analysis
process.multiPhotonAnalyzer.doStoreCompCone = cms.untracked.bool(False)
process.photons.isolationSumsCalculatorSet.trackProducer = process.multiPhotonAnalyzer.TrackProducer

# detector responce
process.load("CmsHi.PhotonAnalysis.isoConeInspector_cfi")
process.load("CmsHi.PhotonAnalysis.ecalHistProducer_cfi")
process.load("CmsHi.PhotonAnalysis.SpikeInspector_cfi")

# high purity tracks
process.highPurityTracks = cms.EDFilter("TrackSelector",
                                        src = cms.InputTag("hiSelectedTracks"),
                                        cut = cms.string('quality("highPurity")')
                                        )


# PAT for data
process.patHeavyIonDefaultSequence.remove(process.heavyIon)
process.patHeavyIonDefaultSequence.remove(process.genPartons)
process.patHeavyIonDefaultSequence.remove(process.hiPartons)

# spike cleaner for island superclsters
process.patPhotons.photonSource = cms.InputTag("cleanPhotons")
process.photonMatch.src = cms.InputTag("cleanPhotons")
process.PhotonIDProd.photonProducer  = cms.string('cleanPhotons')
 

process.patHeavyIonDefalutSequencePhoton = cms.Sequence(process.isoCC1+process.isoCC2+process.isoCC3+process.isoCC4+process.isoCC5+process.isoCR1+process.isoCR2+process.isoCR3+process.isoCR4+process.isoCR5+process.isoT11+process.isoT12+process.isoT13+process.isoT14+process.isoT21+process.isoT22+process.isoT23+process.isoT24+process.isoT31+process.isoT32+process.isoT33+process.isoT34+process.isoT41+process.isoT42+process.isoT43+process.isoT44+process.isoDR11+process.isoDR12+process.isoDR13+process.isoDR14+process.isoDR21+process.isoDR22+process.isoDR23+process.isoDR24+process.isoDR31+process.isoDR32+process.isoDR33+process.isoDR34+process.isoDR41+process.isoDR42+process.isoDR43+process.isoDR44+process.PhotonIDProd+process.interestingEcalDetIdEB*process.interestingEcalDetIdEE*process.reducedEcalRecHitsEB*process.reducedEcalRecHitsEE*process.selectDigi*process.gamIsoDepositTk+process.gamIsoDepositEcalFromHits+process.gamIsoDepositHcalFromTowers+process.gamIsoDepositHcalDepth1FromTowers+process.gamIsoDepositHcalDepth2FromTowers*process.gamIsoFromDepsTk*process.gamIsoFromDepsEcalFromHits*process.gamIsoFromDepsHcalFromTowers*process.gamIsoFromDepsHcalDepth1FromTowers*process.gamIsoFromDepsHcalDepth2FromTowers*process.gamIsoDepositTk*process.gamIsoFromDepsTk+process.gamIsoDepositEcalFromHits*process.gamIsoFromDepsEcalFromHits+process.gamIsoDepositHcalFromTowers*process.gamIsoFromDepsHcalFromTowers*process.patPhotons*process.selectedPatPhotons)
process.interestingEcalDetIdEB.basicClustersLabel = cms.InputTag("islandBasicClusters","islandBarrelBasicClusters")
process.interestingEcalDetIdEE.basicClustersLabel = cms.InputTag("islandBasicClusters","islandEndcapBasicClusters")


import HLTrigger.HLTfilters.hltHighLevel_cfi
process.HIMinBiasBSC = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.HIMinBiasBSC.HLTPaths = ["HLT_HIMinBiasBSC"]
process.HIMinBiasBSC.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
#process.HIphotontrig = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
#process.HIphotontrig.HLTPaths = ["HLT_HIPhoton15"]
#process.HIphotontrig.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")

process.p = cms.Path(
    process.HIMinBiasBSC * 
    process.highPurityTracks *
    #      process.siPixelRecHits*process.anaPixelHit*
    # process.patHeavyIonDefaultSequence *
    process.hiPhotonCleaningSequence *
    process.photonIDSequence*
    process.patHeavyIonDefalutSequencePhoton*
    process.multiPhotonAnalyzer 
    # process.isoConeMap  *
    #   process.HIMinBiasBSC *
    #   process.HIphotontrig *
    #    process.ecalHistProducer *
    #process.hiSpikeCleanedSC*
    #process.SClusterComparison *
    #process.spikeInspector
    )

#process.e = cms.EndPath(process.out)    

