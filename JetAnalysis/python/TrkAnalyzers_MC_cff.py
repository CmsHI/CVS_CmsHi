import FWCore.ParameterSet.Config as cms

from CmsHi.JetAnalysis.TrkAnalyzers_cff import *

anaTrack.doSimTrack = True
anaTrack.fillSimTrack = cms.untracked.bool(True)
anaTrack.simTrackPtMin = 1

pixelTrack.doSimTrack = True
pixelTrack.simTrackPtMin = 1
pixelTrack.fillSimTrack = cms.untracked.bool(False)
