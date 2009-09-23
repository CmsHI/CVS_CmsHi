#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

cvs co -r ap33X-branch Configuration/PyReleaseValidation # for modified ConfigBuilder
cvs co  RecoHI/Configuration                             # for modified RecoHI_EventContent_cff
cvs co -r V02-00-00 SimGeneral/Configuration             # for HiMixing_EventContent
addpkg Configuration/StandardSequences                   # for modified ReconstructionHeavyIons_cff
cvs co RecoHI/HiMuonAlgos/python                         # for muonRecoPbPb sequence

cvs co -d Misc UserCode/edwenger/Misc
mv Misc/ReconstructionHeavyIons_cff.py Configuration/StandardSequences/python # use imported globalRecoPbPb sequence
rm -r Misc

scramv1 b
