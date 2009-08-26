import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os 

process = cms.Process("TEST")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")

#global tags for conditions data: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions#22X_Releases_starting_from_CMSSW
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V5::All'

##################################################################################

# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

# setup any defaults you want
options.output = 'output_testVertex.root'
options.secondaryOutput = 'edmFile_testVertex.root'
options.files= 'dcache:/pnfs/cmsaf.mit.edu/hibat/cms/mc/hydjet_b4_310/HYDJET_MC31XV3_pt11_RECO_7.root'
options.maxEvents = -1 

# get and parse the command line arguments
options.parseArguments()

##################################################################################
# Some Services

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.debugModules = ['hiPixel3ProtoTracks','hiPixelMedianVertex','hiPixelAdaptiveVertex']  
process.MessageLogger.categories = ['MinBiasTracking','heavyIonHLTVertexing']
process.MessageLogger.cerr.threshold = "DEBUG" 

			   
#process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
#                                        ignoreTotal=cms.untracked.int32(0),
#                                        oncePerEventMode = cms.untracked.bool(False)
#                                        )

#process.Timing = cms.Service("Timing")

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
process.load("RecoHI.Configuration.Reconstruction_HI_cff")              # full heavy ion reconstruction

##############################################################################
# Vtx Analyzer
process.vtxAnalyzer = cms.EDAnalyzer("VtxAnalyzer")
# output file service
process.TFileService = cms.Service("TFileService", fileName = cms.string(options.output) 
)


##############################################################################
# Output EDM File
process.load("RecoHI.Configuration.RecoHI_EventContent_cff") #load keep/drop output commands
process.output = cms.OutputModule("PoolOutputModule",
                                  process.RECODEBUGEventContent,
                                  compressionLevel = cms.untracked.int32(2),
                                  commitInterval = cms.untracked.uint32(1),
                                  fileName = cms.untracked.string(options.secondaryOutput)
                                  )

##################################################################################
# Paths
#process.vtxreco = cms.Path(process.hiPixelVertices)
process.ana = cms.Path(process.vtxAnalyzer)
#process.save = cms.EndPath(process.output)
