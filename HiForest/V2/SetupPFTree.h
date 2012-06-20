//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun 20 12:21:51 2012 by ROOT version 5.27/06b
// from TTree pfTree/dijet tree
// found on file: ../Pythia30_HydjetDrum_mix01_HiForest2_v19.root
//////////////////////////////////////////////////////////
#include "commonSetup.h"
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

class PFs {
public :
   PFs(){};
   ~PFs(){};

   // Declaration of leaf types
   Int_t           nPFpart;
   Int_t           pfId[10352];   //[nPFpart]
   Float_t         pfPt[10352];   //[nPFpart]
   Float_t         pfEta[10352];   //[nPFpart]
   Float_t         pfPhi[10352];   //[nPFpart]

   // List of branches
   TBranch        *b_nPFpart;   //!
   TBranch        *b_pfId;   //!
   TBranch        *b_pfPt;   //!
   TBranch        *b_pfEta;   //!
   TBranch        *b_pfPhi;   //!

};


void setupPFTree(TTree *t,PFs &tPFs,bool doCheck = 1)
{
   // Set branch addresses and branch pointers
   if (t->GetBranch("nPFpart")) t->SetBranchAddress("nPFpart", &tPFs.nPFpart, &tPFs.b_nPFpart);
   if (t->GetBranch("pfId")) t->SetBranchAddress("pfId", tPFs.pfId, &tPFs.b_pfId);
   if (t->GetBranch("pfPt")) t->SetBranchAddress("pfPt", tPFs.pfPt, &tPFs.b_pfPt);
   if (t->GetBranch("pfEta")) t->SetBranchAddress("pfEta", tPFs.pfEta, &tPFs.b_pfEta);
   if (t->GetBranch("pfPhi")) t->SetBranchAddress("pfPhi", tPFs.pfPhi, &tPFs.b_pfPhi);
   if (doCheck) {
      if (t->GetMaximum("nPFpart")>10402) cout <<"FATAL ERROR: Arrary size of nPFpart too small!!!  "<<t->GetMaximum("nPFpart")<<endl;
   }
}

