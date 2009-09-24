#include "CmsHi/PhotonAnalysis/interface/HiPhotonMCTruth.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"


#include <vector.h>

using namespace edm;
using namespace reco;

#define PI 3.141592653589793238462643383279502884197169399375105820974945

HiPhotonMCTruth::HiPhotonMCTruth(edm::Handle<GenParticleCollection> inputHandle, edm::Handle<edm::SubEventMap> subs)
{
  using namespace std;

  const GenParticleCollection *collection1 = inputHandle.product();
  int maxindex = (int)collection1->size();
  // cout << " Number of total Particles = " << maxindex << endl;
  
  vector<int> map;
  
  for(int i = 0; i < maxindex; i++)
    {
      int subEvtNum = (*subs)[GenParticleRef(inputHandle,i)];
      //    cout << i<<"th particle belog to " << subEvtNum<<"th sub-event\"<<endl;              
      map.push_back(subEvtNum);
    }
  cout << "map size = " << map.size() << endl;
 
  // HiMCGammaJetSignalDef mcisocut1(collection1 , map);
  mcisocut = HiMCGammaJetSignalDef(collection1 , map);
  
} 

bool HiPhotonMCTruth::indexMatch(const reco::Candidate &pp)
{
  using namespace std;
  using namespace edm;
  using namespace reco;
  // Check if a given particle is isolated.                                                                                                                               

  if (mcisocut.getIndex(pp) == -1)
    return false;
  else
    return true;
}

bool HiPhotonMCTruth::IsIsolated(const reco::Candidate &pp)
{
  using namespace std;
  using namespace edm;
  using namespace reco;
   // Check if a given particle is isolated.

  int ii = mcisocut.getIndex(pp);
  if (ii==-1)
    {
      cout << " the index of candidate map number is -1.. error!!! " << endl;
      //      if (pp.pdgId() ==22)
      //cout << " and it is a photon!!! " << endl;
      
      return false;
    }
  return  mcisocut.IsIsolated(pp,ii);
}


bool HiPhotonMCTruth::IsPrompt(const reco::GenParticle &pp)
{
  using namespace std;
  if ( pp.pdgId() != 22)
    return false;

  if ( pp.mother() ==0 ) 
    {
      //      cout <<    "No mom for this particle.." << endl;
      return false;
    }
  else 
    {
      if (pp.mother()->pdgId() == 22)
	{
	  cout << " found a prompt photon" << endl;
	  return true;
	}
      else
	return false;
    }
  
  
}
