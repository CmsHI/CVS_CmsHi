
/** \class SinglePhotonAnalyzerTree  CmsHi/PhotonAnalysis/plugins/SinglePhotonAnalyzerTree.cc
 *
 * Description: 
 * Analysis code of the QCD Photons group;
 * Data Analyzer for the single photon (inclusive isolated photons and photon plus jets) cross section measurement; 
 * Makes ntuple of the leading photon and array of jets in each event;
 * Store in ntuple run conditions and missing ET information for each event;
 * Store in ntuple trigger and vertexing information for each event;
 * Makes ntuple for the generator prompt photon kinematics and genealogy;
 * Perform the MC truth matching for the reconstructed photon;
 * Fill number of DQM histograms 
 *
 * \author Serguei Ganjour,     CEA-Saclay/IRFU, FR
 * \author Ted Ritchie Kolberg, University of Notre Dame, US
 * \author Michael B. Anderson, University of Wisconsin Madison, US 
 * \author Laurent Millischer,  CEA-Saclay/IRFU, FR
 * \author Vasundhara Chetluru, FNAL, US
 * \author Vladimir Litvin,     Caltech, US
 * \author Yen-Jie Lee,         MIT, US
 * \author Abraham DeBenedetti, University of Minnesota, US
 * \author Pasquale Musella,    LIP, PT
 * \author Shin-Shan Eiko Yu,   National Central University, TW
 * \author Rong-Shyang Lu,      National Taiwan University, TW
 *
 * \version $Id: SinglePhotonAnalyzerTree.cc,v 1.3 2011/10/06 19:16:52 kimy Exp $
 *
 */
// This was modified to fit with Heavy Ion collsion by Yongsun Kim ( MIT)                                                                                                

#include "CmsHi/PhotonAnalysis/plugins/SinglePhotonAnalyzerTree.h"

#include <memory>
#include <iostream>
#include <algorithm>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Utilities/interface/InputTag.h"

//Trigger DataFormats
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
#include "L1Trigger/GlobalTrigger/interface/L1GlobalTrigger.h"

#include "DataFormats/L1Trigger/interface/L1EmParticle.h"
#include "DataFormats/L1Trigger/interface/L1EmParticleFwd.h"

#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidateFwd.h"

#include "DataFormats/Common/interface/TriggerResults.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/VertexReco/interface/Vertex.h"


#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/EgammaReco/interface/PreshowerCluster.h"
#include "DataFormats/EgammaReco/interface/PreshowerClusterFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"
#include "CondFormats/DataRecord/interface/EcalChannelStatusRcd.h"
#include "CommonTools/Utils/interface/PtComparator.h"
//#include "RecoEgamma/EgammaTools/interface/ConversionLikelihoodCalculator.h"
#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"

//geometry
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"

#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/EcalAlgo/interface/EcalPreshowerGeometry.h"

// for conversion truth
#include "RecoEgamma/EgammaMCTools/interface/ElectronMCTruth.h"
#include "RecoEgamma/EgammaMCTools/interface/PhotonMCTruth.h"
#include "RecoEgamma/EgammaMCTools/interface/PhotonMCTruthFinder.h"
#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"

#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"

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

bool operator < (const TLorentzVector & a, const TLorentzVector & b) { return a.Pt() < b.Pt(); }
bool operator < (const TVector3 & a,       const TVector3 & b      ) { return a.Pt() < b.Pt(); }


