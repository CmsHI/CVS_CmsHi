##Gen level ploting are now  working 
##Vineet Kumar & Prashant Shukla
import FWCore.ParameterSet.Config as cms
process = cms.Process("DiMuonPlots")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1


process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

<<<<<<< DiMuonPlots_cfg.py
#process.GlobalTag.globaltag = cms.string('GR_R_39X_V1::All')


process.GlobalTag.globaltag = cms.string('GR10_P_V12::All')

=======
process.GlobalTag.globaltag = 'GR10_P_V12::All'

>>>>>>> 1.9
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")


from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)


process.HeavyIonGlobalParameters = cms.PSet(
        centralityVariable = cms.string("HFhits"),
<<<<<<< DiMuonPlots_cfg.py
          #nonDefaultGlauberModel = cms.string(""),
=======
            nonDefaultGlauberModel = cms.string(""),
>>>>>>> 1.9
            centralitySrc = cms.InputTag("hiCentrality")
            )







###############Vertex Filter#####################################################################
process.primaryVertexFilter = cms.EDFilter("VertexSelector",
                                   src = cms.InputTag("hiSelectedVertex"),
                                   cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
                                   filter = cms.bool(True), # otherwise it won't filter the events, instead making an empty vertex collection
                                   )


##############################  HFMin Bais Filter  #############################################
#process.load("UserCode.edwenger.Skims.hfCoincFilter_cff")
#from HiDiMuonAna.DiMuon.hfCoinFilter_cff import *

process.load("HeavyIonsAnalysis.Configuration.hfCoincFilter_cff")

##############################################################################################

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.source = cms.Source("PoolSource",
<<<<<<< DiMuonPlots_cfg.py
                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
=======
                            #noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
>>>>>>> 1.9
                            fileNames = cms.untracked.vstring(

<<<<<<< DiMuonPlots_cfg.py

'rfio:/castor/cern.ch/cms/store/caf/user/silvest/HICorePhysics_PromptReco-v3_RECO_ZmumuPaperSkim/Zskim_CorePhysics_GoodCollison_86_1_sVL.root'

    #'rfio:/castor/cern.ch/user/k/kumarv/cms391/MC/PureZ0/PythiaZ0_DiMuSkim.root'
    #'rfio:/castor/cern.ch/user/k/kumarv/cms391/HiData/CathV3_2/PromtRecoV3_DiMuonSkim_85.root'
=======
#"file:../../Configuration/test/Zskim_CorePhysics_GoodCollison.root"
#'rfio:/castor/cern.ch/user/k/kumarv/cms391/MC/Z0Grid/Z0MC_DiMuonSkim_HLTDoubleMuOpen_9_1_tJV.root' 
>>>>>>> 1.9


    )
                            )



##This should be uncommented to include all files from any castor directory automatically
<<<<<<< DiMuonPlots_cfg.py
#import os,commands
##def getCastorDirectoryList(path):
#    cmd  = 'nsls %s/ ' % (path)
#    file = ["rfio:%s/%s" % (path,i) for i in commands.getoutput(cmd).split('\n')]
#    return file
#process.source.fileNames= getCastorDirectoryList("")
=======
import os,commands
def getCastorDirectoryList(path):
    cmd  = 'nsls %s/ ' % (path)
    file = ["rfio:%s/%s" % (path,i) for i in commands.getoutput(cmd).split('\n')]
    return file
process.source.fileNames= getCastorDirectoryList("/castor/cern.ch/cms/store/caf/user/silvest/HICorePhysics_PromptReco-v3_RECO_ZmumuPaperSkim")
>>>>>>> 1.9




process.TFileService = cms.Service(
    "TFileService",
    #fileName = cms.string("rfio:/castor/cern.ch/user/k/kumarv/JulyExercise/ZMuMu_Plot.root")

<<<<<<< DiMuonPlots_cfg.py
    fileName = cms.string("DiMuonPlots_PureZ0.root")
=======
    fileName = cms.string("/tmp/silvest/HICorePhysics_PromptReco-v3_RECO_ZmumuPaperSkim.root")
>>>>>>> 1.9
    )


