#!/bin/sh

indir=`pwd` 
cd $CMSSW_BASE/src/


cvs co -r CondFormats/HIObjects
cvs co -r DataFormats/HeavyIonEvent
cvs co -r RecoHI/HiCentralityAlgos
cvs co -d CmsHi/Analysis2010 UserCode/CmsHi/Analysis2010

# Optional for other pings than high-pt:
cvs co -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis

scram b

cd $indir


