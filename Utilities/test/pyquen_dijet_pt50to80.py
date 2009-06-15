import FWCore.ParameterSet.Config as cms

process = cms.Process("DIGI")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.Generator_cff")

#global tags for conditions data: https://twiki.cern.ch/twiki/bin/view/CMSSWGuideFrontierConditions#22X_Releases_starting_from_CMSSW

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'IDEAL_31X::All'

##################################################################################
# Some services

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.debugModules = cms.untracked.vstring("mix")

process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
                                        ignoreTotal=cms.untracked.int32(0),
                                        oncePerEventMode = cms.untracked.bool(False)
                                        )

##################################################################################
# Make sure the random number generator types are consistent with standard

# process.RandomNumberGeneratorService.signal = cms.PSet(process.RandomNumberGeneratorService.generator) # For 3_1_X
process.RandomNumberGeneratorService.signal = cms.PSet(process.RandomNumberGeneratorService.theSource)
process.RandomNumberGeneratorService.signalSIM = cms.PSet(process.RandomNumberGeneratorService.g4SimHits)

process.RandomNumberGeneratorService.signal.initialSeed = 4
process.RandomNumberGeneratorService.signalSIM.initialSeed = 5


##################################################################################
# Pb+Pb Background Source
process.source = cms.Source('PoolSource',
                            fileNames = cms.untracked.vstring('file:///d00/yjlee/sample/hydjet_mb_2_2_4/1EA7C31D-83FB-DD11-8218-001C23BED6CA.root')
                            )

process.maxEvents = cms.untracked.PSet(
                       input = cms.untracked.int32(1)
                       )

##################################################################################
# Generate Pyquen Signal
from GeneratorInterface.PyquenInterface.pyquenPythiaDefault_cff import *
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
                                aBeamTarget = cms.double(207.0), ## beam/target atomic number
                                doCollisionalEnLoss = cms.bool(True), ## if true, perform partonic collisional en loss
                                embeddingMode = cms.bool(True)
                                )

# my modifications to the default pyquen sourceabove (unquenched 100 GeV dijets)
process.signal.PythiaParameters.parameterSets = cms.vstring('pythiaDefault','pythiaJets','kinematics')
process.signal.PythiaParameters.kinematics = cms.vstring (
    "CKIN(3)=100",  #min pthat
    "CKIN(4)=9999", #max pthat
    "CKIN(7)=-2.",  #min rapidity
    "CKIN(8)=2."    #max rapidity
    )
process.signal.doQuench = False


##################################################################################
# Match vertex of the signal event to the background event
process.load("CmsHi.Utilities.MatchVtx_cfi")

##################################################################################
# Run SIM on Pyquen signal
from Configuration.StandardSequences.Simulation_cff import *
process.signalSIM = g4SimHits
process.signalSIM.Generator.HepMCProductLabel = 'signal' # By default it's "source" in 2_x_y

##################################################################################
# Embed Pyquen signal into Background source at SIM level
from CmsHi.Utilities.EventEmbedding_cff import *
process.mix=cms.EDProducer('HiEventEmbedder',
                           simEventEmbeddingMixParameters,
                           signalTag = cms.vstring("signal","signalSIM")
                           )

##################################################################################
# Digi + Reconstruction
process.load("CmsHi.Utilities.HiGenParticles_cfi")                      # hiGenParticles (sub-events)
process.load("SimGeneral.TrackingAnalysis.trackingParticles_cfi")# trackingParticles (sim tracks)
process.mergedtruth.HepMCDataLabels = ['signal']

process.load("Configuration.StandardSequences.Digi_cff")# doAllDigi
process.load("Configuration.StandardSequences.L1Emulator_cff")          # L1Emulator
process.load("Configuration.StandardSequences.DigiToRaw_cff")# DigiToRaw
process.load("Configuration.StandardSequences.RawToDigi_cff")# RawToDigi
process.load("RecoHI.Configuration.Reconstruction_HI_cff")              # full heavy ion reconstruction

##############################################################################
# Output EDM File
process.load("CmsHi.Utilities.HiAnalysisEventContent_cff") #load keep/drop output commands
process.output = cms.OutputModule("PoolOutputModule",
                                  process.HITrackAnalysisObjects,
                                  compressionLevel = cms.untracked.int32(2),
                                  commitInterval = cms.untracked.uint32(1),
                                  fileName = cms.untracked.string('outputDijetEmbeddingTest_DIGI.root')
                                  )

##################################################################################
# Paths
process.sim = cms.Sequence(process.signal*process.matchVtx*process.signalSIM*process.mix)
process.gen = cms.Sequence(process.hiGenParticles * process.trackingParticles)
process.digi = cms.Sequence(process.doAllDigi*process.L1Emulator*process.DigiToRaw*process.RawToDigi)

#process.trkreco = cms.Sequence(process.offlineBeamSpot*process.trackerlocalreco*process.heavyIonTracking)
#process.reco = cms.Sequence(process.reconstruct_PbPb)

process.p = cms.Path(process.sim * process.gen * process.digi)
process.save = cms.EndPath(process.output)





               
