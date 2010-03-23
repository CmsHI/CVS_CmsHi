import FWCore.ParameterSet.Config as cms

### this needs some genjet cleaning or improved matching criteria
### to do proper matching in the heavy-ion environment

JetAnalyzerICPU5Calo = cms.EDAnalyzer("CaloJetTester",
    src = cms.InputTag("iterativeConePu5CaloJets"),
    srcGen = cms.InputTag("iterativeCone5HiGenJets"),
    genEnergyFractionThreshold = cms.double(0.05),
    genPtThreshold = cms.double(1.0),
    RThreshold = cms.double(0.3),
    reverseEnergyFractionThreshold = cms.double(0.5)                                    
)

JetAnalyzerICPU7Calo = cms.EDAnalyzer("CaloJetTester",
    src = cms.InputTag("iterativeConePu7CaloJets"),
    srcGen = cms.InputTag("iterativeCone7HiGenJets"), 
    genEnergyFractionThreshold = cms.double(0.05),
    genPtThreshold = cms.double(1.0),
    RThreshold = cms.double(0.3),
    reverseEnergyFractionThreshold = cms.double(0.5)                                    
)

JetAnalyzerAkPU5Calo = cms.EDAnalyzer("CaloJetTester",
    src = cms.InputTag("akPu5CaloJets"),
    srcGen = cms.InputTag("ak5HiGenJets"),  
    genEnergyFractionThreshold = cms.double(0.05),
    genPtThreshold = cms.double(1.0),
    RThreshold = cms.double(0.3),
    reverseEnergyFractionThreshold = cms.double(0.5)                                    
)

JetAnalyzerAkPU7Calo = cms.EDAnalyzer("CaloJetTester",
    src = cms.InputTag("akPu7CaloJets"),
    srcGen = cms.InputTag("ak7HiGenJets"),       
    genEnergyFractionThreshold = cms.double(0.05),
    genPtThreshold = cms.double(1.0),
    RThreshold = cms.double(0.3),
    reverseEnergyFractionThreshold = cms.double(0.5)
)

JetAnalyzerAkFastPU5Calo = cms.EDAnalyzer("CaloJetTester",
    src = cms.InputTag("akFastPu5CaloJets"),
    srcGen = cms.InputTag("ak5HiGenJets"),  
    genEnergyFractionThreshold = cms.double(0.05),
    genPtThreshold = cms.double(1.0),
    RThreshold = cms.double(0.3),
    reverseEnergyFractionThreshold = cms.double(0.5)                                    
)

JetAnalyzerAkFastPU7Calo = cms.EDAnalyzer("CaloJetTester",
    src = cms.InputTag("akFastPu7CaloJets"),
    srcGen = cms.InputTag("ak7HiGenJets"),       
    genEnergyFractionThreshold = cms.double(0.05),
    genPtThreshold = cms.double(1.0),
    RThreshold = cms.double(0.3),
    reverseEnergyFractionThreshold = cms.double(0.5)
)

hiJetValidation = cms.Sequence(JetAnalyzerICPU5Calo
                               #*JetAnalyzerICPU7Calo
                               #*JetAnalyzerAkPU5Calo
                               #*JetAnalyzerAkPU7Calo
                               #*JetAnalyzerAkFastPU5Calo
                               #*JetAnalyzerAkFastPU7Calo
                               )
