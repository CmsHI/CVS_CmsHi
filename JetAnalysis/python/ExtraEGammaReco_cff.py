import FWCore.ParameterSet.Config as cms

# reco
from RecoHI.HiEgammaAlgos.HiEgamma_cff import *

# detector responce
from CmsHi.PhotonAnalysis.isoConeInspector_cfi import *
from CmsHi.PhotonAnalysis.ecalHistProducer_cfi import *
from CmsHi.PhotonAnalysis.SpikeInspector_cfi import *

photonObj = "cleanPhotons"

# spike cleaner for island superclsters
cleanPhotons.maxHoverEBarrel = cms.double(100)
PhotonIDProd.photonProducer  = cms.string(photonObj)
gamIsoDepositTk.src = cms.InputTag(photonObj)
gamIsoDepositEcalFromHits.src = cms.InputTag(photonObj)
gamIsoDepositHcalFromTowers.src = cms.InputTag(photonObj)
gamIsoDepositHcalDepth1FromTowers.src = cms.InputTag(photonObj)
gamIsoDepositHcalDepth2FromTowers.src = cms.InputTag(photonObj)

# clean photon filter
goodPhotons = cms.EDFilter("PhotonSelector",
	src = cms.InputTag("cleanPhotons"),
	cut = cms.string("pt > 18 & hadronicOverEm < 0.2 & abs(eta) < 1.45"),
	)
filterGoodPhotons = cms.EDFilter("PhotonCountFilter",
	src = cms.InputTag("goodPhotons"),
	minNumber = cms.uint32(0), # tmp solution for both gamma and jets
	maxNumber = cms.uint32(999999),
	)

barrelPhotonFilter = cms.Sequence ( goodPhotons * filterGoodPhotons )

# pat
from PhysicsTools.PatAlgos.producersHeavyIons.heavyIonPhotons_cff import *

patPhotons.photonSource = cms.InputTag(photonObj)
photonMatch.src = cms.InputTag(photonObj)

# final seq
photon_extra_reco = cms.Sequence(
	hiEcalClusteringSequence *
	hiPhotonCleaningSequence *
	barrelPhotonFilter
	)
