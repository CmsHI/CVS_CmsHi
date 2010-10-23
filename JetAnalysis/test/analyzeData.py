
import FWCore.ParameterSet.VarParsing as VarParsing
ivars = VarParsing.VarParsing('standard')

ivars.files = [
# ZS Data:
#    'rfio:/castor/cern.ch/cms/store/data/Run2010B/HeavyIonTest/RECO/PromptReco-v2/000/146/421/FE6B3366-B3C6-DF11-9905-0030487CD812.root',
#NZS Data:
    'rfio:/castor/cern.ch/cms/store/data/Run2010B/HeavyIonTest/RECO/PromptReco-v2/000/146/421/FE8B65B2-ABC6-DF11-8534-0030487CD7E0.root',
    ]


ivars.output = 'Data.root'

ivars.maxEvents = 10

ivars.register ('randomNumber',
                mult=ivars.multiplicity.singleton,
                info="for testing")
ivars.randomNumber=5
ivars.parseArguments()

import FWCore.ParameterSet.Config as cms

process = cms.Process('ANALYSIS')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(ivars.maxEvents)   
    )

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(ivars.files)
                          )

process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string('plots_' + ivars.output)
                                   )


process.output = cms.OutputModule("PoolOutputModule",
                                   outputCommands = cms.untracked.vstring("keep *_*_*_*"),
                                  fileName = cms.untracked.string(ivars.output)
                                  )


process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/Services_cff')

process.ana = cms.EDAnalyzer('MinBiasTowerAnalyzer',
                             nBins = cms.untracked.int32(1),
                             towersSrc =  cms.untracked.InputTag("towerMaker","","RECO"),
                             doRandomCone = cms.untracked.bool(False),
                             doEvtPlane = cms.untracked.bool(False),
                             excludeJets = cms.untracked.bool(True),
                             isSignal = cms.untracked.bool(True),
                             doMC = cms.untracked.bool(False),
                             doTowers = cms.untracked.bool(True),
                             doRecHits = cms.untracked.bool(True),
                             ecalEBRecHitSrc = cms.untracked.InputTag("ecalRecHit","EcalRecHitsEB","RECO"),
                             ecalEERecHitSrc = cms.untracked.InputTag("ecalRecHit","EcalRecHitsEE","RECO")
                             )

process.pana = cms.Path(
    process.ana
    )
