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
TH1D * plotBalance(int cbin, TCut mycut, int isolScheme, int normMode,
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
      if (cbin>=1&&cbin<=2) photonPurity=0.64;
      if (cbin>=3&&cbin<=4) photonPurity=0.57;
   } else if (isolScheme==1) { // cut isol
      nameIsol="3DCutIsol.";
      cutIsol = "cc4 < 6.9 && ct4PtCut20 < 3.00 && cr4<5";
      if (cbin==0) photonPurity=0.46;
      if (cbin>=1&&cbin<=2) photonPurity=0.62;
      if (cbin>=3&&cbin<=4) photonPurity=0.54;
   } else if (isolScheme==2) { // fisher isol
      nameIsol="Fisher Isol.";
      nt->SetAlias("fisherIsol","(4.5536204845644690e-01 +cc5*-1.1621087258504197e-03 +cc4*-1.3139962130657250e-02 +cc3*9.8272534188056666e-03 +cc2*-7.9659880964355362e-02 +cc1*5.6661268034678275e-02 +cr5*-1.2763802967154852e-02 +cr4*-1.2594575465310987e-03 +cr3*-1.3333157740152167e-02 +cr2*-2.5518237583408113e-02 +cr1*-1.3706749407235775e-02 +ct4PtCut20*-7.9844325658248016e-03 +ct3PtCut20*-2.5276510400767658e-03 +ct2PtCut20*-2.0741636383420897e-02 +ct1PtCut20*7.1545293456054884e-04 +ct5PtCut20*7.8080659557798627e-03)");
      cutIsol = "fisherIsol>0.2";
      if (cbin==0) photonPurity=0.62;
      if (cbin>=1&&cbin<=2) photonPurity=0.66;
      if (cbin>=3&&cbin<=4) photonPurity=0.64;
   }
   cout << "Isolation: " << TString(cutIsol) << endl;
   
   if (dataType==1) { // reco
      cut="offlSel&&photonEt>60"&&cutIsol;
      name=Form("reco%d",cbin);
   }
   else if (dataType==0) { // gen
      cut="photonEt>60 && jetEt>30 && acos(cos(photonPhi-jetPhi))>2.0944"; // gen
      name=Form("gen%d",cbin);
   }

   cut=cut&&mycut;
   SignalCorrector anaAgj(nt,name,"Agj",cut,"jetEt>30&&acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta<0.01",weight,normMode); // normalization type 1=unity, 2=per sel photon
   
   // analyze tree
   if (dataType==0) {
      anaAgj.subDPhiSide = false;
      anaAgj.subSShapeSide = false;
      anaAgj.rSigAll.cut = cut;
      anaAgj.MakeHistograms(0,20,-0.999,0.999);
   } else if (dataType==1) {
      anaAgj.subDPhiSide = true;
      anaAgj.subSShapeSide = false;
      if (!isData) anaAgj.subSShapeSide = false; // todo: get purity for mc sample
      anaAgj.MakeHistograms(1-photonPurity,20,-0.999,0.999);
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
      float nPhotonJet = anaAgj.nSigAll;
      if (anaAgj.subDPhiSide) nPhotonJet -= anaAgj.nSigAll * anaAgj.fracDPhiBkg;
      if (anaAgj.subSShapeSide) nPhotonJet -= anaAgj.nSigAll * anaAgj.fracPhotonBkg;
      float lx = 0.1;
      if (cbin%3==0) lx=-0.1;
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
void plotBalanceSignal_AllCent5(
                                int isolScheme=2, // 0=sumIsol, 1=cutIsol, 2=fisherIsol
                                int normMode=2 // 1=unity, 2=per photon
                                )
{
   TH1::SetDefaultSumw2();
   
   TCanvas *c1 = new TCanvas("c1","",1050,700);
   makeMultiPanelCanvas(c1,3,2,0.0,0.0,0.2,0.2,0.02);
   
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
   cout << "\n Centrality 50-100\%" << endl;
   hFrame->Draw();
   //plotBalance(2,-1,"../output-hypho50gen_v4.root",true,false,0,"samehist",false);
   plotBalance(4,"sampleWeight>0.5&&cBin>=20&&cBin<40",isolScheme,normMode,"../output-hypho50mixdj80emdj120em_yongsun_v15.root","weight",false,1,"samehistE",0);
   plotBalance(4,"anaEvtSel&&cBin>=20&&cBin<40",isolScheme,normMode,"../output-data-Photon-v5_v15.root","1==1",true,1,"sameE",1);
   //plotBalance(2,"sampleWeight>0.5",isolScheme,"../output-hypho50q_v15_frac62.root","weight",true,1,"sameE",1);
   drawText("50-100%",0.83,0.25);
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
   cout << "\n Centrality 30-50\%" << endl;
   hFrame->Draw();
   plotBalance(3,"sampleWeight>0.5&&cBin>=12&&cBin<20",isolScheme,normMode,"../output-hypho50mixdj80emdj120em_yongsun_v15.root","weight",false,1,"samehistE",0);
   plotBalance(3,"anaEvtSel&&cBin>=12&&cBin<20",isolScheme,normMode,"../output-data-Photon-v5_v15.root","1==1",true,1,"sameE",1);
   drawText("30-50%",0.8,0.25);
   drawText("(b)",0.05,0.885);

   TLegend *t3=new TLegend(0.44,0.68,0.91,0.94); 
   t3->AddEntry(hFrameData,"PbPb","p");
   //t3->AddEntry(hFrameData,"PYQUEN_Quen+HYDJET","p");
   t3->AddEntry(hFrameDataSigAll,"No Subtraction","l");
   t3->AddEntry(hFrameDataBkg1,"|#Delta#phi| sideband","p");
   t3->AddEntry(hFrameDataBkg2,"#sigma_{#eta#eta} sideband","p");
   t3->AddEntry(hFrameGen,"PYTHIA+HYDJET","lf");
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->SetFillStyle(0);
   t3->SetTextFont(63);
   t3->SetTextSize(15);
   t3->Draw();

   c1->cd(3);
   cout << "\n Centrality 20-30\%" << endl;
   hFrame->Draw();
   plotBalance(2,"sampleWeight>0.5&&cBin>=8&&cBin<12",isolScheme,normMode,"../output-hypho50mixdj80emdj120em_yongsun_v15.root","weight",false,1,"samehistE",0);
   plotBalance(2,"anaEvtSel&&cBin>=8&&cBin<12",isolScheme,normMode,"../output-data-Photon-v5_v15.root","1==1",true,1,"sameE",1);
   drawText("20-30%",0.8,0.25);
   drawText("(c)",0.05,0.885);

   TLatex tsel;
   tsel.SetNDC();
   tsel.SetTextFont(63);
   tsel.SetTextSize(15);
   tsel.DrawLatex(0.55,0.85,"p_{T}^{#gamma} > 60 GeV/c");
   tsel.DrawLatex(0.55,0.75,"p_{T}^{jet} > 30 GeV/c");
   tsel.DrawLatex(0.55,0.65,"#Delta#phi_{12} > #frac{2}{3}#pi");

   c1->cd(4);
   cout << "\n Centrality 10-20\%" << endl;
   hFrame->Draw();
   plotBalance(1,"sampleWeight>0.5&&cBin>=4&&cBin<8",isolScheme,normMode,"../output-hypho50mixdj80emdj120em_yongsun_v15.root","weight",false,1,"samehistE",0);
   plotBalance(1,"anaEvtSel&&cBin>=4&&cBin<8",isolScheme,normMode,"../output-data-Photon-v5_v15.root","1==1",true,1,"sameE",1);
   drawText("10-20%",0.8,0.3);
   drawText("(c)",0.05,0.885);
   
   c1->cd(5);
   cout << "\n Centrality 0-10\%" << endl;
   hFrame->Draw();
   plotBalance(0,"sampleWeight>0.5&&cBin>=0&&cBin<4",isolScheme,normMode,"../output-hypho50mixdj80emdj120em_yongsun_v15.root","weight",false,1,"samehistE",0);
   plotBalance(0,"anaEvtSel&&cBin>=0&&cBin<4",isolScheme,normMode,"../output-data-Photon-v5_v15.root","1==1",true,1,"sameE",1);
   drawText("0-10%",0.8,0.3);
   drawText("(e)",0.05,0.885);

   c1->Print(Form("./fig/12.19datav5_3/photon60_v15_jet30q_imbalance_all_cent5_subDPhi_Isol%d_Norm%d.gif",isolScheme,normMode));
   c1->Print(Form("./fig/12.19datav5_3/photon60_v15_jet30q_imbalance_all_cent5_subDPhi_Isol%d_Norm%d.pdf",isolScheme,normMode));

   // save histograms
//   fout->Write();
}
