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
// $Id: HiJetResponseAnalyzer.cc,v 1.4 2010/09/28 16:02:52 yilmaz Exp $
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

//
// class declaration
//

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

   double genPtMin_;
   double ptMin_;
   double emfMin_;
   double n90Min_;
   double n90hitMin_;

   edm::InputTag jetTag_;

   JRA jra_;
   TTree* t;

   edm::Handle<edm::GenHIEvent> mc;
   edm::Handle<reco::Centrality> cent;

   edm::Handle<reco::JetView> jets;
   edm::Handle<pat::JetCollection> patjets;

   edm::Service<TFileService> fs;

};

bool HiJetResponseAnalyzer::selectJet(int i){
   
   const reco::Jet& jet = (*jets)[i];
   
   if(usePat_){
      //      cout<<"a"<<endl;
      const pat::Jet& patjet = (*patjets)[i];
      //      cout<<"b"<<endl;
      
      if(patjet.emEnergyFraction() <= emfMin_) return false;
      //      cout<<"c"<<endl;

      if(patjet.jetID().n90Hits <= n90hitMin_) return false;
      //      cout<<"d"<<endl;

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

   ptMin_ = iConfig.getUntrackedParameter<double>("ptMin",0);
   genPtMin_ = iConfig.getUntrackedParameter<double>("genPtMin",0);
   emfMin_ = iConfig.getUntrackedParameter<double>("emfMin",0);
   n90Min_ = iConfig.getUntrackedParameter<double>("n90Min",0);
   n90hitMin_ = iConfig.getUntrackedParameter<double>("n90hitMin",0);

   filterJets_ = iConfig.getUntrackedParameter<bool>("filterJets",true);
   diJetsOnly_ = iConfig.getUntrackedParameter<bool>("diJetsOnly",true);
   matchDiJets_ = iConfig.getUntrackedParameter<bool>("usePat",true);
   usePat_ = iConfig.getUntrackedParameter<bool>("usePat",true);
   doMC_ = iConfig.getUntrackedParameter<bool>("doMC",true);
   jetTag_ = iConfig.getUntrackedParameter<edm::InputTag>("src",edm::InputTag("selectedPatJets"));

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

   jra_.nref = 0;
   for(unsigned int j = 0 ; j < jets->size(); ++j){
      
      //      const pat::Jet& jet = (*jets)[j];
      if(filterJets_ && !selectJet(j)) continue;

      const reco::Jet& jet = (*jets)[j];      

      jra_.jtpt[jra_.nref] = jet.pt();
      jra_.jteta[jra_.nref] = jet.eta();
      jra_.jtphi[jra_.nref] = jet.phi();
      jra_.jtcorpt[jra_.nref] = jet.pt();

      if(usePat_){
	 const pat::Jet& patjet = (*patjets)[j];

	 jra_.jtpt[jra_.nref] = patjet.correctedJet("raw").pt();
         jra_.jtcorpt[jra_.nref] = patjet.pt();
	 
	 if(doMC_ && patjet.genJet() != 0){	    
	    if(patjet.genJet()->pt() < genPtMin_) continue;
	    jra_.refpt[jra_.nref] = patjet.genJet()->pt();
	    jra_.refeta[jra_.nref] = patjet.genJet()->eta();
	    jra_.refphi[jra_.nref] = patjet.genJet()->phi();
	    	    	    
	 }else{
	    jra_.refpt[jra_.nref] = -99;
            jra_.refeta[jra_.nref] = -99;
            jra_.refphi[jra_.nref] = -99;
	 }
      }
      
      jra_.nref++;
      
   }

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
