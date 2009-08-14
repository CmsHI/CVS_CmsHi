#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

cvs co RecoHI/Configuration
cvs co -r V01-00-04 RecoHI/HiTracking                        
cvs co RecoHI/HiJetAlgos
cvs co RecoHI/HiEgammaAlgos
cvs co RecoHI/HiCentralityAlgos

cvs co Configuration/Generator
cvs co GeneratorInterface/HydjetInterface
cvs co -r embedding_v02 GeneratorInterface/PyquenInterface

cvs co SimDataFormats/HiGenData

cvs co SimGeneral/MixingModule
cvs co SimGeneral/CrossingFrame

# Turn off ZDC digitization
checkOutVersion=`echo $CMSSW_VERSION | sed "s/_patch1//g"`
ver=`echo $checkOutVersion | sed "s/CMSSW//g" | sed "s/_//g"`
if [ $ver -lt 324 ]; then
cvs co -r $checkOutVersion SimCalorimetry/HcalSimProducers
cat $CMSSW_BASE/src/SimCalorimetry/HcalSimProducers/src/HcalDigitizer.cc | replace "doZDC(true)" "doZDC(false)" | replace "e.getByLabel(\"mix\", zdcHitsName , zdccf)" "// e.getByLabel(\"mix\", zdcHitsName , zdccf)" | replace "colzdc(new MixCollection<PCaloHit>(zdccf.product()))" "colzdc(new MixCollection<PCaloHit>(new CrossingFrame<PCaloHit>))" | replace "theHitCorrection->fillChargeSums(*colzdc)" "// zdc correction" > tmp.cc
mv tmp.cc $CMSSW_BASE/src/SimCalorimetry/HcalSimProducers/src/HcalDigitizer.cc
fi

cvs co UserCode/yetkin/DataFormats
mv UserCode/yetkin/DataFormats .

cvs co UserCode/CmsHi
mv UserCode/CmsHi .

scramv1 b


