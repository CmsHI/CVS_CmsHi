#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "math.h"

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
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
  TH1F* jetPt_  = new TH1F("jetPt", "jet pt",    100,  0.,300.);
  TH1F* jetEta_ = new TH1F("jetEta","jet eta",   100, -3.,  3.);
  TH1F* jetPhi_ = new TH1F("jetPhi","jet phi",   100, -5.,  5.);

  TH2F* jetPtGenPt_ = new TH2F("jetPtGenPt", 
                                       "genJet pt vs matched IC5 jet pt",
                                        100, 0.,100.,100,0.,100);

  // open input file (can be located on castor)
  TFile* inFile = TFile::Open( "HIPAT_output_jetsOnly.root" );

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

    // fwlite::Handle to jet collection
    fwlite::Handle<std::vector<pat::Jet> > jets;
    jets.getByLabel(event, "selectedLayer1Jets");
    
    // loop jet collection and fill histograms
    for(unsigned i=0; i<jets->size(); ++i){
      jetPt_ ->Fill( (*jets)[i].pt()  );
      jetEta_->Fill( (*jets)[i].eta() );
      jetPhi_->Fill( (*jets)[i].phi() );

      // If there is a matched genJet to the jet, 
      // get the pt 
      if( (*jets)[i].genJet() != NULL )
        jetPtGenPt_->Fill( (*jets)[i].genJet()->pt(), (*jets)[i].pt() );
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
  TFile outFile( "analyzeHiPatJets.root", "recreate" );
  outFile.mkdir("analyzeHiPatJets");
  outFile.cd("analyzeHiPatJets");
  jetPt_ ->Write( );
  jetEta_->Write( );
  jetPhi_->Write( );
  jetPtGenPt_->Write( );
  outFile.Close();
  
  // ----------------------------------------------------------------------
  // Fourth Part: 
  //
  //  * never forgett to free the memory of the histograms
  // ----------------------------------------------------------------------

  // free allocated space
  delete jetPt_;
  delete jetEta_;
  delete jetPhi_;
  delete jetPtGenPt_;
  
  // that's it!
  return 0;
}
