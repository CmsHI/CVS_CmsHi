#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TCut.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"
#include "TStyle.h"
#include "TProfile.h"
#include "TLine.h"
#include "DrawTick.C"

void checkRBSignal_prof(
                        double ajCut= 0.12
                        //double ajCut= 3.03
)
{
//   const int nBin = 6;
//   double m[nBin+1] = {-0.5,3.5,7.5,11.5,19.5,31.5,40.5};
   const int nBin = 5;
   double m[nBin+1] = {0,4,8,12,20,40};

   TFile * fdata = TFile::Open("../output-data-Photon-v6_v18.root");
   TTree * tgjdata = (TTree*)fdata->Get("tgj");
   TFile * fmix = TFile::Open("../output-hy18pho50mixdj80emdj120em_v18.root");
   TTree * tgjmix = (TTree*)fmix->Get("tgj");
   TFile * fpp = TFile::Open("../output-data-pp2010-prod3-photon_v18.root");
   TTree * tgjpp = (TTree*)fpp->Get("tgj");

   
   TProfile *hRBData = new TProfile("hRBData","",nBin,m);
   TProfile *hRBMix = new TProfile("hRBMix","",nBin,m);
   TProfile *hRBPp = new TProfile("hRBPp","",nBin,m);
//   TProfile *hRBData = new TProfile("hRBData","",10,0,40);
//   TProfile *hRBMix = new TProfile("hRBMix","",10,0,40);
//   TProfile *hRBPp = new TProfile("hRBPp","",10,0,40);
   
   TCanvas * c0 = new TCanvas("c0","",500,500);
//   TString drawvar=Form("(jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2/3&&Agj<%.3f):cBin",ajCut);
//   TString sel="((cc4+cr4+ct4PtCut20)/0.9<1&&sigmaIetaIeta<0.01&&photonEt>60.0)";
//   TString drawvar=Form("(acos(cos(photonPhi-jetPhi))>%.3f):cBin",ajCut);
//   TString sel="((cc4+cr4+ct4PtCut20)/0.9<1&&sigmaIetaIeta<0.01&&photonEt>60.0&&jetEt>30.0)";
   TString drawvar=Form("(photonEt-jetEt)/photonEt:cBin");
   //TString sel="(fisherIsol>0.2&&sigmaIetaIeta<0.01&&photonEt>60.0&&jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2./3)";
   TString sel="(fisherIsol>0.2&&sigmaIetaIeta>0.011&& sigmaIetaIeta<0.017 &&photonEt>60.0&&jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2./3)";
   //TString sel="(fisherIsol>0.2&&sigmaIetaIeta<0.01&&photonEt>60.0&&jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7&&acos(cos(photonPhi-jetPhi))<3.14159/2)";
//   TString drawvar=Form("(photonEt-jetEt)/photonEt:cBin");
//   TString sel="(sumIsol<1&&sigmaIetaIeta<0.01&&photonEt>60.0)&&(jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2/3.)";

   cout << sel << " " << drawvar << endl;
   float nData = tgjdata->Project("hRBData",drawvar,TCut("(anaEvtSel)&&"+sel),"prof");
   float nMix = tgjmix->Project("hRBMix",drawvar,TCut("(offlSel&&sampleWeight>0.5)&&"+sel)*"weight","prof");
   float nPp = tgjpp->Project("hRBPp",drawvar,TCut("(anaEvtSel)&&"+sel),"prof");
   cout << "nData: " << nData << endl;
   cout << "nMix: " << nMix << endl;
   cout << "nPp: " << nPp << endl;

   TCanvas * c2 = new TCanvas("c2","",500,500);
   hRBData->SetMarkerColor(kRed);
   hRBData->SetLineColor(kRed);
   hRBMix->SetMarkerStyle(kOpenSquare);
   hRBPp->SetMarkerStyle(kOpenStar);
   hRBPp->SetMarkerColor(kBlue);
   //hRBData->SetAxisRange(0,1.,"Y");
   hRBData->SetAxisRange(-0.08,0.52,"Y");
   //hRBData->SetAxisRange(0,30,"Y");
   //hRBData->SetYTitle(Form("R_{B}(A_{GJ} < %.2f)",ajCut));
   //hRBData->SetYTitle(Form("<#DeltaE>",ajCut));
   hRBData->Draw("E");
   hRBMix->Draw("sameE");
   hRBPp->Draw("sameE");
   
//   TLine* pline = new TLine(0,hRBMix->GetBinContent(1),40,hRBMix->GetBinContent(1));
//   pline->SetLineColor(4);
//   pline->SetLineStyle(4);
//   pline->Draw();
}