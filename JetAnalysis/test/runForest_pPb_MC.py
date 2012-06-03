
import FWCore.ParameterSet.VarParsing as VarParsing

ivars = VarParsing.VarParsing('python')

ivars.register ('randomNumber',
                1,
                ivars.multiplicity.singleton,
                ivars.varType.int,
                "Random Seed")

ivars.randomNumber = 1
#ivars.inputFiles = "file:/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet50/reco_v0/set2_random70000_HydjetDrum_362.root"
#ivars.inputFiles = "file:/mnt/hadoop/cms/store/user/yetkin/MC_Production/Pythia80_HydjetDrum_mix01/RECO/set1_random30000_HydjetDrum_12.root"

ivars.inputFiles = "file:/mnt/hadoop/cms/store/user/davidlw/AMPT_pPb/RECO/file_208.root"
ivars.outputFile = './forest_pPb_test0.root'

ivars.parseArguments()


import FWCore.ParameterSet.Config as cms

process = cms.Process('hiForestAna2011')

process.options = cms.untracked.PSet(
   # wantSummary = cms.untracked.bool(True)
)


trackTag = "generalTracks"
vertexTag = "offlinePrimaryVertices"
hiTrackQuality = "highPurity"              # iterative tracks
#hiTrackQuality = "highPuritySetWithPV"    # calo-matched tracks

doElectrons = False
doRegitForBjets = False


#####################################################################################

process.load("CmsHi.JetAnalysis.HiForest_cff")
process.HiForest.inputLines = cms.vstring("HiForest V2",
                                          "PF : "+trackTag,
                                          "EP Flattening OFF",
                                          "Electrons OFF",
                                          "Preshower OFF"
                                          )

#####################################################################################
# Input source
#####################################################################################

process.source = cms.Source("PoolSource",
                            skipEvents = cms.untracked.uint32(70),
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                            fileNames = cms.untracked.vstring(ivars.inputFiles))

# Number of events we want to process, -1 = all events
process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32(-1))


#####################################################################################
# Load some general stuff
#####################################################################################

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('RecoLocalTracker.SiPixelRecHits.PixelCPEESProducers_cff')
#process.load('MitHig.PixelTrackletAnalyzer.pixelHitAnalyzer_cfi')

# Data Global Tag 44x 
#process.GlobalTag.globaltag = 'GR_P_V27::All'

process.Timing = cms.Service("Timing")

# MC Global Tag 44x 
process.GlobalTag.globaltag = 'STARTHI44_V7::All'

# load centrality
from CmsHi.Analysis2010.CommonFunctions_cff import *
overrideCentrality(process)
process.HeavyIonGlobalParameters = cms.PSet(
	centralityVariable = cms.string("HFtowers"),
	nonDefaultGlauberModel = cms.string("Hydjet_Drum"),
	centralitySrc = cms.InputTag("hiCentrality")
	)

process.hiCentrality.pixelBarrelOnly = False
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
process.load("CmsHi/HiHLTAlgos.hievtanalyzer_cfi")


process.load('CmsHi.JetAnalysis.rechitanalyzer_cfi')
process.rechitAna = cms.Sequence(process.rechitanalyzer+process.pfTowers)

process.pfcandAnalyzer.skipCharged = False
process.pfcandAnalyzer.pfPtMin = 0
process.interestingTrackEcalDetIds.TrackCollection = cms.InputTag(trackTag)

#process.load("HiMuonAlgos.HLTMuTree.hltMuTree_cfi")

process.genpana = cms.EDAnalyzer("GenParticleCounter",
                                 src = cms.untracked.string("hiGenParticles"),
                                 doCentrality = cms.untracked.bool(False),
                                 VertexProducer = cms.untracked.string(vertexTag)
                                 )


process.primaryVertexFilter.src = vertexTag
process.hiCentrality.producePixelTracks = False
process.hiCentrality.srcTracks = trackTag
process.hiCentrality.srcVertex = vertexTag
process.particleFlowTmp.vertexCollection = vertexTag
process.iterativeConePu5CaloJets.srcPVs = vertexTag
process.iterativeCone5CaloJets.srcPVs = vertexTag

process.anaTrack.trackSrc = trackTag
process.anaTrack.vertexSrc = [vertexTag]
process.hiEvtAnalyzer.Vertex = vertexTag
process.cleanPhotons.primaryVertexProducer = vertexTag

process.rechitanalyzer.vtxSrc = cms.untracked.InputTag(vertexTag)
process.pfTowers.vtxSrc = cms.untracked.InputTag(vertexTag)

process.pfTrackElec.PrimaryVertexLabel = vertexTag

