import FWCore.ParameterSet.Config as cms

process = cms.Process("Test")

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    'file:HIPAT_output_full.root'
  )
)

process.MessageLogger = cms.Service("MessageLogger")

process.analyzeBasicHiPat = cms.EDFilter("HiPatBasicAnalyzer",
  photonSrc   = cms.untracked.InputTag("selectedLayer1Photons"),
  muonSrc     = cms.untracked.InputTag("selectedLayer1Muons"),                                             
  jetSrc      = cms.untracked.InputTag("selectedLayer1Jets"),
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('analyzeHiPatBasics.root')
                                   )

process.p = cms.Path(process.analyzeBasicHiPat)
