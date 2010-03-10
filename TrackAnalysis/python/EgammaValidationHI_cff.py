import FWCore.ParameterSet.Config as cms

##########################################################
# produce generated paricles in acceptance               #
##########################################################

higenp = cms.EDFilter("PdgIdAndStatusCandViewSelector",
    status = cms.vint32(3),
    src = cms.InputTag("hiGenParticles"),
    pdgId = cms.vint32(22)
)

hifiducial = cms.EDFilter("EtaPtMinCandViewSelector",
    src = cms.InputTag("higenp"),
    etaMin = cms.double(-2.5),
    etaMax = cms.double(2.5), 
    ptMin = cms.double(2.0) 
)

hltlabel = "HLT"

from CmsHi.TrackAnalysis.HLT_HIPhoton15_DQM_cfi import *
HLT_HIPhoton15_DQM.cutcollection = cms.InputTag("hifiducial")
HLT_HIPhoton15_DQM.cutnum = cms.int32(1)
HLT_HIPhoton15_DQM.pdgGen = cms.int32(22)
HLT_HIPhoton15_DQM.triggerobject.setProcessName(hltlabel)

for filterpset in HLT_HIPhoton15_DQM.filters:
    getattr(filterpset,'HLTCollectionLabels').setProcessName(hltlabel)
    for isocollections in getattr(filterpset,'IsoCollections'):
        isocollections.setProcessName(hltlabel)

hiEgammaValidationSequence = cms.Sequence(higenp*hifiducial*HLT_HIPhoton15_DQM)
