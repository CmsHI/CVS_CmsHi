// -*- C++ -*-
//
// Package:    DiMuon2DPlots
// Class:      DiMuon2DPlots
// 
/**\class DiMuon2DPlots DiMuon2DPlots.cc DiMuonAna/DiMuon2DPlots/src/DiMuon2DPlots.cc
   
 Description: [one line class summary]
 
 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Dilep PING, Vineet Kumar, Prashant Shukla
//         Created:  Wed May 12 13:45:14 CEST 2010
// $Id: DiMuon2DPlots.cc,v 1.11 2010/11/20 14:45:22 pshukla Exp $
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

class DiMuon2DPlots : public edm::EDAnalyzer {
   public:
  explicit DiMuon2DPlots(const edm::ParameterSet&);
  ~DiMuon2DPlots();
  
  const CentralityBins *cbins_;
  CentralityProvider * centrality_;  
  std::string fOutputFileName;

  std::string fIsGenInfo;
  bool fisCuts;

  //edm::InputTag fdimuonCandTag;
  //std::string fhistName;
  //std::string fhistName1;

  TFile *fOutputFile ;
  TH1F *Centrality;

  TH2F *diMuonsGlobalInvMassVsPt;
  TH2F *diMuonsGlobalInvMassVsPtY08;
  TH2F *diMuonsGlobalInvMassVsPtY10;
  TH2F *diMuonsGlobalInvMassVsPtY12;
  TH2F *diMuonsGlobalInvMassVsPtY16;
  TH2F *diMuonsGlobalInvMassVsPtY20;
 



  TH2F *diMuonsGlobalInvMassVsY;   
  TH2F *diMuonsGlobalInvMassVsCen;

  TH2F *diMuonsGlobalInvMassVsPtBRL;
  TH2F *diMuonsGlobalInvMassVsYBRL;
  TH2F *diMuonsGlobalInvMassVsCenBRL;
  
  TH2F *diMuonsGlobalInvMassVsPtEtaCut;
  TH2F *diMuonsGlobalInvMassVsPtPtCut;
  TH2F *diMuonsGlobalInvMassVsYPtCut;
  TH2F *diMuonsGlobalInvMassVsYEtaCut; 
  
  TH2F *diMuonsGlobalInvMassVsCenPtCut;
  TH2F *diMuonsGlobalInvMassVsCenEtaCut;

 
  TH2F *diMuonsGlobalSTAInvMassVsPt;
  TH2F *diMuonsGlobalSTAInvMassVsY;
  TH2F *diMuonsGlobalSTAInvMassVsCen;
  
  TH2F *diMuonsSTAInvMassVsPt;
  TH2F *diMuonsSTAInvMassVsY;
  TH2F *diMuonsSTAInvMassVsCen;

  TH2F *diMuonsGlobalSameChargeInvMassVsPt;
 
  TH2F *diMuonsGlobalSameChargeInvMassVsPtY08;
  TH2F *diMuonsGlobalSameChargeInvMassVsPtY10;
  TH2F *diMuonsGlobalSameChargeInvMassVsPtY12;
  TH2F *diMuonsGlobalSameChargeInvMassVsPtY16;
  TH2F *diMuonsGlobalSameChargeInvMassVsPtY20;
  

  TH2F *diMuonsGlobalSameChargeInvMassVsY;
  TH2F *diMuonsGlobalSameChargeInvMassVsCen;

  TH2F *diMuonsGlobalSameChargeInvMassVsPtBRL;
  TH2F *diMuonsGlobalSameChargeInvMassVsYBRL;
  TH2F *diMuonsGlobalSameChargeInvMassVsCenBRL;

  TH2F *diMuonsGlobalSameChargeInvMassVsPtEtaCut; 
  TH2F *diMuonsGlobalSameChargeInvMassVsPtPtCut;

  TH2F *diMuonsGlobalSameChargeInvMassVsYPtCut; 
  TH2F *diMuonsGlobalSameChargeInvMassVsYEtaCut; 

  TH2F *diMuonsGlobalSameChargeInvMassVsCenPtCut;
  TH2F *diMuonsGlobalSameChargeInvMassVsCenEtaCut; 


  TH2F *diMuonsGlobalSTASameChargeInvMassVsPt;
  TH2F *diMuonsGlobalSTASameChargeInvMassVsY;
  TH2F *diMuonsGlobalSTASameChargeInvMassVsCen;

  TH2F *diMuonsSTASameChargeInvMassVsPt;
  TH2F *diMuonsSTASameChargeInvMassVsY;
  TH2F *diMuonsSTASameChargeInvMassVsCen;
  
  TH2F *diMuonsGenInvMassVsPt;
  TH2F *diMuonsGenInvMassVsY;
  TH2F *diMuonsGenInvMassVsCen;
  
  TH1F *diMuonsGenInvMass;
  TH1F *diMuonsGenPt;
  TH1F *diMuonsGenRapidity;

  // Global 

  TH1F *diMuonsMass200;
  TH1F *diMuonsMass200Cut;
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

  TH1F *sMuonsPt;
  TH1F *sMuonsEta;
  TH1F *sMuonsPhi;

  TH1F *hZVtx;

  int bin;

  // Cut histograms

  TH2F *dimu;
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



  TH1F *dimuAll;




private:
  
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void SameChargePlots(const edm::Event&, const edm::EventSetup&);
  virtual void GenPlots(const edm::Event&, const edm::EventSetup& );
  virtual void GenAnalyze(const edm::Event&, const edm::EventSetup& );

  virtual void endJob() ;

  virtual bool selGlobalMuon(const reco::Muon* aMuon); 
  virtual bool selSTAMuon(const reco::Muon* aMuon); 
  virtual bool selTrackerMuon(const reco::Muon* aMuon);
  virtual bool isMuonInAccept(const reco::Muon* aMuon); 

  virtual void MuAnalyze(const edm::Event&, const edm::EventSetup&);
  virtual void printGlobalMuon(const reco::Muon* aMuon);  
  virtual void FillHistoCuts(double mass, double pt, const reco::Muon* Muon1, const reco::Muon* Muon2);

  virtual bool allCutGlobal(const reco::Muon* aMuon); 
    
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


DiMuon2DPlots::DiMuon2DPlots(const edm::ParameterSet& iConfig):
  cbins_(0),fOutputFileName(iConfig.getUntrackedParameter<string>("OutputFileName")),fIsGenInfo(iConfig.getUntrackedParameter<string>("IsGenInfo")), fisCuts(iConfig.getUntrackedParameter<bool>("IsCuts") ),
  Centrality(0),diMuonsGlobalInvMassVsPt(0),diMuonsGlobalInvMassVsY(0),diMuonsGlobalInvMassVsCen(0), diMuonsGlobalInvMassVsPtBRL(0),diMuonsGlobalInvMassVsYBRL(0),diMuonsGlobalInvMassVsCenBRL(0),diMuonsGlobalSTAInvMassVsPt(0),diMuonsGlobalSTAInvMassVsY(0),diMuonsGlobalSTAInvMassVsCen(0),diMuonsSTAInvMassVsPt(0),diMuonsSTAInvMassVsY(0),diMuonsSTAInvMassVsCen(0),diMuonsGlobalSameChargeInvMassVsPt(0),diMuonsGlobalSameChargeInvMassVsY(0),diMuonsGlobalSameChargeInvMassVsCen(0),diMuonsGlobalSTASameChargeInvMassVsPt(0),diMuonsGlobalSTASameChargeInvMassVsY(0),diMuonsGlobalSTASameChargeInvMassVsCen(0),diMuonsSTASameChargeInvMassVsPt(0),diMuonsSTASameChargeInvMassVsY(0),diMuonsSTASameChargeInvMassVsCen(0),diMuonsGenInvMassVsPt(0),diMuonsGenInvMassVsY(0),diMuonsGenInvMassVsCen(0),diMuonsGenInvMass(0),diMuonsGenPt(0),diMuonsGenRapidity(0)
			    //fdimuonCandTag(iConfig.getUntrackedParameter<edm::InputTag>("dimuonCandTag")),
			    //fhistName(iConfig.getUntrackedParameter<string>("histName")),
{ 

//now do what ever initialization is needed

}


DiMuon2DPlots::~DiMuon2DPlots()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
DiMuon2DPlots::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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
  int nbins = cbins_->getNbins();
  int binsize = 100/nbins;
  char* binName = Form("%d to % d",bin*binsize,(bin+1)*binsize);
  
  // Primary Vertex
  Handle<reco::VertexCollection> privtxs;
  iEvent.getByLabel("hiSelectedVertex", privtxs);
  VertexCollection::const_iterator privtx;
  
  nPV = privtxs->size();

  if(!nPV) return; 
  
  if ( privtxs->begin() != privtxs->end() ) {
    privtx=privtxs->begin();
    RefVtx = privtx->position();
    //float d0err = sqrt ( (privtxs->begin()->xError()*privtxs->begin()->yError()) );
    //float dzerr = sqrt ( (privtxs->begin()->zError()*privtxs->begin()->zError()) );



  } else {
    RefVtx.SetXYZ(0.,0.,0.);
  }

  //  RefVtx.SetXYZ(0.,0.,0.);

  hZVtx->Fill(RefVtx.Z());
  //  if (fabs(RefVtx.Z()) > _iConfig.getParameter< double > ("maxAbsZ")) return 0;
  //  hPileUp->Fill(nPV);


  // Fill single muon histos
  MuAnalyze(iEvent, iSetup);
  

  // get dimuonGlobal collection
  edm::Handle<edm::View<reco::Candidate> > diMuonsGlobalCand;
  iEvent.getByLabel("dimuonsGlobal", diMuonsGlobalCand);
  edm::View<reco::Candidate>dimuonsGlobalColl= *diMuonsGlobalCand;
  //  int dimuonsGlobalSize =dimuonsGlobalColl.size();
  //cout<<" no of dimuon Global  :" <<dimuonsGlobalSize <<endl;
  for(size_t ii = 0; ii <dimuonsGlobalColl.size(); ++ ii) {
    const reco::Candidate& p = (dimuonsGlobalColl)[ii];
    
    const reco::Candidate *dau0 = p.daughter(0)->masterClone().get();
    const reco::Muon *mu0 = dynamic_cast<const reco::Muon *>(dau0);
    
    const reco::Candidate *dau1 = p.daughter(1)->masterClone().get();
    const reco::Muon *mu1 = dynamic_cast<const reco::Muon *>(dau1);

    diMuonsMass200->Fill(p.mass());

    if (p.mass() > 50.0) {
      cout << " *************** High Mass Event ******************* " << endl;
      cout << " Zvtx = " <<  RefVtx.Z()  << endl;
      cout<< "centrality bin : " << binName << " id : " << bin <<endl;

      cout << "   Mass,   pt,    eta,   rapidity " << endl;

      cout << p.mass()<< "    " << p.pt() << "    " << p.eta() << "     " << p.rapidity()  << endl << endl;
 
      cout << " properties of Muon 1 " << endl;
      printGlobalMuon(mu0);
      cout << endl;
      cout << " properties of Muon 2 " << endl;
      printGlobalMuon(mu1);
    }  

    // Fill cuts histos
    FillHistoCuts(p.mass(), p.pt(), mu0, mu1);
 
    if ( selGlobalMuon(mu0) && selGlobalMuon(mu1)) {
      diMuonsMass200Cut->Fill(p.mass());
      diMuonsGlobalInvMassVsPt->Fill(p.mass(),p.pt());
      diMuonsGlobalInvMassVsY->Fill(p.mass(),p.rapidity());
      diMuonsGlobalInvMassVsCen->Fill(p.mass(),bin);
      
      if(abs(p.rapidity())<0.8)diMuonsGlobalInvMassVsPtY08->Fill(p.mass(),p.pt());
      if(abs(p.rapidity())<1.0)diMuonsGlobalInvMassVsPtY10->Fill(p.mass(),p.pt());
      if(abs(p.rapidity())<1.2)diMuonsGlobalInvMassVsPtY12->Fill(p.mass(),p.pt());
      if(abs(p.rapidity())<1.6)diMuonsGlobalInvMassVsPtY16->Fill(p.mass(),p.pt());
      if(abs(p.rapidity())<2.0)diMuonsGlobalInvMassVsPtY20->Fill(p.mass(),p.pt());

      // Barrel
      if (fabs(mu0->eta()) < 0.8 && fabs(mu1->eta()) < 0.8 ) {
	diMuonsGlobalInvMassVsPtBRL->Fill(p.mass(),p.pt());
	diMuonsGlobalInvMassVsYBRL->Fill(p.mass(),p.rapidity());
	diMuonsGlobalInvMassVsCenBRL->Fill(p.mass(),bin);
      }
      //eta < 1.2
      if (fabs(mu0->eta()) < 1.2 && fabs(mu1->eta()) < 1.2 ) {
	diMuonsGlobalInvMassVsPtEtaCut->Fill(p.mass(),p.pt());
	diMuonsGlobalInvMassVsYEtaCut->Fill(p.mass(),p.rapidity());
	diMuonsGlobalInvMassVsCenEtaCut->Fill(p.mass(),bin);
      }
      //pT>4
      if (mu0->pt()> 4 && mu1->pt()> 4) {
	diMuonsGlobalInvMassVsPtPtCut->Fill(p.mass(),p.pt());
	diMuonsGlobalInvMassVsYPtCut->Fill(p.mass(),p.rapidity());
	diMuonsGlobalInvMassVsCenPtCut->Fill(p.mass(),bin);
      }
    }
  }


  // get dimuonGlobalSA collection
  edm::Handle<edm::View<reco::Candidate> > diMuonsGlobalSTACand;
  iEvent.getByLabel("dimuonsGlobalSTA", diMuonsGlobalSTACand);
  edm::View<reco::Candidate>dimuonsGlobalSTAColl= *diMuonsGlobalSTACand;
  //  int dimuonsGlobalSTASize =dimuonsGlobalSTAColl.size();
  //cout<<" no of dimuonsGlobalSTA  :" <<dimuonsGlobalSTASize <<endl;
  for(size_t ii = 0; ii <dimuonsGlobalSTAColl.size(); ++ ii) {
    const reco::Candidate& p = (dimuonsGlobalSTAColl)[ii];

    const reco::Candidate *dau0 = p.daughter(0)->masterClone().get();
    const reco::Muon *mu0 = dynamic_cast<const reco::Muon *>(dau0);

    const reco::Candidate *dau1 = p.daughter(1)->masterClone().get();
    const reco::Muon *mu1 = dynamic_cast<const reco::Muon *>(dau1);

    //histContainer2D["diMuonInvMassVsPt"]->Fill(p.mass(),p.pt());

    if ( selGlobalMuon(mu0) && selSTAMuon(mu1)) {
      diMuonsGlobalSTAInvMassVsPt->Fill(p.mass(),p.pt());
      diMuonsGlobalSTAInvMassVsY->Fill(p.mass(),p.rapidity());
      diMuonsGlobalSTAInvMassVsCen->Fill(p.mass(),bin);
    }
  }
  
  // get dimuonSTA collection 
  edm::Handle<edm::View<reco::Candidate> > diMuonsSTACand;
  iEvent.getByLabel("dimuonsSTA", diMuonsSTACand);
  edm::View<reco::Candidate>dimuonsSTAColl= *diMuonsSTACand;
  //  int dimuonsSTASize =dimuonsSTAColl.size();
  //cout<<" no of dimuonsSTA  :" <<dimuonsSTASize <<endl;
  for(size_t ii = 0; ii <dimuonsSTAColl.size(); ++ ii) {
    const reco::Candidate& p = (dimuonsSTAColl)[ii];

    const reco::Candidate *dau0 = p.daughter(0)->masterClone().get();
    const reco::Muon *mu0 = dynamic_cast<const reco::Muon *>(dau0);

    const reco::Candidate *dau1 = p.daughter(1)->masterClone().get();
    const reco::Muon *mu1 = dynamic_cast<const reco::Muon *>(dau1);

    //histContainer2D["diMuonInvMassVsPt"]->Fill(p.mass(),p.pt());

    if ( selSTAMuon(mu0) && selSTAMuon(mu1)) {
      diMuonsSTAInvMassVsPt->Fill(p.mass(),p.pt());
      diMuonsSTAInvMassVsY->Fill(p.mass(),p.rapidity());
      diMuonsSTAInvMassVsCen->Fill(p.mass(),bin);
    }
  }


  // Same Charge plots   
  SameChargePlots(iEvent, iSetup);
  /////////////////////////

  //cout<<"generator info " <<fIsGenInfo.c_str()<<endl;
  
    if(!strcmp(fIsGenInfo.c_str(),"TRUE")){GenPlots(iEvent, iSetup);}
    //if(!strcmp(fIsGenInfo.c_str(),"TRUE")){GenAnalyze(iEvent, iSetup);}

  cout << " --------------------------------------------------------- " << endl;  

}

/////////

void DiMuon2DPlots::SameChargePlots(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  
  // get dimuonGlobal same charge collection                                                                                                               
  edm::Handle<edm::View<reco::Candidate> > diMuonsGlobalSameChargeCand;
  iEvent.getByLabel("dimuonsGlobalSameCharge", diMuonsGlobalSameChargeCand);
  edm::View<reco::Candidate>dimuonsGlobalSameChargeColl= *diMuonsGlobalSameChargeCand;
  //  int dimuonsGlobalSameChargeSize =dimuonsGlobalSameChargeColl.size();
  //cout<<" no of dimuon Global same charge  :" <<dimuonsGlobalSameChargeSize <<endl;
  for(size_t ii = 0; ii <dimuonsGlobalSameChargeColl.size(); ++ ii) {
    const reco::Candidate& p = (dimuonsGlobalSameChargeColl)[ii];

    const reco::Candidate *dau0 = p.daughter(0)->masterClone().get();
    const reco::Muon *mu0 = dynamic_cast<const reco::Muon *>(dau0);

    const reco::Candidate *dau1 = p.daughter(1)->masterClone().get();
    const reco::Muon *mu1 = dynamic_cast<const reco::Muon *>(dau1);

    //histContainer2D["diMuonInvMassVsPt"]->Fill(p.mass(),p.pt());                                                                        
    if ( selGlobalMuon(mu0) && selGlobalMuon(mu1)) {
      diMuonsGlobalSameChargeInvMassVsPt->Fill(p.mass(),p.pt());
      
      if(abs(p.rapidity())<0.8)diMuonsGlobalSameChargeInvMassVsPtY08->Fill(p.mass(),p.pt());
      if(abs(p.rapidity())<1.0)diMuonsGlobalSameChargeInvMassVsPtY10->Fill(p.mass(),p.pt());
      if(abs(p.rapidity())<1.2)diMuonsGlobalSameChargeInvMassVsPtY12->Fill(p.mass(),p.pt());
      if(abs(p.rapidity())<1.6)diMuonsGlobalSameChargeInvMassVsPtY16->Fill(p.mass(),p.pt());
      if(abs(p.rapidity())<2.0)diMuonsGlobalSameChargeInvMassVsPtY20->Fill(p.mass(),p.pt());


      diMuonsGlobalSameChargeInvMassVsY->Fill(p.mass(),p.rapidity());
      diMuonsGlobalSameChargeInvMassVsCen->Fill(p.mass(),bin);

      if ( fabs(mu0->eta()) < 0.8 && fabs(mu1->eta()) < 0.8 ) {
	diMuonsGlobalSameChargeInvMassVsPtBRL->Fill(p.mass(),p.pt());
	diMuonsGlobalSameChargeInvMassVsYBRL->Fill(p.mass(),p.rapidity());
	diMuonsGlobalSameChargeInvMassVsCenBRL->Fill(p.mass(),bin);
      }
      


      //eta 1.2                                                                                                                                          

      if (fabs(mu0->eta()) < 1.2 && fabs(mu1->eta()) < 1.2 ) {
        diMuonsGlobalSameChargeInvMassVsPtEtaCut->Fill(p.mass(),p.pt());
        diMuonsGlobalSameChargeInvMassVsYEtaCut->Fill(p.mass(),p.rapidity());
        diMuonsGlobalSameChargeInvMassVsCenEtaCut->Fill(p.mass(),bin);
      }


      //pT>4                                                                                                                                                  
      if (mu0->pt()> 4 && mu1->pt()> 4) {
        diMuonsGlobalSameChargeInvMassVsPtPtCut->Fill(p.mass(),p.pt());
        diMuonsGlobalSameChargeInvMassVsYPtCut->Fill(p.mass(),p.rapidity());
        diMuonsGlobalSameChargeInvMassVsCenPtCut->Fill(p.mass(),bin);
      }

    }
    
  }


  // get dimuonGlobal STA same charge collection 
  edm::Handle<edm::View<reco::Candidate> > diMuonsGlobalSTASameChargeCand;
  iEvent.getByLabel("dimuonsGlobalSTASameCharge", diMuonsGlobalSTASameChargeCand);
  edm::View<reco::Candidate>dimuonsGlobalSTASameChargeColl= *diMuonsGlobalSTASameChargeCand;
  //  int dimuonsGlobalSTASameChargeSize =dimuonsGlobalSTASameChargeColl.size();
  //cout<<" no of dimuon Global STA same charge  :" <<dimuonsGlobalSTASameChargeSize <<endl;
  for(size_t ii = 0; ii <dimuonsGlobalSTASameChargeColl.size(); ++ ii) {
    const reco::Candidate& p = (dimuonsGlobalSTASameChargeColl)[ii];

    const reco::Candidate *dau0 = p.daughter(0)->masterClone().get();
    const reco::Muon *mu0 = dynamic_cast<const reco::Muon *>(dau0);

    const reco::Candidate *dau1 = p.daughter(1)->masterClone().get();
    const reco::Muon *mu1 = dynamic_cast<const reco::Muon *>(dau1);

    //histContainer2D["diMuonInvMassVsPt"]->Fill(p.mass(),p.pt());                                                                          
    if ( selGlobalMuon(mu0) && selSTAMuon(mu1)) {
      diMuonsGlobalSTASameChargeInvMassVsPt->Fill(p.mass(),p.pt());
      diMuonsGlobalSTASameChargeInvMassVsY->Fill(p.mass(),p.rapidity());
      diMuonsGlobalSTASameChargeInvMassVsCen->Fill(p.mass(),bin);
    } 
 }
  
  
  // get dimuon sta same charge collection                                                                                                                                                           
  edm::Handle<edm::View<reco::Candidate> > diMuonsSTASameChargeCand;
  iEvent.getByLabel("dimuonsSTASameCharge", diMuonsSTASameChargeCand);
  edm::View<reco::Candidate>dimuonsSTASameChargeColl= *diMuonsSTASameChargeCand;
  //  int dimuonsSTASameChargeSize =dimuonsSTASameChargeColl.size();
  //cout<<" no of dimuon STA same charge  :" <<dimuonsSTASameChargeSize <<endl;
  for(size_t ii = 0; ii <dimuonsSTASameChargeColl.size(); ++ ii) {
    const reco::Candidate& p = (dimuonsSTASameChargeColl)[ii];
    //histContainer2D["diMuonInvMassVsPt"]->Fill(p.mass(),p.pt());                                                                                                                                   
    const reco::Candidate *dau0 = p.daughter(0)->masterClone().get();
    const reco::Muon *mu0 = dynamic_cast<const reco::Muon *>(dau0);

    const reco::Candidate *dau1 = p.daughter(1)->masterClone().get();
    const reco::Muon *mu1 = dynamic_cast<const reco::Muon *>(dau1);

    if ( selSTAMuon(mu0) && selSTAMuon(mu1)) {
      diMuonsSTASameChargeInvMassVsPt->Fill(p.mass(),p.pt());
      diMuonsSTASameChargeInvMassVsY->Fill(p.mass(),p.rapidity());
      diMuonsSTASameChargeInvMassVsCen->Fill(p.mass(),bin);
    }
    
  }
}



void DiMuon2DPlots::GenPlots(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  float mumass =0.105658389;
  //cout<<"gen info: "<<endl;
  using namespace edm;
  using namespace std;
  
  edm::Handle<edm::View<reco::GenParticle> >genPar ;
  iEvent.getByLabel("hiGenParticles",genPar) ;
  edm::View<reco::GenParticle> genParticles = *genPar ;
  
  TLorentzVector  genvector1, genvector2;

  double px1[10000], py1[10000], pz1[10000], px2[10000], py2[10000], pz2[10000]; 
  unsigned int nplus = 0, nminus =0;
  
  for(size_t i = 0; i < genParticles.size(); ++ i) {
    const reco::GenParticle& part = (*genPar)[i];
    const  Candidate *mom = part.mother();
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
      //cout<<" gen Inv Mass "<<GenDiMuonMinv<<endl;
      float GenDiMuonPt =genvector3.Pt();
      diMuonsGenInvMassVsPt->Fill(GenDiMuonMinv,GenDiMuonPt);
      diMuonsGenInvMassVsY->Fill(GenDiMuonMinv,GenDiMuonY);
      diMuonsGenInvMassVsCen->Fill(GenDiMuonMinv,bin);
      diMuonsGenInvMass->Fill(GenDiMuonMinv);
      diMuonsGenPt->Fill(GenDiMuonPt);
      diMuonsGenRapidity->Fill(GenDiMuonY);
    }
  }
}

void DiMuon2DPlots::GenAnalyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
  using namespace HepMC;
  using namespace edm;
  edm::Handle<HepMCProduct> evt;
  
  //iEvent.getByLabel("source", evt);
  //iEvent.getByLabel("generator", evt);
  iEvent.getByLabel("hiSignal", evt);
  
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
   
    //if(eta < -2.4 || eta > 2.4) continue;                                                                                                                           

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
	diMuonsGenInvMassVsPt->Fill(minv,genupt);
        diMuonsGenInvMassVsY->Fill(minv,genuy);
        diMuonsGenInvMassVsCen->Fill(minv,bin);
        diMuonsGenInvMass->Fill(minv);
        diMuonsGenPt->Fill(genupt);
        diMuonsGenRapidity->Fill(genuy);
      } // for j                                                                                                                                                        
    } // for i                                                                                                                                                          
  }// if
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
DiMuon2DPlots::beginJob()
{
  edm::Service<TFileService> fs;
  fOutputFile   = new TFile( fOutputFileName.c_str(), "RECREATE" );
  cout<<"begin job"<<endl;
  //if (!fOutputFile) cout<<"File not open "<<endl;
  //fOutputFile->cd();
  //diMuonInvMassVsPt = new TH2F(fhistName.c_str(), fhistName.c_str(), 100, 0, 100, 100, 0, 200);

  diMuonsGlobalInvMassVsPt = new TH2F("diMuonsGlobalInvMassVsPt", "diMuonsGlobalInvMassVsPt", 8000, 0, 200, 200,0,100);

  diMuonsGlobalInvMassVsPtY08 = new TH2F("diMuonsGlobalInvMassVsPt08", "diMuonsGlobalInvMassVsPt08", 8000, 0, 200, 200,0,100);
  diMuonsGlobalInvMassVsPtY10 = new TH2F("diMuonsGlobalInvMassVsPt10", "diMuonsGlobalInvMassVsPt10", 8000, 0, 200, 200,0,100);
  diMuonsGlobalInvMassVsPtY12 = new TH2F("diMuonsGlobalInvMassVsPt12", "diMuonsGlobalInvMassVsPt12", 8000, 0, 200, 200,0,100);
  diMuonsGlobalInvMassVsPtY16 = new TH2F("diMuonsGlobalInvMassVsPt16", "diMuonsGlobalInvMassVsPt16", 8000, 0, 200, 200,0,100);
  diMuonsGlobalInvMassVsPtY20 = new TH2F("diMuonsGlobalInvMassVsPt20", "diMuonsGlobalInvMassVsPt20", 8000, 0, 200, 200,0,100);
  

  diMuonsGlobalInvMassVsY = new TH2F("diMuonsGlobalInvMassVsY","diMuonsGlobalInvMassVsY",8000, 0, 200,100, -5, 5);
  diMuonsGlobalInvMassVsCen = new TH2F("diMuonsGlobalInvMassVsCen","diMuonsGlobalInvMassVsCen", 8000, 0, 200,100,0,100);
  
  // Barrel 

  diMuonsGlobalInvMassVsPtBRL = new TH2F("diMuonsGlobalInvMassVsPtBRL", "diMuonsGlobalInvMassVsPtBRL", 8000, 0, 200, 200,0,100);
  diMuonsGlobalInvMassVsPtEtaCut = new TH2F("diMuonsGlobalInvMassVsPtEtaCut", "diMuonsGlobalInvMassVsPtEtaCut", 8000, 0, 200, 200,0,100);
  diMuonsGlobalInvMassVsPtPtCut = new TH2F("diMuonsGlobalInvMassVsPtPtCut", "diMuonsGlobalInvMassVsPtPtCut", 8000, 0, 200, 200,0,100);



  diMuonsGlobalInvMassVsYBRL = new TH2F("diMuonsGlobalInvMassVsYBRL","diMuonsGlobalInvMassVsYBRL",8000, 0, 200,100, -5, 5);
  diMuonsGlobalInvMassVsYPtCut = new TH2F("diMuonsGlobalInvMassVsYPtCut","diMuonsGlobalInvMassVsYPtCut",8000, 0, 200,100, -5, 5);
  diMuonsGlobalInvMassVsYEtaCut = new TH2F("diMuonsGlobalInvMassVsYEtaCut","diMuonsGlobalInvMassVsYEtaCut",8000, 0, 200,100, -5, 5);




  diMuonsGlobalInvMassVsCenBRL = new TH2F("diMuonsGlobalInvMassVsCenBRL","diMuonsGlobalInvMassVsCenBRL", 8000, 0, 200,100,0,100);
  diMuonsGlobalInvMassVsCenPtCut = new TH2F("diMuonsGlobalInvMassVsCenPtCut","diMuonsGlobalInvMassVsCenPtCut", 8000, 0, 200,100,0,100);
  diMuonsGlobalInvMassVsCenEtaCut = new TH2F("diMuonsGlobalInvMassVsCenEtaCut","diMuonsGlobalInvMassVsCenEtaCut", 8000, 0, 200,100,0,100);





  ////////

 
  diMuonsGlobalSTAInvMassVsPt = new TH2F("diMuonsGlobalSTAInvMassVsPt", "diMuonsGlobalSTAInvMassVsPt",8000, 0, 200,200, 0, 200);
  diMuonsGlobalSTAInvMassVsY = new TH2F("diMuonsGlobalSTAInvMassVsY","diMuonsGlobalSTAInvMassVsY", 8000, 0, 200, 100, -5, 5);
  diMuonsGlobalSTAInvMassVsCen = new TH2F("diMuonsGlobalSTAInvMassVsCen","diMuonsGlobalSTAInvMassVsCen",8000, 0, 200,100,0,100);
    
  diMuonsSTAInvMassVsPt = new TH2F("diMuonsSTAInvMassVsPt","diMuonsSTAInvMassVsPt", 8000, 0, 200, 200,0,100);
  diMuonsSTAInvMassVsY = new TH2F("diMuonsSTAInvMassVsY","diMuonsSTAInvMassVsY",8000, 0, 200, 100, -5, 5);
  diMuonsSTAInvMassVsCen = new TH2F("diMuonsSTAInvMassVsCen","diMuonsSTAInvMassVsCen", 8000, 0, 200,100,0,100);
    
  Centrality = new TH1F("Centrality","Centrality", 100,0,100);


  //same charge  
  diMuonsGlobalSameChargeInvMassVsPt = new TH2F("diMuonsGlobalSameChargeInvMassVsPt", "diMuonsGlobalSameChargeInvMassVsPt", 8000, 0, 200, 200,0,100);
  diMuonsGlobalSameChargeInvMassVsPtY08 = new TH2F("diMuonsGlobalSameChargeInvMassVsPt08", "diMuonsGlobalSameChargeInvMassVsPt08", 8000, 0, 200, 200,0,100);
  diMuonsGlobalSameChargeInvMassVsPtY10 = new TH2F("diMuonsGlobalSameChargeInvMassVsPt10", "diMuonsGlobalSameChargeInvMassVsPt10", 8000, 0, 200, 200,0,100);
  diMuonsGlobalSameChargeInvMassVsPtY12 = new TH2F("diMuonsGlobalSameChargeInvMassVsPt12", "diMuonsGlobalSameChargeInvMassVsPt12", 8000, 0, 200, 200,0,100);
  diMuonsGlobalSameChargeInvMassVsPtY16 = new TH2F("diMuonsGlobalSameChargeInvMassVsPt16", "diMuonsGlobalSameChargeInvMassVsPt16", 8000, 0, 200, 200,0,100);
  diMuonsGlobalSameChargeInvMassVsPtY20 = new TH2F("diMuonsGlobalSameChargeInvMassVsPt20", "diMuonsGlobalSameChargeInvMassVsPt20", 8000, 0, 200, 200,0,100);
 
  
  diMuonsGlobalSameChargeInvMassVsY = new TH2F("diMuonsGlobalSameChargeInvMassVsY","diMuonsGlobalSameChargeInvMassVsY",8000, 0, 200,100, -5, 5);
  diMuonsGlobalSameChargeInvMassVsCen = new TH2F("diMuonsGlobalSameChargeInvMassVsCen","diMuonsGlobalSameChargeInvMassVsCen", 8000, 0, 200,100,0,100);
 
  // Barrel 

  diMuonsGlobalSameChargeInvMassVsPtBRL = new TH2F("diMuonsGlobalSameChargeInvMassVsPtBRL", "diMuonsGlobalSameChargeInvMassVsPtBRL", 8000, 0, 200, 200,0,100);
  diMuonsGlobalSameChargeInvMassVsYBRL = new TH2F("diMuonsGlobalSameChargeInvMassVsYBRL","diMuonsGlobalSameChargeInvMassVsYBRL",8000, 0, 200,100, -5, 5);
  diMuonsGlobalSameChargeInvMassVsCenBRL = new TH2F("diMuonsGlobalSameChargeInvMassVsCenBRL","diMuonsGlobalSameChargeInvMassVsCenBRL", 8000, 0, 200,100,0,100);
  
  diMuonsGlobalSameChargeInvMassVsPtEtaCut = new TH2F("diMuonsGlobalSameChargeInvMassVsPtEtaCut", "diMuonsGlobalSameChargeInvMassVsPtEtaCut", 8000, 0, 200, 200,0,100);
  diMuonsGlobalSameChargeInvMassVsPtPtCut = new TH2F("diMuonsGlobalSameChargeInvMassVsPtPtCut", "diMuonsGlobalSameChargeInvMassVsPtPtCut", 8000, 0, 200, 200,0,100);
  
  diMuonsGlobalSameChargeInvMassVsYPtCut = new TH2F("diMuonsGlobalSameChargeInvMassVsYPtCut","diMuonsGlobalInvMassVsYPtCut",8000, 0, 200,100, -5, 5);
  diMuonsGlobalSameChargeInvMassVsYEtaCut = new TH2F("diMuonsGlobalSameChargeInvMassVsYEtaCut","diMuonsGlobalInvMassVsYEtaCut",8000, 0, 200,100, -5, 5);

  diMuonsGlobalSameChargeInvMassVsCenPtCut = new TH2F("diMuonsGlobalSameChargeInvMassVsCenPtCut","diMuonsGlobalInvMassVsCenPtCut", 8000, 0, 200,100,0,100);
  diMuonsGlobalSameChargeInvMassVsCenEtaCut = new TH2F("diMuonsGlobalSameChargeInvMassVsCenEtaCut","diMuonsGlobalInvMassVsCenEtaCut", 8000, 0, 200,100,0,100);










  /////////


  diMuonsGlobalSTASameChargeInvMassVsPt = new TH2F("diMuonsGlobalSTASameChargeInvMassVsPt", "diMuonsGlobalSTASameChargeInvMassVsPt",8000, 0, 200,200, 0, 100);
  diMuonsGlobalSTASameChargeInvMassVsY = new TH2F("diMuonsGlobalSTASameChargeInvMassVsY","diMuonsGlobalSTASameChargeInvMassVsY", 8000, 0, 200, 100, -5, 5);
  diMuonsGlobalSTASameChargeInvMassVsCen = new TH2F("diMuonsGlobalSTASameChargeInvMassVsCen","diMuonsGlobalSTASameChargeInvMassVsCen",8000, 0, 200,100,0,100);
  
  diMuonsSTASameChargeInvMassVsPt = new TH2F("diMuonsSTASameChargeInvMassVsPt","diMuonsSTASameChargeInvMassVsPt", 8000, 0, 200, 200,0,100);
  diMuonsSTASameChargeInvMassVsY = new TH2F("diMuonsSTASameChargeInvMassVsY","diMuonsSTASameChargeInvMassVsY",8000, 0, 200, 100, -5, 5);
  diMuonsSTASameChargeInvMassVsCen = new TH2F("diMuonsSTASameChargeInvMassVsCen","diMuonsSTASameChargeInvMassVsCen", 8000, 0, 200,100,0,100);
  
  diMuonsGenInvMassVsPt = new TH2F("diMuonsGenInvMassVsPt", "diMuonsGenInvMassVsPt", 8000, 0, 200, 200,0,100);
  diMuonsGenInvMassVsY = new TH2F("diMuonsGenInvMassVsY","diMuonsGenInvMassVsY",8000, 0, 200,100, -5, 5);
  diMuonsGenInvMassVsCen = new TH2F("diMuonsGenInvMassVsCen","diMuonsGenInvMassVsCen", 8000, 0, 200,100,0,100);
  
  diMuonsGenInvMass = new TH1F("diMuonsGenInvMass","diMuonsGenInvMass", 8000,0,200);
  diMuonsGenPt = new TH1F("diMuonsGenPt","diMuonsGenPt", 100,0,20);
  diMuonsGenRapidity = new TH1F("diMuonsGenRapidity","diMuonsGenRapidity", 100,-10,10);

  // Global Histos

  diMuonsMass200 = new TH1F("diMuonsMass200", "diMuonsMass200", 8000, 0, 1000);
  diMuonsMass200Cut = new TH1F("diMuonsMass200Cut", "diMuonsMass200Cut", 8000, 0, 1000);

  gMuonChi2ndf = new TH1F("gMuonChi2ndf", "gMuonChi2ndf", 100, 0, 100);
  gMuonnhits = new TH1F("gMuonnhits", "gMuonnhits", 100, 0, 100);
  gMuonfound = new TH1F("gMuonfound", "gMuonfound ", 200, 0, 100);

  gMuonChi2ndfTrack = new TH1F("gMuonChi2ndfTrack", "gMuonChi2ndfTrack", 200, 0, 100);
  gMuonPixel = new TH1F("gMuonPixel", "gMuonPixel", 100, 0, 100);

  gMuonDxy = new TH1F("gMuonDxy", "gMuonDxy", 200, -50, 50);
  gMuonZ = new TH1F("gMuonZ", "gMuonZ", 200, -50, 50);
  gMuonSeg = new TH1F("gMuonSeg", "gMuonSeg", 200, -50, 50);
  gMuonChamb = new TH1F("gMuonChamb", "gMuonChamb", 200, -50, 50);

  gMuonArb = new TH1F("gMuonArb", "gMuonArb", 11, -1, 10);
  gMuonLastTight = new TH1F("gMuonLastTight", "gMuonLastTight", 11, -1, 10);
  gMuonLastLoose = new TH1F("gMuonLastLoose", "gMuonLastLoose", 11, -1, 10);

  gMuonPtError=new TH1F("gMuonsPtError", "gMuonsPtError", 200, 0, 10);
  gMuonValidHits=new TH1F("gMuonValidHits", "gMuonValidHits", 200, 0, 100);
  
  gMuonsIso=new TH1F("gMuonsIso", "gMuonsIso", 200, 0, 10);

  gMuonsPt = new TH1F("gMuonsPt", "gMuonsPt", 200, 0, 100);
  gMuonsNumber = new TH1F("gMuonsNumber", "gMuonsNumber", 100, 0, 10);
  gMuonsNumberCut = new TH1F("gMuonsNumberCut", "gMuonsNumberCut", 100, 0, 10);
 
  gMuonsEta = new TH1F("gMuonsEta", " gMuonsEta", 100, -10, 10);
  gMuonsPhi = new TH1F("gMuonsPhi", "gMuonsPhi", 100, 0, 10);

  //Tracker Histos

  tMuonfound = new TH1F("tMuonfound", "tMuonfound ", 200, 0, 100);
  tMuonChi2ndfTrack = new TH1F("tMuonChi2ndfTrack", "tMuonChi2ndfTrack", 200, 0, 100);
  tMuonPixel = new TH1F("tMuonPixel", "tMuonPixel", 100, 0, 100);
  tMuonDxy = new TH1F("tMuonDxy", "tMuonDxy", 200, -50, 50);
  tMuonZ = new TH1F("tMuonZ", "tMuonZ", 200, -50, 50);

  tMuonsPt = new TH1F("tMuonsPt", "tMuonsPt", 200, 0, 100);
  tMuonsEta = new TH1F("tMuonsEta", " tMuonsEta", 100, -10, 10);
  tMuonsPhi = new TH1F("tMuonsPhi", "tMuonsPhi", 100, 0, 10);

  // STA Histos

  sMuonnhits = new TH1F("sMuonnhits", "sMuonnhits", 100, 0, 100);
  sMuonDxy = new TH1F("sMuonDxy", "sMuonDxy", 200, -50, 50);
  sMuonZ = new TH1F("sMuonZ", "sMuonZ", 200, -50, 50);

  sMuonsPt = new TH1F("sMuonsPt", "sMuonsPt", 200, 0, 100);
  sMuonsEta = new TH1F("sMuonsEta", " sMuonsEta", 100, -10, 10);
  sMuonsPhi = new TH1F("sMuonsPhi", "sMuonsPhi", 100, 0, 10);

  // Z vertex
  hZVtx = new TH1F("hZVtx", "hZVtx", 200, -100, 100);

  // Cuts histos
 
  dimu = new TH2F("dimu", "dimu", 8000, 0, 200, 200, 0, 100);
  dimuGlbTrk= new TH2F("dimuGlbTrk", "dimuGlbTrk", 8000, 0, 200, 200, 0, 100);
  
  dimuFOUND = new TH1F("dimuFOUND", "dimuFOUND", 8000, 0, 200);
  dimuGLCHI2 = new TH1F("dimuGLCHI2", "dimuGLCHI2", 8000, 0, 200);
  dimuHITS = new TH1F("dimuHITS", "dimuHITS", 8000, 0, 200);
  dimuTRKCHI2 = new TH1F("dimuTRKCHI2", "dimuTRKCHI2", 8000, 0, 200);
  dimuARB = new TH1F("dimuARB", "dimuARB", 8000, 0, 200);
  dimuLast = new TH2F("dimuLast", "dimuLast", 8000, 0, 200, 100, 0, 100);
  dimuLastLoose = new TH2F("dimuLastLoose", "dimuLastLoose", 8000, 0, 200, 200, 0, 100);
  
  dimuPIX = new TH1F("dimuPIX", "dimuPIX", 8000, 0, 200);
  dimuDXY = new TH1F("dimuDXY", "dimuDXY", 8000, 0, 200);
  dimuDZ = new TH1F("dimuDZ", "dimuDZ", 8000, 0, 200);
  dimuAll = new TH1F("dimuAll", "dimuAll", 8000, 0, 200);
  //new cut histos
  dimuPTERROR = new TH1F("dimuPTERROR", "dimuPTERROR", 8000, 0, 200);
  dimuNOOFVALIDHITS = new TH1F("dimuNOOFVALIDHITS", "dimuNOOFVALIDHITS", 8000, 0, 200);
  dimuD0 = new TH1F("dimuD0", "dimuD0", 8000, 0, 200);
  dimuSeg = new TH1F("dimuSeg", "dimuSeg", 8000, 0, 200);
  dimuChamb = new TH1F("dimuChamb", "dimuChamb", 8000, 0, 200);
  
  dimuIso=  new TH1F("dimuIso", "dimuIso", 8000, 0, 200);




//  h_ZetaGen_ = genParticleDir.make<TH1D>("generatedZeta","#eta of generated Z",100,-5.,5.); 

  // Write comments in a file
}



// ------------ method called once each job just after ending the event loop  ------------
void DiMuon2DPlots::endJob() 
{
  cout<<"End Job"<<endl;
  fOutputFile->cd();
  diMuonsGlobalInvMassVsPt->Write();
  
  diMuonsGlobalInvMassVsPtY08->Write();
  diMuonsGlobalInvMassVsPtY10->Write();
  diMuonsGlobalInvMassVsPtY12->Write();
  diMuonsGlobalInvMassVsPtY16->Write();
  diMuonsGlobalInvMassVsPtY20->Write();

  diMuonsGlobalInvMassVsY->Write();
  diMuonsGlobalInvMassVsCen->Write();

  diMuonsGlobalInvMassVsPtBRL->Write();
  diMuonsGlobalInvMassVsYBRL->Write();
  diMuonsGlobalInvMassVsCenBRL->Write();

  diMuonsGlobalInvMassVsPtEtaCut->Write();
  diMuonsGlobalInvMassVsPtPtCut->Write();
  
  diMuonsGlobalInvMassVsYPtCut->Write();
  diMuonsGlobalInvMassVsYEtaCut->Write();
  diMuonsGlobalInvMassVsCenPtCut->Write();
  diMuonsGlobalInvMassVsCenEtaCut->Write();




  diMuonsGlobalSTAInvMassVsPt->Write();
  diMuonsGlobalSTAInvMassVsY->Write();
  diMuonsGlobalSTAInvMassVsCen->Write();
  diMuonsSTAInvMassVsPt->Write();
  diMuonsSTAInvMassVsY->Write();
  diMuonsSTAInvMassVsCen->Write();
  Centrality->Write(); 
  //same charge
  diMuonsGlobalSameChargeInvMassVsPt->Write();
  diMuonsGlobalSameChargeInvMassVsPtY08->Write();
  diMuonsGlobalSameChargeInvMassVsPtY10->Write();
  diMuonsGlobalSameChargeInvMassVsPtY12->Write();
  diMuonsGlobalSameChargeInvMassVsPtY16->Write();
  diMuonsGlobalSameChargeInvMassVsPtY20->Write();  
  diMuonsGlobalSameChargeInvMassVsY->Write();
  diMuonsGlobalSameChargeInvMassVsCen->Write();

  diMuonsGlobalSameChargeInvMassVsPtBRL->Write();
  diMuonsGlobalSameChargeInvMassVsYBRL->Write();
  diMuonsGlobalSameChargeInvMassVsCenBRL->Write();


  diMuonsGlobalSameChargeInvMassVsPtEtaCut->Write();
  diMuonsGlobalSameChargeInvMassVsPtPtCut->Write();
  diMuonsGlobalSameChargeInvMassVsYPtCut->Write();
  diMuonsGlobalSameChargeInvMassVsYEtaCut->Write();
  diMuonsGlobalSameChargeInvMassVsCenPtCut->Write();
  diMuonsGlobalSameChargeInvMassVsCenEtaCut->Write();


  diMuonsGlobalSTASameChargeInvMassVsPt->Write();
  diMuonsGlobalSTASameChargeInvMassVsY->Write();
  diMuonsGlobalSTASameChargeInvMassVsCen->Write();
  diMuonsSTASameChargeInvMassVsPt->Write();
  diMuonsSTASameChargeInvMassVsY->Write();
  diMuonsSTASameChargeInvMassVsCen->Write();
  diMuonsGenInvMassVsPt->Write();
  diMuonsGenInvMassVsY->Write();
  diMuonsGenInvMassVsCen->Write();
  diMuonsGenInvMass->Write(); 
  diMuonsGenPt->Write(); 
  diMuonsGenRapidity->Write();

  // Global histos

  diMuonsMass200->Write();
  diMuonsMass200Cut->Write();
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

  sMuonsPt->Write();
  sMuonsEta->Write();
  sMuonsPhi->Write();

  hZVtx->Write();

  // cuts histos
  dimu->Write();
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

  dimuAll->Write();


  // Output file close
  fOutputFile->Close();

}


bool DiMuon2DPlots::selGlobalMuon(const reco::Muon* aMuon) {
  //Imp subrutine used to fill histogram which are used to fill histograms any cut to be studied should not be 
  //put here 

  if(!fisCuts) return true;

  if(!(aMuon->isGlobalMuon() && aMuon->isTrackerMuon()))
  return false;

  TrackRef iTrack = aMuon->innerTrack();
  const reco::HitPattern& p = iTrack->hitPattern();

  TrackRef gTrack = aMuon->globalTrack();
  const reco::HitPattern& q = aMuon->globalTrack()->hitPattern();

  return (
	  // pp Z0 cuts
	  isMuonInAccept(aMuon) &&
          p.numberOfValidHits() > 12 &&
          p.pixelLayersWithMeasurement() > 1 &&
          aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof() < 10.0 &&
          q.numberOfValidMuonHits() > 0 &&
	  
	  //aMuon->numberOfChambers() > 2 &&
	  //aMuon->numberOfMatches()>2 && removing this cut as it is cutting a signal 
	  
	  // heavy ion track cuts
	  iTrack->ptError()/iTrack->pt() < 0.05 &&
	  fabs(iTrack->dxy(RefVtx)) < 3.0 &&
	  fabs(iTrack->dz(RefVtx)) < 15.0 &&

	  // j/psi pp cuts additional over Z0 cuts
	  iTrack->chi2()/iTrack->ndof() < 4.0 

	  //iTrack->found() > 11 &&
          //NoArbitration, SegmentArbitration, SegmentAndTrackArbitration, SegmentAndTrackArbitrationCleaned 
	  //muon::isGoodMuon(*aMuon, muon::TrackerMuonArbitrated, reco::Muon::NoArbitration) && 
	  //muon::isGoodMuon(*aMuon, muon::TMLastStationAngTight, reco::Muon::NoArbitration) &&
	  //muon::isGoodMuon(*aMuon, muon::TMLastStationAngLoose, reco::Muon::NoArbitration) &&
	  );
}



bool DiMuon2DPlots::selTrackerMuon(const reco::Muon* aMuon) {
  if(!fisCuts) return true;
  
  if(!aMuon->isTrackerMuon())
    return false;

  TrackRef iTrack = aMuon->innerTrack();
  const reco::HitPattern& p = iTrack->hitPattern();

  return (isMuonInAccept(aMuon) &&
	  p.numberOfValidHits() > 12 &&
	  iTrack->chi2()/iTrack->ndof() < 4.0 &&

          //muon::isGoodMuon(*aMuon, muon::TMLastStationAngTight, reco::Muon::NoArbitration) &&  
	  // muon::isGoodMuon(*aMuon, muon::TrackerMuonArbitrated, reco::Muon::NoArbitration) &&

	  p.pixelLayersWithMeasurement() > 1 &&
	  fabs(iTrack->dxy(RefVtx)) < 3.0 &&
	  fabs(iTrack->dz(RefVtx)) < 15.0 );
}




bool
DiMuon2DPlots::selSTAMuon(const reco::Muon* aMuon) {
  if(!fisCuts) return true;

  if(!aMuon->isStandAloneMuon())
    return false;

  //  TrackRef iTrack = aMuon->combinedMuon();
  //  const reco::HitPattern& p = iTrack->hitPattern();

  return (
	  isMuonInAccept(aMuon) &&
          aMuon->standAloneMuon()->numberOfValidHits() > 0 &&
          //muon::isGoodMuon(*aMuon, muon::TMLastStationAngTight, reco::Muon::NoArbitration) &&
          fabs(aMuon->standAloneMuon()->dxy(RefVtx)) < 5.0 &&
          fabs(aMuon->standAloneMuon()->dz(RefVtx)) < 20.0 );
}



bool DiMuon2DPlots::isMuonInAccept(const reco::Muon* aMuon) {
  return (fabs(aMuon->eta()) < 2.4 ); 
  //  return (fabs(aMuon->eta()) < 2.4 &&
  //	  ((fabs(aMuon->eta()) < 1.3 && aMuon->pt() >= 3.3) ||
  //	   (fabs(aMuon->eta()) >= 1.3 && fabs(aMuon->eta()) < 2.2 && aMuon->p() >= 2.9) ||
  //	   (fabs(aMuon->eta()) >= 2.2 && aMuon->pt() >= 0.8)));
}


void DiMuon2DPlots::MuAnalyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)

{
  //All new cuts we can study here and see there disstributions 
  
  int imuplus =0, imuminus=0;
  int GMuon = 0, TMuon=0 , SAMuon=0;

  using namespace edm;
  using namespace std;


  using reco::TrackCollection;
  using reco::MuonCollection;

  edm::Handle<edm::View<reco::Muon> >tmuons;
  iEvent.getByLabel("muons", tmuons);
  
  //int rmuon =tmuons->size();

  for (edm::View<reco::Muon>::const_iterator aMuon = tmuons->begin(); aMuon!= tmuons->end(); ++aMuon) {
    //for(unsigned int j = 0; j <tmuons->size(); ++j){
    //    edm::RefToBase<reco::Muon> aMuon(tmuons, j);
    //if (aMuon.isNull() ) continue;
    
    if(aMuon->isGlobalMuon()) GMuon++;
    gMuonsNumber->Fill(GMuon);
    
    //if(selGlobalMuon()) gMuonsNumberCut->Fill(GMuon);
    
    
    if(aMuon->isTrackerMuon()) TMuon++;
    if((aMuon->isStandAloneMuon()) && (!aMuon->isGlobalMuon())) SAMuon++;
    

    float pt = aMuon->pt();
    float eta = aMuon->eta();
    float phi = aMuon->phi();
    int charge = aMuon->charge();

    if(charge>0) imuplus++;
    if(charge<0) imuminus++;
    
    if(aMuon->isGlobalMuon()) {
      TrackRef gTrack = aMuon->globalTrack();
      const reco::HitPattern& q = aMuon->globalTrack()->hitPattern();
      gMuonnhits->Fill(q.numberOfValidMuonHits());
      //gMuonnhits->Fill(aMuon->globalTrack()->numberOfValidHits());
      gMuonChi2ndf->Fill(aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof());

      // Track
      TrackRef iTrack = aMuon->innerTrack();
      gMuonfound->Fill(iTrack->found());
      
      const reco::HitPattern& p = iTrack->hitPattern();
      gMuonPixel->Fill(p.pixelLayersWithMeasurement());
      
      gMuonChi2ndfTrack->Fill(iTrack->chi2()/iTrack->ndof());
      gMuonDxy->Fill(iTrack->dxy(RefVtx));
      gMuonZ->Fill(iTrack->dz(RefVtx));
     
      gMuonPtError->Fill(iTrack->ptError()/iTrack->pt());
      gMuonValidHits->Fill(p.numberOfValidHits());

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


    if(aMuon->isTrackerMuon()) {
      TrackRef iTrack = aMuon->innerTrack();
      const reco::HitPattern& p = iTrack->hitPattern();
      tMuonPixel->Fill(p.pixelLayersWithMeasurement());

      tMuonfound->Fill(p.numberOfValidHits());
      tMuonChi2ndfTrack->Fill(iTrack->chi2()/iTrack->ndof());

      tMuonDxy->Fill(iTrack->dxy(RefVtx));
      tMuonZ->Fill(iTrack->dz(RefVtx));

      tMuonsPt->Fill(pt);
      tMuonsEta->Fill(eta);
      tMuonsPhi->Fill(phi);

    }

    
    if(aMuon->isStandAloneMuon()) {
      //TrackRef sta = aMuon->combinedMuon();
      sMuonnhits->Fill(aMuon->standAloneMuon()->numberOfValidHits());
      sMuonDxy->Fill(fabs(aMuon->standAloneMuon()->dxy(RefVtx)));
      sMuonZ->Fill(fabs(aMuon->standAloneMuon()->dz(RefVtx)));
      
      sMuonsPt->Fill(pt);
      sMuonsEta->Fill(eta);
      sMuonsPhi->Fill(phi);
    }


  }

    ////  Print ///////

  //    cout << " +ive = " << imuplus << "   -ive  " << imuminus << endl; 

    //cout << " No. of Global Muons = " << GMuon << endl;
    //cout << " No. of Tracker Muons = " << TMuon << endl;
    //cout << " No. of StandAlone Muons = " << SAMuon << endl << endl;

}


void DiMuon2DPlots::printGlobalMuon(const reco::Muon* aMuon) {
  //  if(!aMuon->isGlobalMuon())
  //    return;

  TrackRef iTrack = aMuon->innerTrack();
  const reco::HitPattern& p = iTrack->hitPattern();

  TrackRef gTrack = aMuon->globalTrack();
  const reco::HitPattern& q = aMuon->globalTrack()->hitPattern();

  cout << " pt       eta         phi        charge  "<< endl;

  cout << aMuon->pt() << "   " <<  aMuon->eta() << "    " << aMuon->phi() << "    " << aMuon->charge() <<endl<< endl;
  
  if(allCutGlobal(aMuon) ) cout << "  This single muon passed all quality cuts " << endl << endl;
  if(!allCutGlobal(aMuon) ) cout << "  This single muon FAILED some quality cuts " << endl << endl;
  
  cout << " p.numberOfValidHits = " << p.numberOfValidHits() << endl;
  cout <<  " pixelLayersWithMeasurement() = " << p.pixelLayersWithMeasurement() << endl;
  cout << "  globalChi2/ndof = "  << aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof() << endl;
  cout << " q.numberOfValidMuonHits() = " <<  q.numberOfValidMuonHits() << endl;

  cout << " iTrack->ptError()/iTrack->pt() = " << iTrack->ptError()/iTrack->pt() << endl;
 
  cout <<  " dxy = " << fabs(iTrack->dxy(RefVtx)) << endl;
  cout <<  " dz = " << fabs(iTrack->dz(RefVtx))  << endl;

  cout << " TrackChi2ndof = " <<  iTrack->chi2()/iTrack->ndof() << endl << endl << endl;


  cout << " aMuon->numberOfChambers() = " <<  aMuon->numberOfChambers()  << endl;
  cout << " aMuon->numberOfMatches() = " << aMuon->numberOfMatches() << endl;  
  cout << " iTrack->found() = " <<   iTrack->found() << endl;
  cout << " muon::TrackerMuonArbitrated = " <<  muon::isGoodMuon(*aMuon, muon::TrackerMuonArbitrated, reco::Muon::NoArbitration) << endl;
  cout << " muon::TMLastStationAngTight = " <<  muon::isGoodMuon(*aMuon, muon::TMLastStationAngTight, reco::Muon::NoArbitration) << endl;
  cout << " muon::TMLastStationAngLoose = " <<  muon::isGoodMuon(*aMuon, muon::TMLastStationAngLoose, reco::Muon::NoArbitration) << endl;
  
}


void DiMuon2DPlots::FillHistoCuts(double mass, double pt, const reco::Muon* Muon1, const reco::Muon* Muon2) {

  //You can study here effect of cuts on dimuons
  cout<<"fill cut histo"<<endl;

  TrackRef iTrack1 = Muon1->innerTrack();
  const reco::HitPattern& p1 = iTrack1->hitPattern();
  TrackRef gTrack1 = Muon1->globalTrack();
  const reco::HitPattern& q1 = gTrack1->hitPattern();

  TrackRef iTrack2 = Muon2->innerTrack();
  const reco::HitPattern& p2 = iTrack2->hitPattern();
  
  TrackRef gTrack2 = Muon2->globalTrack();
  const reco::HitPattern& q2 = gTrack2->hitPattern();

  dimu->Fill(mass,pt);
  //glb&&trk

  if( (Muon1->isGlobalMuon() && Muon1->isTrackerMuon()) && (Muon2->isGlobalMuon() && Muon2->isTrackerMuon())) dimuGlbTrk->Fill(mass,pt);

  if(Muon1->isIsolationValid() && Muon2->isIsolationValid() ){
   
    double SumPtMu1 = Muon1->isolationR03().sumPt; 
    double CalMu1   = Muon1->isolationR03().emEt + Muon1->isolationR03().hadEt; 
    double IsoMu1=(SumPtMu1+CalMu1)/Muon1->pt();
  

    double SumPtMu2 = Muon2->isolationR03().sumPt;
    double CalMu2   = Muon2->isolationR03().emEt + Muon2->isolationR03().hadEt;
    double IsoMu2=(SumPtMu2+CalMu2)/Muon2->pt();

    if(IsoMu1<0.15 && IsoMu2<0.15) dimuIso->Fill(mass);
  }

  if(p1.numberOfValidHits() > 12  &&  p2.numberOfValidHits() >12 )dimuNOOFVALIDHITS->Fill(mass);					  
  if(p1.pixelLayersWithMeasurement() > 1  &&  p2.pixelLayersWithMeasurement() > 1) dimuPIX->Fill(mass);
  if(gTrack1->chi2()/gTrack1->ndof() < 10.0  &&  gTrack2->chi2()/gTrack2->ndof() < 10.0) dimuGLCHI2->Fill(mass); 
  if(q1.numberOfValidMuonHits() > 0  &&  q2.numberOfValidMuonHits() >0 ) dimuHITS->Fill(mass);

  if(iTrack1->ptError()/iTrack1->pt() < 0.05 && iTrack2->ptError()/iTrack2->pt() < 0.05) dimuPTERROR->Fill(mass);  
  if(fabs(iTrack1->dxy(RefVtx)) < 3.0  &&  fabs(iTrack2->dxy(RefVtx)) < 3.0) dimuDXY->Fill(mass);
  if(fabs(iTrack1->dz(RefVtx)) < 15.0  && fabs(iTrack2->dz(RefVtx)) < 15.0) dimuDZ->Fill(mass);

  if(iTrack1->chi2()/iTrack1->ndof() < 4.0  &&  iTrack2->chi2()/iTrack2->ndof()) dimuTRKCHI2->Fill(mass);

  if(Muon1->numberOfChambers() >2.0  && Muon2->numberOfChambers() >2.0) dimuChamb->Fill(mass);
  if(Muon1->numberOfMatches() >2.0  && Muon2->numberOfMatches() >2.0) dimuSeg->Fill(mass);
  if(fabs(iTrack1->dxy(RefVtx)) < 2.0  && fabs(iTrack2->dxy(RefVtx)) < 2.0) dimuD0->Fill(mass);

  if(iTrack1->found() > 11  &&  iTrack2->found() > 11)  dimuFOUND->Fill(mass);
  if( muon::isGoodMuon(*Muon1, muon::TrackerMuonArbitrated, reco::Muon::NoArbitration) && 
      muon::isGoodMuon(*Muon2, muon::TrackerMuonArbitrated, reco::Muon::NoArbitration) )  dimuARB->Fill(mass); 
  
  if(muon::isGoodMuon(*Muon1, muon::TMLastStationAngTight, reco::Muon::NoArbitration) &&
     muon::isGoodMuon(*Muon2, muon::TMLastStationAngTight, reco::Muon::NoArbitration) )  dimuLast->Fill(mass, pt);
 
  if(muon::isGoodMuon(*Muon1, muon::TMLastStationAngLoose, reco::Muon::NoArbitration) && 
     muon::isGoodMuon(*Muon2, muon::TMLastStationAngLoose, reco::Muon::NoArbitration) ) dimuLastLoose->Fill(mass, pt);
  
  if(allCutGlobal(Muon1) && allCutGlobal(Muon2)) dimuAll->Fill(mass);  

}




bool DiMuon2DPlots::allCutGlobal(const reco::Muon* aMuon) {

  if(!(aMuon->isGlobalMuon() && aMuon->isTrackerMuon()))
    return false;
  
  TrackRef iTrack = aMuon->innerTrack();
  const reco::HitPattern& p = iTrack->hitPattern();

  TrackRef gTrack = aMuon->globalTrack();
  const reco::HitPattern& q = aMuon->globalTrack()->hitPattern();

  return (
          // pp Z0 cuts
          isMuonInAccept(aMuon) &&
          p.numberOfValidHits() > 12 &&
          p.pixelLayersWithMeasurement() > 1 &&
          aMuon->globalTrack()->chi2()/aMuon->globalTrack()->ndof() < 10.0 &&
          q.numberOfValidMuonHits() > 0 &&
	  
          //aMuon->numberOfChambers() > 2 &&
          //aMuon->numberOfMatches()>2 && removing this cut as it is cutting a signal
	  
          // heavy ion track cuts
          iTrack->ptError()/iTrack->pt() < 0.05 &&
          fabs(iTrack->dxy(RefVtx)) < 3.0 &&
          fabs(iTrack->dz(RefVtx)) < 15.0 &&

          // j/psi pp cuts additional over Z0 cuts
          iTrack->chi2()/iTrack->ndof() < 4.0
	  
          //iTrack->found() > 11 &&
          //NoArbitration, SegmentArbitration, SegmentAndTrackArbitration, SegmentAndTrackArbitrationCleaned
          //muon::isGoodMuon(*aMuon, muon::TrackerMuonArbitrated, reco::Muon::NoArbitration) &&
          //muon::isGoodMuon(*aMuon, muon::TMLastStationAngTight, reco::Muon::NoArbitration) &&
          //muon::isGoodMuon(*aMuon, muon::TMLastStationAngLoose, reco::Muon::NoArbitration) &&
          );
    
}




//define this as a plug-in
DEFINE_FWK_MODULE(DiMuon2DPlots);