# Muons 
process.load("MuTrig.HLTMuTree.hltMuTree_cfi")
process.muonTree = process.hltMuTree.clone()
process.muonTree.doGen = cms.untracked.bool(True)

process.muonTree.vertices = vertexTag

# Event tree

# Not working for the moment..
#process.hiEvtAnalyzer.doMC = cms.bool(True)
process.hiEvtAnalyzer.doEvtPlane = cms.bool(True)

genTag="generator"
process.hiGenParticles.srcVector = cms.vstring(genTag)
process.icPu5JetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu1PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu2PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu3PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu4PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu5PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu6PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu1CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu2CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu3CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu4CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu5CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.akPu6CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak1PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak2PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak3PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak4PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak5PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak6PFJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak1CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak2CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak3CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak4CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak5CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)
process.ak6CaloJetAnalyzer.eventInfoTag = cms.InputTag(genTag)

process.icPu5JetAnalyzer.trackTag = trackTag
process.akPu1PFJetAnalyzer.trackTag = trackTag
process.akPu2PFJetAnalyzer.trackTag = trackTag
process.akPu3PFJetAnalyzer.trackTag = trackTag
process.akPu4PFJetAnalyzer.trackTag = trackTag
process.akPu5PFJetAnalyzer.trackTag = trackTag
process.akPu6PFJetAnalyzer.trackTag = trackTag

process.akPu1CaloJetAnalyzer.trackTag = trackTag
process.akPu2CaloJetAnalyzer.trackTag = trackTag
process.akPu3CaloJetAnalyzer.trackTag = trackTag
process.akPu4CaloJetAnalyzer.trackTag = trackTag
process.akPu5CaloJetAnalyzer.trackTag = trackTag
process.akPu6CaloJetAnalyzer.trackTag = trackTag

process.ak1PFJetAnalyzer.trackTag = trackTag
process.ak2PFJetAnalyzer.trackTag = trackTag
process.ak3PFJetAnalyzer.trackTag = trackTag
process.ak4PFJetAnalyzer.trackTag = trackTag
process.ak5PFJetAnalyzer.trackTag = trackTag
process.ak6PFJetAnalyzer.trackTag = trackTag

process.ak1CaloJetAnalyzer.trackTag = trackTag
process.ak2CaloJetAnalyzer.trackTag = trackTag
process.ak3CaloJetAnalyzer.trackTag = trackTag
process.ak4CaloJetAnalyzer.trackTag = trackTag
process.ak5CaloJetAnalyzer.trackTag = trackTag
process.ak6CaloJetAnalyzer.trackTag = trackTag

process.isoT11.track = trackTag
process.isoT12.track = trackTag
process.isoT13.track = trackTag
process.isoT14.track = trackTag
process.isoT21.track = trackTag
process.isoT22.track = trackTag
process.isoT23.track = trackTag
process.isoT24.track = trackTag
process.isoT31.track = trackTag
process.isoT32.track = trackTag
process.isoT33.track = trackTag
process.isoT34.track = trackTag
process.isoT41.track = trackTag
process.isoT42.track = trackTag
process.isoT43.track = trackTag
process.isoT44.track = trackTag
process.isoDR11.track = trackTag
process.isoDR12.track = trackTag
process.isoDR13.track = trackTag
process.isoDR14.track = trackTag
process.isoDR21.track = trackTag
process.isoDR22.track = trackTag
process.isoDR23.track = trackTag
process.isoDR24.track = trackTag
process.isoDR31.track = trackTag
process.isoDR32.track = trackTag
process.isoDR33.track = trackTag
process.isoDR34.track = trackTag
process.isoDR41.track = trackTag
process.isoDR42.track = trackTag
process.isoDR43.track = trackTag
process.isoDR44.track = trackTag

process.multiPhotonAnalyzer.GenEventScale = cms.InputTag(genTag)
process.multiPhotonAnalyzer.HepMCProducer = cms.InputTag(genTag)



process.trackeff_seq = cms.Sequence(process.cutsTPForFakPxl+process.cutsTPForEffPxl+process.hitrkEffAnalyzer_MergedSelected)
process.hitrkEffAnalyzer_MergedSelected.tracks = trackTag
process.hitrkEffAnalyzer_MergedSelected.vertices = vertexTag


process.icPu5JetAnalyzer.hltTrgResults = cms.untracked.string('TriggerResults::RECO')
process.akPu3PFJetAnalyzer.hltTrgResults = cms.untracked.string('TriggerResults::RECO')


#Commented by Yen-Jie
#process.hiPixelAdaptiveVertex.useBeamConstraint = False

