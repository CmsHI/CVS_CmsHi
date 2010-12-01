import FWCore.ParameterSet.Config as cms

##### event content for heavy-ion analysis objects
from Configuration.EventContent.EventContentHeavyIons_cff import *
from RecoHI.HiMuonAlgos.RecoHiMuon_EventContent_cff import *


hiCommon = cms.PSet(
    outputCommands = cms.untracked.vstring(#'drop *',
                                           'keep *_TriggerResults_*_HLT',
                                           'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
                                           'keep recoVertexs_hiSelectedVertex_*_*',
                                           'keep *_heavyIon_*_*',
                                           'keep *_hiCentrality_*_*',
                                           'keep *_hiEvtPlane_*_*'
                                           )
    )




DiMuonContent = hiCommon.clone()
DiMuonContent.outputCommands.extend(cms.untracked.vstring(
    #'keep *',    
    
    'keep *_offlineBeamSpot_*_*',
    'keep *_hiSelectedTracks_*_*',
    'keep *_towerMaker_*_*',
    'keep *_hiGlobalPrimTracks_*_*',
    'keep *_hiPixel3PrimTracks_*_*',


    'keep *_generator_*_*',
    'keep *_genParticles_*_*',
    'keep *_hiGenParticles_*_*',
    'keep *_hiSignal_*_*',
    'keep patMuons_*_*_*',
    'keep recoMuons_muons_*_*',
    'keep *_dimuonsGlobal_*_*',
    'keep *_dimuonsGlobalSTA_*_*',
    'keep *_dimuonsGlobalTrk_*_*',
    'keep *_dimuonsSTA_*_*',
    'keep *_dimuonsTrk_*_*',
    'keep *_dimuonsGlobalSameCharge_*_*',
    'keep *_dimuonsGlobalSTASameCharge_*_*',
    'keep *_dimuonsGlobalTrkSameCharge_*_*',
    'keep *_dimuonsTrkSameCharge_*_*',
    'keep *_dimuonsSTASameCharge_*_*',
    'keep *_GenDimuons_*_*',
    'keep *_dimuons_*_*',
    'keep *_dimuonsSameCharge_*_*',
    'keep *_ditracksSiliconTrk_*_*')
    )

DiMuonContent.outputCommands.extend(RecoMuonAOD.outputCommands)
DiMuonContent.outputCommands.extend(RecoHiMuonAOD.outputCommands)



