//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 11 10:30:56 2012 by ROOT version 5.27/06b
// from TTree TriggerPrimitivesTree/Tree containing tower and region primitives.
// found on file: HiForest.root
//////////////////////////////////////////////////////////

#ifndef RecHitsTree_calib_h
#define RecHitsTree_calib_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1.h"

//! include the other tree objects
#include "HLTMuTree.C"
#include "HiTree.C"
#include "HltTree.C"
#include "JetTree.C"


class RecHitsTree_calib {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  /* Int_t           event; */
  /* Int_t           run; */
  /* Int_t           ecalDetectorMapSize; */
  /* Int_t           ecalCompressedEt[4032];   //[ecalDetectorMapSize] */
  /* Int_t           ecalEt[4032]; //[ecalDetectorMapSize] */
  /* Int_t           ecalEtaIndex[4032];   //[ecalDetectorMapSize] */
  /* Int_t           ecalPhiIndex[4032];   //[ecalDetectorMapSize] */
  /* Double_t        ecalEta[4032];   //[ecalDetectorMapSize] */
  /* Double_t        ecalPhi[4032];   //[ecalDetectorMapSize] */
  /* Int_t           ecalFineGrain[4032];   //[ecalDetectorMapSize] */
  /* Int_t           ecalTag[4032];   //[ecalDetectorMapSize] */
  /* Int_t           hcalDetectorMapSize; */
  /* Int_t           hcalCompressedEt[4176];   //[hcalDetectorMapSize] */
  /* Int_t           hcalEt[4176];   //[hcalDetectorMapSize] */
  /* Int_t           hcalEtaIndex[4176];   //[hcalDetectorMapSize] */
  /* Int_t           hcalPhiIndex[4176];   //[hcalDetectorMapSize] */
  /* Double_t        hcalEta[4176];   //[hcalDetectorMapSize] */
  /* Double_t        hcalPhi[4176];   //[hcalDetectorMapSize] */
  /* Int_t           hcalFineGrain[4176];   //[hcalDetectorMapSize] */
  /* Int_t           hcalTag[4176];   //[hcalDetectorMapSize] */
  /* Int_t           numRegions; */
  /* Int_t           caloRegionEt[396];   //[numRegions] */
  /* Int_t           caloRegionTau[396];   //[numRegions] */
  /* Int_t           caloRegionEtaIndex[396];   //[numRegions] */
  /* Int_t           caloRegionPhiIndex[396];   //[numRegions] */
  /* Double_t        caloRegionEta[396];   //[numRegions] */
  /* Double_t        caloRegionPhi[396];   //[numRegions] */
  /* Int_t           caloRegionTag[396];   //[numRegions] */
  /* Int_t           caloRCTRegionEtaIndex[396];   //[numRegions] */
  /* Int_t           caloRCTRegionPhiIndex[396];   //[numRegions] */
  Int_t n;
  Float_t e[4320]; //[n]
  Float_t et[4320]; //[n]
  Float_t eta[4320]; //[n]
  Float_t phi[4320]; //[n]
  Float_t emEt[4320]; //[n]
  Float_t hadEt[4320]; //[n]
  Int_t ieta[4320]; //[n]
  Int_t iphi[4320]; //[n]
  

