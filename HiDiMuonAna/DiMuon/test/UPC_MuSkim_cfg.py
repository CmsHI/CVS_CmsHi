import FWCore.ParameterSet.Config as cms
process = cms.Process("MuSkim")
process.load('Configuration/StandardSequences/Services_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.GlobalTag.globaltag = cms.string('START44_V7::All')



process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            fileNames = cms.untracked.vstring(


    "rfio:/castor/cern.ch/user/m/mironov/cmssw440patch10/MC425/jpsi/v3/jpsimc_rawrecohltdebug_50_1_06m.root"

    #"rfio:/castor/cern.ch/user/m/mironov/cmssw440patch10/MC425/ups/v3/upsmc_rawrecohltdebug_100_1_0UA.root"
    #"rfio:/castor/cern.ch/cms//store/hidata/HIRun2010/HIAllPhysics/RECO/ZS-v2/0055/A48380C8-AD4F-E011-AB06-0025901D62A6.root",
    #"rfio:/castor/cern.ch/cms//store/hidata/HIRun2010/HIAllPhysics/RECO/ZS-v2/0055/2E5DB9C2-AD4F-E011-8509-0025901AF6A8.root",
    #"rfio:/castor/cern.ch/cms//store/hidata/HIRun2010/HIAllPhysics/RECO/ZS-v2/0055/00981FC3-AD4F-E011-B696-0025901AFF1C.root",
    #"rfio:/castor/cern.ch/cms//store/hidata/HIRun2010/HIAllPhysics/RECO/ZS-v2/0055/06EB09D0-AD4F-E011-874A-0025901D5D92.root"

    #this file is avilable
    #'rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v1/000/150/063/78197C78-B4E8-DF11-ACE6-001D09F24259.root'
    #'rfio:/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v1/000/150/063/78197C78-B4E8-DF11-ACE6-001D09F24259.root',
    #'rfio:/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v1/000/150/026/5265C692-66E8-DF11-AAE0-000423D9A212.root',
    #'rfio:/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v1/000/150/021/A0550AA0-45E8-DF11-9FED-0030487CD704.root'
    #'/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/F0875E01-99E9-DF11-B59B-001D09F2424A.root',
    #'/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/E65FA901-99E9-DF11-91C3-001D09F24D4E.root',
    ##pp data
    #'/store/data/Run2010A/MinimumBias/RECO/v1/000/136/066/18F6DB82-5566-DF11-B289-0030487CAF0E.root'
    
    ),
                            
                            )

##This should be uncommented if you want to include files automatically from a castor directory 
#import os,commands
#def getCastorDirectoryList(path):
#    cmd  = 'nsls %s/ ' % (path)
#    file = ["rfio:%s/%s" % (path,i) for i in commands.getoutput(cmd).split('\n')]
#    return file
#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/cms//store/hidata/HIRun2010/HIAllPhysics/RECO/ZS-v2/0055")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# UPC trigger selection 
process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltUPC = process.hltHighLevel.clone()
#process.hltUPC.HLTPaths = ["HLT_HIL1SingleMu3"]
process.hltUPC.HLTPaths = ["HLT_HIL1DoubleMuOpen"]

#process.load("HiDiMuonAna.DiMuon.MuSkim_cff")            


#Uncomment for HI reconstruction while PAT reco
#process.patAODTrackCandsUnfiltered.src = cms.InputTag("hiSelectedTracks")
#process.patAODTrackIsoDepositCtfTk.ExtractorPSet.inputTrackCollection = cms.InputTag("hiSelectedTracks")

#process.patAODTrackCandsUnfiltered.src = cms.InputTag("hiGlobalPrimTracks")
#process.patAODTrackIsoDepositCtfTk.ExtractorPSet.inputTrackCollection = cms.InputTag("hiGlobalPrimTracks")
#process.patAODTrackIsoDepositCalByAssociatorTowers.src=cms.InputTag("hiGlobalPrimTracks")


#solved the issue:
#process.patMuons.embedCaloMETMuonCorrs = cms.bool(False)
#process.patMuons.embedTcMETMuonCorrs   = cms.bool(False)

process.load("HiDiMuonAna.DiMuon.patMuonsWithTrigger_cff")
from HiDiMuonAna.DiMuon.patMuonsWithTrigger_cff import addMCinfo, changeRecoMuonInput, useL1MatchingWindowForSinglets, changeTriggerProcessName, switchOffAmbiguityResolution
changeTriggerProcessName(process, "HLT1")



#process.muPAT = cms.Path(process.patMuonsWithTriggerSequence)
                                 
# ====== Layer 0 filters (selecting events with muons )

process.MuonSelector = cms.EDFilter("MuonSelector",
                                    src = cms.InputTag("muons"),
                                    cut = cms.string("(isStandAloneMuon || isGlobalMuon || isTrackerMuon) && pt > 0.0"),
                                    filter = cms.bool(True)
                                    )

process.MuonFilter = cms.EDFilter("MuonCountFilter",
                                  src = cms.InputTag("MuonSelector"),
                                  minNumber = cms.uint32(1)
                                  )
# produce missing l1extraParticles
process.load('Configuration.StandardSequences.L1Reco_cff')
process.L1Reco_step = cms.Path(process.l1extraParticles)




################################### Colllision event selection ####################################################
process.load("HiDiMuonAna.DiMuon.collisionEventSelectionUPC_cff")
#################################################################################################################
#process.UPCMuonSkim_Step = cms.Path(process.collisionEventSelection*process.hltUPC*process.MuonSelector*process.MuonFilter*process.goodMuonRecoForDimuon*process.zdcreco)
#process.goodMuonRecoForDimuon.remove(process.patAODTrackIsoDepositCalByAssociatorTowers)

#process.UPCMuonSkim_Step = cms.Path(process.MuonSelector*process.MuonFilter*process.l1extraParticles*process.goodMuonRecoForDimuon)


process.UPCMuonSkim_Step = cms.Path(process.MuonSelector*process.MuonFilter*process.l1extraParticles*process.patMuonsWithTriggerSequence)



process.load("HiDiMuonAna.DiMuon.UPCMuSkimEventContent_cff")
process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
                                              #process.hiAnalysisSkimContent,
                                              process.MuSkimContent,
                                              dataset = cms.untracked.PSet(
    dataTier = cms.untracked.string('AOD'),
    filterName = cms.untracked.string('')),
                                              fileName = cms.untracked.string(
    'file:UPC_MuSkim.root'
    #'rfio:/castor/cern.ch/user/k/kumarv/cms414/Exp/Data/UPC/Mu/Test/UPC_MuSkim.root' 
    
    ),
                                              SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('UPCMuonSkim_Step')
                                                                                )
                                              )



process.outpath = cms.EndPath(process.FEVTDEBUGHLToutput)
process.schedule=cms.Schedule(process.UPCMuonSkim_Step,process.outpath)
