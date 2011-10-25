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
#include "TrackingCorrections.h"

#include <TTree.h>
#include <TFile.h>
#include <TString.h>
#include <TF1.h>
#include <TCut.h>


//#define CMSSW 1
#ifdef CMSSW

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#else
#include "DummyJetCorrector.h"
#endif


// ==========================================================
// Main class which can be used to read the hiForest trees
//
// Author: Yen-Jie Lee
//
// ==========================================================

namespace names{
  enum Algo{
     icPu5calo,         ic5calo,         akPu3calo,         ak3calo,         akPu3PF,             ak3PF,             akPu5calo,         ak5calo,         akPu5PF,             ak5PF};
  string AlgoRename[100] = {
    "icPu5calo",       "ic5calo",       "akPu3calo",       "ak3calo",       "akPu3PF",           "ak3PF",           "akPu5calo",       "ak5calo",       "akPu5PF",           "ak5PF"};
  string AlgoAnalyzer[100] = {
    "icPu5JetAnalyzer","ic5JetAnalyzer","akPu3JetAnalyzer","ak3JetAnalyzer","akPu3PFJetAnalyzer","ak3PFJetAnalyzer","akPu5JetAnalyzer","ak5JetAnalyzer","akPu5PFJetAnalyzer","ak5PFJetAnalyzer"};
}

class HiForest : public TNamed
{

  public: 
   HiForest(const char *file, const char *name="forest", bool ispp = 0, bool ismc = 0, bool isrecorrected = 0);
  ~HiForest();

  // Utility functions
  void GetEntry(int i);
  int  GetEntries();  						// Get the number of entries 
  void CheckTree(TTree *t,const char *title);				// Check the status of a tree

  void CheckArraySizes();
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
  double deltaPhiDijet(Jets& jets);
  bool hasDiJet(Jets& jets, double pt1 = 100, double pt2 = 40, double dphiMin = 2.*3.1415926/3.);

  // Get track-jet correlated variables. Not needed if correlatePF is run.
  void correlateTracks(TTree* jetTree, Jets& jets, bool allEvents = 1, bool smeared = 0);
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

  vector<TTree*> jetTrees;
  vector<TTree*> cloneForest;                   // Vector of clones for skim

  TF1* fGauss;

  // Branches
  Hlts hlt;
  Skims skim;

  vector<Jets> alljets;

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
  bool doJetCorrection;
  bool doTrackCorrections;

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

  Float_t* zOldLead;
  Float_t* zOldSubLead;

  Float_t* zSingleLead;
  Float_t* zLabLead;
  Float_t* zSingleSubLead;
  Float_t* zLabSubLead;
  Float_t* tjDeltaThetaLead;
  Float_t* tjDeltaThetaLabLead;
  Float_t* tjDeltaThetaSingleLead;

  Float_t* tjDeltaThetaSubLead;
  Float_t* tjDeltaThetaLabSubLead;
  Float_t* tjDeltaThetaSingleSubLead;

  Float_t* corrLead;
  Float_t* corrSubLead;

  int nEntries;
  int currentEvent;

  vector<JetCorrectorParameters> vpar_HI310x;
  FactorizedJetCorrector *_JEC_HI310X;

  vector<TrackingCorrections*> trackCorrections;

 private:

};

