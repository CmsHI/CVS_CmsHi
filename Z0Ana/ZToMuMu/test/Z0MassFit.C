//root macro to calculate Z0 yeild in all Z0 categories
//it takes out put of ZMuMuPlots_cfg.py and 
// if isdata =2 take simulated events and if you give total no of input events then write efficiency in file correction.txt   
//if isdata =1 take efficiency from correction.txt and calculate Z0 yeild in all categories and error on them.
// fit functions relativistic breit wigner + second degree polinomial. Yeild is calculated in 3 sigma from RBW mass.   

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
void Z0Fit(int isData=1, int Nptbin=1)
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


  // Generated Numbers
  float gen_pt[10] = {2000};
  float pt[10], Eff[10]; 

  // Pt bin sizes
  
  if (Nptbin = 1)  float pt_bin[10] = {0, 20.0, 30.0};
  if (Nptbin = 2)  float pt_bin[10] = {0, 10.0, 20.0, 30};
  if (Nptbin = 3)  float pt_bin[10] = {0., 6.0, 12.0, 18.0, 30};


  // Centrality bin sizes
  //  {0, 100.0};
  //  {0, 50.0, 100.0};
  //  {0.0, 30.0, 60.0, 100.0};


  // Fit Function RBW + Pol

  TF1 *RBWPOL = new TF1("RBWPOL", "[0]*x*[1]*[2]*0.5/TMath::Pi()/TMath::Max(1.e-10,(x*x-[1]*[1]) * (x*x-[1]*[1])+[1]*[1]*[2]*[2])+  [3] + [4]*x + [5]*x**2 + [6]*x**3", 10, 120);
  RBWPOL->SetParNames("N","m_{0}", "#Gamma", "p_{0}", "p_{1}", "p_{2}");
  //RBWPOL->FixParameter(1,MassZ0);
  RBWPOL->SetParLimits(1, 84, 98);
  RBWPOL->SetParLimits(2, 1, 8);
  RBWPOL->FixParameter(6,0);

  // Fit ranges
  float mass_low = 10.0;
  float mass_high = 120.0;

  // Yield extraction range
  float m_low = 85.0;
  float m_high = 97.0;



  // Open the file 
  TFile *fil1 = new TFile("TestForGen_Plot.root");



  double yld_cat1[10], yld_cat2[10], yld_cat3[10];

  double eyld_cat1[10], eyld_cat2[10], eyld_cat3[10];


  
  ///////////////////////////////////////////////////////////////////////
  // Category 1 
  TLegend *lcat1;
  lcat1 = new TLegend(.05, .80, .50, .72);
  lcat1->SetName("lphenix");
  lcat1->SetBorderSize(0);
  lcat1->SetFillStyle(0);
  lcat1->SetFillColor(0);
  lcat1->SetTextSize(0.027);
  lcat1->AddEntry(RBWPOL," PbPb at  #sqrt{s_{NN}} = 2.76 TeV ", " ");
  lcat1->AddEntry(RBWPOL," Global-Global ", "P");

 
  TH1D *Z0MassGG = (TH1D*)fil1->Get("dimuonsGlobalPlots/zMass");
  Z0MassGG->Rebin(1);
  Z0MassGG->Fit("RBWPOL","REQ", "", mass_low, mass_high);
  
  double par[20];

  RBWPOL->GetParameters(par);
  
  backfunGG = new TF1("backfunGG", "[0] + [1]*x + [2]*x**2 + [3]*x**3", mass_low, mass_high);
  backfunGG->SetParameters(&par[3]);

  float GGZ0Mass =RBWPOL->GetParameter(1);
  float GGZ0Width =RBWPOL->GetParameter(2);
  
  cout<<"***************************************************************"<<endl;
  cout<< " Global Global Z0 Mass: " << GGZ0Mass << " Width: " <<GGZ0Width<<endl;

  float m_low =GGZ0Mass-(1.5 *GGZ0Width);
  float m_high =GGZ0Mass+(1.5 *GGZ0Width);


  TAxis *axs   = Z0MassGG->GetXaxis();

  int binlow = axs->FindBin(m_low);
  int binhi  = axs->FindBin(m_high);
  
  Double_t bin_size = (1.0*Z0MassGG->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());


  Float_t int_sig = 0.0;
  for(Int_t bin = binlow; bin<=binhi;bin++) {
    int_sig+ = Z0MassGG->GetBinContent(bin);
  }   
  

  yld_cat1[0]  = int_sig - bin_size*backfunGG->Integral(m_low, m_high);
  eyld_cat1[0] = TMath::Sqrt(int_sig + bin_size*backfunGG->Integral(m_low, m_high) );

  cout <<  yld_cat1[0]<<"  "<< eyld_cat1[0]<<endl; 
  cout<<"***************************************************************"<<endl;

  cout<< pt_bin[1]<< " "<<pt_bin[0]<<endl;
  

  pt[0] = (pt_bin[1] + pt_bin[0])/2.0;

  //ofstream fileout("correction.txt");
  if(isData==2) 
    {
      ofstream fileout("correction.txt");
      Eff[0] = yld_cat1[0]/gen_pt[0]; 
      fileout << pt[0] <<"      "<<Eff[0]; 
    }
  

  if(isData==1) {
    ifstream filein("correction.txt");
    filein >> pt[0] >>  Eff[0]; 
    cout << pt[0] << Eff[0] << endl;
    cout << " Eff corrected yeild " << yld_cat1[0]/ Eff[0];
  }
  

  // Simulation
  // if (isData == 2) {
  //ofstream fileout("correction.txt");
  //for (int pt_bin=0; pt_bin<Nptbin; pt_bin++) {
  //  fileout << [pt_bin]<<"  " <<ec_tof[pt_bin] << endl;
  //}
  //}

  // Data
  //if (isData == 1)  {
  //ifstream filein("correction.txt");
  //for (int pt_bin=0; pt_bin<12; pt_bin++) {
  //  filein >> c_tof[pt_bin] >> ec_tof[pt_bin] >> c_pc3[pt_bin] >> ec_pc3[pt_bin] >>
  //    c_trk[pt_bin] >> ec_trk[pt_bin] >> c_opp[pt_bin] >> ec_opp[pt_bin];
  //}
  //}




  // Draw
  Z0MassGG->SetMarkerStyle(kFullCircle);
  Z0MassGG->SetMarkerColor(4);
  Z0MassGG->SetMarkerSize(0.8);
  //new TCanvas;
  Z0MassGG->DrawCopy("EPL");
  
  backfunGG->SetLineColor(kRed);
  backfunGG->SetLineWidth(2);
  
  backfunGG->Draw("same");
  lcat1->Draw("same");
      

  ///////////////////////////////////////////////////////////
  // Category 2

  TLegend *lcat2;
  lcat2 = new TLegend(.05, .80, .50, .72);
  lcat2->SetName("lphenix");
  lcat2->SetBorderSize(0);
  lcat2->SetFillStyle(0);
  lcat2->SetFillColor(0);
  lcat2->SetTextSize(0.027);
  lcat2->AddEntry(RBWPOL," PbPb at  #sqrt{s_{NN}} = 2.76 TeV ", " ");
  lcat2->AddEntry(RBWPOL," Global-STA ", "P");

  TH1D *Z0MassGS = (TH1D*)fil1->Get("dimuonsGlobalSTAPlots/zMass");
  Z0MassGS->Rebin(4);
  
  // Fit ranges
  float mass_low = 10.0;
  float mass_high = 140.0;
 
  RBWPOL->SetParLimits(1, 80, 90);
  RBWPOL->SetParLimits(2, 10, 20);
  RBWPOL->FixParameter(6,0);
  


  new TCanvas;
  Z0MassGS->Fit("RBWPOL","REQ", "", mass_low, mass_high);
  
  float GSZ0Mass =RBWPOL->GetParameter(1);
  float GSZ0Width =RBWPOL->GetParameter(2);
   
  cout<<"***************************************************************"<<endl;
  cout<< " Global Sta  Z0 Mass: " << GSZ0Mass << " Width: " <<GSZ0Width<<endl;
  double par[20];
  RBWPOL->GetParameters(par);
  backfunGS = new TF1("backfunGS", "[0] + [1]*x + [2]*x**2 + [3]*x**3", mass_low, mass_high);
  backfunGS->SetParameters(&par[3]);
  TAxis *axs   = Z0MassGS->GetXaxis();
  
  float m_low =GSZ0Mass-(1.5 *GSZ0Width);
  float m_high =GSZ0Mass+(1.5 *GSZ0Width);

  int binlow = axs->FindBin(m_low);
  int binhi  = axs->FindBin(m_high);
  
  Double_t bin_size = (1.0*Z0MassGS->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());

  Float_t int_sig = 0.0;
  for(Int_t bin = binlow; bin<=binhi;bin++) {
    int_sig+ = Z0MassGS->GetBinContent(bin);
  }   
 
  yld_cat1[0]  = int_sig - bin_size*backfunGS->Integral(m_low, m_high);
  eyld_cat1[0] = TMath::Sqrt(int_sig + bin_size*backfunGS->Integral(m_low, m_high) );

  cout <<  yld_cat1[0]<<"  "<< eyld_cat1[0]<<endl; 
  cout<<"***************************************************************"<<endl;

  // Draw
  Z0MassGS->SetMarkerStyle(kFullCircle);
  Z0MassGS->SetMarkerColor(4);
  Z0MassGS->SetMarkerSize(0.8);
  //new TCanvas;
  Z0MassGS->DrawCopy("EPL");
  
  backfunGS->SetLineColor(kRed);
  backfunGS->SetLineWidth(2);
  
  backfunGS->Draw("same");
  lcat2->Draw("same");
    
  ///////////////////////////////////////////////////////////
  // Category 3

  TLegend *lcat3;
  lcat3 = new TLegend(.05, .80, .50, .72);
  lcat3->SetName("lphenix");
  lcat3->SetBorderSize(0);
  lcat3->SetFillStyle(0);
  lcat3->SetFillColor(0);
  lcat3->SetTextSize(0.027);
  lcat3->AddEntry(RBWPOL," PbPb at  #sqrt{s_{NN}} = 2.76 TeV ", " ");
  lcat3->AddEntry(RBWPOL,"STA-STA ", "P");

  

  // Fit ranges
  float mass_low = 0.0;
  float mass_high = 130.0;
 
  RBWPOL->SetParLimits(1, 80, 100);
  RBWPOL->SetParLimits(2, 10, 24);
  RBWPOL->FixParameter(6,0);
 
 
  TH1D *Z0MassSS = (TH1D*)fil1->Get("dimuonsSTAPlots/zMass");
  Z0MassSS->Rebin(4);
  new TCanvas;
  Z0MassSS->Fit("RBWPOL","REQ", "", mass_low, mass_high);
  double par[20];
  RBWPOL->GetParameters(par);
  backfunSS = new TF1("backfunGS", "[0] + [1]*x + [2]*x**2 + [3]*x**3", mass_low, mass_high);
  backfunSS->SetParameters(&par[3]);

  float SSZ0Mass =RBWPOL->GetParameter(1);
  float SSZ0Width =RBWPOL->GetParameter(2);
  
  cout<<"***************************************************************"<<endl;
  cout<< " Sta Sta  Z0 Mass: " << SSZ0Mass << " Width: " <<SSZ0Width<<endl;

  float m_low =SSZ0Mass-(1.5 *SSZ0Width);
  float m_high =SSZ0Mass+(1.5 *SSZ0Width);
  
  TAxis *axs   = Z0MassSS->GetXaxis();
  
  int binlow = axs->FindBin(m_low);
  int binhi  = axs->FindBin(m_high);
  
  Double_t bin_size = (1.0*Z0MassSS->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
  
  
  Float_t int_sig = 0.0;
  for(Int_t bin = binlow; bin<=binhi;bin++) {
    int_sig+ = Z0MassSS->GetBinContent(bin);
  }   
  
  yld_cat1[0]  = int_sig - bin_size*backfunSS->Integral(m_low, m_high);
  eyld_cat1[0] = TMath::Sqrt(int_sig + bin_size*backfunSS->Integral(m_low, m_high) );
  
  cout <<  yld_cat1[0]<<"  "<< eyld_cat1[0]<<endl; 
  cout<<"***************************************************************"<<endl;
  
  // Draw
  Z0MassSS->SetMarkerStyle(kFullCircle);
  Z0MassSS->SetMarkerColor(4);
  Z0MassSS->SetMarkerSize(0.8);
  //new TCanvas;
  Z0MassSS->DrawCopy("EPL");
  
  backfunSS->SetLineColor(kRed);
  backfunSS->SetLineWidth(2);
  
  backfunSS->Draw("same");
  lcat3->Draw("same");



















}
