//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 11 10:30:56 2012 by ROOT version 5.27/06b
// from TTree TriggerPrimitivesTree/Tree containing tower and region primitives.
// found on file: HiForest.root
//////////////////////////////////////////////////////////

#ifndef TriggerPrimitivesTree_calib_h
#define TriggerPrimitivesTree_calib_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

//! include the other tree objects
#include "HLTMuTree.C"
#include "HiTree.C"
#include "HltTree.C"
#include "JetTree.C"


class TriggerPrimitivesTree_calib {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  Int_t           event;
  Int_t           run;
  Int_t           ecalDetectorMapSize;
  Int_t           ecalCompressedEt[4032];   //[ecalDetectorMapSize]
  Int_t           ecalEtaIndex[4032];   //[ecalDetectorMapSize]
  Int_t           ecalPhiIndex[4032];   //[ecalDetectorMapSize]
  Double_t        ecalEta[4032];   //[ecalDetectorMapSize]
  Double_t        ecalPhi[4032];   //[ecalDetectorMapSize]
  Int_t           ecalFineGrain[4032];   //[ecalDetectorMapSize]
  Int_t           ecalTag[4032];   //[ecalDetectorMapSize]
  Int_t           hcalDetectorMapSize;
  Int_t           hcalCompressedEt[4176];   //[hcalDetectorMapSize]
  Int_t           hcalEtaIndex[4176];   //[hcalDetectorMapSize]
  Int_t           hcalPhiIndex[4176];   //[hcalDetectorMapSize]
  Double_t        hcalEta[4176];   //[hcalDetectorMapSize]
  Double_t        hcalPhi[4176];   //[hcalDetectorMapSize]
  Int_t           hcalFineGrain[4176];   //[hcalDetectorMapSize]
  Int_t           hcalTag[4176];   //[hcalDetectorMapSize]
  Int_t           numRegions;
  Int_t           caloRegionEt[396];   //[numRegions]
  Int_t           caloRegionTau[396];   //[numRegions]
  Int_t           caloRegionEtaIndex[396];   //[numRegions]
  Int_t           caloRegionPhiIndex[396];   //[numRegions]
  Double_t        caloRegionEta[396];   //[numRegions]
  Double_t        caloRegionPhi[396];   //[numRegions]
  Int_t           caloRegionTag[396];   //[numRegions]
  Int_t           caloRCTRegionEtaIndex[396];   //[numRegions]
  Int_t           caloRCTRegionPhiIndex[396];   //[numRegions]

  // List of branches
  TBranch        *b_event;   //!
  TBranch        *b_run;   //!
  TBranch        *b_ecalDetectorMapSize;   //!
  TBranch        *b_ecalCompressedEt;   //!
  TBranch        *b_ecalEtaIndex;   //!
  TBranch        *b_ecalPhiIndex;   //!
  TBranch        *b_ecalEta;   //!
  TBranch        *b_ecalPhi;   //!
  TBranch        *b_ecalFineGrain;   //!
  TBranch        *b_ecalTag;   //!
  TBranch        *b_hcalDetectorMapSize;   //!
  TBranch        *b_hcalCompressedEt;   //!
  TBranch        *b_hcalEtaIndex;   //!
  TBranch        *b_hcalPhiIndex;   //!
  TBranch        *b_hcalEta;   //!
  TBranch        *b_hcalPhi;   //!
  TBranch        *b_hcalFineGrain;   //!
  TBranch        *b_hcalTag;   //!
  TBranch        *b_numRegions;   //!
  TBranch        *b_caloRegionEt;   //!
  TBranch        *b_caloRegionTau;   //!
  TBranch        *b_caloRegionEtaIndex;   //!
  TBranch        *b_caloRegionPhiIndex;   //!
  TBranch        *b_caloRegionEta;   //!
  TBranch        *b_caloRegionPhi;   //!
  TBranch        *b_caloRegionTag;   //!
  TBranch        *b_caloRCTRegionEtaIndex;   //!
  TBranch        *b_caloRCTRegionPhiIndex;   //!
  
  TriggerPrimitivesTree_calib(TFile *f=0);
  virtual ~TriggerPrimitivesTree_calib();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual TH1D*    Loop(int total_events = 0, int cent_bin = 0);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  
  
  //! declare the other tree objects
  HltTree        *fhlt;   
  HiTree         *fhiinfo;
  //JetTree        *fjet;
  //HLTMuTree      *fmu;


};

#endif

