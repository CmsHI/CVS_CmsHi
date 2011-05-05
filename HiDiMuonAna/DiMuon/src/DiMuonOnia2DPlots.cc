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
//edm::InputTag fHLTFilterName;
  

  TFile *In;

  TH1F *Centrality;
  TFile *fOutputFile ;
  
  TTree *SingleMuonTree;
  TTree *SingleGenMuonTree;

   
  TH2F *diMuonsGenInvMassVsPt;
  TH2F *diMuonsGenInvMassVsY;
  TH2F *diMuonsGenInvMassVsCen;
  
  TH2F *diMuonsGenInvMassVsPtW;
  TH2F *diMuonsGenInvMassVsYW;
  TH2F *diMuonsGenInvMassVsCenW;


  TH1F *diMuonsGenInvMass;
  TH1F *diMuonsGenPt;
  TH1F *diMuonsGenRapidity;

  // Global 

  TH1F *gMuonChi2ndf;
  TH1F *gMuonnhits;
  TH1F *gMuonfound;

  TH1F *gMuonChi2ndfTrack;
  TH1F *gMuonPixel;
  TH1F *gMuonDxy;
  TH1F *gMuonZ;
  TH1F *gMuonSeg;
  TH1F *gMuonChamb;

  TH1F *gMuonArb;
  TH1F *gMuonLastTight;
  TH1F *gMuonLastLoose;

 TH1F *gMuonPtError;
 TH1F *gMuonValidHits;


  TH1F *gMuonsPt;
  TH1F *gMuonsNumber;
  TH1F *gMuonsNumberCut;
  
  TH1F *gMuonsEta;
  TH1F *gMuonsPhi;
  TH1F *gMuonsIso;
  // Tracker 

  TH1F *tMuonfound;
  TH1F *tMuonChi2ndfTrack;
  TH1F *tMuonPixel;
  TH1F *tMuonDxy;
  TH1F *tMuonZ;

  TH1F *tMuonsPt;
  TH1F *tMuonsEta;
  TH1F *tMuonsPhi;

  // STA

  TH1F *sMuonnhits;
  TH1F *sMuonDxy;
  TH1F *sMuonZ;

  TH1F *sMuonPtError;  
  TH1F *sMuonChi2ndf;
  TH1F *sMuonSeg;
  TH1F *sMuonChamb;


  TH1F *sMuonsPt;
  TH1F *sMuonsEta;
  TH1F *sMuonsPhi;

  TH1F *hZVtx;

  int bin, gbin, rbin;
  float W;
  float NColl;


  // Cut histograms

  TH2F *dimu;
  TH2F *dimuS;
  
  TH2F *dimuAll;
  TH2F *dimuAllNoPt; 
  TH2F *dimuGlbTrk;
  TH1F *dimuFOUND;
  TH1F *dimuGLCHI2;
  TH1F *dimuHITS;
  TH1F *dimuTRKCHI2;
  TH1F *dimuARB;
  TH2F *dimuLast;
  TH2F *dimuLastLoose;
  
  TH1F *dimuPIX;
  TH1F *dimuDXY;
  TH1F *dimuDZ;
  TH1F *dimuPTERROR;
  TH1F *dimuNOOFVALIDHITS;
  TH1F *dimuD0;
  TH1F *dimuSeg;
  TH1F *dimuChamb;
  
  TH1F *dimuIso;


  //PAT Histo                                                                                                                                                           
  TH2F *diMuonsPATInvMassVsPt;
  TH2F *diMuonsPATInvMassVsY;
  TH2F *diMuonsPATInvMassVsCen;

  TH2F * diMuonsPATSameChargeInvMassVsPt;
  TH2F *diMuonsPATSameChargeInvMassVsY;
  TH2F *diMuonsPATSameChargeInvMassVsCen;
 

  TH2F *diMuonsPATSTAInvMassVsPt;
  TH2F *diMuonsPATSTAWOCutInvMassVsPt;
  TH2F *diMuonsPATSTAWOMatchInvMassVsPt;
  TH2F *diMuonsPATSTAAllInvMassVsPt;

  TH2F *diMuonsPATSTAInvMassVsY;
  TH2F *diMuonsPATSTAInvMassVsCen;

  TH2F *diMuonsPATSTASameChargeInvMassVsPt;
  TH2F *diMuonsPATSTASameChargeInvMassVsY;
  TH2F *diMuonsPATSTASameChargeInvMassVsCen;




private:
  
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void GenPlots(const edm::Event&, const edm::EventSetup& );
  virtual void GenAnalyze(const edm::Event&, const edm::EventSetup& );
  virtual void endJob() ;
  
  virtual bool matchPATMuon(const pat::Muon *pMuon);
  virtual bool selPATMuon(const pat::Muon *pMuon);
  virtual bool selPATSTAMuon(const pat::Muon* aMuon);
  virtual bool isMuonInAccept(const reco::Muon* aMuon); 
  virtual void MuAnalyze(const edm::Event&, const edm::EventSetup&);
  virtual void PATDiMuAnalyze(const edm::Event&, const edm::EventSetup&);
  virtual void PATDiMuSameChargeAnalyze(const edm::Event&, const edm::EventSetup&);
  virtual bool allCutGlobal(const reco::Muon* aMuon); 
  virtual float FindWeight(float pt, float y);
  virtual float FindCenWeight(int Bin);
  

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
  bool muPos_matches, muPos_tracker;  
  //(ii).Negative Muon                                                                                                             
  double muNeg_nchi2In, muNeg_dxy, muNeg_dz, muNeg_nchi2Gl;
  int muNeg_found, muNeg_pixeLayers, muNeg_nValidMuHits,muNeg_arbitrated;
  bool muNeg_matches, muNeg_tracker;  

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
  fHLTFilterName(iConfig.getUntrackedParameter<string>("HLTFilterName"))
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
void
DiMuonOnia2DPlots::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  cout << " ------------------------------------------------------ " << endl;
  using namespace edm;
  using namespace std;
  nPV = 0 ;
  
  centrality_ = new CentralityProvider(iSetup);
  centrality_->newEvent(iEvent,iSetup);
  bin = centrality_->getBin();
  Centrality->Fill(bin);
  //cout<<" bin "<<bin<<endl;
  //rbin=bin;
  //gbin=bin;


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
  
  hZVtx->Fill(RefVtx.Z());
  
  //MuAnalyze(iEvent, iSetup);
  
  //  cout<<"generator info " <<fIsGenInfo.c_str()<<endl;
  if(!strcmp(fIsGenInfo.c_str(),"TRUE")){GenPlots(iEvent, iSetup);}
  
  //if(!strcmp(fIsGenInfo.c_str(),"TRUE")){GenAnalyze(iEvent, iSetup);}    
  //Fill cuts histos
  //FillHistoCuts(p.mass(), p.pt(), mu0, mu1);
  // Same Charge plots   
  //SameChargePlots(iEvent, iSetup); 
  // cout<<" PAT info "<<fIsPATInfo.c_str()<<endl;  
  

  //if(!strcmp(fIsPATInfo.c_str(),"TRUE")){PATDiMuAnalyze(iEvent,iSetup);}
  
  if(!strcmp(fIsPATInfo.c_str(),"TRUE")){FillTree(iEvent,iSetup);}

  if(!strcmp(fIsGenInfo.c_str(),"TRUE")){FillGenTree(iEvent,iSetup);}

 //if(!strcmp(fIsPATInfo.c_str(),"TRUE")){PATDiMuSameChargeAnalyze(iEvent,iSetup);}
  
 

}


