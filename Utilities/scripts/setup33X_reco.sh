#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

addpkg Configuration/PyReleaseValidation        # for modified ConfigBuilder
cvs co -r V00-00-05 RecoHI/Configuration        # for modified RecoHI_EventContent_cff
cvs co -r V02-00-00 SimGeneral/Configuration    # for HiMixing_EventContent

cvs co -d Misc UserCode/edwenger/Misc
mv Misc/ConfigBuilder.py Configuration/PyReleaseValidation/python # with HI event content
rm -r Misc

scramv1 b
