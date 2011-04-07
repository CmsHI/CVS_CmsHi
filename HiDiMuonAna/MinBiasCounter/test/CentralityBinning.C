#include <TStyle.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TNtuple.h>
#include <iostream>
#include <TLine.h>
#include <TMath.h>
#include <math.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TRandom.h>
#include <TCut.h>
#include <TClonesArray.h>
//#include "/home/kimy/script/commonUtility.h"
#include <TLatex.h>
#define PI 3.141592653589


void CentralityBinning()
{
   
  TCanvas *c1 = new TCanvas("c1", "",5,24,400,400);
   gStyle->SetOptStat(0);
   c1->Range(-8.607595,-9.893171,42.02532,2.727967);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(0);
   c1->SetLogy();
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.17);
   c1->SetRightMargin(0.04);
   c1->SetTopMargin(0.05);
   c1->SetBottomMargin(0.15);
   c1->SetFrameLineColor(0);
   c1->SetFrameBorderMode(0);
   c1->SetFrameLineColor(0);
   c1->SetFrameBorderMode(0);

   //   TFile *fDouble=new TFile("DoubleMuCentrality_Histo_all_sum.root");
   TFile *fDouble=new TFile("DoubleMuOpenCentrality_Histo_sum.root");
   TFile *fMinbias=new TFile("MinBiasCentrality_Histo_all_sum.root");
  
  TH1 *hhfMinbias_oppo = new TH1D("hMB","",40,0,40);  
  hhfMinbias_oppo = (TH1D*)fMinbias->Get("hCent");
  TH1 *hhfMinbias = new TH1D("hMBoppo","",40,0,40);
  for(int i=0;i<40;i++)
    {
      hhfMinbias->SetBinContent(40-i,hhfMinbias_oppo->GetBinContent(i)*10);
      cout << " i "<< i <<  " hhfMinbias_oppo->GetBinContent(i) " << hhfMinbias_oppo->GetBinContent(i)<< " new bumber " << hhfMinbias_oppo->GetBinContent(i)*10 << endl;
    }
  hhfMinbias->SetStats(0);
   hhfMinbias->SetFillColor(1);
   hhfMinbias->SetFillStyle(0);
   hhfMinbias->SetLineStyle(0);
   hhfMinbias->SetLineWidth(2);
   hhfMinbias->SetMarkerStyle(20);
   hhfMinbias->SetMarkerSize(1.5);
   hhfMinbias->GetXaxis()->SetTitle("Centrality Bin");
   hhfMinbias->GetXaxis()->SetBinLabel(1,"100%");
   hhfMinbias->GetXaxis()->SetBinLabel(11,"75%");
   hhfMinbias->GetXaxis()->SetBinLabel(21,"50%");
   hhfMinbias->GetXaxis()->SetBinLabel(31,"25%");
   hhfMinbias->GetXaxis()->SetBinLabel(40,"0%");
   hhfMinbias->GetXaxis()->CenterTitle(true);
   hhfMinbias->GetXaxis()->SetNdivisions(505);
   hhfMinbias->GetXaxis()->SetLabelFont(42);
   hhfMinbias->GetXaxis()->SetLabelOffset(0.01);
   hhfMinbias->GetXaxis()->SetLabelSize(0.045);
   hhfMinbias->GetXaxis()->SetTitleSize(0.055);
   hhfMinbias->GetXaxis()->SetTitleFont(42);
   hhfMinbias->GetYaxis()->SetTitle("Fraction of minbias events (arb. scale)");
   //hhfMinbias->GetYaxis()->SetNdivisions(505);
   hhfMinbias->GetYaxis()->CenterTitle(true);
   hhfMinbias->GetYaxis()->SetLabelFont(42);
   hhfMinbias->GetYaxis()->SetLabelOffset(0.01);
   hhfMinbias->GetYaxis()->SetLabelSize(0.045);
   hhfMinbias->GetYaxis()->SetTitleSize(0.055);
   hhfMinbias->GetYaxis()->SetTitleOffset(1.2);
   hhfMinbias->GetYaxis()->SetTitleFont(42);
   hhfMinbias->GetZaxis()->SetLabelFont(42);
   hhfMinbias->GetZaxis()->SetLabelSize(0.045);
   hhfMinbias->GetZaxis()->SetTitleFont(42);
   hhfMinbias->SetMaximum(1e09);
   hhfMinbias->SetMinimum(1e-02);
 
   hhfMinbias->Draw("hist");

  TH1 *hhfDimu_oppo = new TH1D("hhfDimuoppo","",40,0,40);  
  hhfDimu_oppo = (TH1D*)fDouble->Get("hCent");

  TH1 *hhfDimu = new TH1D("hhfDimu","",40,0,40);
  for(int i=0;i<40;i++)
    {
      hhfDimu->SetBinContent(40-i,hhfDimu_oppo->GetBinContent(i));
      cout << " i "<< i <<  " hhfDimu_oppo->GetBinContent(i) " << hhfDimu_oppo->GetBinContent(i) << endl;
    }
  hhfDimu->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ff9999");
   hhfDimu->SetFillColor(ci);
   hhfDimu->SetFillStyle(3544);

   ci = TColor::GetColor("#ff0000");
   hhfDimu->SetLineColor(ci);
   hhfDimu->SetLineStyle(0);
   hhfDimu->SetLineWidth(2);
   hhfDimu->SetMarkerStyle(20);
   hhfDimu->SetMarkerSize(1.5);
   hhfDimu->GetXaxis()->SetLabelFont(42);
   hhfDimu->GetXaxis()->SetLabelOffset(0.01);
   hhfDimu->GetXaxis()->SetLabelSize(0.045);
   hhfDimu->GetXaxis()->SetTitleSize(0.055);
   hhfDimu->GetXaxis()->SetTitleFont(42);
   hhfDimu->GetYaxis()->SetLabelFont(42);
   hhfDimu->GetYaxis()->SetLabelOffset(0.01);
   hhfDimu->GetYaxis()->SetLabelSize(0.045);
   hhfDimu->GetYaxis()->SetTitleSize(0.055);
   hhfDimu->GetYaxis()->SetTitleOffset(1.2);
   hhfDimu->GetYaxis()->SetTitleFont(42);
   hhfDimu->GetZaxis()->SetLabelFont(42);
   hhfDimu->GetZaxis()->SetLabelSize(0.045);
   hhfDimu->GetZaxis()->SetTitleFont(42);
   hhfDimu->Draw("hist same");
  

   TLegend *leg = new TLegend(0.2813131,0.7115054,0.9,0.8439785,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("hhfMinbias","Minimum Bias Trigger","l");
   entry->SetLineColor(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("hhfDimu","Dimuon Trigger","lf");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   TLatex *tex = new TLatex(0.28,0.87,"CMS PbPb  #sqrt{s_{NN}}=2.76 TeV");

   tex->SetNDC();
   tex->SetTextFont(63);
   tex->SetTextSize(16);
   tex->SetLineWidth(2);
   tex->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
   c1->SaveAs("centralityDoubleMuOpen.pdf");
   
}

