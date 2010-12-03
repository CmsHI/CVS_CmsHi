import FWCore.ParameterSet.Config as cms

process = cms.Process('SKIMDIMU')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')


process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('Configuration.StandardSequences.SkimsHeavyIons_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('RecoHI.HiEgammaAlgos.HiElectronSequence_cff')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR10_P_V12::All'


process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.5 $'),
    annotation = cms.untracked.string('centralSkimsHI nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)


process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.5 $'),
    annotation = cms.untracked.string('centralSkimsHI nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
'rfio:/castor/cern.ch/user/e/edwenger/skims/mergeZMM_run151058.root',
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v2/000/150/590/FC055AD2-9EEC-DF11-9115-001D09F2514F.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v2/000/150/590/FC9F86A6-9AEC-DF11-83A0-0030487CD178.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v2/000/150/590/FCA54188-98EC-DF11-BD79-001D09F2545B.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/E2B1A288-E2EF-DF11-B8D7-0030487CD906.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/E85948F4-D2EF-DF11-8ECC-003048F117B4.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/E861B650-D3EF-DF11-905A-003048678110.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/E8AE36B4-E8EF-DF11-9004-001617C3B654.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/EAF2E44D-D3EF-DF11-AAE7-001D09F2423B.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/ECC6CDF3-E1EF-DF11-92FE-001D09F25041.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/EE5E046F-F0EF-DF11-BA90-001617C3B65A.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/EEDEAE00-D0EF-DF11-82A9-001617C3B77C.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/F0917068-DDEF-DF11-B1C2-003048D2BBF0.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/F0E5B26B-E9EF-DF11-B3CF-001617E30CC2.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/F2734D91-E4EF-DF11-90D8-0030487CD6DA.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/F403C928-DBEF-DF11-9B38-001D09F24DA8.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/F4824CF0-CFEF-DF11-9325-0030487CD16E.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/F4D6BA9F-DBEF-DF11-AD7F-0030487CD7E0.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/F654F91C-C8EF-DF11-BABB-001D09F28D4A.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/F65C8FAE-CFEF-DF11-B4C8-003048D2C020.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/F6D7B1B1-CFEF-DF11-A3B1-003048F1C836.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/F8ADCA51-EEEF-DF11-80AF-0016177CA778.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/F8E6B0B5-E8EF-DF11-BCE5-000423D98B6C.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/FABAD7F7-E5EF-DF11-8E0E-003048F11114.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/FE7383EC-D3EF-DF11-9F2B-003048678110.root",
"rfio:/castor/cern.ch/cms/store/hidata/HIRun2010/HICorePhysics/RECO/PromptReco-v3/000/151/058/FE8F3726-D4EF-DF11-B467-001D09F24303.root"
),
                            )

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
    )

#process.Timing = cms.Service("Timing")

# Output definition
process.load("HeavyIonsAnalysis.DiMuon.MuSkimEventContent_cff")
process.load("HeavyIonsAnalysis.DiMuon.DiMuonEventContent_cff")
process.load("HeavyIonsAnalysis.Configuration.analysisEventContent_cff")
#process.load("HLTrigger.Configuration.HLTrigger_EventContent_cff")
process.MyContent =process.FEVTDEBUGEventContent.clone()
#process.MyContent.outputCommands.extend(process.HLTDebugRAW.outputCommands)
#process.MyContent.outputCommands.extend(process.MuSkimContent.outputCommands)
#process.MyContent.outputCommands.extend(process.muonTrkSkimContent.outputCommands)
#process.MyContent.outputCommands.extend(process.muonContent.outputCommands)
process.MyContent.outputCommands.extend(process.DiMuonContent.outputCommands)
process.MyContent.outputCommands.extend(cms.untracked.vstring(
    'keep *_*pat*_*_*'))

process.SKIMStreamZMM = cms.OutputModule("PoolOutputModule",
                                         process.MyContent,
                                         SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('zMMSkimPath')
        ),
                                         fileName = cms.untracked.string('ZoroSkim.root'),
                                         dataset = cms.untracked.PSet(
        filterName = cms.untracked.string('ZMM'),
        dataTier = cms.untracked.string('RECO')
        )
                                         )

# ====================== event selection
# HLT dimuon trigger
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltZMMHI = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltZMMHI.HLTPaths = ["HLT_HIL1DoubleMuOpen_Core","HLT_HIL2DoubleMu3_Core"]
process.hltZMMHI.throw = False
process.hltZMMHI.andOr = True

