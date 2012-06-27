#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <stdlib.h>
#include "TMath.h"
#include <fstream>
#include <iostream>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TLegend.h>
#include <TLine.h>
#include <TLatex.h>
#include <TProfile.h>

void turnon3(){

TH2* hmb_cent=new TH2D();
TH2* hmb_peri=new TH2D();
TFile *f1 = new TFile("turnoncurve_mb_central.root");
hmb_cent = (TH2*)f1->Get("JetEt_cent");
TFile *f2 = new TFile("turnoncurve_mb_peri.root");
hmb_peri = (TH2*)f2->Get("JetEt_peri");

// TCanvas *c1=new TCanvas("c1","",800,600);
TCanvas *c1=new TCanvas();
TProfile* p1=hmb_cent->ProfileX("p1",0,99);
p1->SetTitle("Tower Level Phi-Ring subtraction, 5% Threshold Et 64");
p1->GetXaxis()->SetTitle("HLT Jet Pt (GeV)");
p1->GetYaxis()->SetTitle("Fraction Accepted");
p1->GetXaxis()->SetLimits(0,200);
p1->GetYaxis()->SetLimits(0,1);
p1->SetLineWidth(3);
// p1->SetMarkerSize(0.85);
p1->SetMarkerStyle(20);
p1->Draw();
TProfile* p2=hmb_peri->ProfileX("p2",0,99);
p2->SetMarkerStyle(24);
// p2->SetMarkerSize(0.85);
p2->SetLineWidth(3);
// p2->Draw();
p2->Draw("Same");
// hmb_peri->Draw();

TLegend leg2(0.65,0.30,0.94,0.55,"");
// TLegend leg2(0.71,0.40,0.94,0.6,"");
leg2.AddEntry(p1,"0-30\% Centrality","p");
leg2.AddEntry(p2,"50-100\% Centrality","p");
leg2.SetFillColor(0);
leg2.SetTextSize(0.035);
leg2.Draw("same");
c1->SaveAs("turnon_centbin.png");
}