DiMuPlots = cms.PSet(
    histograms = cms.VPSet(
    cms.PSet(
    min = cms.untracked.double(0.0),
    max = cms.untracked.double(200.0),
    nbins = cms.untracked.int32(4000),
    name = cms.untracked.string("DiMuonMass"),
    description = cms.untracked.string("DiMuon mass [GeV/c^{2}]"),
    plotquantity = cms.untracked.string("mass")
    ),
    
    
    cms.PSet(
    min = cms.untracked.double(-10.0),
    max = cms.untracked.double(10.0),
    nbins = cms.untracked.int32(200),
    name = cms.untracked.string("DiMuonEta"),
    description = cms.untracked.string("DiMuon #eta"),
    plotquantity = cms.untracked.string("eta")
    ),
    cms.PSet(
    min = cms.untracked.double(-6.0),
    max = cms.untracked.double(6.0),
    nbins = cms.untracked.int32(120),
    name = cms.untracked.string("DiMuonRapidity"),
    description = cms.untracked.string("DiMuon y"),
    plotquantity = cms.untracked.string("rapidity")
    ),
    cms.PSet(
    min = cms.untracked.double(0),
    max = cms.untracked.double(200),
    nbins = cms.untracked.int32(200),
    name = cms.untracked.string("DiMuonPt"),
    description = cms.untracked.string("DiMuon p_{t} [GeV/c]"),
    plotquantity = cms.untracked.string("pt")
    ),
    cms.PSet(
    min = cms.untracked.double(-4),
    max = cms.untracked.double(4),
    nbins = cms.untracked.int32(80),
    name = cms.untracked.string("DiMuonPhi"),
    description = cms.untracked.string("DiMuon #phi"),
    plotquantity = cms.untracked.string("phi")
    ),
    cms.PSet(
    min = cms.untracked.double(0.0),
    max = cms.untracked.double(200.0),
    nbins = cms.untracked.int32(200),
    name = cms.untracked.string("mu1Pt"),
    description = cms.untracked.string("Highest muon p_{t} [GeV/c]"),
    plotquantity = cms.untracked.string("max(daughter(0).pt,daughter(1).pt)")
    ),
    cms.PSet(
    min = cms.untracked.double(0.0),
    max = cms.untracked.double(200.0),
    nbins = cms.untracked.int32(200),
    name = cms.untracked.string("mu2Pt"),
    description = cms.untracked.string("Lowest muon p_{t} [GeV/c]"),
    plotquantity = cms.untracked.string("min(daughter(0).pt,daughter(1).pt)")
    ),
    cms.PSet(
    min = cms.untracked.double(-6.0),
    max = cms.untracked.double(6.0),
    nbins = cms.untracked.int32(120),
    name = cms.untracked.string("mu1Eta"),
    description = cms.untracked.string("muon1 #eta"),
    plotquantity = cms.untracked.string("daughter(0).eta"),
    ),
    cms.PSet(
    min = cms.untracked.double(-6.0),
    max = cms.untracked.double(6.0),
    nbins = cms.untracked.int32(120),
    name = cms.untracked.string("mu2Eta"),
    description = cms.untracked.string("muon2 #eta"),
    plotquantity = cms.untracked.string("daughter(1).eta"),
    ),
    cms.PSet(
    min = cms.untracked.double(-6.0),
    max = cms.untracked.double(6.0),
    nbins = cms.untracked.int32(120),
    name = cms.untracked.string("mu1y"),
    description = cms.untracked.string("muon1 y"),
    plotquantity = cms.untracked.string("daughter(0).rapidity"),
    ),
    cms.PSet(
    min = cms.untracked.double(-6.0),
    max = cms.untracked.double(6.0),
    nbins = cms.untracked.int32(120),
    name = cms.untracked.string("mu2y"),
    description = cms.untracked.string("muon2 y"),
    plotquantity = cms.untracked.string("daughter(1).rapidity"),
    ),
    cms.PSet(
    min = cms.untracked.double(-4.0),
    max = cms.untracked.double(4.0),
    nbins = cms.untracked.int32(80),
    name = cms.untracked.string("mu1phi"),
    description = cms.untracked.string("muon1 #phi"),
    plotquantity = cms.untracked.string("daughter(0).phi"),
    ),
    cms.PSet(
    min = cms.untracked.double(-4.0),
    max = cms.untracked.double(4.0),
    nbins = cms.untracked.int32(80),
    name = cms.untracked.string("mu2phi"),
    description = cms.untracked.string("muon2 #phi"),
    plotquantity = cms.untracked.string("daughter(1).phi"),
    ),
    cms.PSet(
    min = cms.untracked.double(-0.1),
    max = cms.untracked.double(6.9),
    nbins = cms.untracked.int32(7000),
    name = cms.untracked.string("absMu1phiMinusMu2phi"),
    description = cms.untracked.string("|mu1 #phi - mu2 #phi|"),
    plotquantity = cms.untracked.string("abs(daughter(0).phi - daughter(1).phi)"),
    ),
    cms.PSet(
    min = cms.untracked.double(-10),
    max = cms.untracked.double(10),
    nbins = cms.untracked.int32(1000),
    name = cms.untracked.string("mu1 dxy"),
    description = cms.untracked.string("muon1 dxy"),
    plotquantity = cms.untracked.string("(- daughter(0).vx * daughter(0).py + daughter(0).vy * daughter(0).px) / daughter(0).pt "),
    ),
    cms.PSet(
    min = cms.untracked.double(-10),
    max = cms.untracked.double(10),
    nbins = cms.untracked.int32(1000),
    name = cms.untracked.string("mu2 dxy"),
    description = cms.untracked.string("muon2 dxy"),
    plotquantity = cms.untracked.string("(- daughter(1).vx * daughter(1).py + daughter(1).vy * daughter(1).px) / daughter(1).pt "),
    ),
    cms.PSet(
    min = cms.untracked.double(-10),
    max = cms.untracked.double(10),
    nbins = cms.untracked.int32(1000),
    name = cms.untracked.string("mu1 dz"),
    description = cms.untracked.string("muon1 dz"),
    plotquantity = cms.untracked.string("daughter(0).vz -  ( daughter(0).vx * daughter(0).px  + daughter(0).vy * daughter(0).py) / daughter(0).pt *  daughter(0).pz / daughter(0).pt"),
    ),
    cms.PSet(
    min = cms.untracked.double(-10),
    max = cms.untracked.double(10),
    nbins = cms.untracked.int32(1000),
    name = cms.untracked.string("mu2 dz"),
    description = cms.untracked.string("muon2 dz"),
    plotquantity = cms.untracked.string("daughter(1).vz -  ( daughter(1).vx * daughter(1).px  + daughter(1).vy * daughter(1).py) / daughter(1).pt *  daughter(1).pz / daughter(1).pt"),
    )
    )
    )




