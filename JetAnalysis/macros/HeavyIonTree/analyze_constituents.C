#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TH3F.h"
#include "TProfile.h"
#include "TNtuple.h"
#include "TLegend.h"
#include "TDirectory.h"

#include "TGraphAsymmErrors.h"
#include "CmsHiFunctions.h"

#define MAXPARTICLES 50000
#define MAXJETS 5000
#define MAXCONS 500
#define MAXHITS 5000
#define MAXVTX 100
#define ETABINS 3

using namespace std;


/*
void shiftHistCenter(TH1* h){
  int nbins = h->GetNbinsX();
  for(){


  }
}

*/

int getBin(double input, int size, const double* edges){

  int bin = -9;

  for(int i = 0; i< size; i++){
    double min = edges[i];

    if(input >= min) bin  = i;
    if(input < min ) break;
  }

  if(bin < 0) cout<<"Warning : Bin not determined correctly - "<<bin<<endl;
  return bin;
}

struct Event{

  int event;
  float b;
  float npart;
  float ncoll;
  float nhard;

  int n[ETABINS];
  float ptav[ETABINS];

  int algos;

  float vx;
  float vy;
  float vz;
  float vr;



};

struct Particles{

  int np;
  float pt[MAXPARTICLES];
  float eta[MAXPARTICLES];
  float phi[MAXPARTICLES];
  int pdg[MAXPARTICLES];
  int chg[MAXPARTICLES];

};

struct Jets{

  int njet;

  float et[MAXJETS];
  float eta[MAXJETS];
  float phi[MAXJETS];
  float area[MAXJETS];

  float r20[MAXJETS];
  float r50[MAXJETS];
  float r90[MAXJETS];

  int ncons[MAXJETS];

};


struct Constituents{

  float etjet;
  float etajet;
  float phijet;
  float area;

  float et[MAXCONS];
  float eta[MAXCONS];
  float phi[MAXCONS];
  float dr[MAXCONS];

  float r20;
  float r50;
  float r90;

  float e02;
  float e04;

  int ncons;

};


