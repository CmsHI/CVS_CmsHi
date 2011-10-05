#include <iostream>

#include "SetupPhotonTree.h"
#include "SetupJetTree.h"
#include "SetupHltTree.h"
#include "SetupSkimTree.h"
#include "SetupTrackTree.h"

#include <TTree.h>
#include <TFile.h>
#include <TString.h>

// ==========================================================
// Main class which can be used to read the hiForest trees
//
// Auther: Yen-Jie Lee
//
// ==========================================================

class HiForest
{

  public: 
  HiForest(char *name);
  ~HiForest(){};

  // Utility functions
  void GetEntry(int i);
  int  GetEntries();  				// Get the number of entries 
  void checkTree(TTree *t,char *title);		// Check the status of a tree
  void printStatus();				// Print the status of the hiForest

  // Event filtering utility functions

  // Photon utility functions
  bool isSpike(int i);                          // return true if it is considered as a spike candidate
  bool isGoodPhoton(int i);                     // return true if it is considered as a hiGoodPhoton candidate

  // Jet utility functions

  // Track utility functions


  // TFile
  TFile *inf; 					// Input file 

  // Trees
  TTree *photonTree;				// Photon Tree, see branches in SetupPhotonTree.h
  TTree *icPu5jetTree;				// Jet Tree with icPu5 algorithm, see branches in SetupJetTree.h
  TTree *akPu3jetTree;				// Jet Tree with akPu3PF algorithm, see branches in SetupJetTree.h
  TTree *hltTree;				// OpenHLT Tree, see branches in SetupHltTree.h
  TTree *trackTree;				// Track Tree, see branches in SetupTrackTree.h
  TTree *skimTree;				// Skim Tree, contains event selection info, see branches in SetupSkimTree.h
  TTree *tree;					// Pointer to the available tree, all trees in the forest are friended to each other

  // Branches
  Hlts hlt;
  Skims skim;
  Jets icPu5;
  Jets akPu3PF;
  Photons photon;
  Tracks track;

  
  // Boolings
  bool hasPhotonTree;
  bool hasIcPu5JetTree;
  bool hasAkPu3JetTree;
  bool hasHltTree;
  bool hasTrackTree;
  bool hasSkimTree;

  private:                   
};

HiForest::HiForest(char *infName)
{
  tree = 0;

  // Input file
  inf = new TFile(infName);

  // Load trees. Hard coded for the moment
  hltTree      = (TTree*) inf->Get("hltanalysis/HltTree");
  skimTree     = (TTree*) inf->Get("skimanalysis/HltTree");
  photonTree   = (TTree*) inf->Get("NTuples/Analysis");
  icPu5jetTree = (TTree*) inf->Get("icPu5JetAnalyzer/t");
  akPu3jetTree = (TTree*) inf->Get("akPu3PFJetAnalyzer/t");
  trackTree    = (TTree*) inf->Get("anaTrack/trackTree");

  // Check the validity of the trees.
  hasPhotonTree    = (photonTree   != 0);
  hasIcPu5JetTree  = (icPu5jetTree != 0);
  hasAkPu3JetTree  = (akPu3jetTree != 0);
  hasTrackTree     = (trackTree    != 0);
  hasHltTree       = (hltTree      != 0);
  hasSkimTree      = (skimTree     != 0);
  
  // Setup branches. See also Setup*.h
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
    setupSkimTree(skimTree,skim);
  }
  
  tree->SetMarkerStyle(20);

  // Print the status of thre forest
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

void HiForest::checkTree(TTree *t,char *title)
{
   int entries = t->GetEntries();
   cout <<title<<": "<<entries<<" entries loaded.";
   if (entries != tree->GetEntries()) {
      // Entries from different trees are inconsistent!!
      cout <<" Inconsistent number of entries!!"<<endl;
   } else {
      cout <<endl;
   }

}

void HiForest::printStatus()
{
  if (hasHltTree) checkTree(hltTree,"HltTree");
  if (hasSkimTree) checkTree(skimTree,"SkimTree");
  if (hasIcPu5JetTree) checkTree(icPu5jetTree,"IcPu5jetTree");
  if (hasAkPu3JetTree) checkTree(akPu3jetTree,"AkPu3jetTree");
  if (hasTrackTree) checkTree(trackTree,"TrackTree");
  if (hasPhotonTree) checkTree(trackTree,"PhotonTree");

}

// ====================== Photon Utilities ========================
bool HiForest::isSpike(int j)
{
  if (photon.isEB[j]) {
    double swiss = 1-(photon.eRight[j]+photon.eLeft[j]+photon.eTop[j]+photon.eBottom[j])/photon.eMax[j];
    if (swiss>0.9) return 1;
    if (fabs(photon.seedTime[j])>3) return 1;
    if (photon.sigmaIetaIeta[j]<0.002) return 1;
    if (photon.sigmaIphiIphi[j]<0.002) return 1;
  } 
  return 0;
}

bool HiForest::isGoodPhoton(int j)
{

  if (photon.isEB[j]) {
    // Barrel photon
    if (photon.hadronicOverEm[j]>0.2) return 0;
    if (photon.isEle[j]) return 0;
    if ((photon.rawEnergy[j]/photon.energy[j])<0.5) return 0;
    if (photon.sigmaIetaIeta[j]>0.011) return 0;
    if ((photon.cr4[j]+photon.cc4[j]+photon.ct4PtCut[j])>5) return 0;
  } else {
    // Endcap photon
    return 0;  // Need to update to include endcap photons
  } 

  return 1;
}

