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


patJetCorrFactors.useNPV = False
# full reco
icPu5corr = patJetCorrFactors.clone(
  src = cms.InputTag("iterativeConePu5CaloJets"),
  levels = cms.vstring('L2Relative','L3Absolute'),
  payload = cms.string('IC5Calo_2760GeV')
  )

#icPu5patJets = patJets.clone(
#  jetSource = cms.InputTag("iterativeConePu5CaloJets"),
#  genJetMatch = cms.InputTag("icPu5match"),
#  genPartonMatch = cms.InputTag("icPu5parton"),
#  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("icPu5corr"))
#  )

akPu5PFcorr = icPu5corr.clone(
  src = cms.InputTag("akPu5PFJets"),
  payload = cms.string('AK5PFTowers_hiGoodTightTracks')
  )
akPu5PFpatJets = patJets.clone(
  jetSource = cms.InputTag("akPu5PFJets"),
  genJetMatch = cms.InputTag("akPu5PFmatch"),
  genPartonMatch = cms.InputTag("akPu5PFparton"),
  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu5PFcorr"))
  )

akPu3PFcorr = icPu5corr.clone(
  src = cms.InputTag("akPu3PFJets"),
  payload = cms.string('AK3PFTowers_hiGoodTightTracks')
  )

#akPu3PFpatJets = patJets.clone(
#  jetSource = cms.InputTag("akPu3PFJets"),
#  genJetMatch = cms.InputTag("akPu3PFmatch"),
#  genPartonMatch = cms.InputTag("akPu3PFparton"),
#  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu3PFcorr"))
#  )

akPu5corr = icPu5corr.clone(
    src = cms.InputTag("akPu5CaloJets"),
    payload = cms.string('AK5Calo')
    )

