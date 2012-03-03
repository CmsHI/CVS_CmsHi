#!/bin/bash -
# for xsec see,
# https://twiki.cern.ch/twiki/bin/view/CMS/HiForestMC2011#Cross_section

#
# mit
#
for algo in akPu3PF; do
  # mixing classes
  mixmbFile="output-hy18mbv2_v29classes.root"
  #root -b -q analyzePhotonJet.C+'("akPu3PF","/net/hisrv0001/home/icali/hadoop/Hydjet1.8/Z2/merged/HydjetMB_merged.root","'$mixmbFile'",0,1.,0,"","",1)'

  cBinRefFile="output-data-Photon-v7-noDuplicate_v29.root"
  mergeCmd="hadd -f output-hy18qcdpho30and50and80v2_v29_xsec_$algo.root"
  mergeMixCmd="hadd -f output-hy18qcdpho30and50and80v2_v29_xsec_mixmb_$algo.root"
  for pthat in 30 50 80; do
    sampleWt=1;
    if [ $pthat -eq 30 ]; then sampleWt=1.59; fi
    if [ $pthat -eq 50 ]; then sampleWt=0.767; fi
    if [ $pthat -eq 80 ]; then sampleWt=0.172; fi
    echo sampleWt: $sampleWt
    inputFile="/net/hisrv0001/home/y_alive/scratch1/gammajet/temp/set1Merge/allQCDPhoton${pthat}_cent10_merged_highstat.root"
    outputFile="output-hy18qcdpho${pthat}v2_v29_xsec.root"
    rewtFile="norewt-"$outputFile
    echo $inputFile
    echo $outputFile
    echo $rewtFile
    echo $mixmbFile
    # mc embedded
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputFile'","'$rewtFile'",0,'$sampleWt',0,"","",0)'
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputFile'","'$outputFile'",0,'$sampleWt',1,"'$rewtFile'","'$cBinRefFile'",0)'
    mergeCmd=$mergeCmd" output-hy18qcdpho${pthat}v2_v29_xsec_$algo.root"

    # mc mix
    outputMixFile="output-hy18qcdpho${pthat}v2_v29_xsec_mixmb.root"
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputFile'","'$outputMixFile'",0,'$sampleWt',1,"'$rewtFile'","'$cBinRefFile'",2,"'$mixmbFile'")'
    mergeCmd=$mergeCmd" output-hy18qcdpho${pthat}v2_v29_xsec_mixmb$algo.root"

    # pp
    inputPpFile="/mnt/hadoop/cms/store/user/icali/Hydjet1.8/Z2/ppForest/allQCDPhotons_OnlySignal_merged/allQCD_hiSignal2760GeV_pthat${pthat}_merged.root"
    outputPpFile="output-qcdpho${pthat}hiSignalv2_v29_xsec.root"
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputPpFile'","'$outputPpFile'",0,'$sampleWt',0,"","",0)'

    # LO Pho
    if [ $pthat -eq 30 ]; then sampleWt=10800; fi
    if [ $pthat -eq 50 ]; then sampleWt=1024; fi
    if [ $pthat -eq 80 ]; then sampleWt=99.28; fi

    inputLOPhoFile="/net/hisrv0001/home/icali/hadoop/Hydjet1.8/Z2/LOPhotons_merged/LOPhotons${pthat}_merged.root"
    outputLOPhoFile="output-hy18lopho${pthat}v2_v29_xsec.root"
    rewtLOPhoFile="norewt-"$outputLOPhoFile
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputLOPhoFile'","'$rewtLOPhoFile'",0,'$sampleWt',0,"","",0)'
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputLOPhoFile'","'$outputLOPhoFile'",0,'$sampleWt',1,"'$rewtLOPhoFile'","'$cBinRefFile'",0)'

    inputPpLOPhoFile="/net/hisrv0001/home/icali/hadoop/Hydjet1.8/Z2/ppForest/LO_onlySignal_merged/LO_hiSignal2760GeV_pthat${pthat}_merged.root"
    outputPpLOPhoFile="output-lopho${pthat}hiSignalv2_v29_xsec.root"
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputPpLOPhoFile'","'$outputPpLOPhoFile'",0,'$sampleWt',0,"","",0)'
  done
  echo $mergeCmd
  echo $mergeMixCmd
done
