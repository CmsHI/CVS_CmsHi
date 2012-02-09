
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
           TString infdataname="../output-pp-photon-7TeV-v4_v24_akPu3PF.root",
           TString infrefname="../output-py7TeV-pho30-v2_v24_akPu3PF.root",
           TString tag="akPu3PF"
//           TString infdataname="../output-pp-photon-7TeV-v4_v24_ak5Calo.root",
//           TString infrefname="../output-py7TeV-pho30-v2_v24_ak5Calo.root",
//           TString tag="ak5Calo"
//           TString infdataname="../output-pp-photon-7TeV-v4_v24_akPu3PF.root",
//           TString infrefname="../output-py7TeV-pho30-v1_v24_akPu3PF.root",
//           TString tag=""
//           TString infdataname="../output-pp-photon-7TeV-v3_v23_akPu3PF.root",
//           TString infrefname="../output-pp-photon-7TeV-v2_v23_akPu3PF.root",
//           TString tag=""
           )
{
   TH1::SetDefaultSumw2();
   
   // inputs
   TFile * infdata = new TFile(infdataname);
   TFile * infref = new TFile(infrefname);
   cout << "compare: " << infdata->GetName() << " " << infref->GetName() << endl;
   
   TTree * tdata = (TTree*)infdata->Get("tgj");
   TTree * tref = (TTree*)infref->Get("tgj");
   
   TCut selPhoSig = "sigmaIetaIeta<0.01&&sumIsol/0.9<1";
   //TCut selref = "offlSel&&photonEt>60&&jetEt>30&&abs(dphi)>3.14159*7./8"&&selPhoSig;
   TCut selref = "photonEt>60&&jetEt>30&&abs(dphi)>3.14159*7./8"&&selPhoSig;
   TCut sel = selref&&"anaEvtSel";
   cout << "compare: " << tdata->GetEntries(sel) << " " << tref->GetEntries(selref) << endl;
   
   
   
   // histograms
   TCanvas * c2 = new TCanvas("c2","c2",700,350);
   c2->Divide(2,1);
   c2->cd(1);
   Compare compx("xjg",tdata,tref,sel,selref,"");
   compx.Init(20,0,2);
   compx.Project("xgj>>");
   //compx.Draw(";x_{J,#gamma} = p_{T}^{J}/p_{T}^{#gamma};Event Fraction",0,0.5,"Iso. #gamma #hat{p}_{T} > 50 GeV/c "+tag,"Iso. #gamma #hat{p}_{T} > 30 GeV/c "+tag,1,0.5,0.8,0.9,0.9);   
   compx.Draw(";x_{J,#gamma} = p_{T}^{J}/p_{T}^{#gamma};Event Fraction",0,0.5,"Data "+tag,"Iso. #gamma #hat{p}_{T} > 30 GeV/c "+tag,1,0.5,0.8,0.9,0.9);
   cout << "Data mean x: " << compx.h1->GetMean() << " +/- " << compx.h1->GetMeanError() << endl;
   cout << "MC mean x  : " << compx.h2->GetMean() << " +/- " << compx.h2->GetMeanError() << endl;
   c2->cd(2);
   TH1D * hXRat = compx.Ratio("Data/Mc");
   hXRat->SetAxisRange(0,2,"Y");
   hXRat->Draw();
//
//   //c2->Print("fig/pp/xjg_"+tag+".gif");
//   //c2->Print("fig/mc/xjg_pthat30_vs_50_photonCut60.gif");
//   c2->Print("fig/pp7TeV/xjg_pp_v2_vs_v3_photonCut60.gif");

   TCanvas * c3 = new TCanvas("c3","c3",700,350);
   c3->Divide(2,1);
   c3->cd(1);
   Compare comppt("pt",tdata,tref,selPhoSig,selPhoSig,"");
   comppt.Init(50,60,200);
   comppt.Project("photonEt>>");
   comppt.Draw(";p_{T}^{#gamma} (GeV/c);count",0,0,"Data "+tag,"Iso. #gamma #hat{p}_{T} > 30 GeV/c "+tag,1,0.5,0.8,0.9,0.9);   
   c3->cd(2);
   TH1D * hPtRat = comppt.Ratio();
   hPtRat->SetAxisRange(0,2,"Y");
   hPtRat->Draw();
}
