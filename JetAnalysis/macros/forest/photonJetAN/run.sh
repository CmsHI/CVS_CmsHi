#!/bin/bash -

outdir="fig/02.09_inclJetPhotonPurity_jgranges"
mkdir -p $outdir

doChk=0

# isolation schemes
for isolScheme in 0 2; do
  # standard
#  for ilog in 0 1; do
#    root -b -q plotPtRatioSignal_AllCent4_wSummary.C+'('$isolScheme',2,1,1,60,30,'$ilog','$doChk',"'$outdir'")'
#    #root -b -q plotDeltaPhiSignal_AllCent4_wSummary.C+'('$isolScheme',1,1,1,60,30,'$ilog','$doChk',"'$outdir'")'
#  done

  # kinematic xchecks
  for phoMin in 70; do
    for jetMin in 35; do
      #root -b -q plotPtRatioSignal_AllCent4_wSummary.C+'('$isolScheme',2,1,1,'$phoMin','$jetMin',0,'$doChk',"'$outdir'")'
      root -b -q plotDeltaPhiSignal_AllCent4_wSummary.C+'('$isolScheme',1,1,1,'$phoMin','$jetMin',0,'$doChk',"'$outdir'")'
    done
  done
  # work done
done
