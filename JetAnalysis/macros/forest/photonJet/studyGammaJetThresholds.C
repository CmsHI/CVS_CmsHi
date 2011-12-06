#include <iostream>
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TH1.h"
#include "TCut.h"
#include "TString.h"
#include "commonUtility.h"

void plotPt(TTree * t, TString name, TCut mycut, TString title, float jetPtMin)
{
   gPad->SetLogy();
   TH1D * h = new TH1D(name,"",50,0,150);
   TH1D * hg = new TH1D(name+"gamma","",50,0,150);

   TCut allcuts = mycut&&Form("jetEt>%.1f&&offlSel&&photonEt>60&&isol<5&&sigmaIetaIeta<0.011",jetPtMin);

   float nSel = t->Project(h->GetName(),"jetEt",allcuts);
   t->Project(hg->GetName(),"photonEt",allcuts);
   cout << name << ": " << nSel << endl;

   h->Scale(1./h->Integral());
   hg->Scale(1./hg->Integral());

   h->SetMarkerStyle(kOpenCircle);
   handsomeTH1(h);
   hg->SetMarkerColor(kRed);
   hg->SetLineColor(kRed);
   h->SetAxisRange(1e-3,10,"Y");
   h->SetTitle(";jet p_{T} (GeV/c);Event Fraction");
   h->Draw("E");
   hg->Draw("sameE");
   
   TLegend *t3 = new TLegend(0.3,0.67,0.8,0.92); 
   t3->AddEntry(hg,title,"");
   t3->AddEntry(hg,"Gamma p_{T} > 60 GeV","p");
   t3->AddEntry(h,Form("Jet p_{T} > %.0f GeV",jetPtMin),"p");
   t3->AddEntry(h,Form("%.0f gamma-jets",nSel),"");
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->SetFillStyle(0);
   t3->SetTextSize(0.05);
   t3->Draw();
}

void plotDPhi(TTree * t, TString name, TCut mycut, TString title, float jetPtMin)
{
   gPad->SetLogy();
   TH1D * h = new TH1D(name,"",40,0,3.14);

   TCut allcuts = mycut&&Form("jetEt>%.1f&&offlSel&&photonEt>60&&isol<5&&sigmaIetaIeta<0.011",jetPtMin);

   float nSel = t->Project(name,"acos(cos(jetPhi-photonPhi))",allcuts);
   h->Scale(1./h->Integral());

   float nSide = t->GetEntries(allcuts&&"acos(cos(jetPhi-photonPhi))<2.093");
   float nBkg = nSide * (1./3)/((2.093-0.3)/3.14);
   float nSigAll = t->GetEntries(allcuts&&"acos(cos(jetPhi-photonPhi))>2.093");
   float fracBkg = nBkg/nSigAll;
   cout << name << ": " << nSel << " ";
   cout << "|dphi| < 2.pi/3 = " << nSide << " bck contamination: " << nBkg << " = " << fracBkg << endl;

   h->SetMarkerStyle(kOpenCircle);
   handsomeTH1(h);
   h->SetAxisRange(5e-3,1,"Y");
   h->SetTitle(";#Delta#phi_{g,j};Event Fraction");
   h->Draw("E");
   TLine * l = new TLine(2.093,5e-3,2.093,0.5);
   l->Draw();

   TLegend *t3 = new TLegend(0.3,0.67,0.8,0.92); 
   t3->AddEntry(h,Form("Bkg Fraction: %.2f",fracBkg),"");
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->SetFillStyle(0);
   t3->SetTextSize(0.05);
   t3->Draw();
}

void studyGammaJetThresholds(int bin=0,
                             TString inname="../output-data-Photon-v1_v4.root"
                             )
{
   TH1::SetDefaultSumw2();
   
   TCut mycut;
   TString title;
   if (bin<0) { mycut="cBin>=0&&cBin<40"; title="0-100%"; }
   if (bin==0) { mycut="cBin>=0&&cBin<4"; title="0-10%"; }
   if (bin==1) { mycut="cBin>=4&&cBin<12"; title="10-30%"; }
   if (bin==2) { mycut="cBin>=12&&cBin<40"; title="30-100%"; }

   TFile * inf = TFile::Open(inname);
   TTree * t = (TTree*)inf->Get("tgj");
   
   TCanvas * c2 = new TCanvas("c2","",1100,600);
   //makeMultiPanelCanvas(c2,3,2,0.0,0.0,0.2,0.2,0.02);
   c2->Divide(3,2);
   c2->cd(1);
   plotPt(t,"hPt20",mycut,title,20);
   
   c2->cd(2);
   plotPt(t,"hPt30",mycut,title,30);
   
   c2->cd(3);
   plotPt(t,"hPt40",mycut,title,40);

   c2->cd(4);
   plotDPhi(t,"hDPhi20",mycut,title,20);

   c2->cd(5);
   plotDPhi(t,"hDPhi30",mycut,title,30);

   c2->cd(6);
   plotDPhi(t,"hDPhi40",mycut,title,40);
   
   c2->Print(Form("out/thresholdStudy_bin%d.gif",bin));
}