akPu5patJets = patJets.clone(
    jetSource = cms.InputTag("akPu5CaloJets"),
    genJetMatch = cms.InputTag("akPu5match"),
    genPartonMatch = cms.InputTag("akPu5parton"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu5corr"))
    )

akPu3corr = icPu5corr.clone(
    src = cms.InputTag("akPu3CaloJets"),
    payload = cms.string('AK5Calo')
    )

akPu3patJets = patJets.clone(
    jetSource = cms.InputTag("akPu3CaloJets"),
    genJetMatch = cms.InputTag("akPu3match"),
    genPartonMatch = cms.InputTag("akPu3parton"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu3corr"))
    )



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

akPu5match = patJetGenJetMatch.clone(
    src = cms.InputTag("akPu5CaloJets"),
    matched = cms.InputTag("akPu5PFclean")
    )
akPu5parton = patJetPartonMatch.clone(
    src = cms.InputTag("akPu5CaloJets")
    )

akPu3match = patJetGenJetMatch.clone(
    src = cms.InputTag("akPu3CaloJets"),
    matched = cms.InputTag("akPu3PFclean")
    )
akPu3parton = patJetPartonMatch.clone(
    src = cms.InputTag("akPu3CaloJets")
    )

from RecoJets.JetAssociationProducers.ak5JTA_cff import *
from RecoBTag.Configuration.RecoBTag_cff import *
# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ calo jet
#### b-tagging:
# b-tagging general configuration
# @@@@@@@@@ calo jet
#### b-tagging:
# b-tagging general configuration
icPu5JetTracksAssociatorAtVertex        = ak5JetTracksAssociatorAtVertex.clone()
icPu5JetTracksAssociatorAtVertex.jets   = cms.InputTag("iterativeConePu5CaloJets")
icPu5JetTracksAssociatorAtVertex.tracks = cms.InputTag("hiSelectedTracks")

# impact parameter b-tag
icPu5ImpactParameterTagInfos                = impactParameterTagInfos.clone()
icPu5ImpactParameterTagInfos.jetTracks      = cms.InputTag("icPu5JetTracksAssociatorAtVertex")
icPu5ImpactParameterTagInfos.primaryVertex  = cms.InputTag("hiSelectedVertex")

icPu5TrackCountingHighEffBJetTags          = trackCountingHighEffBJetTags.clone()
icPu5TrackCountingHighEffBJetTags.tagInfos = cms.VInputTag(cms.InputTag("icPu5ImpactParameterTagInfos"))
icPu5TrackCountingHighPurBJetTags          = trackCountingHighPurBJetTags.clone()
icPu5TrackCountingHighPurBJetTags.tagInfos = cms.VInputTag(cms.InputTag("icPu5ImpactParameterTagInfos"))
icPu5JetProbabilityBJetTags                = jetProbabilityBJetTags.clone()
icPu5JetProbabilityBJetTags.tagInfos       = cms.VInputTag(cms.InputTag("icPu5ImpactParameterTagInfos"))
icPu5JetBProbabilityBJetTags               = jetBProbabilityBJetTags.clone()
icPu5JetBProbabilityBJetTags.tagInfos      = cms.VInputTag(cms.InputTag("icPu5ImpactParameterTagInfos"))

# secondary vertex b-tag
icPu5SecondaryVertexTagInfos                     = secondaryVertexTagInfos.clone()
icPu5SecondaryVertexTagInfos.trackIPTagInfos     = cms.InputTag("icPu5ImpactParameterTagInfos")
icPu5SimpleSecondaryVertexBJetTags               = simpleSecondaryVertexBJetTags.clone()
icPu5SimpleSecondaryVertexBJetTags.tagInfos      = cms.VInputTag(cms.InputTag("icPu5SecondaryVertexTagInfos"))
icPu5CombinedSecondaryVertexBJetTags             = combinedSecondaryVertexBJetTags.clone()
icPu5CombinedSecondaryVertexBJetTags.tagInfos    = cms.VInputTag(cms.InputTag("icPu5ImpactParameterTagInfos"),
                                                                         cms.InputTag("icPu5SecondaryVertexTagInfos"))
icPu5CombinedSecondaryVertexMVABJetTags          = combinedSecondaryVertexMVABJetTags.clone()
icPu5CombinedSecondaryVertexMVABJetTags.tagInfos = cms.VInputTag(cms.InputTag("icPu5ImpactParameterTagInfos"),
                                                                         cms.InputTag("icPu5SecondaryVertexTagInfos"))

# soft muon b-tag
icPu5SoftMuonTagInfos                = softMuonTagInfos.clone()
icPu5SoftMuonTagInfos.jets           = cms.InputTag("iterativeConePu5CaloJets")
icPu5SoftMuonTagInfos.primaryVertex  = cms.InputTag("hiSelectedVertex")
icPu5SoftMuonBJetTags                = softMuonBJetTags.clone()
icPu5SoftMuonBJetTags.tagInfos       = cms.VInputTag(cms.InputTag("icPu5SoftMuonTagInfos"))
icPu5SoftMuonByIP3dBJetTags          = softMuonByIP3dBJetTags.clone()
icPu5SoftMuonByIP3dBJetTags.tagInfos = cms.VInputTag(cms.InputTag("icPu5SoftMuonTagInfos"))
icPu5SoftMuonByPtBJetTags            = softMuonByPtBJetTags.clone()
icPu5SoftMuonByPtBJetTags.tagInfos   = cms.VInputTag(cms.InputTag("icPu5SoftMuonTagInfos"))

# ghost tracks
icPu5GhostTrackVertexTagInfos                 = ghostTrackVertexTagInfos.clone()
icPu5GhostTrackVertexTagInfos.trackIPTagInfos = cms.InputTag("icPu5ImpactParameterTagInfos")
icPu5GhostTrackBJetTags                       = ghostTrackBJetTags.clone()
icPu5GhostTrackBJetTags.tagInfos              = cms.VInputTag(cms.InputTag("icPu5ImpactParameterTagInfos"),
                                                                      cms.InputTag("icPu5GhostTrackVertexTagInfos"))
# prepare a path running the new modules
icPu5JetTracksAssociator = cms.Sequence(icPu5JetTracksAssociatorAtVertex)
icPu5JetBtaggingIP       = cms.Sequence(icPu5ImpactParameterTagInfos * (icPu5TrackCountingHighEffBJetTags +
                                                                                        icPu5TrackCountingHighPurBJetTags +
                                                                                        icPu5JetProbabilityBJetTags +
                                                                                        icPu5JetBProbabilityBJetTags
                                                                                        )
                                                )

icPu5JetBtaggingSV = cms.Sequence(icPu5ImpactParameterTagInfos *
                                          icPu5SecondaryVertexTagInfos * (icPu5SimpleSecondaryVertexBJetTags +
                                                                                  icPu5CombinedSecondaryVertexBJetTags +
                                                                                  icPu5CombinedSecondaryVertexMVABJetTags
                                                                                  )
                                          +icPu5GhostTrackVertexTagInfos
                                          *icPu5GhostTrackBJetTags
                                          )


icPu5JetBtaggingMu = cms.Sequence(icPu5SoftMuonTagInfos * (icPu5SoftMuonBJetTags +
                                                                           icPu5SoftMuonByIP3dBJetTags +
                                                                           icPu5SoftMuonByPtBJetTags
                                                                           )
                                          )

icPu5JetBtagging = cms.Sequence(icPu5JetBtaggingIP 
                                        *icPu5JetBtaggingSV 
                                        *icPu5JetBtaggingMu
                                        )
#----------------------


#----------------------
icPu5corr    = patJetCorrFactors.clone(src      = cms.InputTag("iterativeConePu5CaloJets"),
                                                       levels   = cms.vstring('L2Relative','L3Absolute'),
                                                       payload  = cms.string('IC5Calo_2760GeV'))
icPu5clean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('iterativeCone5HiGenJets')) # cleans the jets, but NOT the partons
icPu5match   = patJetGenJetMatch.clone(src      = cms.InputTag("iterativeConePu5CaloJets"),
                                                       matched  = cms.InputTag("icPu5clean"))

icPu5parton  = patJetPartonMatch.clone(src      = cms.InputTag("iterativeConePu5CaloJets"))

# ----- flavour bit
icPu5PatJetPartonAssociation       = patJetPartonAssociation.clone(jets    = cms.InputTag("iterativeConePu5CaloJets"),
                                                                                   partons = cms.InputTag("genPartons"),
                                                                                   coneSizeToAssociate = cms.double(0.4))
icPu5PatJetFlavourAssociation      = patJetFlavourAssociation.clone(srcByReference = cms.InputTag("icPu5PatJetPartonAssociation"))

icPu5PatJetFlavourId               = cms.Sequence(icPu5PatJetPartonAssociation*icPu5PatJetFlavourAssociation)

#-------

icPu5patJets = patJets.clone(jetSource            = cms.InputTag("iterativeConePu5CaloJets"),
                                             genJetMatch          = cms.InputTag("icPu5match"),
                                             genPartonMatch       = cms.InputTag("icPu5parton"),
                                             jetCorrFactorsSource = cms.VInputTag(cms.InputTag("icPu5corr")),
                                             JetPartonMapSource   = cms.InputTag("icPu5PatJetFlavourAssociation"),
                                             trackAssociationSource = cms.InputTag("icPu5JetTracksAssociatorAtVertex"),
                                             discriminatorSources = cms.VInputTag(cms.InputTag("icPu5CombinedSecondaryVertexBJetTags"),
                                                                                  cms.InputTag("icPu5CombinedSecondaryVertexMVABJetTags"),
                                                                                  cms.InputTag("icPu5JetBProbabilityBJetTags"),
                                                                                  cms.InputTag("icPu5JetProbabilityBJetTags"),
                                                                                  cms.InputTag("icPu5SoftMuonByPtBJetTags"),                
                                                                                  cms.InputTag("icPu5SoftMuonByIP3dBJetTags"),
                                                                                  cms.InputTag("icPu5TrackCountingHighEffBJetTags"),
                                                                                  cms.InputTag("icPu5TrackCountingHighPurBJetTags"),
                                                                                  ),
                                             )


#### B-tagging for this bit:
# b-tagging general configuration
akPu3PFJetTracksAssociatorAtVertex        = ak5JetTracksAssociatorAtVertex.clone()
akPu3PFJetTracksAssociatorAtVertex.jets   = cms.InputTag("akPu3PFJets")
akPu3PFJetTracksAssociatorAtVertex.tracks = cms.InputTag("hiSelectedTracks")
# impact parameter b-tag
akPu3PFImpactParameterTagInfos               = impactParameterTagInfos.clone()
akPu3PFImpactParameterTagInfos.jetTracks     = cms.InputTag("akPu3PFJetTracksAssociatorAtVertex")
akPu3PFImpactParameterTagInfos.primaryVertex = cms.InputTag("hiSelectedVertex")
akPu3PFTrackCountingHighEffBJetTags          = trackCountingHighEffBJetTags.clone()
akPu3PFTrackCountingHighEffBJetTags.tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"))
akPu3PFTrackCountingHighPurBJetTags          = trackCountingHighPurBJetTags.clone()
akPu3PFTrackCountingHighPurBJetTags.tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"))
akPu3PFJetProbabilityBJetTags                = jetProbabilityBJetTags.clone()
akPu3PFJetProbabilityBJetTags.tagInfos       = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"))
akPu3PFJetBProbabilityBJetTags               = jetBProbabilityBJetTags.clone()
akPu3PFJetBProbabilityBJetTags.tagInfos      = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"))

# secondary vertex b-tag
akPu3PFSecondaryVertexTagInfos                     = secondaryVertexTagInfos.clone()
akPu3PFSecondaryVertexTagInfos.trackIPTagInfos     = cms.InputTag("akPu3PFImpactParameterTagInfos")
akPu3PFSimpleSecondaryVertexBJetTags               = simpleSecondaryVertexBJetTags.clone()
akPu3PFSimpleSecondaryVertexBJetTags.tagInfos      = cms.VInputTag(cms.InputTag("akPu3PFSecondaryVertexTagInfos"))
akPu3PFCombinedSecondaryVertexBJetTags             = combinedSecondaryVertexBJetTags.clone()
akPu3PFCombinedSecondaryVertexBJetTags.tagInfos    = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"), 
                                                                           cms.InputTag("akPu3PFSecondaryVertexTagInfos"))
