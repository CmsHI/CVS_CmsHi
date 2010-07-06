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

void Z0MassRapFit(int isData=2)
{

  // isData = 1 for Data
  // isData = 2 for Simulation


  gStyle->SetPadTopMargin(0.15);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadRightMargin(0.15);

  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(600); //Height of canvas
  gStyle->SetCanvasDefW(600); //Width of canvas

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(1);
  gStyle->SetOptFit(1111);
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
  float Eff_cat1[10],Eff_cat2[10], Eff_cat3[10]; 
  
  // Rap bin sizes
  int NRapbin = 3;
  double Rap_bound[10] = {-2.4, -0.8, 0.8, 2.4};
  double RAP[10], DelRAP[10];
  for (Int_t ih = 0; ih < NRapbin; ih++) {
    RAP[ih] = (Rap_bound[ih] + Rap_bound[ih+1])/2.0;
    DelRAP[ih] = Rap_bound[ih+1] - Rap_bound[ih];
  }

  // Generated Numbers 
  int  TotalFlat = 2000;
  float gen_Rap[10];

  for (Int_t ih = 0; ih < NRapbin; ih++) {
    gen_Rap[ih] = 2000;
  }

  // Centrality bin sizes
  //  {0, 100.0};
  //  {0, 50.0, 100.0};
  //  {0.0, 30.0, 60.0, 100.0};
  
  
  // Fit Function RBW + Pol2
  
  TF1 *RBWPOL = new TF1("RBWPOL", RBWPol2, 0, 200, 6);
  RBWPOL->SetParNames("N","m_{0}", "#Gamma", "p_{0}", "p_{1}", "p_{2}");
  //RBWPOL->FixParameter(1,MassZ0);
  RBWPOL->SetParLimits(1, 84, 98);
  RBWPOL->SetParLimits(2, 2, 20);


  // Open the file 
  TFile *fil1 = new TFile("ZMuMu_2DPlot.root");

  double yld_cat1[10], yld_cat2[10], yld_cat3[10];
  double eyld_cat1[10], eyld_cat2[10], eyld_cat3[10];

  char nameRap1[500], nameRap2[500], nameRap3[500];
  char nameRap1B[500], nameRap2B[500], nameRap3B[500];

  char text[100];


 
  ///////////////////////////////////////////////////////////////////////
  // Category 1 
  TLegend *lcat1;
  lcat1 = new TLegend(.05, .78, .50, .83);
  lcat1->SetName("lphenix");
  lcat1->SetBorderSize(0);
  lcat1->SetFillStyle(0);
  lcat1->SetFillColor(0);
  lcat1->SetTextSize(0.027);
  lcat1->AddEntry(RBWPOL," PbPb at  #sqrt{s_{NN}} = 2.76 TeV ", " ");
  lcat1->AddEntry(RBWPOL," Global-Global ", "P");

  TLegend *legend_1[12];
  for(int i=0; i<12; i++) { 
    legend_1[i] = new TLegend(.05, .74, .50, 0.78 );
    legend_1[i]->SetBorderSize(0);
    legend_1[i]->SetFillStyle(0);
    legend_1[i]->SetFillColor(0);
    legend_1[i]->SetTextSize(0.027);
  }

 
  TH2D *Z0MassGG = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsY");


  TH1D *service = (TH1D*)Z0MassGG->ProjectionY("service");
  int Rap_bin_bound[100];

  TH1D *dimuonsGlobalInvMassVsRap[10];


  TCanvas *CanvRap1 = new TCanvas("CanvRap1"," Z0 Yield Vs. Rap ", 40,40,1200,900);
  CanvRap1->Divide(2,2);
    

  for (Int_t ih = 0; ih < NRapbin; ih++) {
    CanvRap1->cd(ih+1);
    gPad->SetTickx();
    gPad->SetTicky();

    // Project 1 D 
    Rap_bin_bound[ih] = service->FindBin(Rap_bound[ih]+0.0000001);
    Rap_bin_bound[ih+1] = service->FindBin(Rap_bound[ih+1]+0.0000001);
    sprintf(nameRap1,"Z0_Rap_%d",ih);
    dimuonsGlobalInvMassVsRap[ih] = (TH1D*)Z0MassGG->ProjectionX(nameRap1, Rap_bin_bound[ih], Rap_bin_bound[ih+1]-1);
    sprintf(text," Y = %.2f to %.2f",  service->GetBinLowEdge(Rap_bin_bound[ih]), 
	      service->GetBinLowEdge(Rap_bin_bound[ih+1]-1)+service->GetBinWidth(Rap_bin_bound[ih+1]));

    dimuonsGlobalInvMassVsRap[ih]->Rebin(1);


    //Fit Function + Bkg Function
    dimuonsGlobalInvMassVsRap[ih]->Fit("RBWPOL","REQ", "", mass_low, mass_high);
    double par[20];
    RBWPOL->GetParameters(par);
    sprintf(nameRap1B,"Rap1B_%d",ih);
    backfunGG = new TF1(nameRap1B, Pol2, mass_low, mass_high, 3);
    backfunGG->SetParameters(&par[3]);
    
    float GGZ0Mass =RBWPOL->GetParameter(1);
    float GGZ0Width =RBWPOL->GetParameter(2);

    // Integrated Yield 
    float m_low =GGZ0Mass-(1.5 *GGZ0Width);
    float m_high =GGZ0Mass+(1.5 *GGZ0Width);
    
    TAxis *axs   = dimuonsGlobalInvMassVsRap[ih]->GetXaxis();
    
    int binlow = axs->FindBin(m_low);
    int binhi  = axs->FindBin(m_high);
    
    Double_t bin_size = (1.0*dimuonsGlobalInvMassVsRap[ih]->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
    
    Float_t int_sig = 0.0;
    for(Int_t bin = binlow; bin<=binhi;bin++) {
      int_sig+ = dimuonsGlobalInvMassVsRap[ih]->GetBinContent(bin);
    }   

    double yld1  = int_sig- bin_size*backfunGG->Integral(m_low, m_high);
    eyld_cat1[ih] = TMath::Sqrt(int_sig + bin_size*backfunGG->Integral(m_low, m_high) );
    cout << " Rap = " << RAP[ih] << " Global Global Yield =  " << yld1 << "  Error =   " << eyld_cat1[ih] << endl; 

    yld_cat1[ih] = yld1;

    // Draw
    dimuonsGlobalInvMassVsRap[ih]->SetMinimum(-.05*dimuonsGlobalInvMassVsRap[ih]->GetMaximum());

    dimuonsGlobalInvMassVsRap[ih]->SetMarkerStyle(kFullCircle);
    dimuonsGlobalInvMassVsRap[ih]->SetMarkerColor(4);
    dimuonsGlobalInvMassVsRap[ih]->SetMarkerSize(0.8);
    
    dimuonsGlobalInvMassVsRap[ih]->DrawCopy("EPL");
    
    backfunGG->SetLineColor(kRed);
    backfunGG->SetLineWidth(2);
    
    backfunGG->Draw("same");

    lcat1->Draw("same"); 

    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsRap[ih], text, "");

    legend_1[ih]->Draw("same");
    
  }
  
  double mom_err[100] = {0};

  TGraphErrors *Z0Rap_cat1 = new TGraphErrors(NRapbin, RAP, yld_cat1, mom_err, eyld_cat1);
  Z0Rap_cat1->SetMarkerStyle(20);
  Z0Rap_cat1->SetMarkerColor(2);
  Z0Rap_cat1->GetXaxis()->SetTitle("Y");
  Z0Rap_cat1->GetYaxis()->SetTitle("counts");

  new TCanvas;
  Z0Rap_cat1->Draw("AP");
  lcat1->Draw("same"); 


  cout << endl << endl;

  ///////////////////////////////////////////////////////////////////////
  // Category 2 
  TLegend *lcat2;
  lcat2 = new TLegend(.05, .78, .50, .83);
  lcat2->SetName("lphenix");
  lcat2->SetBorderSize(0);
  lcat2->SetFillStyle(0);
  lcat2->SetFillColor(0);
  lcat2->SetTextSize(0.027);
  lcat2->AddEntry(RBWPOL," PbPb at  #sqrt{s_{NN}} = 2.76 TeV ", " ");
  lcat2->AddEntry(RBWPOL," Global-STA ", "P");

  TLegend *legend_2[12];
  for(int i=0; i<12; i++) { 
    legend_2[i] = new TLegend(.05, .74, .50, 0.78 );
    legend_2[i]->SetBorderSize(0);
    legend_2[i]->SetFillStyle(0);
    legend_2[i]->SetFillColor(0);
    legend_2[i]->SetTextSize(0.027);
  }

 
  TH2D *Z0MassGS = (TH2D*)fil1->Get("diMuonsGlobalSTAInvMassVsY");


  TH1D *service = (TH1D*)Z0MassGS->ProjectionY("service");
  int Rap_bin_bound[100];

  TH1D *dimuonsGlobalSTAInvMassVsRap[10];


  TCanvas *CanvRap2 = new TCanvas("CanvRap2"," Z0 Yield Vs. Rap ", 40,40,1200,900);
  CanvRap2->Divide(2,2);
    

  for (Int_t ih = 0; ih < NRapbin; ih++) {
    CanvRap2->cd(ih+1);
    gPad->SetTickx();
    gPad->SetTicky();

    // Project 1 D 
    Rap_bin_bound[ih] = service->FindBin(Rap_bound[ih]+0.0000001);
    Rap_bin_bound[ih+1] = service->FindBin(Rap_bound[ih+1]+0.0000001);
    sprintf(nameRap1,"Z0_Rap_%d",ih);
    dimuonsGlobalSTAInvMassVsRap[ih] = (TH1D*)Z0MassGS->ProjectionX(nameRap2, Rap_bin_bound[ih], Rap_bin_bound[ih+1]-1);
    sprintf(text," Y = %.2f to %.2f",  service->GetBinLowEdge(Rap_bin_bound[ih]), 
	      service->GetBinLowEdge(Rap_bin_bound[ih+1]-1)+service->GetBinWidth(Rap_bin_bound[ih+1]));

    dimuonsGlobalSTAInvMassVsRap[ih]->Rebin(1);


    //Fit Function + Bkg Function
    dimuonsGlobalSTAInvMassVsRap[ih]->Fit("RBWPOL","REQ", "", mass_low, mass_high);
    double par[20];
    RBWPOL->GetParameters(par);
    sprintf(nameRap2B,"Rap2B_%d",ih);
    backfunGG = new TF1(nameRap2B, Pol2, mass_low, mass_high, 3);
    backfunGG->SetParameters(&par[3]);
    
    float GGZ0Mass =RBWPOL->GetParameter(1);
    float GGZ0Width =RBWPOL->GetParameter(2);

    // Integrated Yield 
    float m_low =GGZ0Mass-(1.5 *GGZ0Width);
    float m_high =GGZ0Mass+(1.5 *GGZ0Width);
    
    TAxis *axs   = dimuonsGlobalSTAInvMassVsRap[ih]->GetXaxis();
    
    int binlow = axs->FindBin(m_low);
    int binhi  = axs->FindBin(m_high);
    
    Double_t bin_size = (1.0*dimuonsGlobalSTAInvMassVsRap[ih]->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
    
    Float_t int_sig = 0.0;
    for(Int_t bin = binlow; bin<=binhi;bin++) {
      int_sig+ = dimuonsGlobalSTAInvMassVsRap[ih]->GetBinContent(bin);
    }   

    double yld2  = int_sig- bin_size*backfunGG->Integral(m_low, m_high);
    eyld_cat2[ih] = TMath::Sqrt(int_sig + bin_size*backfunGG->Integral(m_low, m_high) );
    cout << " Rap = " << RAP[ih] << " Global STA Yield =  " << yld2 << "  Error =   " << eyld_cat2[ih] << endl; 

    yld_cat2[ih] = yld2;

    // Draw
    dimuonsGlobalSTAInvMassVsRap[ih]->SetMinimum(-.05*dimuonsGlobalSTAInvMassVsRap[ih]->GetMaximum());

    dimuonsGlobalSTAInvMassVsRap[ih]->SetMarkerStyle(kFullCircle);
    dimuonsGlobalSTAInvMassVsRap[ih]->SetMarkerColor(4);
    dimuonsGlobalSTAInvMassVsRap[ih]->SetMarkerSize(0.8);
    
    dimuonsGlobalSTAInvMassVsRap[ih]->DrawCopy("EPL");
    
    backfunGG->SetLineColor(kRed);
    backfunGG->SetLineWidth(2);
    
    backfunGG->Draw("same");

    lcat2->Draw("same"); 

    legend_2[ih]->AddEntry(dimuonsGlobalSTAInvMassVsRap[ih], text, "");

    legend_2[ih]->Draw("same");
    
  }
  
  double mom_err[100] = {0};

  TGraphErrors *Z0Rap_cat2 = new TGraphErrors(NRapbin, RAP, yld_cat2, mom_err, eyld_cat2);
  Z0Rap_cat2->SetMarkerStyle(20);
  Z0Rap_cat2->SetMarkerColor(2);
  Z0Rap_cat2->GetXaxis()->SetTitle("Y ");
  Z0Rap_cat2->GetYaxis()->SetTitle("Counts");

  new TCanvas;
  Z0Rap_cat2->Draw("AP");
  lcat2->Draw("same"); 

  cout << endl << endl;

  ///////////////////////////////////////////////////////////////////////
  // Category 3 
  TLegend *lcat3;
  lcat3 = new TLegend(.05, .78, .50, .83);
  lcat3->SetName("lphenix");
  lcat3->SetBorderSize(0);
  lcat3->SetFillStyle(0);
  lcat3->SetFillColor(0);
  lcat3->SetTextSize(0.027);
  lcat3->AddEntry(RBWPOL," PbPb at  #sqrt{s_{NN}} = 2.76 TeV ", " ");
  lcat3->AddEntry(RBWPOL," STA-STA ", "P");

  TLegend *legend_3[12];
  for(int i=0; i<12; i++) { 
    legend_3[i] = new TLegend(.05, .74, .50, 0.78 );
    legend_3[i]->SetBorderSize(0);
    legend_3[i]->SetFillStyle(0);
    legend_3[i]->SetFillColor(0);
    legend_3[i]->SetTextSize(0.027);
  }

 
  TH2D *Z0MassGS = (TH2D*)fil1->Get("diMuonsSTAInvMassVsY");


  TH1D *service = (TH1D*)Z0MassGS->ProjectionY("service");
  int Rap_bin_bound[100];

  TH1D *dimuonsSTAInvMassVsRap[10];


  TCanvas *CanvRap3 = new TCanvas("CanvRap3"," Z0 Yield Vs. Rap ", 40,40,1200,900);
  CanvRap3->Divide(2,2);
    

  for (Int_t ih = 0; ih < NRapbin; ih++) {
    CanvRap3->cd(ih+1);
    gPad->SetTickx();
    gPad->SetTicky();

    // Project 1 D 
    Rap_bin_bound[ih] = service->FindBin(Rap_bound[ih]+0.0000001);
    Rap_bin_bound[ih+1] = service->FindBin(Rap_bound[ih+1]+0.0000001);
    sprintf(nameRap1,"Z0_Rap_%d",ih);
    dimuonsSTAInvMassVsRap[ih] = (TH1D*)Z0MassGS->ProjectionX(nameRap3, Rap_bin_bound[ih], Rap_bin_bound[ih+1]-1);
    sprintf(text," Y = %.2f to %.2f ",  service->GetBinLowEdge(Rap_bin_bound[ih]), 
	      service->GetBinLowEdge(Rap_bin_bound[ih+1]-1)+service->GetBinWidth(Rap_bin_bound[ih+1]));

    dimuonsSTAInvMassVsRap[ih]->Rebin(1);


    //Fit Function + Bkg Function
    dimuonsSTAInvMassVsRap[ih]->Fit("RBWPOL","REQ", "", mass_low, mass_high);
    double par[20];
    RBWPOL->GetParameters(par);
    sprintf(nameRap3B,"Rap3B_%d",ih);
    backfunGG = new TF1(nameRap3B, Pol2, mass_low, mass_high, 3);
    backfunGG->SetParameters(&par[3]);
    
    float GGZ0Mass =RBWPOL->GetParameter(1);
    float GGZ0Width =RBWPOL->GetParameter(2);

    // Integrated Yield 
    float m_low =GGZ0Mass-(1.5 *GGZ0Width);
    float m_high =GGZ0Mass+(1.5 *GGZ0Width);
    
    TAxis *axs   = dimuonsSTAInvMassVsRap[ih]->GetXaxis();
    
    int binlow = axs->FindBin(m_low);
    int binhi  = axs->FindBin(m_high);
    
    Double_t bin_size = (1.0*dimuonsSTAInvMassVsRap[ih]->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
    
    Float_t int_sig = 0.0;
    for(Int_t bin = binlow; bin<=binhi;bin++) {
      int_sig+ = dimuonsSTAInvMassVsRap[ih]->GetBinContent(bin);
    }   

    double yld3  = int_sig- bin_size*backfunGG->Integral(m_low, m_high);
    eyld_cat3[ih] = TMath::Sqrt(int_sig + bin_size*backfunGG->Integral(m_low, m_high) );
    cout << " Rap = " << RAP[ih] << " STA STA Yield =  " << yld3 << "  Error =   " << eyld_cat3[ih] << endl; 

    yld_cat3[ih] = yld3;

    // Draw
    dimuonsSTAInvMassVsRap[ih]->SetMinimum(-.05*dimuonsSTAInvMassVsRap[ih]->GetMaximum());

    dimuonsSTAInvMassVsRap[ih]->SetMarkerStyle(kFullCircle);
    dimuonsSTAInvMassVsRap[ih]->SetMarkerColor(4);
    dimuonsSTAInvMassVsRap[ih]->SetMarkerSize(0.8);
    
    dimuonsSTAInvMassVsRap[ih]->DrawCopy("EPL");
    
    backfunGG->SetLineColor(kRed);
    backfunGG->SetLineWidth(2);
    
    backfunGG->Draw("same");

    lcat3->Draw("same"); 

    legend_3[ih]->AddEntry(dimuonsSTAInvMassVsRap[ih], text, "");

    legend_3[ih]->Draw("same");
    
  }
  
  double mom_err[100] = {0};

  TGraphErrors *Z0Rap_cat3 = new TGraphErrors(NRapbin, RAP, yld_cat3, mom_err, eyld_cat3);
  Z0Rap_cat3->SetMarkerStyle(20);
  Z0Rap_cat3->SetMarkerColor(2);
  Z0Rap_cat3->GetXaxis()->SetTitle("Y");
  Z0Rap_cat3->GetYaxis()->SetTitle("Counts");

  new TCanvas;
  Z0Rap_cat3->Draw("AP");
  lcat3->Draw("same"); 



  cout << endl << endl;


  ///////////////////////////////////////////////////////////////////

  // Efficiency correction
  if(isData==2) 
    {
      ofstream fileout("correction.txt");
      cout << " Efficiency =     Rap   Eff_cat1,  Eff_cat2,  Eff_cat3  " << endl;

      for (Int_t ih = 0; ih < NRapbin; ih++) {
	Eff_cat1[ih] = yld_cat1[ih]/gen_Rap[ih]; 
	Eff_cat2[ih] = yld_cat2[ih]/gen_Rap[ih]; 
	Eff_cat3[ih] = yld_cat3[ih]/gen_Rap[ih]; 

	fileout << RAP[ih] <<"   "<< Eff_cat1[ih] << "   " << Eff_cat2[ih] <<"    " << Eff_cat3[ih] << endl; 
	cout <<"            " << RAP[ih] <<"   "<< Eff_cat1[ih] << "   " << Eff_cat2[ih] << "   " << Eff_cat3[ih] << endl; 
      }
    }
  

  if(isData==1) {
    ifstream filein("correction.txt");
    cout << " Eff corrected yield=     Rap   yld_cat1,  yld_cat2,  yield_cat3  " << endl;
    for (Int_t ih = 0; ih < NRapbin; ih++) {

      filein >> RAP[ih] >>  Eff_cat1[ih] >>  Eff_cat2[ih]  >>  Eff_cat3[ih] ; 
      cout << "     " << RAP[ih] << "   "<< yld_cat1[ih]/ Eff_cat1[ih] << "    " << yld_cat2[ih]/ Eff_cat2[ih] <<"   " <<  yld_cat3[ih]/ Eff_cat3[ih] << endl;

    }
  }
  


}
