#!/bin/sh

cd $CMSSW_BASE/src
cvs co -d CmsHi/JulyExercise UserCode/CmsHi/JulyExercise
cvs co HeavyIonsAnalysis/Configuration
cvs co RecoHI/HiMuonAlgos

# Jet stuff
cvs co RecoJets/JetAlgorithms
cvs co RecoJets/JetProducers
cvs co RecoHI/HiJetAlgos

cvs co -r jetCorrections_3_6_0_retrofit CondFormats/JetMETObjects
cvs co -r jetCorrections_3_6_0_retrofit JetMETCorrections/Configuration
cvs co -r jetCorrections_3_6_0_retrofit JetMETCorrections/Modules
mv CondFormats/JetMETObjects/data/L5Flavor_IC5Calo.txt CondFormats/JetMETObjects/data/L5Flavor_IC5.txt 

cvs co -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis
mv CmsHi/JetAnalysis/bin/jet_response_analyzer_x.cc JetMETAnalysis/JetAnalyzers/bin/
rm JetMETAnalysis/JetAnalyzers/python/JPTReconstruction_cff.py

mv CmsHi/JetAnalysis/python/jetMETCorrections_cff.py PhysicsTools/PatAlgos/python/recoLayer0/jetMETCorrections_cff.py





scram b





