// -*- C++ -*-
//
// Package:    TriggerPrimitives
// Class:      TriggerPrimitives
// 
/**\class TriggerPrimitives TriggerPrimitives.cc UserCode/CmsHi/HiL1Algos/src/TriggerPrimitives.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Richard Alexander Barbieri
//         Created:  Sun Mar 18 14:50:18 EDT 2012
// $Id: TriggerPrimitives.cc,v 1.8 2012/04/03 17:42:27 richard Exp $
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

// Randomly thrown in by me:
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"
#include "TH1F.h"
#include "TProfile.h"

// Randomly thrown in from Maria
/*************************************************/
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

// Includes for the Calo Scales
#include "CondFormats/DataRecord/interface/L1CaloEcalScaleRcd.h"
#include "CondFormats/L1TObjects/interface/L1CaloEcalScale.h"
#include "CondFormats/DataRecord/interface/L1CaloHcalScaleRcd.h"
#include "CondFormats/L1TObjects/interface/L1CaloHcalScale.h"
#include "FWCore/Framework/interface/EventSetup.h"

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/EcalDigi/interface/EcalTriggerPrimitiveDigi.h"
#include "DataFormats/HcalDigi/interface/HcalTriggerPrimitiveDigi.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloRegion.h"

// #include "SimDataFormats/SLHC/interface/L1CaloTower.h"
// #include "SimDataFormats/SLHC/interface/L1CaloTowerFwd.h"
// #include "SimDataFormats/SLHC/interface/L1CaloTriggerSetup.h"
// #include "SimDataFormats/SLHC/interface/L1CaloTriggerSetupRcd.h"

#include <map>
#include <deque>

//
// class declaration
//


class TriggerPrimitives : public edm::EDAnalyzer {
   public:
      explicit TriggerPrimitives(const edm::ParameterSet&);
      ~TriggerPrimitives();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------


//       const L1CaloEcalScale *mEcalScale;
//       const L1CaloHcalScale *mHcalScale;

      // Calorimeter Digis
      edm::InputTag mEcalDigiInputTag;
      edm::InputTag mHcalDigiInputTag;
      edm::InputTag mGCTDigiInputTag;
      edm::Service<TFileService> fs;

      TTree * RRTree;
      int event;
      int run;

      static const int nEcalEtaStrips = 56; //the ordering of this is very strange - -18 to -28 to -1 to -17 to 18 to 28 to 1 to 17...
      static const int nEcalPhiStrips = 72;
      int ecalDetectorMapSize;// = nEcalEtaStrips*nEcalPhiStrips;

      int *ecalCompressedEt;
      int *ecalEtaIndex;
      int *ecalPhiIndex;
      double *ecalEta;
      double *ecalPhi;
      int *ecalFineGrain;
      int *ecalTag;

  static const int nHcalEtaStrips = 64; // but +-29 to +-32 are weird, only have every fourth phi
  static const int nHcalPhiStrips = 72; // but weirdness for certain eta

  int hcalDetectorMapSize;// = nHcalEtaStrips*nHcalPhiStrips - 2*4*72*3/4;

      int *hcalCompressedEt;
      int *hcalEtaIndex;
      int *hcalPhiIndex;
      double *hcalEta;
      double *hcalPhi;
      int *hcalFineGrain;
      int *hcalTag;
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
TriggerPrimitives::TriggerPrimitives(const edm::ParameterSet& iConfig):
  mEcalDigiInputTag( iConfig.getParameter < edm::InputTag > ( "ECALDigis" ) ),
  mHcalDigiInputTag( iConfig.getParameter < edm::InputTag > ( "HCALDigis" ) ),
  mGCTDigiInputTag( iConfig.getParameter < edm::InputTag > ( "GCTDigis") )
{
   //now do what ever initialization is needed
}


TriggerPrimitives::~TriggerPrimitives()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//


// ------------ method called for each event  ------------
void
TriggerPrimitives::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  double theHBHEHFEtaBounds[] = { 0.000, 0.087, 0.087*2, 0.087*3, 0.087*4,
                                           0.087*5, 0.087*6, 0.087*7, 0.087*8, 0.087*9,
                                           0.087*10, 0.087*11, 0.087*12, 0.087*13, 0.087*14,
                                           0.087*15, 0.087*16, 0.087*17, 0.087*18, 0.087*19,
                                           1.74, 1.83, 1.93, 2.043, 2.172,
                                           2.332, 2.5, 2.65, 3.00, 3.50, 4.00, 4.50, 5.00};
 //This array has to be checked : this version dates from 2000, and the numbers do not agree with some other data I found from the web .....

