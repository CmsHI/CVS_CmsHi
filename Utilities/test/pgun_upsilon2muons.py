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

process.RandomNumberGeneratorService.hiSignal = cms.PSet(process.RandomNumberGeneratorService.generator) # For 3_1_X
#process.RandomNumberGeneratorService.hiSignal = cms.PSet(process.RandomNumberGeneratorService.theSource)
process.RandomNumberGeneratorService.hiSignalG4SimHits = cms.PSet(process.RandomNumberGeneratorService.g4SimHits)

process.RandomNumberGeneratorService.hiSignal.initialSeed = 4
process.RandomNumberGeneratorService.hiSignalG4SimHits.initialSeed = 5


##################################################################################
# Pb+Pb Background Source
process.source = cms.Source('PoolSource',
                            fileNames = cms.untracked.vstring('file:///d00/yjlee/sample/hydjet_mb_2_2_4/1EA7C31D-83FB-DD11-8218-001C23BED6CA.root')
                            )

process.maxEvents = cms.untracked.PSet(
                       input = cms.untracked.int32(1)
                       )

##################################################################################
# Generate Particle Gun Signal (Upsilons here)
process.load("CmsHi.Utilities.DecayGun_cfi")
process.hiSignal.kinematicsFile = cms.untracked.string('')
process.hiSignal.ParticleID = cms.untracked.int32(553)
process.hiSignal.doubleParticle = cms.untracked.bool(False)

# Kinematics
process.hiSignal.Ptmin = cms.untracked.double(5.99)
process.hiSignal.Ptmax = cms.untracked.double(6.01)
process.hiSignal.Etamin = cms.untracked.double(-0.01)
process.hiSignal.Etamax = cms.untracked.double(0.01)

# Decay parameters
process.hiSignal.PythiaParameters.parameterSets = cms.vstring('pythiaDefault','upsilonDecay')

##################################################################################
# Match vertex of the hiSignal event to the background event
process.load("SimGeneral.MixingModule.MatchVtx_cfi")

##################################################################################
# Run SIM on Pyquen hiSignal
from Configuration.StandardSequences.Simulation_cff import *
process.hiSignalG4SimHits = g4SimHits
process.hiSignalG4SimHits.Generator.HepMCProductLabel = 'hiSignal' # By default it's "generator" in 3_1_x

##################################################################################
# Embed Pyquen hiSignal into Background source at SIM level
from SimGeneral.MixingModule.HiEventMixing_cff import *
process.mix=cms.EDProducer('HiMixingModule',
                           simEventEmbeddingMixParameters,
                           signalTag = cms.vstring("hiSignal","hiSignalG4SimHits")
                           )

##################################################################################
# Digi + Reconstruction
process.load("CmsHi.Utilities.HiGenParticles_cfi")                      # hiGenParticles (sub-events)
process.load("SimGeneral.TrackingAnalysis.trackingParticles_cfi")# trackingParticles (sim tracks)
process.mergedtruth.HepMCDataLabels = ['hiSignal']

process.load("Configuration.StandardSequences.Digi_cff")# doAllDigi
process.load("Configuration.StandardSequences.L1Emulator_cff")          # L1Emulator
process.load("Configuration.StandardSequences.DigiToRaw_cff")# DigiToRaw
process.load("Configuration.StandardSequences.RawToDigi_cff")# RawToDigi
process.load("RecoHI.Configuration.Reconstruction_HI_cff")              # full heavy ion reconstruction

##################################################################################
# Digi + Reconstruction of Signal-Only

process.noMix = noMix


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
process.sim = cms.Sequence(process.hiSignal*process.matchVtx*process.hiSignalG4SimHits*process.mix)
process.gen = cms.Sequence(process.hiGenParticles * process.trackingParticles)
process.digi = cms.Sequence(process.doAllDigi*process.L1Emulator*process.DigiToRaw*process.RawToDigi)

#process.trkreco = cms.Sequence(process.offlineBeamSpot*process.trackerlocalreco*process.heavyIonTracking)
#process.reco = cms.Sequence(process.reconstruct_PbPb)

process.p = cms.Path(process.sim * process.gen * process.digi)
process.save = cms.EndPath(process.output)





               
