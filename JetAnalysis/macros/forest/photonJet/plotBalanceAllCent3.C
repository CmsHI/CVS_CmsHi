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

#include "commonUtility.h"
#endif


//---------------------------------------------------------------------
void plotBalance(int cbin = 0,
                 TString infname = "data.root",
                 TString pythia = "pythia.root",
                 TString mix = "mix.root",
                 bool useWeight = true,
                 bool drawXLabel = false,
                 bool drawLeg = false);

void plotPPBalanceAll();

void plotBalanceAllCent3(){
   
   TCanvas *c1 = new TCanvas("c1","",1050,350);
   makeMultiPanelCanvas(c1,3,1,0.0,0.0,0.2,0.2,0.02);
   
   
   c1->cd(1);
   plotBalance(2,"../output-data-Photon-v1-pt60_v2.root","../output-hypho50gen-pt60_v2.root","../output-hypho50gen-pt60_v2.root",true,false,false);
   //plotBalance(2,"../output-hypho50-pt60.root","../output-hypho50gen-pt60.root","../output-hypho50gen-pt60.root",true,false,false);
   drawText("30-100%",0.7,0.3);
   drawText("(a)",0.25,0.885);
   TLatex *cms = new TLatex(0.24,0.43,"CMS Preliminary");
   cms->SetTextFont(63);
   cms->SetTextSize(17);
   cms->Draw();
   TLatex *lumi = new TLatex(0.24,0.30,"#intL dt = 40 #mub^{-1}");
   lumi->SetTextFont(63);
   lumi->SetTextSize(17);
   lumi->Draw();
   TLatex *cme = new TLatex(0.24,0.37,"#sqrt{s}_{_{NN}}=2.76 TeV");
   cme->SetTextFont(63);
   cme->SetTextSize(17);
   cme->Draw();
   
   
   c1->cd(2);
   plotBalance(1,"../output-data-Photon-v1-pt60_v2.root","../output-hypho50gen-pt60_v2.root","../output-hypho50gen-pt60_v2.root",true,true,true);
   drawText("10-30%",0.7,0.3);
   drawText("(b)",0.05,0.885);
   
   
   TLatex *jetf_PbPb;
   //  jetf_PbPb = new TLatex(0.477,0.14,"Iterative Cone, R=0.5");
   // jetf_PbPb->SetTextFont(63);
   //  jetf_PbPb->SetTextSize(15);
   // jetf_PbPb->Draw();
   
   c1->cd(3);
   plotBalance(0,"../output-data-Photon-v1-pt60_v2.root","../output-hypho50gen-pt60_v2.root","../output-hypho50gen-pt60_v2.root",true,false,false);
   drawText("0-10%",0.7,0.3);
   drawText("(c)",0.05,0.885);
   
   TLatex tsel;
   tsel.SetNDC();
   tsel.SetTextFont(63);
   tsel.SetTextSize(15);
   tsel.DrawLatex(0.55,0.85,"p_{T,#gamma} > 60 GeV/c");
   tsel.DrawLatex(0.55,0.75,"p_{T,jet} > 40 GeV/c");
   tsel.DrawLatex(0.55,0.65,"#Delta#phi_{12} > #frac{2}{3}#pi");
   
   c1->Print("./fig/dijet_imbalance_all_cent_20101130_v2.gif");
   c1->Print("./fig/dijet_imbalance_all_cent_20101130_v2.pdf");
   //c1->Print("./fig/dijet_mc_imbalance_all_cent_20101130_v0.gif");
   //c1->Print("./fig/dijet_mc_imbalance_all_cent_20101130_v0.pdf");
}

