import FWCore.ParameterSet.Config as cms


process = cms.Process('ANALYSIS')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2)
   
    )



# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/y/yilmaz/pat/CMSSW_3_7_0/SignalQuenchedDijet80to120_runs1to100.root')

                          )

process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string('plots.root')
                                   )

process.load('Configuration/StandardSequences/GeometryExtended_cff')

from RecoJets.JetProducers.CaloJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

process.bkg4Jets = cms.EDProducer(
    "JetAlgorithmAnalyzer",
#  "BackgroundJetProducer",
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

process.ana = cms.EDAnalyzer('MinBiasTowerAnalyzer')


process.load("CondCore.DBCommon.CondDBCommon_cfi")
process.CondDBCommon.connect = "sqlite_file:/afs/cern.ch/user/n/nart/scratch0/CMSSW_3_7_0_patch4/src/CmsHi/JulyExercise/data/CentralityTables.db"
process.PoolDBESSource = cms.ESSource("PoolDBESSource",
                                      process.CondDBCommon,
                                      toGet = cms.VPSet(cms.PSet(record = cms.string('HeavyIonRcd'),
                                                                 tag = cms.string('HFhits40_DataJulyExercise_Hydjet2760GeV_MC_37Y_V5_v0')
                                                                 )
                                                        )
                                      )

process.p = cms.Path(process.bkgJets*process.ana)

