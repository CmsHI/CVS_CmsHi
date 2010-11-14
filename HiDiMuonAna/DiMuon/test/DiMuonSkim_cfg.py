##Take input from MuSkim_cfg.py or from Z0Ana/JulyExercise10/pythons/muonSkimPatRecoTemplate_cfg.py
##use selected muons at layer 0 , to make exclusive Z0 categories
## can be modified to use patMuons insted of reco::muons
import FWCore.ParameterSet.Config as cms
process = cms.Process("DiMuonSkim")
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.GlobalTag.globaltag = 'GR_R_39X_V1::All'

process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),

  fileNames = cms.untracked.vstring(

    #'rfio:/castor/cern.ch/cms/store/caf/user/hckim/SkimmedHIData/150304/'
    
    #'rfio:/castor/cern.ch/cms/store/caf/user/hckim/SkimmedHIData/150308/run150308_noTRK_CS_MuHI_v5_keepall_1_1_qBv.root',

    ##New runs after 150308
    #'rfio:/castor/cern.ch/cms/store/caf/user/hckim/SkimmedHIData/150308/DimuonSkim0_run150308_v1_noHLT_1_1_OAK.root'
    #'rfio:/castor/cern.ch/cms/store/caf/user/hckim/SkimmedHIData/150386/DimuonSkim0_run150386_v1_noHLT_1_1_U02.root'
    #'rfio:/castor/cern.ch/cms/store/caf/user/hckim/SkimmedHIData/150405/DimuonSkim0_run150405_v1_noHLT_1_1_9Xu.root'
    #'rfio:/castor/cern.ch/cms/store/caf/user/hckim/SkimmedHIData/150414/DimuonSkim0_run150414_v1_noHLT_1_1_MUr.root'
    
    #'rfio:/castor/cern.ch/cms/store/caf/user/hckim/SkimmedHIData/150431_r2/DimuonSkim0_run150431_v2_noHLT_5_1_bxj.root'
    #'rfio:/castor/cern.ch/user/e/edwenger/merge_EventDisplay_run_150431_RECO.root'

    #'rfio:/castor/cern.ch/user/e/edwenger/skims/mergeZMMall.root'

    'file:HI_ExSt_MuSkim_V3.root'

  )
                            
)

##This should be uncommented to include all files from any castor directory automatically
#import os,commands
#def getCastorDirectoryList(path):
#    cmd  = 'nsls %s/ ' % (path)
#    file = ["rfio:%s/%s" % (path,i) for i in commands.getoutput(cmd).split('\n')]
#    return file
#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/user/k/kumarv/cmssw390/Z0/Z0MuSkim")
#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/user/k/kumarv/cmssw390/Z0/JPsiMuSkim")
#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/user/k/kumarv/cmssw390/Z0/UpsilonMuSkim")


process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# =============== Filter Path =====================
process.load("HiDiMuonAna.DiMuon.DiMuonFilters_cff")

#process.DiMuonsGen_Step=cms.Path(process.GenMuons*process.GenDimuons*process.GenDimuonsFilter)

process.Dimuons_Step =cms.Path(process.dimuons)
process.DiMuonsGlobal_Step =cms.Path(process.dimuonsGlobal*process.dimuonsGlobalFilter)
process.DiMuonsGlobalSTA_Step=cms.Path(process.dimuonsGlobalSTA*process.dimuonsGlobalSTAFilter)
process.DiMuonsGlobalTrk_Step=cms.Path(process.dimuonsGlobalTrk*process.dimuonsGlobalTrkFilter)
process.DiMuonsSTA_Step=cms.Path(process.dimuonsSTA*process.dimuonsSTAFilter)
process.DiMuonsTrk_Step=cms.Path(process.dimuonsTrk*process.dimuonsTrkFilter)

########same charge paths
process.DiMuonsSameCharge_Step =cms.Path(process.dimuonsSameCharge*process.dimuonsSameChargeFilter)
process.DiMuonsGlobalSameCharge_Step =cms.Path(process.dimuonsGlobalSameCharge*process.dimuonsGlobalSameChargeFilter)
process.DiMuonsGlobalSTASameCharge_Step =cms.Path(process.dimuonsGlobalSTASameCharge*process.dimuonsGlobalSTASameChargeFilter)
process.DiMuonsGlobalTrkSameCharge_Step =cms.Path(process.dimuonsGlobalTrkSameCharge*process.dimuonsGlobalTrkSameChargeFilter)
process.DiMuonsSTASameCharge_Step =cms.Path(process.dimuonsSTASameCharge*process.dimuonsSTASameChargeFilter)
process.DiMuonsTrkSameCharge_Step =cms.Path(process.dimuonsTrkSameCharge*process.dimuonsTrkSameChargeFilter)

#process.DiMuonsTrk_Step=cms.Path(process.dimuonsTrk)
#process.DiTrk_Step=cms.Path(process.trackCands*process.ditracksSiliconTrk)

# =============== Output ================================
process.load("HiDiMuonAna.DiMuon.DiMuonEventContent_cff")

process.output = cms.OutputModule("PoolOutputModule",
                                  process.DiMuonContent,
                                  
                                  #outputCommands = process.AODEventContent.outputCommands,
                                  dataset = cms.untracked.PSet(
    dataTier = cms.untracked.string('AOD'),
    filterName = cms.untracked.string('')),
                                  #fileName = cms.untracked.string('file:RV_UpsilonToMuMuSkim.root')
                                  #fileName = cms.untracked.string('rfio:/castor/cern.ch/user/p/pshukla/HiData/ExSt/run150431_ed_DiMuSkim.root')
                                  fileName = cms.untracked.string('run150431_ed_DiMuSkim.root')
                                  
                                  )


process.outpath = cms.EndPath(process.output)

# If generator level information is avilable uncomment this
#process.schedule=cms.Schedule(process.DiMuonsGen_Step,process.dimuons_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsSTA_Step,process.DiTrk_Step,process.DiMuonsTrk_Step,process.outpath)
# with trk-trk pairs for debugging
#process.schedule=cms.Schedule(process.dimuons_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsSTA_Step,process.DiTrk_Step,process.DiMuonsTrk_Step,process.outpath)


# standard sequence
process.schedule=cms.Schedule(process.Dimuons_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsGlobalTrk_Step,process.DiMuonsSTA_Step,process.DiMuonsTrk_Step,process.DiMuonsSameCharge_Step,process.DiMuonsGlobalSameCharge_Step,process.DiMuonsGlobalSTASameCharge_Step,process.DiMuonsGlobalTrkSameCharge_Step,process.DiMuonsSTASameCharge_Step,process.DiMuonsTrkSameCharge_Step,process.outpath)

#process.schedule=cms.Schedule(process.Dimuons_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsSTA_Step,process.DiMuonsSameCharge_Step,process.DiMuonsGlobalSameCharge_Step,process.DiMuonsGlobalSTASameCharge_Step,process.DiMuonsSTASameCharge_Step,process.outpath)

