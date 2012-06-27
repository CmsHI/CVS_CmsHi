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

void single(){
TH1D* hmba=new TH1D();
TH1D* hmbb=new TH1D();
TH1D* hcenta=new TH1D();
TH1D* hcentb=new TH1D();
TH1D* hjeta=new TH1D();
TH1D* hjetb=new TH1D();

TFile *f1 = new TFile("singlema.root");
hmba = (TH1D*)f1->Get("Etdist");
TFile *f2 = new TFile("singleja.root");
hjeta = (TH1D*)f2->Get("Etdist");
TFile *f3 = new TFile("singlecenta.root");
hcenta = (TH1D*)f3->Get("Etdist");
TFile *f4 = new TFile("singlembiasb.root");
hmbb = (TH1D*)f4->Get("Etdist");
TFile *f5 = new TFile("singlejb.root");
hjetb = (TH1D*)f5->Get("Etdist");
TFile *f6 = new TFile("singlemb.root");
hcentb = (TH1D*)f6->Get("Etdist");

// TCanvas *c1=new TCanvas("c1","",1800,1000);
TCanvas *c1=new TCanvas("c1","",800,600);

hmba->SetStats(0);    
hmba->GetXaxis()->CenterTitle();
hmba->GetYaxis()->CenterTitle();
hjeta->SetStats(0);
hjeta->GetXaxis()->CenterTitle();
hjeta->GetYaxis()->CenterTitle();
hcenta->SetStats(0);
hcenta->GetXaxis()->CenterTitle();
hcenta->GetYaxis()->CenterTitle();
hmbb->SetStats(0);
hmbb->GetXaxis()->CenterTitle();
hmbb->GetYaxis()->CenterTitle();
hjetb->SetStats(0);
hjetb->GetXaxis()->CenterTitle();
hjetb->GetYaxis()->CenterTitle();
hcentb->SetStats(0);
hcentb->GetXaxis()->CenterTitle();
hcentb->GetYaxis()->CenterTitle();

// c1->Divide(3,2);
// c1->cd(1);
// hmbb->Draw("Box2");
// hmbb->Draw("colz");

// c1->cd(2);
// hjetb->Draw("colz");
// hjetb->Draw("Box2");


// c1->cd(3);
// hcentb->Draw("colz");
hcentb->Draw("Box2");

// c1->cd(4);
// hmba->Draw("Box2");
// hmba->Draw("colz");

// c1->cd(5);
// hjeta->Draw("Box2");
// hjeta->Draw("colz");

// c1->cd(6);
// hcenta->Draw("Box2");
// hcenta->Draw("colz");
c1->SaveAs("singlecb.png");
c1->SaveAs("singlecb.gif");
}