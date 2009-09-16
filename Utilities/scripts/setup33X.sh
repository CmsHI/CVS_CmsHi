#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

# latest configurations
cvs co SimGeneral/MixingModule/python           # for mixHiSignal_cff
cvs co SimGeneral/Configuration                 # for HiMixing_EventContent
cvs co Configuration/Generator                  # for hiSignal Generation
cvs co Configuration/StandardSequences          # for DigiHiMix_cff   
cvs co Configuration/EventContent               # for EventContentHeavyIons
cvs co Configuration/PyReleaseValidation        # for modified ConfigBuilder

# 330_pre4 features
cvs co -r V11-00-00 PhysicsTools/HepMCCandAlgos  # HI GenParticleProducer
cvs co -r V06-00-00 DataFormats/HepMCCandidate   # HI GenParticle format

# HI Event Content
cvs co -r V00-00-05 RecoHI/Configuration        # for modified RecoHI_EventContent_cff
cvs co -d Misc UserCode/edwenger/Misc
mv Misc/EventContentHeavyIons_cff.py Configuration/EventContent/python
mv Misc/HiMixing_EventContent_cff.py SimGeneral/Configuration/python
mv Misc/ConfigBuilder.py Configuration/PyReleaseValidation/python

# HI Tracking Particles
cvs co -r V04-00-00 SimGeneral/TrackingAnalysis                    # HI TrackingTruthProducer
mv Misc/TrackerPSimHitSelector.cc SimGeneral/TrackingAnalysis/src  # fix for PSimHit pointer
mv Misc/DigiHiMix_cff.py Configuration/StandardSequences/python    # Digi sequence using hiTrackingParticles
rm -r Misc

# HI GenParticle and Mixing configurations
cvs co -d Utilities UserCode/CmsHi/Utilities
cp Utilities/python/HiGenParticles_cfi.py PhysicsTools/HepMCCandAlgos/python/ # hiGenParticles
cp Utilities/python/mixHiSignal_cff.py SimGeneral/MixingModule/python/        # with hiGenParticles 
rm -r Utilities

# Random numbers for HI Mixing
cvs co -r V00-11-13 IOMC/RandomEngine           # hiSignal and hiSignalG4SimHits added 

# Stuff needed for PAT and Jet Analysis
cvs co UserCode/CmsHi/JetAnalysis
cvs co UserCode/CmsHi/HiPatAlgos
mv UserCode/CmsHi .
rm -r UserCode

scramv1 b






