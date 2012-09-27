
import FWCore.ParameterSet.VarParsing as VarParsing

ivars = VarParsing.VarParsing('python')

ivars.register ('randomNumber',
                1,
                ivars.multiplicity.singleton,
                ivars.varType.int,
                "Random Seed")

ivars.register ('secFiles',
                1,
                ivars.multiplicity.singleton,
                ivars.varType.string,
                "Random Seed")

ivars.randomNumber = 1

ivars.inputFiles = "___I___"

ivars.outputFile = "___O___"

ivars.parseArguments()


import FWCore.ParameterSet.Config as cms

process = cms.Process('hiForestAna2011')

process.options = cms.untracked.PSet(
   # wantSummary = cms.untracked.bool(True)
)


hiTrackQuality = "highPurity"              # iterative tracks
#hiTrackQuality = "highPuritySetWithPV"    # calo-matched tracks

doElectrons = False
doRegitForBjets = False


#####################################################################################

process.load("CmsHi.JetAnalysis.HiForest_cff")
process.HiForest.inputLines = cms.vstring("HiForest V2 for pPb",
                                          "PF : generalTracks (pp) with highPurity",
                                          "EP Flattening OFF",
                                          "Electrons OFF",
                                          "Preshower OFF"
                                          )

#####################################################################################
# Input source
#####################################################################################

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                            fileNames = cms.untracked.vstring(ivars.inputFiles),
#                            secondaryFileNames = cms.untracked.vstring(ivars.secFiles),
                            )

# Number of events we want to process, -1 = all events
process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32(-1))


#####################################################################################
# Load some general stuff
#####################################################################################

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Services_cff')
#process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('RecoLocalTracker.SiPixelRecHits.PixelCPEESProducers_cff')
process.load('HLTrigger.Configuration.HLT_HIon_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')


#process.load('MitHig.PixelTrackletAnalyzer.pixelHitAnalyzer_cfi')

# Data Global Tag 44x 
#process.GlobalTag.globaltag = 'GR_E_V31::All'
process.GlobalTag.globaltag = 'GR_P_V41::All'

process.Timing = cms.Service("Timing")

# MC Global Tag 44x 
#process.GlobalTag.globaltag = 'PLEASE_ENTER_GT::All'

# load centrality
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)

process.HeavyIonGlobalParameters = cms.PSet(
	centralityVariable = cms.string("HFtowers"),
	nonDefaultGlauberModel = cms.string("Hydjet_Drum"),
	centralitySrc = cms.InputTag("hiCentrality")
	)

process.load("CmsHi.JetAnalysis.RandomCones_cff")

process.RandomNumberGeneratorService.generator.initialSeed = ivars.randomNumber 
process.RandomNumberGeneratorService.akPu3PFConesAna = process.RandomNumberGeneratorService.generator.clone()
process.RandomNumberGeneratorService.icPu5CaloConesAna = process.RandomNumberGeneratorService.generator.clone()
process.RandomNumberGeneratorService.akPu5PFConesAna = process.RandomNumberGeneratorService.generator.clone()
process.RandomNumberGeneratorService.akPu3CaloConesAna = process.RandomNumberGeneratorService.generator.clone()
process.RandomNumberGeneratorService.akPu5CaloConesAna = process.RandomNumberGeneratorService.generator.clone()
process.RandomNumberGeneratorService.multiPhotonAnalyzer = process.RandomNumberGeneratorService.generator.clone()

# EcalSeverityLevel ES Producer
process.load("RecoLocalCalo/EcalRecAlgos/EcalSeverityLevelESProducer_cfi")
process.load("RecoEcal.EgammaCoreTools.EcalNextToDeadChannelESProducer_cff")

#####################################################################################
# Define tree output
#####################################################################################

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string(ivars.outputFile))

#####################################################################################
# Additional Reconstruction and Analysis
#####################################################################################

# MET: Calorimeter based MET
process.load("RecoMET.METProducers.CaloMET_cfi") 

