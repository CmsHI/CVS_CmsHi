#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "math.h"

#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

int main(int argc, char* argv[]) 
{
  // ----------------------------------------------------------------------
  // First Part: 
  //
  //  * enable the AutoLibraryLoader 
  //  * book the histograms of interest 
  //  * open the input file
  // ----------------------------------------------------------------------

  // load framework libraries
  gSystem->Load( "libFWCoreFWLite" );
  AutoLibraryLoader::enable();
  
  // book a set of histograms
  TH1F* muonPt_  = new TH1F("muonPt", "muon pt",    100,  0.,100.);
  TH1F* muonEta_ = new TH1F("muonEta","muon eta",   100, -3.,  3.);
  TH1F* muonPhi_ = new TH1F("muonPhi","muon phi",   100, -5.,  5.);  

  TH1F* muonGenPtPercentErr_ = new TH1F("muonGenPtPercentErr",
                                        "percent error in reco muon and associated MC muon pt",
                                         100, 0.,100.);

  TH1F* photonPt_  = new TH1F("photonPt", "photon pt",    100,  0.,100.);
  TH1F* photonEta_ = new TH1F("photonEta","photon eta",   100, -3.,  3.);
  TH1F* photonPhi_ = new TH1F("photonPhi","photon phi",   100, -5.,  5.);

  TH1F* photonIsolationCC3_ = new TH1F("photonIsolationCC3",
                                       "photon isolation variable CC3",
                                       100, -10., 10.);

  TH1F* jetPt_  = new TH1F("jetPt", "jet pt",    100,  0.,300.);
  TH1F* jetEta_ = new TH1F("jetEta","jet eta",   100, -3.,  3.);
  TH1F* jetPhi_ = new TH1F("jetPhi","jet phi",   100, -5.,  5.);

  TH1F* jetGenPtPercentErr_ = new TH1F("jetGenPtPercentErr", 
                                       "percent error in jet and associated genJet pt",
                                        100, 0.,100.);

  // open input file (can be located on castor)
  TFile* inFile = TFile::Open( "HIPAT_output_full.root" );

  // ----------------------------------------------------------------------
  // Second Part: 
  //
  //  * loop the events in the input file 
  //  * receive the collections of interest via fwlite::Handle
  //  * fill the histograms
  //  * after the loop close the input file
  // ----------------------------------------------------------------------

  // loop the events
  unsigned int iEvent=0;
  fwlite::Event event(inFile);
  for(event.toBegin(); !event.atEnd(); ++event, ++iEvent){
    // break loop after end of file is reached 
    // or after 1000 events have been processed
    if( iEvent==1000 ) break;
    
    // simple event counter
    if(iEvent>0 && iEvent%1==0){
      std::cout << "  processing event: " << iEvent << std::endl;
    }

    // fwlite::Handle to to muon, jet, and photon collections
    fwlite::Handle<std::vector<pat::Muon> > muons;
    muons.getByLabel(event, "selectedLayer1Muons");
    
    fwlite::Handle<std::vector<pat::Photon> > photons;
    photons.getByLabel(event, "selectedLayer1Photons");
    
    fwlite::Handle<std::vector<pat::Jet> > jets;
    jets.getByLabel(event, "selectedLayer1Jets");
    
    // loop muon collection and fill histograms
    for(unsigned i=0; i<muons->size(); ++i){

      muonPt_ ->Fill( (*muons)[i].pt()  );
      muonEta_->Fill( (*muons)[i].eta() );
      muonPhi_->Fill( (*muons)[i].phi() );

      // If there is a matched genParticle to the muon, 
      // get the pt error
      if( (*muons)[i].genLepton() != NULL )
        muonGenPtPercentErr_->Fill( fabs( (*muons)[i].pt() - 
          (*muons)[i].genLepton()->pt() ) / 
          (*muons)[i].pt() * 100. );
    }

    // loop photon collection and fill histograms
    for(unsigned i=0; i<photons->size(); ++i){
      photonPt_ ->Fill( (*photons)[i].pt()  );
      photonEta_->Fill( (*photons)[i].eta() );
      photonPhi_->Fill( (*photons)[i].phi() );
      photonIsolationCC3_->Fill ( (*photons)[i].userFloat("isoCC3") );
    }

    // loop jet collection and fill histograms
    for(unsigned i=0; i<jets->size(); ++i){
      jetPt_ ->Fill( (*jets)[i].pt()  );
      jetEta_->Fill( (*jets)[i].eta() );
      jetPhi_->Fill( (*jets)[i].phi() );

      // If there is a matched genParticle to the muon, 
      // get the pt error
      if( (*jets)[i].genJet() != NULL )
        jetGenPtPercentErr_->Fill( fabs( (*jets)[i].pt() - 
          (*jets)[i].genJet()->pt() ) / 
          (*jets)[i].pt() * 100. );
    }


  }  
  // close input file
  inFile->Close();


  // ----------------------------------------------------------------------
  // Third Part: 
  //
  //  * open the output file 
  //  * write the histograms to the output file
  //  * close the output file
  // ----------------------------------------------------------------------
  
  //open output file
  TFile outFile( "analyzeHiPatBasics.root", "recreate" );
  outFile.mkdir("analyzeHiBasicPat");
  outFile.cd("analyzeHiBasicPat");
  muonPt_ ->Write( );
  muonEta_->Write( );
  muonPhi_->Write( );
  muonGenPtPercentErr_->Write( );
  photonPt_ ->Write( );
  photonEta_->Write( );
  photonPhi_->Write( );
  photonIsolationCC3_->Write( );
  jetPt_ ->Write( );
  jetEta_->Write( );
  jetPhi_->Write( );
  jetGenPtPercentErr_->Write( );
  outFile.Close();
  
  // ----------------------------------------------------------------------
  // Fourth Part: 
  //
  //  * never forgett to free the memory of the histograms
  // ----------------------------------------------------------------------

  // free allocated space
  delete muonPt_;
  delete muonEta_;
  delete muonPhi_;
  delete muonGenPtPercentErr_;
  delete photonPt_;
  delete photonEta_;
  delete photonPhi_;
  delete photonIsolationCC3_;
  delete jetPt_;
  delete jetEta_;
  delete jetPhi_;
  delete jetGenPtPercentErr_;
  
  // that's it!
  return 0;
}
