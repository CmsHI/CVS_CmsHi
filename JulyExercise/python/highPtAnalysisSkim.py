
import FWCore.ParameterSet.Config as cms

process = cms.Process('PAT')

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring("rfio:/castor/cern.ch/cms/store/relval/CMSSW_3_7_0/RelValHydjetQ_MinBias_2760GeV/GEN-SIM-RECO/MC_37Y_V4-v1/0025/1E466625-6169-DF11-A543-002618943829.root"),
                            inputCommands = cms.untracked.vstring("keep *_*_*_*",
                                                                  "drop *_iterativeConePu5CaloJets_*_*"
                                                                  ),
                            dropDescendantsOfDroppedBranches = cms.untracked.bool(False)
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2)
    )

process.load('Configuration/StandardSequences/GeometryExtended_cff')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.GlobalTag.globaltag = 'MC_37Y_V5::All'

process.load('Configuration/StandardSequences/ReconstructionHeavyIons_cff')

process.hiCentrality.produceHFhits = False
process.hiCentrality.produceHFtowers = False
process.hiCentrality.produceEcalhits = False
process.hiCentrality.produceBasicClusters = False
process.hiCentrality.produceZDChits = False
process.hiCentrality.produceETmidRapidity = True
process.hiCentrality.producePixelhits = True

process.load('PhysicsTools.PatAlgos.patHeavyIonSequences_cff')
from PhysicsTools.PatAlgos.tools.heavyIonTools import *
configureHeavyIons(process)

from PhysicsTools.PatAlgos.tools.jetTools import *

process.load("HeavyIonsAnalysis.Configuration.analysisProducers_cff")
process.load("HeavyIonsAnalysis.Configuration.analysisEventContent_cff")

process.output = cms.OutputModule("PoolOutputModule",
                                  process.jetTrkSkimContent,
                                      fileName = cms.untracked.string("allenrichedNZS.root")
                                  )

process.output.outputCommands.extend([
    "keep recoVertexs_hiSelectedVertex__RECO",
    "keep recoTracks_hiSelectedTracks__RECO",
    "keep recoPhotons_*_*_*" ,
    "keep edmTriggerResults_TriggerResults__*" ,
    "keep triggerTriggerEvent_hltTriggerSummaryAOD__*"
    ])

process.prod = cms.Path(
    process.siPixelRecHits +
    process.iterativeConePu5CaloJets +
    process.kt4CaloJets +
    process.ak5CaloJets +
    process.hiCentrality +
    process.makeHeavyIonJets
    )

from CmsHi.JulyExercise.DisableMC_cff import *
disableMC(process)

process.out_step = cms.EndPath(process.output)


