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



    #'rfio:/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v1/000/150/063/78197C78-B4E8-DF11-ACE6-001D09F24259.root',
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
                                                                                                                                                                        
    
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/F0875E01-99E9-DF11-B59B-001D09F2424A.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/E65FA901-99E9-DF11-91C3-001D09F24D4E.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/E2FF8F01-99E9-DF11-BD3A-001D09F2512C.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/D856CB47-98E9-DF11-AAAA-001D09F2AF96.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/D23A6501-99E9-DF11-A53F-0019B9F730D2.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/C02BDA07-99E9-DF11-97E1-003048F1BF68.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/C000DE01-99E9-DF11-B987-001D09F25393.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/B8C23801-99E9-DF11-868E-001D09F2546F.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/B8C07106-99E9-DF11-82AE-001D09F29538.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/B2C66904-99E9-DF11-AC79-001617E30D0A.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/9C872723-99E9-DF11-8BDB-001D09F24664.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/80D5DB47-98E9-DF11-8614-001D09F2424A.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/6CEAE806-99E9-DF11-BCFE-0030487CD180.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/62CC7501-99E9-DF11-B98A-001D09F241B9.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/3CE8CF06-99E9-DF11-A950-001D09F2437B.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/32965D49-98E9-DF11-BE90-001D09F29533.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/2A477E01-99E9-DF11-BFB3-001D09F295FB.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/28A1D001-99E9-DF11-9685-001D09F2905B.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/284A1948-98E9-DF11-A632-001D09F29597.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/260/1AF0E349-98E9-DF11-A138-001D09F27003.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/F2A53CAA-97E9-DF11-9525-001D09F24763.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/ECEA3D2C-94E9-DF11-91E3-0019B9F72BAA.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/E6EF5206-97E9-DF11-B9EE-0019B9F709A4.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/E6D78202-97E9-DF11-8C9F-003048F1BF68.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/DEAB2F02-97E9-DF11-96EB-003048F024FE.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/DE61EF41-96E9-DF11-ACD6-001617E30D0A.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/DC4C417B-95E9-DF11-A6A6-001617C3B6CC.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/DC354C3B-96E9-DF11-94D5-001617E30CC8.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/DA298A42-96E9-DF11-B224-001617C3B706.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/CEF3927C-95E9-DF11-8191-0030486780E6.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/CE9EB8D4-94E9-DF11-9AD6-001617C3B6DE.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/CCA1827C-95E9-DF11-A939-003048D2C020.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/CC4F81D5-94E9-DF11-BE23-000423D9997E.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/2657867D-95E9-DF11-8CB8-001D09F24FBA.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/26332FD6-94E9-DF11-A2B2-003048D2C020.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/1E15E27A-95E9-DF11-A450-001617E30CE8.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/1CBECC00-97E9-DF11-8FFA-003048F118E0.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/1A05D53B-96E9-DF11-9B05-001617C3B70E.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/18661406-97E9-DF11-937B-001D09F24F1F.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/125F2E7D-95E9-DF11-AACC-001D09F24DDF.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/10F2B706-97E9-DF11-8CEA-001D09F24353.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/0CA6EE06-97E9-DF11-A4BB-0030487CD906.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/082E787D-95E9-DF11-A5B2-001D09F244DE.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/00BCF97A-95E9-DF11-A221-001617E30F4C.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/259/00704E7C-95E9-DF11-A954-003048678098.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/F6A00B38-91E9-DF11-88F3-003048F1BF66.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/F6997A39-91E9-DF11-B877-0030487C778E.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/F2AE3234-91E9-DF11-92CA-0030487CD6DA.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/E6AB3E32-91E9-DF11-B2D1-000423D9A212.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/E6A092F7-91E9-DF11-AFE1-0030487C912E.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/E03446FC-91E9-DF11-AC35-0030487CD180.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/B4835138-91E9-DF11-9553-003048F024DE.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/AC6A67FC-91E9-DF11-97A2-0030487CD700.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/98DFEE32-91E9-DF11-BD07-003048F01E88.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/82FF1138-91E9-DF11-AFF7-003048F024FE.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/80E62238-91E9-DF11-BD18-003048F11942.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/64AD62F7-91E9-DF11-A2C6-0030487CD7E0.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/5A0B6439-91E9-DF11-9BB1-0030487CD6D2.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/3ECD54F7-91E9-DF11-B51B-0030487C8CB8.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/34CC1538-91E9-DF11-ADB2-003048F117B6.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/2A318739-91E9-DF11-8A2E-0030487CD812.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/28DC5B34-91E9-DF11-8E68-0030487CD840.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/24116338-91E9-DF11-9160-003048F117EA.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/04B2FFF6-91E9-DF11-8BD4-0030487CD704.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/258/040F0333-91E9-DF11-A86E-003048F1C420.root',
    '/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v3/000/150/256/B26F4498-90E9-DF11-8BC9-00304879FC6C.root'
           



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

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
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
                                  #fileName = cms.untracked.string('file:HI_ExSt_MuSkim_V2.root'),
                                  fileName = cms.untracked.string('rfio:/castor/cern.ch/user/k/kumarv/cms391/HiData/ExSt/HI_ExSt_FEVTDEBUGHLToutput_MuSkim_V3.root'),
                                  SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('MuonSkim_Step')
                                                                    )
                                  )

process.outpath = cms.EndPath(process.FEVTDEBUGHLToutput)
process.schedule=cms.Schedule(process.MuonSkim_Step,process.STAMuonSkim_Step,process.GlobalMuonSkim_Step,process.outpath)