  /* // List of branches */
  /* TBranch        *b_event;   //! */
  /* TBranch        *b_run;   //! */
  /* TBranch        *b_ecalDetectorMapSize;   //! */
  /* TBranch        *b_ecalCompressedEt;   //! */
  /* TBranch        *b_ecalEt;   //! */
  /* TBranch        *b_ecalEtaIndex;   //! */
  /* TBranch        *b_ecalPhiIndex;   //! */
  /* TBranch        *b_ecalEta;   //! */
  /* TBranch        *b_ecalPhi;   //! */
  /* TBranch        *b_ecalFineGrain;   //! */
  /* TBranch        *b_ecalTag;   //! */
  /* TBranch        *b_hcalDetectorMapSize;   //! */
  /* TBranch        *b_hcalCompressedEt;   //! */
  /* TBranch        *b_hcalEt;   //! */
  /* TBranch        *b_hcalEtaIndex;   //! */
  /* TBranch        *b_hcalPhiIndex;   //! */
  /* TBranch        *b_hcalEta;   //! */
  /* TBranch        *b_hcalPhi;   //! */
  /* TBranch        *b_hcalFineGrain;   //! */
  /* TBranch        *b_hcalTag;   //! */
  /* TBranch        *b_numRegions;   //! */
  /* TBranch        *b_caloRegionEt;   //! */
  /* TBranch        *b_caloRegionTau;   //! */
  /* TBranch        *b_caloRegionEtaIndex;   //! */
  /* TBranch        *b_caloRegionPhiIndex;   //! */
  /* TBranch        *b_caloRegionEta;   //! */
  /* TBranch        *b_caloRegionPhi;   //! */
  /* TBranch        *b_caloRegionTag;   //! */
  /* TBranch        *b_caloRCTRegionEtaIndex;   //! */
  /* TBranch        *b_caloRCTRegionPhiIndex;   //! */
  TBranch *b_n;
  TBranch *b_e;
  TBranch *b_et;
  TBranch *b_eta;
  TBranch *b_phi;
  TBranch *b_emEt;
  TBranch *b_hadEt;
  TBranch *b_ieta;
  TBranch *b_iphi;
  
  RecHitsTree_calib(TFile *f=0);
  virtual ~RecHitsTree_calib();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop(int total_events = 0, 
			bool PHI_AVERAGE = false,
			bool cut_noise_events = false);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  
  
  //! declare the other tree objects
  HltTree        *fhlt;   
  HiTree         *fhiinfo;
  JetTree        *fjet;
  HLTMuTree      *fmu;


};

#endif

#ifdef RecHitsTree_calib_cxx
RecHitsTree_calib::RecHitsTree_calib(TFile *f)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (f == 0) {
    f = new TFile("/mnt/hadoop/cms/store/user/luck/Dijet80_trackingv1_reforest_v2/HiForest_dijet80_trackingv1_all.root");
    //f = new TFile("/net/hidsk0001/d00/scratch/dgulhan/mergedforest/L1jet/HiForestL1-jet_merged_v1.root");
    //f = new TFile("/net/hidsk0001/d00/scratch/dgulhan/mergedforest/central/HiForestL1-centeral_merged_v0.root");
    
    //tree = (TTree*)gDirectory->Get("demo/TriggerPrimitivesTree");
    
  }
  TTree *tree = (TTree*)gDirectory->Get("rechitanalyzer/tower");
  fhlt = new HltTree::HltTree((TTree*)gDirectory->Get("hltanalysis/HltTree"));
  fhiinfo = new HiTree::HiTree((TTree*)gDirectory->Get("hiEvtAnalyzer/HiTree"));
  fjet = new JetTree::JetTree((TTree*)gDirectory->Get("icPu5JetAnalyzer/t"));
  //fhlt = new HltTree::HltTree();
  //fhiinfo = new HiTree::HiTree();
  //fjet = new JetTree::JetTree();
  //fmu = new HLTMuTree::HLTMuTree();  
  
  Init(tree);
}

RecHitsTree_calib::~RecHitsTree_calib()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t RecHitsTree_calib::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t RecHitsTree_calib::LoadTree(Long64_t entry)
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

