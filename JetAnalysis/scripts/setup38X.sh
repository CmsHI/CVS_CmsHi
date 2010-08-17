#!/bin/sh                                                                                                                                                   
cvs co -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis

cvs co RecoHI/HiCentralityAlgos
cvs co RecoHI/HiMuonAlgos
cvs co RecoHI/HiCentralityAlgos/data

cvs co RecoJets/JetAlgorithms
cvs co RecoJets/JetProducers

cvs co HeavyIonsAnalysis/Configuration
cvs co DataFormats/HeavyIonEvent

cvs co -r $CMSSW_VERSION PhysicsTools/PatAlgos/python
cvs co CondFormats/JetMETObjects/data
mv CondFormats/JetMETObjects/data/L5Flavor_IC5Calo.txt CondFormats/JetMETObjects/data/L5Flavor_IC5.txt

scram b
