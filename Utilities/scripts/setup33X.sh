#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

cvs co SimGeneral/MixingModule
cvs co Configuration/Generator
cvs co Configuration/StandardSequences

scramv1 b






