#!/bin/sh

infile="/store/relval/CMSSW_3_3_0_pre6/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_31X_V9-v1/0005/1CCBE44D-F1AF-DE11-A698-001D09F27003.root"
outfile="hydjetMB_RECO.root"

cmsDriver.py hiReco -n 1 \
-s RAW2DIGI,RECO  --scenario HeavyIons \
--conditions FrontierConditions_GlobalTag,MC_31X_V9::All \
--datatier 'GEN-SIM-RECO' --eventcontent=RECODEBUG \
--filein=$infile --fileout=$outfile \
--no_exec
