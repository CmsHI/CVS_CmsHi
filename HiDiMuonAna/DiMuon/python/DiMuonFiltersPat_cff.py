import FWCore.ParameterSet.Config as cms
######################################################
# A set of filters for  Z To Mu Mu skimming:
#
#from HeavyIonsAnalysis.DiMuon.patCandidatesForDiMuonSkim_cff import *

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
patdimuons = cms.EDProducer("CandViewShallowCloneCombiner",
                         checkCharge = cms.bool(True),
                         cut = cms.string(' mass > 0 & mass < 10000 & charge=0'),
                         #decay = cms.string("muons@+ muons@-")
                         decay = cms.string("patMuonsWithTrigger@+ patMuonsWithTrigger@-")

                         )

patdimuonsMassCut = cms.EDProducer("CandViewShallowCloneCombiner",
                                checkCharge = cms.bool(True),
                                cut = cms.string(' (mass > 60 & mass < 120 & charge=0) & (daughter(0).isGlobalMuon = 1 & daughter(1).isGlobalMuon = 1)'),
                                decay = cms.string("patMuonsWithTrigger@+ patMuonsWithTrigger@-")
                                #decay = cms.string("muons@+ muons@-")
                                )


patdimuonsMassCutFilter = cms.EDFilter("CandViewCountFilter",
                                src = cms.InputTag("patdimuonsMassCut"),
                                minNumber = cms.uint32(1)
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



patdimuonsGlobalSTA = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("patdimuons"),
                                cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1 &  daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1 &  daughter(0).isGlobalMuon = 1 ))' ),
                                filter = cms.bool(True)
                                )


patdimuonsGlobalSTAFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("patdimuonsGlobalSTA"),
                                      minNumber = cms.uint32(1)
                                      )



dimuonsGlobalTrk = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("patdimuons"),
                                cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isTrackerMuon = 1 &  daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isTrackerMuon = 1 &  daughter(0).isGlobalMuon = 1 ))' ),
#cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isTrackerMuon = 1 & daughter(1).globalTrack()->normalizedChi2() < 10 & daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isTrackerMuon = 1 &  daughter(0).isGlobalMuon = 1 ))' ),





                                filter = cms.bool(True)
                                )


dimuonsGlobalTrkFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("dimuonsGlobalTrk"),
                                      minNumber = cms.uint32(1)
                                      )





patdimuonsGlobal = cms.EDFilter("CandViewRefSelector",
                             src = cms.InputTag("patdimuons"),
                             #cut = cms.string('(daughter(0).pt>10 & daughter(1).pt>10) & (daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 )' ),
                             cut = cms.string('(daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 )' ),
                             filter = cms.bool(True)
                             )

patdimuonsGlobalHighQuality = cms.EDFilter("CandViewRefSelector",
                             src = cms.InputTag("patdimuonsMassCut"),
                             cut = cms.string('(daughter(0).pt>40 & daughter(1).pt>40) & (daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 )' ),
                             filter = cms.bool(True)
                             )


patdimuonsGlobalFilter = cms.EDFilter("CandViewCountFilter",
                                   src = cms.InputTag("patdimuonsGlobal"),
                                   minNumber = cms.uint32(1)
                                   )



patdimuonsSTA = cms.EDFilter("CandViewRefSelector",
                          src = cms.InputTag("patdimuons"),
                          cut = cms.string('(daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1) ' ),
                          filter = cms.bool(True)
                          )
                                                                                                        

patdimuonsSTAFilter = cms.EDFilter("CandViewCountFilter",
                                src = cms.InputTag("patdimuonsSTA"),
                                minNumber = cms.uint32(1)
                                )



dimuonsTrk = cms.EDFilter("CandViewRefSelector",
                          src = cms.InputTag("patdimuons"),
                          cut = cms.string('(daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 0 & daughter(0).isTrackerMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 0 & daughter(1).isTrackerMuon = 1) ' ),
                          filter = cms.bool(True)
                          )



dimuonsTrkFilter = cms.EDFilter("CandViewCountFilter",
                                src = cms.InputTag("dimuonsTrk"),
                                minNumber = cms.uint32(1)
                                )





patdimuonsSameCharge = cms.EDProducer("CandViewShallowCloneCombiner",
                                                  checkCharge = cms.bool(False),
                                                  cut = cms.string(' (mass > 0)'),
                                                     decay = cms.string("patMuonsWithTrigger@+ patMuonsWithTrigger@-")
#  decay = cms.string("muons@+ muons@-")
                                                  )



patdimuonsSameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                       src = cms.InputTag("patdimuonsSameCharge"),
                                       minNumber = cms.uint32(1)
                                       )






patdimuonsGlobalSameCharge = cms.EDFilter("CandViewRefSelector",
                                       src = cms.InputTag("patdimuonsSameCharge"),
                                       cut = cms.string('(daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 ) & (charge != 0)' ),
                             filter = cms.bool(True)
                             )



patdimuonsGlobalSameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("patdimuonsGlobalSameCharge"),
                                      minNumber = cms.uint32(1)
                                      )





patdimuonsGlobalSTASameCharge = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("patdimuonsSameCharge"),
                                cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1 &  daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1 &  daughter(0).isGlobalMuon = 1 ))& (charge != 0)' ),
                                filter = cms.bool(True)
                                                               
                                )


patdimuonsGlobalSTASameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("patdimuonsGlobalSTASameCharge"),
                                      minNumber = cms.uint32(1)
                                      )

                                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                  
patdimuonsSTASameCharge = cms.EDFilter("CandViewRefSelector",
                          src = cms.InputTag("patdimuonsSameCharge"),
                                    cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1)) & (charge != 0) '),
                          filter = cms.bool(True)
                          )


patdimuonsSTASameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                          src = cms.InputTag("patdimuonsSTASameCharge"),
                                          minNumber = cms.uint32(1)
                                          )






dimuonsTrkSameCharge = cms.EDFilter("CandViewRefSelector",
                                    src = cms.InputTag("patdimuonsSameCharge"),
                                    cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 0 & daughter(0).isTrackerMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 0 & daughter(1).isTrackerMuon = 1)& (charge != 0))' ),
                                    filter = cms.bool(True)
                                    )
 
dimuonsTrkSameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                          src = cms.InputTag("patdimuonsTrkSameCharge"),
                                          minNumber = cms.uint32(1)
                                          )

                                                                                                                            


dimuonsGlobalTrkSameCharge = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("patdimuonsSameCharge"),
                                cut = cms.string('(((daughter(0).isGlobalMuon = 0 & daughter(0).isTrackerMuon = 1 &  daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isTrackerMuon = 1 &  daughter(0).isGlobalMuon = 1 ))&(charge != 0))        ' ),
                                filter = cms.bool(True)
                                )


dimuonsGlobalTrkSameChargeFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("patdimuonsGlobalTrkSameCharge"),
                                      minNumber = cms.uint32(1)
                                      )


########################################################################################
patgoodSTAMuons = cms.EDFilter("CandViewRefSelector",
                            src = cms.InputTag("patdimuons"),
                            cut = cms.string('isStandAloneMuon = 1  & abs(eta)<2.5'), 
                            filter = cms.bool(True)                                
                            )


#goodGlobalMuons = cms.EDFilter("MuonViewRefSelector",
patgoodGlobalMuons = cms.EDFilter("CandViewRefSelector",
                                src = cms.InputTag("patdimuons"),
                               cut = cms.string('isGlobalMuon = 1 & abs(eta)<2.5'),                         
                               filter = cms.bool(True)
                            )






