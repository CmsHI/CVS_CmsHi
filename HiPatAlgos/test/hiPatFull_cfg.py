
######################################################################################
#
# PAT Sequence Script for Heavy Ion Analysis
#

import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring("rfio:/castor/cern.ch/user/y/yilmaz/reco/CMSSW_3_3_0_pre5/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V8-v1/061D468F-62AB-DE11-8869-001D09F253D4.root"),
                            duplicateCheckMode = cms.untracked.string( 'noDuplicateCheck' )
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

########################################################################################
# Timing and memory services
#

process.Timing = cms.Service("Timing")

process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
                                        oncePerEventMode = cms.untracked.bool(True),
                                        ignoreTotal = cms.untracked.int32(0)
                                        )


##################################################################################
##################################################################################
#
# PAT object production & selection
#                                                                       
process.load("CmsHi.HiPatAlgos.HiPatSequences_cff")

##################################################################################
##################################################################################
# Heavy Ion reconstruction for the missing objects in the standard HI - RECO

process.load("PhysicsTools.HepMCCandAlgos.HiGenParticles_cfi")
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V2::All'

#######################################################################################
# Output file
#

process.output = cms.OutputModule("PoolOutputModule",
    process.hiPatExtraEventContent,
    compressionLevel = cms.untracked.int32(2),
    commitInterval = cms.untracked.uint32(1),
    fileName = cms.untracked.string("hi_pat.root")
)

#######################################################################################
#
# Paths to run
#

process.producePat = cms.Path(process.hiGenParticles *
                              process.hiPatProductionSequence *
                              process.hiPatSelectionSequence
                              )

process.out = cms.EndPath( process.output )
