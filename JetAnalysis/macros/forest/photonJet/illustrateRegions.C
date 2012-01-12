#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TString.h"
#include "TLine.h"
#include "TLegend.h"
#include <iostream>
#include "commonUtility.h"
using namespace std;

void illustrateRegions(){
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);

   TH1::SetDefaultSumw2();
   TFile * inf = TFile::Open("../output-data-Photon-v7_v19.root");
   TTree * tgj = (TTree*)inf->Get("tgj");
   
   //TCut sel = "(anaEvtSel&&cBin>=0&&cBin<4&&photonEt>60&&jetEt>30&&fisherIsol>0.3)";
   TCut sel = "(anaEvtSel&&cBin>=0&&cBin<4&&photonEt>60&&jetEt>30&&sumIsol/0.9<1)";
   TCut cutSigAll = "acos(cos(photonPhi-jetPhi))>2.0944&&sigmaIetaIeta<0.01";
   TCut cutBkgDPhi = "acos(cos(photonPhi-jetPhi))>0.7&&acos(cos(photonPhi-jetPhi))<3.14/2&&sigmaIetaIeta<0.01";
   TCut cutBkgSS = "acos(cos(photonPhi-jetPhi))>2.0944&&sigmaIetaIeta>0.01&&sigmaIetaIeta<0.017";
   TCut cutBkgSSDPhi = "acos(cos(photonPhi-jetPhi))>0.7&&acos(cos(photonPhi-jetPhi))<3.14/2&&sigmaIetaIeta>0.01&&sigmaIetaIeta<0.017";
   
   float nSigAll = tgj->GetEntries(sel&&cutSigAll);
   float nBkgDPhi = tgj->GetEntries(sel&&cutBkgDPhi);
   float nBkgSS = tgj->GetEntries(sel&&cutBkgSS);
   float nBkgSSDPhi = tgj->GetEntries(sel&&cutBkgSSDPhi);
   
   TH2D * h = new TH2D("h","",40,0,3.1415926,40,0,0.025);
   tgj->Project("h","sigmaIetaIeta:acos(cos(jetPhi-photonPhi))",sel);
   
   TCanvas * c2 = new TCanvas("c2","",500,500);
   c2->SetRightMargin(0.15);
   h->SetTitle(";|#Delta#phi|;#sigma_{#eta#eta}");
   h->SetAxisRange(0.004,0.02,"Y");
   h->Draw("colz");

   TLegend *t2=new TLegend(0.31,0.15,0.59,0.29);
   t2->AddEntry(h,"0-10%","");
   t2->SetFillColor(0);
   t2->SetBorderSize(0);
   t2->SetFillStyle(0);
   t2->SetTextSize(0.04);
   t2->Draw();
   
   TLine * l0 = new TLine(2.0944,0.004,2.0944,0.02);
   l0->SetLineColor(kRed);
   l0->SetLineStyle(2);
   l0->SetLineWidth(3);
   l0->Draw();
   
   TLine * l1 = new TLine(*l0);
   l1->SetX1(0.7); l1->SetX2(0.7);
   l1->Draw();

   TLine * l2 = new TLine(*l0);
   l2->SetX1(0); l2->SetX2(3.1415926);
   l2->SetY1(0.01); l2->SetY2(0.01);
   l2->Draw();

   TLine * l3 = new TLine(*l2);
   l3->SetY1(0.017); l3->SetY2(0.017);
   l3->Draw();
   
   drawText(Form("%.0f",nSigAll),0.685,0.288);
   drawText(Form("%.0f",nBkgDPhi),0.48,0.288);
   drawText(Form("%.0f",nBkgSS),0.71,0.62);
   drawText(Form("%.0f",nBkgSSDPhi),0.48,0.62);
}