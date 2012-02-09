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

void checkRBSignal_prof()
{
   TH1::SetDefaultSumw2();
   const int nBin = 5;
   double m[nBin+1] = {0,4,8,12,20,40};

   TFile * fdata = TFile::Open("../output-data-Photon-v7_v24_akPu3PF.root");
   TTree * tgjdata = (TTree*)fdata->Get("tgj");
   TFile * fmix = TFile::Open("../output-hy18qcdpho30and50merge_v24_xsec_akPu3PF.root");
   TTree * tgjmix = (TTree*)fmix->Get("tgj");
   TFile * fpp = TFile::Open("../output-pp-photon-7TeV-v4_v24_akPu3PF.root");
   TTree * tgjpp = (TTree*)fpp->Get("tgj");

   
   TProfile *hRBData = new TProfile("hRBData","",nBin,m);
   TProfile *hRBMix = new TProfile("hRBMix","",nBin,m);
   TProfile *hRBPp = new TProfile("hRBPp","",nBin,m);
   
   TString drawvar=Form("(jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*7./8):cBin");
   TString sel="(photonEt>60.0&&sumIsol/0.9<1&&sigmaIetaIeta<0.01)";

   cout << sel << " " << drawvar << endl;
   float nData = tgjdata->Project("hRBData",drawvar,TCut("(anaEvtSel)&&"+sel),"prof");
   float nMix = tgjmix->Project("hRBMix",drawvar,TCut("(offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22)&&"+sel)*"weight*sampleWeight","prof");
   float nPp = tgjpp->Project("hRBPp",drawvar,TCut("(anaEvtSel)&&"+sel),"prof");
   cout << "nData: " << nData << endl;
   cout << "nMix: " << nMix << endl;
   cout << "nPp: " << nPp << endl;

   TCanvas * c2 = new TCanvas("c2","c2",500,500);
   hRBData->SetMarkerColor(kRed);
   hRBData->SetLineColor(kRed);
   hRBMix->SetMarkerStyle(kOpenSquare);
   hRBPp->SetMarkerStyle(kOpenStar);
   hRBPp->SetMarkerColor(kRed);
   hRBData->SetAxisRange(0,1.5,"Y");
   hRBData->Draw("E");
   hRBMix->Draw("sameE");
   hRBPp->Draw("sameE");
}