#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

cvs co Configuration/EventContent               # for EventContentHeavyIons
cvs co Configuration/PyReleaseValidation        # for modified ConfigBuilder
cvs co -r V00-00-05 RecoHI/Configuration        # for modified RecoHI_EventContent_cff
cvs co UserCode/edwenger/Misc
mv UserCode/edwenger/Misc/EventContentHeavyIons_cff.py Configuration/EventContent/python
mv UserCode/edwenger/Misc/ConfigBuilder.py Configuration/PyReleaseValidation/python

# HI Utilities and Examples
cvs co UserCode/CmsHi/Utilities/python
cvs co UserCode/CmsHi/Utilities/test
mv UserCode/CmsHi .
rm -r UserCode

scramv1 b
