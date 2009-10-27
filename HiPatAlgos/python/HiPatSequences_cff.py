import FWCore.ParameterSet.Config as cms

from CmsHi.HiPatAlgos.HiPatPhotonSequence_cfi import *
from CmsHi.HiPatAlgos.HiPatJetSequence_cfi import *
from CmsHi.HiPatAlgos.HiPatMuonSequence_cfi import *
from CmsHi.HiPatAlgos.heavyIon_cfi import *
#from RecoHI.HiTracking.HISelectedTracks_cfi import *

hiPatProductionSequence = cms.Sequence(
    heavyIon *
    hiPatJetSequence *
    hiPatPhotonSequence *
    hiPatMuonSequence
    )

hiPatSelectionSequence = cms.Sequence(
#    hiSelectedTracks +
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
                                           'keep patHeavyIon_heavyIon_*_*'
                                           )
    )

hiPatExtra = cms.PSet( outputCommands = cms.untracked.vstring('keep recoGenParticles_hiGenParticles_*_*',
                                                              'keep recoGenJets_iterativeCone5HiGenJets_*_*', # until a better solution
                                                              'keep recoTracks_hiSelectedTracks_*_*'
                                                              ))

hiPatExtraEventContent = hiPatEventContent.clone()
hiPatExtraEventContent.outputCommands.extend(hiPatExtra.outputCommands)

