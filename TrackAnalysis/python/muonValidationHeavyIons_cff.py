import FWCore.ParameterSet.Config as cms

from Validation.RecoMuon.muonValidation_cff import *

# MuonAssociation
tpToTkMuonAssociation.tracksTag = 'hiSelectedTracks'
tpToTkmuTrackAssociation.label_tr = 'hiSelectedTracks'

# RecoMuonValidators
trkMuonTrackVTrackAssoc.label = ['hiSelectedTracks']
recoMuonVMuAssoc.trkMuLabel = 'hiSelectedTracks'
recoMuonVTrackAssoc.trkMuLabel = 'hiSelectedTracks'

# Muon validation sequences
hiMuonValidation_seq = cms.Sequence(trkMuonTrackVTrackAssoc
                                    +staMuonTrackVTrackAssoc
                                    +staUpdMuonTrackVTrackAssoc
                                    +glbMuonTrackVTrackAssoc
                                    +staMuonTrackVMuonAssoc
                                    +staUpdMuonTrackVMuonAssoc
                                    +glbMuonTrackVMuonAssoc
                                    +recoMuonVMuAssoc
                                    +recoMuonVTrackAssoc
                                    )

hiRecoMuonValidation = cms.Sequence(muonAssociation_seq * hiMuonValidation_seq)    