SinglePhotonAnalyzerTree::SinglePhotonAnalyzerTree(const edm::ParameterSet& ps):
   cbins_(0)
 {

  verbose_                         = ps.getUntrackedParameter<bool>("verbose", false);
  fillMCNTuple_                    = ps.getUntrackedParameter<bool>("FillMCNTuple", true);
  doL1Objects_                     = ps.getUntrackedParameter<bool>("DoL1Objects",  false);
  isMCData_                        = kFALSE;//Set by checking if generator block is valid
  storePhysVectors_                = ps.getUntrackedParameter<bool>("StorePhysVectors",  false);
  outputFile_                      = ps.getParameter<string>("OutputFile");

  hlTriggerResults_                = ps.getParameter<InputTag>("HltTriggerResults");
  l1gtReadout_                     = ps.getParameter<InputTag>("L1gtReadout");
  l1IsolTag_                       = ps.getParameter<InputTag>("L1IsolTag");
  l1NonIsolTag_                    = ps.getParameter<InputTag>("L1NonIsolTag");
  triggerPathsToStore_             = ps.getParameter<vector<string> >("TriggerPathsToStore");

  genParticleProducer_             = ps.getParameter<InputTag>("GenParticleProducer");
  hepMCProducer_                   = ps.getParameter<InputTag>("HepMCProducer");
  genEventScale_                   = ps.getParameter<InputTag>("GenEventScale");
  photonProducer_                  = ps.getParameter<InputTag>("PhotonProducer"); 
  compPhotonProducer_              = ps.getParameter<InputTag>("compPhotonProducer");
  
  trackProducer_                   = ps.getParameter<InputTag>("TrackProducer");
  jetProducer_                     = ps.getParameter<InputTag>("JetProducer");
  metProducer_                     = ps.getParameter<InputTag>("METProducer");
  vertexProducer_                  = ps.getParameter<InputTag>("VertexProducer");
  beamSpotProducer_                = ps.getParameter<edm::InputTag>("BeamSpotProducer");

  ebReducedRecHitCollection_       = ps.getParameter<edm::InputTag>("ebReducedRecHitCollection");
  eeReducedRecHitCollection_       = ps.getParameter<edm::InputTag>("eeReducedRecHitCollection");
  srcTowers_                       = ps.getParameter<edm::InputTag>("caloTowers");
  //heavy ion
  basicClusterBarrel_              = ps.getParameter<edm::InputTag>("basicClusterBarrel");
  basicClusterEndcap_              = ps.getParameter<edm::InputTag>("basicClusterEndcap");
  hbhe_                            = ps.getParameter<edm::InputTag>("hbhe");
  hf_                              = ps.getParameter<edm::InputTag>("hf");
  ho_                              = ps.getParameter<edm::InputTag>("ho");


  
  //event plance
  evtPlaneLabel                    =  ps.getParameter<edm::InputTag>("hiEvtPlane_");


  // for July exercise
  isMC_                        = ps.getUntrackedParameter<bool>("isMC_",false); 
  
  ptMin_                           = ps.getUntrackedParameter<double>("GammaPtMin", 15);
  etaMax_                          = ps.getUntrackedParameter<double>("GammaEtaMax",3);
  ecalBarrelMaxEta_                = ps.getUntrackedParameter<double>("EcalBarrelMaxEta",1.45);
  ecalEndcapMinEta_                = ps.getUntrackedParameter<double>("EcalEndcapMinEta",1.55);

  ptJetMin_                        = ps.getUntrackedParameter<double>("JetPtMin", 20);
  ptTrackMin_                      = ps.getUntrackedParameter<double>("TrackPtMin",1.5);
  etaTrackMax_                     = ps.getUntrackedParameter<double>("TrackEtaMax",1.75);
  
  pdgId_                           = ps.getUntrackedParameter<int>("pdgId", 22);
  otherPdgIds_                     = ps.getUntrackedParameter<vector<int> >("OtherPdgIds", vector<int>(1,11) );
  mcPtMin_                         = ps.getUntrackedParameter<double>("McPtMin", 12);
  mcEtaMax_                        = ps.getUntrackedParameter<double>("McEtaMax",1.7);

  etCutGenMatch_                   = ps.getUntrackedParameter<double>("etCutGenMatch",13);
  etaCutGenMatch_                  = ps.getUntrackedParameter<double>("etaCutGenMatch",3);
  
  doStoreCentrality_                  = ps.getUntrackedParameter<bool>("doStoreCentrality",false);
  doStoreL1Trigger_                = ps.getUntrackedParameter<bool>("doStoreL1Trigger",false);
  doStoreHLT_                      = ps.getUntrackedParameter<bool>("doStoreHLT",false);
  doStoreHF_                       = ps.getUntrackedParameter<bool>("doStoreHF",false);
  doStoreVertex_                   = ps.getUntrackedParameter<bool>("doStoreVertex",false);
  doStoreMET_                      = ps.getUntrackedParameter<bool>("doStoreMET",false);
  doStoreJets_                     = ps.getUntrackedParameter<bool>("doStoreJets",false);
  doStoreCompCone_                 = ps.getUntrackedParameter<bool>("doStoreCompCone",false);
  doStoreConversions_              = ps.getUntrackedParameter<bool>("doStoreConversions",false);
  
  doStoreTracks_                   = ps.getUntrackedParameter<bool>("doStoreTracks",false);

  // electorn collection
  EleTag_                          = ps.getUntrackedParameter<edm::InputTag>("gsfElectronCollection");
  
  
  
  // book ntuples; columns are defined dynamically later
  tplmgr = new HTupleManager(outputFile_.c_str(),"RECREATE");

  tplmgr->SetDir("1D-Spectra");
  _ptHist    = tplmgr->MomentumHistogram("GenPt"  ,"p_{T} MC photon (GeV/c);p_{T} (GeV/c)",100,0,50);
  _ptHatHist = tplmgr->MomentumHistogram("GenPtHat"  ,"p_{T} Hat MC Events (GeV/c);p_{T} (GeV/c)",500,0,500);
  
  _etaHist   = tplmgr->MomentumHistogram("GenEta" ,"#eta MC photon;#eta"  ,100,-3,3);
  _vtxX      = tplmgr->MomentumHistogram("GenVtxX","Generated Vertex X"   ,100, 0.01,0.06);
  _vtxY      = tplmgr->MomentumHistogram("GenVtxY","Generated Vertex Y"   ,100,-0.02,0.02);
  _vtxZ      = tplmgr->MomentumHistogram("GenVtxZ","Generated Vertex X"   ,100,-10,10);

 
  _gammaPtHist  = tplmgr->MomentumHistogram("GammaPt" ,"p_{T} leading photon candidate (GeV/c);p_{T} (GeV/c)",100,0,50);
  _gammaEtaHist = tplmgr->MomentumHistogram("GammaEta","#eta leading photon candidate;#eta"        ,100,-3,3);
    // note 0.1745329 = 2*pi/360 (there are 360 ecal crystals in circle in phi)
  _gammaPhiModHist=tplmgr->MomentumHistogram("GammaPhiMod","#phi_{mod} leading photon candidate (Barrel only);#phi_{mod}" , 42, (-1.-1./20)*0.1745329, (1.+1./20.)*0.1745329);
  _metHist      = tplmgr->MomentumHistogram("MET"     ,"MET (GeV);MET (GeV)"                      ,100,0,100);
  _nVtxHist     = tplmgr->Histogram("NumVtx",20,0,20);
  _primVtxX     = tplmgr->MomentumHistogram("PrimVtxX","Primary Vertex X"   ,100, 0.01,0.06);
  _primVtxY     = tplmgr->MomentumHistogram("PrimVtxY","Primary Vertex Y"   ,100,-0.02,0.02);
  _primVtxZ     = tplmgr->MomentumHistogram("PrimVtxZ","Primary Vertex Z"   ,100,-10,10);

  _nPhotonsHist   = tplmgr->Histogram("NumPhotons",10,0,10);
  _nJetsHist    = tplmgr->Histogram("NumJets",20,-0.5,19.5);
  
  tplmgr->SetDir("NTuples");  
  _ntuple     = tplmgr->Ntuple("Analysis");
  //  _ntupleMC   = tplmgr->Ntuple("Generator");

#if MPA_VERSION < 2
  theLikelihoodCalc_ = new ConversionLikelihoodCalculator();
  edm::FileInPath path_mvaWeightFile("RecoEgamma/EgammaTools/data/TMVAnalysis_Likelihood.weights.txt");
  theLikelihoodCalc_->setWeightsFile(path_mvaWeightFile.fullPath().c_str());
#endif

  // conversion MC truth
 thePhotonMCTruthFinder_ = new PhotonMCTruthFinder();



}

SinglePhotonAnalyzerTree::~SinglePhotonAnalyzerTree() {

#if MPA_VERSION < 2
  delete theLikelihoodCalc_;
#endif

 delete thePhotonMCTruthFinder_;

}

void SinglePhotonAnalyzerTree::analyze(const edm::Event& e, const edm::EventSetup& iSetup) {

	if (doStoreHLT_) 	storeHLT(e);
	if (doStoreHF_)		storeHF(e);
	analyzeMC(e,iSetup);
	if (doStoreVertex_)	storeVertex(e);
	if (doStoreMET_)	storeMET(e);
	if (doStoreJets_)	storeJets(e);
	if (doStoreTracks_)     storeTracks(e);

	if (foundPhoton){
		// Dump analysis ntuple 
		// NOTE: dump ntuple only if at least one photon detected in a given acceptance
		//       number of entries in ntuple does not correspond to the number of analyzed events
		//       number of entries in certain histograms like "NumJets", "NumVtx" corresponds to the number of analyzed events  
		_ntuple->DumpData();   
	}


}

