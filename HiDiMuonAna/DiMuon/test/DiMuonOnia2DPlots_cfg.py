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
process.GlobalTag.globaltag = cms.string('GR10_P_V12::All')

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")


from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)


process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string(""), 
    centralitySrc = cms.InputTag("hiCentrality")
    )






process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
    )

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.source = cms.Source("PoolSource",
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            fileNames = cms.untracked.vstring(


#'rfio:/castor/cern.ch/cms/store/caf/user/tdahms/HeavyIons/Onia/Data2010/v4/Skims/Prompt/150256-150619/onia2MuMuPAT_46_1_jWF.root'


    )
                            )



##This should be uncommented to include all files from any castor directory automatically
import os,commands
def getCastorDirectoryList(path):
    cmd  = 'nsls %s/ ' % (path)
    file = ["rfio:%s/%s" % (path,i) for i in commands.getoutput(cmd).split('\n')]
    return file
process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/cms/store/caf/user/tdahms/HeavyIons/Onia/Data2010/v4/Skims/Prompt/150256-150619/")



process.dimuonsOnia2DPlots = cms.EDAnalyzer(
    "DiMuonOnia2DPlots",
    OutputFileName = cms.untracked.string('file:DimuonOnia2Dplots.root'),
    #HLTFilterName=cms.untracked.InputTag('hltHIL2DoubleMu3L2Filtered'),    
    HLTFilterName=cms.untracked.string('hltHIDoubleMuLevel1PathL1OpenFiltered'),
    IsGenInfo=cms.untracked.string("FALSE"),
    IsPATInfo=cms.untracked.string("TRUE"),
    IsCuts = cms.untracked.bool(True)

    )




process.eventInfo = cms.OutputModule (
    "AsciiOutputModule"
       )
 

process.dimuonsOnia2DPlotsPath = cms.Path(process.dimuonsOnia2DPlots)


process.schedule=cms.Schedule(process.dimuonsOnia2DPlotsPath)


