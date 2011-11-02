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


##2010 HI run global tag
#process.GlobalTag.globaltag = cms.string('GR_R_41_V0::All')

process.GlobalTag.globaltag = cms.string('START44_V7::All')


process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")


##from CmsHi.Analysis2010.CommonFunctions_cff import *
##overrideCentrality(process)
##process.HeavyIonGlobalParameters = cms.PSet(
##    #reco data centralityVariable = cms.string("HFhits"),
##    centralityVariable = cms.string("HFtowers"),
##    centralitySrc = cms.InputTag("hiCentrality"),
##    #nonDefaultGlauberModel = cms.string("Hydjet_Bass")
##    nonDefaultGlauberModel = cms.string("")
    
##    )


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





'file:UPC_MuSkim.root'

#"rfio:/castor/cern.ch/user/k/kumarv/cms414/Exp/Data/UPC/Mu/Test/UPC_MuSkim.root",

#"rfio:/castor/cern.ch/user/k/kumarv/cms414/Exp/Data/UPC/Mu/AllPhyMukim_V5/UPC_MuSkim_984_3_O3Y.root",
#"rfio:/castor/cern.ch/user/k/kumarv/cms414/Exp/Data/UPC/Mu/AllPhyMukim_V5/UPC_MuSkim_883_1_92T.root"




#"rfio:/castor/cern.ch/user/k/kumarv/cms414/Exp/Data/UPC/Mu/AllPhyMukim_V3/UPC_MuSkim_182_1_V4j.root",
#"rfio:/castor/cern.ch/user/k/kumarv/cms414/Exp/Data/UPC/Mu/AllPhyMukim_V3/UPC_MuSkim_68_1_aYH.root"
#"rfio:/castor/cern.ch/user/k/kumarv/cms414/Exp/Data/UPC/Mu/AllPhyMukim_V3/UPC_MuSkim_25_1_VOQ.root"
#"rfio:/castor/cern.ch/user/k/kumarv/cms414/Exp/Data/UPC/Mu/AllPhyMukim_V3/UPC_MuSkim_91_1_itH.root"
#'file:UPC_MuSkim.root'
#"rfio:/castor/cern.ch/user/k/kumarv/cms414/Exp/Data/UPC/Mu/AllPhyMukim/UPC_MuSkim_103_1_5nB.root"
#"rfio:/castor/cern.ch/user/k/kumarv/cms414/Exp/Data/UPC/Mu/AllPhyV3/UPC_MuSkim_188_1_4KM.root"
#"rfio:/castor/cern.ch/user/k/kumarv/cms414/Exp/Data/UPC/Mu/AllPhyV3/UPC_MuSkim_541_1_NGl.root"



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
  

################################################# HF Filter #######################################################################
#process.load("HeavyIonsAnalysis.Configuration.collisionEventSelection_cff")
##################################################################################################################################


process.dimuonUPCTree = cms.EDAnalyzer(
    "DiMuonUPCTree",
    OutputFileName = cms.untracked.string('file:UPCTree_Test.root'),
    HLTFilterName=cms.untracked.string('HLT_L1DoubleMu0_v1'),
    MotherID=cms.untracked.string("JPsi"),
    IsGenInfo=cms.untracked.string("TRUE"),
    IsPATInfo=cms.untracked.string("TRUE"),
    IsCuts = cms.untracked.bool(True)
    )


process.eventInfo = cms.OutputModule (
    "AsciiOutputModule"
       )




process.dimuonUPCTreePath = cms.Path(process.dimuonUPCTree)
process.schedule=cms.Schedule(process.dimuonUPCTreePath)


