import FWCore.ParameterSet.Config as cms
######################################################
# A set of filters for  Z To Mu Mu skimming:
#
from Z0Ana.ZToMuMu.patCandidatesForZMuMuSkim_cff import *

GenMuons = cms.EDFilter("CandViewRefSelector",
                        src = cms.InputTag("genParticles"),
                        cut = cms.string('abs(pdgId) = 13 & (pt > 10 & abs(eta)<2.5)'),
                        filter = cms.bool(True)
                        )

GenDimuons = cms.EDFilter("CandViewShallowCloneCombiner",
                          checkCharge = cms.bool(True),
                          cut = cms.string(' mass > 70 & mass < 120 & charge=0'),
                          #decay = cms.string("muons@+ muons@-")
                          decay = cms.string('GenMuons@+ GenMuons@-')
                          )





# muons
Dimuons = cms.EDFilter("CandViewShallowCloneCombiner",
                       checkCharge = cms.bool(True),
                       cut = cms.string(' mass > 70 & mass < 120 & charge=0'),
                       #decay = cms.string("muons@+ muons@-")
                       decay = cms.string('selectedPatMuonsTriggerMatch@+ selectedPatMuonsTriggerMatch@-')
                       )

dimuonsGlobalSTA = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("Dimuons"),
                                cut = cms.string('(daughter(0).pt>10 & daughter(1).pt>10)&((daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1 &  daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1 &  daughter(0).isGlobalMuon = 1 ))' ),
                                filter = cms.bool(True)
                            )


dimuonsGlobalSTAFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("dimuonsGlobalSTA"),
                                      minNumber = cms.uint32(1)
                                      )


dimuonsGlobal = cms.EDFilter("CandViewRefSelector",
                             src = cms.InputTag("Dimuons"),
                             cut = cms.string('(daughter(0).pt>10 & daughter(1).pt>10) & (daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 )' ),
                             filter = cms.bool(True)
                             )


dimuonsSTA = cms.EDFilter("CandViewRefSelector",
                          src = cms.InputTag("Dimuons"),
                          cut = cms.string('(daughter(0).pt>10 & daughter(1).pt>10) & (daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1) ' ),
                                                          filter = cms.bool(True)
                                                          )






#goodSTAMuons = cms.EDFilter("MuonViewRefSelector",
goodSTAMuons = cms.EDFilter("CandViewRefSelector",
    src = cms.InputTag("muons"),
    cut = cms.string('isStandAloneMuon = 1 & pt > 10 & abs(eta)<2.5'),
    filter = cms.bool(True)                                
)

#dimuonsSTA = cms.EDFilter("CandViewShallowCloneCombiner",
#    checkCharge = cms.bool(True),
#    cut = cms.string('mass > 70 & mass < 120 & charge=0'),
#    decay = cms.string("goodSTAMuons@+ goodSTAMuons@-")
#)
 
dimuonsSTAFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("dimuonsSTA"),
    minNumber = cms.uint32(1)
)


#goodGlobalMuons = cms.EDFilter("MuonViewRefSelector",
goodGlobalMuons = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("muons"),
                                #src=cms.InputTag("selectedPatMuons"),
                                cut = cms.string('isGlobalMuon = 1 & pt > 10 & abs(eta)<2.5'),
                                filter = cms.bool(True)
                            )

#dimuonsGlobal = cms.EDFilter("CandViewShallowCloneCombiner",
#                              checkCharge = cms.bool(True),
#                              cut = cms.string(' mass > 70 & mass < 120 & charge=0'),
#                              decay = cms.string("goodGlobalMuons@+ goodGlobalMuons@-")
#                             #decay = cms.string('selectedPatMuonsTriggerMatch@+ selectedPatMuonsTriggerMatch@-')
#                          )

dimuonsGlobalFilter = cms.EDFilter("CandViewCountFilter",
                                    src = cms.InputTag("dimuonsGlobal"),
                                    minNumber = cms.uint32(1)
                                )