process.HiGenParticleAna = cms.EDAnalyzer("HiGenAnalyzer")
process.HiGenParticleAna.src= cms.untracked.InputTag("hiGenParticles")
process.HiGenParticleAna.chargedOnly = cms.untracked.bool(False)
process.HiGenParticleAna.ptMin = cms.untracked.double(0.5)

process.load("RecoHI.HiMuonAlgos.HiRecoMuon_cff")
process.muons.JetExtractorPSet.JetCollectionLabel = cms.InputTag("iterativeConePu5CaloJets")
process.hiTracks.cut = cms.string('quality("' + hiTrackQuality+  '")')

#process.load("edwenger.HiTrkEffAnalyzer.hitrkEffAnalyzer_cff")

process.cutsTPForFak.tracks = cms.untracked.InputTag('TrackingParticles')

#  Following is the reco before adding b-tagging -Matt

###########################################
# Here it is after including b-tagging -Matt

process.pfTrack.TrackQuality = cms.string(hiTrackQuality)

process.reco_extra =  cms.Path(
    process.siPixelRecHits *
    process.hiCentrality *
#    process.hiTrackReco
#    +process.hiTrackDebug
    
    #        *process.muonRecoPbPb
    process.HiParticleFlowLocalReco
    *process.HiParticleFlowReco
    *process.iterativeConePu5CaloJets
    *process.PFTowers
)    
    

# seed the muons with iterative tracks
process.globalMuons.TrackerCollectionLabel = trackTag
process.muons.TrackExtractorPSet.inputTrackCollection = trackTag
process.muons.inputCollectionLabels = [trackTag, "globalMuons", "standAloneMuons:UpdatedAtVtx", "tevMuons:firstHit", "tevMuons:picky", "tevMuons:dyt"]

# set track collection to iterative tracking
process.pfTrack.TkColList = cms.VInputTag(trackTag)


# End modifications to reco sequence -Matt
##########################################

process.reco_extra_jet    = cms.Path(process.iterativeConePu5CaloJets *
                                     process.iterativeCone5CaloJets *
                                     process.recoAk1to6 *
                                     process.photon_extra_reco)
process.gen_step          = cms.Path( process.hiGen )

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

    process.hiGeneralAndRegitTracks.TrackProducer1 = trackTag

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

process.pat_step          = cms.Path(process.makeHeavyIonJets +
                                     process.makeHeavyIonPhotons
                                     )

# change to btagging pat sequence
if doRegitForBjets:
    process.pat_step.replace(process.akPu3PFpatSequence,process.akPu3PFpatSequence_withBtagging)
# Note that for data you need: akPu3PFpatSequence_withBtagging_data
    
process.pat_step.remove(process.interestingTrackEcalDetIds)
process.photonMatch.matched = cms.InputTag("hiGenParticles")
#process.pat_step.remove(process.photonMatch)
#+ process.patPhotons)

process.patPhotons.addPhotonID = cms.bool(False)
#process.makeHeavyIonPhotons)
process.extrapatstep = cms.Path(process.selectedPatPhotons)

process.multiPhotonAnalyzer.GammaEtaMax = cms.untracked.double(100)
process.multiPhotonAnalyzer.GammaPtMin = cms.untracked.double(10)
process.ana_step          = cms.Path( process.genpana +
                                      process.hcalNoise +
                                      process.jetAnalyzers +                                      
                                      process.multiPhotonAnalyzer +
                                      process.HiGenParticleAna +
#                                      process.cutsTPForFak +
#                                      process.cutsTPForEff +
                                      process.trackeff_seq+

                                      process.anaTrack + 
                                      process.pfcandAnalyzer +
                                      process.rechitAna +
                                      process.met * process.anaMET +
				      process.muonTree +
				      process.hiEvtAnalyzer +
#                                      process.randomCones +
                                      process.HiForest
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

# Customization
from CmsHi.JetAnalysis.customise_cfi import *
setPhotonObject(process,"cleanPhotons")

process.load('L1Trigger.Configuration.L1Extra_cff')
process.load('CmsHi.HiHLTAlgos.hltanalysis_cff')

process.hltanalysis.hltresults = cms.InputTag("TriggerResults","","RECO")
process.hltAna = cms.Path(process.hltanalysis)
process.pAna = cms.EndPath(process.skimanalysis)
process.reco_extra*=process.L1Extra


########### random number seed

#####################################################################################
# Edm Output
#####################################################################################

#process.out = cms.OutputModule("PoolOutputModule",
#                               fileName = cms.untracked.string("output.root")
#                               )
#process.save = cms.EndPath(process.out)
