import FWCore.ParameterSet.Config as cms

process = cms.Process('EvtAna')

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                            fileNames = cms.untracked.vstring(
    #'file:/afs/cern.ch/user/t/tuos/work/public/pPb/AMPT/evening/pPbRecoShift_f1001_e.root'
    #'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3130_e.root', 'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3131_e.root', 'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3132_e.root', 'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3133_e.root', 'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3134_e.root', 'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3140_e.root', 'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3141_e.root', 'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3142_e.root', 'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3143_e.root', 'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3155_e.root', 'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3156_e.root', 'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Hijing/pPbRecoShift_f3157_e.root'
    #'root://eoscms//eos/cms/store/group/phys_heavyions/cbaus/pPb_5020_eposLHC_5_3_3_patch3/RECO/job_N200_1.root','root://eoscms//eos/cms/store/group/phys_heavyions/cbaus/pPb_5020_eposLHC_5_3_3_patch3/RECO/job_N200_2.root'
    'root://eoscms//eos/cms/store/group/phys_heavyions/cbaus/pPb_5020_eposLHC_5_3_7_patch1/RECO/job_N200_945.root'
    #'file:/afs/cern.ch/user/t/tuos/work/public/pPb/Data/9CC7A87A-31FF-E111-AD42-0025901D6288.root'
    ))

process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32(-1))

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'STARTHI53_V9::All'
#process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('RecoLocalTracker.SiPixelRecHits.PixelCPEESProducers_cff')

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('GeneratorInterface.HiGenCommon.HeavyIon_cff')

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltZeroBiasSingleTrack = process.hltHighLevel.clone()
process.hltZeroBiasSingleTrack.HLTPaths = ["HLT_PAZeroBiasPixel_SingleTrack_v1"]

process.HeavyIonGlobalParameters = cms.PSet(
	centralityVariable = cms.string("HFtowers"),
	nonDefaultGlauberModel = cms.string("Hydjet_Drum"),
	centralitySrc = cms.InputTag("pACentrality")
)

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("test.root"))

#from CmsHi.Analysis2010.CommonFunctions_cff import *
#overrideCentrality(process)

process.hiEvtAnalyzer = cms.EDAnalyzer('HiEvtAnalyzer',
   Centrality    = cms.InputTag("pACentrality"),
   CentralityBin = cms.InputTag("centralityBin"),
   EvtPlane      = cms.InputTag("hiEvtPlane","recoLevel"),
   EvtPlaneFlat  = cms.InputTag("hiEvtPlaneFlat",""),                               
   Vertex        = cms.InputTag("offlinePrimaryVerticesWithBS"),
   HiMC          = cms.InputTag("heavyIon"),
   doCentrality  = cms.bool(True),
   doEvtPlane    = cms.bool(False),
   doEvtPlaneFlat= cms.bool(False),                               
   doVertex      = cms.bool(True),
   doMC          = cms.bool(True)
)

process.p = cms.Path(process.siPixelRecHits * process.heavyIon * process.pACentrality * process.hiEvtAnalyzer)
#process.p = cms.Path(process.PAcollisionEventSelection * process.siPixelRecHits * process.heavyIon * process.pACentrality * process.hiEvtAnalyzer)
#process.p = cms.Path(process.hltZeroBiasSingleTrack * process.PAcollisionEventSelection * process.siPixelRecHits * process.heavyIon * process.pACentrality * process.hiEvtAnalyzer)
