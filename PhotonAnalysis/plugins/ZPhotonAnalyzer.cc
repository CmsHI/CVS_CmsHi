#include "QCDPhotonAnalysis/DataAnalyzers/plugins/MultiPhotonAnalyzer.h"

#include <memory>
#include <iostream>
#include <algorithm>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/LorentzVector.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/EgammaReco/interface/PreshowerCluster.h"
#include "DataFormats/EgammaReco/interface/PreshowerClusterFwd.h"
#include "PhysicsTools/TagAndProbe/interface/CandidateAssociation.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"


// Histograms, ntuples
#include "UserCode/HafHistogram/interface/HTupleManager.h"
#include "UserCode/HafHistogram/interface/HHistogram.h"
#include "UserCode/HafHistogram/interface/HTuple.h"

//ROOT includes
#include <Math/VectorUtil.h>
#include <TLorentzVector.h>

using namespace pat;
using namespace edm;
using namespace std;
using namespace ROOT::Math::VectorUtil;


class ZPhotonAnalyzer : public MultiPhotonAnalyzer { 
  
public:

	explicit ZPhotonAnalyzer(const edm::ParameterSet&);
  ~ZPhotonAnalyzer();

protected:

  virtual void analyze(const edm::Event&, const edm::EventSetup&);

	virtual int selectStoreProbes(const edm::Event&,const edm::EventSetup&);

	
	edm::InputTag tagProbeMapProducer_; 	
	edm::InputTag tagProducer_;

	HHistogram *_invmassHist;
	
	
};

ZPhotonAnalyzer::ZPhotonAnalyzer(const edm::ParameterSet& ps):
	MultiPhotonAnalyzer(ps){

		tagProbeMapProducer_             = ps.getParameter<InputTag>("TagProbeMapProducer"); 
		tagProducer_                     = ps.getParameter<InputTag>("TagProducer");

		pdgId_                           = ps.getUntrackedParameter<int>("pdgId", 11);
		
		tplmgr->SetDir("1D-Spectra");
		_invmassHist = tplmgr->MomentumHistogram("Z_invmass"  ,"Invariant Mass (GeV/c^{2}); M (GeV/c^{2})",100,70,110);
		
}

void ZPhotonAnalyzer::analyze(const edm::Event& e, const edm::EventSetup& iSetup) {
   storeGeneral(e,iSetup);
	storeL1Trigger(e);
	storeHLT(e);
	storeHF(e);
	analyzeMC(e);
	storeVertex(e);
	storeMET(e);
	storeJets(e);

	int foundProbe = selectStoreProbes(e,iSetup);
	
	if (foundProbe > 0){
		// Dump analysis ntuple 
		// NOTE: dump ntuple only if at least one photon detected in a given acceptance
		//       number of entries in ntuple does not correspond to the number of analyzed events
		//       number of entries in certain histograms like "NumJets", "NumVtx" corresponds to the number of analyzed events  
		_ntuple->DumpData();   
	}
	
}

ZPhotonAnalyzer::~ZPhotonAnalyzer(){
}


