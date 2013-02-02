##Gen level ploting are now  working 
##Vineet Kumar & Prashant Shukla
import FWCore.ParameterSet.Config as cms
process = cms.Process("DiMuonOnia2DPlots")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1


#process.load("Configuration.StandardSequences.Geometry_cff")

#new files
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("SimTracker.TrackAssociation.TrackAssociatorByChi2_cfi")
process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")
process.load("SimGeneral.TrackingAnalysis.trackingParticles_cfi")



process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'STARTHI53_V17::All' # MC


process.load("Configuration.StandardSequences.MagneticField_cff")

#from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
#overrideCentrality(process)
#process.HeavyIonGlobalParameters = cms.PSet(
#      centralityVariable = cms.string("HFtowersPlusTrunc"),
#        nonDefaultGlauberModel = cms.string("Hijing"),
#       centralitySrc = cms.InputTag("pACentrality"),
#        #pPbRunFlip = cms.untracked.uint32(99999999)
#        )
#process.load('RecoHI.HiCentralityAlgos.HiCentrality_cfi')



process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),

                            fileNames = cms.untracked.vstring(



    'file:/afs/cern.ch/work/k/kumarv/public/Y1SUnBoostedSkim/onia2MuMuPAT_UnBoosted.root'
    #_input_
   

    ),
                            dropDescendantsOfDroppedBranches=cms.untracked.bool(False),
                            inputCommands=cms.untracked.vstring(
    'keep *',
    'drop *_TriggerResults_*_Onia2MuMuPAT',
    'drop *_TriggerResults_*_RECO',
    ),








)

process.dimuonsOnia2DPlots = cms.EDAnalyzer(
    "DiMuonOnia2DPlots",
    OutputFileName = cms.untracked.string('file:test_Coll_Unboosted.root'),
    #OutputFileName = cms.untracked.string('_output_file_'),
    HLTFilterName=cms.untracked.string('HLT_L1DoubleMu0_v1'),
    MotherID=cms.untracked.string("Upsilon1s"),
    IsGenInfo=cms.untracked.string("TRUE"),
    IsPATInfo=cms.untracked.string("TRUE"),
    IsPATWTInfo=cms.untracked.string("TRUE"),
    IsRecoInfo=cms.untracked.string("FALSE"),
    IsCuts = cms.untracked.bool(True)
    )


process.eventInfo = cms.OutputModule (
    "AsciiOutputModule"
       )

process.dimuonsOnia2DPlotsPath = cms.Path(process.dimuonsOnia2DPlots)
process.schedule=cms.Schedule(process.dimuonsOnia2DPlotsPath)


