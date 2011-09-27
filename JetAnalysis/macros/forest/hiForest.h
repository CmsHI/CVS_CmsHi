#include <iostream>

#include "SetupPhotonTree.h"
#include "SetupJetTree.h"
#include "SetupHltTree.h"
#include "SetupTrackTree.h"

#include <TTree.h>
#include <TFile.h>
#include <TString.h>

// Main class which can be used to read the hiForest trees
//
//

class HiForest
{

  public: 
  HiForest(char *name);
  ~HiForest(){};

  // Utility functions
  void GetEntry(int i);
  int  GetEntries();
  void printStatus();


  // TFile
  TFile *inf; 

  // Trees
  TTree *photonTree;
  TTree *icPu5jetTree;
  TTree *akPu3jetTree;
  TTree *hltTree;
  TTree *trackTree;
  TTree *skimTree;
  TTree *tree;

  // Branches
  Hlts hlt;
  Hlts skim;
  Jets icPu5;
  Jets akPu3PF;
  Photons photon;
  Tracks track;

  private:
  
  // Boolings
  bool hasPhotonTree;
  bool hasIcPu5JetTree;
  bool hasAkPu3JetTree;
  bool hasHltTree;
  bool hasTrackTree;
  bool hasSkimTree;

                   
};

HiForest::HiForest(char *infName)
{
  tree = 0;

  inf = new TFile(infName);
  hltTree = (TTree*) inf->Get("hltanalysis/HltTree");
  skimTree = (TTree*) inf->Get("skimanalysis/HltTree");
  photonTree = (TTree*) inf->Get("NTuples/Analysis");
  icPu5jetTree = (TTree*) inf->Get("icPu5JetAnalyzer/t");
  akPu3jetTree = (TTree*) inf->Get("akPu3PFJetAnalyzer/t");
  trackTree = (TTree*) inf->Get("anaTrack/trackTree");

  hasPhotonTree    = (photonTree   != 0);
  hasIcPu5JetTree  = (icPu5jetTree != 0);
  hasAkPu3JetTree  = (akPu3jetTree != 0);
  hasTrackTree     = (trackTree    != 0);
  hasHltTree       = (hltTree      != 0);
  hasSkimTree       = (skimTree      != 0);
  

  if (hasPhotonTree) {
    photonTree->SetName("photon");
    if (tree == 0) tree = photonTree;
    setupPhotonTree(photonTree,photon);
  }

  if (hasHltTree) {
    hltTree->SetName("hlt");
    if (tree == 0) tree = hltTree; else tree->AddFriend(hltTree);
    setupHltTree(hltTree,hlt);
  }

  if (hasIcPu5JetTree) {
    icPu5jetTree->SetName("icPu5");
    if (tree == 0) tree = icPu5jetTree; else tree->AddFriend(icPu5jetTree);
    setupJetTree(icPu5jetTree,icPu5);
  }

  if (hasAkPu3JetTree) {
    akPu3jetTree->SetName("akPu3PF");
    if (tree == 0) tree = akPu3jetTree; else tree->AddFriend(akPu3jetTree);
    setupJetTree(akPu3jetTree,akPu3PF);
  }

  if (hasTrackTree) {
    trackTree->SetName("track");
    if (tree == 0) tree = trackTree; else tree->AddFriend(trackTree);
    setupTrackTree(trackTree,track);
  }

  if (hasSkimTree) {
    skimTree->SetName("skim");
    if (tree == 0) tree = skimTree; else tree->AddFriend(skimTree);
    setupHltTree(skimTree,skim);
  }
  
  tree->SetMarkerStyle(20);
  printStatus();
}

void HiForest::GetEntry(int i)
{
  // get the entry of the available trees
  if (hasPhotonTree)   photonTree   ->GetEntry(i);
  if (hasHltTree)      hltTree      ->GetEntry(i);
  if (hasSkimTree)     skimTree      ->GetEntry(i);
  if (hasIcPu5JetTree) icPu5jetTree ->GetEntry(i);
  if (hasAkPu3JetTree) akPu3jetTree ->GetEntry(i);
  if (hasTrackTree)    trackTree    ->GetEntry(i);
}

int HiForest::GetEntries()
{
  // get the entries of the available trees
  
  return tree->GetEntries();
}

void HiForest::printStatus()
{
  if (hasHltTree)      cout <<"Hlt tree loaded."<<endl;
  if (hasSkimTree)      cout <<"Skim tree loaded."<<endl;
  if (hasPhotonTree)   cout <<"Photon tree loaded."<<endl;
  if (hasTrackTree)    cout <<"Track tree loaded."<<endl;
  if (hasAkPu3JetTree) cout <<"AkPu3PFJet tree loaded."<<endl;
  if (hasIcPu5JetTree) cout <<"IcPu5Jet tree loaded."<<endl;
}
