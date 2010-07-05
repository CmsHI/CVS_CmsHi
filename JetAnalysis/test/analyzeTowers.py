process = cms.Process('ANALYSIS')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2)
)

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/y/yilmaz/pat/CMSSW_3_7_0/Hydjet_MinBias_2760GeV_000.root')
                            )

process.ana = cms.EDAnalyzer('MinBiasTowerAnalyzer')

process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string('plots.root')
                                   )

process.p = cms.Path(process.ana)

