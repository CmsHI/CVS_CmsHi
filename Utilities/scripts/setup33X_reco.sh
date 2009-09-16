#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

cvs co Configuration/EventContent               # for EventContentHeavyIons
cvs co Configuration/PyReleaseValidation        # for modified ConfigBuilder

cvs co -r V00-00-05 RecoHI/Configuration        # for modified RecoHI_EventContent_cff
cvs co -d Misc UserCode/edwenger/Misc
mv Misc/EventContentHeavyIons_cff.py Configuration/EventContent/python
mv Misc/ConfigBuilder.py Configuration/PyReleaseValidation/python

#Need also HiMixing event content or cmsDriver breaks on python error
cvs co SimGeneral/Configuration                 # for HiMixing_EventContent
mv Misc/HiMixing_EventContent_cff.py SimGeneral/Configuration/python

rm -r Misc

scramv1 b