process.load("CmsHi.JetAnalysis.hcalNoise_cff")

# Define Analysis sequencues
process.load('CmsHi.JetAnalysis.EventSelection_cff')
process.load('CmsHi.JetAnalysis.ExtraGenReco_cff')
process.load('CmsHi.JetAnalysis.ExtraTrackReco_cff')
process.load('CmsHi.JetAnalysis.ExtraPfReco_cff')
process.load('CmsHi.JetAnalysis.ExtraJetReco_cff')
process.load('CmsHi.JetAnalysis.ExtraEGammaReco_cff')
process.load('CmsHi.JetAnalysis.PatAna_MC_cff')
process.load('CmsHi.JetAnalysis.JetAnalyzers_MC_cff')
process.load('CmsHi.JetAnalysis.TrkAnalyzers_MC_cff')
process.load('CmsHi.JetAnalysis.EGammaAnalyzers_cff')

process.load("MitHig.PixelTrackletAnalyzer.METAnalyzer_cff")
process.load("CmsHi.JetAnalysis.pfcandAnalyzer_cfi")

process.load('CmsHi.JetAnalysis.rechitanalyzer_cfi')
process.rechitAna = cms.Sequence(process.rechitanalyzer+process.pfTowers)

process.pfcandAnalyzer.skipCharged = False
process.pfcandAnalyzer.pfPtMin = 0
process.interestingTrackEcalDetIds.TrackCollection = cms.InputTag("generalTracks")

#process.load("HiMuonAlgos.HLTMuTree.hltMuTree_cfi")

#########################
# Track Analyzer
#########################
process.ppTrack.qualityStrings = cms.untracked.vstring('highPurity','highPuritySetWithPV')
process.ppTrack.doSimTrack = cms.untracked.bool(False)

# Muons 
process.load("MuTrig.HLTMuTree.hltMuTree_cfi")
process.muonTree = process.hltMuTree.clone()
process.muonTree.doGen = cms.untracked.bool(True)

process.load("CmsHi/HiHLTAlgos.hievtanalyzer_cfi")
process.hiEvtAnalyzer.doEvtPlane = cms.bool(True)

process.iterativeConePu5CaloJets.srcPVs = "offlinePrimaryVerticesWithBS"
process.iterativeCone5CaloJets.srcPVs = "offlinePrimaryVerticesWithBS"

process.particleFlowTmp.vertexCollection = cms.InputTag("offlinePrimaryVerticesWithBS")
process.rechitanalyzer.vtxSrc = cms.untracked.InputTag("offlinePrimaryVerticesWithBS")
process.rechitanalyzer.useJets = cms.untracked.bool(False)
process.pfTowers.useJets = cms.untracked.bool(False)

process.muonTree.vertices = cms.InputTag("offlinePrimaryVerticesWithBS")

process.hiEvtAnalyzer.Vertex = cms.InputTag("offlinePrimaryVerticesWithBS")
process.hiEvtAnalyzer.doEvtPlane = False

process.primaryVertexFilter.src = cms.InputTag("offlinePrimaryVerticesWithBS")

process.icPu5JetAnalyzer.hltTrgResults = cms.untracked.string('TriggerResults::hiForestAna2011')
process.akPu3PFJetAnalyzer.hltTrgResults = cms.untracked.string('TriggerResults::hiForestAna2011')

process.load("RecoHI.HiMuonAlgos.HiRecoMuon_cff")
process.muons.JetExtractorPSet.JetCollectionLabel = cms.InputTag("iterativeConePu5CaloJets")
process.hiTracks.cut = cms.string('quality("' + hiTrackQuality+  '")')

#process.load("edwenger.HiTrkEffAnalyzer.hitrkEffAnalyzer_cff")

process.cutsTPForFak.tracks = cms.untracked.InputTag('TrackingParticles')

#  Following is the reco before adding b-tagging -Matt

###########################################
# Here it is after including b-tagging -Matt

