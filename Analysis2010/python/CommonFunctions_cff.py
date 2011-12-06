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

def hltFromREDIGI(process):
    process.hltanalysis.HLTProcessName      = "REDIGI"
    process.hltanalysis.l1GtObjectMapRecord = cms.InputTag("hltL1GtObjectMap::REDIGI")
    process.hltanalysis.l1GtReadoutRecord   = cms.InputTag("hltGtDigis::REDIGI")
    process.hltanalysis.hltresults          = cms.InputTag("TriggerResults::REDIGI")   
    return process

def overrideBeamSpot(process):
    process.GlobalTag.toGet = cms.VPSet(
        cms.PSet(record = cms.string("BeamSpotObjectsRcd"),
                 tag = cms.string("Realistic2.76ATeVCollisions_STARTUP_v0_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_BEAMSPOT")
                 ),
        )
    return process


def addRPFlat(process):
    process.GlobalTag.toGet.extend([
        cms.PSet(record = cms.string("HeavyIonRPRcd"),
                 tag = cms.string("RPFlatParams_Test_v0_offline"),
                 connect = cms.untracked.string("frontier://FrontierPrep/CMS_COND_TEMP"),
                 ),
        ])
    return process


def overrideGlobalTag(process):
    process.GlobalTag.toGet.extend([

        #==================== MC Tables ====================
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
                 tag = cms.string("CentralityTable_HFhits40_HydjetBass_vv44x01_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("HFhitsHydjet_Bass")
                                    ),
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_PixelHits40_HydjetBass_vv44x01_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("PixelHitsHydjet_Bass")
                 ),               
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_Tracks40_HydjetBass_vv44x01_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("TracksHydjet_Bass")
                 ),
        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_PixelTracks40_HydjetBass_vv44x01_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("PixelTracksHydjet_Bass")
                 ),

        cms.PSet(record = cms.string("HeavyIonRcd"),
                 tag = cms.string("CentralityTable_HFtowers40_HydjetBass_vv44x01_mc"),
                 connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                 label = cms.untracked.string("HFtowersHydjet_Bass")   
                 ),        


    cms.PSet(record = cms.string("HeavyIonRcd"),
                              tag = cms.string("CentralityTable_HFhits40_Hydjet18_vv44x01_mc"),
                              connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                              label = cms.untracked.string("HFhitsHydjet_Drum")
                                                 ),
                cms.PSet(record = cms.string("HeavyIonRcd"),
                                          tag = cms.string("CentralityTable_PixelHits40_Hydjet18_vv44x01_mc"),
                                          connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                                          label = cms.untracked.string("PixelHitsHydjet_Drum")
                                          ),
                cms.PSet(record = cms.string("HeavyIonRcd"),
                                          tag = cms.string("CentralityTable_Tracks40_Hydjet18_vv44x01_mc"),
                                          connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                                          label = cms.untracked.string("TracksHydjet_Drum")
                                          ),
                cms.PSet(record = cms.string("HeavyIonRcd"),
                                          tag = cms.string("CentralityTable_PixelTracks40_Hydjet18_vv44x01_mc"),
                                          connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                                          label = cms.untracked.string("PixelTracksHydjet_Drum")
                                          ),

                cms.PSet(record = cms.string("HeavyIonRcd"),
                                          tag = cms.string("CentralityTable_HFtowers40_Hydjet18_vv44x01_mc"),
                                          connect = cms.untracked.string("frontier://FrontierProd/CMS_COND_31X_PHYSICSTOOLS"),
                                          label = cms.untracked.string("HFtowersHydjet_Drum")
                                          ),
        

#==================== DATA ONLY, FIXED RUN TAGS =====================================
# NOTHING
        ])
    
    return process


def overrideCentrality(process):    
    overrideGlobalTag(process)
    return process

                              