/////////


void DiMuonOnia2DPlots::GenPlots(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  float mumass =0.105658389;
  //cout<<"gen info: "<<endl;
  using namespace edm;
  using namespace std;
  
  edm::Handle<edm::View<reco::GenParticle> >genPar ;
  iEvent.getByLabel("hiGenParticles",genPar) ;
  //iEvent.getByLabel("genMuons",genPar) ;
 
  if(!(genPar.isValid())) return;

  //iEvent.getByLabel("genParticles",genPar) ;
  edm::View<reco::GenParticle> genParticles = *genPar ;

  TLorentzVector  genvector1, genvector2;

  double px1[10000], py1[10000], pz1[10000], px2[10000], py2[10000], pz2[10000]; 
  unsigned int nplus = 0, nminus =0;
  
  for(size_t i = 0; i < genParticles.size(); ++ i) {
    const reco::GenParticle& part = (*genPar)[i];
    const  Candidate *mom = part.mother();
   
    if(part.pdgId()==443){
      diMuonsGenInvMass->Fill(part.mass());
      diMuonsGenPt->Fill(part.pt());
      diMuonsGenRapidity->Fill(part.rapidity());
    }



 if (part.numberOfMothers()!=1) continue;
    int momId = mom->pdgId();
 



   if (abs(part.pdgId()) == 13 &&  momId == 443){
      if(part.pdgId() == 13 ){
	px1[nplus] = part.px();
	py1[nplus] = part.py();
	pz1[nplus] = part.pz();
	nplus++;
      }

      if(part.pdgId()== -13) {
	px2[nminus] = part.px();
	py2[nminus] = part.py();
	pz2[nminus] = part.pz();
	nminus++;
      }
    }
  }
  
  for(size_t i = 0; i < nplus; i++) {
    
    double en1 = sqrt(px1[i]*px1[i] + py1[i]*py1[i] + pz1[i]*pz1[i] + mumass*mumass);
      
    for(size_t j = 0; j< nminus; j++) {
      
      double en2 = sqrt(px2[j]*px2[j] + py2[j]*py2[j] + pz2[j]*pz2[j] + mumass*mumass);
      
      TLorentzVector  genvector1,genvector2,genvector3;
      
      genvector1.SetPxPyPzE(px1[i], py1[i], pz1[i], en1);
      genvector2.SetPxPyPzE(px2[j], py2[j], pz2[j], en2);
      
      genvector3=genvector1+genvector2;
      
      float GenDiMuonY=genvector3.Rapidity();
      float GenDiMuonMinv=genvector3.M();
      float GenDiMuonPt =genvector3.Pt();
      
      W=FindWeight(GenDiMuonPt,GenDiMuonY); 
      NColl=FindCenWeight(bin);
      
      //if(abs(GenDiMuonY) <= 2.0 ){
	diMuonsGenInvMassVsPt->Fill(GenDiMuonMinv,GenDiMuonPt);
	diMuonsGenInvMassVsY->Fill(GenDiMuonMinv,GenDiMuonY);
	diMuonsGenInvMassVsCen->Fill(GenDiMuonMinv,bin);
	//cout<<" weight while gen level histo: "<<W<<endl;
	//cout<<"Gen Level bin "<<bin<<" NColl "<<NColl<<endl;
	diMuonsGenInvMassVsPtW->Fill(GenDiMuonMinv,GenDiMuonPt,W*NColl);
	diMuonsGenInvMassVsYW->Fill(GenDiMuonMinv,GenDiMuonY,W*NColl);
	diMuonsGenInvMassVsCenW->Fill(GenDiMuonMinv,bin,NColl*W);
	//}
      //diMuonsGenInvMass->Fill(GenDiMuonMinv);
      //diMuonsGenPt->Fill(GenDiMuonPt);
      //diMuonsGenRapidity->Fill(GenDiMuonY);
    }
  }
}

