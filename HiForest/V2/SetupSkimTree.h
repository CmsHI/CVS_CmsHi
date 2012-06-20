//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun 20 11:30:51 2012 by ROOT version 5.27/06b
// from TTree HltTree/
// found on file: ../Pythia30_HydjetDrum_mix01_HiForest2_v19.root
//////////////////////////////////////////////////////////
#include "commonSetup.h"
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

class Skims {
public :
   Skims(){};
   ~Skims(){};

   // Declaration of leaf types
   Int_t           L1simulation_step;
   Int_t           reco_extra;
   Int_t           reco_extra_jet;
   Int_t           gen_step;
   Int_t           pat_step;
   Int_t           extrapatstep;
   Int_t           ana_step;
   Int_t           phltJetHI;
   Int_t           pcollisionEventSelection;
   Int_t           pHBHENoiseFilter;
   Int_t           phiEcalRecHitSpikeFilter;
   Int_t           phfCoincFilter;
   Int_t           ppurityFractionFilter;

   // List of branches
   TBranch        *b_L1simulation_step;   //!
   TBranch        *b_reco_extra;   //!
   TBranch        *b_reco_extra_jet;   //!
   TBranch        *b_gen_step;   //!
   TBranch        *b_pat_step;   //!
   TBranch        *b_extrapatstep;   //!
   TBranch        *b_ana_step;   //!
   TBranch        *b_phltJetHI;   //!
   TBranch        *b_pcollisionEventSelection;   //!
   TBranch        *b_pHBHENoiseFilter;   //!
   TBranch        *b_phiEcalRecHitSpikeFilter;   //!
   TBranch        *b_phfCoincFilter;   //!
   TBranch        *b_ppurityFractionFilter;   //!

};


void setupSkimTree(TTree *t,Skims &tSkims,bool doCheck = 0)
{
   // Set branch addresses and branch pointers
   t->SetBranchAddress("L1simulation_step", &tSkims.L1simulation_step, &tSkims.b_L1simulation_step);
   t->SetBranchAddress("reco_extra", &tSkims.reco_extra, &tSkims.b_reco_extra);
   t->SetBranchAddress("reco_extra_jet", &tSkims.reco_extra_jet, &tSkims.b_reco_extra_jet);
   t->SetBranchAddress("gen_step", &tSkims.gen_step, &tSkims.b_gen_step);
   t->SetBranchAddress("pat_step", &tSkims.pat_step, &tSkims.b_pat_step);
   t->SetBranchAddress("extrapatstep", &tSkims.extrapatstep, &tSkims.b_extrapatstep);
   t->SetBranchAddress("ana_step", &tSkims.ana_step, &tSkims.b_ana_step);
   t->SetBranchAddress("phltJetHI", &tSkims.phltJetHI, &tSkims.b_phltJetHI);
   t->SetBranchAddress("pcollisionEventSelection", &tSkims.pcollisionEventSelection, &tSkims.b_pcollisionEventSelection);
   t->SetBranchAddress("pHBHENoiseFilter", &tSkims.pHBHENoiseFilter, &tSkims.b_pHBHENoiseFilter);
   t->SetBranchAddress("phiEcalRecHitSpikeFilter", &tSkims.phiEcalRecHitSpikeFilter, &tSkims.b_phiEcalRecHitSpikeFilter);
   t->SetBranchAddress("phfCoincFilter", &tSkims.phfCoincFilter, &tSkims.b_phfCoincFilter);
   t->SetBranchAddress("ppurityFractionFilter", &tSkims.ppurityFractionFilter, &tSkims.b_ppurityFractionFilter);
   if (doCheck) {
   }
}

