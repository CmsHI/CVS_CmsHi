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
   Region(TString n, TString v, TCut c, TString w) :
   name(n),var(v),cut(c),weight(w) {}
   void Init(TTree * t, int nbins, float xmin, float xmax, float frac, float area=1.) {
      fraction = frac;
      cut*=weight;
      h = new TH1D(name,"",nbins,xmin,xmax);
      cout << " ** " << h->GetName() << " with fraction: " << fraction << " area: " << area << " **" << endl;
      float nSel = t->Project(h->GetName(),var,cut);
      cout << "draw: " << var << " cut: " << TString(cut) << ": " << nSel << endl;
      hNorm = (TH1D*)h->Clone(Form("%sNorm",h->GetName()));
      if (h->Integral()>0) hNorm->Scale(area/h->Integral());
      hScaled = (TH1D*)hNorm->Clone(Form("%sScaled",hNorm->GetName()));
      cout << hScaled->GetName() << " ";
      cout << "scale by: " << area*fraction << endl;
      hScaled->Scale(fraction);
      //for (int i=1; i<=hScaled->GetNbinsX()+1 ; ++i) cout << hScaled->GetBinLowEdge(i) << " (" << hScaled->GetBinContent(i) << ") ";
      //cout << endl;
      // check
      t->Draw("cBin>>"+name+"_cbin(40,0,40)",cut,"goff");
   }
   
   TH1D * h;
   TH1D * hNorm;
   TH1D * hScaled;
   TString name;
   TString var;
   TCut cut;
   TString weight;
   float fraction;
};

//---------------------------------------------------------------------
class SignalCorrector
{
public:
   SignalCorrector(TTree * tree, TString n, TCut s, TString w="(1==1)", int nm=1) : 
   name(n),
   sel(s),
   rSigAll(n+"SignalAll","Agj",s&&"jetEt>30&&acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta<0.01",w),
   rBkgDPhi(n+"BkgDPhi","Agj",s&&"jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta<0.01",w),
   rBkgSShape(n+"BkgSShape","Agj",s&&"jetEt>30&&acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta>0.011",w),
   weight(w),
   normMode(nm), // 0=area is signal region count, 1=unit normalization, 2=per photon normalization
   subDPhiSide(true),
   subSShapeSide(true),
   nSelPhoton(0),nSigAll(0),fracDPhiBkg(0),fracPhotonBkg(0) {
      t = tree;
   }
   
   void MakeHistograms(float frac2) {
      fracPhotonBkg=frac2;
      // photon normalization
      nSelPhoton = t->GetEntries(sel&&"sigmaIetaIeta<0.01");
      // number of events in signal region
      nSigAll = t->GetEntries(rSigAll.cut);
      cout << "Number of selection photons: " << nSelPhoton << " gamma-jets: " << nSigAll << endl;
      float area=1.;
      if (normMode==0) area=nSigAll;
      if (normMode==2) area=nSigAll/nSelPhoton;
      rSigAll.Init(t,20,-0.999,0.999,1.,area);
      if (subDPhiSide) {
         float nDPhiSide = t->GetEntries(rBkgDPhi.cut);
         float nDPhiBkg = nDPhiSide * (3.14159-2.0944)/(3.14159/2.-0.7);
         fracDPhiBkg = nDPhiBkg/nSigAll;
         rBkgDPhi.Init(t,20,-0.999,0.999,fracDPhiBkg,area);
         cout << "|dhpi| sig all = " << nSigAll << "|dphi| side = " << nDPhiSide << " bck contamination: " << nDPhiBkg << " = " << fracDPhiBkg << endl;
      }
      if (subSShapeSide) {
         cout << "fracPhotonBkg: " << fracPhotonBkg << endl;
         rBkgSShape.Init(t,20,-0.999,0.999,fracPhotonBkg,area);
      }
      
      hSubtracted = (TH1D*)rSigAll.hScaled->Clone(name+"Subtracted");
      if (subDPhiSide) hSubtracted->Add(rBkgDPhi.hScaled,-1);
      if (subSShapeSide) hSubtracted->Add(rBkgSShape.hScaled,-1);
      // Rescale after subtraction
      if (normMode==2&&subDPhiSide&&subSShapeSide) area*=(1-fracDPhiBkg-fracPhotonBkg)/(1-fracPhotonBkg);
      rSigAll.hScaled->Scale(area/rSigAll.hScaled->Integral());
      if (subSShapeSide) rBkgSShape.hScaled->Scale(area/rBkgSShape.hScaled->Integral());
      hSubtracted->Scale(area/hSubtracted->Integral());
   }
   TTree * t;
   TString name;
   TCut sel;
   Region rSigAll;
   Region rBkgDPhi;
   Region rBkgSShape;
   TH1D * hSubtracted;
   TString weight;
   int normMode;
   bool subDPhiSide;
   bool subSShapeSide;
   float nSelPhoton;
   float nSigAll;
   float fracDPhiBkg;
   float fracPhotonBkg;
};