void DiMuonOnia2DPlots::GenAnalyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  using namespace HepMC;
  using namespace edm;
  edm::Handle<HepMCProduct> evt;
  
  //iEvent.getByLabel("source", evt);
  iEvent.getByLabel("generator", evt);
  //iEvent.getByLabel("hiSignal", evt);
  
  const HepMC::GenEvent *genEvent = evt->GetEvent();
  int gcnt = genEvent->particles_size();

  gcnt = 0;
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
	W=FindWeight(genupt,genuy);
        NColl=FindCenWeight(bin);
	
	//if(abs(genuy) <= 2.0){
	 
	  diMuonsGenInvMassVsPt->Fill(minv,genupt);
	  diMuonsGenInvMassVsY->Fill(minv,genuy);
	  diMuonsGenInvMassVsCen->Fill(minv,bin);
	  diMuonsGenInvMass->Fill(minv);
	  diMuonsGenPt->Fill(genupt);
	  diMuonsGenRapidity->Fill(genuy);
	  //cout<<" weight while gen level histo: "<<W<<endl;
	  //cout<<"Gen Level bin "<<bin<<" NColl "<<NColl<<endl;
	  diMuonsGenInvMassVsPtW->Fill(minv,genupt,W*NColl);
	  diMuonsGenInvMassVsYW->Fill(minv,genuy,W*NColl);
	  diMuonsGenInvMassVsCenW->Fill(minv,bin,NColl*W);
	

	  //}
      } // for j                                                                                                                                                        
    } // for i                                                                                                                                                          
  }// if
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
DiMuonOnia2DPlots::beginJob()
{


  
  In = new TFile("/afs/cern.ch/user/k/kumarv/scratch0/CMSSW_3_9_4/src/HiDiMuonAna/DiMuon/src/pythiaZ0_nofilter_CTEQ6L1_re6_totevt100000_2DAllDimu.root");

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
   
  diMuonsGenInvMassVsPt = new TH2F("diMuonsGenInvMassVsPt", "diMuonsGenInvMassVsPt", 800, 0, 20, 200,0,100);
  diMuonsGenInvMassVsY = new TH2F("diMuonsGenInvMassVsY","diMuonsGenInvMassVsY",800, 0, 20,100, -5, 5);
  diMuonsGenInvMassVsCen = new TH2F("diMuonsGenInvMassVsCen","diMuonsGenInvMassVsCen", 800, 0, 20,100,0,100);

  diMuonsGenInvMassVsPtW = new TH2F("diMuonsGenInvMassVsPtW", "diMuonsGenInvMassVsPtW", 800, 0, 20, 200,0,100);
  diMuonsGenInvMassVsPtW->Sumw2();
  diMuonsGenInvMassVsYW = new TH2F("diMuonsGenInvMassVsYW","diMuonsGenInvMassVsYW",800, 0, 20,100, -5, 5);
  diMuonsGenInvMassVsYW->Sumw2();
  diMuonsGenInvMassVsCenW = new TH2F("diMuonsGenInvMassVsCenW","diMuonsGenInvMassVsCenW", 800, 0, 20,100,0,100);
  diMuonsGenInvMassVsCenW->Sumw2();

  diMuonsGenInvMass = new TH1F("diMuonsGenInvMass","diMuonsGenInvMass", 800,0,20);
  diMuonsGenPt = new TH1F("diMuonsGenPt","diMuonsGenPt", 200,0,100);
  diMuonsGenRapidity = new TH1F("diMuonsGenRapidity","diMuonsGenRapidity", 100,-5,5);

  gMuonChi2ndf = new TH1F("gMuonChi2ndf", "gMuonChi2ndf", 100, 0, 100);
  gMuonnhits = new TH1F("gMuonnhits", "gMuonnhits", 100, 0, 100);
  gMuonfound = new TH1F("gMuonfound", "gMuonfound ", 200, 0, 100);

  gMuonChi2ndfTrack = new TH1F("gMuonChi2ndfTrack", "gMuonChi2ndfTrack", 200, 0, 50);
  gMuonPixel = new TH1F("gMuonPixel", "gMuonPixel", 100, 0, 10);

  gMuonDxy = new TH1F("gMuonDxy", "gMuonDxy", 200, -10, 10);
  gMuonZ = new TH1F("gMuonZ", "gMuonZ", 200, -10, 10);
  gMuonSeg = new TH1F("gMuonSeg", "gMuonSeg", 200, -50, 50);
  gMuonChamb = new TH1F("gMuonChamb", "gMuonChamb", 200, -50, 50);

  gMuonArb = new TH1F("gMuonArb", "gMuonArb", 11, -1, 10);
  gMuonLastTight = new TH1F("gMuonLastTight", "gMuonLastTight", 11, -1, 10);
  gMuonLastLoose = new TH1F("gMuonLastLoose", "gMuonLastLoose", 11, -1, 10);

  gMuonPtError=new TH1F("gMuonsPtError", "gMuonsPtError", 200, 0, 10);
  gMuonValidHits=new TH1F("gMuonValidHits", "gMuonValidHits", 200, 0, 50);
  
  gMuonsIso=new TH1F("gMuonsIso", "gMuonsIso", 200, 0, 10);

  gMuonsPt = new TH1F("gMuonsPt", "gMuonsPt", 200, 0, 100);
  gMuonsNumber = new TH1F("gMuonsNumber", "gMuonsNumber", 100, 0, 10);
  gMuonsNumberCut = new TH1F("gMuonsNumberCut", "gMuonsNumberCut", 100, 0, 10);
 
  gMuonsEta = new TH1F("gMuonsEta", " gMuonsEta", 100, -10, 10);
  gMuonsPhi = new TH1F("gMuonsPhi", "gMuonsPhi", 100, -10, 10);

  //Tracker Histos

  tMuonfound = new TH1F("tMuonfound", "tMuonfound ", 200, 0, 100);
  tMuonChi2ndfTrack = new TH1F("tMuonChi2ndfTrack", "tMuonChi2ndfTrack", 200, 0, 100);
  tMuonPixel = new TH1F("tMuonPixel", "tMuonPixel", 100, 0, 100);
  tMuonDxy = new TH1F("tMuonDxy", "tMuonDxy", 200, -50, 50);
  tMuonZ = new TH1F("tMuonZ", "tMuonZ", 200, -50, 50);

  tMuonsPt = new TH1F("tMuonsPt", "tMuonsPt", 200, 0, 100);
  tMuonsEta = new TH1F("tMuonsEta", " tMuonsEta", 100, -10, 10);
  tMuonsPhi = new TH1F("tMuonsPhi", "tMuonsPhi", 100, -10, 10);

  // STA Histos

  sMuonnhits = new TH1F("sMuonnhits", "sMuonnhits", 100, 0, 100);
  sMuonDxy = new TH1F("sMuonDxy", "sMuonDxy", 200, -10, 10);
  sMuonZ = new TH1F("sMuonZ", "sMuonZ", 200, -10, 10);

  sMuonsPt = new TH1F("sMuonsPt", "sMuonsPt", 200, 0, 100);
  sMuonsEta = new TH1F("sMuonsEta", " sMuonsEta", 100, -10, 10);
  sMuonsPhi = new TH1F("sMuonsPhi", "sMuonsPhi", 100, -10, 10);


  sMuonPtError=new TH1F("sMuonsPtError", "sMuonsPtError", 200, 0, 10);
  sMuonChi2ndf = new TH1F("sMuonChi2ndf", "sMuonChi2ndf", 100, 0, 100);
  sMuonSeg = new TH1F("sMuonSeg", "sMuonSeg", 200, -50, 50);
  sMuonChamb = new TH1F("sMuonChamb", "sMuonChamb", 200, -50, 50);


  // Z vertex
  hZVtx = new TH1F("hZVtx", "hZVtx", 200, -100, 100);

  // Cuts histos
 
  dimu = new TH2F("dimu", "dimu", 800, 0, 20, 200, 0, 100);
  dimuS = new TH2F("dimuS", "dimuS", 800, 0, 20, 200, 0, 100);
  
  dimuAll = new TH2F("dimuAll", "dimuAll", 800, 0, 20, 200, 0, 100);
  dimuAllNoPt = new TH2F("dimuAllNoPt", "dimuAllNoPt", 800, 0, 20, 200, 0, 100);
  
  dimuGlbTrk= new TH2F("dimuGlbTrk", "dimuGlbTrk", 800, 0, 20, 200, 0, 100);
  
  dimuFOUND = new TH1F("dimuFOUND", "dimuFOUND", 800, 0, 20);
  dimuGLCHI2 = new TH1F("dimuGLCHI2", "dimuGLCHI2", 800, 0, 20);
  dimuHITS = new TH1F("dimuHITS", "dimuHITS", 800, 0, 20);
  dimuTRKCHI2 = new TH1F("dimuTRKCHI2", "dimuTRKCHI2", 800, 0, 20);
  dimuARB = new TH1F("dimuARB", "dimuARB", 800, 0, 20);
  dimuLast = new TH2F("dimuLast", "dimuLast", 800, 0, 20, 100, 0, 100);
  dimuLastLoose = new TH2F("dimuLastLoose", "dimuLastLoose", 800, 0, 20, 200, 0, 100);
  
  dimuPIX = new TH1F("dimuPIX", "dimuPIX", 800, 0, 20);
  dimuDXY = new TH1F("dimuDXY", "dimuDXY", 800, 0, 20);
  dimuDZ = new TH1F("dimuDZ", "dimuDZ", 800, 0, 20);
 
  //new cut histos
  dimuPTERROR = new TH1F("dimuPTERROR", "dimuPTERROR", 800, 0, 20);
  dimuNOOFVALIDHITS = new TH1F("dimuNOOFVALIDHITS", "dimuNOOFVALIDHITS", 800, 0, 20);
  dimuD0 = new TH1F("dimuD0", "dimuD0", 800, 0, 20);
  dimuSeg = new TH1F("dimuSeg", "dimuSeg", 800, 0, 20);
  dimuChamb = new TH1F("dimuChamb", "dimuChamb", 800, 0, 20);
  dimuIso=  new TH1F("dimuIso", "dimuIso", 800, 0, 20);



  ///PAT Histo                                                                                                             
  diMuonsPATInvMassVsPt = new TH2F("diMuonsPATInvMassVsPt", "diMuonsPATInvMassVsPt", 800, 0, 20, 200,0,100);
  diMuonsPATInvMassVsY = new TH2F("diMuonsPATInvMassVsY","diMuonsPATInvMassVsY",800, 0, 20,100, -5, 5);
  diMuonsPATInvMassVsCen = new TH2F("diMuonsPATInvMassVsCen","diMuonsPATInvMassVsCen", 800, 0, 20,100,0,100);

  diMuonsPATSameChargeInvMassVsPt = new TH2F("diMuonsPATSameChargeInvMassVsPt", "diMuonsPATSameChargeInvMassVsPt", 800, 0, 20, 200,0,100);
  diMuonsPATSameChargeInvMassVsY = new TH2F("diMuonsPATSameChargeInvMassVsY","diMuonsPATSameChargeInvMassVsY",800, 0, 20,100, -5, 5);
  diMuonsPATSameChargeInvMassVsCen = new TH2F("diMuonsPATSameChargeInvMassVsCen","diMuonsPATSameChargeInvMassVsCen", 800, 0, 20,100,0,100);


  diMuonsPATSTAInvMassVsPt = new TH2F("diMuonsPATSTAInvMassVsPt", "diMuonsPATSTAInvMassVsPt", 800, 0, 20, 200,0,100);
  diMuonsPATSTAWOCutInvMassVsPt= new TH2F("diMuonsPATSTAWOCutInvMassVsPt", "diMuonsPATWOCutSTAInvMassVsPt", 800, 0, 20, 200,0,100);
  diMuonsPATSTAWOMatchInvMassVsPt= new TH2F("diMuonsPATSTAWOMatchInvMassVsPt", "diMuonsPATWOMatchSTAInvMassVsPt", 800, 0, 20, 200,0,100);
  diMuonsPATSTAAllInvMassVsPt= new TH2F("diMuonsPATSTAAllInvMassVsPt", "diMuonsPATSTAAllInvMassVsPt", 800, 0, 20, 200,0,100);
  diMuonsPATSTAInvMassVsY = new TH2F("diMuonsPATSTAInvMassVsY","diMuonsPATSTAInvMassVsY",800, 0, 20,100, -5, 5);
  diMuonsPATSTAInvMassVsCen = new TH2F("diMuonsPATSTAInvMassVsCen","diMuonsPATSTAInvMassVsCen", 800, 0, 20,100,0,100);
  diMuonsPATSTASameChargeInvMassVsPt = new TH2F("diMuonsPATSTASameChargeInvMassVsPt", "diMuonsPATSTASameChargeInvMassVsPt", 800, 0, 20, 200,0,100);
  diMuonsPATSTASameChargeInvMassVsY = new TH2F("diMuonsPATSTASameChargeInvMassVsY","diMuonsPATSTASameChargeInvMassVsY",800, 0, 20,100, -5, 5);
  diMuonsPATSTASameChargeInvMassVsCen = new TH2F("diMuonsPATSTASameChargeInvMassVsCen","diMuonsPATSTASameChargeInvMassVsCen", 800, 0, 20,100,0,100);



 //h_ZetaGen_ = genParticleDir.make<TH1D>("generatedZeta","#eta of generated Z",100,-5.,5.); 

  // Write comments in a file
}



