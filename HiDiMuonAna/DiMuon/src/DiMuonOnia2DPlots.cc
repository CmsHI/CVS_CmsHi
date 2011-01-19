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
// user include files   
#include "TH1.h"
#include "TH2.h"
#include "TH2F.h"
#include "TFile.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/FWLite/interface/TFileService.h"
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



using std::cout;
using std::endl;

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

  int bin;
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
  // virtual void SameChargePlots(const edm::Event&, const edm::EventSetup&);
  virtual void GenPlots(const edm::Event&, const edm::EventSetup& );
  virtual void GenAnalyze(const edm::Event&, const edm::EventSetup& );

  virtual void endJob() ;

  //virtual bool selGlobalMuon(const reco::Muon* aMuon); 
  
  virtual bool matchPATMuon(const pat::Muon *pMuon);
  virtual bool selPATMuon(const pat::Muon *pMuon);
  virtual bool selPATSTAMuon(const pat::Muon* aMuon);

 
  //virtual bool selSTAMuon(const reco::Muon* aMuon); 
  //virtual bool selTrackerMuon(const reco::Muon* aMuon);
  virtual bool isMuonInAccept(const reco::Muon* aMuon); 

  virtual void MuAnalyze(const edm::Event&, const edm::EventSetup&);
  virtual void PATDiMuAnalyze(const edm::Event&, const edm::EventSetup&);
  virtual void PATDiMuSameChargeAnalyze(const edm::Event&, const edm::EventSetup&);

  //virtual void printGlobalMuon(const reco::Muon* aMuon);  
  virtual void FillHistoCuts(double mass, double pt, const reco::Muon* Muon1, const reco::Muon* Muon2);

  virtual bool allCutGlobal(const reco::Muon* aMuon); 
  virtual bool allButOneCutGlobal(const reco::Muon* aMuon, int x);    

  virtual float FindWeight(float pt, float y);
  virtual float FindCenWeight(int Bin);


  math::XYZPoint RefVtx;
  float nPV;
  

 //edm::Service<TFileService> fs;

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
  cbins_(0),
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
  
    if(!cbins_) cbins_ = getCentralityBinsFromDB(iSetup);
  edm::Handle<reco::Centrality> cent;
  iEvent.getByLabel(edm::InputTag("hiCentrality"),cent);
  double hf = cent->EtHFhitSum();
  
   bin = cbins_->getBin(hf);
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
  hZVtx->Fill(RefVtx.Z());
  // Fill single muon histos
  MuAnalyze(iEvent, iSetup);
  





  //cout<<"generator info " <<fIsGenInfo.c_str()<<endl;                                                                                          
  //if(!strcmp(fIsGenInfo.c_str(),"TRUE")){GenPlots(iEvent, iSetup);}                                                                          
  if(!strcmp(fIsGenInfo.c_str(),"TRUE")){GenAnalyze(iEvent, iSetup);}    
      // Fill cuts histos
  //FillHistoCuts(p.mass(), p.pt(), mu0, mu1);

  
  // Same Charge plots   
  //SameChargePlots(iEvent, iSetup); 
  
  // cout<<" PAT info "<<fIsPATInfo.c_str()<<endl;  
  //PATDiMuAnalyze(iEvent,iSetup);
  if(!strcmp(fIsPATInfo.c_str(),"TRUE")){PATDiMuAnalyze(iEvent,iSetup);}
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
  //iEvent.getByLabel("genParticles",genPar) ;
  edm::View<reco::GenParticle> genParticles = *genPar ;
  
  TLorentzVector  genvector1, genvector2;

  double px1[10000], py1[10000], pz1[10000], px2[10000], py2[10000], pz2[10000]; 
  unsigned int nplus = 0, nminus =0;
  
  for(size_t i = 0; i < genParticles.size(); ++ i) {
    const reco::GenParticle& part = (*genPar)[i];
    const  Candidate *mom = part.mother();
   
    if(part.pdgId()==23 ){
      diMuonsGenInvMass->Fill(part.mass());
      diMuonsGenPt->Fill(part.pt());
      diMuonsGenRapidity->Fill(part.rapidity());
    }



 if (part.numberOfMothers()!=1) continue;
    int momId = mom->pdgId();
    



   if (abs(part.pdgId()) == 13 &&  momId == 23){
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
      
      if(abs(GenDiMuonY) <= 2.0 ){
	diMuonsGenInvMassVsPt->Fill(GenDiMuonMinv,GenDiMuonPt);
	diMuonsGenInvMassVsY->Fill(GenDiMuonMinv,GenDiMuonY);
	diMuonsGenInvMassVsCen->Fill(GenDiMuonMinv,bin);
	//cout<<" weight while gen level histo: "<<W<<endl;
	//cout<<"Gen Level bin "<<bin<<" NColl "<<NColl<<endl;
	diMuonsGenInvMassVsPtW->Fill(GenDiMuonMinv,GenDiMuonPt,W*NColl);
	diMuonsGenInvMassVsYW->Fill(GenDiMuonMinv,GenDiMuonY,W*NColl);
	diMuonsGenInvMassVsCenW->Fill(GenDiMuonMinv,bin,NColl*W);
      }
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
        double minv = sqrt(2.0*pt1[i]*pt2[j]*(TMath::CosH(eta1[i]-eta2[j])-TMath::Cos(phi1[i]-phi2[j])));
	W=FindWeight(genupt,genuy);
        NColl=FindCenWeight(bin);
	
	if(abs(genuy) <= 2.0){
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
	}
      } // for j                                                                                                                                                        
    } // for i                                                                                                                                                          
  }// if
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
DiMuonOnia2DPlots::beginJob()
{


  //In = new TFile("/afs/cern.ch/user/k/kumarv/scratch0/CMSSW_3_9_4/src/HiDiMuonAna/DiMuon/src/pythiaZ0_nofilter_CTEQ6L1_re6_totevt100000_2DAllDimu.root");
  //In = new TFile("/afs/cern.ch/user/k/kumarv/scratch0/CMSSW_3_9_4/src/HiDiMuonAna/DiMuon/src/pythiaZ0_nofilter_CTEQ6M_re6_totevt100000_ckin1_20_2DAllDimu_yz24_pt10cut_v3.root");
  In = new TFile("/afs/cern.ch/user/k/kumarv/scratch0/CMSSW_3_9_4/src/HiDiMuonAna/DiMuon/src/MCNLOZ0_nofilter_CTEQ6M_re9_totevt100000_2DAllDimu_yz24_pt10cut_v2.root");


  edm::Service<TFileService> fs;
  fOutputFile   = new TFile( fOutputFileName.c_str(), "RECREATE" );
  cout<<"begin job"<<endl;
      
  Centrality = new TH1F("Centrality","Centrality", 100,0,100);
   
  diMuonsGenInvMassVsPt = new TH2F("diMuonsGenInvMassVsPt", "diMuonsGenInvMassVsPt", 800, 0, 20, 200,0,100);
  diMuonsGenInvMassVsY = new TH2F("diMuonsGenInvMassVsY","diMuonsGenInvMassVsY",800, 0, 20,100, -5, 5);
  diMuonsGenInvMassVsCen = new TH2F("diMuonsGenInvMassVsCen","diMuonsGenInvMassVsCen", 800, 0, 20,100,0,100);

  diMuonsGenInvMassVsPtW = new TH2F("diMuonsGenInvMassVsPtW", "diMuonsGenInvMassVsPtW", 800, 0, 20, 200,0,100);
  diMuonsGenInvMassVsPtW->Sumw2();
  diMuonsGenInvMassVsYW = new TH2F("diMuonsGenInvMassVsYW","diMuonsGenInvMassVsYW",800, 0, 20,100, -5, 5);
  diMuonsGenInvMassVsYW->Sumw2();
  diMuonsGenInvMassVsCenW = new TH2F("diMuonsGenInvMassVsCenW","diMuonsGenInvMassVsCenW", 800, 0, 20,100,0,100);
  diMuonsGenInvMassVsCenW->Sumw2();

  diMuonsGenInvMass = new TH1F("diMuonsGenInvMass","diMuonsGenInvMass", 800,0,200);
  diMuonsGenPt = new TH1F("diMuonsGenPt","diMuonsGenPt", 100,0,20);
  diMuonsGenRapidity = new TH1F("diMuonsGenRapidity","diMuonsGenRapidity", 100,-10,10);

  // Global Histos

  //  diMuonsMass200 = new TH1F("diMuonsMass200", "diMuonsMass200", 800, 0, 1000);
  //diMuonsMass200Cut = new TH1F("diMuonsMass200Cut", "diMuonsMass200Cut", 800, 0, 1000);


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

  // Global histos

  // diMuonsMass200->Write();
  //diMuonsMass200Cut->Write();
  
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
 return (fabs(aMuon->eta()) < 2.4); 
  
  //return ( (fabs(aMuon->eta()) <= 2.4 && aMuon->pt() >= 10.0) ); 
  
  //  return (fabs(aMuon->eta()) < 2.4 &&
  //((fabs(aMuon->eta()) < 1.3 && aMuon->pt() >= 3.3) ||
  //(fabs(aMuon->eta()) >= 1.3 && fabs(aMuon->eta()) < 2.2 && aMuon->p() >= 2.9) ||
  //(fabs(aMuon->eta()) >= 2.2 && aMuon->pt() >= 0.8)));
}





