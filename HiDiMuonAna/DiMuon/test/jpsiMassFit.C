////////////////////////////////////////////////////////
// Fit Macro for Z0 in dimuon channel 
//
// Authors: CMS Heavy Ion Dilepton PiNG 
// Prashant Shukla and Vineet Kumar
/////////////////////////////////////////////////////////

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TROOT.h>
#include <TDirectory.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TMath.h>
#include <TGraphAsymmErrors.h>

// miscellaneous  
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>


#endif




#include "FitFunctions.h"

void jpsiMassFit(int isData = 1, int nff = 2, int yieldInt = 1, int iSpec = 1)
{

  // gROOT->Macro("rootlogon.C+");

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
  

  int whis = 1; // 1 for all eta, pT decided by PtBin
                //2 for barrel pT all (0,30)
                // 21 for single muon pt > 4 GeV
                // 3 for |y| < 1.2   & 6.5<pt<30 
                // 4 for  1.2<|y|< 1.6   &  2<pt<30 
                // 5 for   1.6<|y|<2.4   &  0<pt<30 
  
  //use with whis=1 and iSpec =1;
  int PtBin = 2;  //1 pT [0,30]  
                  //2 pT [6.5,30]
                  //3 pT {0, 5.0, 10.0, 30.0};
                  //4 pT {6.5, 10.0, 12.0, 30.0};}

  //gStyle->SetOptStat(1);
  gStyle->SetOptStat(0);
  //gStyle->SetOptFit(1111);
  gStyle->SetOptFit(0000); 
  
  // Fit ranges
  float mass_low, mass_high, mlow, mhigh;
  int nrebin;
  bool isLog, isFit;
  double MassZ0, WidthZ0;
  
  // Low mass range J/psi
  MassZ0 = 3.096; WidthZ0 = 0.040;
  mass_low = 2.6; mass_high = 3.7;  // Fit ranges
  mlow = 2.6; mhigh = 3.7;   // Draw ranges
  nrebin = 1; isLog = 0; isFit = 1; // draw ranges
  
    
  // Open the file 

  if (isData == 1) TFile *fil1 = new TFile("PromtRecoV3_DiMuonPlot_WithCut_Nov30All.root");  // With cut

  //  if (isData == 1) TFile *fil1 = new TFile("PromtRecoV2V3_DiMuonPlot_WithCut_26Nov_All.root");  // With cut
  
  if (isData == 2) TFile *fil1 = new TFile("MCJPsi_Grid_DiMuonPlot_All.root");
  
  //if (isData == 2) TFile *fil1 = new TFile("MCJPsi_Grid_DiMuonPlot_2180.root");
  
  //  if (isData == 1) TFile *fil1 = new TFile("CathNew_WithOutCut_DiMuonPlot.root");  // Without cut
  
  //  if (isData == 1) TFile *fil1 = new TFile("CathNewV2V3_DiMuonPlot_WithCut_All.root");  // With cut
  
  
  
  // Pt bin sizes
  int Nptbin;
  float GenRange;
  double pt_bound[10];
  
  if(iSpec == 1) { 
    GenRange = 20;

    if(whis ==1 && PtBin==1){Nptbin=1; double pt_bound[10] = {0.0, 30.0};}
    
    if(whis==1 && PtBin==2){Nptbin=1; double pt_bound[10] = {6.5, 30.0};}    

    if(whis==1 && PtBin==3){Nptbin=3; double pt_bound[10] = {0, 5.0, 10.0, 30.0};}

    if(whis==1 && PtBin==4){Nptbin=3;  double pt_bound[10] = {6.5, 10.0, 12.0, 30.0};}

    if(whis == 2) {Nptbin = 1; double pt_bound[10] = {0.0, 30.0}; } // 2 for  |etaMu|<0.8  
    if(whis == 21) {Nptbin = 1; double pt_bound[10] = {0.0, 30.0}; } // 2 for  |etaMu|<0.8  
    
    if(whis == 3) {Nptbin = 1;double pt_bound[10] = {6.5, 30.0}; } // 3 for  |y|<1.2  
    if(whis == 4) {Nptbin = 1;double pt_bound[10] = {2.0, 30.0}; } // 4 for  1.2<|y|< 1.6  
    if(whis == 5) {Nptbin = 1;Nptbin = 1;double pt_bound[10] = {0.0, 30.0}; } // 5 for  1.6<|y|<2.4  
  }
  
  
  // Y bin sizes
  if(iSpec == 2) {
    Nptbin = 3;
    GenRange = 4.8;
    double pt_bound[10] = {-2.0, -1.0, 1.0, 2.0};
    //    double pt_bound[10] = {-2.4, -1.6, -1.2, 1.2, 1.6, 2.4};
  }
  

  // Cen bin sizes
  if(iSpec == 3) {
    Nptbin = 4;
    GenRange = 40;
    //    double pt_bound[10] = {0, 4, 8, 16, 24, 32, 40};
    double pt_bound[10] = {0, 4, 12, 24, 36};

  }

  double PT[10], DelPT[10], mom_err[100];
  for (Int_t ih = 0; ih < Nptbin; ih++) {
    PT[ih] = (pt_bound[ih] + pt_bound[ih+1])/2.0;
    DelPT[ih] = pt_bound[ih+1] - pt_bound[ih];
    mom_err[ih] = DelPT[ih]/2.0;
  }

  // Generated Numbers 

  int  TotalFlat = 2180.0;  // J/psi

  float gen_pt[10];

  for (Int_t ih = 0; ih < Nptbin; ih++) {
    gen_pt[ih] = TotalFlat*DelPT[ih]/GenRange;
  }
  
  // Fit Function RBW + Pol2

  char *name_fit[] = {"  ", "RBWPol1", "GausPol1", "RBWGausPol1"};

  if(nff == 1) TF1 *RBWPOL = new TF1("RBWPOL", RBWPol2, 0, 200, 6);
  if(nff == 2) TF1 *RBWPOL = new TF1("RBWPOL", GausPol2, 0, 200, 6);
  if(nff == 3) TF1 *RBWPOL = new TF1("RBWPOL", RBWGausPol2, 0, 200, 7);

  RBWPOL->SetLineWidth(1.4);


  RBWPOL->SetParameter(1, MassZ0);
  RBWPOL->SetParameter(2, WidthZ0);

  RBWPOL->SetParLimits(1, 0.9*MassZ0, 1.1*MassZ0);
  RBWPOL->SetParLimits(2, 0.1*WidthZ0, 5.0*WidthZ0);
  
  //  if(nff == 1 || nff == 2) RBWPOL->FixParameter(5, 0);

  if(nff == 3) {
    RBWPOL->SetParameter(3, WidthZ0);
    RBWPOL->SetParLimits(3, 0.1, 20);
    RBWPOL->FixParameter(2, WidthZ0);
    RBWPOL->FixParameter(6, 0);
  }

  // Efficiency
  float Eff_cat_1[10], Eff_cat_2[10], Eff_cat_3[10]; 
  float errEff_cat_1[10], errEff_cat_2[10], errEff_cat_3[10]; 
  char *Xname[] = {" ", "p_{T}^{Dimuon} (GeV/c)", "rapidity", "centrality"};

  double yld_cat_1[10], yld_cat_2[10], yld_cat_3[10];
  double cyld_cat_1[10], cyld_cat_2[10], cyld_cat_3[10];
  double eyld_cat_1[10], eyld_cat_2[10], eyld_cat_3[10];
  double ceyld_cat_1[10], ceyld_cat_2[10], ceyld_cat_3[10];

  char namePt_1[500], namePt_2[500], namePt_3[500];
  char namePt_1S[500], namePt_2S[500], namePt_3S[500];
  char namePt_1B[500], namePt_2B[500], namePt_3B[500];

  char text[100];

  ///// Write the spectra 
  char fspectra[500];
  sprintf(fspectra,"fileSpecta%d.root", yieldInt);
  TFile *fileSpectra = new TFile(fspectra, "recreate");


  ///////////////////////////////////////////////////////////////////////
  // Category _1 
  TLegend *lcat_1;
  lcat_1 = new TLegend(.1, .82, .50, .93);
  lcat_1->SetName("lcat_1");
  lcat_1->SetBorderSize(0);
  lcat_1->SetFillStyle(0);
  lcat_1->SetFillColor(0);
  lcat_1->SetTextSize(0.032);
  lcat_1->AddEntry(RBWPOL," CMS Preliminary", " ");
  lcat_1->AddEntry(RBWPOL," PbPb at  #sqrt{s_{NN}} = 2.76 TeV ", " ");
  //  lcat_1->AddEntry(RBWPOL," Global-Global ", "");
  //lcat_1->AddEntry(RBWPOL," |y| < 2.4 ", "P");
  //lcat_1->AddEntry(RBWPOL," Run# 150431-151027 ", "P");

  TLegend *legend_1[12];
  for(int i=0; i<12; i++) { 
    if(isFit) legend_1[i] = new TLegend(.63, .52, .91, 0.93 );
    if(!isFit) legend_1[i] = new TLegend(.63, .66, .91, 0.93 );
    //    legend_1[i] = new TLegend(.63, .66, .91, 0.93 );

    legend_1[i]->SetBorderSize(0);
    legend_1[i]->SetFillStyle(0);
    legend_1[i]->SetFillColor(0);
    legend_1[i]->SetTextSize(0.032);
  }

  TH2D * Z0Mass_1;

  if(whis == 1 && iSpec == 1 ) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPt");
  if(whis == 21 && iSpec == 1 ) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPtPtCut");
  if(whis == 2 && iSpec == 1) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPtBRL");

  if(whis == 3 && iSpec == 1) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPt12");

  if(whis == 4 && iSpec == 1) {
    Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPt16");
    TH2D *m12 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPt12");
    Z0Mass_1->Add(m12, -1);
  }

  if(whis == 5 && iSpec == 1) {
    Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPt");
    TH2D *m16 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPt16");
    Z0Mass_1 = Z0Mass_1->Add(m16, -1);
  }


  if(iSpec == 2) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsY");

  if(whis == 1 && iSpec == 3) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsCen");
  if(whis == 21 && iSpec == 3) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsCenPtCut");
  if(whis == 2 && iSpec == 3) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsCenBRL");

  TH2D * Z0Mass_1S;

  if(whis == 1 && iSpec == 1) Z0Mass_1S = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsPt");
  if(whis == 21 && iSpec == 1) Z0Mass_1S = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsPtPtCut");

  if(whis == 2 && iSpec ==1) Z0Mass_1S = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsPtBRL");
  if(whis == 3 && iSpec == 1) Z0Mass_1S = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsPt12");

  if(whis == 4 && iSpec == 1) {
    Z0Mass_1S = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsPt16");
    TH2D *m12 = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsPt12");
    Z0Mass_1S = Z0Mass_1S->Add(m12, -1);
  }

  if(whis == 5 && iSpec == 1) {
    Z0Mass_1S = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsPt");
    TH2D *m16 = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsPt16");
    Z0Mass_1S = Z0Mass_1S->Add(m16, -1);
  }

  if(iSpec == 2) Z0Mass_1S = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsY");

  if(whis ==1 && iSpec == 3) Z0Mass_1S = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsCen");
  if(whis == 21 && iSpec == 3) Z0Mass_1S = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsCenPtCut");
  if(whis == 2 && iSpec == 3) Z0Mass_1S = (TH2D*)fil1->Get("diMuonsGlobalSameChargeInvMassVsCenBRL");



  TH1D *service = (TH1D*)Z0Mass_1->ProjectionY("service");

  int pt_bin_bound[100];
  
  TH1D *dimuonsGlobalInvMassVsPt[10],  *dimuonsGlobalInvMassVsPtS[10];


  TCanvas *CanvPt_1 = new TCanvas("CanvPt_1"," Z0 Yield Vs. Pt ", 40,40,1000,700);

  if (Nptbin == 2)  CanvPt_1->Divide(2,1);
  if (Nptbin == 3 || Nptbin == 4)  CanvPt_1->Divide(2,2);
  if (Nptbin == 5 || Nptbin == 6)  CanvPt_1->Divide(3,2);

    
  cout << endl << Xname[iSpec] << "    Yield      Mass (GeV)    Width (GeV)    GauWidth    chi2/ndf " << endl << endl; 

  for (Int_t ih = 0; ih < Nptbin; ih++) {
    CanvPt_1->cd(ih+1);
    gPad->SetTickx();
    gPad->SetTicky();

    // Project 1 D 
    pt_bin_bound[ih] = service->FindBin(pt_bound[ih]+0.0000001);
    pt_bin_bound[ih+1] = service->FindBin(pt_bound[ih+1]+0.0000001);
    sprintf(namePt_1,"Z0_1_pt_%d",ih);
    sprintf(namePt_1S,"Z0_1S_pt_%d",ih);

    dimuonsGlobalInvMassVsPt[ih] = (TH1D*)Z0Mass_1->ProjectionX(namePt_1, pt_bin_bound[ih], pt_bin_bound[ih+1]-1, "e");

    //h1->ProjectionX("m",1,h1->GetNbinsY()+1,"e")


    dimuonsGlobalInvMassVsPtS[ih] = (TH1D*)Z0Mass_1S->ProjectionX(namePt_1S, pt_bin_bound[ih], pt_bin_bound[ih+1]-1);

    sprintf(text," %s [%.1f, %.1f]", Xname[iSpec], service->GetBinLowEdge(pt_bin_bound[ih]), 
	      service->GetBinLowEdge(pt_bin_bound[ih+1]-1)+service->GetBinWidth(pt_bin_bound[ih+1]));

    if(iSpec==3)  sprintf(text," %s [%.1f, %.1f]", Xname[iSpec], 2.5*service->GetBinLowEdge(pt_bin_bound[ih]), 
	    2.5*service->GetBinLowEdge(pt_bin_bound[ih+1]-1)+2.5*service->GetBinWidth(pt_bin_bound[ih+1]));


    dimuonsGlobalInvMassVsPt[ih]->Rebin(nrebin);
    dimuonsGlobalInvMassVsPtS[ih]->Rebin(nrebin);

    //Fit Function + Bkg Function
    if(isFit)  dimuonsGlobalInvMassVsPt[ih]->Fit("RBWPOL","LEQ", "", mass_low, mass_high);
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
    //    float m_low =GGZ0Mass-(3.0*GGZ0Width);
    //    float m_high =GGZ0Mass+(3.0*GGZ0Width);

    float m_low = 3.0;
    float m_high = 3.2;

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
    //    dimuonsGlobalInvMassVsPt[ih]->SetMinimum(-.05*dimuonsGlobalInvMassVsPt[ih]->GetMaximum());

    if(isLog) gPad->SetLogy(1);

    // color schemes
    TColor *pal = new TColor();
    Int_t kblue = pal->GetColor(9,0,200);
    Int_t korange  = pal->GetColor(101, 42,  0);

    dimuonsGlobalInvMassVsPt[ih]->SetMarkerStyle(21);
    dimuonsGlobalInvMassVsPt[ih]->SetMarkerColor(kblue);
    dimuonsGlobalInvMassVsPt[ih]->SetLineColor(kblue);
    dimuonsGlobalInvMassVsPt[ih]->SetMarkerSize(0.8);
    dimuonsGlobalInvMassVsPt[ih]->GetXaxis()->SetTitle("Dimuon mass (GeV/c^{2})");
    dimuonsGlobalInvMassVsPt[ih]->GetYaxis()->SetTitle("Events/( 25 MeV/c^{2})");

    dimuonsGlobalInvMassVsPt[ih]->GetXaxis()->SetRangeUser(mlow,mhigh);

    //    dimuonsGlobalInvMassVsPt[ih]->Add(dimuonsGlobalInvMassVsPtS[ih], -1);

    dimuonsGlobalInvMassVsPt[ih]->DrawCopy("EPL");

    // same charge
    dimuonsGlobalInvMassVsPtS[ih]->SetMarkerStyle(8);
    dimuonsGlobalInvMassVsPtS[ih]->SetMarkerColor(46);
    dimuonsGlobalInvMassVsPtS[ih]->SetLineColor(46);

    dimuonsGlobalInvMassVsPtS[ih]->SetMarkerSize(0.8);
    dimuonsGlobalInvMassVsPtS[ih]->DrawCopy("EPsame");

    //    RBWPOL->SetLineColor(kblue);
    backfun_1->SetLineColor(46);
    backfun_1->SetLineWidth(1.4);
    if(isFit) backfun_1->Draw("same");

    lcat_1->Draw("same"); 


    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih]," Global-Global", " ");
    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih]," |y| < 2.4 ", "");  
    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], text, "");
    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih]," Opposite Charge ", "LP");
    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPtS[ih]," Same Charge ", "LP");
    
    char label_1[512], label_2[512], label_3[512], label_4[512];

    //    isFit = 0;

    if(isFit) sprintf(label_1, "N=%1.2f #pm %1.2f ", yld_cat_1[ih], eyld_cat_1[ih]);

    if(!isFit) sprintf(label_1, "N_{J/#psi} #approx 200");

    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], label_1, "");
    sprintf(label_2, "m=%1.3f #pm %1.3f GeV/c^{2}", RBWPOL->GetParameter(1), RBWPOL->GetParError(1));
    if(isFit) legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], label_2, "");
    sprintf(label_3, "#sigma=%1.3f #pm %1.3f GeV/c^{2}", RBWPOL->GetParameter(2), RBWPOL->GetParError(2));
    if(nff==3) sprintf(label_3, "#sigma=%1.3f #pm %1.3f GeV/c^{2}", RBWPOL->GetParameter(3), RBWPOL->GetParError(3));
    if(isFit) legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], label_3, "");

    sprintf(label_4, "#chi^{2}/ndf = %1.2f / %d ", chisq, ndf);
    if(isFit) legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], label_4, "");

    legend_1[ih]->Draw("same");
    
  }

  cout << endl << endl;

  CanvPt_1->Print("Pt_Z0MassCat_1.png");
 
  if(iSpec == 3) {
    for (Int_t ih = 0; ih < Nptbin; ih++) {
      PT[ih] = 2.5*PT[ih];
      DelPT[ih] = 2.5*DelPT[ih] ;
      mom_err[ih] = DelPT[ih]/2.0;
    }
  }


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



  //////////////////////////////////////////////////////////////////////////////

  // Efficiency correction
  if(isData==2) 
    {
      ofstream fileout("correction.txt");
      cout << Xname[iSpec] << "   Eff_cat_1  " << endl;
      
      for (Int_t ih = 0; ih < Nptbin; ih++) {
	Eff_cat_1[ih] = yld_cat_1[ih]/gen_pt[ih]; 
	Eff_cat_2[ih] = yld_cat_2[ih]/gen_pt[ih]; 
	Eff_cat_3[ih] = yld_cat_3[ih]/gen_pt[ih]; 
	
	errEff_cat_1[ih] = eyld_cat_1[ih]/gen_pt[ih]; 
	errEff_cat_2[ih] = eyld_cat_2[ih]/gen_pt[ih]; 
	errEff_cat_3[ih] = eyld_cat_3[ih]/gen_pt[ih]; 
	
	
	//	fileout << PT[ih] <<"   "<< Eff_cat_1[ih] << "   " << Eff_cat_2[ih] <<"    " << Eff_cat_3[ih] << endl; 
	//	cout <<"    " << PT[ih] <<"      "<< Eff_cat_1[ih] << "      " << Eff_cat_2[ih] << "      " << Eff_cat_3[ih] << endl; 
	
	fileout << PT[ih] <<"   "<< Eff_cat_1[ih] << "   " << errEff_cat_1[ih] << endl; 
	cout <<"    " << PT[ih] <<"    "<< Eff_cat_1[ih] << " +- " << errEff_cat_1[ih] << endl;
	cyld_cat_1[ih] = Eff_cat_1[ih];
	ceyld_cat_1[ih] = errEff_cat_1[ih];
 
     }
    }
  
  
  if(isData==1) {
    ifstream filein("correction.txt");
    cout <<  Xname[iSpec] << " yld_cat_1 "  << "  efficiency " <<  " corr. yld_cat_1  " << endl;
    for (Int_t ih = 0; ih < Nptbin; ih++) {

      //      filein >> PT[ih] >>  Eff_cat_1[ih] >>  Eff_cat_2[ih]  >>  Eff_cat_3[ih] ; 
      //      cout << "       " << PT[ih] << "      "<< yld_cat_1[ih] << "       " << yld_cat_2[ih] <<"      " <<  yld_cat_3[ih] << endl;

      filein >> PT[ih] >>  Eff_cat_1[ih]  >> errEff_cat_1[ih]; 
      cout << "    " << PT[ih] << "     " << yld_cat_1[ih] << "     " << Eff_cat_1[ih] << "     " << yld_cat_1[ih]/Eff_cat_1[ih] << endl;
      cyld_cat_1[ih] = yld_cat_1[ih]/Eff_cat_1[ih];
      ceyld_cat_1[ih] = eyld_cat_1[ih]/Eff_cat_1[ih];

    }
  }

  TF1 *EXPA = new TF1("EXPA", Exp, 0, 100, 2);

  TGraphErrors *Z0ptC_cat_1 = new TGraphErrors(Nptbin, PT, cyld_cat_1, mom_err, ceyld_cat_1);
  Z0ptC_cat_1->SetMarkerStyle(20);
  Z0ptC_cat_1->SetMarkerColor(2);
  Z0ptC_cat_1->GetXaxis()->SetTitle(Xname[iSpec]);
  Z0ptC_cat_1->GetYaxis()->SetTitle("counts");
  //  if(part == 2) Z0ptC_cat_1->Fit("EXPA","LEQ", "", 7, 16);


  new TCanvas;
  Z0ptC_cat_1->SetMinimum(0.0);
  Z0ptC_cat_1->SetName("Z0ptC_cat_1");
  Z0ptC_cat_1->Draw("AP");
  lcat_1->Draw("same"); 

  cout << endl << endl;

  Z0ptC_cat_1->Write();

}



  /*
  //  gStyle->SetPadTopMargin(0.15);
  //  gStyle->SetPadBottomMargin(0.13);
  //  gStyle->SetPadLeftMargin(0.13);
  //  gStyle->SetPadRightMargin(0.15);
    
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(600); // Height of canvas
  gStyle->SetCanvasDefW(600); // Width of canvas

  gStyle->SetCanvasColor(10);
  gStyle->SetPadColor(0);
  gStyle->SetHistLineWidth(1.0);
  gStyle->SetOptTitle(0);
  */

