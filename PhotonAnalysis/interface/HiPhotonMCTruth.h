#ifndef HiPhotonMCTruth_h
#define HiPhotonMCTruth_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "SimDataFormats/HiGenData/interface/SubEventMap.h"
#include "CmsHi/PhotonAnalysis/interface/HiMCGammaJetSignalDef.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"

#include <vector.h>

class HiPhotonMCTruth
{
 public:
  HiPhotonMCTruth(edm::Handle<reco::GenParticleCollection> inputHandle, edm::Handle<edm::SubEventMap> subs);
  bool indexMatch(const reco::Candidate &pp1);
  bool IsPrompt(const reco::GenParticle &pp);
  bool IsIsolated(const reco::Candidate &pp);
  
 private:
  HiMCGammaJetSignalDef mcisocut;
};

#endif

