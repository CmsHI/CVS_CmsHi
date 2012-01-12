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
#include "SignalCorrector.h"
#endif

//---------------------------------------------------------------------
SignalCorrector plotBalance(int cbin, TCut mycut, int isolScheme, int normMode,
                   TString infname,
                   TString weight, bool isData, int dataType, // 0=mc gen, 1=reco
                   TString opt,
                   int subDPhiSide = 1,
                   int subSShapeSide = 1,
                   float minPhoton=60,
                   float minJet=30,
                   bool doCheck=false)
{
   // open the data file
   TFile *inf = new TFile(infname.Data());
   TTree *nt =(TTree*)inf->FindObjectAny("tgj");
   cout << endl << "# " << endl;
   cout << "# " << infname << ": useWeight: " << weight << " isData: " << isData << " photon: " << minPhoton << " jet: " << minJet << endl;
   cout << "# " << endl;
   TString name;
   
   if (dataType==1) { // reco
      name=Form("reco%d",cbin);
   }
   else if (dataType==0) { // gen
      name=Form("gen%d",cbin);
   }

   SignalCorrector anaAgj(nt,name,"(jetEt/photonEt)",Form("photonEt>%.3f",minPhoton)&&mycut,weight,cbin);
   anaAgj.cutBkgDPhi= Form("jetEt>%.3f&&acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta<0.01",minJet);
   anaAgj.cutSShape= Form("jetEt>%.3f&&acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta>0.011 && sigmaIetaIeta<0.017",minJet);
   anaAgj.cutSShapeDPhi= Form("jetEt>%.3f&&acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta>0.011 && sigmaIetaIeta<0.017",minJet);
   
   // analyze tree
   if (dataType==0) {
      anaAgj.subDPhiSide = false;
      anaAgj.subSShapeSide = false;
      anaAgj.subSShapeSideDPhiSide = false;
      anaAgj.MakeHistograms(Form("jetEt>%.03f && acos(cos(photonPhi-jetPhi))>2.0944",minJet),20,0.001,1.999);
   } else if (dataType==1) {
      anaAgj.subDPhiSide = subDPhiSide;
      anaAgj.subSShapeSide = subSShapeSide;
      anaAgj.subSShapeSideDPhiSide = subDPhiSide&&subSShapeSide;
      anaAgj.SetPhotonIsolation(isolScheme);
      anaAgj.MakeHistograms(Form("jetEt>%.03f && acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta<0.01",minJet),20,0.001,1.999);
   }

   anaAgj.Extrapolate(2.0944);
   anaAgj.SubtractBkg();
   anaAgj.Normalize(normMode);

   // histogram style
   if (isData) {
      anaAgj.rSubtracted.hExtrapNorm->SetLineColor(kRed);
      anaAgj.rSubtracted.hExtrapNorm->SetMarkerColor(kRed);
      anaAgj.rSubtracted.hExtrapNorm->SetMarkerStyle(20);
   } else {
      if (dataType==0) {
         anaAgj.rSubtracted.hExtrapNorm->SetLineColor(kBlue);
         anaAgj.rSubtracted.hExtrapNorm->SetFillColor(kAzure-8);
         anaAgj.rSubtracted.hExtrapNorm->SetFillStyle(3005);
         anaAgj.rSubtracted.hExtrapNorm->SetMarkerStyle(0);
      } else if (dataType==1) {   
         anaAgj.rSubtracted.hExtrapNorm->SetLineColor(kBlue);
         anaAgj.rSubtracted.hExtrapNorm->SetFillColor(kAzure-8);
         anaAgj.rSubtracted.hExtrapNorm->SetFillStyle(3005);
         anaAgj.rSubtracted.hExtrapNorm->SetMarkerStyle(0);
      } else if (dataType==2) {   
         anaAgj.rSubtracted.hExtrapNorm->SetLineColor(kBlue);
         anaAgj.rSubtracted.hExtrapNorm->SetFillColor(kAzure-8);
         anaAgj.rSubtracted.hExtrapNorm->SetFillStyle(3004);
         anaAgj.rSubtracted.hExtrapNorm->SetStats(0);
         anaAgj.rSubtracted.hExtrapNorm->SetLineStyle(2);
         anaAgj.rSubtracted.hExtrapNorm->SetMarkerStyle(0);
      }
   }
   anaAgj.rSubtracted.hExtrapNorm->Draw(opt);

   // check subtraction
   if (doCheck) {
      if (anaAgj.subDPhiSide) {
         anaAgj.rBkgDPhi.hExtrapNorm->SetMarkerStyle(kOpenCircle);
         anaAgj.rBkgDPhi.hExtrapNorm->SetMarkerColor(kGreen+2);
         anaAgj.rBkgDPhi.hExtrapNorm->Draw("sameE");
      }
      if (anaAgj.subSShapeSide) {
         anaAgj.rBkgSShape.hExtrapNorm->SetMarkerStyle(kOpenCircle);
         anaAgj.rBkgSShape.hExtrapNorm->SetMarkerColor(kViolet);
         anaAgj.rBkgSShape.hExtrapNorm->Draw("sameE");
         anaAgj.rBkgSShapeDPhi.hExtrapNorm->SetMarkerSize(0.8);
         anaAgj.rBkgSShapeDPhi.hExtrapNorm->SetMarkerStyle(kOpenCircle);
         anaAgj.rBkgSShapeDPhi.hExtrapNorm->SetMarkerColor(kYellow+2);
         anaAgj.rBkgSShapeDPhi.hExtrapNorm->Draw("sameE");
      }
   }
   if (isData) {
      anaAgj.rSigAll.hExtrapNorm->SetLineStyle(2);
      anaAgj.rSigAll.hExtrapNorm->Draw("same hist");
      // Draw count
      float nPhotonJet = anaAgj.rSubtracted.nExtrap;
      float lx = 0.1;
      if (cbin==2||cbin==0) lx=-0.1;
      TLegend *t3=new TLegend(lx,0.7,0.5,0.85);
      if (cbin==0) t3->AddEntry(anaAgj.rSigAll.h,anaAgj.nameIsol,"");
      t3->AddEntry(anaAgj.rSigAll.h,Form("%.0f #gamma-jets",nPhotonJet),"");
      t3->AddEntry(anaAgj.rSigAll.h,Form("#gamma purity %.2f",1-anaAgj.fracPhotonBkg),"");
      t3->SetFillColor(0);
      t3->SetBorderSize(0);
      t3->SetFillStyle(0);
      t3->SetTextFont(63);
      t3->SetTextSize(15);
      t3->Draw();
   }
   return anaAgj;
}