process.load("HeavyIonsAnalysis.Configuration.collisionEventSelection_cff")

'''
# Minimum bias trigger selection (early runs) before 150882
process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltMinBiasHFOrBSC = process.hltHighLevel.clone()
process.hltMinBiasHFOrBSC.HLTPaths = ["HLT_HIMinBiasHfOrBSC_Core","HLT_HIMinBiasHf_Core","HLT_HIMinBiasBSC_Core"]
process.hltMinBiasHFOrBSC.throw = cms.bool(False) # ignore missing paths
#process.hltMinBiasHFOrBSC.HLTPaths = ["HLT_HIMinBiasHf_Core","HLT_HIMinBiasBSC_Core"]
#process.hltMinBiasHFOrBSC.throw = cms.bool(True) # ignore missing paths
'''
# BSC or HF coincidence (masked unprescaled L1 bits)
process.load('L1Trigger.Skimmer.l1Filter_cfi')
process.bscOrHfCoinc = process.l1Filter.clone(
    algorithms = cms.vstring('L1_BscMinBiasThreshold1', 'L1_HcalHfCoincidencePm')
)

# ========================= making dimuon pairs opposite and same sign
# selection of dimuons (at least STA+STA) with mass in Z range
process.muonSelector = cms.EDFilter("MuonSelector",
    src = cms.InputTag("muons"),
    cut = cms.string("isStandAloneMuon && pt>1. && outerTrack().hitPattern().numberOfValidMuonHits()>0"),
    filter = cms.bool(True)
    )

process.muonFilter = cms.EDFilter("MuonCountFilter",
    src = cms.InputTag("muonSelector"),
    minNumber = cms.uint32(2)
    )


# Z->mumu skim sequence
process.zMMSkimPath = cms.Path(
    process.bscOrHfCoinc*
    process.collisionEventSelection*
    process.hltZMMHI *
    process.muonSelector *
    process.muonFilter #*
    #process.dimuonMassCut *
    #process.dimuonMassCutFilter
    )

#================== PAT sequences
process.load("HeavyIonsAnalysis.Configuration.patMuonsWithTrigger_cff")
from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import addMCinfo, changeRecoMuonInput, useL1MatchingWindowForSinglets, changeTriggerProcessName, switchOffAmbiguityResolution
useL1MatchingWindowForSinglets(process)
changeTriggerProcessName(process, "HLT")
switchOffAmbiguityResolution(process) # Switch off ambiguity resolution: allow multiple reco muons to match to the same trigger muon
process.muonMatchHLTL3.maxDeltaR = 0.1
process.muonMatchHLTL3.maxDPtRel = 10.0
process.muonMatchHLTCtfTrack.maxDeltaR = 0.1
process.muonMatchHLTCtfTrack.maxDPtRel = 10.0
process.muonMatchHLTTrackMu.maxDeltaR = 0.1
process.muonMatchHLTTrackMu.maxDPtRel = 10.0
'''
process.patGoodZMuons = cms.EDFilter("CandViewSelector",
                                     src = cms.InputTag("patMuonsWithTrigger"),
                                     cut = cms.string('isGlobalMuon = 1 & isTrackerMuon = 1 & abs(eta)<2.4 &\
                                        innerTrack().hitPattern().numberOfValidHits() > 11 &\
                                        innerTrack().hitPattern().pixelLayersWithMeasurement() > 1 &\
                                        globalTrack().chi2()/globalTrack().ndof() < 10 &\
                                        globalTrack().hitPattern().numberOfValidMuonHits() > 0 &\
                                        abs(innerTrack().dxy()) < 3.0 &\
                                        abs(innerTrack().dz()) < 15.0 &\
                                        innerTrack().chi2()/innerTrack().ndof() < 4.0'
                                        ),
                                         filter = cms.bool(False)
                                     )

process.patGoodZMuonsFilter = cms.EDFilter("MuonCountFilter",
    src = cms.InputTag("patGoodZMuons"),
    minNumber = cms.uint32(1)
    )
'''
process.muPAT = cms.Path(
    process.patMuonsWithTriggerSequence#* 
  #  process.patGoodZMuons
    )

# =========================================

