import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os 

process = cms.Process("TEST")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")

#global tags for conditions data:
#https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V9::All'

##################################################################################

# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

# setup any defaults you want
options.output = 'output_testVertex.root'
options.secondaryOutput = 'edmFile_testVertex.root'
options.files = [
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/F8157400-F0B6-DE11-8940-001D09F29114.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/E82BBD98-F4B6-DE11-B138-001D09F2A690.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/E6F3BDBD-F9B6-DE11-BDAD-001D09F2437B.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/E6B3AB36-ECB6-DE11-A5A3-001D09F251FE.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/C6E6BA91-F6B6-DE11-8525-000423D987E0.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/A8564AC8-FCB6-DE11-8892-001D09F2924F.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/8CBE366A-09B7-DE11-9178-000423D33970.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/786C7243-00B7-DE11-8FF0-000423D94E70.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/6EA2BDAA-FEB6-DE11-88F8-001D09F24664.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/668FF650-03B7-DE11-9EC3-001D09F291D2.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/60C0481F-EFB6-DE11-985C-000423D98634.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/50A27EB5-E7B6-DE11-86F7-000423D9A2AE.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/3C01DE3C-F2B6-DE11-BB35-001D09F2AD4D.root',
       '/store/relval/CMSSW_3_3_0/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0008/2E0345BE-06B7-DE11-9DC3-001D09F291D7.root' ]
options.maxEvents = 1 

# get and parse the command line arguments
options.parseArguments()

##################################################################################
# Some Services

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.debugModules = ['*']  
process.MessageLogger.categories = ['HeavyIonVertexing','heavyIonHLTVertexing']
process.MessageLogger.cerr = cms.untracked.PSet(
    threshold = cms.untracked.string('DEBUG'),
    DEBUG = cms.untracked.PSet(
        limit = cms.untracked.int32(0)
    ),
	INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(0)
    ),
    HeavyIonVertexing = cms.untracked.PSet(
        limit = cms.untracked.int32(-1)
	),
    heavyIonHLTVertexing = cms.untracked.PSet(
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
process.load("Configuration.StandardSequences.ReconstructionHeavyIons_cff")
process.load("Configuration.StandardSequences.RawToDigi_cff")

#test functionality of best vertex selector
#process.hiPixelAdaptiveVertex.TrackLabel = cms.InputTag("hiPixel3ProtoTracks")

##############################################################################
# Vtx Analyzer
process.vtxAnalyzer = cms.EDAnalyzer("VtxAnalyzer")
# output file service
process.TFileService = cms.Service("TFileService", fileName = cms.string(options.output) 
)


##############################################################################
# Output EDM File
process.load("Configuration.EventContent.EventContentHeavyIons_cff")
process.output = cms.OutputModule("PoolOutputModule",
                                  process.FEVTDEBUGEventContent,
                                  compressionLevel = cms.untracked.int32(2),
                                  commitInterval = cms.untracked.uint32(1),
                                  fileName = cms.untracked.string(options.secondaryOutput)
                                  )

##################################################################################
# Paths
process.localreco = cms.Path(process.RawToDigi*process.offlineBeamSpot*process.trackerlocalreco)
process.vtxreco = cms.Path(process.hiPixelVertices)
process.ana = cms.Path(process.vtxAnalyzer)
process.save = cms.EndPath(process.output)
