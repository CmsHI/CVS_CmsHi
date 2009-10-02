#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

# all reco/mixing stuff is in 330_pre6

# some code under development may be checked out:
# cvs co -r hiTrkFilter_BRANCH RecoHI/HiTracking

# Stuff needed for PAT and Jet Analysis
#cvs co UserCode/CmsHi/JetAnalysis
#cvs co UserCode/CmsHi/HiPatAlgos
#mv UserCode/CmsHi .
#rm -r UserCode

scramv1 b






