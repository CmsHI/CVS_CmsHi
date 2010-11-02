import FWCore.ParameterSet.Config as cms
######################################################
# A set of filters for  Z To Mu Mu skimming:
#
from DiMuonAna.DiMuon.patCandidatesForZMuMuSkim_cff import *

GenMuons = cms.EDFilter("CandViewRefSelector",
                        #src = cms.InputTag("genParticles"),
                        src = cms.InputTag("hiGenParticles"),
                        cut = cms.string('abs(pdgId) = 13  & abs(eta)<2.5)'),
                        filter = cms.bool(True)
                        )

GenDimuons = cms.EDProducer("CandViewShallowCloneCombiner",
                            checkCharge = cms.bool(True),
                            cut = cms.string(' mass > 0 & mass < 1000 & charge=0'),
                            decay = cms.string('GenMuons@+ GenMuons@-')
                            )

GenDimuonsFilter = cms.EDFilter("CandViewCountFilter",
                                src = cms.InputTag("GenDimuons"),
                                minNumber = cms.uint32(1)
                                )


# muons
dimuons = cms.EDProducer("CandViewShallowCloneCombiner",
                         checkCharge = cms.bool(True),
                         cut = cms.string(' mass > 0 & mass < 10000 & charge=0'),
                         decay = cms.string("muons@+ muons@-")
                         #decay = cms.string("patMuons@+ patMuons@-")

                         )

dimuonsMassCut = cms.EDProducer("CandViewShallowCloneCombiner",
                                checkCharge = cms.bool(True),
                                cut = cms.string(' mass > 88 & mass < 92 & charge=0'),
                                decay = cms.string("muons@+ muons@-")
                                )
#Ditracks
trackCands = cms.EDProducer("ConcreteChargedCandidateProducer",
                            src          = cms.InputTag("hiGlobalPrimTracks"),
                            particleType = cms.string('mu+')   # to fix mass hypothesis
                            )
ditracksSiliconTrk = cms.EDProducer("CandViewShallowCloneCombiner",
                                    checkCharge = cms.bool(True),
                                    cut = cms.string(' mass > 0 & mass < 10000 & charge=0'),
                                    decay = cms.string("trackCands@+ trackCands@-")
                                    )
#=================================





dimuonsGlobalSTA = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("dimuons"),
                                cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1 &  daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1 &  daughter(0).isGlobalMuon = 1 ))' ),
                                filter = cms.bool(True)
                                )


dimuonsGlobalSTAFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("dimuonsGlobalSTA"),
                                      minNumber = cms.uint32(1)
                                      )



dimuonsGlobalTrk = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("dimuons"),
                                cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isTrackerMuon = 1 &  daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isTrackerMuon = 1 &  daughter(0).isGlobalMuon = 1 ))' ),
                                filter = cms.bool(True)
                                )


dimuonsGlobalTrkFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("dimuonsGlobalTrk"),
                                      minNumber = cms.uint32(1)
                                      )





dimuonsGlobal = cms.EDFilter("CandViewRefSelector",
                             src = cms.InputTag("dimuons"),
                             #cut = cms.string('(daughter(0).pt>10 & daughter(1).pt>10) & (daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 )' ),
                             cut = cms.string('(daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 )' ),
                             filter = cms.bool(True)
                             )

dimuonsGlobalHighQuality = cms.EDFilter("CandViewRefSelector",
                             src = cms.InputTag("dimuonsMassCut"),
                             cut = cms.string('(daughter(0).pt>40 & daughter(1).pt>40) & (daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 )' ),
                             filter = cms.bool(True)
                             )


dimuonsGlobalFilter = cms.EDFilter("CandViewCountFilter",
                                   src = cms.InputTag("dimuonsGlobal"),
                                   minNumber = cms.uint32(1)
                                   )



dimuonsSTA = cms.EDFilter("CandViewRefSelector",
                          src = cms.InputTag("dimuons"),
                          cut = cms.string('(daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1) ' ),
                          filter = cms.bool(True)
                          )
                                                                                                        

