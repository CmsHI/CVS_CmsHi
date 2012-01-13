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

void checkRBSignal_subprof(
                        double ajCut= 0.12
                        //double ajCut= 3.03
)
{
   const int nBin = 4;
   float m[nBin+1] = {0,4,12,20,40};
   const int nBinr = 100;
   float rbins[nBinr+1];
   for (int i=0; i<=nBinr; ++i) rbins[i] = -1.+i*6./nBinr;

   TFile * fdata = TFile::Open("../output-data-Photon-v7_v19.root");
   TTree * tgjdata = (TTree*)fdata->Get("tgj");


   TH2D * hSigAll = new TH2D("hSigAll","",nBin,m,nBinr,rbins);
   TH2D * hBkgDPhi = new TH2D("hBkgDPhi","",nBin,m,nBinr,rbins);
   TH2D * hBkgSS = new TH2D("hBkgSS","",nBin,m,nBinr,rbins);
   
   TCanvas * c0 = new TCanvas("c0","",500,500);
   TString drawvar=Form("jetEt/photonEt:cBin");
   TString selSigAll="(fisherIsol>0.3&&sigmaIetaIeta<0.01&&photonEt>60.0&&jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2./3)";
   TString selBkgDPhi="(fisherIsol>0.3&&sigmaIetaIeta<0.01&&photonEt>60.0&&jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7&&acos(cos(photonPhi-jetPhi))<3.14159/2)";
   TString selBkgSS="(fisherIsol>0.3&&sigmaIetaIeta>0.011&& sigmaIetaIeta<0.017 &&photonEt>60.0&&jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2./3)";
//   TString selSigAll="(sumIsol/0.9<1&&sigmaIetaIeta<0.01&&photonEt>60.0&&jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2./3)";
//   TString selBkgDPhi="(sumIsol/0.9<1&&sigmaIetaIeta<0.01&&photonEt>60.0&&jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7&&acos(cos(photonPhi-jetPhi))<3.14159/2)";
//   TString selBkgSS="(sumIsol/0.9<1&&sigmaIetaIeta>0.011&& sigmaIetaIeta<0.017 &&photonEt>60.0&&jetEt>30&&acos(cos(photonPhi-jetPhi))>3.14159*2./3)";
   
   cout << selSigAll << " " << drawvar << endl;
   float nSigAll = tgjdata->Project("hSigAll",drawvar,TCut("(anaEvtSel)&&"+selSigAll),"colz");
   cout << "nSigAll: " << nSigAll << endl;

   cout << selBkgDPhi << " " << drawvar << endl;
   float nBkgDPhi = tgjdata->Project("hBkgDPhi",drawvar,TCut("(anaEvtSel)&&"+selBkgDPhi),"colz");
   cout << "nBkgDPhi: " << nBkgDPhi << endl;

   cout << selBkgSS << " " << drawvar << endl;
   float nBkgSS = tgjdata->Project("hBkgSS",drawvar,TCut("(anaEvtSel)&&"+selBkgSS),"colz");
   cout << "nBkgSS: " << nBkgSS << endl;
   
   
   float ymax = 1.1;
   float zmax = 110;
   // Individual Regions
   TCanvas * c2 = new TCanvas("c2","",1500,500);
   c2->Divide(3,1);
   c2->cd(1);
   hSigAll->SetTitle(";cBin;ptratio (SigAll)");
   hSigAll->SetAxisRange(0,zmax,"Z");
   hSigAll->Draw("colz");
   TProfile * hSigAll_pfx = hSigAll->ProfileX(Form("%s_pfx",hSigAll->GetName()),1,-1,"");
   hSigAll_pfx->DrawCopy("sameE");

   c2->cd(2);
   hBkgDPhi->SetTitle(";cBin;ptratio (BkgDPhi)");
   hBkgDPhi->SetAxisRange(0,zmax,"Z");
   hBkgDPhi->Draw("colz");
   TProfile * hBkgDPhi_pfx = hBkgDPhi->ProfileX(Form("%s_pfx",hBkgDPhi->GetName()),1,-1,"");
   hBkgDPhi_pfx->DrawCopy("sameE");

   c2->cd(3);
   hBkgSS->SetTitle(";cBin;ptratio (BkgSS)");
   hBkgSS->SetAxisRange(0,zmax,"Z");
   hBkgSS->Draw("colz");
   TProfile * hBkgSS_pfx = hBkgSS->ProfileX(Form("%s_pfx",hBkgSS->GetName()),1,-1,"");
   hBkgSS_pfx->DrawCopy("sameE");

   // Scale
   TH2D * hBkgDPhiScaled = (TH2D*)hBkgDPhi->Clone(Form("%sScaled",hBkgDPhi->GetName()));
   hBkgDPhiScaled->Scale(1.20257);

   TH2D * hBkgSSScaled = (TH2D*)hBkgSS->Clone(Form("%sScaled",hBkgSS->GetName()));
   hBkgSSScaled->Scale(0.91);
   
   // Subtract
   TH2D * hSubDPhi = (TH2D*)hSigAll->Clone("hSubDPhi");
   hSubDPhi->Add(hBkgDPhiScaled,-1);

   TH2D * hSubSS = (TH2D*)hSigAll->Clone("hSubSS");
   hSubSS->Add(hBkgSSScaled,-1);

   TH2D * hSubAll = (TH2D*)hSigAll->Clone("hSubAll");
   hSubAll->Add(hBkgDPhiScaled,-1);
   hSubAll->Add(hBkgSSScaled,-1);

   TCanvas * c6 = new TCanvas("c6","",1500,500);
   c6->Divide(3,1);
   c6->cd(1);
   hSubDPhi->SetTitle(";cBin;ptratio (SubDPhi)");
   hSubDPhi->SetAxisRange(0,zmax,"Z");
   hSubDPhi->Draw("colz");
   TProfile * hSubDPhi_pfx = hSubDPhi->ProfileX(Form("%s_pfx",hSubDPhi->GetName()),1,-1,"");
   hSubDPhi_pfx->DrawCopy("sameE");
   
   c6->cd(2);
   hSubSS->SetTitle(";cBin;ptratio (SubSS)");
   hSubSS->SetAxisRange(0,zmax,"Z");
   hSubSS->Draw("colz");
   TProfile * hSubSS_pfx = hSubSS->ProfileX(Form("%s_pfx",hSubSS->GetName()),1,-1,"");
   hSubSS_pfx->DrawCopy("sameE");
   
   c6->cd(3);
   hSubAll->SetTitle(";cBin;ptratio (SubAll)");
   hSubAll->SetAxisRange(0,zmax,"Z");
   hSubAll->Draw("colz");
   TProfile * hSubAll_pfx = hSubAll->ProfileX(Form("%s_pfx",hSubAll->GetName()),1,-1,"");
   hSubAll_pfx->DrawCopy("sameE");

   // Summarize
   TCanvas * cFin = new TCanvas("cFin","",1000,500);
   cFin->Divide(2,1);
   cFin->cd(1);
   hSigAll_pfx->SetMarkerStyle(kOpenCircle);
   hBkgDPhi_pfx->SetMarkerColor(kGreen+2);
   hBkgDPhi_pfx->SetLineColor(kGreen+2);
   hBkgDPhi_pfx->SetMarkerStyle(kOpenCircle);
   hBkgSS_pfx->SetMarkerColor(kMagenta);
   hBkgSS_pfx->SetLineColor(kMagenta);
   hBkgSS_pfx->SetMarkerStyle(kOpenCircle);
   hSigAll_pfx->SetAxisRange(0.45,1.12,"Y");
   hSigAll_pfx->Draw();
   hBkgDPhi_pfx->Draw("sameE");
   hBkgSS_pfx->Draw("sameE");
   
   cFin->cd(2);
   hSubDPhi_pfx->SetMarkerColor(kGreen+2);
   hSubDPhi_pfx->SetLineColor(kGreen+2);
   hSubDPhi_pfx->SetMarkerStyle(kOpenCircle);
   
   hSubSS_pfx->SetMarkerColor(kMagenta);
   hSubSS_pfx->SetLineColor(kMagenta);
   hSubSS_pfx->SetMarkerStyle(kOpenCircle);
   
   hSubAll_pfx->SetMarkerStyle(kFullCircle);
   hSubAll_pfx->SetMarkerColor(kRed);
   hSubAll_pfx->SetLineColor(kRed);

   hSigAll_pfx->SetAxisRange(0.45,1.2,"Y");
   hSigAll_pfx->Draw();
   hSubDPhi_pfx->Draw("sameE");
   hSubSS_pfx->Draw("sameE");
   hSubAll_pfx->Draw("sameE");
}