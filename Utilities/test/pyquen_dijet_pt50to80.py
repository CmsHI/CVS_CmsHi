import FWCore.ParameterSet.Config as cms

process = cms.Process("DIGI")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.Generator_cff")

#global tags for conditions data: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions#31X_pre_releases_and_integration
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'IDEAL_31X::All'

##################################################################################
# Some services

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.debugModules = cms.untracked.vstring("mix")

process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
                                        ignoreTotal=cms.untracked.int32(0),
                                        oncePerEventMode = cms.untracked.bool(False)
                                        )

##################################################################################
# Make sure the random number generator types are consistent with standard

process.RandomNumberGeneratorService.signal = cms.PSet(process.RandomNumberGeneratorService.generator) # For 3_1_X
#process.RandomNumberGeneratorService.signal = cms.PSet(process.RandomNumberGeneratorService.theSource)
process.RandomNumberGeneratorService.signalSIM = cms.PSet(process.RandomNumberGeneratorService.g4SimHits)

process.RandomNumberGeneratorService.signal.initialSeed = 4
process.RandomNumberGeneratorService.signalSIM.initialSeed = 5


##################################################################################
# Pb+Pb Background Source
process.source = cms.Source('PoolSource',
                            #fileNames = cms.untracked.vstring('file:///d00/yjlee/sample/hydjet_mb_2_2_4/1EA7C31D-83FB-DD11-8218-001C23BED6CA.root')
                            fileNames = cms.untracked.vstring('dcache:/pnfs/cmsaf.mit.edu/hibat/cms/users/davidlw/HYDJET_Minbias_4TeV_31X/sim/HYDJET_Minbias_4TeV_seq11_31X.root')
							)

process.maxEvents = cms.untracked.PSet(
                       input = cms.untracked.int32(1)
                       )

##################################################################################
# Generate Pyquen Signal
from GeneratorInterface.PyquenInterface.pyquenPythiaDefault_cff import *
import GeneratorInterface.PyquenInterface.pyquenDefault_cfi
process.signal = GeneratorInterface.PyquenInterface.pyquenDefault_cfi.generator.clone()
process.signal.embeddingMode = cms.bool(True)

# modifications to the default pyquen source (unquenched 100 GeV dijets)
process.signal.PythiaParameters.parameterSets = cms.vstring('pythiaDefault','pythiaJets','kinematics')
process.signal.PythiaParameters.kinematics = cms.vstring (
    "CKIN(3)=100",  #min pthat
    "CKIN(4)=9999", #max pthat
    "CKIN(7)=-2.",  #min rapidity
    "CKIN(8)=2."    #max rapidity
    )	
process.signal.doQuench = False


##################################################################################
# Match vertex of the signal event to the background event
process.load("CmsHi.Utilities.MatchVtx_cfi")

##################################################################################
# Run SIM on Pyquen signal
from Configuration.StandardSequences.Simulation_cff import *
process.signalSIM = g4SimHits
process.signalSIM.Generator.HepMCProductLabel = 'signal' # By default it's "generator" in 3_1_x

##################################################################################
# Embed Pyquen signal into Background source at SIM level
from CmsHi.Utilities.EventEmbedding_cff import *
process.mix=cms.EDProducer('HiEventEmbedder',
                           simEventEmbeddingMixParameters,
                           signalTag = cms.vstring("signal","signalSIM")
                           )

##################################################################################
# Digi + Reconstruction
process.load("CmsHi.Utilities.HiGenParticles_cfi")                      # hiGenParticles (sub-events)
process.load("SimGeneral.TrackingAnalysis.trackingParticles_cfi")# trackingParticles (sim tracks)
process.mergedtruth.HepMCDataLabels = ['signal']

process.load("Configuration.StandardSequences.Digi_cff")# doAllDigi
process.load("Configuration.StandardSequences.L1Emulator_cff")          # L1Emulator
process.load("Configuration.StandardSequences.DigiToRaw_cff")# DigiToRaw
process.load("Configuration.StandardSequences.RawToDigi_cff")# RawToDigi
process.load("RecoHI.Configuration.Reconstruction_HI_cff")              # full heavy ion reconstruction

##############################################################################
# Output EDM File
process.load("CmsHi.Utilities.HiAnalysisEventContent_cff") #load keep/drop output commands
process.output = cms.OutputModule("PoolOutputModule",
                                  process.HITrackAnalysisObjects,
                                  compressionLevel = cms.untracked.int32(2),
                                  commitInterval = cms.untracked.uint32(1),
                                  fileName = cms.untracked.string('outputDijetEmbeddingTest_DIGI.root')
                                  )

##################################################################################
# Paths
process.sim = cms.Sequence(process.signal*process.matchVtx*process.signalSIM*process.mix)
process.gen = cms.Sequence(process.hiGenParticles * process.trackingParticles)
process.digi = cms.Sequence(process.doAllDigi*process.L1Emulator*process.DigiToRaw*process.RawToDigi)

#process.trkreco = cms.Sequence(process.offlineBeamSpot*process.trackerlocalreco*process.heavyIonTracking)
#process.reco = cms.Sequence(process.reconstruct_PbPb)

process.p = cms.Path(process.sim * process.gen * process.digi)
process.save = cms.EndPath(process.output)





               
