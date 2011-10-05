#include <TChain.h>
#include <TFile.h>
#include <iostream>

void mergeForest(){

   const char* fname = "merged_*.root";

   string dir[10] = {
      "hltanalysis",
      "skimanalysis",
      "icPu5JetAnalyzer",
      "akPu3PFJetAnalyzer",
//      "ak3PFJetAnalyzer",
//      "ak5CaloJetAnalyzer",
      "anaTrack",
      "NTuples",
      "",
      ""
   };

   string trees[10] = {
      "HltTree",
      "HltTree",
      "t",
      "t",
//      "t",
//      "t",
      "trackTree",
      "Analysis",
      "",
      ""
   };

   TChain* ch[10];

   int N = 6;

   for(int i = 0; i < N; ++i){
      ch[i] = new TChain(string(dir[i]+"/"+trees[i]).data());
      ch[i]->Add(fname);      
   }
   

   TFile* file = new TFile("newfile.root", "RECREATE");

   for(int i = 0; i < N; ++i){
      file->cd();
      cout <<string(dir[i]+"/"+trees[i]).data()<<endl;
      file->mkdir(dir[i].data())->cd();
      ch[i]->Merge(file,0,"keep");
   }
   cout <<"Good"<<endl;
   file->Write();
   file->Close();

}

