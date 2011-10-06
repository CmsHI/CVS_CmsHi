/** \class MultiPhotonAnalyzerTree MultiPhotonAnalyzerTree.cc CmsHi/PhotonAnalysis/plugin/MultiPhotonAnalyzerTree.cc
 *
 * Description: 
 * Analysis code of the QCD Photons group;
 * Data Analyzer for the single photon (inclusive isolated photons and photon plus jets) cross section measurement; 
 * Store in ntuple run conditions and missing ET information for each event;
 * Makes ntuple of the photon and jet arrays in each event;
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
 * \author Yongsun Kim,         MIT, US
 * \author Pasquale Musella,    LIP, PT
 * \author Shin-Shan Eiko Yu,   National Central University, TW
 * \author Abe DeBenedetti,     University of Minnesota, US  
 * \author Rong-Shyang Lu,      National Taiwan University, TW
 * \version $Id: MultiPhotonAnalyzerTree.cc,v 1.3 2011/10/05 16:08:37 kimy Exp $
 *
 */


// This MultiphotonAnalyzer was modified to fit with Heavy Ion collsion by Yongsun Kim ( MIT)


#include <memory>
#include <iostream>
#include <algorithm>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Common/interface/TriggerNames.h"

//Trigger DataFormats
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
#include "L1Trigger/GlobalTrigger/interface/L1GlobalTrigger.h"

#include "DataFormats/Common/interface/TriggerResults.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/PatCandidates/interface/Photon.h"
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

#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"

// Histograms, ntuples
#include "UserCode/HafHistogram/interface/HTupleManager.h"
#include "UserCode/HafHistogram/interface/HHistogram.h"
#include "UserCode/HafHistogram/interface/HTuple.h"

//ROOT includes
#include <Math/VectorUtil.h>
#include <TLorentzVector.h>

//Include the Single Photon Analyzer
#include "CmsHi/PhotonAnalysis/plugins/MultiPhotonAnalyzerTree.h"

//Include Heavy Ion isolation variable calculator
#include "RecoHI/HiEgammaAlgos/interface/CxCalculator.h"
#include "RecoHI/HiEgammaAlgos/interface/RxCalculator.h"
#include "RecoHI/HiEgammaAlgos/interface/TxCalculator.h"
#include "RecoHI/HiEgammaAlgos/interface/TxyCalculator.h"
#include "RecoHI/HiEgammaAlgos/interface/dRxyCalculator.h"

// Electron
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"



using namespace pat;
using namespace edm;
using namespace std;
using namespace ROOT::Math::VectorUtil;


MultiPhotonAnalyzerTree::MultiPhotonAnalyzerTree(const edm::ParameterSet& ps):
   SinglePhotonAnalyzerTree(ps)
   //  kMaxPhotons(ps.getUntrackedParameter<int>("MaxPhotons", 50))
   // already defined as 50
{
}

MultiPhotonAnalyzerTree::~MultiPhotonAnalyzerTree(){
}



void MultiPhotonAnalyzerTree::analyze(const edm::Event& e, const edm::EventSetup& iSetup) {
   
   //  if (doStoreGeneral_) 	storeGeneral(e, iSetup);
   //  if (doStoreL1Trigger_) 	storeL1Trigger(e);
   //   if (doStoreHLT_) 	storeHLT(e);
   //  if (doStoreHF_)		storeHF(e);
   //   analyzeMC(e,iSetup);
   //  if (doStoreVertex_)	storeVertex(e);
   //  if (doStoreMET_)	storeMET(e);
   //  if (doStoreJets_)	storeJets(e);
   //  if (doStoreTracks_)     storeTracks(e);

   //   storeEvtPlane(e);
   
   int foundPhotons = selectStorePhotons(e,iSetup,"");
   cout <<"Found photons? "<<foundPhotons<<endl;
   

   foundPhotons = true;
   if (foundPhotons){
      _ntuple->DumpData();   
   }
   
}