akPu3PFCombinedSecondaryVertexMVABJetTags          = combinedSecondaryVertexMVABJetTags.clone()
akPu3PFCombinedSecondaryVertexMVABJetTags.tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"), 
                                                                           cms.InputTag("akPu3PFSecondaryVertexTagInfos"))

# soft muon b-tag
akPu3PFSoftMuonTagInfos                = softMuonTagInfos.clone()
akPu3PFSoftMuonTagInfos.jets           = cms.InputTag("akPu3PFJets")
akPu3PFSoftMuonTagInfos.primaryVertex  = cms.InputTag("hiSelectedVertex")
akPu3PFSoftMuonBJetTags                = softMuonBJetTags.clone()
akPu3PFSoftMuonBJetTags.tagInfos       = cms.VInputTag(cms.InputTag("akPu3PFSoftMuonTagInfos"))
akPu3PFSoftMuonByIP3dBJetTags          = softMuonByIP3dBJetTags.clone()
akPu3PFSoftMuonByIP3dBJetTags.tagInfos = cms.VInputTag(cms.InputTag("akPu3PFSoftMuonTagInfos"))
akPu3PFSoftMuonByPtBJetTags            = softMuonByPtBJetTags.clone()
akPu3PFSoftMuonByPtBJetTags.tagInfos   = cms.VInputTag(cms.InputTag("akPu3PFSoftMuonTagInfos"))

# ghost tracks
akPu3PFGhostTrackVertexTagInfos                 = ghostTrackVertexTagInfos.clone()
akPu3PFGhostTrackVertexTagInfos.trackIPTagInfos = cms.InputTag("akPu3PFImpactParameterTagInfos")
akPu3PFGhostTrackBJetTags                       = ghostTrackBJetTags.clone()
akPu3PFGhostTrackBJetTags.tagInfos              = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"),
                                                                        cms.InputTag("akPu3PFGhostTrackVertexTagInfos"))
# prepare a path running the new modules
akPu3PFJetTracksAssociator = cms.Sequence(akPu3PFJetTracksAssociatorAtVertex)
akPu3PFJetBtaggingIP       = cms.Sequence(akPu3PFImpactParameterTagInfos * (akPu3PFTrackCountingHighEffBJetTags +
                                                                                        akPu3PFTrackCountingHighPurBJetTags +
                                                                                        akPu3PFJetProbabilityBJetTags +
                                                                                        akPu3PFJetBProbabilityBJetTags
                                                                                        )
                                                )

akPu3PFJetBtaggingSV = cms.Sequence(akPu3PFImpactParameterTagInfos *
                                          akPu3PFSecondaryVertexTagInfos * (akPu3PFSimpleSecondaryVertexBJetTags +
                                                                                  akPu3PFCombinedSecondaryVertexBJetTags +
                                                                                  akPu3PFCombinedSecondaryVertexMVABJetTags
                                                                                  )
                                          +akPu3PFGhostTrackVertexTagInfos
                                          *akPu3PFGhostTrackBJetTags
                                          )


akPu3PFJetBtaggingMu = cms.Sequence(akPu3PFSoftMuonTagInfos * (akPu3PFSoftMuonBJetTags +
                                                                           akPu3PFSoftMuonByIP3dBJetTags +
                                                                           akPu3PFSoftMuonByPtBJetTags
                                                                           )
                                          )

