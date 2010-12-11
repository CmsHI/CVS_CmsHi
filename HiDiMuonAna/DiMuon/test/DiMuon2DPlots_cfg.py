##Gen level ploting are now  working 
##Vineet Kumar & Prashant Shukla
import FWCore.ParameterSet.Config as cms
process = cms.Process("DiMuon2DPlots")
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



#'file:/tmp/camelia/ZoroSkim_v2.root'



'rfio:/castor/cern.ch/user/k/kumarv/cms391/MC/HydTest/HydPt50Test.root'

#'rfio:/castor/cern.ch/user/k/kumarv/cms391/MC/Z0HydPt50PatDiMuon/Z0HydPt50_PatDiMuonSkim_95.root',
#'rfio:/castor/cern.ch/user/k/kumarv/cms391/MC/Z0HydPt50PatDiMuon/Z0HydPt50_PatDiMuonSkim_93.root'

#'file:/tmp/kumarv/ReReco_ZoroSkimMC.root'
#'rfio:/castor/cern.ch/user/k/kumarv/cms391/MC/Z0DataMixPt50PatDiMuon/Z0DataMixPt50PatDiMuon_DiMuonSkim_8.root'
#'rfio:/castor/cern.ch/user/k/kumarv/cms391/MC/Z0HydPt50PatDiMuon/Z0HydPt50_PatDiMuonSkim_94.root'
#'rfio:/castor/cern.ch/user/k/kumarv/cms391/HiData/ReReco/V3/ReRecoV3_ZS_DiMuonSkim_8.root'
#'file:/tmp/kumarv/ReReco_ZoroSkimMC.root'
#'rfio:/castor/cern.ch/cms/store/caf/user/silvest/ZoroSkim_v2_150436-152643/ZoroSkim_50_1_p9x.root'
#Old paper skim
#'rfio:/castor/cern.ch/cms/store/caf/user/silvest/HICorePhysics_MinBias_GoodCollision_DoubleMu_2STA_ZmumuPaperSkim_v2/paperZskim_CorePhysics_GoodCollison_7_1_qfp.root'

##testing re reco
##'rfio:/castor/cern.ch/user/k/kumarv/cms391/HiData/ReReco/V3/ReRecoV3_DiMuonSkim_62.root'

    )
                            )



##This should be uncommented to include all files from any castor directory automatically
#import os,commands
#def getCastorDirectoryList(path):
#    cmd  = 'nsls %s/ ' % (path)
#    file = ["rfio:%s/%s" % (path,i) for i in commands.getoutput(cmd).split('\n')]
#    return file
#process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/user/k/kumarv/cms391/MC/Z0HydPt50PatDiMuon")




#process.TFileService = cms.Service(
 #   "TFileService",
    #fileName = cms.string("rfio:/castor/cern.ch/user/k/kumarv/JulyExercise/ZMuMu_Plot.root")
  #  fileName = cms.string('file:DiMuon1D_PlotsDM.root')
   # )





process.dimuons2DPlots = cms.EDAnalyzer(
    "DiMuon2DPlots",
    OutputFileName = cms.untracked.string('file:Dimuon2DplotsHydTest.root'),
    IsGenInfo=cms.untracked.string("TRUE"),
    IsPATInfo=cms.untracked.string("TRUE"),
    IsCuts = cms.untracked.bool(True)

    )




process.eventInfo = cms.OutputModule (
    "AsciiOutputModule"
       )
 

process.dimuons2DPlotsPath = cms.Path(process.dimuons2DPlots)


process.schedule=cms.Schedule(process.dimuons2DPlotsPath)


