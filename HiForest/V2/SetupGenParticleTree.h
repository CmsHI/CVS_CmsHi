//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jul  8 19:41:41 2012 by ROOT version 5.27/06b
// from TTree photon/Tree of Rechits around photon
// found on file: /d102/yjlee/hiForest2MC/Pythia80_HydjetDrum_mix01_HiForest2_v20.root
//////////////////////////////////////////////////////////
#include "commonSetup.h"
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

class GenParticles {
public :
   GenParticles(){};
   ~GenParticles(){};

   // Declaration of leaf types
   Int_t           cBin;
   Float_t         hf;
   Int_t           nPar;
   Float_t         recoVtxZ;
   Float_t         et[372];   //[nPar]
   Float_t         eta[372];   //[nPar]
   Float_t         phi[372];   //[nPar]
   Int_t           id[372];   //[nPar]
   Int_t           momId[372];   //[nPar]
   Int_t           status[372];   //[nPar]
   Int_t           collId[372];   //[nPar]

   // List of branches
   TBranch        *b_cBin;   //!
   TBranch        *b_hf;   //!
   TBranch        *b_nPar;   //!
   TBranch        *b_recoVtxZ;   //!
   TBranch        *b_et;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_id;   //!
   TBranch        *b_momId;   //!
   TBranch        *b_status;   //!
   TBranch        *b_collId;   //!

};


void setupGenParticleTree(TTree *t,GenParticles &tGenParticles,bool doCheck = 1)
{
   // Set branch addresses and branch pointers
   if (t->GetBranch("cBin")) t->SetBranchAddress("cBin", &tGenParticles.cBin, &tGenParticles.b_cBin);
   if (t->GetBranch("hf")) t->SetBranchAddress("hf", &tGenParticles.hf, &tGenParticles.b_hf);
   if (t->GetBranch("nPar")) t->SetBranchAddress("nPar", &tGenParticles.nPar, &tGenParticles.b_nPar);
   if (t->GetBranch("recoVtxZ")) t->SetBranchAddress("recoVtxZ", &tGenParticles.recoVtxZ, &tGenParticles.b_recoVtxZ);
   if (t->GetBranch("et")) t->SetBranchAddress("et", tGenParticles.et, &tGenParticles.b_et);
   if (t->GetBranch("eta")) t->SetBranchAddress("eta", tGenParticles.eta, &tGenParticles.b_eta);
   if (t->GetBranch("phi")) t->SetBranchAddress("phi", tGenParticles.phi, &tGenParticles.b_phi);
   if (t->GetBranch("id")) t->SetBranchAddress("id", tGenParticles.id, &tGenParticles.b_id);
   if (t->GetBranch("momId")) t->SetBranchAddress("momId", tGenParticles.momId, &tGenParticles.b_momId);
   if (t->GetBranch("status")) t->SetBranchAddress("status", tGenParticles.status, &tGenParticles.b_status);
   if (t->GetBranch("collId")) t->SetBranchAddress("collId", tGenParticles.collId, &tGenParticles.b_collId);
   if (doCheck) {
      if (t->GetMaximum("nPar")>372) { cout <<"FATAL ERROR: Arrary size of nPar too small!!!  "<<t->GetMaximum("nPar")<<endl; exit(0);
 }   }
}

