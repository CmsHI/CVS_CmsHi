#define TriggerPrimitivesTree_cxx
#include "TriggerPrimitivesTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void TriggerPrimitivesTree::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L TriggerPrimitivesTree.C
  //      Root > TriggerPrimitivesTree t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    // ientry = fjet->LoadTree(jentry);
    // ientry = fhlt->LoadTree(jentry);
    // ientry = fhiinfo->LoadTree(jentry);
    // ientry = fmu->LoadTree(jentry);
    if (ientry < 0) break;
    
    //! here it loads the same event from all the trees
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    fjet->GetEntry(jentry);
    fhlt->GetEntry(jentry);
    fhiinfo->GetEntry(jentry);
    fmu->GetEntry(jentry);
    // if (Cut(ientry) < 0) continue;
    
    cout<<"ecalDetectorMapSize from trigger primitives tree: "<<ecalDetectorMapSize<<endl;
    cout<<"nref from jet tree: "<<fjet->nref<<endl;
    cout<<"L1EtTot from hlt tree: "<<fhlt->L1EtTot<<endl;
    cout<<"centrality bin from hieventanalyzer: "<<fhiinfo->hiBin<<endl;
    cout<<"Glb_nptl from muon tree: "<<fmu->Glb_nptl<<endl;
    
    if(jentry>10) break;
  }
}
