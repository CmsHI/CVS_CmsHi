// -*- C++ -*-
//
// Package:    HiJetResponseAnalyzer
// Class:      HiJetResponseAnalyzer
// 
/**\class HiJetResponseAnalyzer HiJetResponseAnalyzer.cc CmsHi/HiJetResponseAnalyzer/src/HiJetResponseAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Yetkin Yilmaz
//         Created:  Thu Sep  9 10:38:59 EDT 2010
// $Id: HiJetResponseAnalyzer.cc,v 1.5 2010/09/29 15:59:10 yilmaz Exp $
//
//


// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "TTree.h"

using namespace std;

static const int MAXJETS = 500;

struct etdr{
   double et;
   double dr;
};

struct JRA{

   int nref;
   int bin;
   float b;
   float hf;
   float jtpt[MAXJETS];
   float jtcorpt[MAXJETS];
   float refpt[MAXJETS];
   float jteta[MAXJETS];
   float refeta[MAXJETS];
   float jtphi[MAXJETS];
   float refphi[MAXJETS];

   float weight;
};


struct JRAV{

  float jtpt;
  float jtcorpt;
  float refpt;
  float refcorpt;
  float jteta;
  float refeta;
  float jtphi;
  float refphi;
 
};

//
// class declaration
//
bool compareCorPt(JRAV a, JRAV b) {return a.jtcorpt > b.jtcorpt;}
bool comparePt(JRAV a, JRAV b) {return a.jtpt > b.jtpt;}

class HiJetResponseAnalyzer : public edm::EDAnalyzer {
   public:
      explicit HiJetResponseAnalyzer(const edm::ParameterSet&);
      ~HiJetResponseAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
   bool selectJet(int i);
      // ----------member data ---------------------------

  bool usePat_;
  bool doMC_;
  bool filterJets_;
  bool diJetsOnly_;
  bool matchDiJets_;
  bool matchPatGen_;
  bool matchNew_;
  bool sortJets_;
  bool correctJets_;

  double matchR_;  
   double genPtMin_;
   double ptMin_;
   double emfMin_;
   double n90Min_;
   double n90hitMin_;

   edm::InputTag jetTag_;
  edm::InputTag matchTag_;

   JRA jra_;
   TTree* t;

   edm::Handle<edm::GenHIEvent> mc;
   edm::Handle<reco::Centrality> cent;

   edm::Handle<reco::JetView> jets;
   edm::Handle<pat::JetCollection> patjets;
  edm::Handle<reco::JetView> matchedJets;

   edm::Service<TFileService> fs;

};

bool HiJetResponseAnalyzer::selectJet(int i){
   const reco::Jet& jet = (*jets)[i];
   if(usePat_){
      const pat::Jet& patjet = (*patjets)[i];
      if(patjet.emEnergyFraction() <= emfMin_) return false;
      if(patjet.jetID().n90Hits <= n90hitMin_) return false;
      if(doMC_){
	 
      }

   }

   return true;
}


//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
HiJetResponseAnalyzer::HiJetResponseAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  matchR_ = iConfig.getUntrackedParameter<double>("matchR",0.25);

   ptMin_ = iConfig.getUntrackedParameter<double>("ptMin",0);
   genPtMin_ = iConfig.getUntrackedParameter<double>("genPtMin",20);
   emfMin_ = iConfig.getUntrackedParameter<double>("emfMin",0.01);
   n90Min_ = iConfig.getUntrackedParameter<double>("n90Min",1);
   n90hitMin_ = iConfig.getUntrackedParameter<double>("n90hitMin",1);

   filterJets_ = iConfig.getUntrackedParameter<bool>("filterJets",true);
   diJetsOnly_ = iConfig.getUntrackedParameter<bool>("diJetsOnly",false);
   matchDiJets_ = iConfig.getUntrackedParameter<bool>("matchDiJets",false);
   matchPatGen_ = iConfig.getUntrackedParameter<bool>("matchPatGen",false);

   matchNew_ = iConfig.getUntrackedParameter<bool>("matchNew",false);

   usePat_ = iConfig.getUntrackedParameter<bool>("usePat",true);
   doMC_ = iConfig.getUntrackedParameter<bool>("doMC",true);

   sortJets_ = iConfig.getUntrackedParameter<bool>("sortJets",true);
   correctJets_ = iConfig.getUntrackedParameter<bool>("correctJets",false);

   jetTag_ = iConfig.getUntrackedParameter<edm::InputTag>("src",edm::InputTag("selectedPatJets"));
   matchTag_ = iConfig.getUntrackedParameter<edm::InputTag>("match",edm::InputTag("selectedPatJets"));
}


HiJetResponseAnalyzer::~HiJetResponseAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
HiJetResponseAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   iEvent.getByLabel(jetTag_,jets);
   if(usePat_)iEvent.getByLabel(jetTag_,patjets);
   if(matchNew_)iEvent.getByLabel(matchTag_,matchedJets);

   std::vector<JRAV> jraV;

   for(unsigned int j = 0 ; j < jets->size(); ++j){

     if(filterJets_ && !selectJet(j)) continue;
     const reco::Jet& jet = (*jets)[j];
     JRAV jv;
     jv.jtpt = jet.pt();
     jv.jteta = jet.eta();
     jv.jtphi = jet.phi();
     jv.jtcorpt = jet.pt();

     if(usePat_){
       const pat::Jet& patjet = (*patjets)[j];

       jv.jtpt = patjet.correctedJet("raw").pt();
       jv.jtcorpt = patjet.pt();

       if(doMC_ && matchPatGen_ && patjet.genJet() != 0){
	 if(patjet.genJet()->pt() < genPtMin_) continue;
	 jv.refpt = patjet.genJet()->pt();
	 jv.refeta = patjet.genJet()->eta();
	 jv.refphi = patjet.genJet()->phi();

       }else{
	 jv.refpt = -99;
	 jv.refeta = -99;
	 jv.refphi = -99;
       }
     }

     if(matchNew_){
       for(unsigned int m = 0 ; m < matchedJets->size(); ++m){
	 const reco::Jet& match = (*matchedJets)[m];
	 double dr = reco::deltaR(jet.eta(),jet.phi(),match.eta(),match.phi());
	 if(dr < matchR_){
	   jv.refcorpt = -99;
           jv.refpt = match.pt();
           jv.refeta = match.eta();
           jv.refphi = match.phi();
	 }
       }
     }
     jraV.push_back(jv);
   }

   if(sortJets_){
     if(usePat_ || correctJets_) std::sort(jraV.begin(),jraV.end(),compareCorPt);
     else std::sort(jraV.begin(),jraV.end(),comparePt);
   }

   for(unsigned int i = 0; i < jraV.size(); ++i){
     JRAV& jv = jraV[i];
     jra_.jtpt[jra_.nref] = jv.jtpt;
     jra_.jteta[jra_.nref] = jv.jteta;
     jra_.jtphi[jra_.nref] = jv.jtphi;
     jra_.jtcorpt[jra_.nref] = jv.jtcorpt;
     jra_.refpt[jra_.nref] = jv.refpt;
     jra_.refeta[jra_.nref] = jv.refeta;
     jra_.refphi[jra_.nref] = jv.refphi;
   }
   jra_.nref = jraV.size();

   t->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
HiJetResponseAnalyzer::beginJob()
{

   t= fs->make<TTree>("t","Jet Response Analyzer");
   t->Branch("b",&jra_.b,"b/F");
   t->Branch("hf",&jra_.hf,"hf/F");
   t->Branch("nref",&jra_.nref,"nref/I");
   t->Branch("jtpt",jra_.jtpt,"jtpt[nref]/F");
   t->Branch("jtcorpt",jra_.jtcorpt,"jtcorpt[nref]/F");
   t->Branch("refpt",jra_.refpt,"refpt[nref]/F");
   t->Branch("refcorpt",jra_.refpt,"refcorpt[nref]/F");
   t->Branch("jteta",jra_.jteta,"jteta[nref]/F");
   t->Branch("refeta",jra_.refeta,"refeta[nref]/F");
   t->Branch("jtphi",jra_.jtphi,"jtphi[nref]/F");
   t->Branch("refphi",jra_.refphi,"refphi[nref]/F");
   t->Branch("weight",&jra_.weight,"weight/F");
   t->Branch("bin",&jra_.bin,"bin/I");



}

// ------------ method called once each job just after ending the event loop  ------------
void 
HiJetResponseAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HiJetResponseAnalyzer);
