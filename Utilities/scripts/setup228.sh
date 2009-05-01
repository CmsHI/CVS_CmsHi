#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

cvs co RecoHI/HiTracking/python
cvs co RecoHI/HiJetAlgos
cvs co RecoHI/HiEgammaAlgos

cvs co GeneratorInterface/HydjetInterface
cvs co GeneratorInterface/PyquenInterface
cvs co SimDataFormats/HiGenData
cvs co SimDataFormats/HepMCProduct
cvs co SimDataFormats/GeneratorProducts
cvs co -r $CMSSW_VERSION SimCalorimetry/HcalSimProducers
cat $CMSSW_BASE/src/SimCalorimetry/HcalSimProducers/src/HcalDigiProducer.cc | replace "doZDC(true)" "doZDC(false)" | replace "e.getByLabel(\"mix\", zdcHitsName , zdccf)" "// e.getByLabel(\"mix\", zdcHitsName , zdccf)" | replace "colzdc(new MixCollection<PCaloHit>(zdccf.product()))" "colzdc(new MixCollection<PCaloHit>(new CrossingFrame<PCaloHit>))" | replace "theHitCorrection->fillChargeSums(*colzdc)" "// zdc correction" > tmp.cc
mv tmp.cc $CMSSW_BASE/src/SimCalorimetry/HcalSimProducers/src/HcalDigiProducer.cc
cvs co UserCode/CmsHi
mv UserCode/CmsHi .
scramv1 b