HiForest::HiForest(const char *infName, const char* name, bool ispp, bool ismc, bool recjec):
   tree(0),
   fGauss(0),
   verbose(0),
   pp(ispp),
   mc(ismc),
   nEntries(0),
   currentEvent(0)
{
  tree = new TTree("tree","");
  SetName(name);
  // Input file
  inf = TFile::Open(infName);

  doTrackCorrections = false;

  // Load trees. Hard coded for the moment
  hltTree      = (TTree*) inf->Get("hltanalysis/HltTree");
  skimTree     = (TTree*) inf->Get("skimanalysis/HltTree");
  photonTree   = (TTree*) inf->Get("NTuples/Analysis");
  trackTree    = (TTree*) inf->Get("anaTrack/trackTree");
  towerTree    = (TTree*) inf->Get("rechitanalyzer/tower");
  hbheTree    = (TTree*) inf->Get("rechitanalyzer/hbhe");

  if(pp){
    icPu5jetTree = 0;//(TTree*) inf->Get(Form("%s/t",names::AlgoAnalyzer[names::icPu5calo].data()));
    akPu3jetTree = (TTree*) inf->Get(Form("%s/t",names::AlgoAnalyzer[names::ak3PF].data()));
  }else{
    icPu5jetTree = 0;//(TTree*) inf->Get(Form("%s/t",names::AlgoAnalyzer[names::icPu5calo].data()));
    if(recjec){
       akPu3jetTree = (TTree*) inf->Get(Form("%s/t",(names::AlgoAnalyzer[names::akPu3PF]+"_recorrected").data()));
       cout<<"HEEY, the jets are: "<<akPu3jetTree->GetName()<<endl;
    }else{
       akPu3jetTree = (TTree*) inf->Get(Form("%s/t",names::AlgoAnalyzer[names::akPu3PF].data()));
    }
  }

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


  // Setup Jet Corrections
  string prestring399x = "/net/hidsk0001/d00/scratch/mnguyen/CMSSW_3_9_9_patch1/src/CondFormats/JetMETObjects/data/HI_PFTowers_hiGoodTightTracks_D6T_399_v2";

  string prestring399y = "/net/hidsk0001/d00/scratch/mnguyen/CMSSW_4_1_3_patch2/src/macros/JEC/data/HI_PFTowers_hiGoodTightTracks_D6T_399";

  string prestring399 = "/net/hidsk0001/d00/scratch/mnguyen/CMSSW_3_9_9_patch1/src/macros/JEC/data/HI_PFTowers_hiGoodTightTracks_D6T_399";

  string prestring413 = "/net/hidsk0001/d00/scratch/mnguyen/CMSSW_4_1_3_patch2/src/macros/JEC/data/HI_PFTowers_hiGoodTightTracks_D6T_413";

  string L2Name = "", L3Name = "";

  L2Name = prestring399 + "_L2Relative_AK3PF.txt";
  L3Name = prestring399 + "_L3Absolute_AK3PF.txt";
  
  cout<<"a"<<endl;
  vpar_HI310x.push_back(JetCorrectorParameters(L2Name.data()));
  cout<<"b"<<endl;

  vpar_HI310x.push_back(JetCorrectorParameters(L3Name.data()));
  cout<<"c"<<endl;

  _JEC_HI310X = new FactorizedJetCorrector(vpar_HI310x);
  doJetCorrection = 1;
  cout<<"d"<<endl;

  // Setup Track Corrections
  if(doTrackCorrections){
    if(pp){
      trackCorrections.push_back(new TrackingCorrections("trkCorrHisAna_djuq","_ppcorrpthgtv4","hitrkEffAnalyzer_akpu3pf"));
      trackCorrections.push_back(new TrackingCorrections("trkCorrHisAna_djuq","_ppcorrpthgtv4","hitrkEffAnalyzer_akpu3pf"));
    }else{
      trackCorrections.push_back(new TrackingCorrections("trkCorrHisAna_djuq","_tev9hgtv4_3","hitrkEffAnalyzer_akpu3pf"));
      trackCorrections.push_back(new TrackingCorrections("trkCorrHisAna_djuq","_tev9hgtv4_3","hitrkEffAnalyzer_akpu3pf"));
    }
    
    trackCorrections[0]->isLeadingJet_ = 1;
    trackCorrections[1]->isLeadingJet_ = 0;
    
    for(int i = 0; i < trackCorrections.size(); ++i){
      
      trackCorrections[i]->sampleMode_ = 1;
      trackCorrections[i]->smoothLevel_ = 4;
      trackCorrections[i]->Init();
    }
  }
  
  //  CheckArraySizes();
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
  return nEntries;
}

void HiForest::CheckTree(TTree *t,const char *title)
{
  int entries = t->GetEntries();
  if (nEntries==0) nEntries = entries;
  cout <<title<<": "<<entries<<" entries loaded.";
  if (entries != nEntries) {
    cout <<" Inconsistent number of entries!!"<<endl;
  } else {
    cout <<endl;
  }
}


void HiForest::CheckArraySizes(){

  vector<int> trackOverflow(0);
  vector<int> objectOverflow(0);

  for(int ie = 0; ie < nEntries; ++ie){
    GetEntry(ie);
    if(track.nTrk > maxEntryTrack) trackOverflow.push_back(track.nTrk);
    if(akPu3PF.nref > maxEntry) objectOverflow.push_back(akPu3PF.nref);
    if(icPu5.nref > maxEntry) objectOverflow.push_back(icPu5.nref);
  }

  for(int i = 0; i < trackOverflow.size(); ++i){
    cout<<trackOverflow[i]<<endl;
  }

  if(trackOverflow.size() == 0) cout<<"Track sizes OK"<<endl;
  else cout<<"tracks crash"<<endl; // TODO : really crash

  for(int i = 0; i < objectOverflow.size(); ++i){
    cout<<objectOverflow[i]<<endl;
  }

  if(objectOverflow.size() == 0) cout<<"Object sizes OK"<<endl;
  else cout<<"objects crash"<<endl; // TODO : really crash

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

     if(pp){
	if (hasIcPu5JetTree) AddCloneTree(icPu5jetTree, names::AlgoAnalyzer[names::icPu5calo].data(),   "t");
	if (hasAkPu3JetTree) AddCloneTree(akPu3jetTree, names::AlgoAnalyzer[names::ak3PF].data(), "t");
     }else{
	if (hasIcPu5JetTree) AddCloneTree(icPu5jetTree, names::AlgoAnalyzer[names::icPu5calo].data(),   "t");
	if (hasAkPu3JetTree) AddCloneTree(akPu3jetTree, names::AlgoAnalyzer[names::akPu3PF].data(), "t");
     }

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