int MultiPhotonAnalyzerTree::selectStorePhotons(const edm::Event& e,const edm::EventSetup& iSetup, const char* prefx){
   
   /////////////////////////////////////////////////////////////////////////////
   // Photon Section: store kMaxPhotons in the events as an array in the tree //
   /////////////////////////////////////////////////////////////////////////////
   // Get photon details  
   Handle<pat::PhotonCollection> photons;
   e.getByLabel(photonProducer_, photons);   
   
   pat::PhotonCollection myphotons;
   for (PhotonCollection::const_iterator phoItr = photons->begin(); phoItr != photons->end(); ++phoItr) {  
      myphotons.push_back(*phoItr);
   }
   
   reco::PhotonCollection myCompPhotons;
   if (doStoreCompCone_) {
      Handle<reco::PhotonCollection> compPhotons;
      e.getByLabel(compPhotonProducer_, compPhotons);
      for (reco::PhotonCollection::const_iterator phoItr = compPhotons->begin(); phoItr != compPhotons->end(); ++phoItr){
	 myCompPhotons.push_back(*phoItr);
      }
   }
   
   GreaterByPt<Photon> pTComparator_;
   
   // Sort photons according to pt
   std::sort(myphotons.begin(), myphotons.end(), pTComparator_);
   std::sort(myCompPhotons.begin(), myCompPhotons.end(), pTComparator_);
   
  TString pfx(prefx);
  
  // Tools to get cluster shapes

  edm::Handle<EcalRecHitCollection> EBReducedRecHits;
  e.getByLabel(ebReducedRecHitCollection_, EBReducedRecHits);
  edm::Handle<EcalRecHitCollection> EEReducedRecHits;
  e.getByLabel(eeReducedRecHitCollection_, EEReducedRecHits); 
  // get the channel status from the DB
  edm::ESHandle<EcalChannelStatus> chStatus;
  iSetup.get<EcalChannelStatusRcd>().get(chStatus);
  
  EcalClusterLazyTools lazyTool(e, iSetup, ebReducedRecHitCollection_, eeReducedRecHitCollection_ );   

  // Tools to get electron informations.
  edm::Handle<reco::GsfElectronCollection> EleHandle ;
  e.getByLabel (EleTag_.label(),EleHandle) ;
  reco::GsfElectronCollection myEle;
  
  bool isEleRecoed = false;
  if (EleHandle.isValid()) {
     cout << " electron was reconstructed! " << endl;
    isEleRecoed = true;
  }
  
  if ( isEleRecoed) {
     for (reco::GsfElectronCollection::const_iterator eleItr = EleHandle->begin(); eleItr != EleHandle->end(); ++eleItr) {
	myEle.push_back(*eleItr);
     }
  }
  
  // Heavy Ion variable calculator
  CxCalculator CxC(e,iSetup, basicClusterBarrel_, basicClusterEndcap_);
  RxCalculator RxC(e,iSetup, hbhe_, hf_, ho_);
  TxCalculator TxC(e,iSetup, trackProducer_);
  TxyCalculator Txy(e,iSetup,trackProducer_);
  dRxyCalculator dRxy(e,iSetup,trackProducer_);
  
  
  
  /*
    HTValVector<TLorentzVector> p4(kMaxPhotons);
    HTValVector<Float_t> p(kMaxPhotons),  et(kMaxPhotons),  energy(kMaxPhotons);
    HTValVector<Float_t> px(kMaxPhotons), py(kMaxPhotons),  pz(kMaxPhotons);
    HTValVector<Float_t> pt(kMaxPhotons), eta(kMaxPhotons), phi(kMaxPhotons);
  
  HTValVector<Float_t> r9(kMaxPhotons), scEnergy(kMaxPhotons), rawEnergy(kMaxPhotons), preshowerEnergy(kMaxPhotons);
  HTValVector<Float_t> phiWidth(kMaxPhotons), etaWidth(kMaxPhotons), scEta(kMaxPhotons), scPhi(kMaxPhotons);
  HTValVector<Int_t>   clustersSize(kMaxPhotons), numOfPreshClusters(kMaxPhotons);
  HTValVector<Float_t> ESRatio(kMaxPhotons);
  HTValVector<bool>    isEBGap(kMaxPhotons),  isEEGap(kMaxPhotons), isEBEEGap(kMaxPhotons);
  HTValVector<bool>    isTransGap(kMaxPhotons),  isEB(kMaxPhotons), isEE(kMaxPhotons);
  HTValVector<Int_t>   scSize(kMaxPhotons);
  
  // Photon shower shape parameters 
  HTValVector<Float_t> maxEnergyXtal(kMaxPhotons), sigmaEtaEta(kMaxPhotons), sigmaIetaIeta(kMaxPhotons), sigmaIphiIphi(kMaxPhotons);
  
  // sigmaIetaIet with various relative cuts.
  HTValVector<Float_t>  sieie47(kMaxPhotons), sieie50(kMaxPhotons), sieie46(kMaxPhotons), sieie45(kMaxPhotons) , sieie44(kMaxPhotons),  sieie43(kMaxPhotons), sieie42(kMaxPhotons), sieie39(kMaxPhotons) ;


  // sigmaIetaIet with various absolute cuts.                                                                                    
  HTValVector<Float_t>  sieie02a(kMaxPhotons), sieie03a(kMaxPhotons), sieie04a(kMaxPhotons), sieie05a(kMaxPhotons), sieie08a(kMaxPhotons), sieie10a(kMaxPhotons) ;       
  HTValVector<Float_t> sieie022a(kMaxPhotons), sieie025a(kMaxPhotons), sieie027a(kMaxPhotons), sieie032a(kMaxPhotons), sieie035a(kMaxPhotons), sieie037a(kMaxPhotons);

  HTValVector<Float_t> r1x5(kMaxPhotons), r2x5(kMaxPhotons), e1x5(kMaxPhotons), e2x5(kMaxPhotons), e3x3(kMaxPhotons);
  // with lazyTool
  HTValVector<Float_t> eMax(kMaxPhotons), e2nd(kMaxPhotons), e2x2(kMaxPhotons), e3x2(kMaxPhotons), e4x4(kMaxPhotons), e5x5(kMaxPhotons);
  HTValVector<Float_t> e2x5Right(kMaxPhotons), e2x5Left(kMaxPhotons), e2x5Top(kMaxPhotons), e2x5Bottom(kMaxPhotons);
  HTValVector<Float_t> eRight(kMaxPhotons), eLeft(kMaxPhotons), eTop(kMaxPhotons), eBottom(kMaxPhotons);
  HTValVector<Float_t> e2overe8(kMaxPhotons); //NEW
  HTValVector<Float_t> covPhiPhi(kMaxPhotons), covEtaPhi(kMaxPhotons), covEtaEta(kMaxPhotons);

  HTValVector<Float_t> seedTime(kMaxPhotons), seedChi2(kMaxPhotons), seedOutOfTimeChi2(kMaxPhotons), seedEnergy(kMaxPhotons);
  HTValVector<Float_t> tLef(kMaxPhotons), tRight(kMaxPhotons), tTop(kMaxPhotons), tBottom(kMaxPhotons);  
  HTValVector<Int_t>   seedRecoFlag(kMaxPhotons), seedSeverity(kMaxPhotons);
  

  // AOD isolation and identification
  HTValVector<Float_t> hadronicOverEm(kMaxPhotons), hadronicDepth1OverEm(kMaxPhotons), hadronicDepth2OverEm(kMaxPhotons);
  HTValVector<Float_t> trackIso(kMaxPhotons), caloIso(kMaxPhotons), ecalIso(kMaxPhotons), hcalIso(kMaxPhotons);

  // Delta R= 0.4
  HTValVector<Float_t> ecalRecHitSumEtConeDR04(kMaxPhotons), hcalTowerSumEtConeDR04(kMaxPhotons), hcalDepth1TowerSumEtConeDR04(kMaxPhotons);
  HTValVector<Float_t> hcalDepth2TowerSumEtConeDR04(kMaxPhotons), trkSumPtSolidConeDR04(kMaxPhotons), trkSumPtHollowConeDR04(kMaxPhotons);
  HTValVector<Int_t> nTrkSolidConeDR04(kMaxPhotons), nTrkHollowConeDR04(kMaxPhotons);
  
  // Comp. Cone R= 0.4   (Average of all comp cones corresponding to that photon )
  HTValVector<Float_t> compTrackIso(kMaxPhotons), compEcalIso(kMaxPhotons), compHcalIso(kMaxPhotons);
  
  // Delta R= 0.3
  HTValVector<Float_t> ecalRecHitSumEtConeDR03(kMaxPhotons), hcalTowerSumEtConeDR03(kMaxPhotons), hcalDepth1TowerSumEtConeDR03(kMaxPhotons);
  HTValVector<Float_t> hcalDepth2TowerSumEtConeDR03(kMaxPhotons), trkSumPtSolidConeDR03(kMaxPhotons), trkSumPtHollowConeDR03(kMaxPhotons);
  HTValVector<Int_t> nTrkSolidConeDR03(kMaxPhotons), nTrkHollowConeDR03(kMaxPhotons);
  
 

  // Heavy Ion Variables
  HTValVector<Float_t> c1(kMaxPhotons), c2(kMaxPhotons),c3(kMaxPhotons),c4(kMaxPhotons),c5(kMaxPhotons), c4j(kMaxPhotons);
  HTValVector<Float_t> cc1(kMaxPhotons), cc2(kMaxPhotons),cc3(kMaxPhotons),cc4(kMaxPhotons),cc5(kMaxPhotons),cc05(kMaxPhotons), cc4j(kMaxPhotons);
  HTValVector<Float_t> t1(kMaxPhotons), t2(kMaxPhotons),t3(kMaxPhotons),t4(kMaxPhotons),t5(kMaxPhotons), t05(kMaxPhotons);
  HTValVector<Float_t> ct1(kMaxPhotons), ct2(kMaxPhotons),ct3(kMaxPhotons),ct4(kMaxPhotons),ct5(kMaxPhotons),ct05(kMaxPhotons);
  HTValVector<Float_t> t1PtCut(kMaxPhotons), t2PtCut(kMaxPhotons),t3PtCut(kMaxPhotons),t4PtCut(kMaxPhotons),t5PtCut(kMaxPhotons),t05PtCut(kMaxPhotons);
  HTValVector<Float_t> ct1PtCut(kMaxPhotons), ct2PtCut(kMaxPhotons),ct3PtCut(kMaxPhotons),ct4PtCut(kMaxPhotons),ct5PtCut(kMaxPhotons), ct05PtCut(kMaxPhotons);
    
  HTValVector<Float_t> ct4j(kMaxPhotons), ct4j10(kMaxPhotons),ct4j15(kMaxPhotons),ct4j20(kMaxPhotons);

  HTValVector<Float_t> trackIsohi(kMaxPhotons), trackIsohi10(kMaxPhotons), trackIsohi15(kMaxPhotons), trackIsohi20(kMaxPhotons);
  HTValVector<Float_t> trackIsohij(kMaxPhotons), trackIsohi10j(kMaxPhotons), trackIsohi15j(kMaxPhotons), trackIsohi20j(kMaxPhotons);

  // missing pt
  HTValVector<Float_t> mpt0(kMaxPhotons), mpt05(kMaxPhotons), mpt2(kMaxPhotons), mpt4(kMaxPhotons); 
  
  
  
  HTValVector<Float_t> r1(kMaxPhotons), r2(kMaxPhotons),r3(kMaxPhotons),r4(kMaxPhotons),r5(kMaxPhotons);
  HTValVector<Float_t> cr1(kMaxPhotons), cr2(kMaxPhotons),cr3(kMaxPhotons),cr4(kMaxPhotons),cr5(kMaxPhotons), cr05(kMaxPhotons), cr4j(kMaxPhotons);
  HTValVector<Float_t> dr11(kMaxPhotons),dr12(kMaxPhotons),dr13(kMaxPhotons),dr14(kMaxPhotons);
  HTValVector<Float_t> dr21(kMaxPhotons),dr22(kMaxPhotons),dr23(kMaxPhotons),dr24(kMaxPhotons);
  HTValVector<Float_t> dr31(kMaxPhotons),dr32(kMaxPhotons),dr33(kMaxPhotons),dr34(kMaxPhotons);
  HTValVector<Float_t> dr41(kMaxPhotons),dr42(kMaxPhotons),dr43(kMaxPhotons),dr44(kMaxPhotons);
  HTValVector<Float_t> t11(kMaxPhotons),t12(kMaxPhotons),t13(kMaxPhotons),t14(kMaxPhotons);
  HTValVector<Float_t> t21(kMaxPhotons),t22(kMaxPhotons),t23(kMaxPhotons),t24(kMaxPhotons);
  HTValVector<Float_t> t31(kMaxPhotons),t32(kMaxPhotons),t33(kMaxPhotons),t34(kMaxPhotons);
  HTValVector<Float_t> t41(kMaxPhotons),t42(kMaxPhotons),t43(kMaxPhotons),t44(kMaxPhotons);
  HTValVector<Float_t> nLocalTracks(kMaxPhotons), nAllTracks(kMaxPhotons);

  // Electron ID
  HTValVector<bool> isElectron(kMaxPhotons);
  HTValVector<Float_t>  dphiEle(kMaxPhotons), detaEle(kMaxPhotons) ; 
  HTValVector<Float_t>  deltaEtaEleCT(kMaxPhotons), deltaPhiEleCT(kMaxPhotons) ;
  HTValVector<Int_t>  eleCharge(kMaxPhotons);
  HTValVector<Float_t>  eleEoverP(kMaxPhotons);
  
  // Conversion
  HTValVector<bool> isConverted(kMaxPhotons), hasConversionTracks(kMaxPhotons), hasPixelSeed(kMaxPhotons);
  
  
  // ID
  HTValVector<bool> isLoose(kMaxPhotons), isTight(kMaxPhotons);
  
  HTValVector<Int_t>   nTracks(kMaxPhotons);
  HTValVector<TVector3> convPairMomentum(kMaxPhotons);
  HTValVector<Float_t> convPairInvariantMass(kMaxPhotons), convpairCotThetaSeparation(kMaxPhotons), convPairMomentumMag(kMaxPhotons);
  HTValVector<Float_t> convPairMomentumPerp(kMaxPhotons), convPairMomentumPhi(kMaxPhotons), convPairMomentumEta(kMaxPhotons);
  HTValVector<Float_t> convPairMomentumX(kMaxPhotons), convPairMomentumY(kMaxPhotons), convPairMomentumZ(kMaxPhotons);
  HTValVector<Float_t> convDistOfMinimumApproach(kMaxPhotons), convDPhiTracksAtVtx(kMaxPhotons), convDPhiTracksAtEcal(kMaxPhotons);
  HTValVector<Float_t> convDEtaTracksAtEcal(kMaxPhotons);

  HTValVector<Bool_t> convVtxValid(kMaxPhotons);
  HTValVector<TVector3> convVtx(kMaxPhotons);
  HTValVector<Float_t> convVtxEta(kMaxPhotons), convVtxPhi(kMaxPhotons), convVtxR(kMaxPhotons);
  HTValVector<Float_t> convVtxX(kMaxPhotons), convVtxY(kMaxPhotons), convVtxZ(kMaxPhotons);
  HTValVector<Float_t> convVtxChi2(kMaxPhotons), convVtxNdof(kMaxPhotons), convMVALikelihood(kMaxPhotons), chi2Prob(kMaxPhotons);

  HTValVector<Float_t> convEoverP(kMaxPhotons), convzOfPrimaryVertexFromTracks(kMaxPhotons);

  // Generator matched 
  HTValVector<TLorentzVector>    genMatchedP4(kMaxPhotons);
  HTValVector<bool>    isGenMatched(kMaxPhotons);
  HTValVector<Int_t>   genMomId(kMaxPhotons);
  HTValVector<Int_t>   genGrandMomId(kMaxPhotons);
  HTValVector<Int_t>   genNSiblings(kMaxPhotons);
  HTValVector<Int_t>   genMatchedCollId(kMaxPhotons);
  HTValVector<Float_t> genMatchedPt(kMaxPhotons), genMatchedEta(kMaxPhotons), genMatchedPhi(kMaxPhotons);
  HTValVector<Float_t> genCalIsoDR03(kMaxPhotons), genTrkIsoDR03(kMaxPhotons);
  HTValVector<Float_t> genCalIsoDR04(kMaxPhotons), genTrkIsoDR04(kMaxPhotons);


  */
  // store general
  run = (Int_t)e.id().run();
  event = (Int_t)e.id().event();
  bunchCrossing = (Int_t)e.bunchCrossing();
  luminosityBlock = (Int_t)e.luminosityBlock();
  
  int nphotonscounter(0);
  for (PhotonCollection::const_iterator phoItr = myphotons.begin(); phoItr != myphotons.end(); ++phoItr) {  
     if(phoItr->pt() < ptMin_ || fabs(phoItr->p4().eta()) > etaMax_) continue;
     // Dump photon kinematics and AOD
     Photon photon = Photon(*phoItr);
     // NOTE: since CMSSW_3_1_x all photons are corrected to the primary vertex
     //       hence, Photon::setVertex() leaves photon object unchanged
     //     photon.setVertex(vtx_);   <== Test if this makes error
     
     //   p4    (nphotonscounter) =  TLorentzVector(photon.px(),photon.py(),photon.pz(),photon.energy());
    p     (nphotonscounter) =  photon.p();
    et    (nphotonscounter) =  photon.et();

    pt[nphotonscounter] = photon.p4().pt();
    px[nphotonscounter] = photon.px();
    py[nphotonscounter] = photon.py();
    pz[nphotonscounter] = photon.pz();
    energy[nphotonscounter] = photon.energy();
    rawEnergy[nphotonscounter] =  photon.superCluster()->rawEnergy();
    
    eta[nphotonscounter] =  photon.p4().eta();
    phi[nphotonscounter] =  photon.p4().phi();

    r9[nphotonscounter]    =  photon.r9();
 
    isEBGap[nphotonscounter]    =  photon.isEBGap()? 1:0;
    isEEGap[nphotonscounter]    =  photon.isEEGap()? 1:0;
    isEBEEGap[nphotonscounter]  =  photon.isEBEEGap()? 1:0;
    isTransGap[nphotonscounter] =  (fabs(photon.eta()) > ecalBarrelMaxEta_ && fabs(photon.eta()) < ecalEndcapMinEta_) ? 1:0;
    
    preshowerEnergy[nphotonscounter]    =  photon.superCluster()->preshowerEnergy();
    numOfPreshClusters[nphotonscounter] =  getNumOfPreshClusters(&photon, e);
    clustersSize[nphotonscounter]   =  photon.superCluster()->clustersSize();
    phiWidth  [nphotonscounter]  =  photon.superCluster()->phiWidth();
    etaWidth  [nphotonscounter]   =  photon.superCluster()->etaWidth();
    scEta     [nphotonscounter]   =  photon.superCluster()->eta();
    scPhi     [nphotonscounter]  =  photon.superCluster()->phi();
    scSize    [nphotonscounter]   =  photon.superCluster()->size();

    //ES Ratio
    ESRatio   [nphotonscounter]   =  getESRatio(&photon, e, iSetup);
    
    // Cluster shape variables
    
    const reco::CaloClusterPtr  seed = photon.superCluster()->seed();

    DetId id = lazyTool.getMaximum(*seed).first; 
    float time  = -999., outOfTimeChi2 = -999., chi2 = -999.;
    int   flags=-1, severity = -1; 
    const EcalRecHitCollection & rechits = ( photon.isEB() ? *EBReducedRecHits : *EEReducedRecHits); 
    EcalRecHitCollection::const_iterator it = rechits.find( id );
    if( it != rechits.end() ) { 
      time = it->time(); 
      outOfTimeChi2 = it->outOfTimeChi2();
      chi2 = it->chi2();
      flags = it->recoFlag();
      severity = EcalSeverityLevelAlgo::severityLevel( id, rechits, *chStatus );
    }

    float tlef = -999., tright=-999., ttop=-999., tbottom=-999.;
    std::vector<DetId> left   = lazyTool.matrixDetId(id,-1,-1, 0, 0);
    std::vector<DetId> right  = lazyTool.matrixDetId(id, 1, 1, 0, 0);
    std::vector<DetId> top    = lazyTool.matrixDetId(id, 0, 0, 1, 1);
    std::vector<DetId> bottom = lazyTool.matrixDetId(id, 0, 0,-1,-1);
    
    float *times[4] = {&tleft,&tright,&ttop,&tbottom};
    std::vector<DetId> ids[4]  = {left,right,top,bottom};
    int nt = sizeof(times)/sizeof(float);
    for(int ii=0; ii<nt; ++ii) {
       if( ids[ii].empty() ) { continue; }
       it = rechits.find( ids[ii][0] );
       if( it != rechits.end() ) { *(times[ii]) = it->time(); }
    }
    
    seedTime              [nphotonscounter]  = time;
    seedOutOfTimeChi2     [nphotonscounter]  = outOfTimeChi2;
    seedChi2              [nphotonscounter]  = chi2;
    seedRecoFlag          [nphotonscounter] = flags;
    seedSeverity          [nphotonscounter]  = severity;
    
    tLeft         [nphotonscounter] = tleft;
    tRight        [nphotonscounter] = tright;
    tTop        [nphotonscounter] = ttop;
    tBottom        [nphotonscounter] = tbottom;
    
    
    eMax         [nphotonscounter] =  lazyTool.eMax(*seed);
    e2nd         [nphotonscounter] =  lazyTool.e2nd(*seed);
    e2x2         [nphotonscounter] =  lazyTool.e2x2(*seed);
    e3x2         [nphotonscounter] =  lazyTool.e3x2(*seed);
    e3x3         [nphotonscounter] =  lazyTool.e3x3(*seed);
    e4x4         [nphotonscounter] =  lazyTool.e4x4(*seed);
    e5x5         [nphotonscounter] =  lazyTool.e5x5(*seed);
    e2overe8     [nphotonscounter] =  ( lazyTool.e3x3(*seed)-lazyTool.eMax(*seed) ==0 )? 0: lazyTool.e2nd(*seed)/( lazyTool.e3x3(*seed)-lazyTool.eMax(*seed) );
    
    e2x5Right    [nphotonscounter] =  lazyTool.e2x5Right(*seed);
    e2x5Left     [nphotonscounter] =  lazyTool.e2x5Left(*seed);
    e2x5Top      [nphotonscounter] =  lazyTool.e2x5Top(*seed);
    e2x5Bottom   [nphotonscounter] =  lazyTool.e2x5Bottom(*seed);
    eRight       [nphotonscounter] =  lazyTool.eRight(*seed);
    eLeft        [nphotonscounter] =  lazyTool.eLeft(*seed);
    eTop         [nphotonscounter] =  lazyTool.eTop(*seed);
    eBottom      [nphotonscounter] =  lazyTool.eBottom(*seed);
    swissCrx     [nphotonscounter] =  1 - eMax[nphotonscounter] / ( eRight[nphotonscounter] + eLeft[nphotonscounter] + eTop[nphotonscounter] + eBottom[nphotonscounter] )  ;
    
    vector<float> vCov;
    vCov = lazyTool.covariances(*seed);
    covPhiPhi    (nphotonscounter) = vCov[0];
    covEtaPhi    (nphotonscounter) = vCov[1];
    covEtaEta    (nphotonscounter) = vCov[2];

// Photon shower shape parameters 

    maxEnergyXtal(nphotonscounter) =  photon.maxEnergyXtal();
    sigmaEtaEta  (nphotonscounter) =  photon.sigmaEtaEta();
    sigmaIetaIeta(nphotonscounter) =  photon.sigmaIetaIeta();

    // see http://cmslxr.fnal.gov/lxr/source/RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h#076
    // other sieie values;
    vector<float> lCov47 = lazyTool.localCovariances(*seed, 4.7 );
    sieie47(nphotonscounter) = sqrt(lCov47[0]);
    sigmaIphiIphi(nphotonscounter) =  sqrt(lCov47[2]);
    
    
    vector<float> lCov50 = lazyTool.localCovariances(*seed, 5.0 );
    sieie50(nphotonscounter) = sqrt(lCov50[0]);
    vector<float> lCov46 = lazyTool.localCovariances(*seed, 4.6 );
    sieie46(nphotonscounter) = sqrt(lCov46[0]);
    vector<float> lCov45 = lazyTool.localCovariances(*seed, 4.5 );
    sieie45(nphotonscounter) = sqrt(lCov45[0]);
    vector<float> lCov44 = lazyTool.localCovariances(*seed, 4.4 );
    sieie44(nphotonscounter) = sqrt(lCov44[0]);
    vector<float> lCov43 = lazyTool.localCovariances(*seed, 4.3 );
    sieie43(nphotonscounter) = sqrt(lCov43[0]);
    vector<float> lCov42 = lazyTool.localCovariances(*seed, 4.2 );
    sieie42(nphotonscounter) = sqrt(lCov42[0]);
    vector<float> lCov39 = lazyTool.localCovariances(*seed, 3.9 );
    sieie39(nphotonscounter) = sqrt(lCov39[0]);
    
    // absolute cuts.   cut = eMax * exp(-v)   so, v = -log(cut/eMax)
    float  theSeedE = eMax(nphotonscounter);
    vector<float> lCov02a = lazyTool.localCovariances(*seed, -log(0.2/theSeedE) );
    sieie02a(nphotonscounter) = sqrt(lCov02a[0]);
    //    cout << "theSeedE = " << theSeedE << "    and cut = 0.2 " << "log (cut/theSeedE) = " << -log( 0.2 / theSeedE )  << endl;
    vector<float> lCov03a = lazyTool.localCovariances(*seed, -log( 0.3 / theSeedE ) );
    sieie03a(nphotonscounter) = sqrt(lCov03a[0]);
    vector<float> lCov04a = lazyTool.localCovariances(*seed, -log( 0.4 / theSeedE ) );
    sieie04a(nphotonscounter) = sqrt(lCov04a[0]);
    vector<float> lCov05a = lazyTool.localCovariances(*seed, -log( 0.5 / theSeedE ) );
    sieie05a(nphotonscounter) = sqrt(lCov05a[0]);
    vector<float> lCov08a = lazyTool.localCovariances(*seed, -log( 0.8 / theSeedE ) );
    sieie08a(nphotonscounter) = sqrt(lCov08a[0]);
    vector<float> lCov10a = lazyTool.localCovariances(*seed, -log( 1.0 / theSeedE ) );
    sieie10a(nphotonscounter) = sqrt(lCov10a[0]);

    vector<float> lCov022a = lazyTool.localCovariances(*seed, -log( 0.22 / theSeedE ) );
    sieie022a(nphotonscounter) = sqrt(lCov022a[0]);
    vector<float> lCov025a = lazyTool.localCovariances(*seed, -log( 0.25 / theSeedE ) );
    sieie025a(nphotonscounter) = sqrt(lCov025a[0]);
    vector<float> lCov027a = lazyTool.localCovariances(*seed, -log( 0.27 / theSeedE ) );
    sieie027a(nphotonscounter) = sqrt(lCov027a[0]);

    vector<float> lCov032a = lazyTool.localCovariances(*seed, -log( 0.32 / theSeedE ) );
    sieie032a(nphotonscounter) = sqrt(lCov032a[0]);
    vector<float> lCov035a = lazyTool.localCovariances(*seed, -log( 0.35 / theSeedE ) );
    sieie035a(nphotonscounter) = sqrt(lCov035a[0]);
    vector<float> lCov037a = lazyTool.localCovariances(*seed, -log( 0.37 / theSeedE ) );
    sieie037a(nphotonscounter) = sqrt(lCov037a[0]);



    //  HTValVector<Float_t>  sieie47(kMaxPhotons), sieie50(kMaxPhotons), sieie46(kMaxPhotons), sieie45(kMaxPhotons) , sieie44(kMaxPhotons),  sieie43(kMaxPhotons), sieie42(kMaxPhotons), sieie39(kMaxPhotons) ;



    r1x5         (nphotonscounter) =  photon.r1x5();
    r2x5         (nphotonscounter) =  photon.r2x5();
    e1x5         (nphotonscounter) =  photon.e1x5();
    e2x5         (nphotonscounter) =  photon.e2x5();


    
    // AOD isolation and identification
    
    hadronicOverEm      (nphotonscounter)   =  photon.hadronicOverEm();
    hadronicDepth1OverEm(nphotonscounter)   =  photon.hadronicDepth1OverEm();
    hadronicDepth2OverEm(nphotonscounter)   =  photon.hadronicDepth2OverEm();
    trackIso            (nphotonscounter)   =  photon.trackIso();
    caloIso             (nphotonscounter)   =  photon.caloIso();
    ecalIso             (nphotonscounter)   =  photon.ecalIso();
    hcalIso             (nphotonscounter)   =  photon.hcalIso();
 
    // electron id
    bool isEleTemp = false;
    float dphiTemp(100), detaTemp(100);
    float deltaPhiEleCTTemp(100), deltaEtaEleCTTemp(100);
    int eleChargeTemp(100);
    float eleEpTemp(100);
    
    //    cout << "photon et = " << photon.et() << "  eta =" << photon.eta() << endl;
    
    if ( isEleRecoed ) {
      //   cout << " start electron search " << endl;
      // We will find the smallest e/p electron canddiates.
      for ( reco::GsfElectronCollection::const_iterator eleItr = myEle.begin(); eleItr != myEle.end(); ++eleItr) {
	if ( eleItr->superCluster()->energy() < 10 ) continue;
	//	cout << "electron et = " << eleItr->et() << "    eta = " << eleItr->eta() << endl ;
	if ( abs( eleItr->superCluster()->eta() - photon.superCluster()->eta() ) > 0.03 ) continue;
	
	float dphi = eleItr->superCluster()->phi() - photon.superCluster()->phi();
	if ( dphi >  3.141592 ) dphi = dphi - 2* 3.141592;
	if ( dphi < -3.141592 ) dphi = dphi + 2* 3.141592;
	if ( abs(dphi) > 0.03 )  continue;
	
	  float iEp = eleItr->eSuperClusterOverP() ;   
	
	  // We should match with higher momentum electron candidates. 
	  //	  cout << " current iEp = " << iEp << endl;
	  //	  cout << " eleEpTemp = " << eleEpTemp << endl;

	  if ( eleEpTemp < iEp )  continue;
	  //  cout << " so.. it was replaced " << endl;
	  eleEpTemp = iEp;
	  eleChargeTemp =  eleItr->charge();
	  deltaPhiEleCTTemp =  eleItr->deltaPhiEleClusterTrackAtCalo() ; 
	  deltaEtaEleCTTemp =  eleItr->deltaEtaEleClusterTrackAtCalo() ;
	  dphiTemp = dphi;  
	  detaTemp = eleItr->superCluster()->eta() - photon.superCluster()->eta() ;
	  
	  cout << " this is electron " << endl;
	  isEleTemp = true;
       }
       
       if ( isEleTemp == false)  
	  cout << " this is not an electron" << endl;
    }
    
    isElectron         (nphotonscounter)    =  isEleTemp;
    detaEle            (nphotonscounter)    =  detaTemp;
    dphiEle            (nphotonscounter)    =  dphiTemp;
    deltaEtaEleCT      (nphotonscounter)    =  deltaEtaEleCTTemp;
    deltaPhiEleCT      (nphotonscounter)    =  deltaPhiEleCTTemp;
    eleCharge          (nphotonscounter)    =  eleChargeTemp;
    eleEoverP          (nphotonscounter)    =  eleEpTemp;


    
    
    // comp cones;
    int nComp = 0;
    int allcomps = 0;
    float sumCompEIso=0;
    float sumCompHIso=0;
    float sumCompTIso=0;
    
  
    for (reco::PhotonCollection::const_iterator compItr = myCompPhotons.begin(); compItr != myCompPhotons.end(); ++compItr) {
       allcomps++;
       if(compItr->pt() < ptMin_ || fabs(compItr->p4().eta()) > etaMax_) continue;
       
       if(compItr->superCluster()->energy() != photon.superCluster()->energy() ) continue;
       
       
       nComp++;
       Photon compPhoton = Photon(*compItr);
       compPhoton.setVertex(vtx_);
       sumCompEIso =  sumCompEIso + compItr->ecalRecHitSumEtConeDR04();
       sumCompHIso =  sumCompHIso + compItr->hcalTowerSumEtConeDR04();
       sumCompTIso =  sumCompTIso + compItr->trkSumPtHollowConeDR04();
       
    }
    
    //    cout << " Number of matched compl cones = " << nComp << endl;
    
    if ( nComp > 0 ) {
       compTrackIso(nphotonscounter) = sumCompTIso/(double)nComp;
       compEcalIso (nphotonscounter) = sumCompEIso/(double)nComp;
       compHcalIso (nphotonscounter) = sumCompHIso/(double)nComp;
    }
    else {
       compTrackIso(nphotonscounter) = -100;
       compEcalIso (nphotonscounter) = -100;
       compHcalIso (nphotonscounter) = -100;
    }
      
    
// Delta R= 0.4
    
    ecalRecHitSumEtConeDR04     (nphotonscounter)   =  photon.ecalRecHitSumEtConeDR04();
    hcalTowerSumEtConeDR04      (nphotonscounter)   =  photon.hcalTowerSumEtConeDR04();
    hcalDepth1TowerSumEtConeDR04(nphotonscounter)   =  photon.hcalDepth1TowerSumEtConeDR04();
    hcalDepth2TowerSumEtConeDR04(nphotonscounter)   =  photon.hcalDepth2TowerSumEtConeDR04();
    trkSumPtSolidConeDR04       (nphotonscounter)   =  photon.trkSumPtSolidConeDR04();
    trkSumPtHollowConeDR04      (nphotonscounter)   =  photon.trkSumPtHollowConeDR04();
    nTrkSolidConeDR04           (nphotonscounter)   =  photon.nTrkSolidConeDR04();
    nTrkHollowConeDR04          (nphotonscounter)   =  photon.nTrkHollowConeDR04();

// Delta R= 0.3

    ecalRecHitSumEtConeDR03     (nphotonscounter)   =  photon.ecalRecHitSumEtConeDR03();
    hcalTowerSumEtConeDR03      (nphotonscounter)   =  photon.hcalTowerSumEtConeDR03();
    hcalDepth1TowerSumEtConeDR03(nphotonscounter)   =  photon.hcalDepth1TowerSumEtConeDR03();
    hcalDepth2TowerSumEtConeDR03(nphotonscounter)   =  photon.hcalDepth2TowerSumEtConeDR03();
    trkSumPtSolidConeDR03       (nphotonscounter)   =  photon.trkSumPtSolidConeDR03();
    trkSumPtHollowConeDR03      (nphotonscounter)   =  photon.trkSumPtHollowConeDR03();
    nTrkSolidConeDR03           (nphotonscounter)   =  photon.nTrkSolidConeDR03();
    nTrkHollowConeDR03          (nphotonscounter)   =  photon.nTrkHollowConeDR03();
    

    c1                          (nphotonscounter)   =  CxC.getCx(photon.superCluster(),1,0);
    c2                          (nphotonscounter)   =  CxC.getCx(photon.superCluster(),2,0);
    c3                          (nphotonscounter)   =  CxC.getCx(photon.superCluster(),3,0);
    c4                          (nphotonscounter)   =  CxC.getCx(photon.superCluster(),4,0);
    c5                          (nphotonscounter)   =  CxC.getCx(photon.superCluster(),5,0);

    t1                          (nphotonscounter)   =  TxC.getTx(photon,1,0);
    t2                          (nphotonscounter)   =  TxC.getTx(photon,2,0);
    t3                          (nphotonscounter)   =  TxC.getTx(photon,3,0);
    t4                          (nphotonscounter)   =  TxC.getTx(photon,4,0);
    t5                          (nphotonscounter)   =  TxC.getTx(photon,5,0);

    r1                          (nphotonscounter)   =  RxC.getRx(photon.superCluster(),1,0);
    r2                          (nphotonscounter)   =  RxC.getRx(photon.superCluster(),2,0);
    r3                          (nphotonscounter)   =  RxC.getRx(photon.superCluster(),3,0);
    r4                          (nphotonscounter)   =  RxC.getRx(photon.superCluster(),4,0);
    r5                          (nphotonscounter)   =  RxC.getRx(photon.superCluster(),5,0);

    t1PtCut                     (nphotonscounter)   =  TxC.getTx(photon,1,2); // 2 GeV cut
    t2PtCut                     (nphotonscounter)   =  TxC.getTx(photon,2,2);
    t3PtCut                     (nphotonscounter)   =  TxC.getTx(photon,3,2);
    t4PtCut                     (nphotonscounter)   =  TxC.getTx(photon,4,2);
    t5PtCut                     (nphotonscounter)   =  TxC.getTx(photon,5,2);


    cc1                          (nphotonscounter)   =  CxC.getCCx(photon.superCluster(),1,0);
    cc2                          (nphotonscounter)   =  CxC.getCCx(photon.superCluster(),2,0);
    cc3                          (nphotonscounter)   =  CxC.getCCx(photon.superCluster(),3,0);
    cc4                          (nphotonscounter)   =  CxC.getCCx(photon.superCluster(),4,0);
    cc5                          (nphotonscounter)   =  CxC.getCCx(photon.superCluster(),5,0);
    cc05                         (nphotonscounter)   =  CxC.getCCx(photon.superCluster(),0.5,0);
    
    // jurassic cone;
    cc4j                         (nphotonscounter)   =  CxC.getJcc(photon.superCluster(),0.4,0.06,0.04,0);
    
    
    ct1                          (nphotonscounter)   =  TxC.getCTx(photon,1,0);
    ct2                          (nphotonscounter)   =  TxC.getCTx(photon,2,0);
    ct3                          (nphotonscounter)   =  TxC.getCTx(photon,3,0);
    ct4                          (nphotonscounter)   =  TxC.getCTx(photon,4,0);
    ct5                          (nphotonscounter)   =  TxC.getCTx(photon,5,0);
    ct05                         (nphotonscounter)   =  TxC.getCTx(photon,0.5,0);
    
    cr1                          (nphotonscounter)   =  RxC.getCRx(photon.superCluster(),1,0);
    cr2                          (nphotonscounter)   =  RxC.getCRx(photon.superCluster(),2,0);
    cr3                          (nphotonscounter)   =  RxC.getCRx(photon.superCluster(),3,0);
    cr4                          (nphotonscounter)   =  RxC.getCRx(photon.superCluster(),4,0);
    cr5                          (nphotonscounter)   =  RxC.getCRx(photon.superCluster(),5,0);
    cr05                         (nphotonscounter)   =  RxC.getCRx(photon.superCluster(),0.5,0);

    cr4j                         (nphotonscounter)   =  RxC.getCRx(photon.superCluster(),4,0,0.15);

    
    ct1PtCut                     (nphotonscounter)   =  TxC.getCTx(photon,1,2); // 2 GeV cut
    ct2PtCut                     (nphotonscounter)   =  TxC.getCTx(photon,2,2); 
    ct3PtCut                     (nphotonscounter)   =  TxC.getCTx(photon,3,2);
    ct4PtCut                     (nphotonscounter)   =  TxC.getCTx(photon,4,2);
    ct5PtCut                     (nphotonscounter)   =  TxC.getCTx(photon,5,2);
    ct05PtCut                    (nphotonscounter)   =  TxC.getCTx(photon,0.5,2);

    trackIsohi                   (nphotonscounter)   =  TxC.getTx(photon,4, 0.0, 0.04);
    trackIsohi10                 (nphotonscounter)   =  TxC.getTx(photon,4, 1.0, 0.04);
    trackIsohi15                 (nphotonscounter)   =  TxC.getTx(photon,4, 1.5, 0.04);
    trackIsohi20                 (nphotonscounter)   =  TxC.getTx(photon,4, 2.0, 0.04);
    
    trackIsohij                   (nphotonscounter)   =  TxC.getJt(photon, 0.4, 0.04, 0.015,0.0);
    trackIsohi10j                 (nphotonscounter)   =  TxC.getJt(photon, 0.4, 0.04, 0.015,1.0);
    trackIsohi15j                 (nphotonscounter)   =  TxC.getJt(photon, 0.4, 0.04, 0.015,1.5);
    trackIsohi20j                 (nphotonscounter)   =  TxC.getJt(photon, 0.4, 0.04, 0.015,2.0);
    ct4j                          (nphotonscounter)   =  TxC.getJct(photon,0.4, 0.04, 0.015,0);
    ct4j10                        (nphotonscounter)   =  TxC.getJct(photon,0.4, 0.04, 0.015,1.0);
    ct4j15                        (nphotonscounter)   =  TxC.getJct(photon,0.4, 0.04, 0.015,1.5);
    ct4j20                        (nphotonscounter)   =  TxC.getJct(photon,0.4, 0.04, 0.015,2.0);



    mpt0                         (nphotonscounter)   =  TxC.getMPT(0.);
    mpt05                        (nphotonscounter)   =  TxC.getMPT(0.5);
    mpt2                         (nphotonscounter)   =  TxC.getMPT(2);
    mpt4                         (nphotonscounter)   =  TxC.getMPT(4);
    
    
    dr11                         (nphotonscounter)   =  dRxy.getDRxy(photon,1,1);
    dr12                         (nphotonscounter)   =  dRxy.getDRxy(photon,1,2);
    dr13                         (nphotonscounter)   =  dRxy.getDRxy(photon,1,3);
    dr14                         (nphotonscounter)   =  dRxy.getDRxy(photon,1,4);
  
    dr21                         (nphotonscounter)   =  dRxy.getDRxy(photon,2,1);
    dr22                         (nphotonscounter)   =  dRxy.getDRxy(photon,2,2);
    dr23                         (nphotonscounter)   =  dRxy.getDRxy(photon,2,3);
    dr24                         (nphotonscounter)   =  dRxy.getDRxy(photon,2,4);
  
    dr31                         (nphotonscounter)   =  dRxy.getDRxy(photon,3,1);
    dr32                         (nphotonscounter)   =  dRxy.getDRxy(photon,3,2);
    dr33                         (nphotonscounter)   =  dRxy.getDRxy(photon,3,3);
    dr34                         (nphotonscounter)   =  dRxy.getDRxy(photon,3,4);

    dr41                         (nphotonscounter)   =  dRxy.getDRxy(photon,4,1);
    dr42                         (nphotonscounter)   =  dRxy.getDRxy(photon,4,2);
    dr43                         (nphotonscounter)   =  dRxy.getDRxy(photon,4,3);
    dr44                         (nphotonscounter)   =  dRxy.getDRxy(photon,4,4);

    t11                         (nphotonscounter)   =  Txy.getTxy(photon,1,1);
    t12                         (nphotonscounter)   =  Txy.getTxy(photon,1,2);
    t13                         (nphotonscounter)   =  Txy.getTxy(photon,1,3);
    t14                         (nphotonscounter)   =  Txy.getTxy(photon,1,4);

    t21                         (nphotonscounter)   =  Txy.getTxy(photon,2,1);
    t22                         (nphotonscounter)   =  Txy.getTxy(photon,2,2);
    t23                         (nphotonscounter)   =  Txy.getTxy(photon,2,3);
    t24                         (nphotonscounter)   =  Txy.getTxy(photon,2,4);

    t31                         (nphotonscounter)   =  Txy.getTxy(photon,3,1);
    t32                         (nphotonscounter)   =  Txy.getTxy(photon,3,2);
    t33                         (nphotonscounter)   =  Txy.getTxy(photon,3,3);
    t34                         (nphotonscounter)   =  Txy.getTxy(photon,3,4);

    t41                         (nphotonscounter)   =  Txy.getTxy(photon,4,1);
    t42                         (nphotonscounter)   =  Txy.getTxy(photon,4,2);
    t43                         (nphotonscounter)   =  Txy.getTxy(photon,4,3);
    t44                         (nphotonscounter)   =  Txy.getTxy(photon,4,4);
    
    nAllTracks                  (nphotonscounter)   =  (float)Txy.getNumAllTracks(1);   // pt Cut of the track = 1GeV
    nLocalTracks                (nphotonscounter)   =  (float)Txy.getNumLocalTracks(photon,0.5,1); // dEta cut = 0.5     and    pt Cut = 1GeV                                                                               
    // Conversion
    
    if (doStoreConversions_)
       hasConversionTracks(nphotonscounter)   =  photon.hasConversionTracks();
    hasPixelSeed       (nphotonscounter)   =  photon.hasPixelSeed();
    
    // IDs
    try { isLoose(nphotonscounter)=photon.photonID("PhotonCutBasedIDLoose"); } 
    catch (std::exception &e) {} // HeavyIon photons does not have photonID yet....edm::LogError("NotFound") << e.what();  }
    try { isTight(nphotonscounter)=photon.photonID("PhotonCutBasedIDTight"); } 
    catch (std::exception &e) {} //  edm::LogError("NotFound") << e.what();  }
    
    // removed converted photon part    
    
    
    
    ///////////////////////////////////////////
    //  Build Monte Carlo truth associations //
    ///////////////////////////////////////////
    if (isMCData_) {
      
      edm::Handle<reco::GenParticleCollection> genParticles;
      
      //  get generated particles and store generator ntuple 
      try { e.getByLabel( genParticleProducer_,      genParticles );} catch (...) {;}
      
      float delta(0.15);
      isGenMatched(nphotonscounter) = kFALSE; genMomId(nphotonscounter) = 0; genGrandMomId(nphotonscounter) = 0; genNSiblings(nphotonscounter) = 0;
      genMatchedPt(nphotonscounter) = -1; genMatchedEta(nphotonscounter) = -1000;   genMatchedPhi(nphotonscounter) = 0;
      genMatchedCollId(nphotonscounter) = -100;
      
      genCalIsoDR03(nphotonscounter) = 99999.; genTrkIsoDR03(nphotonscounter) = 99999.;
      genCalIsoDR04(nphotonscounter) = 99999.; genTrkIsoDR04(nphotonscounter) = 99999.;
      const reco::Candidate *cndMc(0);
      reco::GenParticleCollection::const_iterator matchedPart;
      Float_t currentMaxPt(-1);
      
      for (reco::GenParticleCollection::const_iterator it_gen = 
	     genParticles->begin(); it_gen!= genParticles->end(); it_gen++){   
	
	const reco::Candidate &p = (*it_gen);    
	if (p.status() != 1 || (p.pdgId()) != pdgId_ ) continue;      
	if(ROOT::Math::VectorUtil::DeltaR(p.p4(),phoItr->p4())<delta && p.pt() > currentMaxPt ) {
	  if( p.numberOfMothers() > 0 ) {
	    genMomId(nphotonscounter) = p.mother()->pdgId();
	    genNSiblings(nphotonscounter) = p.mother()->numberOfDaughters();
	    if( p.mother()->numberOfMothers() > 0 ) { 
	      genGrandMomId(nphotonscounter) = p.mother()->mother()->pdgId();
	    }
	  }
	  isGenMatched(nphotonscounter) = kTRUE; cndMc = &p;
	  genMatchedCollId(nphotonscounter) = it_gen->collisionId();
	  currentMaxPt = p.pt();
	  matchedPart  = it_gen;
	}
      }      
	
      
      // if no matching photon was found try with other particles
      if( ! isGenMatched(nphotonscounter) ) {
	
	currentMaxPt = -1;
	for (reco::GenParticleCollection::const_iterator it_gen = 
	       genParticles->begin(); it_gen!= genParticles->end(); it_gen++){
	  const reco::Candidate &p = (*it_gen);    
	  
	  if (p.status() != 1 || find(otherPdgIds_.begin(),otherPdgIds_.end(),fabs(p.pdgId())) == otherPdgIds_.end() ) continue;      	
	  if(ROOT::Math::VectorUtil::DeltaR(p.p4(),phoItr->p4())<delta && p.pt() > currentMaxPt ) {
	    genMomId(nphotonscounter) = p.pdgId();	
	    if( p.numberOfMothers() > 0 ) {
	      genGrandMomId(nphotonscounter) = p.mother()->pdgId();
	      genNSiblings(nphotonscounter)  = p.mother()->numberOfDaughters();
	    }
	    cndMc = &p; // do not set the isGenMatched in this case
	    currentMaxPt = p.pt();
	    matchedPart  = it_gen;
	  }	
	
	} // end of loop over gen particles
      } // if not matched to gen photon

      if(cndMc) {
	genMatchedP4 (nphotonscounter)  = TLorentzVector(cndMc->px(),cndMc->py(),cndMc->pz(),cndMc->energy());
	genMatchedPt (nphotonscounter)  = cndMc->pt();
	genMatchedEta(nphotonscounter)  = cndMc->eta();
	genMatchedPhi(nphotonscounter)  = cndMc->phi();
	
	genCalIsoDR03(nphotonscounter)= getGenCalIso(genParticles,matchedPart,0.3);
	genTrkIsoDR03(nphotonscounter)= getGenTrkIso(genParticles,matchedPart,0.3);
	genCalIsoDR04(nphotonscounter)= getGenCalIso(genParticles,matchedPart,0.4);
	genTrkIsoDR04(nphotonscounter)= getGenTrkIso(genParticles,matchedPart,0.4);
      }

    } // if it's a MC


    if (nphotonscounter>kMaxPhotons-1) break;
    
    nphotonscounter++;
  }
  
  nPho  = nphotonscounter;
  
  // pixel seed? 
  _ntuple->Column(pfx+"hasPixelSeed",        hasPixelSeed,        pfx+"nPhotons");
  
  

// MC truth associations
  if (isMCData_) {
    _ntuple->Column(pfx+"isGenMatched", isGenMatched,  pfx+"nPhotons");
    if( storePhysVectors_ ) {
      _ntuple->Column(pfx+"genMatchedP4", genMatchedP4,  pfx+"nPhotons");
    } else {
      _ntuple->Column(pfx+"genMatchedPt", genMatchedPt,  pfx+"nPhotons");
      _ntuple->Column(pfx+"genMatchedEta",genMatchedEta, pfx+"nPhotons");
      _ntuple->Column(pfx+"genMatchedPhi",genMatchedPhi, pfx+"nPhotons");
    }

    _ntuple->Column(pfx+"genMomId",          genMomId,           pfx+"nPhotons");
    _ntuple->Column(pfx+"genMatchedCollId",  genMatchedCollId,   pfx+"nPhotons");
    _ntuple->Column(pfx+"genGrandMomId",     genGrandMomId,      pfx+"nPhotons");
    _ntuple->Column(pfx+"genNSiblings",      genNSiblings,       pfx+"nPhotons");    
    _ntuple->Column(pfx+"genCalIsoDR03",     genCalIsoDR03,      pfx+"nPhotons");
    _ntuple->Column(pfx+"genTrkIsoDR03",     genTrkIsoDR03,      pfx+"nPhotons");
    _ntuple->Column(pfx+"genCalIsoDR04",     genCalIsoDR04,      pfx+"nPhotons");
    _ntuple->Column(pfx+"genTrkIsoDR04",     genTrkIsoDR04,      pfx+"nPhotons");
  }
  
  return (nphotonscounter);
  
}



DEFINE_FWK_MODULE(MultiPhotonAnalyzerTree);
