#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"
#include "TCut.h"

#include "commonUtility.h"
#endif

//---------------------------------------------------------------------
class Region
{
public:
   Region(TString n, TString v, TCut c, bool w) :
   name(n),var(v),cut(c),useWeight(w) {}
   void Init(TTree * t, int nbins, float xmin, float xmax, float frac) {
      fraction = frac;
      h = new TH1D(name,"",nbins,xmin,xmax);
      cout << "=== " << h->GetName() << " with fraction: " << fraction << " ===" << endl;
      if (useWeight) cut*="weight";
      float nSel = t->Project(h->GetName(),var,cut);
      cout << TString(cut) << ": " << nSel << endl;
      hNorm = (TH1D*)h->Clone(Form("%sNorm",h->GetName()));
      if (h->Integral()>0) hNorm->Scale(1./h->Integral());
      hScaled = (TH1D*)hNorm->Clone(Form("%sScaled",hNorm->GetName()));
      hScaled->Scale(fraction);
      // check
      t->Draw("cBin>>"+name+"_cbin(40,0,40)",cut,"goff");
   }
   
   TH1D * h;
   TH1D * hNorm;
   TH1D * hScaled;
   TString name;
   TString var;
   TCut cut;
   bool useWeight;
   float fraction;
};

//---------------------------------------------------------------------
class SignalCorrector
{
public:
   SignalCorrector(TTree * tree, TString n, TCut s, bool w=false) : 
   name(n),
   sel(s),
   rSigAll(n+"SignalAll","Agj",s&&"acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta<0.01",w),
   rBkgDPhi(n+"BkgDPhi","Agj",s&&"acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta<0.01",w),
   rBkgSShape(n+"BkgSShape","Agj",s&&"acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta>0.011",w),
   useWeight(w),
   subDPhiSide(true),
   subSShapeSide(true) {
      t = tree;
   }
   
   void MakeHistograms(float fracPhotonBkg) {
      rSigAll.Init(t,20,-0.999,0.999,1.);
      if (subDPhiSide) {
         float nDPhiSigAll = t->GetEntries(rSigAll.cut);
         float nDPhiSide = t->GetEntries(rBkgDPhi.cut);
         float nDPhiBkg = nDPhiSide * (3.14159-2.0944)/(3.14159/2.-0.7);
         float fracDPhiBkg = nDPhiBkg/nDPhiSigAll;
         rBkgDPhi.Init(t,20,-0.999,0.999,fracDPhiBkg);
         cout << "|dhpi| sig all = " << nDPhiSigAll << "|dphi| side = " << nDPhiSide << " bck contamination: " << nDPhiBkg << " = " << fracDPhiBkg << endl;
      }
      if (subSShapeSide) {
         cout << "fracPhotonBkg: " << fracPhotonBkg << endl;
         rBkgSShape.Init(t,20,-0.999,0.999,fracPhotonBkg);
      }
      
      hSubtracted = (TH1D*)rSigAll.hScaled->Clone(name+"Subtracted");
      if (subDPhiSide) hSubtracted->Add(rBkgDPhi.hScaled,-1);
      if (subSShapeSide) hSubtracted->Add(rBkgSShape.hScaled,-1);
      // Rescale after subtraction
      hSubtracted->Scale(1./hSubtracted->Integral());
   }
   TTree * t;
   TString name;
   TCut sel;
   Region rSigAll;
   Region rBkgDPhi;
   Region rBkgSShape;
   TH1D * hSubtracted;
   bool useWeight;
   bool subDPhiSide;
   bool subSShapeSide;
};

