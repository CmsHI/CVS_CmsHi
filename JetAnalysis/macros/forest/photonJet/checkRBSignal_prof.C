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
   const int nBin = 6;
   double m[nBin+1] = {-0.5,3.5,7.5,11.5,20.5,31.5,40.5};
//   const int nBin = 5;
//   double m[nBin+1] = {-0.5,3.5,7.5,11.5,20.5,40.5};

   TFile * fdata = TFile::Open("../output-data-Photon-v4_v11.root");
   TTree * tgjdata = (TTree*)fdata->Get("tgj");
   tgjdata->SetAlias("fisherIsol","(6.5481e-01 +cc5*8.127033e-03 +cc4*-1.275908e-02 +cc3*-2.24332e-02 +cc2*-6.96778e-02 +cc1*4.682052e-02 +cr5*-2.35164e-02 +cr4*1.74567e-03 +cr3*-2.39334e-04 +cr2*-3.1724e-02 +cr1*-3.65306e-02 +ct4PtCut20*1.8335e-02 +ct3PtCut20*-2.609068e-02 +ct2PtCut20*-4.523171e-02 +ct1PtCut20*-1.270661e-02 +ct5PtCut20*9.218723e-03)");
   TFile * fmix = TFile::Open("../output-hypho50v2_50kyongsun_v11.root");
   TTree * tgjmix = (TTree*)fmix->Get("tgj");
   tgjmix->SetAlias("fisherIsol","(6.5481e-01 +cc5*8.127033e-03 +cc4*-1.275908e-02 +cc3*-2.24332e-02 +cc2*-6.96778e-02 +cc1*4.682052e-02 +cr5*-2.35164e-02 +cr4*1.74567e-03 +cr3*-2.39334e-04 +cr2*-3.1724e-02 +cr1*-3.65306e-02 +ct4PtCut20*1.8335e-02 +ct3PtCut20*-2.609068e-02 +ct2PtCut20*-4.523171e-02 +ct1PtCut20*-1.270661e-02 +ct5PtCut20*9.218723e-03)");
   TFile * fpp = TFile::Open("../output-data-pp2010-prod3-photon_v10.root");
   TTree * tgjpp = (TTree*)fpp->Get("tgj");
   tgjpp->SetAlias("fisherIsol","(6.5481e-01 +cc5*8.127033e-03 +cc4*-1.275908e-02 +cc3*-2.24332e-02 +cc2*-6.96778e-02 +cc1*4.682052e-02 +cr5*-2.35164e-02 +cr4*1.74567e-03 +cr3*-2.39334e-04 +cr2*-3.1724e-02 +cr1*-3.65306e-02 +ct4PtCut20*1.8335e-02 +ct3PtCut20*-2.609068e-02 +ct2PtCut20*-4.523171e-02 +ct1PtCut20*-1.270661e-02 +ct5PtCut20*9.218723e-03)");


   
   TProfile *hRBData = new TProfile("hRBData","",nBin,m);
   TProfile *hRBMix = new TProfile("hRBMix","",nBin,m);
   TProfile *hRBPp = new TProfile("hRBPp","",nBin,m);
//   TProfile *hRBData = new TProfile("hRBData","",10,0,40);
//   TProfile *hRBMix = new TProfile("hRBMix","",10,0,40);
//   TProfile *hRBPp = new TProfile("hRBPp","",10,0,40);
   
   TCanvas * c0 = new TCanvas("c0","",500,500);
//   TString drawvar=Form("(jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2/3&&Agj<%.3f):cBin",ajCut);
//   TString sel="(fisherIsol>0.3&&sigmaIetaIeta<0.01&&photonEt>60.0)";
//   TString drawvar=Form("(acos(cos(photonPhi-jetPhi))>%.3f):cBin",ajCut);
//   TString sel="(fisherIsol>0.3&&sigmaIetaIeta<0.01&&photonEt>60.0&&jetEt>30.0)";
//   TString drawvar=Form("(jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2/3.)*(photonEt-jetEt):cBin");
//   TString sel="(fisherIsol>0.3&&sigmaIetaIeta<0.01&&photonEt>60.0)";
   TString drawvar=Form("(photonEt-jetEt):cBin");
   TString sel="(fisherIsol>0.3&&sigmaIetaIeta<0.01&&photonEt>50.0)&&(jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2/3.)";
   cout << sel << " " << drawvar << endl;
   tgjdata->Project("hRBData",drawvar,TCut("(anaEvtSel)&&"+sel),"prof");
   tgjmix->Project("hRBMix",drawvar,TCut("(offlSel)&&"+sel),"prof");
   tgjpp->Project("hRBPp",drawvar,TCut("(anaEvtSel)&&"+sel),"prof");

   TCanvas * c2 = new TCanvas("c2","",500,500);
   hRBData->SetMarkerColor(kRed);
   hRBData->SetLineColor(kRed);
   hRBMix->SetMarkerStyle(kOpenSquare);
   hRBPp->SetMarkerStyle(kOpenStar);
   hRBPp->SetMarkerColor(kBlue);
   //hRBData->SetAxisRange(0,1.,"Y");
   hRBData->SetAxisRange(0,20,"Y");
   //hRBData->SetYTitle(Form("R_{B}(A_{GJ} < %.2f)",ajCut));
   //hRBData->SetYTitle(Form("R_{B}(A_{GJ} < %.2f)",ajCut));
   hRBData->SetYTitle(Form("<#DeltaE>",ajCut));
   hRBData->Draw("E");
   hRBMix->Draw("sameE");
   hRBPp->Draw("sameE");
   
//   TLine* pline = new TLine(0,hRBMix->GetBinContent(1),40,hRBMix->GetBinContent(1));
//   pline->SetLineColor(4);
//   pline->SetLineStyle(4);
//   pline->Draw();
}