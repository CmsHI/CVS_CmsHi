'''
Template configuration for skimming the global (HI group level) reconstructed hi-events/files into smaller edm files that contain only the information needed by any muon analsyis
At this same step, we reconstruct and keep in the edm file the patMuons
'''

import FWCore.ParameterSet.Config as cms
process = cms.Process("MUONSKIMPAT")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore.MessageLogger.MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/StandardSequences/ReconstructionHeavyIons_cff')

process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('HeavyIonsAnalysis/Configuration/analysisEventContent_cff')


process.MessageLogger = cms.Service("MessageLogger",
                                    cout = cms.untracked.PSet(
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(0) ## kill all messages in the log
            )
        ),
                                    destinations = cms.untracked.vstring('cout')
                                    )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/d/dmoon/cms370/Hydjet_MinBias_2.76TeV_Z0_Emb_Reco/Hydjet_MinBias_2.76TeV_Z0Emb_Reco_e10_05_908.root')
#rfio:///castor/cern.ch/user/m/mironov/cmssw370/digireco/root/z0_sgn_hitrk_f0.root')
                            )

process.GlobalTag.globaltag = 'MC_37Y_V5::All'
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))


# =============== PAT sequence and settings =====================
process.load("PhysicsTools.PatAlgos.producersHeavyIons.heavyIonMuons_cff")
process.patMuons.embedCaloMETMuonCorrs = cms.bool(False)
process.patMuons.embedTcMETMuonCorrs   = cms.bool(False)
process.patMuons.useParticledFlow      = cms.bool(False)

# in case you do NOT want genMatching (deltaR) 
process.patMuons.addGenMatch      = cms.bool(False)
process.patMuons.embedGenMatch    = cms.bool(False)
# if want genMAtching and have a HI mixed sample: 
#process.muonMatch.matched         = cms.InputTag("hiGenParticles")


# ====== filter skimming
process.muonSelector = cms.EDFilter("MuonSelector",
                                    src = cms.InputTag("muons"),
                                    cut = cms.string("(isStandAloneMuon || isGlobalMuon || isTrackerMuon || isCaloMuon) && pt > 1."),
                                    filter = cms.bool(True)
                                    )
process.muonFilter = cms.EDFilter("MuonCountFilter",
                                  src = cms.InputTag("muonSelector"),
                                  minNumber = cms.uint32(1)
                                  )
process.muonskim = cms.Path(process.muonSelector*process.muonFilter)
#-------------------------------------------------------------------------------------
process.outputmuskim = cms.OutputModule("PoolOutputModule",
                                        outputCommands = process.muonSkimContent.outputCommands,
                                        fileName = cms.untracked.string("test_hitrk.root"),
                                        dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RAW-RECO')
        )             
                                        ,  SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('muonskim')
        )                         
                                        )


process.hiMuonPat     = cms.Path(process.patMuons)#process.makeHeavyIonMuons)
process.endjob_step   = cms.Path(process.endOfProcess)
process.out_step      = cms.EndPath(process.outputmuskim)

