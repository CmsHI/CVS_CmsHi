infile = "/store/relval/CMSSW_3_3_0_pre5/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V8-v1/0004/D2E41C64-41AB-DE11-890F-001D09F2932B.root"
outfile = "gammajet20_MIX_RAW.root"

cmsDriver.py Pyquen_GammaJet_pt20_4TeV_cfi.py -n 1 \
-s GEN:hiSignal,SIM,DIGI,L1,DIGI2RAW  --scenario HeavyIons --himix \
--conditions FrontierConditions_GlobalTag,MC_31X_V9::All \
--datatier 'GEN-SIM-RAW' --eventcontent=RAWDEBUG \
--filein=$infile --fileout=$outfile --processName 'HISIGNAL' \
--no_exec