// ------------ method called once each job just after ending the event loop  ------------
void DiMuonOnia2DPlots::endJob() 
{


  In->Close();
  cout<<"End Job"<<endl;
  fOutputFile->cd();
  
  SingleMuonTree->Write();
  SingleGenMuonTree->Write();
  
  Centrality->Write(); 
  diMuonsGenInvMassVsPt->Write();
  diMuonsGenInvMassVsY->Write();
  diMuonsGenInvMassVsCen->Write();
  
  diMuonsGenInvMassVsPtW->Write();
  diMuonsGenInvMassVsYW->Write();
  diMuonsGenInvMassVsCenW->Write();

  diMuonsGenInvMass->Write(); 
  diMuonsGenPt->Write(); 
  diMuonsGenRapidity->Write();

  gMuonChi2ndf->Write();
  gMuonnhits->Write();
  gMuonfound->Write();

  gMuonChi2ndfTrack->Write();
  gMuonPixel->Write();
  gMuonDxy->Write();
  gMuonZ->Write();
  gMuonSeg->Write();
  gMuonChamb->Write();

  gMuonArb->Write();
  gMuonLastTight->Write();
  gMuonLastLoose->Write();

  gMuonPtError->Write();
  gMuonValidHits->Write();

  gMuonsIso->Write();

  gMuonsPt->Write();
  gMuonsNumber->Write();
  gMuonsNumberCut->Write();
  
  gMuonsEta->Write();
  gMuonsPhi->Write();


  // Tracker Histos
  tMuonfound->Write();
  tMuonChi2ndfTrack->Write();
  tMuonPixel->Write();
  tMuonDxy->Write();
  tMuonZ->Write();

  tMuonsPt->Write();
  tMuonsEta->Write();
  tMuonsPhi->Write();

  // STA 

  sMuonnhits->Write();
  sMuonDxy->Write();
  sMuonZ->Write();
  
  sMuonPtError->Write();
  sMuonChi2ndf->Write();
  sMuonChamb->Write();
  sMuonSeg->Write();


  sMuonsPt->Write();
  sMuonsEta->Write();
  sMuonsPhi->Write();


  hZVtx->Write();

  // cuts histos
  dimu->Write();
  dimuS->Write();
  
  dimuGlbTrk->Write();
  dimuFOUND->Write();
  dimuGLCHI2->Write();
  dimuHITS->Write();
  dimuTRKCHI2->Write();
  dimuARB->Write();
  dimuLast->Write();
  dimuLastLoose->Write();
  
  dimuPIX->Write();
  dimuDXY->Write();
  dimuDZ->Write();
  
  dimuPTERROR->Write(); 
  dimuNOOFVALIDHITS->Write();
  dimuD0->Write();
  dimuSeg->Write();
  dimuChamb->Write();
  dimuIso->Write();
  dimuAllNoPt->Write();
  dimuAll->Write();


  //pat histo
  diMuonsPATInvMassVsPt->Write(); 
  diMuonsPATInvMassVsY->Write(); 
  diMuonsPATInvMassVsCen->Write();

  diMuonsPATSameChargeInvMassVsPt->Write();
  diMuonsPATSameChargeInvMassVsY->Write(); 
  diMuonsPATSameChargeInvMassVsCen->Write(); 


  diMuonsPATSTAInvMassVsPt->Write();
  diMuonsPATSTAWOCutInvMassVsPt->Write();
  diMuonsPATSTAWOMatchInvMassVsPt->Write();
  diMuonsPATSTAAllInvMassVsPt->Write();

  
  diMuonsPATSTAInvMassVsY->Write();
  diMuonsPATSTAInvMassVsCen->Write();

  diMuonsPATSTASameChargeInvMassVsPt->Write();
  diMuonsPATSTASameChargeInvMassVsY->Write();
  diMuonsPATSTASameChargeInvMassVsCen->Write();

  // Output file close
  fOutputFile->Close();

}


