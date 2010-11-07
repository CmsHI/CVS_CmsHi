
import FWCore.ParameterSet.Config as cms

process = cms.Process("TESTC")

process.HeavyIonGlobalParameters = cms.PSet(
    centralitySrc = cms.InputTag("hiCentrality"),
    centralityVariable = cms.string("HFhits"),
    nonDefaultGlauberModel = cms.string("")
    )

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_39X_V1::All'

from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(-1)
        )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_10_1_q4x.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_11_1_YsR.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_12_1_A8J.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_13_1_HvH.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_14_1_pVp.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_15_1_JdA.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_16_1_36I.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_17_1_G6d.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_18_1_95N.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_19_1_O2W.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_1_1_R7b.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_20_1_lP0.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_21_1_2kG.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_22_1_3pM.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_23_1_CjS.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_24_1_WNK.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_25_1_BaE.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_26_1_BSm.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_27_1_E9j.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_2_1_ReL.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_3_1_nrP.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_4_1_4zm.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_5_1_s5n.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_6_1_EY1.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_7_1_yn5.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_8_1_BdG.root",
"rfio:/castor/cern.ch/cms/store/caf/user/frankma/HR10Exp3/r150308HFSkim/skim_RECO_9_1_2w4.root",

)
    
                            )

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.analyze = cms.EDAnalyzer("AnalyzerWithCentrality")

process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string("histograms.root")
                                   )

process.p = cms.Path(process.centralityBin*process.analyze)

