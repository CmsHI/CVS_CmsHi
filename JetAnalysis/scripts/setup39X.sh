#Centrality
cvs co          CondFormats/HIObjects
cvs co          DataFormats/HeavyIonEvent
cvs co          RecoHI/HiCentralityAlgos
cvs co -d       CmsHi/Analysis2010 UserCode/CmsHi/Analysis2010

## tracking
cvs co -d       edwenger/HiVertexAnalyzer UserCode/edwenger/HiVertexAnalyzer
cvs co -d       edwenger/HiTrkEffAnalyzer UserCode/edwenger/HiTrkEffAnalyzer
cvs co -d       Appeltel/PixelTracksRun2010 UserCode/Appeltel/PixelTracksRun2010
cvs co -d       MNguyen/iterTracking UserCode/MNguyen/iterTracking
cvs co -d       MitHig/PixelTrackletAnalyzer UserCode/MitHig/PixelTrackletAnalyzer

# pat macros
cvs co -d      MNguyen/patMacrosForMC  UserCode/MNguyen/patMacrosForMC
cvs co -d      MNguyen/patMacrosForDataSkims  UserCode/MNguyen/patMacrosForDataSkims
cvs co -d      MNguyen/Configuration  UserCode/MNguyen/Configuration
cvs co         HeavyIonsAnalysis/Configuration

# Jet and HI Software
cvs co -d       MNguyen/InclusiveJetAnalyzer UserCode/MNguyen/InclusiveJetAnalyzer
cvs co -r       V05-01-09-01 RecoJets/JetProducers
cvs co          RecoHI/HiJetAlgos

# needed to get PFTowers to work
cvs co -r cmssw39x_branch -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis

# gamma analysis
cvs co RecoHI/HiEgammaAlgos                  # for 3_9_8 reconstruction   including spike cleaner 
cvs co -d CmsHi/PhotonAnalysis UserCode/CmsHi/PhotonAnalysis
cvs co -d UserCode/HafHistogram UserCode/CmsHi/HafHistogram
cp CmsHi/JetAnalysis/modifiedFiles/HiIsolationCommonParameters_cff.py RecoHI/HiEgammaAlgos/python/
# electron reco sequence
rm -f RecoHI/HiEgammaAlgos/python/HiElectronSequence_cff.py
cvs co -r CMSSW_3_9_9_patch1 RecoHI/HiEgammaAlgos/python/HiElectronSequence_cff.py # temp fix b/c head version not working

#ecal and hcal cleaning
#hcal
addpkg RecoLocalCalo/HcalRecAlgos
cvs co -r V00-07-21 RecoLocalCalo/HcalRecAlgos/src/HBHETimingShapedFlag.cc
cvs co -r V00-07-21 RecoLocalCalo/HcalRecAlgos/interface/HBHETimingShapedFlag.h
cvs co -r V00-00-18 JetMETAnalysis/HcalReflagging
cvs co -d HcalFilter UserCode/MTonjes/HcalFilter

# keep 39X version for spike cleaner.
rm RecoHI/HiEgammaAlgos/plugins/HiSpikeCleaner.cc
cvs co -r HI_HLT_2010_11_20_fix2 RecoHI/HiEgammaAlgos/plugins/HiSpikeCleaner.cc

# openhlt
cvs co -r V03-03-08-01 HLTrigger/HLTanalyzers
# cvs co -r branch_HI39X HLTrigger/HLTanalyzers

# muons for PF
addpkg DataFormats/ParticleFlowCandidate
addpkg RecoParticleFlow/PFProducer
addpkg RecoParticleFlow/PFRootEvent

# private mods related to muon reco

modifiedFileDir=UserCode/yetkin/ParticleFlow/modifiedFiles
cvs co $modifiedFileDir

cp $modifiedFileDir/PFRootEventManager.cc RecoParticleFlow/PFRootEvent/src/ 
cp $modifiedFileDir/PFBlockAlgo.h RecoParticleFlow/PFProducer/interface/
cp $modifiedFileDir/PFBlockProducer.cc RecoParticleFlow/PFProducer/plugins/ 
cp $modifiedFileDir/HiHackedAnalyticalTrackSelector.cc  edwenger/HiTrkEffAnalyzer/src/









scram b -j4