//---------------------------------------------------------------------
TH1D * plotBalance(int cbin, int isolScheme,
                   TString infname,
                   bool useWeight, bool isData, int dataType, // 0=mc gen, 1=reco
                   TString opt,
                   bool doCheck=false)
{
   // open the data file
   TFile *inf = new TFile(infname.Data());
   TTree *nt =(TTree*)inf->FindObjectAny("tgj");
   cout << "useWeight: " << useWeight << " isData: " << isData << endl;
   TCut cut,cutIsol;
   TString name,nameIsol;
   float photonPurity;
   if (isolScheme==0) { //sum isol
      nameIsol="Sum(Isol.)";
      cutIsol = "sumIsol/0.9<5";
      if (cbin==0) photonPurity=0.65;
      if (cbin==1) photonPurity=0.70;
      if (cbin==2) photonPurity=0.74;
   } else if (isolScheme==1) { // cut isol
      nameIsol="3DCutIsol.";
      cutIsol = "cc4 < 6.9 && ct4PtCut20 < 3.00 && cr4<5";
      if (cbin==0) photonPurity=0.64;
      if (cbin==1) photonPurity=0.68;
      if (cbin==2) photonPurity=0.70;
   } else if (isolScheme==2) { // fisher isol
      nameIsol="Fisher Isol.";
      nt->SetAlias("fisherIsol","(6.5481e-01 +cc5*8.127033e-03 +cc4*-1.275908e-02 +cc3*-2.24332e-02 +cc2*-6.96778e-02 +cc1*4.682052e-02 +cr5*-2.35164e-02 +cr4*1.74567e-03 +cr3*-2.39334e-04 +cr2*-3.1724e-02 +cr1*-3.65306e-02 +ct4PtCut20*1.8335e-02 +ct3PtCut20*-2.609068e-02 +ct2PtCut20*-4.523171e-02 +ct1PtCut20*-1.270661e-02 +ct5PtCut20*9.218723e-03)");
      cutIsol = "fisherIsol>0.3";
      if (cbin==0) photonPurity=0.72;
      if (cbin==1) photonPurity=0.74;
      if (cbin==2) photonPurity=0.79;
   }
   cout << "Isolation: " << TString(cutIsol) << endl;
   
   if (dataType==1) { // reco
      cut="photonEt>60 && jetEt>30"&&cutIsol;
      if (isData) cut = "anaEvtSel"&&cut;
      else cut = "offlSel"&&cut;
      name=Form("reco%d",cbin);
   }
   else if (dataType==0) { // gen
      cut="photonEt>60 && jetEt>30 && acos(cos(photonPhi-jetPhi))>2.0944"; // gen
      name=Form("gen%d",cbin);
   }

   TString cstring = "";
   if(cbin==-1) {
      cstring = "0-100%";
      cut= cut&&"cBin>=0 && cBin<40";
   }
   else if(cbin==0) {
      cstring = "0-10%";
      cut=cut&&"cBin>=0 && cBin<4";
   } else if (cbin==1) {
      cstring = "10-30%";
      cut=cut&&"cBin>=4 && cBin<12";
   } else  {
      cstring = "30-100%";
      cut=cut&&"cBin>=12 && cBin<40";
   }

   SignalCorrector anaAgj(nt,name,cut,useWeight);
   
   // analyze tree
   if (dataType==0) {
      anaAgj.subDPhiSide = false;
      anaAgj.subSShapeSide = false;
      anaAgj.rSigAll.cut = cut;
      anaAgj.MakeHistograms(0);
   } else if (dataType==1) {
      anaAgj.subDPhiSide = true;
      anaAgj.subSShapeSide = true;
      if (!isData) anaAgj.subSShapeSide = false; // todo: get purity for mc sample
      anaAgj.MakeHistograms(1-photonPurity);
   }
   
   // histogram style
   if (isData) {
      anaAgj.hSubtracted->SetLineColor(kRed);
      anaAgj.hSubtracted->SetMarkerColor(kRed);
      anaAgj.hSubtracted->SetMarkerStyle(20);
   } else {
      if (dataType==0) {
         anaAgj.hSubtracted->SetLineColor(kBlue);
         anaAgj.hSubtracted->SetFillColor(kAzure-8);
         anaAgj.hSubtracted->SetFillStyle(3005);
         anaAgj.hSubtracted->SetMarkerStyle(0);
      } else if (dataType==1) {   
         anaAgj.hSubtracted->SetLineColor(kBlue);
         anaAgj.hSubtracted->SetFillColor(kAzure-8);
         anaAgj.hSubtracted->SetFillStyle(3005);
         anaAgj.hSubtracted->SetMarkerStyle(0);
      } else if (dataType==2) {   
         anaAgj.hSubtracted->SetLineColor(kBlue);
         anaAgj.hSubtracted->SetFillColor(kAzure-8);
         anaAgj.hSubtracted->SetFillStyle(3004);
         anaAgj.hSubtracted->SetStats(0);
         anaAgj.hSubtracted->SetLineStyle(2);
         anaAgj.hSubtracted->SetMarkerStyle(0);
      }
   }
   anaAgj.hSubtracted->Draw(opt);
   if (doCheck) {
      if (anaAgj.subDPhiSide) {
         anaAgj.rBkgDPhi.hScaled->SetMarkerStyle(kOpenCircle);
         anaAgj.rBkgDPhi.hScaled->SetMarkerColor(kGreen+2);
         anaAgj.rBkgDPhi.hScaled->Draw("sameE");
      }
      if (anaAgj.subSShapeSide) {
         anaAgj.rBkgSShape.hScaled->SetMarkerStyle(kOpenCircle);
         anaAgj.rBkgSShape.hScaled->SetMarkerColor(kViolet);
         anaAgj.rBkgSShape.hScaled->Draw("sameE");
      }
      anaAgj.rSigAll.hScaled->SetLineStyle(2);
      anaAgj.rSigAll.hScaled->Draw("same hist");
      // Draw count
      float nPhotonJet = anaAgj.rSigAll.h->GetEntries();
      if (anaAgj.subDPhiSide) nPhotonJet -= anaAgj.rBkgDPhi.h->GetEntries()*(3.14159-2.0944)/(3.14159/2.-0.7);
      if (anaAgj.subSShapeSide) nPhotonJet -= anaAgj.rBkgSShape.h->GetEntries();
      float lx = 0.1;
      if (cbin<2) lx=-0.1;
      TLegend *t3=new TLegend(lx,0.7,0.5,0.85);
      if (cbin==0) t3->AddEntry(anaAgj.rSigAll.h,nameIsol,"");
      t3->AddEntry(anaAgj.rSigAll.h,Form("%.0f #gamma-jets",nPhotonJet),"");
      t3->AddEntry(anaAgj.rSigAll.h,Form("#gamma purity %.2f",photonPurity),"");
      t3->SetFillColor(0);
      t3->SetBorderSize(0);
      t3->SetFillStyle(0);
      t3->SetTextFont(63);
      t3->SetTextSize(15);
      t3->Draw();
   }
   return anaAgj.hSubtracted;
}

