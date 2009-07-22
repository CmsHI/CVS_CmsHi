
from PhysicsTools.PatAlgos.jetProducer_cff import *
from PhysicsTools.PatAlgos.recoLayer0.jetCorrFactors_cfi import *
from PhysicsTools.PatAlgos.mcMatchLayer0.jetMatch_cfi import *

#####################################################
# Heavy Ion Specific Jet Modules

from CmsHi.JetAnalysis.IterativeCone5HiGenJets_cff import *
from SimGeneral.HepPDTESSource.pythiapdt_cfi import *
hiGenJetCleaner = cms.EDProducer('HiGenJetCleaner')

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

