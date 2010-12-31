////////////////////////////////////////////////////////
// Fit Macro for Z0 in dimuon channel 
//
// Authors: CMS Heavy Ion Dilepton PiNG 
// Prashant Shukla and Vineet Kumar
/////////////////////////////////////////////////////////

#if !defined(__CINT__) || defined(__MAKECINT__)

#include "TROOT.h"
#include "Riostream.h"

#include "TCanvas.h"
#include "TColor.h"
#include "TF1.h"
#include "TFile.h"
//#include "TFitResult.h"
//#include "TFitResultPtr.h"
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

#include "FitFunctions.h"


void dileptonMassFit(const char* pInFileName="PromtRecoV2V3V3H_DiMuonPlot_TightSTACutsAll15Dec.root",//Z0_DataMixPt50_PatDiMuonPlots_NewCutAll14Dec.root",
		     const char* pHistNameOpCh="diMuonsGlobalInvMassVsPt",//diMuonsGlobalInvMassVsPtW",
		     const char* pHistNameSameCh="diMuonsGlobalSameChargeInvMassVsPt",
		     const char* pSpectra="pt",  // pt, y, centr
		     bool doMc=false, 
		     int nFitFunction = 3, 
		     int getYield = 1)
{
  gROOT->Macro("setStyle.C+");
  //gROOT->Macro("/Users/eusmartass/Software/utilities/setStyle.C+");
  char szBuf[256];
  ////////  definitions of Switches   ///////////
  //  nFitFunction  = 1  RBW + Pol2  
  //  nFitFunction  = 2  Gaus + Pol2 
  //  nFitFunction  = 3  RBWGaus + Pol2 

  //  getYield = 1  Bin counting 
  //  getYield = 2  Integral
  ////////////////////////////////////////////////////////////
  
  // make some choices
  float MassZ0         = 91.1876; 
  float WidthZ0        = 2.4952;
  float massFit_low    = 60;
  float massFit_high   = 120;  // Fit ranges
  float massDraw_low   = 30.0; //0.
  float massDraw_high  = 160.0; //200/
  int nrebin           = 80; 
  bool isLog           = 0; 
  bool isFit           = 1; // draw ranges
  
  float massCount_low  = 60.0; //78.0
  float massCount_high = 120.0; //102.0

  //___________________________________________________________________________________  
  // ------- Open input file 
  sprintf(szBuf,"%s",pInFileName);
  TString inFileName(szBuf);
  TFile *pfInFile = new TFile(inFileName); 

  // ------- get histograms: 
  sprintf(szBuf,"%s",pHistNameOpCh);
  TH2D *phDimuMass_1  = (TH2D*)pfInFile->Get(szBuf)->Clone("phDimuMass_1");
  
  sprintf(szBuf,"%s",pHistNameSameCh);
  TH2D *phDimuMass_1S = (TH2D*)pfInFile->Get(szBuf)->Clone("phDimuMass_1S");

  phDimuMass_1->SetDirectory(0);
  phDimuMass_1S->SetDirectory(0);
  //___________________________________________________________________________________  
  // bins definition: 
  const char* Xname[] = {" ", "p_{T}^{Dimuon} (GeV/c)", "rapidity", "centrality"};
  bool doPt   = false;
  bool doY    =  false;
  bool doCent = false;
  int GenRange, nBins;
  double binEdge[10];
  char* label;
  sprintf(szBuf,"%s",pSpectra);
  TString wichSpectra(szBuf);
  if ( wichSpectra.CompareTo("pt") == 0) 
    {
      doPt               = true;
      label              = (char*)Xname[1]; 
      GenRange           = 20;
      nBins              = 1;
      binEdge[0] = 0.0; binEdge[1]= 100.0;
      //    double binEdge[10] = {0.0, 10., 20., 100.0};
      if(doMc) 
	{
	  nBins              = 1;
	  binEdge[0] = 0.0; binEdge[1]= 50.0;
	  //	  nBins          = 7;
	  // binEdge[0] =  0.0;  binEdge[1] =  2.0;  binEdge[2] =  4.0;  binEdge[3] = 8.0;    
	  //binEdge[4] = 12.0;  binEdge[5] = 16.0;  binEdge[6] = 22.0;  binEdge[7] = 50.0;
	}
    } else{
    if ( wichSpectra.CompareTo("y") == 0) 
      {
	doY              = true;
	label            = (char*)Xname[2]; 
      	nBins            = 3;
	GenRange         = 4.8;
	binEdge[0] = -2.4; binEdge[1] = -0.8;
	binEdge[2] =  0.8; binEdge[3] =  2.4;
      } else{
      if ( wichSpectra.CompareTo("cent") == 0) 
	{
	  doCent           = true;
	  label            = (char*)Xname[3]; 
      	  nBins            = 4;
	  GenRange         = 40;
	  binEdge[0] = 0.; binEdge[1] =   4;
	  binEdge[2] = 8.; binEdge[3] =  16; binEdge[4] =  40;
	}else {
	cout<<"Don't know what you want to do!!!!"<<endl;
	return;
      }
    }
  }

  double PT[10], DelPT[10], mom_err[100];
  for (Int_t ih = 0; ih < nBins; ih++) 
    {
      PT[ih]      = (binEdge[ih] + binEdge[ih+1])/2.0;
      DelPT[ih]   = binEdge[ih+1] - binEdge[ih];
      mom_err[ih] = DelPT[ih]/2.0;
  }
  //___________________________________________________________________________________  

  double gen_pt[10];
  double egen_pt[10];
  
  TCanvas *pcPt_1 = new TCanvas("pcPt_1"," Z0 Yield Vs. Pt ", 40,40,600,600);

    if(doMc)
    {
      pcPt_1->Divide(nBins,2);
      
      //TH2D *genMass_1 = (TH2D*)pfInFile->Get("diMuonsGenInvMassVsPt");
      TH2D *genMass_1 = (TH2D*)pfInFile->Get("diMuonsGenInvMassVsPtW");
      TH1D *ptaxis    = (TH1D*)genMass_1->ProjectionY("ptaxis");
      
      for (Int_t ih = 0; ih < nBins; ih++) 
	{
	  pcPt_1->cd(ih+nBins+1);
	  
	  int bin1 = ptaxis->FindBin(binEdge[ih]+0.0000001);
	  int bin2 = ptaxis->FindBin(binEdge[ih+1]+0.0000001);
	  
	  TH1D * genMassVsPt = (TH1D*)genMass_1->ProjectionX("genMassVsPt", bin1, bin2-1);
	  genMassVsPt->Draw("EPL");
	  pcPt_1->Update();
	  
	  TAxis *axs        = genMassVsPt->GetXaxis();
	  int binlow        = axs->FindBin(massCount_low);
	  int binhi         = axs->FindBin(massCount_high);

	  double int_sig_gen;
	  double int_sig_gen_sqr;
	  for(Int_t bin = binlow; bin<=binhi;bin++) 
	    {
	      //    cout << "	  int_sig += dimuonsGlobalInvMassVsPt[ih]->GetBinContent(bin);"<<int_sigpow_gen <<"+="<< "bin" << bin << " content"<<genMassVsPt->GetBinContent(bin)<<endl;
	      int_sig_gen += genMassVsPt->GetBinContent(bin);
	      int_sig_gen_sqr += pow(genMassVsPt->GetBinContent(bin),2);
	    }   
	  
	  
	  gen_pt[ih] = int_sig_gen;//genMassVsPt->GetEntries();
	  cout<<" gen entries : "<< gen_pt[ih]<<endl; 
	  egen_pt[ih] =int_sig_gen_sqr;

	}
    }
    else {
      if (nBins == 2)  pcPt_1->Divide(2,1);
      if (nBins == 3 || nBins == 4)  pcPt_1->Divide(2,2);
      if (nBins == 5 || nBins == 6)  pcPt_1->Divide(3,2);
      
    }

    
  //___________________________________________________________________________________  
  // Fit Function 
  const char *name_fit[] = {"  ", "RBWPol1", "GausPol1", "RBWGausPol2"};
  int nParam[]           = {0,6,6,7};
  int nFitParam          = nParam[nFitFunction];
  TF1 *RBWPOL=0;
  if(nFitFunction == 1) RBWPOL = new TF1("RBWPOL", RBWPol2,     0, 200, nFitParam);
  if(nFitFunction == 2) RBWPOL = new TF1("RBWPOL", GausPol2,    0, 200, nFitParam);
  if(nFitFunction == 3) RBWPOL = new TF1("RBWPOL", RBWGausPol2, 0, 200, nFitParam);
  TF1 *EXP               = new TF1("EXP", Exp, 0, 200, 2);


  RBWPOL->SetLineWidth(1);
  RBWPOL->SetParameter(1, MassZ0);
  RBWPOL->SetParameter(2, WidthZ0);

  RBWPOL->SetParLimits(1, 0.9*MassZ0, 1.1*MassZ0);
  RBWPOL->SetParLimits(2, 0.1*WidthZ0, 5.0*WidthZ0);
  
  if(nFitFunction  == 1 || nFitFunction  == 2) RBWPOL->FixParameter(5, 0);
  if(nFitFunction  == 3 || nFitFunction  == 4) 
    {
      RBWPOL->SetParameter(3, WidthZ0);
      RBWPOL->SetParLimits(3, 0.1, 20);
      RBWPOL->FixParameter(2, WidthZ0);
      
      RBWPOL->FixParameter(4, 0);   // for no bkg
      RBWPOL->FixParameter(5, 0);   // for no bkg
      RBWPOL->FixParameter(6, 0);
    }


  //___________________________________________________________________________________  
  // Efficiency
  float Eff_cat_1[10], Eff_cat_2[10], Eff_cat_3[10]; 
  float errEff_cat_1[10], errEff_cat_2[10], errEff_cat_3[10]; 

  double yld_cat_1[10], yld_cat_2[10], yld_cat_3[10];
  double cyld_cat_1[10], cyld_cat_2[10], cyld_cat_3[10];
  double eyld_cat_1[10], eyld_cat_2[10], eyld_cat_3[10];
  double ceyld_cat_1[10], ceyld_cat_2[10], ceyld_cat_3[10];

  ///// Write the spectra 
  sprintf(szBuf,"fileSpecta%d.root", getYield);
  TFile *fileSpectra = new TFile(szBuf, "recreate");


  //___________________________________________________________________________________  
  // Drawing
  // Category _1 
  TLegend *pLegCategory = new TLegend(.005, .83, .42, .88);
  //  pLegCategory = new TLegend(.1, .82, .50, .93);
  pLegCategory->SetBorderSize(0);
  pLegCategory->SetFillStyle(0);
  pLegCategory->SetFillColor(0);
  pLegCategory->SetTextSize(0.03);
  //  pLegCategory->AddEntry(RBWPOL," CMS Preliminary", " ");
  pLegCategory->AddEntry(RBWPOL," PbPb at  #sqrt{s_{NN}} = 2.76 TeV ", " ");
  //  pLegCategory->AddEntry(RBWPOL," Global-Global ", "");
  //pLegCategory->AddEntry(RBWPOL," |y| < 2.4 ", "P");
  //pLegCategory->AddEntry(RBWPOL," Run# 150431-151027 ", "P");

  TLegend *legend_1[12];
  for(int i=0; i<12; i++) { 
    if(isFit) legend_1[i] = new TLegend(.48, .55, .82, 0.88);
    if(!isFit) legend_1[i] = new TLegend(.48, .66, .86, 0.82 );
    //    legend_1[i] = new TLegend(.68, .62, .91, 0.93 );
    legend_1[i]->SetBorderSize(0);
    legend_1[i]->SetFillStyle(0);
    legend_1[i]->SetFillColor(0);
    legend_1[i]->SetTextSize(0.028);
  }
  
  int bin_bound[100];
  TH1D *dimuonsGlobalInvMassVsPt[10];
  TH1D *dimuonsGlobalInvMassVsPtS[10];
  TH1D *service = (TH1D*)phDimuMass_1->ProjectionY("service");

  //  cout << endl << label << "    Yield      Mass (GeV)    Width (GeV)    GauWidth    chi2/ndf " << endl << endl; 
  for (Int_t ih = 0; ih < nBins; ih++) 
    {
      pcPt_1->cd(ih+1);
      gPad->SetTickx();
      gPad->SetTicky();

      // Project 1 D 
      bin_bound[ih]   = service->FindBin(binEdge[ih]+0.0000001);
      bin_bound[ih+1] = service->FindBin(binEdge[ih+1]+0.0000001);
    
      sprintf(szBuf,"Z0_1_pt_%d",ih);
      dimuonsGlobalInvMassVsPt[ih]  = (TH1D*)phDimuMass_1->ProjectionX(szBuf, bin_bound[ih], bin_bound[ih+1]-1+1, "e");
      sprintf(szBuf,"Z0_1S_pt_%d",ih);
      dimuonsGlobalInvMassVsPtS[ih] = (TH1D*)phDimuMass_1S->ProjectionX(szBuf, bin_bound[ih], bin_bound[ih+1]-1);
      cout << "reco entries" << dimuonsGlobalInvMassVsPt[ih]->GetEntries() <<endl;
      if(doPt || doY) 
	{
	  sprintf(szBuf," %s [%.1f, %.1f]",
		  label, 
		  service->GetBinLowEdge(bin_bound[ih]), 
		  service->GetBinLowEdge(bin_bound[ih+1]-1) + service->GetBinWidth(bin_bound[ih+1]));
	}
      
      if(doCent) 
	{
	  sprintf(szBuf," %s [%.1f, %.1f] %s", 
		  label, 
		  2.5*service->GetBinLowEdge(bin_bound[ih]), 
		  2.5*(service->GetBinLowEdge(bin_bound[ih+1]-1) + service->GetBinWidth(bin_bound[ih+1])), "%");
	}
      
      dimuonsGlobalInvMassVsPt[ih]->Rebin(nrebin);
      dimuonsGlobalInvMassVsPtS[ih]->Rebin(nrebin);
      
      // -------- Fit Function + Bkg Function
      double part[20];
      dimuonsGlobalInvMassVsPt[ih]->Fit("EXP","LEQ", "", 34, 60);
      EXP->GetParameters(part);
      if(nFitFunction  == 4)
	{
	  RBWPOL->FixParameter(4, part[0]);
	  RBWPOL->FixParameter(5, part[1]);
	}
      
      if(isFit)
      {
	//dimuonsGlobalInvMassVsPt[ih]->Fit("RBWPOL","LEQ", "", massFit_low, massFit_high);
	//TFitResultPtr r = 
	  dimuonsGlobalInvMassVsPt[ih]->Fit("RBWPOL","LEQS","", massFit_low, massFit_high);
	  //	if(r->IsValid()) r->Print();
	  //else cout<<"Fit not valid!!!\n"<<endl;
      }

      //------  get fit parameters
      double par[20];
      RBWPOL->GetParameters(par);
      
      float GGphDimuMass = RBWPOL->GetParameter(1);
      float GGZ0Width    = RBWPOL->GetParameter(2);
      float GauWidth     =0;
      if(nFitFunction  == 3 || nFitFunction  == 4) GauWidth = RBWPOL->GetParameter(3);
      
      double chisq      = RBWPOL->GetChisquare();
      int ndf           = RBWPOL->GetNDF();
      double chisqdf    =1000;
      if(ndf!=0) chisqdf=chisq/ndf;
      
      // +++ set backgroudn fit
      sprintf(szBuf,"pt_1B_%d",ih);
      TF1 *bkgFit_1 = new TF1(szBuf, Pol2, massFit_low, massFit_high, 3);
      // if(nFitFunction  == 4) bkgFit_1 = new TF1(namePt_1B, Exp, massFit_low, massFit_high, 2);
      
      bkgFit_1->SetParameters(&par[3]);
      if(nFitFunction  == 3 || nFitFunction  == 4) bkgFit_1->SetParameters(&par[4]);
      
      // ----------  Integrated Yield 
      //    float massCount_low =GGphDimuMass-(4.0*GGZ0Width);
      //    float massCount_high =GGphDimuMass+(4.0*GGZ0Width);
      
      TAxis *axs        = dimuonsGlobalInvMassVsPt[ih]->GetXaxis();
      int binlow        = axs->FindBin(massCount_low);
      int binhi         = axs->FindBin(massCount_high);
      Double_t bin_size = (1.0*dimuonsGlobalInvMassVsPt[ih]->GetNbinsX())/(axs->GetXmax() - axs->GetXmin());
      
      Float_t int_sig   = 0.0;
      Float_t int_sig_sqr   = 0.0;
      for(Int_t bin = binlow; bin<=binhi;bin++) 
	{
	  //	  cout << "	  int_sig += dimuonsGlobalInvMassVsPt[ih]->GetBinContent(bin);"<<int_sig <<"+="<< "bin" << bin << " content"<<dimuonsGlobalInvMassVsPt[ih]->GetBinContent(bin)<<endl;
	  int_sig += dimuonsGlobalInvMassVsPt[ih]->GetBinContent(bin);
	  int_sig_sqr += pow(dimuonsGlobalInvMassVsPt[ih]->GetBinContent(bin),2);
	}   
      
      if(getYield == 2)
	{
	  int_sig =  RBWPOL->Integral(massCount_low, massCount_high)*bin_size;
	  yld_cat_1[ih]   = int_sig - bin_size*bkgFit_1->Integral(massCount_low, massCount_high);
	  eyld_cat_1[ih] = TMath::Sqrt(int_sig + bin_size*bkgFit_1->Integral(massCount_low, massCount_high) );
	}
  
      else 
	{
	  yld_cat_1[ih]   = int_sig ;
	  eyld_cat_1[ih] = int_sig_sqr;
	}
      cout << "int_sig - bin_size*bkgFit_1->Integral(massCount_low, massCount_high);" << int_sig<< "  -"<< bin_size<<"*"<<bkgFit_1->Integral(massCount_low, massCount_high)<< " with low"<< massCount_low<<" high "<< massCount_high<<endl;
      //// Printing /////
      cout <<  PT[ih] << "    " << yld_cat_1[ih] << " +- " << eyld_cat_1[ih] <<"     " << GGphDimuMass << "    " << GGZ0Width  << "    " << GauWidth <<"   "<< chisq << "/" << ndf  << endl; 
      
      
      // -------------- Draw
    //    dimuonsGlobalInvMassVsPt[ih]->SetMinimum(-.05*dimuonsGlobalInvMassVsPt[ih]->GetMaximum());

    if(isLog) gPad->SetLogy(1);

    TColor *pal    = new TColor();
    Int_t kblue    = pal->GetColor(9,0,200);
    Int_t korange  = pal->GetColor(101, 42,  0);

    // +++ opposite charge
    dimuonsGlobalInvMassVsPt[ih]->SetMarkerStyle(21);
    dimuonsGlobalInvMassVsPt[ih]->SetMarkerColor(kblue);
    dimuonsGlobalInvMassVsPt[ih]->SetLineColor(kblue);
    dimuonsGlobalInvMassVsPt[ih]->SetMarkerSize(1.1);
    dimuonsGlobalInvMassVsPt[ih]->GetXaxis()->SetTitle("Dimuon mass (GeV/c^{2})");
    dimuonsGlobalInvMassVsPt[ih]->GetYaxis()->SetTitle("Events");

    dimuonsGlobalInvMassVsPt[ih]->GetXaxis()->SetRangeUser(massDraw_low,massDraw_high);
    //    dimuonsGlobalInvMassVsPt[ih]->Add(dimuonsGlobalInvMassVsPtS[ih], -1);

    pcPt_1->cd(ih+1);
    dimuonsGlobalInvMassVsPt[ih]->DrawCopy("EPLsame");
    //    dimuonsGlobalInvMassVsPt[ih]->Draw("B");

    // +++ same charge
    dimuonsGlobalInvMassVsPtS[ih]->SetMarkerStyle(8);
    dimuonsGlobalInvMassVsPtS[ih]->SetMarkerColor(46);
    dimuonsGlobalInvMassVsPtS[ih]->SetLineColor(46);

    dimuonsGlobalInvMassVsPtS[ih]->SetMarkerSize(1.1);
    dimuonsGlobalInvMassVsPtS[ih]->DrawCopy("EPsame");

    // background
    //    RBWPOL->SetLineColor(kblue);
    bkgFit_1->SetLineColor(46);
    bkgFit_1->SetLineWidth(1);
    if(isFit) bkgFit_1->Draw("same");

    // ++++ legend
    pLegCategory->Draw("same"); 

    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih]," Global-Global", " ");
    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih]," |y| < 2.4 ", "");  
    //    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], text, "");
    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih]," Opposite Charge ", "LP");
    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPtS[ih]," Same Charge ", "LP");
  
    sprintf(szBuf, "N=%1.2f #pm %1.2f ", yld_cat_1[ih], eyld_cat_1[ih]);
    legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], szBuf, "");
    //    sprintf(label_1, "N_{Z^{0}} = 27");

    sprintf(szBuf, "m=%1.2f #pm %1.2f GeV/c^{2}", RBWPOL->GetParameter(1), RBWPOL->GetParError(1));
    if(isFit) legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih],szBuf, "");
  
    sprintf(szBuf, "#sigma= 2.49 + %1.2f #pm %1.2f GeV/c^{2}", RBWPOL->GetParameter(2), RBWPOL->GetParError(2));
    if(nFitFunction ==3 || nFitFunction  == 4) 
      sprintf(szBuf, "#sigma=2.49 + %1.2f #pm %1.2f GeV/c^{2}", RBWPOL->GetParameter(3), RBWPOL->GetParError(3));
   
    if(isFit) legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], szBuf, "");

    sprintf(szBuf, "#chi^{2}/ndf = %1.2f / %d", chisq, ndf);
    //    if(isFit) legend_1[ih]->AddEntry(dimuonsGlobalInvMassVsPt[ih], label_4, "");

    legend_1[ih]->Draw("same");

    pcPt_1->Update();    
    }

  cout << endl << endl;


  TGraphErrors *Z0pt_cat_1 = new TGraphErrors(nBins, PT, yld_cat_1, mom_err, eyld_cat_1);
  Z0pt_cat_1->SetMarkerStyle(20);
  Z0pt_cat_1->SetMarkerColor(2);
  Z0pt_cat_1->GetXaxis()->SetTitle(label);
  Z0pt_cat_1->GetYaxis()->SetTitle("counts");

  TCanvas *pc2 = new TCanvas("pc2","pc2");
  Z0pt_cat_1->SetMinimum(0.0);
  Z0pt_cat_1->SetName("Z0pt_cat_1");
  Z0pt_cat_1->Draw("AP");


  TGraphErrors *Z0ptC_cat_1_gen = new TGraphErrors(nBins, PT, gen_pt, mom_err, egen_pt);
  //  Z0ptC_cat_1_gen->SetMarkerStyle(23);
  //Z0ptC_cat_1_gen->SetMarkerColor(3);
  //Z0ptC_cat_1_gen->Draw("AP");


  pLegCategory->Draw("same"); 

  Z0pt_cat_1->Write();
  pLegCategory->Write();


  //    gPad->Print("Pt_Z0YieldCat_1.png");
  pcPt_1->Print("Pt_Z0YieldCat_1.png");
 

  cout << endl << endl;




  //////////////////////////////////////////////////////////////////////////////

  // Efficiency correction
  if(doMc) 
    {
      ofstream fileout("correction.txt");
      cout << label << "   Eff_cat_1  " << endl;
      
      for (Int_t ih = 0; ih < nBins; ih++) 
	{
	  Eff_cat_1[ih] = yld_cat_1[ih]/gen_pt[ih]; 
	  
	  errEff_cat_1[ih] = sqrt( (pow(Eff_cat_1[ih]/yld_cat_1[ih],2))*eyld_cat_1[ih]
				   +(pow((1-Eff_cat_1[ih]/yld_cat_1[ih]),2))*( yld_cat_1[ih]-gen_pt[ih]/ yld_cat_1[ih])); 
	  //	  errEff_cat_1[ih] = sqrt( (pow(Eff_cat_1[ih]/yld_cat_1[ih],2))*eyld_cat_1[ih]
	  //			   +(pow((1-Eff_cat_1[ih]/yld_cat_1[ih]),2))*event failing); 
	  
	  
	  //	fileout << PT[ih] <<"   "<< Eff_cat_1[ih] << "   " << Eff_cat_2[ih] <<"    " << Eff_cat_3[ih] << endl; 
	  //	cout <<"    " << PT[ih] <<"      "<< Eff_cat_1[ih] << "      " << Eff_cat_2[ih] << "      " << Eff_cat_3[ih] << endl; 
	  
	  fileout << PT[ih] <<"   "<< Eff_cat_1[ih] << "   " << errEff_cat_1[ih] << endl; 
	  cout <<"    " << PT[ih] <<"    "<< Eff_cat_1[ih] << " +- " << errEff_cat_1[ih] << endl;
	  cyld_cat_1[ih] = Eff_cat_1[ih];
	  ceyld_cat_1[ih] = errEff_cat_1[ih];
	  
	}
    }else{
  
    ifstream filein("correction.txt");
    cout <<  label << " yld_cat_1 "  << "  efficiency " <<  " corr. yld_cat_1  " << endl;
    for (Int_t ih = 0; ih < nBins; ih++) 
      {
	
	//      filein >> PT[ih] >>  Eff_cat_1[ih] >>  Eff_cat_2[ih]  >>  Eff_cat_3[ih] ; 
	//      cout << "       " << PT[ih] << "      "<< yld_cat_1[ih] << "       " << yld_cat_2[ih] <<"      " <<  yld_cat_3[ih] << endl;
	
	filein >> PT[ih] >>  Eff_cat_1[ih]  >> errEff_cat_1[ih]; 
	cout << "    " << PT[ih] << "     " << yld_cat_1[ih] << "     " << Eff_cat_1[ih] << "     " << yld_cat_1[ih]/Eff_cat_1[ih] << endl;
	cyld_cat_1[ih] = yld_cat_1[ih]/Eff_cat_1[ih];
	ceyld_cat_1[ih] = eyld_cat_1[ih]/Eff_cat_1[ih];
	
      }
  }

  TF1 *EXPA = new TF1("EXPA", Exp, 0, 100, 2);

  TGraphErrors *Z0ptC_cat_1 = new TGraphErrors(nBins, PT, cyld_cat_1, mom_err, ceyld_cat_1);
  Z0ptC_cat_1->SetMarkerStyle(20);
  Z0ptC_cat_1->SetMarkerColor(2);
  Z0ptC_cat_1->GetXaxis()->SetTitle(label);
  Z0ptC_cat_1->GetYaxis()->SetTitle("Acc x Eff");
  //  if(part == 2) Z0ptC_cat_1->Fit("EXPA","LEQ", "", 7, 16);


  new TCanvas;
  Z0ptC_cat_1->SetMinimum(0.0);
  Z0ptC_cat_1->SetMaximum(0.8);
  Z0ptC_cat_1->SetName("Z0ptC_cat_1");
  Z0ptC_cat_1->Draw("AP");


  pLegCategory->Draw("same"); 

  cout << endl << endl;

  Z0ptC_cat_1->Write();
    
}

