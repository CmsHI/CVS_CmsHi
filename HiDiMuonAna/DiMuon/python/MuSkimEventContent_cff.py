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
    'keep *_globalMuons_*_*',
    'keep patMuons_*_*_*',
    'keep recoMuons_muons_*_*',
    'keep *_goodMuons_*_*',
    'keep *_goodGlobalMuons_*_*',
    'keep *_goodSTAMuons_*_*',
    'keep *_TriggerResults_*_*'
  )
)
