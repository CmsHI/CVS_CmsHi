#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>

// Example of forest skim

void dijetSkim(bool pp = 1)
{

   // Define the input file and HiForest
  HiForest *c;

  if(pp){
    c = new HiForest("/d100/yjlee/hiForest/merged_pp2760_AllPhysics_NoPhoyon_Prod02.root","ppForest",1);
    c->SetOutputFile("skim_Dijet_pp2.root");
  }else{
    c = new HiForest("/d100/yjlee/hiForest/merged_HI2010_SD_Jet35_prod05_full.root");
    c->SetOutputFile("skim_Dijet_PbPb.root");
  }

  c->verbose = 1;

  cout<<"Forest ready."<<endl;

  c->hasPhotonTree = 0;
  c->hasTowerTree = 0;
  c->hasHbheTree = 0;
  c->hasIcPu5JetTree = 0;

  if(pp){
    c->sortJets(c->akPu3jetTree, c->akPu3PF, 2., 20, 1);
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
      if(c->hasDiJet(c->akPu3PF)) c->FillOutput();
   }

   delete c;
}
