import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)
## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
## magnet
process.load("Configuration.StandardSequences.MagneticField_cff")
## Timing service
process.Timing = cms.Service("Timing")

## Global Tag
process.GlobalTag.globaltag = 'START39_V2::All'
################# ESSource for the centrality #####
process.GlobalTag.toGet = cms.VPSet(
    cms.PSet(record = cms.string("HeavyIonRcd"),
             tag = cms.string("CentralityTable_HFhits40_Hydjet2760GeV_v0_mc"),
             connect = cms.untracked.string("frontier://FrontierPrep/CMS_COND_PHYSICSTOOLS")
             ))
            
## Source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    'rfio:/castor/cern.ch/cms/store/relval/CMSSW_3_9_0/RelValPyquen_GammaJet_pt20_2760GeV/GEN-SIM-RECO/MC_39Y_V2-v1/0052/0A790EE2-26D9-DF11-9EE2-001A928116CE.root'
                                                                
                                                                )
                            )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
                                                   randomSuperCluster = cms.PSet(
    engineName = cms.untracked.string("TRandom3"),
    initialSeed = cms.untracked.uint32(1823)
    ))

##  Heavy Ion EGamma sequence
process.load("RecoHI.HiEgammaAlgos.HiEgamma_cff")
process.load("PhysicsTools.PatAlgos.patHeavyIonSequences_cff")
from PhysicsTools.PatAlgos.tools.heavyIonTools import *
configureHeavyIons(process)
process.patPhotons.addGenMatch = cms.bool(False)
process.patPhotons.embedGenMatch= cms.bool(False)
process.photonMatch.matched = cms.InputTag("hiGenParticles")

# Modification for HI
process.load("CmsHi.PhotonAnalysis.MultiPhotonAnalyzer_cfi")
process.multiPhotonAnalyzer.GenParticleProducer = cms.InputTag("hiGenParticles")
process.multiPhotonAnalyzer.PhotonProducer = cms.InputTag("selectedPatPhotons")
process.multiPhotonAnalyzer.VertexProducer = cms.InputTag("hiSelectedVertex")
process.multiPhotonAnalyzer.doStoreMET = cms.untracked.bool(False)
process.multiPhotonAnalyzer.doStoreJets = cms.untracked.bool(False)
process.multiPhotonAnalyzer.OutputFile = cms.string('hiMPA.root')
process.multiPhotonAnalyzer.isMC_      = cms.untracked.bool(False)
process.singlePhotonAnalyzer.isMC_      = cms.untracked.bool(False)

# Comp Cone Analysis
process.multiPhotonAnalyzer.doStoreCompCone = cms.untracked.bool(True)

# Change the track collection
process.photons.isolationSumsCalculatorSet.trackProducer = process.multiPhotonAnalyzer.TrackProducer

# timing
#process.Timing = cms.Service("Timing")                                         

# random Cone
process.load("RandomConeAna.RandomPhotonProducer.randomConeSequence_cff")
process.compleSuperCluster.etCut            = process.multiPhotonAnalyzer.GammaPtMin
process.compleSuperCluster.etaCut           = process.multiPhotonAnalyzer.GammaEtaMax
process.compleSuperCluster.hoeCut           = cms.untracked.double(0.5)
#for HI setting
process.complePhoton.primaryVertexProducer  = process.multiPhotonAnalyzer.VertexProducer
process.complePhoton.isolationSumsCalculatorSet.trackProducer = process.multiPhotonAnalyzer.TrackProducer
process.randomPhoton.isolationSumsCalculatorSet.trackProducer = process.multiPhotonAnalyzer.TrackProducer
process.randomPhoton.primaryVertexProducer  = process.multiPhotonAnalyzer.VertexProducer
process.randomPhotonAnalyzer.vertexProducer = process.multiPhotonAnalyzer.VertexProducer


process.randomPhotonAnalyzer.useHICentrality = cms.untracked.bool(True)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('randomConeNtuple.root'),
                                   closeFileFast = cms.untracked.bool(True)
                                   )

########### End process #################
process.load('Configuration.StandardSequences.EndOfProcess_cff')


# let it run
process.p = cms.Path(
    #  process.photonCore*process.photons*process.photonIDSequence*
    #    process.patHeavyIonDefaultSequence 
    #    process.heavyIon *

    process.makeHeavyIonPhotons *
    process.selectedPatPhotons *
    process.complePhotonSequence *
    process.randomConeSqeunce *
    process.multiPhotonAnalyzer *
    process.endOfProcess
    )


