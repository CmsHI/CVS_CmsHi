#example cmsDriver.py CmsHi/HiMuonAlgos/HydjetWithQuarkonia_cfi -s GEN,SIM,DIGI,L1,DIGI2RAW -n 5 --geometry DB --conditions auto:mc --datatier 'GEN-SIM-RAW' --eventcontent RAWDEBUG --scenario HeavyIons --no_exec
import FWCore.ParameterSet.Config as cms
from Configuration.Generator.Hydjet_Quenched_MinBias_2760GeV_cfi import *
myPars = cms.vstring('pythiaBottomoniumNRQCD',
                     'pythiaCharmoniumNRQCD')
generator.PythiaParameters.parameterSets.extend(myPars)
