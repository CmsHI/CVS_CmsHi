######################################################################################
#
# PAT Sequence Script for Heavy Ion Testing
#

import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

################################################################################
# Input Variable Parsing
#
# This script uses input variable parsing, which means that you
# can change the input and output files, as well as max events
# from the command line rather than having to edit the file
#
# Usage:
#
# cmsRun pat_hi_sequence_cfg.py files=/path/to/input1.root output=file:output.root maxEvents=10
#
# You can use multiple files= options to read in multiple inputs
#


import FWCore.ParameterSet.VarParsing as VarParsing

ivars = VarParsing.VarParsing('standard')

ivars.output = 'HIPAT_output_full.root'
ivars.maxEvents = -1

ivars.files = 'file:/afs/cern.ch/user/a/appeltel/public/HYDJET-b9-3_1_X_2009-MC_31X_V2.10.root'

ivars.parseArguments()

########################################################################################
# Input Files and max events
#
#
# Although MC data sets should not have duplicate event numbers, checking
# for duplicate events is turned off here for testing purposes.
#

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring( ivars.files ),
    duplicateCheckMode = cms.untracked.string( 'noDuplicateCheck' )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(ivars.maxEvents)
)

########################################################################################
# Timing and memory services
#

# process.Timing = cms.Service("Timing")

# process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#    oncePerEventMode = cms.untracked.bool(True),
#    ignoreTotal = cms.untracked.int32(0)
#)

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)

##################################################################################
#
# hiGenParticles - (Temporary)
#
# Currently not in production sequence, needed for pat::Jets
#

process.load("CmsHi.Utilities.HiGenParticles_cfi")

process.hiGenParticles.src = cms.vstring("generator")
process.hiGenTemp = cms.Path( process.hiGenParticles )


##################################################################################
# Additional Reconstruction (Muons - Temporary)
#
# Until the reco::Muon object is added to standard HI reconstruction,
# the object will be produced in this script for testing.
#
#
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("RecoLocalMuon.Configuration.RecoLocalMuon_cff")
process.load("RecoMuon.Configuration.RecoMuon_cff")
process.load("RecoMuon.MuonIdentification.muonIdProducerSequence_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V2::All'


# process.muons.inputCollectionLabels = ['globalPrimTracks', 'globalMuons', 'standAloneMuons:UpdatedAtVtx']
# process.muons.TrackExtractorPSet.inputTrackCollection = 'globalPrimTracks'
# process.calomuons.inputTracks = 'globalPrimTracks'
# process.muIsoDepositTk.ExtractorPSet.inputTrackCollection = 'globalPrimTracks'
# process.globalMuons.TrackerCollectionLabel = 'globalPrimTracks'

process.muons.JetExtractorPSet.JetCollectionLabel = cms.InputTag("iterativeConePu5CaloJets")
process.muIsoDepositJets.ExtractorPSet.JetCollectionLabel = cms.InputTag("iterativeConePu5CaloJets")

process.muonRecoTemp = cms.Path(
    process.muonCSCDigis *
    process.muonDTDigis *
    process.muonRPCDigis *
    process.muonlocalreco *
    process.muontracking_with_TeVRefinement *
    process.muonIdProducerSequence *
    process.muIsolation
)

###################################################################################
#
# PAT Track Production
#
# For now, selection is run on the track collection globalPrimTracks and renamed generalTracks
# which most high level reconstruction algorithms look for by default. The other track
# collections are dropped in the EventContent to avoid confusion when looking for
# the correct collection of tracks to analyze.
#

import RecoHI.HiTracking.SelectHITracks_cfi
process.generalTracks =  RecoHI.HiTracking.SelectHITracks_cfi.selectHiTracks.clone()

process.hiTracks = cms.Path( process.generalTracks )

##################################################################################
#
# PAT object production
#

process.load("CmsHi.HiPatAlgos.HiPatPhotonSequence_cfi")
process.load("CmsHi.HiPatAlgos.HiPatJetSequence_cfi")
process.load("CmsHi.HiPatAlgos.HiPatMuonSequence_cfi")


process.patHIProductionSequence = cms.Path(
    process.hiPatJetSequence *
    process.hiPatPhotonSequence *
    process.hiPatMuonSequence
)

####################################################################################
#
# PAT object selection
#

process.load("PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi")
process.load("PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi")
process.load("PhysicsTools.PatAlgos.selectionLayer1.photonSelector_cfi")

process.selectedLayer1Muons.cut = cms.string('pt > 0. & abs(eta) < 12.')
process.selectedLayer1Jets.cut = cms.string('pt > 0. & abs(eta) < 12.')
process.selectedLayer1Photons.cut = cms.string('pt > 0. & abs(eta) < 12.')


process.patHISelectionSequence = cms.Path(
    process.selectedLayer1Muons +
    process.selectedLayer1Photons +
    process.selectedLayer1Jets
)


#####################################################################################
# Event Content
#

process.HIPATObjects = cms.PSet(
        outputCommands = cms.untracked.vstring('drop *',
                                               'keep patPhotons_selected*_*_*',
                                               'keep patMuons_selected*_*_*',
                                               'keep patJets_selected*_*_*',
                                               'keep recoCentrality_*_*_*',
                                               'keep recoEvtPlane_*_*_*',
                                               'keep recoTracks_generalTracks_*_*'
        )
)

#######################################################################################
# Output file
#

process.output = cms.OutputModule("PoolOutputModule",
    process.HIPATObjects,
    compressionLevel = cms.untracked.int32(2),
    commitInterval = cms.untracked.uint32(1),
    fileName = cms.untracked.string(ivars.output)
)

process.out = cms.EndPath( process.output )

process.schedule = cms.Schedule(
    process.hiGenTemp,
    process.hiTracks,
    process.muonRecoTemp,
    process.patHIProductionSequence,
    process.patHISelectionSequence,
    process.out
)

