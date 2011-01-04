////////////////////////////////////////////////////////
// Fit Macro for Z0 in dimuon channel 
//// Authors: CMS Heavy Ion Dilepton PiNG 
// Prashant Shukla and Vineet Kumar
/////////////////////////////////////////////////////////

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "TROOT.h"
#include "Riostream.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TPad.h"
#include "TString.h"
#include "TStyle.h"
#include "TTree.h"
#include <fstream>
#include <iostream>
#include "stdio.h"
#include <string>
#endif


void Z0AccEff(int isData = 2, int yieldInt = 1, int iSpec = 3, int Weight =1)
{
  ////////  definitions of Switches   ///////////
  //  isData = 1 for Data
  //  isData = 2 for Simulation
  
    
  // iSpec = 1  pT spectra
  // iSpec = 2  Y spectra
  // iSpec = 3  Centrality Spectra
  
  //Weight = 1 for weighted histo
  //weight = 0  for non weighted histo



  ////////////////////////////////////////////////////////////
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0000); 

  // Fit ranges
  float mass_low, mass_high, mlow, mhigh;
  int nrebin;
  bool isLog, isFit;
  double MassZ0, WidthZ0;

  // High Mass range
  MassZ0 = 91.1876; WidthZ0 = 2.4952;
  mass_low = 60; mass_high = 120;  // Fit ranges Glb Glb
  //mass_low = 40; mass_high = 140;  // Fit ranges STA
  mlow = 0.0; mhigh = 200.0; nrebin = 80; isLog =0; isFit = 0; // draw ranges
  
  int whis = 1; // 1 for full all eta, 2 for barrel  //4 for trigger matched PAT
  
  //file one is good file

  TFile *fil1, *fil2;

  if (isData == 2) fil2 = new TFile("Z0_DataMixPt50_PatDiMuonPlots_All11Dec.root");
  //if (isData == 2) fil2 = new TFile("ReReco_DM_DiMuonPlot_All16Dec.root");
  if (isData == 2)  fil1 = new TFile("Z0HydPt50_PatDiMuonPlots_AllWOSel12Dec.root");

  // Pt bin sizes
  int Nptbin=1;
  double pt_bound[100] = {0};
  
  if(iSpec == 1) { 
    Nptbin = 3;
    pt_bound[0] = 0.0; pt_bound[1] = 6.0;
    pt_bound[2] = 12.0; pt_bound[3] = 100.0;
    
    if(isData == 2) {
      Nptbin = 25;
      // pt_bound[100] = {0.0,100.0,12.0,100.0};
      pt_bound[0] = 0;
      pt_bound[1] = 2;
      pt_bound[2] = 4;
      pt_bound[3] = 6;
      pt_bound[4] = 8;
      pt_bound[5] = 10;
      pt_bound[6] = 12;
      pt_bound[7] = 14;
      pt_bound[8] = 16;
      pt_bound[9] = 18;
      pt_bound[10] = 20;
      pt_bound[11] = 22;
      pt_bound[12] = 24;
      pt_bound[13] = 26;
      pt_bound[14] = 28;
      pt_bound[15] = 30;
      pt_bound[16] = 32;
      pt_bound[17] = 34;
      pt_bound[18] = 36;
      pt_bound[19] = 38;
      pt_bound[20] = 40;
      pt_bound[21] = 42;
      pt_bound[22] = 44;
      pt_bound[23] = 46;
      pt_bound[24] = 48;
      pt_bound[25] = 50;
    }
  }
  
  // Y bin sizes
  if(iSpec == 2) {
    Nptbin = 10;
    // pt_bound[100] = {-2.4,-1.0,-0.5,0.5,1.0,2.4}; 
    // pt_bound[100] = {-2.4,-1.0,-0.5,0.5,1.0,2.4}; 
    // pt_bound[100] = {-2.4,-2.1,-1.6,-1.1,-0.6,0,0.6,1.1,1.6,2.1,2.4}; 
    pt_bound[0] = -2.4; 
    pt_bound[1] = -2.1; 
    pt_bound[2] = -1.6; 
    pt_bound[3] = -1.1; 
    pt_bound[4] = -0.6; 
    pt_bound[5] =  0.0; 
    pt_bound[6] = 0.6; 
    pt_bound[7] = 1.1; 
    pt_bound[8] = 1.6; 
    pt_bound[9] = 2.1; 
    pt_bound[10] = 2.4; 

  }
  
  if(iSpec == 3) {
    if(isData == 2) { 
      Nptbin = 9;
      pt_bound[0] = 0.0;
      pt_bound[1] = 4.0;
      pt_bound[2] = 8.0;
      pt_bound[3] = 12.0;
      pt_bound[4] = 16.0;
      pt_bound[5] = 20.0;
      pt_bound[6] = 24.0;
      pt_bound[7] = 28.0;
      pt_bound[8] = 32.0;
      pt_bound[9] = 40.0;
    }
  }
  
  double PT[100], DelPT[100], mom_err[100];
  for (Int_t ih = 0; ih < Nptbin; ih++) {
    PT[ih] = (pt_bound[ih] + pt_bound[ih+1])/2.0;
    DelPT[ih] = pt_bound[ih+1] - pt_bound[ih];
    mom_err[ih] = DelPT[ih]/2.0;
  }
  
  float gen_pt[100], gen_ptError[100];
  float gen_ptS[100], gen_ptErrorS[100];
  
  if(isData==2){

    TH2D *genMass_1, *genMassS_1;

    if (iSpec == 1 &&  Weight==1 ) genMass_1 = (TH2D*)fil1->Get("diMuonsGenInvMassVsPtW");
    if (iSpec == 2 &&  Weight==1) genMass_1 = (TH2D*)fil1->Get("diMuonsGenInvMassVsYW");
    if (iSpec == 3 &&  Weight==1) genMass_1 = (TH2D*)fil1->Get("diMuonsGenInvMassVsCenW");
    
    if (iSpec == 1 &&  Weight==1) genMassS_1 = (TH2D*)fil2->Get("diMuonsGenInvMassVsPtW");
    if (iSpec == 2 &&  Weight==1) genMassS_1 = (TH2D*)fil2->Get("diMuonsGenInvMassVsYW");
    if (iSpec == 3 &&  Weight==1) genMassS_1 = (TH2D*)fil2->Get("diMuonsGenInvMassVsCenW");
    
    if (iSpec == 1 &&  Weight==0) genMass_1 = (TH2D*)fil1->Get("diMuonsGenInvMassVsPt");
    if (iSpec == 2 &&  Weight==0) genMass_1 = (TH2D*)fil1->Get("diMuonsGenInvMassVsY");
    if (iSpec == 3 &&  Weight==0) genMass_1 = (TH2D*)fil1->Get("diMuonsGenInvMassVsCen");


    if (iSpec == 1 &&  Weight==0) genMassS_1 = (TH2D*)fil2->Get("diMuonsGenInvMassVsPt");
    if (iSpec == 2 &&  Weight==0) genMassS_1 = (TH2D*)fil2->Get("diMuonsGenInvMassVsY");
    if (iSpec == 3 &&  Weight==0) genMassS_1 = (TH2D*)fil2->Get("diMuonsGenInvMassVsCen");

    TH1D *ptaxis = (TH1D*)genMass_1->ProjectionY("ptaxis");
    
    for (Int_t ih = 0; ih < Nptbin; ih++) {
      cout<<pt_bound[ih]<<"  "<<pt_bound[ih+1]<<endl;
      int pt_bin1 = ptaxis->FindBin(pt_bound[ih]+0.0000001);
      int pt_bin2 = ptaxis->FindBin(pt_bound[ih+1]+0.0000001);
      
      cout<< pt_bin1<<"  "<< pt_bin2<<endl; 
      TH1D * genMassVsPt = (TH1D*)genMass_1->ProjectionX("genMassVsPt", pt_bin1, pt_bin2-1);
      TH1D * genMassVsPtS = (TH1D*)genMassS_1->ProjectionX("genMassVsPtS", pt_bin1, pt_bin2-1);
      
      //does not work with weight
      //gen_pt[ih] = genMassVsPt->GetEntries();
      
      double genError,genErrorS;
      gen_pt[ih] = genMassVsPt->IntegralAndError(1,8000,genError);
      gen_ptError[ih]= genError;
      
      gen_ptS[ih] = genMassVsPtS->IntegralAndError(1,8000,genErrorS);
      gen_ptErrorS[ih]= genErrorS;
      
      cout<<" gen entries : "<< gen_pt[ih]<<endl;
      cout<<"genErro "<<genError<<"  "<< gen_ptError[ih]<<endl<<endl;
    }
  }
  
  // Efficiency
  float Eff_cat_1[100]; 
  float Eff_catS_1[100]; 
  
  float errEff_cat_1[100];
  float errEff_catS_1[100];
  
  float errEff_cat_S1[100], errEff_cat_S2[100];
  float errEff_catS_S1[100], errEff_catS_S2[100];
  
  char *Xname[100] = {" ", "p_{T}^{Dimuon} (GeV/c)", "rapidity", "centrality"};
  
  double yld_cat_1[100];
  double yld_catS_1[100];
  double cyld_cat_1[100];
  double cyld_catS_1[100];
  double eyld_cat_1[100];
  double eyld_catS_1[100];
  double ceyld_cat_1[100], ceyld_catS_1[100];

  char namePt_1[500];
  char namePt_1S[500];
  //char namePt_1B[500];
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
  //lcat_1->AddEntry(RBWPOL," CMS Preliminary", " ");
  //lcat_1->AddEntry(RBWPOL," PbPb #sqrt{s_{NN}} = 2.76 TeV ", " ");
  
  TLegend *legend_1[100];
  for(int i=0; i<100; i++) { 
    if(isFit) legend_1[i] = new TLegend(.62, .52, .91, 0.93 );
    if(!isFit) legend_1[i] = new TLegend(.62, .68, .91, 0.93 );
    legend_1[i]->SetBorderSize(0);
    legend_1[i]->SetFillStyle(0);
    legend_1[i]->SetFillColor(0);
    legend_1[i]->SetTextSize(0.032);
  }
  
  //for no cut
  //if(whis == 1 && iSpec == 1 ) TH2D *Z0Mass_1 = (TH2D*)fil1->Get("dimu");
  //if(whis == 2 && iSpec == 1) TH2D *Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPtBRL");
  //if(whis == 4 && iSpec == 1 ) {
    //TH2D *Z0Mass_1 = (TH2D*)fil1->Get("diMuonsPATInvMassVsPt");
    //TH2D *Z0Mass_1 = (TH2D*)fil1->Get("diMuonsPATSTAInvMassVsPt");
  //}



  TH2D *Z0Mass_1, *Z0Mass_1S;

  //with weight

  if(iSpec == 1 &&  Weight==1 ) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPtW");
  if(iSpec == 2 &&  Weight==1) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsYW");
  if(iSpec == 3 &&  Weight==1) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsCenW");


  //without weight
  if(iSpec == 1  &&  Weight==0) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsPt");
  if(iSpec == 2 &&  Weight==0) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsY");
  if(iSpec == 3 &&  Weight==0) Z0Mass_1 = (TH2D*)fil1->Get("diMuonsGlobalInvMassVsCen");
      
  //with weight fil2
  if(iSpec == 1  &&  Weight==1) Z0Mass_1S = (TH2D*)fil2->Get("diMuonsGlobalInvMassVsPtW");
  if(iSpec == 2 &&  Weight==1) Z0Mass_1S = (TH2D*)fil2->Get("diMuonsGlobalInvMassVsYW");
  if(iSpec == 3 &&  Weight==1) Z0Mass_1S = (TH2D*)fil2->Get("diMuonsGlobalInvMassVsCenW");

  //without weight fil2
  if(iSpec == 1 &&  Weight==0  ) Z0Mass_1S = (TH2D*)fil2->Get("diMuonsGlobalInvMassVsPt");
  if(iSpec == 2 &&  Weight==0  ) Z0Mass_1S = (TH2D*)fil2->Get("diMuonsGlobalInvMassVsY");
  if(iSpec == 3 &&  Weight==0  ) Z0Mass_1S = (TH2D*)fil2->Get("diMuonsGlobalInvMassVsCen");
  
  TH1D *service = (TH1D*)Z0Mass_1->ProjectionY("service");
  int pt_bin_bound[100];
  TH1D *dimuonsGlobalInvMassVsPt[100],  *dimuonsGlobalInvMassVsPtS[100];
  
  TCanvas *CanvPt_1 = new TCanvas("CanvPt_1"," Z0 Yield Vs. Pt ", 40,40,1000,700);
  if (Nptbin == 2)  CanvPt_1->Divide(2,1);
  if (Nptbin == 3 || Nptbin == 4)  CanvPt_1->Divide(2,2);
  if (Nptbin == 5 || Nptbin == 6)  CanvPt_1->Divide(3,2);
  if (Nptbin == 9 || Nptbin == 10)  CanvPt_1->Divide(5,2);
  cout << endl << Xname[iSpec] << "    Yield      Mass (GeV)    Width (GeV)    GauWidth    chi2/ndf " << endl << endl; 
  //ih loop
  for (Int_t ih = 0; ih < Nptbin; ih++) 
    {
      CanvPt_1->cd(ih+1);
      gPad->SetTickx();
      gPad->SetTicky();
      
      // Project 1 D 
      pt_bin_bound[ih] = Z0Mass_1->GetYaxis()->FindBin(pt_bound[ih]+0.0000001);
      pt_bin_bound[ih+1] = Z0Mass_1->GetYaxis()->FindBin(pt_bound[ih+1]-0.0000001);
      sprintf(namePt_1,"Z0_1_pt_%d",ih);
      sprintf(namePt_1S,"Z0_1S_pt_%d",ih);
      
      //printf(namePt_1,"Z0_1_pt_%d",ih);
      //cout<<endl<<endl;
      //continue;
      
      dimuonsGlobalInvMassVsPt[ih] = (TH1D*)Z0Mass_1->ProjectionX(namePt_1, pt_bin_bound[ih], pt_bin_bound[ih+1]-1+1, "e");
      dimuonsGlobalInvMassVsPtS[ih] = (TH1D*)Z0Mass_1S->ProjectionX(namePt_1S, pt_bin_bound[ih], pt_bin_bound[ih+1]-1+1,"e");
      if(iSpec == 1 || iSpec == 2) {sprintf(text," %s [%.1f, %.1f]", Xname[iSpec], service->GetBinLowEdge(pt_bin_bound[ih]), 
					    service->GetBinLowEdge(pt_bin_bound[ih+1])+service->GetBinWidth(pt_bin_bound[ih+1]));}
      if(iSpec == 3) {sprintf(text," %s [%.1f, %.1f] %s", Xname[iSpec], 2.5*service->GetBinLowEdge(pt_bin_bound[ih]), 
			      2.5*(service->GetBinLowEdge(pt_bin_bound[ih+1])+service->GetBinWidth(pt_bin_bound[ih+1])), "%");}
      
      dimuonsGlobalInvMassVsPt[ih]->Rebin(nrebin);
      dimuonsGlobalInvMassVsPtS[ih]->Rebin(nrebin);
      
      float m_low = 60.0;
      float m_high = 120.0;
      
      TAxis *axs   = dimuonsGlobalInvMassVsPt[ih]->GetXaxis();
      int binlow = axs->FindBin(m_low);
      int binhi  = axs->FindBin(m_high);
      //      Double_t bin_size = (1.0*dimuonsGlobalInvMassVsPt[ih]->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
      //    Float_t int_sig = 0.0;
      //for(Int_t bin = binlow; bin<=binhi;bin++) {
      //int_sig+ = dimuonsGlobalInvMassVsPt[ih]->GetBinContent(bin);
      //}   
      double recerror,recerrorS;
      //double yld;
      double yld_1 = dimuonsGlobalInvMassVsPt[ih]->IntegralAndError(binlow, binhi, recerror);
      double yldS_1 = dimuonsGlobalInvMassVsPtS[ih]->IntegralAndError(binlow, binhi, recerrorS); 
      eyld_cat_1[ih] =recerror;
      eyld_catS_1[ih] =recerrorS;
      cout<< "yld " << yld_1 <<"  eyld_cat_1[ih]  "<< eyld_cat_1[ih]<<" rec error "<<recerror<<endl;
      
      yld_cat_1[ih] = yld_1;
      yld_catS_1[ih] = yldS_1;
      
      if(isLog) gPad->SetLogy(1);
      TColor *pal = new TColor();
      Int_t kblue = pal->GetColor(9,0,200);
      //      Int_t korange  = pal->GetColor(101, 42,  0);
      
      dimuonsGlobalInvMassVsPt[ih]->SetMarkerStyle(21);
      dimuonsGlobalInvMassVsPt[ih]->SetMarkerColor(kblue);
      dimuonsGlobalInvMassVsPt[ih]->SetLineColor(kblue);
      dimuonsGlobalInvMassVsPt[ih]->GetXaxis()->SetTitle("Dimuon mass (GeV/c^{2})");
      dimuonsGlobalInvMassVsPt[ih]->GetYaxis()->SetTitle("Events/(2 GeV/c^{2})");
      dimuonsGlobalInvMassVsPt[ih]->GetXaxis()->SetRangeUser(mlow,mhigh);
      dimuonsGlobalInvMassVsPt[ih]->DrawCopy("EPL");
      // fil2
      dimuonsGlobalInvMassVsPtS[ih]->SetMarkerStyle(8);
      dimuonsGlobalInvMassVsPtS[ih]->SetMarkerColor(46);
      dimuonsGlobalInvMassVsPtS[ih]->SetLineColor(46);
      //****** dimuonsGlobalInvMassVsPtS[ih]->DrawCopy("EPsame");
      //RBWPOL->SetLineColor(kblue);
      //backfun_1->SetLineColor(46);
      //backfun_1->SetLineWidth(1);
      //if(isFit) backfun_1->Draw("same");
      lcat_1->Draw("same"); 
      legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih],"Global-Global", " ");
      legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih]," |y| < 2.4 ", "");  
      legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], text, "");
      legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih]," Opposite Charge ", "LP");
      legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPtS[ih]," Same Charge ", "LP");
      char label_1[512];
      //      char label_2[512], label_3[512], label_4[512];
      sprintf(label_1, "N=%1.2f #pm %1.2f ", yld_cat_1[ih], eyld_cat_1[ih]);
      //    sprintf(label_1, "N_{Z^{0}} = 27");
      legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], label_1, "");
    }//ih loop
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
  
  // Efficiency correction
  if(isData==2) 
    {
       ofstream fileout("correction.txt");
       cout << Xname[iSpec] << "   Eff_cat_1  " << endl;
       
       for (Int_t ih = 0; ih < Nptbin; ih++) {
      	//cout<<"gen_pt[ih];  "<<gen_pt[ih]<<endl;
	 Eff_cat_1[ih] = yld_cat_1[ih]/gen_pt[ih]; 
	 Eff_catS_1[ih] = yld_catS_1[ih]/gen_ptS[ih]; 
	 //eyld_cat_1[ih];
	 //gen_ptError[ih];
	 //cout<<endl<<endl<<endl;
	//cout<<"Eff_cat_1[ih] "<<Eff_cat_1[ih]<<endl;
	//cout<<"yld_cat_1[ih] "<< yld_cat_1[ih] <<endl;
	//cout<<"eyld_cat_1[ih] "<<eyld_cat_1[ih] <<endl;
	//cout<<"gen_pt[ih]    "<< gen_pt[ih] <<endl;
	//cout<<"gen_ptError[ih] "<< gen_ptError[ih]<<endl;
	 //Error for first graph
	 double errEff_cat_S1_1[100]={0},errEff_cat_S1_2[100]={0};
	 double errEff_cat_S2_1[100]={0},errEff_cat_S2_2[100]={0};
	 errEff_cat_S1_1[ih]= ( (Eff_cat_1[ih] * Eff_cat_1[ih]) /(gen_pt[ih] * gen_pt[ih]) );
	 errEff_cat_S1_2[ih]= (gen_ptError[ih] * gen_ptError[ih] ) - ( eyld_cat_1[ih] * eyld_cat_1[ih] );
	 errEff_cat_S1[ih]= (errEff_cat_S1_1[ih] * errEff_cat_S1_2[ih]);
	 //cout<<" errEff_cat_S1_1[ih] "<<	errEff_cat_S1_1[ih]<< " errEff_cat_S1_2[ih] "<<errEff_cat_S1_2[ih]<<endl;
	 errEff_cat_S2_1[ih]= ( (1 - Eff_cat_1[ih])* (1 - Eff_cat_1[ih]) ) / ( gen_pt[ih] * gen_pt[ih]);
	 errEff_cat_S2_2[ih]= (eyld_cat_1[ih] * eyld_cat_1[ih]);
	 errEff_cat_S2[ih]=errEff_cat_S2_1[ih]*errEff_cat_S2_2[ih];
	 //cout<<" errEff_cat_S2_1[ih] "<<	errEff_cat_S2_1[ih]<< " errEff_cat_S2_2[ih] "<<errEff_cat_S2_2[ih]<<endl;
	 //cout<<"errEff_cat_S1[ih]    "<<errEff_cat_S1[ih]<< " errEff_cat_S2[ih]   "<< errEff_cat_S2[ih]<<endl;	
	 errEff_cat_1[ih]=sqrt(errEff_cat_S1[ih] + errEff_cat_S2[ih]);
	 
	 //Error for second graph
	 double errEff_catS_S1_1[100]={0},errEff_catS_S1_2[100]={0};
	 double errEff_catS_S2_1[100]={0},errEff_catS_S2_2[100]={0};
	 errEff_catS_S1_1[ih]= ( (Eff_catS_1[ih] * Eff_catS_1[ih]) /(gen_ptS[ih] * gen_ptS[ih]) );
	 errEff_catS_S1_2[ih]= (gen_ptErrorS[ih] * gen_ptErrorS[ih] ) - (eyld_catS_1[ih] * eyld_catS_1[ih] );
	 errEff_catS_S1[ih]= (errEff_catS_S1_1[ih] * errEff_catS_S1_2[ih]);
	 errEff_catS_S2_1[ih]= ( (1 - Eff_catS_1[ih])* (1 - Eff_catS_1[ih]) ) / ( gen_ptS[ih] * gen_ptS[ih]);
	 errEff_catS_S2_2[ih]= (eyld_catS_1[ih] * eyld_catS_1[ih]);
	 errEff_catS_S2[ih]= errEff_catS_S2_1[ih]*errEff_catS_S2_2[ih];
	 errEff_catS_1[ih]=sqrt(errEff_catS_S1[ih] + errEff_catS_S2[ih]);
	 //Error for no weight
	 //errEff_cat_1[ih] =((Eff_cat_1[ih]*(1- Eff_cat_1[ih]))/gen_pt[ih]);
	 //Prashant error
	 //errEff_cat_1[ih] = eyld_cat_1[ih]/gen_pt[ih]; 
	 fileout << PT[ih] <<"   "<< Eff_cat_1[ih] << "   " << errEff_cat_1[ih] << endl; 
	 cout <<"    " << PT[ih] <<"    "<< Eff_cat_1[ih] << " +- " << errEff_cat_1[ih] << endl;
	 cyld_cat_1[ih] = Eff_cat_1[ih];
	 ceyld_cat_1[ih] = errEff_cat_1[ih];
	 cyld_catS_1[ih] = Eff_catS_1[ih];
	 ceyld_catS_1[ih] = errEff_catS_1[ih];
       }
    }
  
  TGraphErrors *Z0ptC_cat_1 = new TGraphErrors(Nptbin, PT, cyld_cat_1, mom_err, ceyld_cat_1);
  Z0ptC_cat_1->SetMarkerStyle(20);
  Z0ptC_cat_1->SetMarkerColor(2);
  Z0ptC_cat_1->GetXaxis()->SetTitle(Xname[iSpec]);
  Z0ptC_cat_1->GetYaxis()->SetTitle("Acc #times Eff");
  Z0ptC_cat_1->GetYaxis()->SetRangeUser(0,1.0);

  TGraphErrors *Z0ptC_catS_1 = new TGraphErrors(Nptbin, PT, cyld_catS_1, mom_err, ceyld_catS_1);
  Z0ptC_catS_1->SetMarkerStyle(8);
  Z0ptC_catS_1->SetMarkerColor(1);
  Z0ptC_catS_1->GetYaxis()->SetRangeUser(0,0.8);
  
  TLegend *legend_GP = new TLegend( 0.59,0.79,0.88,0.89);
  legend_GP->SetBorderSize(0);
  legend_GP->SetFillStyle(0);
  legend_GP->SetFillColor(0);
  legend_GP->SetTextSize(0.032);
  //legend_GP->AddEntry(Z0ptC_catS_1,"Pythia Gun in MB HI Data ", "");
  legend_GP->AddEntry(Z0ptC_catS_1,"Pythia Gun in MB Hydjet ", "");
  new TCanvas;
  Z0ptC_cat_1->SetMinimum(0.0);
  Z0ptC_cat_1->Draw("AP");
  //Z0ptC_catS_1->Draw("sameP");
  lcat_1->Draw("same"); 
  legend_GP->Draw("same");
  cout << endl << endl;
  Z0ptC_cat_1->Write();
}






