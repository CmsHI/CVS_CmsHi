
import FWCore.ParameterSet.Config as cms

process = cms.Process('TUNE')

process.load('CmsHi.HiGenTools.hiTrivialTuner_cfi')
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.ana = cms.EDAnalyzer('TuneAnalyzer')

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/cms/store/relval/CMSSW_3_7_0_pre5/RelValHydjetQ_MinBias_2760GeV/GEN-SIM-RAW/MC_37Y_V4-v1/0022/1499A186-5963-DF11-8D1F-00261894385A.root')
                            
                            )

process.output = cms.OutputModule("PoolOutputModule",
                                  fileName = cms.untracked.string('tuned.root')
                                  )

process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string('treefile.root')
                                   )

process.p = cms.Path(process.hiTunedG4SimHits*process.ana)
process.e = cms.EndPath(process.output)








