##Take input from MuSkim_cfg.py or from Z0Ana/JulyExercise10/pythons/muonSkimPatRecoTemplate_cfg.py
##use selected muons at layer 0 , to make exclusive Z0 categories
## can be modified to use patMuons insted of reco::muons
import FWCore.ParameterSet.Config as cms
process = cms.Process("ZMuMuSkim")
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

'rfio:/castor/cern.ch/user/h/hckim/JulyExercise10/JulyExercise10_HardEnriched_Vtxcor_ZS_dilepton_skim0/JulyExercise10_HardEnriched_Vtxcor_ZS_dilepton_skim0_9_1_8BO.root'
#'rfio:/castor/cern.ch/user/h/hckim/JulyExercise10/JulyExercise10_MinimumBiasHI_dilepton_skim0/JulyExercise10_MinimumBiasHI_dilepton_skim0_95_1_E2H.root'
    )
                            
)

##This should be uncommented to include all files from any castor directory automatically
#import os,commands
#def getCastorDirectoryList(path):
#    cmd  = 'nsls %s/ ' % (path)
#    file = ["rfio:%s/%s" % (path,i) for i in commands.getoutput(cmd).split('\n')]
#    return file
#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/user/d/dmoon/cms370/Hydjet_MinBias_2.76TeV_Z0_Emb_Reco")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# =============== Filter Path =====================
process.load("Z0Ana.ZToMuMu.ZMuMuFilters_cff")

#process.DiMuonsGen_Step=cms.Path(process.GenMuons*process.GenDimuons*process.GenDimuonsFilter)

process.Dimuons_Step =cms.Path(process.dimuons)
process.DiMuonsGlobal_Step =cms.Path(process.dimuonsGlobal*process.dimuonsGlobalFilter)
process.DiMuonsGlobalSTA_Step=cms.Path(process.dimuonsGlobalSTA*process.dimuonsGlobalSTAFilter)
process.DiMuonsSTA_Step=cms.Path(process.dimuonsSTA*process.dimuonsSTAFilter)

process.DiMuonsSameCharge_Step =cms.Path(process.dimuonsSameCharge*process.dimuonsSameChargeFilter)
process.DiMuonsGlobalSameCharge_Step =cms.Path(process.dimuonsGlobalSameCharge*process.dimuonsGlobalSameChargeFilter)
process.DiMuonsGlobalSTASameCharge_Step =cms.Path(process.dimuonsGlobalSTASameCharge*process.dimuonsGlobalSTASameChargeFilter)
process.DiMuonsSTASameCharge_Step =cms.Path(process.dimuonsSTASameCharge*process.dimuonsSTASameChargeFilter)



#process.DiMuonsTrk_Step=cms.Path(process.dimuonsTrk)
#process.DiTrk_Step=cms.Path(process.trackCands*process.ditracksSiliconTrk)

# =============== Output ================================
process.load("Z0Ana.ZToMuMu.ZMuMuEventContent_cff")
process.output = cms.OutputModule("PoolOutputModule",
                                  process.ZMuMuContent,
                                  dataset = cms.untracked.PSet(
    dataTier = cms.untracked.string('AOD'),
    filterName = cms.untracked.string('')),
                                  fileName = cms.untracked.string('file:ZToMuMuSkim_Vtxcor_ZS.root')
                                  #fileName = cms.untracked.string('rfio:/castor/cern.ch/user/k/kumarv/Z0/cms370/ZMuMuSkimData.root')

                                  )

process.outpath = cms.EndPath(process.output)
# If generator level information is avilable uncomment this
#process.schedule=cms.Schedule(process.DiMuonsGen_Step,process.dimuons_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsSTA_Step,process.DiTrk_Step,process.DiMuonsTrk_Step,process.outpath)
# with trk-trk pairs for debugging
#process.schedule=cms.Schedule(process.dimuons_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsSTA_Step,process.DiTrk_Step,process.DiMuonsTrk_Step,process.outpath)


# standard sequence
process.schedule=cms.Schedule(process.Dimuons_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsSTA_Step,process.DiMuonsSameCharge_Step,process.DiMuonsGlobalSameCharge_Step,process.DiMuonsGlobalSTASameCharge_Step,process.DiMuonsSTASameCharge_Step,process.outpath)

