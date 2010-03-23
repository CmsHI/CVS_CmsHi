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
process.GlobalTag.globaltag = 'MC_3XY_V21::All'

##################################################################################

# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

# setup any defaults you want
options.output = 'outputTree_testAnalyzer.root'
options.secondaryOutput = 'edmFile_testAnalyzer.root'
options.files = '/store/relval/CMSSW_3_5_2/RelValPyquen_DiJet_pt80to120_4TeV/GEN-SIM-RECO/MC_3XY_V21-v1/0001/FA961928-A01F-DF11-85F6-0030487CD7C0.root'
options.maxEvents=1

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

process.hiPixel3PrimTracks.FilterPSet.ptMin = cms.double(0.2)
process.hiPixel3PrimTracks.FilterPSet.nSigmaTipMaxTolerance = cms.double(4.0)
process.hiPixel3PrimTracks.FilterPSet.tipMax = cms.double(0.2)
process.hiPixel3PrimTracks.FilterPSet.nSigmaLipMaxTolerance = cms.double(4.0)
process.hiPixel3PrimTracks.FilterPSet.lipmax = cms.double(0.2)
#process.hiPixel3PrimTracks.FilterPSet.useClusterShape = cms.bool(True)

##############################################################################
# sim-reco track association
process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")
process.TrackAssociatorByHits.SimToRecoDenominator = cms.string('reco')
process.TrackAssociatorByHits.UseGrouped = cms.bool(False)  

# high pt track analyzer settings
process.testHighPtGlobalTracks = cms.EDAnalyzer("HighPtTrackAnalyzer",
                                                trackCollection = cms.vstring("hiPixel3PrimTracks"),
                                                truthCollection = cms.string("mergedtruth"),
                                                resultFile      = cms.string(options.output),
                                                useAbsoluteNumberOfHits = cms.untracked.bool(False), 
                                                keepLowPtSimTracks = cms.untracked.bool(True), 
                                                infoHiEventTopology = cms.untracked.bool(True) 
                                                )

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
process.rechits = cms.Sequence(process.siPixelRecHits*process.siStripMatchedRecHits)
process.localreco = cms.Sequence(process.RawToDigi*process.offlineBeamSpot*process.trackerlocalreco)
process.vtxreco = cms.Sequence(process.offlineBeamSpot * process.trackerlocalreco * process.hiPixelVertices)
process.pxlreco = cms.Sequence(process.hiPixelVertices*process.hiPixel3PrimTracks)
process.trkreco = cms.Sequence(process.heavyIonTracking)

#process.reco = cms.Path(process.localreco * process.pxlreco * process.testHighPtGlobalTracks)
process.rereco = cms.Path(process.rechits * process.hiPixel3PrimTracks * process.testHighPtGlobalTracks)
#process.save = cms.EndPath(process.output)
