#/bin/bash -
# l1/HLT menu tags
#cvs co -r V12-03-18     HLTrigger/Configuration
cvs co -r V12-03-21     HLTrigger/Configuration
cvs co -r V03-00-07     L1TriggerConfig/L1GtConfigProducers

# get hlt menu
hltGetConfiguration --cff --offline --data /dev/CMSSW_4_2_0/HIon/V337 --type HIon --unprescale > $CMSSW_BASE/src/HLTrigger/Configuration/python/HLT_HIon_data_cff.py
hltGetConfiguration --cff --offline --data /users/frankma/devCMSSW_4_2_0/HIonV1047 --type HIon --unprescale > $CMSSW_BASE/src/HLTrigger/Configuration/python/HLT_HIon_Jet_data_cff.py

# trigger analyzers
cvs co -d       CmsHi/HiHLTAlgos UserCode/CmsHi/HiHLTAlgos

# custom l1 menu from xml
addpkg L1Trigger/Configuration
cp -v CmsHi/HiHLTAlgos/modifiedFiles/L1Trigger_custom.py L1Trigger/Configuration/python/

scram build -c