void SinglePhotonAnalyzerTree::beginJob() {
   //   centrality_=0;
   theTree  = fs->make<TTree>("photon","Tree of photons");
   int run;
   int evt;
   int bunchCrossing;
   int luminosityBlock;
   theTree->Branch("run",&run,"run/I");
   theTree->Branch("event",&event,"event/I");
   theTree->Branch("bunchCrossing",&bunchCrossing,"bunchCrossing/I");
   theTree->Branch("luminosityBlock",&luminosityBlock,"luminosityBlock/I");
   
   theTree->Branch("nPho",nPho,"nPho/I");
   theTree->Branch("pt",pt,"pt[nPho]/F");
   theTree->Branch("et",et,"et[nPho]/F");
   theTree->Branch("energy",energy,"energy[nPho]/F");
   theTree->Branch("rawEnergy",rawEnergy,"rawEnergy[nPho]/F");
   theTree->Branch("px",px,"px[nPho]/F");
   theTree->Branch("py",py,"py[nPho]/F");
   theTree->Branch("pz",pz,"pz[nPho]/F");
   theTree->Branch("eta",eta,"eta[nPho]/F");
   theTree->Branch("phi",phi,"phi[nPho]/F");
   theTree->Branch("r9",r9,"r9[nPho]/F");
   theTree->Branch("isEBGap",isEBGap,"isEBGap[nPho]/F");
   theTree->Branch("isEEGap",isEEGap,"isEEGap[nPho]/F");
   theTree->Branch("isEBEEGap",isEBEEGap,"isEBEEGap[nPho]/F");
   theTree->Branch("isTransGap",isTransGap,"isTransGap[nPho]/F");
   theTree->Branch("preshowerEnergy",preshowerEnergy,"preshowerEnergy[nPho]/F");
   theTree->Branch("numOfPreshClusters",numOfPreshClusters,"numOfPreshClusters[nPho]/F");
   theTree->Branch("ESRatio",ESRatio,"ESRatio[nPho]/F");
   theTree->Branch("clustersSize",clustersSize,"clustersSize[nPho]/F");
   theTree->Branch("scSize",scSize,"scSize[nPho]/F");
   theTree->Branch("phiWidth",phiWidth,"phiWidth[nPho]/F");
   theTree->Branch("etaWidth",etaWidth,"etaWidth[nPho]/F");
   theTree->Branch("scEta",scEta,"scEta[nPho]/F");
   theTree->Branch("scPhi",scPhi,"scPhi[nPho]/F");
   theTree->Branch("sigmaEtaEta",sigmaEtaEta,"sigmaEtaEta[nPho]/F");
   theTree->Branch("sigmaIetaIeta",sigmaIetaIeta,"sigmaIetaIeta[nPho]/F");
   theTree->Branch("sigmaIphiIphi",sigmaIphiIphi,"sigmaIphiIphi[nPho]/F");
   theTree->Branch("sieie50",sieie50,"sieie50[nPho]/F");
   theTree->Branch("sieie45",sieie45,"sieie45[nPho]/F");
   theTree->Branch("sieie47",sieie47,"sieie47[nPho]/F");
   theTree->Branch("sieie42",sieie42,"sieie42[nPho]/F");
   theTree->Branch("sieie39",sieie39,"sieie39[nPho]/F");
   theTree->Branch("covPhiPhi",covPhiPhi,"covPhiPhi[nPho]/F");
   theTree->Branch("covEtaPhi",covEtaPhi,"covEtaPhi[nPho]/F");
   theTree->Branch("covEtaEta",covEtaEta,"covEtaEta[nPho]/F");
   theTree->Branch("r1x5",r1x5,"r1x5[nPho]/F");
   theTree->Branch("r2x5",r2x5,"r2x5[nPho]/F");
   theTree->Branch("e1x5",e1x5,"e1x5[nPho]/F");
   theTree->Branch("e2x5",e2x5,"e2x5[nPho]/F");
   theTree->Branch("eMax",eMax,"eMax[nPho]/F");
   theTree->Branch("e2nd",e2nd,"e2nd[nPho]/F");
   theTree->Branch("e2x2",e2x2,"e2x2[nPho]/F");
   theTree->Branch("e3x3",e3x3,"e3x3[nPho]/F");
   theTree->Branch("e3x2",e3x2,"e3x2[nPho]/F");
   theTree->Branch("e4x4",e4x4,"e4x4[nPho]/F");
   theTree->Branch("e5x5",e5x5,"e5x5[nPho]/F");
   theTree->Branch("e2overe8",e2overe8,"e2overe8[nPho]/F");
   theTree->Branch("eRight",eRight,"eRight[nPho]/F");
   theTree->Branch("eLeft",eLeft,"eLeft[nPho]/F");
   theTree->Branch("eTop",eTop,"eTop[nPho]/F");
   theTree->Branch("eBottom",eBottom,"eBottom[nPho]/F");
   theTree->Branch("e2x5Right",e2x5Right,"e2x5Right[nPho]/F");
   theTree->Branch("e2x5Left",e2x5Left,"e2x5Left[nPho]/F");
   theTree->Branch("e2x5Top",e2x5Top,"e2x5Top[nPho]/F");
   theTree->Branch("e2x5Bottom",e2x5Bottom,"e2x5Bottom[nPho]/F");
   theTree->Branch("seedTime",seedTime,"seedTime[nPho]/F");
   theTree->Branch("seedChi2",seedChi2,"seedChi2[nPho]/F");
   theTree->Branch("seedOutOfTimeChi2",seedOutOfTimeChi2,"seedOutOfTimeChi2[nPho]/F");
   theTree->Branch("seedRecoFlag",seedRecoFlag,"seedRecoFlag[nPho]/F");
   theTree->Branch("seedSeverity",seedSeverity,"seedSeverity[nPho]/F");
   theTree->Branch("tRight",tRight,"tRight[nPho]/F");
   theTree->Branch("tLeft",tLeft,"tLeft[nPho]/F");
   theTree->Branch("tTop",tTop,"tTop[nPho]/F");
   theTree->Branch("tBottom",tBottom,"tBottom[nPho]/F");
   theTree->Branch("swissCrx",swissCrx,"swissCrx[nPho]/F");
   theTree->Branch("hadronicOverEm",hadronicOverEm,"hadronicOverEm[nPho]/F");
   theTree->Branch("hadronicDepth1OverEm",hadronicDepth1OverEm,"hadronicDepth1OverEm[nPho]/F");
   theTree->Branch("hadronicDepth2OverEm",hadronicDepth2OverEm,"hadronicDepth2OverEm[nPho]/F");
   theTree->Branch("ecalRecHitSumEtConeDR04",ecalRecHitSumEtConeDR04,"ecalRecHitSumEtConeDR04[nPho]/F");
   theTree->Branch("hcalTowerSumEtConeDR04",hcalTowerSumEtConeDR04,"hcalTowerSumEtConeDR04[nPho]/F");
   theTree->Branch("hcalDepth1TowerSumEtConeDR04",hcalDepth1TowerSumEtConeDR04,"hcalDepth1TowerSumEtConeDR04[nPho]/F");
   theTree->Branch("hcalDepth2TowerSumEtConeDR04",hcalDepth2TowerSumEtConeDR04,"hcalDepth2TowerSumEtConeDR04[nPho]/F");
   theTree->Branch("trkSumPtHollowConeDR04",trkSumPtHollowConeDR04,"trkSumPtHollowConeDR04[nPho]/F");
   theTree->Branch("trkSumPtSolidConeDR04",trkSumPtSolidConeDR04,"trkSumPtSolidConeDR04[nPho]/F");
   
   theTree->Branch("ecalRecHitSumEtConeDR03",ecalRecHitSumEtConeDR03,"ecalRecHitSumEtConeDR03[nPho]/F");
   theTree->Branch("hcalTowerSumEtConeDR03",hcalTowerSumEtConeDR03,"hcalTowerSumEtConeDR03[nPho]/F");
   theTree->Branch("hcalDepth1TowerSumEtConeDR03",hcalDepth1TowerSumEtConeDR03,"hcalDepth1TowerSumEtConeDR03[nPho]/F");
   theTree->Branch("hcalDepth2TowerSumEtConeDR03",hcalDepth2TowerSumEtConeDR03,"hcalDepth2TowerSumEtConeDR03[nPho]/F");
   theTree->Branch("trkSumPtHollowConeDR03",trkSumPtHollowConeDR03,"trkSumPtHollowConeDR03[nPho]/F");
   theTree->Branch("trkSumPtSolidConeDR03",trkSumPtSolidConeDR03,"trkSumPtSolidConeDR03[nPho]/F");
   
   theTree->Branch("isEle",isEle,"isEle[nPho]/F");
   theTree->Branch("detaEle",detaEle,"detaEle[nPho]/F");
   theTree->Branch("dphiEle",dphiEle,"dphiEle[nPho]/F");
   theTree->Branch("eleCharge",eleCharge,"eleCharge[nPho]/F");
   theTree->Branch("eleEoverP",eleEoverP,"eleEoverP[nPho]/F");
   theTree->Branch("c1",c1,"c1[nPho]/F");
   theTree->Branch("c2",c2,"c2[nPho]/F");
   theTree->Branch("c3",c3,"c3[nPho]/F");
   theTree->Branch("c4",c4,"c4[nPho]/F");
   theTree->Branch("c5",c5,"c5[nPho]/F");
   theTree->Branch("r1",r1,"r1[nPho]/F");
   theTree->Branch("r2",r2,"r2[nPho]/F");
   theTree->Branch("r3",r3,"r3[nPho]/F");
   theTree->Branch("r4",r4,"r4[nPho]/F");
   theTree->Branch("r5",r5,"r5[nPho]/F");
   theTree->Branch("t1PtCut",t1PtCut,"t1PtCut[nPho]/F");
   theTree->Branch("t2PtCut",t2PtCut,"t2PtCut[nPho]/F");
   theTree->Branch("t3PtCut",t3PtCut,"t3PtCut[nPho]/F");
   theTree->Branch("t4PtCut",t4PtCut,"t4PtCut[nPho]/F");
   theTree->Branch("t5PtCut",t5PtCut,"t5PtCut[nPho]/F");
   theTree->Branch("cc1",cc1,"cc1[nPho]/F");
   theTree->Branch("cc2",cc2,"cc2[nPho]/F");
   theTree->Branch("cc3",cc3,"cc3[nPho]/F");
   theTree->Branch("cc4",cc4,"cc4[nPho]/F");
   theTree->Branch("cc4j",cc4j,"cc4j[nPho]/F");
   theTree->Branch("cc5",cc5,"cc5[nPho]/F");
   theTree->Branch("cr1",cr1,"cr1[nPho]/F");
   theTree->Branch("cr2",cr2,"cr2[nPho]/F");
   theTree->Branch("cr3",cr3,"cr3[nPho]/F");
   theTree->Branch("cr4",cr4,"cr4[nPho]/F");
   theTree->Branch("cr5",cr5,"cr5[nPho]/F");
   theTree->Branch("cr4j",cr4j,"cr4j[nPho]/F");
   theTree->Branch("ct1",ct1,"ct1[nPho]/F");
   theTree->Branch("ct2",ct2,"ct2[nPho]/F");
   theTree->Branch("ct3",ct3,"ct3[nPho]/F");
   theTree->Branch("ct4",ct4,"ct4[nPho]/F");
   theTree->Branch("ct5",ct5,"ct5[nPho]/F");
   theTree->Branch("ct1PtCut20",ct1PtCut20,"ct1PtCut20[nPho]/F");
   theTree->Branch("ct2PtCut20",ct2PtCut20,"ct2PtCut20[nPho]/F");
   theTree->Branch("ct3PtCut20",ct3PtCut20,"ct3PtCut20[nPho]/F");
   theTree->Branch("ct4PtCut20",ct4PtCut20,"ct4PtCut20[nPho]/F");
   theTree->Branch("ct5PtCut20",ct5PtCut20,"ct5PtCut20[nPho]/F");
   theTree->Branch("ct4j20",ct4j20,"ct4j20[nPho]/F");
   theTree->Branch("ct4j10",ct4j10,"ct4j10[nPho]/F");
   theTree->Branch("ct4j15",ct4j15,"ct4j15[nPho]/F");
   theTree->Branch("ct4j",ct4j,"ct4j[nPho]/F");
   theTree->Branch("dr11",dr11,"dr11[nPho]/F");
   theTree->Branch("dr21",dr21,"dr21[nPho]/F");
   theTree->Branch("dr31",dr31,"dr31[nPho]/F");
   theTree->Branch("dr41",dr41,"dr41[nPho]/F");
   theTree->Branch("dr12",dr12,"dr12[nPho]/F");
   theTree->Branch("dr22",dr22,"dr22[nPho]/F");
   theTree->Branch("dr32",dr32,"dr32[nPho]/F");
   theTree->Branch("dr42",dr42,"dr42[nPho]/F");
   theTree->Branch("dr13",dr13,"dr13[nPho]/F");
   theTree->Branch("dr23",dr23,"dr23[nPho]/F");
   theTree->Branch("dr33",dr33,"dr33[nPho]/F");
   theTree->Branch("dr43",dr43,"dr43[nPho]/F");
   theTree->Branch("dr14",dr14,"dr14[nPho]/F");
   theTree->Branch("dr24",dr24,"dr24[nPho]/F");
   theTree->Branch("dr34",dr34,"dr34[nPho]/F");
   theTree->Branch("dr44",dr44,"dr44[nPho]/F");
   theTree->Branch("t11",t11,"t11[nPho]/F");
   theTree->Branch("t21",t21,"t21[nPho]/F");
   theTree->Branch("t31",t31,"t31[nPho]/F");
   theTree->Branch("t41",t41,"t41[nPho]/F");
   theTree->Branch("t12",t12,"t12[nPho]/F");
   theTree->Branch("t22",t22,"t22[nPho]/F");
   theTree->Branch("t32",t32,"t32[nPho]/F");
   theTree->Branch("t42",t42,"t42[nPho]/F");
   theTree->Branch("t13",t13,"t13[nPho]/F");
   theTree->Branch("t23",t23,"t23[nPho]/F");
   theTree->Branch("t33",t33,"t33[nPho]/F");
   theTree->Branch("t43",t43,"t43[nPho]/F");
   theTree->Branch("t14",t14,"t14[nPho]/F");
   theTree->Branch("t24",t24,"t24[nPho]/F");
   theTree->Branch("t34",t34,"t34[nPho]/F");
   theTree->Branch("t44",t44,"t44[nPho]/F");


   theTree->Branch("isGenMatched",&isGenMatched,"isGenMatched[nPho]/I");
   theTree->Branch("genMatchedCollId",genMatchedCollId,"genMatchedCollId[nPho]/F");
   theTree->Branch("genMatchedPt",genMatchedPt,"genMatchedPt[nPho]/F");
   theTree->Branch("genMatchedEta",genMatchedEta,"genMatchedEta[nPho]/F");
   theTree->Branch("genMatchedPhi",genMatchedPhi,"genMatchedPhi[nPho]/F");
   theTree->Branch("genMomId",genMomId,"genMomId[nPho]/F");
   theTree->Branch("genGrandMomId",genGrandMomId,"genGrandMomId[nPho]/F");
   theTree->Branch("genNSiblings",genNSiblings,"genNSiblings[nPho]/F");
   theTree->Branch("genCalIsoDR03",genCalIsoDR03,"genCalIsoDR03[nPho]/F");
   theTree->Branch("genCalIsoDR04",genCalIsoDR04,"genCalIsoDR04[nPho]/F");
   theTree->Branch("genTrkIsoDR03",genTrkIsoDR03,"genTrkIsoDR03[nPho]/F");
   theTree->Branch("genTrkIsoDR04",genTrkIsoDR04,"genTrkIsoDR04[nPho]/F");


}

