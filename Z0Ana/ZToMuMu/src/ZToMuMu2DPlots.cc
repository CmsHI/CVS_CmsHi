// -*- C++ -*-
//
// Package:    ZToMuMu2DPlots
// Class:      ZToMuMu2DPlots
// 
/**\class ZToMuMu2DPlots ZToMuMu2DPlots.cc Z0Ana/ZToMuMu2DPlots/src/ZToMuMu2DPlots.cc
   
 Description: [one line class summary]
 
 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Vineet Kumar,,,
//         Created:  Wed May 12 13:45:14 CEST 2010
// $Id: ZToMuMu2DPlots.cc,v 1.1 2010/07/06 06:04:35 kumarv Exp $
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



using std::cout;
using std::endl;
using namespace reco;
using namespace edm;
using namespace std;
using namespace HepMC;


//
// class declaration
//

class ZToMuMu2DPlots : public edm::EDAnalyzer {
   public:
  explicit ZToMuMu2DPlots(const edm::ParameterSet&);
  ~ZToMuMu2DPlots();
 
  const CentralityBins *cbins_;
  std::string fOutputFileName;
  std::string fIsGenInfo;
  //edm::InputTag fdimuonCandTag;
  //std::string fhistName;
  //std::string fhistName1;

  TFile *fOutputFile ;
  TH1F *Centrality;
  TH2F *diMuonsGlobalInvMassVsPt;
  TH2F *diMuonsGlobalInvMassVsY;   
  TH2F *diMuonsGlobalInvMassVsCen;
  
  TH2F *diMuonsGlobalSTAInvMassVsPt;
  TH2F *diMuonsGlobalSTAInvMassVsY;
  TH2F *diMuonsGlobalSTAInvMassVsCen;
  
  TH2F *diMuonsSTAInvMassVsPt;
  TH2F *diMuonsSTAInvMassVsY;
  TH2F *diMuonsSTAInvMassVsCen;

  TH2F *diMuonsGlobalSameChargeInvMassVsPt;
  TH2F *diMuonsGlobalSameChargeInvMassVsY;
  TH2F *diMuonsGlobalSameChargeInvMassVsCen;

  TH2F *diMuonsGlobalSTASameChargeInvMassVsPt;
  TH2F *diMuonsGlobalSTASameChargeInvMassVsY;
  TH2F *diMuonsGlobalSTASameChargeInvMassVsCen;

  TH2F *diMuonsSTASameChargeInvMassVsPt;
  TH2F *diMuonsSTASameChargeInvMassVsY;
  TH2F *diMuonsSTASameChargeInvMassVsCen;
  
  TH2F *diMuonsGenInvMassVsPt;
  TH2F *diMuonsGenInvMassVsY;
  TH2F *diMuonsGenInvMassVsCen;
  
  TH1F  *diMuonsGenInvMass;
  TH1F  *diMuonsGenPt;
  TH1F  *diMuonsGenRapidity;
  
  int bin;


private:
  
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void SameChargePlots(const edm::Event&, const edm::EventSetup&);
  virtual void GenPlots(const edm::Event&, const edm::EventSetup& );
  virtual void endJob() ;
  
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


ZToMuMu2DPlots::ZToMuMu2DPlots(const edm::ParameterSet& iConfig):
  cbins_(0),fOutputFileName(iConfig.getUntrackedParameter<string>("OutputFileName")),fIsGenInfo(iConfig.getUntrackedParameter<string>("IsGenInfo")),
  Centrality(0),diMuonsGlobalInvMassVsPt(0),diMuonsGlobalInvMassVsY(0),diMuonsGlobalInvMassVsCen(0),diMuonsGlobalSTAInvMassVsPt(0),diMuonsGlobalSTAInvMassVsY(0),diMuonsGlobalSTAInvMassVsCen(0),diMuonsSTAInvMassVsPt(0),diMuonsSTAInvMassVsY(0),diMuonsSTAInvMassVsCen(0),diMuonsGlobalSameChargeInvMassVsPt(0),diMuonsGlobalSameChargeInvMassVsY(0),diMuonsGlobalSameChargeInvMassVsCen(0),diMuonsGlobalSTASameChargeInvMassVsPt(0),diMuonsGlobalSTASameChargeInvMassVsY(0),diMuonsGlobalSTASameChargeInvMassVsCen(0),diMuonsSTASameChargeInvMassVsPt(0),diMuonsSTASameChargeInvMassVsY(0),diMuonsSTASameChargeInvMassVsCen(0),diMuonsGenInvMassVsPt(0),diMuonsGenInvMassVsY(0),diMuonsGenInvMassVsCen(0),diMuonsGenInvMass(0),diMuonsGenPt(0),diMuonsGenRapidity(0)
   //fdimuonCandTag(iConfig.getUntrackedParameter<edm::InputTag>("dimuonCandTag")),
  //fhistName(iConfig.getUntrackedParameter<string>("histName")),
{ 

//now do what ever initialization is needed

}


ZToMuMu2DPlots::~ZToMuMu2DPlots()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
ZToMuMu2DPlots::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

   if(!cbins_) cbins_ = getCentralityBinsFromDB(iSetup);
   edm::Handle<reco::Centrality> cent;
   iEvent.getByLabel(edm::InputTag("hiCentrality"),cent);

   double hf = cent->EtHFhitSum();
   //   double hftp = cent->EtHFtowerSumPlus();
   //   double hftm = cent->EtHFtowerSumMinus();
   //   double eb = cent->EtEBSum();
   //   double eep = cent->EtEESumPlus();
   //   double eem = cent->EtEESumMinus();

   //   cout<<"Centrality variables in the event:"<<endl;
   //   cout<<"Total energy in HF hits : "<<hf<<endl;
   //   cout<<"Asymmetry of HF towers : "<<fabs(hftp-hftm)/(hftp+hftm)<<endl;
   //   cout<<"Total energy in EE basic clusters : "<<eep+eem<<endl;
   //   cout<<"Total energy in EB basic clusters : "<<eb<<endl;

   bin = cbins_->getBin(hf);

   Centrality ->Fill(bin);                                                                                                                                  
   int nbins = cbins_->getNbins();
   int binsize = 100/nbins;
   char* binName = Form("%d to % d",bin*binsize,(bin+1)*binsize);
   cout<<"The event falls into centrality bin : "<<binName<<" id : "<<bin<<endl;

// get dimuonGlobal collection                                                                                   
   edm::Handle<edm::View<reco::Candidate> > diMuonsGlobalCand;
   iEvent.getByLabel("dimuonsGlobal", diMuonsGlobalCand);
   edm::View<reco::Candidate>dimuonsGlobalColl= *diMuonsGlobalCand;
   int dimuonsGlobalSize =dimuonsGlobalColl.size();
   cout<<" no of dimuon Global  :" <<dimuonsGlobalSize <<endl;
   for(size_t ii = 0; ii <dimuonsGlobalColl.size(); ++ ii) {
     const reco::Candidate& p = (dimuonsGlobalColl)[ii];
     //histContainer2D["diMuonInvMassVsPt"]->Fill(p.mass(),p.pt());
     diMuonsGlobalInvMassVsPt->Fill(p.mass(),p.pt());
     diMuonsGlobalInvMassVsY->Fill(p.mass(),p.rapidity());
     diMuonsGlobalInvMassVsCen->Fill(p.mass(),bin);
   }


   // get dimuonGlobalSTA collection
   edm::Handle<edm::View<reco::Candidate> > diMuonsGlobalSTACand;
   iEvent.getByLabel("dimuonsGlobalSTA", diMuonsGlobalSTACand);
   edm::View<reco::Candidate>dimuonsGlobalSTAColl= *diMuonsGlobalSTACand;
   int dimuonsGlobalSTASize =dimuonsGlobalSTAColl.size();
   cout<<" no of dimuonsGlobalSTA  :" <<dimuonsGlobalSTASize <<endl;
   for(size_t ii = 0; ii <dimuonsGlobalSTAColl.size(); ++ ii) {
     const reco::Candidate& p = (dimuonsGlobalSTAColl)[ii];
     //histContainer2D["diMuonInvMassVsPt"]->Fill(p.mass(),p.pt());
     diMuonsGlobalSTAInvMassVsPt->Fill(p.mass(),p.pt());
     diMuonsGlobalSTAInvMassVsY->Fill(p.mass(),p.rapidity());
     diMuonsGlobalSTAInvMassVsCen->Fill(p.mass(),bin);   
   }

   // get dimuonSTA collection 
   edm::Handle<edm::View<reco::Candidate> > diMuonsSTACand;
   iEvent.getByLabel("dimuonsSTA", diMuonsSTACand);
   edm::View<reco::Candidate>dimuonsSTAColl= *diMuonsSTACand;
   int dimuonsSTASize =dimuonsSTAColl.size();
   cout<<" no of dimuonsSTA  :" <<dimuonsSTASize <<endl;
   for(size_t ii = 0; ii <dimuonsSTAColl.size(); ++ ii) {
     const reco::Candidate& p = (dimuonsSTAColl)[ii];
     //histContainer2D["diMuonInvMassVsPt"]->Fill(p.mass(),p.pt());
     diMuonsSTAInvMassVsPt->Fill(p.mass(),p.pt());
     diMuonsSTAInvMassVsY->Fill(p.mass(),p.rapidity());
     diMuonsSTAInvMassVsCen->Fill(p.mass(),bin);
   }
   
   SameChargePlots(iEvent, iSetup);
   cout<<"generator info " <<fIsGenInfo.c_str()<<endl;
   

   if(!strcmp(fIsGenInfo.c_str(),"TRUE")){GenPlots(iEvent, iSetup);}



}


void ZToMuMu2DPlots::SameChargePlots(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;

  // get dimuonGlobal same charge collection                                                                                                               
  edm::Handle<edm::View<reco::Candidate> > diMuonsGlobalSameChargeCand;
  iEvent.getByLabel("dimuonsGlobalSameCharge", diMuonsGlobalSameChargeCand);
  edm::View<reco::Candidate>dimuonsGlobalSameChargeColl= *diMuonsGlobalSameChargeCand;
  int dimuonsGlobalSameChargeSize =dimuonsGlobalSameChargeColl.size();
  cout<<" no of dimuon Global same charge  :" <<dimuonsGlobalSameChargeSize <<endl;
  for(size_t ii = 0; ii <dimuonsGlobalSameChargeColl.size(); ++ ii) {
    const reco::Candidate& p = (dimuonsGlobalSameChargeColl)[ii];
    //histContainer2D["diMuonInvMassVsPt"]->Fill(p.mass(),p.pt());                                                                          
    diMuonsGlobalSameChargeInvMassVsPt->Fill(p.mass(),p.pt());
    diMuonsGlobalSameChargeInvMassVsY->Fill(p.mass(),p.rapidity());
    diMuonsGlobalSameChargeInvMassVsCen->Fill(p.mass(),bin);
  }



  // get dimuonGlobal STA same charge collection 
    edm::Handle<edm::View<reco::Candidate> > diMuonsGlobalSTASameChargeCand;
    iEvent.getByLabel("dimuonsGlobalSTASameCharge", diMuonsGlobalSTASameChargeCand);
    edm::View<reco::Candidate>dimuonsGlobalSTASameChargeColl= *diMuonsGlobalSTASameChargeCand;
    int dimuonsGlobalSTASameChargeSize =dimuonsGlobalSTASameChargeColl.size();
    cout<<" no of dimuon Global STA same charge  :" <<dimuonsGlobalSTASameChargeSize <<endl;
    for(size_t ii = 0; ii <dimuonsGlobalSTASameChargeColl.size(); ++ ii) {
      const reco::Candidate& p = (dimuonsGlobalSTASameChargeColl)[ii];
      //histContainer2D["diMuonInvMassVsPt"]->Fill(p.mass(),p.pt());                                                                          
      diMuonsGlobalSTASameChargeInvMassVsPt->Fill(p.mass(),p.pt());
      diMuonsGlobalSTASameChargeInvMassVsY->Fill(p.mass(),p.rapidity());
      diMuonsGlobalSTASameChargeInvMassVsCen->Fill(p.mass(),bin);
    }



    // get dimuon sta same charge collection                                                                                                                                                           
    edm::Handle<edm::View<reco::Candidate> > diMuonsSTASameChargeCand;
    iEvent.getByLabel("dimuonsSTASameCharge", diMuonsSTASameChargeCand);
    edm::View<reco::Candidate>dimuonsSTASameChargeColl= *diMuonsSTASameChargeCand;
    int dimuonsSTASameChargeSize =dimuonsSTASameChargeColl.size();
    cout<<" no of dimuon STA same charge  :" <<dimuonsSTASameChargeSize <<endl;
    for(size_t ii = 0; ii <dimuonsSTASameChargeColl.size(); ++ ii) {
      const reco::Candidate& p = (dimuonsSTASameChargeColl)[ii];
      //histContainer2D["diMuonInvMassVsPt"]->Fill(p.mass(),p.pt());                                                                                                                                   
      diMuonsSTASameChargeInvMassVsPt->Fill(p.mass(),p.pt());
      diMuonsSTASameChargeInvMassVsY->Fill(p.mass(),p.rapidity());
      diMuonsSTASameChargeInvMassVsCen->Fill(p.mass(),bin);
    }

}




void ZToMuMu2DPlots::GenPlots(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  cout<<"gen info: "<<endl;
  using namespace edm;
  using namespace std;
  edm::Handle<edm::View<reco::GenParticle> >genPar ;
  iEvent.getByLabel("hiGenParticles",genPar) ;
  edm::View<reco::GenParticle> genParticles = *genPar ;
  //unsigned int genparsize=genParticles.size();
  for(size_t i = 0; i < genParticles.size(); ++ i) {
    const reco::GenParticle& part1 = (*genPar)[i];
    //cout<<"befor mom ID "<<endl;
    //const Candidate *mom1 = part1.mother();    
    //int momID1 =mom1->pdgId();
    // cout<<"momId1 "<<momID1<<endl;


    for(size_t j = i+1; j<genParticles.size(); ++j) {
      const reco::GenParticle& part2 = (*genPar)[j];
      //const Candidate *mom2 = part2.mother();
      //int momID2 =mom2->pdgId();
      
     
      if ( ( i != j) && ( (part1.pdgId()*part2.pdgId()==-169 && part1.status()*part2.status()==1))){
	TLorentzVector  genvector1,genvector2,genvector3;
        genvector1.SetPxPyPzE(part1.px(), part1.py(), part1.pz(), part1.energy());
        genvector2.SetPxPyPzE(part2.px(), part2.py(), part2.pz(), part2.energy());
        genvector3=genvector1+genvector2;
        //float GenDiMuonEta=genvector3.Eta();
        float GenDiMuonY=genvector3.Rapidity();
        //float GenDiMuonY1=genvector3.Rapidity();
        float GenDiMuonMinv=genvector3.M();
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
}


// ------------ method called once each job just before starting event loop  ------------
void 
ZToMuMu2DPlots::beginJob()
{
  edm::Service<TFileService> fs;
  fOutputFile   = new TFile( fOutputFileName.c_str(), "RECREATE" );
  cout<<"begin job"<<endl;
  //if (!fOutputFile) cout<<"File not open "<<endl;
  //fOutputFile->cd();
  //diMuonInvMassVsPt = new TH2F(fhistName.c_str(), fhistName.c_str(), 100, 0, 100, 100, 0, 200);
  diMuonsGlobalInvMassVsPt = new TH2F("diMuonsGlobalInvMassVsPt", "diMuonsGlobalInvMassVsPt", 4000, 0, 200, 100,0,100);
  diMuonsGlobalInvMassVsPt->SetYTitle("pT (GeV/C^{2})");
  diMuonsGlobalInvMassVsPt->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGlobalInvMassVsY = new TH2F("diMuonsGlobalInvMassVsY","diMuonsGlobalInvMassVsY",4000, 0, 200,100, -5, 5);
  diMuonsGlobalInvMassVsY->SetYTitle("rapidity");
  diMuonsGlobalInvMassVsY->SetXTitle("Inv Mass (GeV/C^{2})");
  
  diMuonsGlobalInvMassVsCen = new TH2F("diMuonsGlobalInvMassVsCen","diMuonsGlobalInvMassVsCen", 4000, 0, 200,100,0,100);
  diMuonsGlobalInvMassVsCen->SetXTitle("Inv Mass (GeV/C^{2})");
  diMuonsGlobalInvMassVsCen->SetYTitle("Centrality");

  diMuonsGlobalSTAInvMassVsPt = new TH2F("diMuonsGlobalSTAInvMassVsPt", "diMuonsGlobalSTAInvMassVsPt",4000, 0, 200,100, 0, 100);
  diMuonsGlobalSTAInvMassVsPt->SetYTitle("pT (GeV/C^{2})");
  diMuonsGlobalSTAInvMassVsPt->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGlobalSTAInvMassVsY = new TH2F("diMuonsGlobalSTAInvMassVsY","diMuonsGlobalSTAInvMassVsY", 4000, 0, 200, 100, -5, 5);
  diMuonsGlobalSTAInvMassVsY->SetYTitle("rapidity");
  diMuonsGlobalSTAInvMassVsY->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGlobalSTAInvMassVsCen = new TH2F("diMuonsGlobalSTAInvMassVsCen","diMuonsGlobalSTAInvMassVsCen",4000, 0, 200,100,0,100);
  diMuonsGlobalSTAInvMassVsCen->SetXTitle("Inv Mass (GeV/C^{2})");
  diMuonsGlobalSTAInvMassVsCen->SetYTitle("Centrality");

  diMuonsSTAInvMassVsPt = new TH2F("diMuonsSTAInvMassVsPt","diMuonsSTAInvMassVsPt", 4000, 0, 200, 100,0,100);
  diMuonsSTAInvMassVsPt->SetYTitle("pT (GeV/C^{2})");
  diMuonsSTAInvMassVsPt->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsSTAInvMassVsY = new TH2F("diMuonsSTAInvMassVsY","diMuonsSTAInvMassVsY",4000, 0, 200, 100, -5, 5);
  diMuonsSTAInvMassVsY->SetYTitle("rapidity");
  diMuonsSTAInvMassVsY->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsSTAInvMassVsCen = new TH2F("diMuonsSTAInvMassVsCen","diMuonsSTAInvMassVsCen", 4000, 0, 200,100,0,100);
  diMuonsSTAInvMassVsCen->SetXTitle("Inv Mass (GeV/C^{2})");
  diMuonsSTAInvMassVsCen->SetYTitle("Centrality");

  Centrality = new TH1F("Centrality","Centrality", 100,0,100);

  
  diMuonsGlobalSameChargeInvMassVsPt = new TH2F("diMuonsGlobalSameChargeInvMassVsPt", "diMuonsGlobalSameChargeInvMassVsPt", 4000, 0, 200, 100,0,100);
  diMuonsGlobalSameChargeInvMassVsPt->SetYTitle("pT (GeV/C^{2})");
  diMuonsGlobalSameChargeInvMassVsPt->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGlobalSameChargeInvMassVsY = new TH2F("diMuonsGlobalSameChargeInvMassVsY","diMuonsGlobalSameChargeInvMassVsY",4000, 0, 200,100, -5, 5);
  diMuonsGlobalSameChargeInvMassVsY->SetYTitle("rapidity");
  diMuonsGlobalSameChargeInvMassVsY->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGlobalSameChargeInvMassVsCen = new TH2F("diMuonsGlobalSameChargeInvMassVsCen","diMuonsGlobalSameChargeInvMassVsCen", 4000, 0, 200,100,0,100);
  diMuonsGlobalSameChargeInvMassVsCen->SetXTitle("Inv Mass (GeV/C^{2})");
  diMuonsGlobalSameChargeInvMassVsCen->SetYTitle("Centrality");


  diMuonsGlobalSTASameChargeInvMassVsPt = new TH2F("diMuonsGlobalSTASameChargeInvMassVsPt", "diMuonsGlobalSTASameChargeInvMassVsPt",4000, 0, 200,100, 0, 100);
  diMuonsGlobalSTASameChargeInvMassVsPt->SetYTitle("pT (GeV/C^{2})");
  diMuonsGlobalSTASameChargeInvMassVsPt->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGlobalSTASameChargeInvMassVsY = new TH2F("diMuonsGlobalSTASameChargeInvMassVsY","diMuonsGlobalSTASameChargeInvMassVsY", 4000, 0, 200, 100, -5, 5);
  diMuonsGlobalSTASameChargeInvMassVsY->SetYTitle("rapidity");
  diMuonsGlobalSTASameChargeInvMassVsY->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGlobalSTASameChargeInvMassVsCen = new TH2F("diMuonsGlobalSTASameChargeInvMassVsCen","diMuonsGlobalSTASameChargeInvMassVsCen",4000, 0, 200,100,0,100);
  diMuonsGlobalSTASameChargeInvMassVsCen->SetXTitle("Inv Mass (GeV/C^{2})");
  diMuonsGlobalSTASameChargeInvMassVsCen->SetYTitle("Centrality");


  diMuonsSTASameChargeInvMassVsPt = new TH2F("diMuonsSTASameChargeInvMassVsPt","diMuonsSTASameChargeInvMassVsPt", 4000, 0, 200, 100,0,100);
  diMuonsSTASameChargeInvMassVsPt->SetYTitle("pT (GeV/C^{2})");
  diMuonsSTASameChargeInvMassVsPt->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsSTASameChargeInvMassVsY = new TH2F("diMuonsSTASameChargeInvMassVsY","diMuonsSTASameChargeInvMassVsY",4000, 0, 200, 100, -5, 5);
  diMuonsSTASameChargeInvMassVsY->SetYTitle("rapidity");
  diMuonsSTASameChargeInvMassVsY->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsSTASameChargeInvMassVsCen = new TH2F("diMuonsSTASameChargeInvMassVsCen","diMuonsSTASameChargeInvMassVsCen", 4000, 0, 200,100,0,100);
  diMuonsSTASameChargeInvMassVsCen->SetXTitle("Inv Mass (GeV/C^{2})");
  diMuonsSTASameChargeInvMassVsCen->SetYTitle("Centrality");


  diMuonsGenInvMassVsPt = new TH2F("diMuonsGenInvMassVsPt", "diMuonsGenInvMassVsPt", 4000, 0, 200, 100,0,100);
  diMuonsGenInvMassVsPt->SetYTitle("pT (GeV/C^{2})");
  diMuonsGenInvMassVsPt->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGenInvMassVsY = new TH2F("diMuonsGenInvMassVsY","diMuonsGenInvMassVsY",4000, 0, 200,100, -5, 5);
  diMuonsGenInvMassVsY->SetYTitle("rapidity");
  diMuonsGenInvMassVsY->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGenInvMassVsCen = new TH2F("diMuonsGenInvMassVsCen","diMuonsGenInvMassVsCen", 4000, 0, 200,100,0,100);
  diMuonsGenInvMassVsCen->SetXTitle("Inv Mass (GeV/C^{2})");
  diMuonsGenInvMassVsCen->SetYTitle("Centrality");

  diMuonsGenInvMass = new TH1F("diMuonsGenInvMass","diMuonsGenInvMass", 4000,0,200);
  diMuonsGenPt = new TH1F("diMuonsGenPt","diMuonsGenPt", 100,0,20);
  diMuonsGenRapidity = new TH1F("diMuonsGenRapidity","diMuonsGenRapidity", 100,-10,10);



//  h_ZetaGen_ = genParticleDir.make<TH1D>("generatedZeta","#eta of generated Z",100,-5.,5.); 
}


// ------------ method called once each job just after ending the event loop  ------------
void ZToMuMu2DPlots::endJob() 
{
  cout<<"End Job"<<endl;
  fOutputFile->cd();
  diMuonsGlobalInvMassVsPt->Write();
  diMuonsGlobalInvMassVsY->Write();
  diMuonsGlobalInvMassVsCen->Write();
  diMuonsGlobalSTAInvMassVsPt->Write();
  diMuonsGlobalSTAInvMassVsY->Write();
  diMuonsGlobalSTAInvMassVsCen->Write();
  diMuonsSTAInvMassVsPt->Write();
  diMuonsSTAInvMassVsY->Write();
  diMuonsSTAInvMassVsCen->Write();
  Centrality->Write(); 
  diMuonsGlobalSameChargeInvMassVsPt->Write();
  diMuonsGlobalSameChargeInvMassVsY->Write();
  diMuonsGlobalSameChargeInvMassVsCen->Write();
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




fOutputFile->Close();
}

//define this as a plug-in
DEFINE_FWK_MODULE(ZToMuMu2DPlots);
