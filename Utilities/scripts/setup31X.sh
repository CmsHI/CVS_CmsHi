#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

# Fix for 3_1_0_pre10
if echo "$CMSSW_VERSION" | grep "CMSSW_3_1_0_pre10" >/dev/null 2>&1
then
  echo You are using CMSSW_3_1_0_pre10.  Must patch pyqt.xml...
  cat $CMSSW_BASE/config/toolbox/slc4_ia32_gcc345/tools/selected/pyqt.xml | sed -e '/environment.*PYTHONPATH/d' > temp.xml
  mv temp.xml $CMSSW_BASE/config/toolbox/slc4_ia32_gcc345/tools/selected/pyqt.xml 
  scramv1 setup pyqt; scramv1 b clean
fi

cvs co RecoHI/Configuration
cvs co RecoHI/HiTracking                        
cvs co RecoHI/HiJetAlgos
cvs co RecoHI/HiEgammaAlgos
cvs co RecoHI/HiCentralityAlgos

cvs co Configuration/Generator
cvs co GeneratorInterface/HydjetInterface
cvs co -r embedding_v02 GeneratorInterface/PyquenInterface

cvs co SimDataFormats/HiGenData

# Turn off ZDC digitization
checkOutVersion=`echo $CMSSW_VERSION | sed "s/_patch1//g"`
cvs co -r $checkOutVersion SimCalorimetry/HcalSimProducers
cat $CMSSW_BASE/src/SimCalorimetry/HcalSimProducers/src/HcalDigitizer.cc | replace "doZDC(true)" "doZDC(false)" | replace "e.getByLabel(\"mix\", zdcHitsName , zdccf)" "// e.getByLabel(\"mix\", zdcHitsName , zdccf)" | replace "colzdc(new MixCollection<PCaloHit>(zdccf.product()))" "colzdc(new MixCollection<PCaloHit>(new CrossingFrame<PCaloHit>))" | replace "theHitCorrection->fillChargeSums(*colzdc)" "// zdc correction" > tmp.cc
mv tmp.cc $CMSSW_BASE/src/SimCalorimetry/HcalSimProducers/src/HcalDigitizer.cc

cvs co UserCode/CmsHi
mv UserCode/CmsHi .

scramv1 b


