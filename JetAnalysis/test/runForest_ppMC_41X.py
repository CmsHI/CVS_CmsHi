import FWCore.ParameterSet.Config as cms

process = cms.Process('JetAna')

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
#    'rfio:/castor/cern.ch/cms/store/relval/CMSSW_3_9_9/RelValPyquen_DiJet_pt80to120_2760GeV/GEN-SIM-RECO/START39_V7HI-v1/0001/708F4C5C-6E3E-E011-B6A6-00261894390C.root'
    'file:Pyquen_UnquenchedDiJet_Pt80_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_RECO_11_1_4Qu.root'
    ))

process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32(-1))

#load some general stuff
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
#process.MessageLogger.cerr.FwkReport.reportEvery = 100
#process.GlobalTag.globaltag = 'GR_R_41_V0::All'
#process.GlobalTag.globaltag = 'GR_P_V17::All'
process.GlobalTag.globaltag = 'START41_V0::All'

# load centrality
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
	centralityVariable = cms.string("HFhits"),
	nonDefaultGlauberModel = cms.string(""),
	centralitySrc = cms.InputTag("hiCentrality")
	)

# tree output
process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("JetAnaTrees.root"))

# Define Jet energy correction
process.jec = cms.ESSource("PoolDBESSource",
	DBParameters = cms.PSet(messageLevel = cms.untracked.int32(0)),
	timetype = cms.string('runnumber'),
	toGet = cms.VPSet(

          cms.PSet(record = cms.string("JetCorrectionsRecord"),
                                            tag = cms.string("JetCorrectorParametersCollection_HI_Calo_hiGoodTightTracks_D6T_413_IC5Calo"),
                                            label = cms.untracked.string("IC5Calo")),

                          cms.PSet(record = cms.string("JetCorrectionsRecord"),
                                                            tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_D6T_413_AK3PF'),
                                                            label = cms.untracked.string("AK3PF")),

                          cms.PSet(record = cms.string("JetCorrectionsRecord"),
                                                            tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_D6T_413_AK4PF'),
                                                            label = cms.untracked.string("AK4PF")),

                          cms.PSet(record = cms.string("JetCorrectionsRecord"),
                                                            tag    = cms.string('JetCorrectorParametersCollection_HI_PFTowers_hiGoodTightTracks_D6T_413_AK5PF'),
                                                            label = cms.untracked.string("AK5PF")
                                                            ),
          ),
                           connect = cms.string("sqlite_file:JEC_HI_PFTower_413patch2_2011_v3.db"),
                           )
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource','jec')

# Define Analysis sequencues
process.load('CmsHi.JetAnalysis.EventSelection_cff')
#process.load('CmsHi.JetAnalysis.ExtraGenReco_cff')
process.load('CmsHi.JetAnalysis.ExtraTrackReco_cff')
process.load('CmsHi.JetAnalysis.ExtraPfReco_cff')
process.load('CmsHi.JetAnalysis.ExtraJetReco_cff')
process.load('CmsHi.JetAnalysis.ExtraEGammaReco_cff')
process.load('CmsHi.JetAnalysis.PatAna_cff')
process.load('CmsHi.JetAnalysis.JetAnalyzers_cff')
process.load('CmsHi.JetAnalysis.EGammaAnalyzers_cff')
process.load("MitHig.PixelTrackletAnalyzer.trackAnalyzer_cff")
process.anaTrack.trackPtMin = 4

process.ak5CaloJets = process.akPu5CaloJets.clone(doPUOffsetCorr = False)
process.ak5corr = process.icPu5corr.clone( src = cms.InputTag("ak5CaloJets"),
            payload = cms.string('AK5Calo'))

process.ak5match = process.patJetGenJetMatch.clone( src = cms.InputTag("ak5CaloJets"),
                                                    matched = cms.InputTag("akPu5PFclean") )
process.ak5parton = process.patJetPartonMatch.clone( src = cms.InputTag("ak5CaloJets"))

process.ak5patJets = process.akPu5PFpatJets.clone(jetSource = cms.InputTag("ak5CaloJets"),
                                                  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak5corr")),
                                                  genJetMatch = cms.InputTag("ak5match"),
                                                  genPartonMatch = cms.InputTag("ak5parton"))

process.ak5CaloJetAnalyzer = process.icPu5JetAnalyzer.clone(jetTag = 'ak5patJets',
                                                            genjetTag = 'ak5HiGenJets',
                                                            isMC = False)
    

process.ak3PFJetsX = process.akPu3PFJets.clone(doPUOffsetCorr = False)
process.ak3corrX = process.icPu5corr.clone(src = cms.InputTag("ak3PFJetsX"),
    payload = cms.string('AK3PF'))
    
process.ak3PFmatchX = process.patJetGenJetMatch.clone(src = cms.InputTag("ak3PFJetsX"),
        matched = cms.InputTag("akPu3PFclean"))

process.ak3PFpartonX = process.patJetPartonMatch.clone(
    src = cms.InputTag("ak3PFJetsX")
    )
