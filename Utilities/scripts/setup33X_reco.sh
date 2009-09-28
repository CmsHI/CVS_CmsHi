#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

# all reco stuff is in 330_pre5

# some code under development may be checked out:
# cvs co -r hiTrkFilter_BRANCH RecoHI/HiTracking

scramv1 b