//---------------------------------------------------------------------
void plotPtRatioSignal_AllCent4(
                                int isolScheme=0, // 0=sumIsol, 1=cutIsol, 2=fisherIsol
                                int normMode=2, // 1=unity, 2=per photon
                                int subDPhiSide = 1,
                                int subSShapeSide = 1,
                                float minPhoton=60,
                                float minJet=30,
                                TString outdir = "./fig/01.11v19AN"
                                )
{
   TH1::SetDefaultSumw2();

   int drawCheck = 1;

   TCanvas *c1 = new TCanvas("c1","",700,700);
   makeMultiPanelCanvas(c1,2,2,0.0,0.0,0.2,0.2,0.02);
   
   TFile * fout = new TFile("outhists.root","recreate");
   TH1D * hFrame = new TH1D("hFrame","",20,0.001,1.999);
   hFrame->SetAxisRange(0.001,1.999,"X");
   hFrame->SetAxisRange(-0.05,0.45,"Y");
   hFrame->SetStats(0);
   hFrame->SetXTitle("x_{JG} = p_{T}^{J}/p_{T}^{#gamma}");
   hFrame->SetYTitle("N_{#gamma}^{-1} dN/dx");
   if (normMode==1) hFrame->SetYTitle("Event Fraction");
   hFrame->GetXaxis()->SetLabelSize(22);
   hFrame->GetXaxis()->SetLabelFont(43);
   hFrame->GetXaxis()->SetTitleSize(24);
   hFrame->GetXaxis()->SetTitleFont(43);
   hFrame->GetXaxis()->SetTitleOffset(2);
   hFrame->GetXaxis()->CenterTitle();
   hFrame->GetXaxis()->SetNdivisions(505,true);
   hFrame->GetYaxis()->SetLabelSize(22);
   hFrame->GetYaxis()->SetLabelFont(43);
   hFrame->GetYaxis()->SetTitleSize(22);
   hFrame->GetYaxis()->SetTitleFont(43);
   hFrame->GetYaxis()->SetTitleOffset(2.6);
   hFrame->GetYaxis()->CenterTitle();
   hFrame->GetYaxis()->SetNdivisions(505,true);   
   TH1D * hFrameData = new TH1D("hFrameData","",20,0.001,1.999);
   TH1D * hFrameDataSigAll = new TH1D("hFrameDataSigAll","",20,0.001,1.999);
   hFrameDataSigAll->SetLineStyle(2);
   TH1D * hFrameDataBkg1 = new TH1D("hFrameDataBkg1","",20,0.001,1.999);
   hFrameDataBkg1->SetMarkerStyle(kOpenCircle);
   hFrameDataBkg1->SetMarkerColor(kGreen+2);
   TH1D * hFrameDataBkg2 = new TH1D("hFrameDataBkg2","",20,0.001,1.999);
   hFrameDataBkg2->SetMarkerStyle(kOpenCircle);
   hFrameDataBkg2->SetMarkerColor(kViolet);
   TH1D * hFrameMix = new TH1D("hFrameMix","",20,0.001,1.999);
   TH1D * hFrameGen = new TH1D("hFrameGen","",20,0.001,1.999);
   hFrameData->SetLineColor(kRed);
   hFrameData->SetMarkerColor(kRed);
   hFrameData->SetMarkerStyle(20);
   hFrameGen->SetLineColor(kBlue);
   hFrameGen->SetFillColor(kAzure-8);
   hFrameGen->SetFillStyle(3005);
   TH1D * hFrameNoY = (TH1D*)hFrame->Clone("hFrameNoY");
   hFrameNoY->SetYTitle("");
   
   c1->cd(1);
   hFrame->DrawClone();
   plotBalance(3,"offlSel&&sampleWeight>0.5&&cBin>=20&&cBin<40",isolScheme,normMode,"../output-hy18pho50mixdj80emdj120em_v18.root","weight",false,1,"samehistE",subDPhiSide,0,minPhoton,minJet,0);
   plotBalance(3,"anaEvtSel&&cBin>=20&&cBin<40",isolScheme,normMode,"../output-data-Photon-v7_v19.root","1==1",true,1,"sameE",subDPhiSide,subSShapeSide,minPhoton,minJet,drawCheck);
   drawText("50-100%",0.8,0.25);
   drawText("(a)",0.25,0.885);

   TLegend *t2=new TLegend(0.44,0.66,0.91,0.94);
   t2->AddEntry(hFrameData,"CMS Preliminary","");
   t2->AddEntry(hFrameData,"#intL dt = 150 #mub^{-1}","");
   t2->AddEntry(hFrameData,"#sqrt{s}_{_{NN}}=2.76 TeV","");
   t2->SetFillColor(0);
   t2->SetBorderSize(0);
   t2->SetFillStyle(0);
   t2->SetTextFont(63);
   t2->SetTextSize(17);
   t2->Draw();
   drawText("Ak PF, R=0.3",0.56,0.61,15);
   
   c1->cd(2);
   hFrameNoY->DrawClone();
   plotBalance(2,"offlSel&&sampleWeight>0.5&&cBin>=12&&cBin<20",isolScheme,normMode,"../output-hy18pho50mixdj80emdj120em_v18.root","weight",false,1,"samehistE",subDPhiSide,0,minPhoton,minJet,0);
   plotBalance(2,"anaEvtSel&&cBin>=12&&cBin<20",isolScheme,normMode,"../output-data-Photon-v7_v19.root","1==1",true,1,"sameE",subDPhiSide,subSShapeSide,minPhoton,minJet,drawCheck);
   drawText("30-50%",0.8,0.25);
   drawText("(b)",0.05,0.885);

   TLegend *t3=new TLegend(0.43,0.68,0.91,0.94); 
   t3->AddEntry(hFrameData,"PbPb","p");
   //t3->AddEntry(hFrameData,"PYQUEN_Quen+HYDJET","p");
   t3->AddEntry(hFrameDataSigAll,"No Subtraction","l");
   if (subDPhiSide&&drawCheck) t3->AddEntry(hFrameDataBkg1,"|#Delta#phi| sideband","p");
   if (subSShapeSide&&drawCheck) t3->AddEntry(hFrameDataBkg2,"#sigma_{#eta#eta} sideband","p");
   t3->AddEntry(hFrameGen,"PYTHIA+HYDJET1.8","lf");
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->SetFillStyle(0);
   t3->SetTextFont(63);
   t3->SetTextSize(15);
   t3->Draw();

   c1->cd(3);
   hFrame->DrawClone();
   plotBalance(1,"offlSel&&sampleWeight>0.5&&cBin>=4&&cBin<12",isolScheme,normMode,"../output-hy18pho50mixdj80emdj120em_v18.root","weight",false,1,"samehistE",subDPhiSide,0,minPhoton,minJet,0);
   plotBalance(1,"anaEvtSel&&cBin>=4&&cBin<12",isolScheme,normMode,"../output-data-Photon-v7_v19.root","1==1",true,1,"sameE",subDPhiSide,subSShapeSide,minPhoton,minJet,drawCheck);
   drawText("10-30%",0.8,0.4);
   drawText("(c)",0.25,0.885);

   TLegend *t4=new TLegend(0.43,0.7,0.91,0.94);
   t4->AddEntry(hFrameData,Form("p_{T}^{#gamma} > %.0f GeV/c",minPhoton),"");
   t4->AddEntry(hFrameData,Form("p_{T}^{jet} > %.0f GeV/c",minJet),"");
   t4->AddEntry(hFrameData,"#Delta#phi_{12} > #frac{2}{3}#pi","");
   t4->SetFillColor(0);
   t4->SetBorderSize(0);
   t4->SetFillStyle(0);
   t4->SetTextFont(63);
   t4->SetTextSize(15);
   t4->Draw();   

   c1->cd(4);
   hFrameNoY->DrawClone();
   plotBalance(0,"offlSel&&sampleWeight>0.5&&cBin>=0&&cBin<4",isolScheme,normMode,"../output-hy18pho50mixdj80emdj120em_v18.root","weight",false,1,"samehistE",subDPhiSide,0,minPhoton,minJet,0);
   plotBalance(0,"anaEvtSel&&cBin>=0&&cBin<4",isolScheme,normMode,"../output-data-Photon-v7_v19.root","1==1",true,1,"sameE",subDPhiSide,subSShapeSide,minPhoton,minJet,drawCheck);
   drawText("0-10%",0.75,0.4);
   drawText("(d)",0.05,0.885);

   c1->Print(Form("%s/Photonv7_v19_gamma%.0fjet%.0f_ptratio_all_cent4_subDPhi%dSS%d_Isol%d_Norm%d_drawChk%d.gif",outdir.Data(),minPhoton,minJet,subDPhiSide,subSShapeSide,isolScheme,normMode,drawCheck));
   c1->Print(Form("%s/Photonv7_v19_gamma%.0fjet%.0f_ptratio_all_cent4_subDPhi%dSS%d_Isol%d_Norm%d_drawChk%d.pdf",outdir.Data(),minPhoton,minJet,subDPhiSide,subSShapeSide,isolScheme,normMode,drawCheck));

//   save histograms
//   fout->Write();
}
