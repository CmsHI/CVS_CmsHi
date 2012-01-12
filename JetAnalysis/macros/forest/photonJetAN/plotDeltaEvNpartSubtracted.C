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
#include "commonUtility.h"
using namespace std;

TGraphAsymmErrors * getRBSignal(
                                float minPhoton = 60,
                                float minJet = 30,
                                float ajCut= 1,
                                TCut mycut="offlSel", TString myweight="1.",
                                TString infname = "../output-data-Photon-v3_v10.root",
                                int dataType=0, // 0=mc, 1=data, 2=pp
                                int isolScheme=2,
                                bool subDPhiSide=true,
                                bool subSShapeSide=true,
                                bool drawCheck=false
)
{
   // Get npart
   int nBin = 4;
   float * m = new float[nBin+1];
   m[0]=0;
   m[1]=4;
   m[2]=12;
   m[3]=20;
   m[4]=40;
   if (dataType==2) { // pp
      nBin = 1;
      m[0]=0;
      m[1]=40;
   }
   vector<TCut> vcutCent;
   for (int ib=0; ib<nBin; ++ib) vcutCent.push_back(Form("cBin>=%.1f&&cBin<%.1f",m[ib],m[ib+1]));
   float npart[nBin];// = {2,358.623,232.909,97.9521};
   GetNPartBins(infname, nBin, npart, m, minPhoton,dataType);
   cout << "got npart" << endl;

   // Analysis gamma-jet
   // open the data file
   TFile *inf = TFile::Open(infname);
   TTree *nt =(TTree*)inf->FindObjectAny("tgj");
   cout << "# " << endl;
   cout << "# " << inf->GetName() << " dataType: " << dataType << endl;
   cout << "# " << endl;
   
   TString name;   
   vector<SignalCorrector*> vana;
   // loop over centrality bins
   for (int ib=0; ib<nBin; ++ib) {
      if (dataType==0) { // mc
         name=Form("mc%d",ib);
      } else if (dataType==1) { // reco
         name=Form("hi%d",ib);
      } else if (dataType==2) { // reco
         name=Form("pp%d",ib);
      }      
      vana.push_back(new SignalCorrector(nt,name,"(jetEt/photonEt)",Form("photonEt>%.3f",minPhoton)&&mycut&&vcutCent[ib],myweight,ib));
      vana[ib]->cutBkgDPhi= Form("jetEt>%.3f&&acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta<0.01",minJet);
      vana[ib]->cutSShape= Form("jetEt>%.3f&&acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta>0.011 && sigmaIetaIeta<0.017",minJet);
      vana[ib]->cutSShapeDPhi= Form("jetEt>%.3f&&acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta>0.011 && sigmaIetaIeta<0.017",minJet);
      // analyze tree
      if (dataType==0) {
         vana[ib]->subDPhiSide = subDPhiSide;
         vana[ib]->subSShapeSide = false;
         vana[ib]->subSShapeSideDPhiSide = false;
         vana[ib]->MakeHistograms(Form("jetEt>%.03f && acos(cos(photonPhi-jetPhi))>2.0944",minJet),20,0.001,1.999);
      } else if (dataType==1||dataType==2) {
         vana[ib]->subDPhiSide = subDPhiSide;
         vana[ib]->subSShapeSide = subSShapeSide;
         vana[ib]->subSShapeSideDPhiSide = subDPhiSide&&subSShapeSide;
         vana[ib]->SetPhotonIsolation(isolScheme);
         vana[ib]->MakeHistograms(Form("jetEt>%.03f && acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta<0.01",minJet),20,0.001,1.999);
      }
      
      vana[ib]->Extrapolate(2.0944);
      vana[ib]->SubtractBkg();
      vana[ib]->Normalize(2);
   }
   
   // make graph
   TGraphAsymmErrors * gAve = new TGraphAsymmErrors(nBin);

   for (int ib=0;ib<gAve->GetN();++ib)
   {
      float y=vana[ib]->rSubtracted.hExtrapNorm->GetMean();
      float errYL = vana[ib]->rSubtracted.hExtrapNorm->GetMeanError();
      float errYH = vana[ib]->rSubtracted.hExtrapNorm->GetMeanError();
      gAve->SetPointError(ib,0,0,errYL,errYH);
      if (dataType!=2) gAve->SetPoint(ib,npart[ib],y);
      else {
         gAve->SetPoint(ib,2,y);
         cout<<" Setting PYTHIA point to npart=2 by hand"<<endl;
      }
      cout <<"bin: " << ib <<" npart: "<<npart[ib]<< " y: " << y << " yerr: " << errYH << endl;
   }
   
   // Draw count
   if (dataType==1) {
      TLegend *t3=new TLegend(0.1,0.2,0.5,0.45);
      t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,vana[0]->nameIsol,"");
      t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,"","");
      for (int ib=nBin-1;ib>=0;--ib) {
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,Form("%.0f to %.0f \%: %.0f #gamma-j",m[ib]*2.5,m[ib+1]*2.5,vana[ib]->rSubtracted.nExtrap),"");
      }
      //t3->AddEntry(anaNum.rSigAll.h,Form("#gamma purity %.2f",anaNum.photonPurity),"");
      t3->SetFillColor(0);
      t3->SetBorderSize(0);
      t3->SetFillStyle(0);
      t3->SetTextFont(63);
      t3->SetTextSize(15);
      t3->Draw();      
   }
   if (dataType==2) {
      TLegend *t3=new TLegend(0.1,0.2,0.5,0.45);
      t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,Form("pp: %.0f #gamma-j",vana[0]->rSubtracted.nExtrap),"");
      for (int ib=nBin-1;ib>=0;--ib) { t3->AddEntry("","",""); }
      t3->SetFillColor(0);
      t3->SetBorderSize(0);
      t3->SetFillStyle(0);
      t3->SetTextFont(63);
      t3->SetTextSize(15);
      t3->Draw();      
   }

   return gAve;
}

