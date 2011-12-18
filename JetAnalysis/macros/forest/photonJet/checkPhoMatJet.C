#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TCut.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"
#include "TStyle.h"
#include "TProfile.h"
#include "TLine.h"
#include "DrawTick.C"
using namespace std;

void checkPhoMatJet()
{
   TFile * fdata = TFile::Open("../output-data-Photon-v2_v15.root");
   TTree * tdata = (TTree*)fdata->Get("tgj");
   TFile * fhypho = TFile::Open("../output-hypho50v2_yongsun50k_v15_frac62.root");
   TTree * thypho = (TTree*)fhypho->Get("tgj");
   TFile * fhysb = TFile::Open("../output-hypho50mixdj80emdj120em_yongsun_v15.root");
   TTree * thysb = (TTree*)fhysb->Get("tgj");
   TFile * fpp = TFile::Open("../output-data-pp2010-prod3-photon_v10.root");
   TTree * tpp = (TTree*)fpp->Get("tgj");
   
   TProfile * hEtRatData = new TProfile("hEtRatData","",50,0,200);
   TProfile * hEtRatMcBkg = new TProfile("hEtRatMcBkg","",50,0,200);
   
   TCanvas * c0 = new TCanvas("c0","",500,500);
   TString drawvar=Form("(phoMatJetEt/photonEt):photonEt");
   TCut sel="phoMatJetEt>0&&sigmaIetaIeta>0.01&&cBin<12&&(fisherIsol>0.2&&photonEt>60.0)&&(jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2/3.)";
   cout << sel << " " << drawvar << endl;
   tdata->Project("hEtRatData",drawvar,("anaEvtSel"&&sel),"prof");
   thysb->Project("hEtRatMcBkg",drawvar,("offlSel&&sampleWeight<0.5"&&sel),"prof");

   TCanvas * c2 = new TCanvas("c2","",500,500);
   hEtRatData->SetMarkerColor(kRed);
   hEtRatData->SetLineColor(kRed);
   hEtRatMcBkg->SetMarkerStyle(kOpenCircle);
   hEtRatData->SetAxisRange(60,150,"X");
   hEtRatData->SetAxisRange(0,1.8,"Y");
   hEtRatData->SetTitle(";photon candidate E_{T};(matched jet E_{T})/(photon E_{T})");
   hEtRatData->Draw("E");
   hEtRatMcBkg->Draw("sameE");
   
   TLegend *t3=new TLegend(0.2,0.26,0.59,0.5);
   t3->AddEntry(hEtRatData,"0-30%","");
   t3->AddEntry(hEtRatData,"#sigma_{#eta#eta} > 0.011 (Non-Photon Like)","");
   t3->AddEntry(hEtRatData,"Data 2011","p");
   t3->AddEntry(hEtRatMcBkg,"MC Bkg Sample","p");
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->SetFillStyle(0);
   t3->SetTextSize(0.04);
   t3->Draw();

   TLine* pline = new TLine(60,1,150,1);
   pline->SetLineStyle(2);
   pline->Draw();
   
   c2->Print("./fig/12.15smixb/photonMatchedJet_data_vs_mc.gif");
   c2->Print("./fig/12.15smixb/photonMatchedJet_data_vs_mc.pdf");
}