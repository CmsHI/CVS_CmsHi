#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

cvs co -r BRANCH22X RecoHI/Configuration

cvs co -r BRANCH22X RecoHI/HiTracking
cvs co -r V02-02-06 RecoPixelVertexing/PixelLowPtUtilities

cvs co -r BRANCH22X RecoHI/HiJetAlgos
cvs co -r BRANCH22X RecoHI/HiEgammaAlgos

cvs co -r V01-02-16 GeneratorInterface/HydjetInterface
cvs co -r V00-02-12 GeneratorInterface/PyquenInterface

cvs co -r V00-00-04 SimDataFormats/HiGenData
cvs co -r V01-00-01 SimDataFormats/HepMCProduct
cvs co -r V01-00-04 SimDataFormats/GeneratorProducts

cvs co -r $CMSSW_VERSION SimCalorimetry/HcalSimProducers
cat $CMSSW_BASE/src/SimCalorimetry/HcalSimProducers/src/HcalDigiProducer.cc | replace "doZDC(true)" "doZDC(false)" | replace "e.getByLabel(\"mix\", zdcHitsName , zdccf)" "// e.getByLabel(\"mix\", zdcHitsName , zdccf)" | replace "colzdc(new MixCollection<PCaloHit>(zdccf.product()))" "colzdc(new MixCollection<PCaloHit>(new CrossingFrame<PCaloHit>))" | replace "theHitCorrection->fillChargeSums(*colzdc)" "// zdc correction" > tmp.cc
mv tmp.cc $CMSSW_BASE/src/SimCalorimetry/HcalSimProducers/src/HcalDigiProducer.cc

cvs co -r BRANCH22X UserCode/CmsHi
mv UserCode/CmsHi .

scramv1 b


