// -*- C++ -*-
//
// Package:    DiMuonUPCTree
// Class:      DiMuonUPCTree
// 
/**\class DiMuonUPCTree DiMuonUPCTree.cc DiMuonAna/DiMuonUPCTree/src/DiMuonUPCTree.cc
   
 Description: [one line class summary]
 
 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Dilep PING, Vineet Kumar, Prashant Shukla
//         Created:  Wed May 12 13:45:14 CEST 2010
// $Id: DiMuonUPCTree.cc,v 1.15 2010/12/05 17:43:18 pshukla Exp $
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

class DiMuonUPCTree : public edm::EDAnalyzer {
   public:
  explicit DiMuonUPCTree(const edm::ParameterSet&);
  ~DiMuonUPCTree();

  const CentralityBins *cbins_;
  CentralityProvider *centrality_;    
 
 
  bool fisCuts;  
  std::string fOutputFileName;
  std::string fIsGenInfo;
  std::string fIsPATInfo;
  std::string fHLTFilterName;  
  std::string fMotherID;  

  //TFile *In;

  TH1F *Centrality;
  TFile *fOutputFile ;
  TTree *EventTree;
  
  int bin, rbin;

private:
  
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void FillTree(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  math::XYZPoint RefVtx;
  float nPV;
  int nDiMuon;

  //Tree variables defined here  
  int eventNb,runNb,lumiBlock, trackNb;
  int DiMuSize;
  double DiMuCharge[100],DiMuNo[100], DiMuMass[100] , DiMuPt[100], DiMuRap[100];
  double DiMuPx[100], DiMuPy[100], DiMuPz[100];



  double Mu1Charge[100],Mu1No[100], Mu1Mass[100] , Mu1Pt[100], Mu1Eta[100];
  double Mu1Px[100], Mu1Py[100], Mu1Pz[100], Mu1Phi[100];
  double Mu1_nchi2In[100], Mu1_dxy[100], Mu1_dz[100], Mu1_nchi2Gl[100];
  int Mu1_found[100], Mu1_pixeLayers[100], Mu1_nValidMuHits[100],Mu1_arbitrated[100];
  int Mu1_tracker[100], Mu1_global[100], Mu1_standalone[100];
  int Mu1_trigger1[100],Mu1_trigger2[100],Mu1_trigger3[100];

  double Mu2Charge[100],Mu2No[100], Mu2Mass[100] , Mu2Pt[100], Mu2Eta[100];
  double Mu2Px[100], Mu2Py[100], Mu2Pz[100], Mu2Phi[100];
  double Mu2_nchi2In[100], Mu2_dxy[100], Mu2_dz[100], Mu2_nchi2Gl[100];
  int Mu2_found[100], Mu2_pixeLayers[100], Mu2_nValidMuHits[100],Mu2_arbitrated[100];
  int Mu2_tracker[100], Mu2_global[100], Mu2_standalone[100];

  int Mu2_trigger1[100],Mu2_trigger2[100],Mu2_trigger3[100];

  //track variables
  //double Mu2Px[100], Mu2Py[100], Mu2Pz[100], Mu2Phi[100];




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


DiMuonUPCTree::DiMuonUPCTree(const edm::ParameterSet& iConfig):

  centrality_(0),
  //cbins_(0),
  fisCuts(iConfig.getUntrackedParameter<bool>("IsCuts")),
  fOutputFileName(iConfig.getUntrackedParameter<string>("OutputFileName")),
  fIsGenInfo(iConfig.getUntrackedParameter<string>("IsGenInfo")), 
  fIsPATInfo(iConfig.getUntrackedParameter<string>("IsPATInfo")), 
  fHLTFilterName(iConfig.getUntrackedParameter<string>("HLTFilterName")),
  fMotherID(iConfig.getUntrackedParameter<string>("MotherID"))
  

{ 

//now do what ever initialization is needed

}


DiMuonUPCTree::~DiMuonUPCTree()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
DiMuonUPCTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //cout << " ------------------------------------------------------ " << endl;
  using namespace edm;
  using namespace std;
  
  nPV = 0 ;
  
  centrality_ = new CentralityProvider(iSetup);
  centrality_->newEvent(iEvent,iSetup);
  bin = centrality_->getBin();
  Centrality->Fill(bin);
  if(!strcmp(fIsPATInfo.c_str(),"TRUE")){FillTree(iEvent,iSetup);}
  
  if(nDiMuon>0 && nDiMuon <100) {EventTree->Fill();}

}

// ------------ method called once each job just before starting event loop  ------------
void 
DiMuonUPCTree::beginJob()
{
  edm::Service<TFileService> fs;
  fOutputFile   = new TFile( fOutputFileName.c_str(), "RECREATE" );
  cout<<"begin job"<<endl;
  EventTree = new TTree("EventTree","EventTree");
  // Event variables
  EventTree->Branch("eventNb",             &eventNb,             "eventNb/I");
  EventTree->Branch("runNb",               &runNb,               "runNb/I");
  EventTree->Branch("lumiBlock",           &lumiBlock,           "lumiBlock/I");
  EventTree->Branch("rbin",                 &rbin,                  "rbin/I");
  EventTree->Branch("trackNb",             &trackNb,             "trackNb/I");
//DiMuon variables
  EventTree->Branch("DiMuSize",   &DiMuSize,  "DiMuSize/I");  
  EventTree->Branch("DiMuCharge", DiMuCharge,  "DiMuCharge[DiMuSize]/D");
  EventTree->Branch("DiMuMass",   DiMuMass,  "DiMuMass[DiMuSize]/D");
  EventTree->Branch("DiMuPt",     DiMuPt,    "DiMuPt[DiMuSize]/D");
  EventTree->Branch("DiMuRap",    DiMuRap,   "DiMuRap[DiMuSize]/D");
  EventTree->Branch("DiMuPx",     DiMuPx,    "DiMuPx[DiMuSize]/D");
  EventTree->Branch("DiMuPy",     DiMuPy,    "DiMuPy[DiMuSize]/D");
  EventTree->Branch("DiMuPz",     DiMuPz,    "DiMuPz[DiMuSize]/D");
  
  //Muon1 variables
  EventTree->Branch("Mu1Charge", Mu1Charge,  "Mu1Charge[DiMuSize]/D");
  EventTree->Branch("Mu1Mass",   Mu1Mass,  "Mu1Mass[DiMuSize]/D");
  EventTree->Branch("Mu1Pt",     Mu1Pt,    "Mu1Pt[DiMuSize]/D");
  EventTree->Branch("Mu1Eta",    Mu1Eta,   "Mu1Eta[DiMuSize]/D");
  EventTree->Branch("Mu1Px",     Mu1Px,    "Mu1Px[DiMuSize]/D");
  EventTree->Branch("Mu1Py",     Mu1Py,    "Mu1Py[DiMuSize]/D");
  EventTree->Branch("Mu1Pz",     Mu1Pz,    "Mu1Pz[DiMuSize]/D");
  EventTree->Branch("Mu1Phi",     Mu1Phi,    "Mu1Phi[DiMuSize]/D");
  //Muon1 cut variables
  EventTree->Branch("Mu1_nchi2In",  Mu1_nchi2In, "Mu1_nchi2In[DiMuSize]/D");
  EventTree->Branch("Mu1_dxy",  Mu1_dxy, "Mu1_dxy[DiMuSize]/D");
  EventTree->Branch("Mu1_dz",  Mu1_dz, "Mu1_dz[DiMuSize]/D");
  EventTree->Branch("Mu1_nchi2Gl",  Mu1_nchi2Gl, "Mu1_nchi2Gl[DiMuSize]/D");
  EventTree->Branch("Mu1_found",  Mu1_found, "Mu1_found[DiMuSize]/I");
  EventTree->Branch("Mu1_pixeLayers",  Mu1_pixeLayers, "Mu1_pixeLayers[DiMuSize]/I");
  EventTree->Branch("Mu1_nValidMuHits",  Mu1_nValidMuHits, "Mu1_nValidMuHits[DiMuSize]/I");
  EventTree->Branch("Mu1_arbitrated",  Mu1_arbitrated, "Mu1_arbitrated[DiMuSize]/I");

  EventTree->Branch("Mu1_tracker",  Mu1_tracker, "Mu1_tracker[DiMuSize]/I");
  EventTree->Branch("Mu1_global",  Mu1_global, "Mu1_global[DiMuSize]/I");
  EventTree->Branch("Mu1_standalone",  Mu1_standalone, "Mu1_standalone[DiMuSize]/I");

  EventTree->Branch("Mu1_trigger1",  Mu1_trigger1, "Mu1_trigger1[DiMuSize]/I");
  EventTree->Branch("Mu1_trigger2",  Mu1_trigger2, "Mu1_trigger2[DiMuSize]/I");
  EventTree->Branch("Mu1_trigger3",  Mu1_trigger3, "Mu1_trigger3[DiMuSize]/I");
  
  //EventTree->Branch("Mu1_trigger4",  Mu1_trigger4, "Mu1_trigger4[DiMuSize]/I");
  //EventTree->Branch("Mu1_trigger5",  Mu1_trigger5, "Mu1_trigger5[DiMuSize]/I");
  //EventTree->Branch("Mu1_trigger6",  Mu1_trigger6, "Mu1_trigger6[DiMuSize]/I");
  //EventTree->Branch("Mu1_trigger7",  Mu1_trigger7, "Mu1_trigger7[DiMuSize]/I");
  //EventTree->Branch("Mu1_trigger8",  Mu1_trigger8, "Mu1_trigger8[DiMuSize]/I");



 //Muon2 variables
  EventTree->Branch("Mu2Charge", Mu2Charge,  "Mu2Charge[DiMuSize]/D");
  EventTree->Branch("Mu2Mass",   Mu2Mass,  "Mu2Mass[DiMuSize]/D");
  EventTree->Branch("Mu2Pt",     Mu2Pt,    "Mu2Pt[DiMuSize]/D");
  EventTree->Branch("Mu2Eta",    Mu2Eta,   "Mu2Eta[DiMuSize]/D");
  EventTree->Branch("Mu2Px",     Mu2Px,    "Mu2Px[DiMuSize]/D");
  EventTree->Branch("Mu2Py",     Mu2Py,    "Mu2Py[DiMuSize]/D");
  EventTree->Branch("Mu2Pz",     Mu2Pz,    "Mu2Pz[DiMuSize]/D");
  EventTree->Branch("Mu2Phi",     Mu2Phi,    "Mu2Phi[DiMuSize]/D");
  //Muon2 cut variables                                                                                                                                                                                         
  EventTree->Branch("Mu2_nchi2In",  Mu2_nchi2In, "Mu2_nchi2In[DiMuSize]/D");
  EventTree->Branch("Mu2_dxy",  Mu2_dxy, "Mu2_dxy[DiMuSize]/D");
  EventTree->Branch("Mu2_dz",  Mu2_dz, "Mu2_dz[DiMuSize]/D");
  EventTree->Branch("Mu2_nchi2Gl",  Mu2_nchi2Gl, "Mu2_nchi2Gl[DiMuSize]/D");
  EventTree->Branch("Mu2_found",  Mu2_found, "Mu2_found[DiMuSize]/I");
  EventTree->Branch("Mu2_pixeLayers",  Mu2_pixeLayers, "Mu2_pixeLayers[DiMuSize]/I");
  EventTree->Branch("Mu2_nValidMuHits",  Mu2_nValidMuHits, "Mu2_nValidMuHits[DiMuSize]/I");
  EventTree->Branch("Mu2_arbitrated",  Mu2_arbitrated, "Mu2_arbitrated[DiMuSize]/I");
  EventTree->Branch("Mu2_tracker",  Mu2_tracker, "Mu2_tracker[DiMuSize]/I");
  EventTree->Branch("Mu2_global",  Mu2_global, "Mu2_global[DiMuSize]/I");
  EventTree->Branch("Mu2_standalone",  Mu2_standalone, "Mu2_standalone[DiMuSize]/I");


  EventTree->Branch("Mu2_trigger1",  Mu2_trigger1, "Mu2_trigger1[DiMuSize]/I");
  EventTree->Branch("Mu2_trigger2",  Mu2_trigger2, "Mu2_trigger2[DiMuSize]/I");
  EventTree->Branch("Mu2_trigger3",  Mu2_trigger3, "Mu2_trigger3[DiMuSize]/I");


  
  cout<<"Tree booked "<<endl;
  
  //Histograms       
  Centrality = new TH1F("Centrality","Centrality", 60,-10,50);
   


  // Write comments in a file
}



// ------------ method called once each job just after ending the event loop  ------------
void DiMuonUPCTree::endJob() 
{


  //In->Close();
  cout<<"End Job"<<endl;
  fOutputFile->cd();
  EventTree->Write();
  Centrality->Write(); 
  fOutputFile->Close();
}

void DiMuonUPCTree::FillTree(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{


  using namespace edm;
  using namespace std;
  using namespace reco;


  using reco::TrackCollection;
  using reco::MuonCollection;
  
  float massMu=0.105658;
  //reset EVENT information
  eventNb= 0 ;
  runNb= 0 ;
  lumiBlock= 0 ;
  rbin=0;
  DiMuSize=0;

  // Event related infos
  eventNb= iEvent.id().event();
  runNb=iEvent.id().run();
  lumiBlock= iEvent.luminosityBlock();
  
  centrality_ = new CentralityProvider(iSetup);
  centrality_->newEvent(iEvent,iSetup);
  rbin = centrality_->getBin();
  //cout<<" rbin "<<rbin<<endl;


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

  
  //====================================================================================

  // get muon collection                                                                                                                                       
  edm::Handle<edm::View<pat::Muon> >Muons;
  iEvent.getByLabel("patMuons",Muons);
  edm::View<pat::Muon>MuonColl=*Muons;
  int MuonSize =MuonColl.size();
  cout<<" no of pat muons : "<<MuonSize<<endl;  

  for ( int i=0 ; i < MuonSize ; ++i ){
    const pat::Muon& aMuon = (*Muons)[i];
    //if (aMuon.isNull() ) continue;
    for ( int j=i+1 ; j < MuonSize ; ++j){
      const pat::Muon& bMuon = (*Muons)[j];
      if(MuonSize>10) return;

      //if (bMuon.isNull() ) continue;
      //====================================================================================
      //Muon coolection  
      //edm::Handle<edm::View<reco::Muon> >tmuons;
      //iEvent.getByLabel("muons", tmuons);
      //int MuonSize =tmuons->size();
      // for(unsigned int i = 0; i <tmuons->size(); ++i){
      //    <pat::Muon> aMuon(tmuons, i);
      //if (aMuon.isNull() ) continue;
      
      //for(unsigned int j = i+1; j<tmuons->size(); ++j) {
      //edm::RefToBase<pat::Muon> bMuon(tmuons, j);
      //if (bMuon.isNull() ) continue;
      //cout<< "aMuon.px() "<<aMuon.px()<<endl;
      TVector3 vmuon1(aMuon.px(),aMuon.py(),aMuon.pz());
      float muon1_e =sqrt((vmuon1.Mag()*vmuon1.Mag())+(massMu*massMu));
      TLorentzVector lmuon1(vmuon1,muon1_e);
      
      //cout<< "bMuon.px() "<<bMuon.px()<<endl;
      TVector3 vmuon2(bMuon.px(),bMuon.py(),bMuon.pz());
      float muon2_e =sqrt((vmuon2.Mag()*vmuon2.Mag())+(massMu*massMu));
      TLorentzVector lmuon2(vmuon2,muon2_e);
      
      TLorentzVector dimuon = lmuon1+lmuon2;
      
      int Charge=aMuon.charge()+bMuon.charge();
      DiMuMass[DiMuSize]= dimuon.M();
      DiMuPt[DiMuSize]=dimuon.Pt();     
      DiMuRap[DiMuSize]=dimuon.Rapidity();
      DiMuPx[DiMuSize]=dimuon.Px();
      DiMuPy[DiMuSize]=dimuon.Py();
      DiMuPz[DiMuSize]=dimuon.Pz();
      DiMuCharge[DiMuSize]=Charge;
      
      
      Mu1Pt[DiMuSize]=aMuon.pt();
      Mu1Eta[DiMuSize]=aMuon.eta();
      Mu1Px[DiMuSize]=aMuon.px();
      Mu1Py[DiMuSize]=aMuon.py();
      Mu1Pz[DiMuSize]=aMuon.pz();
      Mu1Phi[DiMuSize]=aMuon.phi();
      Mu1Charge[DiMuSize]=aMuon.charge();
      if(aMuon.isGlobalMuon()){Mu1_global[DiMuSize]=1;} else {Mu1_global[DiMuSize]=0;}
      if(aMuon.isTrackerMuon()){Mu1_tracker[DiMuSize]=1;} else {Mu1_tracker[DiMuSize]=0;}
      if(aMuon.isStandAloneMuon()){Mu1_standalone[DiMuSize]=1;} else{Mu1_standalone[DiMuSize]=0;} 
      

      
      if(!aMuon.triggerObjectMatchesByPath("HLT_HIL1SingleMu3").empty()) {Mu1_trigger1[DiMuSize]=1;} else {Mu1_trigger1[DiMuSize]=0;}
      if(!aMuon.triggerObjectMatchesByPath("HLT_HIL1DoubleMuOpen").empty()) {Mu1_trigger2[DiMuSize]=1;} else {Mu1_trigger2[DiMuSize]=0;}
      if(!aMuon.triggerObjectMatchesByPath("HLT_HIUpcMu").empty()) {Mu1_trigger3[DiMuSize]=1;} else {Mu1_trigger3[DiMuSize]=0;}


      //cout<<" trigger path "<<aMuon.triggerObjectMatchesByPath("HLT_HIL1DoubleMuOpen").empty()<<endl;
      //cout<<" trigger path "<<aMuon.triggerObjectMatchesByPath("HLT_L1DoubleMu0_v1").empty()<<endl;
      //cout<<" trigger filter "<<aMuon.triggerObjectMatchesByFilter("HLT_L1DoubleMu0_v1").empty()<<endl;
      //cout<<" mu1: global "<<Mu1_global[DiMuSize]<<" tracker "<<Mu1_tracker[DiMuSize]<<" sa "<<Mu1_standalone[DiMuSize]<<endl; 
          


      //const pat::TriggerObjectStandAloneCollection mu1HLTMatches = aMuon.triggerObjectMatchesByPath( "HLT_L1DoubleMu0_v1" );
      //if(mu1HLTMatches)cout<<" trigger 2 "<<endl;

      

      if(aMuon.isTrackerMuon())
	{
	  TrackRef iTrack =aMuon.innerTrack();
	  const reco::HitPattern& p1=iTrack->hitPattern();
	  Mu1_found[DiMuSize]=iTrack->found();
	  Mu1_nchi2In[DiMuSize]=iTrack->chi2()/iTrack->ndof();
	  Mu1_pixeLayers[DiMuSize]=p1.pixelLayersWithMeasurement();
	  Mu1_dxy[DiMuSize]=iTrack->dxy(RefVtx);
	  Mu1_dz[DiMuSize]=iTrack->dz(RefVtx);
	  if(aMuon.isGlobalMuon())
	    {
	      TrackRef gTrack =aMuon.globalTrack();
	      const reco::HitPattern& q1=gTrack->hitPattern();
	      Mu1_nValidMuHits[DiMuSize]=q1.numberOfValidMuonHits();
	      Mu1_nchi2Gl[DiMuSize]=gTrack->chi2()/gTrack->ndof();
	    }
	  
	  else {Mu1_nValidMuHits[DiMuSize]=-999;Mu1_nchi2Gl[DiMuSize]=-999;}

	}
      else{Mu1_found[DiMuSize]=-999;Mu1_nchi2In[DiMuSize]=-999;Mu1_pixeLayers[DiMuSize]=-999;Mu1_dxy[DiMuSize]=-999;Mu1_dz[DiMuSize]=-999;}

      Mu2Pt[DiMuSize]=bMuon.pt();
      Mu2Eta[DiMuSize]=bMuon.eta();
      Mu2Px[DiMuSize]=bMuon.px();
      Mu2Py[DiMuSize]=bMuon.py();
      Mu2Pz[DiMuSize]=bMuon.pz();
      Mu2Phi[DiMuSize]=bMuon.phi();
      Mu2Charge[DiMuSize]=bMuon.charge();
      
      
	if(bMuon.isGlobalMuon()){Mu2_global[DiMuSize]=1;} else {Mu2_global[DiMuSize]=0;}
	if(bMuon.isTrackerMuon()){Mu2_tracker[DiMuSize]=1;} else {Mu2_tracker[DiMuSize]=0;}
	if(bMuon.isStandAloneMuon()){Mu2_standalone[DiMuSize]=1;} else{Mu2_standalone[DiMuSize]=0;}
	


	if(!bMuon.triggerObjectMatchesByPath("HLT_HIL1SingleMu3").empty()) {Mu2_trigger1[DiMuSize]=1;} else {Mu2_trigger1[DiMuSize]=0;}
	if(!bMuon.triggerObjectMatchesByPath("HLT_HIL1DoubleMuOpen").empty()) {Mu2_trigger2[DiMuSize]=1;} else {Mu2_trigger2[DiMuSize]=0;}
	if(!bMuon.triggerObjectMatchesByPath("HLT_HIUpcMu").empty()) {Mu2_trigger3[DiMuSize]=1;} else {Mu2_trigger3[DiMuSize]=0;}





	//cout<<"mu2 : global "<<Mu2_global[DiMuSize]<<" tracker "<<Mu2_tracker[DiMuSize]<<" sa "<<Mu2_standalone[DiMuSize]<<endl; 
	
	if(bMuon.isTrackerMuon())
          {
            TrackRef iTrack =bMuon.innerTrack();
            const reco::HitPattern& p2=iTrack->hitPattern();
            Mu2_found[DiMuSize]=iTrack->found();
            Mu2_nchi2In[DiMuSize]=iTrack->chi2()/iTrack->ndof();
            Mu2_pixeLayers[DiMuSize]=p2.pixelLayersWithMeasurement();
            Mu2_dxy[DiMuSize]=iTrack->dxy(RefVtx);
            Mu2_dz[DiMuSize]=iTrack->dz(RefVtx);
            if(bMuon.isGlobalMuon())
              {
		TrackRef gTrack =bMuon.globalTrack();
		const reco::HitPattern& q2=gTrack->hitPattern();
		Mu2_nValidMuHits[DiMuSize]=q2.numberOfValidMuonHits();
		Mu2_nchi2Gl[DiMuSize]=gTrack->chi2()/gTrack->ndof();
              }
	    else {Mu2_nValidMuHits[DiMuSize]=-999;Mu2_nchi2Gl[DiMuSize]=-999;}

	  }
	else{Mu2_found[DiMuSize]=-999;Mu2_nchi2In[DiMuSize]=-999;Mu2_pixeLayers[DiMuSize]=-999;Mu2_dxy[DiMuSize]=-999;Mu2_dz[DiMuSize]=-999;}
	

	cout<<"Mu2_found[DiMuSize] "<<Mu2_found[DiMuSize]<<endl;

	//cout<<" DiMuMass "<<DiMuMass[DiMuSize]<< " DiMuCharge  "<< DiMuCharge[DiMuSize]<<endl;
	DiMuSize++;
    }
    nDiMuon=DiMuSize;  
  }


  

  Handle<edm::TriggerResults> triggerResults;
  iEvent.getByLabel("TriggerResults", triggerResults);
  const edm::TriggerNames triggerNames = iEvent.triggerNames(*triggerResults);
  for (unsigned i=0; i<triggerNames.size(); i++) {
    std::string hltName = triggerNames.triggerName(i);
    unsigned int index = triggerNames.triggerIndex(hltName);
    cout << "HLT: " << hltName << " fired? " << triggerResults->accept(index) << endl;
  }




  //Get a handle ("pointer") to the TrackCollection within the event
  Handle<TrackCollection> trackCollectionHandle;
  iEvent.getByLabel("hiSelectedTracks", trackCollectionHandle);
  //iEvent.getByLabel("hiSelectedTracks", tracks);
  
  //Check if there was a problem accessing the TrackCollection
  if( !trackCollectionHandle.isValid() ){
    cout << "Error! Can't get selectTracks!" << endl;
    return ;
  }
  trackNb=trackCollectionHandle->size();
  cout<<" no of reconstrcuted tracks in event "<<trackNb<<endl;  
  
  //Loop over tracks
  for(TrackCollection::const_iterator track = trackCollectionHandle->begin(); track != trackCollectionHandle->end(); track++){
    //double track_eta = track->eta();
    //double track_phi = track->phi();
    //double track_pt  = track->pt();
    //cout << track_eta << " " << track_phi << " " << track_pt << endl;
  }
















}

//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonUPCTree);