void plotDeltaEvNpartSubtracted(
                                float photonMinPt=60,
                                float minJet = 30,
                                int isolScheme=2,
                                int subDPhiSide=1,
                                int subSShapeSide=1,
                                TString outdir = "./fig/01.11v19AN"
                                )
{
   TH1::SetDefaultSumw2();
   int drawCheck = 0;

   TH1D *hTmp = new TH1D("hTmp","",100,-10,400);
   hTmp->SetXTitle("N_{part}");
   //hTmp->SetYTitle("<#DeltaE_{T}/E_{T,#gamma}> (GeV)");
   hTmp->SetYTitle("<x_{JG}>");
   hTmp->GetXaxis()->CenterTitle();
   hTmp->GetYaxis()->CenterTitle();
   hTmp->GetYaxis()->SetTitleOffset(1.4);
   hTmp->GetYaxis()->SetTitleSize(0.05);
   float ymin=0.45,ymax=1.2; // 35, 2, 0.4
   hTmp->SetAxisRange(ymin,ymax,"Y");
   TCanvas *c2 = new TCanvas("c","",500,500);
   hTmp->Draw();

   cout << endl << "     Data" << endl;
   TGraphAsymmErrors * gdata = getRBSignal(photonMinPt,minJet,-1,"anaEvtSel","(1==1)","../output-data-Photon-v7_v19.root",1,isolScheme,subDPhiSide,subSShapeSide,drawCheck);
   //cout << "returned graph with N points: " << gdata->GetN()<<endl;
   gdata->SetMarkerSize(1.25);
   gdata->SetMarkerColor(2);
   gdata->SetLineColor(2);
   gdata->Draw("p same");

   cout << endl << "     MC" << endl;
   TGraphAsymmErrors * ghypho = getRBSignal(photonMinPt,minJet,-1,"offlSel&&sampleWeight>0.5","weight","../output-hy18pho50mixdj80emdj120em_v18.root",0,isolScheme,subDPhiSide,subSShapeSide,drawCheck);
   ghypho->SetMarkerSize(1.25);
   ghypho->SetMarkerStyle(kOpenSquare);
   ghypho->Draw("p same");
   
   cout << endl << "     pp" << endl;
   TGraphAsymmErrors * gpp = getRBSignal(photonMinPt,minJet,-1,"anaEvtSel","(1==1)","../output-data-pp2010-prod3-photon_v18.root",2,isolScheme,subDPhiSide,subSShapeSide,drawCheck);
   gpp->SetMarkerSize(1.25);
   gpp->SetMarkerStyle(kOpenStar);
   gpp->SetMarkerColor(kBlue);
   gpp->Draw("p same");

   // Annotation
   drawText("CMS Preliminary",0.198,0.89,17);
   TLine* pline = new TLine(0,ghypho->GetY()[4],400,ghypho->GetY()[4]);
   pline->SetLineColor(4);
   pline->SetLineStyle(4);
   pline->Draw();   

   TH1D * hFrameDataSigAll = new TH1D("hFrameDataSigAll","",20,-0.999,0.999);
   hFrameDataSigAll->SetMarkerStyle(kOpenCircle);
   hFrameDataSigAll->SetMarkerColor(kGray+2);
   TH1D * hFrameDataBkg1 = new TH1D("hFrameDataBkg1","",20,-0.999,0.999);
   hFrameDataBkg1->SetMarkerStyle(kOpenCircle);
   hFrameDataBkg1->SetMarkerColor(kGreen+2);
   TH1D * hFrameDataBkg2 = new TH1D("hFrameDataBkg2","",20,-0.999,0.999);
   hFrameDataBkg2->SetMarkerStyle(kOpenCircle);
   hFrameDataBkg2->SetMarkerColor(kViolet);
   
   TLegend *leg=new TLegend(0.55,0.64,0.85,0.91);
   leg->AddEntry(gdata,"#intL dt = 150 #mub^{-1}","");
   leg->AddEntry(gdata,"PbPb  #sqrt{s}_{_{NN}}=2.76 TeV","p");
   leg->AddEntry(hFrameDataSigAll,"No Subtraction","p");
   if (drawCheck&&subDPhiSide) leg->AddEntry(hFrameDataBkg1,"|#Delta#phi| sideband","p");
   if (drawCheck&&subSShapeSide) leg->AddEntry(hFrameDataBkg2,"#sigma_{#eta#eta} sideband","p");
   leg->AddEntry(ghypho,"PYTHIA+HYDJET1.8","p");
   leg->AddEntry(gpp,"pp","p");
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetFillStyle(0);
   leg->SetTextFont(63);
   leg->SetTextSize(17);
   leg->Draw();
   
   TLegend *leg2=new TLegend(0.54,0.17,0.86,0.35);
   leg2->AddEntry(hTmp,Form("p_{T,#gamma} > %.0f GeV/c",photonMinPt),"");
   leg2->AddEntry(hTmp,Form("p_{T,jet} > %.0f GeV/c",minJet),"");
   leg2->AddEntry(hTmp,"#Delta#phi_{12} > #frac{2}{3}#pi","");
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->SetFillStyle(0);
   leg2->SetTextFont(63);
   leg2->SetTextSize(17);
   leg2->Draw();

   c2->Print(Form("%s/Photonv7_v19_DeltaESubDPhi%dSS%d_gamma%.0fjet%.0f_vs_Npart_Isol%d_drawChk%d.gif",outdir.Data(),subDPhiSide,subSShapeSide,photonMinPt,minJet,isolScheme,drawCheck));
   c2->Print(Form("%s/Photonv7_v19_DeltaESubDPhi%dSS%d_gamma%.0fjet%.0f_Npart_Isol%d_drawChk%d.pdf",outdir.Data(),subDPhiSide,subSShapeSide,photonMinPt,minJet,isolScheme,drawCheck));
}
