#
# \version $Id: MPA_Apr27_V00-00-06_MC35X_START3X_V26.py,v 1.1 2010/04/27 16:15:21 musella Exp $
#

import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

## Source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    #  'dcache:///pnfs/cmsaf.mit.edu/t2bat/cms/store/user/kimy/MinimumBiasHI/Spring10-JulyAnalysisExercise_MC_37Y_V4-HardEnriched-NZS-v3-RECO-prelim-v1/599a3a4efd1a163b86e329cbf44e9f6a/hiRecoJEX_RAW2DIGI_RECO_9_1_0uP.root'
    'rfio:/castor/cern.ch/cms/store/relval/CMSSW_3_7_0/RelValPyquen_GammaJet_pt20_2760GeV/GEN-SIM-RECO/MC_37Y_V4-v1/0026/B891436A-766A-DF11-9196-0026189438A5.root'
    
    )
)

################# ESSource for the centrality #####
process.load("CondCore.DBCommon.CondDBCommon_cfi")
process.CondDBCommon.connect = "sqlite_file:CentralityTables.db"
process.PoolDBESSource = cms.ESSource("PoolDBESSource",
                                      process.CondDBCommon,
                                      toGet = cms.VPSet(cms.PSet(record = cms.string('HeavyIonRcd'),
                                                                 tag = cms.string('HFhits40_MC_Hydjet2760GeV_MC_3XY_V24_v0')
                                                                 )
                                                        )
                                      )
######################################################


## # EGamma sequence
process.load("RecoHI.HiEgammaAlgos.HiEgamma_cff")

## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(15) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START3X_V26::All')
# process.GlobalTag.globaltag = cms.string('GR10_P_V4::All')
process.load("Configuration.StandardSequences.MagneticField_cff")

## Standard PAT Configuration File
#process.load("PhysicsTools.PatAlgos.patSequences_cff")
process.load("PhysicsTools.PatAlgos.patHeavyIonSequences_cff")
from PhysicsTools.PatAlgos.tools.heavyIonTools import *
configureHeavyIons(process)

process.patPhotons.addGenMatch = cms.bool(False)
process.patPhotons.embedGenMatch= cms.bool(False)

#from PhysicsTools.PatAlgos.tools.coreTools import *
# turn off MC matching for the process -- ONLY needed if running over data -- for MC comment out
#removeMCMatching(process, ['All'])

# reduce verbosity
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(200)

# configure HLT
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('40 OR 41')

# EGAMMA customization 
#process.photons.minSCEtBarrel = 15.
#process.photons.minSCEtEndcap = 15.
#process.photonCore.minSCEt = 10.
#process.conversionTrackCandidates.minSCEt =1.
#process.conversions.minSCEt =1.
#process.trackerOnlyConversions.AllowTrackBC = cms.bool(False)
#process.trackerOnlyConversions.AllowRightBC = cms.bool(False)
#process.trackerOnlyConversions.MinApproach = cms.double(-.25)
#process.trackerOnlyConversions.DeltaCotTheta = cms.double(.07)
#process.trackerOnlyConversions.DeltaPhi = cms.double(.2)

# Remove impact parameter cuts
#process.photons.isolationSumsCalculatorSet.transImpactParameterA_Barrel=9999.0
#process.photons.isolationSumsCalculatorSet.transImpactParameterB_Barrel=9999.0
#process.photons.isolationSumsCalculatorSet.transImpactParameterA_Endcap=9999.0
#process.photons.isolationSumsCalculatorSet.transImpactParameterB_Endcap=9999.0
#process.photons.isolationSumsCalculatorSet.longImpactParameterA_Barrel=9999.0
#process.photons.isolationSumsCalculatorSet.longImpactParameterB_Barrel=9999.0
#process.photons.isolationSumsCalculatorSet.longImpactParameterA_Endcap=9999.0
#process.photons.isolationSumsCalculatorSet.longImpactParameterB_Endcap=9999.0

# Modification for HI
process.load("QCDPhotonAnalysis.DataAnalyzers.MultiPhotonAnalyzer_cfi")

process.multiPhotonAnalyzer.GenParticleProducer = cms.InputTag("hiGenParticles")
process.multiPhotonAnalyzer.PhotonProducer = cms.InputTag("selectedPatPhotons")
process.multiPhotonAnalyzer.VertexProducer = cms.InputTag("hiSelectedVertex")
process.multiPhotonAnalyzer.doStoreMET = cms.untracked.bool(False)
process.multiPhotonAnalyzer.doStoreJets = cms.untracked.bool(False)
process.multiPhotonAnalyzer.OutputFile = cms.string('ntuple-HiMPA.root')
process.multiPhotonAnalyzer.isMC_      = cms.untracked.bool(False)
process.singlePhotonAnalyzer.isMC_      = cms.untracked.bool(False)

#process.photonMatch.matched = cms.InputTag("hiGenParticles")
#process.selectDigi.barrelSuperClusterProducer = cms.InputTag("correctedIslandBarrelSuperClusters")
#process.selectDigi.endcapSuperClusterProducer = cms.InputTag("correctedIslandEndcapSuperClusters")


process.load("RandomConeAna.RandomPhotonProducer.randomConeSequence_cff")
process.compleSuperCluster.etCut            = process.multiPhotonAnalyzer.GammaPtMin
process.compleSuperCluster.etaCut           = process.multiPhotonAnalyzer.GammaEtaMax
process.compleSuperCluster.hoeCut           = cms.untracked.double(0.5)
process.complePhoton.isolationSumsCalculatorSet.trackProducer = process.multiPhotonAnalyzer.TrackProducer
#for HI setting
process.complePhoton.isolationSumsCalculatorSet.trackProducer = cms.InputTag("hiSelectedTracks")
process.complePhoton.primaryVertexProducer = cms.string('hiSelectedVertex')
process.compleSuperCluster.etCut            = process.multiPhotonAnalyzer.GammaPtMin
process.compleSuperCluster.etaCut           = process.multiPhotonAnalyzer.GammaEtaMax
process.compleSuperCluster.hoeCut           = cms.untracked.double(0.5)

#process.TFileService = cms.Service("TFileService",
#                                   fileName = cms.string('compConeAna.root'),
#                                   closeFileFast = cms.untracked.bool(True)
#                                   )



########### End process #################
process.load('Configuration.StandardSequences.EndOfProcess_cff')

process.Timing = cms.Service("Timing")


# let it run
process.p = cms.Path(
    #process.photonCore*process.photons*
    process.photonIDSequence*
    #    process.patHeavyIonDefaultSequence 
    #    process.heavyIon *
    process.makeHeavyIonPhotonsData *
    process.selectedPatPhotons *
    process.complePhotonSequence *
    process.multiPhotonAnalyzer *
    process.endOfProcess
    )


