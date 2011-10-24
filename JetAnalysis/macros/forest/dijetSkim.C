#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>

// Example of forest skim

void dijetSkim(const char* fname = "recor.root", const char* outname = "out.root", bool pp = 0)
{

   // Define the input file and HiForest
  HiForest *c;

  c = new HiForest(fname,"myForest",pp,0,1);
  c->SetOutputFile(outname);


  c->verbose = 1;

  cout<<"Forest ready."<<endl;

  c->hasPhotonTree = 0;
  c->hasTowerTree = 0;
  c->hasHbheTree = 0;
  c->hasIcPu5JetTree = 0;

  if(pp){
     c->sortJets(c->akPu3jetTree, c->akPu3PF, 2., 0, 1);
  }else{
    c->sortJets(c->akPu3jetTree, c->akPu3PF, 2., 40, 1);
  }
  
  cout<<"Jets sorted."<<endl;

   // Main loop
   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<endl;
      if(!c->selectEvent()) continue;
      if(pp && c->hasDiJet(c->akPu3PF,70,0,1.)) c->FillOutput(); // Leave room for smearing
      if(!pp && c->hasDiJet(c->akPu3PF)) c->FillOutput();
   }

   delete c;
}