void SinglePhotonAnalyzerTree::endJob() {
   //  tplmgr->Store();
   // tplmgr->SetDir("Info");
   //  TObjString codeVersion = "$Name:  $";
   //  codeVersion.Write("CodeVersion");
   //  delete tplmgr;
   
}

void SinglePhotonAnalyzerTree::storeGeneral(const edm::Event& e, const edm::EventSetup& iSetup){
   using namespace edm;
  
}

void SinglePhotonAnalyzerTree::storeL1Trigger(const edm::Event& e){
  
}

void SinglePhotonAnalyzerTree::storeHLT(const edm::Event& e){
}
				
void SinglePhotonAnalyzerTree::storeHF(const edm::Event& e){
}	

bool SinglePhotonAnalyzerTree::analyzeMC(const edm::Event& e, const edm::EventSetup& iSetup){

  /////////////////////////////////////////////////////////
  // Generator Section: Analyzing Monte Carlo Truth Info //                                  
  /////////////////////////////////////////////////////////
  
  Handle<HepMCProduct> evtMC;
  e.getByLabel(hepMCProducer_,evtMC);
  if (evtMC.isValid())  isMCData_=kTRUE;
  edm::Handle<reco::GenParticleCollection> genParticles;

  if (isMCData_) {
    // get simulated vertex and store in ntuple
     Float_t simVertexX(0), simVertexY(0), simVertexZ(0);
     if(evtMC->GetEvent()->signal_process_vertex() != NULL) {
	simVertexX = evtMC->GetEvent()->signal_process_vertex()->position().x();
	simVertexY = evtMC->GetEvent()->signal_process_vertex()->position().y();
	simVertexZ = evtMC->GetEvent()->signal_process_vertex()->position().z();
	_vtxX->Fill(simVertexX);
	_vtxY->Fill(simVertexY);
	_vtxZ->Fill(simVertexZ);
     }
     
     if( storePhysVectors_ ) {
       _ntuple->Column("simVertex", TVector3(simVertexX,simVertexY,simVertexZ));
     } else {
       _ntuple->Column("simVertexX", simVertexX);
       _ntuple->Column("simVertexY", simVertexY);
       _ntuple->Column("simVertexZ", simVertexZ);     
     }
     
     // get pthat value and store in ntuple                                                                                 
     edm::Handle<GenEventInfoProduct>    genEventScale;
     e.getByLabel(genEventScale_, genEventScale);   // hi style                                                                 
     Float_t  pthat(0);
     pthat = genEventScale->qScale();
     _ptHatHist->Fill(pthat);
     
     //    if( genEventScale->hasBinningValues() ) {                                                                       
     //   pthat = genEventScale->binningValues()[0];                                                                    
     //  } 
     _ntuple->Column("ptHat", pthat);
     
     //  get generated particles and store generator ntuple 
     try { e.getByLabel( genParticleProducer_,      genParticles );} catch (...) {;}
     const int nMaxGenPar = 50;
     HTValVector<Float_t> gpEt(nMaxGenPar), gpEta(nMaxGenPar), gpPhi(nMaxGenPar), gpIsoDR04(nMaxGenPar), gpIsoDR03(nMaxGenPar);
     HTValVector<Int_t> gpId(nMaxGenPar), gpStatus(nMaxGenPar), gpMomId(nMaxGenPar), gpCollId(nMaxGenPar);
     
     int nGenParCounter=0;
     for (reco::GenParticleCollection::const_iterator it_gen = 
	    genParticles->begin(); it_gen!= genParticles->end(); it_gen++){
       const reco::GenParticle &p = (*it_gen);    
       if ( p.pt() < mcPtMin_ ||  fabs(p.p4().eta()) > mcEtaMax_ ) continue; 
       //_ptHist->Fill(p.pt()); 
       //_etaHist->Fill(p.eta()); 
       gpEt(nGenParCounter) = p.et();
       gpEta(nGenParCounter) = p.eta();
       gpPhi(nGenParCounter) = p.phi();
       gpIsoDR04(nGenParCounter) =  getGenCalIso(genParticles, it_gen, 0.4);
       gpIsoDR03(nGenParCounter) =  getGenCalIso(genParticles, it_gen, 0.3);
       //      genTrkIsoDR03 = getGenTrkIso(genParticles, it_gen, 0.3);      
      //    genTrkIsoDR04 = getGenTrkIso(genParticles, it_gen, 0.4);
       gpStatus(nGenParCounter) = p.status();
       gpCollId(nGenParCounter) = p.collisionId();
       gpId(nGenParCounter) = p.pdgId();
       gpMomId(nGenParCounter) = 0;
       if( p.numberOfMothers() > 0 )
	 gpMomId(nGenParCounter) = p.mother()->pdgId();
       
       nGenParCounter++;
       if (nGenParCounter> nMaxGenPar-1) break;       
     }
    
     _ntuple->Column("nGp", (Int_t) nGenParCounter);
     _ntuple->Column("gpEt",         gpEt,           "nGp");
     _ntuple->Column("gpEta",        gpEta,          "nGp");
     _ntuple->Column("gpPhi",        gpPhi,          "nGp");
     _ntuple->Column("gpIsoDR04",    gpIsoDR04    ,  "nGp");
     _ntuple->Column("gpIsoDR03",    gpIsoDR03    ,  "nGp");
     _ntuple->Column("gpStatus",     gpStatus,       "nGp");
     _ntuple->Column("gpCollId",     gpCollId,          "nGp");
     _ntuple->Column("gpId",         gpId,          "nGp");
     _ntuple->Column("gpMomId",      gpMomId,          "nGp");
  }
  return (isMCData_ && fillMCNTuple_);
}	


