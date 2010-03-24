import FWCore.ParameterSet.Config as cms
from Configuration.Generator.PyquenDefaultSettings_cff import pyquenPythiaDefaultBlock
pyquenPythiaDefaultBlock.ppDefault = cms.vstring('MSEL=1   ! QCD hight pT processes',
                            'CKIN(3)=4.',# ! ptMin
                            'MSTP(81)=0')

from Configuration.Generator.Hydjet_Quenched_MinBias_2760GeV_cfi import *
myPars = cms.vstring('pythiaBottomoniumNRQCD',
                     'pythiaCharmoniumNRQCD',
                     'pythiaWeakBosons')
generator.PythiaParameters.parameterSets.extend(myPars)

