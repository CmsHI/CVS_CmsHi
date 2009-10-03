import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os 

process = cms.Process("PXLTRKVALIDATOR")
process.load("Configuration/StandardSequences/GeometryPilot2_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V8::All'

##################################################################################

# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

# setup any defaults you want
options.output = 'output_pxlVal.root'
options.secondaryOutput = 'edmFile_pxlVal.root'
#options.files = '/store/relval/CMSSW_3_3_0_pre5/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V8-v1/0004/D2E41C64-41AB-DE11-890F-001D09F2932B.root'
options.files = '/store/relval/CMSSW_3_3_0_pre5/RelValHydjetQ_B0_4TeV/GEN-SIM-RAW/MC_31X_V8-v1/0004/E61657FD-9AAB-DE11-B79D-001D09F2437B.root'
options.maxEvents = 1 

# get and parse the command line arguments
options.parseArguments()

##################################################################################
# Some Services

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.debugModules = ['hiPixel3ProtoTracks','hiPixelMedianVertex','hiPixelAdaptiveVertex']  
process.MessageLogger.categories = ['MinBiasTracking','heavyIonHLTVertexing']
process.MessageLogger.cerr = cms.untracked.PSet(
    threshold = cms.untracked.string('DEBUG'),
    DEBUG = cms.untracked.PSet(
        limit = cms.untracked.int32(0)
    ),
	INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(0)
    ),
    MinBiasTracking = cms.untracked.PSet(
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

###################

#Modified parameters
#process.hiPixel3PrimTracks.RegionFactoryPSet.RegionPSet.originRadius = 0.2

#process.hiPixel3PrimTracks.FilterPSet.useClusterShape = False
process.hiPixel3PrimTracks.FilterPSet.nSigmaTipMaxTolerance = 6.0
process.hiPixel3PrimTracks.FilterPSet.tipMax = 0.3
process.hiPixel3PrimTracks.FilterPSet.chi2 = 1000.

process.hiPixel3PrimTracks.CleanerPSet.ComponentName="TrackCleaner"

###################

# reco pxl track quality cuts
process.selectHiPxlTracks = cms.EDFilter("TrackSelector",
  src = cms.InputTag("hiPixel3PrimTracks"),
  cut = cms.string('pt > 1.0 && abs(eta) < 1.0')
)

# quality cuts on tracking particles
process.load("Validation.RecoTrack.cuts_cff")
process.load("CmsHi.TrackAnalysis.findableSimTracks_cfi")
process.findableSimTracks.minHit = 3
process.findableSimTracks.signalOnly = True
process.findableSimTracks.ptMin = 1.0
process.findableSimTracks.tip = 0.05
process.findableSimTracks.minRapidity=-1.
process.findableSimTracks.maxRapidity=1.

# track associator settings
process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")
process.TrackAssociatorByHits.SimToRecoDenominator = 'reco' #quality = purity i.e. (shared/reco)
process.TrackAssociatorByHits.ThreeHitTracksAreSpecial = True #require all hits shared on 3-hit tracks (default)

# setup pxl track validator
process.load("Validation.RecoTrack.MultiTrackValidator_cff")
process.multiTrackValidator.associators = cms.vstring('TrackAssociatorByHits')
process.multiTrackValidator.UseAssociators = True
process.multiTrackValidator.label = ['selectHiPxlTracks'] # selection on globalPrimTracks
process.multiTrackValidator.label_tp_effic = cms.InputTag("findableSimTracks") # selection on mergedtruth
process.multiTrackValidator.label_tp_fake  = cms.InputTag("cutsTPFake")
process.multiTrackValidator.outputFile = options.output

##############################################################################
# Output EDM File
process.load("Configuration.EventContent.EventContentHeavyIons_cff") #load keep/drop output commands
process.output = cms.OutputModule("PoolOutputModule",
                                  process.FEVTDEBUGEventContent,
                                  compressionLevel = cms.untracked.int32(2),
                                  commitInterval = cms.untracked.uint32(1),
                                  fileName = cms.untracked.string(options.secondaryOutput)
                                  )

###################

# paths
process.localreco = cms.Path(process.RawToDigi*process.offlineBeamSpot*process.trackerlocalreco)
process.pxlreco = cms.Path(process.hiPixelVertices*process.hiPixel3PrimTracks)
#process.trkreco = cms.Path(process.heavyIonTracking)
process.pcut  = cms.Path(process.selectHiPxlTracks * process.findableSimTracks * process.cutsTPFake)
process.pval  = cms.Path(process.multiTrackValidator)
#process.save = cms.EndPath(process.output)




