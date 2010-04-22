import FWCore.ParameterSet.VarParsing as VarParsing

ivars = VarParsing.VarParsing('standard')

#ivars.files = 'file:PyquenDijet80to120_d20100325_runs1to500.root'
#ivars.output = 'jets_pat_80to120.root'
#ivars.files = 'file:PyquenDijet120to170_d20100325_runs1to500.root'
#ivars.output = 'jets_pat_120to170.root'

ivars.files = 'file:PyquenDijet50to80_d20100325_runs1to500.root'
ivars.output = 'jets_pat_50to80.root'
ivars.maxEvents = -1

ivars.parseArguments()

import FWCore.ParameterSet.Config as cms

process = cms.Process('MATCH')

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(ivars.files)
                            )

process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(ivars.maxEvents)
        )

process.load('PhysicsTools.PatAlgos.patHeavyIonSequences_cff')
from PhysicsTools.PatAlgos.tools.heavyIonTools import *
configureHeavyIons(process)

from PhysicsTools.PatAlgos.tools.jetTools import *
switchJECSet( process, "Summer09_7TeV_ReReco332")

process.ak5corr = process.patJetCorrFactors.clone()
process.ak5corr.jetSource = cms.InputTag("akFastPu5CaloJets")
process.ak5corr.corrLevels.L2Relative = "L2Relative_AK5Calo"
process.ak5corr.corrLevels.L3Absolute = "L3Absolute_AK5Calo"

process.ak7corr = process.patJetCorrFactors.clone()
process.ak7corr.jetSource = cms.InputTag("akFastPu7CaloJets")
process.ak7corr.corrLevels.L2Relative = cms.string('L2Relative_AK7Calo')
process.ak7corr.corrLevels.L3Absolute = cms.string('L3Absolute_AK7Calo')

process.akPu5corr = process.ak5corr.clone()
process.akPu5corr.jetSource = cms.InputTag("akPu5CaloJets")
process.akPu7corr = process.ak7corr.clone()
process.akPu7corr.jetSource = cms.InputTag("akPu7CaloJets")

process.kt4corr = process.patJetCorrFactors.clone()
process.kt4corr.jetSource = cms.InputTag("ktFastPu4CaloJets")
process.kt4corr.corrLevels.L2Relative = cms.string('L2Relative_KT4Calo')
process.kt4corr.corrLevels.L3Absolute = cms.string('L3Absolute_KT4Calo')

process.kt6corr = process.patJetCorrFactors.clone()
process.kt6corr.jetSource = cms.InputTag("ktFastPu6CaloJets")
process.kt6corr.corrLevels.L2Relative = cms.string('L2Relative_KT6Calo')
process.kt6corr.corrLevels.L3Absolute = cms.string('L3Absolute_KT6Calo')

process.ktPu4corr = process.patJetCorrFactors.clone()
process.ktPu4corr.jetSource = cms.InputTag("ktPu4CaloJets")
process.ktPu4corr.corrLevels.L2Relative = cms.string('L2Relative_KT4Calo')
process.ktPu4corr.corrLevels.L3Absolute = cms.string('L3Absolute_KT4Calo')

process.ktPu6corr = process.patJetCorrFactors.clone()
process.ktPu6corr.jetSource = cms.InputTag("ktPu6CaloJets")
process.ktPu6corr.corrLevels.L2Relative = cms.string('L2Relative_KT6Calo')
process.ktPu6corr.corrLevels.L3Absolute = cms.string('L3Absolute_KT6Calo')
       
process.icPu5corr = process.patJetCorrFactors.clone()
process.icPu5corr.jetSource = cms.InputTag("iterativeConePu5CaloJets")
process.icPu5corr.corrLevels.L2Relative = cms.string('L2Relative_IC5Calo')
process.icPu5corr.corrLevels.L3Absolute = cms.string('L3Absolute_IC5Calo')

