#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

checkOutVersion=`echo $CMSSW_VERSION | sed "s/_pre1//g" | sed "s/_pre2//g" | sed "s/_pre3//g"`
ver=`echo $checkOutVersion | sed "s/CMSSW//g" | sed "s/_//g"`
if [ $ver -lt 330 ]; then

# latest reconstruction code
cvs co -r V00-00-00 RecoHI/Configuration
cvs co -r V01-00-05 RecoHI/HiTracking                        
cvs co -r V00-00-01 RecoHI/HiJetAlgos
cvs co -r V00-00-03 RecoHI/HiEgammaAlgos
cvs co -r V00-00-05 RecoHI/HiMuonAlgos
cvs co RecoHI/HiCentralityAlgos
cvs co RecoHI/HiEvtPlaneAlgos

# latest generator configurations
cvs co Configuration/Generator
# latest generator interfaces (consistent impact parameter generation)
cvs co GeneratorInterface/Core
cvs co GeneratorInterface/HydjetInterface
cvs co GeneratorInterface/PyquenInterface # genfiltering in branch
# heavy ion event mixing tools
cvs co SimGeneral/MixingModule
#cvs co -r V05-00-00 SimGeneral/MixingModule
cvs co -r V04-00-00 SimDataFormats/CrossingFrame
cvs co -r V03-02-00 Mixing/Base
cvs co -r V00-15-07 FWCore/Sources

# latest centrality and event plane formats
cvs co DataFormats/HeavyIonEvent

# Turn off ZDC digitization for versions before 3_2_4
checkOutVersion=`echo $CMSSW_VERSION | sed "s/_patch1//g"`
ver=`echo $checkOutVersion | sed "s/CMSSW//g" | sed "s/_//g"`
if [ $ver -lt 324 ]; then
cvs co -r $checkOutVersion SimCalorimetry/HcalSimProducers
cat $CMSSW_BASE/src/SimCalorimetry/HcalSimProducers/src/HcalDigitizer.cc | replace "doZDC(true)" "doZDC(false)" | replace "e.getByLabel(\"mix\", zdcHitsName , zdccf)" "// e.getByLabel(\"mix\", zdcHitsName , zdccf)" | replace "colzdc(new MixCollection<PCaloHit>(zdccf.product()))" "colzdc(new MixCollection<PCaloHit>(new CrossingFrame<PCaloHit>))" | replace "theHitCorrection->fillChargeSums(*colzdc)" "// zdc correction" > tmp.cc
mv tmp.cc $CMSSW_BASE/src/SimCalorimetry/HcalSimProducers/src/HcalDigitizer.cc
fi

# Disable RecoHIMuon/HiMuTracking plugins with duplicate names
cvs co RecoHIMuon/HiMuTracking
cat $CMSSW_BASE/src/RecoHIMuon/HiMuTracking/plugins/SealModule.cc | replace "DEFINE_ANOTHER_FWK_MODULE" "// DEFINE_ANOTHER_FWK_MODULE" > tmp2.cc
mv tmp2.cc $CMSSW_BASE/src/RecoHIMuon/HiMuTracking/plugins/SealModule.cc
cat $CMSSW_BASE/src/RecoHIMuon/HiMuTracking/plugins/BuildFile | replace "RecoHI/HiMuonAlgos" "RecoHIMuon/HiMuTracking" | replace "RecoHIHiMuonAlgos" "RecoHIMuonHiMuTracking" > tmp3
mv tmp3 $CMSSW_BASE/src/RecoHIMuon/HiMuTracking/plugins/BuildFile

################################

cvs co -r V00-01-02 -d CmsHi/Utilities UserCode/CmsHi/Utilities
cvs co -r cmshi_32X -d CmsHi/JetAnalysis UserCode/CmsHi/JetAnalysis
scramv1 b

else
echo "This script is for 3_1_X and 3_2_X only. Use setup33X.sh for 3_3_X please!"
fi
