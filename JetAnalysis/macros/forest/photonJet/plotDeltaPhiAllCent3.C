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

#endif


//---------------------------------------------------------------------
void makeMultiPanelCanvas(TCanvas*& canv, const Int_t columns, 
			  const Int_t rows, const Float_t leftOffset=0.,
                          const Float_t bottomOffset=0., 
			  const Float_t leftMargin=0.2, 
			  const Float_t bottomMargin=0.2,
                          const Float_t edge=0.05);

void plotDeltaPhi(int cbin = 0,
		 TString infname = "data.root",
		 TString pythia = "pythia.root",
		 TString mix = "mix.root",
		 bool useWeight = true,
		 bool drawXLabel = false,
		 bool drawLeg = false);

void plotPPDeltaPhiAll();

void drawText(const char *text, float xp, float yp);

//--------------------------------------------------------------
// drawPatch() is a crazy way of removing 0 in the second and third 
// pad which is partially shown due to no margin between the pads
// if anybody has a better way of doing it let me know! - Andre
//--------------------------------------------------------------
void drawPatch(float x1, float y1, float x2, float y2); 
//---------------------------------------------------------------------

void plotDeltaPhiAllCent3(){

   TCanvas *c1 = new TCanvas("c1","",1050,350);
   makeMultiPanelCanvas(c1,3,1,0.0,0.0,0.2,0.2,0.02);

 
  c1->cd(1);
  gPad->SetLogy(); 
  plotDeltaPhi(2,"output-40-HIBck.root","output-40-MC.root","output-40-MC.root",true,false,false);
  drawText("30-100%",0.25,0.6);
  drawText("(a)",0.25,0.885);
  TLatex *cms = new TLatex(1,0.7,"CMS Preliminary");
  cms->SetTextFont(63);
  cms->SetTextSize(17);
  cms->Draw();
  TLatex *lumi = new TLatex(1,0.20,"#intL dt = 40 #mub^{-1}");
  lumi->SetTextFont(63);
  lumi->SetTextSize(17);
  lumi->Draw();
  TLatex *cme = new TLatex(1,0.40,"#sqrt{s}_{_{NN}}=2.76 TeV");
  cme->SetTextFont(63);
  cme->SetTextSize(17);
  cme->Draw();


  c1->cd(2);
  gPad->SetLogy(); 
  plotDeltaPhi(1,"output-40-HIBck.root","output-40-MC.root","output-40-MC.root",true,true,true);
  drawText("10-30%",0.1,0.6);
  drawText("(b)",0.05,0.885);


  TLatex *jetf_PbPb;
//  jetf_PbPb = new TLatex(0.477,0.14,"Iterative Cone, R=0.5");
 // jetf_PbPb->SetTextFont(63);
//  jetf_PbPb->SetTextSize(15);
 // jetf_PbPb->Draw();

  c1->cd(3);
  gPad->SetLogy(); 
  plotDeltaPhi(0,"output-40-HIBck.root","output-40-MC.root","output-40-MC.root",true,false,false);
  drawText("0-10%",0.1,0.6);
  drawText("(c)",0.05,0.885);

  TLatex tsel;
  tsel.SetNDC();
  tsel.SetTextFont(63);
  tsel.SetTextSize(15);
  tsel.DrawLatex(0.45,0.85,"p_{T,#gamma} > 60 GeV/c");
  tsel.DrawLatex(0.45,0.75,"p_{T,jet} > 40 GeV/c");
  tsel.DrawLatex(0.45,0.65,"#Delta#phi_{12} > #frac{2}{3}#pi");

  c1->Print("./fig/dijet_imDeltaPhi_all_cent_20101126_v0.gif");
  c1->Print("./fig/dijet_imDeltaPhi_all_cent_20101126_v0.eps");
  c1->Print("./fig/dijet_imDeltaPhi_all_cent_20101126_v0.pdf");

}

