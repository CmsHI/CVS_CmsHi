import FWCore.ParameterSet.VarParsing as VarParsing
ivars = VarParsing.VarParsing('standard')

ivars.files = [
'file:/net/hisrv0001/home/yetkin/hibat0007/aod/JulyExercise/MinBias0709/MinBias0709_runs11to20.root',
'file:/net/hisrv0001/home/yetkin/hibat0007/aod/JulyExercise/MinBias0709/MinBias0709_runs1to10.root',
'file:/net/hisrv0001/home/yetkin/hibat0007/aod/JulyExercise/MinBias0709/MinBias0709_runs1to5.root',
'file:/net/hisrv0001/home/yetkin/hibat0007/aod/JulyExercise/MinBias0709/MinBias0709_runs21to30.root',
'file:/net/hisrv0001/home/yetkin/hibat0007/aod/JulyExercise/MinBias0709/MinBias0709_runs31to40.root',
'file:/net/hisrv0001/home/yetkin/hibat0007/aod/JulyExercise/MinBias0709/MinBias0709_runs41to50.root',
'file:/net/hisrv0001/home/yetkin/hibat0007/aod/JulyExercise/MinBias0709/MinBias0709_runs51to100.root'
    ]

'''
ivars.files = [
        'file:/net/hisrv0001/home/yetkin/pstore02/reco/NoZSP/local2/Hydjet_MinBias_2760GeV_d20100628/Hydjet_MinBias_2760GeV_runs101to200.root',
            'file:/net/hisrv0001/home/yetkin/pstore02/reco/NoZSP/local2/Hydjet_MinBias_2760GeV_d20100628/Hydjet_MinBias_2760GeV_runs1to1.root',
            'file:/net/hisrv0001/home/yetkin/pstore02/reco/NoZSP/local2/Hydjet_MinBias_2760GeV_d20100628/Hydjet_MinBias_2760GeV_runs1to100.root',
            'file:/net/hisrv0001/home/yetkin/pstore02/reco/NoZSP/local2/Hydjet_MinBias_2760GeV_d20100628/Hydjet_MinBias_2760GeV_runs201to300.root',
            'file:/net/hisrv0001/home/yetkin/pstore02/reco/NoZSP/local2/Hydjet_MinBias_2760GeV_d20100628/Hydjet_MinBias_2760GeV_runs301to400.root'
            ]
'''

ivars.output = 'towers_data02.root'

ivars.maxEvents = -1

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
process.load('Configuration/StandardSequences/ReconstructionHeavyIons_cff')

process.RandomNumberGeneratorService.bkg4Jets = cms.PSet(initialSeed = cms.untracked.uint32(ivars.randomNumber),
                                                         engineName = cms.untracked.string('HepJamesRandom') )
process.RandomNumberGeneratorService.bkg5Jets = process.RandomNumberGeneratorService.bkg4Jets.clone()
process.RandomNumberGeneratorService.bkg6Jets = process.RandomNumberGeneratorService.bkg4Jets.clone()
process.RandomNumberGeneratorService.bkg7Jets = process.RandomNumberGeneratorService.bkg4Jets.clone()

from RecoJets.JetProducers.CaloJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

process.bkg4Jets = cms.EDProducer(
#    "JetAlgorithmAnalyzer",
  "BackgroundJetProducer",
  CaloJetParameters,
  AnomalousCellParameters,
  jetAlgorithm = cms.string("IterativeCone"),
  rParam       = cms.double(0.4),
  avoidNegative = cms.bool(False),
  subtractorName = cms.string("MultipleAlgoIterator")
  )

process.bkg4Jets.doPUOffsetCorr = True
process.bkg4Jets.doPVCorrection = False
process.bkg4Jets.jetPtMin = 10
process.bkg4Jets.radiusPU = 0.4

process.bkg5Jets = process.bkg4Jets.clone()
process.bkg5Jets.rParam = 0.5
process.bkg5Jets.radiusPU = 0.5

process.bkg6Jets = process.bkg4Jets.clone()
process.bkg6Jets.rParam = 0.6
process.bkg6Jets.radiusPU = 0.6

process.bkg7Jets = process.bkg4Jets.clone()
process.bkg7Jets.rParam = 0.7
process.bkg7Jets.radiusPU = 0.7

process.bkgJets = cms.Sequence(process.bkg5Jets)

process.ana = cms.EDAnalyzer('MinBiasTowerAnalyzer',
                             jetTowersMean = cms.untracked.vdouble(21,21.4,21.4,22,22.5,21.3,17.4,16.1,11.5,0),
                             jetTowersRMS = cms.untracked.vdouble(5.4,5.2,5.2,5.4,5.8,5.8,4.9,4.1,3.2,0),
                             fakeJetSrc = cms.untracked.InputTag('bkg5Jets'),
                             patJetSrc = cms.untracked.InputTag('patJets')                             
                             )

process.load("CondCore.DBCommon.CondDBCommon_cfi")
process.CondDBCommon.connect = "sqlite_file:/net/hisrv0001/home/yetkin/cvs/UserCode/CmsHi/JulyExercise/data/CentralityTables.db"
process.PoolDBESSource = cms.ESSource("PoolDBESSource",
                                      process.CondDBCommon,
                                      toGet = cms.VPSet(cms.PSet(record = cms.string('HeavyIonRcd'),
                                                                 tag = cms.string('HFhits10_DataJulyExercise_AMPT2760GeV_MC_37Y_V5_NZS_v0')
                                                                 )
                                                        )
                                      )

process.p = cms.Path(
    process.ak5CaloJets *
    process.kt4CaloJets *
    process.bkgJets *
    process.ana
    )
#process.out_step = cms.EndPath(process.output)



