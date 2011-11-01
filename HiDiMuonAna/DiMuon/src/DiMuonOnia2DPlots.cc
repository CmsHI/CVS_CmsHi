// -*- C++ -*-
//
// Package:    DiMuonOnia2DPlots
// Class:      DiMuonOnia2DPlots
// 
/**\class DiMuonOnia2DPlots DiMuonOnia2DPlots.cc DiMuonAna/DiMuonOnia2DPlots/src/DiMuonOnia2DPlots.cc
   
 Description: [one line class summary]
 
 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Dilep PING, Vineet Kumar, Prashant Shukla
//         Created:  Wed May 12 13:45:14 CEST 2010
// $Id: DiMuonOnia2DPlots.cc,v 1.15 2010/12/05 17:43:18 pshukla Exp $
//
//
// system include files
#include <memory>
#include <map>
#include <string>
#include <TLorentzVector.h>
#include <TNtuple.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>



// user include files   
#include "TH1.h"
#include "TH2.h"
#include "TH2F.h"
#include "TFile.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include <DataFormats/VertexReco/interface/VertexFwd.h>
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"



using std::cout;
using std::endl;

using namespace pat;
using namespace reco;
using namespace edm;
using namespace std;
using namespace HepMC;
using namespace muon;

//
// class declaration
//

class DiMuonOnia2DPlots : public edm::EDAnalyzer {
   public:
  explicit DiMuonOnia2DPlots(const edm::ParameterSet&);
  ~DiMuonOnia2DPlots();

  const CentralityBins *cbins_;
  CentralityProvider *centrality_;    
 

  
  bool fisCuts;  
  std::string fOutputFileName;
  //std::string fGenLevel;
  //std::string fHLTPathName;
  
  std::string fIsGenInfo;
  std::string fIsPATInfo;
  std::string fHLTFilterName;  
  std::string fMotherID;  
 


//edm::InputTag fHLTFilterName;
  

  TFile *In;

  TH1F *Centrality;
  TFile *fOutputFile ;
  
  TTree *SingleMuonTree;
  TTree *SingleGenMuonTree;

  int bin, gbin, rbin;   
  

private:
  
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  virtual bool matchPATMuon(const pat::Muon *pMuon);
  virtual void FillTree(const edm::Event&, const edm::EventSetup&);
  virtual void FillGenTree(const edm::Event&, const edm::EventSetup&);
  math::XYZPoint RefVtx;
  float nPV;
  //Tree variables defined here  
  int eventNb,runNb,lumiBlock;

  //1.) J/psi variables RECO                                                                                                                                     
  //init events                                                                                                                                             
  //int RecJPsiSize, RecMuPlusSize, RecMuMinusSize;

  double JpsiCharge,JpsiNo , JpsiMass , JpsiPt , JpsiRap ,JpsiVprob ;
  double JpsiPx , JpsiPy , JpsiPz ;
  
  

  double RecoCtau,RecoCtauErr,RecoCtauTrue;  
  //TLorentzVector* JpsiP;
 
  //2.) muon variables RECO                                                                                                                                                                                  
  double muPosPx, muPosPy, muPosPz,  muPosEta,  muPosPhi;
  double muNegPx, muNegPy, muNegPz,  muNegEta,  muNegPhi;

  //3.) cut variables

  //(i). Positive Muon                                                                                                            
  double muPos_nchi2In, muPos_dxy, muPos_dz, muPos_nchi2Gl;
  int muPos_found, muPos_pixeLayers, muPos_nValidMuHits,muPos_arbitrated;
  bool muPos_matches, muPos_tracker, muPos_global;  
  //(ii).Negative Muon                                                                                                             
  double muNeg_nchi2In, muNeg_dxy, muNeg_dz, muNeg_nchi2Gl;
  int muNeg_found, muNeg_pixeLayers, muNeg_nValidMuHits,muNeg_arbitrated;
  bool muNeg_matches, muNeg_tracker,muNeg_global;  

  int GeventNb,GrunNb,GlumiBlock;
  //Gen JPsi Variables
  double GenJpsiMass, GenJpsiPt, GenJpsiRap;
  double GenJpsiPx, GenJpsiPy, GenJpsiPz;

  //2.) muon variables Gen                                         
                                                                                                                 
  double GenmuPosPx, GenmuPosPy, GenmuPosPz,  GenmuPosEta, GenmuPosPhi;
  double GenmuNegPx, GenmuNegPy, GenmuNegPz,  GenmuNegEta, GenmuNegPhi;



};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//


DiMuonOnia2DPlots::DiMuonOnia2DPlots(const edm::ParameterSet& iConfig):

  centrality_(0),
  //cbins_(0),
  fisCuts(iConfig.getUntrackedParameter<bool>("IsCuts")),
  fOutputFileName(iConfig.getUntrackedParameter<string>("OutputFileName")),
  fIsGenInfo(iConfig.getUntrackedParameter<string>("IsGenInfo")), 
  fIsPATInfo(iConfig.getUntrackedParameter<string>("IsPATInfo")), 
  fHLTFilterName(iConfig.getUntrackedParameter<string>("HLTFilterName")),
  fMotherID(iConfig.getUntrackedParameter<string>("MotherID"))
  //fHLTFilterName(iConfig.getUntrackedParameter<edm::InputTag>("HLTFilterName"))

{ 

  //now do what ever initialization is needed

}


DiMuonOnia2DPlots::~DiMuonOnia2DPlots()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called to for each event  ------------

void DiMuonOnia2DPlots::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  cout << " ------------------------------------------------------ " << endl;
  using namespace edm;
  using namespace std;
  nPV = 0 ;
  
  centrality_ = new CentralityProvider(iSetup);
  centrality_->newEvent(iEvent,iSetup);
  bin = centrality_->getBin();
  Centrality->Fill(bin);
  
  // Primary Vertex
  Handle<reco::VertexCollection> privtxs;
  iEvent.getByLabel("hiSelectedVertex", privtxs);
  VertexCollection::const_iterator privtx;
  nPV = privtxs->size();
  if(!nPV) return; 
  if ( privtxs->begin() != privtxs->end() ) {
    privtx=privtxs->begin();
   RefVtx = privtx->position();

  } else {
   RefVtx.SetXYZ(0.,0.,0.);
  }
  if(!strcmp(fIsPATInfo.c_str(),"TRUE")){FillTree(iEvent,iSetup);}
  if(!strcmp(fIsGenInfo.c_str(),"TRUE")){FillGenTree(iEvent,iSetup);}

}

// ------------ method called once each job just before starting event loop  ------------
void 
DiMuonOnia2DPlots::beginJob()
{

  edm::Service<TFileService> fs;
  fOutputFile   = new TFile( fOutputFileName.c_str(), "RECREATE" );
  
  cout<<"begin job"<<endl;
  
  SingleMuonTree = new TTree("SingleMuonTree","SingleMuonTree");
  
  // Event variables
  SingleMuonTree->Branch("eventNb",             &eventNb,             "eventNb/I");
  SingleMuonTree->Branch("runNb",               &runNb,               "runNb/I");
  SingleMuonTree->Branch("lumiBlock",           &lumiBlock,           "lumiBlock/I");
  SingleMuonTree->Branch("nPV",                 &nPV,             "nPV/I");
  SingleMuonTree->Branch("rbin",                 &rbin,                  "rbin/I");



  //SingleMuonTree->Branch("RecJPsiSize",   &RecJPsiSize,  "RecJPsiSize/I");  

  // Jpsi Variables dimuon variable.

  //RecJPsiSize  (if we want to put array
  //SingleMuonTree->Branch("JpsiCharge", JpsiCharge,  "JpsiCharge[RecJPsiSize]/D");
  //SingleMuonTree->Branch("JpsiMass",   JpsiMass,  "JpsiMass[RecJPsiSize]/D");
  //SingleMuonTree->Branch("JpsiPt",     JpsiPt,    "JpsiPt[RecJPsiSize]/D");
  //SingleMuonTree->Branch("JpsiRap",    JpsiRap,   "JpsiRap[RecJPsiSize]/D");
  //SingleMuonTree->Branch("JpsiPx",     JpsiPx,    "JpsiPx[RecJPsiSize]/D");
  //SingleMuonTree->Branch("JpsiPy",     JpsiPy,    "JpsiPy[RecJPsiSize]/D");
  //SingleMuonTree->Branch("JpsiPz",     JpsiPz,    "JpsiPz[RecJPsiSize]/D");
  //SingleMuonTree->Branch("JpsiVprob",  JpsiVprob, "JpsiVprob[RecJPsiSize]/D");



  //RecJPsiSize                                                                                                                                                                                    
  SingleMuonTree->Branch("JpsiCharge", &JpsiCharge,  "JpsiCharge/D");
  SingleMuonTree->Branch("JpsiNo", &JpsiNo,  "JpsiNo/D");
  SingleMuonTree->Branch("JpsiMass",   &JpsiMass,  "JpsiMass/D");
  SingleMuonTree->Branch("JpsiPt",     &JpsiPt,    "JpsiPt/D");
  SingleMuonTree->Branch("JpsiRap",    &JpsiRap,   "JpsiRap/D");
  SingleMuonTree->Branch("JpsiPx",     &JpsiPx,    "JpsiPx/D");
  SingleMuonTree->Branch("JpsiPy",     &JpsiPy,    "JpsiPy/D");
  SingleMuonTree->Branch("JpsiPz",     &JpsiPz,    "JpsiPz/D");
  SingleMuonTree->Branch("JpsiVprob",  &JpsiVprob, "JpsiVprob/D");
  SingleMuonTree->Branch("RecoCtau",   &RecoCtau,   "RecoCtau/D");
  SingleMuonTree->Branch("RecoCtauErr", &RecoCtauErr,   "RecoCtauErr/D");
  SingleMuonTree->Branch("RecoCtauTrue", &RecoCtauTrue,   "RecoCtauTrue/D");



  //muon variable
  SingleMuonTree->Branch("muPosPx",    &muPosPx,   "muPosPx/D");
  SingleMuonTree->Branch("muPosPy",    &muPosPy,   "muPosPy/D");
  SingleMuonTree->Branch("muPosPz",    &muPosPz,   "muPosPz/D");
  SingleMuonTree->Branch("muPosEta",    &muPosEta,  "muPosEta/D");
  SingleMuonTree->Branch("muPosPhi",    &muPosPhi,  "muPosPhi/D");
  
  SingleMuonTree->Branch("muNegPx",    &muNegPx,   "muNegPx/D");
  SingleMuonTree->Branch("muNegPy",    &muNegPy,   "muNegPy/D");
  SingleMuonTree->Branch("muNegPz",    &muNegPz,   "muNegPz/D");
  SingleMuonTree->Branch("muNegEta",   &muNegEta,   "muNegEta/D");
  SingleMuonTree->Branch("muNegPhi",   &muNegPhi,   "muNegPhi/D");
 

  //1). Positive Muon                                                                                                                                                                          
  SingleMuonTree->Branch("muPos_nchi2In", &muPos_nchi2In, "muPos_nchi2In/D");
  SingleMuonTree->Branch("muPos_dxy", &muPos_dxy, "muPos_dxy/D");
  SingleMuonTree->Branch("muPos_dz", &muPos_dz, "muPos_dz/D");
  SingleMuonTree->Branch("muPos_nchi2Gl", &muPos_nchi2Gl, "muPos_nchi2Gl/D");
  SingleMuonTree->Branch("muPos_found", &muPos_found, "muPos_found/I");
  SingleMuonTree->Branch("muPos_pixeLayers", &muPos_pixeLayers, "muPos_pixeLayers/I");
  SingleMuonTree->Branch("muPos_nValidMuHits", &muPos_nValidMuHits, "muPos_nValidMuHits/I");
  SingleMuonTree->Branch("muPos_arbitrated", &muPos_arbitrated, "muPos_arbitrated/I");
  SingleMuonTree->Branch("muPos_matches", &muPos_matches, "muPos_matches/O");
  SingleMuonTree->Branch("muPos_tracker", &muPos_tracker, "muPos_tracker/O");
  SingleMuonTree->Branch("muPos_global", &muPos_global, "muPos_global/O");
  



  //2). Negative Muon                                                                                                                                                                          
  SingleMuonTree->Branch("muNeg_nchi2In", &muNeg_nchi2In, "muNeg_nchi2In/D");
  SingleMuonTree->Branch("muNeg_dxy", &muNeg_dxy, "muNeg_dxy/D");
  SingleMuonTree->Branch("muNeg_dz", &muNeg_dz, "muNeg_dz/D");
  SingleMuonTree->Branch("muNeg_nchi2Gl", &muNeg_nchi2Gl, "muNeg_nchi2Gl/D");
  SingleMuonTree->Branch("muNeg_found", &muNeg_found, "muNeg_found/I");
  SingleMuonTree->Branch("muNeg_pixeLayers", &muNeg_pixeLayers, "muNeg_pixeLayers/I");
  SingleMuonTree->Branch("muNeg_nValidMuHits", &muNeg_nValidMuHits, "muNeg_nValidMuHits/I");
  SingleMuonTree->Branch("muNeg_arbitrated", &muNeg_arbitrated, "muNeg_arbitrated/I");
  SingleMuonTree->Branch("muNeg_matches", &muNeg_matches, "muNeg_matches/O");
  SingleMuonTree->Branch("muNeg_tracker", &muNeg_tracker, "muNeg_tracker/O");
  SingleMuonTree->Branch("muNeg_global", &muNeg_global, "muNeg_global/O");





  SingleGenMuonTree = new TTree("SingleGenMuonTree","SingleGenMuonTree");


  // Event variables                                                              
                                                          
  SingleGenMuonTree->Branch("GeventNb",   &GeventNb,       "GeventNb/I");
  SingleGenMuonTree->Branch("GrunNb",     &GrunNb,         "GrunNb/I");
  SingleGenMuonTree->Branch("GlumiBlock", &GlumiBlock,     "GlumiBlock/I");

  //Gen Jpsi Variables                                                                                                                                                        
  SingleGenMuonTree->Branch("GenJpsiMass",   &GenJpsiMass,  "GenJpsiMass/D");
  SingleGenMuonTree->Branch("GenJpsiPt",     &GenJpsiPt,    "GenJpsiPt/D");
  SingleGenMuonTree->Branch("GenJpsiRap",    &GenJpsiRap,   "GenJpsiRap/D");
  SingleGenMuonTree->Branch("GenJpsiPx",     &GenJpsiPx,    "GenJpsiPx/D");
  SingleGenMuonTree->Branch("GenJpsiPy",     &GenJpsiPy,    "GenJpsiPy/D");
  SingleGenMuonTree->Branch("GenJpsiPz",     &GenJpsiPz,    "GenJpsiPz/D");
  SingleGenMuonTree->Branch("gbin",          &gbin,             "gbin/I");

  //muon variable
  SingleGenMuonTree->Branch("GenmuPosPx",    &GenmuPosPx,   "GenmuPosPx/D");
  SingleGenMuonTree->Branch("GenmuPosPy",    &GenmuPosPy,   "GenmuPosPy/D");
  SingleGenMuonTree->Branch("GenmuPosPz",    &GenmuPosPz,   "GenmuPosPz/D");
  SingleGenMuonTree->Branch("GenmuPosEta",    &GenmuPosEta,   "GenmuPosEta/D");
  SingleGenMuonTree->Branch("GenmuPosPhi",    &GenmuPosPhi,   "GenmuPosPhi/D");
  
  SingleGenMuonTree->Branch("GenmuNegPx",    &GenmuNegPx,   "GenmuNegPx/D");
  SingleGenMuonTree->Branch("GenmuNegPy",    &GenmuNegPy,   "GenmuNegPy/D");
  SingleGenMuonTree->Branch("GenmuNegPz",    &GenmuNegPz,   "GenmuNegPz/D");
  SingleGenMuonTree->Branch("GenmuNegEta",    &GenmuNegEta,   "GenmuNegEta/D");
  SingleGenMuonTree->Branch("GenmuNegPhi",    &GenmuNegPhi,   "GenmuNegPhi/D");



  cout<<"Tree booked "<<endl;


  //Histograms       
  Centrality = new TH1F("Centrality","Centrality", 60,-10,50);
   
  //h_ZetaGen_ = genParticleDir.make<TH1D>("generatedZeta","#eta of generated Z",100,-5.,5.); 

  // Write comments in a file
}



// ------------ method called once each job just after ending the event loop  ------------
void DiMuonOnia2DPlots::endJob() 
{
  cout<<"End Job"<<endl;
  fOutputFile->cd();
  SingleMuonTree->Write();
  SingleGenMuonTree->Write();
  Centrality->Write(); 
  fOutputFile->Close();

}



bool DiMuonOnia2DPlots::matchPATMuon(const pat::Muon *pMuon) 
{
  return(
	 //to match with filter name
	 //(!pMuon->triggerObjectMatchesByFilter(fHLTFilterName).empty())  
	 //to match with trigger name
	 //!pMuon->triggerObjectMatchesByPath("HLT_HIL1DoubleMuOpen").empty()
	 !pMuon->triggerObjectMatchesByPath(fHLTFilterName).empty()
	 );
}

void DiMuonOnia2DPlots::FillTree(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  //init events
  //RecJPsiSize=0;
  //reset J/psi RECO variables
  JpsiNo=-9999.;
  JpsiCharge=-9999.;
  JpsiMass=-9999.;
  JpsiPt=-9999.;
  JpsiRap=-9999.;
  JpsiVprob=-9999.;
  JpsiPx=-9999.;
  JpsiPy=-9999.;
  JpsiPz=-9999.;
  RecoCtau=-9999;
  RecoCtauErr=-9999;
  RecoCtauTrue=-9999;

  
  
  muPosPx=-9999.;
  muPosPy=-9999.;
  muPosPz=-9999.;
  muPosEta=-9999.;
  muPosPhi=-9999.;
  
  muNegPx=-9999.;
  muNegPy=-9999.;
  muNegPz=-9999.;
  muNegEta=-9999.;
  muNegPhi=-9999.;

  
//1).Positive Muon                                                                                                                                                                                                                         
  muPos_nchi2In=-9999.;
  muPos_dxy=-9999.;
  muPos_dz=-9999.;
  muPos_nchi2Gl=-9999.;
  muPos_found=-9999;
  muPos_pixeLayers=-9999;
  muPos_nValidMuHits=-9999;
  muPos_arbitrated=-9999;
  muPos_matches=0;
  muPos_tracker=0;
  muPos_global=0;

  //2).Negtive Muon                                                                                                                                                                                                                          
  muNeg_nchi2In=-9999.;
  muNeg_dxy=-9999.;
  muNeg_dz=-9999.;
  muNeg_nchi2Gl=-9999.;
  muNeg_found=-9999;
  muNeg_pixeLayers=-9999;
  muNeg_nValidMuHits=-9999;
  muNeg_arbitrated=-9999;
  muNeg_matches=0;
  muNeg_tracker=0;
  muNeg_global=0;

  //reset EVENT information                                                                                                                                                                                                                    
  eventNb= 0 ;
  runNb= 0 ;
  lumiBlock= 0 ;
  rbin=0;

 // Event related infos
  eventNb= iEvent.id().event();
  runNb=iEvent.id().run();
  lumiBlock= iEvent.luminosityBlock();

  centrality_ = new CentralityProvider(iSetup);
  centrality_->newEvent(iEvent,iSetup);
  rbin = centrality_->getBin();
  
  cout<<" rbin "<<rbin<<endl;

  //--------------------------------------Reco DimuonGlobal ---------------------------------------------------------------------

  using namespace edm;
  using namespace std;
  using namespace pat;

  edm::Handle<edm::View<pat::CompositeCandidate> > diMuonsPATCand;
  iEvent.getByLabel("onia2MuMuPatGlbGlb", diMuonsPATCand);
  if(!(diMuonsPATCand.isValid())) return;
  edm::View<pat::CompositeCandidate>dimuonsPATColl= *diMuonsPATCand;
  JpsiNo=dimuonsPATColl.size();
  cout<<" reco Jpsi size : "<<dimuonsPATColl.size()<<endl;
                                                                                                                                           
  
  for(size_t ii = 0; ii <dimuonsPATColl.size(); ++ ii) 
    {
    const pat::CompositeCandidate &p = (dimuonsPATColl)[ii];
    const reco::Candidate *dau0 = p.daughter(0);
    const pat::Muon *mu0 = dynamic_cast<const pat::Muon *>(dau0);
    const reco::Candidate *dau1 = p.daughter(1); 
    const pat::Muon *mu1 = dynamic_cast<const pat::Muon *>(dau1);
    const pat::Muon *muonPos = 0, *muonNeg = 0;
    
    if(mu0->charge() > 0){ muonPos = mu0; muonNeg = mu1;}
    else if(mu0->charge() < 0){ muonPos = mu1; muonNeg = mu0;}
    
    //---------------------------------------- Trigger Matches -----------------------------------------//
    
    //to match with filter name                                                                                                                                              
    //(!pMuon->triggerObjectMatchesByFilter(fHLTFilterName).empty())                                                                                                         
    //to match with trigger name                                                                                                                                             
    //!pMuon->triggerObjectMatchesByPath("HLT_HIL1DoubleMuOpen").empty()                                                                                                     
    //!pMuon->triggerObjectMatchesByPath(fHLTFilterName).empty()
    
    //TriggerResultsLabel = cms.InputTag("TriggerResults","","HLT")
    
    cout<< !muonPos->triggerObjectMatchesByPath("HLT_HIL1DoubleMuOpen").empty()  <<" matches "<<!muonNeg->triggerObjectMatchesByPath("HLT_HIL1DoubleMuOpen").empty()<<endl;                                                                                                                                                                                                                  
    
      
    //Trigger matches        
    //cout<<matchPATMuon(muonPos)<<" matches "<<matchPATMuon(muonNeg)<<endl;                                                                                                                                                                                                                  
    if(!muonPos->triggerObjectMatchesByPath("HLT_HIL1DoubleMuOpen").empty()) {muPos_matches=1;}
    if(!muonNeg->triggerObjectMatchesByPath("HLT_HIL1DoubleMuOpen").empty()) {muNeg_matches=1;}

    
    if(muonPos->isTrackerMuon()){muPos_tracker=1;}
    if(muonNeg->isTrackerMuon()){muNeg_tracker=1;}

    if(muonPos->isGlobalMuon()){muPos_global=1;}
    if(muonNeg->isGlobalMuon()){muNeg_global=1;}


    cout<<muPos_tracker<<"    "<<muNeg_tracker<<endl;
    cout<<"muPos_matches "<<muPos_matches<<" muNeg_matches "<<muNeg_matches<<endl; 
    cout<<"JpsiCharge " <<p.charge()<<" JpsiMass  "<<p.mass()<<endl;
    

    // write out JPsi RECO information
    //cout<<" inside loop RecJPsiSize "<<RecJPsiSize<<endl;
   
    JpsiCharge  = p.charge();
    JpsiMass =p.mass();
    JpsiPt =p.pt();
    JpsiRap =p.rapidity();
    JpsiPx =p.px();
    JpsiPy =p.py();
    JpsiPz =p.pz();

    JpsiVprob =p.userFloat("vProb");

    RecoCtau=10.0*p.userFloat("ppdlPV");
    RecoCtauErr=10.0*p.userFloat("ppdlErrPV");
    RecoCtauTrue=10.*p.userFloat("ppdlTrue");

    
    // write out Muon RECO information                                                                                                                                                                                                     
    float f_muPosPx, f_muPosPy, f_muPosPz, f_muPosEta, f_muPosPhi;
    float f_muNegPx, f_muNegPy, f_muNegPz, f_muNegEta, f_muNegPhi;
    
    f_muPosPx = muonPos->px();
    f_muPosPy = muonPos->py();
    f_muPosPz = muonPos->pz();
    f_muPosEta = muonPos->eta();
    f_muPosPhi= muonPos->phi();

    f_muNegPx = muonNeg->px();
    f_muNegPy = muonNeg->py();
    f_muNegPz = muonNeg->pz();
    f_muNegEta = muonNeg->eta();
    f_muNegPhi = muonNeg->phi();

    muPosPx= f_muPosPx ;
    muPosPy= f_muPosPy ;
    muPosPz= f_muPosPz ;
    muPosEta= f_muPosEta;
    muPosPhi= f_muPosPhi;
    
    muNegPx= f_muNegPx ;
    muNegPy= f_muNegPy ;
    muNegPz= f_muNegPz ;
    muNegEta= f_muNegEta;
    muNegPhi= f_muNegPhi;

    //-----------------------------------------------------                                                                                                                                                                                
    //-----------additional Reco Muon Variables------------                                                                                                                                                                                
    //----------------------------------------------------- 



    //1.Positive Muon                                                                                                                                                                                                                      
    if(muonPos->isTrackerMuon())
      {
	TrackRef iTrack =muonPos->innerTrack();
	const reco::HitPattern& p1=iTrack->hitPattern();
	muPos_found=iTrack->found();
	muPos_nchi2In=iTrack->chi2()/iTrack->ndof();
	muPos_arbitrated=muonPos->muonID("TrackerMuonArbitrated");
	muPos_pixeLayers=p1.pixelLayersWithMeasurement();
	muPos_dxy=iTrack->dxy(RefVtx);
	muPos_dz=iTrack->dz(RefVtx);
	if(muonPos->isGlobalMuon())
	  {
	    TrackRef gTrack =muonPos->globalTrack();
	    const reco::HitPattern& q1=gTrack->hitPattern();
	    muPos_nValidMuHits=q1.numberOfValidMuonHits();
	    muPos_nchi2Gl=gTrack->chi2()/gTrack->ndof();
	  }
      }



    //2.Negative Muobn                                                                                                                                                                                                                     
    if(muonNeg->isTrackerMuon())
      {
	TrackRef iTrack =muonNeg->innerTrack();
	const reco::HitPattern& p2=iTrack->hitPattern();
	muNeg_found=iTrack->found();
	muNeg_nchi2In=iTrack->chi2()/iTrack->ndof();
	muNeg_arbitrated=muonNeg->muonID("TrackerMuonArbitrated");
	muNeg_pixeLayers=p2.pixelLayersWithMeasurement();
	muNeg_dxy=iTrack->dxy(RefVtx);
	muNeg_dz=iTrack->dz(RefVtx);
	
	if(muonNeg->isGlobalMuon())
	  {
	    TrackRef gTrack =muonNeg->globalTrack();
	    const reco::HitPattern& q2=gTrack->hitPattern();
	    muNeg_nValidMuHits=q2.numberOfValidMuonHits();
	    muNeg_nchi2Gl=gTrack->chi2()/gTrack->ndof();
	  }
      }     
    
    SingleMuonTree->Fill();
    //RecJPsiSize++;
    //cout<<"RecJPsiSiZe " <<RecJPsiSize<<endl;
    }
  
   cout<<" fill tree called "<<endl;

}

void DiMuonOnia2DPlots::FillGenTree(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  GenJpsiMass=-9999.;
  GenJpsiPt=-9999.;
  GenJpsiRap=-9999.;
  GenJpsiPx=-9999.;
  GenJpsiPy=-9999.;
  GenJpsiPz=-9999.;
  
  GenmuPosPx=-9999.;
  GenmuPosPy=-9999.;
  GenmuPosPz=-9999.;
  GenmuPosEta=-9999.;
  GenmuPosPhi=-9999.;
  
  GenmuNegPx=-9999.;
  GenmuNegPy=-9999.;
  GenmuNegPz=-9999.;
  GenmuNegEta=-9999.; 
  GenmuNegPhi=-9999.; 


  //reset EVENT information  
    GeventNb= 0 ;
    GrunNb= 0 ;
    GlumiBlock= 0 ;
    gbin=0;

    // Event related infos 
                                                                                                                    
    GeventNb= iEvent.id().event();
    GrunNb=iEvent.id().run();
    GlumiBlock= iEvent.luminosityBlock();


    centrality_ = new CentralityProvider(iSetup);
    centrality_->newEvent(iEvent,iSetup);
    gbin = centrality_->getBin();
    cout<<" gbin "<<gbin<<endl;


  //-----------------------------------------------------hiGenParticle----------------------------------------------------------------------

  float mumass =0.105658389;
  using namespace edm;
  using namespace std;
  
  edm::Handle<edm::View<reco::GenParticle> >genPar;
  iEvent.getByLabel("hiGenParticles",genPar) ;
  //iEvent.getByLabel("genMuons",genPar) ;
 

  if(!(genPar.isValid())) return;


  edm::View<reco::GenParticle> genParticles = *genPar ;
  TLorentzVector  genvector1, genvector2;
  
  double px1[10000], py1[10000], pz1[10000], px2[10000], py2[10000], pz2[10000];
  unsigned int nplus = 0, nminus =0;

  for(size_t i = 0; i < genParticles.size(); ++ i) {
    const reco::GenParticle& part = (*genPar)[i];
    const  Candidate *mom = part.mother();

   
    if (part.numberOfMothers()!=1) continue;
    int momId = mom->pdgId();

    //!strcmp(fIsPATInfo.c_str(),"TRUE")

    char* MID=(char*)"AB";

    if(momId == 443) MID=(char *)"JPsi";
    if(momId == 553) MID=(char *)"Upsilon1s";
    if(momId == 100553)MID=(char *)"Upsilon2s";


    //cout<<"momId "<<momId<<endl;
    //JPsi
    
    if ((abs(part.pdgId()) == 13) && ( !strcmp(fMotherID.c_str(),MID)) ){
        
    //if (abs(part.pdgId()) == 13 &&  momId == 443){
   //Upsilon 1s
    // if (abs(part.pdgId()) == 13 &&  momId == 553){
   //Upsilon 2s
    //if (abs(part.pdgId()) == 13 &&  momId == 100553){

      

      if(part.pdgId() == 13 ){
        px1[nplus] = part.px();
	py1[nplus] = part.py();
        pz1[nplus] = part.pz();
	nplus++;
	
	GenmuNegPx=part.px();
	GenmuNegPy=part.py();
	GenmuNegPz=part.pz();
	GenmuNegEta=part.eta();
	GenmuNegPhi=part.phi();
      
	cout<<"motherID "<<MID<<endl;


      }
      
      if(part.pdgId()== -13) {
        px2[nminus] = part.px();
        py2[nminus] = part.py();
        pz2[nminus] = part.pz();
      	nminus++;
      
	GenmuPosPx=part.px();
	GenmuPosPy=part.py();
	GenmuPosPz=part.pz();
	GenmuPosEta=part.eta();
	GenmuPosPhi=part.phi();

      }
    }
  }
  cout<<" nplus : "<<nplus<<"  "<<nminus<<endl;
  
  for(size_t i = 0; i < nplus; i++) {
    double en1 = sqrt(px1[i]*px1[i] + py1[i]*py1[i] + pz1[i]*pz1[i] + mumass*mumass);
    
    for(size_t j = 0; j< nminus; j++) {
      double en2 = sqrt(px2[j]*px2[j] + py2[j]*py2[j] + pz2[j]*pz2[j] + mumass*mumass);
      TLorentzVector  genvector1,genvector2,genvector3;
      
      genvector1.SetPxPyPzE(px1[i], py1[i], pz1[i], en1);
      genvector2.SetPxPyPzE(px2[j], py2[j], pz2[j], en2);
      
      genvector3=genvector1+genvector2;
      
      double GenDiMuonY=genvector3.Rapidity();
      double GenDiMuonMinv=genvector3.M();
      double GenDiMuonPt =genvector3.Pt();
      double GenDiMuonPx=genvector3.Px();
      double GenDiMuonPy=genvector3.Py();
      double GenDiMuonPz=genvector3.Pz();

      cout<<" gen mass "<< GenDiMuonMinv   <<" pT "<< GenDiMuonPt<<endl; 
      GenJpsiMass=GenDiMuonMinv;
      GenJpsiPt=GenDiMuonPt;
      GenJpsiRap=GenDiMuonY;
      GenJpsiPx=GenDiMuonPx;
      GenJpsiPy=GenDiMuonPy;
      GenJpsiPz=GenDiMuonPz;
      
      SingleGenMuonTree->Fill();
      //cout<<"gen Tree Filled "<<endl;

    }
  }

}

//----------------------------------------- HepMC -----------------------------------------------------------------------------
/*
  using namespace HepMC;
  using namespace edm;
  edm::Handle<HepMCProduct> evt;
  iEvent.getByLabel("generator", evt);
  const HepMC::GenEvent *genEvent = evt->GetEvent();

  float pt1[100], eta1[100], phi1[100], ppx1[100], ppy1[100], ppz1[100],ener1[100];
  float pt2[100], eta2[100], phi2[100],ppx2[100], ppy2[100], ppz2[100],ener2[100];
  int imuplus=0, imuminus=0;
  int nmp=0;
  int nmn=0;
  const float muonmass = 0.105658369; //  GeV                                                                                                                                                    
  for (HepMC::GenEvent::particle_const_iterator p = genEvent->particles_begin();
  p != genEvent->particles_end(); ++p) {
  
  int ID     = (*p)->pdg_id();
  float eta = (*p)->momentum().eta();
  float phi = (*p)->momentum().phi();
  float pt = (*p)->momentum().perp();
  float px = (*p)->momentum().px();
  float py = (*p)->momentum().py();
  float pz = (*p)->momentum().pz();
  float ener=sqrt((px*px+py*py+pz*pz+muonmass*muonmass));
  
  if(ID==-13) {
  pt1[imuplus] = pt;
  eta1[imuplus] = eta;
  phi1[imuplus] = phi;
  ppx1[imuplus]=px;
  ppy1[imuplus]=py;
  ppz1[imuplus]=pz;
  ener1[imuplus]=ener;
  
  GenmuPosPx=px;
  GenmuPosPy=py;
  GenmuPosPz=pz;
  GenmuPosEta=eta;
  
  imuplus++;
  nmp++;
  }
  
  
  if(ID==13) {
  pt2[imuminus] = pt;
  eta2[imuminus] = eta;
  phi2[imuminus] = phi;
  ppx2[imuminus]=px;
  ppy2[imuminus]=py;
  ppz2[imuminus]=pz;
  ener2[imuminus]=ener;
  
  GenmuNegPx=px;
  GenmuNegPy=py;
  GenmuNegPz=pz;
  GenmuNegEta=eta;
  imuminus++;
  nmn++;
  }
  
  }//genrated particle loop 

  if(nmp>0 && nmn>0){
  // fill muon properties and do 2-mu inv.mass                                                                                                                                                 
  for (  int i=0; i< imuplus; i++ ) {
  for (  int j=0; j< imuminus; j++ ){
  double eptot=ener1[i]+ener2[j];
  double ppxtot=ppx1[i]+ppx2[j];
  double ppytot=ppy1[i]+ppy2[j];
  double ppztot=ppz1[i]+ppz2[j];
  double genupt=sqrt((ppxtot*ppxtot)+(ppytot*ppytot));
  double genuy=0.5*(log((eptot+ppztot)/(eptot-ppztot)));
  double minv = TMath::Sqrt(eptot*eptot - (ppxtot*ppxtot + ppytot*ppytot + ppztot*ppztot) );	
  
  GenJpsiMass=minv;
  GenJpsiPt=genupt;
  GenJpsiRap=genuy;
  GenJpsiPx=ppxtot;
  GenJpsiPy=ppytot;
  GenJpsiPz=ppztot;
  } // for j				
  } // for i				      
  
      SingleGenMuonTree->Fill();
      cout<<" Gen loop "<<endl;
      
  }// if      
  */
  

//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonOnia2DPlots);