void plotDeltaPhi(int cbin,
		 TString infname,
		 TString pythia,
		 TString mix,
		 bool useWeight,
		 bool drawXLabel,
		 bool drawLeg)
{

  TString cut="photonEt>60 && jetEt>40";
  TString cutpp="photonEt>60 && jetEt>40";

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
  TTree *nt =(TTree*)inf->FindObjectAny("nt");

  // open the pythia (MC) file
  TFile *infPythia = new TFile(pythia.Data());
  TTree *ntPythia = (TTree*) infPythia->FindObjectAny("nt");

  // open the datamix file
  TFile *infMix = new TFile(mix.Data());
  TTree *ntMix =(TTree*)infMix->FindObjectAny("nt");


  // projection histogram
  TH1D *h = new TH1D("h","",20,0.0001,3.1416);
  TH1D *hPythia = new TH1D("hPythia","",20,0.0001,3.1416);
  TH1D *hDataMix;
  if(cbin==2) hDataMix= new TH1D("hDataMix","",20,0.0001,3.1416);
  else if(cbin==0) hDataMix= new TH1D("hDataMix","",20,0.0001,3.1416);
  else hDataMix= new TH1D("hDataMix","",20,0.0001,3.1416);

  nt->Draw("acos(cos(photonPhi-jetPhi))>>h",Form("(%s)",cut.Data())); 
   
  if (useWeight) {
    // use the weight value caluculated by Matt's analysis macro
    ntMix->Draw("acos(cos(photonPhi-jetPhi))>>hDataMix",Form("(%s)*1",cutpp.Data())); 
  } else {
    // ignore centrality reweighting
    ntMix->Draw("acos(cos(photonPhi-jetPhi))>>hDataMix",Form("(%s)",cut.Data()));  
  }
  ntPythia->Draw("acos(cos(photonPhi-jetPhi))>>hPythia",Form("(%s)",cutpp.Data()));

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


  h->SetStats(0);
  hDataMix->SetLineStyle(2);
  hDataMix->SetMarkerStyle(0);
  h->GetXaxis()->SetLabelSize(22);
  h->GetXaxis()->SetLabelFont(43);
  h->GetXaxis()->SetTitleSize(24);
  h->GetXaxis()->SetTitleFont(43);
  h->GetXaxis()->SetTitleOffset(1.2);
  h->GetXaxis()->CenterTitle();
  
  
  h->GetYaxis()->SetLabelSize(22);
  h->GetYaxis()->SetLabelFont(43);
  h->GetYaxis()->SetTitleSize(22);
  h->GetYaxis()->SetTitleFont(43);
  h->GetYaxis()->SetTitleOffset(1.2);
  h->GetYaxis()->CenterTitle();
  
  if(drawXLabel) h->SetXTitle("|#Delta#phi|");  
  h->SetYTitle("Event Fraction");
  if(cbin==2)h->SetAxisRange(0.0001,3.1416,"X");
  else h->SetAxisRange(0.0001,3.1416,"X");

  if(cbin==2)h->SetAxisRange(0.003,1.2,"Y");
  else h->SetAxisRange(0.003,1.2,"Y");

  //hDataMix->GetXaxis()->SetNdivisions(905,true);
  h->GetYaxis()->SetNdivisions(505,true);
  
 
//  hDataMix->Draw("hist e");
  //hPythia->Draw("hist");  
  h->Draw("");
  hDataMix->Draw("hist e same");
  h->Draw("same");

  cout<<" mean value of data "<<h->GetMean()<<endl;
  if(drawLeg){
    TLegend *t3=new TLegend(0.46,0.70,0.91,0.86); 
    t3->AddEntry(h,"PbPb","p");
    //t3->AddEntry(hPythia,"PYTHIA","lf");  
    t3->AddEntry(hDataMix,"pp","lf");
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(63);
    t3->SetTextSize(15);
    t3->Draw();
  }

}

void drawPatch(float x1, float y1, float x2, float y2){
  TLegend *t1=new TLegend(x1,y1,x2,y2);
  t1->SetFillColor(kWhite);
  t1->SetBorderSize(0);
  t1->SetFillStyle(1001);
  t1->Draw("");
}