void plotBalance(int cbin,
                 TString infname,
                 TString pythia,
                 TString mix,
                 bool useWeight,
                 bool drawXLabel,
                 bool drawLeg)
{
   
   TString cut="photonEt>60 && jetEt>40 && acos(cos(photonPhi-jetPhi))>2.0944";
   TString cutpp="photonEt>60 && jetEt>40 && acos(cos(photonPhi-jetPhi))>2.0944";
   
   TString cstring = "";
   if(cbin==-1) {
      cstring = "0-100%";
      cut+=" && cBin>=0 && cBin<40";
   }
   else if(cbin==0) {
      cstring = "0-10%";
      cut+=" && cBin>=0 && cBin<4";
   } else if (cbin==1) {
      cstring = "10-30%";
      cut+=" && cBin>=4 && cBin<12";
   } else  {
      cstring = "30-100%";
      cut+=" && cBin>=12 && cBin<40";
   }
   // open the data file
   TFile *inf = new TFile(infname.Data());
   TTree *nt =(TTree*)inf->FindObjectAny("tgj");
   
   // open the pythia (MC) file
   TFile *infPythia = new TFile(pythia.Data());
   TTree *ntPythia = (TTree*) infPythia->FindObjectAny("tgj");
   
   // open the datamix file
   TFile *infMix = new TFile(mix.Data());
   TTree *ntMix =(TTree*)infMix->FindObjectAny("tgj");
   
   
   // projection histogram
   TH1D *h = new TH1D("h","",20,-0.999,0.999);
   TH1D *hPythia = new TH1D("hPythia","",20,-0.999,0.999);
   TH1D *hDataMix;
   if(cbin==2) hDataMix= new TH1D("hDataMix","",20,-0.999,0.999);
   else if(cbin==0) hDataMix= new TH1D("hDataMix","",20,-0.999,0.999);
   else hDataMix= new TH1D("hDataMix","",20,-0.999,0.999);
   
   nt->Draw("Agj>>h",Form("(%s)",cut.Data())); 
   
   if (useWeight) {
      // use the weight value caluculated by Matt's analysis macro
      ntMix->Draw("Agj>>hDataMix",Form("(%s)*1",cutpp.Data())); 
   } else {
      // ignore centrality reweighting
      ntMix->Draw("Agj>>hDataMix",Form("(%s)",cut.Data()));  
   }
   ntPythia->Draw("Agj>>hPythia",Form("(%s)",cutpp.Data()));
   
   // calculate the statistical error and normalize
   h->Sumw2();
   h->SetLineColor(kRed);
   h->SetMarkerColor(kRed);
   h->Scale(1./h->GetEntries());
   h->SetMarkerStyle(20);
   
   hPythia->Scale(1./hPythia->Integral(0,20));
   hPythia->SetLineColor(kBlue);
   hPythia->SetFillColor(kAzure-8);
   hPythia->SetFillStyle(3005);
   
   hDataMix->Sumw2();
   hDataMix->Scale(1./hDataMix->Integral(0,20));
   hDataMix->SetLineColor(kBlue);
   hDataMix->SetFillColor(kAzure-8);
   hDataMix->SetFillStyle(3004);
   
   
   hDataMix->SetStats(0);
   hDataMix->SetLineStyle(2);
   hDataMix->SetMarkerStyle(0);
   hDataMix->GetXaxis()->SetLabelSize(22);
   hDataMix->GetXaxis()->SetLabelFont(43);
   hDataMix->GetXaxis()->SetTitleSize(24);
   hDataMix->GetXaxis()->SetTitleFont(43);
   hDataMix->GetXaxis()->SetTitleOffset(1.2);
   hDataMix->GetXaxis()->CenterTitle();
   
   
   hDataMix->GetYaxis()->SetLabelSize(22);
   hDataMix->GetYaxis()->SetLabelFont(43);
   hDataMix->GetYaxis()->SetTitleSize(22);
   hDataMix->GetYaxis()->SetTitleFont(43);
   hDataMix->GetYaxis()->SetTitleOffset(1.2);
   hDataMix->GetYaxis()->CenterTitle();
   
   if(drawXLabel) hDataMix->SetXTitle("A_{GJ} = (p_{T,#gamma}-p_{T,Jet})/(p_{T,#gamma}+p_{T,Jet})");  
   hDataMix->SetYTitle("Event Fraction");
   if(cbin==2)hDataMix->SetAxisRange(-0.499,0.999,"X");
   else hDataMix->SetAxisRange(-0.499,0.999,"X");
   
   if(cbin==2)hDataMix->SetAxisRange(0,0.499,"Y");
   else hDataMix->SetAxisRange(0.0001,0.499,"Y");
   
   //hDataMix->GetXaxis()->SetNdivisions(905,true);
   hDataMix->GetYaxis()->SetNdivisions(505,true);
   
   
   hDataMix->Draw("hist e");
   //hPythia->Draw("hist");  
   h->Draw("same");
   
   cout<<" mean value of data "<<h->GetMean()<<endl;
   if(drawLeg){
      TLegend *t3=new TLegend(0.44,0.70,0.91,0.86); 
      t3->AddEntry(h,"PbPb","p");
      //t3->AddEntry(h,"PYTHIA+HYD Reco","p");
      t3->AddEntry(h,"PYTHIA+HYD Gen","l");
      //t3->AddEntry(hPythia,"PYTHIA","lf");  
      //t3->AddEntry(hDataMix,"pp","lf");
      //t3->AddEntry(hDataMix,"pp","lf");
      t3->SetFillColor(0);
      t3->SetBorderSize(0);
      t3->SetFillStyle(0);
      t3->SetTextFont(63);
      t3->SetTextSize(15);
      t3->Draw();
   }
   
}


