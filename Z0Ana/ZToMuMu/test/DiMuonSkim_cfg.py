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
process.GlobalTag.globaltag = 'MC_37Y_V4::All'


process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),


   fileNames = cms.untracked.vstring(

#'rfio:/castor/cern.ch/user/h/hckim/TestJEX/crab/v3/SingleZ0mumu/test_Weisfile_SingleZ0mumu_CRAB_yesTRK_passHLT_CS_dimuonZ0HI_v3_9_1_pX8.root'
#'rfio:/castor/cern.ch/user/h/hckim/TestJEX/crab/v3/SingleJPsimumu/test_Weisfile_SingleJPsimumu_CRAB_yesTRK_passHLT_CS_dimuonJPsiHI_v3_10_1_hPi.root'
#'rfio:/castor/cern.ch/user/h/hckim/TestJEX/crab/v3/SingleUpsimumu/test_Weisfile_SingleUpsimumu_CRAB_yesTRK_passHLT_CS_dimuonUpsilonHI_v3_10_1_z09.root'    

#'file:MuSkim.root'
#'rfio:/castor/cern.ch/user/h/hckim/JulyExercise10/JulyExercise10_HardEnriched_Vtxcor_ZS_dilepton_skim0/JulyExercise10_HardEnriched_Vtxcor_ZS_dilepton_skim0_9_1_8BO.root'
#'rfio:/castor/cern.ch/user/h/hckim/JulyExercise10/JulyExercise10_MinimumBiasHI_dilepton_skim0/JulyExercise10_MinimumBiasHI_dilepton_skim0_95_1_E2H.root'
    )
                            
)

##This should be uncommented to include all files from any castor directory automatically
import os,commands
def getCastorDirectoryList(path):
    cmd  = 'nsls %s/ ' % (path)
    file = ["rfio:%s/%s" % (path,i) for i in commands.getoutput(cmd).split('\n')]
    return file
#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/user/k/kumarv/cmssw390/Z0/MuSkim")
#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/user/k/kumarv/cmssw390/Z0/JPsiMuSkim")
process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/user/k/kumarv/cmssw390/Z0/UpsilonMuSkim")


process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# =============== Filter Path =====================
process.load("DiMuonAna.DiMuon.DiMuonFilters_cff")

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
process.load("Z0Ana.ZToMuMu.ZMuMuEventContent_cff")
process.output = cms.OutputModule("PoolOutputModule",
                                  process.DiMuonContent,
                                  dataset = cms.untracked.PSet(
    dataTier = cms.untracked.string('AOD'),
    filterName = cms.untracked.string('')),
                                  #fileName = cms.untracked.string('file:RV_UpsilonToMuMuSkim.root')
                                  #fileName = cms.untracked.string('rfio:/castor/cern.ch/user/k/kumarv/cmssw390/Z0/MuSkim/RV_WTrk_ZMuMuSkim.root')
                                  fileName = cms.untracked.string('rfio:/castor/cern.ch/user/k/kumarv/cmssw390/Z0/UpsilonMuSkim/RV_WTrk_UpsilonMuMuSkim.root')

                                  )

process.outpath = cms.EndPath(process.output)
# If generator level information is avilable uncomment this
#process.schedule=cms.Schedule(process.DiMuonsGen_Step,process.dimuons_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsSTA_Step,process.DiTrk_Step,process.DiMuonsTrk_Step,process.outpath)
# with trk-trk pairs for debugging
#process.schedule=cms.Schedule(process.dimuons_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsSTA_Step,process.DiTrk_Step,process.DiMuonsTrk_Step,process.outpath)


# standard sequence
process.schedule=cms.Schedule(process.Dimuons_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsGlobalTrk_Step,process.DiMuonsSTA_Step,process.DiMuonsTrk_Step,process.DiMuonsSameCharge_Step,process.DiMuonsGlobalSameCharge_Step,process.DiMuonsGlobalSTASameCharge_Step,process.DiMuonsGlobalTrkSameCharge_Step,process.DiMuonsSTASameCharge_Step,process.DiMuonsTrkSameCharge_Step,process.outpath)

