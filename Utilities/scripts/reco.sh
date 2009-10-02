infile = "/store/relval/CMSSW_3_3_0_pre5/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V8-v1/0004/D2E41C64-41AB-DE11-890F-001D09F2932B.root"
outfile = "hydjetMB_RECO.root"

cmsDriver.py hiReco -n 1 \
-s RAW2DIGI,RECO  --scenario HeavyIons \
--conditions FrontierConditions_GlobalTag,MC_31X_V9::All \
--datatier 'GEN-SIM-RECO' --eventcontent=RECODEBUG \
--filein=$infile --fileout=$outfile \
--no_exec