process.GenDimuonsPlots = cms.EDAnalyzer(
    "CandViewHistoAnalyzer",
    DiMuPlots,
    src = cms.InputTag("dimuons"),
    filter = cms.bool(False)
    )


process.dimuonsPlots = cms.EDAnalyzer(
    "CandViewHistoAnalyzer",
    DiMuPlots,
    src = cms.InputTag("dimuons"),
    filter = cms.bool(False)
    )

process.dimuonsGlobalPlots = cms.EDAnalyzer(
    "CandViewHistoAnalyzer",
    DiMuPlots,
    src = cms.InputTag("dimuonsGlobal"),
    filter = cms.bool(False)
    )



process.dimuonsGlobalSTAPlots = cms.EDAnalyzer(
    "CandViewHistoAnalyzer",
    DiMuPlots,
    src = cms.InputTag("dimuonsGlobalSTA"),
    filter = cms.bool(False)
    )



process.dimuonsGlobalTrkPlots = cms.EDAnalyzer(
        "CandViewHistoAnalyzer",
            DiMuPlots,
            src = cms.InputTag("dimuonsGlobalTrk"),
            filter = cms.bool(False)
            )



process.dimuonsSTAPlots = cms.EDAnalyzer(
    "CandViewHistoAnalyzer",
    DiMuPlots,
    src = cms.InputTag("dimuonsSTA"),
    filter = cms.bool(False)
    )

process.dimuonsTrkPlots = cms.EDAnalyzer(
        "CandViewHistoAnalyzer",
            DiMuPlots,
            src = cms.InputTag("dimuonsTrk"),
            filter = cms.bool(False)
            )



process.dimuons2DPlots = cms.EDAnalyzer(
    "DiMuon2DPlots",
<<<<<<< DiMuonPlots_cfg.py
    OutputFileName = cms.untracked.string("DiMuon2DPlots_PureZ0.root"),
=======
    OutputFileName = cms.untracked.string("/tmp/silvest/DiMuon2DPlots_HICorePhysics_PromptReco-v3_RECO_ZmumuPaperSkim.root"),
>>>>>>> 1.9
    ##for generator info put IsGenInfo as TRUE
    #IsGenInfo=cms.untracked.string("TRUE"),
    IsGenInfo=cms.untracked.string("FALSE"),
    IsPATInfo=cms.untracked.string("TRUE"),
    IsCuts = cms.untracked.bool(True)

    )


process.dimuonsSameChargePlots = cms.EDAnalyzer(
    "CandViewHistoAnalyzer",
    DiMuPlots,
    src = cms.InputTag("dimuonsSameCharge"),
    filter = cms.bool(False)
    )

