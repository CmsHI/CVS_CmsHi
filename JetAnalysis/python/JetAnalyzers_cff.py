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

jetana_seq = cms.Sequence( icPu5JetAnalyzer * akPu5PFJetAnalyzer * akPu3PFJetAnalyzer * akPu5CaloJetAnalyzer * akPu3CaloJetAnalyzer)
