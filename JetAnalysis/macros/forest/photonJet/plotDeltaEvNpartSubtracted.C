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
#include "SignalCorrector.h"
using namespace std;

TGraphAsymmErrors *calcEff(TH1* h1, TH1* hCut,float *npart, int dataType)
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
//   TCanvas * cw = new TCanvas("cw","",500,500);
//   
//   TCanvas * cc2 = new TCanvas("cc2","",500,500);
//   h1->Draw("hist");
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
                                float threshold1 = 60,
                                float ajCut= 1,
                                TCut mycut="offlSel", TString myweight="1.",
                                TString infname = "../output-data-Photon-v3_v10.root",
                                int dataType=0, // 0=mc, 1=data, 2=pp
                                int isolScheme=1
)
{
   // open the data file
   TFile *inf = new TFile(infname.Data());
   TTree *nt =(TTree*)inf->FindObjectAny("tgj");
   cout << inf->GetName() << " dataType: " << dataType << endl;
   
   TString name=Form("photon%.0fdata%d",threshold1,dataType);

   // Get npart
   const int nBin = 5;
   float m[nBin+1] = {-0.5,3.5,7.5,11.5,20.5,40.5};
   //const int nBin = 6;
   //float m[nBin+1] = {-1.5,-0.5,3.5,7.5,11.5,20.5,40.5};
   //   const int nBin = 7;
   //   float m[nBin+1] = {-1.5,-0.5,3.5,7.5,11.5,20.5,31.5,40.5};
   float npart[nBin];// = {2,358.623,232.909,97.9521};
   EvtSel evt;
   GammaJet gj;
   nt->SetBranchAddress("evt",&evt.run);
   nt->SetBranchAddress("jet",&gj.photonEt);
   GetNPartBins(nt, evt, gj, nBin, npart, m, threshold1,dataType);
   cout << "got npart" << endl;

   // Analysis gamma-jet
   // Setup cuts
   TCut cut1=Form("photonEt>%.3f",threshold1)&&mycut;
   cout <<cut1<<endl;
     
   // Get counts for numorator vs denominator
   cout << " === Get Denominator === " << endl;
   SignalCorrector anaDen(nt,name+"Den","cBin",cut1,myweight,0); // normalization type 1=unity, 2=per sel photon
   anaDen.subDPhiSide = true;
   anaDen.subSShapeSide = false;
   anaDen.SetPhotonIsolation(isolScheme,0);
   anaDen.MakeHistograms("jetEt>30&&acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta<0.01",nBin,m);

   cout << " === Get Numerator === " << endl;
   //SignalCorrector anaNum(nt,name+"Num",cut1,"acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta<0.01","photonEt-jetEt",0);   
   //SignalCorrector anaNum(nt,name+"Num",cut1,"acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta<0.01","(photonEt-jetEt)/photonEt",0);   
   SignalCorrector anaNum(nt,name+"Num","cBin",cut1,"(photonEt-jetEt)/photonEt*"+myweight,0); // normalization type 1=unity, 2=per sel photon
   anaNum.subDPhiSide = true;
   anaNum.subSShapeSide = false;
   anaNum.SetPhotonIsolation(isolScheme,0);
   //anaNum.MakeHistograms(1-photonPurity,nBin,m);
   anaNum.MakeHistograms("jetEt>30&&acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta<0.01",nBin,m);

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
                                float photonMinPt=60,
                                int isolScheme=0
)
{
   TH1::SetDefaultSumw2();
   float ajCut=0.15;
   TH1D *hTmp = new TH1D("hTmp","",100,-10,400);
   hTmp->SetXTitle("N_{part}");
   //hTmp->SetYTitle("<#DeltaE_{T}> (GeV)");
   hTmp->SetYTitle("<#DeltaE_{T}/E_{T,#gamma}> (GeV)");
   hTmp->GetXaxis()->CenterTitle();
   hTmp->GetYaxis()->CenterTitle();
   hTmp->GetYaxis()->SetTitleOffset(1.4);
   hTmp->GetYaxis()->SetTitleSize(0.05);
   float ymax=0.4; // 35, 2, 0.4
   hTmp->SetAxisRange(0,ymax,"Y");
   TCanvas *c2 = new TCanvas("c","",500,500);
   hTmp->Draw();

   cout << "     Data" << endl;
   TGraphAsymmErrors * gdata = getRBSignal(photonMinPt,ajCut,"anaEvtSel","(1==1)","../output-data-Photon-v5_v15.root",1,isolScheme);
   //cout << "returned graph with N points: " << gdata->GetN()<<endl;
   gdata->SetMarkerSize(1.25);
   gdata->SetMarkerColor(2);
   gdata->SetLineColor(2);
   gdata->Draw("p same");

   cout << "     MC" << endl;
   TGraphAsymmErrors * ghypho = getRBSignal(photonMinPt,ajCut,"offlSel&&sampleWeight>0.5","(weight)","../output-hypho50mixdj80emdj120em_yongsun_v15.root",0,isolScheme);
   ghypho->SetMarkerSize(1.25);
   ghypho->SetMarkerStyle(kOpenSquare);
   ghypho->Draw("p same");
   
   cout << "     pp" << endl;
   TGraphAsymmErrors * gpp = getRBSignal(photonMinPt,ajCut,"offlSel","(1==1)","../output-data-pp2010-prod3-photon_v10.root",2,isolScheme);
   gpp->SetMarkerSize(1.25);
   gpp->SetMarkerStyle(kOpenStar);
   gpp->SetMarkerColor(kBlue);
   gpp->Draw("p same");

   // Annotation
   TLine* pline = new TLine(0,ghypho->GetY()[4],400,ghypho->GetY()[4]);
   pline->SetLineColor(4);
   pline->SetLineStyle(4);
   pline->Draw();
   
   TLatex *cms = new TLatex(0.1,0.91*ymax,"CMS Preliminary");
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
   leg->AddEntry(gdata,"#intL dt = 112 #mub^{-1}","");
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

   c2->Print(Form("fig/12.20AN/DeltaEFracSubDPhivNpart_PhotonMin%.0f_Ratio_vs_Npart_Isol%d.gif",photonMinPt,isolScheme));
   c2->Print(Form("fig/12.20AN/DeltaEFracSubDPhivNpart_PhotonMin%.0f_Ratio_vs_Npart_Isol%d.pdf",photonMinPt,isolScheme));
}
