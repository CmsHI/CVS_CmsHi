import FWCore.ParameterSet.Config as cms

findableSimTracks = cms.EDFilter("HitPixelLayersTPSelection",
    src = cms.InputTag("mergedtruth","MergedTrackTruth"),
	tripletSeedOnly = cms.bool(True),
	chargedOnly = cms.bool(True),
	signalOnly = cms.bool(False),
	ptMin = cms.double(2.0),
	minHit = cms.int32(8),
	minRapidity = cms.double(-2.5),
	maxRapidity = cms.double(2.5),
	tip = cms.double(0.05), #was 3.5
	lip = cms.double(30.0),
	pdgId = cms.vint32()
)


