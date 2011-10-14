#include <iostream>
#include <vector>
#include <algorithm>

#include "commonTool.h"
#include "SetupPhotonTree.h"
#include "SetupJetTree.h"
#include "SetupHltTree.h"
#include "SetupSkimTree.h"
#include "SetupTrackTree.h"
#include "SetupHitTree.h"

#include <TTree.h>
#include <TFile.h>
#include <TString.h>
#include <TF1.h>
#include <TCut.h>

// ==========================================================
// Main class which can be used to read the hiForest trees
//
// Author: Yen-Jie Lee
//
// ==========================================================

class HiForest : public TNamed
{

  public: 
   HiForest(const char *file, const char *name="forest", bool ispp = 0, bool ismc = 0);
  ~HiForest();

  // Utility functions
  void GetEntry(int i);
  int  GetEntries();  						// Get the number of entries 
  void CheckTree(TTree *t,const char *title);				// Check the status of a tree
  void PrintStatus();						// Print the status of the hiForest
  void SetOutputFile(const char *name);               		// Set output file name for skim
  void AddCloneTree(TTree* t, const char *dirName, const char *treeName);   // Add a clone tree to the clone forest
  void FillOutput();						// Fill output forest  
  Long64_t Draw(const char* varexp, const char* selection, Option_t* option = "", Long64_t nentries = 1000000000, Long64_t firstentry = 0){
     return tree->Draw(varexp,selection,option,nentries,firstentry);
  }

  // Event filtering utility functions
  bool selectEvent();
  TCut eventSelection();

  // Photon utility functions
  bool isSpike(int i);                          // return true if it is considered as a spike candidate
  bool isGoodPhoton(int i);                     // return true if it is considered as a hiGoodPhoton candidate

  // Jet utility functions
  void sortJets(TTree* jetTree, Jets& jets, double etaMax = 2, double ptMin = 40, bool allEvents = 1, int smearType = -1);
  int leadingJet();
  int subleadingJet();
  int thirdJet();

  // Get track-jet correlated variables. Not needed if correlatePF is run.
  void correlateTracks(TTree* jetTree, Jets& jets, bool allEvents = 1);
  // Build correlations between jet & its constituents, builds jetIDs
  void correlatePF(TTree* jetTree, Jets& jets, bool allEvents = 1){return;}

  double jetFracChg(int i);
  double jetFracNeut(int i);
  double jetFracEM(int i);

  // Track utility functions
  int getMatchedCaloTowerAllowReuse(int j);
  int getMatchedHBHEAllowReuse(int j);
  void matchTrackCalo(bool allEvents = 1);

  // TFile
  TFile *inf; 					// Input file 
  TFile *outf;                                  // Output file

  // Trees
  TTree *photonTree;				// Photon Tree, see branches in SetupPhotonTree.h
  TTree *icPu5jetTree;				// Jet Tree with icPu5 algorithm, see branches in SetupJetTree.h
  TTree *akPu3jetTree;				// Jet Tree with akPu3PF algorithm, see branches in SetupJetTree.h
  TTree *hltTree;				// OpenHLT Tree, see branches in SetupHltTree.h
  TTree *trackTree;				// Track Tree, see branches in SetupTrackTree.h
  TTree *skimTree;				// Skim Tree, contains event selection info, see branches in SetupSkimTree.h
  TTree *towerTree;                             // Tower Tree
  TTree *hbheTree;                              // HCAL HBHE Tree

  TTree *tree;					// Pointer to the available tree, all trees in the forest are friended to each other

  vector<TTree*> cloneForest;                   // Vector of clones for skim

  TF1* fGauss;

  // Branches
  Hlts hlt;
  Skims skim;
  Jets icPu5;
  Jets akPu3PF;
  Photons photon;
  Tracks track;
  Hits tower;
  Hits hbhe;
  
  // Booleans
  bool hasPhotonTree;
  bool hasIcPu5JetTree;
  bool hasAkPu3JetTree;
  bool hasHltTree;
  bool hasTrackTree;
  bool hasSkimTree;
  bool hasTowerTree;
  bool hasHbheTree;

