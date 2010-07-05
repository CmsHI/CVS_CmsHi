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
// $Id: MinBiasTowerAnalyzer.cc,v 1.3 2010/06/03 09:11:03 yilmaz Exp $
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
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
   void loadEvent(const edm::Event&, const edm::EventSetup&);
   void sumET();
   void analyzeMC();
   void analyzeTowers();
   void analyzeRandomCones();
      double       getEt(const DetId &id, double energy);
   double       getEta(const DetId &id);
   double       getPhi(const DetId &id);

      // ----------member data ---------------------------


   int iEtamax;
   double Et_Min;
   double Et_Max;
   double jetEtMin;
   double sumET_;

   double b;
   double npart;
   double ncoll;
   double nhard;
   double phi0;

   bool doMC_;
   InputTag jetSrc_;

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
   edm::Handle<edm::GenHIEvent> mc;
   edm::Handle<reco::Centrality> centrality;
   const CentralityBins* cbins_;

   TH1D* hNtowers;
   TH1D* hNtowers2;
   TH1D* Genpt;
   TH1D* Geneta;
   TH1D* Genet;
   TH1D* etaweight;
   TH1D* phiwet;
   TH2D* h2;
   TH1D* towereta;
   TH1D* towerpt;
   TH1D* Sum_et;
   TH1D* towerptjet;
   TH1D* towerptnojet;
   TH1D* toweret;
   TH1D* genparticlept;
   TH1D* Dndeta;
   TH1D* towerrms;
   TH1D* towerav;
   TH1D* nojetav;
   TH1D* towermeanrms;
   TH1D* nojet_mean_rms;
   TH1D* pt_nojet_rms;
   TH1D* jet_Et;

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
geo(0)
{
   //now do what ever initialization is needed
   TH1D::SetDefaultSumw2();
   Et_Min = 1000;
   Et_Max = 1500;
   jetEtMin = -50;

   doMC_ = iConfig.getUntrackedParameter<bool>("doMC",false);
   jetSrc_ = iConfig.getUntrackedParameter<edm::InputTag>("jetSrc_",edm::InputTag("icPu5patJets"));
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
   if(doMC_) analyzeMC();
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

   ev.getByLabel(edm::InputTag("heavyIon"),mc);
   ev.getByLabel(edm::InputTag("hiCentrality"),centrality);
   ev.getByLabel(edm::InputTag("towerMaker"),towers);
   ev.getByLabel(jetSrc_,jets);
  //   ev.getByLabel(edm::InputTag("iterativeConePu5CaloJets"),jets); 
   ev.getByLabel(edm::InputTag("bkg5Jets","directions"),directions);
   ev.getByLabel(edm::InputTag("bkg5Jets"),fakejets);
   ev.getByLabel(edm::InputTag("iterativeCone5HiGenJets"),genjets);

}

void MinBiasTowerAnalyzer::sumET(){
   sumET_ = 0;
   for(unsigned int i = 0 ; i < towers->size(); ++i){
      const CaloTower& tower = (*towers)[i];
      if(abs(tower.ieta())>iEtamax) continue;
      double tower_et = tower.et();
      sumET_=sumET_+tower_et;
   }
}

void MinBiasTowerAnalyzer::analyzeMC(){

b = mc->b();
npart = mc->Npart();
ncoll = mc->Ncoll();
nhard = mc->Nhard();
phi0 = mc->evtPlane();

}

void MinBiasTowerAnalyzer::analyzeTowers(){


   double cone = 0.5;
   double genJetPtMin = 20.;
   double towersize=1584;
   bool hydromatched = false;
   bool hydjetmatched = false;
   bool amptmatched = false;
   double average_pt = 0;
   double average_nojetpt = 0;
   double jetEtaMax = 1;
   double towerEtamax =11.5;
   double genpartEtamax = 0.5;

   bool interest = sumET_>Et_Min && sumET_<Et_Max;
   double hf = centrality->EtHFhitSum();
   int bin = cbins_->getBin(hf);

   // Run analysis on towers
   double dndetac=0;
   double sum = 0;
   double sum3 = 0;
   double sum4 = 0;
   double sum2 = 0;
   double rms=0;
   double rms2 = 0;
   double ortpt_rms = 0;
   double ortpt_rms2 = 0;
   double cont=0; 
   double ntower=0;
   double ptcount=0;

   for(unsigned int i = 0 ; i < towers->size(); ++i){
      const CaloTower& tower = (*towers)[i];
      if(abs(tower.ieta())>iEtamax) continue;
      
      ntower++;
      
      double eta = tower.eta();
      double pt = tower.pt();
      double et = tower.et();
      double phi = tower.phi();      
      bool recomatched = false;

      for(unsigned int j = 0 ; j < jets->size(); ++j){

	 //         const reco::CaloJet& jet = (*jets)[j];
	 const pat::Jet& jet = (*jets)[j];

	 double rawEt = jet.correctedJet("raw").et();
	 if(rawEt < jetEtMin ) continue;
	 double dr = reco::deltaR(tower.eta(),tower.phi(),jet.eta(),jet.phi());
	 if(dr < cone){
	    recomatched = true;
	 }
      }
      if(recomatched){
	 towerptjet->Fill(pt);
      }
      else {
	 towerptnojet->Fill(pt);
	 sum3=sum3+pt;
	 cont++;
	 sum4=sum4+pt*pt;
      }

      
      average_pt=sum/(towersize);
      average_nojetpt=sum3/cont;
      rms2=sqrt( (sum4/cont) - (average_nojetpt*average_nojetpt));
      pt_nojet_rms->Fill(rms2);
      towerav->Fill(average_pt);
      nojetav->Fill(average_nojetpt);
      rms=sqrt( ( sum2/towersize ) - (average_pt*average_pt) );
      towerrms->Fill(rms);
      ortpt_rms=average_pt+rms;
      ortpt_rms2=average_nojetpt+rms2;
      towermeanrms->Fill(ortpt_rms);
      nojet_mean_rms->Fill(ortpt_rms2);
      h2->Fill(ortpt_rms,dndetac);

   }

}