dimuonsSTAFilter = cms.EDFilter("CandViewCountFilter",
                                src = cms.InputTag("dimuonsSTA"),
                                minNumber = cms.uint32(1)
                                )



dimuonsTrk = cms.EDFilter("CandViewRefSelector",
                          src = cms.InputTag("dimuons"),
                          cut = cms.string('(daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 0 & daughter(0).isTrackerMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 0 & daughter(1).isTrackerMuon = 1) ' ),
                          filter = cms.bool(True)
                          )



dimuonsTrkFilter = cms.EDFilter("CandViewCountFilter",
                                src = cms.InputTag("dimuonsTrk"),
                                minNumber = cms.uint32(1)
                                )





dimuonsSameCharge = cms.EDProducer("CandViewShallowCloneCombiner",
                                                  checkCharge = cms.bool(False),
                                                  cut = cms.string(' (mass > 0)'),
                                                  decay = cms.string("muons@+ muons@-")
                                                  )



dimuonsSameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                       src = cms.InputTag("dimuonsSameCharge"),
                                       minNumber = cms.uint32(1)
                                       )






dimuonsGlobalSameCharge = cms.EDFilter("CandViewRefSelector",
                                       src = cms.InputTag("dimuonsSameCharge"),
                                       cut = cms.string('(daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 ) & (charge != 0)' ),
                             filter = cms.bool(True)
                             )



dimuonsGlobalSameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("dimuonsGlobalSameCharge"),
                                      minNumber = cms.uint32(1)
                                      )





dimuonsGlobalSTASameCharge = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("dimuonsSameCharge"),
                                cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1 &  daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1 &  daughter(0).isGlobalMuon = 1 ))& (charge != 0)' ),
                                filter = cms.bool(True)
                                                               
                                )


dimuonsGlobalSTASameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("dimuonsGlobalSTASameCharge"),
                                      minNumber = cms.uint32(1)
                                      )

                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
dimuonsSTASameCharge = cms.EDFilter("CandViewRefSelector",
                          src = cms.InputTag("dimuonsSameCharge"),
                                    cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1)) & (charge != 0) '),
                          filter = cms.bool(True)
                          )


dimuonsSTASameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                          src = cms.InputTag("dimuonsSTASameCharge"),
                                          minNumber = cms.uint32(1)
                                          )






dimuonsTrkSameCharge = cms.EDFilter("CandViewRefSelector",
                                    src = cms.InputTag("dimuonsSameCharge"),
                                    cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 0 & daughter(0).isTrackerMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 0 & daughter(1).isTrackerMuon = 1)& (charge != 0))' ),
                                    filter = cms.bool(True)
                                    )
 
dimuonsTrkSameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                          src = cms.InputTag("dimuonsTrkSameCharge"),
                                          minNumber = cms.uint32(1)
                                          )

                                                                                                                            


dimuonsGlobalTrkSameCharge = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("dimuonsSameCharge"),
                                cut = cms.string('(((daughter(0).isGlobalMuon = 0 & daughter(0).isTrackerMuon = 1 &  daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isTrackerMuon = 1 &  daughter(0).isGlobalMuon = 1 ))&(charge != 0))        ' ),
                                filter = cms.bool(True)
                                )


dimuonsGlobalTrkSameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("dimuonsGlobalTrkSameCharge"),
                                      minNumber = cms.uint32(1)
                                      )


########################################################################################
goodSTAMuons = cms.EDFilter("CandViewRefSelector",
                            src = cms.InputTag("muons"),
                            cut = cms.string('isStandAloneMuon = 1  & abs(eta)<2.5'), 
                            filter = cms.bool(True)                                
                            )


#goodGlobalMuons = cms.EDFilter("MuonViewRefSelector",
goodGlobalMuons = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("muons"),
                               cut = cms.string('isGlobalMuon = 1 & abs(eta)<2.5'),                         
                               filter = cms.bool(True)
                            )






