#!/bin/sh

infile="/store/relval/CMSSW_3_4_0_pre5/RelValHydjetQ_MinBias_4TeV/GEN-SIM-RAW/MC_3XY_V12-v1/0002/F4B78E40-0FCC-DE11-9C42-0030487A322E.root"
outfile="zmumuAcc_GEN.root"

cmsDriver.py GeneratorInterface/PyquenInterface/python/Pyquen_Zmumu_4TeV_dimuonAcc_cfi.py -n 1 \
-s GEN:hiSignal  --scenario HeavyIons --himix \
--conditions FrontierConditions_GlobalTag,MC_3XY_V12::All \
--datatier 'GEN' --eventcontent=RAWDEBUG \
--filein=$infile --fileout=$outfile --processName 'HISIGNAL' \
--no_exec
