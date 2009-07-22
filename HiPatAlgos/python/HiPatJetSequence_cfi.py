
from PhysicsTools.PatAlgos.jetProducer_cff import *

#####################################################
# Heavy Ion Specific Jet Modules

from CmsHi.JetAnalysis.IterativeCone5HiGenJets_cff import *
hiGenJetCleaner = cms.EDProducer('HiGenJetCleaner')

#####################################################
# Pat Jet Options

process.allLayer1Jets.addBTagInfo = cms.bool(False)
process.allLayer1Jets.addGenPartonMatch = cms.bool(False)
process.allLayer1Jets.addAssociatedTracks = cms.bool(False)
process.allLayer1Jets.addJetCharge = cms.bool(False)
process.allLayer1Jets.addBTagInfo = cms.bool(False)
process.allLayer1Jets.addDiscriminators = cms.bool(False)
process.allLayer1Jets.addTagInfos = cms.bool(False)
process.allLayer1Jets.getJetMCFlavour = cms.bool(False)

process.allLayer1Jets.addGenJetMatch = cms.bool(True)

#####################################################
# Input Labels

process.allLayer1Jets.jetSource = cms.InputTag("iterativeConePu5CaloJets")
# (Placeholder for validated corrections)
process.jetCorrFactors.jetSource = cms.InputTag("iterativeConePu5CaloJets")
process.jetGenJetMatch.src = cms.InputTag("iterativeConePu5CaloJets")
process.jetGenJetMatch.matched = cms.InputTag("hiGenJetCleaner")

hiPatJetSequence = cms.Sequence(process.hiGenParticlesForJets *
                                process.iterativeCone5HiGenJets*
                                process.hiGenJetCleaner *
                                process.jetGenJetMatch *
                                process.jetCorrFactors *
                                process.allLayer1Jets)

