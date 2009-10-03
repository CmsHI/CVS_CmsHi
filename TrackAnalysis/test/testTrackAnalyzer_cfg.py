import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os 

process = cms.Process("TEST")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")

#global tags for conditions data: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_v8::All'

##################################################################################

# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

# setup any defaults you want
options.output = 'outputTree_testAnalyzer.root'
options.secondaryOutput = 'edmFile_testAnalyzer.root'
options.files = '/store/relval/CMSSW_3_3_0_pre5/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V8-v1/0004/D2E41C64-41AB-DE11-890F-001D09F2932B.root'
#options.files = '/store/relval/CMSSW_3_3_0_pre5/RelValHydjetQ_B0_4TeV/GEN-SIM-RAW/MC_31X_V8-v1/0004/E61657FD-9AAB-DE11-B79D-001D09F2437B.root'
options.maxEvents = 1 

# get and parse the command line arguments
options.parseArguments()

##################################################################################
# Some Services

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.debugModules = ['testHighPtGlobalTracks']  
process.MessageLogger.categories = ['TrackAnalyzer']
process.MessageLogger.cerr = cms.untracked.PSet(
    threshold = cms.untracked.string('DEBUG'),
    DEBUG = cms.untracked.PSet(
        limit = cms.untracked.int32(0)
    ),
	INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(0)
    ),
    TrackAnalyzer = cms.untracked.PSet(
        limit = cms.untracked.int32(-1)
    )
)
			   
process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
                                        ignoreTotal=cms.untracked.int32(0),
                                        oncePerEventMode = cms.untracked.bool(False)
                                        )

process.Timing = cms.Service("Timing")

##################################################################################
# Input Source
process.source = cms.Source('PoolSource',
	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
	fileNames = cms.untracked.vstring(options.files) 
)
							
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

##################################################################################
#Reconstruction
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.StandardSequences.ReconstructionHeavyIons_cff") 

process.hiPixel3PrimTracks.FilterPSet.useClusterShape = False
process.hiPixel3PrimTracks.FilterPSet.nSigmaTipMaxTolerance = 0.0
process.hiPixel3PrimTracks.FilterPSet.nSigmaLipMaxTolerance = 0.0
process.hiPixel3PrimTracks.FilterPSet.lipMax = 0.0

##############################################################################
# Track Analyzer
process.load("CmsHi.TrackAnalysis.testHighPtGlobalTracks_cff")   # track association and analyzer
process.testHighPtGlobalTracks.trackCollection = ["hiPixel3PrimTracks"]
process.testHighPtGlobalTracks.resultFile = options.output
#process.testHighPtGlobalTracks.keepLowPtSimTracks = True

process.TrackAssociatorByHits.SimToRecoDenominator = 'reco' #quality = purity i.e. (shared/reco)

##############################################################################
# Output EDM File
process.load("Configuration.EventContent.EventContentHeavyIons_cff") #load keep/drop output commands
process.output = cms.OutputModule("PoolOutputModule",
                                  process.FEVTDEBUGEventContent,
                                  compressionLevel = cms.untracked.int32(2),
                                  commitInterval = cms.untracked.uint32(1),
                                  fileName = cms.untracked.string(options.secondaryOutput)
                                  )

##################################################################################
# Paths
process.localreco = cms.Sequence(process.RawToDigi*process.offlineBeamSpot*process.trackerlocalreco)
process.pxlreco = cms.Sequence(process.hiPixelVertices*process.hiPixel3PrimTracks)
process.trkreco = cms.Sequence(process.heavyIonTracking)

process.p = cms.Path(process.localreco * process.pxlreco * process.testHighPtGlobalTracks)
#process.save = cms.EndPath(process.output)
