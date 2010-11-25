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
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START39_V4::All' #for MC# Make sure you have the right global tag (*)
#process.GlobalTag.globaltag = 'GR10_P_V12::All'

from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#from QuickPlots.DimuonAnalyzer.HIExpressHIrun2010_v1_cfi import *
process.source = cms.Source("PoolSource",
    noEventSort = cms.untracked.bool(True),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
   #                         fileNames = readFiles,
    fileNames = cms.untracked.vstring(
"file:/tmp/jrobles/hiRecoDM_RECO.root")
#'rfio:///castor/cern.ch/user/d/dmoon/cms390pre5/Hydjet_MinBias_2.76TeV_Z0_Flat_Emb_HLT_Reco/Hydjet_MinBias_2.76TeV_Z0_Flat_Emb_HLT_Reco_1.root' )
                           )


process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("Hydjet_2760GeV"),
    centralitySrc = cms.InputTag("hiCentrality")
    )


process.demo = cms.EDAnalyzer('DimuonAnalyzer',
                              genParticle  = cms.InputTag("genParticles"),
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
                              ptMinMuon    = cms.double(1.),
                              etaMaxTrack  = cms.double(2.5),
                              etaMinTrack  = cms.double(-2.5),
                              ptMinTrack   = cms.double(1.),
                              doRecoSingleMuon = cms.bool(True),  #To check reconstructed muons = True
                              doReco       = cms.bool(True),  #To check various reconstructed objects = True
                              doMC         = cms.bool(True), #To read various generation level informations = True
                              doSim        = cms.bool(True), #To do SimTrack checking = True
                              doSignal     = cms.bool(False), #To see signal from generation = True
                              doZ0check    = cms.bool(False), #To see mother of gen muons and daugher of gen Z0 = True
                              genSignal    = cms.untracked.InputTag("hiSignal"),
                              vertices     = cms.untracked.InputTag("hiSelectedVertex"),
                              simtracks    = cms.untracked.InputTag("mergedtruth","MergedTrackTruth")
                              )
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")

process.TFileService = cms.Service("TFileService", 
                                   fileName =
                                   cms.string("HydjetMBZ0Emb.root")
                                   )

process.p = cms.Path(process.demo)
