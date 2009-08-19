#!/bin/sh

export CVSROOT=:gserver:cmscvs.cern.ch:/cvs_server/repositories/CMSSW

cd $CMSSW_BASE/src
eval `scramv1 ru -sh`

# latest reconstruction code
cvs co RecoHI/Configuration
cvs co -r V01-00-04 RecoHI/HiTracking                        
cvs co RecoHI/HiJetAlgos
cvs co -r V00-00-02 RecoHI/HiEgammaAlgos
cvs co RecoHI/HiCentralityAlgos
cvs co -r V00-00-04 RecoHI/HiMuonAlgos

# latest generator configurations
cvs co Configuration/Generator
# latest generator interfaces (consistent impact parameter generation)
cvs co GeneratorInterface/HydjetInterface
cvs co -r embedding_v02 GeneratorInterface/PyquenInterface
# heavy ion event mixing tools
cvs co SimGeneral/MixingModule
cvs co SimDataFormats/CrossingFrame

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

# for heavy ion PAT candidates
cvs co UserCode/yetkin/DataFormats
mv UserCode/yetkin/DataFormats .

### Use the code below if you need gen-level filter for signal-mixing
### Warning: Not compatible with consistent b generation pyquen

#rm -r GeneratorInterface/PyquenInterface
#cvs co UserCode/yetkin/GeneratorInterface
#mv UserCode/yetkin/GeneratorInterface/* GeneratorInterface/

################################

cvs co UserCode/CmsHi
cvs co -r V00-01-02 UserCode/CmsHi/Utilities #HEAD as of Aug 19 without Philip's hiGenParticle modifications
mv UserCode/CmsHi .

scramv1 b


