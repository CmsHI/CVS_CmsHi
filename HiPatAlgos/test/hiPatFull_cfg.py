
######################################################################################
#
# PAT Sequence Script for Heavy Ion Analysis
#

import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring("dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/davidlw/Hydjet_MinBias_4TeV/pyquen_unquenjets_pt160to220_hydjet_quen_mb_4TeV_d20090728_run0/c326a8a6786819f03f98d68667992fa4/pyquen_unquenjets_pt160to220_intoHIEvt_91.root"),
    duplicateCheckMode = cms.untracked.string( 'noDuplicateCheck' )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

########################################################################################
# Timing and memory services
#

process.Timing = cms.Service("Timing")

process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
                                        oncePerEventMode = cms.untracked.bool(True),
                                        ignoreTotal = cms.untracked.int32(0)
                                        )


##################################################################################
##################################################################################
#
# PAT object production & selection
#                                                                       
process.load("CmsHi.HiPatAlgos.HiPatSequences_cff")

##################################################################################
##################################################################################
# Heavy Ion reconstruction for the missing objects in the standard HI - RECO

process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'MC_31X_V2::All'

process.load("RecoHI.Configuration.Reconstruction_HI_cff")

process.load("RecoLocalMuon.Configuration.RecoLocalMuon_cff")
process.load("RecoMuon.Configuration.RecoMuon_cff")
process.load("RecoMuon.MuonIdentification.muonIdProducerSequence_cff")


# PAT Track Production
#
# For now, selection is run on the track collection globalPrimTracks and renamed hiGeneralTracks
# which most high level reconstruction algorithms look for by default. The other track
# collections are dropped in the EventContent to avoid confusion when looking for
# the correct collection of tracks to analyze.
#

import RecoHI.HiTracking.SelectHITracks_cfi
process.hiGeneralTracks =  RecoHI.HiTracking.SelectHITracks_cfi.selectHiTracks.clone()
process.hiTrackSequence = cms.Sequence(process.offlineBeamSpot * process.trackerlocalreco * process.heavyIonTracking * process.hiGeneralTracks)

# Photon
process.gamIsoDepositTk.ExtractorPSet.inputTrackCollection = cms.InputTag('hiGeneralTracks')

#
# Until the reco::Muon object is added to standard HI reconstruction,
# the object will be produced in this script for testing.
#
# Muons
process.muons.inputCollectionLabels = ['hiGeneralTracks', 'globalMuons', 'standAloneMuons:UpdatedAtVtx']
process.muons.TrackExtractorPSet.inputTrackCollection = 'hiGeneralTracks'
process.calomuons.inputTracks = 'hiGeneralTracks'
process.muIsoDepositTk.ExtractorPSet.inputTrackCollection = 'hiGeneralTracks'
process.globalMuons.TrackerCollectionLabel = 'hiGeneralTracks'

process.muons.JetExtractorPSet.JetCollectionLabel = cms.InputTag("iterativeConePu5CaloJets")
process.muIsoDepositJets.ExtractorPSet.JetCollectionLabel = cms.InputTag("iterativeConePu5CaloJets")

process.muonRecoTemp = cms.Sequence(
    process.muonCSCDigis *
    process.muonDTDigis *
    process.muonRPCDigis *
    process.muonlocalreco *
    process.muontracking_with_TeVRefinement *
    process.muonIdProducerSequence *
    process.muIsolation
)

#######################################################################################
# Output file
#

process.output = cms.OutputModule("PoolOutputModule",
    process.hiPatExtraEventContent,
    compressionLevel = cms.untracked.int32(2),
    commitInterval = cms.untracked.uint32(1),
    fileName = cms.untracked.string("hi_pat.root")
)

#######################################################################################
#
# Paths to run
#

process.producePat = cms.Path(process.hiTrackSequence *
                     process.muonRecoTemp *
                     process.hiEgammaSequence *
                     process.hiPatProductionSequence *
                     process.hiPatSelectionSequence
                     )

process.out = cms.EndPath( process.output )
