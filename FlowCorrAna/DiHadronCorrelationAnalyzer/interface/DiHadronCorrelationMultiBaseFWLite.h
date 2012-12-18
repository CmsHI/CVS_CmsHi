#ifndef DiHadronCorrelationMultiBaseFWLite_
#define DiHadronCorrelationMultiBaseFWLite_

#include <exception>
#include <vector>
#include <string>

#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/HcalRecHit/interface/HBHERecHit.h"
#include "DataFormats/HcalRecHit/interface/HFRecHit.h"
#include "DataFormats/HcalRecHit/interface/HORecHit.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/DeDxData.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/ElectronFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidateFwd.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "RecoJets/JetAlgorithms/interface/JetAlgoHelper.h"
#include "WeisQCDAna/DiHadronCorrelationAnalyzer/interface/CutParameters.h"
#include "WeisQCDAna/DiHadronCorrelationAnalyzer/interface/DiHadronCorrelationEvent.h"
#endif

#include "DataFormats/FWLite/interface/ChainEvent.h"

class TBranch;
class TClonesArray;
class TH1D;
class TH2D;
class TH3D;
class TList;
class TTree;
class TNtuple;
class TVector3;
class TLorentzVector;
class DiHadronCorrelationEvent;

using namespace std;
using namespace reco;
using namespace edm;

#define PI 3.141592

class DiHadronCorrelationMultiBaseFWLite{
   
 protected:
   fwlite::ChainEvent event;
   
   // particle types
   enum ParticleType {
     kGenParticle=0,
     kTrack=1,
     kJet=2,
     kMuon=3,
     kPhoton=4,
     kEcalSC=5,
     kEcalBC=6,
     kPFHadron=7,
     kPFPhoton=8,
     kPFHadronPhoton=9,
     kPFPhotonTrack=10,
     kPFElectron=11,
     kPFMuon=12,
     kPFNeutral=13,
     kPFHadronHF=14,
     kPFEgammaHF=15,
     kPionZero=16,
     kPionZeroBkgUp=17,
     kPionZeroBkgDown=18,
     kCaloTower=19,
     kEcalRecHit=20,
     kHcalRecHit=21,
     kKshort=22,
     kLambda=23
   };

   ParticleType  trgID;
   ParticleType  assID;

   TFile *centFile;
   CentralityBins::RunMap HFhitBinMap;
   TString centTableName;
   int nCentBins;
   int centRunnum;

   //  vectors for tracks, hits etc
   DiHadronCorrelationEvent* eventcorr;
   vector<DiHadronCorrelationEvent> eventcorrArray;

