######################################################################################
#
# PAT Sequence Script for Jet Analysis
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

ivars.output = 'HIPAT_output_jetsOnly.root'
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
#
# PAT object production
#

process.load("CmsHi.HiPatAlgos.HiPatJetSequence_cfi")


process.patHIProductionSequence = cms.Path(
    process.hiPatJetSequence 
)

####################################################################################
#
# PAT object selection
#

process.load("PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi")

process.selectedLayer1Jets.cut = cms.string('pt > 0. & abs(eta) < 12.')


process.patHISelectionSequence = cms.Path(
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
    process.patHIProductionSequence,
    process.patHISelectionSequence,
    process.out
)

