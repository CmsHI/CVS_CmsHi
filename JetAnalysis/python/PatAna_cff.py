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