int ZPhotonAnalyzer::selectStoreProbes(const edm::Event& e,const edm::EventSetup& iSetup){
	

  //Setup Tag And Probe quantities to be stored
  HTValVector<TLorentzVector> Z_p4(kMaxPhotons);
  HTValVector<Float_t>  Z_invmass(kMaxPhotons);
  HTValVector<Float_t> Z_pt(kMaxPhotons),Z_eta(kMaxPhotons),Z_phi(kMaxPhotons);

  HTValVector<TLorentzVector> Z_tag_p4(kMaxPhotons);
  HTValVector<Float_t> Z_tag_pt(kMaxPhotons),Z_tag_eta(kMaxPhotons),Z_tag_phi(kMaxPhotons);


  ///////////////////////////////////////////////////
  // Photon Section: Store Photons that are probes //
  ///////////////////////////////////////////////////
  
  // Tag-Probes
  edm::Handle< reco::CandViewCandViewAssociation> tagprobes;
  if ( ! e.getByLabel(tagProbeMapProducer_,tagprobes) ) {
    edm::LogWarning("Z") << "Could not extract tag-probe map with input tag " 
                         << tagProbeMapProducer_;
  }
  
  int probesFound = 0;

  if( tagprobes.isValid() ){
		
    PhotonCollection myprobes;

    // Loop over "photon" collection until we find a decent High Pt Photon
    reco::CandViewCandViewAssociation::const_iterator tpItr = tagprobes->begin();
    for( ; tpItr != tagprobes->end() && (probesFound < kMaxPhotons); ++tpItr ){
      const reco::CandidateBaseRef &tag = tpItr->key;
      reco::CandViewCandViewAssociation::result_type vprobes = (*tagprobes)[tag];
			

      //Finde the highest Pt probe for this tag
      int tempProbeNum = -1;
      double thePt = 0.;
      for ( uint myProbe = 0; myProbe < vprobes.size(); ++myProbe) {
        if((vprobes[myProbe].first)->pt() < ptMin_ || fabs((vprobes[myProbe].first)->eta()) > etaMax_) continue;
        double ptp = (vprobes[myProbe].first)->pt();
        if (ptp > thePt) {tempProbeNum = myProbe; thePt = ptp; }
      }
      
      if (tempProbeNum==-1) continue;
      
      Photon photon(*(vprobes[tempProbeNum].first.castTo< PhotonRef >()));
      myprobes.push_back(photon);
      
      /*******************************************************************************************/
      // Z information
      math::XYZTLorentzVector tpP4 = tag->p4() + photon.p4();
      
      Z_p4(probesFound)=TLorentzVector(tpP4.px(),tpP4.py(),tpP4.pz(),tpP4.energy());
      Z_invmass(probesFound)=tpP4.M();
      Z_pt(probesFound)=tpP4.pt();
      Z_eta(probesFound)=tpP4.eta();
      Z_phi(probesFound)=tpP4.phi();

      Z_tag_p4(probesFound)=TLorentzVector(tag->p4().px(),tag->p4().py(),tag->p4().pz(),tag->p4().energy());
      Z_tag_pt(probesFound)=tag->pt();
      Z_tag_eta(probesFound)=tag->eta();
      Z_tag_phi(probesFound)=tag->phi();
        
      _invmassHist->Fill(tpP4.M());

      /*******************************************************************************************/

      _gammaPtHist ->Fill(photon.et());
      _gammaEtaHist->Fill(photon.eta());
      
      float photon_phi = photon.phi();  // phi is over a whole circle, use fmod to collapse together all ecal modules
      // Only fill phiMod plot with barrel photons
      if (fabs(photon.eta())<1.5) _gammaPhiModHist->Fill( fmod(photon_phi+3.14159,20.0*3.141592/180.0)-10.0*3.141592/180.0 );
      probesFound++;
    }

    //Store Data for probes
    TString pfx("");
    storePhotons(e,iSetup,myprobes,pfx.Data());
    if( storePhysVectors_ ) {
      _ntuple->Column("Z_p4",Z_p4,pfx+"nPhotons");
    } else {
      _ntuple->Column("Z_invmass",Z_invmass,pfx+"nPhotons");
      _ntuple->Column("Z_pt",Z_pt,pfx+"nPhotons");
      _ntuple->Column("Z_eta",Z_eta,pfx+"nPhotons");
      _ntuple->Column("Z_phi",Z_phi,pfx+"nPhotons");
    }
    
    if( storePhysVectors_ ) {
      _ntuple->Column("Z_tag_p4",Z_tag_p4,pfx+"nPhotons");
    } else {
      _ntuple->Column("Z_tag_pt",Z_tag_pt,pfx+"nPhotons");
      _ntuple->Column("Z_tag_eta",Z_tag_eta,pfx+"nPhotons");
      _ntuple->Column("Z_tag_phi",Z_tag_phi,pfx+"nPhotons");
    }
    
  }	
  return (probesFound);
}

DEFINE_FWK_MODULE(ZPhotonAnalyzer);
