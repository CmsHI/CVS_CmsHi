# Auto generated configuration file
# using: 
# Revision: 1.165 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step1 -s HLT:HIon -n 1 --filein file.root --eventcontent FEVTDEBUGHLT --conditions MC_3XY_V25::All --mc --scenario HeavyIons --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('HLTrigger.Configuration.HLT_HIon_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')

process.Timing = cms.Service("Timing")

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.4 $'),
    annotation = cms.untracked.string('step2 nevts:10'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)
process.options = cms.untracked.PSet(

)
# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    #'/store/relval/CMSSW_3_5_2/RelValQCD_Pt_80_120/GEN-SIM-DIGI-RAW-HLTDEBUG/MC_3XY_V21-v1/0015/FA48FEA0-191E-DF11-9B68-003048679076.root'
    '/store/relval/CMSSW_3_5_2/RelValPyquen_DiJet_pt80to120_4TeV/GEN-SIM-RECO/MC_3XY_V21-v1/0001/FA961928-A01F-DF11-85F6-0030487CD7C0.root'
    )
)

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    fileName = cms.untracked.string('step1_HLT.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string(''),
        filterName = cms.untracked.string('')
    )
)

# Additional output definition

# Other statements
#process.mix.playback = True
process.GlobalTag.globaltag = 'MC_3XY_V25::All'

# Path and EndPath definitions
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule()
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.out_step])
