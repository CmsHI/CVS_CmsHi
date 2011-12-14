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
#include "TLine.h"
#include "DrawTick.C"
#include "npart.h"
using namespace std;

//---------------------------------------------------------------------
class Region
{
public:
   Region(TString n, TString v, TCut c, TString w) :
   name(n),var(v),cut(c),weight(w) {}
   void Init(TTree * t, int nbins, double * x, float frac, float area=1.) {
      fraction = frac;
      cut*=weight;
      h = new TH1D(name,"",nbins,x);
      cout << " ** " << h->GetName() << " with fraction: " << fraction << ", area: " << area << " **" << endl;
      //float nSel = t->Project(h->GetName(),var,cut);
      float nSel = t->Draw(Form("%s>>%s",var.Data(),h->GetName()),cut,"goff");
      cout << "draw: " << var << " cut: " << TString(cut) << ": " << nSel << endl;
      hNorm = (TH1D*)h->Clone(Form("%sNorm",h->GetName()));
      //if (h->Integral()>0) hNorm->Scale(area/h->Integral());
      hScaled = (TH1D*)hNorm->Clone(Form("%sScaled",hNorm->GetName()));
      cout << hScaled->GetName() << " ";
      cout << "scale by: " << area*fraction << endl;
      hScaled->Scale(fraction);
      for (int i=1; i<=hScaled->GetNbinsX()+1 ; ++i) cout << hScaled->GetBinLowEdge(i) << " (" << hScaled->GetBinContent(i) << ") ";
      cout << endl;
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
   SignalCorrector(TTree * tree, TString n, TCut s, TCut cutSig, TString w="(1==1)", int nm=1) : 
   name(n),
   sel(s),
   rSigAll(n+"SignalAll","cBin",s&&cutSig,w),
   rBkgDPhi(n+"BkgDPhi","cBin",s&&"acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta<0.01",w),
   rBkgSShape(n+"BkgSShape","cBin",s&&"acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta>0.011",w),
   weight(w),
   normMode(nm), // 0=area is signal region count, 1=unit normalization
   subDPhiSide(true),
   subSShapeSide(true) {
      t = tree;
   }
   
   void MakeHistograms(float fracPhotonBkg, int nBin, double * m) {
      // number of events in signal region
      float nSigAll = t->GetEntries(rSigAll.cut);
      float area=1.;
      if (normMode==0) area=nSigAll;
      rSigAll.Init(t,nBin,m,1,area);
      if (subDPhiSide) {
         // number of events in dphi sideband region
         float nDPhiSide = t->GetEntries(rBkgDPhi.cut);
         float nDPhiBkg = nDPhiSide * (3.14159-2.0944)/(3.14159/2.-0.7);
         float fracDPhiBkg = nDPhiBkg/nSigAll;
         rBkgDPhi.Init(t,nBin,m,fracDPhiBkg,area);
         cout << "|dhpi| sig all = " << nSigAll << "|dphi| side = " << nDPhiSide << " bck contamination: " << nDPhiBkg << " = " << fracDPhiBkg << endl;
      }
      if (subSShapeSide) {
         cout << "fracPhotonBkg: " << fracPhotonBkg << endl;
         rBkgSShape.Init(t,nBin,m,fracPhotonBkg,area);
      }
      
      hSubtracted = (TH1D*)rSigAll.hScaled->Clone(name+"Subtracted");
      if (subDPhiSide) hSubtracted->Add(rBkgDPhi.hScaled,-1);
      if (subSShapeSide) hSubtracted->Add(rBkgSShape.hScaled,-1);
      if (normMode==1) { // if unity normalization, rescale after subtraction
         hSubtracted->Scale(1./hSubtracted->Integral());
      }
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

TGraphAsymmErrors *calcEff(TH1* h1, TH1* hCut,double *npart, int dataType)
{
   cout << "Divide: " << hCut->GetName() << " by: " << h1->GetName() << endl;
   if (dataType==2) { // pp
      h1->Rebin(h1->GetNbinsX());
      hCut->Rebin(hCut->GetNbinsX());
   }
//   TGraphAsymmErrors *gEfficiency = new TGraphAsymmErrors();
//   cout << "hCut bins: ";
//   for (int i=1; i<=hCut->GetNbinsX()+1 ; ++i) cout << hCut->GetBinLowEdge(i) << " (" << hCut->GetBinContent(i) << ") ";
//   cout << endl << "h1 bins: ";
//   for (int i=1; i<=h1->GetNbinsX()+1 ; ++i) cout << h1->GetBinLowEdge(i) << " (" << h1->GetBinContent(i) << ") ";
//   cout << endl;
//   TCanvas * cc2 = new TCanvas("cc2","",500,500);
//   h1->Draw();
//   hCut->Draw("sameE");
//   gEfficiency->BayesDivide(hCut,h1);
   TH1D * hDiv = (TH1D*)hCut->Clone(Form("%s_div",hCut->GetName()));
   //hDiv->Divide(hCut,h1,1,1,"B");
   hDiv->Divide(hCut,h1,1,1);
   TGraphAsymmErrors *gEfficiency = new TGraphAsymmErrors(hDiv);
   cout << "graph N points: " << gEfficiency->GetN()<<endl;
//   TCanvas * cc3 = new TCanvas("cc3","",500,500);
//   gEfficiency->Draw("ap");
//   return gEfficiency;
   for (int i=0;i<gEfficiency->GetN();i++)
   {
      double x,y;
      gEfficiency->GetPoint(i,x,y);
      double errYL = gEfficiency->GetErrorYlow(i);
      double errYH = gEfficiency->GetErrorYhigh(i);
      gEfficiency->SetPointError(i,0,0,errYL,errYH);
      if (dataType!=2) gEfficiency->SetPoint(i,npart[h1->FindBin(x)-1],y);
      else {
         gEfficiency->SetPoint(i,2,y);
         cout<<" Setting PYTHIA point to npart=2 by hand"<<endl;
      }
      cout <<"x: " << x<<" "<<h1->FindBin(x)<<" "<<npart[h1->FindBin(x)-1]<< " y: " << y << endl;
   }
   return gEfficiency;
}

TGraphAsymmErrors * getRBSignal(
                                double threshold1 = 60,
                                double ajCut= 1,
                                TString infname = "../output-data-Photon-v3_v10.root",
                                int dataType=0, // 0=mc, 1=data, 2=pp
                                int isolScheme=2
)
{
   TString name=Form("photon%.0fdata%d",threshold1,dataType);
   // open the data file
   TFile *inf = new TFile(infname.Data());
   TTree *nt =(TTree*)inf->FindObjectAny("tgj");
   cout << inf->GetName() << " dataType: " << dataType << endl;
   
   // Get npart
   const int nBin = 5;
   double m[nBin+1] = {-0.5,3.5,7.5,11.5,20.5,40.5};
   //const int nBin = 6;
   //double m[nBin+1] = {-1.5,-0.5,3.5,7.5,11.5,20.5,40.5};
   //   const int nBin = 7;
   //   double m[nBin+1] = {-1.5,-0.5,3.5,7.5,11.5,20.5,31.5,40.5};
   double npart[nBin];// = {2,358.623,232.909,97.9521};
   EvtSel evt;
   GammaJet gj;
   nt->SetBranchAddress("evt",&evt.run);
   nt->SetBranchAddress("jet",&gj.photonEt);
   GetNPartBins(nt, evt, gj, nBin, npart, m, threshold1,dataType);
   cout << "got npart" << endl;

   // Analysis gamma-jet
   TCut cut1,cutIsol,cutAna;
   TString nameIsol;
   float photonPurity;
   if (isolScheme==0) { //sum isol
      nameIsol="Sum(Isol.)";
      cutIsol = "sumIsol/0.9<5";
      photonPurity=0.65;
   } else if (isolScheme==1) { // cut isol
      nameIsol="3DCutIsol.";
      cutIsol = "cc4 < 6.9 && ct4PtCut20 < 3.00 && cr4<5";
      photonPurity=0.64;
   } else if (isolScheme==2) { // fisher isol
      nameIsol="Fisher Isol.";
      nt->SetAlias("fisherIsol","(6.5481e-01 +cc5*8.127033e-03 +cc4*-1.275908e-02 +cc3*-2.24332e-02 +cc2*-6.96778e-02 +cc1*4.682052e-02 +cr5*-2.35164e-02 +cr4*1.74567e-03 +cr3*-2.39334e-04 +cr2*-3.1724e-02 +cr1*-3.65306e-02 +ct4PtCut20*1.8335e-02 +ct3PtCut20*-2.609068e-02 +ct2PtCut20*-4.523171e-02 +ct1PtCut20*-1.270661e-02 +ct5PtCut20*9.218723e-03)");
      cutIsol = "fisherIsol>0.3";
      //photonPurity=0.72;
      photonPurity=0.79;
   }
   cout << "Isolation: " << TString(cutIsol) << endl;

   // Setup cuts
   if (dataType==0) { // mc
      cut1=Form("offlSel&&photonEt>%.3f&&jetEt>30",threshold1)&&cutIsol;
   } else { // hi data or pp data
      cut1=Form("anaEvtSel&&photonEt>%.3f&&jetEt>30",threshold1)&&cutIsol;
   }
   cout <<cut1<<endl;
     
   // Get counts for numorator vs denominator
   cout << " === Get Denominator === " << endl;
   SignalCorrector anaDen(nt,name+"Den",cut1,"acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta<0.01","1==1",0);   
   anaDen.subDPhiSide = true;
   anaDen.subSShapeSide = false;
   if (dataType==0) anaDen.subSShapeSide = false; // assume 100% purity for gamma-jet mc
   anaDen.MakeHistograms(1-photonPurity,nBin,m);
   
   cout << " === Get Numerator === " << endl;
   SignalCorrector anaNum(nt,name+"Num",cut1,"acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta<0.01","photonEt-jetEt",0);   
   anaNum.subDPhiSide = true;
   anaNum.subSShapeSide = false;
   if (dataType==0) anaNum.subSShapeSide = false; // assume 100% purity for gamma-jet mc
   anaNum.MakeHistograms(1-photonPurity,nBin,m);

   TGraphAsymmErrors *g = calcEff(anaDen.hSubtracted,anaNum.hSubtracted,npart,dataType);
   
   if (dataType==1) {
      TGraphAsymmErrors *gSigAll = calcEff(anaDen.rSigAll.hScaled,anaNum.rSigAll.hScaled,npart,dataType);
      gSigAll->SetMarkerSize(1.25);
      gSigAll->SetLineColor(kGray+2);
      gSigAll->SetLineStyle(2);
      gSigAll->SetMarkerColor(kGray+2);
      gSigAll->SetMarkerStyle(kOpenCircle);
      gSigAll->Draw("p");
      if (anaNum.subDPhiSide) {
         TGraphAsymmErrors *gDPhiSide = calcEff(anaDen.rSigAll.hScaled,anaNum.rBkgDPhi.hScaled,npart,dataType);
         gDPhiSide->SetMarkerSize(1.25);
         gDPhiSide->SetLineColor(kGreen+2);
         gDPhiSide->SetLineStyle(2);
         gDPhiSide->SetMarkerColor(kGreen+2);
         gDPhiSide->SetMarkerStyle(kOpenCircle);
         gDPhiSide->Draw("p");
      }
      if (anaNum.subSShapeSide) {
         TGraphAsymmErrors *gSShapeSide = calcEff(anaDen.rSigAll.hScaled,anaNum.rBkgSShape.hScaled,npart,dataType);
         gSShapeSide->SetMarkerSize(1.25);
         gSShapeSide->SetLineColor(kViolet);
         gSShapeSide->SetLineStyle(2);
         gSShapeSide->SetMarkerColor(kViolet);
         gSShapeSide->SetMarkerStyle(kOpenCircle);
         gSShapeSide->Draw("p");
      }
   }
   return g;
}

void plotDeltaEvNpartSubtracted(
                                float photonMinPt=60
)
{
   TH1::SetDefaultSumw2();
   float ajCut=0.15;
   TCanvas *c2 = new TCanvas("c","",500,500);
   TH1D *hTmp = new TH1D("hTmp","",100,-10,400);
   hTmp->SetXTitle("N_{part}");
   hTmp->SetYTitle("<#DeltaE_{T}> (GeV)");
   hTmp->GetXaxis()->CenterTitle();
   hTmp->GetYaxis()->CenterTitle();
   hTmp->GetYaxis()->SetTitleOffset(1.4);
   hTmp->GetYaxis()->SetTitleSize(0.05);
   hTmp->SetAxisRange(0,35.,"Y");
   hTmp->Draw();

   cout << "     Data" << endl;
   TGraphAsymmErrors * gdata = getRBSignal(photonMinPt,ajCut,"../output-data-Photon-v2_v12.root",1);
   //cout << "returned graph with N points: " << gdata->GetN()<<endl;
   gdata->SetMarkerSize(1.25);
   gdata->SetMarkerColor(2);
   gdata->SetLineColor(2);
   gdata->Draw("p same");

   cout << "     MC" << endl;
   TGraphAsymmErrors * ghypho = getRBSignal(photonMinPt,ajCut,"../output-hypho50v2_50kyongsun_v12.root",0);
   ghypho->SetMarkerSize(1.25);
   ghypho->SetMarkerStyle(kOpenSquare);
   ghypho->Draw("p same");
   
   cout << "     pp" << endl;
   TGraphAsymmErrors * gpp = getRBSignal(photonMinPt,ajCut,"../output-data-pp2010-prod3-photon_v10.root",2);
   gpp->SetMarkerSize(1.25);
   gpp->SetMarkerStyle(kOpenStar);
   gpp->SetMarkerColor(kBlue);
   gpp->Draw("p same");

   // Annotation
   TLine* pline = new TLine(0,ghypho->GetY()[4],400,ghypho->GetY()[4]);
   pline->SetLineColor(4);
   pline->SetLineStyle(4);
   pline->Draw();
   
   TLatex *cms = new TLatex(0.1,0.91*35,"CMS Preliminary");
   cms->SetTextFont(63);
   cms->SetTextSize(17);
   cms->Draw();

   TH1D * hFrameDataSigAll = new TH1D("hFrameDataSigAll","",20,-0.999,0.999);
   hFrameDataSigAll->SetMarkerStyle(kOpenCircle);
   hFrameDataSigAll->SetMarkerColor(kGray+2);
   TH1D * hFrameDataBkg1 = new TH1D("hFrameDataBkg1","",20,-0.999,0.999);
   hFrameDataBkg1->SetMarkerStyle(kOpenCircle);
   hFrameDataBkg1->SetMarkerColor(kGreen+2);
   TH1D * hFrameDataBkg2 = new TH1D("hFrameDataBkg2","",20,-0.999,0.999);
   hFrameDataBkg2->SetMarkerStyle(kOpenCircle);
   hFrameDataBkg2->SetMarkerColor(kViolet);
   
   TLegend *leg=new TLegend(0.55,0.68,0.85,0.91);
   leg->AddEntry(gdata,"#intL dt = 84 #mub^{-1}","");
   leg->AddEntry(gdata,"PbPb  #sqrt{s}_{_{NN}}=2.76 TeV","p");
   leg->AddEntry(hFrameDataSigAll,"No Subtraction","p");
   leg->AddEntry(hFrameDataBkg1,"|#Delta#phi| sideband","p");
   //leg->AddEntry(hFrameDataBkg2,"#sigma_{i#etai#eta} sideband","p");
   leg->AddEntry(ghypho,"PYTHIA+HYDJET","p");
   leg->AddEntry(gpp,"pp","p");
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetFillStyle(0);
   leg->SetTextFont(63);
   leg->SetTextSize(17);
   leg->Draw();
   
   TLegend *leg2=new TLegend(0.16,0.62,0.49,0.80);
   leg2->AddEntry(hTmp,Form("p_{T,#gamma} > %.0f GeV/c",photonMinPt),"");
   leg2->AddEntry(hTmp,"p_{T,jet} > 30 GeV/c","");
   leg2->AddEntry(hTmp,"#Delta#phi_{12} > #frac{2}{3}#pi","");
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->SetFillStyle(0);
   leg2->SetTextFont(63);
   leg2->SetTextSize(17);
   leg2->Draw();

   c2->Print(Form("fig/12.13photonNorm/DeltaESubDPhivNpart_PhotonMin%.0f_Ratio_vs_Npart.gif",photonMinPt));
   c2->Print(Form("fig/12.13photonNorm/DeltaESubDPhivNpart_PhotonMin%.0f_Ratio_vs_Npart.pdf",photonMinPt));
}
