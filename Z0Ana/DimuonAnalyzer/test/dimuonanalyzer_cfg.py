import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

#process.MessageLogger = cms.Service("MessageLogger",
#                                    cout = cms.untracked.PSet(
#       default = cms.untracked.PSet(
#            limit = cms.untracked.int32(1) ## kill all messages in the log
#            )
#        ),
#                                    destinations = cms.untracked.vstring('cout')
#                                    )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            fileNames = cms.untracked.vstring(
                            "rfio:/castor/cern.ch/user/d/dmoon/cms370/Hydjet_MinBias_2.76TeV_Z0_Emb_Reco/Hydjet_MinBias_2.76TeV_Z0Emb_Reco_e10_01_1.root"
                            )
                           )

#process.load("RecoHI.HiCentralityAlgos.CentralityFilter_cfi")
#process.load("CondCore.DBCommon.CondDBCommon_cfi")
#process.CondDBCommon.connect = "sqlite_file:/afs/cern.ch/user/m/miheejo/scratch0/cms370v4/src/RecoHI/HiCentralityAlgos/data/CentralityTables.db"

#process.PoolDBESSource = cms.ESSource("PoolDBESSource",
#                                        process.CondDBCommon,
#                                        toGet = cms.VPSet(cms.PSet(record = cms.string('HeavyIonRcd'),
#                                                                    tag = cms.string('HFhits40_DataJulyExercise_AMPT2760GeV_MC_37Y_V5_NZS_v0')
#                                                                   )
#                                                          )
#                                       )

process.demo = cms.EDAnalyzer('DimuonAnalyzer',
                              genParticle  = cms.InputTag("hiGenParticles"),#no mixing:genParticles
                              muonTracks   = cms.untracked.InputTag("globalMuons"),
#                              trackTracks  = cms.untracked.InputTag("hiGlobalPrimTracks"), # pp reco: "generalTracks"),   
                              trackTracks  = cms.untracked.InputTag("hiSelectedTracks"), # pp reco: "generalTracks"),   
                              muons        = cms.untracked.InputTag("muons"),
                              massMaxDimuon= cms.double(200),
                              massMinDimuon= cms.double(0),
                              pdgDimuon    = cms.double(23),
                              ptMinDimuon  = cms.double(0.),
                              etaMaxMuon   = cms.double(2.5),
                              etaMinMuon   = cms.double(-2.5),
                              ptMinMuon    = cms.double(1.0), #Same as skim 0
                              etaMaxTrack  = cms.double(2.5),
                              etaMinTrack  = cms.double(-2.5),
                              ptMinTrack   = cms.double(1.),
                              doRecoSingleMuon = cms.bool(True),
                              doMC         = cms.bool(False),
                              doReco       = cms.bool(True),
                              doSim        = cms.bool(False),
                              doSignal     = cms.bool(False),
                              doZ0check    = cms.bool(False),
                              genSignal    = cms.untracked.InputTag("hiSignal"),
                              vertices     = cms.untracked.InputTag("hiSelectedVertex"),
                              simtracks    = cms.untracked.InputTag("mergedtruth","MergedTrackTruth")
                              )

process.TFileService = cms.Service("TFileService", 
                                   fileName =
                                   cms.string("HydjetMBZ0Emb.root")
                                   )

#process.p = cms.Path(process.demo*process.centralityFilter)
process.p = cms.Path(process.demo)