void plotPPBalanceAll(){
   
   bool isPF = false;
   
   TString data_tag;
   TString mc_tag;
   TString jetfinder, jetfinder_tag;
   
   if(!isPF){
      data_tag = "hdata_ak5calo_DijetBalance";
      mc_tag = "hmc_ak5calo_DijetBalance_histonly";
      jetfinder_tag = "calo";
   }else{
      data_tag = "hdata_ak5pf_DijetBalance";
      mc_tag = "hmc_ak5pf_DijetBalance_histonly";
      jetfinder_tag ="pf";
   }
   
   TFile *fDATA = new TFile(Form("./pp/%s.root",data_tag.Data()));
   TFile *fMC = new TFile(Form("./pp/%s.root",mc_tag.Data()));
   
   TH1F *hDijetBal_data = (TH1F*) fDATA->Get("hDataDijetBalance");
   TH1F *hDijetBal_mc = (TH1F*) fMC->Get("hQCDDijetBalance");
   
   
   // normalization should be matched with what's in ANA
   hDijetBal_data->Scale(1./hDijetBal_data->Integral());
   hDijetBal_data->Rebin(2);
   
   hDijetBal_mc->Scale(1./hDijetBal_mc->Integral());
   hDijetBal_mc->Rebin(2);
   
   cout<<"Bin Width, pp = "<<hDijetBal_data->GetBinWidth(1)<<endl;
   cout<<"# of bins, pp = "<<hDijetBal_data->GetNbinsX()<<endl;
   cout<<"Max Bin Center, pp = "<<hDijetBal_data->GetBinCenter(25)<<endl;
   
   
   // canvas setting ---
   //  TCanvas *c1 = new TCanvas("c1","",490,530);
   
   // dum styling ----
   /*
    TH1F *hDum = new TH1F("hDum","",10,0,1.0);
    hDum->SetLineColor(kBlue);
    hDum->SetFillColor(kAzure-8);
    hDum->SetFillStyle(3005);
    */
   hDijetBal_mc->SetStats(0);
   hDijetBal_mc->SetXTitle("A_{J} = (E_{T}^{j1}-E_{T}^{j2})/(E_{T}^{j1}+E_{T}^{j2})");
   hDijetBal_mc->SetYTitle("Event Fraction");
   
   hDijetBal_mc->GetXaxis()->SetLabelSize(22);
   hDijetBal_mc->GetXaxis()->SetLabelFont(43);
   hDijetBal_mc->GetXaxis()->SetTitleSize(24);
   hDijetBal_mc->GetXaxis()->SetTitleFont(43);
   hDijetBal_mc->GetXaxis()->SetTitleOffset(2.4);
   hDijetBal_mc->GetXaxis()->CenterTitle();
   
   hDijetBal_mc->GetXaxis()->SetNdivisions(905,true);
   hDijetBal_mc->GetYaxis()->SetNdivisions(505,true);
   
   hDijetBal_mc->GetYaxis()->SetLabelSize(22);
   hDijetBal_mc->GetYaxis()->SetLabelFont(43);
   hDijetBal_mc->GetYaxis()->SetTitleSize(22);
   hDijetBal_mc->GetYaxis()->SetTitleFont(43);
   hDijetBal_mc->GetYaxis()->SetTitleOffset(3.);
   hDijetBal_mc->GetYaxis()->CenterTitle();
   
   hDijetBal_mc->SetAxisRange(0.0001,0.7,"Y");
   hDijetBal_mc->SetAxisRange(-0.999,0.999,"X");
   
   
   
   // data, mc styling
   hDijetBal_mc->SetLineColor(kBlue);
   hDijetBal_mc->SetFillColor(kAzure-8);
   hDijetBal_mc->SetFillStyle(3005);
   
   hDijetBal_mc->Draw("hist");
   
   hDijetBal_mc->Draw("hist");
   hDijetBal_data->Draw("pzsame");
   
   
   // Legend
   TLegend *t3a=new TLegend(0.57,0.6,0.89,0.8); 
   //t3a->SetHeader("ant-k_{T} (R=0.5) CaloJets");
   t3a->AddEntry(hDijetBal_data,"pp  #sqrt{s}=7.0 TeV","p");
   t3a->AddEntry(hDijetBal_mc,"PYTHIA","lf");
   t3a->SetFillColor(0);
   t3a->SetBorderSize(0);
   t3a->SetFillStyle(0);
   t3a->SetTextFont(63);
   t3a->SetTextSize(15);
   t3a->Draw();
   
   
   // other labeling
   TLatex *cms = new TLatex(0.34,0.23,"CMS");
   cms->SetTextFont(63);
   cms->SetTextSize(17);
   cms->Draw();
   
   TLatex *lumi_pp = new TLatex(0.50,0.23,"#intL dt = 35.1 pb^{-1}");
   lumi_pp->SetTextFont(63);
   lumi_pp->SetTextSize(15);
   lumi_pp->Draw();
   
   
   TLatex *jetf_pp;
   if(!isPF) jetf_pp = new TLatex(0.477,0.14,"Anti-k_{T}, R=0.5");
   else jetf_pp = new TLatex(0.477,0.14,"anti-k_{T} (R=0.5) PFJets");
   jetf_pp->SetTextFont(63);
   jetf_pp->SetTextSize(15);
   jetf_pp->Draw();
   
   
}
