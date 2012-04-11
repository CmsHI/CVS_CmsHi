//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 11 10:29:59 2012 by ROOT version 5.27/06b
// from TTree HLTMuTree/HLTMuTree
// found on file: HiForest.root
//////////////////////////////////////////////////////////

#ifndef HLTMuTree_h
#define HLTMuTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class HLTMuTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Event;
   Int_t           Lumi;
   Int_t           CentBin;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Int_t           Gen_nptl;
   Int_t           Gen_pid[1];   //[Gen_nptl]
   Int_t           Gen_mom[1];   //[Gen_nptl]
   Int_t           Gen_status[1];   //[Gen_nptl]
   Float_t         Gen_p[1];   //[Gen_nptl]
   Float_t         Gen_pt[1];   //[Gen_nptl]
   Float_t         Gen_eta[1];   //[Gen_nptl]
   Float_t         Gen_phi[1];   //[Gen_nptl]
   Int_t           Glb_nptl;
   Int_t           Glb_charge[3];   //[Glb_nptl]
   Float_t         Glb_p[3];   //[Glb_nptl]
   Float_t         Glb_pt[3];   //[Glb_nptl]
   Float_t         Glb_eta[3];   //[Glb_nptl]
   Float_t         Glb_phi[3];   //[Glb_nptl]
   Float_t         Glb_dxy[3];   //[Glb_nptl]
   Float_t         Glb_dz[3];   //[Glb_nptl]
   Int_t           Glb_nValMuHits[3];   //[Glb_nptl]
   Int_t           Glb_nValTrkHits[3];   //[Glb_nptl]
   Int_t           Glb_nTrkFound[3];   //[Glb_nptl]
   Float_t         Glb_glbChi2_ndof[3];   //[Glb_nptl]
   Float_t         Glb_trkChi2_ndof[3];   //[Glb_nptl]
   Int_t           Glb_pixLayerWMeas[3];   //[Glb_nptl]
   Float_t         Glb_trkDxy[3];   //[Glb_nptl]
   Float_t         Glb_trkDz[3];   //[Glb_nptl]
   Int_t           Sta_nptl;
   Int_t           Sta_charge[2];   //[Sta_nptl]
   Float_t         Sta_p[2];   //[Sta_nptl]
   Float_t         Sta_pt[2];   //[Sta_nptl]
   Float_t         Sta_eta[2];   //[Sta_nptl]
   Float_t         Sta_phi[2];   //[Sta_nptl]
   Float_t         Sta_dxy[2];   //[Sta_nptl]
   Float_t         Sta_dz[2];   //[Sta_nptl]

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_cbin;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_Gen_nptl;   //!
   TBranch        *b_Gen_pid;   //!
   TBranch        *b_Gen_mom;   //!
   TBranch        *b_Gen_status;   //!
   TBranch        *b_Gen_p;   //!
   TBranch        *b_Gen_pt;   //!
   TBranch        *b_Gen_eta;   //!
   TBranch        *b_Gen_phi;   //!
   TBranch        *b_Glb_nptl;   //!
   TBranch        *b_Glb_charge;   //!
   TBranch        *b_Glb_p;   //!
   TBranch        *b_Glb_pt;   //!
   TBranch        *b_Glb_eta;   //!
   TBranch        *b_Glb_phi;   //!
   TBranch        *b_Glb_dxy;   //!
   TBranch        *b_Glb_dz;   //!
   TBranch        *b_Glb_nValMuHits;   //!
   TBranch        *b_Glb_nValTrkHits;   //!
   TBranch        *b_Glb_nTrkFound;   //!
   TBranch        *b_Glb_glbChi2_ndof;   //!
   TBranch        *b_Glb_trkChi2_ndof;   //!
   TBranch        *b_Glb_pixLayerWMeas;   //!
   TBranch        *b_Glb_trkDxy;   //!
   TBranch        *b_Glb_trkDz;   //!
   TBranch        *b_Sta_nptl;   //!
   TBranch        *b_Sta_charge;   //!
   TBranch        *b_Sta_p;   //!
   TBranch        *b_Sta_pt;   //!
   TBranch        *b_Sta_eta;   //!
   TBranch        *b_Sta_phi;   //!
   TBranch        *b_Sta_dxy;   //!
   TBranch        *b_Sta_dz;   //!

   HLTMuTree(TTree *tree=0);
   virtual ~HLTMuTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HLTMuTree_cxx
