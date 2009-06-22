import FWCore.ParameterSet.Config as cms


kinematics20 = cms.vstring('CKIN(3) = 20','CKIN(4) = 40')
kinematics40 = cms.vstring('CKIN(3) = 40','CKIN(4) = 70')
kinematics70 = cms.vstring('CKIN(3) = 70','CKIN(4) = 100')
kinematics100 = cms.vstring('CKIN(3) = 100','CKIN(4) = 2000')


partontrig100 = cms.EDFilter("MCSingleParticleFilter",
                                     moduleLabel = cms.untracked.string("signal"),
                                     Status = cms.untracked.vint32(2,2,2,2,2,2,2,1),
                                     MaxEta = cms.untracked.vdouble(3,3,3,3,3,3,3,3),
                                     MinEta = cms.untracked.vdouble(-3,-3,-3,-3,-3,-3,-3,-3),
                                     MinPt = cms.untracked.vdouble(38.5,38.5,38.5,38.5,38.5,38.5,38.5,38.5),
                                     ParticleID = cms.untracked.vint32(1,2,3,4,5,6,21,22)
                                     )

ecaltrig100 = cms.EDFilter("MCSingleParticleFilter",
                                   moduleLabel = cms.untracked.string("signal"),
                                   Status = cms.untracked.vint32(2, 2, 2, 2, 2,
                                                                 2, 1, 1, 2, 2,
                                                                 1, 1, 1),
                                   MaxEta = cms.untracked.vdouble(3, 3, 3, 3, 3,
                                                                  3, 3, 3, 3, 3,
                                                                  3, 3, 3),
                                   MinEta = cms.untracked.vdouble(-3, -3, -3, -3, -3,
                                                                  -3, -3, -3, -3, -3,
                                                                  -3, -3, -3),
                                   MinPt = cms.untracked.vdouble(36.125, 36.125, # eta
                                                                 35.25, 35.25, # eta'
                                                                 34.75, 34.75, # omega
                                                                 32.25, 32.25, # pi
                                                                 32.25,        # pi0
                                                                 31.5,         # K0
                                                                 38.75, 38.75, # e
                                                                 71.625       # gamma
                                                                 ),
                                   
                                   ParticleID = cms.untracked.vint32(221, -221, # eta
                                                                     331, -331, # eta'
                                                                     223, -223, # omega
                                                                     211, -211, # pi
                                                                     111,       # pi0
                                                                     311,       # K0
                                                                     11, -11,   # e
                                                                     22         # gamma
                                                                     )
                                   )

partontrig70 = cms.EDFilter("MCSingleParticleFilter",
                                    moduleLabel = cms.untracked.string("signal"),
                                    Status = cms.untracked.vint32(2,2,2,2,2,2,2,1),
                                    MaxEta = cms.untracked.vdouble(3,3,3,3,3,3,3,3),
                                    MinEta = cms.untracked.vdouble(-3,-3,-3,-3,-3,-3,-3,-3),
                                    MinPt = cms.untracked.vdouble(38.5,38.5,38.5,38.5,38.5,38.5,38.5,38.5),
                                    ParticleID = cms.untracked.vint32(1,2,3,4,5,6,21,22)
                                    )

ecaltrig70 = cms.EDFilter("MCSingleParticleFilter",
                                  moduleLabel = cms.untracked.string("signal"),
                                  Status = cms.untracked.vint32(2, 2, 2, 2, 2,
                                                                2, 1, 1, 2, 2,
                                                                1, 1, 1),
                                  MaxEta = cms.untracked.vdouble(3, 3, 3, 3, 3,
                                                                 3, 3, 3, 3, 3,
                                                                 3, 3, 3),
                                  MinEta = cms.untracked.vdouble(-3, -3, -3, -3, -3,
                                                                 -3, -3, -3, -3, -3,
                                                                 -3, -3, -3),
                                  MinPt = cms.untracked.vdouble(17.5, 17.5, # eta
                                                                16., 16., # eta'
                                                                18., 18., # omega
                                                                14.5, 14.5, # pi
                                                                17.5,       # pi0
                                                                15,       # K0
                                                                17.5, 17.5,   # e
                                                                38.5         # gamma
                                                                ),
                                  
                                  ParticleID = cms.untracked.vint32(221, -221, # eta
                                                                    331, -331, # eta'
                                                                    223, -223, # omega
                                                                    211, -211, # pi
                                                                    111,       # pi0
                                                                    311,       # K0
                                                                    11, -11,   # e
                                                                    22         # gamma
                                                                    )
                                  )