akPu3PFJetBtagging = cms.Sequence(akPu3PFJetBtaggingIP 
                                        *akPu3PFJetBtaggingSV 
                                        *akPu3PFJetBtaggingMu
                                        )

#__________________________________________________________
# ----- flavour bit
akPu3PFPatJetPartonAssociation       = patJetPartonAssociation.clone(jets    = cms.InputTag("akPu3PFJets"),
                                                                                     partons = cms.InputTag("genPartons"),
                                                                                     coneSizeToAssociate = cms.double(0.4))
akPu3PFPatJetFlavourAssociation      = patJetFlavourAssociation.clone(srcByReference = cms.InputTag("akPu3PFPatJetPartonAssociation"))

akPu3PFPatJetFlavourId               = cms.Sequence(akPu3PFPatJetPartonAssociation*akPu3PFPatJetFlavourAssociation)
#
#-------
akPu3PFcorr = patJetCorrFactors.clone(src     = cms.InputTag("akPu3PFJets"),
                                      levels  = cms.vstring('L2Relative','L3Absolute'),
                                      payload = cms.string('AK3PFTowers_hiGoodTightTracks')
                                                      )
akPu3PFclean   = heavyIonCleanedGenJets.clone(src = cms.InputTag('ak3HiGenJets'))
akPu3PFmatch   = patJetGenJetMatch.clone(src      = cms.InputTag("akPu3PFJets"),
                                                         matched  = cms.InputTag("akPu3PFclean"))
akPu3PFparton  = patJetPartonMatch.clone(src      = cms.InputTag("akPu3PFJets"))
akPu3PFpatJets = patJets.clone(jetSource            = cms.InputTag("akPu3PFJets"),
                                               genJetMatch          = cms.InputTag("akPu3PFmatch"),
                                               genPartonMatch       = cms.InputTag("akPu3PFparton"),
                                               jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu3PFcorr")),
                                               JetPartonMapSource   = cms.InputTag("akPu3PFPatJetFlavourAssociation"),
                                               trackAssociationSource = cms.InputTag("akPu3PFJetTracksAssociatorAtVertex"),
                                               discriminatorSources = cms.VInputTag(cms.InputTag("akPu3PFCombinedSecondaryVertexBJetTags"),
                                                                                    cms.InputTag("akPu3PFCombinedSecondaryVertexMVABJetTags"),
                                                                                    cms.InputTag("akPu3PFJetBProbabilityBJetTags"),
                                                                                    cms.InputTag("akPu3PFJetProbabilityBJetTags"),
                                                                                    cms.InputTag("akPu3PFSoftMuonByPtBJetTags"),                
                                                                                    cms.InputTag("akPu3PFSoftMuonByIP3dBJetTags"),
                                                                                    cms.InputTag("akPu3PFTrackCountingHighEffBJetTags"),
                                                                                    cms.InputTag("akPu3PFTrackCountingHighPurBJetTags"),
                                                                                    ),
                                               )

# end batagging


# === mc sequences ===
icPu5patSequence = cms.Sequence(icPu5corr * icPu5clean * icPu5match * icPu5parton  *  icPu5patJets)
akPu5PFpatSequence = cms.Sequence(akPu5PFcorr * akPu5PFclean * akPu5PFmatch * akPu5PFparton * akPu5PFpatJets)
akPu3PFpatSequence = cms.Sequence(akPu3PFcorr * akPu3PFclean * akPu3PFmatch * akPu3PFparton * akPu3PFpatJets)
akPu5patSequence = cms.Sequence(akPu5corr * akPu5PFclean * akPu5match * akPu5parton * akPu5patJets)
akPu3patSequence = cms.Sequence(akPu3corr * akPu3PFclean * akPu3match * akPu3parton * akPu3patJets)

icPu5patSequence_withBtagging = cms.Sequence(icPu5corr * icPu5clean * icPu5match * icPu5parton  * icPu5PatJetFlavourId * icPu5JetTracksAssociator * icPu5JetBtagging * icPu5patJets)
akPu3PFpatSequence_withBtagging = cms.Sequence(akPu3PFcorr * akPu3PFclean * akPu3PFmatch * akPu3PFparton * akPu3PFPatJetFlavourId * akPu3PFJetTracksAssociator *akPu3PFJetBtagging * akPu3PFpatJets)


# === data sequences ===
# Note still need to use enableData function in cfg to remove mc dep of patjet
icPu5patSequence_data = cms.Sequence( icPu5corr * icPu5patJets )
akPu5PFpatSequence_data = cms.Sequence(akPu5PFcorr * akPu5PFpatJets )
akPu3PFpatSequence_data = cms.Sequence( akPu3PFcorr * akPu3PFpatJets )
akPu5patSequence_data = cms.Sequence( akPu5corr * akPu5patJets )
akPu3patSequence_data = cms.Sequence( akPu3corr * akPu3patJets )

icPu5patSequence_withBtagging_data = cms.Sequence( icPu5corr * icPu5JetTracksAssociator * icPu5JetBtagging * icPu5JetTracksAssociator * icPu5JetBtagging * icPu5patJets )
akPu3PFpatSequence_withBtagging_data = cms.Sequence( akPu3PFcorr * akPu3PFJetTracksAssociator *akPu3PFJetBtagging * akPu3PFJetTracksAssociator *akPu3PFJetBtagging * akPu3PFpatJets )


# AK Algorithms


