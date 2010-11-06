import FWCore.ParameterSet.Config as cms
from HiDiMuonAna.DiMuon.patCandidatesForDiMuonSkim_cff import *

#goodMuons = cms.EDFilter("MuonViewRefSelector",
goodMuons = cms.EDFilter("CandViewRefSelector",
                         src = cms.InputTag("muons"),
                         #src = cms.InputTag("patMuons"),
                         cut = cms.string('pt >10 & abs(eta)<2.5'),
                         filter = cms.bool(True)
                         )

goodMuonFilter = cms.EDFilter("CandViewCountFilter",
                              src = cms.InputTag("goodMuons"),
                              minNumber = cms.uint32(1)
                              )

#goodSTAMuons =cms.EDFilter("MuonViewRefSelector",
          
goodSTAMuons = cms.EDFilter("CandViewRefSelector",
                            #src = cms.InputTag("patMuons"),
                            src = cms.InputTag("muons"),
                            cut = cms.string('isGlobalMuon = 0 & isStandAloneMuon = 1 & pt > 10 & abs(eta)<2.5'),
                            filter = cms.bool(True)
                            )

goodSTAMuonFilter = cms.EDFilter("CandViewCountFilter",
                             src = cms.InputTag("goodSTAMuons"),
                             minNumber = cms.uint32(1)
                             )



#goodGlobalMuons =cms.EDFilter("MuonViewRefSelector",
goodGlobalMuons = cms.EDFilter("CandViewRefSelector",
                               #src = cms.InputTag("patMuons"),
                               src = cms.InputTag("muons"),
                               cut = cms.string('isGlobalMuon = 1 & pt > 10 & abs(eta)<2.5'),
                               filter = cms.bool(True)
                               )

goodGlobalMuonFilter = cms.EDFilter("CandViewCountFilter",
                                   src = cms.InputTag("goodGlobalMuons"),
                                   minNumber = cms.uint32(1)
                                   )

