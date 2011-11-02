// -*- C++ -*-
//
// Package:    HiEvtAnalyzer
// Class:      HiEvtAnalyzer
// 
/**\class HiEvtAnalyzer HiEvtAnalyzer.cc CmsHi/HiHLTAlgos/src/HiEvtAnalyzer.cc
 
 Description: [one line class summary]
 
 Implementation:
 [Notes on implementation]
 */
//
// Original Author:  Teng Ma
//         Created:  Wed Nov  2 06:51:29 EDT 2011
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

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"

#include "TTree.h"

//
// class declaration
//

class HiEvtAnalyzer : public edm::EDAnalyzer {
public:
   explicit HiEvtAnalyzer(const edm::ParameterSet&);
   ~HiEvtAnalyzer();
   
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
   edm::InputTag CentralityTag_;
   edm::InputTag CentralityBinTag_;
   edm::InputTag EvtPlaneTag_;
   edm::InputTag HiMCTag_;

   bool doEvtPlane_;
   bool doMC_;
   
   edm::Service<TFileService> fs_;
   
   TTree * thi_;
   
   float *hiEvtPlane;
   int nEvtPlanes;
   int HltEvtCnt;
   int hiBin;
   int hiNpix, hiNpixelTracks, hiNtracks, hiNtracksPtCut, hiNtracksEtaCut, hiNtracksEtaPtCut;
   float hiHF, hiHFplus, hiHFminus, hiHFhit, hiHFhitPlus, hiHFhitMinus, hiEB, hiET, hiEE, hiEEplus, hiEEminus, hiZDC, hiZDCplus, hiZDCminus;
   
   float fNpart;
   float fNcoll;
   float fNhard;
   float fPhi0;
   float fb;
   
   int fNcharged;
   int fNchargedMR;
   float fMeanPt;
   float fMeanPtMR;
   float fEtMR;
   int fNchargedPtCut;
   int fNchargedPtCutMR;
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
HiEvtAnalyzer::HiEvtAnalyzer(const edm::ParameterSet& iConfig) :
CentralityTag_(iConfig.getParameter<edm::InputTag> ("Centrality")),
CentralityBinTag_(iConfig.getParameter<edm::InputTag> ("CentralityBin")),
EvtPlaneTag_(iConfig.getParameter<edm::InputTag> ("EvtPlane")),
HiMCTag_(iConfig.getParameter<edm::InputTag> ("HiMC")),
doEvtPlane_(iConfig.getParameter<bool> ("doEvtPlane")),
doMC_(iConfig.getParameter<bool> ("doMC"))
{
   //now do what ever initialization is needed
   
}


HiEvtAnalyzer::~HiEvtAnalyzer()
{
   
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
   
}


//
// member functions
//

// ------------ method called for each event  ------------
void
HiEvtAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   //ESHandle<SetupData> pSetup;
   //iSetup.get<SetupRecord>().get(pSetup);

   edm::Handle<edm::GenHIEvent> mchievt;
   edm::Handle<reco::Centrality> centrality;
   edm::Handle<int> binHandle;
   edm::Handle<reco::EvtPlaneCollection> evtPlanes;
   
   if(doMC_){
      edm::Handle<edm::GenHIEvent> mchievt;
      iEvent.getByLabel(edm::InputTag(HiMCTag_),mchievt);
      fb = mchievt->b();
      fNpart = mchievt->Npart();
      fNcoll = mchievt->Ncoll();
      fNhard = mchievt->Nhard();
      fPhi0 = mchievt->evtPlane();
      fNcharged = mchievt->Ncharged();
      fNchargedMR = mchievt->NchargedMR();
      fMeanPt = mchievt->MeanPt();
      fMeanPtMR = mchievt->MeanPtMR();
      fEtMR = mchievt->EtMR();
      fNchargedPtCut = mchievt->NchargedPtCut();
      fNchargedPtCutMR = mchievt->NchargedPtCutMR();
   }
   
   iEvent.getByLabel(CentralityBinTag_,binHandle);
   hiBin = *binHandle;
   
   iEvent.getByLabel(CentralityTag_,centrality);
   hiNpix = centrality->multiplicityPixel();
   hiNpixelTracks = centrality->NpixelTracks();
   hiNtracks = centrality->Ntracks();
   hiNtracksPtCut = centrality->NtracksPtCut();
   hiNtracksEtaCut = centrality->NtracksEtaCut();
   hiNtracksEtaPtCut = centrality->NtracksEtaPtCut();
   
   hiHF = centrality->EtHFtowerSum();
   hiHFplus = centrality->EtHFtowerSumPlus();
   hiHFminus = centrality->EtHFtowerSumMinus();
   hiHFhit = centrality->EtHFhitSum();
   hiHFhitPlus = centrality->EtHFhitSumPlus();
   hiHFhitMinus = centrality->EtHFhitSumMinus();
   
   hiZDC = centrality->zdcSum();
   hiZDCplus = centrality->zdcSumPlus();
   hiZDCminus = centrality->zdcSumMinus();
   
