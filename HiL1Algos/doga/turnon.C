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

void turnon(){
TH2* hmb=new TH2D();
TH2* hmbb=new TH2D();
TH2* hcent=new TH2D();
TH2* hcentb=new TH2D();
TH2* hjet=new TH2D();
TH2* hjetb=new TH2D();
TH2* hpp=new TH2D();
TH2* hppb=new TH2D();


TFile *f1 = new TFile("turnonmb_after_woutselection.root");
hmb = (TH2*)f1->Get("JetEt");
TFile *f2 = new TFile("turnonjet_after_woutselection.root");
hjet = (TH2*)f2->Get("JetEt");
TFile *f3 = new TFile("turnoncent_after_woutselection.root");
hcent = (TH2*)f3->Get("JetEt");
TFile *f4 = new TFile("turnonpp_after_woutselection.root");
hpp = (TH2*)f4->Get("JetEt");
// TFile *f5 = new TFile("turnonmb_after.root");
TFile *f5 = new TFile("turnonmb_after_wselection.root");
hmbb = (TH2*)f5->Get("JetEt");
TFile *f6 = new TFile("turnonjet_after_wselection.root");
hjetb = (TH2*)f6->Get("JetEt");
TFile *f7 = new TFile("turnoncent_after_wselection.root");
hcentb = (TH2*)f7->Get("JetEt");
TFile *f8 = new TFile("turnonpp_after_wselection.root");
hppb = (TH2*)f8->Get("JetEt");

TCanvas *c1=new TCanvas("c1","",1600,800);
c1->Divide(4,2);

c1->cd(1); 
TProfile* p1=hmb->ProfileX("p1",0,99);
// p1->SetTitle("Minimum Bias Data After Subtraction");
p1->SetTitle("Minimum bias data without event selection");
p1->GetXaxis()->SetTitle("Leading Jet pt (GeV)");
p1->GetXaxis()->CenterTitle();
p1->GetYaxis()->CenterTitle();
p1->Draw();
TLatex* t1=new TLatex(350,0.1,"E_{thr}=63.5");
TLatex* t9=new TLatex(300,0.2,"N_{event}=234457");
t1->SetTextSize(0.05);
t9->SetTextSize(0.05);
t1->Draw();
t9->Draw();

c1->cd(2);
TProfile* p2=hjet->ProfileX("p2",0,99);
// p2->SetTitle("Jet Data After Subtraction");
p2->SetTitle("Jet data without event selection");
p2->GetXaxis()->SetTitle("Leading Jet pt (GeV)");
p2->GetXaxis()->CenterTitle();
p2->GetYaxis()->CenterTitle();
p2->Draw();
TLatex* t2=new TLatex(350,0.1,"E_{thr}=63.5");
TLatex* t10=new TLatex(350,0.2,"N_{event}=3000");
t2->SetTextSize(0.05);
t10->SetTextSize(0.05);
t2->Draw();
t10->Draw();


c1->cd(3); 
TProfile* p3=hcent->ProfileX("p3",0,99);
// p3->SetTitle("Central Data After Subtraction");
p3->SetTitle("Central data without event selection");
p3->GetXaxis()->SetTitle("Leading Jet pt (GeV)");
p3->GetXaxis()->CenterTitle();
p3->GetYaxis()->CenterTitle();
p3->Draw();
TLatex* t3=new TLatex(350,0.1,"E_{thr}=63.5");
TLatex* t11=new TLatex(350,0.2,"N_{event}=3000");
t3->SetTextSize(0.05);
t11->SetTextSize(0.05);
t3->Draw();
t11->Draw();

c1->cd(4);
TProfile* p4=hpp->ProfileX("p4",0,99);
// p4->SetTitle("pp Data After Subtraction");
p4->SetTitle("pp data without event selection");
p4->GetXaxis()->SetTitle("Leading Jet pt (GeV)");
p4->GetXaxis()->CenterTitle();
p4->GetYaxis()->CenterTitle();
p4->Draw();
TLatex* t4=new TLatex(350,0.1,"E_{thr}=63.5");
TLatex* t12=new TLatex(350,0.2,"N_{event}=3000");
t4->SetTextSize(0.05);
t12->SetTextSize(0.05);
t4->Draw();
t12->Draw();

c1->cd(5); 
TProfile* p5=hmbb->ProfileX("p5",0,99);
// p5->SetTitle("Minimum Bias Data Before Subtraction");
p5->SetTitle("Minimum bias data with event selection");
p5->GetXaxis()->SetTitle("Leading Jet pt (GeV)");
p5->GetXaxis()->CenterTitle();
p5->GetYaxis()->CenterTitle();
p5->Draw();
// TLatex* t5=new TLatex(350,0.1,"E_{thr}=295");
TLatex* t5=new TLatex(350,0.1,"E_{thr}=63.5");
TLatex* t13=new TLatex(300,0.2,"N_{event}=214549");
t5->SetTextSize(0.05);
t13->SetTextSize(0.05);
t5->Draw();
t13->Draw();

c1->cd(6);
TProfile* p6=hjetb->ProfileX("p6",0,99);
// p6->SetTitle("Jet Data Before Subtraction");
p6->SetTitle("Jet data with event selection");
p6->GetXaxis()->SetTitle("Leading Jet pt (GeV)");
p6->GetXaxis()->CenterTitle();
p6->GetYaxis()->CenterTitle();
p6->Draw();
// TLatex* t6=new TLatex(350,0.1,"E_{thr}=295");
TLatex* t6=new TLatex(350,0.1,"E_{thr}=63.5");
TLatex* t14=new TLatex(350,0.2,"N_{event}=2530");
t6->SetTextSize(0.05);
t14->SetTextSize(0.05);
t6->Draw();
t14->Draw();

c1->cd(7);
TProfile* p7=hcentb->ProfileX("p7",0,99);
// p7->SetTitle("Central Data Before Subtraction");
p7->SetTitle("Central data with event selection");
p7->GetXaxis()->SetTitle("Leading Jet pt (GeV)");
p7->GetXaxis()->CenterTitle();
p7->GetYaxis()->CenterTitle();
p7->Draw();
// TLatex* t7=new TLatex(350,0.1,"E_{thr}=295");
TLatex* t7=new TLatex(350,0.1,"E_{thr}=63.5");
TLatex* t15=new TLatex(350,0.2,"N_{event}=2996");
t7->SetTextSize(0.05);
t15->SetTextSize(0.05);
t7->Draw();
t15->Draw();


c1->cd(8);
TProfile* p8=hppb->ProfileX("p8",0,99);
p8->SetTitle("pp Data Before Subtraction");
p8->SetTitle("pp data with event selection");
p8->GetXaxis()->SetTitle("Leading Jet pt (GeV)");
p8->GetXaxis()->CenterTitle();
p8->GetYaxis()->CenterTitle();
p8->Draw();
TLatex* t8=new TLatex(350,0.1,"E_{thr}=295");
TLatex* t16=new TLatex(350,0.2,"N_{event}=3342");
t8->SetTextSize(0.05);
t16->SetTextSize(0.05);
t8->Draw();
t16->Draw();

c1->SaveAs("turnon.png");

}