  using namespace edm;
  using namespace std;

  event = iEvent.id().event();
  run = iEvent.id().run();
  ecalDetectorMapSize = 0;

  // Loop through the TPGs
  edm::Handle < EcalTrigPrimDigiCollection > lEcalDigiHandle;
  iEvent.getByLabel( mEcalDigiInputTag, lEcalDigiHandle );

  int i = 0;

  for ( EcalTrigPrimDigiCollection::const_iterator lEcalTPItr = lEcalDigiHandle->begin(  ); lEcalTPItr != lEcalDigiHandle->end(  ); ++lEcalTPItr )
    {      
      //cout << lEcalTPItr->compressedEt(  ) << " " << lEcalTPItr->id(  ).ieta(  ) << " " << lEcalTPItr->id(  ).iphi(  ) << " " << lEcalTPItr->fineGrain(  )  << endl;

      ecalCompressedEt[i] = lEcalTPItr->compressedEt(  );
      ecalEtaIndex[i] = lEcalTPItr->id(  ).ieta(  );
      ecalPhiIndex[i] = lEcalTPItr->id(  ).iphi(  );
      ecalFineGrain[i] = lEcalTPItr->fineGrain(  );
      int signEta;
      if (ecalEtaIndex[i]>0) {signEta=1;} else {signEta=-1;}
      if (ecalEtaIndex[i]*signEta<=17) {ecalTag[i]=1;} else {ecalTag[i]=2;}

      ecalEta[i]=signEta * (theHBHEHFEtaBounds[signEta * ecalEtaIndex[i]-1] + theHBHEHFEtaBounds[signEta * ecalEtaIndex[i]])/2.;
      ecalPhi[i]=0.0872664626*(ecalPhiIndex[i]-1);
      //std::cout<<"ecal :"<<ecalEtaIndex[i]<<" "<<ecalPhiIndex[i]<<" "<<ecalEta[i]<<" "<<ecalPhi[i]<<" "<<ecalTag[i]<<std::endl;
      i++;
    }
  ecalDetectorMapSize = i;

  i = 0;

  hcalDetectorMapSize = 0;

  edm::Handle < HcalTrigPrimDigiCollection > lHcalDigiHandle;
  iEvent.getByLabel( mHcalDigiInputTag, lHcalDigiHandle );

  for ( HcalTrigPrimDigiCollection::const_iterator lHcalTPItr = lHcalDigiHandle->begin(  ); lHcalTPItr != lHcalDigiHandle->end(  ); ++lHcalTPItr )
    {
      //cout << lHcalTPItr->SOI_compressedEt(  ) << " " << lHcalTPItr->id(  ).ieta(  ) << " " << lHcalTPItr->id(  ).iphi(  ) << " " << lHcalTPItr->SOI_fineGrain(  )  << endl;

      hcalCompressedEt[i] = lHcalTPItr->SOI_compressedEt(  );
      hcalEtaIndex[i] = lHcalTPItr->id(  ).ieta(  );
      hcalPhiIndex[i] = lHcalTPItr->id(  ).iphi(  );
      hcalFineGrain[i] = lHcalTPItr->SOI_fineGrain(  );
      int signEta;
      if (hcalEtaIndex[i]>0) {signEta=1;} else {signEta=-1;}
      if (hcalEtaIndex[i]*signEta<=28)  {
         if (hcalEtaIndex[i]*signEta<=17) { hcalTag[i]=1;} else {hcalTag[i]=2;}
      }
      else { 
        hcalTag[i]=3;    }

      hcalEta[i]=signEta * (theHBHEHFEtaBounds[signEta * hcalEtaIndex[i]-1] + theHBHEHFEtaBounds[signEta * hcalEtaIndex[i]])/2.;
      hcalPhi[i]=0.0872664626*(hcalPhiIndex[i]-1);
      //std::cout<<"hcal :"<<hcalEtaIndex[i]<<" "<<hcalPhiIndex[i]<<" "<<hcalEta[i]<<" "<<hcalPhi[i]<<" "<<hcalTag[i]<<"    "<<lHcalTPItr->SOI_compressedEt()<<std::endl;
      i++;
    }
  hcalDetectorMapSize = i;

