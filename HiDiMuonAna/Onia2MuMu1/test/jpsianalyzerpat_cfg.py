import FWCore.ParameterSet.Config as cms

process = cms.Process("ANAPAT")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(250) )

process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames = cms.untracked.vstring(
   # "rfio:///castor/cern.ch/cms/store/user/tdahms/HeavyIons/Onia/MC/v4/Skims/PromptJpsiPt03",
   # "rfio:///castor/cern.ch/cms/store/user/tdahms/HeavyIons/Onia/MC/v4/Skims/PromptJpsiPt36",
   # "rfio:///castor/cern.ch/cms/store/user/tdahms/HeavyIons/Onia/MC/v4/Skims/PromptJpsiPt69",
   # "rfio:///castor/cern.ch/cms/store/user/tdahms/HeavyIons/Onia/MC/v4/Skims/PromptJpsiPt912",
   # "rfio:///castor/cern.ch/cms/store/user/tdahms/HeavyIons/Onia/MC/v4/Skims/PromptJpsiPt1215",
    "rfio:///castor/cern.ch/cms/store/user/tdahms/HeavyIons/Onia/MC/v4/Skims/PromptJpsiPt1530"
    # "rfio:///castor/cern.ch/user/p/pshukla/cms394/MC/DMJPsiOniaSkim/JPsi_OniaSkim_DM_43.root"
    )
)

#process.hltMu3 = cms.EDFilter("HLTHighLevel",
#                 TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
#                 HLTPaths = cms.vstring("HLT_HIL1DoubleMuOpen"),
#                 eventSetupPathsKey = cms.string(''),
#                 andOr = cms.bool(True),
#                 throw = cms.bool(False)
#)


process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 10

process.demo = cms.EDAnalyzer('JPsiAnalyzerPAT',

    src = cms.InputTag("onia2MuMuPatGlbGlb"),
    srcWithCaloMuons = cms.InputTag("onia2MuMuPatGlbCal"),
    writeTree = cms.bool(True),
    treeFileName = cms.string("file:MC_CutTree_Mar26.root"),

    #histFileName = cms.string("Histos_362_data.root"),   
    writeDataSet = cms.bool(True),

    dataSetName = cms.string("DataSetFile.root"),

    triggerForDataset  = cms.string("HLT_HIL1DoubleMuOpen"),
    massMin  = cms.double(2.6),
    massMax = cms.double(3.5),
                              
    pTBinRanges = cms.vdouble(0.0, 6.0, 8.0, 9.0, 10.0, 12.0, 15.0, 40.0),
    # pTBinRanges = cms.vdouble(0.0, 40.0),
    etaBinRanges = cms.vdouble(0.0, 1.3, 2.5),
    # etaBinRanges = cms.vdouble(0.0, 3.0),

    onlyTheBest = cms.bool(True),		
    applyCuts = cms.bool(False),			





    storeEfficiency = cms.bool(False),	
    useBeamSpot = cms.bool(True),
    useRapidity = cms.bool(True),
    useCaloMuons = cms.untracked.bool(False),
    removeSignalEvents = cms.untracked.bool(False),
    removeTrueMuons = cms.untracked.bool(False),
    storeWrongSign = cms.untracked.bool(True),
    writeOutCandidates = cms.untracked.bool(False),
    includePsiPrime = cms.untracked.bool(False),
    massCorrectionMode=cms.int32(3),    # mode 0 no correction, mode 1 constant corr, mode 2 pt dependent corr, mode 3 pt and eta dependent corr
    oniaPDG = cms.int32(443),
    genParticles = cms.InputTag("generator"),
    isMC = cms.untracked.bool(True),
    isPromptMC = cms.untracked.bool(False),
    TriggerResultsLabel = cms.InputTag("TriggerResults"),
    makeJSON = cms.untracked.bool(True) # make a JSON (PseudoJSON.txt) file out of the runs and lumis analyzed 

)


process.p = cms.Path(process.demo)
