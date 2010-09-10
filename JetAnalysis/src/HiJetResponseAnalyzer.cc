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
// $Id: HiJetResponseAnalyzer.cc,v 1.1 2010/09/09 15:05:01 yilmaz Exp $
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

      // ----------member data ---------------------------

   bool usePat_;
   bool doMC_;

   double genJetPtMin_;


   edm::InputTag jetTag_;

   JRA jra_;
   TTree* t;

   edm::Handle<edm::GenHIEvent> mc;
   edm::Handle<reco::Centrality> cent;

   edm::Handle<reco::JetView> jets;
   //   edm::Handle<pat::JetCollection> jets;


   edm::Service<TFileService> fs;

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
HiJetResponseAnalyzer::HiJetResponseAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   genJetPtMin_ = 0;

   usePat_ = false;
   doMC_ = false;

   jetTag_ = edm::InputTag("selectedPatJets");

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
   cout<<"a"<<endl;

   jra_.nref = 0;
   for(unsigned int j = 0 ; j < jets->size(); ++j){
      cout<<"b"<<endl;
      
      //      const pat::Jet& jet = (*jets)[j];
      const reco::Jet jet = (*jets)[j];      
      jra_.jtpt[jra_.nref] = jet.pt();
      jra_.jteta[jra_.nref] = jet.eta();
      jra_.jtphi[jra_.nref] = jet.phi();
      cout<<"c"<<endl;
      
      if(usePat_){
	 const pat::Jet& patjet = (*jets)[j];
	 
	 if(doMC_ && patjet.genJet() != 0){	    
	    //	    if(jet.genJet()->pt() < genJetPtMin_) continue;
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
