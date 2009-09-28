#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

# latest configurations
cvs co Configuration/Generator               # for hiSignal GEN configs
addpkg Configuration/PyReleaseValidation     # for modified ConfigBuilder

cvs co -d Misc UserCode/edwenger/Misc
mv Misc/ConfigBuilder.py Configuration/PyReleaseValidation/python  #hiTrackingParticles without DigiHiMix
rm -r Misc

# Stuff needed for PAT and Jet Analysis
#cvs co UserCode/CmsHi/JetAnalysis
#cvs co UserCode/CmsHi/HiPatAlgos
#mv UserCode/CmsHi .
#rm -r UserCode

scramv1 b






