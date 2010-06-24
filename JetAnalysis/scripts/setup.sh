#!/bin/sh

cd $CMSSW_BASE/src
cvs co RecoHI/HiCentralityAlgos/data
cvs co HeavyIonsAnalysis/Configuration

#RECO stuff
cvs co RecoJets/JetProducers
cvs co UserCode/yetkin/RecoJets/JetProducers/plugins/VirtualJetProducer.* RecoJets/JetProducers/plugins/
cvs co -r $CMSSW_VERSION PhysicsTools/PatAlgos
rm -r PhysicsTools/PatAlgos/python/producersHeavyIons
cvs co PhysicsTools/PatAlgos/python/producersHeavyIons

# JRA stuff
cvs co -r V00-07-04 JetMETAnalysis/JetUtilities
cvs co -r V00-08-06 JetMETAnalysis/JetAnalyzers

# JetMET stuff
cvs co -r jetCorrections_3_6_0_retrofit CondFormats/JetMETObjects
cvs co -r jetCorrections_3_6_0_retrofit JetMETCorrections/Configuration
cvs co -r jetCorrections_3_6_0_retrofit JetMETCorrections/Modules
mv CondFormats/JetMETObjects/data/L5Flavor_IC5Calo.txt CondFormats/JetMETObjects/data/L5Flavor_IC5.txt 

cvs co -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis
mv CmsHi/JetAnalysis/bin/jet_response_analyzer_x.cc JetMETAnalysis/JetAnalyzers/bin/
rm JetMETAnalysis/JetAnalyzers/python/JPTReconstruction_cff.py

mv CmsHi/JetAnalysis/python/jetMETCorrections_cff.py PhysicsTools/PatAlgos/python/recoLayer0/jetMETCorrections_cff.py

scram b
pwd


