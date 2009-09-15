# Auto generated configuration file
# using: 
# Revision: 1.140 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: hiReco -s DIGI,L1,DIGI2RAW,RAW2DIGI,RECO --scenario HeavyIons --conditions FrontierConditions_GlobalTag,MC_31X_V5::All --filein=/store/relval/CMSSW_3_3_0_pre1/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V5-v1/0012/ECD0FB45-6796-DE11-B075-001D09F28D54.root -n 10 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
#process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/Digi_cff')
process.load('Configuration/StandardSequences/SimL1Emulator_cff')
process.load('Configuration/StandardSequences/DigiToRaw_cff')
process.load('Configuration/StandardSequences/RawToDigi_cff')
process.load('Configuration/StandardSequences/ReconstructionHeavyIons_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.load('Configuration.Generator.Pyquen_GammaJet_pt20_4TeV_cfi')
process.load('SimGeneral.MixingModule.mixHiSignal_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('hiReco nevts:10'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)
# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/relval/CMSSW_3_3_0_pre3/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V8-v1/0015/22EFEE98-4EA1-DE11-BEFC-001D09F2B30B.root')
)

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    fileName = cms.untracked.string('hiReco_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string(''),
        filterName = cms.untracked.string('')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'MC_31X_V8::All'

# Path and EndPath definitions
process.signal_step = cms.Path(process.hiSignalSequence)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.signal_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step,process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.out_step)