HLTMuTree::HLTMuTree(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = new TFile("HiForest.root");
      tree = (TTree*)gDirectory->Get("muonTree/HLTMuTree");

   }
   Init(tree);
}

HLTMuTree::~HLTMuTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HLTMuTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HLTMuTree::LoadTree(Long64_t entry)
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

void HLTMuTree::Init(TTree *tree)
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

   fChain->SetBranchAddress("Run", &Run, &b_run);
   fChain->SetBranchAddress("Event", &Event, &b_event);
   fChain->SetBranchAddress("Lumi", &Lumi, &b_lumi);
   fChain->SetBranchAddress("CentBin", &CentBin, &b_cbin);
   fChain->SetBranchAddress("vx", &vx, &b_vx);
   fChain->SetBranchAddress("vy", &vy, &b_vy);
   fChain->SetBranchAddress("vz", &vz, &b_vz);
   fChain->SetBranchAddress("Gen_nptl", &Gen_nptl, &b_Gen_nptl);
   fChain->SetBranchAddress("Gen_pid", &Gen_pid, &b_Gen_pid);
   fChain->SetBranchAddress("Gen_mom", &Gen_mom, &b_Gen_mom);
   fChain->SetBranchAddress("Gen_status", &Gen_status, &b_Gen_status);
   fChain->SetBranchAddress("Gen_p", &Gen_p, &b_Gen_p);
   fChain->SetBranchAddress("Gen_pt", &Gen_pt, &b_Gen_pt);
   fChain->SetBranchAddress("Gen_eta", &Gen_eta, &b_Gen_eta);
   fChain->SetBranchAddress("Gen_phi", &Gen_phi, &b_Gen_phi);
   fChain->SetBranchAddress("Glb_nptl", &Glb_nptl, &b_Glb_nptl);
   fChain->SetBranchAddress("Glb_charge", Glb_charge, &b_Glb_charge);
   fChain->SetBranchAddress("Glb_p", Glb_p, &b_Glb_p);
   fChain->SetBranchAddress("Glb_pt", Glb_pt, &b_Glb_pt);
   fChain->SetBranchAddress("Glb_eta", Glb_eta, &b_Glb_eta);
   fChain->SetBranchAddress("Glb_phi", Glb_phi, &b_Glb_phi);
   fChain->SetBranchAddress("Glb_dxy", Glb_dxy, &b_Glb_dxy);
   fChain->SetBranchAddress("Glb_dz", Glb_dz, &b_Glb_dz);
   fChain->SetBranchAddress("Glb_nValMuHits", Glb_nValMuHits, &b_Glb_nValMuHits);
   fChain->SetBranchAddress("Glb_nValTrkHits", Glb_nValTrkHits, &b_Glb_nValTrkHits);
   fChain->SetBranchAddress("Glb_nTrkFound", Glb_nTrkFound, &b_Glb_nTrkFound);
   fChain->SetBranchAddress("Glb_glbChi2_ndof", Glb_glbChi2_ndof, &b_Glb_glbChi2_ndof);
   fChain->SetBranchAddress("Glb_trkChi2_ndof", Glb_trkChi2_ndof, &b_Glb_trkChi2_ndof);
   fChain->SetBranchAddress("Glb_pixLayerWMeas", Glb_pixLayerWMeas, &b_Glb_pixLayerWMeas);
   fChain->SetBranchAddress("Glb_trkDxy", Glb_trkDxy, &b_Glb_trkDxy);
   fChain->SetBranchAddress("Glb_trkDz", Glb_trkDz, &b_Glb_trkDz);
   fChain->SetBranchAddress("Sta_nptl", &Sta_nptl, &b_Sta_nptl);
   fChain->SetBranchAddress("Sta_charge", Sta_charge, &b_Sta_charge);
   fChain->SetBranchAddress("Sta_p", Sta_p, &b_Sta_p);
   fChain->SetBranchAddress("Sta_pt", Sta_pt, &b_Sta_pt);
   fChain->SetBranchAddress("Sta_eta", Sta_eta, &b_Sta_eta);
   fChain->SetBranchAddress("Sta_phi", Sta_phi, &b_Sta_phi);
   fChain->SetBranchAddress("Sta_dxy", Sta_dxy, &b_Sta_dxy);
   fChain->SetBranchAddress("Sta_dz", Sta_dz, &b_Sta_dz);
   Notify();
}

Bool_t HLTMuTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HLTMuTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HLTMuTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HLTMuTree_cxx
