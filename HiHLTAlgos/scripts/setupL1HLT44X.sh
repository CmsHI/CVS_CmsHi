#/bin/bash -
# l1
cvs co UserCode/L1TriggerDPG
cvs co RecoLuminosity/LumiDB
addpkg L1Trigger/Configuration

# HLT
cvs co -r V12-00-03 HLTrigger/Configuration
addpkg HLTrigger/HLTanalyzers

# get menu
hltGetConfiguration --cff --offline --data /users/frankma/devCMSSW_4_2_0/HIonV226 --type HIon --unprescale > HLT_HIon_data_cff.py
mv HLT_HIon_data_cff.py HLTrigger/Configuration/python/

# hiGoodMergedTracks and the track analyzer
cvs co -d       edwenger/HiVertexAnalyzer UserCode/edwenger/HiVertexAnalyzer
cvs co -d       edwenger/HiTrkEffAnalyzer UserCode/edwenger/HiTrkEffAnalyzer

# jet analyzers
cvs co          RecoHI/HiJetAlgos
cvs co -d       CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis
cvs co -d       MNguyen/InclusiveJetAnalyzer UserCode/MNguyen/InclusiveJetAnalyzer

# trigger analyzers
cvs co -d       CmsHi/HiHLTAlgos UserCode/CmsHi/HiHLTAlgos
cp CmsHi/HiHLTAlgos/modifiedFiles/cmssw44X/EventHeader.cc HLTrigger/HLTanalyzers/src
cp CmsHi/HiHLTAlgos/modifiedFiles/cmssw44X/HLTBitAnalyzer.cc HLTrigger/HLTanalyzers/src
cp CmsHi/HiHLTAlgos/modifiedFiles/cmssw44X/HLTBitAnalyzer.h HLTrigger/HLTanalyzers/interface

scram build -c