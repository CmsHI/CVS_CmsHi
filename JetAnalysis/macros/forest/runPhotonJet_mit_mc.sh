#!/bin/bash -
# for xsec see,
# https://twiki.cern.ch/twiki/bin/view/CMS/HiForestMC2011#Cross_section

#
# mit
#
for algo in akPu3PF; do
  # mixing classes
  #root -b -q analyzePhotonJet.C+'("akPu3PF","/mnt/hadoop/cms/store/user/jazzitup/hiForest/mergedFiles/forest_hydjetDrum_MB_20k.root","output-hy18mb_v28classes.root",0,1.,0,"","",1)'

  # mc embedded
  cBinRefFile="output-data-Photon-v7-noDuplicate_v29.root"
  mixFile="output-data-Photon-v7-noDuplicate_v29.root"
  mergeCmd="hadd -f output-hy18qcdpho30and50v2_v29_xsec_$algo.root"
  mergeMixCmd="hadd -f output-hy18qcdpho30and50v2_v29_xsec_mixmb_$algo.root"
  for pthat in 30 50 80; do
    sampleWt=1;
    if [ $pthat -eq 30 ]; then sampleWt=1.59; fi
    if [ $pthat -eq 50 ]; then sampleWt=0.767; fi
    if [ $pthat -eq 80 ]; then sampleWt=0.172; fi
    echo sampleWt: $sampleWt
    inputFile="/mnt/hadoop/cms/store/user/icali/Hydjet1.8/Z2/merged/allQCDPhoton${pthat}_merged.root"
    outputFile="output-hy18qcdpho${pthat}v2_v29_xsec.root"
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputFile'","norewt-'$outputFile'",0,'$sampleWt',0,"","",0)'
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputFile'","'$outputFile'",0,'$sampleWt',1,"norewt-'$outputFile'","'$cBinRefFile'",0)'
    mergeCmd=$mergeCmd" output-hy18qcdpho${pthat}v2_v29_xsec_$algo.root"
    # mc mix
    outputMixFile="output-hy18qcdpho${pthat}v2_v29_xsec_mixmb.root"
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputFile'","norewt-'$outputFile'",0,'$sampleWt',0,"","",2,"'$outputMixFile'")'
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputFile'","'$outputFile'",0,'$sampleWt',1,"norewt-'$outputFile'","'$cBinRefFile'",2,"'$outputMixFile'")'
  done
  echo $mergeCmd

  # pp
  #root -b -q analyzePhotonJet.C+'("'$algo'","/mnt/hadoop/cms/store/user/icali/Hydjet1.8/Z2/ppForest/allQCDPhotons_OnlySignal_merged/allQCD_hiSignal2760GeV_pthat30_merged.root","output-qcdpho30hiSignalv2_v29_xsec.root",0,1.59,0)'
  #root -b -q analyzePhotonJet.C+'("'$algo'","/mnt/hadoop/cms/store/user/icali/Hydjet1.8/Z2/ppForest/allQCDPhotons_OnlySignal_merged/allQCD_hiSignal2760GeV_pthat50_merged.root","output-qcdpho50hiSignalv2_v29_xsec.root",0,0.767,0)'
  #hadd -f output-qcdpho30and50hiSignalv2_v29_xsec_$algo.root output-qcdpho30hiSignalv2_v29_xsec_$algo.root output-qcdpho50hiSignalv2_v29_xsec_$algo.root
done
