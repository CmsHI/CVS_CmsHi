#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TMath.h"
#include "TF1.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"
#include "TChain.h"

#include "TCut.h"
#include "TNtuple.h"

#include "THStack.h"

using namespace std;

static bool subtract = 0;
static int QID = 3;

static TString weightString;

static bool normLead = 0;

static int mixColor = 2;
static int dataColor = 1;
static int ppColor = 4;

static int centralBin = 8;
static int leadCut = 120;
static int subleadCut = 30;

static double sideMin = 0.1;
static double sideMax = TMath::Pi()/3 + 0.1;

static double sideCorrect = 1;

static const char* LUM = "#int L dt=150";

static bool plotSubtraction = 0;

static bool reweightCentrality = 1;

static const double pi = TMath::Pi();


TCut weightSample(
		  bool mix = 1,
		  bool PbPb2011 = 0
		  ){


  TH1::SetDefaultSumw2();
  bool validate = 1;
  //  validate = 0;

  double xs15 = 2.03E-01 * 1000000;
  double xs30 = 1.079E-02 * 1000000;
  double xs50 = 1.021E-03 * 1000000;
  double xs80 = 9.913E-05 * 1000000;
  double xs100 = 3.069E-05 * 1000000;
  double xs120 = 1.128E-05 * 1000000;
  double xs170 = 1.470E-06 * 1000000;
  double xs200 = 5.310E-07 * 1000000;
  double xs250 = 1.192E-07 * 1000000;
  double xs300 = 3.176E-08 * 1000000;

  if(PbPb2011){
    xs15 = 2.03E-01 * 1000000;
    xs30 = 1.079E-02 * 1000000;
    xs50 = 1.021E-03 * 1000000;
    xs80 = 9.913E-05 * 1000000;
    xs100 = 3.069E-05 * 1000000;
    xs120 = 1.128E-05 * 1000000;
    xs170 = 1.470E-06 * 1000000;
    xs200 = 5.310E-07 * 1000000;
    xs250 = 1.192E-07 * 1000000;
    xs300 = 3.176E-08 * 1000000;
  }

  xs15  -= xs30;
  xs30  -= xs50;
  xs50  -= xs80;
  xs80  -= xs100;
  xs100 -= xs120;
  xs120 -= xs170;
  xs170 -= xs200;
  xs200 -= xs250;
  xs250 -= xs300;

  TChain* nt;
  TFile* outf;
  if(mix){
    if(PbPb2011){
      outf = new TFile("weights_hydjet.root","recreate");
      nt = new TChain("ntevt");
    }else{
      outf = new TFile("weights_hijing.root","recreate");
      if(0){
	nt = new TChain("ak5PFJetAnalyzer/t");
      }else{
	nt = new TChain("ntevt");
      }
    }
  }else{
    outf = new TFile("weights_signal.root","recreate");
    nt = new TChain("ak5PFJetAnalyzer/t");
  }

  TNtuple* ntw = new TNtuple("ntw","","weight:ptweight:cweight:varpthat");

  float varpthat, varbin;
  //  TNtuple* nt = (TNtuple*)(new TFile("mix.root"))->Get("nt");


  int pthats[] = {15,30,50,80,120,170};

  if(PbPb2011){
    nt->AddFile("mix_hydjet.root");
  }else{

    if(0){
      for(int ip = 0; ip < 6; ++ip){
	int forestversion = 2;
	if(ip  >= 5) forestversion = 1;	
	if(mix){	  
	  nt->AddFile(Form("root://eoscms//eos/cms/store/caf/user/dgulhan/pPb/HP03/prod09/Hijing_Pythia_pt%d/HiForest_v55_v04_merged01/pt%d_HP03_prod09_merged_forest_0.root",pthats[ip],pthats[ip]));	  	  
	}else{      
	  forestversion =1;
	  nt->AddFile(Form("root://eoscms//eos/cms/store/caf/user/dgulhan/pPb_A03/Signal_Pythia%d/JEC_merged02/merged_forest_0.root",pthats[ip]));      
	}	
      }
    }else{
      nt->AddFile("mix_hijing.root");
    }

  }
    
  nt->SetBranchAddress("pthat",&varpthat);
  if(0){
    nt->SetBranchAddress("bin",&varbin);
  }else{
    varbin = 0;
  }

  int nev= 0, nev15, nev30 = 0, nev50 = 0, nev80 = 0, nev100 = 0, nev120 = 0, nev170 = 0, nev200 = 0, nev250 = 0, nev300 = 0;
  int n = 0, n15, n30 = 0, n50 = 0, n80 = 0, n100 = 0, n120 = 0, n170 = 0, n200 = 0, n250 = 0, n300 = 0;

  nev = nt->GetEntries();

  TCut pthat15("pthat >= 15 && pthat < 30");
  TCut pthat30("pthat >= 30 && pthat < 50");
  TCut pthat50("pthat >= 50 && pthat < 80");
  TCut pthat80("pthat >= 80 && pthat < 100");
  TCut pthat100("pthat >= 100 && pthat < 120");
  TCut pthat120("pthat >= 120 && pthat < 170");
  TCut pthat170("pthat >= 170 && pthat < 200");
  TCut pthat200("pthat >= 200 && pthat < 250");
  TCut pthat250("pthat >= 250 && pthat < 300");
  TCut pthat300("pthat >= 300");

  n = nev;
  n15 = nt->GetEntries(pthat15);
  n30 = nt->GetEntries(pthat30);
  n50 = nt->GetEntries(pthat50);
  n80 = nt->GetEntries(pthat80);
  n120 = nt->GetEntries(pthat120);
  n100 = nt->GetEntries(pthat100);
  n170 = nt->GetEntries(pthat170);
  n200 = nt->GetEntries(pthat200);
  n250 = nt->GetEntries(pthat250);
  n300 = nt->GetEntries(pthat300);

  TCut w15(Form("%f/%d",xs15,n15));
  TCut w30(Form("%f/%d",xs30,n30));
  TCut w50(Form("%f/%d",xs50,n50));
  TCut w80(Form("%f/%d",xs80,n80));
  TCut w100(Form("%f/%d",xs100,n100));
  TCut w120(Form("%f/%d",xs120,n120));
  TCut w170(Form("%f/%d",xs170,n170));
  TCut w200(Form("%f/%d",xs200,n200));
  TCut w250(Form("%f/%d",xs250,n250));
  TCut w300(Form("%f/%d",xs300,n300));

  w15 = w15*(pthat15);
  w30 = w30*(pthat30);
  w50 = w50*(pthat50);
  w80 = w80*(pthat80);
  w100 = w100*(pthat100);
  w120 = w120*(pthat120);
  w170 = w170*(pthat170);
  w200 = w200*(pthat200);
  w250 = w250*(pthat250);
  w300 = w300*(pthat300);

  for(int ie = 0; ie < nt->GetEntries(); ++ie){
    nt->GetEntry(ie);
    double pthatweight = 0;
    if(n15 > 0 && varpthat >= 15) pthatweight = xs15/n15;
    if(n30 > 0 && varpthat >= 30) pthatweight = xs30/n30;
    if(n50 > 0 && varpthat >= 50) pthatweight = xs50/n50;
    if(n80 > 0 && varpthat >= 80) pthatweight = xs80/n80;
    if(n100 > 0 && varpthat >= 100) pthatweight = xs100/n100;
    if(n120 > 0 && varpthat >= 120) pthatweight = xs120/n120;
    if(n170 > 0 && varpthat >= 170) pthatweight = xs170/n170;
    if(n200 > 0 && varpthat >= 200) pthatweight = xs200/n200;
    if(n250 > 0 && varpthat >= 250) pthatweight = xs250/n250;
    if(n300 > 0 && varpthat >= 300) pthatweight = xs300/n300;

    //    cout<<"pthat : "<<varpthat<<"  weight : "<<pthatweight<<endl;

    double cweight = exp(-  pow(varbin+1.11957e+01,2)  /    pow(1.34120e+01,2) / 2);
    ntw->Fill(pthatweight*cweight,pthatweight,cweight,varpthat);
  }

  TCut weight(Form("%s + %s + %s + %s",(const char*)w80,(const char*)w120,(const char*)w170,(const char*)w200));

  if(reweightCentrality) weight = Form("(%s)*%s",(const char*)weight,
				       "exp(-  pow(bin+1.11957e+01,2)  /    pow(1.34120e+01,2) / 2)");
  
  if(validate){

    TCanvas* c1 = new TCanvas("c1","",600,600);
    TH1D* hMix = new TH1D("hMix",";p_{T}^{Leading RecoJet};",120,0,600);

  cout<<"Entries : "<<nt->GetEntries(weight)<<endl;
  nt->Draw("pt1>>hMix",weight);

  THStack* h = new THStack("h",";p_{T}^{Leading RecoJet}; Weighted Entries");
  TH1D* h80 = new TH1D("h80",";p_{T}^{Leading RecoJet};",380,120,600);
  TH1D* h120 = new TH1D("h120",";p_{T}^{Leading RecoJet};",380,120,600);
  TH1D* h170 = new TH1D("h170",";p_{T}^{Leading RecoJet};",380,120,600);
  TH1D* h200 = new TH1D("h200",";p_{T}^{Leading RecoJet};",380,120,600);

  c1->SetLogy();
  //  hMix->SetAxisRange(120,500);
  //  hMix->SetMinimum(0.00001);
  hMix->Draw();

  TCanvas* c2 = new TCanvas("c2","",600,600);
  c2->SetLogy();
  nt->Draw("pt1>>h80",w80);
  nt->Draw("pt1>>h120",w120);
  nt->Draw("pt1>>h170",w170);
  nt->Draw("pt1>>h200",w200);

  h80->Rebin(5);
  h120->Rebin(5);
  h170->Rebin(5);
  h200->Rebin(5);

  h80->SetFillColor(12);
  h120->SetFillColor(4);
  h170->SetFillColor(5);
  h200->SetFillColor(2);

  h80->SetFillStyle(1);
  h120->SetFillStyle(1);
  h170->SetFillStyle(1);
  h200->SetFillStyle(1);

  h->Add(h80);
  h->Add(h120);
  h->Add(h170);
  h->Add(h200);

  h->Draw("hist");

  weightString = TString((const char*)weight);
  new TCanvas();

  nt->Draw("bin",weightString.Data());

  new TCanvas();


  TF1* f = new TF1("f","exp(-  pow(x+1.11957e+01,2)  /    pow(1.34120e+01,2) / 2)",0,40);
  f->Draw();

  }

  outf->cd();
  ntw->Write();
  outf->Write();

  cout<<(const char*)weight<<endl;
  weightString = TString((const char*)weight);


  return weight;
}

void weightMix(){

  //  weightSample(1,0);
  weightSample(1,1);

}

