#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TString.h"
#include "TLine.h"
#include "TLegend.h"
#include <iostream>
using namespace std;

void checkPhotonSideBand(){
   TH1::SetDefaultSumw2();
   TFile * inf = TFile::Open("../output-hypho50mixdj80emdj120em_yongsun_v12.root");
   TTree * tgj = (TTree*)inf->Get("tgj");
   tgj->SetAlias("fisherIsol","(4.5536204845644690e-01 +cc5*-1.1621087258504197e-03 +cc4*-1.3139962130657250e-02 +cc3*9.8272534188056666e-03 +cc2*-7.9659880964355362e-02 +cc1*5.6661268034678275e-02 +cr5*-1.2763802967154852e-02 +cr4*-1.2594575465310987e-03 +cr3*-1.3333157740152167e-02 +cr2*-2.5518237583408113e-02 +cr1*-1.3706749407235775e-02 +ct4PtCut20*-7.9844325658248016e-03 +ct3PtCut20*-2.5276510400767658e-03 +ct2PtCut20*-2.0741636383420897e-02 +ct1PtCut20*7.1545293456054884e-04 +ct5PtCut20*7.8080659557798627e-03)");
   
   TCut sel = "(offlSel&&cBin<40&&photonEt>60&&jetEt>30&&acos(cos(photonPhi-jetPhi))>2.0944 && fisherIsol>0.2)";
   
   float nSig,nBkg,nBkgSide,nMix;
   TCanvas * c2 = new TCanvas("c2","",1000,500);
   c2->Divide(2,1);
   c2->cd(1);
   TH1D * hSSSig = new TH1D("hSSSig",";#sigma_{#eta#eta};u.n.",20,0,0.02);
   TH1D * hSSBkg = new TH1D("hSSBkg",";#sigma_{#eta#eta};u.n.",20,0,0.02);
   TH1D * hSSMix = new TH1D("hSSMix",";#sigma_{#eta#eta};u.n.",20,0,0.02);
   nSig = tgj->Draw("sigmaIetaIeta>>hSSSig",(sel)*"(sampleWeight>0.5)","");
   nBkg = tgj->Draw("sigmaIetaIeta>>hSSBkg",(sel)*"(sampleWeight<0.5)","");
   nMix = tgj->Draw("sigmaIetaIeta>>hSSMix",(sel)*Form("(sampleWeight>0.5)*0.62+(sampleWeight<0.5)*0.38/(%f/%f)",nBkg,nSig),"");
   hSSMix->Scale(1./hSSMix->Integral());
   hSSSig->Scale(1./hSSSig->Integral()*0.62);
   hSSBkg->Scale(1./hSSBkg->Integral()*0.38);
   hSSSig->Add(hSSBkg);
   hSSSig->SetLineColor(kBlue);
   hSSSig->SetFillColor(kAzure-8);
   hSSSig->SetFillStyle(3005);
   hSSBkg->SetLineColor(kGreen+2);
   hSSBkg->SetFillColor(kGreen+2);
   hSSBkg->SetFillStyle(1001);
   
   hSSSig->SetAxisRange(0,0.8,"Y");
   hSSSig->Draw("histf");
   hSSBkg->Draw("histfsame");
   hSSMix->Draw("sameE");
   hSSMix->SetLineColor(kRed);
   hSSMix->SetMarkerColor(kRed);
   hSSMix->SetLineColor(kRed);
   TLine * l = new TLine(0.011,0,0.011,hSSMix->GetMaximum());
   l->SetLineStyle(2);
   l->SetLineColor(kViolet);
   l->Draw();
   
   c2->cd(2);
   TH1D * hAjSig = new TH1D("hAjSig",";A_{GJ};u.n.",20,-1,1);
   TH1D * hAjBkg = new TH1D("hAjBkg",";A_{GJ};u.n.",20,-1,1);
   TH1D * hAjBkgSide = new TH1D("hAjBkgSide",";A_{GJ};u.n.",20,-1,1);
   TH1D * hAjMix = new TH1D("hAjMix",";A_{GJ};u.n.",20,-1,1);
   
   nSig = tgj->Draw("Agj>>hAjSig",(sel&&"sigmaIetaIeta<0.01")*"(sampleWeight>0.5)","");
   hAjSig->Scale(1./hAjSig->Integral());
   nBkg = tgj->Draw("Agj>>hAjBkg",TCut(sel&&"sigmaIetaIeta<0.01")*"(sampleWeight<0.5)","");
   hAjBkg->Scale(1./hAjBkg->Integral());
   nBkgSide = tgj->Draw("Agj>>hAjBkgSide",TCut(sel&&"sigmaIetaIeta>0.011")*Form("(sampleWeight>0.5)*0.62+(sampleWeight<0.5)*0.38/(%f/%f)",nBkg,nSig),"");
   hAjBkgSide->Scale(1./hAjBkgSide->Integral());
   cout << "nSig: " << nSig << " nBkg: " << nBkg << " nBkgSide: " << nBkgSide << endl;
   nMix = tgj->Draw("Agj>>hAjMix",TCut(sel&&"sigmaIetaIeta<0.01")*Form("(sampleWeight>0.5)*0.62+(sampleWeight<0.5)*0.38/(%f/%f)",nBkg,nSig),"");
   hAjMix->Scale(1./hAjMix->Integral());
   
   hAjSig->SetLineColor(kBlue);
   hAjSig->SetFillColor(kAzure-8);
   hAjSig->SetFillStyle(3005);
   hAjBkg->SetLineColor(kGreen+2);
   hAjBkgSide->SetLineColor(kViolet);
   hAjBkgSide->SetMarkerColor(kViolet);
   hAjBkgSide->SetMarkerStyle(kOpenCircle);
   hAjMix->SetLineColor(kRed);
   hAjMix->SetMarkerColor(kRed);
   hAjMix->SetLineColor(kRed);
   
   hAjSig->SetAxisRange(-0.05,0.50499,"Y");
   hAjSig->Draw("histf");
   hAjBkg->Draw("histsame");
   hAjBkgSide->Draw("sameE");
   hAjMix->Draw("sameE");
   
   TLegend *t3=new TLegend(0.58,0.75,0.97,0.93);
   t3->AddEntry(hAjSig,"Sig Sample","lf");
   t3->AddEntry(hAjBkg,"Bkg Sample","l");
   t3->AddEntry(hAjMix,"S+B Mixed","p");
   t3->AddEntry(hAjBkgSide,"#sigma_{i#etai#eta} sideband","p");
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->SetFillStyle(0);
   t3->SetTextSize(0.04);
   t3->Draw();

   c2->Print("./fig/12.15smixb/photon60mix_sig_vs_bkg.gif");
}