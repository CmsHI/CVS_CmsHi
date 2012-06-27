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

void percentage2(){

TH1D* hmb2=new TH1D();
TH1D* hcent2=new TH1D();
TH1D* hjet2=new TH1D();

//before subtraction
TFile *f4 = new TFile("largestEtHist_minbias.root");
hmb2 = (TH1D*)f4->Get("LargestEt");
TFile *f5 = new TFile("largestEtHist_central.root");
hcent2 = (TH1D*)f5->Get("LargestEt");
TFile *f6 = new TFile("largestEtHist_jet.root");
hjet2 = (TH1D*)f6->Get("LargestEt");



Float_t percentJetb[100];
Float_t percentMBb[100];
Float_t percentCentb[100];
Float_t Ecut[100];

for (int i=0;i<100;i++){
  percentJetb[i]=100*hjet2->Integral(i,99)/hjet2->Integral();
  percentMBb[i]=100*hmb2->Integral(i,99)/hmb2->Integral();
  percentCentb[i]=100*hcent2->Integral(i,99)/hcent2->Integral();
  Ecut[i]=i*5;  
}



TCanvas *c1=new TCanvas("c1","Threshold Et cut vs percentage of events that pass after subtraction",800,600);

c1->cd(3);
// TGraphErrors *percentageMB = new TGraphErrors(200,Ecut,percentMB);
TGraphErrors *percentageMBb = new TGraphErrors(100,Ecut,percentMBb);
percentageMBb->SetLineWidth(3);
percentageMBb->SetLineColor(8);
percentageMBb->SetTitle("Accept Percentages Before Background Subtraction");
percentageMBb->GetXaxis()->SetTitle("L1 Threshold");
percentageMBb->GetYaxis()->SetTitle("Event(%)");
percentageMBb->GetXaxis()->CenterTitle();
percentageMBb->GetYaxis()->CenterTitle();
percentageMBb->Draw("AL");



TGraphErrors *percentageJetb = new TGraphErrors(100,Ecut,percentJetb);
// TGraphErrors *percentageJet = new TGraphErrors(200,Ecut,percentJet);
percentageJetb->SetLineWidth(3);
percentageJetb->SetLineColor(2);
percentageJetb->Draw("LSame");
      
TGraphErrors *percentageCentb = new TGraphErrors(100,Ecut,percentCentb);
// TGraphErrors *percentageCent = new TGraphErrors(200,Ecut,percentCent);
percentageCentb->SetLineWidth(3);
percentageCentb->SetLineColor(4);
percentageCentb->Draw("LSame");


// TLegend leg2(0.71,0.30,0.94,0.6,"");
TLegend leg2(0.71,0.40,0.94,0.6,"");
leg2.AddEntry(percentageMBb,"min bias","l");
leg2.AddEntry(percentageJetb,"jet","l"); 
leg2.AddEntry(percentageCentb,"central","l");

leg2.SetFillColor(0);
leg2.SetTextSize(0.055);
leg2.Draw("same");

c1->SaveAs("percentageb.png");
c1->SaveAs("percentageb.gif");
// c1->SaveAs("percentagezoom.png");
// c1->SaveAs("percentagezoom.gif");
}