void drawText(const char *text, float xp, float yp){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(63);
  tex->SetTextSize(22);
  //tex->SetTextSize(0.05);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}


void makeMultiPanelCanvas(TCanvas*& canv,
                          const Int_t columns,
                          const Int_t rows,
                          const Float_t leftOffset,
                          const Float_t bottomOffset,
                          const Float_t leftMargin,
                          const Float_t bottomMargin,
                          const Float_t edge) {
   if (canv==0) {
      Error("makeMultiPanelCanvas","Got null canvas.");
      return;
   }
   canv->Clear();
   
   TPad* pad[columns][rows];

   Float_t Xlow[columns];
   Float_t Xup[columns];
   Float_t Ylow[rows];
   Float_t Yup[rows];
   Float_t PadWidth = 
   (1.0-leftOffset)/((1.0/(1.0-leftMargin)) +
   (1.0/(1.0-edge))+(Float_t)columns-2.0);
   Float_t PadHeight =
   (1.0-bottomOffset)/((1.0/(1.0-bottomMargin)) +
   (1.0/(1.0-edge))+(Float_t)rows-2.0);
   Xlow[0] = leftOffset;
   Xup[0] = leftOffset + PadWidth/(1.0-leftMargin);
   Xup[columns-1] = 1;
   Xlow[columns-1] = 1.0-PadWidth/(1.0-edge);

   Yup[0] = 1;
   Ylow[0] = 1.0-PadHeight/(1.0-edge);
   Ylow[rows-1] = bottomOffset;
   Yup[rows-1] = bottomOffset + PadHeight/(1.0-bottomMargin);

   for(Int_t i=1;i<columns-1;i++) {
      Xlow[i] = Xup[0] + (i-1)*PadWidth;
      Xup[i] = Xup[0] + (i)*PadWidth;
   }
   Int_t ct = 0;
   for(Int_t i=rows-2;i>0;i--) {
      Ylow[i] = Yup[rows-1] + ct*PadHeight;
      Yup[i] = Yup[rows-1] + (ct+1)*PadHeight;
      ct++;
   }

   TString padName;
   for(Int_t i=0;i<columns;i++) {
      for(Int_t j=0;j<rows;j++) {
         canv->cd();
         padName = Form("p_%d_%d",i,j);
         pad[i][j] = new TPad(padName.Data(),padName.Data(),
            Xlow[i],Ylow[j],Xup[i],Yup[j]);
         if(i==0) pad[i][j]->SetLeftMargin(leftMargin);
         else pad[i][j]->SetLeftMargin(0);

         if(i==(columns-1)) pad[i][j]->SetRightMargin(edge);
         else pad[i][j]->SetRightMargin(0);

         if(j==0) pad[i][j]->SetTopMargin(edge);
         else pad[i][j]->SetTopMargin(0);

         if(j==(rows-1)) pad[i][j]->SetBottomMargin(bottomMargin);
         else pad[i][j]->SetBottomMargin(0);

         pad[i][j]->Draw();
         pad[i][j]->cd();
         pad[i][j]->SetNumber(columns*j+i+1);
      }
   }
}


void plotPPDeltaPhiAll(){

  bool isPF = false;

  TString data_tag;
  TString mc_tag;
  TString jetfinder, jetfinder_tag;

  if(!isPF){
    data_tag = "hdata_ak5calo_DijetDeltaPhi";
    mc_tag = "hmc_ak5calo_DijetDeltaPhi_histonly";
    jetfinder_tag = "calo";
  }else{
    data_tag = "hdata_ak5pf_DijetDeltaPhi";
    mc_tag = "hmc_ak5pf_DijetDeltaPhi_histonly";
    jetfinder_tag ="pf";
  }

  TFile *fDATA = new TFile(Form("./pp/%s.root",data_tag.Data()));
  TFile *fMC = new TFile(Form("./pp/%s.root",mc_tag.Data()));

  TH1F *hDijetBal_data = (TH1F*) fDATA->Get("hDataDijetDeltaPhi");
  TH1F *hDijetBal_mc = (TH1F*) fMC->Get("hQCDDijetDeltaPhi");


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
  hDijetBal_mc->SetXTitle("|#Delta #phi|");
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
