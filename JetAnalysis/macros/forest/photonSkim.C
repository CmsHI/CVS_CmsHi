#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>

// Example of forest skim

void photonSkim(double etCut=40, char *infname = "/d100/yjlee/hiForest/PromptReco2011/HIHighPt/skim_Photon35/merged_HIData2011_HIHighPt_highPtExercise_photonSkim35GeVEB.root")
{
   // Define the input file and HiForest
   HiForest *c = new HiForest(infname);
   c->SetOutputFile("skim_Photon.root");

   // Main loop
   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<endl;

      int leadingPhoton=-1;
      int leadingJet=-1;

      // Loop over photons to look for leading photon candidate in the event
      for (int j=0;j<c->photon.nPhotons;j++) {
         if (c->photon.pt[j]<etCut) break;          // photon pT cut, assuming that et is sorted
         if (fabs(c->photon.eta[j])>1.44) continue; // |eta|<1.44
         if (c->isSpike(j)) continue;               // spike removal
         //if (!c->isGoodPhoton(j)) continue;         // hiGoodPhoton cut
         leadingPhoton=j;  
         break;  
      }	 
      if (leadingPhoton!=-1){
         c->FillOutput(); // Write output forest
      }
   }

   delete c;
}
