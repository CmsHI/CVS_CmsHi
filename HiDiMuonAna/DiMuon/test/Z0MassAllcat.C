////////////////////////////////////////////////////////
// Fit Macro for Z0 in dimuon channel 
//
// Authors: CMS Heavy Ion Dilepton PiNG 
// Prashant Shukla and Vineet Kumar
/////////////////////////////////////////////////////////

#ifndef __CINT__
#include <iostream>
#include "TROOT.h"
#include "TStyle.h"
#include "TPad.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TLatex.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TLine.h"
#include <TObjArray.h>
#include <TTree.h>
#include "stdio.h"
#endif

#include "FitFunctions.h"

void Z0MassAllcat(int isData=1, int nff = 1, int yieldInt = 1, int iSpec = 1)
{

  ////////  definitions of Switches   ///////////
  //  isData = 1 for Data
  //  isData = 2 for Simulation

  //  nff = 1  RBW + Pol2  
  //  nff = 2  Gaus + Pol2 
  //  nff = 3  RBWGaus + Pol2 

  //  yieldInt = 1  Bin counting 
  //  yieldInt = 2  Integral

  // iSpec = 1  pT spectra
  // iSpec = 2  Y spectra
  // iSpec = 3  Centrality Spectra


  ////////////////////////////////////////////////////////////

  //  gStyle->SetPadTopMargin(0.15);
  //  gStyle->SetPadBottomMargin(0.13);
  //  gStyle->SetPadLeftMargin(0.13);
  //  gStyle->SetPadRightMargin(0.15);
    
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(600); //Height of canvas
  gStyle->SetCanvasDefW(600); //Width of canvas

  gStyle->SetOptTitle(0);
  //gStyle->SetOptStat(1);

  gStyle->SetOptStat(0);
  //  gStyle->SetOptFit(1111);
  gStyle->SetOptFit(0000); 

  gStyle->SetCanvasColor(10);
  gStyle->SetPadColor(0);
  gStyle->SetHistLineWidth(1.0);

  // PDG values for Z0
  double MassZ0 = 91.1876;
  double WidthZ0 = 2.4952;

  // Fit ranges
  float mass_low = 20.0;
  float mass_high = 120.0;
  
  // Efficiency
  float Eff_cat_1[10],Eff_cat_2[10], Eff_cat_3[10]; 
  

  char *Xname[] = {" ", "p_{T} (GeV/c)", "rapidity", "centrality"};

  // Pt bin sizes
  int Nptbin;
  float GenRange;
  double pt_bound[10];
		
  if(iSpec == 1) { 
    Nptbin = 5;
    GenRange = 20;
    double pt_bound[10] = {0.0, 4.0, 8.0, 12.0, 16.0, 20.0};
  }

  // Y bin sizes
  if(iSpec == 2) {
    Nptbin = 3;
    GenRange = 4.8;
    double pt_bound[10] = {-2.4, -0.8, 0.8, 2.4};
  }

  // Cen bin sizes
  if(iSpec == 3) {
    Nptbin = 4;
    GenRange = 40;
    double pt_bound[10] = {0, 4, 8, 16, 40};
  }

  double PT[10], DelPT[10], mom_err[100];
  for (Int_t ih = 0; ih < Nptbin; ih++) {
    PT[ih] = (pt_bound[ih] + pt_bound[ih+1])/2.0;
    DelPT[ih] = pt_bound[ih+1] - pt_bound[ih];
    mom_err[ih] = DelPT[ih]/2.0;
  }

  // Generated Numbers 
  int  TotalFlat = 5000;
  float gen_pt[10];

  for (Int_t ih = 0; ih < Nptbin; ih++) {
    gen_pt[ih] = TotalFlat*DelPT[ih]/GenRange;
  }
  
  // Fit Function RBW + Pol2

  char *name_fit[] = {"  ", "RBWPol2", "GausPol2", "RBWGausPol2"};

  if(nff == 1) TF1 *RBWPOL = new TF1("RBWPOL", RBWPol2, 0, 200, 6);
  if(nff == 2) TF1 *RBWPOL = new TF1("RBWPOL", GausPol2, 0, 200, 6);
  if(nff == 3) TF1 *RBWPOL = new TF1("RBWPOL", RBWGausPol2, 0, 200, 7);

  //  RBWPOL->SetLineWidth(1);

  RBWPOL->SetParameter(1, MassZ0);
  RBWPOL->SetParameter(2, WidthZ0);

  RBWPOL->SetParLimits(1, 86, 98);
  RBWPOL->SetParLimits(2, 0.8, 20);
  
  if(nff == 1 || nff == 2) RBWPOL->FixParameter(5, 0);

  if(nff == 3) {
    RBWPOL->SetParameter(3, WidthZ0);
    RBWPOL->SetParLimits(3, 0.1, 20);
    RBWPOL->FixParameter(2, WidthZ0);
    RBWPOL->FixParameter(6, 0);
  }

  // Open the file 

  //  TFile *fil1 = new TFile("RV_WTrk_ZToMuMu_2DPlot.root");   // 1000 Flat 
  TFile *fil1 = new TFile("/castor/cern.ch/cms/store/caf/user/silvest/HICorePhysics_PromptReco_RECO_ZmumuPaperSkim_DiMuon2DPlots_merged.root");   // 5000 Flat 
  //  TFile *fil1 = new TFile("Hu_Z0ToMuMu_2DPlot.root");  // 500 Flat 
  //  TFile *fil1 = new TFile("ZMuMu_2DDataSameCharge.root"); // JEX
  //ZMuMu_2DPlotNew.root");

  double yld_cat_1[10], yld_cat_2[10], yld_cat_3[10];
  double eyld_cat_1[10], eyld_cat_2[10], eyld_cat_3[10];

  char namePt_1[500], namePt_2[500], namePt_3[500];
  char namePt_1B[500], namePt_2B[500], namePt_3B[500];

  char text[100];

  ///// Write the spectra 
  char fspectra[500];
  sprintf(fspectra,"fileSpecta%d.root", yieldInt);
  TFile *fileSpectra = new TFile(fspectra, "recreate");


  ///////////////////////////////////////////////////////////////////////
  // Category _1 
  TLegend *lcat_1;
  lcat_1 = new TLegend(.42, .70, .92, .86);
  lcat_1->SetName("lcat_1");
  lcat_1->SetBorderSize(0);
  lcat_1->SetFillStyle(0);
  lcat_1->SetFillColor(0);
  lcat_1->SetTextSize(0.032);
  lcat_1->AddEntry(RBWPOL," PbPb at  #sqrt{s_{NN}} = 2.76 TeV ", " ");
  lcat_1->AddEntry(RBWPOL," Global-Global ", "P");
  lcat_1->AddEntry(RBWPOL," |y| < 2.4 ", "P");

  TLegend *legend_1[12];
  for(int i=0; i<12; i++) { 
    legend_1[i] = new TLegend(.42, .60, .92, 0.70 );
    legend_1[i]->SetBorderSize(0);
    legend_1[i]->SetFillStyle(0);
    legend_1[i]->SetFillColor(0);
    legend_1[i]->SetTextSize(0.032);
  }

  if(iSpec == 1) TH2D *Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPt");
  if(iSpec == 2) TH2D *Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsY");
  if(iSpec == 3) TH2D *Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsCen");


  TH1D *service = (TH1D*)Z0Mass_1->ProjectionY("service");
  
  int pt_bin_bound[100];
  
  TH1D *dimuonsGlobalInvMassVsPt[10];


  TCanvas *CanvPt_1 = new TCanvas("CanvPt_1"," Z0 Yield Vs. Pt ", 40,40,1000,700);
  CanvPt_1->Divide(2,2);
    
  cout << endl << Xname[iSpec] << "    Yield      Mass (GeV)    Width (GeV)    GauWidth    chi2/ndf " << endl << endl; 

  for (Int_t ih = 0; ih < Nptbin; ih++) {
    CanvPt_1->cd(ih+1);
    gPad->SetTickx();
    gPad->SetTicky();

    // Project 1 D 
    pt_bin_bound[ih] = service->FindBin(pt_bound[ih]+0.0000001);
    pt_bin_bound[ih+1] = service->FindBin(pt_bound[ih+1]+0.0000001);
    sprintf(namePt_1,"Z0_1_pt_%d",ih);
    dimuonsGlobalInvMassVsPt[ih] = (TH1D*)Z0Mass_1->ProjectionX(namePt_1, pt_bin_bound[ih], pt_bin_bound[ih+1]-1);
    sprintf(text," %s [%.1f, %.1f]", Xname[iSpec], service->GetBinLowEdge(pt_bin_bound[ih]), 
	      service->GetBinLowEdge(pt_bin_bound[ih+1]-1)+service->GetBinWidth(pt_bin_bound[ih+1]));

    dimuonsGlobalInvMassVsPt[ih]->Rebin(40);

    //Fit Function + Bkg Function
    dimuonsGlobalInvMassVsPt[ih]->Fit("RBWPOL","RQWW", "", mass_low, mass_high);
    double par[20];
    RBWPOL->GetParameters(par);
    sprintf(namePt_1B,"pt_1B_%d",ih);
    backfun_1 = new TF1(namePt_1B, Pol2, mass_low, mass_high, 3);
    backfun_1->SetParameters(&par[3]);
    if(nff == 3) backfun_1->SetParameters(&par[4]);
    
    float GGZ0Mass = RBWPOL->GetParameter(1);
    float GGZ0Width = RBWPOL->GetParameter(2);
    float GauWidth =0;
    if(nff == 3) GauWidth = RBWPOL->GetParameter(3);
   

    double chisq = RBWPOL->GetChisquare();
    double ndf = RBWPOL->GetNDF();
    if(ndf!=0) double chisqdf=chisq/ndf;
    else double chisqdf=1000;


    // Integrated Yield 
    float m_low =GGZ0Mass-(2.5*GGZ0Width);
    float m_high =GGZ0Mass+(2.5*GGZ0Width);
    
    TAxis *axs   = dimuonsGlobalInvMassVsPt[ih]->GetXaxis();
    
    int binlow = axs->FindBin(m_low);
    int binhi  = axs->FindBin(m_high);
    
    Double_t bin_size = (1.0*dimuonsGlobalInvMassVsPt[ih]->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
    
    Float_t int_sig = 0.0;
    for(Int_t bin = binlow; bin<=binhi;bin++) {
      int_sig+ = dimuonsGlobalInvMassVsPt[ih]->GetBinContent(bin);
    }   

    if(yieldInt == 2) int_sig =  RBWPOL->Integral(m_low, m_high)*bin_size;

    double yld_1  = int_sig- bin_size*backfun_1->Integral(m_low, m_high);
    eyld_cat_1[ih] = TMath::Sqrt(int_sig + bin_size*backfun_1->Integral(m_low, m_high) );


    //// Printing /////
    cout <<  PT[ih] << "    " << yld_1 << " +- " << eyld_cat_1[ih] <<"     " << GGZ0Mass << "    " << GGZ0Width  << "    " << GauWidth <<"   "<< chisq << "/" << ndf  << endl; 

    yld_cat_1[ih] = yld_1;

    // Draw
    dimuonsGlobalInvMassVsPt[ih]->SetMinimum(-.05*dimuonsGlobalInvMassVsPt[ih]->GetMaximum());

    dimuonsGlobalInvMassVsPt[ih]->SetMarkerStyle(kFullCircle);
    dimuonsGlobalInvMassVsPt[ih]->SetMarkerColor(4);
    dimuonsGlobalInvMassVsPt[ih]->SetMarkerSize(0.8);
    dimuonsGlobalInvMassVsPt[ih]->GetXaxis()->SetTitle("Invariant Mass of #mu^{+} #mu^{-} (GeV/c^{2})");
    dimuonsGlobalInvMassVsPt[ih]->GetYaxis()->SetTitle("counts");

    dimuonsGlobalInvMassVsPt[ih]->DrawCopy("EPL");
    
    backfun_1->SetLineColor(kRed);
    backfun_1->SetLineWidth(2);
    backfun_1->Draw("same");

    lcat_1->Draw("same"); 

    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], text, "");

    char label_1[512];
    sprintf(label_1, "N_{Z^{0}}=%1.2f #pm %1.2f (%s) ", yld_cat_1[ih], eyld_cat_1[ih], name_fit[nff]);
    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], label_1, "");

    legend_1[ih]->Draw("same");
    
  }
  cout << endl << endl;

  CanvPt_1->Print("Pt_Z0MassCat_1.png");
 


  TGraphErrors *Z0pt_cat_1 = new TGraphErrors(Nptbin, PT, yld_cat_1, mom_err, eyld_cat_1);
  Z0pt_cat_1->SetMarkerStyle(20);
  Z0pt_cat_1->SetMarkerColor(2);
  Z0pt_cat_1->GetXaxis()->SetTitle(Xname[iSpec]);
  Z0pt_cat_1->GetYaxis()->SetTitle("counts");

  new TCanvas;
  Z0pt_cat_1->SetMinimum(0.0);
  Z0pt_cat_1->SetName("Z0pt_cat_1");
  Z0pt_cat_1->Draw("AP");
  lcat_1->Draw("same"); 
  gPad->Print("Pt_Z0YieldCat_1.png");

  cout << endl << endl;

  Z0pt_cat_1->Write();
  lcat_1->Write();


 ///////////////////////////////////////////////////////////////////////
  // Category _2 
  TLegend *lcat_2;
  lcat_2 = new TLegend(.42, .70, .92, .86);
  lcat_2->SetName("lcat_2");
  lcat_2->SetBorderSize(0);
  lcat_2->SetFillStyle(0);
  lcat_2->SetFillColor(0);
  lcat_2->SetTextSize(0.032);
  lcat_2->AddEntry(RBWPOL," PbPb at  #sqrt{s_{NN}} = 2.76 TeV ", " ");
  lcat_2->AddEntry(RBWPOL," Global-STA ", "P");
  lcat_2->AddEntry(RBWPOL," |y| < 2.4 ", "P");

  TLegend *legend_2[12];
  for(int i=0; i<12; i++) { 
    legend_2[i] = new TLegend(.42, .60, .92, 0.70 );
    legend_2[i]->SetBorderSize(0);
    legend_2[i]->SetFillStyle(0);
    legend_2[i]->SetFillColor(0);
    legend_2[i]->SetTextSize(0.032);
  }

  if(iSpec == 1) TH2D *Z0Mass_2 = (TH2D*)fil1->Get("diMuonsGlobalSTAInvMassVsPt");
  if(iSpec == 2) TH2D *Z0Mass_2 = (TH2D*)fil1->Get("diMuonsGlobalSTAInvMassVsY");
  if(iSpec == 3) TH2D *Z0Mass_2 = (TH2D*)fil1->Get("diMuonsGlobalSTAInvMassVsCen");


  TH1D *service = (TH1D*)Z0Mass_2->ProjectionY("service");
  
  int pt_bin_bound[100];
  
  TH1D *dimuonsGlobalSTAInvMassVsPt[10];


  TCanvas *CanvPt_2 = new TCanvas("CanvPt_2"," Z0 Yield Vs. Pt ", 40,40,1000,700);
  CanvPt_2->Divide(2,2);
    
  cout << endl << Xname[iSpec] << "    Yield      Mass (GeV)    Width (GeV)    GauWidth    chi2/ndf " << endl << endl; 

  for (Int_t ih = 0; ih < Nptbin; ih++) {
    CanvPt_2->cd(ih+1);
    gPad->SetTickx();
    gPad->SetTicky();

    // Project 1 D 
    pt_bin_bound[ih] = service->FindBin(pt_bound[ih]+0.0000001);
    pt_bin_bound[ih+1] = service->FindBin(pt_bound[ih+1]+0.0000001);
    sprintf(namePt_2,"Z0_2_pt_%d",ih);
    dimuonsGlobalSTAInvMassVsPt[ih] = (TH1D*)Z0Mass_2->ProjectionX(namePt_2, pt_bin_bound[ih], pt_bin_bound[ih+1]-1);
    sprintf(text," %s [%.1f, %.1f]", Xname[iSpec], service->GetBinLowEdge(pt_bin_bound[ih]), 
	      service->GetBinLowEdge(pt_bin_bound[ih+1]-1)+service->GetBinWidth(pt_bin_bound[ih+1]));

    dimuonsGlobalSTAInvMassVsPt[ih]->Rebin(80);

    //Fit Function + Bkg Function
    dimuonsGlobalSTAInvMassVsPt[ih]->Fit("RBWPOL","RQWW", "", mass_low, mass_high);
    double par[20];
    RBWPOL->GetParameters(par);
    sprintf(namePt_2B,"pt_2B_%d",ih);
    backfun_2 = new TF1(namePt_2B, Pol2, mass_low, mass_high, 3);
    backfun_2->SetParameters(&par[3]);
    if(nff == 3) backfun_2->SetParameters(&par[4]);
    
    float GGZ0Mass = RBWPOL->GetParameter(1);
    float GGZ0Width = RBWPOL->GetParameter(2);
    float GauWidth =0;
    if(nff == 3) GauWidth = RBWPOL->GetParameter(3);
   

    double chisq = RBWPOL->GetChisquare();
    double ndf = RBWPOL->GetNDF();
    if(ndf!=0) double chisqdf=chisq/ndf;
    else double chisqdf=1000;


    // Integrated Yield 
    float m_low =GGZ0Mass-(2.5*GGZ0Width);
    float m_high =GGZ0Mass+(2.5*GGZ0Width);
    
    TAxis *axs   = dimuonsGlobalSTAInvMassVsPt[ih]->GetXaxis();
    
    int binlow = axs->FindBin(m_low);
    int binhi  = axs->FindBin(m_high);
    
    Double_t bin_size = (1.0*dimuonsGlobalSTAInvMassVsPt[ih]->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
    
    Float_t int_sig = 0.0;
    for(Int_t bin = binlow; bin<=binhi;bin++) {
      int_sig+ = dimuonsGlobalSTAInvMassVsPt[ih]->GetBinContent(bin);
    }   

    if(yieldInt == 2) int_sig =  RBWPOL->Integral(m_low, m_high)*bin_size;

    double yld_2  = int_sig- bin_size*backfun_2->Integral(m_low, m_high);
    eyld_cat_2[ih] = TMath::Sqrt(int_sig + bin_size*backfun_2->Integral(m_low, m_high) );


    //// Printing /////
    cout <<  PT[ih] << "    " << yld_2 << " +- " << eyld_cat_2[ih] <<"     " << GGZ0Mass << "    " << GGZ0Width  << "    " << GauWidth <<"   "<< chisq << "/" << ndf  << endl; 

    yld_cat_2[ih] = yld_2;

    // Draw
    dimuonsGlobalSTAInvMassVsPt[ih]->SetMinimum(-.05*dimuonsGlobalSTAInvMassVsPt[ih]->GetMaximum());

    dimuonsGlobalSTAInvMassVsPt[ih]->SetMarkerStyle(kFullCircle);
    dimuonsGlobalSTAInvMassVsPt[ih]->SetMarkerColor(4);
    dimuonsGlobalSTAInvMassVsPt[ih]->SetMarkerSize(0.8);
    dimuonsGlobalSTAInvMassVsPt[ih]->GetXaxis()->SetTitle("Invariant Mass of #mu^{+} #mu^{-} (GeV/c^{2})");
    dimuonsGlobalSTAInvMassVsPt[ih]->GetYaxis()->SetTitle("counts");

    dimuonsGlobalSTAInvMassVsPt[ih]->DrawCopy("EPL");
    
    backfun_2->SetLineColor(kRed);
    backfun_2->SetLineWidth(2);
    backfun_2->Draw("same");

    lcat_2->Draw("same"); 

    legend_2[ih]->AddEntry(dimuonsGlobalSTAInvMassVsPt[ih], text, "");

    char label_2[512];
    sprintf(label_2, "N_{Z^{0}}=%1.2f #pm %1.2f (%s) ", yld_cat_2[ih], eyld_cat_2[ih], name_fit[nff]);
    legend_2[ih]->AddEntry(dimuonsGlobalSTAInvMassVsPt[ih], label_2, "");

    legend_2[ih]->Draw("same");
    
  }
  cout << endl << endl;

  CanvPt_2->Print("Pt_Z0MassCat_2.png");
 


  TGraphErrors *Z0pt_cat_2 = new TGraphErrors(Nptbin, PT, yld_cat_2, mom_err, eyld_cat_2);
  Z0pt_cat_2->SetMarkerStyle(20);
  Z0pt_cat_2->SetMarkerColor(2);
  Z0pt_cat_2->GetXaxis()->SetTitle(Xname[iSpec]);
  Z0pt_cat_2->GetYaxis()->SetTitle("counts");

  new TCanvas;
  Z0pt_cat_2->SetMinimum(0.0);
  Z0pt_cat_2->SetName("Z0pt_cat_2");
  Z0pt_cat_2->Draw("AP");
  lcat_2->Draw("same"); 
  gPad->Print("Pt_Z0YieldCat_2.png");

  cout << endl << endl;

  Z0pt_cat_2->Write();
  lcat_2->Write();


 ///////////////////////////////////////////////////////////////////////
  // Category _3 
  TLegend *lcat_3;
  lcat_3 = new TLegend(.42, .70, .92, .86);
  lcat_3->SetName("lcat_3");
  lcat_3->SetBorderSize(0);
  lcat_3->SetFillStyle(0);
  lcat_3->SetFillColor(0);
  lcat_3->SetTextSize(0.032);
  lcat_3->AddEntry(RBWPOL," PbPb at  #sqrt{s_{NN}} = 2.76 TeV ", " ");
  lcat_3->AddEntry(RBWPOL," STA-STA ", "P");
  lcat_3->AddEntry(RBWPOL," |y| < 2.4 ", "P");

  TLegend *legend_3[12];
  for(int i=0; i<12; i++) { 
    legend_3[i] = new TLegend(.42, .60, .92, 0.70 );
    legend_3[i]->SetBorderSize(0);
    legend_3[i]->SetFillStyle(0);
    legend_3[i]->SetFillColor(0);
    legend_3[i]->SetTextSize(0.032);
  }

  if(iSpec == 1) TH2D *Z0Mass_3 = (TH2D*)fil1->Get("diMuonsSTAInvMassVsPt");
  if(iSpec == 2) TH2D *Z0Mass_3 = (TH2D*)fil1->Get("diMuonsSTAInvMassVsY");
  if(iSpec == 3) TH2D *Z0Mass_3 = (TH2D*)fil1->Get("diMuonsSTAInvMassVsCen");


  TH1D *service = (TH1D*)Z0Mass_3->ProjectionY("service");
  
  int pt_bin_bound[100];
  
  TH1D *dimuonsSTAInvMassVsPt[10];


  TCanvas *CanvPt_3 = new TCanvas("CanvPt_3"," Z0 Yield Vs. Pt ", 40,40,1000,700);
  CanvPt_3->Divide(2,2);
    
  cout << endl << Xname[iSpec] << "    Yield      Mass (GeV)    Width (GeV)    GauWidth    chi2/ndf " << endl << endl; 

  for (Int_t ih = 0; ih < Nptbin; ih++) {
    CanvPt_3->cd(ih+1);
    gPad->SetTickx();
    gPad->SetTicky();

    // Project 1 D 
    pt_bin_bound[ih] = service->FindBin(pt_bound[ih]+0.0000001);
    pt_bin_bound[ih+1] = service->FindBin(pt_bound[ih+1]+0.0000001);
    sprintf(namePt_3,"Z0_3_pt_%d",ih);
    dimuonsSTAInvMassVsPt[ih] = (TH1D*)Z0Mass_3->ProjectionX(namePt_3, pt_bin_bound[ih], pt_bin_bound[ih+1]-1);
    sprintf(text," %s [%.1f, %.1f]", Xname[iSpec], service->GetBinLowEdge(pt_bin_bound[ih]), 
	      service->GetBinLowEdge(pt_bin_bound[ih+1]-1)+service->GetBinWidth(pt_bin_bound[ih+1]));

    dimuonsSTAInvMassVsPt[ih]->Rebin(80);

    //Fit Function + Bkg Function
    dimuonsSTAInvMassVsPt[ih]->Fit("RBWPOL","RQWW", "", mass_low, mass_high);
    double par[20];
    RBWPOL->GetParameters(par);
    sprintf(namePt_3B,"pt_3B_%d",ih);
    backfun_3 = new TF1(namePt_3B, Pol2, mass_low, mass_high, 3);
    backfun_3->SetParameters(&par[3]);
    if(nff == 3) backfun_3->SetParameters(&par[4]);
    
    float GGZ0Mass = RBWPOL->GetParameter(1);
    float GGZ0Width = RBWPOL->GetParameter(2);
    float GauWidth =0;
    if(nff == 3) GauWidth = RBWPOL->GetParameter(3);
   

    double chisq = RBWPOL->GetChisquare();
    double ndf = RBWPOL->GetNDF();
    if(ndf!=0) double chisqdf=chisq/ndf;
    else double chisqdf=1000;


    // Integrated Yield 
    float m_low =GGZ0Mass-(2.5*GGZ0Width);
    float m_high =GGZ0Mass+(2.5*GGZ0Width);
    
    TAxis *axs   = dimuonsSTAInvMassVsPt[ih]->GetXaxis();
    
    int binlow = axs->FindBin(m_low);
    int binhi  = axs->FindBin(m_high);
    
    Double_t bin_size = (1.0*dimuonsSTAInvMassVsPt[ih]->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
    
    Float_t int_sig = 0.0;
    for(Int_t bin = binlow; bin<=binhi;bin++) {
      int_sig+ = dimuonsSTAInvMassVsPt[ih]->GetBinContent(bin);
    }   

    if(yieldInt == 2) int_sig =  RBWPOL->Integral(m_low, m_high)*bin_size;

    double yld_3  = int_sig- bin_size*backfun_3->Integral(m_low, m_high);
    eyld_cat_3[ih] = TMath::Sqrt(int_sig + bin_size*backfun_3->Integral(m_low, m_high) );


    //// Printing /////
    cout <<  PT[ih] << "    " << yld_3 << " +- " << eyld_cat_3[ih] <<"     " << GGZ0Mass << "    " << GGZ0Width  << "    " << GauWidth <<"   "<< chisq << "/" << ndf  << endl; 

    yld_cat_3[ih] = yld_3;

    // Draw
    dimuonsSTAInvMassVsPt[ih]->SetMinimum(-.05*dimuonsSTAInvMassVsPt[ih]->GetMaximum());

    dimuonsSTAInvMassVsPt[ih]->SetMarkerStyle(kFullCircle);
    dimuonsSTAInvMassVsPt[ih]->SetMarkerColor(4);
    dimuonsSTAInvMassVsPt[ih]->SetMarkerSize(0.8);
    dimuonsSTAInvMassVsPt[ih]->GetXaxis()->SetTitle("Invariant Mass of #mu^{+} #mu^{-} (GeV/c^{2})");
    dimuonsSTAInvMassVsPt[ih]->GetYaxis()->SetTitle("counts");

    dimuonsSTAInvMassVsPt[ih]->DrawCopy("EPL");
    
    backfun_3->SetLineColor(kRed);
    backfun_3->SetLineWidth(2);
    backfun_3->Draw("same");

    lcat_3->Draw("same"); 

    legend_3[ih]->AddEntry(dimuonsSTAInvMassVsPt[ih], text, "");

    char label_3[512];
    sprintf(label_3, "N_{Z^{0}}=%1.2f #pm %1.2f (%s) ", yld_cat_3[ih], eyld_cat_3[ih], name_fit[nff]);
    legend_3[ih]->AddEntry(dimuonsSTAInvMassVsPt[ih], label_3, "");

    legend_3[ih]->Draw("same");
    
  }
  cout << endl << endl;

  CanvPt_3->Print("Pt_Z0MassCat_3.png");
 


  TGraphErrors *Z0pt_cat_3 = new TGraphErrors(Nptbin, PT, yld_cat_3, mom_err, eyld_cat_3);
  Z0pt_cat_3->SetMarkerStyle(20);
  Z0pt_cat_3->SetMarkerColor(2);
  Z0pt_cat_3->GetXaxis()->SetTitle(Xname[iSpec]);
  Z0pt_cat_3->GetYaxis()->SetTitle("counts");

  new TCanvas;
  Z0pt_cat_3->SetMinimum(0.0);
  Z0pt_cat_3->SetName("Z0pt_cat_3");
  Z0pt_cat_3->Draw("AP");
  lcat_3->Draw("same"); 
  gPad->Print("Pt_Z0YieldCat_3.png");

  cout << endl << endl;

  Z0pt_cat_3->Write();
  lcat_3->Write();





  ///////////////////////////////////////////////////////////////////


  // Efficiency correction
  if(isData==2) 
    {
      ofstream fileout("correction.txt");
      cout << Xname[iSpec] << "   Eff_cat_1,  Eff_cat_2,  Eff_cat_3  " << endl;

      for (Int_t ih = 0; ih < Nptbin; ih++) {
	Eff_cat_1[ih] = yld_cat_1[ih]/gen_pt[ih]; 
	Eff_cat_2[ih] = yld_cat_2[ih]/gen_pt[ih]; 
	Eff_cat_3[ih] = yld_cat_3[ih]/gen_pt[ih]; 

	fileout << PT[ih] <<"   "<< Eff_cat_1[ih] << "   " << Eff_cat_2[ih] <<"    " << Eff_cat_3[ih] << endl; 
	cout <<"    " << PT[ih] <<"      "<< Eff_cat_1[ih] << "      " << Eff_cat_2[ih] << "      " << Eff_cat_3[ih] << endl; 
      }
    }
  

  if(isData==1) {
    ifstream filein("correction.txt");
    cout <<  Xname[iSpec] << "   yld_cat_1,  yld_cat_2,  yield_cat_3  " << endl;
    for (Int_t ih = 0; ih < Nptbin; ih++) {

      filein >> PT[ih] >>  Eff_cat_1[ih] >>  Eff_cat_2[ih]  >>  Eff_cat_3[ih] ; 
      //      cout << "     " << PT[ih] << "   "<< yld_cat_1[ih]/ Eff_cat_1[ih] << "    " << yld_cat_2[ih]/ Eff_cat_2[ih] <<"   " <<  yld_cat_3[ih]/ Eff_cat_3[ih] << endl;

     cout << "       " << PT[ih] << "      "<< yld_cat_1[ih] << "       " << yld_cat_2[ih] <<"      " <<  yld_cat_3[ih] << endl;


    }
  }
  

}