bool DiMuonOnia2DPlots::isMuonInAccept(const reco::Muon* aMuon) {
  
  // return (fabs(aMuon->eta()) < 2.4); 
  return (fabs(aMuon->eta()) < 2.4 &&
	  ((fabs(aMuon->eta()) < 0.3 && aMuon->pt() >= 4.0) ||
	   (0.3 <= fabs(aMuon->eta()) && fabs(aMuon->eta()) < 1.0 && aMuon->pt() >= 3.5) ||
	   (1.0 <= fabs(aMuon->eta()) && fabs(aMuon->eta()) < 1.5 && aMuon->p() > 5.2) ||
	   (1.5 <= fabs(aMuon->eta()) && aMuon->pt() >= 3.033-5.0/9.0*fabs(aMuon->eta()))));

  }




void DiMuonOnia2DPlots::MuAnalyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  
{

  //Mu_Eta=-999;
  //All new cuts we can study here and see there disstributions 
  int imuplus =0, imuminus=0;
  int GMuon = 0, TMuon=0 , SAMuon=0;
  using namespace edm;
  using namespace std;
  using reco::TrackCollection;
  using reco::MuonCollection;
  

  cout<<" 1"<<endl;  
  
  edm::Handle<edm::View<pat::Muon> >tmuons;
  iEvent.getByLabel("patMuonsWithTrigger", tmuons);
  
  cout<<" 2"<<endl;  
  
  if(!(tmuons.isValid())) return;
    cout<<" rec mu size : "<<tmuons->size()<<endl;
    for(unsigned int j = 0; j <tmuons->size(); ++j){
      edm::RefToBase<pat::Muon> aMuon(tmuons, j);
      if (aMuon.isNull()) continue;
      cout<<" inside muon loop "<<endl;
      if(aMuon->isGlobalMuon()) GMuon++;
      if(aMuon->isTrackerMuon()) TMuon++;
      if((aMuon->isStandAloneMuon()) && (!aMuon->isGlobalMuon())) SAMuon++;
      float pt = aMuon->pt();
      float eta = aMuon->eta();
    float phi = aMuon->phi();
    int charge = aMuon->charge();
    //Mu_Eta=eta;

    if(charge>0) imuplus++;
    if(charge<0) imuminus++;
    
    if(aMuon->isGlobalMuon()) {
      
      //cout<<"is global muon "<<endl;
      TrackRef gTrack = aMuon->globalTrack();
      const reco::HitPattern& q = aMuon->globalTrack()->hitPattern();
      
      TrackRef iTrack = aMuon->innerTrack();
      if(!iTrack.isAvailable()) continue;
      const reco::HitPattern& p = iTrack->hitPattern();
      //cout<<" inner track hit pattern "<<endl; 
      //cout<<p.numberOfValidHits()<<" valid hits "<<endl;
      if(aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof() <= 10.0 && q.numberOfValidMuonHits() >= 1 
	 && fabs(iTrack->dxy(RefVtx)) < 0.03 && fabs(iTrack->dz(RefVtx)) < 0.15 && iTrack->chi2()/iTrack->ndof() <= 4.0 )
	{//cout<<" first cut "<<endl;
	  gMuonValidHits->Fill(p.numberOfValidHits());
	}
      if(p.numberOfValidHits() >= 11 && q.numberOfValidMuonHits() >= 1
	 && fabs(iTrack->dxy(RefVtx)) <= 0.03 && fabs(iTrack->dz(RefVtx)) <= 0.15 && iTrack->chi2()/iTrack->ndof() <= 4.0 )
	{//cout<<" second cut "<<endl;

	  gMuonChi2ndf->Fill(aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof());}
      
      if(p.numberOfValidHits() >= 11 && aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof()<= 10
	 && fabs(iTrack->dxy(RefVtx)) < 0.03 && fabs(iTrack->dz(RefVtx)) < 0.15 && iTrack->chi2()/iTrack->ndof() <= 4.0 )
	{gMuonnhits->Fill(q.numberOfValidMuonHits());}
      
      
      if(p.numberOfValidHits() >= 11 && aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof()<=10
	 && q.numberOfValidMuonHits()>= 1 && fabs(iTrack->dz(RefVtx)) < 0.15 && iTrack->chi2()/iTrack->ndof() <= 4.0 )
	{gMuonDxy->Fill(iTrack->dxy(RefVtx));}
      
      
      if(p.numberOfValidHits() >= 11 && aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof()<=10
         && q.numberOfValidMuonHits()>=1 && fabs(iTrack->dxy(RefVtx)) < 0.03 && iTrack->chi2()/iTrack->ndof() <= 4.0 )
	{gMuonZ->Fill(iTrack->dz(RefVtx));}
      
      
      if(p.numberOfValidHits() >= 11 && aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof()<= 10
         && q.numberOfValidMuonHits()>=1 && fabs(iTrack->dxy(RefVtx)) <= 0.03 && iTrack->dz(RefVtx)<=0.15)
	{gMuonChi2ndfTrack->Fill(iTrack->chi2()/iTrack->ndof());}
      
      
      if(p.numberOfValidHits() >= 11 && aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof()<=10
         && q.numberOfValidMuonHits()>=1 && fabs(iTrack->dxy(RefVtx)) <= 0.03 && iTrack->dz(RefVtx)<=0.15 && iTrack->chi2()/iTrack->ndof()<= 4.0){
	
	gMuonPtError->Fill(iTrack->ptError()/iTrack->pt());     
	gMuonfound->Fill(iTrack->found());
	gMuonPixel->Fill(p.pixelLayersWithMeasurement());
	gMuonSeg->Fill(aMuon->numberOfMatches());
	gMuonChamb->Fill(aMuon->numberOfChambers());
	
	if(aMuon->isIsolationValid()){
	  double SumPtMu = aMuon->isolationR03().sumPt;
	  double CalMu   = aMuon->isolationR03().emEt + aMuon->isolationR03().hadEt;
	  double IsoMu=(SumPtMu+CalMu)/aMuon->pt();
	  gMuonsIso->Fill(IsoMu); //not in all cuts and sel global still should not be
	}
	gMuonArb->Fill(muon::isGoodMuon(*aMuon, muon::TrackerMuonArbitrated, reco::Muon::NoArbitration));
	gMuonLastTight->Fill(muon::isGoodMuon(*aMuon, muon::TMLastStationAngTight, reco::Muon::NoArbitration));
	gMuonLastLoose->Fill(muon::isGoodMuon(*aMuon, muon::TMLastStationAngLoose, reco::Muon::NoArbitration));
	gMuonsPt->Fill(pt);
	gMuonsEta->Fill(eta);
	gMuonsPhi->Fill(phi);
      }
      
    }
    
    if(aMuon->isTrackerMuon()) {
      //cout<<" Tracker Muon "<<endl;
      TrackRef iTrack = aMuon->innerTrack();
      if(!iTrack.isAvailable()) continue;
      //cout<<" Tracker Muon2 "<<endl;
      const reco::HitPattern& p = iTrack->hitPattern();
      tMuonPixel->Fill(p.pixelLayersWithMeasurement());
      //cout<<" Tracker Muon3 "<<endl;
      tMuonfound->Fill(p.numberOfValidHits());
      //cout<<" Tracker Muon4 "<<endl;
      tMuonChi2ndfTrack->Fill(iTrack->chi2()/iTrack->ndof());
      tMuonDxy->Fill(iTrack->dxy(RefVtx));
      tMuonZ->Fill(iTrack->dz(RefVtx));
      tMuonsPt->Fill(pt);
      tMuonsEta->Fill(eta);
      tMuonsPhi->Fill(phi);
      //cout<<" Tracker Muon 5"<<endl;
    }
    if(aMuon->isStandAloneMuon()) {
      sMuonPtError->Fill(aMuon->outerTrack()->ptError()/aMuon->outerTrack()->pt()); 
      sMuonChi2ndf->Fill(aMuon->outerTrack()->chi2()/aMuon->outerTrack()->ndof());  
      sMuonSeg->Fill(aMuon->numberOfMatches());  
      sMuonChamb->Fill(aMuon->numberOfChambers()); 
      //cout<< " pt error "<<aMuon->outerTrack()->ptError()/aMuon->outerTrack()->pt()<<endl;
      //cout<<" chi2/ndf "<<aMuon->outerTrack()->chi2()/aMuon->outerTrack()->ndof()<<endl;
      //cout<<" number of matches "<<aMuon->numberOfMatches()<<endl;
      //cout<<" number of chambers "<<aMuon->numberOfChambers()<<endl;
      //TrackRef sta = aMuon->combinedMuon();
      sMuonnhits->Fill(aMuon->standAloneMuon()->numberOfValidHits());
      //sMuonDxy->Fill(fabs(aMuon->standAloneMuon()->dxy(RefVtx)));
      //sMuonZ->Fill(fabs(aMuon->standAloneMuon()->dz(RefVtx)));
      sMuonZ->Fill(aMuon->standAloneMuon()->dz(RefVtx));
      sMuonDxy->Fill(aMuon->standAloneMuon()->dxy(RefVtx));
      sMuonsPt->Fill(pt);
      sMuonsEta->Fill(eta);
      sMuonsPhi->Fill(phi);
    }
    

  }
 
  gMuonsNumber->Fill(GMuon);
 

  return;
}