process.pfTrack.TrackQuality = cms.string(hiTrackQuality)

process.hiTracks.src = cms.InputTag("generalTracks")
process.hiCaloCompatibleGeneralTracksQuality.src = cms.InputTag("generalTracks")
process.hiGeneralTracksQuality.src = cms.InputTag("generalTracks")
process.hiSelectedTrackQuality.src = cms.InputTag("generalTracks")
process.hiCentrality.srcTracks = cms.InputTag("generalTracks")
process.hiCentrality.srcPixelTracks = cms.InputTag("pixelTracks")
process.hiCentrality.srcVertex = cms.InputTag("offlinePrimaryVerticesWithBS")
process.hitrkEffAnalyzer_akpu3pf.tracks = cms.untracked.InputTag("generalTracks")

process.hiTrackReco = cms.Sequence(process.hiTracks)
process.hiTrackDebug = cms.Sequence(process.hiSelectedTrackQuality)
process.trackeff_seq = cms.Sequence(process.hitrkEffAnalyzer_akpu3pf)

process.pfTrackElec.PrimaryVertexLabel = cms.InputTag("offlinePrimaryVerticesWithBS")
process.pfTrack.PrimaryVertexLabel = cms.InputTag("offlinePrimaryVerticesWithBS")
process.particleFlowTmp.vertexCollection = cms.InputTag("offlinePrimaryVerticesWithBS")
process.mvaElectrons.vertexTag = cms.InputTag("offlinePrimaryVerticesWithBS")

process.iterativeConePu5CaloJets.jetPtMin = cms.double(3.0)

process.reco_extra =  cms.Path(
    process.siPixelRecHits*
    process.hiCentrality
    *process.hiTrackReco
    *process.HiParticleFlowLocalReco
    *process.HiParticleFlowReco
#    *process.iterativeConePu5CaloJets
    *process.PFTowers
#    *process.ak5CaloJets
#    *process.ak3PFJets
)    
    

# seed the muons with iterative tracks
process.globalMuons.TrackerCollectionLabel = "generalTracks"
process.muons.TrackExtractorPSet.inputTrackCollection = "generalTracks"
process.muons.inputCollectionLabels = ["generalTracks", "globalMuons", "standAloneMuons:UpdatedAtVtx", "tevMuons:firstHit", "tevMuons:picky", "tevMuons:dyt"]

# set track collection to iterative tracking
process.pfTrack.TkColList = cms.VInputTag("generalTracks")

# End modifications to reco sequence -Matt
##########################################

process.reco_extra_jet    = cms.Path(#process.iterativeConePu5CaloJets *
                                     #process.iterativeCone5CaloJets *
                                     #process.recoAk1to6 *
                                     #process.ak1PFJets *
                                     #process.ak2PFJets *
                                     #process.ak3PFJets *
                                     #process.ak4PFJets *
                                     #process.ak5PFJets *
                                     #process.ak6PFJets *
                                     #process.ak1CaloJets *
                                     #process.ak2CaloJets *
                                     #process.ak3CaloJets *
                                     #process.ak4CaloJets *
                                     #process.ak5CaloJets *
                                     #process.ak6CaloJets *
                                     process.photon_extra_reco)
#process.gen_step          = cms.Path( process.hiGen )

###########################################
# Do regit and b-tagging

if doRegitForBjets:
    

    process.akPu3PFSelectedJets = cms.EDFilter("CandViewSelector",
                                               src = cms.InputTag("akPu3PFJets"),
                                               cut = cms.string("pt > 40. && eta > -2. && eta < 2")
                                               )
    
    
    process.load("RecoHI.HiTracking.hiRegitTracking_cff")
