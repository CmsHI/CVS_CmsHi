import FWCore.ParameterSet.Config as cms

from CmsHi.JetAnalysis.TrkAnalyzers_cff import *

process.anaTrack.doSimTrack = True
process.anaTrack.fillSimTrack = cms.untracked.bool(True)
process.anaTrack.simTrackPtMin = 1

process.pixelTrack.doSimTrack = True
process.pixelTrack.simTrackPtMin = 1
process.pixelTrack.fillSimTrack = False
