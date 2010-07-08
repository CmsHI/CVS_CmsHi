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

#from Z0Ana.ZToMuMu.enriched_list_skimmed0_cfi import *
#from Z0Ana.ZToMuMu.MC_Zembedding_RECO_cfi import *
#from Z0Ana.ZToMuMu.RealData_cfi import *
from Z0Ana.ZToMuMu.RD_NZS_enriched_cfi import *
process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            # this is how to select events on their event number
                     #       eventsToProcess = cms.untracked.VEventRange('1:3291','1:6160','1:10264','1:17438','1:27609','1:30911','1:44604','1:48319','1:57709','1:59044','1:63920','1:78825','1:80858','1:82551','1:88892','1:89061','1:94201','1:95370','1:98242','1:101094','1:113175','1:113285','1:9698','1:10047','1:24431','1:26720','1:26999','1:28240','1:30149','1:31357','1:32389','1:35650','1:37750','1:42707','1:43796','1:46824','1:54058','1:64090','1:67407','1:67639','1:78999','1:79109','1:89809','1:92268','1:94137','1:105586','1:109814','1:23768','1:24151','1:24380','1:28568','1:31858','1:34027','1:34538','1:39219','1:40725','1:43232','1:51451','1:52885','1:58935','1:60966','1:63238','1:65264','1:65586','1:68853','1:68917','1:71647','1:83043','1:33882','1:37065','1:38053','1:38141','1:49468','1:62685','1:68758','1:80560','1:82397','1:82878','1:84581','1:86635','1:86746','1:87176','1:89757','1:89901','1:99553','1:103787','1:107598','1:6452','1:18605','1:29712','1:45013','1:51273','1:52750','1:55578','1:57310','1:58648','1:63832','1:65793','1:66603','1:68435','1:71249','1:73039','1:73562','1:75051','1:81731','1:98847','1:110005','1:113336','1:5996','1:6537','1:8562','1:8563','1:9600','1:11064','1:11706','1:15254','1:18138','1:24781','1:33821','1:38919','1:44772','1:50476','1:50761','1:57334','1:60748','1:63907','1:67332','1:69518','1:72999','1:73720','1:77138','1:80760','1:95878','1:107669','1:109256','1:780','1:12068','1:23818','1:32766','1:53261','1:59918','1:60082','1:63710','1:69071','1:69457','1:71398','1:77730','1:95266','1:95666','1:110675','1:2572','1:3066','1:4421','1:5817','1:5948','1:7895','1:14349','1:18965','1:21874','1:29402','1:37486','1:43008','1:51797','1:54814','1:54961','1:67981','1:72312','1:72721','1:92458','1:99445','1:108288','1:68571','1:97867','1:114276'),
                           fileNames = readFiles
 #fileNames = cms.untracked.vstring(
# 'file:/afs/cern.ch/user/s/silvest/public/html/JulyExercise/ZMuMuSkim_fireworks_filtering.root'
 #'/store/user/kimy/MinimumBiasHI/Spring10-JulyAnalysisExercise_MC_37Y_V4-HardEnriched-v3-RECO-prelim-v1/599a3a4efd1a163b86e329cbf44e9f6a/hiRecoJEX_RAW2DIGI_RECO_99_1_UFG.root'
  #  )# fileNames = cms.untracked.vstring(

    #'rfio:/castor/cern.ch/user/d/dmoon/cms370/Hydjet_MinBias_2.76TeV_Z0_Emb_Reco/Hydjet_MinBias_2.76TeV_Z0Emb_Reco_e10_05_908.root'
    ##pp Cath File
    #'rfio:/castor/cern.ch/user/s/silvest/rootfiles/SignalOnly/Z0/root/RECO/Z0_SignalOnly_PPofflineReco_job1_RECO.root'
    #'rfio:/castor/cern.ch/user/k/kumarv/Z0/cms370/MuSkim.root'
    #'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_pp_Reco_1_10.root',
    #'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_pp_Reco_11_20.root'
 #  'file:dilepton_skim0.root'
  #  ),
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

process.DiMuonsSTA_Step=cms.Path(process.DimuonsMassCut*process.dimuonsSTA*process.dimuonsSTAFilter)
process.DiMuonsGlobalHighQuality_Step = cms.Path(process.DimuonsMassCut*process.dimuonsGlobalHighQuality*process.dimuonsGlobalFilter)

# =============== Output ================================

#process.load("Z0Ana.ZToMuMu.ZMuMuEventContent_cff")
process.load("HeavyIonsAnalysis.Configuration.analysisEventContent_cff")
process.output = cms.OutputModule("PoolOutputModule",
                                  process.FEVTDEBUGEventContent,
                                  #process.muonSkimContent,
                                    fileName = cms.untracked.string('/net/hibat0007/d00/scratch/silvestr/JulyExercise/Z_filtering_hightQuarlity_diGLB.root'),
                               #      fileName = cms.untracked.string('/castor/cern.ch/user/s/silvest/JulyExercise/rootfiles/MC_370_ZembeddedHydjet_filtering_RECO_on_STApairs_60-120.root'),
 SelectEvents=cms.untracked.PSet(
                                   #SelectEvents=cms.vstring('DiMuonsSTA_Step')
                                   SelectEvents=cms.vstring('DiMuonsGlobalHighQuality_Step') 	
                                   ))
                                  
process.outpath = cms.EndPath(process.output)
# If generator level information is avilable uncomment this
#process.schedule=cms.Schedule(process.DiMuonsSTA_Step,process.outpath)
process.schedule=cms.Schedule(process.DiMuonsGlobalHighQuality_Step,process.outpath)
