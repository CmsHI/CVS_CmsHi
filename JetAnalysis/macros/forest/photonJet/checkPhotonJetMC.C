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
   TFile * inf = TFile::Open("../output-hy18pho50_37k_v18_frac74.root");
   TTree * tgj = (TTree*)inf->Get("tgj");
   //tgj->SetAlias("fisherIsol","(4.5536204845644690e-01 +cc5*-1.1621087258504197e-03 +cc4*-1.3139962130657250e-02 +cc3*9.8272534188056666e-03 +cc2*-7.9659880964355362e-02 +cc1*5.6661268034678275e-02 +cr5*-1.2763802967154852e-02 +cr4*-1.2594575465310987e-03 +cr3*-1.3333157740152167e-02 +cr2*-2.5518237583408113e-02 +cr1*-1.3706749407235775e-02 +ct4PtCut20*-7.9844325658248016e-03 +ct3PtCut20*-2.5276510400767658e-03 +ct2PtCut20*-2.0741636383420897e-02 +ct1PtCut20*7.1545293456054884e-04 +ct5PtCut20*7.8080659557798627e-03)");
   //TCut isolCut = "fisherIsol>0.2";
   TCut isolCut = "(cc4+cr4+ct4PtCut20)/0.9<1";
   TCut sel = "offlSel&&cBin<12&&photonEt>60&&sigmaIetaIeta<0.01"&&isolCut;
   
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
   
   TCanvas * c3 = new TCanvas("c3","",500,500);
   TH1D * hRecPtRat = new TH1D("hRecPtRat","",20,0,2);
   TH1D * hGenPtRat = new TH1D("hGenPtRat","",20,0,2);
   TH1D * hPartonPtRat = new TH1D("hPartonPtRat","",20,0,2);
   TH1D * hTreePtRat = new TH1D("hTreePtRat","",20,0,2);
   tgj->Draw("jetEt/photonEt>>hRecPtRat",sel&&"jetEt>30&&abs(dphi)>2.0944","E");
   tgj->Draw("refJetEt/photonEt>>hGenPtRat",sel&&"jetEt>30&&abs(dphi)>2.0944","same hist");
   tgj->Draw("refPartonPt/photonEt>>hPartonPtRat",sel&&"jetEt>30&&abs(dphi)>2.0944","same hist");
   tgj->Draw("refPartonPt/refPhoPt>>hTreePtRat",sel&&"jetEt>30&&abs(dphi)>2.0944","same hist");
   hRecPtRat->SetTitle(";jet p_{T} / photon p_{T};");
   hRecPtRat->SetAxisRange(0,1000,"Y");
   hGenPtRat->SetLineColor(kRed);
   hPartonPtRat->SetLineColor(kBlue);
   hTreePtRat->SetLineColor(kBlue);
   hTreePtRat->SetLineStyle(2);
   hRecPtRat->Draw("E");
   hGenPtRat->Draw("same hist");
   hPartonPtRat->Draw("same hist");
   hTreePtRat->Draw("same hist");

   TCanvas * c4 = new TCanvas("c4","",500,500);
   gPad->SetLogy();
   TH1D * hRecDPhi = new TH1D("hRecDPhi","",40,0,3.14159);
   TH1D * hGenDPhi = new TH1D("hGenDPhi","",40,0,3.14159);
   TH1D * hPartonDPhi = new TH1D("hPartonDPhi","",40,0,3.14159);
   tgj->Draw("acos(cos(jetPhi-photonPhi))>>hRecDPhi",sel&&"jetEt>30","E");
   tgj->Draw("acos(cos(refJetPhi-photonPhi))>>hGenDPhi",sel&&"jetEt>30","same hist");
   hRecDPhi->SetTitle(";#Delta#phi;");
   hRecDPhi->SetAxisRange(0.1,1e4,"Y");
   hGenDPhi->SetLineColor(kRed);
   hRecDPhi->Draw("E");
   hGenDPhi->Draw("same hist");
}