   // histograms
   TH1D*  hdz;
   TH1D*  hd0;
   TH3D*  hEffWeight;
   TH1D*  hTrgWeight;
   TH1D*  hPileup_distfunc;
   TH1D*  hNVtx;
   TH2D*  hNVtxVsNMult;
   TH1D*  hZVtx;
   TH2D*  hXYVtx;
   TH1D*  hZVtxSep;
   TH1D*  hXVtxSep;
   TH1D*  hYVtxSep;
   TH1D*  hXYZVtxSep;
   TH1D*  hXYZVtxSepMin;
   TH1D*  hZVtxSim;
   TH2D*  hXYVtxSim;
   TH2D*  hZVtxRecoVsSim;
   TH2D*  hXVtxRecoVsSim;
   TH2D*  hYVtxRecoVsSim;
   TH2D*  hZVtxResVsNMult;
   TH2D*  hXVtxResVsNMult;
   TH2D*  hYVtxResVsNMult;
   TH1D*  hTrkZVtxRes;
   TH2D*  hTrkXYVtxRes;
   TH1D*  hTrkZVtxResSig;
   TH2D*  hTrkXYVtxResSig;
   TH2D*  hTrkZVtxResVsNMult;
   TH2D*  hTrkXVtxResVsNMult;
   TH2D*  hTrkYVtxResVsNMult;
   TH2D*  hTrkZVtxResVsPt;
   TH2D*  hTrkXVtxResVsPt;
   TH2D*  hTrkYVtxResVsPt;
   TH2D*  hTrkZVtxSimResVsNMult;
   TH2D*  hTrkXVtxSimResVsNMult;
   TH2D*  hTrkYVtxSimResVsNMult;
   TH1D*  hMultRawAll;
   TH1D*  hMultCorrAll;
   TH2D*  hMultRawTrigVsAssoc;
   TH2D*  hMultMaxVsSec;
   TH1D*  hPtAll_trg;
   TH2D*  hdNdetadptAll_trg;
   TH2D*  hdNdetadphiAll_trg;
   TH1D*  hPtAll_ass;
   TH2D*  hdNdetadptAll_ass;
   TH2D*  hdNdetadphiAll_ass;
   TH1D*  hPtCorrAll_trg;
   TH2D*  hdNdetadptCorrAll_trg;
   TH2D*  hdNdetadphiCorrAll_trg;
   TH1D*  hPtCorrAll_ass;
   TH2D*  hdNdetadptCorrAll_ass;
   TH2D*  hdNdetadphiCorrAll_ass;
   TH1D*  hdNJetsAll; 
   TH1D*  hPtJetsAll; 
   TH2D*  hdNdetadphiJetsAll; 
   TH1D*  hCentrality;
   TH1D*  hEPAngle;
   TH1D*  hHFTowerSum; 
   TH2D*  hHFvsNpixel;
   TH2D*  hHFvsZDC;
   TH1D*  hNpart;
   TH1D*  hHLTPaths;
   TH1D*  hEtTot;
   TH1D*  hInvMass;
   TH1D*  hMissEt;
   TH2D*  hMeanPtVsMult;
   TH1D*  hImbalance;
   TH2D*  hdNdPtdcostheta;
   TH2D*  hBetaVsP;
   TH1D*  hLeadTrackPt;
   TH1D*  hInvMass_Signal;
   TH2D*  hInvMassVsPt_Signal;
   TH2D*  hOpenAngleVsPt_Signal;
   TH1D*  hInvMass_Background;
   TH2D*  hInvMassVsPt_Background;
   TH2D*  hOpenAngleVsPt_Background;
   TH1D*  hInvMass_diphoton;
   TH2D*  hInvMassVsPt_diphoton;
   TH2D*  hOpenAngleVsPt_diphoton;
   TH2D*  hV0InvMassVsPt;

   TH2D*  hdNdetadphi_trg[MAXPTTRGBINS];
   TH2D*  hdNdetadphi_ass[MAXPTASSBINS];
   TH2D*  hdNdetadphiCorr_trg[MAXPTTRGBINS];
   TH2D*  hdNdetadphiCorr_ass[MAXPTASSBINS];
   TH1D*  hMult_trg[MAXPTTRGBINS];
   TH1D*  hMult_ass[MAXPTASSBINS];
   TH1D*  hMultCorr_trg[MAXPTTRGBINS];
   TH1D*  hMultCorr_ass[MAXPTASSBINS];
   TH1D*  hpT_Signal_trg[MAXPTTRGBINS];
   TH1D*  hpT_Signal_ass[MAXPTASSBINS];
   TH1D*  hpTCorr_Signal_trg[MAXPTTRGBINS];
   TH1D*  hpTCorr_Signal_ass[MAXPTASSBINS];
   TH1D*  hpT_Background_trg[MAXPTTRGBINS];
   TH1D*  hpT_Background_ass[MAXPTASSBINS];
   TH1D*  hpTCorr_Background_trg[MAXPTTRGBINS];
   TH1D*  hpTCorr_Background_ass[MAXPTASSBINS];

   TNtuple* eventNtuple;
   TNtuple* particleNtuple;
   TNtuple* trackNtuple;
   TNtuple* jetNtuple;
   TNtuple* highmultNtuple;
   TNtuple* hiGenInfoNtuple;
   
