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
   rSigAll(n+"SignalAll","acos(cos(photonPhi-jetPhi))",s&&"jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7 && sigmaIetaIeta<0.01",w),
   rBkgDPhi(n+"BkgDPhi","acos(cos(photonPhi-jetPhi))",s&&"jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta<0.01",w),
   rBkgSShape(n+"BkgSShape","acos(cos(photonPhi-jetPhi))",s&&"jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7 && sigmaIetaIeta>0.011",w),
   weight(w),
   normMode(nm), // 0=area is signal region count, 1=unit normalization, 2=per photon normalization
   subDPhiSide(true),
   subSShapeSide(true) {
      t = tree;
   }
   
   void MakeHistograms(float fracPhotonBkg) {
      // photon normalization
      float nSelPhoton = t->GetEntries(sel&&"sigmaIetaIeta<0.01");
      cout << "Number of selection photons: " << nSelPhoton << endl;
      // number of events in signal region
      float nSigAll = t->GetEntries(rSigAll.cut);
      float area=1.;
      if (normMode==0) area=nSigAll;
      if (normMode==2) area=nSigAll/nSelPhoton;
      rSigAll.Init(t,20,0.0001,3.1415926,1.,area);
      float fracDPhiBkg=0;
      if (subDPhiSide) {
         float nDPhiSide = t->GetEntries(rBkgDPhi.cut);
         float nDPhiBkg = nDPhiSide * (3.14159-2.0944)/(3.14159/2.-0.7);
         fracDPhiBkg = nDPhiBkg/nSigAll;
         rBkgDPhi.Init(t,20,0.0001,3.1415926,fracDPhiBkg,area);
         cout << "|dhpi| sig all = " << nSigAll << "|dphi| side = " << nDPhiSide << " bck contamination: " << nDPhiBkg << " = " << fracDPhiBkg << endl;
      }
      if (subSShapeSide) {
         cout << "fracPhotonBkg: " << fracPhotonBkg << endl;
         rBkgSShape.Init(t,20,0.0001,3.1415926,fracPhotonBkg,area);
      }
      
      hSubtracted = (TH1D*)rSigAll.hScaled->Clone(name+"Subtracted");
      if (subDPhiSide) hSubtracted->Add(rBkgDPhi.hScaled,-1);
      if (subSShapeSide) hSubtracted->Add(rBkgSShape.hScaled,-1);
      // Rescale after subtraction
      if (normMode==2&&subDPhiSide&&subSShapeSide) area*=(1-fracDPhiBkg-fracPhotonBkg)/(1-fracPhotonBkg);
      rSigAll.hScaled->Scale(area/rSigAll.hScaled->Integral());
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
};

