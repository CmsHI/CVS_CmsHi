# Auto generated configuration file
# using: 
# Revision: 1.341.2.2 
# Source: /local/reps/CMSSW.admin/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions auto:com10 --scenario HeavyIons --process l1RECO --data --eventcontent RECODEBUG -s RAW2DIGI,L1Reco,RECO --datatier RECO --magField AutoFromDBCurrent --repacked --filein file:/net/hisrv0001/home/dav2105/hdir/raw/181985/00026B4D-DD11-E111-B567-00237DDC5CB0.root -n 2 --no_exe
import FWCore.ParameterSet.Config as cms

process = cms.Process('L1RECO2Primitives')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(
#    'file:/net/hisrv0001/home/dav2105/hdir/raw/181985/00026B4D-DD11-E111-B567-00237DDC5CB0.root',
    'file:/mnt/hadoop/cms/store/user/velicanu/step2_RAW2DIGI_L1Reco_RECO_94_1_Br3.root'
    )
                            
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.2 $'),
    annotation = cms.untracked.string('step2 nevts:2'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'GR_R_44_V7::All'

process.TFileService = cms.Service("TFileService",
		fileName = cms.string("dump_prims.root") 
		)
process.TriggerPrimitives = cms.EDAnalyzer('TriggerPrimitives',
                              ECALDigis = cms.InputTag("ecalDigis:EcalTriggerPrimitives"),
                              HCALDigis = cms.InputTag("hcalDigis"),
                              GCTDigis = cms.InputTag("gctDigis")
)

process.p = cms.Path(process.TriggerPrimitives)


from Configuration.PyReleaseValidation.ConfigBuilder import MassReplaceInputTag
MassReplaceInputTag(process)