void DiMuonOnia2DPlots::MuAnalyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  
{

  //All new cuts we can study here and see there disstributions 
  int imuplus =0, imuminus=0;
  int GMuon = 0, TMuon=0 , SAMuon=0;
  using namespace edm;
  using namespace std;
  using reco::TrackCollection;
  using reco::MuonCollection;
  
  edm::Handle<edm::View<pat::Muon> >tmuons;
  iEvent.getByLabel("patMuonsWithTrigger", tmuons);
  
  for(unsigned int j = 0; j <tmuons->size(); ++j){
    
    edm::RefToBase<pat::Muon> aMuon(tmuons, j);
  
    if (aMuon.isNull() ) continue;
    //cout<<" inside muon loop "<<endl;
    
    if(aMuon->isGlobalMuon()) GMuon++;
    if(aMuon->isTrackerMuon()) TMuon++;
    
    if((aMuon->isStandAloneMuon()) && (!aMuon->isGlobalMuon())) SAMuon++;
    
    float pt = aMuon->pt();
    float eta = aMuon->eta();
    float phi = aMuon->phi();
    int charge = aMuon->charge();
    
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
  
  //gMuonsNumberCut->Fill(GMuonCut);  
 ////  Print ///////
 //    cout << " +ive = " << imuplus << "   -ive  " << imuminus << endl; 
 //cout << " No. of Global Muons = " << GMuon << endl;
 //cout << " No. of Tracker Muons = " << TMuon << endl;
 // cout << " No. of StandAlone Muons = " << SAMuon << endl << endl;
}

void DiMuonOnia2DPlots::FillHistoCuts(double mass, double pt, const reco::Muon* Muon1, const reco::Muon* Muon2) {

  //You can study here effect of cuts on dimuons
  //cout<<"fill cut histo"<<endl;

  TrackRef iTrack1 = Muon1->innerTrack();
  if(!iTrack1.isAvailable()) return; 
  const reco::HitPattern& p1 = iTrack1->hitPattern();


  TrackRef gTrack1 = Muon1->globalTrack();
  //const reco::HitPattern& q1 = gTrack1->hitPattern();

  TrackRef iTrack2 = Muon2->innerTrack();
  if(!iTrack2.isAvailable()) return;
  const reco::HitPattern& p2 = iTrack2->hitPattern();
  
  TrackRef gTrack2 = Muon2->globalTrack();
  //const reco::HitPattern& q2 = gTrack2->hitPattern();

  dimu->Fill(mass,pt);
 
  //glb&&trk
  if((Muon1->isGlobalMuon() && Muon1->isTrackerMuon()) && (Muon2->isGlobalMuon() && Muon2->isTrackerMuon())) dimuGlbTrk->Fill(mass,pt);

  

  if(Muon1->isIsolationValid() && Muon2->isIsolationValid() ){
    
    double SumPtMu1 = Muon1->isolationR03().sumPt; 
    double CalMu1   = Muon1->isolationR03().emEt + Muon1->isolationR03().hadEt; 
    double IsoMu1=(SumPtMu1+CalMu1)/Muon1->pt();
  

    double SumPtMu2 = Muon2->isolationR03().sumPt;
    double CalMu2   = Muon2->isolationR03().emEt + Muon2->isolationR03().hadEt;
    double IsoMu2=(SumPtMu2+CalMu2)/Muon2->pt();

    if(IsoMu1<0.15 && IsoMu2<0.15) dimuIso->Fill(mass);
  }
  
 
  if(allButOneCutGlobal(Muon1,1) && allButOneCutGlobal(Muon2,1))dimuNOOFVALIDHITS->Fill(mass);					  
  if(allButOneCutGlobal(Muon1,2) && allButOneCutGlobal(Muon2,2)) dimuGLCHI2->Fill(mass);  
  if(allButOneCutGlobal(Muon1,3) && allButOneCutGlobal(Muon2,3)) dimuHITS->Fill(mass);
  if(allButOneCutGlobal(Muon1,4) && allButOneCutGlobal(Muon2,4)) dimuDXY->Fill(mass);
  if(allButOneCutGlobal(Muon1,5) && allButOneCutGlobal(Muon2,5)) dimuDZ->Fill(mass);
  if(allButOneCutGlobal(Muon1,6) && allButOneCutGlobal(Muon2,6))dimuTRKCHI2->Fill(mass);
  if(allButOneCutGlobal(Muon1,7) && allButOneCutGlobal(Muon2,7))dimuAllNoPt->Fill(mass,pt);


  if(allCutGlobal(Muon1) && allCutGlobal(Muon2)){
  
    if(p1.pixelLayersWithMeasurement() > 1  &&  p2.pixelLayersWithMeasurement() > 1) dimuPIX->Fill(mass);
    if(iTrack1->ptError()/iTrack1->pt() < 0.1 && iTrack2->ptError()/iTrack2->pt() < 0.1) dimuPTERROR->Fill(mass);  
    if(Muon1->numberOfChambers() >2.0  && Muon2->numberOfChambers() >2.0) dimuChamb->Fill(mass);
    if(Muon1->numberOfMatches() > 1.0  && Muon2->numberOfMatches() >1.0) dimuSeg->Fill(mass);
    if(fabs(iTrack1->dxy(RefVtx)) < 0.03  && fabs(iTrack2->dxy(RefVtx)) < 0.03) dimuD0->Fill(mass);
    if(iTrack1->found() > 11  &&  iTrack2->found() > 11)  dimuFOUND->Fill(mass);
    if( muon::isGoodMuon(*Muon1, muon::TrackerMuonArbitrated, reco::Muon::NoArbitration) && 
	muon::isGoodMuon(*Muon2, muon::TrackerMuonArbitrated, reco::Muon::NoArbitration) )  dimuARB->Fill(mass); 
    
    if(muon::isGoodMuon(*Muon1, muon::TMLastStationAngTight, reco::Muon::NoArbitration) &&
       muon::isGoodMuon(*Muon2, muon::TMLastStationAngTight, reco::Muon::NoArbitration) )  dimuLast->Fill(mass, pt);
    
    if(muon::isGoodMuon(*Muon1, muon::TMLastStationAngLoose, reco::Muon::NoArbitration) && 
       muon::isGoodMuon(*Muon2, muon::TMLastStationAngLoose, reco::Muon::NoArbitration) ) dimuLastLoose->Fill(mass, pt);
  }
  
  if(allCutGlobal(Muon1) && allCutGlobal(Muon2)) dimuAll->Fill(mass,pt);  

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
          p.numberOfValidHits() >= 11 &&
	  aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof() <= 10.0 &&
          q.numberOfValidMuonHits() >= 1 &&
	  fabs(iTrack->dxy(RefVtx)) <= 0.03 &&
          fabs(iTrack->dz(RefVtx)) <= 0.15 &&
          iTrack->chi2()/iTrack->ndof() <= 4.0
          );
    
}