process.dimuonsGlobalSameChargePlots = cms.EDAnalyzer(
        "CandViewHistoAnalyzer",
            DiMuPlots,
            src = cms.InputTag("dimuonsGlobalSameCharge"),
            filter = cms.bool(False)
            )


process.dimuonsGlobalSTASameChargePlots = cms.EDAnalyzer(
    "CandViewHistoAnalyzer",
    DiMuPlots,
    src = cms.InputTag("dimuonsGlobalSTASameCharge"),
    filter = cms.bool(False)
    )


process.dimuonsGlobalTrkSameChargePlots = cms.EDAnalyzer(
    "CandViewHistoAnalyzer",
    DiMuPlots,
    src = cms.InputTag("dimuonsGlobalTrkSameCharge"),
    filter = cms.bool(False)
    )



process.dimuonsSTASameChargePlots = cms.EDAnalyzer(
    "CandViewHistoAnalyzer",
    DiMuPlots,
    src = cms.InputTag("dimuonsSTASameCharge"),
    filter = cms.bool(False)
    )


process.dimuonsTrkSameChargePlots = cms.EDAnalyzer(
    "CandViewHistoAnalyzer",
    DiMuPlots,
    src = cms.InputTag("dimuonsTrkSameCharge"),
    filter = cms.bool(False)
    )




process.eventInfo = cms.OutputModule (
    "AsciiOutputModule"
       )
 
#process.primaryVertexFilterPath=cms.Path(process.primaryVertexFilter)
#process.filter_step = cms.Path(process.hfCoincFilter)

process.GenDimuonsPlotsPath = cms.Path(process.hfCoincFilter*process.primaryVertexFilter*process.GenDimuonsPlots)
process.dimuonsPlotsPath = cms.Path(process.primaryVertexFilter*process.dimuonsPlots)

process.dimuonsGlobalPlotsPath = cms.Path(process.dimuonsGlobalPlots)


process.dimuonsGlobalSTAPlotsPath = cms.Path(process.primaryVertexFilter*process.dimuonsGlobalSTAPlots)
process.dimuonsGlobalTrkPlotsPath = cms.Path(process.primaryVertexFilter*process.dimuonsGlobalTrkPlots)
process.dimuonsSTAPlotsPath = cms.Path(process.primaryVertexFilter*process.dimuonsSTAPlots)
process.dimuonsTrkPlotsPath = cms.Path(process.primaryVertexFilter*process.dimuonsTrkPlots)


process.dimuons2DPlotsPath = cms.Path(process.dimuons2DPlots)


process.dimuonsSameChargePlotsPath = cms.Path(process.dimuonsSameChargePlots)

process.dimuonsGlobalSameChargePlotsPath = cms.Path(process.dimuonsGlobalSameChargePlots)
process.dimuonsGlobalSTASameChargePlotsPath = cms.Path(process.dimuonsGlobalSTASameChargePlots)
process.dimuonsGlobalTrkSameChargePlotsPath = cms.Path(process.dimuonsGlobalTrkSameChargePlots)
process.dimuonsSTASameChargePlotsPath = cms.Path(process.dimuonsSTASameChargePlots)
process.dimuonsTrkSameChargePlotsPath = cms.Path(process.dimuonsTrkSameChargePlots)
process.endPath = cms.EndPath(process.eventInfo)

#process.schedule=cms.Schedule(process.dimuonsPlotsPath,process.dimuonsGlobalPlotsPath,process.dimuonsGlobalSTAPlotsPath,process.dimuonsGlobalTrkPlotsPath,process.dimuonsSTAPlotsPath,process.dimuonsTrkPlotsPath,process.dimuons2DPlotsPath,process.dimuonsSameChargePlotsPath,process.dimuonsGlobalSameChargePlotsPath,process.dimuonsGlobalSTASameChargePlotsPath,process.dimuonsGlobalTrkSameChargePlotsPath,process.dimuonsSTASameChargePlotsPath,process.dimuonsTrkSameChargePlotsPath,process.endPath)

process.schedule=cms.Schedule(process.dimuonsGlobalPlotsPath,process.dimuonsGlobalSameChargePlotsPath,process.dimuons2DPlotsPath,process.endPath)








#process.schedule=cms.Schedule(process.DimuonsPlotsPath,process.dimuonsGlobalPlotsPath,process.dimuonsGlobalSTAPlotsPath,process.dimuonsSTAPlotsPath,process.endPath)
