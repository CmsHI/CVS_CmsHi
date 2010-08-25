#!/bin/sh                                                                                                                                                   
cvs co -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis

cvs co RecoHI/HiCentralityAlgos
cvs co RecoHI/HiEvtPlaneAlgos
cvs co RecoHI/HiJetAlgos
cvs co RecoHI/HiMuonAlgos
cvs co RecoHI/HiTracking

cvs co RecoJets/JetAlgorithms
cvs co RecoJets/JetProducers

cvs co HeavyIonsAnalysis/Configuration
cvs co DataFormats/HeavyIonEvent
cvs co SimDataFormats/HiGenData

scram b
