import FWCore.ParameterSet.Config as cms
from Configuration.Generator.Hydjet_Quenched_MinBias_2760GeV_cfi import *
myPars = cms.vstring('pythiaBottomoniumNRQCD',
                     'pythiaCharmoniumNRQCD')
generator.PythiaParameters.parameterSets.extend(myPars)
