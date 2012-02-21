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
   TFile * inf = TFile::Open("../output-data-Photon-v7-noDuplicate_v26_akPu3PF.root");
   TTree * tgj = (TTree*)inf->Get("tgj");
   
   TCut sel = "(anaEvtSel&&cBin>=0&&cBin<4&&photonEt>60&&sumIsol/0.9<1&&inclJetPt>30&&acos(cos(photonPhi-inclJetPhi))>0.7)";
//   TCut sel = "(anaEvtSel&&cBin>=0&&cBin<4&&photonEt>60&&fisherIsol>0.3&&inclJetPt>30&&acos(cos(photonPhi-inclJetPhi))>0.7)";
   TCut cutSigAll = "acos(cos(photonPhi-inclJetPhi))>7./8*3.1415926&&sigmaIetaIeta<0.01";
   TCut cutBkgDPhi = "acos(cos(photonPhi-inclJetPhi))>0.7&&acos(cos(photonPhi-inclJetPhi))<3.14/2&&sigmaIetaIeta<0.01";
   TCut cutBkgSS = "acos(cos(photonPhi-inclJetPhi))>7./8*3.1415926&&sigmaIetaIeta>0.01&&sigmaIetaIeta<0.017";
   TCut cutBkgSSDPhi = "acos(cos(photonPhi-inclJetPhi))>0.7&&acos(cos(photonPhi-inclJetPhi))<3.14/2&&sigmaIetaIeta>0.01&&sigmaIetaIeta<0.017";
   
   float nSigAll = tgj->Draw("inclJetPt/photonEt",sel&&cutSigAll,"goff");
   float nBkgDPhi = tgj->Draw("inclJetPt/photonEt",sel&&cutBkgDPhi,"goff");
   float nBkgSS = tgj->Draw("inclJetPt/photonEt",sel&&cutBkgSS,"goff");
   float nBkgSSDPhi = tgj->Draw("inclJetPt/photonEt",sel&&cutBkgSSDPhi,"goff");
   
   cout << TString(sel&&cutSigAll) << " " << nSigAll << endl;
   
   TH2D * h = new TH2D("h","",40,0,3.1415926,40,0,0.025);
   tgj->Project("h","sigmaIetaIeta:acos(cos(inclJetPhi-photonPhi))",sel);
   
   TCanvas * c2 = new TCanvas("c2","",500,500);
   c2->SetRightMargin(0.15);
   h->SetTitle(";|#Delta#phi|;#sigma_{#eta#eta}");
   h->SetAxisRange(0.004,0.02,"Y");
   h->Draw("colz");

   TLegend *t2=new TLegend(0.15,0.86,0.35,0.94);
   t2->AddEntry(h,"0-10%","");
   t2->SetFillColor(0);
   t2->SetBorderSize(0);
   t2->SetFillStyle(0);
   t2->SetTextSize(0.04);
   t2->Draw();
   
   TLine * l0 = new TLine(3.1415926*7./8,0.004,3.1415926*7./8,0.02);
   l0->SetLineColor(kRed);
   l0->SetLineStyle(2);
   l0->SetLineWidth(3);
   l0->Draw();
   
//   TLine * l1 = new TLine(*l0);
//   l1->SetX1(0.7); l1->SetX2(0.7);
//   l1->Draw();

//   TLine * l11 = new TLine(*l0);
//   l11->SetX1(3.14159/2); l11->SetX2(3.14159/2);
//   l11->Draw();

   TLine * l2 = new TLine(*l0);
   l2->SetX1(0); l2->SetX2(3.1415926);
   l2->SetY1(0.01); l2->SetY2(0.01);
   l2->Draw();

   TLine * l3 = new TLine(*l2);
   l3->SetY1(0.017); l3->SetY2(0.017);
   l3->Draw();
   
   drawText(Form("%.0f",nSigAll),0.78,0.288);
//   drawText(Form("%.0f",nBkgDPhi),0.4,0.288);
   drawText(Form("%.0f",nBkgSS),0.78,0.62);
//   drawText(Form("%.0f",nBkgSSDPhi),0.4,0.62);
   
//   c2->Print("fig/draw/IllustrateRegions_Isol0.pdf");
//   c2->Print("fig/draw/IllustrateRegions_Isol0.gif");
//   c2->Print("fig/draw/IllustrateRegions_Isol2.pdf");
//   c2->Print("fig/draw/IllustrateRegions_Isol2.gif");
}