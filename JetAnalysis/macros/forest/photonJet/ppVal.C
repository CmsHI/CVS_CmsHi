#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TCut.h"
#include "TLegend.h"
#include "TLine.h"
#include "commonUtility.h"
#include "compare.h"
using namespace std;

void ppVal(
           TString infdataname="../output-pp-photon-7TeV-v2_v23_akPu3PF.root",
           TString infrefname="../output-py7TeV-pho30-v1_v23_akPu3PF.root",
           TString tag="akPu3PF"
//           TString infdataname="../output-pp-photon-7TeV-v2_v23_ak5Calo.root",
//           TString infrefname="../output-py7TeV-pho30-v1_v23_ak5Calo.root",
//           TString tag="ak5Calo"
           )
{
   TH1::SetDefaultSumw2();
   
   // inputs
   TFile * infdata = new TFile(infdataname);
   TFile * infref = new TFile(infrefname);
   cout << "compare: " << infdata->GetName() << " " << infref->GetName() << endl;
   
   TTree * tdata = (TTree*)infdata->Get("tgj");
   TTree * tref = (TTree*)infref->Get("tgj");
   
   TCut selref = "offlSel&&photonEt>60&&sigmaIetaIeta<0.01&&sumIsol/0.9<1&&jetEt>30&&abs(dphi)>3.14159*7./8";
   TCut sel = selref&&"anaEvtSel";
   cout << "compare: " << tdata->GetEntries() << " " << tref->GetEntries() << endl;
   
   
   
   // histograms
   TCanvas * c2 = new TCanvas("c2","c2",700,350);
   c2->Divide(2,1);
   c2->cd(1);
   Compare compx("xjg",tdata,tref,sel,selref,"");
   compx.Init(20,0,2);
   compx.Project("xgj>>");
   compx.Draw(";x_{J,#gamma} = p_{T}^{J}/p_{T}^{#gamma};Event Fraction",0,0.5,"pp 7TeV Data "+tag,"pythia 7TeV "+tag,1,0.5,0.8,0.9,0.9);   
   c2->cd(2);
   TH1D * hXRat = compx.Ratio("Data/Mc");
   hXRat->SetAxisRange(0,2,"Y");
   hXRat->Draw();

   c2->Print("fig/pp7TeV/xjg_"+tag+".gif");
}