bool DiMuonOnia2DPlots::allCutGlobal(const reco::Muon* aMuon) {
  
  if(!(aMuon->isGlobalMuon() && aMuon->isTrackerMuon()))
    return false;
  
  TrackRef iTrack = aMuon->innerTrack();
  if(!iTrack.isAvailable()) return false;
  const reco::HitPattern& p = iTrack->hitPattern();

  TrackRef gTrack = aMuon->globalTrack();
  const reco::HitPattern& q = aMuon->globalTrack()->hitPattern();

  return (
          //pp Z0 cuts
          isMuonInAccept(aMuon) &&
          p.numberOfValidHits() > 10 &&
	  aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof() <= 20.0 &&
          q.numberOfValidMuonHits() > 0 &&
	  fabs(iTrack->dxy(RefVtx)) <= 2.0 &&
          fabs(iTrack->dz(RefVtx)) <= 15.0 &&
          iTrack->chi2()/iTrack->ndof() <= 2.0
          );
    
}


bool DiMuonOnia2DPlots::matchPATMuon(const pat::Muon *pMuon) {
  

return(
	 
       (!pMuon->triggerObjectMatchesByFilter(fHLTFilterName).empty())  
       //!pMuon->triggerObjectMatchesByPath("HLT_HIL1DoubleMuOpen").empty()



	 );


 

}

