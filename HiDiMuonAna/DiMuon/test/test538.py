##Gen level ploting are now  working 
##Vineet Kumar & Prashant Shukla
import FWCore.ParameterSet.Config as cms
process = cms.Process("DiMuonOnia2DPlots")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1


#process.load("Configuration.StandardSequences.Geometry_cff")

#new files
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load("SimTracker.TrackAssociation.TrackAssociatorByChi2_cfi")
process.load("SimTracker.TrackAssociation.TrackAssociatorByHits_cfi")
process.load("SimGeneral.TrackingAnalysis.trackingParticles_cfi")



process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'STARTHI53_V17::All' # MC

process.GlobalTag.globaltag = 'STARTHI53_V25::All' # MC right tag for centrality

process.load("Configuration.StandardSequences.MagneticField_cff")

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFtowersPlusTrunc"),
    nonDefaultGlauberModel = cms.string("Hijing"),
    centralitySrc = cms.InputTag("pACentrality"),
    #pPbRunFlip = cms.untracked.uint32(99999999)
    )
process.load('RecoHI.HiCentralityAlgos.HiCentrality_cfi')



process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),

                            fileNames = cms.untracked.vstring(
    

    
'file:/afs/cern.ch/user/k/kumarv/scratch0/CMSSW_5_3_8_HI/src/Y1sGen/MC_Upsilon1S_NoFSR_276TeV_FEVTSIM.root'

#"/store/group/phys_heavyions/dileptons/MC2013/5TeV/Upsilon1S/Skims/onia2MuMuPAT_MC_0.root",
#"/store/group/phys_heavyions/dileptons/MC2013/5TeV/Upsilon1S/Skims/onia2MuMuPAT_MC_1.root",
#"/store/group/phys_heavyions/dileptons/MC2013/5TeV/Upsilon1S/Skims/onia2MuMuPAT_MC_2.root",
#"/store/group/phys_heavyions/dileptons/MC2013/5TeV/Upsilon1S/Skims/onia2MuMuPAT_MC_3.root",
#"/store/group/phys_heavyions/dileptons/MC2013/5TeV/Upsilon1S/Skims/onia2MuMuPAT_MC_4.root",
#"/store/group/phys_heavyions/dileptons/MC2013/5TeV/Upsilon1S/Skims/onia2MuMuPAT_MC_5.root",
#"/store/group/phys_heavyions/dileptons/MC2013/5TeV/Upsilon1S/Skims/onia2MuMuPAT_MC_6.root",
#"/store/group/phys_heavyions/dileptons/MC2013/5TeV/Upsilon1S/Skims/onia2MuMuPAT_MC_7.root",
#"/store/group/phys_heavyions/dileptons/MC2013/5TeV/Upsilon1S/Skims/onia2MuMuPAT_MC_8.root",
#"/store/group/phys_heavyions/dileptons/MC2013/5TeV/Upsilon1S/Skims/onia2MuMuPAT_MC_9.root"


),
                            dropDescendantsOfDroppedBranches=cms.untracked.bool(False),
                            inputCommands=cms.untracked.vstring(
                            'keep *',
                            'drop *_TriggerResults_*_Onia2MuMuPAT',
                            'drop *_TriggerResults_*_RECO',
                            ),
                            
                            
                            

                            
                            


)

#process.options = cms.untracked.PSet(SkipEvent = cms.untracked.vstring('ProductNotFound'))

process.dimuonsOnia2DPlots = cms.EDAnalyzer(
    "DiMuonOnia2DPlots",
    OutputFileName = cms.untracked.string('file:Y1S_OniaTree_PriMC_NoFSR_276TeV_All02052013.root'),
    
    #OutputFileName = cms.untracked.string('_output_file_'),
    HLTFilterName=cms.untracked.string('HLT_L1DoubleMu0_v1'),
    MotherID=cms.untracked.string("Upsilon1s"),
    IsGenInfo=cms.untracked.string("TRUE"),
    IsPATInfo=cms.untracked.string("FALSE"),
    IsCentInfo=cms.untracked.string("FALSE"),
    IsPATWTInfo=cms.untracked.string("FALSE"),
    IsRecoInfo=cms.untracked.string("FALSE"),
    IsCuts = cms.untracked.bool(True)
    )


process.eventInfo = cms.OutputModule (
    "AsciiOutputModule"
       )

process.dimuonsOnia2DPlotsPath = cms.Path(process.dimuonsOnia2DPlots)
process.schedule=cms.Schedule(process.dimuonsOnia2DPlotsPath)


