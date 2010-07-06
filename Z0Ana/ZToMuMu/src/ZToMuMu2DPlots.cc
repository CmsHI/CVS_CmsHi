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
// $Id: ZToMuMu2DPlots.cc,v 1.1 2010/05/14 10:44:32 kumarv Exp $
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



using std::cout;
using std::endl;
// class decleration       
// user include files
//#include "FWCore/Framework/interface/Frameworkfwd.h"
//#include "FWCore/Framework/interface/EDAnalyzer.h"
//#include "FWCore/Framework/interface/Event.h"
//#include "FWCore/Framework/interface/MakerMacros.h"
//#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "PhysicsTools/FWLite/interface/TFileService.h"
//#include "FWCore/ServiceRegistry/interface/Service.h"

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

private:
  
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
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
  cbins_(0),fOutputFileName(iConfig.getUntrackedParameter<string>("OutputFileName")),
  Centrality(0),diMuonsGlobalInvMassVsPt(0),diMuonsGlobalInvMassVsY(0),diMuonsGlobalInvMassVsCen(0),diMuonsGlobalSTAInvMassVsPt(0),diMuonsGlobalSTAInvMassVsY(0),diMuonsGlobalSTAInvMassVsCen(0),diMuonsSTAInvMassVsPt(0),diMuonsSTAInvMassVsY(0),diMuonsSTAInvMassVsCen(0)


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

   int bin = cbins_->getBin(hf);

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
  diMuonsGlobalInvMassVsPt = new TH2F("diMuonsGlobalInvMassVsPt", "diMuonsGlobalInvMassVsPt", 100, 0, 200, 100,0,100);
  diMuonsGlobalInvMassVsPt->SetYTitle("pT (GeV/C^{2})");
  diMuonsGlobalInvMassVsPt->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGlobalInvMassVsY = new TH2F("diMuonsGlobalInvMassVsY","diMuonsGlobalInvMassVsY",100, 0, 200,100, -5, 5);
  diMuonsGlobalInvMassVsY->SetYTitle("rapidity");
  diMuonsGlobalInvMassVsY->SetXTitle("Inv Mass (GeV/C^{2})");
  
  diMuonsGlobalInvMassVsCen = new TH2F("diMuonsGlobalInvMassVsCen","diMuonsGlobalInvMassVsCen", 100, 0, 200,100,0,100);
  diMuonsGlobalInvMassVsCen->SetXTitle("Inv Mass (GeV/C^{2})");
  diMuonsGlobalInvMassVsCen->SetYTitle("Centrality");

  diMuonsGlobalSTAInvMassVsPt = new TH2F("diMuonsGlobalSTAInvMassVsPt", "diMuonsGlobalSTAInvMassVsPt",100, 0, 200,100, 0, 100);
  diMuonsGlobalSTAInvMassVsPt->SetYTitle("pT (GeV/C^{2})");
  diMuonsGlobalSTAInvMassVsPt->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGlobalSTAInvMassVsY = new TH2F("diMuonsGlobalSTAInvMassVsY","diMuonsGlobalSTAInvMassVsY", 100, 0, 200, 100, -5, 5);
  diMuonsGlobalSTAInvMassVsY->SetYTitle("rapidity");
  diMuonsGlobalSTAInvMassVsY->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsGlobalSTAInvMassVsCen = new TH2F("diMuonsGlobalSTAInvMassVsCen","diMuonsGlobalSTAInvMassVsCen",100, 0, 200,100,0,100);
  diMuonsGlobalSTAInvMassVsCen->SetXTitle("Inv Mass (GeV/C^{2})");
  diMuonsGlobalSTAInvMassVsCen->SetYTitle("Centrality");

  diMuonsSTAInvMassVsPt = new TH2F("diMuonsSTAInvMassVsPt","diMuonsSTAInvMassVsPt", 100, 0, 200, 100,0,100);
  diMuonsSTAInvMassVsPt->SetYTitle("pT (GeV/C^{2})");
  diMuonsSTAInvMassVsPt->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsSTAInvMassVsY = new TH2F("diMuonsSTAInvMassVsY","diMuonsSTAInvMassVsY",100, 0, 200, 100, -5, 5);
  diMuonsSTAInvMassVsY->SetYTitle("rapidity");
  diMuonsSTAInvMassVsY->SetXTitle("Inv Mass (GeV/C^{2})");

  diMuonsSTAInvMassVsCen = new TH2F("diMuonsSTAInvMassVsCen","diMuonsSTAInvMassVsCen", 100, 0, 200,100,0,100);
  diMuonsSTAInvMassVsCen->SetXTitle("Inv Mass (GeV/C^{2})");
  diMuonsSTAInvMassVsCen->SetYTitle("Centrality");

  Centrality = new TH1F("Centrality","Centrality", 100,0,100);

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
  fOutputFile->Close();
}

//define this as a plug-in
DEFINE_FWK_MODULE(ZToMuMu2DPlots);