void SinglePhotonAnalyzerTree::storeEvtPlane(const edm::Event& e){
}

void SinglePhotonAnalyzerTree::storeVertex(const edm::Event& e){
}




bool SinglePhotonAnalyzerTree::storeMET(const edm::Event& e){
   return false;
}


bool SinglePhotonAnalyzerTree::storeTracks(const edm::Event& e){
}




int SinglePhotonAnalyzerTree::storeJets(const edm::Event& e){

}

bool SinglePhotonAnalyzerTree::storeMCMatch( const edm::Event& e,pat::Photon *photon, const char* prefx){

  TString prx(prefx);
  Handle<HepMCProduct> evtMC;
  e.getByLabel("generator",evtMC);
  if (evtMC.isValid())  isMCData_=kTRUE;	
  
  if (isMCData_) {
    float delta(0.15);
    Int_t momId(0), grandMomId(0), nSiblings(0), genMatchedCollId(-100);
    Bool_t isGenMatched(kFALSE);
    Float_t genMatchedPt(-1), genMatchedEta(-1000), genMatchedPhi(0);
    Float_t currentMaxPt(-1);
    Float_t genCalIsoDR04(99999.), genTrkIsoDR04(99999.), genCalIsoDR03(99999.), genTrkIsoDR03(99999.);
    TLorentzVector genMatchedP4(0,0,0,0); 
    const reco::Candidate *cndMc(0);
    reco::GenParticleCollection::const_iterator matchedPart; 

    // get hold of generated particles from MC thuth 
    edm::Handle<reco::GenParticleCollection> genParticles;
    try { e.getByLabel( genParticleProducer_,      genParticles );} catch (...) {;}
    
    for (reco::GenParticleCollection::const_iterator it_gen = 
	    genParticles->begin(); it_gen!= genParticles->end(); it_gen++){
       
       const reco::Candidate &p = (*it_gen);  
       if ( p.status() != 1 || fabs(p.pdgId()) != pdgId_ ) continue;
       if ( p.et() < etCutGenMatch_ ) continue;
       if ( fabs(p.eta()) > etaCutGenMatch_ ) continue;
       
       if(ROOT::Math::VectorUtil::DeltaR(p.p4(),photon->p4())<delta && p.pt() > currentMaxPt ) {
	  if( p.numberOfMothers() > 0 ) {
	     momId = p.mother()->pdgId();
	  if( p.mother()->numberOfMothers() > 0 ) {
	     grandMomId = p.mother()->mother()->pdgId();
	  }
	  nSiblings = p.mother()->numberOfDaughters();
	}
	isGenMatched  = kTRUE; cndMc = &p;
	currentMaxPt  = p.pt();
	matchedPart   = it_gen;
	genMatchedCollId = it_gen->collisionId();
       }
    } // end of loop over gen particles

    // if no matching photon was found try with other particles
    if( !isGenMatched ) { 
       
       currentMaxPt = -1;
       for (reco::GenParticleCollection::const_iterator it_gen = 
	       genParticles->begin(); it_gen!= genParticles->end(); it_gen++){      
	  const reco::Candidate &p = (*it_gen);    	
	  if (p.status() != 1 || find(otherPdgIds_.begin(),otherPdgIds_.end(),fabs(p.pdgId())) == otherPdgIds_.end() ) continue;
	  if ( p.et() < etCutGenMatch_ ) continue;
	  if ( fabs(p.eta()) > etaCutGenMatch_ ) continue;
	  
	  if(ROOT::Math::VectorUtil::DeltaR(p.p4(),photon->p4())<delta && p.pt() > currentMaxPt ) {
	  momId = p.pdgId();
	  if( p.numberOfMothers() > 0 ) {
	    grandMomId = p.mother()->pdgId();
	    nSiblings = p.mother()->numberOfDaughters();
	  }
	  cndMc = &p; // do not set the isGenMatched in this case
	  currentMaxPt = p.pt();
	  matchedPart = it_gen;
	}
      } // end of loop over gen particles

    } // if not matched to gen photon
    
    if(cndMc) {
      genMatchedP4.SetXYZT(cndMc->px(),cndMc->py(),cndMc->pz(),cndMc->energy());
      genMatchedPt   = cndMc->pt();
      genMatchedEta  = cndMc->eta();
      genMatchedPhi  = cndMc->phi();
      // calculate isolation at the generator level
      genCalIsoDR03  = getGenCalIso(genParticles, matchedPart, 0.3);
      genTrkIsoDR03  = getGenTrkIso(genParticles, matchedPart, 0.3);      
      genCalIsoDR04  = getGenCalIso(genParticles, matchedPart, 0.4);
      genTrkIsoDR04  = getGenTrkIso(genParticles, matchedPart, 0.4);
    }	       	      	
    
    _ntuple->Column(prx+"isGenMatched", isGenMatched);
    if( storePhysVectors_ ) {
      _ntuple->Column(prx+"genMatchedP4", genMatchedP4);
    } else { 
      _ntuple->Column(prx+"genMatchedPt", genMatchedPt);
      _ntuple->Column(prx+"genMatchedEta",genMatchedEta);
      _ntuple->Column(prx+"genMatchedPhi",genMatchedPhi);
    }
    _ntuple->Column(prx+"genCollId",     genMatchedCollId);
    _ntuple->Column(prx+"motherID",     momId);
    _ntuple->Column(prx+"grandMotherID",     grandMomId);
    _ntuple->Column(prx+"nSiblings",     nSiblings);
    // calculate isolation at the generator level
    _ntuple->Column(prx+"genCalIsoDR03", genCalIsoDR03);
    _ntuple->Column(prx+"genTrkIsoDR03", genTrkIsoDR03);
    
    _ntuple->Column(prx+"genCalIsoDR04", genCalIsoDR04);
    _ntuple->Column(prx+"genTrkIsoDR04", genTrkIsoDR04);
    
    
  }
  
  return (isMCData_);
}