bool DiMuonOnia2DPlots::allButOneCutGlobal(const reco::Muon* aMuon, int x){

 
  if(!(aMuon->isGlobalMuon() && aMuon->isTrackerMuon()))
    return false;
  
  //if(!isMuonInAccept(aMuon))
  //return false;
  //int MuPt = aMuon->pt();
  int MuEta = aMuon->eta();
  

  int MuonIn = isMuonInAccept(aMuon);

  //cout<<" muon eta pT cut "<<MuonIn<<endl;

  TrackRef iTrack = aMuon->innerTrack();
  if(!iTrack.isAvailable()) return false;
  const reco::HitPattern& p = iTrack->hitPattern();

  TrackRef gTrack = aMuon->globalTrack();
  const reco::HitPattern& q = aMuon->globalTrack()->hitPattern();
  
  int ValidTrackHits=p.numberOfValidHits();  
  float GlobalChi2Ndf=aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof();
  int ValidMuonHits=q.numberOfValidMuonHits();
  float Dxy =iTrack->dxy(RefVtx);
  float Dz=iTrack->dz(RefVtx);
  float TrackChi2Ndf=iTrack->chi2()/iTrack->ndof();
  
  

  if(x==1){return(  (MuonIn) &&    (GlobalChi2Ndf <= 10) && (ValidMuonHits >= 1) && (Dxy <= 0.03) && (Dz <= 0.15) && (TrackChi2Ndf <= 4.0));}
  
  if(x==2) return( (MuonIn) && ValidTrackHits >= 11.0 && ValidMuonHits >= 1 && Dxy <= 0.03 && Dz <= 0.15 && TrackChi2Ndf <= 4.0 );

  if(x==3) return( (MuonIn) && ValidTrackHits >= 11.0 &&  GlobalChi2Ndf <= 10.0 && Dxy <= 3.0 && Dz <= 0.15 && TrackChi2Ndf <= 4.0 );

  if(x==4) return( (MuonIn) && ValidTrackHits >= 11.0 &&  GlobalChi2Ndf <= 10.0 && ValidMuonHits >= 1 && Dz <= 0.15 && TrackChi2Ndf<= 4.0 );

  if(x==5) return( (MuonIn) && ValidTrackHits >= 11.0 &&  GlobalChi2Ndf <= 10.0 && ValidMuonHits >= 1 && Dxy <= 0.03 && TrackChi2Ndf<= 4.0 );

  if(x==6) return( (MuonIn) && ValidTrackHits >= 11.0 &&  GlobalChi2Ndf <= 10.0 && ValidMuonHits >= 1 && Dxy <= 0.03 && Dz <= 0.15 );

  if(x==7) return( (abs(MuEta)<= 2.4) && ValidTrackHits >= 11.0 &&  GlobalChi2Ndf <= 10.0 && ValidMuonHits >= 1 && Dxy <= 0.03 && Dz <= 0.15 && TrackChi2Ndf <= 4.0);


  return true;
        
         
}






