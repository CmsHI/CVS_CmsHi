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

process.GlobalTag.globaltag='GR10_P_V12::All'
#process.GlobalTag.globaltag = 'GR_R_39X_V1::All'
process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),


   fileNames = cms.untracked.vstring(

    "rfio:/castor/cern.ch/user/d/dmoon/cms390pre5/Hydjet_MinBias_2.76TeV_Z0_Flat_Emb_HLT_SMX_Reco/Hydjet_MinBias_2.76TeV_Z0_Flat_Reco_SMX_4.root"



    #'rfio:/castor/cern.ch/cms/store/caf/user/silvest/HFCoinc_PrimaryVTX_DoubleMu_1GLB_CorePhysics_RECO-allv3/DiMuon_115_1_Wui.root'



    )
                            
)

##This should be uncommented to include all files from any castor directory automatically
#import os,commands
#def getCastorDirectoryList(path):
#    cmd  = 'nsls %s/ ' % (path)
#    file = ["rfio:%s/%s" % (path,i) for i in commands.getoutput(cmd).split('\n')]
#    return file
#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/cms/store/caf/user/hckim/DiMuonSkimmedData/HICorePhysics/150886/HLT_noMB")


process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# =============== Filter Path =====================
process.load("HiDiMuonAna.DiMuon.DiMuonFilters_cff")

#process.DiMuonsGlobalMassCut_Step =cms.Path(process.dimuonsMassCut*process.dimuonsMassCutFilter)


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
           fileName = cms.untracked.string('file:ZMuMudata_DiMuSkim_tem.root')
           #fileName = cms.untracked.string('rfio:/castor/cern.ch/user/k/kumarv/cms391/HiData/CorePhy_1/run150886_HiCore_DiMuSkim_NC_1.root')
                                  
                                  )

process.outpath = cms.EndPath(process.output)


# standard sequence
process.schedule=cms.Schedule(process.Dimuons_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsGlobalTrk_Step,process.DiMuonsSTA_Step,process.DiMuonsTrk_Step,process.DiMuonsSameCharge_Step,process.DiMuonsGlobalSameCharge_Step,process.DiMuonsGlobalSTASameCharge_Step,process.DiMuonsGlobalTrkSameCharge_Step,process.DiMuonsSTASameCharge_Step,process.DiMuonsTrkSameCharge_Step,process.outpath)


