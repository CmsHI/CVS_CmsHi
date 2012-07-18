//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 11 11:01:53 2012 by ROOT version 5.27/06b
// from TTree t/icPu5patJets Jet Analysis Tree
// found on file: HiForest.root
//////////////////////////////////////////////////////////

#ifndef JetTree_h
#define JetTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>

class JetTree {
  public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  Int_t           evt;
  Float_t         b;
  Int_t           nref;
  Float_t         rawpt[2400];   //[nref]
  Float_t         jtpt[2400];   //[nref]
  Float_t         jteta[2400];   //[nref]
  Float_t         jty[2400];   //[nref]
  Float_t         jtphi[2400];   //[nref]
  Float_t         jtpu[2400];   //[nref]

  Int_t           ngen;
  Float_t         genpt[500];
  Float_t         geneta[500];
  Float_t         genphi[500];
  Int_t           gensubid[500];

  // List of branches
  TBranch        *b_evt;   //!
  TBranch        *b_b;   //!
  TBranch        *b_nref;   //!
  TBranch        *b_rawpt;   //!
  TBranch        *b_jtpt;   //!
  TBranch        *b_jteta;   //!
  TBranch        *b_jty;   //!
  TBranch        *b_jtphi;   //!
  TBranch        *b_jtpu;   //!

  TBranch        *b_ngen;
  TBranch        *b_genpt;
  TBranch        *b_geneta;
  TBranch        *b_genphi;
  TBranch        *b_gensubid;

  JetTree(TTree *tree=0);
  virtual ~JetTree();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef JetTree_cxx
JetTree::JetTree(TTree *tree)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = new TFile("HiForest.root");
    tree = (TTree*)gDirectory->Get("icPu5JetAnalyzer/t");
  }
  Init(tree);
}

JetTree::~JetTree()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t JetTree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t JetTree::LoadTree(Long64_t entry)
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

void JetTree::Init(TTree *tree)
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

  fChain->SetBranchAddress("evt", &evt, &b_evt);
  fChain->SetBranchAddress("b", &b, &b_b);
  fChain->SetBranchAddress("nref", &nref, &b_nref);
  fChain->SetBranchAddress("rawpt", rawpt, &b_rawpt);
  fChain->SetBranchAddress("jtpt", jtpt, &b_jtpt);
  fChain->SetBranchAddress("jteta", jteta, &b_jteta);
  fChain->SetBranchAddress("jty", jty, &b_jty);
  fChain->SetBranchAddress("jtphi", jtphi, &b_jtphi);
  fChain->SetBranchAddress("jtpu", jtpu, &b_jtpu);

  fChain->SetBranchAddress("ngen", &ngen, &b_ngen);
  fChain->SetBranchAddress("genpt", genpt, &b_genpt);
  fChain->SetBranchAddress("geneta", geneta, &b_geneta);
  fChain->SetBranchAddress("genphi", genphi, &b_genphi);
  fChain->SetBranchAddress("gensubid", &gensubid, &b_gensubid);
  
  Notify();
}

Bool_t JetTree::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void JetTree::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t JetTree::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef JetTree_cxx
