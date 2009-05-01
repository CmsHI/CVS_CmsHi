import FWCore.ParameterSet.Config as cms

process = cms.Process("MIX")

from GeneratorInterface.PyquenInterface.pyquenPythiaDefault_cff import *

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("RecoHI.Configuration.Reconstruction_HI_cff")


process.MessageLogger.debugModules = cms.untracked.vstring("mix")
                             

process.source = cms.Source('PoolSource',
                            fileNames = cms.untracked.vstring('dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/unmerged/mc/Summer08/Pyquen_ON_GammaJet_pt10/GEN-SIM/IDEAL_V9_FixedVtx_OldPhysicsList/0000/FE75CAB2-0CCD-DD11-B9F4-001EC94B4F59.root')
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

process.signal = cms.EDProducer('PyquenProducer',
                                doQuench = cms.bool(True),
                                doIsospin = cms.bool(True),
                                qgpInitialTemperature = cms.double(1.0), ## initial temperature of QGP; allowed range [0.2,2.0]GeV;
                                pythiaPylistVerbosity = cms.untracked.int32(0),
                                doRadiativeEnLoss = cms.bool(True), ## if true, perform partonic radiative en loss
                                bFixed = cms.double(0.0), ## fixed impact param (fm); valid only if cflag_=0
                                angularSpectrumSelector = cms.int32(0), ## angular emitted gluon spectrum :
                                pythiaHepMCVerbosity = cms.untracked.bool(False),
                                PythiaParameters = cms.PSet(pyquenPythiaDefaultBlock,
                                                            parameterSets = cms.vstring('pythiaDefault','pythiaJets','kinematics'),
                                                            kinematics = cms.vstring('CKIN(3) = 50','CKIN(4) = 80')
                                                            ),
                                qgpProperTimeFormation = cms.double(0.1), ## proper time of QGP formation; allowed range [0.01,10.0]fm/c;
                                comEnergy = cms.double(5500.0),
                                numQuarkFlavor = cms.int32(0), ## number of active quark flavors in qgp; allowed values: 0,1,2,3
                                cFlag = cms.int32(0), ## centrality flag
                                bMin = cms.double(0.0), ## min impact param (fm); valid only if cflag_!=0
                                bMax = cms.double(0.0), ## max impact param (fm); valid only if cflag_!=0
                                maxEventsToPrint = cms.untracked.int32(0), ## events to print if pythiaPylistVerbosit
                                aBeamTarget = cms.double(208.0), ## beam/target atomic number
                                doCollisionalEnLoss = cms.bool(True), ## if true, perform partonic collisional en loss
                                embeddingMode = cms.bool(True)
                                )


process.RandomNumberGeneratorService.signal = cms.PSet(
    initialSeed = cms.untracked.uint32(5)
    )

process.RandomNumberGeneratorService.signalSIM = cms.PSet(process.RandomNumberGeneratorService.g4SimHits)

from CmsHi.Utilities.EventEmbedding_cff import *
process.mix=cms.EDProducer('HiEventEmbedder',
                           simEventEmbeddingMixParameters,
                           signalTag = cms.vstring("signal","signalSIM")
                           )

process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
                                        ignoreTotal=cms.untracked.int32(0),
                                        oncePerEventMode = cms.untracked.bool(False)
                                        )

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.Generator_cff")
process.load("Configuration.StandardSequences.Digi_cff")
process.load("Configuration.StandardSequences.L1Emulator_cff")
process.load("Configuration.StandardSequences.DigiToRaw_cff")
process.load("Configuration.StandardSequences.RawToDigi_cff")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'IDEAL_V12::All'

process.load("CmsHi.Utilities.HiGenParticles_cfi")
process.load("CmsHi.Utilities.HiAnalysisEventContent_cff")

from Configuration.StandardSequences.Simulation_cff import *

process.signalSIM = g4SimHits
process.signalSIM.Generator.HepMCProductLabel = 'signal'

process.output = cms.OutputModule("PoolOutputModule",
                                  process.HIRecoObjects,
                                  compressionLevel = cms.untracked.int32(2),
                                  commitInterval = cms.untracked.uint32(1),
                                  fileName = cms.untracked.string('pyquen_dijet_pt50to80_hydjet_mb_d20090428.root')
                                  )

process.sim = cms.Path(process.signal*process.signalSIM*process.mix)
process.gen = cms.Path(process.hiGenParticles)
process.digi = cms.Path(process.doAllDigi*process.L1Emulator*process.DigiToRaw*process.RawToDigi)

process.reco = cms.Path(process.caloReco*process.hiEcalClusters+process.runjets+process.hiCentrality+process.hiEvtPlane)

#process.reco = cms.Path(process.reconstruct_PbPb)
process.end = cms.EndPath(process.output)