  bool setupOutput;
  bool verbose;
  bool pp;
  bool mc;

  // Extra variables
  Float_t* towerEt;
  Float_t* towerdR;
  Float_t* hbheEt;
  Float_t* hbhedR;

  Float_t* jtChg;
  Float_t* jtNeut;
  Float_t* jtEM;

  Float_t* jtChgGen;
  Float_t* jtNeutGen;
  Float_t* jtEMGen;

  Float_t* jtPtMax;
  Float_t* jtPtMean;
  Float_t* jtPtMeanW;

  Int_t* jtLeadType;

  Int_t jtLead;
  Int_t jtSubLead;
  bool jtHasDijet;
  bool jtHasLeadingJet;

  Float_t* tjDeltaEtaLead;
  Float_t* tjDeltaPhiLead;
  Float_t* zLead;

  Float_t* tjDeltaEtaSubLead;
  Float_t* tjDeltaPhiSubLead;
  Float_t* zSubLead;

  int currentEvent;
 private:

};

HiForest::HiForest(const char *infName, const char* name, bool ispp, bool ismc):
   tree(0),
   fGauss(0),
   verbose(0),
   pp(ispp),
   mc(ismc)
{

  SetName(name);
  // Input file
  inf = TFile::Open(infName);

  // Load trees. Hard coded for the moment
  hltTree      = (TTree*) inf->Get("hltanalysis/HltTree");
  skimTree     = (TTree*) inf->Get("skimanalysis/HltTree");
  photonTree   = (TTree*) inf->Get("NTuples/Analysis");
  icPu5jetTree = (TTree*) inf->Get("icPu5JetAnalyzer/t");
  akPu3jetTree = (TTree*) inf->Get("akPu3PFJetAnalyzer/t");
  trackTree    = (TTree*) inf->Get("anaTrack/trackTree");
  towerTree    = (TTree*) inf->Get("rechitanalyzer/tower");
  hbheTree    = (TTree*) inf->Get("rechitanalyzer/hbhe");

  // Check the validity of the trees.
  hasPhotonTree    = (photonTree   != 0);
  hasIcPu5JetTree  = (icPu5jetTree != 0);
  hasAkPu3JetTree  = (akPu3jetTree != 0);
  hasTrackTree     = (trackTree    != 0);
  hasHltTree       = (hltTree      != 0);
  hasSkimTree      = (skimTree     != 0);
  hasTowerTree     = (towerTree    != 0);
  hasHbheTree      = (hbheTree     != 0);
  setupOutput = false;
  
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

  if (hasTowerTree) {
    towerTree->SetName("tower");
    if (tree == 0) tree = towerTree; else tree->AddFriend(towerTree);
    setupHitTree(towerTree,tower);
  }

  if (hasHbheTree) {
    hbheTree->SetName("hbhe");
    if (tree == 0) tree = hbheTree; else tree->AddFriend(hbheTree);
    setupHitTree(hbheTree,hbhe);
  }
  
  tree->SetMarkerStyle(20);

  // Print the status of thre forest
  PrintStatus();

  currentEvent = 0;
}

HiForest::~HiForest()
{
  if (setupOutput) {
    for (unsigned int i=0; i<cloneForest.size(); i++)
    {
      cloneForest[i]->AutoSave();
    }
    outf->Close();
  }
}

void HiForest::GetEntry(int i)
{

   currentEvent = i;
  // get the entry of the available trees
  if (hasPhotonTree)   photonTree   ->GetEntry(i);
  if (hasHltTree)      hltTree      ->GetEntry(i);
  if (hasSkimTree)     skimTree     ->GetEntry(i);
  if (hasIcPu5JetTree) icPu5jetTree ->GetEntry(i);
  if (hasAkPu3JetTree) akPu3jetTree ->GetEntry(i);
  if (hasTrackTree)    trackTree    ->GetEntry(i);
  if (hasTowerTree)    towerTree    ->GetEntry(i);
  if (hasHbheTree)     hbheTree     ->GetEntry(i);
}

