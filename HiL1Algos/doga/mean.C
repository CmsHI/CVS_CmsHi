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

void mean(){
TH2D* hmb=new TH2D();
TH2D* hmb2=new TH2D();
TH2D* hcent=new TH2D();
TH2D* hcent2=new TH2D();
TH2D* hjet=new TH2D();
TH2D* hjet2=new TH2D();

TFile *f1 = new TFile("Mean.root");
hmb = (TH2D*)f1->Get("MeanEtMB");
TFile *f2 = new TFile("Meancent.root");
hcent = (TH2D*)f2->Get("MeanEtCent");
TFile *f3 = new TFile("Meanjet.root");
hjet = (TH2D*)f3->Get("MeanEtJet");
TFile *f4 = new TFile("Meanmbz.root");
hmb2 = (TH2D*)f4->Get("MeanEtMB_z");
TFile *f5 = new TFile("Meancentz.root");
hcent2 = (TH2D*)f5->Get("MeanEtCent_z");
TFile *f6 = new TFile("Meanjetz.root");
hjet2 = (TH2D*)f6->Get("MeanEtJet_z");

hmb->SetStats(0);    
hmb->GetXaxis()->CenterTitle();
hmb->GetYaxis()->CenterTitle();
hjet->SetStats(0);
hjet->GetXaxis()->CenterTitle();
hjet->GetYaxis()->CenterTitle();
hcent->SetStats(0);
hcent->GetXaxis()->CenterTitle();
hcent->GetYaxis()->CenterTitle();
hmb2->SetStats(0);
hmb2->GetXaxis()->CenterTitle();
hmb2->GetYaxis()->CenterTitle();
hjet2->SetStats(0);
hjet2->GetXaxis()->CenterTitle();
hjet2->GetYaxis()->CenterTitle();
hcent2->SetStats(0);
hcent2->GetXaxis()->CenterTitle();
hcent2->GetYaxis()->CenterTitle();


TCanvas *c1=new TCanvas("c1","",1800,1000);
c1->Divide(3,2);
c1->cd(1);
// hmb->Draw("Box2");
hmb->Draw("colz");
TLatex* t1=new TLatex(30,25,"N_{event}=3000");
t1->SetTextSize(0.05);
t1->Draw();

c1->cd(2);
hjet->Draw("colz");
TLatex* t2=new TLatex(30,25,"N_{event}=3000");
t2->SetTextSize(0.05);
t2->Draw();
// hjet->Draw("Box2");


c1->cd(3);
hcent->Draw("colz");
TLatex* t3=new TLatex(30,25,"N_{event}=3000");
t3->SetTextSize(0.05);
t3->Draw();
// hcent->Draw("Box2");

c1->cd(4);
// hmb2->Draw("Box2");
hmb2->Draw("colz");
c1->cd(5);
// hjet2->Draw("Box2");
hjet2->Draw("colz");
c1->cd(6);
// hcent2->Draw("Box2");
hcent2->Draw("colz");
c1->SaveAs("meanall.png");
c1->SaveAs("meanall.gif");

}