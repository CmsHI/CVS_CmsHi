#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <stdlib.h>

vector< pair<int,double> > evtCentVz;
int comparecentvz (const void * a, const void * b);


// void sortforestCentVz(double etCut=40, char *infname = "/mnt/hadoop/cms/store/user/velicanu/forest/HiForestTrack_v3.root")
void sortforestCentVz(double etCut=40, char *infname = "/mnt/hadoop/cms/store/user/velicanu/HIHighPt/HIRun2011_hiHighPtTrack_PromptSkim_forest_v0/9902eec616cc8b0649a7a8bb69754615/HiForest_998_1_rJ1.root")
{
  //! Define the input and output file and HiForest
  HiForest *c = new HiForest(infname);
  c->SetOutputFile("sortedHiForest.root");

  
  //! loop through all the events once to construct the cent,vz pair array we'll be sorting over
  cout << "Constructing the cent:vz pair array..." << endl;
  for (int i=0;i<c->GetEntries();i++)
  {
    c->GetEntry(i);
    pair<int,double> centvz;
    centvz.first = c->evt.hiBin;
    centvz.second = c->evt.vz;
    evtCentVz.push_back(centvz);
    if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<endl;
    
  }
  
  //! Make the index array which will get sorted on first centrality
  int evtindecies[c->GetEntries()];
  for (int i=0;i<c->GetEntries();i++)
  {
    evtindecies[i] = i;
  }
  
  cout << "Sorting the cent:vz pair array..." << endl;
  //! Sort the index array first on the centrality bin, then on the vz of the entry at that index
  qsort (evtindecies, c->GetEntries(), sizeof(int), comparecentvz);
  
  //! Now fill the tree in the new order
  cout << "Filling the tree in the sorted order..." << endl;
  for (int i=0;i<c->GetEntries();i++)
  {
    c->GetEntry(evtindecies[i]);
    c->FillOutput();
    if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<endl;
  }

  delete c;
}

//! The comparison function for qsort which compares two indecies by looking up their centbin and vz in
//! evtCentVz pair array
int comparecentvz (const void * a, const void * b)
{
  if( ( evtCentVz[*(int*)a].first - evtCentVz[*(int*)b].first ) > 0)
    return 1;
  else if( ( evtCentVz[*(int*)a].first - evtCentVz[*(int*)b].first ) < 0)
    return -1;
  else if( ( evtCentVz[*(int*)a].first - evtCentVz[*(int*)b].first ) == 0)
  {
    if( (evtCentVz[*(int*)a].second - evtCentVz[*(int*)b].second) < 0 )
      return -1;
    if( (evtCentVz[*(int*)a].second - evtCentVz[*(int*)b].second) > 0 )
      return 1;
    if( (evtCentVz[*(int*)a].second - evtCentVz[*(int*)b].second) == 0 )
      return 0;
    
  }
}