import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing
import os 

process = cms.Process("TRKVALIDATOR")
process.load("Configuration/StandardSequences/GeometryPilot2_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V2::All'

###################

# message logging
process.MessageLogger.categories = ['TrackAssociator', 'TrackValidator']
process.MessageLogger.debugModules = ['*']
process.MessageLogger.cout = cms.untracked.PSet(
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
process.MessageLogger.cerr = cms.untracked.PSet(
    placeholder = cms.untracked.bool(True)
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
options.maxEvents = -1 
options.output = 'trkVal.root'
inDir = "/pnfs/cmsaf.mit.edu/hibat/cms/mc/hydjet_b4_310"
for seqNo in range(0,20):
	options.files.append( 'dcache:%s/HYDJET_MC31XV3_HighPtCleaner_adaptiveVtx_RECO_%d.root' % (inDir,seqNo) )

# get and parse the command line arguments
options.parseArguments()

# setup pool source
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(options.files), 
	skipEvents = cms.untracked.uint32(options.skipEv)
)

###################

# reco track quality cuts
process.load("RecoHI.HiTracking.SelectHITracks_cfi")
process.selectHiTracks.cut = cms.string('pt > 2.0 && d0/d0Error<3. && recHitsSize>12. && chi2prob(chi2,ndof)>0.01')

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
process.multiTrackValidator.label = ['selectHiTracks'] # selection on globalPrimTracks
process.multiTrackValidator.label_tp_effic = cms.InputTag("findableSimTracks") # selection on mergedtruth
process.multiTrackValidator.label_tp_fake  = cms.InputTag("cutsTPFake")
process.multiTrackValidator.outputFile = options.output


###################

# paths
process.pcut  = cms.Path(process.selectHiTracks * process.findableSimTracks * process.cutsTPFake)
process.pval  = cms.Path(process.multiTrackValidator)




