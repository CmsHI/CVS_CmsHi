import FWCore.ParameterSet.Config as cms

from SimGeneral.MixingModule.mixObjects_cfi import *
eventEmbeddingSourceParameters = cms.PSet(
    nbPileupEvents = cms.PSet(
        averageNumber = cms.double(1.0)
    ),
    seed = cms.int32(325),
    type = cms.string('fixed')
)
eventEmbeddingMixParameters = cms.PSet(
    LabelPlayback = cms.string(''),
    maxBunch = cms.int32(0),
    minBunch = cms.int32(0),
    Label = cms.string(''),
    bunchspace = cms.int32(125),
    checktof = cms.bool(False)
)
simEventEmbeddingMixParameters = cms.PSet(
    eventEmbeddingMixParameters,
    mixObjects = cms.PSet(
        mixCH = cms.PSet(
            mixCaloHits
        ),
        mixTracks = cms.PSet(
            mixSimTracks
        ),
        mixVertices = cms.PSet(
            mixSimVertices
        ),
        mixSH = cms.PSet(
            mixSimHits
        ),
        mixHepMC = cms.PSet(
            mixHepMCProducts
        )
    )
)
genEventEmbeddingMixParameters = cms.PSet(
    eventEmbeddingMixParameters,
    mixObjects = cms.PSet(
        mySet = cms.PSet(
            input = cms.VInputTag(cms.InputTag("generator"), cms.InputTag("secsource")),
            type = cms.string('HepMCProduct')
        )
    )
)

mixSim = cms.EDProducer("MixingModule",
                        simEventEmbeddingMixParameters,
                        input = cms.SecSource("PoolRASource",
                                              eventEmbeddingSourceParameters,
                                              fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/cms/store/cmshi/mc/sim/hydjet_sim_x2_c10_d20080425/hydjet_sim_x2_c10_d20080425_r000002.root')
                                              )
                             )


mixGen = cms.EDProducer("MixingModule",
                        genEventEmbeddingMixParameters,
                        input = cms.SecSource("PoolRASource",
                                              eventEmbeddingSourceParameters,
                                              fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/cms/store/cmshi/mc/sim/hydjet_sim_x2_c10_d20080425/hydjet_sim_x2_c10_d20080425_r000002.root')
                                              )
                        )



mixGenNoPU = cms.EDProducer("MixingModule",
                            genEventEmbeddingMixParameters)

mixSimNoPU = cms.EDProducer("MixingModule",
                            simEventEmbeddingMixParameters)

#Parameters for Signal-Only digitization in Heavy Ion Mixing

noMix = mixSimNoPU.clone()
noMix.mixObjects.mixHepMC.input = cms.VInputTag(cms.InputTag("signal"))

noMix.mixObjects.mixCH.input = cms.VInputTag(cms.InputTag("signalSIM","CaloHitsTk"), cms.InputTag("signalSIM","CastorBU"),
                                             cms.InputTag("signalSIM","CastorFI"), cms.InputTag("signalSIM","CastorPL"), cms.InputTag("signalSIM","CastorTU"),
                                             cms.InputTag("signalSIM","EcalHitsEB"), cms.InputTag("signalSIM","EcalHitsEE"), cms.InputTag("signalSIM","EcalHitsES"),
                                             cms.InputTag("signalSIM","EcalTBH4BeamHits"), cms.InputTag("signalSIM","HcalHits"),
                                             cms.InputTag("signalSIM","HcalTB06BeamHits"), cms.InputTag("signalSIM","ZDCHITS"))

noMix.mixObjects.mixSH.input = cms.VInputTag(cms.InputTag("signalSIM","BSCHits"), cms.InputTag("signalSIM","FP420SI"), cms.InputTag("signalSIM","MuonCSCHits"),
                                             cms.InputTag("signalSIM","MuonDTHits"), cms.InputTag("signalSIM","MuonRPCHits"),
                                             cms.InputTag("signalSIM","TotemHitsRP"), cms.InputTag("signalSIM","TotemHitsT1"),
                                             cms.InputTag("signalSIM","TotemHitsT2Gem"), cms.InputTag("signalSIM","TrackerHitsPixelBarrelHighTof"),
                                             cms.InputTag("signalSIM","TrackerHitsPixelBarrelLowTof"), cms.InputTag("signalSIM","TrackerHitsPixelEndcapHighTof"),
                                             cms.InputTag("signalSIM","TrackerHitsPixelEndcapLowTof"), cms.InputTag("signalSIM","TrackerHitsTECHighTof"),
                                             cms.InputTag("signalSIM","TrackerHitsTECLowTof"), cms.InputTag("signalSIM","TrackerHitsTIBHighTof"),
                                             cms.InputTag("signalSIM","TrackerHitsTIBLowTof"), cms.InputTag("signalSIM","TrackerHitsTIDHighTof"),
                                             cms.InputTag("signalSIM","TrackerHitsTIDLowTof"), cms.InputTag("signalSIM","TrackerHitsTOBHighTof"),
                                             cms.InputTag("signalSIM","TrackerHitsTOBLowTof"))

noMix.mixObjects.mixTracks.input = cms.VInputTag(cms.InputTag("signalSIM"))
noMix.mixObjects.mixVertices.input = cms.VInputTag(cms.InputTag("signalSIM"))

