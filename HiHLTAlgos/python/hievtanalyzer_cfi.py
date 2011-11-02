import FWCore.ParameterSet.Config as cms

hiEvtAnalyzer = cms.EDAnalyzer('HiEvtAnalyzer',
   Centrality    = cms.InputTag("hiCentrality"),
   CentralityBin = cms.InputTag("centralityBin"),
   EvtPlane      = cms.InputTag("hiEvtPlane","recoLevel"),
   Vertex        = cms.InputTag("hiSelectedVertex"),
   HiMC          = cms.InputTag("heavyIon"),
   doEvtPlane    = cms.bool(False),
   doVertex      = cms.bool(True),
   doMC          = cms.bool(False)
)
