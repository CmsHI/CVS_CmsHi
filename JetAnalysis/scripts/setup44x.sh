## hiGoodMergedTracks and the track analyzer
cvs co -d       edwenger/HiVertexAnalyzer UserCode/edwenger/HiVertexAnalyzer
cvs co -d       edwenger/HiTrkEffAnalyzer UserCode/edwenger/HiTrkEffAnalyzer
cvs co -d       MitHig/PixelTrackletAnalyzer UserCode/MitHig/PixelTrackletAnalyzer
rm MitHig/PixelTrackletAnalyzer/src/SimTrackAnalyzer.cc

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

# Standard sequences
#<
#reconstructionHeavyIons_withPF *= HiParticleFlowReco
#reconstructionHeavyIons_HcalNZS_withPF *= HiParticleFlowReco
#>
#reconstructionHeavyIons_withPF *= hiElectronSequence*HiParticleFlowReco
#reconstructionHeavyIons_HcalNZS_withPF *= hiElectronSequence*HiParticleFlowReco
#addpkg Configuration/StandardSequences


# Jet and HI Software
cvs co -d       MNguyen/InclusiveJetAnalyzer UserCode/MNguyen/InclusiveJetAnalyzer

# Latest hiSelectedTrack (= hiGoodTightTrack)
cvs co RecoHI/HiTracking
cvs co RecoHI/HiMuonAlgos

#Commented out by yenjie
#cvs co -r       V05-01-09-01 RecoJets/JetProducers

cvs co          RecoHI/HiJetAlgos
addpkg           RecoHI/Configuration

#Centrality
cvs co          CondFormats/HIObjects
cvs co          DataFormats/HeavyIonEvent
cvs co          RecoHI/HiCentralityAlgos
cvs co -d       CmsHi/Analysis2010 UserCode/CmsHi/Analysis2010

# needed to get PFTowers to work
cvs co -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis

#ecal and hcal cleaning
#hcal
#addpkg RecoLocalCalo/HcalRecAlgos
#cvs co -r V00-07-21 RecoLocalCalo/HcalRecAlgos/src/HBHETimingShapedFlag.cc
#cvs co -r V00-07-21 RecoLocalCalo/HcalRecAlgos/interface/HBHETimingShapedFlag.h

# broken, Yen-Jie checked with Yi
#cvs co -r V00-00-18 JetMETAnalysis/HcalReflagging

cvs co -d HcalFilter UserCode/MTonjes/HcalFilter

#ecal requires some code from the photon analyzer, 'rm' commands are to truncate the endless chain of packages obviously, this should be cleaned up

# Removed by Yen-Jie
#cvs co -d RecoHI/HiEgammaAlgos UserCode/yetkin/RecoHI/HiEgammaAlgos
# Needed to fix PF reco
cvs co RecoHI/HiEgammaAlgos
cvs co -r V00-00-15 RecoHI/Configuration

cvs co -d CmsHi/PhotonAnalysis UserCode/CmsHi/PhotonAnalysis
rm CmsHi/PhotonAnalysis/plugins/SpikeInspector.cc 

echo '54c54
< reconstructionHeavyIons_withPF *= HiParticleFlowReco
---
> reconstructionHeavyIons_withPF *= hiElectronSequence*HiParticleFlowReco
57c57
< reconstructionHeavyIons_HcalNZS_withPF *= HiParticleFlowReco
---
> reconstructionHeavyIons_HcalNZS_withPF *= hiElectronSequence*HiParticleFlowReco' > patch.tmp

patch Configuration/StandardSequences/python/ReconstructionHeavyIons_cff.py < patch.tmp
rm patch.tmp

# trigger analyzers
cvs co -r HLTrigger/HLTanalyzers

# event analyzer
cvs co -d  CmsHi/HiHLTAlgos UserCode/CmsHi/HiHLTAlgos

# muon analyzer
cvs co -d MuTrig/HLTMuTree UserCode/CmsHi/HiMuonAlgos/HLTMuTree/

scram build -c
scram b -j4