void analyze_constituents(char * infile = "/home/yilmaz/analysis/jets/4TeV/corrected/pythia_dijet_pt80to120_hydjet_mb_4TeV_d20090615/run2/pre.root"){
//void analyze_constituents(char * infile = "/home/yilmaz/analysis/jets/4TeV/corrected/pythia_dijet_pt80to120_hydjet_mb_4TeV_d20090612/jet234.root"){
//void analyze_constituents(char * infile = "/home/yilmaz/analysis/jets/4TeV/corrected/pythia_dijet_pt80to120_hydjet_mb_4TeV_d20090612/jet234.root"){

  double match = 0.15;
  double genJetEt = 20;

  TH1::SetDefaultSumw2();

  TFile* inf = new TFile(infile);
  TTree* tcon = dynamic_cast<TTree*>(inf->Get("genevent/jet"));
  TTree* tgen = dynamic_cast<TTree*>(inf->Get("genevent/hi"));

  TTree* treco = dynamic_cast<TTree*>(inf->Get("recoevent/hi"));

  const int nbBins = 10;
  const int nEtBins = 13;
  const int nEtaBins = 3;

  int color[17] = {1,1,4,2,2,4,4,2,2,1,1,1,2,1,1,4,4};

  int etStep = 3;
  int bStep = 2;

  int bBegin = 0;
  int etBegin = 5;

  double bBins[nbBins + 1] = {0,5.045,7.145,8.755,10.105,11.294,12.373,13.359,14.283,15.202,18};
  double etBins[nEtBins + 1] = {0,20,30,40,45,50,55,60,65,70,75,80,100,200};
  double etaBins[nEtaBins + 1] = {0,1.3,3,5.2};

  const char* det[nEtaBins] = {"Barrel","Endcap","Forward"};

  TH1D* hDR = new TH1D("hDR",";#Delta R;jet-particles",100,0,1);
  TH2D* hEtDR = new TH2D("hEtDR","#Delta R vs Particle E_{T};E_{T}^{GenParticle};#Delta R",100,0,100,100,0,1);
  //  TH2D* hEtDR = new TH2D("hEtDR","#Delta R vs Jet E_{T};E_{T}^{GenJet};#Delta R",100,0,200,100,0,1);

  TH1D* hE02 = new TH1D("hE02",";E_{T} fraction in cone;jets",100,0,1.05);
  TH1D* hE04 = new TH1D("hE04",";E_{T} fraction in cone;jets",100,0,1.05);

  TH1D* hR50 = new TH1D("hR50",";Radius of Fraction of E_{T};jets",100,0,.65);
  TH1D* hR90 = new TH1D("hR90",";Radius of Fraction of E_{T};jets",100,0,.65);

  Constituents cons;
  Jets gen;

  tgen->SetBranchAddress("r50",gen.r50);
  tgen->SetBranchAddress("r90",gen.r90);
  tgen->SetBranchAddress("njet",&gen.njet);
  tgen->SetBranchAddress("et",gen.et);

  tcon->SetBranchAddress("ncons",&cons.ncons);
  tcon->SetBranchAddress("et",cons.et);
  tcon->SetBranchAddress("eta",cons.eta);
  tcon->SetBranchAddress("phi",cons.phi);
  tcon->SetBranchAddress("dr",cons.dr);

  tcon->SetBranchAddress("etjet",&cons.etjet);
  tcon->SetBranchAddress("etajet",&cons.etajet);
  tcon->SetBranchAddress("phijet",&cons.phijet);

  tcon->SetBranchAddress("e02",&cons.e02);
  tcon->SetBranchAddress("e04",&cons.e04);
  tcon->SetBranchAddress("r50",&cons.r50);
  tcon->SetBranchAddress("r90",&cons.r90);

  // Jet Loop
  int njets = tcon->GetEntries();
  cout<<"Number of Jets : "<<njets<<endl;
  for(int i = 0; i< njets; ++i){
    tcon->GetEntry(i);

    if(fabs(cons.etajet) > 5) continue;
    if(cons.etjet < 20) continue;

    hE02->Fill(cons.e02);
    hE04->Fill(cons.e04);

    for(int j = 0; j < cons.ncons; ++j){

      //      if(ncons < 2) continue;

      double dr = deltaR(cons.eta[j],cons.phi[j],cons.etajet,cons.phijet);
      hDR->Fill(dr);
      hEtDR->Fill(cons.et[j],dr);
      //      hEtDR->Fill(cons.etjet,dr);

    }
  }

  int nevents = tgen->GetEntries();
  for(int i = 0; i< nevents; ++i){
    tgen->GetEntry(i);

    for(int j = 0; j < gen.njet; ++j){
      if(gen.et[j] < 20) continue;
      hR50->Fill(gen.r50[j]);
      hR90->Fill(gen.r90[j]);
    }

  }


  hR90->SetLineColor(2);

  hE02->SetLineColor(2);

  TLegend *leg1 = new TLegend(0.29,0.61,0.82,0.88,NULL,"brNDC");
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.04);
  leg1->SetBorderSize(0);
  leg1->AddEntry(hR50,"Radius of 50% of Jet E_{T}","L");
  leg1->AddEntry(hR90,"Radius of 90% of Jet E_{T}","L");
  
  TLegend *leg2 = new TLegend(0.29,0.61,0.82,0.88,NULL,"brNDC");
  leg2->SetFillColor(0);
  leg2->SetTextSize(0.04);
  leg2->SetBorderSize(0);
  leg2->AddEntry(hE02,"Energy Fraction in #Delta R < 0.2","L");
  leg2->AddEntry(hE04,"Energy Fraction in #Delta R < 0.4","L");
  
  TCanvas* c1 = new TCanvas("c1","c1",400,400);
  hDR->Draw();

  TCanvas* c2 = new TCanvas("c2","c2",400,400);
  hEtDR->Draw("colz");

  TCanvas* c3 = new TCanvas("c3","c3",400,400);
  hR50->Draw("hist");
  hR90->Draw("hist same");
  leg1->Draw();
  c3->Print("Energy_shape.gif");

  TCanvas* c4 = new TCanvas("c4","c4",400,400);
  hE04->Draw("hist");
  hE02->Draw("hist same");
  leg2->Draw();
  c4->Print("Energy_radius.gif");

}
