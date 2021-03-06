##Gen level ploting are now  working 
##Vineet Kumar & Prashant Shukla
import FWCore.ParameterSet.Config as cms
process = cms.Process("DiMuonOnia2DPlots")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1


process.load("Configuration.StandardSequences.Geometry_cff")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = cms.string('MC_44_V1::All')

process.GlobalTag.globaltag = cms.string('START44_V7::All')


process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")


from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFhits"),
    centralitySrc = cms.InputTag("hiCentrality"),
    nonDefaultGlauberModel = cms.string("Hydjet_Bass")
    )



process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),

                            fileNames = cms.untracked.vstring(


"rfio:/castor/cern.ch/user/t/tdahms/ForVineet_onia2MuMu_441.root"
#"rfio:/castor/cern.ch/cms/store/user/tdahms/pp2760/Onia/MC/v1/Skims/PromptJpsi/onia2MuMuPAT_MC_19.root"


#'rfio:/castor/cern.ch/cms/store/user/tdahms/HeavyIons/Onia/MC/v9/Skims/Upsilon2SPt05/onia2MuMuPAT_MC_83_1_SaH.root'

#'file:onia2MuMuPATSkim_Test.root'
#'rfio:/castor/cern.ch/user/p/pshukla/cms394/MC/DMJPsiOniaSkim/JPsi_OniaSkim_DM_2.root'
#'rfio:/castor/cern.ch/cms/store/caf/user/tdahms/HeavyIons/Onia/Data2010/v4/Skims/Prompt/150256-150619/onia2MuMuPAT_46_1_jWF.root'
#'rfio:/castor/cern.ch/cms/store/user/tdahms/HeavyIons/Onia/MC/v3/Skims/PromptJpsiPt03/onia2MuMuPAT_MC_1_1_WUq.root'
#'rfio:/castor/cern.ch/user/k/kumarv/cms3111/MC/JPsiOniaSkim/JPsiPt1530/JPsiPt1530_OniaMuMuSkim_20_1_0xS.root'



    )
                            )



##This should be uncommented to include all files from any castor directory automatically
#import os,commands
#def getCastorDirectoryList(path):
#    cmd  = 'nsls %s/ ' % (path)
#    file = ["rfio:%s/%s" % (path,i) for i in commands.getoutput(cmd).split('\n')]
#    return file
#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/cms/store/user/tdahms/HeavyIons/Onia/MC/v4/Skims/PromptJpsiPt03/")




####New 
#import os,commands
# get a list of files from a specified directory

#mydir ="/castor/cern.ch/cms/store/user/tdahms/HeavyIons/Onia/MC/v9/Skims/PromptJpsiPt1530"
#cmd  = 'nsls %s/ ' % (mydir)
#mylist = ["rfio:%s/%s" % (mydir,j) for j in commands.getoutput(cmd).split('\n')]
# add a specified number of files from mydir to the list of fileNames
#nfiles=1
#for i in range(0,nfiles):
#    process.source.fileNames.append('%s' % (mylist[i]))
#    print "process.source.fileNames.append(%s" % (mylist[i])
#    (len(process.source.fileNames))
  



process.dimuonsOnia2DPlots = cms.EDAnalyzer(
    "DiMuonOnia2DPlots",
    OutputFileName = cms.untracked.string('file:DimuonOnia2Dplots_JPsiPt_PP_test.root'),
    HLTFilterName=cms.untracked.string('HLT_L1DoubleMu0_v1'),
    MotherID=cms.untracked.string("JPsi"),

    IsGenInfo=cms.untracked.string("TRUE"),
    IsPATInfo=cms.untracked.string("TRUE"),
    IsCuts = cms.untracked.bool(True)
    )


process.eventInfo = cms.OutputModule (
    "AsciiOutputModule"
       )

process.dimuonsOnia2DPlotsPath = cms.Path(process.dimuonsOnia2DPlots)
process.schedule=cms.Schedule(process.dimuonsOnia2DPlotsPath)


