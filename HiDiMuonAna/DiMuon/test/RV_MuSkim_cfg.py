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



#process.GlobalTag.globaltag = 'START39_V1::All'
process.GlobalTag.globaltag = 'GR_R_39X_V1::All'


process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            fileNames = cms.untracked.vstring(

'/store/express/HIRun2010/HIExpressPhysics/FEVT/Express-v1/000/150/064/E6333CC5-B5E8-DF11-8AEE-003048F118DE.root'
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

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))
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

process.output = cms.OutputModule("PoolOutputModule",
                                  #process.hiAnalysisSkimContent,
                                  process.MuSkimContent,
                                  dataset = cms.untracked.PSet(
    dataTier = cms.untracked.string('AOD'),
    filterName = cms.untracked.string('')),
                                  fileName = cms.untracked.string('file:HI_expressStream_MuSkim.root'),
                                  SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('MuonSkim_Step')
                                                                    )
                                  )

process.outpath = cms.EndPath(process.output)
process.schedule=cms.Schedule(process.MuonSkim_Step,process.STAMuonSkim_Step,process.GlobalMuonSkim_Step,process.outpath)
