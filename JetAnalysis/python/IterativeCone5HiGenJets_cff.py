import FWCore.ParameterSet.Config as cms

from RecoJets.Configuration.RecoGenJets_cff import *
from RecoJets.Configuration.GenJetParticles_cff import *
from RecoJets.JetProducers.IconeJetParameters_cfi import *

hiGenParticlesForJets = genParticlesForJets.clone()
hiGenParticlesForJets.src = cms.InputTag("hiGenParticles")

iterativeCone5HiGenJets = cms.EDProducer("IterativeConeHiGenJetProducer",
                                         IconeJetParameters,
                                         jetPtMin = cms.double(5.0),
                                         inputEtMin = cms.double(0.0),
                                         inputEMin = cms.double(0.0),
                                         src = cms.InputTag("hiGenParticlesForJets"),
                                         srcMap = cms.InputTag("hiGenParticles"),
                                         jetType = cms.string('GenJet'),
                                         alias = cms.untracked.string('IC5HiGenJet'),
                                         coneRadius = cms.double(0.5)
                                         )

#iterativeCone5HiGenJets.src = cms.InputTag("hiGenParticlesForJets")

signalJets = cms.Sequence(genJetParticles*iterativeCone5GenJets)

subEventJets = cms.Sequence(hiGenParticlesForJets*iterativeCone5HiGenJets)

allGenJets = cms.Sequence(signalJets+subEventJets)
