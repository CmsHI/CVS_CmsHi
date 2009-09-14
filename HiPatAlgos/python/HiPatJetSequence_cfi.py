import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.producersLayer1.jetProducer_cff import *
from PhysicsTools.PatAlgos.recoLayer0.jetCorrFactors_cfi import *
from PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi import *

#####################################################
# Heavy Ion Specific Jet Modules

from RecoHI.HiJetAlgos.IterativeCone5HiGenJets_cff import *
from SimGeneral.HepPDTESSource.pythiapdt_cfi import *
hiGenJetCleaner = cms.EDProducer('HiGenJetCleaner',
                                 src = cms.untracked.string('iterativeCone5HiGenJets'),
                                 deltaR = cms.untracked.double(0.25),
                                 ptCut = cms.untracked.double(20),
                                 createNewCollection = cms.untracked.bool(True),
                                 fillDummyEntries = cms.untracked.bool(True)
                                 )

#####################################################
# Pat Jet Options

allLayer1Jets.addBTagInfo = cms.bool(False)
allLayer1Jets.addGenPartonMatch = cms.bool(False)
allLayer1Jets.addAssociatedTracks = cms.bool(False)
allLayer1Jets.addJetCharge = cms.bool(False)
allLayer1Jets.addBTagInfo = cms.bool(False)
allLayer1Jets.addDiscriminators = cms.bool(False)
allLayer1Jets.addTagInfos = cms.bool(False)
allLayer1Jets.getJetMCFlavour = cms.bool(False)
allLayer1Jets.addGenJetMatch = cms.bool(True)

#####################################################
# Input Labels

allLayer1Jets.jetSource = cms.InputTag("iterativeConePu5CaloJets")
# (Placeholder for validated corrections)
jetCorrFactors.jetSource = cms.InputTag("iterativeConePu5CaloJets")
jetGenJetMatch.src = cms.InputTag("iterativeConePu5CaloJets")
jetGenJetMatch.matched = cms.InputTag("hiGenJetCleaner")

hiPatJetSequence = cms.Sequence(hiGenParticlesForJets *
                                iterativeCone5HiGenJets*
                                hiGenJetCleaner *
                                jetGenJetMatch *
                                jetCorrFactors *
                                allLayer1Jets)


#####################################################
# Cleaning

from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
selectedLayer1Jets.cut = cms.string('pt > 20.')

