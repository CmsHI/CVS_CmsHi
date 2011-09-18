import FWCore.ParameterSet.Config as cms

# Pat Jets
from PhysicsTools.PatAlgos.patHeavyIonSequences_cff import *
patJets.jetSource  = cms.InputTag("iterativeConePu5CaloJets")
patJets.addBTagInfo         = False
patJets.addTagInfos         = False
patJets.addDiscriminators   = False
patJets.addAssociatedTracks = False
patJets.addJetCharge        = False
patJets.addJetID            = False
patJets.getJetMCFlavour     = False
patJets.addGenPartonMatch   = True
patJets.addGenJetMatch      = True
patJets.embedGenJetMatch    = True
patJets.embedGenPartonMatch = True
patJets.embedCaloTowers	    = False


# full reco
icPu5corr = patJetCorrFactors.clone(
  src = cms.InputTag("iterativeConePu5CaloJets"),
  levels = cms.vstring('L2Relative','L3Absolute'),
  payload = cms.string('IC5Calo')
  )
icPu5patJets = patJets.clone(
  jetSource = cms.InputTag("iterativeConePu5CaloJets"),
  genJetMatch = cms.InputTag("icPu5match"),
  genPartonMatch = cms.InputTag("icPu5parton"),
  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("icPu5corr"))
  )

akPu5PFcorr = icPu5corr.clone(
  src = cms.InputTag("akPu5PFJets"),
  payload = cms.string('AK5PF')
  )
akPu5PFpatJets = patJets.clone(
  jetSource = cms.InputTag("akPu5PFJets"),
  genJetMatch = cms.InputTag("akPu5PFmatch"),
  genPartonMatch = cms.InputTag("akPu5PFparton"),
  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu5PFcorr"))
  )

akPu3PFcorr = icPu5corr.clone(
  src = cms.InputTag("akPu3PFJets"),
  payload = cms.string('AK3PF')
  )
akPu3PFpatJets = patJets.clone(
  jetSource = cms.InputTag("akPu3PFJets"),
  genJetMatch = cms.InputTag("akPu3PFmatch"),
  genPartonMatch = cms.InputTag("akPu3PFparton"),
  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu3PFcorr"))
  )

# === data sequences ===
# Note still need to use enableData function in cfg to remove mc dep of patjet
icPu5patSequence_data = cms.Sequence( icPu5corr * icPu5patJets )
akPu5PFpatSequence_data = cms.Sequence(akPu5PFcorr * akPu5PFpatJets )
akPu3PFpatSequence_data = cms.Sequence( akPu3PFcorr * akPu3PFpatJets )

# mc matching
patJetPartonMatch.matched = cms.InputTag("hiPartons")

icPu5clean = heavyIonCleanedGenJets.clone( src = cms.InputTag('iterativeCone5HiGenJets') )
icPu5match = patJetGenJetMatch.clone(
  src = cms.InputTag("iterativeConePu5CaloJets"),
  matched = cms.InputTag("icPu5clean")
  )
icPu5parton = patJetPartonMatch.clone(
  src = cms.InputTag("iterativeConePu5CaloJets")
	)


akPu5PFclean = heavyIonCleanedGenJets.clone( src = cms.InputTag('ak5HiGenJets') ) 
akPu5PFmatch = patJetGenJetMatch.clone(
  src = cms.InputTag("akPu5PFJets"),
  matched = cms.InputTag("akPu5PFclean")
  )
akPu5PFparton = patJetPartonMatch.clone(
  src = cms.InputTag("akPu5PFJets")
	)

akPu3PFclean = heavyIonCleanedGenJets.clone( src = cms.InputTag('ak3HiGenJets') ) 
akPu3PFmatch = patJetGenJetMatch.clone(
  src = cms.InputTag("akPu3PFJets"),
  matched = cms.InputTag("akPu3PFclean")
  )
akPu3PFparton = patJetPartonMatch.clone(
  src = cms.InputTag("akPu3PFJets")
	)

# === mc sequences ===
icPu5patSequence = cms.Sequence(icPu5corr * icPu5clean * icPu5match * icPu5parton * icPu5patJets)
akPu5PFpatSequence = cms.Sequence(akPu5PFcorr * akPu5PFclean * akPu5PFmatch * akPu5PFparton * akPu5PFpatJets)
akPu3PFpatSequence = cms.Sequence(akPu3PFcorr * akPu3PFclean * akPu3PFmatch * akPu3PFparton * akPu3PFpatJets)

# Pat Photon
from PhysicsTools.PatAlgos.producersHeavyIons.heavyIonPhotons_cff import *
from PhysicsTools.PatAlgos.producersLayer1.photonProducer_cff import *
from PhysicsTools.PatAlgos.selectionLayer1.photonSelector_cfi import selectedPatPhotons
from RecoHI.HiEgammaAlgos.HiEgammaIsolation_cff import * # (must be decleared after PAT sequence Yen-Jie)

# from PhysicsTools/PatAlgos/python/tools/heavyIonTools.py
photonMatch.matched = cms.InputTag("hiGenParticles")
patPhotons.addPhotonID   = cms.bool(True)
patPhotons.addGenMatch   = cms.bool(True)
patPhotons.embedGenMatch = cms.bool(True)
patPhotons.userData.userFloats.src  = cms.VInputTag(
    cms.InputTag( "isoCC1"),cms.InputTag( "isoCC2"),cms.InputTag( "isoCC3"),cms.InputTag( "isoCC4"),cms.InputTag("isoCC5"),
    cms.InputTag( "isoCR1"),cms.InputTag( "isoCR2"),cms.InputTag( "isoCR3"),cms.InputTag( "isoCR4"),cms.InputTag("isoCR5"),
    cms.InputTag( "isoT11"),cms.InputTag( "isoT12"),cms.InputTag( "isoT13"),cms.InputTag( "isoT14"),  
    cms.InputTag( "isoT21"),cms.InputTag( "isoT22"),cms.InputTag( "isoT23"),cms.InputTag( "isoT24"),  
    cms.InputTag( "isoT31"),cms.InputTag( "isoT32"),cms.InputTag( "isoT33"),cms.InputTag( "isoT34"),  
    cms.InputTag( "isoT41"),cms.InputTag( "isoT42"),cms.InputTag( "isoT43"),cms.InputTag( "isoT44"),  
    cms.InputTag("isoDR11"),cms.InputTag("isoDR12"),cms.InputTag("isoDR13"),cms.InputTag("isoDR14"),  
    cms.InputTag("isoDR21"),cms.InputTag("isoDR22"),cms.InputTag("isoDR23"),cms.InputTag("isoDR24"),  
    cms.InputTag("isoDR31"),cms.InputTag("isoDR32"),cms.InputTag("isoDR33"),cms.InputTag("isoDR34"),  
    cms.InputTag("isoDR41"),cms.InputTag("isoDR42"),cms.InputTag("isoDR43"),cms.InputTag("isoDR44")
    )
patPhotons.photonIDSource = cms.InputTag("PhotonIDProd","PhotonCutBasedIDLoose")
del patPhotons.photonIDSources

# pat photon selection
selectedPatPhotons.cut = cms.string('pt > 0. & abs(eta) < 12.')

makeHeavyIonPhotons = cms.Sequence(
  # reco pre-production
  hiEgammaIsolationSequence *
  patPhotonIsolation *
  # pat and HI specifics    
  photonMatch *
  # object production
  patPhotons *
  selectedPatPhotons
  )
