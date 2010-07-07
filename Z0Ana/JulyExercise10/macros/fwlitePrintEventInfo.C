/*
Macro to loop over theevents in a file and print different info of the event

To run this:
root -l

a1)  gSystem->Load("libFWCoreFWLite.so"); 
   AutoLibraryLoader::enable();
   gSystem->Load("libDataFormatsFWLite.so");
   gSystem->Load("libDataFormatsPatCandidates.so");



a2) if you've already set your root invironemnt to work with FWlite as described here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/WorkBookFWLite 
you do nothing


b) .x fwlitePrintEventInfo.C+
 */


#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"



#include "TROOT.h"
#include <TSystem.h>
#include <TFile.h>

#include <string>
#include <vector>
#include <iostream>
#endif
using namespace std;

void fwlitePrintEventInfo()
{
  
   TFile *file = new TFile("ZMuMuSkim_fireworks_filtering.root");

   fwlite::Event ev(file);

   for( ev.toBegin();! ev.atEnd();++ev) 
     {
       cout << "run " << ev.eventAuxiliary().run() << "\t event "<< ev.eventAuxiliary().event() << endl;
       
     }
   
   return;
}

