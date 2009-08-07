import FWCore.ParameterSet.Config as cms

from CmsHi.HiPatAlgos.HiPatPhotonSequence_cfi import *
from CmsHi.HiPatAlgos.HiPatJetSequence_cfi import *
from CmsHi.HiPatAlgos.HiPatMuonSequence_cfi import *

hiPatProductionSequence = cms.Sequence(
    hiPatJetSequence *
    hiPatPhotonSequence *
    hiPatMuonSequence
    )

hiPatSelectionSequence = cms.Sequence(
    selectedLayer1Muons +
    selectedLayer1Photons +
    selectedLayer1Jets
    )

#####################################################
#
# Event Content
#

hiPatEventContent = cms.PSet(
    outputCommands = cms.untracked.vstring('drop *',
                                           'keep patPhotons_selected*_*_*',
                                           'keep patMuons_selected*_*_*',
                                           'keep patJets_selected*_*_*',
                                           'keep recoCentrality_*_*_*',
                                           'keep recoEvtPlane_*_*_*',
                                           'keep recoTracks_hiGeneralTracks_*_*'
                                           )
            )

hiPatExtra = cms.PSet( outputCommands = cms.untracked.vstring('keep *_hiGenParticles_*_*'))

hiPatExtraEventContent = hiPatEventContent.clone()
hiPatExtraEventContent.outputCommands.extend(hiPatExtra.outputCommands)