void MinBiasTowerAnalyzer::analyzeRandomCones(){
   bool interest = sumET_>Et_Min && sumET_<Et_Max;
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
      double phi = reco::deltaPhi(fakejet.phi(),phi0);

      int nc = 0;
      int missingTowers = 72;
      for(int ic1 = 0; ic1 < ncons-missingTowers; ++ic1){
	 int ic = -1;
	 while(find(used.begin(),used.end(), ic) != used.end() || ic < 0 || ic >= ncons){
            ic = (int)(ncons*rand->Rndm());
	 }
	 used.push_back(ic);

	 double toweta = constits[ic]->eta();
	 double towphi = reco::deltaPhi(constits[ic]->phi(),phi0);
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
MinBiasTowerAnalyzer::beginJob(const edm::EventSetup& iSetup)
{
   nt = fs->make<TNtuple>("nt","","eta1:eta2:phi1:phi2:pt1:pt2:bin:et:pu:subt:sign:njet:njet20:njet30:ncons:area:nc");
   rand = new TRandom();

   hNtowers = fs->make<TH1D>("nTowers","histogram;N_{towers};entries",480,-0.5,60.5);
   hNtowers2 = fs->make<TH1D>("nTowers2","histogram;N_{towers}; entries",240,-0.5,60.5);          
   Genpt = fs->make<TH1D>("Genpt","histogram",100,0,100);
   Geneta = fs->make<TH1D>("Geneta","histogram",100,-10,10);
   Genet = fs->make<TH1D>("Genet","histogram",100,0,100);
   etaweight = fs->make<TH1D>("eta-pt","fhisto; eta ;pt(GeV/c) ",1000,-15,15);
   phiwet = fs->make<TH1D>("et-phi","fhisto; phi ;et(GeV) ",1000,-5,5);
   h2 = fs->make<TH2D>("h2","mean_dndeta; mean tower p_{T} [GeV/c]; dNdeta",100,0,5,3000,0,3000);
   towereta = fs->make<TH1D>("towereta","histogram; eta",1000,-15,15);
    towerpt = fs->make<TH1D>("towerpt","histogram; p_{T} [GeV/c]; entries",505,-1,100);
   Sum_et = fs->make<TH1D>("Sum_et","histogram;SumTower E_{T}[GeV]; entries",300,-1,3001);
    towerptjet = fs->make<TH1D>("towerptjet","histo; p_{T} [GeV/c]; entries",505,-1,100);
    towerptnojet = fs->make<TH1D>("pt_nojet","histo; p_{T} [GeV/c]; entries",505,-1,100);
    toweret = fs->make<TH1D>("toweret","histogram; E_{T} [GeV]; entries",505,-1,100);
   genparticlept = fs->make<TH1D>("genparticlept","histogram; p_{T} [GeV/c]; entries",100,0,100);
    Dndeta = fs->make<TH1D>("Dndeta","histogram; dNdeta; entries",3000,0,3000);
    towerrms= fs->make<TH1D> ("tower_rms","histo",100,0,10);
    towerav = fs->make<TH1D>("ptaverage","histo;p_{T} GeV/c; entries",100, 0,5);
    nojetav = fs->make<TH1D>("nojet_ptaverage","histo;p_{T} GeV/c",100, 0,5);
    towermeanrms = fs->make<TH1D>("tower_mean_rms","histo; Tower mean+rms p_{T} [GeV/c]; entries",100,0,5);
    nojet_mean_rms= fs->make<TH1D>("nojet_mean_rms","histo; No-Jet Tower mean+rms p_{T} [GeV/c]; entries",100,0,5);
    pt_nojet_rms = fs->make<TH1D>("pt_nojet_rms","histo; pt_nojet_rms",100,0,5);
    jet_Et = fs->make<TH1D>("jet_Et","histogram;Jet E_{T} [GeV]; entries",600,0,150);

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
