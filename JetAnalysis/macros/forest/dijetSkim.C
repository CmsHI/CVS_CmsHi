#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>

// Example of forest skim

void dijetSkim(bool pp = 0)
{

   // Define the input file and HiForest
  HiForest *c;

  if(pp){
    c = new HiForest("rfio:/castor/cern.ch/user/y/yjlee/HiForest/merged_pp2760_AllPhysics_NoPhoyon_Prod02.root");
    c->SetOutputFile("skim_Dijet_pp.root");
  }else{
    c = new HiForest("rfio:/castor/cern.ch/user/y/yjlee/HiForest/merged_HI2010_SD_Jet35_prod05_full.root ");
    c->SetOutputFile("skim_Dijet_PbPb.root");
  }

  if(pp){
    c->sortJets(c->akPu3jetTree, c->akPu3PF, 2., 0, 1);
  }else{
    c->sortJets(c->akPu3jetTree, c->akPu3PF, 2., 40, 1);
  }

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
