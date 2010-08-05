import FWCore.ParameterSet.Config as cms

process = cms.Process("HLTAna")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'rfio:/castor/cern.ch/user/d/dmoon/cms370/Hydjet_MinBias_2.76TeV_Z0_Emb_Reco/Hydjet_MinBias_2.76TeV_Z0Emb_Reco_e10_02_176.root'
    )
)

process.hltL3MuonCandidate = cms.EDProducer('L3GenMuonCandidateProducer',
        TriggerResults = cms.InputTag("TriggerResults","","HISIGNAL"),
        HLT_Path = cms.string("HLT_HIDoubleMu")
        #HLT_Path = cms.string("L1_DoubleMuOpen")
)

process.out = cms.OutputModule("PoolOutputModule",
        outputCommands = cms.untracked.vstring(
            'drop *',
            'keep *_*_*_HLTAna'),
    fileName = cms.untracked.string('test.root')
)
  
process.p = cms.Path(process.hltL3MuonCandidate)

process.e = cms.EndPath(process.out)