bool DiMuonOnia2DPlots::matchPATMuon(const pat::Muon *pMuon) {
  

  //cout<<" hlt filter name : "<<fHLTFilterName<<endl;

return(
	 
	 (
	  
	  !pMuon->triggerObjectMatchesByFilter(fHLTFilterName).empty())  
	
	  );


 

}



//making new subrutine for PAT dimuons
void DiMuonOnia2DPlots::PATDiMuAnalyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  

  //edm::Handle<edm::View<reco::Candidate> > diMuonsPATCand;
  edm::Handle<edm::View<reco::Candidate> > diMuonsPATCand;
  iEvent.getByLabel("onia2MuMuPatGlbGlb", diMuonsPATCand);
  edm::View<reco::Candidate>dimuonsPATColl= *diMuonsPATCand;
    
  for(size_t ii = 0; ii <dimuonsPATColl.size(); ++ ii) {
    const reco::Candidate &p = (dimuonsPATColl)[ii];
   

    //const reco::Candidate *dau0 = p.daughter(0)->masterClone().get();
    
    const reco::Candidate *dau0 = p.daughter(0);//      ->Clone().get();
    const pat::Muon *mu0 = dynamic_cast<const pat::Muon *>(dau0);
    
    const reco::Candidate *dau1 = p.daughter(1);    //->Clone().get();
    
    const pat::Muon *mu1 = dynamic_cast<const pat::Muon *>(dau1); 
    
    FillHistoCuts(p.mass(), p.pt(), mu0, mu1);       

    if (( matchPATMuon(mu0) && matchPATMuon(mu1)) && (selPATMuon(mu0)&&selPATMuon(mu1))) {
          
      diMuonsPATInvMassVsPt->Fill(p.mass(),p.pt());
      diMuonsPATInvMassVsY->Fill(p.mass(),p.rapidity());
      diMuonsPATInvMassVsCen->Fill(p.mass(),bin);
    }
  }
}