Int_t SinglePhotonAnalyzerTree::getNumOfPreshClusters(Photon *photon, const edm::Event& e) {

// ES clusters in X plane
  edm::Handle<reco::PreshowerClusterCollection> esClustersX;
  e.getByLabel(InputTag("multi5x5SuperClustersWithPreshower:preshowerXClusters"), esClustersX);
  const reco::PreshowerClusterCollection *ESclustersX = esClustersX.product();

// ES clusters in Y plane
  edm::Handle<reco::PreshowerClusterCollection> esClustersY;
  e.getByLabel(InputTag("multi5x5SuperClustersWithPreshower:preshowerYClusters"),esClustersY);
  const reco::PreshowerClusterCollection *ESclustersY = esClustersY.product();


  Int_t numOfPreshClusters(-1);
  
// Is the photon in region of Preshower?
  if (fabs(photon->eta())>1.62) {
    numOfPreshClusters=0;

  // Loop over all ECAL Basic clusters in the supercluster
    for (reco::CaloCluster_iterator ecalBasicCluster = photon->superCluster()->clustersBegin();
	 ecalBasicCluster!=photon->superCluster()->clustersEnd(); ecalBasicCluster++) {
      const reco::CaloClusterPtr ecalBasicClusterPtr = *(ecalBasicCluster);

      for (reco::PreshowerClusterCollection::const_iterator iESClus = ESclustersX->begin(); iESClus != ESclustersX->end(); ++iESClus) {
	const reco::CaloClusterPtr preshBasicCluster = iESClus->basicCluster();
//	const reco::PreshowerCluster *esCluster = &*iESClus;
	if (preshBasicCluster == ecalBasicClusterPtr) {
	  numOfPreshClusters++;
//	  cout << esCluster->energy() <<"\t" << esCluster->x() << "\t" << esCluster->y() << endl;
	}
      }  

      for (reco::PreshowerClusterCollection::const_iterator iESClus = ESclustersY->begin(); iESClus != ESclustersY->end(); ++iESClus) {
	const reco::CaloClusterPtr preshBasicCluster = iESClus->basicCluster();
//	const reco::PreshowerCluster *esCluster = &*iESClus;
	if (preshBasicCluster == ecalBasicClusterPtr) {
	  numOfPreshClusters++;
//	  cout << esCluster->energy() <<"\t" << esCluster->x() << "\t" << esCluster->y() << endl;
	}
      }
    } 
  } 

  return numOfPreshClusters;
  
}

