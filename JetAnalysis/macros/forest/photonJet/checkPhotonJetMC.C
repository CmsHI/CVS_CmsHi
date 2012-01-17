#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TString.h"
#include "TLine.h"
#include "TLegend.h"
#include <iostream>
#include "commonUtility.h"
using namespace std;

void checkPhotonJetMC(){
   TH1::SetDefaultSumw2();
   TFile * inf = TFile::Open("../output-hy18fragpho80_v21_frac10.root");
   TTree * tgj = (TTree*)inf->Get("tgj");
   TCut isolCut = "fisherIsol>0.3";
   //TCut isolCut = "(cc4+cr4+ct4PtCut20)/0.9<1";
   TCut sel = "offlSel&&photonEt>60&&sigmaIetaIeta<0.01"&&isolCut;
   cout << "photon Sel: " << sel << " " << tgj->GetEntries(sel) << endl;
   cout << "photonJet Sel: " << TString(sel&&"jetEt>30&&abs(dphi)>2.0944") << " " << tgj->GetEntries(sel&&"jetEt>30&&abs(dphi)>2.0944") << endl;
   
   // Centrality bin cuts
   const int nBin = 4;
   float m[nBin+1] = {0,4,12,20,40};
   vector<TCut> vcutCent;
   for (int ib=0; ib<nBin; ++ib) vcutCent.push_back(Form("cBin>=%.1f&&cBin<%.1f",m[ib],m[ib+1]));
   
   TCanvas * c2 = new TCanvas("c2","",500,500);
   //tgj.Draw("isEle",sel,"")
   tgj->Draw("refPartonFlavor",sel&&"refPartonPt>0","hist");
   TCanvas * c2_2 = new TCanvas("c2_2","",500,500);
   tgj->Draw("cBin","(offlSel&&photonEt>60)*weight","E");
   tgj->Draw("cBin","(offlSel&&photonEt>60)","same hist");
   TCanvas * c2_3 = new TCanvas("c2_3","",500,500);
   TProfile * hPhoScale = new TProfile("hPhoScale","",50,0,200);
   tgj->Draw("photonEt/refPhoPt:refPhoPt>>hPhoScale",sel&&"refPhoPt>0","prof");
   hPhoScale->SetAxisRange(0,1.5,"Y");
   hPhoScale->Draw();
   
   TCanvas * c3 = new TCanvas("c3","",700,700);
   cout << endl;
   c3->Divide(2,2);
   for (int i=0; i<vcutCent.size(); ++i) {
      c3->cd(i+1);
      int ib=3-i;
      TH1D * hRecPtRat = new TH1D(Form("hRecPtRat_%d",ib),"",30,0,4);
      TH1D * hGenPtRat = new TH1D(Form("hGenPtRat_%d",ib),"",30,0,4);
      TH1D * hPartonPtRat = new TH1D(Form("hPartonPtRat_%d",ib),"",30,0,4);
      tgj->Draw(Form("jetEt/photonEt>>%s",hRecPtRat->GetName()),vcutCent[ib]&&sel&&"jetEt>30&&abs(dphi)>2.0944","E");
      tgj->Draw(Form("refJetEt/refPhoPt>>%s",hGenPtRat->GetName()),vcutCent[ib]&&sel&&"jetEt>30&&abs(dphi)>2.0944","same hist");
      tgj->Draw(Form("refPartonPt/refPhoPt>>%s",hPartonPtRat->GetName()),vcutCent[ib]&&sel&&"jetEt>30&&abs(dphi)>2.0944","same hist");
      cout << TString(vcutCent[ib]&&sel&&"jetEt>30&&abs(dphi)>2.0944") << " " << tgj->GetEntries(vcutCent[ib]&&sel&&"jetEt>30&&abs(dphi)>2.0944") << endl;
      hRecPtRat->SetTitle(";jet p_{T} / photon p_{T};");
      hRecPtRat->SetAxisRange(0,100,"Y");
      hGenPtRat->SetLineColor(kRed);
      hPartonPtRat->SetLineColor(kBlue);
      hRecPtRat->Draw("E");
      hGenPtRat->Draw("same hist");
      //hPartonPtRat->Draw("same hist");
      TLegend *leg2=new TLegend(0.22,0.71,0.53,0.90);
      leg2->AddEntry(hRecPtRat,Form("%.0f to %.0f %%",m[ib]*2.5,m[ib+1]*2.5),"");
      if (i==1) {
         leg2->AddEntry(hRecPtRat,"(Rec #gamma, Rec Jet)","p");
         leg2->AddEntry(hGenPtRat,"(Gen #gamma, Gen Jet)","l");
      }
      leg2->SetFillColor(0);
      leg2->SetBorderSize(0);
      leg2->SetFillStyle(0);
      leg2->SetTextSize(0.04);
      leg2->Draw();
   }


   TCanvas * c4_0 = new TCanvas("c4_0","",500,500);
   tgj->Draw("refPhoFlavor",sel,"hist");

   TCanvas * c4 = new TCanvas("c4","",700,700);
   cout << endl;
   c4->Divide(2,2);
   for (int i=0; i<vcutCent.size(); ++i) {
      c4->cd(i+1);
      gPad->SetLogy();
      int ib=3-i;
      TH1D * hRecDPhi = new TH1D(Form("hRecDPhi_%d",ib),"",40,0,3.14159);
      TH1D * hGenDPhi = new TH1D(Form("hGenDPhi_%d",ib),"",40,0,3.14159);
      tgj->Draw(Form("acos(cos(jetPhi-photonPhi))>>%s",hRecDPhi->GetName()),vcutCent[ib]&&sel&&"jetEt>30","E");
      cout << TString(vcutCent[ib]&&sel&&"jetEt>30") << " " << tgj->GetEntries(vcutCent[ib]&&sel&&"jetEt>30") << endl;
      tgj->Draw(Form("acos(cos(refJetPhi-refPhoPhi))>>%s",hGenDPhi->GetName()),vcutCent[ib]&&sel&&"jetEt>30&&refJetEt>0&&refPhoPt>0","same hist");
      hRecDPhi->SetTitle(";#Delta#phi;");
      hRecDPhi->SetAxisRange(0.1,1e4,"Y");
      hGenDPhi->SetLineColor(kRed);
      hRecDPhi->Draw("E");
      hGenDPhi->Draw("same hist");
      TLegend *leg2=new TLegend(0.22,0.71,0.53,0.90);
      leg2->AddEntry(hRecDPhi,Form("%.0f to %.0f %%",m[ib]*2.5,m[ib+1]*2.5),"");
      if (i==1) {
         leg2->AddEntry(hRecDPhi,"(Rec #gamma, Rec Jet)","p");
         leg2->AddEntry(hGenDPhi,"(Gen #gamma, Gen Jet)","l");
      }
      leg2->SetFillColor(0);
      leg2->SetBorderSize(0);
      leg2->SetFillStyle(0);
      leg2->SetTextSize(0.04);
      leg2->Draw();
   }
}