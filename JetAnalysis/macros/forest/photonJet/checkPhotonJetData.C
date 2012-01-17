#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TString.h"
#include "TLine.h"
#include "TLegend.h"
#include <iostream>
#include "commonUtility.h"
using namespace std;

void checkPhotonJetData(
                        int dataSrcType=1 // 0=mc, 1=data, 2=pp
                        ){
   TH1::SetDefaultSumw2();
   TFile * inf = TFile::Open("../output-data-Photon-v7_v21.root");
   TTree * tgj = (TTree*)inf->Get("tgj");
   TCut selPre = "anaEvtSel";
   TString dataSrcTitle="PbPb Data";
   if (!dataSrcType) {
      selPre = "offlSel";
      dataSrcTitle="MC";
   } else if (dataSrcType==1) {
   } else if (dataSrcType==2) {
      dataSrcTitle="pp Data";
   }
   TCut isolCut = "fisherIsol>0.3";
   //TCut isolCut = "(cc4+cr4+ct4PtCut20)/0.9<1";
   TCut selPho = selPre&&"photonEt>60&&sigmaIetaIeta<0.01"&&isolCut;
   TCut selPhoJet = selPho&&"jetEt>30&&abs(dphi)>2.0944";
   cout << "photon Sel: " << selPho << " " << tgj->GetEntries(selPho) << endl;
   cout << "photonJet Sel: " << selPhoJet << " " << tgj->GetEntries(selPhoJet) << endl;
   
   // Centrality bin cuts
   const int nBin = 2;
   float m[nBin+1] = {0,12,40};
   vector<TCut> vcutCent;
   for (int ib=0; ib<nBin; ++ib) vcutCent.push_back(Form("cBin>=%.1f&&cBin<%.1f",m[ib],m[ib+1]));
   
   TCanvas * c2_2 = new TCanvas("c2_2","",500,500);
   tgj->Draw("cBin",selPho,"");
   
   TCanvas * c3 = new TCanvas("c3","",700,350);
   c3->Divide(2,1);
   cout << "Pt2D" << endl;
   for (int i=0; i<vcutCent.size(); ++i) {
      c3->cd(i+1);
      gPad->SetRightMargin(0.15);
      int ib=vcutCent.size()-1-i;
      TH2D * hPt2D = new TH2D(Form("hPt2D_%d",ib),"",50,0,250,50,0,250);
      TCut selInBin = vcutCent[ib]&&selPhoJet;
      tgj->Project(hPt2D->GetName(),"jetEt:photonEt",selInBin,"E");
      cout << TString(selInBin) << " " << tgj->GetEntries(selInBin) << endl;
      hPt2D->SetTitle(";photon p_{T} (GeV/c);jet p_{T} (GeV/c)");
      hPt2D->SetAxisRange(0,200,"X");
      hPt2D->SetAxisRange(0,200,"Y");
      hPt2D->Draw("colz");
      TLegend *leg2=new TLegend(0.138,0.81,0.38,0.94);
      leg2->AddEntry(hPt2D,dataSrcTitle,"");
      leg2->AddEntry(hPt2D,Form("%.0f to %.0f %%",m[ib]*2.5,m[ib+1]*2.5),"");
//      if (i==1) {
//         leg2->AddEntry(hPt2D,"","");
//      }
      leg2->SetFillColor(0);
      leg2->SetBorderSize(0);
      leg2->SetFillStyle(0);
      leg2->SetTextSize(0.04);
      leg2->Draw();
   }
}