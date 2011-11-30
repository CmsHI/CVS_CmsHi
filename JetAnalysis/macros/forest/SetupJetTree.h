//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 28 23:45:57 2011 by ROOT version 5.27/06b
// from TTree t/icPu5patJets Jet Analysis Tree
// found on file: ../../ntout/GenHiForest_HyPhton50_all_v2.root
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
   Float_t         hf;
   Int_t           bin;
   Int_t           nref;
   Float_t         rawpt[56];   //[nref]
   Float_t         jtpt[56];   //[nref]
   Float_t         jteta[56];   //[nref]
   Float_t         jty[56];   //[nref]
   Float_t         jtphi[56];   //[nref]
   Float_t         jtpu[56];   //[nref]
   Float_t         pthat;
   Float_t         refpt[56];   //[nref]
   Float_t         refeta[56];   //[nref]
   Float_t         refy[56];   //[nref]
   Float_t         refphi[56];   //[nref]
   Float_t         refdphijt[56];   //[nref]
   Float_t         refdrjt[56];   //[nref]
   Float_t         refparton_pt[56];   //[nref]
   Float_t         refparton_flavor[56];   //[nref]
   Int_t           ngen;
   Int_t           genmatchindex[10];   //[ngen]
   Float_t         genpt[10];   //[ngen]
   Float_t         geneta[10];   //[ngen]
   Float_t         geny[10];   //[ngen]
   Float_t         genphi[10];   //[ngen]
   Float_t         gendphijt[10];   //[ngen]
   Float_t         gendrjt[10];   //[ngen]
   Float_t         smpt[56];   //[nref]

   // List of branches
   TBranch        *b_evt;   //!
   TBranch        *b_b;   //!
   TBranch        *b_hf;   //!
   TBranch        *b_bin;   //!
   TBranch        *b_nref;   //!
   TBranch        *b_rawpt;   //!
   TBranch        *b_jtpt;   //!
   TBranch        *b_jteta;   //!
   TBranch        *b_jty;   //!
   TBranch        *b_jtphi;   //!
   TBranch        *b_jtpu;   //!
   TBranch        *b_pthat;   //!
   TBranch        *b_refpt;   //!
   TBranch        *b_refeta;   //!
   TBranch        *b_refy;   //!
   TBranch        *b_refphi;   //!
   TBranch        *b_refdphijt;   //!
   TBranch        *b_refdrjt;   //!
   TBranch        *b_refparton_pt;   //!
   TBranch        *b_refparton_flavor;   //!
   TBranch        *b_ngen;   //!
   TBranch        *b_genmatchindex;   //!
   TBranch        *b_genpt;   //!
   TBranch        *b_geneta;   //!
   TBranch        *b_geny;   //!
   TBranch        *b_genphi;   //!
   TBranch        *b_gendphijt;   //!
   TBranch        *b_gendrjt;   //!
   TBranch        *b_smpt;   //!

};


void setupJetTree(TTree *t,Jets &tJets,bool doCheck = 0)
{
   // Set branch addresses and branch pointers
   t->SetBranchAddress("evt", &tJets.evt, &tJets.b_evt);
   t->SetBranchAddress("b", &tJets.b, &tJets.b_b);
   t->SetBranchAddress("hf", &tJets.hf, &tJets.b_hf);
   t->SetBranchAddress("bin", &tJets.bin, &tJets.b_bin);
   t->SetBranchAddress("nref", &tJets.nref, &tJets.b_nref);
   t->SetBranchAddress("rawpt", tJets.rawpt, &tJets.b_rawpt);
   t->SetBranchAddress("jtpt", tJets.jtpt, &tJets.b_jtpt);
   t->SetBranchAddress("jteta", tJets.jteta, &tJets.b_jteta);
   t->SetBranchAddress("jty", tJets.jty, &tJets.b_jty);
   t->SetBranchAddress("jtphi", tJets.jtphi, &tJets.b_jtphi);
   t->SetBranchAddress("jtpu", tJets.jtpu, &tJets.b_jtpu);
   t->SetBranchAddress("pthat", &tJets.pthat, &tJets.b_pthat);
   t->SetBranchAddress("refpt", tJets.refpt, &tJets.b_refpt);
   t->SetBranchAddress("refeta", tJets.refeta, &tJets.b_refeta);
   t->SetBranchAddress("refy", tJets.refy, &tJets.b_refy);
   t->SetBranchAddress("refphi", tJets.refphi, &tJets.b_refphi);
   t->SetBranchAddress("refdphijt", tJets.refdphijt, &tJets.b_refdphijt);
   t->SetBranchAddress("refdrjt", tJets.refdrjt, &tJets.b_refdrjt);
   t->SetBranchAddress("refparton_pt", tJets.refparton_pt, &tJets.b_refparton_pt);
   t->SetBranchAddress("refparton_flavor", tJets.refparton_flavor, &tJets.b_refparton_flavor);
   t->SetBranchAddress("ngen", &tJets.ngen, &tJets.b_ngen);
   t->SetBranchAddress("genmatchindex", tJets.genmatchindex, &tJets.b_genmatchindex);
   t->SetBranchAddress("genpt", tJets.genpt, &tJets.b_genpt);
   t->SetBranchAddress("geneta", tJets.geneta, &tJets.b_geneta);
   t->SetBranchAddress("geny", tJets.geny, &tJets.b_geny);
   t->SetBranchAddress("genphi", tJets.genphi, &tJets.b_genphi);
   t->SetBranchAddress("gendphijt", tJets.gendphijt, &tJets.b_gendphijt);
   t->SetBranchAddress("gendrjt", tJets.gendrjt, &tJets.b_gendrjt);
   t->SetBranchAddress("smpt", tJets.smpt, &tJets.b_smpt);
   if (doCheck) {
      if (t->GetMaximum("nref")>56) cout <<"FATAL ERROR: Arrary size of nref too small!!!  "<<t->GetMaximum("nref")<<endl;
      if (t->GetMaximum("ngen")>10) cout <<"FATAL ERROR: Arrary size of ngen too small!!!  "<<t->GetMaximum("ngen")<<endl;
   }
}

