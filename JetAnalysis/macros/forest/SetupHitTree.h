//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Nov 27 11:40:13 2011 by ROOT version 5.27/06b
// from TTree hbhe/v1
// found on file: ../HiForestPhoton.root
//////////////////////////////////////////////////////////
#include "commonSetup.h"
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

class Hits {
public :
   Hits(){};
   ~Hits(){};

   // Declaration of leaf types
   Int_t           n;
   Float_t         e[5028];   //[n]
   Float_t         et[5028];   //[n]
   Float_t         eta[5028];   //[n]
   Float_t         phi[5028];   //[n]
   Float_t         perp[5028];   //[n]
   Bool_t          isjet[5028];   //[n]
   Int_t           depth[5028];   //[n]

   // List of branches
   TBranch        *b_n;   //!
   TBranch        *b_e;   //!
   TBranch        *b_et;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_perp;   //!
   TBranch        *b_isjet;   //!
   TBranch        *b_depth;   //!

};


void setupHitTree(TTree *t,Hits &tHits,bool doCheck = 0)
{
   // Set branch addresses and branch pointers
   t->SetBranchAddress("n", &tHits.n, &tHits.b_n);
   t->SetBranchAddress("e", tHits.e, &tHits.b_e);
   t->SetBranchAddress("et", tHits.et, &tHits.b_et);
   t->SetBranchAddress("eta", tHits.eta, &tHits.b_eta);
   t->SetBranchAddress("phi", tHits.phi, &tHits.b_phi);
   t->SetBranchAddress("perp", tHits.perp, &tHits.b_perp);
   t->SetBranchAddress("isjet", tHits.isjet, &tHits.b_isjet);
   t->SetBranchAddress("depth", tHits.depth, &tHits.b_depth);
   if (doCheck) {
      if (t->GetMaximum("n")>5028) cout <<"FATAL ERROR: Arrary size of n too small!!!  "<<t->GetMaximum("n")<<endl;
   }
}

