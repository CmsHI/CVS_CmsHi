
import FWCore.ParameterSet.Config as cms

from CmsHi.JetAnalysis.IterativeCone5HiGenJets_cff import *
from CmsHi.Utilities.HiGenParticles_cfi import *
from SimGeneral.HepPDTESSource.pythiapdt_cfi import *
from Configuration.StandardSequences.Generator_cff import *
from JetMETCorrections.Configuration.L2L3Corrections_Summer08_cff import *

genParticles.src = cms.InputTag("signal")
L2L3CorJetIC5Calo.src = cms.InputTag("iterativeConePu5CaloJets")

recoevent = cms.EDAnalyzer('HeavyIonJetAnalyzer',
                                   jetSrc = cms.vstring('iterativeConePu5CaloJets'),
                                   doParticles = cms.untracked.bool(True),
                                   doVertices = cms.untracked.bool(False)
                                   )

corrected = cms.EDAnalyzer('HeavyIonJetAnalyzer',
                                   jetSrc = cms.vstring('L2L3CorJetIC5Calo'),
                                   doParticles = cms.untracked.bool(False),
                                   doVertices = cms.untracked.bool(False)
                                   )

signalevent =  cms.EDAnalyzer('HeavyIonJetAnalyzer',
                                      jetSrc = cms.vstring('iterativeCone5GenJets'),
                                      doParticles = cms.untracked.bool(False)
                                      )

genevent = cms.EDAnalyzer('HeavyIonJetAnalyzer',
                                  jetSrc = cms.vstring('iterativeCone5HiGenJets'),
                                  doParticles = cms.untracked.bool(False)
                                  )