   // parameters
   CutParameters cutPara;
   int  checksign;
   int  eventClass;
   double hf;
   double hft;
   double npixel;
   double zdc;
   int bin;
   double b;
   double npart;
   double ncoll;
   double nhard;
   double phi0;
   int  nEvent; 
   int  nMult;
   int  nMultAll_trg;
   int  nMultAll_ass;
   double nMultCorr;
   double nMultAllCorr_trg;
   double nMultAllCorr_ass;
   int  nJets;
   int  nVertices;
   unsigned int  maxofflinetracks;
   unsigned int  secofflinetracks;
   double minVtxSep;
   int  NEtaBins;
   int  NPhiBins;      
   double  xVtx;
   double  yVtx;
   double  zVtx;
   double  xVtxError;
   double  yVtxError;
   double  zVtxError;
   double  xVtxSim;
   double  yVtxSim;
   double  zVtxSim;
   int  hiCentrality;
   int  EPIndex;
   double EPAngle;
   double  massTrg;
   double  massAss;
   unsigned int nMult_trg[MAXPTTRGBINS];
   unsigned int nMult_ass[MAXPTASSBINS];
   double nMultCorr_trg[MAXPTTRGBINS];
   double nMultCorr_ass[MAXPTASSBINS];
   double ptMean_trg[MAXPTTRGBINS];
   double ptMean_ass[MAXPTASSBINS];
   double ptMean2_trg[MAXPTTRGBINS];
   double ptMean2_ass[MAXPTASSBINS];
  
   double  getEnergyLoss(const reco::TrackRef & track); 
   virtual void Process(); 
   virtual void Analyze(int ievt);
   virtual void Init();
   virtual void MakeHists();
   virtual void NormalizeHists(int itrg, int jass);
   virtual void DeleteHists();
   virtual void GetMult();
   virtual void GetJets(); 
   virtual void LoopParticles(bool istrg);    
   virtual void LoopTracks(bool istrg, TString input);
   virtual void LoopEcalSC(bool istrg);
   virtual void LoopEcalBC(bool istrg);
   virtual void LoopJets(bool istrg);
   virtual void LoopMuons(bool istrg);
//   virtual void LoopPhotons(bool istrg);
   virtual void LoopPFCandidates(bool istrg, reco::PFCandidate::ParticleType pfID);
   virtual void LoopPionZeros(bool istrg, double massShift=0.0);
   virtual void LoopCaloTower(bool istrg);
   virtual void LoopEcalRecHits(bool istrg);
   virtual void LoopHcalRecHits(bool istrg);
   virtual void LoopV0Candidates(bool istrg, TString candtype);
   virtual void GetVertices();
   virtual void GetSimVertices();
   virtual void FillHistsInvariantMass(const DiHadronCorrelationEvent& eventcorr);
   virtual void AssignTrgPtBins(double pt, double eta, double phi, double charge, double effweight);
   virtual void AssignAssPtBins(double pt, double eta, double phi, double charge, double effweight);
   virtual bool SelectTriggerBit();
   virtual int  GetCentralityBin();
   virtual double GetEventPlaneAngle(unsigned int index);
   virtual double GetDeltaEta(double eta_trg, double eta_ass);
   virtual double GetDeltaPhi(double phi_trg, double phi_ass);
   virtual bool   GetPttrgBin(double pt, double eta, int itrg);
   virtual bool   GetPtassBin(double pt, double eta, int jass);
   virtual double GetTrgWeight(double nmult);
   virtual double GetEffWeight(double eta, double pt, double zvtx, int centbin);
   virtual TList* GetOutputs();
   
 public:

   DiHadronCorrelationMultiBaseFWLite(fwlite::ChainEvent&);
   virtual ~DiHadronCorrelationMultiBaseFWLite();

   ParticleType GetParticleID(TString particleid);
   void SetCutParameters(const CutParameters& cut) {cutPara = cut;} 
   void SetTrgID(ParticleType trgid) {trgID = trgid;}
   void SetAssID(ParticleType assid) {assID = assid;}
   void SetCentrality(TFile* centfile=0, TString centtablename=0, int ncentbins=20, int centrunnum=181502) {centFile = centfile; centTableName = centtablename; nCentBins = ncentbins; centRunnum=centrunnum;}
   void SetEventPlaneIndex(int epindex=-1) {EPIndex = epindex;}
   void SetCheckSign(int setchecksign) {checksign = setchecksign;}
   void SetEventClass(int eventclass=-1) {eventClass = eventclass;}
   void LoadEffWeight(TH3D* effweight) {hEffWeight=effweight;}
   void LoadTrgWeight(TH1D* trgweight) {hTrgWeight=trgweight;}
   void LoadPileUpDistFunc(TH1D* pileup_distfunc) {hPileup_distfunc=pileup_distfunc;}
   void SetNEtaPhiBins(int netabins, int nphibins)
	           { NEtaBins = netabins; NPhiBins = nphibins;}
};
#endif  // DiHadronCorrelationMultiBaseFWLite_
