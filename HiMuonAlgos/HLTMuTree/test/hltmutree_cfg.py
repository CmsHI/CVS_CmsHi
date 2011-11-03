import FWCore.ParameterSet.Config as cms

process = cms.Process("hltAnaMu")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.GlobalTag.globaltag = 'GR_R_44_V4::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames = cms.untracked.vstring(
"rfio:/castor/cern.ch/user/m/mironov/cmssw440/MC425/jpsi/v1/jpsimc_rawrecohltdebug_93_1_Rp7.root",
    )
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("test.root")
)

# load centrality
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
  centralityVariable = cms.string("HFhits"),
  nonDefaultGlauberModel = cms.string(""),
  centralitySrc = cms.InputTag("hiCentrality")
)


process.load("CmsHi.HiMuonAlgos.HLTMuTree.hltMuTree_cfi")
process.analysis = cms.EDAnalyzer('HLTMuTree',
  doReco = cms.untracked.bool(True),
  doGen = cms.untracked.bool(False),
)

process.p = cms.Path(process.analysis)
