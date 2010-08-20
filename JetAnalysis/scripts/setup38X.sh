#!/bin/sh                                                                                                                                                   
cvs co -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis

cvs co RecoHI/Configuration
cvs co RecoHI/HiCentralityAlgos
cvs co RecoHI/HiEvtPlaneAlgos
cvs co RecoHI/HiJetAlgos
cvs co RecoHI/HiMuonAlgos

cvs co RecoJets/JetAlgorithms
cvs co RecoJets/JetProducers

cvs co HeavyIonsAnalysis/Configuration
cvs co DataFormats/HeavyIonEvent
cvs co SimDataFormats/HiGenData

cvs co -r V08-00-24 PhysicsTools/PatAlgos

scram b
