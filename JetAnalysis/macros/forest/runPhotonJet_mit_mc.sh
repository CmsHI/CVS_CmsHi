#!/bin/bash -
# for xsec see,
# https://twiki.cern.ch/twiki/bin/view/CMS/HiForestMC2011#Cross_section

#
# mit
#
#for algo in akPu3PF; do
#  # mixing classes
#  mixmbFile="output-hy18mbv2_v30classes.root"
#  #root -b -q analyzePhotonJet.C+'("akPu3PF","/net/hisrv0001/home/icali/hadoop/Hydjet1.8/Z2/merged/HydjetMB_merged.root","'$mixmbFile'",0,0,1.,0,"","",1)'
#
#  cBinRefFile="output-data-Photon-v7-noDuplicate_v29.root"
#  mergeCmd="hadd -f output-hy18qcdpho_pthatsv2_v30_xsec_$algo.root"
#  mergeMixCmd="hadd -f output-hy18qcdpho_pthatsv2_v30_xsec_mixmb_$algo.root"
#  mergePpCmd="hadd -f output-hiSignalqcdpho_pthatsv2_v30_xsec_$algo.root"
#  for pthat in 30 50 80; do
#    sampleWt=1;
#    if [ $pthat -eq 30 ]; then sampleWt=1.59; fi
#    if [ $pthat -eq 50 ]; then sampleWt=0.767; fi
#    if [ $pthat -eq 80 ]; then sampleWt=0.172; fi
#    echo sampleWt: $sampleWt
#    inputFile="/net/hisrv0001/home/y_alive/scratch1/gammajet/temp/set1Merge/allQCDPhoton${pthat}_cent10_merged_highstat.root"
#    outputFile="output-hy18qcdpho${pthat}v2_v30_xsec.root"
#    rewtFile="norewt-"$outputFile
##    echo $inputFile
##    echo $outputFile
##    echo $rewtFile
##    echo $mixmbFile
##    # mc embedded
##    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputFile'","'$rewtFile'",0,'$pthat,$sampleWt',0,"","",0)'
##    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputFile'","'$outputFile'",0,'$pthat,$sampleWt',1,"'$rewtFile'","'$cBinRefFile'",0)'
##    mergeCmd="${mergeCmd} $outputFile"
#
#    # mc mix
#    outputMixFile="output-hy18qcdpho${pthat}v2_v30_xsec_mixmb.root"
#    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputFile'","'$outputMixFile'",0,'$pthat,$sampleWt',1,"'$rewtFile'","'$cBinRefFile'",2,"'$mixmbFile'")'
#    mergeMixCmd+=" $outputMixFile"
#
##    # pp
##    inputPpFile="/mnt/hadoop/cms/store/user/icali/Hydjet1.8/Z2/ppForest/allQCDPhotons_OnlySignal_merged/allQCD_hiSignal2760GeV_pthat${pthat}_merged.root"
##    outputPpFile="output-qcdpho${pthat}hiSignalv2_v30_xsec.root"
##    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputPpFile'","'$outputPpFile'",0,'$pthat,$sampleWt',0,"","",0)'
##    mergePpCmd="${mergePpCmd} $outputPpFile"
#  done
#  echo $mergeCmd
#  echo $mergeMixCmd
#  echo $mergePpCmd
#
#  #eval $mergeCmd
#  #eval $mergeMixCmd
#  #eval $mergePpCmd
#done

# LO Pho
#mergeLOCmd="hadd -f output-hy18lophoAllPtHatv2_v30_xsec.root"
#mergePpLOCmd="hadd -f output-lophoAllPtHathiSignalv2_v30_xsec.root"
#for algo in akPu3PF; do
#  for pthat in 15 30 50 80; do
#    if [ $pthat -eq 15 ]; then sampleWt=53.94; fi
#    if [ $pthat -eq 30 ]; then sampleWt=4.961; fi
#    if [ $pthat -eq 50 ]; then sampleWt=0.6683; fi
#    if [ $pthat -eq 80 ]; then sampleWt=0.08547; fi
#
#    cBinRefFile="output-data-Photon-v7-noDuplicate_v29.root"
#    inputLOPhoFile="/net/hisrv0001/home/icali/hadoop/Hydjet1.8/Z2/LOPhotons_merged/LOPhotons${pthat}_merged.root"
#    outputLOPhoFile="output-hy18lopho${pthat}v2_v30_xsec.root"
#    rewtLOPhoFile="norewt-"$outputLOPhoFile
#    #root -b -q analyzePhotonJet.C+'("'$algo'","'$inputLOPhoFile'","'$rewtLOPhoFile'",0,'$pthat,$sampleWt',0,"","",0)'
#    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputLOPhoFile'","'$outputLOPhoFile'",0,'$pthat,$sampleWt',1,"'$rewtLOPhoFile'","'$cBinRefFile'",0)'
#    mergeLOCmd+=" $outputLOPhoFile"
#
#    inputPpLOPhoFile="/net/hisrv0001/home/icali/hadoop/Hydjet1.8/Z2/ppForest/LO_onlySignal_merged/LO_hiSignal2760GeV_pthat${pthat}_merged.root"
#    outputPpLOPhoFile="output-lopho${pthat}hiSignalv2_v30_xsec.root"
#    #root -b -q analyzePhotonJet.C+'("'$algo'","'$inputPpLOPhoFile'","'$outputPpLOPhoFile'",0,'$pthat,$sampleWt',0,"","",0)'
#    mergePpLOCmd+=" $outputPpLOPhoFile"
#  done
#done
#eval $mergeLOCmd
#eval $mergePpLOCmd

for algo in akPu3PF; do
  for pthat in 50; do
    if [ $pthat -eq 50 ]; then sampleWt=0.6683; fi
    inputLOPhoFile="/net/hisrv0001/home/icali/hadoop/Hydjet1.8/Z2/LOPhotons_merged/LOPhotons${pthat}_merged.root"
    outputLOPhoFile="output-hy18lopho${pthat}v2_v31_gensmear_xsec.root"
    #root -b -q analyzePhotonJet.C+'("'$algo'","'$inputLOPhoFile'","'$outputLOPhoFile'",0,'$pthat,$sampleWt',0,"","",0)'

    mixmbFile="output-hy18mbv2_v30classes.root"
    outputMixFile="output-hy18qcdpho${pthat}v2_v31_gensmear_xsec_mixmb.root"
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputLOPhoFile'","'$outputMixFile'",0,'$pthat,$sampleWt',0,"","",2,"'$mixmbFile'")'

    inputPyqFile="/net/hisrv0001/home/icali/hadoop/Pyquen/D6T/merged/Pyquen_LOPhotons${pthat}_merged.root"
    outputPyqFile="output-hy18pyquenlopho${pthat}v2_v31_gensmear_xsec.root"
    #root -b -q analyzePhotonJet.C+'("'$algo'","'$inputPyqFile'","'$outputPyqFile'",0,'$pthat,$sampleWt',0,"","",0,"")'

    outputPyqMixFile="output-hy18pyquenlopho${pthat}v2_v31_gensmear_xsec_mixmb.root"
    root -b -q analyzePhotonJet.C+'("'$algo'","'$inputPyqFile'","'$outputPyqMixFile'",0,'$pthat,$sampleWt',0,"","",2,"'$mixmbFile'")'
  done
done
