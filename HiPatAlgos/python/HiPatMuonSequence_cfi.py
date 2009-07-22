from PhysicsTools.PatAlgos.producersLayer1.muonProducer_cff import *
from PhysicsTools.PatAlgos.mcMatchLayer0.muonMatch_cfi import *


##################################################################################
#
# Heavy Ion pat::Muon Production
#

allLayer1Muons.embedGenMatch = cms.bool(True)

hiPatMuonSequence = cms.Sequence( muonMatch * allLayer1Muons )