partontrig40 = cms.EDFilter("MCSingleParticleFilter",
                                    moduleLabel = cms.untracked.string("signal"),
                                    Status = cms.untracked.vint32(2,2,2,2,2,2,2,1),
                                    MaxEta = cms.untracked.vdouble(3,3,3,3,3,3,3,3),
                                    MinEta = cms.untracked.vdouble(-3,-3,-3,-3,-3,-3,-3,-3),
                                    MinPt = cms.untracked.vdouble(38.5,38.5,38.5,38.5,38.5,38.5,38.5,38.5),
                                    ParticleID = cms.untracked.vint32(1,2,3,4,5,6,21,22)
                                    )

ecaltrig40 = cms.EDFilter("MCSingleParticleFilter",
                                  moduleLabel = cms.untracked.string("signal"),
                                  Status = cms.untracked.vint32(2, 2, 2, 2, 2,
                                                                2, 1, 1, 2, 2,
                                                                1, 1, 1),
                                  MaxEta = cms.untracked.vdouble(3, 3, 3, 3, 3,
                                                                 3, 3, 3, 3, 3,
                                                                 3, 3, 3),
                                  MinEta = cms.untracked.vdouble(-3, -3, -3, -3, -3,
                                                                 -3, -3, -3, -3, -3,
                                                                 -3, -3, -3),
                                  MinPt = cms.untracked.vdouble(17.5, 17.5, # eta
                                                                16., 16., # eta'
                                                                18., 18., # omega
                                                                14.5, 14.5, # pi
                                                                17.5,       # pi0
                                                                15,       # K0
                                                                17.5, 17.5,   # e
                                                                38.5         # gamma
                                                                ),
                                  
                                  ParticleID = cms.untracked.vint32(221, -221, # eta
                                                                    331, -331, # eta'
                                                                    223, -223, # omega
                                                                    211, -211, # pi
                                                                    111,       # pi0
                                                                    311,       # K0
                                                                    11, -11,   # e
                                                                    22         # gamma
                                                                    )
                                )


partontrig20 = cms.EDFilter("MCSingleParticleFilter",
                                    moduleLabel = cms.untracked.string("signal"),
                                    Status = cms.untracked.vint32(2,2,2,2,2,2,2,1),
                                    MaxEta = cms.untracked.vdouble(3,3,3,3,3,3,3,3),
                                    MinEta = cms.untracked.vdouble(-3,-3,-3,-3,-3,-3,-3,-3),
                                    MinPt = cms.untracked.vdouble(20,20,20,20,20,20,20,20),
                                    ParticleID = cms.untracked.vint32(1,2,3,4,5,6,21,22)
                                    )

ecaltrig20 = cms.EDFilter("MCSingleParticleFilter",
                                moduleLabel = cms.untracked.string("signal"),
                                Status = cms.untracked.vint32(2, 2, 2, 2, 2,
                                                              2, 1, 1, 2, 2,
                                                              1, 1, 1),
                                MaxEta = cms.untracked.vdouble(3, 3, 3, 3, 3,
                                                               3, 3, 3, 3, 3,
                                                               3, 3, 3),
                                MinEta = cms.untracked.vdouble(-3, -3, -3, -3, -3,
                                                               -3, -3, -3, -3, -3,
                                                               -3, -3, -3),
                                MinPt = cms.untracked.vdouble( 16.75,16.75, # eta
                                                               10.5,10.5, # eta'
                                                               16.375, 16.375, # omega
                                                               13.25, 13.25, # pi
                                                               12.5,       # pi0
                                                               13.375,       # K0
                                                               23.625,23.625,   # e
                                                               21.625         # gamma
                                                               ),
                                
                                ParticleID = cms.untracked.vint32(221, -221, # eta
                                                                  331, -331, # eta'
                                                                  223, -223, # omega
                                                                  211, -211, # pi
                                                                  111,       # pi0
                                                                  311,       # K0
                                                                  11, -11,   # e
                                                                  22         # gamma
                                                                  )
                                )



ecalGenTrigger100 = cms.Sequence(partontrig100*ecaltrig100)
ecalGenTrigger70 = cms.Sequence(partontrig70*ecaltrig70)
ecalGenTrigger40 = cms.Sequence(partontrig40*ecaltrig40)
ecalGenTrigger20 = cms.Sequence(partontrig20*ecaltrig20)

