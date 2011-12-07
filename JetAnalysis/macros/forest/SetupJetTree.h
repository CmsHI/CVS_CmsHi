//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Dec  7 12:58:41 2011 by ROOT version 5.27/06b
// from TTree t/akPu3PFpatJets Jet Analysis Tree
// found on file: ../HiForestMinBias_v2.root
//////////////////////////////////////////////////////////
#include "commonSetup.h"
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

class Jets {
public :
   Jets(){};
   ~Jets(){};

   // Declaration of leaf types
   Int_t           evt;
   Float_t         b;
   Int_t           nref;
   Float_t         rawpt[174];   //[nref]
   Float_t         jtpt[174];   //[nref]
   Float_t         jteta[174];   //[nref]
   Float_t         jty[174];   //[nref]
   Float_t         jtphi[174];   //[nref]
   Float_t         jtpu[174];   //[nref]
   Float_t         smpt[174];   //[nref]
   Float_t         fr01Chg[174];   //[nref]
   Float_t         fr01EM[174];   //[nref]
   Float_t         fr01[174];   //[nref]

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
   TBranch        *b_smpt;   //!
   TBranch        *b_fr01Chg;   //!
   TBranch        *b_fr01EM;   //!
   TBranch        *b_fr01;   //!

};


void setupJetTree(TTree *t,Jets &tJets,bool doCheck = 0)
{
   // Set branch addresses and branch pointers
   t->SetBranchAddress("evt", &tJets.evt, &tJets.b_evt);
   t->SetBranchAddress("b", &tJets.b, &tJets.b_b);
   t->SetBranchAddress("nref", &tJets.nref, &tJets.b_nref);
   t->SetBranchAddress("rawpt", tJets.rawpt, &tJets.b_rawpt);
   t->SetBranchAddress("jtpt", tJets.jtpt, &tJets.b_jtpt);
   t->SetBranchAddress("jteta", tJets.jteta, &tJets.b_jteta);
   t->SetBranchAddress("jty", tJets.jty, &tJets.b_jty);
   t->SetBranchAddress("jtphi", tJets.jtphi, &tJets.b_jtphi);
   t->SetBranchAddress("jtpu", tJets.jtpu, &tJets.b_jtpu);
   t->SetBranchAddress("smpt", tJets.smpt, &tJets.b_smpt);
   t->SetBranchAddress("fr01Chg", tJets.fr01Chg, &tJets.b_fr01Chg);
   t->SetBranchAddress("fr01EM", tJets.fr01EM, &tJets.b_fr01EM);
   t->SetBranchAddress("fr01", tJets.fr01, &tJets.b_fr01);
   if (doCheck) {
      if (t->GetMaximum("nref")>174) cout <<"FATAL ERROR: Arrary size of nref too small!!!  "<<t->GetMaximum("nref")<<endl;
   }
}

