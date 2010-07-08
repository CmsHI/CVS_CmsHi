// -*- C++ -*-
//
// Package:    MinBiasTowerAnalyzer
// Class:      MinBiasTowerAnalyzer
// 
/**\class MinBiasTowerAnalyzer MinBiasTowerAnalyzer.cc yetkin/MinBiasTowerAnalyzer/src/MinBiasTowerAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yetkin Yilmaz
//         Created:  Wed Oct  3 08:07:18 EDT 2007
// $Id: MinBiasTowerAnalyzer.cc,v 1.4 2010/07/08 16:34:01 nart Exp $
//
//


// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
//#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"

#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/JetReco/interface/JetCollection.h"
#include "DataFormats/JetReco/interface/Jet.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TNtuple.h>
#include <TMath.h>
#include <TString.h>
#include <TRandom.h>

using namespace std;
using namespace edm;
using namespace reco;

static const int nEtaBins = 4;
static const int nPhiBins = 4;
static const int nCentBins = 11;


//
// class decleration
//

class MinBiasTowerAnalyzer : public edm::EDAnalyzer {
public:
  explicit MinBiasTowerAnalyzer(const edm::ParameterSet&);
  ~MinBiasTowerAnalyzer();
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  void loadEvent(const edm::Event&, const edm::EventSetup&);
  void sumET();
  void analyzeMC();
  int analyzeGenParticles();
  void analyzeTowers();
  void analyzeRandomCones();
  double       getEt(const DetId &id, double energy);
  double       getEta(const DetId &id);
  double       getPhi(const DetId &id);
  
  // ----------member data ---------------------------
   
  
  int iEtamax_;
  double SumEtMin_;
  double SumEtMax_;
  double jetEtMin_;
  double sumET_;
  double Et_Min_;
  double Et_Max_;
  int missingTowers_;
  
  double cone_;
  double genJetPtMin_;
  double towersize_;
  double jetEtaMax_;
  double genpartEtamax_;
  double b_;
  double npart_;
  double ncoll_;
  double nhard_;
  double phi0_;
  
  bool doMC_;
  bool doGenParticles_;
  bool excludeJets_;
  InputTag jetSrc_;
  InputTag Hi_;
  InputTag HiCent_;
  InputTag Towers_;
  InputTag jetFake_;
  InputTag jetGen_;
  InputTag Direct_;
  
  const CaloGeometry *geo;
  edm::Service<TFileService> fs;
  
  TNtuple* nt;
  TRandom * rand;

  edm::Handle<CaloTowerCollection> towers;
  edm::Handle<pat::JetCollection> jets;
  edm::Handle<reco::CaloJetCollection> calojets;
	edm::Handle<reco::CaloJetCollection> fakejets;
  edm::Handle<std::vector<bool> > directions;
  edm::Handle<reco::GenJetCollection> genjets;
  edm::Handle<reco::GenParticleCollection> genparticles;

	edm::Handle<edm::GenHIEvent> mc;
	edm::Handle<reco::Centrality> centrality;
	const CentralityBins* cbins_;

	TH1D* hNtowers;
	TH1D* hNtowers2;
	TH1D* hGenpt;
	TH1D* hhGeneta;
	TH1D* hGenet;
	TH1D* hETeta;
	TH1D* hETphi;
	TH2D* hMeanETdNdEta;
	TH1D* hTowerEta;
	TH1D* hTowerET;
	TH1D* hhSumET;
	TH1D* hTowerETjet;
	TH1D* hTowerETnojet;
	TH1D* toweret;
	TH1D* hPtGen;
	TH1D* hDndeta;
	TH1D* hRMS;
	TH1D* hMean;
	TH1D* hMeanNoJets;
	TH1D* hMeanRMS;
	TH1D* hMeanRMSnoJets;
	TH1D* hRMSnoJets;
	TH1D* hJetET;
   
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
MinBiasTowerAnalyzer::MinBiasTowerAnalyzer(const edm::ParameterSet& iConfig) : 
  cbins_(0),
  geo(0)
{
   //now do what ever initialization is needed
	TH1D::SetDefaultSumw2();
	SumEtMin_ = iConfig.getUntrackedParameter<double>("sumEtMin",1000);
	SumEtMax_ = iConfig.getUntrackedParameter<double>("sumEtMax",1500);

	jetEtMin_ = iConfig.getUntrackedParameter<double>("jetEtMin",0);
	missingTowers_ = iConfig.getUntrackedParameter<int>("missingTowers",67);
	cone_ = iConfig.getUntrackedParameter<double>("coneSize",0.5);

	genJetPtMin_ =  iConfig.getUntrackedParameter<double>("genJetPtMin",20);
	towersize_ = iConfig.getUntrackedParameter<int>("nTowers",1584);
	jetEtaMax_ = iConfig.getUntrackedParameter<double>("jetEtaMax",1);
	genpartEtamax_ = 0.5;
	iEtamax_ = 11.5;
	
	doMC_ = iConfig.getUntrackedParameter<bool>("doMC",false);
	doGenParticles_  = iConfig.getUntrackedParameter<bool>("doGenParticles",false);
        excludeJets_ = iConfig.getUntrackedParameter<bool>("excludeJets",false);
	
	jetSrc_ = iConfig.getUntrackedParameter<edm::InputTag>("jetSrc_",edm::InputTag("icPu5patJets"));
	Hi_ = iConfig.getUntrackedParameter<edm::InputTag>("Hi_",edm::InputTag("heavyIon"));
	HiCent_ = iConfig.getUntrackedParameter<edm::InputTag>("HiCent_",edm::InputTag("hiCentrality"));
	Towers_ = iConfig.getUntrackedParameter<edm::InputTag>("Towers_",edm::InputTag("towerMaker"));
	jetFake_ = iConfig.getUntrackedParameter<edm::InputTag>("jetFake_",edm::InputTag("bkg5Jets"));
	Direct_ = iConfig.getUntrackedParameter<edm::InputTag>("Direct_",edm::InputTag("bkg5Jets","directions"));
	jetGen_ = iConfig.getUntrackedParameter<edm::InputTag>("jetGen_",edm::InputTag("iterativeCone5HiGenJets"));
	
}


MinBiasTowerAnalyzer::~MinBiasTowerAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------


void
MinBiasTowerAnalyzer::analyze(const edm::Event& ev, const edm::EventSetup& iSetup)
{
   loadEvent(ev, iSetup);
   sumET();
   if(doMC_){
      analyzeMC();
   }
   
   analyzeTowers();
   analyzeRandomCones();
   
}

void MinBiasTowerAnalyzer::loadEvent(const edm::Event& ev, const edm::EventSetup& iSetup){

   using namespace edm;
   if(!geo){
      edm::ESHandle<CaloGeometry> pGeo;
      iSetup.get<CaloGeometryRecord>().get(pGeo);
      geo = pGeo.product();
   }
   if(!cbins_) cbins_ = getCentralityBinsFromDB(iSetup);

   ev.getByLabel(Hi_,mc);
   ev.getByLabel(HiCent_,centrality);
   ev.getByLabel(Towers_,towers);
   ev.getByLabel(jetSrc_,jets);
   // ev.getByLabel(edm::InputTag("iterativeConePu5CaloJets"),jets); 
   ev.getByLabel(Direct_,directions);
   ev.getByLabel(jetFake_,fakejets);
   ev.getByLabel(jetGen_,genjets);
	
}

void MinBiasTowerAnalyzer::sumET(){
   sumET_ = 0;
   for(unsigned int i = 0 ; i < towers->size(); ++i){
      const CaloTower& tower = (*towers)[i];
      if(abs(tower.ieta())>iEtamax_) continue;
      double tower_et = tower.et();
      sumET_=sumET_+tower_et;
   }
}

void MinBiasTowerAnalyzer::analyzeMC(){

b_ = mc->b();
npart_ = mc->Npart();
ncoll_ = mc->Ncoll();
nhard_ = mc->Nhard();
phi0_ = mc->evtPlane();

}

void MinBiasTowerAnalyzer::analyzeTowers(){


	bool interest = sumET_>SumEtMin_ && sumET_<SumEtMax_;
	double hf = centrality->EtHFhitSum();
	int bin = cbins_->getBin(hf);
	double sumofTowerpt = 0;
	double sumofTowerNojetpt = 0;
	double T_ptsquare = 0;
	double T_nojet_ptsquare = 0;
	double rmsofTowerpt =0;
	double rmsofNojetTowerpt = 0;
	double numberofTower = 0;
	double numberofNojetTower = 0;
	double average_ptrms = 0;
	double average_Nojetptrms = 0;
	double Zeroptcount = 0;

	int genparticlecount = 0;
	if(doMC_ && doGenParticles_) genparticlecount = analyzeGenParticles();
	
	// Run analysis on towers

	for(unsigned int i = 0 ; i < towers->size(); ++i){
		const CaloTower& tower = (*towers)[i];
		if(abs(tower.ieta())>iEtamax_) continue;
      
		numberofTower++;
      
	   double eta = tower.eta();
	   double pt = tower.pt();
	   double et = tower.et();
	   double phi = tower.phi();      
	   bool recomatched = false;
	   
		sumofTowerpt=sumofTowerpt+pt;
		T_ptsquare=T_ptsquare+pt*pt;
		hTowerET->Fill(pt);
		if(pt==0) Zeroptcount++;
		hTowerEta->Fill(eta);
		toweret->Fill(et);
		hETeta->Fill(eta,pt);
		hETphi->Fill(phi,et);
		

      for(unsigned int j = 0 ; j < jets->size(); ++j){
	 //         const reco::CaloJet& jet = (*jets)[j];
	 const pat::Jet& jet = (*jets)[j];

	 double rawEt = jet.correctedJet("raw").et();
	 if(rawEt < jetEtMin_ ) continue;
	 double dr = reco::deltaR(tower.eta(),tower.phi(),jet.eta(),jet.phi());
	 if(dr < cone_){
	    recomatched = true;
	 }
      }
      if(recomatched){
	 hTowerETjet->Fill(pt);
      }
      else {
	 hTowerETnojet->Fill(pt);
	 sumofTowerNojetpt=sumofTowerNojetpt+pt;
	 numberofNojetTower++;
	 T_nojet_ptsquare=T_nojet_ptsquare+pt*pt;
      }

   }
	
	for(unsigned int k=0; k< (towersize_- numberofTower) ; k++)
	{	hTowerET->Fill(0); }

      
      double average_pt=sumofTowerpt/(numberofTower);
      double average_nojetpt=sumofTowerNojetpt/numberofNojetTower;
      rmsofNojetTowerpt=sqrt( (T_nojet_ptsquare/numberofNojetTower) - (average_nojetpt*average_nojetpt));
      hRMSnoJets->Fill(rmsofNojetTowerpt);
      hMean->Fill(average_pt);
      hMeanNoJets->Fill(average_nojetpt);
      rmsofTowerpt=sqrt( ( T_ptsquare/numberofTower ) - (average_pt*average_pt) );
      hRMS->Fill(rmsofTowerpt);
      average_ptrms=average_pt+rmsofTowerpt;
      average_Nojetptrms=average_nojetpt+rmsofNojetTowerpt;
      hMeanRMS->Fill(average_ptrms);
      hMeanRMSnoJets->Fill(average_Nojetptrms);
      hMeanETdNdEta->Fill(average_ptrms,genparticlecount);


}

/// LOOP OVER gen particles

int MinBiasTowerAnalyzer::analyzeGenParticles(){
  
	bool interest = sumET_>SumEtMin_ && sumET_<SumEtMax_;
	int genparticlecount = 0;
	
	for(unsigned int i = 0 ; i < genparticles->size(); ++i){
	   const reco::GenParticle& genparticle = (*genparticles)[i];
	   if(fabs(genparticle.eta())>genpartEtamax_) continue;
	   if(genparticle.charge() != 0) continue;
	   if(genparticle.status() == 1) {
	      double pt = genparticle.pt();
	      hPtGen->Fill(pt);
	      genparticlecount++;
	   }
	}
	hDndeta->Fill(genparticlecount); 
	return genparticlecount;
}

void MinBiasTowerAnalyzer::analyzeRandomCones(){
   bool interest = sumET_>SumEtMin_ && sumET_<SumEtMax_;
   int njet = jets->size();
   int njet20 = 0;
   int njet30 = 0;

   double hf = centrality->EtHFhitSum();
   int bin = cbins_->getBin(hf);
   
   for(unsigned int i = 0 ; i < fakejets->size(); ++i){
      const reco::CaloJet& fakejet = (*fakejets)[i];
      vector<edm::Ptr<CaloTower> > constits = fakejet.getCaloConstituents();
      double aveta = 0;
      double totpt = 0;
      double avphi = 0;

      int ncons = constits.size();
      vector<int> used;

      double area = fakejet.towersArea();

      double sign = (int)((*directions)[i])*2 - 1;
      double fpt = sign*fakejet.pt();
      double fpu = fakejet.pileup();
      double phi = reco::deltaPhi(fakejet.phi(),phi0_);

      int nc = 0;
      for(int ic1 = 0; ic1 < ncons-missingTowers_; ++ic1){
	 int ic = -1;
	 while(find(used.begin(),used.end(), ic) != used.end() || ic < 0 || ic >= ncons){
            ic = (int)(ncons*rand->Rndm());
	 }
	 used.push_back(ic);

	 double toweta = constits[ic]->eta();
	 double towphi = reco::deltaPhi(constits[ic]->phi(),phi0_);
	 double towpt = constits[ic]->et();
	 aveta += toweta*towpt;
	 avphi += towphi*towpt;
	 totpt += towpt;
	 nc++;

      }

      aveta /= totpt;
      avphi /= totpt;

      float entry[17] = {fakejet.eta(),aveta,phi,avphi,fpt+fpu,totpt,bin,fpt+fpu,fpu,fpt,sign,njet,njet20,njet30,ncons,area,nc};
      nt->Fill(entry);
      
      if(interest){
	 float entry[17] = {fakejet.eta(),aveta,phi,avphi,fpt+fpu,totpt,-1,fpt+fpu,fpu,fpt,sign,njet,njet20,njet30,ncons,area,nc};
	 nt->Fill(entry);
      }
      
   }
      
}


// ------------ method called once each job just before starting event loop  ------------
void 
MinBiasTowerAnalyzer::beginJob()
{
   nt = fs->make<TNtuple>("nt","","eta1:eta2:phi1:phi2:pt1:pt2:bin:et:pu:subt:sign:njet:njet20:njet30:ncons:area:nc");
   rand = new TRandom();

	hNtowers = fs->make<TH1D>("nTowers","histogram;N_{towers};entries",480,-0.5,60.5);
	hNtowers2 = fs->make<TH1D>("nTowers2","histogram;N_{towers}; entries",240,-0.5,60.5);          
	hGenpt = fs->make<TH1D>("hGenpt","histogram",100,0,100);
	hhGeneta = fs->make<TH1D>("hhGeneta","histogram",100,-10,10);
	hGenet = fs->make<TH1D>("hGenet","histogram",100,0,100);
	hETeta = fs->make<TH1D>("eta-pt","fhisto; eta ;pt(GeV/c) ",1000,-15,15);
	hETphi = fs->make<TH1D>("et-phi","fhisto; phi ;et(GeV) ",1000,-5,5);
	hMeanETdNdEta = fs->make<TH2D>("hMeanETdNdEta","mean_dndeta; mean tower p_{T} [GeV/c]; dNdeta",100,0,2,300,0,3000);
	hTowerEta = fs->make<TH1D>("hTowerEta","histogram; eta",1000,-15,15);
	hTowerET = fs->make<TH1D>("hTowerET","histogram; p_{T} [GeV/c]; entries",505,-1,100);
	hhSumET = fs->make<TH1D>("hhSumET","histogram;SumTower E_{T}[GeV]; entries",250,-1,2501);
	hTowerETjet = fs->make<TH1D>("hTowerETjet","histo; p_{T} [GeV/c]; entries",505,-1,100);
	hTowerETnojet = fs->make<TH1D>("pt_nojet","histo; p_{T} [GeV/c]; entries",505,-1,100);
	toweret = fs->make<TH1D>("toweret","histogram; E_{T} [GeV]; entries",505,-1,100);
	hPtGen = fs->make<TH1D>("hPtGen","histogram; p_{T} [GeV/c]; entries",100,0,100);
	hDndeta = fs->make<TH1D>("hDndeta","histogram; dNdeta; entries",300,0,3000);
	hRMS= fs->make<TH1D> ("tower_rms","histo",100,0.,1.5);
	hMean = fs->make<TH1D>("ptaverage","histo;p_{T} GeV/c; entries",100, 0.,1.5);
	hMeanNoJets = fs->make<TH1D>("nojet_ptaverage","histo;p_{T} GeV/c",100, 0.,1.5);
	hMeanRMS = fs->make<TH1D>("tower_mean_rms","histo; Tower mean+rms p_{T} [GeV/c]; entries",100,0.5,2.5);
	hMeanRMSnoJets= fs->make<TH1D>("hMeanRMSnoJets","histo; No-Jet Tower mean+rms p_{T} [GeV/c]; entries",100,0.5,2.);
	hRMSnoJets = fs->make<TH1D>("hRMSnoJets","histo; hRMSnoJets",100,0,1.5);
	hJetET = fs->make<TH1D>("hJetET","histogram;Jet E_{T} [GeV]; entries",280,0,70);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
MinBiasTowerAnalyzer::endJob() {

}

double MinBiasTowerAnalyzer::getEt(const DetId &id, double energy){
   const GlobalPoint& pos=geo->getPosition(id);
   double et = energy*sin(pos.theta());
   return et;
}
 
double MinBiasTowerAnalyzer::getEta(const DetId &id){
   const GlobalPoint& pos=geo->getPosition(id);
   double et = pos.eta();
   return et;
}

double MinBiasTowerAnalyzer::getPhi(const DetId &id){
   const GlobalPoint& pos=geo->getPosition(id);
   double et = pos.phi();
   return et;
}

//define this as a plug-in
DEFINE_FWK_MODULE(MinBiasTowerAnalyzer);