#    process.hiGeneralTrackFilter.recTracks = cms.InputTag("hiSelectedTracks")
        
    # Region optimized for b-jets
    process.hiRegitInitialStepSeeds.RegionFactoryPSet.RegionPSet.originRadius = 0.02
    process.hiRegitInitialStepSeeds.RegionFactoryPSet.RegionPSet.originHalfLength = 0.02
    process.hiRegitLowPtTripletStepSeeds.RegionFactoryPSet.RegionPSet.originRadius = 0.02
    process.hiRegitLowPtTripletStepSeeds.RegionFactoryPSet.RegionPSet.originHalfLength = 0.02
    process.hiRegitPixelPairStepSeeds.RegionFactoryPSet.RegionPSet.originRadius = 0.015
    process.hiRegitPixelPairStepSeeds.RegionFactoryPSet.RegionPSet.originHalfLength = 0.015
    process.hiRegitDetachedTripletStepSeeds.RegionFactoryPSet.RegionPSet.originRadius = 1.5
    process.hiRegitDetachedTripletStepSeeds.RegionFactoryPSet.RegionPSet.originHalfLength = 1.5
    process.hiRegitMixedTripletStepSeedsA.RegionFactoryPSet.RegionPSet.originRadius = 1.0
    process.hiRegitMixedTripletStepSeedsA.RegionFactoryPSet.RegionPSet.originHalfLength = 1.0
    process.hiRegitMixedTripletStepSeedsB.RegionFactoryPSet.RegionPSet.originRadius = 0.5
    process.hiRegitMixedTripletStepSeedsB.RegionFactoryPSet.RegionPSet.originHalfLength = 0.5

    process.hiRegitInitialStepSeeds.RegionFactoryPSet.RegionPSet.deltaPhiRegion = 0.3
    process.hiRegitInitialStepSeeds.RegionFactoryPSet.RegionPSet.deltaEtaRegion = 0.3
    process.hiRegitLowPtTripletStepSeeds.RegionFactoryPSet.RegionPSet.deltaPhiRegion = 0.3
    process.hiRegitLowPtTripletStepSeeds.RegionFactoryPSet.RegionPSet.deltaEtaRegion = 0.3
    process.hiRegitPixelPairStepSeeds.RegionFactoryPSet.RegionPSet.deltaPhiRegion = 0.3
    process.hiRegitPixelPairStepSeeds.RegionFactoryPSet.RegionPSet.deltaEtaRegion = 0.3
    process.hiRegitDetachedTripletStepSeeds.RegionFactoryPSet.RegionPSet.deltaPhiRegion = 0.3
    process.hiRegitDetachedTripletStepSeeds.RegionFactoryPSet.RegionPSet.deltaEtaRegion = 0.3
    process.hiRegitMixedTripletStepSeedsA.RegionFactoryPSet.RegionPSet.deltaPhiRegion = 0.3
    process.hiRegitMixedTripletStepSeedsA.RegionFactoryPSet.RegionPSet.deltaEtaRegion = 0.3
    process.hiRegitMixedTripletStepSeedsB.RegionFactoryPSet.RegionPSet.deltaPhiRegion = 0.3
    process.hiRegitMixedTripletStepSeedsB.RegionFactoryPSet.RegionPSet.deltaEtaRegion = 0.3

    process.hiRegitInitialStepSeeds.RegionFactoryPSet.RegionPSet.JetSrc = cms.InputTag("akPu3PFSelectedJets")
    process.hiRegitLowPtTripletStepSeeds.RegionFactoryPSet.RegionPSet.JetSrc = cms.InputTag("akPu3PFSelectedJets")
    process.hiRegitPixelPairStepSeeds.RegionFactoryPSet.RegionPSet.JetSrc = cms.InputTag("akPu3PFSelectedJets")
    process.hiRegitDetachedTripletStepSeeds.RegionFactoryPSet.RegionPSet.JetSrc = cms.InputTag("akPu3PFSelectedJets")
    process.hiRegitMixedTripletStepSeedsA.RegionFactoryPSet.RegionPSet.JetSrc = cms.InputTag("akPu3PFSelectedJets")
    process.hiRegitMixedTripletStepSeedsB.RegionFactoryPSet.RegionPSet.JetSrc = cms.InputTag("akPu3PFSelectedJets")


    # merge the regit with the global tracking
    process.load("RecoHI.HiTracking.MergeRegit_cff")

    process.hiGeneralAndRegitTracks.TrackProducer1 = 'generalTracks'

    # redo the muons, too to get the displaced muons in jets
    process.regGlobalMuons = process.globalMuons.clone(
        TrackerCollectionLabel = "hiGeneralAndRegitTracks"
        )
    process.regGlbTrackQual = process.glbTrackQual.clone(
        InputCollection = "regGlobalMuons",
        InputLinksCollection = "regGlobalMuons"
        )
    process.regMuons = process.muons.clone()
    process.regMuons.TrackExtractorPSet.inputTrackCollection = "hiGeneralAndRegitTracks"
    process.regMuons.globalTrackQualityInputTag = "regGlbTrackQual"
    process.regMuons.inputCollectionLabels = cms.VInputTag("hiGeneralAndRegitTracks", "regGlobalMuons", "standAloneMuons:UpdatedAtVtx", "tevMuons:firstHit", "tevMuons:picky", "tevMuons:dyt")
    
    process.regMuonReco = cms.Sequence(
        process.regGlobalMuons*
        process.regGlbTrackQual*
        process.regMuons
        )
    
    # re-run particle flow to do the calo-matching
    process.pfRegTrack = process.pfTrack.clone(TkColList = cms.VInputTag("hiGeneralAndRegitTracks"))
    process.pfRegBlock = process.particleFlowBlock.clone()
    process.regParticleFlow = process.particleFlowTmp.clone()
        
    process.pfRegTrack.GsfTracksInEvents = False
    process.regParticleFlow.usePFElectrons = False
    process.regParticleFlow.muons = "regMuons"
        
    process.hiRegPF =  cms.Sequence(
        process.pfRegTrack
        *process.pfRegBlock
        *process.regParticleFlow
    )

    process.load("RecoHI.HiTracking.HICaloCompatibleTracks_cff")
    process.hiGeneralAndRegitCaloMatchedTracks = process.hiCaloCompatibleTracks.clone(    
        srcTracks = 'hiGeneralAndRegitTracks',
        srcPFCands = 'regParticleFlow'
        )
        
    process.hiCaloMatchFilteredTracks = cms.EDFilter("TrackSelector",
                                                     src = cms.InputTag("hiGeneralAndRegitCaloMatchedTracks"),
                                                     cut = cms.string(
        'quality("highPuritySetWithPV") && pt > 1')                                                                                            
                                                     )
    
    
    process.regionalTracking = cms.Path(
        process.akPu3PFSelectedJets *
        process.hiRegitTracking *
        process.hiGeneralAndRegitTracks *
        process.regMuonReco *
        process.hiRegPF *
        process.hiGeneralAndRegitCaloMatchedTracks *
        process.hiCaloMatchFilteredTracks
        )
    
    
    process.icPu5SecondaryVertexTagInfos.trackSelection.qualityClass = 'any'
    process.akPu3PFSecondaryVertexTagInfos.trackSelection.qualityClass = 'any'
    process.icPu5JetTracksAssociatorAtVertex.tracks = cms.InputTag("hiCaloMatchFilteredTracks")
    process.akPu3PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("hiCaloMatchFilteredTracks")

    process.akPu3PFpatJets.addAssociatedTracks = True
    process.akPu3PFpatJets.addTagInfos = True
    process.akPu3PFpatJets.addBTagInfo         = True
    process.akPu3PFpatJets.addDiscriminators   = True
    process.akPu3PFpatJets.getJetMCFlavour     = True


    process.akPu3PFpatJets.tagInfoSources = cms.VInputTag(
        cms.InputTag("akPu3PFImpactParameterTagInfos"),
        cms.InputTag("akPu3PFGhostTrackVertexTagInfos"),
        cms.InputTag("akPu3PFSecondaryVertexTagInfos"),
        cms.InputTag("akPu3PFSoftMuonTagInfos"),
        )


