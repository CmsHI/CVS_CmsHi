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
                        //double ajCut= 0.15
                        double ajCut= 3.03
)
{
   const int nBin = 7;
   double m[nBin+1] = {-1.5,-0.5,3.5,7.5,11.5,20.5,31.5,40.5};
   //const int nBin = 6;
   //double m[nBin+1] = {-1.5,-0.5,3.5,7.5,11.5,20.5,40.5};

   TFile * fdata = TFile::Open("../output-data-Photon-v2_v11.root");
   TTree * tgjdata = (TTree*)fdata->Get("tgj");
   TFile * fmix = TFile::Open("../output-hypho50v2_50kyongsun_v11.root");
   TTree * tgjmix = (TTree*)fmix->Get("tgj");
   TFile * fpp = TFile::Open("../output-data-pp2010-prod3-photon_v10.root");
   TTree * tgjpp = (TTree*)fpp->Get("tgj");

   
   TProfile *hRBData = new TProfile("hRBData","",nBin,m);
   TProfile *hRBMix = new TProfile("hRBMix","",nBin,m);
   TProfile *hRBPp = new TProfile("hRBPp","",nBin,m);
   
   TCanvas * c0 = new TCanvas("c0","",500,500);
   //TString drawvar=Form("(jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2/3&&Agj<%.3f):cBin",ajCut);
   //TString sel="(photonEt>60.0)";
   TString drawvar=Form("(acos(cos(photonPhi-jetPhi))>%.3f):cBin",ajCut);
   TString sel="(photonEt>60.0&&jetEt>30.0)";
   cout << sel << " " << drawvar << endl;
   tgjdata->Project("hRBData",drawvar,"(anaEvtSel)&&"+sel,"prof");
   tgjmix->Project("hRBMix",drawvar,"(offlSel)&&"+sel,"prof");
   tgjpp->Project("hRBPp",drawvar,"(anaEvtSel)&&"+sel,"prof");

   TCanvas * c2 = new TCanvas("c2","",500,500);
   hRBData->SetMarkerColor(kRed);
   hRBData->SetLineColor(kRed);
   hRBMix->SetMarkerStyle(kOpenSquare);
   hRBPp->SetMarkerStyle(kOpenStar);
   hRBPp->SetMarkerColor(kBlue);
   hRBData->SetAxisRange(0,1.,"Y");
   hRBData->SetYTitle(Form("R_{B}(A_{GJ} < %.2f)",ajCut));
   hRBData->Draw("E");
   hRBMix->Draw("sameE");
   hRBPp->Draw("sameE");
   
   TLine* pline = new TLine(0,hRBMix->GetBinContent(1),40,hRBMix->GetBinContent(1));
   pline->SetLineColor(4);
   pline->SetLineStyle(4);
   pline->Draw();
}