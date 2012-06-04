import FWCore.ParameterSet.Config as cms


from CmsHi.JetAnalysis.JetAnalyzers_cff import *

icPu5JetAnalyzer.fillGenJets   = cms.untracked.bool(True)
akPu1PFJetAnalyzer.fillGenJets = cms.untracked.bool(True)
akPu2PFJetAnalyzer.fillGenJets = cms.untracked.bool(True)
akPu3PFJetAnalyzer.fillGenJets = cms.untracked.bool(True)
akPu4PFJetAnalyzer.fillGenJets = cms.untracked.bool(True)
akPu5PFJetAnalyzer.fillGenJets = cms.untracked.bool(True)
akPu6PFJetAnalyzer.fillGenJets = cms.untracked.bool(True)

icPu5JetAnalyzer.genPtMin = cms.untracked.double(15)
akPu1PFJetAnalyzer.genPtMin = cms.untracked.double(15)
akPu2PFJetAnalyzer.genPtMin = cms.untracked.double(15)
akPu3PFJetAnalyzer.genPtMin = cms.untracked.double(15)
akPu4PFJetAnalyzer.genPtMin = cms.untracked.double(15)
akPu5PFJetAnalyzer.genPtMin = cms.untracked.double(15)
akPu6PFJetAnalyzer.genPtMin = cms.untracked.double(15)





jetAnalyzers = cms.Sequence(icPu5JetAnalyzer +

                            akPu1PFJetAnalyzer +
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