process.ak3patJetsX = process.akPu5PFpatJets.clone(
    jetSource = cms.InputTag("ak3PFJetsX"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak3corrX")),
    genJetMatch = cms.InputTag("ak3PFmatchX"),
    genPartonMatch = cms.InputTag("ak3PFpartonX"),
    )
process.ak3PFJetAnalyzer = process.icPu5JetAnalyzer.clone(
    jetTag = 'ak3patJetsX',
    genjetTag = 'ak3HiGenJets',
    isMC = False
    )

process.ak5extra = cms.Sequence(process.ak5CaloJets*process.ak5corr*
                                process.ak5match * process.ak5parton *
                                process.ak5patJets*process.ak5CaloJetAnalyzer)
process.ak3extra = cms.Sequence(process.ak3PFJetsX*process.ak3corrX*
                                process.ak3PFmatchX*process.ak3PFpartonX*
                                process.ak3patJetsX*process.ak3PFJetAnalyzer)

process.load("edwenger.Skims.EventFilter_cff")
from edwenger.Skims.customise_cfi import *
run2760GeVmode(process)

# Filtering
process.hltJetHI.HLTPaths = ['HLT_HIJet35U','HLT_HIPhoton20']
print "Add cleaning to analysis"
process.event_filter_seq = cms.Sequence(
  process.hltJetHI *
#  process.collisionEventSelection *
  process.hbheReflagNewTimeEnv *
  process.hcalTimingFilter *
  process.HBHENoiseFilter *

  process.hiEcalRecHitSpikeFilter *

  process.preTrgTest *
  process.minBiasBscFilter *
  process.postTrgTest *
  process.hfCoincFilter *
  process.purityFractionFilter

  )

process.hiPixelAdaptiveVertex.useBeamConstraint = False

process.load("RecoHI.HiMuonAlgos.HiRecoMuon_cff")
process.muons.JetExtractorPSet.JetCollectionLabel = cms.InputTag("iterativeConePu5CaloJets")

process.hiGoodTightTracks.src = cms.InputTag("hiGlobalPrimTracks")
process.hiGoodTightTracksDirect = process.hiGoodTightTracks.clone(keepAllTracks = True)
process.hiGoodTracks = process.hiGoodTightTracks.clone()

process.pfTrack.TkColList = ["hiGoodTightTracksDirect"]
process.pfTrack.GsfTracksInEvents = False

process.reco_extra        = cms.Path( process.hiTrackReReco * process.hiextraTrackReco * process.iterativeConePu5CaloJets *
                                      process.hiGoodTightTracksDirect *  process.muonRecoPbPb *
                                      process.HiParticleFlowRecoNoJets * process.hiCentrality * process.hiGoodTracks)
process.reco_extra_jet    = cms.Path( process.iterativeConePu5CaloJets * process.akPu3PFJets * process.akPu5PFJets * process.photon_extra_reco)
process.gen_step          = cms.Path( process.hiGenParticlesForJets * process.genPartons * process.hiPartons * process.hiRecoGenJets)
process.pat_step          = cms.Path( process.icPu5patSequence + process.akPu3PFpatSequence + process.akPu5PFpatSequence + process.makeHeavyIonPhotons + process.ak5extra + process.ak3extra)
process.extrapatstep = cms.Path(process.selectedPatPhotons)
process.ana_step          = cms.Path( process.icPu5JetAnalyzer + process.akPu3PFJetAnalyzer + process.multiPhotonAnalyzer + process.anaTrack)

process.phltJetHI = cms.Path( process.hltJetHI )
# process.pcollisionEventSelection = cms.Path(process.collisionEventSelection)
process.phbheReflagNewTimeEnv = cms.Path( process.hbheReflagNewTimeEnv )
process.phcalTimingFilter = cms.Path( process.hcalTimingFilter )
process.pHBHENoiseFilter = cms.Path( process.HBHENoiseFilter )
process.phiEcalRecHitSpikeFilter = cms.Path(process.hiEcalRecHitSpikeFilter )
#process.ppreTrgTest = cms.Path(process.preTrgTest )
#process.pminBiasBscFilter = cms.Path(process.minBiasBscFilter )
#process.ppostTrgTest = cms.Path(process.postTrgTest )
process.phfCoincFilter = cms.Path(process.hfCoincFilter )
#process.ppurityFractionFilter = cms.Path(process.purityFractionFilter )

# Customization
from CmsHi.JetAnalysis.customise_cfi import *
#enableDataPat(process)
enableDataAnalyzers(process)

# Photon modifications - to be confirmed:
setPhotonObject(process,"cleanPhotons")
process.multiPhotonAnalyzer.GenEventScale = cms.InputTag("generator")
process.interestingTrackEcalDetIds.TrackCollection = cms.InputTag("hiSelectedTracks")
process.photonMatch.matched = cms.InputTag("hiGenParticles")

enableOpenHlt(process,process.ana_step)
process.hltanalysis.RunParameters.DoAlCa = cms.untracked.bool(False)
process.hltanalysis.RunParameters.DoJets = cms.untracked.bool(False)
process.hltanalysis.RunParameters.DoVertex = cms.untracked.bool(True)
process.hltanalysis.PrimaryVertices = cms.InputTag("hiSelectedVertex")
process.hltanalysis.OfflinePrimaryVertices0 = cms.InputTag("hiSelectedVertex")

process.skimanalysis = process.hltanalysis.clone(
    HLTProcessName                  = cms.string("JetAna"),
    hltresults                      = cms.InputTag("TriggerResults::JetAna")
    )
process.pAna = cms.EndPath(process.skimanalysis)

########### random number seed
process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
  multiPhotonAnalyzer = cms.PSet(
    engineName = cms.untracked.string("TRandom3"),
    initialSeed = cms.untracked.uint32(98236)
    )
  )

#process.out = cms.OutputModule("PoolOutputModule",
#                               fileName = cms.untracked.string("output.root")
#                               )
#process.save = cms.EndPath(process.out)