process.icPu7corr = process.patJetCorrFactors.clone()
process.icPu7corr.jetSource = cms.InputTag("iterativeConePu7CaloJets")
process.icPu7corr.corrLevels.L2Relative = cms.string('L2Relative_IC5Calo') # No IC7
process.icPu7corr.corrLevels.L3Absolute = cms.string('L3Absolute_IC5Calo') # No IC7

process.ak5clean = process.heavyIonCleanedGenJets.clone()
process.ak5clean.src = cms.untracked.string('ak5HiGenJets')
process.ak7clean = process.heavyIonCleanedGenJets.clone()
process.ak7clean.src = cms.untracked.string('ak7HiGenJets')
process.kt4clean = process.heavyIonCleanedGenJets.clone()
process.kt4clean.src = cms.untracked.string('kt4HiGenJets')
process.kt6clean = process.heavyIonCleanedGenJets.clone()
process.kt6clean.src = cms.untracked.string('kt6HiGenJets')
process.ic5clean = process.heavyIonCleanedGenJets.clone()
process.ic5clean.src = cms.untracked.string('iterativeCone5HiGenJets')
process.ic7clean = process.heavyIonCleanedGenJets.clone()
process.ic7clean.src = cms.untracked.string('iterativeCone7HiGenJets')

process.ak5match = process.patJetGenJetMatch.clone()
process.ak5match.src = cms.InputTag("akFastPu5CaloJets")
process.ak5match.matched = cms.InputTag("ak5clean")
process.ak7match = process.patJetGenJetMatch.clone()
process.ak7match.src = cms.InputTag("akFastPu7CaloJets")
process.ak7match.matched = cms.InputTag("ak7clean")
process.akPu5match = process.patJetGenJetMatch.clone()
process.akPu5match.src = cms.InputTag("akPu5CaloJets")
process.akPu5match.matched = cms.InputTag("ak5clean")
process.akPu7match = process.patJetGenJetMatch.clone()
process.akPu7match.src = cms.InputTag("akPu7CaloJets")
process.akPu7match.matched = cms.InputTag("ak7clean")

process.kt4match = process.patJetGenJetMatch.clone()
process.kt4match.src = cms.InputTag("ktFastPu4CaloJets")
process.kt4match.matched = cms.InputTag("kt4clean")
process.kt6match = process.patJetGenJetMatch.clone()
process.kt6match.src = cms.InputTag("ktFastPu6CaloJets")
process.kt6match.matched = cms.InputTag("kt6clean")
process.ktPu4match = process.patJetGenJetMatch.clone()
process.ktPu4match.src = cms.InputTag("ktPu4CaloJets")
process.ktPu4match.matched = cms.InputTag("kt4clean")
process.ktPu6match = process.patJetGenJetMatch.clone()
process.ktPu6match.src = cms.InputTag("ktPu6CaloJets")
process.ktPu6match.matched = cms.InputTag("kt6clean")

process.icPu5match = process.patJetGenJetMatch.clone()
process.icPu5match.src = cms.InputTag("iterativeConePu5CaloJets")
process.icPu5match.matched = cms.InputTag("ic5clean")
process.icPu7match = process.patJetGenJetMatch.clone()
process.icPu7match.src = cms.InputTag("iterativeConePu7CaloJets")
process.icPu7match.matched = cms.InputTag("ic7clean")

process.patJets.addJetCorrFactors = True
process.patJets.addGenPartonMatch   = False
process.patJets.addJetID            = False
process.patJets.addGenJetMatch      = True
process.patJets.embedGenJetMatch    = True
        
process.ak5patJets = process.patJets.clone()
process.ak5patJets.jetSource  = cms.InputTag("akFastPu5CaloJets")
process.ak5patJets.genJetMatch = cms.InputTag("ak5match")
process.ak5patJets.jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak5corr") )

process.ak7patJets = process.patJets.clone()
process.ak7patJets.jetSource  = cms.InputTag("akFastPu7CaloJets")
process.ak7patJets.genJetMatch = cms.InputTag("ak7match")
process.ak7patJets.jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak7corr") )