  RRTree->Fill();

  edm::Handle < vector<L1CaloRegion>  > lGCTDigiHandle;
  iEvent.getByLabel ( mGCTDigiInputTag, lGCTDigiHandle );
   for ( vector<L1CaloRegion>::const_iterator lGCTRegionPItr = lGCTDigiHandle->begin(  ); lGCTRegionPItr != lGCTDigiHandle->end(  ); ++lGCTRegionPItr ){
     cout <<  lGCTRegionPItr->rctEta() << " " << lGCTRegionPItr->rctPhi() << " " << lGCTRegionPItr->gctEta() << " " << lGCTRegionPItr->gctPhi() << " " << lGCTRegionPItr->isHf() << " " << lGCTRegionPItr->et() << endl;
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
TriggerPrimitives::beginJob()
{

  RRTree = fs->make<TTree>("RRTree","Tree containing ecal and hcal info");
  RRTree->Branch("event",&event,"event/I");
  RRTree->Branch("run", &run, "run/I");

  //detectorMapSize = 0;
  int ecalSize = nEcalEtaStrips*nEcalPhiStrips;

  ecalCompressedEt = new int[ecalSize];
  ecalEtaIndex = new int[ecalSize];
  ecalPhiIndex = new int[ecalSize];
  ecalEta = new double[ecalSize];
  ecalPhi = new double[ecalSize];
  ecalFineGrain = new int[ecalSize];
  ecalTag = new int[ecalSize];

  RRTree->Branch("ecalDetectorMapSize",&ecalDetectorMapSize,"ecalDetectorMapSize/I");
  RRTree->Branch("ecalCompressedEt",ecalCompressedEt,"ecalCompressedEt[ecalDetectorMapSize]/I");
  RRTree->Branch("ecalEtaIndex",ecalEtaIndex,"ecalEtaIndex[ecalDetectorMapSize]/I");
  RRTree->Branch("ecalPhiIndex",ecalPhiIndex,"ecalPhiIndex[ecalDetectorMapSize]/I");
  RRTree->Branch("ecalEta",ecalEta,"ecalEta[ecalDetectorMapSize]/D");
  RRTree->Branch("ecalPhi",ecalPhi,"ecalPhi[ecalDetectorMapSize]/D");
  RRTree->Branch("ecalFineGrain",ecalFineGrain,"ecalFineGrain[ecalDetectorMapSize]/I");
  RRTree->Branch("ecalTag",ecalTag,"ecalTag[ecalDetectorMapSize]/I");

  int hcalSize = nHcalEtaStrips*nHcalPhiStrips;

  hcalCompressedEt = new int[hcalSize];
  hcalEtaIndex = new int[hcalSize];
  hcalPhiIndex = new int[hcalSize];
  hcalEta = new double[hcalSize];
  hcalPhi = new double[hcalSize];
  hcalFineGrain = new int[hcalSize];
  hcalTag = new int[hcalSize];

  RRTree->Branch("hcalDetectorMapSize",&hcalDetectorMapSize,"hcalDetectorMapSize/I");
  RRTree->Branch("hcalCompressedEt",hcalCompressedEt,"hcalCompressedEt[hcalDetectorMapSize]/I");
  RRTree->Branch("hcalEtaIndex",hcalEtaIndex,"hcalEtaIndex[hcalDetectorMapSize]/I");
  RRTree->Branch("hcalPhiIndex",hcalPhiIndex,"hcalPhiIndex[hcalDetectorMapSize]/I");
  RRTree->Branch("hcalEta",hcalEta,"hcalEta[hcalDetectorMapSize]/D");
  RRTree->Branch("hcalPhi",hcalPhi,"hcalPhi[hcalDetectorMapSize]/D");
  RRTree->Branch("hcalFineGrain",hcalFineGrain,"hcalFineGrain[hcalDetectorMapSize]/I");
  RRTree->Branch("hcalTag",hcalTag,"hcalTag[hcalDetectorMapSize]/I");

  
}

// ------------ method called once each job just after ending the event loop  ------------
void TriggerPrimitives::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void TriggerPrimitives::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
TriggerPrimitives::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
TriggerPrimitives::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
TriggerPrimitives::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TriggerPrimitives::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerPrimitives);
