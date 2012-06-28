# Auto generated configuration file
# using: 
# Revision: 1.341.2.2 
# Source: /local/reps/CMSSW.admin/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions auto:com10 --scenario HeavyIons --process l1RECO --data --eventcontent RECODEBUG -s RAW2DIGI,L1,RECO --datatier RECO --customise Configuration/DataProcessing/RecoTLR.customiseCommonHI,L1Trigger/Configuration/customise_l1GtEmulatorFromRaw --magField AutoFromDBCurrent --repacked --filein file:/net/hisrv0001/home/dav2105/hdir/raw/181985/00026B4D-DD11-E111-B567-00237DDC5CB0.root -n 2 --processName=L1EmulRaw --no_exe
import FWCore.ParameterSet.Config as cms

process = cms.Process('L1EmulRaw')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('file:/d102/richard/HIminbias2011_RAW/SD_MinBiasHI_100_1_D9e.root',
                                      'file:/d102/richard/HIminbias2011_RAW/SD_MinBiasHI_101_1_r6h.root',
                                      'file:/d102/richard/HIminbias2011_RAW/SD_MinBiasHI_10_1_wmy.root')
)

process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(True))

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('step2 nevts:2'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RECODEBUGoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    #outputCommands = process.RECODEBUGEventContent.outputCommands,
    fileName = cms.untracked.string('/d102/richard/l1emul_reco/minbias_l1emul_reco_1.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('RECO')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'GR_R_44_V7::All'

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECODEBUGoutput_step = cms.EndPath(process.RECODEBUGoutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1simulation_step,process.reconstruction_step,process.endjob_step,process.RECODEBUGoutput_step)
#process.schedule = cms.Schedule(process.raw2digi_step,process.L1simulation_step)

from Configuration.PyReleaseValidation.ConfigBuilder import MassReplaceInputTag
MassReplaceInputTag(process)

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.RecoTLR
from Configuration.DataProcessing.RecoTLR import customiseCommonHI 

#call to customisation function customiseCommonHI imported from Configuration.DataProcessing.RecoTLR
process = customiseCommonHI(process)

# Automatic addition of the customisation function from L1Trigger.Configuration.customise_l1GtEmulatorFromRaw
from L1Trigger.Configuration.customise_l1EmulatorFromRaw import customise 

#call to customisation function customise imported from L1Trigger.Configuration.customise_l1GtEmulatorFromRaw
process = customise(process)

# End of customisation functions