# end btagging mods, expect for pat replace just below -Matt
##########################################

#process.load('JetMETCorrections.Type1MET.caloMETCorrections_cff')
#process.load('JetMETCorrections.Type1MET.pfMETCorrections_cff')
#process.load('JetMETCorrections.Configuration.JetCorrectionCondDB_cff')
#process.load('JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff')

#process.ak5Calocorr = cms.EDProducer("JetCorrFactorsProducer",
#     emf = cms.bool(False),
#     src = cms.InputTag("ak5CaloJets"),
#     payload = cms.string('AK5Calo'),
#     levels = cms.vstring(
#         'L1Offset', 'L2Relative', 'L3Absolute'#, 'L5Flavor', 'L7Parton'
#     ),
#     flavorType = cms.string('J'), ## alternatively use 'T'
#     useNPV = cms.bool(True),
#     primaryVertices = cms.InputTag('offlinePrimaryVertices'),
#     useRho = cms.bool(False),
#     rho = cms.InputTag('kt6PFJets', 'rho')
#)
#process.ak5PFcorr = cms.EDProducer("JetCorrFactorsProducer",
#     emf = cms.bool(False),
#     src = cms.InputTag("ak5PFJets"),
#     payload = cms.string('AK5PF'),
#     levels = cms.vstring(
#         'L1Offset', 'L2Relative', 'L3Absolute'#, 'L5Flavor', 'L7Parton'
#     ),
#     flavorType = cms.string('J'), ## alternatively use 'T'
#     useNPV = cms.bool(True),
#     primaryVertices = cms.InputTag('offlinePrimaryVertices'),
#     useRho = cms.bool(False),
#     rho = cms.InputTag('kt6PFJets', 'rho')
#)