//---------------------------------------------------------------------
void plotBalanceSignal_AllCent3(
                                int isolScheme=2 // 0=sumIsol, 1=cutIsol, 2=fisherIsol
                                )
{
   TH1::SetDefaultSumw2();
   
   TCanvas *c1 = new TCanvas("c1","",1050,350);
   makeMultiPanelCanvas(c1,3,1,0.0,0.0,0.2,0.2,0.02);
   
   TFile * fout = new TFile("outhists.root","recreate");
   TH1D * hFrame = new TH1D("hFrame","",20,-0.999,0.999);
   hFrame->SetAxisRange(-0.4999,0.999,"X");
   hFrame->SetAxisRange(-0.05,0.50499,"Y");
   hFrame->SetStats(0);
   hFrame->SetXTitle("A_{#gamma J} = (p_{T}^{#gamma}-p_{T}^{J})/(p_{T}^{#gamma}+p_{T}^{J})");
   hFrame->SetYTitle("N_{evt}^{-1} dN/dA_{#gamma J}");
   hFrame->GetXaxis()->SetLabelSize(22);
   hFrame->GetXaxis()->SetLabelFont(43);
   hFrame->GetXaxis()->SetTitleSize(24);
   hFrame->GetXaxis()->SetTitleFont(43);
   hFrame->GetXaxis()->SetTitleOffset(1.2);
   hFrame->GetXaxis()->CenterTitle();
   hFrame->GetYaxis()->SetLabelSize(22);
   hFrame->GetYaxis()->SetLabelFont(43);
   hFrame->GetYaxis()->SetTitleSize(22);
   hFrame->GetYaxis()->SetTitleFont(43);
   hFrame->GetYaxis()->SetTitleOffset(1.2);
   hFrame->GetYaxis()->CenterTitle();
   hFrame->GetYaxis()->SetNdivisions(505,true);
   TH1D * hFrameData = new TH1D("hFrameData","",20,-0.999,0.999);
   TH1D * hFrameDataSigAll = new TH1D("hFrameDataSigAll","",20,-0.999,0.999);
   hFrameDataSigAll->SetLineStyle(2);
   TH1D * hFrameDataBkg1 = new TH1D("hFrameDataBkg1","",20,-0.999,0.999);
   hFrameDataBkg1->SetMarkerStyle(kOpenCircle);
   hFrameDataBkg1->SetMarkerColor(kGreen+2);
   TH1D * hFrameDataBkg2 = new TH1D("hFrameDataBkg2","",20,-0.999,0.999);
   hFrameDataBkg2->SetMarkerStyle(kOpenCircle);
   hFrameDataBkg2->SetMarkerColor(kViolet);
   TH1D * hFrameMix = new TH1D("hFrameMix","",20,-0.999,0.999);
   TH1D * hFrameGen = new TH1D("hFrameGen","",20,-0.999,0.999);
   hFrameData->SetLineColor(kRed);
   hFrameData->SetMarkerColor(kRed);
   hFrameData->SetMarkerStyle(20);
   hFrameGen->SetLineColor(kBlue);
   hFrameGen->SetFillColor(kAzure-8);
   hFrameGen->SetFillStyle(3005);
   
   c1->cd(1);
   cout << "\n Centrality 30-100\%" << endl;
   hFrame->Draw();
   //plotBalance(2,-1,"../output-hypho50gen_v4.root",true,false,0,"samehist",false);
   plotBalance(2,isolScheme,"../output-hypho50v2_50kyongsun_v10.root",true,false,1,"samehistE",0);
   plotBalance(2,isolScheme,"../output-data-Photon-v3_v9.root",false,true,1,"sameE",1);
   drawText("30-100%",0.83,0.3);
   drawText("(a)",0.25,0.885);
   TLatex *cms = new TLatex(0.24,0.43,"CMS Preliminary");
   cms->SetTextFont(63);
   cms->SetTextSize(17);
   cms->Draw();
   TLatex *lumi = new TLatex(0.24,0.30,"#intL dt = 84 #mub^{-1}");
   lumi->SetTextFont(63);
   lumi->SetTextSize(17);
   lumi->Draw();
   TLatex *cme = new TLatex(0.24,0.37,"#sqrt{s}_{_{NN}}=2.76 TeV");
   cme->SetTextFont(63);
   cme->SetTextSize(17);
   cme->Draw();
   TLatex *jetf_PbPb;
   jetf_PbPb = new TLatex(0.477,0.14,"Ak PF, R=0.3");
   jetf_PbPb->SetTextFont(63);
   jetf_PbPb->SetTextSize(15);
   jetf_PbPb->Draw();
   
   
   c1->cd(2);
   cout << "\n Centrality 10-30\%" << endl;
   hFrame->Draw();
   //plotBalance(1,-1,"../output-hypho50gen_v4.root",true,false,0,"samehist",false);
   plotBalance(1,isolScheme,"../output-hypho50v2_50kyongsun_v10.root",true,false,1,"samehistE",0);
   plotBalance(1,isolScheme,"../output-data-Photon-v3_v9.root",false,true,1,"sameE",1);
   drawText("10-30%",0.8,0.3);
   drawText("(b)",0.05,0.885);

   TLegend *t3=new TLegend(0.44,0.68,0.91,0.94); 
   t3->AddEntry(hFrameData,"PbPb","p");
   t3->AddEntry(hFrameDataSigAll,"No Subtraction","l");
   t3->AddEntry(hFrameDataBkg1,"|#Delta#phi| sideband","p");
   t3->AddEntry(hFrameDataBkg2,"#sigma_{i#etai#eta} sideband","p");
   t3->AddEntry(hFrameGen,"PYTHIA+HYDJET","lf");
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->SetFillStyle(0);
   t3->SetTextFont(63);
   t3->SetTextSize(15);
   t3->Draw();

   c1->cd(3);
   cout << "\n Centrality 0-10\%" << endl;
   hFrame->Draw();
   //plotBalance(0,-1,"../output-hypho50gen_v4.root",true,false,0,"samehist",false);
   plotBalance(0,isolScheme,"../output-hypho50v2_50kyongsun_v10.root",true,false,1,"samehistE",0);
   plotBalance(0,isolScheme,"../output-data-Photon-v3_v9.root",false,true,1,"sameE",1);
   drawText("0-10%",0.8,0.3);
   drawText("(c)",0.05,0.885);

   TLatex tsel;
   tsel.SetNDC();
   tsel.SetTextFont(63);
   tsel.SetTextSize(15);
   tsel.DrawLatex(0.55,0.85,"p_{T}^{#gamma} > 60 GeV/c");
   tsel.DrawLatex(0.55,0.75,"p_{T}^{jet} > 30 GeV/c");
   tsel.DrawLatex(0.55,0.65,"#Delta#phi_{12} > #frac{2}{3}#pi");

   c1->Print(Form("./fig/12.08svn/photon60v3_v9_jet30_imbalance_all_cent_subAll_Isol%d.gif",isolScheme));
   c1->Print(Form("./fig/12.08svn/photon60v3_v9_jet30_imbalance_all_cent_subAll_Isol%d.pdf",isolScheme));   

   // save histograms
//   fout->Write();
//   TCanvas * ctest = new TCanvas("ctest","",500,500);
//   hFrame->Draw();
//   plotBalance(0,"../output-data-Photon-v2d1204_v9.root",false,1,"sameE",1);
//   plotBalance(0,"../output-data-Photon-v3_v9.root",false,1,"sameE",1);
}
