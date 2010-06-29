import FWCore.ParameterSet.Config as cms

##### event content for heavy-ion analysis objects
from Configuration.EventContent.EventContentHeavyIons_cff import *

#jets
jetContent = cms.PSet(
    outputCommands = cms.untracked.vstring(
    'keep double*_*CaloJets_*_*',
    'drop recoCaloJets_*_*_*',
    'keep recoGenJets_*_*_*',
    'keep patJets_*_*_*'
    )
  )

jetContentExtended = jetContent.clone()
jetContentExtended.outputCommands.extend(cms.untracked.vstring('keep *_towerMaker_*_*'))

#tracks
trkContent = cms.PSet(
    outputCommands = cms.untracked.vstring(
      'keep *_offlineBeamSpot_*_*',
      'keep recoTracks_hiSelectedTracks_*_*',
      'keep recoTracks_hiPixel3PrimTracks_*_*' # low-fake selection to lower pt?
      )
    )

lightTrackContent = cms.PSet(
    outputCommands = cms.untracked.vstring(
    'keep *_offlineBeamSpot_*_*',
    'keep *_allTracks_*_*' # Selected Charged Candidates
    )
    )

#muons
muonContent = cms.PSet(
    outputCommands = cms.untracked.vstring(
      'keep patMuons_selected*_*_*'
      )
    )

muonContentExtended = muonContent.clone()
muonContentExtended.outputCommands.extend(RecoHiMuonAOD.outputCommands)

#photons
photonContent = cms.PSet(
    outputCommands = cms.untracked.vstring(
      'keep patPhotons_selected*_*_*'
      )
    )

photonContentExtended = photonContent.clone()
photonContentExtended.outputCommands.extend(RecoEgammaAOD.outputCommands)

#correlations
corrContent = cms.PSet(
    outputCommands = cms.untracked.vstring( 
      'keep recoRecoChargedCandidates_allTracks_*_*',
      'keep recoRecoChargedCandidates_allPxltracks_*_*'
      )
    )

#common
hiCommon = cms.PSet(
    outputCommands = cms.untracked.vstring('drop *',
      'keep *_TriggerResults_*_HLT',
      'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
      'keep recoVertexs_hiSelectedVertex_*_*',                              
      'keep *_heavyIon_*_*',
      'keep *_hiCentrality_*_*'
    )
)

##### combinations for specific skims

# HI PAG skim
hiAnalysisSkimContent = hiCommon.clone()
hiAnalysisSkimContent.outputCommands.extend(jetContentExtended.outputCommands)
hiAnalysisSkimContent.outputCommands.extend(trkContent.outputCommands)
hiAnalysisSkimContent.outputCommands.extend(muonContent.outputCommands)
hiAnalysisSkimContent.outputCommands.extend(photonContent.outputCommands)
hiAnalysisSkimContent.outputCommands.extend(corrContent.outputCommands)

# [highpt] skim
jetTrkSkimContent = hiCommon.clone()
jetTrkSkimContent.outputCommands.extend(jetContentExtended.outputCommands)
jetTrkSkimContent.outputCommands.extend(lightTrackContent.outputCommands)

# [dilepton] skim0
muonSkimContent = hiCommon.clone()
# include event content from RecoHI packages
muonSkimContent.outputCommands.extend(cms.untracked.vstring('keep patMuons_*_*_*'))
muonSkimContent.outputCommands.extend(RecoHiMuonRECO.outputCommands)
muonSkimContent.outputCommands.extend(RecoHiTrackerRECO.outputCommands)

# SKIM MC
muonSkimContentMC =  cms.PSet(
    outputCommands = cms.untracked.vstring('keep patMuons_*_*_*',
                                           'keep *_generator_*_*',
                                           'keep *_hiSignal_*_*',
                                           'keep *_genParticles_*_*'
                                           )
    )
muonSkimContentMC.outputCommands.extend(muonSkimContent.outputCommands)

#[dilepton] skim 1
muonTrkSkimContent = hiCommon.clone()  # trigger, L!, vertex,centrality, etc
muonTrkSkimContent.outputCommands.extend(muonContentExtended.outputCommands) # muon AOD
muonTrkSkimContent.outputCommands.extend(trkContent.outputCommands)
