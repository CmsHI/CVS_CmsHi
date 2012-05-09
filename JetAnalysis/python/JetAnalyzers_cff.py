import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Generator_cff import *
from CmsHi.JetAnalysis.inclusiveJetAnalyzer_cff import *

inclusiveJetAnalyzer.eventInfoTag = cms.InputTag("hiSignal")
inclusiveJetAnalyzer.useCentrality   = cms.untracked.bool(False)

icPu5JetAnalyzer = inclusiveJetAnalyzer.clone()

akPu5PFJetAnalyzer = icPu5JetAnalyzer.clone(
    jetTag = 'akPu5PFpatJets',
    genjetTag = 'ak5HiGenJets'
    )

akPu3PFJetAnalyzer = icPu5JetAnalyzer.clone(
    jetTag = 'akPu3PFpatJets',
    genjetTag = 'ak3HiGenJets'
    )

akPu5CaloJetAnalyzer = icPu5JetAnalyzer.clone(
    jetTag = 'akPu5patJets',
    genjetTag = 'ak5HiGenJets'
    )

akPu3CaloJetAnalyzer = icPu5JetAnalyzer.clone(
    jetTag = 'akPu3patJets',
    genjetTag = 'ak3HiGenJets'
    )

ic5JetAnalyzer = icPu5JetAnalyzer.clone(jetTag = cms.InputTag("iterativeCone5CaloJets"))

akPu1PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak1PFpatJets"))
akPu2PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak2PFpatJets"))
akPu3PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak3PFpatJets"))
akPu4PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak4PFpatJets"))
akPu5PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak5PFpatJets"))
akPu6PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak6PFpatJets"))

akPu3CaloJetAnalyzer = akPu3PFJetAnalyzer.clone()

akPu1CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak1CalopatJets"))
akPu2CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak2CalopatJets"))
akPu3CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak3CalopatJets"))
akPu4CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak4CalopatJets"))
akPu5CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak5CalopatJets"))
akPu6CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak6CalopatJets"))

ak1PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak1PFpatJets"))
ak2PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak2PFpatJets"))
ak3PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak3PFpatJets"))
ak4PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak4PFpatJets"))
ak5PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak5PFpatJets"))
ak6PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak6PFpatJets"))
ak3CaloJetAnalyzer = akPu3PFJetAnalyzer.clone()

ak1CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak1CalopatJets"))
ak2CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak2CalopatJets"))
ak3CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak3CalopatJets"))
ak4CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak4CalopatJets"))
ak5CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak5CalopatJets"))
ak6CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak6CalopatJets"))

jetAnalyzers = cms.Sequence(akPu1PFJetAnalyzer +
                            akPu2PFJetAnalyzer +
                            akPu3PFJetAnalyzer +
                            akPu4PFJetAnalyzer +
                            akPu5PFJetAnalyzer +
                            akPu6PFJetAnalyzer +
                            
                            akPu1CaloJetAnalyzer +
                            akPu2CaloJetAnalyzer +
                            akPu3CaloJetAnalyzer +
                            akPu4CaloJetAnalyzer +
                            akPu5CaloJetAnalyzer +
                            akPu6CaloJetAnalyzer +
                            
                            ak1PFJetAnalyzer +
                            ak2PFJetAnalyzer +
                            ak3PFJetAnalyzer +
                            ak4PFJetAnalyzer +
                            ak5PFJetAnalyzer +
                            ak6PFJetAnalyzer +
                            
                            ak1CaloJetAnalyzer +
                            ak2CaloJetAnalyzer +
                            ak3CaloJetAnalyzer +
                            ak4CaloJetAnalyzer +
                            ak5CaloJetAnalyzer +
                            ak6CaloJetAnalyzer
                            
                            )



