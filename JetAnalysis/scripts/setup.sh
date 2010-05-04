#!/bin/sh

cd $CMSSW_BASE/src
cvs co -r V00-07-04 JetMETAnalysis/JetUtilities
cvs co -r V00-08-06 JetMETAnalysis/JetAnalyzers
cvs co -r jetCorrections_3_6_0_retrofit CondFormats/JetMETObjects
mv CondFormats/JetMETObjects/data/L5Flavor_IC5Calo.txt CondFormats/JetMETObjects/data/L5Flavor_IC5.txt 

cvs co UserCode/CmsHi/JetAnalysis
mv UserCode/CmsHi/JetAnalysis/bin/jet_response_analyzer_x.cc JetMETAnalysis/JetAnalyzers/bin/
scram b
`pwd`


