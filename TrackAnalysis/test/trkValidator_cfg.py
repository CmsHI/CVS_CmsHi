import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os 

process = cms.Process("TRKVALIDATOR")
process.load("Configuration/StandardSequences/GeometryPilot2_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V9::All'

###################

# message logging
process.MessageLogger.categories = ['TrackAssociator', 'TrackValidator']
process.MessageLogger.debugModules = ['*']
process.MessageLogger.cerr = cms.untracked.PSet(
    threshold = cms.untracked.string('DEBUG'),
    DEBUG = cms.untracked.PSet(
        limit = cms.untracked.int32(0)
    ),
	INFO = cms.untracked.PSet(
        limit = cms.untracked.int32(0)
    ),
    TrackAssociator = cms.untracked.PSet(
        limit = cms.untracked.int32(0)
    ),
    TrackValidator = cms.untracked.PSet(
        limit = cms.untracked.int32(-1)
    )
)

# memory check
process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
                                        ignoreTotal=cms.untracked.int32(0),
                                        oncePerEventMode = cms.untracked.bool(False)
                                        )

# timing service
process.Timing = cms.Service("Timing")

###################

# setup 'standard'  options
options = VarParsing.VarParsing ('standard')

# register custom variables
options.register('skipEv', 0, options.multiplicity.singleton, options.varType.int, "Number of events to skip (default=0)")		

# setup any defaults you want
options.maxEvents = 2 
options.output = 'trkVal.root'
options.secondaryOutput = 'edmFile.root'
inDir = "/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/edwenger/HYDJET_B0_4.0TeV"
for seqNo in range(1,10):
	options.files.append( 'dcache:%s/dijet80_MIX_RECO_%d.root' % (inDir,seqNo) )
	
# get and parse the command line arguments
options.parseArguments()

# setup pool source
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(options.files), 
    skipEvents = cms.untracked.uint32(options.skipEv),
    inputCommands = cms.untracked.vstring('keep *', 'drop *_hiSelectedTracks_*_*'),
    dropDescendantsOfDroppedBranches = cms.untracked.bool(False)
)

###################

# reco track quality cuts
process.load("RecoHI.HiTracking.HISelectedTracks_cfi")
process.hiSelectedTracks.ptMin=2.0

# sim track quality cuts: pt>2, nhit>8, # of hit pixel layers >=3, etc.
process.load("Validation.RecoTrack.cuts_cff")
process.load("CmsHi.TrackAnalysis.findableSimTracks_cfi")

# track associator settings
process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")	 # sim to reco associator
process.TrackAssociatorByHits.SimToRecoDenominator = cms.string('reco')  # matching fraction: shared/nrechit! default='sim', shared/nsimhit
process.TrackAssociatorByHits.UseGrouped = cms.bool(False)               # grouping hits on overlap layers? default=True

# setup track validator
process.load("Validation.RecoTrack.MultiTrackValidator_cff")
process.multiTrackValidator.associators = cms.vstring('TrackAssociatorByHits')
process.multiTrackValidator.UseAssociators = True
process.multiTrackValidator.label = ['hiSelectedTracks'] # selection on globalPrimTracks
process.multiTrackValidator.label_tp_effic = cms.InputTag("findableSimTracks") # selection on mergedtruth
process.multiTrackValidator.label_tp_fake  = cms.InputTag("cutsTPFake")
process.multiTrackValidator.outputFile = options.output


###################

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
process.pcut  = cms.Path(process.hiSelectedTracks 
			* process.findableSimTracks
			* process.cutsTPFake
			)
process.pval  = cms.Path(process.multiTrackValidator)
#process.save = cms.EndPath(process.output)





