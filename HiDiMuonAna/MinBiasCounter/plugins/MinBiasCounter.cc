// -*- C++ -*-
//
// Package:    MinBiasCounter
// Class:      MinBiasCounter
// 
/**\class MinBiasCounter MinBiasCounter.cc HiDiMuonAna/MinBiasCounter/src/MinBiasCounter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Torsten Dahms,40 4-A32,+41227671635,
//         Created:  Mon Dec  6 15:52:57 CET 2010
// $Id: MinBiasCounter.cc,v 1.2 2010/12/06 18:57:21 tdahms Exp $
//
//


// system include files
#include <memory>
#include <utility>
#include <string>
#include <TH1F.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Framework/interface/Run.h"

#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"

//
// class declaration
//

class MinBiasCounter : public edm::EDAnalyzer {
   public:
      explicit MinBiasCounter(const edm::ParameterSet&);
      ~MinBiasCounter();


   private:
      virtual void beginJob() ;
      virtual void beginRun(const edm::Run&, const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
  int nRawEvents;
  int prescale;
  int nScaledEvents;

  HLTConfigProvider hltConfig;
  bool isHLTChanged;

  edm::InputTag _triggerresults;
  std::string _histfilename;
  const edm::ParameterSet _iConfig;
  
  // centrality
  TH1F *hCent;

  CentralityProvider* centrality_;
  int centBin;
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
MinBiasCounter::MinBiasCounter(const edm::ParameterSet& iConfig) :
  _triggerresults(iConfig.getParameter<edm::InputTag>("TriggerResultsLabel")),
  _histfilename(iConfig.getParameter<std::string>("histFileName")),
  _iConfig(iConfig)
{
   //now do what ever initialization is needed
  nRawEvents=0;
  prescale=0;
  nScaledEvents=0;
  isHLTChanged=false;
  centrality_ = 0;
}


MinBiasCounter::~MinBiasCounter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
MinBiasCounter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   nRawEvents++;
   
   int runNb = iEvent.id().run();
   int eventNb = iEvent.id().event();
   int lumiSection = iEvent.luminosityBlock();

   int isPrescaleSet = hltConfig.prescaleSet(iEvent, iSetup);
   if (isPrescaleSet<0) {
     std::cerr << "Warning: Prescale for event " << eventNb << " in LS " <<  lumiSection << " of run " << runNb << " not set" << std::endl;
     std::cerr << "HLT prescaleSet = " << isPrescaleSet  << std::endl;
   }
   
   /// Combined L1T (pair.first) and HLT (pair.second) prescales per HLT path
   std::pair<int,int> prescales = hltConfig.prescaleValues(iEvent, iSetup, _iConfig.getParameter< std::string > ("triggerName"));
   // any one negative => error in retrieving this (L1T or HLT) prescale

   if (prescales.first<0 || prescales.second<0) {
     std::cerr << "Warning: Prescale for event " << eventNb << " in LS " <<  lumiSection << " of run " << runNb << " not found" << std::endl;
     std::cerr << "L1 prescale = " << prescales.first << "\t HLT prescale = " << prescales.second  << std::endl;

     return;
   }

   nScaledEvents += prescales.first * prescales.second;
   
   if(!centrality_) centrality_ = new CentralityProvider(iSetup);
   centrality_->newEvent(iEvent,iSetup); // make sure you do this first in every event
   centBin = centrality_->getBin();
   hCent->Fill(centBin);

   return;
}

void 
MinBiasCounter::beginRun(const edm::Run& run, const edm::EventSetup& iSetup)
{
  if (!hltConfig.init(run, iSetup, _triggerresults.process(), isHLTChanged))
    std::cerr << "hltConfig.init() failed" << std::endl;
}


// ------------ method called once each job just before starting event loop  ------------
void 
MinBiasCounter::beginJob()
{
  hCent = new TH1F("hCent","hCent;centrality bin;Number of Events",40,0,40);
  hCent->Sumw2();
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MinBiasCounter::endJob() {
  std::cout << "Summary:" << std::endl;
  std::cout << "HLT filter name: " << _iConfig.getParameter< std::string > ("triggerName") << std::endl;
  std::cout << "Number of recorded events: " << nRawEvents << std::endl;
  std::cout << "Number of sampled events: " << nScaledEvents << std::endl;

  TFile *outf = new TFile(_histfilename.c_str(), "RECREATE");
  hCent->Write();
  outf->Close();
}

//define this as a plug-in
DEFINE_FWK_MODULE(MinBiasCounter);
