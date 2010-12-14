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
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('centralSkimsHI nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
'rfio:/castor/cern.ch/user/e/edwenger/skims/mergeZMM_run151058.root'
),
                            )

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
    )

#process.Timing = cms.Service("Timing")

# Output definition
process.load("HiDiMuonAna.DiMuon.MuSkimEventContent_cff")
process.load("HiDiMuonAna.DiMuon.DiMuonEventContent_cff")
process.load("HeavyIonsAnalysis.Configuration.analysisEventContent_cff")
process.MyContent =process.FEVTDEBUGEventContent.clone()
process.MyContent.outputCommands.extend(process.DiMuonContent.outputCommands)
process.MyContent.outputCommands.extend(cms.untracked.vstring(
    'keep *_*pat*_*_*','keep *_*dimuons*_*_*'))

process.SKIMStreamZMM = cms.OutputModule("PoolOutputModule",
                                         process.MyContent,
                                         SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('zMMSkimPath')
        ),
                                         fileName = cms.untracked.string('PanchoSkim.root'),
                                         dataset = cms.untracked.PSet(
        filterName = cms.untracked.string('ZMM'),
        dataTier = cms.untracked.string('RECO')
        )
                                         )

# ====================== event selection
# HLT dimuon trigger
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltZMMHI = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltZMMHI.HLTPaths = ["HLT_HIL1DoubleMuOpen_Core"]
process.hltZMMHI.throw = False
process.hltZMMHI.andOr = True

process.load("HeavyIonsAnalysis.Configuration.collisionEventSelection_cff")


# Minimum bias trigger selection (early runs) before 150882
process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltMinBiasHFOrBSC = process.hltHighLevel.clone()

#process.hltMinBiasHFOrBSC.HLTPaths = ["HLT_HIMinBiasHfOrBSC_Core"]#,"HLT_HIMinBiasHf_Core","HLT_HIMinBiasBSC_Core"]
#process.hltMinBiasHFOrBSC.throw = cms.bool(False) # ignore missing paths
process.hltMinBiasHFOrBSC.HLTPaths = ["HLT_HIMinBiasHf_Core","HLT_HIMinBiasBSC_Core"]
process.hltMinBiasHFOrBSC.throw = cms.bool(False) # ignore missing paths

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
process.dimuonMassCut = cms.EDProducer("CandViewShallowCloneCombiner",
    checkCharge = cms.bool(False),
    cut = cms.string(' 30 < mass '),
    decay = cms.string("muonSelector@+ muonSelector@-")
    )

process.dimuonMassCutFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("dimuonMassCut"),
    minNumber = cms.uint32(1)
    )



process.MinBiasCounterHIMinBiasHfOrBSC = cms.EDAnalyzer('MinBiasCounter',
                              TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                              triggerName = cms.string("HLT_HIMinBiasHfOrBSC_Core")
)
process.MinBiasCounterHIMinBiasHf = cms.EDAnalyzer('MinBiasCounter',
                              TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                              triggerName = cms.string("HLT_HIMinBiasHf_Core")
)
process.MinBiasCounterHIMinBiasBSC = cms.EDAnalyzer('MinBiasCounter',
                              TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                              triggerName = cms.string("HLT_HIMinBiasBSC_Core")
)
process.MinBiasCounterHIL2DoubleMu3 = cms.EDAnalyzer('MinBiasCounter',
                              TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                              triggerName = cms.string("HLT_HIL2DoubleMu3_Core")
)
process.MinBiasCounterHIL1DoubleMuOpen = cms.EDAnalyzer('MinBiasCounter',
                              TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT"),
                              triggerName = cms.string("HLT_HIL1DoubleMuOpen_Core")
)

process.minbiasPath = cms.Path(
    process.hltMinBiasHFOrBSC*
   #process.MinBiasCounterHIMinBiasHfOrBSC*
    process.MinBiasCounterHIMinBiasHf*
  #  process.MinBiasCounterHIMinBiasBSC*
    process.collisionEventSelection
    )

# Z->mumu skim sequence
process.zMMSkimPath = cms.Path(
    process.hltZMMHI *
  #  process.MinBiasCounterHIL2DoubleMu3*
    process.MinBiasCounterHIL1DoubleMuOpen*
    process.bscOrHfCoinc*
    process.collisionEventSelection*
    process.muonSelector *
    process.muonFilter*
    process.dimuonMassCut *
    process.dimuonMassCutFilter
    )

#================== PAT sequences
process.load("HiDiMuonAna.DiMuon.patMuonsWithTrigger_cff")
from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import addMCinfo, changeRecoMuonInput, useL1MatchingWindowForSinglets, changeTriggerProcessName, switchOffAmbiguityResolution
useL1MatchingWindowForSinglets(process)
changeTriggerProcessName(process, "HLT")
switchOffAmbiguityResolution(process) # Switch off ambiguity resolution: allow multiple reco muons to match to the same trigger muon
process.muonMatchHLTL1.fallbackToME1 = True


process.muPAT = cms.Path(
    process.patMuonsWithTriggerSequence#* 
  #  process.patGoodZMuons
    )

# =========================================

# filter on dimuon mass 
process.load("HiDiMuonAna.DiMuon.DiMuonFilters_cff")
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
process.load("HiDiMuonAna.DiMuon.DiMuonFiltersPat_cff")
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
process.minbiasPath,
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




