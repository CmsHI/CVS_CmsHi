import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('DimuonAnalyzer',
                              genParticle  = cms.InputTag("hiGenParticles"),#no mixing:genParticles
                              muonTracks   = cms.InputTag("globalMuons"),
                              trackTracks  = cms.untracked.InputTag("hiGlobalPrimTracks"), # pp reco: "generalTracks"),   
                              massMaxDimuon= cms.double(120),
                              massMinDimuon= cms.double(0),
                              pdgDimuon    = cms.double(23),
                              ptMinDimuon  = cms.double(0.),
                              etaMaxMuon   = cms.double(2.5),
                              etaMinMuon   = cms.double(-2.5),
                              ptMinMuon    = cms.double(3.5),
                              etaMaxTrack  = cms.double(2.5),
                              etaMinTrack  = cms.double(-2.5),
<<<<<<< dimuonanalyzer_cfi.py
                              ptMinTrack   = cms.double(1.),
                              doRecoSingleMuon = cms.bool(True),
                              doMC         = cms.bool(False),
                              doReco       = cms.bool(True),
                              doSim        = cms.bool(False),
                              doSignal     = cms.bool(False),
                              genSignal    = cms.untracked.InputTag("hiSignal"),
                              vertices     = cms.untracked.InputTag("hiSelectedVertex"),
                              simtracks    = cms.untracked.InputTag("mergedtruth","MergedTrackTruth")
=======
                              ptMinTrack   = cms.double(1.),
                              doSingleMuon = cms.bool(True),
                              doMC         = cms.bool(False)
>>>>>>> 1.2
                      )
