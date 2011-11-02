#/bin/bash -

# trigger analyzers
# evt
cvs co UserCode/L1TriggerDPG
cvs co UserCode/CmsHi UserCode/CmsHi/Analysis2010
# trk
cvs co MitHig/PixelTrackletAnalyzer UserCode/MitHig/PixelTrackletAnalyzer
cvs co -d       edwenger/HiVertexAnalyzer UserCode/edwenger/HiVertexAnalyzer
cvs co -d       edwenger/HiTrkEffAnalyzer UserCode/edwenger/HiTrkEffAnalyzer
# jet
cvs co          RecoHI/HiJetAlgos
cvs co          HeavyIonsAnalysis/Configuration
cvs co -d       CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis
# photon
cvs co -r V02-02-01  RecoHI/HiEgammaAlgos
cvs co -r V00-00-15  RecoHI/Configuration
cvs co -d CmsHi/PhotonAnalysis UserCode/CmsHi/PhotonAnalysis
# muon
cvs co -d MuTrig/HLTMuTree UserCode/Miheejo/MuTrig/HLTMuTree

scram build -c