Float_t SinglePhotonAnalyzerTree::getESRatio(Photon *photon, const edm::Event& e, const edm::EventSetup& iSetup){

  //get Geometry
  ESHandle<CaloGeometry> caloGeometry;
  iSetup.get<CaloGeometryRecord>().get(caloGeometry);
  const CaloSubdetectorGeometry *geometry = caloGeometry->getSubdetectorGeometry(DetId::Ecal, EcalPreshower);
  const CaloSubdetectorGeometry *& geometry_p = geometry;

  // Get ES rechits
  edm::Handle<EcalRecHitCollection> PreshowerRecHits;
  e.getByLabel(InputTag("ecalPreshowerRecHit","EcalRecHitsES"), PreshowerRecHits);
  if( PreshowerRecHits.isValid() ) EcalRecHitCollection preshowerHits(*PreshowerRecHits);

  Float_t esratio=-1.;

  if (fabs(photon->eta())>1.62) {

    const reco::CaloClusterPtr seed = (*photon).superCluster()->seed();    
    reco::CaloCluster cluster = (*seed);
    const GlobalPoint phopoint(cluster.x(), cluster.y(), cluster.z());
  
    DetId photmp1 = (dynamic_cast<const EcalPreshowerGeometry*>(geometry_p))->getClosestCellInPlane(phopoint, 1);
    DetId photmp2 = (dynamic_cast<const EcalPreshowerGeometry*>(geometry_p))->getClosestCellInPlane(phopoint, 2);
    ESDetId esfid = (photmp1 == DetId(0)) ? ESDetId(0) : ESDetId(photmp1);
    ESDetId esrid = (photmp2 == DetId(0)) ? ESDetId(0) : ESDetId(photmp2);

    int gs_esfid = -99;
    int gs_esrid = -99;
    gs_esfid = esfid.six()*32+esfid.strip();
    gs_esrid = esrid.siy()*32+esrid.strip();

    float esfe3 = 0.; 
    float esfe21 = 0.; 
    float esre3 = 0.; 
    float esre21 = 0.;

    const ESRecHitCollection *ESRH = PreshowerRecHits.product();
    EcalRecHitCollection::const_iterator esrh_it;
    for ( esrh_it = ESRH->begin(); esrh_it != ESRH->end(); esrh_it++) {
      ESDetId esdetid = ESDetId(esrh_it->id());
      if ( esdetid.plane()==1 ) {
	if ( esdetid.zside() == esfid.zside() &&
	     esdetid.siy() == esfid.siy() ) {
	  int gs_esid = esdetid.six()*32+esdetid.strip();
	  int ss = gs_esid-gs_esfid;
	  if ( TMath::Abs(ss)<=10) {
	    esfe21 += esrh_it->energy();
	  } 
	  if ( TMath::Abs(ss)<=1) {
	    esfe3 += esrh_it->energy();
	  } 
	}
      }
      if (esdetid.plane()==2 ){
	if ( esdetid.zside() == esrid.zside() &&
	     esdetid.six() == esrid.six() ) {
	  int gs_esid = esdetid.siy()*32+esdetid.strip();
	  int ss = gs_esid-gs_esrid;
	  if ( TMath::Abs(ss)<=10) {
	    esre21 += esrh_it->energy();
	  } 
	  if ( TMath::Abs(ss)<=1) {
	    esre3 += esrh_it->energy();
	  } 
	}
      }
    }
  
    if( (esfe21+esre21) == 0.) {
      esratio = 1.;
    }else{
      esratio = (esfe3+esre3) / (esfe21+esre21);
    }


    if ( esratio>1.) {
      cout << "es numbers " << esfe3 << " " << esfe21 << " " << esre3 << " " << esre21 << endl;
    }
    
  }

  return esratio;
  
}


// get amount of generator isolation
// default cut value of etMin is 0.0
// return number of particles and sumEt surrounding candidate

