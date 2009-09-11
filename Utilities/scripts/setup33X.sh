#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

# latest configurations
cvs co SimGeneral/MixingModule/python           # HiMixing Configuration
cvs co SimGeneral/Configuration                 # HiMixing Event Content
cvs co Configuration/Generator                  # HiSignal Generation
cvs co Configuration/StandardSequences          
cvs co Configuration/EventContent
cvs co Configuration/PyReleaseValidation

# 330_pre4 features
cvs co -r V11-00-00 PhysicsTools/HepMCCandAlgos # HI GenParticles
cvs co -r V06-00-00 DataFormats/HepMCCandidate
#cvs co -r V04-00-00 SimGeneral/TrackingAnalysis # HI TrackingParticles

# HI Event Content
cvs co -r V00-00-05 RecoHI/Configuration
cvs co UserCode/edwenger/Misc
mv UserCode/edwenger/Misc/EventContentHeavyIons_cff.py Configuration/EventContent
mv UserCode/edwenger/Misc/HiMixing_EventContent_cff.py SimGeneral/Configuration
mv UserCode/edwenger/Misc/DigiHiMix_cff.py Configuration/StandardSequences
mv UserCode/edwenger/Misc/ConfigBuilder.py Configuration/PyReleaseValidation

# HI Utilities and Examples
cvs co UserCode/CmsHi/Utilities/python
cvs co UserCode/CmsHi/Utilities/test

# Stuff needed for PAT and Jet Analysis
cvs co UserCode/CmsHi/JetAnalysis
cvs co UserCode/CmsHi/HiPatAlgos
mv UserCode/CmsHi .
rm -r UserCode

scramv1 b






