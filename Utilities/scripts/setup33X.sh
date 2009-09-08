#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

cvs co SimGeneral/MixingModule
cvs co Configuration/Generator
cvs co Configuration/StandardSequences

# Stuff needed for PAT and Jet Analysis
cvs co UserCode/CmsHi/JetAnalysis
cvs co UserCode/CmsHi/HiPatAlgos
mv UserCode/CmsHi .
rm -r UserCode

scramv1 b