   hiEEplus = centrality->EtEESumPlus();
   hiEEminus = centrality->EtEESumMinus();
   hiEE = centrality->EtEESum();
   hiEB = centrality->EtEBSum();
   hiET = centrality->EtMidRapiditySum();
   
   if (doEvtPlane_) {
      iEvent.getByLabel(EvtPlaneTag_,evtPlanes);
      if(evtPlanes.isValid()){
         nEvtPlanes = evtPlanes->size();
         for(unsigned int i = 0; i < evtPlanes->size(); ++i){
            hiEvtPlane[i] = (*evtPlanes)[i].angle();     
         }
      }
   }
   
   // Done w/ all vars
   thi_->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
HiEvtAnalyzer::beginJob()
{
   thi_ = fs_->make<TTree>("HiTree", "");
   
   HltEvtCnt = 0;
   const int kMaxEvtPlanes = 1000;
   
   fNpart = -1;
   fNcoll = -1;
   fNhard = -1;
   fPhi0 = -1;
   fb = -1;
   fNcharged = -1;
   fNchargedMR = -1;
   fMeanPt = -1;
   fMeanPtMR = -1;
   
   fEtMR = -1;
   fNchargedPtCut = -1;
   fNchargedPtCutMR = -1;
   
   nEvtPlanes = 0;
   hiBin = -1;
   hiEvtPlane = new float[kMaxEvtPlanes];
   
   thi_->Branch("Npart",&fNpart,"Npart/F");
   thi_->Branch("Ncoll",&fNcoll,"Ncoll/F");
   thi_->Branch("Nhard",&fNhard,"Nhard/F");
   thi_->Branch("phi0",&fPhi0,"NPhi0/F");
   thi_->Branch("b",&fb,"b/F");
   thi_->Branch("Ncharged",&fNcharged,"Ncharged/I");
   thi_->Branch("NchargedMR",&fNchargedMR,"NchargedMR/I");
   thi_->Branch("MeanPt",&fMeanPt,"MeanPt/F");
   thi_->Branch("MeanPtMR",&fMeanPtMR,"MeanPtMR/F");
   thi_->Branch("EtMR",&fEtMR,"EtMR/F");
   thi_->Branch("NchargedPtCut",&fNchargedPtCut,"NchargedPtCut/I");
   thi_->Branch("NchargedPtCutMR",&fNchargedPtCutMR,"NchargedPtCutMR/I");
   thi_->Branch("hiBin",&hiBin,"hiBin/I");
   thi_->Branch("hiHF",&hiHF,"hiHF/F");
   thi_->Branch("hiHFplus",&hiHFplus,"hiHFplus/F");
   thi_->Branch("hiHFminus",&hiHFminus,"hiHFminus/F");
   thi_->Branch("hiZDC",&hiZDC,"hiZDC/F");
   thi_->Branch("hiZDCplus",&hiZDCplus,"hiZDCplus/F");
   thi_->Branch("hiZDCminus",&hiZDCminus,"hiZDCminus/F");
   
   thi_->Branch("hiHFhit",&hiHFhit,"hiHFhit/F");
   thi_->Branch("hiHFhitPlus",&hiHFhitPlus,"hiHFhitPlus/F");
   thi_->Branch("hiHFhitMinus",&hiHFhitMinus,"hiHFhitMinus/F");
   
   thi_->Branch("hiET",&hiET,"hiET/F");
   thi_->Branch("hiEE",&hiEE,"hiEE/F");
   thi_->Branch("hiEB",&hiEB,"hiEB/F");
   thi_->Branch("hiEEplus",&hiEEplus,"hiEEplus/F");
   thi_->Branch("hiEEminus",&hiEEminus,"hiEEminus/F");
   thi_->Branch("hiNpix",&hiNpix,"hiNpix/I");
   thi_->Branch("hiNpixelTracks",&hiNpixelTracks,"hiNpixelTracks/I");
   thi_->Branch("hiNtracks",&hiNtracks,"hiNtracks/I");
   thi_->Branch("hiNevtPlane",&nEvtPlanes,"hiNevtPlane/I");
   thi_->Branch("hiEvtPlanes",hiEvtPlane,"hiEvtPlanes[hiNevtPlane]/F");
   thi_->Branch("hiNtracksPtCut",&hiNtracksPtCut,"hiNtracksPtCut/I");
   thi_->Branch("hiNtracksEtaCut",&hiNtracksEtaCut,"hiNtracksEtaCut/I");
   thi_->Branch("hiNtracksEtaPtCut",&hiNtracksEtaPtCut,"hiNtracksEtaPtCut/I");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HiEvtAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
HiEvtAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
HiEvtAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
HiEvtAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
HiEvtAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HiEvtAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
   //The following says we do not know what parameters are allowed so do no validation
   // Please change this to state exactly what you do use, even if it is no parameters
   edm::ParameterSetDescription desc;
   desc.setUnknown();
   descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HiEvtAnalyzer);
