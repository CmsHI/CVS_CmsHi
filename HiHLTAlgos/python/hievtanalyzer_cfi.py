import FWCore.ParameterSet.Config as cms

hiEvtAnalyzer = cms.EDAnalyzer('HiEvtAnalyzer',
   Centrality    = cms.InputTag("hiCentrality"),
   CentralityBin = cms.InputTag("centralityBin"),
   EvtPlane      = cms.InputTag("hiEvtPlane","recoLevel"),
   HiMC          = cms.InputTag("heavyIon"),
   doEvtPlane    = cms.bool(False),
   doMC          = cms.bool(False)
)
