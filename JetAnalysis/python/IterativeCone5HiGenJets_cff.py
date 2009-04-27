import FWCore.ParameterSet.Config as cms

from RecoJets.Configuration.RecoGenJets_cff import *
from RecoJets.Configuration.GenJetParticles_cff import *
from RecoJets.JetProducers.IconeJetParameters_cfi import *

iterativeCone5HiGenJets = cms.EDProducer("IterativeConeHiGenJetProducer",
                                         IconeJetParameters,
                                         inputEtMin = cms.double(0.0),
                                         inputEMin = cms.double(0.0),
                                         src = cms.InputTag("hiGenParticles"),
                                         jetType = cms.string('GenJet'),
                                         alias = cms.untracked.string('IC5HiGenJet'),
                                         coneRadius = cms.double(0.5)
                                         )

signalJets = cms.Sequence(genJetParticles*iterativeCone5GenJets*iterativeCone5HiGenJets)

subEventJets = cms.Sequence(iterativeCone5HiGenJets)