void DiMuonOnia2DPlots::PATDiMuSameChargeAnalyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  edm::Handle<edm::View<reco::Candidate> > diMuonsPATSameChargeCand;
  iEvent.getByLabel("onia2MuMuPatGlbGlb", diMuonsPATSameChargeCand);
  edm::View<reco::Candidate>dimuonsPATSameChargeColl= *diMuonsPATSameChargeCand;

  for(size_t ii = 0; ii <dimuonsPATSameChargeColl.size(); ++ ii) {
    const reco::Candidate &p = (dimuonsPATSameChargeColl)[ii];
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
          p.numberOfValidHits() >= 11 &&
	  aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof() <= 10.0 &&
          q.numberOfValidMuonHits() >= 1 &&
          iTrack->ptError()/iTrack->pt() <= 0.1 &&
          
	  fabs(iTrack->dxy(RefVtx)) <= 0.03 &&
          fabs(iTrack->dz(RefVtx)) <= 0.15 &&
          
	  iTrack->chi2()/iTrack->ndof() <= 4.0
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

  //float NCollArray[50];

  float NCollArray[50]={1747.49,1566.92,1393.97,1237.02,1095.03,979.836,863.228,765.968,677.894,594.481,
		  522.453,456.049,399.178,347.174,299.925,258.411,221.374,188.676,158.896,135.117,
		  112.481,93.5697,77.9192,63.2538,52.0938,42.3553,33.7461,27.3213,21.8348,17.1722,
		  13.5661,10.6604,8.31383,6.37662,5.12347,3.73576,3.07268,2.41358,2.10707,1.76851, };

  return(
            
	  NCollArray[Bin]


	 );

}


//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonOnia2DPlots);



