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

void comparePhotonJet2D_All4Cent(
                        int dataSrcType=1, // 0=mc, 1=data, 2=pp
                        int isolScheme=0
                        )
{
   TH1::SetDefaultSumw2();
   TFile * inf;
   if (dataSrcType==0) inf = TFile::Open("../output-hy18qcdpho30and50merge_v26_xsec_akPu3PF.root");
   if (dataSrcType==1) inf = TFile::Open("../output-data-Photon-v7-noDuplicate_v26_akPu3PF.root");
//   if (dataSrcType==2) inf = TFile::Open("../output-data-pp2010-prod3-photon_v18.root");
//   if (dataSrcType==3) inf = TFile::Open("../output-pp7TeV-test2_v21.root");

   TTree * tgj = (TTree*)inf->Get("tgj");
   TCut selPre = "anaEvtSel";
   TString dataSrcTitle="PbPb";
   if (!dataSrcType) {
      selPre = "offlSel";
      dataSrcTitle="PYTHIA+HYDJET";
   } else if (dataSrcType==1) {
   } else if (dataSrcType==2) {
      dataSrcTitle="pp 2.76 TeV";
   } else if (dataSrcType==3) {
      dataSrcTitle="pp 7 TeV";
   }
   TCut isolCut = "(cc4+cr4+ct4PtCut20)/0.9<1";
   if (isolScheme==2) isolCut = "fisherIsol>0.3";
   
   TCut selPho = selPre&&"photonEt>60&&sigmaIetaIeta<0.01"&&isolCut;
   TCut selPhoJet = selPho&&"inclJetPt>30&&acos(cos(inclJetPhi-photonPhi))>3.1415926*7./8";
   TCut selPhoJetAllDPhi = selPho&&"inclJetPt>30&&acos(cos(inclJetPhi-photonPhi))>0.7";
   float nPhoton=tgj->Draw("photonEt",selPho,"goff");
   float nPhotonJet=tgj->Draw("inclJetPt/photonEt",selPhoJet,"goff");
   cout << "photon Sel: " << selPho << " " << nPhoton << endl;
   cout << "photonJet Sel: " << selPhoJet << " " << nPhotonJet << endl;

   TString weight;
   if (dataSrcType==0) weight="sampleWeight*weight";
   
   // Centrality bin cuts
   const int nBin = 4;
   float m[nBin+1] = {0,4,12,20,40};
   vector<TCut> vcutCent;
   for (int ib=0; ib<nBin; ++ib) vcutCent.push_back(Form("cBin>=%.1f&&cBin<%.1f",m[ib],m[ib+1]));
   
   TCanvas * c2_2 = new TCanvas("c2_2","",500,500);
   tgj->Draw("cBin",selPho*weight,"");
   
   //////////////////////////////////////////////////////////////////////////
   // Generic correlation plots
   //////////////////////////////////////////////////////////////////////////

//   TString tag = "ptj_ptg";
//   TString var = "inclJetPt:photonEt";
//   TString title = ";#gamma p_{T} (GeV/c);Jet p_{T} (GeV/c)";
//   float nxbins=50, xmin=0, xmax=250, nybins=50, ymin=0, ymax=250;
//   TCut mycut = selPhoJet;

//   TString tag = "x_dphi";
//   TString var = "inclJetPt/photonEt:acos(cos(inclJetPhi-photonPhi))";
//   TString title = ";|#Delta#phi|;x_{J#gamma}";
//   float nxbins=40, xmin=0, xmax=3.14159, nybins=40, ymin=0, ymax=2;
//   TCut mycut = selPhoJetAllDPhi;

//   TString tag = "jpt_dphi";
//   TString var = "inclJetPt:acos(cos(inclJetPhi-photonPhi))";
//   TString title = ";|#Delta#phi|;Jet p_{T} (GeV/c)";
//   float nxbins=40, xmin=0, xmax=3.14159, nybins=40, ymin=0, ymax=200;
//   TCut mycut = selPhoJetAllDPhi;

//   TString tag = "ss_dphi";
//   TString var = "sigmaIetaIeta:acos(cos(inclJetPhi-photonPhi))";
//   TString title = ";|#Delta#phi|;#sigma_{#eta#eta}";
//   float nxbins=40, xmin=0, xmax=3.14159, nybins=40, ymin=0, ymax=0.02;
//   TCut mycut = selPre&&"photonEt>60&&inclJetPt>30&&acos(cos(inclJetPhi-photonPhi))>0.7"&&isolCut;;
   
   TString tag = "ss_x";
   TString var = "sigmaIetaIeta:(inclJetPt/photonEt)";
   TString title = ";x_{J#gamma};#sigma_{#eta#eta}";
   float nxbins=40, xmin=0, xmax=2, nybins=40, ymin=0, ymax=0.02;
   TCut mycut = selPre&&"photonEt>60&&inclJetPt>30&&acos(cos(inclJetPhi-photonPhi))>7./8*3.1415926"&&isolCut;;

//   TString tag = "ss_isol";
//   TString var = "sigmaIetaIeta:sumIsol/0.9";
//   TString title = ";sumIsol;#sigma_{#eta#eta}";
//   float nxbins=40, xmin=-40, xmax=50, nybins=40, ymin=0, ymax=0.02;
//   TCut mycut = selPre&&"photonEt>60";

   TCanvas * c4 = new TCanvas("c4","",1000,250);
   c4->Divide(4,1);
   cout << tag << " draw: " << var << endl;
   for (int i=0; i<vcutCent.size(); ++i) {
      c4->cd(i+1);
      gPad->SetRightMargin(0.15);
      int ib=vcutCent.size()-1-i;
      TH2D * h2D = new TH2D(Form("h%s_%d",tag.Data(),ib),"",nxbins,xmin,xmax,nybins,ymin,ymax);
      TCut selInBin = vcutCent[ib]&&mycut;
      float nPhotonJetInBin = tgj->Project(h2D->GetName(),var,selInBin*weight,"E");
      cout << TString(selInBin*weight) << " " << nPhotonJetInBin << endl;
      h2D->SetTitle(title);
      h2D->Draw("colz");
      TLegend *leg2=new TLegend(0.138,0.81,0.38,0.94);
      leg2->AddEntry(h2D,dataSrcTitle,"");
      if (dataSrcType<=1) leg2->AddEntry(h2D,Form("%.0f to %.0f %%",m[ib]*2.5,m[ib+1]*2.5),"");
      leg2->SetFillColor(0);
      leg2->SetBorderSize(0);
      leg2->SetFillStyle(0);
      leg2->SetTextSize(0.04);
      leg2->Draw();
//      TLine * l0 = new TLine(3.1415926*7./8,0,3.1415926*7./8,2);
      TLine * l0 = new TLine(1,ymin,1,ymax);
      l0->SetLineColor(kRed);
      l0->SetLineStyle(2);
      l0->SetLineWidth(3);
//      l0->Draw();      
   }
   c4->Print(Form("fig/draw/%s_src%d_Isol%d.gif",tag.Data(),dataSrcType,isolScheme));
   c4->Print(Form("fig/draw/%s_src%d_Isol%d.pdf",tag.Data(),dataSrcType,isolScheme));
}