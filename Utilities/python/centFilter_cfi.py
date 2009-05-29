import FWCore.ParameterSet.Config as cms

#10.00% 5.045
#20.00% 7.145
#30.00% 8.755
#40.00% 10.105
#50.00% 11.294
#60.00% 12.373
#70.00% 13.359
#80.00% 14.283
#90.00% 15.202
#100.00 %inf   

centFilter0010 = cms.EDFilter("CentFilter",
                              bmin = cms.untracked.double(0.),
                              bmax = cms.untracked.double(5.045)
                              )

centFilter1020 = cms.EDFilter("CentFilter",
                              bmin = cms.untracked.double(5.045),
                              bmax = cms.untracked.double(7.145)
                              )

centFilter2030 = cms.EDFilter("CentFilter",
                              bmin = cms.untracked.double(7.145),
                              bmax = cms.untracked.double(8.755)
                              )
centFilter3040 = cms.EDFilter("CentFilter",
                              bmin = cms.untracked.double(8.755),
                              bmax = cms.untracked.double(10.105)
                              )
centFilter4050 = cms.EDFilter("CentFilter",
                              bmin = cms.untracked.double(10.105),
                              bmax = cms.untracked.double(11.294)
                              )
centFilter5060 = cms.EDFilter("CentFilter",
                              bmin = cms.untracked.double(11.294),
                              bmax = cms.untracked.double(12.373)
                              )
centFilter6070 = cms.EDFilter("CentFilter",
                              bmin = cms.untracked.double(12.373),
                              bmax = cms.untracked.double(13.359)
                              )

centFilter7080 = cms.EDFilter("CentFilter",
                              bmin = cms.untracked.double(13.359),
                              bmax = cms.untracked.double(14.283)
                              )


centFilter8090 = cms.EDFilter("CentFilter",
                              bmin = cms.untracked.double(14.283),
                              bmax = cms.untracked.double(15.202)
                              )

centFilter90100 = cms.EDFilter("CentFilter",
                               bmin = cms.untracked.double(15.202),
                               bmax = cms.untracked.double(1000.)
                               )
