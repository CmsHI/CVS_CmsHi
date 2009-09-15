#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

# latest configurations
cvs co SimGeneral/MixingModule/python           # for mixHiSignal_cff
cvs co SimGeneral/Configuration/python                 # for HiMixing_EventContent
cvs co Configuration/Generator/python                  # for hiSignal Generation
cvs co Configuration/StandardSequences/python          # for DigiHiMix_cff   
cvs co Configuration/EventContent/python               # for EventContentHeavyIons
cvs co Configuration/PyReleaseValidation        # for modified ConfigBuilder

# 330_pre4 features
cvs co -r V11-00-00 PhysicsTools/HepMCCandAlgos/python  # HI GenParticleProducer
#cvs co -r V04-00-00 SimGeneral/TrackingAnalysis  # HI TrackingTruthProducer

# 330_pre5
cvs co -r V00-11-13 IOMC/RandomEngine/python


# HI Event Content
cvs co -r V00-00-05 RecoHI/Configuration        # for modified RecoHI_EventContent_cff
cvs co UserCode/edwenger/Misc
mv UserCode/edwenger/Misc/EventContentHeavyIons_cff.py Configuration/EventContent/python
mv UserCode/edwenger/Misc/HiMixing_EventContent_cff.py SimGeneral/Configuration/python
#mv UserCode/edwenger/Misc/DigiHiMix_cff.py Configuration/StandardSequences/python
mv UserCode/edwenger/Misc/ConfigBuilder.py Configuration/PyReleaseValidation/python

# HI Utilities and Examples
cvs co UserCode/CmsHi/Utilities/python
cvs co UserCode/CmsHi/Utilities/test

cp UserCode/CmsHi/Utilities/python/mixHiSignal_cff.py SimGeneral/MixingModule/python/
cp UserCode/CmsHi/Utilities/python/HiGenParticles_cfi.py PhysicsTools/HepMCCandAlgos/python/
cp UserCode/CmsHi/Utilities/python/IOMC_cff.py IOMC/RandomEngine/python/

# Stuff needed for PAT and Jet Analysis
cvs co UserCode/CmsHi/JetAnalysis/python
cvs co UserCode/CmsHi/HiPatAlgos/python
mv UserCode/CmsHi .
rm -r UserCode

cvs co RecoJets/Configuration/python
cvs co RecoJets/JetProducers/python
cvs co RecoJets/JetAlgorithms/python
cvs co RecoHI/HiTracking/python
cvs co RecoHI/HiJetAlgos/python
cvs co RecoHI/HiEgammaAlgos/python
cvs co RecoHI/HiMuonAlgos/python
cvs co RecoHI/HiCentralityAlgos/python
cvs co RecoHI/HiEvtPlaneAlgos/python

scramv1 b






