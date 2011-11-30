import FWCore.ParameterSet.Config as cms

# reco jet with russian pileup subtraction
from RecoHI.HiJetAlgos.HiRecoJets_cff import *
from RecoHI.HiJetAlgos.HiRecoPFJets_cff import *

akPu3CaloJets = cms.EDProducer(
    "FastjetJetProducer",
    HiCaloJetParameters,
    AnomalousCellParameters,
    MultipleAlgoIteratorBlock,
    jetAlgorithm = cms.string("AntiKt"),
    rParam       = cms.double(0.3)
    )
akPu5CaloJets.radiusPU = 0.5

iterativeConePu5CaloJets.doPVCorrection = cms.bool(True)
iterativeConePu5CaloJets.srcPVs = 'hiSelectedVertex'

akPu5PFJets = ak5PFJets.clone()
akPu5PFJets.src = 'PFTowers'
akPu5PFJets.jetType = 'BasicJet'
akPu5PFJets.doPUOffsetCorr = True
akPu5PFJets.sumRecHits = False

akPu3PFJets = akPu5PFJets.clone()
akPu3PFJets.rParam = cms.double(0.3)

# pileup subtraction jet exclusion pt min
iterativeConePu5CaloJets.puPtMin = cms.double(10.0)
akPu5PFJets.puPtMin = cms.double(25.0)
akPu3PFJets.puPtMin = cms.double(15.0)
akPu5CaloJets.puPtMin = cms.double(10.0)
akPu3CaloJets.puPtMin = cms.double(10.0)

akPu5PFJets.doRhoFastjet = False
akPu5PFJets.doAreaFastjet = False

akPu3PFJets.doRhoFastjet = False
akPu3PFJets.doAreaFastjet = False

akPu5CaloJets.doRhoFastjet = False
akPu5CaloJets.doAreaFastjet = False
akPu5CaloJets.doPUOffsetCorr = True

akPu3CaloJets.doRhoFastjet = False
akPu3CaloJets.doAreaFastjet = False
akPu3CaloJets.doPUOffsetCorr = True