process.makeppJets = cms.Sequence(
   process.ak5PFcorr+process.ak5PFpatJets+
   process.ak5Calocorr+process.ak5CalopatJets
)

process.pat_step          = cms.Path(#process.makeHeavyIonJets +
                                     process.makeppJets +
                                     process.makeHeavyIonPhotons
                                     )

# change to btagging pat sequence
if doRegitForBjets:
    process.pat_step.replace(process.akPu3PFpatSequence,process.akPu3PFpatSequence_withBtagging)
# Note that for data you need: akPu3PFpatSequence_withBtagging_data
    
process.pat_step.remove(process.interestingTrackEcalDetIds)
process.photonMatch.matched = cms.InputTag("hiGenParticles")
process.pat_step.remove(process.photonMatch)
process.cleanPhotons.primaryVertexProducer = cms.string('offlinePrimaryVerticesWithBS') 

process.patPhotons.addPhotonID = cms.bool(False)
#process.makeHeavyIonPhotons)
process.extrapatstep = cms.Path(process.selectedPatPhotons)

process.multiPhotonAnalyzer.GammaEtaMax = cms.untracked.double(100)
process.multiPhotonAnalyzer.GammaPtMin = cms.untracked.double(10)

process.ak5PFJetAnalyzer.fillGenJets = cms.untracked.bool(False)
process.ak5PFJetAnalyzer.isMC = cms.untracked.bool(False)
process.ak5PFJetAnalyzer.jetTag = cms.InputTag("ak3PFpatJets")
process.ak5PFJetAnalyzer.matchTag = cms.untracked.InputTag("ak5CalopatJets")

process.ak5CaloJetAnalyzer.fillGenJets = cms.untracked.bool(False)
process.ak5CaloJetAnalyzer.isMC = cms.untracked.bool(False)
process.ak5CaloJetAnalyzer.jetTag = cms.InputTag("ak5CalopatJets")
process.ak5CaloJetAnalyzer.matchTag = cms.untracked.InputTag("ak5PFpatJets")


