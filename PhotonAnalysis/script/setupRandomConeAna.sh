cd $CMSSW_BASE/src

cvs co -d RandomConeAna UserCode/EYKim/photonStudy/RandomConeAna
addpkg RecoEgamma/PhotonIdentification
addpkg RecoEgamma/EgammaIsolationAlgos

# apply Yongsun's patch (ignore version dependence for the moment)
mv RandomConeAna/patches/PhotonIsolationCalculator.cc  $CMSSW_BASE/src/RecoEgamma/PhotonIdentification/src
mv RandomConeAna/patches/PhotonIsolationCalculator.h   $CMSSW_BASE/src/RecoEgamma/PhotonIdentification/interface
mv RandomConeAna/patches/EgammaRecHitIsolation.cc      $CMSSW_BASE/src/RecoEgamma/EgammaIsolationAlgos/src
mv RandomConeAna/patches/EgammaRecHitIsolation.h       $CMSSW_BASE/src/RecoEgamma/EgammaIsolationAlgos/interface
mv RandomConeAna/patches/isolationCalculator_cfi.py    $CMSSW_BASE/src/RecoEgamma/PhotonIdentification/python
mv RandomConeAna/patches/EgammaEcalRecHitIsolationProducer.h   $CMSSW_BASE/src/RecoEgamma/EgammaIsolationAlgos/plugins
mv RandomConeAna/patches/EgammaEcalRecHitIsolationProducer.cc  $CMSSW_BASE/src/RecoEgamma/EgammaIsolationAlgos/plugins

rm RandomConAna/patches -rf
