import FWCore.ParameterSet.Config as cms

# Turn of MC dependence in pat sequence
def removePatMCMatch(process):
    process.prod.remove(process.genPartons)
    process.prod.remove(process.heavyIonCleanedGenJets)
    process.prod.remove(process.hiPartons)
    process.prod.remove(process.patJetGenJetMatch)
    process.prod.remove(process.patJetPartonMatch)
    
    process.patJets.addGenPartonMatch   = False
    process.patJets.embedGenPartonMatch = False
    process.patJets.genPartonMatch      = ''
    process.patJets.addGenJetMatch      = False
    process.patJets.genJetMatch      = ''
    process.patJets.getJetMCFlavour     = False
    process.patJets.JetPartonMapSource  = ''
    return process

# Top Config to turn off all mc dependence
def disableMC(process):
    process.prod.remove(process.heavyIon)
    removePatMCMatch(process)
    return process

def overrideCentrality(process):
    process.GlobalTag.toGet = cms.VPSet(
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_HFhits40_AMPTOrgan_v0_offline"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("HFhitsAMPT_Organ")
                 ),
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_PixelHits40_AMPTOrgan_v0_offline"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("PixelHitsAMPT_Organ")
                 ),
        
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_HFhits40_HydjetBass_v0_offline"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("HFhitsHydjet_Bass")
                                    ),
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_PixelHits40_HydjetBass_v0_offline"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("PixelHitsHydjet_Bass")
                 ),
        
        cms.PSet(record = cms.string("HeavyIonRcd"),
#                 tag = cms.string("CentralityTable_HFhits40_AMPTPiano_v0_offline"),
                 tag = cms.string("CentralityTable_HFhits40_AMPTPiano_v0_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("HFhitsAMPT_Piano")
                 ),
        cms.PSet(record = cms.string("HeavyIonRcd"),
#                 tag = cms.string("CentralityTable_PixelHits40_AMPTPiano_v0_offline"),
                 tag = cms.string("CentralityTable_PixelHits40_AMPTPiano_v0_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("PixelHitsAMPT_Piano")
                 ),
        
        cms.PSet(record = cms.string("HeavyIonRcd"),
#                 tag = cms.string("CentralityTable_HFhits40_HydjetGuitar_v0_offline"),
                 tag = cms.string("CentralityTable_HFhits40_HydjetGuitar_v0_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("HFhitsHydjet_Guitar")
                 ),

        cms.PSet(record = cms.string("HeavyIonRcd"),
                 #                 tag = cms.string("CentralityTable_HFhits40_HydjetGuitar_v0_offline"),
                 tag = cms.string("CentralityTable_PixelHits40_HydjetGuitar_v0_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("PixelHitsHydjet_Guitar")
                 ),
        
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_HFhits40_AMPTOrgan_PreliminaryRun150476v0_mc"),
                 connect = cms.untracked.string("frontier://FrontierPrep/CMS_COND_PHYSICSTOOLS"),
                 label = cms.untracked.string("HFhits")
                 ),
        
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_PixelHits40_AMPTOrgan_PreliminaryRun150476v0_offline"),
                 connect = cms.untracked.string("frontier://FrontierPrep/CMS_COND_PHYSICSTOOLS"),
                 label = cms.untracked.string("PixelHits")
                 ),
        
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_HFhits40_AMPT2760GeV_PreliminaryData1107v2_mc"),
                 connect = cms.untracked.string("frontier://FrontierPrep/CMS_COND_PHYSICSTOOLS"),                 
                 label = cms.untracked.string("HFhits")
                 ),
        
        )
    
    return process


                              
