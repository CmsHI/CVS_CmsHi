#############################
#  HiForest2 Configuration  #
#############################

# Simulations
cvs co -r V00-01-11 GeneratorInterface/HiGenCommon
cvs co -r V02-02-25 GeneratorInterface/PyquenInterface

# Track studies
cvs co -r HiForest_V02_00 -d       edwenger/EvtSelAnalyzer                  UserCode/edwenger/EvtSelAnalyzer
cvs co -r HiForest_V02_00 -d       edwenger/HiVertexAnalyzer                UserCode/edwenger/HiVertexAnalyzer
cvs co -r HiForest_V02_01 -d       edwenger/HiTrkEffAnalyzer                UserCode/edwenger/HiTrkEffAnalyzer
cvs co -r HiForest_V02_00 -d       edwenger/TrkEffAnalyzer                  UserCode/edwenger/TrkEffAnalyzer
cvs co -r HiForest_V02_00 -d       edwenger/TrackSpectraAnalyzer            UserCode/edwenger/TrackSpectraAnalyzer
cvs co -r HiForest_V02_00 -d       edwenger/Skims                           UserCode/edwenger/Skims
cvs co -r HiForest_V02_00 -d       edwenger/VertexAnalyzer                  UserCode/edwenger/VertexAnalyzer
cvs co -r HiForest_V02_00 -d       SpectraAna/JetEtaPhiFilter               UserCode/ASYoon/SpectraAna/JetEtaPhiFilter
cvs co -r HiForest_V02_00 -d       SpectraAna/TrackSpectraAnalyzer          UserCode/ASYoon/SpectraAna/TrackSpectraAnalyzer
cvs co -r HiForest_V02_09 -d       MitHig/PixelTrackletAnalyzer             UserCode/MitHig/PixelTrackletAnalyzer
cvs co -r HiForest_V02_00          UserCode/FerencSiklerVertexing

# pat macros
cvs co -r HiForest_V02_00 -d       MNguyen/patMacrosForMC  UserCode/MNguyen/patMacrosForMC
cvs co -r HiForest_V02_00 -d       MNguyen/patMacrosForDataSkims  UserCode/MNguyen/patMacrosForDataSkims
cvs co -r HiForest_V02_00 -d       MNguyen/Configuration  UserCode/MNguyen/Configuration
cvs co -r pPbProd_v1               HeavyIonsAnalysis/Configuration

# Jet and HI Software
cvs co -r HiForest_V02_00 -d       MNguyen/InclusiveJetAnalyzer UserCode/MNguyen/InclusiveJetAnalyzer

# pi0 analyzer (optional)
cvs co -r HiForest_V02_00 -d       MNguyen/pi0Analyzer  UserCode/MNguyen/pi0Analyzer

cvs co -r pPbProd_v1               RecoHI/HiCentralityAlgos
cvs co -r pPbProd_v1               DataFormats/HeavyIonEvent

# Track validation histograms
cvs co -r HiForest_V02_00 -d       PbPbTrackingTools/HiTrackValidator UserCode/ASYoon/PbPbTrackingTools/HiTrackValidator

# Vertex constraint producer (Yen-Jie where do we need this?)
cvs co -r HiForest_V02_00 -d       PbPbTrackingTools/VertexConstraintProducer 

# Centrality and event plane
#      Yen-Jie: Evt plane configuration need check!
cvs co -r HiForest_V02_04 -d       CmsHi/Analysis2010 UserCode/CmsHi/Analysis2010
cvs co -r HiForest_V02_01 -d       CmsHi/Analysis2012 UserCode/CmsHi/Analysis2012
cvs co -r HiForest_V02_01 -d       CmsHi/PhotonAnalysis UserCode/CmsHi/PhotonAnalysis
cvs co -r HiForest_V02_33 -d       CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis
cvs co -r HiForest_V02_00 -d       HcalFilter UserCode/MTonjes/HcalFilter

#PixelTrack
cvs co -r HiForest_V02_00 -d       Appeltel/PixelTrackAnalysis UserCode/Appeltel/PixelTrackAnalysis
cvs co -r HiForest_V02_01 -d       Appeltel/PixelTracksRun2010 UserCode/Appeltel/PixelTracksRun2010


#ecal requires some code from the photon analyzer, 'rm' commands are to truncate the endless chain of packages obviously, 

# Top Level Forest cfg
cvs co -r HEAD -d		   CmsHi/JetAnalysis/test UserCode/CmsHi/JetAnalysis/test

# trigger analyzers
cvs co -r branch_hi44X HLTrigger/HLTanalyzers

# event analyzer
cvs co -r HiForest_V02_00 -d       CmsHi/HiHLTAlgos UserCode/CmsHi/HiHLTAlgos

# muon analyzer
cvs co -r HiForest_V02_02 -d       MuTrig/HLTMuTree UserCode/yenjie/HLTMuTree/

# Build!

scram build -c
scram b -j4


