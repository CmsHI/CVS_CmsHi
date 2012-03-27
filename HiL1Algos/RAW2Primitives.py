# Auto generated configuration file
# using: 
# Revision: 1.341.2.2 
# Source: /local/reps/CMSSW.admin/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions auto:com10 --scenario HeavyIons --process l1RECO --data --eventcontent RECODEBUG -s RAW2DIGI,L1Reco,RECO --datatier RECO --magField AutoFromDBCurrent --repacked --filein file:/net/hisrv0001/home/dav2105/hdir/raw/181985/00026B4D-DD11-E111-B567-00237DDC5CB0.root -n 2 --no_exe
import FWCore.ParameterSet.Config as cms

process = cms.Process('l1RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('file:/net/hisrv0001/home/dav2105/hdir/raw/181985/00026B4D-DD11-E111-B567-00237DDC5CB0.root')
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.341.2.2 $'),
    annotation = cms.untracked.string('step2 nevts:2'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RECODEBUGoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RECODEBUGEventContent.outputCommands,
    fileName = cms.untracked.string('step2_RAW2DIGI_L1Reco_RECO.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('RECO')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'GR_R_44_V7::All'

process.TFileService = cms.Service("TFileService",
		fileName = cms.string("dump_prims.root") 
		)
process.demo = cms.EDAnalyzer('TriggerPrimitives',
                              ECALDigis = cms.InputTag("ecalDigis:EcalTriggerPrimitives"),
                              HCALDigis = cms.InputTag("hcalDigis")
)

#process.p = cms.Path(process.demo)

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
#process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
process.p = cms.Path(process.demo)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECODEBUGoutput_step = cms.EndPath(process.RECODEBUGoutput)

# Schedule definition
#process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.RECODEBUGoutput_step,process.p)

process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.p)

from Configuration.PyReleaseValidation.ConfigBuilder import MassReplaceInputTag
MassReplaceInputTag(process)