#ifdef TriggerPrimitivesTree_calib_cxx
TriggerPrimitivesTree_calib::TriggerPrimitivesTree_calib(TFile *f)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (f == 0) {
    f = new TFile("/net/hidsk0001/d00/scratch/dgulhan/mergedforest/minbiasL1/HiForestL1_merged_v2.root");
    //f = new TFile("/net/hidsk0001/d00/scratch/dgulhan/mergedforest/L1jet/HiForestL1-jet_merged_v1.root");
    //f = new TFile("/net/hidsk0001/d00/scratch/dgulhan/mergedforest/central/HiForestL1-centeral_merged_v0.root");
    
    //tree = (TTree*)gDirectory->Get("demo/TriggerPrimitivesTree");
    
    }
  
  TTree *tree = (TTree*)gDirectory->Get("demo/TriggerPrimitivesTree");
  fhlt = new HltTree::HltTree((TTree*)gDirectory->Get("hltanalysis/HltTree"));
  fhiinfo = new HiTree::HiTree((TTree*)gDirectory->Get("hiEvtAnalyzer/HiTree"));
  //fjet = new JetTree::JetTree();
  //fmu = new HLTMuTree::HLTMuTree();  
  
  Init(tree);
}

TriggerPrimitivesTree_calib::~TriggerPrimitivesTree_calib()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t TriggerPrimitivesTree_calib::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t TriggerPrimitivesTree_calib::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void TriggerPrimitivesTree_calib::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("ecalDetectorMapSize", &ecalDetectorMapSize, &b_ecalDetectorMapSize);
  fChain->SetBranchAddress("ecalCompressedEt", ecalCompressedEt, &b_ecalCompressedEt);
  fChain->SetBranchAddress("ecalEtaIndex", ecalEtaIndex, &b_ecalEtaIndex);
  fChain->SetBranchAddress("ecalPhiIndex", ecalPhiIndex, &b_ecalPhiIndex);
  fChain->SetBranchAddress("ecalEta", ecalEta, &b_ecalEta);
  fChain->SetBranchAddress("ecalPhi", ecalPhi, &b_ecalPhi);
  fChain->SetBranchAddress("ecalFineGrain", ecalFineGrain, &b_ecalFineGrain);
  fChain->SetBranchAddress("ecalTag", ecalTag, &b_ecalTag);
  fChain->SetBranchAddress("hcalDetectorMapSize", &hcalDetectorMapSize, &b_hcalDetectorMapSize);
  fChain->SetBranchAddress("hcalCompressedEt", hcalCompressedEt, &b_hcalCompressedEt);
  fChain->SetBranchAddress("hcalEtaIndex", hcalEtaIndex, &b_hcalEtaIndex);
  fChain->SetBranchAddress("hcalPhiIndex", hcalPhiIndex, &b_hcalPhiIndex);
  fChain->SetBranchAddress("hcalEta", hcalEta, &b_hcalEta);
  fChain->SetBranchAddress("hcalPhi", hcalPhi, &b_hcalPhi);
  fChain->SetBranchAddress("hcalFineGrain", hcalFineGrain, &b_hcalFineGrain);
  fChain->SetBranchAddress("hcalTag", hcalTag, &b_hcalTag);
  fChain->SetBranchAddress("numRegions", &numRegions, &b_numRegions);
  fChain->SetBranchAddress("caloRegionEt", caloRegionEt, &b_caloRegionEt);
  fChain->SetBranchAddress("caloRegionTau", caloRegionTau, &b_caloRegionTau);
  fChain->SetBranchAddress("caloRegionEtaIndex", caloRegionEtaIndex, &b_caloRegionEtaIndex);
  fChain->SetBranchAddress("caloRegionPhiIndex", caloRegionPhiIndex, &b_caloRegionPhiIndex);
  fChain->SetBranchAddress("caloRegionEta", caloRegionEta, &b_caloRegionEta);
  fChain->SetBranchAddress("caloRegionPhi", caloRegionPhi, &b_caloRegionPhi);
  fChain->SetBranchAddress("caloRegionTag", caloRegionTag, &b_caloRegionTag);
  fChain->SetBranchAddress("caloRCTRegionEtaIndex", caloRCTRegionEtaIndex, &b_caloRCTRegionEtaIndex);
  fChain->SetBranchAddress("caloRCTRegionPhiIndex", caloRCTRegionPhiIndex, &b_caloRCTRegionPhiIndex);
  Notify();
}

Bool_t TriggerPrimitivesTree_calib::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void TriggerPrimitivesTree_calib::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t TriggerPrimitivesTree_calib::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef TriggerPrimitivesTree_calib_cxx