# filter on dimuon mass 
process.load("HeavyIonsAnalysis.DiMuon.DiMuonFilters_cff")
process.Dimuons_Step                    =cms.Path(process.dimuons)
process.DiMuonsGlobal_Step              =cms.Path(process.dimuonsGlobal*process.dimuonsGlobalFilter)
process.DiMuonsGlobalSTA_Step           =cms.Path(process.dimuonsGlobalSTA*process.dimuonsGlobalSTAFilter)
process.DiMuonsSTA_Step                 =cms.Path(process.dimuonsSTA*process.dimuonsSTAFilter)
process.DiMuonsSTAinclusive_Step        =cms.Path(process.dimuonsSTAinclusive*process.dimuonsSTAFilterInclusive)
process.DiMuonsSameCharge_Step          =cms.Path(process.dimuonsSameCharge*process.dimuonsSameChargeFilter)
process.DiMuonsGlobalSameCharge_Step    =cms.Path(process.dimuonsGlobalSameCharge*process.dimuonsGlobalSameChargeFilter)
process.DiMuonsGlobalSTASameCharge_Step =cms.Path(process.dimuonsGlobalSTASameCharge*process.dimuonsGlobalSTASameChargeFilter)
process.DiMuonsSTASameCharge_Step       =cms.Path(process.dimuonsSTASameCharge*process.dimuonsSTASameChargeFilter)
process.DiMuonsSTASameChargeInclusive_Step       =cms.Path(process.dimuonsSTASameChargeInclusive*process.dimuonsSTASameChargeFilterInclusive)

# filter on dimuon mass 
process.load("HeavyIonsAnalysis.DiMuon.DiMuonFiltersPat_cff")
# making dimuon pairs opposite and same sign
process.patDimuons_Step                 =cms.Path(process.patdimuons)
process.patDiMuonsGlobal_Step           =cms.Path(process.patdimuonsGlobal*process.patdimuonsGlobalFilter)
process.patDiMuonsGlobalSTA_Step        =cms.Path(process.patdimuonsGlobalSTA*process.patdimuonsGlobalSTAFilter)
process.patDiMuonsSTA_Step              =cms.Path(process.patdimuonsSTA*process.patdimuonsSTAFilter)

process.patDiMuonsSameCharge_Step       =cms.Path(process.patdimuonsSameCharge*process.patdimuonsSameChargeFilter)
process.patDiMuonsGlobalSameCharge_Step =cms.Path(process.patdimuonsGlobalSameCharge*process.patdimuonsGlobalSameChargeFilter)
process.patDiMuonsGlobalSTASameCharge_Step =cms.Path(process.patdimuonsGlobalSTASameCharge*process.patdimuonsGlobalSTASameChargeFilter)
process.patDiMuonsSTASameCharge_Step       =cms.Path(process.patdimuonsSTASameCharge*process.patdimuonsSTASameChargeFilter)

process.patDiMuonsSTAinclusive_Step                 =cms.Path(process.patdimuonsSTAinclusive*process.patdimuonsSTAFilterInclusive)
process.patDiMuonsSTASameChargeInclusive_Step       =cms.Path(process.patdimuonsSTASameChargeInclusive*process.patdimuonsSTASameChargeFilterInclusive)


process.SKIMStreamZMMOutPath = cms.EndPath(process.SKIMStreamZMM)

# Schedule definition
process.schedule = cms.Schedule(
process.zMMSkimPath,
process.Dimuons_Step,
process.DiMuonsGlobal_Step,
process.DiMuonsGlobalSTA_Step,
process.DiMuonsSTA_Step,
process.DiMuonsSTAinclusive_Step,
process.DiMuonsSameCharge_Step,
process.DiMuonsGlobalSameCharge_Step,
process.DiMuonsGlobalSTASameCharge_Step,
process.DiMuonsSTASameCharge_Step,
process.DiMuonsSTASameChargeInclusive_Step,
process.muPAT,
process.patDimuons_Step,
process.patDiMuonsGlobal_Step,
process.patDiMuonsGlobalSTA_Step,
process.patDiMuonsSTA_Step,
process.patDiMuonsSTAinclusive_Step,
process.patDiMuonsSameCharge_Step,
process.patDiMuonsGlobalSameCharge_Step,
process.patDiMuonsGlobalSTASameCharge_Step,
process.patDiMuonsSTASameCharge_Step,
process.patDiMuonsSTASameChargeInclusive_Step,
process.SKIMStreamZMMOutPath)





