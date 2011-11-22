import FWCore.ParameterSet.Config as cms

from HLTrigger.HLTanalyzers.HLTBitAnalyser_cfi import *

process.hltbitanalysis.UseTFileService = cms.untracked.bool(True)
process.hltanalysis = process.hltbitanalysis.clone(
    dummyBranches = cms.untracked.vstring(
    "HLT_HICentral10_v1",
    "HLT_HICentral10_v2",
    "HLT_HIUCC010_v1",
    "HLT_HIUCC015_v1",
    "HLT_HIUCC010_v2",
    "HLT_HIUCC015_v2",
    "HLT_HISinglePhoton20_v1",
    "HLT_HISinglePhoton30_v1",
    "HLT_HISinglePhoton40_v1",
    "HLT_HISinglePhoton20_v2",
    "HLT_HISinglePhoton30_v2",
    "HLT_HISinglePhoton40_v2",
    "HLT_HISinglePhoton20_v3",
    "HLT_HISinglePhoton30_v3",
    "HLT_HISinglePhoton40_v3",
    ),
    
    l1GtReadoutRecord            = cms.InputTag("gtDigis"),
    l1GctHFBitCounts     = cms.InputTag("gctDigis"),
    l1GctHFRingSums      = cms.InputTag("gctDigis"),
    l1extramu            = cms.string('l1extraParticles'),
    l1extramc            = cms.string('l1extraParticles'),
    hltresults           = cms.InputTag("TriggerResults","","HLT"),
    HLTProcessName       = cms.string("HLT")
    )

process.skimanalysis = cms.EDAnalyzer("FilterAnalyzer",
                                      hltresults = cms.InputTag("TriggerResults","","hiForestAna2011")
                                      )



