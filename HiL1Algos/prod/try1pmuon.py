import FWCore.ParameterSet.Config as cms

def removePatMCOne(patJets):
  patJets.addGenPartonMatch   = False
  patJets.embedGenPartonMatch = False
  patJets.genPartonMatch      = ''
  patJets.addGenJetMatch      = False
  patJets.genJetMatch	      = ''
  patJets.getJetMCFlavour     = False
  patJets.JetPartonMapSource  = ''
  
process = cms.Process('JetAna')

# process.options = cms.untracked.PSet(
    # wantSummary = cms.untracked.bool(True)
# )

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
    # 'file:/d102/velicanu/prod/data/96A31CE6-1921-E111-B606-00A0D1E953AA.root'
    # 'file:/mnt/hadoop/cms/store/user/velicanu/reco/96A31CE6-1921-E111-B606-00A0D1E953AA.root'
    # 'file:/mnt/hadoop/cms/store/user/velicanu/reco/96A31CE6-1921-E111-B606-00A0D1E953AA.root'
    # 'file:/net/hidsk0001/d00/scratch/dav2105/reco/step2_RAW2DIGI_L1Reco_RECO_94_1_Br3.root'
    # 'file:/net/hisrv0001/home/dav2105/run/CMSSW_4_4_4/src/mbl1ivan/step2_RAW2DIGI_L1Reco_RECO.root'
    'file:/mnt/hadoop/cms/store/user/velicanu/HIMinBiasUPC/hiL1TriggerUpgrade-v1/ca244ca4b350f7d8b4b8f1c6d4172fde/step2_RAW2DIGI_L1Reco_RECO_99_1_vvK.root'
    ))

process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32(-1))

            

#load some general stuff
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('RecoLocalTracker.SiPixelRecHits.PixelCPEESProducers_cff')
# process.hiSelectedTrackHighPurity = cms.EDFilter("TrackSelector",
   # src = cms.InputTag("hiSelectedTracks"),
   # cut = cms.string(
   # 'quality("highPurity")')
# )
#process.MessageLogger.cerr.FwkReport.reportEvery = 100
# process.GlobalTag.globaltag = 'GR_R_39X_V6B::All'
process.load('Configuration.EventContent.EventContentHeavyIons_cff')


process.GlobalTag.globaltag = 'GR_P_V27A::All'
# process.GlobalTag.globaltag = 'GR_R_44_V7::All'


# load centrality
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
	centralityVariable = cms.string("HFtowers"),
	nonDefaultGlauberModel = cms.string(""),
	centralitySrc = cms.InputTag("hiCentrality")
	)

# tree output
process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("HiForest.root"))

# Define Analysis sequencues
process.load('CmsHi.JetAnalysis.EventSelection_cff')
#process.load('CmsHi.JetAnalysis.ExtraGenReco_cff')
#process.load('CmsHi.JetAnalysis.ExtraTrackReco_cff')
process.load('CmsHi.JetAnalysis.ExtraPfReco_cff')
process.load('CmsHi.JetAnalysis.ExtraJetReco_cff')
process.load('CmsHi.JetAnalysis.ExtraEGammaReco_cff')
process.load('CmsHi.JetAnalysis.PatAna_cff')
process.load('CmsHi.JetAnalysis.JetAnalyzers_cff')
process.load('CmsHi.JetAnalysis.EGammaAnalyzers_cff')
process.load("MitHig.PixelTrackletAnalyzer.trackAnalyzer_cff")

process.icPu5JetAnalyzer.isMC = False

# Muons 
process.load("MuTrig.HLTMuTree.hltMuTree_cfi")
process.muonTree = process.hltMuTree.clone()
process.muonTree.doGen = cms.untracked.bool(False)

# Event tree
process.load("CmsHi/HiHLTAlgos.hievtanalyzer_cfi")
process.hiEvtAnalyzer.doEvtPlane = cms.bool(True)

process.reco_extra_jet    = cms.Path( process.iterativeConePu5CaloJets)
                                      
process.pat_step          = cms.Path( 
                                      process.icPu5patSequence_data
                                      )


# jet
removePatMCOne(process.icPu5patJets)

# l1 primitives
process.demo = cms.EDAnalyzer('TriggerPrimitives',
                              ECALDigis = cms.InputTag("ecalDigis:EcalTriggerPrimitives"),
                              HCALDigis = cms.InputTag("hcalDigis"),
                              GCTDigis = cms.InputTag("gctDigis")
)

# hlt
process.load('HLTrigger.HLTanalyzers.HLTBitAnalyser_cfi')
process.hltbitanalysis.UseTFileService                  = cms.untracked.bool(True)
process.hltanalysis = process.hltbitanalysis.clone(
  dummyBranches = cms.untracked.vstring(),
  l1GtReadoutRecord    = cms.InputTag("gtDigis"),
  l1GctHFBitCounts     = cms.InputTag("gctDigis"),
  l1GctHFRingSums      = cms.InputTag("gctDigis"),
  l1extramu            = cms.string('l1extraParticles'),
  l1extramc            = cms.string('l1extraParticles'),
  hltresults           = cms.InputTag("TriggerResults","","HLT"),
  HLTProcessName       = cms.string("HLT")
 )

process.ana_step          = cms.Path( 
                                      process.icPu5JetAnalyzer +
                                      process.muonTree +
                                      process.hiEvtAnalyzer +
                                      process.hltanalysis +
                                      process.demo
                                      )
                                      

# =============== Final Schedule =====================
process.schedule = cms.Schedule(process.reco_extra_jet,process.pat_step,process.ana_step)




# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.2 $'),
    annotation = cms.untracked.string('step2 nevts:2'),
    name = cms.untracked.string('PyReleaseValidation')
)










