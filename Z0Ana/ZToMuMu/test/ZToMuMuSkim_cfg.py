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
process.GlobalTag.globaltag = 'MC_37Y_V5::All'

process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            fileNames = cms.untracked.vstring(

    #'rfio:/castor/cern.ch/user/d/dmoon/cms370/Hydjet_MinBias_2.76TeV_Z0_Emb_Reco/Hydjet_MinBias_2.76TeV_Z0Emb_Reco_e10_05_908.root'
    ##pp Cath File
    #'rfio:/castor/cern.ch/user/s/silvest/rootfiles/SignalOnly/Z0/root/RECO/Z0_SignalOnly_PPofflineReco_job1_RECO.root'
    #'rfio:/castor/cern.ch/user/k/kumarv/Z0/cms370/MuSkim.root'
    #'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_pp_Reco_1_10.root',
    #'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_pp_Reco_11_20.root'
   'file:MuSkim.root'
    ),
)

##This should be uncommented to include all files from any castor directory automatically
#import os,commands
#def getCastorDirectoryList(path):
#    cmd  = 'nsls %s/ ' % (path)
#    file = ["rfio:%s/%s" % (path,i) for i in commands.getoutput(cmd).split('\n')]
#    return file

#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/user/d/dmoon/cms370/Hydjet_MinBias_2.76TeV_Z0_Emb_Reco")


process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# =============== Filter Path =====================
process.load("Z0Ana.ZToMuMu.ZMuMuFilters_cff")


process.DiMuonsGen_Step=cms.Path(process.GenMuons*process.GenDimuons*process.GenDimuonsFilter)
process.DiMuonsGlobal_Step =cms.Path(process.Dimuons*process.dimuonsGlobal*process.dimuonsGlobalFilter)
process.DiMuonsGlobalSTA_Step=cms.Path(process.Dimuons*process.dimuonsGlobalSTA*process.dimuonsGlobalSTAFilter)
process.DiMuonsSTA_Step=cms.Path(process.Dimuons*process.dimuonsSTA*process.dimuonsSTAFilter)

# =============== Output ================================
process.load("Z0Ana.ZToMuMu.ZMuMuEventContent_cff")
process.output = cms.OutputModule("PoolOutputModule",
                                  process.ZMuMuContent,
                                  dataset = cms.untracked.PSet(
    dataTier = cms.untracked.string('AOD'),
    filterName = cms.untracked.string('')),
                                  #fileName = cms.untracked.string('rfio:/castor/cern.ch/user/k/kumarv/Z0/cms370/Z0MuMuSkimAfterMuSkim.root')
                                  fileName = cms.untracked.string('file:ZMuMuSkim.root')
                                  
                                  )

process.outpath = cms.EndPath(process.output)
# If generator level information is avilable uncomment this
process.schedule=cms.Schedule(process.DiMuonsGen_Step,process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsSTA_Step,process.outpath)
#process.schedule=cms.Schedule(process.DiMuonsGlobal_Step,process.DiMuonsGlobalSTA_Step,process.DiMuonsSTA_Step,process.outpath)
