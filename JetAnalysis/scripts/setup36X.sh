#!/bin/sh

cd $CMSSW_BASE/src

cvs co -r V07-13-13 PhysicsTools/PatAlgos # B3_6_X ?
cvs co -r V09-05-17 DataFormats/PatCandidates # B3_6_X ?
cvs co RecoHI/HiJetAlgos
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
scram b
`pwd`


