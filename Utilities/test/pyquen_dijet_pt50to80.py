import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

process = cms.Process("RECO")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.Generator_cff")

#global tags for conditions data: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions#3XY_Releases_MC
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V5::All'

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
process.RandomNumberGeneratorService.hiSignalG4SimHits = cms.PSet(process.RandomNumberGeneratorService.g4SimHits)

process.RandomNumberGeneratorService.hiSignal.initialSeed = 4
process.RandomNumberGeneratorService.hiSignalG4SimHits.initialSeed = 5

##################################################################################

# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

# setup any defaults you want
options.output = 'outputDijetEmbeddingTest_RECODEBUG.root'
#options.files= 'dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/mc/Summer09/Hydjet_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V3-GaussianVtx_312_ver1/0005/FECC5F18-1982-DE11-ACF9-001EC94BA3AE.root'
options.files= 'rfio:/castor/cern.ch/cms/store/relval/CMSSW_3_2_4/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V3-v1/0010/D62F586C-4E84-DE11-80D3-000423D98E54.root'
#options.files= 'rfio:/castor/cern.ch/cms/store/relval/CMSSW_3_2_4/RelValHydjetQ_B0_4TeV/GEN-SIM-RAW/MC_31X_V3-v1/0010/FC70A0E1-6A84-DE11-AE66-000423D98DB4.root'
options.maxEvents = 1 

# get and parse the command line arguments
options.parseArguments()

##################################################################################
# Pb+Pb Background Source
process.source = cms.Source('PoolSource',
	fileNames = cms.untracked.vstring(options.files)
)
							
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

##################################################################################
# Generate Pyquen Signal
from Configuration.Generator.PyquenDefaultSettings_cff import *
import GeneratorInterface.PyquenInterface.pyquenDefault_cfi
process.hiSignal = GeneratorInterface.PyquenInterface.pyquenDefault_cfi.generator.clone()
process.hiSignal.embeddingMode = cms.bool(True)

# modifications to the default pyquen source (unquenched 100 GeV dijets)
process.hiSignal.PythiaParameters.parameterSets = cms.vstring('pythiaDefault','pythiaJets','kinematics')
process.hiSignal.PythiaParameters.kinematics = cms.vstring (
    "CKIN(3)=100",  #min pthat
    "CKIN(4)=9999", #max pthat
    "CKIN(7)=-2.",  #min rapidity
    "CKIN(8)=2."    #max rapidity
    )	
process.hiSignal.doQuench = False


##################################################################################
# Match vertex of the hiSignal event to the background event
process.load("SimGeneral.MixingModule.MatchVtx_cfi")

##################################################################################
# Run SIM on Pyquen hiSignal
from Configuration.StandardSequences.Simulation_cff import *

process.hiSignalG4SimHits = g4SimHits
process.hiSignalG4SimHits.Generator.HepMCProductLabel = 'hiSignal' # By default it's "generator" in 3_x_y

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

process.load("Configuration.StandardSequences.Digi_cff")				# doAllDigi
process.load("Configuration.StandardSequences.L1Emulator_cff")          # L1Emulator
process.load("Configuration.StandardSequences.DigiToRaw_cff")			# DigiToRaw
process.load("Configuration.StandardSequences.RawToDigi_cff")			# RawToDigi
process.load("RecoHI.Configuration.Reconstruction_HI_cff")              # full heavy ion reconstruction

##############################################################################
# Output EDM File
process.load("RecoHI.Configuration.RecoHI_EventContent_cff") #load keep/drop output commands
process.output = cms.OutputModule("PoolOutputModule",
                                  process.RECODEBUGEventContent,
                                  compressionLevel = cms.untracked.int32(2),
                                  commitInterval = cms.untracked.uint32(1),
                                  fileName = cms.untracked.string(options.output)
                                  )

##################################################################################
# Paths
process.sim = cms.Sequence(process.hiSignal*process.matchVtx*process.hiSignalG4SimHits*process.mix)
process.gen = cms.Sequence(process.hiGenParticles * process.trackingParticles)
process.digi = cms.Sequence(process.doAllDigi*process.L1Emulator*process.DigiToRaw*process.RawToDigi)

#process.trkreco = cms.Sequence(process.offlineBeamSpot*process.trackerlocalreco*process.heavyIonTracking)
process.reco = cms.Sequence(process.reconstruct_PbPb)

process.p = cms.Path(process.sim * process.gen * process.digi * process.reco)
process.save = cms.EndPath(process.output)





               
