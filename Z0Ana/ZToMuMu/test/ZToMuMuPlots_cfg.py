##Gen level ploting is not working so gen level plots are same as reconstructed :)
##Vineet Kumar & Prashant Shukla
import FWCore.ParameterSet.Config as cms

process = cms.Process("ZMuMuGolden")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_3XY_V26::All')
process.load("Configuration.StandardSequences.MagneticField_cff")


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )


process.source = cms.Source("PoolSource",

                            noEventSort = cms.untracked.bool(True),
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),

                            fileNames = cms.untracked.vstring(


    #'file:TestForGenPlots.root'
##Central PbPb
#'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_ZMuMuSkim_EmbaddedCentral2_recoMu.root',
#'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_ZMuMuSkim_EmbaddedCentral3_recoMu.root',
#'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_ZMuMuSkim_CentralEmbadded4_recoMu.root'


## Minimum biased PbPb
    'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_ZMuMuSkim_Embadded_recoMu.root',
    'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_ZMuMuSkim_Embadded2_recoMu.root',
    'rfio:/castor/cern.ch/user/k/kumarv/Z0/Z0_ZMuMuSkim_Embadded3_recoMu.root'

#'file:Z0_ZMuMuSkim_HI_PAT.root'
#'file:Z0_hiCommonSkimAOD_pp_PAT.root'   
    )
                            )


process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string("TestForGen_Plot.root")
    )

zPlots = cms.PSet(
    histograms = cms.VPSet(
    cms.PSet(
    min = cms.untracked.double(0.0),
    max = cms.untracked.double(200.0),
    nbins = cms.untracked.int32(200),
    name = cms.untracked.string("zMass"),
    description = cms.untracked.string("Z mass [GeV/c^{2}]"),
    plotquantity = cms.untracked.string("mass")
    ),
    
    cms.PSet(
    min = cms.untracked.double(-10.0),
    max = cms.untracked.double(10.0),
    nbins = cms.untracked.int32(200),
    name = cms.untracked.string("zEta"),
    description = cms.untracked.string("Z #eta"),
    plotquantity = cms.untracked.string("eta")
    ),
    cms.PSet(
    min = cms.untracked.double(-6.0),
    max = cms.untracked.double(6.0),
    nbins = cms.untracked.int32(120),
    name = cms.untracked.string("zRapidity"),
    description = cms.untracked.string("Z y"),
    plotquantity = cms.untracked.string("rapidity")
    ),
    cms.PSet(
    min = cms.untracked.double(0),
    max = cms.untracked.double(200),
    nbins = cms.untracked.int32(200),
    name = cms.untracked.string("zPt"),
    description = cms.untracked.string("Z p_{t} [GeV/c]"),
    plotquantity = cms.untracked.string("pt")
    ),
    cms.PSet(
    min = cms.untracked.double(-4),
    max = cms.untracked.double(4),
    nbins = cms.untracked.int32(80),
    name = cms.untracked.string("zPhi"),
    description = cms.untracked.string("Z #phi"),
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


process.GenDimuonsPlots = cms.EDFilter(
    "CandViewHistoAnalyzer",
    zPlots,
    src = cms.InputTag("Dimuons"),
    filter = cms.bool(False)
    )


process.DimuonsPlots = cms.EDFilter(
    "CandViewHistoAnalyzer",
    zPlots,
    src = cms.InputTag("Dimuons"),
    filter = cms.bool(False)
    )

process.dimuonsGlobalPlots = cms.EDFilter(
    "CandViewHistoAnalyzer",
    zPlots,
    src = cms.InputTag("dimuonsGlobal"),
    filter = cms.bool(False)
    )

process.dimuonsGlobalSTAPlots = cms.EDFilter(
    "CandViewHistoAnalyzer",
    zPlots,
    src = cms.InputTag("dimuonsGlobalSTA"),
    filter = cms.bool(False)
    )


process.dimuonsSTAPlots = cms.EDFilter(
    "CandViewHistoAnalyzer",
    zPlots,
    src = cms.InputTag("dimuonsSTA"),
    filter = cms.bool(False)
    )

process.eventInfo = cms.OutputModule (
    "AsciiOutputModule"
        )

process.GenDimuonsPlotsPath = cms.Path(
        process.GenDimuonsPlots
            )

process.DimuonsPlotsPath = cms.Path(
    process.DimuonsPlots
    )


process.dimuonsGlobalPlotsPath = cms.Path(
    process.dimuonsGlobalPlots
    )
process.dimuonsGlobalSTAPlotsPath = cms.Path(
    process.dimuonsGlobalSTAPlots
    )

process.dimuonsSTAPlotsPath = cms.Path(
    process.dimuonsSTAPlots
    )


process.endPath = cms.EndPath(
    process.eventInfo
    )
process.schedule=cms.Schedule(process.GenDimuonsPlotsPath,process.DimuonsPlotsPath,process.dimuonsGlobalPlotsPath,process.dimuonsGlobalSTAPlotsPath,process.dimuonsSTAPlotsPath,process.endPath)
#process.schedule=cms.Schedule(process.DimuonsPlotsPath,process.dimuonsGlobalPlotsPath,process.dimuonsGlobalSTAPlotsPath,process.dimuonsSTAPlotsPath,process.endPath)