//---------------------------------------------------------------------
TH1D * plotBalance(int cbin, int isolScheme,
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
      if (cbin==1) photonPurity=0.66;
      if (cbin==2) photonPurity=0.64;
   }
   cout << "Isolation: " << TString(cutIsol) << endl;
   
   if (dataType==1) { // reco
      cut="photonEt>60"&&cutIsol;
      if (isData) cut = "anaEvtSel"&&cut;
      else cut = "offlSel"&&cut;
      name=Form("reco%d",cbin);
   }
   else if (dataType==0) { // gen
      cut="photonEt>60 && jetEt>30 && acos(cos(photonPhi-jetPhi))>2.0944";
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
      float lx = 0.5;
      if (cbin>=2) lx+=0.1;
      TLegend *t3=new TLegend(lx,0.7,0.9,0.85);
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
void plotDeltaPhiSingal_AllCent3(
                                int isolScheme=2 // 0=sumIsol, 1=cutIsol, 2=fisherIsol
                                )
{
   TH1::SetDefaultSumw2();
   
   TCanvas *c1 = new TCanvas("c1","",1050,350);
   makeMultiPanelCanvas(c1,3,1,0.0,0.0,0.2,0.2,0.02);
   
   TFile * fout = new TFile("outhists.root","recreate");
   TH1D * hFrame = new TH1D("hFrame","",20,0.0001,3.1415926);
   hFrame->SetAxisRange(0.0001,3.1415926,"X");
   hFrame->SetAxisRange(1e-3,1,"Y");
   hFrame->SetStats(0);
   hFrame->SetXTitle("|#Delta#phi|");
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
   TH1D * hFrameData = new TH1D("hFrameData","",20,0.0001,3.1415926);
   TH1D * hFrameDataSigAll = new TH1D("hFrameDataSigAll","",20,0.0001,3.1415926);
   hFrameDataSigAll->SetLineStyle(2);
   TH1D * hFrameDataBkg1 = new TH1D("hFrameDataBkg1","",20,0.0001,3.1415926);
   hFrameDataBkg1->SetMarkerStyle(kOpenCircle);
   hFrameDataBkg1->SetMarkerColor(kGreen+2);
   TH1D * hFrameDataBkg2 = new TH1D("hFrameDataBkg2","",20,0.0001,3.1415926);
   hFrameDataBkg2->SetMarkerStyle(kOpenCircle);
   hFrameDataBkg2->SetMarkerColor(kViolet);
   TH1D * hFrameMix = new TH1D("hFrameMix","",20,0.0001,3.1415926);
   TH1D * hFrameGen = new TH1D("hFrameGen","",20,0.0001,3.1415926);
   hFrameData->SetLineColor(kRed);
   hFrameData->SetMarkerColor(kRed);
   hFrameData->SetMarkerStyle(20);
   hFrameGen->SetLineColor(kBlue);
   hFrameGen->SetFillColor(kAzure-8);
   hFrameGen->SetFillStyle(3005);
   
   c1->cd(1);
   gPad->SetLogy();
   cout << "\n Centrality 30-100\%" << endl;
   hFrame->Draw();
   //plotBalance(2,-1,"../output-hypho50gen_v4.root",true,false,0,"samehist",false);
   plotBalance(2,isolScheme,"../output-hypho50v2_50kyongsun_v12.root","weight",false,1,"samehistE",0);
   plotBalance(2,isolScheme,"../output-data-Photon-v2_v12.root","1==1",true,1,"sameE",1);
   drawText("30-100%",0.83,0.3);
   drawText("(a)",0.25,0.885);
   TLatex *cms = new TLatex(0.53,0.43,"CMS Preliminary");
   cms->SetTextFont(63);
   cms->SetTextSize(17);
   cms->Draw();
   TLegend *leg=new TLegend(0.18,0.54,0.48,0.79);
   leg->AddEntry(hFrameData,"#intL dt = 84 #mub^{-1}","");
   leg->AddEntry(hFrameData,"#sqrt{s}_{_{NN}}=2.76 TeV","");
   leg->AddEntry(hFrameData,"Ak PF, R=0.3","");
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetFillStyle(0);
   leg->SetTextFont(63);
   leg->SetTextSize(17);
   leg->Draw();
   
   c1->cd(2);
   gPad->SetLogy();
   cout << "\n Centrality 10-30\%" << endl;
   hFrame->Draw();
   //plotBalance(1,-1,"../output-hypho50gen_v4.root",true,false,0,"samehist",false);
   plotBalance(1,isolScheme,"../output-hypho50v2_50kyongsun_v12.root","weight",false,1,"samehistE",0);
   plotBalance(1,isolScheme,"../output-data-Photon-v2_v12.root","1==1",true,1,"sameE",1);
   drawText("10-30%",0.8,0.3);
   drawText("(b)",0.05,0.885);

   TLegend *t3=new TLegend(0.,0.60,0.54,0.86); 
   t3->AddEntry(hFrameData,"PbPb","p");
   t3->AddEntry(hFrameDataSigAll,"No Subtraction","l");
   //t3->AddEntry(hFrameDataBkg1,"|#Delta#phi| sideband","p");
   t3->AddEntry(hFrameDataBkg2,"#sigma_{i#etai#eta} sideband","p");
   t3->AddEntry(hFrameGen,"PYTHIA+HYDJET","lf");
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->SetFillStyle(0);
   t3->SetTextFont(63);
   t3->SetTextSize(15);
   t3->Draw();

   c1->cd(3);
   gPad->SetLogy();
   cout << "\n Centrality 0-10\%" << endl;
   hFrame->Draw();
   //plotBalance(0,-1,"../output-hypho50gen_v4.root",true,false,0,"samehist",false);
   plotBalance(0,isolScheme,"../output-hypho50v2_50kyongsun_v12.root","weight",false,1,"samehistE",0);
   plotBalance(0,isolScheme,"../output-data-Photon-v2_v12.root","1==1",true,1,"sameE",1);
   drawText("0-10%",0.8,0.3);
   drawText("(c)",0.05,0.885);

   TLegend *leg2=new TLegend(-0.1,0.54,0.48,0.79);
   leg2->AddEntry(hFrameData,"p_{T,#gamma} > 60 GeV/c","");
   leg2->AddEntry(hFrameData,"p_{T,jet} > 30 GeV/c","");
   //leg2->AddEntry(hFrameData,"#Delta#phi_{12} > #frac{2}{3}#pi","");
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->SetFillStyle(0);
   leg2->SetTextFont(63);
   leg2->SetTextSize(17);
   leg2->Draw();

   c1->Print(Form("./fig/12.14updatePurity/photon60v2_v12_mcv2yongsun_jet30_dphi_all_cent_subAll_Isol%d_photonNorm.gif",isolScheme));
   c1->Print(Form("./fig/12.14updatePurity/photon60v2_v12_mcv2yongsun_jet30_dphi_all_cent_subAll_Isol%d_photonNorm.pdf",isolScheme));   

   //TCanvas * call = new TCanvas("call","",500,500);
   //gPad->SetLogy();
   //cout << "\n Centrality 0-100\%" << endl;
   //hFrame->Draw();
   //plotBalance(-1,-1,"../output-hypho50gen_v4.root",true,false,0,"samehist",0);
   //plotBalance(-1,isolScheme,"../output-hypho50v2_50kyongsun_v12.root",true,false,1,"samehist",1);
   //plotBalance(-1,isolScheme,"../output-data-Photon-v2_v12.root",false,true,1,"sameE",1);
   //drawText("0-100%",0.8,0.3);
}