int HiForest::GetEntries()
{
  // get the entries of the available trees
  return tree->GetEntries();
}

void HiForest::CheckTree(TTree *t,const char *title)
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

void HiForest::PrintStatus()
{
  if (hasHltTree)      CheckTree(hltTree,      "HltTree");
  if (hasSkimTree)     CheckTree(skimTree,     "SkimTree");
  if (hasIcPu5JetTree) CheckTree(icPu5jetTree, "IcPu5jetTree");
  if (hasAkPu3JetTree) CheckTree(akPu3jetTree, "AkPu3jetTree");
  if (hasTrackTree)    CheckTree(trackTree,    "TrackTree");
  if (hasPhotonTree)   CheckTree(photonTree,   "PhotonTree");
  if (hasTowerTree)    CheckTree(towerTree,    "TowerTree");
  if (hasHbheTree)     CheckTree(hbheTree,     "HbheTree");

}

void HiForest::SetOutputFile(const char *name)
{
  outf = new TFile(name,"recreate");
  if (hasHltTree)      AddCloneTree(hltTree,      "hltanalysis",        "HltTree");
  if (hasSkimTree)     AddCloneTree(skimTree,     "skimanalysis",       "HltTree");
  if (hasIcPu5JetTree) AddCloneTree(icPu5jetTree, "icPu5JetAnalyzer",   "t");
  if (hasAkPu3JetTree) AddCloneTree(akPu3jetTree, "akPu3PFJetAnalyzer", "t");
  if (hasTrackTree)    AddCloneTree(trackTree,    "anaTrack",           "trackTree");
  if (hasPhotonTree)   AddCloneTree(photonTree,   "NTuples",            "Analysis");
  if (hasTowerTree)    AddCloneTree(towerTree,    "tower",              "rechitanalyzer");
  if (hasHbheTree)     AddCloneTree(hbheTree,     "hbhe",               "rechitanalyzer");
  setupOutput = true;
}

void HiForest::AddCloneTree(TTree* t, const char *dirName, const char *treeName)
{
  // Make directory
  outf->cd();
  outf->mkdir(dirName);
  outf->cd(dirName);

  // Add a clone tree to the clone forest
  TTree *tClone = t->CloneTree(0);
  tClone->SetMaxTreeSize(4000000000);
  tClone->SetName(treeName);
  
  cloneForest.push_back(tClone);
}

void HiForest::FillOutput()
{
  if (setupOutput) {
     for (unsigned int i=0; i<cloneForest.size(); i++)
     {
       cloneForest[i]->Fill();
     } 
  } else {
       cout <<"ERROR: Specify an output file by hiForest.SetOutputFile(filename)!"<<endl;
  }
}

// ====================== Event Utilities ========================

bool HiForest::selectEvent(){
   bool select = skim.phbheReflagNewTimeEnv 
      && 
      skim.phcalTimingFilter 
      && 
      skim.pHBHENoiseFilter 
      && 
      skim.phiEcalRecHitSpikeFilter;

   if(!pp){
      select = select && skim.pcollisionEventSelection;
   }else{
      select = select && skim.phfCoincFilter && skim.ppurityFractionFilter;
   }
   return select;
}

TCut HiForest::eventSelection(){
   TCut select("skim.phbheReflagNewTimeEnv && skim.phcalTimingFilter && skim.pHBHENoiseFilter && skim.phiEcalRecHitSpikeFilter");
   if(!pp){
      select = select && "skim.pcollisionEventSelection";
   }else{
      select = select && "skim.phfCoincFilter && skim.ppurityFractionFilter";
   }
   return select;
}


// ====================== Track Utilities ========================
#include "TrackUtilities.C"

// ======================= Jet Utilities =========================
#include "JetUtilities.C"

// ====================== Photon Utilities ========================
#include "PhotonUtilities.C"


