#!/bin/sh

cd $CMSSW_BASE/src

cvs co RecoHI/HiCentralityAlgos/data

cvs co -r B3_6_X PhysicsTools/PatAlgos # B3_6_X ?
cvs co -r B3_6_X DataFormats/PatCandidates # B3_6_X ?
#cvs co -r V03-01-14 RecoMET/METAlgorithms/python

cvs co -r V00-00-09 RecoHI/HiJetAlgos
cvs co HeavyIonsAnalysis/Configuration
cvs co GeneratorInterface/HiGenCommon

# JRA stuff
cvs co -r V00-07-04 JetMETAnalysis/JetUtilities
cvs co -r V00-08-06 JetMETAnalysis/JetAnalyzers

# JetMET stuff
cvs co -r jetCorrections_3_6_0_retrofit CondFormats/JetMETObjects
cvs co -r jetCorrections_3_6_0_retrofit JetMETCorrections/Configuration
cvs co -r jetCorrections_3_6_0_retrofit JetMETCorrections/Modules
mv CondFormats/JetMETObjects/data/L5Flavor_IC5Calo.txt CondFormats/JetMETObjects/data/L5Flavor_IC5.txt 

cvs co UserCode/CmsHi/JetAnalysis
mv UserCode/CmsHi/JetAnalysis/bin/jet_response_analyzer_x.cc JetMETAnalysis/JetAnalyzers/bin/
rm JetMETAnalysis/JetAnalyzers/python/JPTReconstruction_cff.py
scram b
pwd


