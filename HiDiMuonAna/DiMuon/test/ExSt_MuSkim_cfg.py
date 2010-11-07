##Takes input put from heavy ion reconstructed files and do layer 0 skimming
## make PAT muons and store them (using pp pat sequence, No MC matching)
##Select muons with kinematical cuts which can be specified right here
import FWCore.ParameterSet.Config as cms
process = cms.Process("MuSkim")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
#process.load('Configuration.EventContent.EventContent_cff')


#process.GlobalTag.globaltag = 'START39_V1::All'
process.GlobalTag.globaltag = 'GR_R_39X_V1::All'


process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            fileNames = cms.untracked.vstring(



 'rfio:/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v1/000/150/063/78197C78-B4E8-DF11-ACE6-001D09F24259.root',
    #'rfio:/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v1/000/150/026/5265C692-66E8-DF11-AAE0-000423D9A212.root',
    #'rfio:/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v1/000/150/021/A0550AA0-45E8-DF11-9FED-0030487CD704.root'
      



##HI data express stream
#    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/064/E6333CC5-B5E8-DF11-8AEE-003048F118DE.root',
#    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/064/CC36B6C6-B5E8-DF11-AF20-0030486780A8.root',
#    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/064/82DDEDEF-A7E8-DF11-9D3C-001D09F25109.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/064/74672D92-9FE8-DF11-8E98-001D09F23A84.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/064/5CE7ED77-B4E8-DF11-843B-001D09F25109.root',
#    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/064/524BC403-B2E8-DF11-B7B7-001D09F24259.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/064/2CB29576-B4E8-DF11-848F-001D09F2B2CF.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/064/0C3BF9C6-B5E8-DF11-99F8-001D09F290CE.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/064/04EBA177-B4E8-DF11-8AE3-001D09F24E39.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/063/E4111D45-88E8-DF11-AB9B-000423D9A212.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/063/C62277AE-90E8-DF11-8BD6-0030487C7392.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/063/C46F1554-9DE8-DF11-9540-0030487CD162.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/063/98F239FC-88E8-DF11-B2CC-0030487C90EE.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/063/96F46CDD-8DE8-DF11-A359-0030487D05B0.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/063/34BAED01-9EE8-DF11-9E81-0030487A195C.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/063/32E15B7E-84E8-DF11-B9BB-001D09F2983F.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/063/3061AF01-9EE8-DF11-BFD5-0030487C60AE.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/063/004D2101-9EE8-DF11-A4E5-0030487A1FEC.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/062/FE2AACAF-A1E8-DF11-8B85-003048F1C836.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/062/B893B8B2-A1E8-DF11-90CD-003048F024E0.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/062/2E0921B9-A1E8-DF11-B9A1-003048F117B6.root',
 #   '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/062/0085E1AF-A1E8-DF11-AF37-003048F117B4.root'
                                                                                                                                                                        
   
#    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/F0875E01-99E9-DF11-B59B-001D09F2424A.root',
#    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/E65FA901-99E9-DF11-91C3-001D09F24D4E.root',

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
#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/user/d/dmoon/cms370/Hydjet_MinBias_2.76TeV_Z0_Emb_Reco")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.load("HiDiMuonAna.DiMuon.MuSkim_cff")            

#Uncomment for HI reconstruction while PAT reco
#process.patAODTrackCandsUnfiltered.src = cms.InputTag("hiSelectedTracks")
#process.patAODTrackIsoDepositCtfTk.ExtractorPSet.inputTrackCollection = cms.InputTag("hiSelectedTracks")

#solved the issue:
#process.patMuons.embedCaloMETMuonCorrs = cms.bool(False)
#process.patMuons.embedTcMETMuonCorrs   = cms.bool(False)

# ====== Layer 0 filters (selecting events with muons )
process.MuonSelector = cms.EDFilter("MuonSelector",
                                    src = cms.InputTag("muons"),
                                    cut = cms.string("(isStandAloneMuon || isGlobalMuon || isTrackerMuon) && pt > 1.0"),
                                    filter = cms.bool(True)
                                    )




#process.MuonSelector = cms.EDFilter("MuonSelector",
#                                    src = cms.InputTag("muons"),
 #                                   cut = cms.string("(isStandAloneMuon || isGlobalMuon || isCaloMuon) && pt > 1.0"),
 #                                   filter = cms.bool(True)
 #                                   ) 


process.MuonFilter = cms.EDFilter("MuonCountFilter",
                                  src = cms.InputTag("MuonSelector"),
                                  minNumber = cms.uint32(1)
                                  )

process.PatMuon_Step=cms.Path(process.goodMuonRecoForDimuon)
process.MuonSkim_Step = cms.Path(process.MuonSelector*process.MuonFilter)


process.STAMuonSkim_Step=cms.Path(process.goodSTAMuons*process.goodSTAMuonFilter)
process.GlobalMuonSkim_Step=cms.Path(process.goodGlobalMuons*process.goodGlobalMuonFilter)

process.load("HiDiMuonAna.DiMuon.MuSkimEventContent_cff")

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",

outputCommands = process.AODEventContent.outputCommands,
                                  #process.FEVTDEBUGHLToutput,
                                  #process.hiAnalysisSkimContent,
                                  #process.MuSkimContent,
                                  dataset = cms.untracked.PSet(
    dataTier = cms.untracked.string('AOD'),
    filterName = cms.untracked.string('')),
                                  fileName = cms.untracked.string('file:HI_ExSt_MuSkim_V2.root'),
                                  #fileName = cms.untracked.string('rfio:/castor/cern.ch/user/k/kumarv/cms391/HiData/ExSt/HI_ExSt_FEVTDEBUGHLToutput_MuSkim_V3.root'),
                                  SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('MuonSkim_Step')
                                                                    )
                                  )

process.outpath = cms.EndPath(process.FEVTDEBUGHLToutput)
process.schedule=cms.Schedule(process.MuonSkim_Step,process.STAMuonSkim_Step,process.GlobalMuonSkim_Step,process.outpath)