Float_t SinglePhotonAnalyzerTree::getGenCalIso(edm::Handle<reco::GenParticleCollection> handle,
					   reco::GenParticleCollection::const_iterator thisPho,                                            const Float_t dRMax)
{
  const Float_t etMin = 0.0;
  Float_t genCalIsoSum = 0.0;
  if(!isMCData_)return genCalIsoSum;
  if(!handle.isValid())return genCalIsoSum;

  for (reco::GenParticleCollection::const_iterator it_gen = 
	 handle->begin(); it_gen!=handle->end(); it_gen++){

    if(it_gen == thisPho)continue;      // can't be the original photon
    if(it_gen->status()!=1)continue;    // need to be a stable particle
    if (thisPho->collisionId() != it_gen->collisionId())  // has to come from the same collision
       continue; 
   
    Int_t pdgCode = abs(it_gen->pdgId());
    if(pdgCode>11 && pdgCode < 20)continue;     // we should not count neutrinos, muons

    Float_t et = it_gen->et();
    if(et < etMin) continue; // pass a minimum et threshold, default 0

    Float_t dR = reco::deltaR(thisPho->momentum(), 
			      it_gen->momentum());
    if(dR > dRMax) continue; // within deltaR cone
    genCalIsoSum += et;
    
  }// end of loop over gen particles

  return genCalIsoSum;
}


//=============================================================================
// default cut value of ptMin is 0.0

Float_t SinglePhotonAnalyzerTree::getGenTrkIso(edm::Handle<reco::GenParticleCollection> handle,
					   reco::GenParticleCollection::const_iterator thisPho,                                            const Float_t dRMax)
{
  const Float_t ptMin = 0.0;
  Float_t genTrkIsoSum = 0.0;
  if(!isMCData_)return genTrkIsoSum;
  if(!handle.isValid())return genTrkIsoSum;

  for (reco::GenParticleCollection::const_iterator it_gen = 
	 handle->begin(); it_gen!=handle->end(); it_gen++){

    if(it_gen == thisPho)continue;      // can't be the original photon
    if(it_gen->status()!=1)continue;    // need to be a stable particle
    if (thisPho->collisionId() != it_gen->collisionId())  // has to come from the same collision
       continue; 
   
   if(it_gen->charge()==0)continue;    // we should not count neutral particles
   
    Float_t pt = it_gen->pt();
    if(pt < ptMin) continue; // pass a minimum pt threshold, default 0

    Float_t dR = reco::deltaR(thisPho->momentum(), 
			      it_gen->momentum());
    if(dR > dRMax) continue; // within deltaR cone
    genTrkIsoSum += pt;
    
  }// end of loop over gen particles

  return genTrkIsoSum;
}


//=============================================================================
// get conversion truth
void SinglePhotonAnalyzerTree::storeConvMCTruth(const edm::Event& e, 				
					    reco::GenParticleCollection::const_iterator it_gen, 
					    HTuple *tpl, const char* prefx)
{
  if(!isMCData_)return;
  TString prx(prefx);

  Int_t isConv = 0;
  Float_t convVx = -9999.;
  Float_t convVy = -9999.;
  Float_t convVz = -9999.;
  Float_t TrkPt1 = -9999;
  Float_t TrkPt2 = -9999;

  std::vector<SimTrack>        theSimTracks;
  std::vector<SimVertex>       theSimVertices;
  std::vector<PhotonMCTruth>   myPhotonMCTruth;
  std::vector<ElectronMCTruth> myElectronMCTruth;

  edm::Handle<SimTrackContainer> SimTk;
  edm::Handle<SimVertexContainer> SimVtx;
  e.getByLabel("g4SimHits",SimTk);
  e.getByLabel("g4SimHits",SimVtx);
  if(SimTk.isValid())
    theSimTracks.insert(theSimTracks.end(),SimTk->begin(),SimTk->end());
  if(SimVtx.isValid())
    theSimVertices.insert(theSimVertices.end(),SimVtx->begin(),SimVtx->end());
  myPhotonMCTruth = 
    thePhotonMCTruthFinder_->find (theSimTracks,  theSimVertices);

  for ( std::vector<PhotonMCTruth>::const_iterator 
	  iPho=myPhotonMCTruth.begin(); iPho !=myPhotonMCTruth.end(); 
	++iPho ){
    
    if(!iPho->isAConversion())continue;

    if(abs(it_gen->pdgId())!= 22 || it_gen->status()!= 1)continue;
    
    float dpx = fabs(iPho->fourMomentum().x() - it_gen->p4().x());
    float dpy = fabs(iPho->fourMomentum().y() - it_gen->p4().y());
    float dpz = fabs(iPho->fourMomentum().z() - it_gen->p4().z());
    float dvx = fabs(iPho->primaryVertex().x() - it_gen->vx());
    float dvy = fabs(iPho->primaryVertex().y() - it_gen->vy());
    float dvz = fabs(iPho->primaryVertex().z() - it_gen->vz());
    myElectronMCTruth.clear();
    
    if(dpx < 0.001 && dpy < 0.001 && dpz < 0.001 && 
       (iPho->primaryVertex().x() < -9999 || 
	iPho->primaryVertex().y() < -9999 || 
	iPho->primaryVertex().z() < -9999 || 
	(dvx < 0.001 && dvy < 0.001 && dvz < 0.001)))
      {

	isConv = 1;
	convVx = iPho->vertex().x();
	convVy = iPho->vertex().y();
	convVz = iPho->vertex().z();
	myElectronMCTruth = iPho->electrons();
	int ie=0;
	for ( std::vector<ElectronMCTruth>::const_iterator 
		iEle=myElectronMCTruth.begin(); 
	      iEle !=myElectronMCTruth.end(); ++iEle ){

	    Float_t tempPt = sqrt(pow(iEle->fourMomentum().x(),2)+
		     pow(iEle->fourMomentum().y(),2));
	    if(ie==0)TrkPt1 = tempPt;
	    else if(ie==1)TrkPt2 = tempPt;
	    ie++;
	  }
	break;
      } // if this gen photon has converted


  } // end of loop over photonMCTruth

  
  tpl->Column(prx + "genIsConv"  , isConv ); // conversion or not
  tpl->Column(prx + "genConvVtxX", convVx);  // conversion vertex x
  tpl->Column(prx + "genConvVtxY", convVy);  // conversion vertex y
  tpl->Column(prx + "genConvVtxZ", convVz);  // conversion vertex z
  tpl->Column(prx + "genConvElePt1", TrkPt1); // conversion electron pt
  tpl->Column(prx + "genConvElePt2", TrkPt2); // conversion electron pt


}





DEFINE_FWK_MODULE(SinglePhotonAnalyzerTree);