//making new subrutine for PAT dimuons
void DiMuonOnia2DPlots::PATDiMuAnalyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    
  using namespace edm;
  using namespace std;
  using namespace pat;

  edm::Handle<edm::View<pat::CompositeCandidate> > diMuonsPATCand;   
  iEvent.getByLabel("onia2MuMuPatGlbGlb", diMuonsPATCand);
  
  if(!(diMuonsPATCand.isValid())) return;
  edm::View<pat::CompositeCandidate>dimuonsPATColl= *diMuonsPATCand; 
  for(size_t ii = 0; ii <dimuonsPATColl.size(); ++ ii) {
    const pat::CompositeCandidate &p = (dimuonsPATColl)[ii];
    
    //if((p.charge()==0 && p.userFloat("vProb") > 0.01)) continue;

    const reco::Candidate *dau0 = p.daughter(0);//      ->Clone().get();
    const pat::Muon *mu0 = dynamic_cast<const pat::Muon *>(dau0);
    const reco::Candidate *dau1 = p.daughter(1);    //->Clone().get();
    const pat::Muon *mu1 = dynamic_cast<const pat::Muon *>(dau1); 
    
    const pat::Muon *muonPos = 0, *muonNeg = 0;
    if(mu0->charge() > 0){ muonPos = mu0; muonNeg = mu1;}
    else if(mu0->charge() < 0){ muonPos = mu1; muonNeg = mu0;}
    

  if (( matchPATMuon(mu0) && matchPATMuon(mu1)) && (selPATMuon(mu0)&&selPATMuon(mu1))) {      
        
	diMuonsPATInvMassVsPt->Fill(p.mass(),p.pt());
	diMuonsPATInvMassVsY->Fill(p.mass(),p.rapidity());
	diMuonsPATInvMassVsCen->Fill(p.mass(),bin);
	}
	
 }  

}

void DiMuonOnia2DPlots::PATDiMuSameChargeAnalyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{


  edm::Handle<edm::View<pat::CompositeCandidate> > diMuonsPATCand;
  iEvent.getByLabel("onia2MuMuPatGlbGlb", diMuonsPATCand);
  edm::View<pat::CompositeCandidate>dimuonsPATColl= *diMuonsPATCand;


  for(size_t ii = 0; ii <dimuonsPATColl.size(); ++ ii) {

  const pat::CompositeCandidate &p = (dimuonsPATColl)[ii];
  //    const reco::Candidate &p = (dimuonsPATSameChargeColl)[ii];

    if(( !(p.charge()==0)  && p.userFloat("vProb") <0.01)){

      const reco::Candidate *dau0 = p.daughter(0)->masterClone().get();
      const pat::Muon *mu0 = dynamic_cast<const pat::Muon *>(dau0);
      
      const reco::Candidate *dau1 = p.daughter(1)->masterClone().get();
      const pat::Muon *mu1 = dynamic_cast<const pat::Muon *>(dau1);
      
      if (( matchPATMuon(mu0) && matchPATMuon(mu1)) && (selPATMuon(mu0)&&selPATMuon(mu1))) {
	diMuonsPATSameChargeInvMassVsPt->Fill(p.mass(),p.pt());
	diMuonsPATSameChargeInvMassVsY->Fill(p.mass(),p.rapidity());
	diMuonsPATSameChargeInvMassVsCen->Fill(p.mass(),bin);
      }
    }
  }
  
  edm::Handle<edm::View<reco::Candidate> > diMuonsPATSTASameChargeCand;
  iEvent.getByLabel("onia2MuMuPatGlbGlb", diMuonsPATSTASameChargeCand);
  edm::View<reco::Candidate>dimuonsPATSTASameChargeColl= *diMuonsPATSTASameChargeCand;
  
  for(size_t ii = 0; ii <dimuonsPATSTASameChargeColl.size(); ++ ii) {
    const reco::Candidate &p = (dimuonsPATSTASameChargeColl)[ii];
    const reco::Candidate *dau0 = p.daughter(0)->masterClone().get();
    const pat::Muon *mu0 = dynamic_cast<const pat::Muon *>(dau0);
    
    const reco::Candidate *dau1 = p.daughter(1)->masterClone().get();
    const pat::Muon *mu1 = dynamic_cast<const pat::Muon *>(dau1);
    
    if (( matchPATMuon(mu0) && matchPATMuon(mu1)) && (selPATSTAMuon(mu0)&&selPATSTAMuon(mu1))) {
      diMuonsPATSTASameChargeInvMassVsPt->Fill(p.mass(),p.pt());
      diMuonsPATSTASameChargeInvMassVsY->Fill(p.mass(),p.rapidity());
      diMuonsPATSTASameChargeInvMassVsCen->Fill(p.mass(),bin);
    }
  }
}


