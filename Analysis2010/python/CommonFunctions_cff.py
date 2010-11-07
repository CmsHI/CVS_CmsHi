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
                 tag = cms.string("CentralityTable_PixelHits40_Hydjet2760GeV_v1_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("PixelHitsHydjet_2760GeV")
                 ),
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_PixelHits40_AMPT2760GeV_v1_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("PixelHitsAMPT_2760GeV")
                 ),
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_HFhits40_Hydjet2760GeV_v1_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("HFhitsHydjet_2760GeV")
                                  ),
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_HFhits40_AMPT2760GeV_v1_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("HFhitsAMPT_2760GeV")
                 ),
        
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("Preliminary_NoEffCor_AMPT_d1107"),
                 connect = cms.untracked.string("sqlite_file:/afs/cern.ch/user/y/yilmaz/public/CentralityTables_d1107.db"),
                 label = cms.untracked.string("HFhits")
                 ),
                
        )
    
    return process


                              
