
import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
#process.Timing = cms.Service("Timing")

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

## Source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    'file:skim_RECO_10_1_q4x.root',
    'file:skim_RECO_11_1_YsR.root',
    'file:skim_RECO_12_1_A8J.root',
'file:skim_RECO_13_1_HvH.root',
'file:skim_RECO_14_1_pVp.root',
'file:skim_RECO_15_1_JdA.root',
'file:skim_RECO_16_1_36I.root',
'file:skim_RECO_17_1_G6d.root',
'file:skim_RECO_18_1_95N.root',
'file:skim_RECO_19_1_O2W.root',
'file:skim_RECO_1_1_R7b.root',
'file:skim_RECO_20_1_lP0.root',
'file:skim_RECO_21_1_2kG.root',
'file:skim_RECO_22_1_3pM.root',
'file:skim_RECO_23_1_CjS.root',
'file:skim_RECO_24_1_WNK.root',
'file:skim_RECO_25_1_BaE.root',
'file:skim_RECO_26_1_BSm.root',
'file:skim_RECO_27_1_E9j.root',
'file:skim_RECO_2_1_ReL.root',
'file:skim_RECO_3_1_nrP.root',
'file:skim_RECO_4_1_4zm.root',
'file:skim_RECO_5_1_s5n.root',
'file:skim_RECO_6_1_EY1.root',
'file:skim_RECO_7_1_yn5.root',
'file:skim_RECO_8_1_BdG.root',
'file:skim_RECO_9_1_2w4.root'
    ),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
                            )

## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(125721) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load("RecoHI.HiEgammaAlgos.HiEgamma_cff")

#process.GlobalTag.globaltag = cms.string('MC_38Y_V13::All')
process.GlobalTag.globaltag = cms.string('GR10_P_V12::All')  # for data global run.

# For the global tags without centrality table
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)

process.load("Configuration.StandardSequences.MagneticField_cff")

## Standard PAT Configuration File
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
process.multiPhotonAnalyzer.OutputFile = cms.string('mpa_hfSkim_icludingSpikes.root')
#process.multiPhotonAnalyzer.isMC_      = cms.untracked.bool(False)
#process.singlePhotonAnalyzer.isMC_      = cms.untracked.bool(False)

#  Not embedding sample..
process.multiPhotonAnalyzer.GenEventScale = cms.InputTag("generator")   

#
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('___outf2___.root'),
                                   closeFileFast = cms.untracked.bool(True)
                                   )


# Comp Cone Analysis
process.multiPhotonAnalyzer.doStoreCompCone = cms.untracked.bool(False)
process.photons.isolationSumsCalculatorSet.trackProducer = process.multiPhotonAnalyzer.TrackProducer

# Centrality 
process.load("RecoHI.HiCentralityAlgos.HiCentrality_cfi")
# Heavyion

#process.GlobalTag.toGet = cms.VPSet(
#    cms.PSet(record = cms.string("HeavyIonRcd"),
#             tag = cms.string("CentralityTable_HFhits40_AMPT2760GeV_v3_mc"),
#             connect = cms.untracked.string("frontier://FrontierPrep/CMS_COND_PHYSICSTOOLS")
#             )
#    )  #### old configuartion

 # spike cleaner
process.patPhotons.photonSource = cms.InputTag("cleanPhotons")
process.photonMatch.src = cms.InputTag("cleanPhotons")
process.PhotonIDProd.photonProducer  = cms.string('cleanPhotons')

# detector responce
process.load("CmsHi.PhotonAnalysis.isoConeInspector_cfi")
process.load("CmsHi.PhotonAnalysis.ecalHistProducer_cfi")
process.load("CmsHi.PhotonAnalysis.SpikeInspector_cfi")

# high purity tracks
process.highPurityTracks = cms.EDFilter("TrackSelector",
                                        src = cms.InputTag("hiSelectedTracks"),
                                        cut = cms.string('quality("highPurity")')
                                        )

# get the pixel tree
process.pixelVertexFromClusters = cms.EDProducer('PixelVertexProducerClusters')
process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("AMPT_2760GeV"),
    centralitySrc = cms.InputTag("hiCentrality")
    )


process.anaPixelHit = cms.EDAnalyzer('PixelHitAnalyzer',
                                     vertexSrc = cms.vstring('hiSelectedVertex'),
                                     trackSrc = cms.InputTag('hiSelectedTracks'),
                                     doTracking = cms.untracked.bool(False),
                                     L1gtReadout = cms.InputTag('gtDigis'),
                                     hltTrgResults = cms.untracked.string("TriggerResults::HLT"),
                                     doMC        = cms.untracked.bool(False),
                                     doPixel     = cms.untracked.bool(False)
                                     )



# for data
process.patHeavyIonDefaultSequence.remove(process.heavyIon)
process.patHeavyIonDefaultSequence.remove(process.genPartons)
process.patHeavyIonDefaultSequence.remove(process.hiPartons)

process.patHeavyIonDefalutSequencePhoton = cms.Sequence(process.isoCC1+process.isoCC2+process.isoCC3+process.isoCC4+process.isoCC5+process.isoCR1+process.isoCR2+process.isoCR3+process.isoCR4+process.isoCR5+process.isoT11+process.isoT12+process.isoT13+process.isoT14+process.isoT21+process.isoT22+process.isoT23+process.isoT24+process.isoT31+process.isoT32+process.isoT33+process.isoT34+process.isoT41+process.isoT42+process.isoT43+process.isoT44+process.isoDR11+process.isoDR12+process.isoDR13+process.isoDR14+process.isoDR21+process.isoDR22+process.isoDR23+process.isoDR24+process.isoDR31+process.isoDR32+process.isoDR33+process.isoDR34+process.isoDR41+process.isoDR42+process.isoDR43+process.isoDR44+process.PhotonIDProd+process.interestingEcalDetIdEB*process.interestingEcalDetIdEE*process.reducedEcalRecHitsEB*process.reducedEcalRecHitsEE*process.selectDigi*process.gamIsoDepositTk+process.gamIsoDepositEcalFromHits+process.gamIsoDepositHcalFromTowers+process.gamIsoDepositHcalDepth1FromTowers+process.gamIsoDepositHcalDepth2FromTowers*process.gamIsoFromDepsTk*process.gamIsoFromDepsEcalFromHits*process.gamIsoFromDepsHcalFromTowers*process.gamIsoFromDepsHcalDepth1FromTowers*process.gamIsoFromDepsHcalDepth2FromTowers*process.gamIsoDepositTk*process.gamIsoFromDepsTk+process.gamIsoDepositEcalFromHits*process.gamIsoFromDepsEcalFromHits+process.gamIsoDepositHcalFromTowers*process.gamIsoFromDepsHcalFromTowers*process.patPhotons*process.selectedPatPhotons)


# no cut at this moment
process.hiSpikeCleanedSC.TimingCut = cms.untracked.double(1000.0)
process.hiSpikeCleanedSC.swissCutThr = cms.untracked.double(2)


process.p = cms.Path(
        process.highPurityTracks *
        process.siPixelRecHits*process.anaPixelHit*
        process.hiPhotonCleaningSequence*
        process.photonIDSequence*
        # process.patHeavyIonDefaultSequence *
        process.patHeavyIonDefalutSequencePhoton*
        process.multiPhotonAnalyzer *
        process.isoConeMap  *
        process.ecalHistProducer *
        process.spikeInspector
        )

#process.e = cms.EndPath(process.out)    
    