process.akPu5patJets = process.patJets.clone()
process.akPu5patJets.jetSource  = cms.InputTag("akPu5CaloJets")
process.akPu5patJets.genJetMatch = cms.InputTag("akPu5match")
process.akPu5patJets.jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu5corr") )

process.akPu7patJets = process.patJets.clone()
process.akPu7patJets.jetSource  = cms.InputTag("akPu7CaloJets")
process.akPu7patJets.genJetMatch = cms.InputTag("akPu7match")
process.akPu7patJets.jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu7corr") )

process.kt4patJets = process.patJets.clone()
process.kt4patJets.jetSource  = cms.InputTag("ktFastPu4CaloJets")
process.kt4patJets.genJetMatch = cms.InputTag("kt4match")
process.kt4patJets.jetCorrFactorsSource = cms.VInputTag(cms.InputTag("kt4corr") )

process.kt6patJets = process.patJets.clone()
process.kt6patJets.jetSource  = cms.InputTag("ktFastPu6CaloJets")
process.kt6patJets.genJetMatch = cms.InputTag("kt6match")
process.kt6patJets.jetCorrFactorsSource = cms.VInputTag(cms.InputTag("kt6corr") )

process.ktPu4patJets = process.patJets.clone()
process.ktPu4patJets.jetSource  = cms.InputTag("ktPu4CaloJets")
process.ktPu4patJets.genJetMatch = cms.InputTag("ktPu4match")
process.ktPu4patJets.jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ktPu4corr") )

process.ktPu6patJets = process.patJets.clone()
process.ktPu6patJets.jetSource  = cms.InputTag("ktPu6CaloJets")
process.ktPu6patJets.genJetMatch = cms.InputTag("ktPu6match")
process.ktPu6patJets.jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ktPu6corr") )

process.icPu5patJets = process.patJets.clone()
process.icPu5patJets.jetSource  = cms.InputTag("iterativeConePu5CaloJets")
process.icPu5patJets.genJetMatch = cms.InputTag("icPu5match")
process.icPu5patJets.jetCorrFactorsSource = cms.VInputTag(cms.InputTag("icPu5corr") )

process.icPu7patJets = process.patJets.clone()
process.icPu7patJets.jetSource  = cms.InputTag("iterativeConePu7CaloJets")
process.icPu7patJets.genJetMatch = cms.InputTag("icPu7match")
process.icPu7patJets.jetCorrFactorsSource = cms.VInputTag(cms.InputTag("icPu7corr") )

process.output = cms.OutputModule("PoolOutputModule",
                                  fileName = cms.untracked.string(ivars.output),
                                  outputCommands = cms.untracked.vstring(
    'drop *',
    'keep *_*FastPu*_*_JETS',
    'drop recoCaloJets_*_*_*',
    'keep recoGenJets_*_*_HISIGNAL',
    'keep *_heavyIon_*_*',
    'keep *_hiCentrality_*_*',
    'keep *_towerMaker_*_JETS',
    'keep patJets_*_*_*'
    )
                                  )

process.matches = cms.Path(
    process.ak5clean +
    process.ak7clean +
    process.kt4clean +
    process.kt6clean +
    process.ic5clean +
    process.ic7clean +

    process.ak5match +
    process.ak7match +
    process.akPu5match +
    process.akPu7match +

    process.kt4match +
    process.kt6match +
    process.ktPu4match +
    process.ktPu6match +

    process.icPu5match +
    process.icPu7match
    )

process.corrections = cms.Path(
    process.ak5corr+
    process.ak7corr+
    process.akPu5corr+
    process.akPu7corr+

    process.kt4corr+
    process.kt6corr+
    process.ktPu4corr+
    process.ktPu6corr+

    process.icPu5corr+
    process.icPu7corr
    )

process.pats = cms.Path(
    process.ak5patJets +
    process.ak7patJets +
    process.akPu5patJets +
    process.akPu7patJets +

    process.kt4patJets +
    process.kt6patJets +
    process.ktPu4patJets +
    process.ktPu6patJets +

    process.icPu5patJets +
    process.icPu7patJets
    )

process.out_step = cms.EndPath(process.output)
