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

void percentage(){
TH1D* hmb=new TH1D();
TH1D* hmb2=new TH1D();
TH1D* hcent=new TH1D();
TH1D* hcent2=new TH1D();
TH1D* hjet=new TH1D();
TH1D* hjetpcoll=new TH1D();
TH1D* hjet2=new TH1D();

// after subtraction
// TFile *f1 = new TFile("largestEtHist_minbias_after.root");
// hmb = (TH1D*)f1->Get("LargestEt");
// TFile *f2 = new TFile("largestEtHist_central_after.root");
// hcent = (TH1D*)f2->Get("LargestEt");
// TFile *f3 = new TFile("largestEtHist_jet_after.root");
// hjet = (TH1D*)f3->Get("LargestEt");

TFile *f1 = new TFile("newEtHist_mb.root");
hmb = (TH1D*)f1->Get("LargestEt");
TFile *f2 = new TFile("newEtHist_jet.root");
hjet = (TH1D*)f2->Get("LargestEt");
TFile *f7 = new TFile("largestEtHist_jet_after_pcoll.root");
hjetpcoll = (TH1D*)f7->Get("LargestEt");
TFile *f3 = new TFile("newEtHist_cent.root");
hcent = (TH1D*)f3->Get("LargestEt");

//before subtraction
TFile *f4 = new TFile("largestEtHist_minbias.root");
hmb2 = (TH1D*)f4->Get("LargestEt");
TFile *f5 = new TFile("largestEtHist_central.root");
hcent2 = (TH1D*)f5->Get("LargestEt");
TFile *f6 = new TFile("largestEtHist_jet.root");
hjet2 = (TH1D*)f6->Get("LargestEt");

/*
//histogram plot__________________________________________________________
// TCanvas *c1=new TCanvas("c1");
TCanvas *c1=new TCanvas("c1","",1600,1000);
c1->Divide(2,2);
c1->cd(2);
TLegend leg(0.72,0.6,0.95,0.78,"");
hcent->SetStats(0);
hmb->SetStats(0);
hjet->SetStats(0);
hcent->SetTitle("Largest Jet Et Distribution After Subtraction");
hcent->GetXaxis()->SetTitle("Compressed Et");
hcent-> Draw();
hmb->Draw("Same");
// hcent->GetXaxis()->SetRangeUser(0.,400.);
hjet->Draw("Same");
hjet->SetLineColor(2);
hcent->SetLineColor(4);
hmb->SetLineColor(8);
// leg.AddEntry(hmb,"min bias","l");
// leg.AddEntry(hjet,"jet","l");
// leg.AddEntry(hcent,"central","l");
// leg.SetFillColor(0);
// leg.Draw("same");
// leg.SetTextSize(0.04);

// TLegend leg(0.72,0.6,0.95,0.78,"");
c1->cd(1);
hcent2->SetStats(0);
hmb2->SetStats(0);
hjet2->SetStats(0);
hmb2->SetTitle("Largest Jet Et Distribution Before Subtraction");
hmb2->GetXaxis()->SetTitle("Compressed Et");
hmb2->Draw();
hcent2-> Draw("Same");
// hcent->GetXaxis()->SetRangeUser(0.,400.);
hjet2->Draw("Same");
hjet2->SetLineColor(2);
hcent2->SetLineColor(4);
hmb2->SetLineColor(8);
leg.AddEntry(hmb2,"min bias","l");
leg.AddEntry(hjet2,"jet","l");
leg.AddEntry(hcent2,"central","l");
leg.SetFillColor(0);
leg.Draw("same");
leg.SetTextSize(0.05);
// c1->SaveAs("histall.png");
//__________________________________________________________________________
*/

// Float_t percentJet[100];
// Float_t percentMB[100];
// Float_t percentCent[100];
// Float_t Ecut[100];
Float_t percentJet[1000];
Float_t percentJetpcoll[1000];
Float_t percentMB[1000];
Float_t percentCent[1000];
Float_t Ecut[1000];

// for (int i=0;i<100;i++){
for (int i=0;i<1000;i++){
  // percentJet[i]=100*hjet->Integral(i,99)/hjet->Integral();
  // percentMB[i]=100*hmb->Integral(i,99)/hmb->Integral();
  // percentCent[i]=100*hcent->Integral(i,99)/hcent->Integral();
  // Ecut[i]=i*5;  
  percentJet[i]=100*hjet->Integral(i,999)/hjet->Integral();
  percentJetpcoll[i]=100*hjetpcoll->Integral(i,999)/hjetpcoll->Integral();
  percentMB[i]=100*hmb->Integral(i,999)/hmb->Integral();
  percentCent[i]=100*hcent->Integral(i,999)/hcent->Integral();
  Ecut[i]=i*0.5;
}

Float_t percentJetb[100];
Float_t percentMBb[100];
Float_t percentCentb[100];


// for (int i=0;i<100;i++){
// for (int i=0;i<1000;i++){
  // percentJetb[i]=100*hjet2->Integral(i,99)/hjet2->Integral();
  // percentMBb[i]=100*hmb2->Integral(i,99)/hmb2->Integral();
  // percentCentb[i]=100*hcent2->Integral(i,99)/hcent2->Integral();
  // Ecut[i]=i*5;  
  // percentJet[i]=100*hjet->Integral(i,999)/hjet->Integral();
  // percentMB[i]=100*hmb->Integral(i,999)/hmb->Integral();
  // percentCent[i]=100*hcent->Integral(i,999)/hcent->Integral();
  // Ecut[i]=i*0.5;
// }


float max=0;
float maxE=0;
float ratio=0;
float mbpercent=0;
float jetpercent=0;
float jetpercentpcoll=0;
float centpercent=0;
// for (int i=0;i<21;i++){
for (int i=0;i<1000;i++){
   float d=percentJet[i]-percentMB[i];
   if (d>max){
      max=d;
      // maxE=i*5;
      maxE=i*0.5;
      ratio=percentJet[i]/percentMB[i];
      jetpercent=percentJet[i];
      jetpercentpcoll=percentJetpcoll[i];
      mbpercent=percentMB[i];
      centpercent=percentCent[i];
   }
}

float E5=0;
float E5b=0;
float E2=0;
float jetpercent5=0;
float jetpercent5pcoll=0;
float jetpercent5b=0;
float mbpercent5=0;
float mbpercent5b=0;
float centpercent5=0;
float centpercent5b=0;
float jetpercent2=0;
float jetpercent2pcoll=0;
float mbpercent2=0;
float centpercent2=0;

// for (int i=0;i<21;i++){
for (int i=0;i<1000;i++){
cout<<percentMB[i]<<endl;
   if (percentMB[i]<=5.0){
     cout<<"found it(5)!"<<endl;
	  // maxE=i*5;
      E5=i*0.5;
      jetpercent5=percentJet[i];
      jetpercent5pcoll=percentJetpcoll[i];
      mbpercent5=percentMB[i];
      centpercent5=percentCent[i];
      break;
   }
}

// for (int i=0;i<21;i++){
for (int i=0;i<100;i++){
cout<<percentMBb[i]<<endl;
   if (percentMBb[i]<=5.0){
     cout<<"found it(5)!"<<endl;
	  // maxE=i*5;
      E5b=i*5;
      jetpercent5b=percentJetb[i];
      mbpercent5b=percentMBb[i];
      centpercent5b=percentCentb[i];
      break;
   }
}

// for (int i=0;i<21;i++){
for (int i=0;i<1000;i++){
cout<<percentMB[i]<<endl;
   if (percentMB[i]<=2.0){
     cout<<"found it(2)!"<<endl;
      E2=i*0.5;
      // E2=i*5;
      jetpercent2=percentJet[i];
      jetpercent2pcoll=percentJetpcoll[i];
      mbpercent2=percentMB[i];
      centpercent2=percentCent[i];
      break;
   }
}

cout<<"percentaged=  "<<max<<endl;
cout<<"optimum energy=  "<<maxE<<endl;
cout<<"ratio= "<<ratio<<endl;
cout<<"minbias= "<<mbpercent<<endl;
cout<<"jet= "<<jetpercent<<endl;
cout<<"jet= "<<jetpercentpcoll<<endl;
cout<<"cent= "<<centpercent<<endl;

cout<<"E5=  "<<E5<<endl;
cout<<"minbias5= "<<mbpercent5<<endl;
cout<<"jet5= "<<jetpercent5<<endl;
cout<<"jet5= "<<jetpercent5pcoll<<endl;
cout<<"cent5= "<<centpercent5<<endl;

cout<<"E5b=  "<<E5b<<endl;
cout<<"minbias5b= "<<mbpercent5b<<endl;
cout<<"jet5b= "<<jetpercent5b<<endl;
cout<<"cent5b= "<<centpercent5b<<endl;

cout<<"E2=  "<<E2<<endl;
cout<<"minbias2= "<<mbpercent2<<endl;
cout<<"jet2= "<<jetpercent2<<endl;
cout<<"jet2= "<<jetpercent2pcoll<<endl;
cout<<"cent2= "<<centpercent2<<endl;



TCanvas *c1=new TCanvas("c1","Threshold Et cut vs percentage of events that pass after subtraction",800,600);
// c1->SetTitleSize(20);
// TGraphErrors *percentageMB = new TGraphErrors(21,Ecut,percentMB);


// c1->cd(4);
TGraphErrors *percentageMB = new TGraphErrors(200,Ecut,percentMB);
// TGraphErrors *percentageMB = new TGraphErrors(1000,Ecut,percentMB);
// TGraphErrors *percentageMB = new TGraphErrors(100,Ecut,percentMB);
percentageMB->SetLineWidth(3);
percentageMB->SetLineColor(8);
percentageMB->SetTitle("Accept Percentages After Background Subtraction");
percentageMB->GetXaxis()->SetTitle("L1 Threshold");
percentageMB->GetYaxis()->SetTitle("Event(%)");
percentageMB->GetXaxis()->CenterTitle();
percentageMB->GetYaxis()->CenterTitle();
percentageMB->Draw("AL");



// TGraphErrors *percentageJet = new TGraphErrors(100,Ecut,percentJet);
TGraphErrors *percentageJet = new TGraphErrors(200,Ecut,percentJet);
// TGraphErrors *percentageJet = new TGraphErrors(1000,Ecut,percentJet);
percentageJet->SetLineWidth(3);
percentageJet->SetLineColor(2);
percentageJet->Draw("LSame");

// TGraphErrors *percentageJet = new TGraphErrors(100,Ecut,percentJet);
TGraphErrors *percentageJetpcoll = new TGraphErrors(200,Ecut,percentJetpcoll);
// TGraphErrors *percentageJetpcoll = new TGraphErrors(1000,Ecut,percentJetpcoll);
percentageJetpcoll->SetLineWidth(3);
percentageJetpcoll->SetLineColor(6);
// percentageJetpcoll->Draw("LSame");
      
// TGraphErrors *percentageCent = new TGraphErrors(100,Ecut,percentCent);
TGraphErrors *percentageCent = new TGraphErrors(200,Ecut,percentCent);
// TGraphErrors *percentageCent = new TGraphErrors(1000,Ecut,percentCent);
percentageCent->SetLineWidth(3);
percentageCent->SetLineColor(4);
percentageCent->Draw("LSame");

/*
c1->cd(3);
// TGraphErrors *percentageMB = new TGraphErrors(200,Ecut,percentMB);
TGraphErrors *percentageMBb = new TGraphErrors(100,Ecut,percentMBb);
percentageMBb->SetLineWidth(3);
percentageMBb->SetLineColor(8);
percentageMBb->SetTitle("Acceptance Before Background Subtraction");
percentageMBb->GetXaxis()->SetTitle("Threshold Energy(Compressed Et)");
percentageMBb->GetYaxis()->SetTitle("Event(%)");
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
*/


TLine* line=new TLine(maxE,0.,maxE,110);
line->SetLineWidth(2);
line->SetLineStyle(2);
// line->Draw("same");
// cout<<maxE<<endl;

TLine* line5=new TLine(E5,0.,E5,110);
line5->SetLineWidth(3);
line5->SetLineStyle(3);
line5->Draw("same");

TLine* line2=new TLine(E2,0.,E2,110);
line2->SetLineWidth(3);
line2->SetLineStyle(4);
line2->Draw("same");


TLegend leg2(0.71,0.30,0.94,0.6,"");
// TLegend leg2(0.71,0.40,0.94,0.6,"");
leg2.AddEntry(percentageMB,"min bias","l");
leg2.AddEntry(percentageJet,"jet","l");
// leg2.AddEntry(percentageJetpcoll,"pcoll jet","l");
leg2.AddEntry(percentageCent,"central","l");
// leg2.AddEntry(line,"optimum","l");
leg2.AddEntry(line5,"5% minbias","l");
leg2.AddEntry(line2,"2% minbias","l");
leg2.SetFillColor(0);
leg2.SetTextSize(0.055);
leg2.Draw("same");

// c1->SaveAs("percentage.png");
// c1->SaveAs("percentage.gif");
c1->SaveAs("percentagezoom.png");
c1->SaveAs("percentagezoom.gif");
}