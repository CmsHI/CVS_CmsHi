import FWCore.ParameterSet.Config as cms

from edwenger.HiTrkEffAnalyzer.hitrkEffAnalyzer_cff import *

hitrkEffAnalyzer_akpu3pf = hitrkEffAnalyzer.clone(
  # evt
  neededCentBins = cms.untracked.vint32(0, 1, 3, 11, 19, 35),
  # trk selection
  tracks = "hiSelectedTracks",
  fiducialCut = True,
  # setup
  fillNtuples = False,
  ptBinScheme = 3, # coarse binning for jet ana
  # jet-trk
  jets = 'akPu3PFpatJets',
  trkAcceptedJet = True, # jet |eta|<2
  useJetEtMode = 2, # mode2: jet1, jet1 or jet_pt=0
  jetTrkOnly = False # only trks in 0.8 cone or not
  )

hitrkEffAna_akpu3pf = cms.Sequence(cutsTPForFak*cutsTPForEff*hitrkEffAnalyzer_akpu3pf)

anaTrack.trackPtMin = 0.5
anaTrack.useQuality = True
anaTrack.doPFMatching = True
anaTrack.pfCandSrc = cms.InputTag("particleFlowTmp")
anaTrack.trackSrc = cms.InputTag("hiGeneralCaloMatchedTracks")

pixelTrack = process.anaTrack.clone(trackSrc = cms.InputTag("hiConformalPixelTracks"))
pixelTrack.useQuality = False
pixelTrack.trackPtMin = 0.5