akPu6PFJets = akPu3PFJets.clone(rParam = 0.6)
akPu6CaloJets = akPu3CaloJets.clone(rParam = 0.6)
akPu4PFJets = akPu3PFJets.clone(rParam = 0.4)
akPu4CaloJets = akPu3CaloJets.clone(rParam = 0.4)
akPu2PFJets = akPu3PFJets.clone(rParam = 0.2)
akPu2CaloJets = akPu3CaloJets.clone(rParam = 0.2)
akPu1PFJets = akPu3PFJets.clone(rParam = 0.1)
akPu1CaloJets = akPu3CaloJets.clone(rParam = 0.1)

iterativeCone5CaloJets = iterativeConePu5CaloJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak6PFJets = akPu6PFJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak6CaloJets = akPu6CaloJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak5PFJets = akPu5PFJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak5CaloJets = akPu5CaloJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak4PFJets = akPu4PFJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak4CaloJets = akPu4CaloJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak3PFJets = akPu3PFJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak3CaloJets = akPu3CaloJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak2PFJets = akPu2PFJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak2CaloJets = akPu2CaloJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak1PFJets = akPu1PFJets.clone(doPUOffsetCorr = False, jetPtMin = 1)
ak1CaloJets = akPu1CaloJets.clone(doPUOffsetCorr = False, jetPtMin = 1)


recoAllJets = cms.Sequence(akPu1PFJets * akPu2PFJets *akPu3PFJets * akPu4PFJets * akPu5PFJets * akPu6PFJets *
                           ak1PFJets * ak2PFJets *ak3PFJets * ak4PFJets * ak5PFJets * ak6PFJets *
                           akPu1CaloJets * akPu2CaloJets *akPu3CaloJets * akPu4CaloJets * akPu5CaloJets * akPu6CaloJets *
                           ak1CaloJets * ak2CaloJets *ak3CaloJets * ak4CaloJets * ak5CaloJets * ak6CaloJets *
                           
                           )
                           


# All corrections


