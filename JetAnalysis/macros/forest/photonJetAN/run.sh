#for m in plotPtRatioSignal_AllCent4.C plotDeltaPhiSignal_AllCent4.C; do
for m in plotPtRatioSignal_AllCent4.C; do
  for log in 0 1; do
    for doChk in 0 1; do
      for phoMin in 60; do
	for jetMin in 30; do
	  root -b -q $m+'(0,1,1,1,'$phoMin','$jetMin','$log','$doChk')'
	  root -b -q $m+'(2,1,1,1,'$phoMin','$jetMin','$log','$doChk')'
	  if [ $m == "plotPtRatioSignal_AllCent4.C" ]; then
	    root -b -q $m+'(0,2,1,1,'$phoMin','$jetMin','$log','$doChk')'
	    root -b -q $m+'(2,2,1,1,'$phoMin','$jetMin','$log','$doChk')'
	  fi
	done
      done
    done
  done
done
