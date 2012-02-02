#!/bin/bash -

outdir="02.02_AN"
mkdir -p $outdir

doChk=0

for m in plotPtRatioSignal_AllCent4_wSummary.C plotDeltaPhiSignal_AllCent4_wSummary.C; do
  log=0
  normMode=2
  if [ $m=="plotDeltaPhiSignal_AllCent4_wSummary.C" ]; then
    log=1
    normMode=1
  fi

  # isolation schemes
  for isolScheme in 0 2; do
    
    for ilog in 0 1; do
      root -b -q $m+'('$isolScheme','$normMode',1,1,60,30,'$ilog','$doChk',"'$outdir'")'
    done

    # kinematic xchecks
    for phoMin in 60 50 70; do
      for jetMin in 30 35; do
	root -b -q $m+'('$isolScheme','$normMode',1,1,'$phoMin','$jetMin','$log','$doChk',"'$outdir'")'
      done
    done

  done
done
