#!/bin/sh

cvs co -r V04-00-01 RecoJets/JetAlgorithms
cvs co -r V05-01-04 RecoJets/JetProducers
cvs co DataFormats/HeavyIonEvent
cvs co RecoHI/HiJetAlgos
cvs co RecoHI/HiCentralityAlgos

scram b





