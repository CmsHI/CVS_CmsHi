#include <string>
#include <vector>
#include <iostream>
#include <TH2D.h>
#include <TH1D.h>
#include <TFile.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TTree.h>

#define MAXJETS 100

struct JRA{

  //  unsigned char nref;
  int nref;
  int bin;
  float b;
  float hf;
  float jtpt[MAXJETS];
  float refpt[MAXJETS];
  float jteta[MAXJETS];
  float refeta[MAXJETS];
  float jtphi[MAXJETS];
  float refphi[MAXJETS];
  float jty[MAXJETS];
  float refy[MAXJETS];
  float refdrjt[MAXJETS];

  float weight;
};

void checkWeights(const char* inf = "jra_all.root", const char* outf = "test.root"){

  TFile* infile = new TFile(inf,"read");
  TFile* outFile = new TFile(outf,"recreate");

  TH1::SetDefaultSumw2();
  TH1D* hPT = new TH1D("hPT",";p_{T}^{GenJet}",100,0,200);
  TH1D* hPTnoWeight = new TH1D("hPTnoWeight",";p_{T}^{GenJet}",100,0,200);

  JRA jets_;
  TTree* t= (TTree*)infile->Get("icPu5calo/t");
  t->SetBranchAddress("b",&jets_.b);
  t->SetBranchAddress("hf",&jets_.hf);
  t->SetBranchAddress("nref",&jets_.nref);
  t->SetBranchAddress("jtpt",jets_.jtpt);
  t->SetBranchAddress("refpt",jets_.refpt);
  t->SetBranchAddress("jteta",jets_.jteta);
  t->SetBranchAddress("refeta",jets_.refeta);
  t->SetBranchAddress("jtphi",jets_.jtphi);
  t->SetBranchAddress("refphi",jets_.refphi);
  t->SetBranchAddress("weight",&jets_.weight);
  t->SetBranchAddress("bin",&jets_.bin);

  int nevents = t->GetEntries();

  for(int ie = 0; ie < nevents; ++ie){
    t->GetEntry(ie);
    for(int i = 0; i < jets_.nref; ++i){
      hPT->Fill(jets_.refpt[i],jets_.weight);
      hPTnoWeight->Fill(jets_.refpt[i]);
    }

  }

  new TCanvas();
  hPT->Draw();
  new TCanvas();
  hPTnoWeight->Draw();

  hPT->Write();
  outFile->Write();


}