bool DiMuonOnia2DPlots::selPATMuon(const pat::Muon* aMuon) {
  
  if(!fisCuts) return true;
  if(!(aMuon->isGlobalMuon() && aMuon->isTrackerMuon()))
    return false;

  TrackRef iTrack = aMuon->innerTrack();
  if(!iTrack.isAvailable()) return false;
  const reco::HitPattern& p = iTrack->hitPattern();

  TrackRef gTrack = aMuon->globalTrack();
  const reco::HitPattern& q = aMuon->globalTrack()->hitPattern();
  
  return (
	  isMuonInAccept(aMuon) &&
          p.numberOfValidHits() > 10 &&
	  aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof() <= 20.0 &&
          q.numberOfValidMuonHits() > 0 &&
	  fabs(iTrack->dxy(RefVtx)) <= 2.0 &&
          fabs(iTrack->dz(RefVtx)) <= 15.0 &&
	  iTrack->chi2()/iTrack->ndof() <= 2.0
	  
	  //mu_innerTrackHits > 10
          //mu_pixeLayers > 0
          //mu_innerTrack_chi2NDOF < 2
          //mu_dxy < 0.1 cm          
          //mu_dz < 15. cm
          //mu_globalTrack_chi2NDOF < 20 
          //mu_validMuHits > 0
          //vProb > 0.01  

	  );
}


bool DiMuonOnia2DPlots::selPATSTAMuon(const pat::Muon* aMuon) {

  if(!fisCuts) return true;
  
  if(!(aMuon->isStandAloneMuon()))
    return false;


  
  return (
	 
	  isMuonInAccept(aMuon) &&
	  aMuon->standAloneMuon()->numberOfValidHits() >= 1 &&
	  aMuon->outerTrack()->ptError()/aMuon->outerTrack()->pt()<=1.0 &&
	  aMuon->outerTrack()->chi2()/aMuon->outerTrack()->ndof()<=10 &&
	  aMuon->numberOfMatches()>=1 &&
	  aMuon->numberOfChambers()>=2 &&
	  fabs(aMuon->standAloneMuon()->dxy(RefVtx)) <= 3 &&
	  fabs(aMuon->standAloneMuon()->dz(RefVtx)) <= 15 
 	  
	  );
}
	  

float DiMuonOnia2DPlots::FindWeight(float pt, float y)
{

  In->cd();  
  TH2D *WeightHisto = (TH2D*)In->Get("TwoDenDimuYPt");
  float wptbin= WeightHisto->GetYaxis()->FindBin(pt);
  float wrapbin= WeightHisto->GetXaxis()->FindBin(y);
  float w=WeightHisto->GetBinContent(wrapbin,wptbin);
  return(w);
 
}


float DiMuonOnia2DPlots::FindCenWeight(int Bin)
{

  float NCollArray[50]={1747.49,1566.92,1393.97,1237.02,1095.03,979.836,863.228,765.968,677.894,594.481,
		  522.453,456.049,399.178,347.174,299.925,258.411,221.374,188.676,158.896,135.117,
		  112.481,93.5697,77.9192,63.2538,52.0938,42.3553,33.7461,27.3213,21.8348,17.1722,
		  13.5661,10.6604,8.31383,6.37662,5.12347,3.73576,3.07268,2.41358,2.10707,1.76851, };

  return(
            
	  NCollArray[Bin]


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
  
  //cout<<" rbin "<<rbin<<endl;

  //--------------------------------------Reco DimuonGlobal ---------------------------------------------------------------------

  using namespace edm;
  using namespace std;
  using namespace pat;

  edm::Handle<edm::View<pat::CompositeCandidate> > diMuonsPATCand;
  iEvent.getByLabel("onia2MuMuPatGlbGlb", diMuonsPATCand);

  if(!(diMuonsPATCand.isValid())) return;

  edm::View<pat::CompositeCandidate>dimuonsPATColl= *diMuonsPATCand;

  JpsiNo=dimuonsPATColl.size();

  //cout<<" reco Jpsi size : "<<dimuonsPATColl.size()<<endl;
                                                                                                                                               
  
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
    //Trigger matches        
    //cout<<matchPATMuon(muonPos)<<" matches "<<matchPATMuon(muonNeg)<<endl;                                                                                                                                                                                                                  
    if(matchPATMuon(muonPos)) {muPos_matches=1;}
    if(matchPATMuon(muonNeg)) {muNeg_matches=1;}

    if(muonPos->isTrackerMuon()){muPos_tracker=1;}
    if(muonNeg->isTrackerMuon()){muNeg_tracker=1;}

    //cout<<muPos_tracker<<"    "<<muNeg_tracker<<endl;
    cout<<"muPos_matches "<<muPos_matches<<" muNeg_matches "<<muNeg_matches<<endl; 
    


    // cout<<"JpsiCharge " <<p.charge()<<endl;
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
  
  //  cout<<" fill tree called "<<endl;

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
    //cout<<" gbin "<<gbin<<endl;


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
    //cout<<"momId "<<momId<<endl;
    //JPsi
    //    if (abs(part.pdgId()) == 13 &&  momId == 443){
    
      //Upsilon 1s
    // if (abs(part.pdgId()) == 13 &&  momId == 553){
    
    //Upsilon 2s
    if (abs(part.pdgId()) == 13 &&  momId == 100553){



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
  
  
  //cout<<" nplus : "<<nplus<<"  "<<nminus<<endl;
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



