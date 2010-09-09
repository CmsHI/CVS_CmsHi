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
// $Id$
//
//


// system include files
#include <memory>

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

   double genJetPtMin_;

   JRA jra_;
   TTree* t;

   edm::Handle<edm::GenHIEvent> mc;
   edm::Handle<reco::Centrality> cent;

   edm::Handle<reco::JetView> jets;




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


   for(unsigned int j = 0 ; j < jets->size(); ++j){

      const pat::Jet jet = (pat::Jet)((*jets)[j]);
      
      if(jet.genJet() != 0){

	 if(jet.genJet()->pt() < genJetPtMin_) continue;
	 jra_.refpt[jra_.nref] = jet.genJet()->pt();
	 jra_.refeta[jra_.nref] = jet.genJet()->eta();
	 jra_.refphi[jra_.nref] = jet.genJet()->phi();
	   
	 jra_.jtpt[jra_.nref] = jet.pt();
	 jra_.jteta[jra_.nref] = jet.eta();
	 jra_.jtphi[jra_.nref] = jet.phi();
	  
	 jra_.nref++;
	   
      }
   }

   t->Fill();



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
HiJetResponseAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HiJetResponseAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HiJetResponseAnalyzer);