process.ana_step          = cms.Path( 
#process.genpana +
                                      process.hcalNoise +
                                      #process.jetAnalyzers +                                      
                                      #process.ak5PFJetAnalyzer +
                                      #process.ak5CaloJetAnalyzer +
                                      process.ak5CaloJetAnalyzer +
#                                      process.ak5PFJetAnalyzer +
                                      process.multiPhotonAnalyzer +
#                                      process.HiGenParticleAna +
#                                      process.cutsTPForFak +
#                                      process.cutsTPForEff +
#                                      process.trackeff_seq+
                                      process.ppTrack +

#                                      process.pfcandAnalyzer +
                                      process.rechitAna +
                                      process.met * process.anaMET +
				      process.muonTree +
				      process.hiEvtAnalyzer +
#                                      process.randomCones +
                                      process.HiForest
                                      )


process.hfPosFilter2 = cms.EDFilter("CandCountFilter",
    src = cms.InputTag("hfPosTowers"),
    minNumber = cms.uint32(2)
)

process.hfNegFilter2 = cms.EDFilter("CandCountFilter",
    src = cms.InputTag("hfNegTowers"),
    minNumber = cms.uint32(2)
)
        

process.phltJetHI = cms.Path( process.hltJetHI )
process.pcollisionEventSelection = cms.Path(process.collisionEventSelection)
process.pHBHENoiseFilter = cms.Path( process.HBHENoiseFilter )
process.phiEcalRecHitSpikeFilter = cms.Path(process.hiEcalRecHitSpikeFilter )
#process.ppreTrgTest = cms.Path(process.preTrgTest )
#process.pminBiasBscFilter = cms.Path(process.minBiasBscFilter )
#process.ppostTrgTest = cms.Path(process.postTrgTest )
#process.phfCoincFilter = cms.Path(process.hfCoincFilter )
#process.ppurityFractionFilter = cms.Path(process.purityFractionFilter )

process.phfPosFilter3 = cms.Path(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfPosFilter3)
process.phfNegFilter3 = cms.Path(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfNegFilter3)
process.phfPosFilter2 = cms.Path(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfPosFilter2)
process.phfNegFilter2 = cms.Path(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfNegFilter2)
process.phfPosFilter1 = cms.Path(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfPosFilter)
process.phfNegFilter1 = cms.Path(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfNegFilter)
process.phltPixelClusterShapeFilter = cms.Path(process.siPixelRecHits+process.hltPixelClusterShapeFilter)
process.pprimaryvertexFilter = cms.Path(process.primaryVertexFilter)


# Customization
from CmsHi.JetAnalysis.customise_cfi import *
setPhotonObject(process,"cleanPhotons")

process.load('L1Trigger.Configuration.L1Extra_cff')
process.load('CmsHi.HiHLTAlgos.hltanalysis_cff')

process.hltanalysis.hltresults = cms.InputTag("TriggerResults","","HLT")
process.hltanalysis.dummyBranches = ()
process.hltAna = cms.EndPath(process.hltanalysis)
process.reco_extra*=process.L1Extra

process.pAna = cms.EndPath(process.skimanalysis)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.schedule = cms.Schedule(process.reco_extra, process.reco_extra_jet, process.pat_step, process.extrapatstep, process.ana_step, process.phltJetHI,process.pcollisionEventSelection,process.pHBHENoiseFilter,process.phiEcalRecHitSpikeFilter,process.phfPosFilter1,process.phfPosFilter2,process.phfPosFilter3,process.phfNegFilter1,process.phfNegFilter2,process.phfNegFilter3,process.phltPixelClusterShapeFilter,process.pprimaryvertexFilter,process.hltAna,process.pAna)

process.HLTSchedule.extend(process.schedule)



########### random number seed

#####################################################################################
# Edm Output
#####################################################################################

#process.out = cms.OutputModule("PoolOutputModule",
#                               fileName = cms.untracked.string("output.root")
#                               )
#process.save = cms.EndPath(process.out)
