import FWCore.ParameterSet.Config as cms

process = cms.Process("processPixelRecHitValid")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'MC_3XY_V21::All'

############# Services ###############

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

# timing service
process.Timing = cms.Service("Timing")

############# Input Source ###############

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/relval/CMSSW_3_5_2/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_3XY_V21-v1/0016/F61D4025-5F1E-DF11-8EF8-00261894388D.root'))

############# Run HI Validation ###############

# re-make crossing-frame of simhits
process.load("SimGeneral.MixingModule.mixNoPU_cfi")

# re-run track reconstruction
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load("Configuration.StandardSequences.ReconstructionHeavyIons_cff")

# include HI global validation sequence
process.load("CmsHi.TrackAnalysis.globalValidationHeavyIons_cff")
process.globalValidationHI.remove(process.condDataValidation)

# set output file (only needed once. the other modules follow?)
process.pixRecHitsValid.outputFile="test_HI_validation.root"

# path
process.p = cms.Path(process.mix*
                     process.RawToDigi*
                     process.offlineBeamSpot*
                     process.trackerlocalreco*
                     process.heavyIonTracking*
                     process.globalValidationHI
                     )
