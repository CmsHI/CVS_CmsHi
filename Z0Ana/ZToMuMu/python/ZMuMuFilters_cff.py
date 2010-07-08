import FWCore.ParameterSet.Config as cms
######################################################
# A set of filters for  Z To Mu Mu skimming:
#


from Z0Ana.ZToMuMu.patCandidatesForZMuMuSkim_cff import *

GenMuons = cms.EDFilter("CandViewRefSelector",
                        #src = cms.InputTag("genParticles"),
                        src = cms.InputTag("hiGenParticles"),
                        cut = cms.string('abs(pdgId) = 13  & abs(eta)<2.5)'),
			# cut = cms.string('abs(pdgId) = 13 & (pt > 10 & abs(eta)<2.5)'),
                        filter = cms.bool(True)
                        )

GenDimuons = cms.EDProducer("CandViewShallowCloneCombiner",
                          checkCharge = cms.bool(True),
			 cut = cms.string(' mass > 0 & mass < 1000 & charge=0'),
                       #   cut = cms.string(' mass > 70 & mass < 120 & charge=0'),
                          #decay = cms.string("muons@+ muons@-")
                          decay = cms.string('GenMuons@+ GenMuons@-')
                          )

GenDimuonsFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("GenDimuons"),
                                      minNumber = cms.uint32(1)
                                      )


# muons
Dimuons = cms.EDProducer("CandViewShallowCloneCombiner",
                       checkCharge = cms.bool(True),
                         #cut = cms.string(' mass > 70 & mass < 120 & charge=0'),
                         cut = cms.string(' mass > 0 & mass < 10000 & charge=0'),
                         #goodMuons
                                        
                         #decay = cms.string("goodMuons@+ goodMuons@-")
                         decay = cms.string("muons@+ muons@-")
                         #decay = cms.string('patMuons@+ patMuons@-')
                         )

DimuonsMassCut = cms.EDProducer("CandViewShallowCloneCombiner",
                       checkCharge = cms.bool(True),
                         #cut = cms.string(' mass > 70 & mass < 120 & charge=0'),
                         cut = cms.string(' mass > 88 & mass < 92 & charge=0'),
                         #goodMuons
                                        
                         #decay = cms.string("goodMuons@+ goodMuons@-")
                         decay = cms.string("muons@+ muons@-")
                         #decay = cms.string('patMuons@+ patMuons@-')
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
                                src = cms.InputTag("Dimuons"),
                                #cut = cms.string('(daughter(0).pt>10 & daughter(1).pt>10)&((daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1 &  daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1 &  daughter(0).isGlobalMuon = 1 ))' ),
                                cut = cms.string('((daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1 &  daughter(1).isGlobalMuon = 1)  || (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1 &  daughter(0).isGlobalMuon = 1 ))' ),
                                filter = cms.bool(True)
                                                          

                            )


dimuonsGlobalSTAFilter = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("dimuonsGlobalSTA"),
                                      minNumber = cms.uint32(1)
                                      )


dimuonsGlobal = cms.EDFilter("CandViewRefSelector",
                             src = cms.InputTag("Dimuons"),
                             #cut = cms.string('(daughter(0).pt>10 & daughter(1).pt>10) & (daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 )' ),
                             cut = cms.string('(daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 )' ),
                             filter = cms.bool(True)
                             )

dimuonsGlobalHighQuality = cms.EDFilter("CandViewRefSelector",
                             src = cms.InputTag("DimuonsMassCut"),
                             cut = cms.string('(daughter(0).pt>40 & daughter(1).pt>40) & (daughter(0).isGlobalMuon = 1 &  daughter(1).isGlobalMuon = 1 )' ),
                             filter = cms.bool(True)
                             )



dimuonsSTA = cms.EDFilter("CandViewRefSelector",
                          src = cms.InputTag("Dimuons"),
                          #cut = cms.string('(daughter(0).pt>10 & daughter(1).pt>10) & (daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1) ' ),
                          
                          cut = cms.string('(daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 1) ' ),
                          filter = cms.bool(True)
                          )


dimuonsTrk = cms.EDFilter("CandViewRefSelector",
                          src = cms.InputTag("Dimuons"),
                          cut = cms.string('(daughter(0).isGlobalMuon = 0 & daughter(0).isStandAloneMuon = 0 & daughter(0).isTrackerMuon = 1) & (daughter(1).isGlobalMuon = 0 & daughter(1).isStandAloneMuon = 0 & daughter(0).isTrackerMuon = 1) ' ),
                          filter = cms.bool(True)
                          )



#goodSTAMuons = cms.EDFilter("MuonViewRefSelector",
goodSTAMuons = cms.EDFilter("CandViewRefSelector",
    src = cms.InputTag("muons"),
  cut = cms.string('isStandAloneMuon = 1  & abs(eta)<2.5'), 
#  cut = cms.string('isStandAloneMuon = 1 & pt > 10 & abs(eta)<2.5'),
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
				 cut = cms.string('isGlobalMuon = 1 & abs(eta)<2.5'),                         
#       cut = cms.string('isGlobalMuon = 1 & pt > 10 & abs(eta)<2.5'),
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








