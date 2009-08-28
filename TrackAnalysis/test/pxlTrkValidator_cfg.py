import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os 

process = cms.Process("PXLTRKVALIDATOR")
process.load("Configuration/StandardSequences/GeometryPilot2_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V5::All'

##################################################################################

# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

# setup any defaults you want
options.output = 'output_pxlVal.root'
options.secondaryOutput = 'edmFile_pxlVal.root'
#options.files= 'dcache:/pnfs/cmsaf.mit.edu/hibat/cms/mc/hydjet_b4_310/HYDJET_MC31XV3_pt11_RECO_7.root'
options.files = '/store/relval/CMSSW_3_2_5/RelValHydjetQ_B0_4TeV/GEN-SIM-RAW/MC_31X_V5-v1/0011/FC711C9E-4F8E-DE11-8DE0-003048D2C0F4.root'
options.maxEvents = 1 

# get and parse the command line arguments
options.parseArguments()

##################################################################################
# Some Services

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.debugModules = ['hiPixel3ProtoTracks','hiPixelMedianVertex','hiPixelAdaptiveVertex']  
process.MessageLogger.categories = ['MinBiasTracking','heavyIonHLTVertexing']
process.MessageLogger.cout = cms.untracked.PSet(
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
#process.load("RecoHI.Configuration.Reconstruction_HI_cff")              # full heavy ion reconstruction
process.load("Configuration.StandardSequences.ReconstructionHeavyIons_cff")
process.load("Configuration.StandardSequences.RawToDigi_cff")

###################

#test with slightly wider region
#process.hiPixel3PrimTracks.RegionFactoryPSet.RegionPSet.originRadius = 0.2

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
process.TrackAssociatorByHits.ThreeHitTracksAreSpecial = True #require all hits shared on 3-hit tracks

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
process.load("RecoHI.Configuration.RecoHI_EventContent_cff") #load keep/drop output commands
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




