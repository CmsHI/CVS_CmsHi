# Auto generated configuration file
# using: 
# Revision: 1.334 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: l1EmulatorFromRaw -s RAW2DIGI,L1 -n 100 --conditions auto:com10 --datatier DIGI-RECO --eventcontent FEVTDEBUGHLT --data --filein /store/data/Run2011A/MinimumBias/RAW/v1/000/165/514/28C65E11-E584-E011-AED9-0030487CD700.root,/store/data/Run2011A/MinimumBias/RAW/v1/000/165/514/44C0FC26-EE84-E011-B657-003048F1C424.root --customise=L1Trigger/Configuration/customise_l1EmulatorFromRaw --processName=L1EmulRaw --no_exec
# Other references:
# - /afs/cern.ch/user/g/guiducci/public/rerunL1/l1EmulatorFromRaw_RAW2DIGI_L1_L1Ntuple.py
# - https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGlobalHLT#Running_the_L1_emulator
import FWCore.ParameterSet.Config as cms

process = cms.Process('L1EmulRawHLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('HLTrigger.Configuration.HLT_HIon_data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# L1 Ntuple
process.load("UserCode.L1TriggerDPG.l1NtupleProducer_cfi")
process.l1NtupleProducer.gctTauJetsSource     = cms.InputTag("none","")
process.l1NtupleProducer.gctCentralJetsSource = cms.InputTag("none","")
process.l1NtupleProducer.gctNonIsoEmSource    = cms.InputTag("none","")
process.l1NtupleProducer.gctForwardJetsSource = cms.InputTag("none","")
process.l1NtupleProducer.gctIsoEmSource       = cms.InputTag("none","")
process.l1NtupleProducer.gctEnergySumsSource  = cms.InputTag("none","")
process.l1NtupleProducer.gctTauJetsSource     = cms.InputTag("none","")
process.l1NtupleProducer.rctSource            = cms.InputTag("none")
process.l1NtupleProducer.dttfSource           = cms.InputTag("none")
process.l1NtupleProducer.csctfTrkSource       = cms.InputTag("none")
process.l1NtupleProducer.csctfLCTSource       = cms.InputTag("none")
process.l1NtupleProducer.csctfStatusSource    = cms.InputTag("none")
process.l1NtupleProducer.csctfDTStubsSource   = cms.InputTag("none")
process.l1NtupleProducer.gtSource             = cms.InputTag("simGtDigis") # put gtDigis for data
process.l1NtupleProducer.gmtSource            = cms.InputTag("simGmtDigis") # put gtDigis (yes, not gmtDigis) for data

process.l1NtupleOrg = process.l1NtupleProducer.clone(
  gtSource             = cms.InputTag("gtDigis"), # put gtDigis for data
  gmtSource            = cms.InputTag("gtDigis") # put gtDigis (yes, not gmtDigis) for data
  )
  
# Analyzers
process.load("HLTrigger.HLTanalyzers.HLTBitAnalyser_cfi")
process.hltbitanalysis.UseTFileService			= cms.untracked.bool(True)

process.hltbitnew = process.hltbitanalysis.clone(
  l1GtObjectMapRecord	= cms.InputTag("hltL1GtObjectMap","",process.name_()),
  l1GtReadoutRecord		= cms.InputTag("simGtDigis","",process.name_()),
  hltresults           = cms.InputTag("TriggerResults","",process.name_()),
  HLTProcessName       = cms.string(process.name_())
  )

process.hltbitorg = process.hltbitanalysis.clone(l1GtReadoutRecord = "gtDigis")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

# Other statements
#process.GlobalTag.globaltag = 'GR_R_44_V2::All'
process.GlobalTag.globaltag = 'START44_V4::All'
fname='L1Tree_olddata_mctag_l1hlt.root'

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(
      #'/store/hidata/HIRun2010/HIAllPhysics/RAW/v1/000/150/590/02D89852-5DEC-DF11-9E11-001D09F282F5.root'
			'file:/d101/frankma/data/HICorePhysics/raw/mbskim_0.root',
			'file:/d101/frankma/data/HICorePhysics/raw/mbskim_1.root'
      #'/store/data/Run2011A/MinimumBias/RAW/v1/000/173/692/3C024415-BECC-E011-96B3-001D09F244BB.root'
      )
)

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.334 $'),
    annotation = cms.untracked.string('l1EmulatorFromRaw nevts:100'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition
process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    fileName = cms.untracked.string('l1EmulatorFromRaw_RAW2DIGI_L1.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('DIGI-RECO')
    )
)
process.FEVTDEBUGHLToutput.outputCommands = ['keep *']


# Jet Analyzers
process.load("PhysicsTools.PatAlgos.patHeavyIonSequences_cff")
process.patJets.jetSource  = cms.InputTag("hltHICaloJetCorrected")
process.patJets.addBTagInfo         = False
process.patJets.addTagInfos         = False
process.patJets.addDiscriminators   = False
process.patJets.addAssociatedTracks = False
process.patJets.addJetCharge        = False
process.patJets.addJetID            = False
process.patJets.getJetMCFlavour     = False
process.patJets.addGenPartonMatch   = False
process.patJets.addGenJetMatch      = False
process.patJets.embedGenJetMatch    = False
process.patJets.embedGenPartonMatch = False
process.patJets.embedCaloTowers	    = False
process.patJets.addJetCorrFactors		= False

from MNguyen.InclusiveJetAnalyzer.inclusiveJetAnalyzer_cff import *
process.icPu5JetAnalyzer = inclusiveJetAnalyzer.clone(
	L1gtReadout = 'hltGtDigis::'+process.name_(),
	hltTrgResults = cms.untracked.string('TriggerResults::'+process.name_()),
	jetTag = 'patJets',
	hltTrgNames = ['HLT_HIJet45'],
	useCentrality = False,
	useJEC = cms.untracked.bool(False),
	useVtx = cms.untracked.bool(False),
	isMC = False
	)

# Additional output definition
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(fname)                                  
)

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.L1Ntuple_step = cms.Path(process.l1NtupleProducer*process.l1NtupleOrg)
process.ana_step = cms.Path(process.HLTHIRecoJetSequenceIC5Corrected*process.patJets)
process.endjob_step = cms.EndPath(process.endOfProcess*process.hltbitnew*process.hltbitorg*process.icPu5JetAnalyzer)
#process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1simulation_step,
                                process.HLT_HIJet45,
                                process.ana_step,
                                process.L1Ntuple_step,process.endjob_step)

# customisation of the process.

# Automatic addition of the customisation function from L1Trigger.Configuration.customise_l1EmulatorFromRaw
from L1Trigger.Configuration.customise_l1EmulatorFromRaw import customise 

#call to customisation function customise imported from L1Trigger.Configuration.customise_l1EmulatorFromRaw
process = customise(process)

# customize the HLT to use the emulated results
import HLTrigger.Configuration.customizeHLTforL1Emulator
process = HLTrigger.Configuration.customizeHLTforL1Emulator.switchToL1Emulator( process )
process = HLTrigger.Configuration.customizeHLTforL1Emulator.switchToSimGtDigis( process )
process.hltL1sL1SingleJet30UBptxAND.L1SeedsLogicalExpression = "L1_SingleJet36"

# End of customisation functions
