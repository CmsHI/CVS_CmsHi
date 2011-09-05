import FWCore.ParameterSet.Config as cms
MuSkimContent = cms.PSet(
  outputCommands = cms.untracked.vstring(
    #'keep *',
    
    'keep *_generator_*_*',
    'keep *_genParticles_*_*',
    'keep *_hiGenParticles_*_*',
    'keep *_hiCentrality_*_*',
    'keep *_hiEvtPlane_*_*',
    'keep *_standAloneMuons_*_*',
    'keep *_hiGlobalPrimTracks_*_*',
    'keep *_hiSelectedTracks_*_*',
    'keep *_hiPixelAdaptiveVertex_*_*',
    'keep *_hiPixelMedianVertex_*_*',
    'keep *_hiSelectedVertex_*_*',
    'keep *_globalMuons_*_*',
    'keep patMuons_*_*_*',
    'keep *_hfreco_*_*',
    'keep *_horeco_*_*',
    'keep *_zdcreco_*_*',
    'keep recoMuons_muons_*_*',
    'keep *_goodMuons_*_*',
    'keep *_goodGlobalMuons_*_*',
    'keep *_goodSTAMuons_*_*',
    'keep *_TriggerResults_*_HLT'
  )
)



