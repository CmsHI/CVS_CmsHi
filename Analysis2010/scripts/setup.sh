#!/bin/sh

indir=`pwd` 
cd $CMSSW_BASE/src/


cvs co -r V00-00-06 CondFormats/HIObjects
cvs co -r V00-01-20 DataFormats/HeavyIonEvent
cvs co -r V00-01-18 RecoHI/HiCentralityAlgos
cvs co -d CmsHi/Analysis2010 UserCode/CmsHi/Analysis2010

# Optional for other pings than high-pt:
cvs co -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis

scram b

cd $indir


