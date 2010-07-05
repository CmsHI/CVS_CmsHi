#!/bin/sh

cd $CMSSW_BASE/src
cvs co -d CmsHi/JulyExercise UserCode/CmsHi/JulyExercise
cvs co HeavyIonsAnalysis/Configuration
cvs co RecoHI/HiMuonAlgos
scram b





