#ifndef CmsHi_PhotonAnalysis_SinglePhotonAnalyzer_h
#define CmsHi_PhotonAnalysis_SinglePhotonAnalyzer_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include <TLorentzVector.h>
#include "UserCode/HafHistogram/interface/HColumn.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"

#include "CmsHi/PhotonAnalysis/plugins/Limits.h"
#if MPA_VERSION < 2
#include "RecoEgamma/EgammaTools/interface/ConversionLikelihoodCalculator.h"
#endif

class HTupleManager;
class HHistogram;
class HTuple;
class EcalClusterLazyTools;
class ConversionLikelihoodCalculator;
class PhotonMCTruthFinder;

// comparison operator needed by HTValVector
bool operator < (const TLorentzVector & a, const TLorentzVector & b);
bool operator < (const TVector3 & a,       const TVector3 & b      );

class SinglePhotonAnalyzer : public edm::EDAnalyzer { 
  
public:
  
  explicit SinglePhotonAnalyzer(const edm::ParameterSet&);
  ~SinglePhotonAnalyzer();

  math::XYZPoint vtx_;

#if MPA_VERSION < 2
  ConversionLikelihoodCalculator* theLikelihoodCalc_;
#endif

protected:
	
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
	
  virtual void storeGeneral(const edm::Event&, const edm::EventSetup& );
  virtual void storeL1Trigger(const edm::Event&);
  virtual void storeHLT(const edm::Event&);
  virtual void storeHF(const edm::Event&);
  virtual bool analyzeMC(const edm::Event&);
  virtual void storeVertex(const edm::Event&);
  virtual bool storeMET(const edm::Event&);
  virtual int  storeJets(const edm::Event&);
  virtual bool selectStorePhoton(const edm::Event&,const edm::EventSetup&);
	       	
	
  virtual void storePhotonAOD(pat::Photon *photon, const edm::Event& e, const edm::EventSetup &es, HTuple *tpl, const char* prefx = "PHO1_");
  virtual bool storeMCMatch( const edm::Event& e,pat::Photon *photon, const char* prefx = "PHO1_");	
  virtual Int_t getNumOfPreshClusters(pat::Photon *photon, const edm::Event&);
  virtual Float_t getESRatio(pat::Photon *photon, const edm::Event&, const edm::EventSetup&);


  // obtain generator-level calorimeter isolation and track isolation 
  // distribution, return number of particles and sumet surrounding the candidate
  
  virtual Float_t getGenCalIso(edm::Handle<reco::GenParticleCollection> handle,
			       reco::GenParticleCollection::const_iterator thisPho, const Float_t dRMax=0.4);
  virtual Float_t getGenTrkIso(edm::Handle<reco::GenParticleCollection> handle,
			       reco::GenParticleCollection::const_iterator thisPho, const Float_t dRMax=0.4);

  // collection of gen particles that are converted photons
  virtual void storeConvMCTruth(const edm::Event& e, 
				reco::GenParticleCollection::const_iterator thisPho, HTuple *tpl, const char* prefx = "");

  PhotonMCTruthFinder*                            thePhotonMCTruthFinder_;

	
	// Configured fields
  bool verbose_;                 // verbose flag
  bool fillMCNTuple_;            // fill generator ntuple flag
  bool doL1Objects_;             // store L1 Object flag
  bool isMCData_;                // run over MCData flag
  bool storePhysVectors_;        // store TLorentzVector/TVector3 objects instead of plain floats
  std::string outputFile_;       // name of output file
	
  edm::InputTag hlTriggerResults_;    // Input tag for TriggerResults
  edm::InputTag l1gtReadout_;         // Input tag for L1 Global Trigger Readout
  edm::InputTag l1IsolTag_;           // Input tag for L1 EM isolated collection
  edm::InputTag l1NonIsolTag_;        // Input tag for L1 EM non isolated collection
  std::vector<std::string> triggerPathsToStore_;  // Vector to store list of HLT paths to store results of in ntuple

  edm::InputTag genParticleProducer_; // MC particle producer
  edm::InputTag photonProducer_;      // photon producer
  edm::InputTag trackProducer_;       // track producer 
  edm::InputTag jetProducer_;         // jet producer 
  edm::InputTag metProducer_;         // input tag for MET 
  edm::InputTag vertexProducer_;      // vertecies producer
  edm::InputTag beamSpotProducer_;    // beam spot producer
	
  edm::InputTag compPhotonProducer_;      // photon producer                                                                                                          
  
  edm::InputTag ebReducedRecHitCollection_;
  edm::InputTag eeReducedRecHitCollection_;
  edm::InputTag srcTowers_;           // CaloTowers
	
  edm::TriggerNames triggerNames_;    // TriggerNames class
	

  // HepMC switch for HI July Exercise.
  bool         isMC_; 
  
  // basiccluster inputtags for heavy ion
  edm::InputTag basicClusterBarrel_;
  edm::InputTag basicClusterEndcap_;
  edm::InputTag hbhe_;
  edm::InputTag hf_;
  edm::InputTag ho_;
     
  double       ptMin_;            // Photon pt threshold
  double       etaMax_;           // Maximum photon |eta|
  double       ecalBarrelMaxEta_; // Begining of ECAL Barrel/Endcap gap
  double       ecalEndcapMinEta_; // End of ECAL Barrel/Endcap gap
  double       ptJetMin_;         // Jet pt threshold
  int          pdgId_;            // PDG ID of expected MC particle
  std::vector<int> otherPdgIds_;  // PDG ID of other MC particles to match
  double       mcPtMin_;          // min MC particle pt
  double       mcEtaMax_;         // max MC particle eta
  
  // TupleManager, Histograms, ntuples
  HTupleManager  *tplmgr; 
  
  // Leading photon  MC truth histograms
  HHistogram     *_ptHist;       // leading photon pt histo
  HHistogram     *_ptHatHist;       // leading photon pt histo                                                                    
  HHistogram     *_etaHist;      // leading photon eta histo
  HHistogram     *_vtxX;         // generated vertex X
  HHistogram     *_vtxY;         // generated vertex Y
  HHistogram     *_vtxZ;         // generated vertex Z
	
  // Reco histograms
  HHistogram     *_gammaPtHist;  // leading photon pt histo
  HHistogram     *_gammaEtaHist; // leading photon eta histo
  HHistogram     *_gammaPhiModHist; // leading photon phi_mod = phi * 180/pi mod 20 - 10
  HHistogram     *_metHist;      // MET histo
  HHistogram     *_nVtxHist;     // number of vertecies
  HHistogram     *_primVtxX;     // reconstructed primary vertex X
  HHistogram     *_primVtxY;     // reconstructed primary vertex Y
  HHistogram     *_primVtxZ;     // reconstructed primary vertex Z
  HHistogram     *_nJetsHist;    // number of jets
  HHistogram     *_nPhotonsHist;  //number of Photons

  // Flags for the fillers
  bool 	doStoreGeneral_; 	 // Store General information
  bool 	doStoreHLT_;     	 // Store HLT Trigger	
  bool	doStoreL1Trigger_;	 // Store L1 Trigger
  bool 	doStoreHF_;		 // Store HF
  bool	doStoreVertex_;		 // Store Vertex
  bool 	doStoreMET_; 		 // Store MET
  bool 	doStoreJets_;		 // Store Jets

  bool  doStoreCompCone_;

  HTuple         *_ntuple;        // Analysis ntuple
  HTuple         *_ntupleMC;      // MC truth ntuple

  // heavy ion stuffs

  const CentralityBins * cbins_;

	
};


#endif
