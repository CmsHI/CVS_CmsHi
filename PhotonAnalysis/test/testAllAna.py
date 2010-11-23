
import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

## MessageLogger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.Timing = cms.Service("Timing")

## Options and Output Report
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    'file:/d101/kimy/recoFiles/HiPhoton15_HIMinBiasHF_skim_99_1_LVg-151027.root'
    ),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
                            )

## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load("RecoHI.HiEgammaAlgos.HiEgamma_cff")

#process.GlobalTag.globaltag = cms.string('START36_V10::All')
process.GlobalTag.globaltag = cms.string('GR10_P_V12::All')  # for data global run.

process.load("Configuration.StandardSequences.MagneticField_cff")

## Standard PAT Configuration File
#process.load("PhysicsTools.PatAlgos.patSequences_cff")
process.load('PhysicsTools.PatAlgos.patHeavyIonSequences_cff')
from PhysicsTools.PatAlgos.tools.heavyIonTools import *
configureHeavyIons(process)

from PhysicsTools.PatAlgos.tools.coreTools import *

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)



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


#ecal filter
process.goodPhotons = cms.EDFilter("PhotonSelector",
                           src = cms.InputTag("photons"),
                           cut = cms.string('et > 40 && hadronicOverEm < 0.1 && r9 > 0.8')
                           )
# leading photon E_T filter
process.photonFilter = cms.EDFilter("EtMinPhotonCountFilter",
                            src = cms.InputTag("goodPhotons"),
                            etMin = cms.double(40.0),
                            minNumber = cms.uint32(1)
                            )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('isoRecHitTree.root'),
                                   closeFileFast = cms.untracked.bool(True)
                                   )

#process.load("RecoHI.HiEgammaAlgos.hiEcalSpikeFilter_cfi")

process.load("CmsHi.PhotonAnalysis.isoConeInspector_cfi")
process.load("CmsHi.PhotonAnalysis.ecalHistProducer_cfi")
process.load("CmsHi.PhotonAnalysis.SpikeInspector_cfi")

process.isoConeMap.etCut = 5;  # For hydjet



process.p = cms.Path(
    #   process.goodPhotons *
    #    process.photonFilter*
    # process.hiEcalSpikeFilter    
  #  process.isoConeMap  *
    process.ecalHistProducer * 
    process.spikeInspector
    )


#process.e = cms.EndPath(process.out)    
    
    
