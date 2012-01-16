#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TString.h"
#include "TLine.h"
#include "TLegend.h"
#include <iostream>
#include "commonUtility.h"
using namespace std;

void illustrateDPhi(){
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);

   TH1::SetDefaultSumw2();
   TFile * inf = TFile::Open("../output-data-Photon-v7_v19.root");
   TTree * tgj = (TTree*)inf->Get("tgj");
   
   TCut sel = "(anaEvtSel&&cBin>=0&&cBin<4&&photonEt>60&&jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7 && sigmaIetaIeta<0.01 && fisherIsol>0.3)";
   
   TH1D * hDPhi = new TH1D("hDPhi","",20,0,3.1415926);
   tgj->Project("hDPhi","acos(cos(jetPhi-photonPhi))",sel);
   
   TCanvas * c2 = new TCanvas("c2","",500,500);
   c2->SetLogy();
   hDPhi->SetTitle(";|#Delta#phi|;Entries");
   hDPhi->Draw();
   
   TF1 * p0 = new TF1("p0","pol0",0.7,3.14);
   hDPhi->Fit("p0","0","",0.7,3.14/2);
   p0->Draw("same");

   TLegend *t2=new TLegend(0.23,0.68,0.62,0.90);
   t2->AddEntry(hDPhi,"0-10%","");
   t2->SetFillColor(0);
   t2->SetBorderSize(0);
   t2->SetFillStyle(0);
   t2->SetTextSize(0.04);
   t2->Draw();
}