//---------------------------------------------------------------------
TH1D * plotBalance(int cbin, TCut mycut, int isolScheme,
                   TString infname,
                   TString weight, bool isData, int dataType, // 0=mc gen, 1=reco
                   TString opt,
                   bool doCheck=false)
{
   // open the data file
   TFile *inf = new TFile(infname.Data());
   TTree *nt =(TTree*)inf->FindObjectAny("tgj");
   cout << "useWeight: " << weight << " isData: " << isData << endl;
   TCut cut,cutIsol;
   TString name,nameIsol;
   float photonPurity;
   if (isolScheme==0) { //sum isol
      nameIsol="Sum(Isol.)";
      cutIsol = "sumIsol/0.9<5";
      if (cbin==0) photonPurity=0.50;
      if (cbin==1) photonPurity=0.64;
      if (cbin==2) photonPurity=0.57;
   } else if (isolScheme==1) { // cut isol
      nameIsol="3DCutIsol.";
      cutIsol = "cc4 < 6.9 && ct4PtCut20 < 3.00 && cr4<5";
      if (cbin==0) photonPurity=0.46;
      if (cbin==1) photonPurity=0.62;
      if (cbin==2) photonPurity=0.54;
   } else if (isolScheme==2) { // fisher isol
      nameIsol="Fisher Isol.";
      nt->SetAlias("fisherIsol","(4.5536204845644690e-01 +cc5*-1.1621087258504197e-03 +cc4*-1.3139962130657250e-02 +cc3*9.8272534188056666e-03 +cc2*-7.9659880964355362e-02 +cc1*5.6661268034678275e-02 +cr5*-1.2763802967154852e-02 +cr4*-1.2594575465310987e-03 +cr3*-1.3333157740152167e-02 +cr2*-2.5518237583408113e-02 +cr1*-1.3706749407235775e-02 +ct4PtCut20*-7.9844325658248016e-03 +ct3PtCut20*-2.5276510400767658e-03 +ct2PtCut20*-2.0741636383420897e-02 +ct1PtCut20*7.1545293456054884e-04 +ct5PtCut20*7.8080659557798627e-03)");
      cutIsol = "fisherIsol>0.2";
      if (cbin==0) photonPurity=0.62;
      //if (cbin==0) photonPurity=0.744; // +20%
      //if (cbin==0) photonPurity=0.496; // -20%
      if (cbin==1) photonPurity=0.66;
      if (cbin==2) photonPurity=0.64;
   }
   cout << "Isolation: " << TString(cutIsol) << endl;
   
   if (dataType==1) { // reco
      cut="photonEt>60"&&cutIsol;
      name=Form("reco%d",cbin);
   }
   else if (dataType==0) { // gen
      cut="photonEt>60 && jetEt>30 && acos(cos(photonPhi-jetPhi))>2.0944"; // gen
      name=Form("gen%d",cbin);
   }

   cut=cut&&mycut;
   SignalCorrector anaAgj(nt,name,cut,weight,2);
   
   // analyze tree
   if (dataType==0) {
      anaAgj.subDPhiSide = false;
      anaAgj.subSShapeSide = false;
      anaAgj.rSigAll.cut = cut;
      anaAgj.MakeHistograms(0);
   } else if (dataType==1) {
      anaAgj.subDPhiSide = false;
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
      float nPhotonJet = anaAgj.nSigAll;
      if (anaAgj.subDPhiSide) nPhotonJet -= anaAgj.nSigAll * anaAgj.fracDPhiBkg;
      if (anaAgj.subSShapeSide) nPhotonJet -= anaAgj.nSigAll * anaAgj.fracPhotonBkg;
      TLegend *t3=new TLegend(0.18,0.73,0.57,0.88);
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
void plotBalanceSignal_SideSubClosure(
                                int isolScheme=2 // 0=sumIsol, 1=cutIsol, 2=fisherIsol
                                )
{
   TH1::SetDefaultSumw2();
   
   TCanvas *c1 = new TCanvas("c1","",1000,500);
   c1->Divide(2,1);
   
   TFile * fout = new TFile("outhists.root","recreate");
   TH1D * hFrame = new TH1D("hFrame","",20,-0.999,0.999);
   hFrame->SetAxisRange(-0.4999,0.999,"X");
   hFrame->SetAxisRange(-0.05,0.50499,"Y");
   hFrame->SetStats(0);
   hFrame->SetXTitle("A_{#gamma J} = (p_{T}^{#gamma}-p_{T}^{J})/(p_{T}^{#gamma}+p_{T}^{J})");
   hFrame->SetYTitle("N_{#gamma}^{-1} dN/dA_{#gamma J}");
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
   hFrame->Draw();
   TH1D * h = plotBalance(0,"offlSel&&cBin>=0&&cBin<40&&sampleWeight>0.5",isolScheme,"../output-hypho50mixdj80emdj120em_yongsun_v12.root","",false,1,"samehistE",0);
   h->Draw("hist sameE");
   TH1D * h2 = plotBalance(0,"offlSel&&cBin>=0&&cBin<40&&sampleWeight<0.5",isolScheme,"../output-hypho50mixdj80emdj120em_yongsun_v12.root","",false,1,"samehistE",0);
   h2->SetFillStyle(0);
   h2->SetLineColor(kGreen+2);
   h2->Draw("hist sameE");
   TH1D * h3 = plotBalance(0,"offlSel&&cBin>=0&&cBin<40",isolScheme,"../output-hypho50mixdj80emdj120em_yongsun_v12.root","(sampleWeight>0.5)*0.62+(sampleWeight<0.5)*0.38/(382./14038)",true,1,"samehistE",1);
   TH1D * h4 = plotBalance(0,"offlSel&&cBin>=0&&cBin<40",isolScheme,"../output-hypho50mixdj80emdj120em_yongsun_v12.root","(sampleWeight>0.5)*0.62+(sampleWeight<0.5)*0.38/(382./14038)",false,1,"samehistE",0);
   h3->Draw("sameE");
   drawText("0-100%",0.8,0.3);

   TLegend *t3=new TLegend(0.56,0.67,0.96,0.93); 
   t3->AddEntry(h3,"MC Subtracted","p");
   t3->AddEntry(hFrameDataSigAll,"No Subtraction","l");
   //t3->AddEntry(hFrameDataBkg1,"|#Delta#phi| sideband","p");
   t3->AddEntry(hFrameDataBkg2,"#sigma_{i#etai#eta} sideband","p");
   t3->AddEntry(h,"MC Sig","fl");
   t3->AddEntry(h2,"MC Bkg","l");
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->SetFillStyle(0);
   t3->SetTextFont(63);
   t3->SetTextSize(15);
   t3->Draw();
   
   c1->cd(2);
   TH1D * hRat3 = (TH1D*)h3->Clone("hRat3");
   hRat3->Divide(h);
   hRat3->SetYTitle("Ratio");
   hRat3->SetAxisRange(-0.4999,0.999,"X");
   hRat3->SetAxisRange(-2,4,"Y");
   hRat3->SetXTitle("A_{#gamma J} = (p_{T}^{#gamma}-p_{T}^{J})/(p_{T}^{#gamma}+p_{T}^{J})");
   hRat3->Draw("E");
   TH1D * hRat4 = (TH1D*)h4->Clone("hRat");
   hRat4->Divide(h);
   hRat4->SetMarkerStyle(kOpenCircle);
   hRat4->SetMarkerColor(kBlack);
   hRat4->SetLineColor(kBlack);
   hRat4->SetLineStyle(2);
   hRat4->Draw("sameE");
   TLine * l1 = new TLine(-0.4999,1,0.999,1);
   l1->Draw();
   
   c1->Print(Form("./fig/12.15smixb/photon60mix_v12_jet30_imbalance_Isol%d_photonNorm_PhotonSubClosurePurity.gif",isolScheme));
   c1->Print(Form("./fig/12.15smixb/photon60mix_v12_jet30_imbalance_Isol%d_photonNorm_PhotonSubClosurePurity.pdf",isolScheme));
}
