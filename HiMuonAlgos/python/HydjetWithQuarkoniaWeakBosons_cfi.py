# example cmsDriver.py CmsHi/HiMuonAlgos/HydjetWithQuarkoniaWeakBosons_cfi -s GEN,SIM,DIGI,L1,DIGI2RAW -n 5 --geometry DB --conditions auto:mc --datatier 'GEN-SIM-RAW' --eventcontent RAWDEBUG --scenario HeavyIons --no_exec
import FWCore.ParameterSet.Config as cms
from Configuration.Generator.Hydjet_Quenched_MinBias_2760GeV_cfi import *
myPars = cms.vstring('pythiaJets','pythiaZjets',
                     'pythiaBottomoniumNRQCD',
                     'pythiaCharmoniumNRQCD',
                     'pythiaQuarkoniaSettings',
                     'pythiaWeakBosons')
generator.PythiaParameters.parameterSets.extend(myPars)
generator.PythiaParameters.ppDefault = cms.vstring('MSEL=0   ! QCD hight pT processes',
                            'CKIN(3)=6.',# ! ptMin
                            'MSTP(81)=0')