void RecHitsTree_calib::Init(TTree *tree)
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

  /* fChain->SetBranchAddress("event", &event, &b_event); */
  /* fChain->SetBranchAddress("run", &run, &b_run); */
  /* fChain->SetBranchAddress("ecalDetectorMapSize", &ecalDetectorMapSize, &b_ecalDetectorMapSize); */
  /* fChain->SetBranchAddress("ecalCompressedEt", ecalCompressedEt, &b_ecalCompressedEt); */
  /* fChain->SetBranchAddress("ecalEt", ecalEt, &b_ecalEt); */
  /* fChain->SetBranchAddress("ecalEtaIndex", ecalEtaIndex, &b_ecalEtaIndex); */
  /* fChain->SetBranchAddress("ecalPhiIndex", ecalPhiIndex, &b_ecalPhiIndex); */
  /* fChain->SetBranchAddress("ecalEta", ecalEta, &b_ecalEta); */
  /* fChain->SetBranchAddress("ecalPhi", ecalPhi, &b_ecalPhi); */
  /* fChain->SetBranchAddress("ecalFineGrain", ecalFineGrain, &b_ecalFineGrain); */
  /* fChain->SetBranchAddress("ecalTag", ecalTag, &b_ecalTag); */
  /* fChain->SetBranchAddress("hcalDetectorMapSize", &hcalDetectorMapSize, &b_hcalDetectorMapSize); */
  /* fChain->SetBranchAddress("hcalCompressedEt", hcalCompressedEt, &b_hcalCompressedEt); */
  /* fChain->SetBranchAddress("hcalEt", hcalEt, &b_hcalEt); */
  /* fChain->SetBranchAddress("hcalEtaIndex", hcalEtaIndex, &b_hcalEtaIndex); */
  /* fChain->SetBranchAddress("hcalPhiIndex", hcalPhiIndex, &b_hcalPhiIndex); */
  /* fChain->SetBranchAddress("hcalEta", hcalEta, &b_hcalEta); */
  /* fChain->SetBranchAddress("hcalPhi", hcalPhi, &b_hcalPhi); */
  /* fChain->SetBranchAddress("hcalFineGrain", hcalFineGrain, &b_hcalFineGrain); */
  /* fChain->SetBranchAddress("hcalTag", hcalTag, &b_hcalTag); */
  /* fChain->SetBranchAddress("numRegions", &numRegions, &b_numRegions); */
  /* fChain->SetBranchAddress("caloRegionEt", caloRegionEt, &b_caloRegionEt); */
  /* fChain->SetBranchAddress("caloRegionTau", caloRegionTau, &b_caloRegionTau); */
  /* fChain->SetBranchAddress("caloRegionEtaIndex", caloRegionEtaIndex, &b_caloRegionEtaIndex); */
  /* fChain->SetBranchAddress("caloRegionPhiIndex", caloRegionPhiIndex, &b_caloRegionPhiIndex); */
  /* fChain->SetBranchAddress("caloRegionEta", caloRegionEta, &b_caloRegionEta); */
  /* fChain->SetBranchAddress("caloRegionPhi", caloRegionPhi, &b_caloRegionPhi); */
  /* fChain->SetBranchAddress("caloRegionTag", caloRegionTag, &b_caloRegionTag); */
  /* fChain->SetBranchAddress("caloRCTRegionEtaIndex", caloRCTRegionEtaIndex, &b_caloRCTRegionEtaIndex); */
  /* fChain->SetBranchAddress("caloRCTRegionPhiIndex", caloRCTRegionPhiIndex, &b_caloRCTRegionPhiIndex); */
  fChain->SetBranchAddress("n", &n, &b_n);
  fChain->SetBranchAddress("et", et, &b_et);
  fChain->SetBranchAddress("eta", eta, &b_eta);
  fChain->SetBranchAddress("phi", phi, &b_phi);
  fChain->SetBranchAddress("e", e, &b_e);
  fChain->SetBranchAddress("emEt", emEt, &b_emEt);
  fChain->SetBranchAddress("hadEt", hadEt, &b_hadEt);
  fChain->SetBranchAddress("ieta", ieta, &b_ieta);
  fChain->SetBranchAddress("iphi", iphi, &b_iphi);
  
  Notify();
}

Bool_t RecHitsTree_calib::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void RecHitsTree_calib::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t RecHitsTree_calib::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef RecHitsTree_calib_cxx