akPu1PFcorr = akPu3PFcorr.clone(src = cms.InputTag("akPu1PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))
akPu2PFcorr = akPu3PFcorr.clone(src = cms.InputTag("akPu2PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))
akPu3PFcorr = akPu3PFcorr.clone(src = cms.InputTag("akPu3PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))
akPu4PFcorr = akPu3PFcorr.clone(src = cms.InputTag("akPu4PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))
akPu5PFcorr = akPu3PFcorr.clone(src = cms.InputTag("akPu5PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))
akPu6PFcorr = akPu3PFcorr.clone(src = cms.InputTag("akPu6PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))

ak1PFcorr = akPu3PFcorr.clone(src = cms.InputTag("ak1PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))
ak2PFcorr = akPu3PFcorr.clone(src = cms.InputTag("ak2PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))
ak3PFcorr = akPu3PFcorr.clone(src = cms.InputTag("ak3PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))
ak4PFcorr = akPu3PFcorr.clone(src = cms.InputTag("ak4PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))
ak5PFcorr = akPu3PFcorr.clone(src = cms.InputTag("ak5PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))
ak6PFcorr = akPu3PFcorr.clone(src = cms.InputTag("ak6PFJets"),payload = cms.string('AK3PFTowers_hiGoodTightTracks'))

akPu1Calocorr = akPu3PFcorr.clone(src = cms.InputTag("akPu1CaloJets"),payload = cms.string('AK5Calo'))
akPu2Calocorr = akPu3PFcorr.clone(src = cms.InputTag("akPu2CaloJets"),payload = cms.string('AK5Calo'))
akPu3Calocorr = akPu3PFcorr.clone(src = cms.InputTag("akPu3CaloJets"),payload = cms.string('AK5Calo'))
akPu4Calocorr = akPu3PFcorr.clone(src = cms.InputTag("akPu4CaloJets"),payload = cms.string('AK5Calo'))
akPu5Calocorr = akPu3PFcorr.clone(src = cms.InputTag("akPu5CaloJets"),payload = cms.string('AK5Calo'))
akPu6Calocorr = akPu3PFcorr.clone(src = cms.InputTag("akPu6CaloJets"),payload = cms.string('AK5Calo'))

ak1Calocorr = akPu3PFcorr.clone(src = cms.InputTag("ak1CaloJets"),payload = cms.string('AK5Calo'))
ak2Calocorr = akPu3PFcorr.clone(src = cms.InputTag("ak2CaloJets"),payload = cms.string('AK5Calo'))
ak3Calocorr = akPu3PFcorr.clone(src = cms.InputTag("ak3CaloJets"),payload = cms.string('AK5Calo'))
ak4Calocorr = akPu3PFcorr.clone(src = cms.InputTag("ak4CaloJets"),payload = cms.string('AK5Calo'))
ak5Calocorr = akPu3PFcorr.clone(src = cms.InputTag("ak5CaloJets"),payload = cms.string('AK5Calo'))
ak6Calocorr = akPu3PFcorr.clone(src = cms.InputTag("ak6CaloJets"),payload = cms.string('AK5Calo'))

# Gen stuff

ak1clean = akPu3PFclean.clone()
ak2clean = akPu3PFclean.clone()
ak3clean = akPu3PFclean.clone()
ak4clean = akPu3PFclean.clone()
ak5clean = akPu3PFclean.clone()
ak6clean = akPu3PFclean.clone()


akPu1PFmatch = akPu3PFmatch.clone(src = cms.InputTag("akPu1PFJets"), matched = cms.InputTag("ak1clean"))
akPu2PFmatch = akPu3PFmatch.clone(src = cms.InputTag("akPu2PFJets"), matched = cms.InputTag("ak2clean"))
akPu3PFmatch = akPu3PFmatch.clone(src = cms.InputTag("akPu3PFJets"), matched = cms.InputTag("ak3clean"))
akPu4PFmatch = akPu3PFmatch.clone(src = cms.InputTag("akPu4PFJets"), matched = cms.InputTag("ak4clean"))
akPu5PFmatch = akPu3PFmatch.clone(src = cms.InputTag("akPu5PFJets"), matched = cms.InputTag("ak5clean"))
akPu6PFmatch = akPu3PFmatch.clone(src = cms.InputTag("akPu6PFJets"), matched = cms.InputTag("ak6clean"))
akPu1Calomatch = akPu3PFmatch.clone(src = cms.InputTag("akPu1CaloJets"), matched = cms.InputTag("ak1clean"))
akPu2Calomatch = akPu3PFmatch.clone(src = cms.InputTag("akPu2CaloJets"), matched = cms.InputTag("ak2clean"))
akPu3Calomatch = akPu3PFmatch.clone(src = cms.InputTag("akPu3CaloJets"), matched = cms.InputTag("ak3clean"))
akPu4Calomatch = akPu3PFmatch.clone(src = cms.InputTag("akPu4CaloJets"), matched = cms.InputTag("ak4clean"))
akPu5Calomatch = akPu3PFmatch.clone(src = cms.InputTag("akPu5CaloJets"), matched = cms.InputTag("ak5clean"))
akPu6Calomatch = akPu3PFmatch.clone(src = cms.InputTag("akPu6CaloJets"), matched = cms.InputTag("ak6clean"))
ak1PFmatch = akPu3PFmatch.clone(src = cms.InputTag("ak1PFJets"), matched = cms.InputTag("ak1clean"))
ak2PFmatch = akPu3PFmatch.clone(src = cms.InputTag("ak2PFJets"), matched = cms.InputTag("ak2clean"))
ak3PFmatch = akPu3PFmatch.clone(src = cms.InputTag("ak3PFJets"), matched = cms.InputTag("ak3clean"))
ak4PFmatch = akPu3PFmatch.clone(src = cms.InputTag("ak4PFJets"), matched = cms.InputTag("ak4clean"))
ak5PFmatch = akPu3PFmatch.clone(src = cms.InputTag("ak5PFJets"), matched = cms.InputTag("ak5clean"))
ak6PFmatch = akPu3PFmatch.clone(src = cms.InputTag("ak6PFJets"), matched = cms.InputTag("ak6clean"))
ak1Calomatch = akPu3PFmatch.clone(src = cms.InputTag("ak1CaloJets"), matched = cms.InputTag("ak1clean"))
ak2Calomatch = akPu3PFmatch.clone(src = cms.InputTag("ak2CaloJets"), matched = cms.InputTag("ak2clean"))
ak3Calomatch = akPu3PFmatch.clone(src = cms.InputTag("ak3CaloJets"), matched = cms.InputTag("ak3clean"))
ak4Calomatch = akPu3PFmatch.clone(src = cms.InputTag("ak4CaloJets"), matched = cms.InputTag("ak4clean"))
ak5Calomatch = akPu3PFmatch.clone(src = cms.InputTag("ak5CaloJets"), matched = cms.InputTag("ak5clean"))
ak6Calomatch = akPu3PFmatch.clone(src = cms.InputTag("ak6CaloJets"), matched = cms.InputTag("ak6clean"))
akPu1PFparton = akPu3PFparton.clone(src = cms.InputTag("akPu1PFJets"))
akPu2PFparton = akPu3PFparton.clone(src = cms.InputTag("akPu2PFJets"))
akPu3PFparton = akPu3PFparton.clone(src = cms.InputTag("akPu3PFJets"))
akPu4PFparton = akPu3PFparton.clone(src = cms.InputTag("akPu4PFJets"))
akPu5PFparton = akPu3PFparton.clone(src = cms.InputTag("akPu5PFJets"))
akPu6PFparton = akPu3PFparton.clone(src = cms.InputTag("akPu6PFJets"))
akPu1Caloparton = akPu3PFparton.clone(src = cms.InputTag("akPu1CaloJets"))
akPu2Caloparton = akPu3PFparton.clone(src = cms.InputTag("akPu2CaloJets"))
akPu3Caloparton = akPu3PFparton.clone(src = cms.InputTag("akPu3CaloJets"))
akPu4Caloparton = akPu3PFparton.clone(src = cms.InputTag("akPu4CaloJets"))
akPu5Caloparton = akPu3PFparton.clone(src = cms.InputTag("akPu5CaloJets"))
akPu6Caloparton = akPu3PFparton.clone(src = cms.InputTag("akPu6CaloJets"))
ak1PFparton = akPu3PFparton.clone(src = cms.InputTag("ak1PFJets"))
ak2PFparton = akPu3PFparton.clone(src = cms.InputTag("ak2PFJets"))
ak3PFparton = akPu3PFparton.clone(src = cms.InputTag("ak3PFJets"))
ak4PFparton = akPu3PFparton.clone(src = cms.InputTag("ak4PFJets"))
ak5PFparton = akPu3PFparton.clone(src = cms.InputTag("ak5PFJets"))
ak6PFparton = akPu3PFparton.clone(src = cms.InputTag("ak6PFJets"))
ak1Caloparton = akPu3PFparton.clone(src = cms.InputTag("ak1CaloJets"))
ak2Caloparton = akPu3PFparton.clone(src = cms.InputTag("ak2CaloJets"))
ak3Caloparton = akPu3PFparton.clone(src = cms.InputTag("ak3CaloJets"))
ak4Caloparton = akPu3PFparton.clone(src = cms.InputTag("ak4CaloJets"))
ak5Caloparton = akPu3PFparton.clone(src = cms.InputTag("ak5CaloJets"))
ak6Caloparton = akPu3PFparton.clone(src = cms.InputTag("ak6CaloJets"))


# PAT Maker

akPu1PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu1PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu1PFcorr")), genJetMatch = cms.InputTag("akPu1PFmatch"), genPartonMatch = cms.InputTag("akPu1PFparton"))
akPu2PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu2PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu2PFcorr")), genJetMatch = cms.InputTag("akPu2PFmatch"), genPartonMatch = cms.InputTag("akPu2PFparton"))
akPu3PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu3PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu3PFcorr")), genJetMatch = cms.InputTag("akPu3PFmatch"), genPartonMatch = cms.InputTag("akPu3PFparton"))
akPu4PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu4PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu4PFcorr")), genJetMatch = cms.InputTag("akPu4PFmatch"), genPartonMatch = cms.InputTag("akPu4PFparton"))
akPu5PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu5PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu5PFcorr")), genJetMatch = cms.InputTag("akPu5PFmatch"), genPartonMatch = cms.InputTag("akPu5PFparton"))
akPu6PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu6PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu6PFcorr")), genJetMatch = cms.InputTag("akPu6PFmatch"), genPartonMatch = cms.InputTag("akPu6PFparton"))
akPu1CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu1CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu1Calocorr")), genJetMatch = cms.InputTag("akPu1Calomatch"), genPartonMatch = cms.InputTag("akPu1Caloparton"))
akPu2CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu2CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu2Calocorr")), genJetMatch = cms.InputTag("akPu2Calomatch"), genPartonMatch = cms.InputTag("akPu2Caloparton"))
akPu3CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu3CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu3Calocorr")), genJetMatch = cms.InputTag("akPu3Calomatch"), genPartonMatch = cms.InputTag("akPu3Caloparton"))
akPu4CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu4CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu4Calocorr")), genJetMatch = cms.InputTag("akPu4Calomatch"), genPartonMatch = cms.InputTag("akPu4Caloparton"))
akPu5CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu5CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu5Calocorr")), genJetMatch = cms.InputTag("akPu5Calomatch"), genPartonMatch = cms.InputTag("akPu5Caloparton"))
akPu6CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("akPu6CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu6Calocorr")), genJetMatch = cms.InputTag("akPu6Calomatch"), genPartonMatch = cms.InputTag("akPu6Caloparton"))
ak1PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak1PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak1PFcorr")), genJetMatch = cms.InputTag("ak1PFmatch"), genPartonMatch = cms.InputTag("ak1PFparton"))
ak2PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak2PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak2PFcorr")), genJetMatch = cms.InputTag("ak2PFmatch"), genPartonMatch = cms.InputTag("ak2PFparton"))
ak3PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak3PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak3PFcorr")), genJetMatch = cms.InputTag("ak3PFmatch"), genPartonMatch = cms.InputTag("ak3PFparton"))
ak4PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak4PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak4PFcorr")), genJetMatch = cms.InputTag("ak4PFmatch"), genPartonMatch = cms.InputTag("ak4PFparton"))
ak5PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak5PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak5PFcorr")), genJetMatch = cms.InputTag("ak5PFmatch"), genPartonMatch = cms.InputTag("ak5PFparton"))
ak6PFpatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak6PFJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak6PFcorr")), genJetMatch = cms.InputTag("ak6PFmatch"), genPartonMatch = cms.InputTag("ak6PFparton"))
ak1CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak1CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak1Calocorr")), genJetMatch = cms.InputTag("ak1Calomatch"), genPartonMatch = cms.InputTag("ak1Caloparton"))
ak2CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak2CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak2Calocorr")), genJetMatch = cms.InputTag("ak2Calomatch"), genPartonMatch = cms.InputTag("ak2Caloparton"))
ak3CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak3CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak3Calocorr")), genJetMatch = cms.InputTag("ak3Calomatch"), genPartonMatch = cms.InputTag("ak3Caloparton"))
ak4CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak4CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak4Calocorr")), genJetMatch = cms.InputTag("ak4Calomatch"), genPartonMatch = cms.InputTag("ak4Caloparton"))
ak5CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak5CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak5Calocorr")), genJetMatch = cms.InputTag("ak5Calomatch"), genPartonMatch = cms.InputTag("ak5Caloparton"))
ak6CalopatJets = akPu3PFpatJets.clone(jetSource = cms.InputTag("ak6CaloJets"), jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak6Calocorr")), genJetMatch = cms.InputTag("ak6Calomatch"), genPartonMatch = cms.InputTag("ak6Caloparton"))




akPu1PFpatSequence = cms.Sequence(akPu1PFcorr+ak1clean+akPu1PFmatch+akPu1PFparton+akPu1PFpatJets)
akPu2PFpatSequence = cms.Sequence(akPu2PFcorr+ak2clean+akPu2PFmatch+akPu2PFparton+akPu2PFpatJets)
akPu3PFpatSequence = cms.Sequence(akPu3PFcorr+ak3clean+akPu3PFmatch+akPu3PFparton+akPu3PFpatJets)
akPu4PFpatSequence = cms.Sequence(akPu4PFcorr+ak4clean+akPu4PFmatch+akPu4PFparton+akPu4PFpatJets)
akPu5PFpatSequence = cms.Sequence(akPu5PFcorr+ak5clean+akPu5PFmatch+akPu5PFparton+akPu5PFpatJets)
akPu6PFpatSequence = cms.Sequence(akPu6PFcorr+ak6clean+akPu6PFmatch+akPu6PFparton+akPu6PFpatJets)


akPu1CalopatSequence = cms.Sequence(akPu1Calocorr+ak1clean+akPu1Calomatch+akPu1Caloparton+akPu1CalopatJets)
akPu2CalopatSequence = cms.Sequence(akPu2Calocorr+ak2clean+akPu2Calomatch+akPu2Caloparton+akPu2CalopatJets)
akPu3CalopatSequence = cms.Sequence(akPu3Calocorr+ak3clean+akPu3Calomatch+akPu3Caloparton+akPu3CalopatJets)
akPu4CalopatSequence = cms.Sequence(akPu4Calocorr+ak4clean+akPu4Calomatch+akPu4Caloparton+akPu4CalopatJets)
akPu5CalopatSequence = cms.Sequence(akPu5Calocorr+ak5clean+akPu5Calomatch+akPu5Caloparton+akPu5CalopatJets)
akPu6CalopatSequence = cms.Sequence(akPu6Calocorr+ak6clean+akPu6Calomatch+akPu6Caloparton+akPu6CalopatJets)

ak1PFpatSequence = cms.Sequence(ak1PFcorr+ak1clean+ak1PFmatch+ak1PFparton+ak1PFpatJets)
ak2PFpatSequence = cms.Sequence(ak2PFcorr+ak2clean+ak2PFmatch+ak2PFparton+ak2PFpatJets)
ak3PFpatSequence = cms.Sequence(ak3PFcorr+ak3clean+ak3PFmatch+ak3PFparton+ak3PFpatJets)
ak4PFpatSequence = cms.Sequence(ak4PFcorr+ak4clean+ak4PFmatch+ak4PFparton+ak4PFpatJets)
ak5PFpatSequence = cms.Sequence(ak5PFcorr+ak5clean+ak5PFmatch+ak5PFparton+ak5PFpatJets)
ak6PFpatSequence = cms.Sequence(ak6PFcorr+ak6clean+ak6PFmatch+ak6PFparton+ak6PFpatJets)

ak1CalopatSequence = cms.Sequence(ak1Calocorr+ak1clean+ak1Calomatch+ak1Caloparton+ak1CalopatJets)
ak2CalopatSequence = cms.Sequence(ak2Calocorr+ak2clean+ak2Calomatch+ak2Caloparton+ak2CalopatJets)
ak3CalopatSequence = cms.Sequence(ak3Calocorr+ak3clean+ak3Calomatch+ak3Caloparton+ak3CalopatJets)
ak4CalopatSequence = cms.Sequence(ak4Calocorr+ak4clean+ak4Calomatch+ak4Caloparton+ak4CalopatJets)
ak5CalopatSequence = cms.Sequence(ak5Calocorr+ak5clean+ak5Calomatch+ak5Caloparton+ak5CalopatJets)
ak6CalopatSequence = cms.Sequence(ak6Calocorr+ak6clean+ak6Calomatch+ak6Caloparton+ak6CalopatJets)

makeHeavyIonJets = cms.Sequence(icPu5patSequence +
                                
                                akPu1PFpatSequence +
                                akPu2PFpatSequence +
                                akPu3PFpatSequence +
                                akPu4PFpatSequence +
                                akPu5PFpatSequence +
                                akPu6PFpatSequence +

                                akPu1CalopatSequence +
                                akPu2CalopatSequence +
                                akPu3CalopatSequence +
                                akPu4CalopatSequence +
                                akPu5CalopatSequence +
                                akPu6CalopatSequence +
                                
                                ak1PFpatSequence +
                                ak2PFpatSequence +
                                ak3PFpatSequence +
                                ak4PFpatSequence +
                                ak5PFpatSequence +
                                ak6PFpatSequence +
                                
                                ak1CalopatSequence +
                                ak2CalopatSequence +
                                ak3CalopatSequence +
                                ak4CalopatSequence +
                                ak5CalopatSequence +
                                ak6CalopatSequence
                                

                                )
                                





















ic5JetAnalyzer = icPu5JetAnalyzer.clone(jetTag = cms.InputTag("iterativeCone5CaloJets"))

akPu1PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak1PFpatJets"))
akPu2PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak2PFpatJets"))
akPu3PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak3PFpatJets"))
akPu4PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak4PFpatJets"))
akPu5PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak5PFpatJets"))
akPu6PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak6PFpatJets"))

akPu3CaloJetAnalyzer = akPu3PFJetAnalyzer.clone()

akPu1CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak1CalopatJets"))
akPu2CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak2CalopatJets"))
akPu3CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak3CalopatJets"))
akPu4CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak4CalopatJets"))
akPu5CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak5CalopatJets"))
akPu6CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak6CalopatJets"))

ak1PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak1PFpatJets"))
ak2PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak2PFpatJets"))
ak3PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak3PFpatJets"))
ak4PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak4PFpatJets"))
ak5PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak5PFpatJets"))
ak6PFJetAnalyzer = akPu3PFJetAnalyzer.clone(jetTag = cms.InputTag("ak6PFpatJets"))

ak3CaloJetAnalyzer = akPu3PFJetAnalyzer.clone()

ak1CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak1CalopatJets"))
ak2CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak2CalopatJets"))
ak3CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak3CalopatJets"))
ak4CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak4CalopatJets"))
ak5CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak5CalopatJets"))
ak6CaloJetAnalyzer = akPu3CaloJetAnalyzer.clone(jetTag = cms.InputTag("ak6CalopatJets"))

jetAnalyzers = cms.Sequence(
        akPu1PFJetAnalyzer +
            akPu2PFJetAnalyzer +
                akPu3PFJetAnalyzer +
                akPu4PFJetAnalyzer +
                akPu5PFJetAnalyzer +
                akPu6PFJetAnalyzer +

            akPu1CaloJetAnalyzer +
            akPu2CaloJetAnalyzer +
                akPu3CaloJetAnalyzer +
                akPu4CaloJetAnalyzer +
                akPu5CaloJetAnalyzer +
                akPu6CaloJetAnalyzer +

            ak1PFJetAnalyzer +
            ak2PFJetAnalyzer +
                ak3PFJetAnalyzer +
                ak4PFJetAnalyzer +
                ak5PFJetAnalyzer +
                ak6PFJetAnalyzer +

            ak1CaloJetAnalyzer +
            ak2CaloJetAnalyzer +
                ak3CaloJetAnalyzer +
                ak4CaloJetAnalyzer +
                ak5CaloJetAnalyzer +
                ak6CaloJetAnalyzer

            )









