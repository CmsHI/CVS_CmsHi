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

void Z0Fit(int isData=2)
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
  
  // Pt bin sizes
  int Nptbin = 3;
  double pt_bound[10] = {0., 4.0, 8.0, 20.0};
  double PT[10], DelPT[10];
  for (Int_t ih = 0; ih < Nptbin; ih++) {
    PT[ih] = (pt_bound[ih] + pt_bound[ih+1])/2.0;
    DelPT[ih] = pt_bound[ih+1] - pt_bound[ih];
  }

  // Generated Numbers 
  int  TotalFlat = 2000;
  float gen_pt[10];

  for (Int_t ih = 0; ih < Nptbin; ih++) {
    gen_pt[ih] = 2000;
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

  char namePt1[500], namePt2[500], namePt3[500];
  char namePt1B[500], namePt2B[500], namePt3B[500];

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

 
  TH2D *Z0MassGG = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPt");


  TH1D *service = (TH1D*)Z0MassGG->ProjectionY("service");
  int pt_bin_bound[100];

  TH1D *dimuonsGlobalInvMassVsPt[10];


  TCanvas *CanvPt1 = new TCanvas("CanvPt1"," Z0 Yield Vs. Pt ", 40,40,1200,900);
  CanvPt1->Divide(2,2);
    

  for (Int_t ih = 0; ih < Nptbin; ih++) {
    CanvPt1->cd(ih+1);
    gPad->SetTickx();
    gPad->SetTicky();

    // Project 1 D 
    pt_bin_bound[ih] = service->FindBin(pt_bound[ih]+0.0000001);
    pt_bin_bound[ih+1] = service->FindBin(pt_bound[ih+1]+0.0000001);
    sprintf(namePt1,"Z0_pt_%d",ih);
    dimuonsGlobalInvMassVsPt[ih] = (TH1D*)Z0MassGG->ProjectionX(namePt1, pt_bin_bound[ih], pt_bin_bound[ih+1]-1);
    sprintf(text," p_{T} = %.2f-%.2f GeV/c",  service->GetBinLowEdge(pt_bin_bound[ih]), 
	      service->GetBinLowEdge(pt_bin_bound[ih+1]-1)+service->GetBinWidth(pt_bin_bound[ih+1]));

    dimuonsGlobalInvMassVsPt[ih]->Rebin(1);


    //Fit Function + Bkg Function
    dimuonsGlobalInvMassVsPt[ih]->Fit("RBWPOL","REQ", "", mass_low, mass_high);
    double par[20];
    RBWPOL->GetParameters(par);
    sprintf(namePt1B,"pt1B_%d",ih);
    backfunGG = new TF1(namePt1B, Pol2, mass_low, mass_high, 3);
    backfunGG->SetParameters(&par[3]);
    
    float GGZ0Mass =RBWPOL->GetParameter(1);
    float GGZ0Width =RBWPOL->GetParameter(2);

    // Integrated Yield 
    float m_low =GGZ0Mass-(1.5 *GGZ0Width);
    float m_high =GGZ0Mass+(1.5 *GGZ0Width);
    
    TAxis *axs   = dimuonsGlobalInvMassVsPt[ih]->GetXaxis();
    
    int binlow = axs->FindBin(m_low);
    int binhi  = axs->FindBin(m_high);
    
    Double_t bin_size = (1.0*dimuonsGlobalInvMassVsPt[ih]->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
    
    Float_t int_sig = 0.0;
    for(Int_t bin = binlow; bin<=binhi;bin++) {
      int_sig+ = dimuonsGlobalInvMassVsPt[ih]->GetBinContent(bin);
    }   

    double yld1  = int_sig- bin_size*backfunGG->Integral(m_low, m_high);
    eyld_cat1[ih] = TMath::Sqrt(int_sig + bin_size*backfunGG->Integral(m_low, m_high) );
    cout << " pT = " << PT[ih] << " Global Global Yield =  " << yld1 << "  Error =   " << eyld_cat1[ih] << endl; 

    yld_cat1[ih] = yld1;

    // Draw
    dimuonsGlobalInvMassVsPt[ih]->SetMinimum(-.05*dimuonsGlobalInvMassVsPt[ih]->GetMaximum());

    dimuonsGlobalInvMassVsPt[ih]->SetMarkerStyle(kFullCircle);
    dimuonsGlobalInvMassVsPt[ih]->SetMarkerColor(4);
    dimuonsGlobalInvMassVsPt[ih]->SetMarkerSize(0.8);
    
    dimuonsGlobalInvMassVsPt[ih]->DrawCopy("EPL");
    
    backfunGG->SetLineColor(kRed);
    backfunGG->SetLineWidth(2);
    
    backfunGG->Draw("same");

    lcat1->Draw("same"); 

    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], text, "");

    legend_1[ih]->Draw("same");
    
  }
  
  double mom_err[100] = {0};

  TGraphErrors *Z0pt_cat1 = new TGraphErrors(Nptbin, PT, yld_cat1, mom_err, eyld_cat1);
  Z0pt_cat1->SetMarkerStyle(20);
  Z0pt_cat1->SetMarkerColor(2);
  Z0pt_cat1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  Z0pt_cat1->GetYaxis()->SetTitle("counts");

  new TCanvas;
  Z0pt_cat1->Draw("AP");
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

 
  TH2D *Z0MassGS = (TH2D*)fil1->Get("diMuonsGlobalSTAInvMassVsPt");


  TH1D *service = (TH1D*)Z0MassGS->ProjectionY("service");
  int pt_bin_bound[100];

  TH1D *dimuonsGlobalSTAInvMassVsPt[10];


  TCanvas *CanvPt2 = new TCanvas("CanvPt2"," Z0 Yield Vs. Pt ", 40,40,1200,900);
  CanvPt2->Divide(2,2);
    

  for (Int_t ih = 0; ih < Nptbin; ih++) {
    CanvPt2->cd(ih+1);
    gPad->SetTickx();
    gPad->SetTicky();

    // Project 1 D 
    pt_bin_bound[ih] = service->FindBin(pt_bound[ih]+0.0000001);
    pt_bin_bound[ih+1] = service->FindBin(pt_bound[ih+1]+0.0000001);
    sprintf(namePt1,"Z0_pt_%d",ih);
    dimuonsGlobalSTAInvMassVsPt[ih] = (TH1D*)Z0MassGS->ProjectionX(namePt2, pt_bin_bound[ih], pt_bin_bound[ih+1]-1);
    sprintf(text," p_{T} = %.2f-%.2f GeV/c",  service->GetBinLowEdge(pt_bin_bound[ih]), 
	      service->GetBinLowEdge(pt_bin_bound[ih+1]-1)+service->GetBinWidth(pt_bin_bound[ih+1]));

    dimuonsGlobalSTAInvMassVsPt[ih]->Rebin(1);


    //Fit Function + Bkg Function
    dimuonsGlobalSTAInvMassVsPt[ih]->Fit("RBWPOL","REQ", "", mass_low, mass_high);
    double par[20];
    RBWPOL->GetParameters(par);
    sprintf(namePt2B,"pt2B_%d",ih);
    backfunGG = new TF1(namePt2B, Pol2, mass_low, mass_high, 3);
    backfunGG->SetParameters(&par[3]);
    
    float GGZ0Mass =RBWPOL->GetParameter(1);
    float GGZ0Width =RBWPOL->GetParameter(2);

    // Integrated Yield 
    float m_low =GGZ0Mass-(1.5 *GGZ0Width);
    float m_high =GGZ0Mass+(1.5 *GGZ0Width);
    
    TAxis *axs   = dimuonsGlobalSTAInvMassVsPt[ih]->GetXaxis();
    
    int binlow = axs->FindBin(m_low);
    int binhi  = axs->FindBin(m_high);
    
    Double_t bin_size = (1.0*dimuonsGlobalSTAInvMassVsPt[ih]->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
    
    Float_t int_sig = 0.0;
    for(Int_t bin = binlow; bin<=binhi;bin++) {
      int_sig+ = dimuonsGlobalSTAInvMassVsPt[ih]->GetBinContent(bin);
    }   

    double yld2  = int_sig- bin_size*backfunGG->Integral(m_low, m_high);
    eyld_cat2[ih] = TMath::Sqrt(int_sig + bin_size*backfunGG->Integral(m_low, m_high) );
    cout << " pT = " << PT[ih] << " Global STA Yield =  " << yld2 << "  Error =   " << eyld_cat2[ih] << endl; 

    yld_cat2[ih] = yld2;

    // Draw
    dimuonsGlobalSTAInvMassVsPt[ih]->SetMinimum(-.05*dimuonsGlobalSTAInvMassVsPt[ih]->GetMaximum());

    dimuonsGlobalSTAInvMassVsPt[ih]->SetMarkerStyle(kFullCircle);
    dimuonsGlobalSTAInvMassVsPt[ih]->SetMarkerColor(4);
    dimuonsGlobalSTAInvMassVsPt[ih]->SetMarkerSize(0.8);
    
    dimuonsGlobalSTAInvMassVsPt[ih]->DrawCopy("EPL");
    
    backfunGG->SetLineColor(kRed);
    backfunGG->SetLineWidth(2);
    
    backfunGG->Draw("same");

    lcat2->Draw("same"); 

    legend_2[ih]->AddEntry(dimuonsGlobalSTAInvMassVsPt[ih], text, "");

    legend_2[ih]->Draw("same");
    
  }
  
  double mom_err[100] = {0};

  TGraphErrors *Z0pt_cat2 = new TGraphErrors(Nptbin, PT, yld_cat2, mom_err, eyld_cat2);
  Z0pt_cat2->SetMarkerStyle(20);
  Z0pt_cat2->SetMarkerColor(2);
  Z0pt_cat2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  Z0pt_cat2->GetYaxis()->SetTitle("Counts");

  new TCanvas;
  Z0pt_cat2->Draw("AP");
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

 
  TH2D *Z0MassGS = (TH2D*)fil1->Get("diMuonsSTAInvMassVsPt");


  TH1D *service = (TH1D*)Z0MassGS->ProjectionY("service");
  int pt_bin_bound[100];

  TH1D *dimuonsSTAInvMassVsPt[10];


  TCanvas *CanvPt3 = new TCanvas("CanvPt3"," Z0 Yield Vs. Pt ", 40,40,1200,900);
  CanvPt3->Divide(2,2);
    

  for (Int_t ih = 0; ih < Nptbin; ih++) {
    CanvPt3->cd(ih+1);
    gPad->SetTickx();
    gPad->SetTicky();

    // Project 1 D 
    pt_bin_bound[ih] = service->FindBin(pt_bound[ih]+0.0000001);
    pt_bin_bound[ih+1] = service->FindBin(pt_bound[ih+1]+0.0000001);
    sprintf(namePt1,"Z0_pt_%d",ih);
    dimuonsSTAInvMassVsPt[ih] = (TH1D*)Z0MassGS->ProjectionX(namePt3, pt_bin_bound[ih], pt_bin_bound[ih+1]-1);
    sprintf(text," p_{T} = %.2f-%.2f GeV/c",  service->GetBinLowEdge(pt_bin_bound[ih]), 
	      service->GetBinLowEdge(pt_bin_bound[ih+1]-1)+service->GetBinWidth(pt_bin_bound[ih+1]));

    dimuonsSTAInvMassVsPt[ih]->Rebin(1);


    //Fit Function + Bkg Function
    dimuonsSTAInvMassVsPt[ih]->Fit("RBWPOL","REQ", "", mass_low, mass_high);
    double par[20];
    RBWPOL->GetParameters(par);
    sprintf(namePt3B,"pt3B_%d",ih);
    backfunGG = new TF1(namePt3B, Pol2, mass_low, mass_high, 3);
    backfunGG->SetParameters(&par[3]);
    
    float GGZ0Mass =RBWPOL->GetParameter(1);
    float GGZ0Width =RBWPOL->GetParameter(2);

    // Integrated Yield 
    float m_low =GGZ0Mass-(1.5 *GGZ0Width);
    float m_high =GGZ0Mass+(1.5 *GGZ0Width);
    
    TAxis *axs   = dimuonsSTAInvMassVsPt[ih]->GetXaxis();
    
    int binlow = axs->FindBin(m_low);
    int binhi  = axs->FindBin(m_high);
    
    Double_t bin_size = (1.0*dimuonsSTAInvMassVsPt[ih]->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
    
    Float_t int_sig = 0.0;
    for(Int_t bin = binlow; bin<=binhi;bin++) {
      int_sig+ = dimuonsSTAInvMassVsPt[ih]->GetBinContent(bin);
    }   

    double yld3  = int_sig- bin_size*backfunGG->Integral(m_low, m_high);
    eyld_cat3[ih] = TMath::Sqrt(int_sig + bin_size*backfunGG->Integral(m_low, m_high) );
    cout << " pT = " << PT[ih] << " STA STA Yield =  " << yld3 << "  Error =   " << eyld_cat3[ih] << endl; 

    yld_cat3[ih] = yld3;

    // Draw
    dimuonsSTAInvMassVsPt[ih]->SetMinimum(-.05*dimuonsSTAInvMassVsPt[ih]->GetMaximum());

    dimuonsSTAInvMassVsPt[ih]->SetMarkerStyle(kFullCircle);
    dimuonsSTAInvMassVsPt[ih]->SetMarkerColor(4);
    dimuonsSTAInvMassVsPt[ih]->SetMarkerSize(0.8);
    
    dimuonsSTAInvMassVsPt[ih]->DrawCopy("EPL");
    
    backfunGG->SetLineColor(kRed);
    backfunGG->SetLineWidth(2);
    
    backfunGG->Draw("same");

    lcat3->Draw("same"); 

    legend_3[ih]->AddEntry(dimuonsSTAInvMassVsPt[ih], text, "");

    legend_3[ih]->Draw("same");
    
  }
  
  double mom_err[100] = {0};

  TGraphErrors *Z0pt_cat3 = new TGraphErrors(Nptbin, PT, yld_cat3, mom_err, eyld_cat3);
  Z0pt_cat3->SetMarkerStyle(20);
  Z0pt_cat3->SetMarkerColor(2);
  Z0pt_cat3->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  Z0pt_cat3->GetYaxis()->SetTitle("Counts");

  new TCanvas;
  Z0pt_cat3->Draw("AP");
  lcat3->Draw("same"); 



  cout << endl << endl;


  ///////////////////////////////////////////////////////////////////

  // Efficiency correction
  if(isData==2) 
    {
      ofstream fileout("correction.txt");
      cout << " Efficiency =     pT   Eff_cat1,  Eff_cat2,  Eff_cat3  " << endl;

      for (Int_t ih = 0; ih < Nptbin; ih++) {
	Eff_cat1[ih] = yld_cat1[ih]/gen_pt[ih]; 
	Eff_cat2[ih] = yld_cat2[ih]/gen_pt[ih]; 
	Eff_cat3[ih] = yld_cat3[ih]/gen_pt[ih]; 

	fileout << PT[ih] <<"   "<< Eff_cat1[ih] << "   " << Eff_cat2[ih] <<"    " << Eff_cat3[ih] << endl; 
	cout <<"            " << PT[ih] <<"   "<< Eff_cat1[ih] << "   " << Eff_cat2[ih] << "   " << Eff_cat3[ih] << endl; 
      }
    }
  

  if(isData==1) {
    ifstream filein("correction.txt");
    cout << " Eff corrected yield=     pT   yld_cat1,  yld_cat2,  yield_cat3  " << endl;
    for (Int_t ih = 0; ih < Nptbin; ih++) {

      filein >> PT[ih] >>  Eff_cat1[ih] >>  Eff_cat2[ih]  >>  Eff_cat3[ih] ; 
      cout << "     " << PT[ih] << "   "<< yld_cat1[ih]/ Eff_cat1[ih] << "    " << yld_cat2[ih]/ Eff_cat2[ih] <<"   " <<  yld_cat3[ih]/ Eff_cat3[ih] << endl;

    }
  }
  


}
