## hiGoodMergedTracks and the track analyzer
cvs co -d       edwenger/HiVertexAnalyzer UserCode/edwenger/HiVertexAnalyzer
cvs co -d       edwenger/HiTrkEffAnalyzer UserCode/edwenger/HiTrkEffAnalyzer
cvs co -r hi39X_01 -d       MitHig/PixelTrackletAnalyzer UserCode/MitHig/PixelTrackletAnalyzer
cvs co -d       edwenger/Skims UserCode/edwenger/Skims
cvs co -d       edwenger/VertexAnalyzer UserCode/edwenger/VertexAnalyzer
cvs co -d       edwenger/TrkEffAnalyzer UserCode/edwenger/TrkEffAnalyzer

cvs co -d       edwenger/TrackSpectraAnalyzer UserCode/edwenger/TrackSpectraAnalyzer
cvs co -d       edwenger/EvtSelAnalyzer  UserCode/edwenger/EvtSelAnalyzer
cvs co -d       SpectraAna/JetEtaPhiFilter UserCode/ASYoon/SpectraAna/JetEtaPhiFilter
cvs co -d       SpectraAna/TrackSpectraAnalyzer UserCode/ASYoon/SpectraAna/TrackSpectraAnalyzer

cvs co          UserCode/FerencSiklerVertexing

# pat macros
cvs co -d      MNguyen/patMacrosForMC  UserCode/MNguyen/patMacrosForMC
cvs co -d      MNguyen/patMacrosForDataSkims  UserCode/MNguyen/patMacrosForDataSkims
cvs co -d      MNguyen/Configuration  UserCode/MNguyen/Configuration
cvs co         HeavyIonsAnalysis/Configuration

# Jet and HI Software
cvs co -d       MNguyen/InclusiveJetAnalyzer UserCode/MNguyen/InclusiveJetAnalyzer

cvs co -r       V05-01-09-01 RecoJets/JetProducers
cvs co          RecoHI/HiJetAlgos
addpkg           RecoHI/Configuration

#Centrality
cvs co          CondFormats/HIObjects
cvs co          DataFormats/HeavyIonEvent
cvs co          RecoHI/HiCentralityAlgos
cvs co -d       CmsHi/Analysis2010 UserCode/CmsHi/Analysis2010

# needed to get PFTowers to work
cvs co -r hi413_08 -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis

#ecal and hcal cleaning
#hcal
addpkg RecoLocalCalo/HcalRecAlgos
cvs co -r V00-07-21 RecoLocalCalo/HcalRecAlgos/src/HBHETimingShapedFlag.cc
cvs co -r V00-07-21 RecoLocalCalo/HcalRecAlgos/interface/HBHETimingShapedFlag.h
cvs co -r V00-00-18 JetMETAnalysis/HcalReflagging
cvs co -d HcalFilter UserCode/MTonjes/HcalFilter

#ecal requires some code from the photon analyzer, 'rm' commands are to truncate the endless chain of packages obviously, this should be cleaned up
cvs co -d RecoHI/HiEgammaAlgos UserCode/yetkin/RecoHI/HiEgammaAlgos
cvs co -d CmsHi/PhotonAnalysis UserCode/yetkin/PhotonAnalysis
cvs co -d UserCode/HafHistogram UserCode/CmsHi/HafHistogram

# trigger analyzers
cvs co -r hi413_05 HLTrigger/HLTanalyzers

scram build -c
scram b -j4