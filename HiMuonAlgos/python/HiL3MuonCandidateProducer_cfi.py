import FWCore.ParameterSet.Config as cms

hltHIL3MuonCandidate = cms.EDProducer('L3GenMuonCandidateProducer',
    TriggerResults = cms.InputTag("TriggerResults","","*HLT*"),
    HLT_Path = cms.string("HLT_HIDoubleMu"), 
)


