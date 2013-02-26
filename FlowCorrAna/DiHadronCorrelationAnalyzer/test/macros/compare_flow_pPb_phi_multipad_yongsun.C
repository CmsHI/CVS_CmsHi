#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/GetMultiJetCorrFunc.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/DrawTick.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/GetGraphFromFile.C"
#include "TStyle.h"
#include "TNtuple.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "/net/hisrv0001/home/davidlw/useful_macros/Histograms.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvas.C"
//#include "/net/hisrv0001/home/davidlw/useful_macros/makeMultiPanelCanvasNew.C"
#include <fstream>

static const int ptbinmax=4;
double ptmin[ptbinmax] = {0.1,1.0,2.0,3.0};
double ptmax[ptbinmax] = {1.0,2.0,3.0,4.0};
double ptbins[ptbinmax+1] = {0.1,1.0,2.0,3.0,4.0};
TString pttitle[ptbinmax]={"0.1 < p_{T} < 1.0 GeV/c","1.0 < p_{T} < 2.0 GeV/c","2.0 < p_{T} < 3.0 GeV/c","3.0 < p_{T} < 4.0 GeV/c"};

/*
static const int ptbinmax=9;
double ptmin[ptbinmax] = {0.1,1.0,2.0,3.0,4.0,5.0,6.0,8.0,1.0};
double ptmax[ptbinmax] = {1.0,2.0,3.0,4.0,5.0,6.0,8.0,12.0,3.0};
double ptbins[ptbinmax] = {0.1,1.0,2.0,3.0,4.0,5.0,6.0,8.0,12.0};
TString pttitle[ptbinmax]={"0.1 < p_{T} < 1.0 GeV/c","1.0 < p_{T} < 2.0 GeV/c","2.0 < p_{T} < 3.0 GeV/c","3.0 < p_{T} < 4.0 GeV/c","4.0 < p_{T} < 5.0 GeV/c","5.0 < p_{T} < 6.0 GeV/c","6.0 < p_{T} < 8.0 GeV/c","8.0 < p_{T} < 12.0 GeV/c","1.0 < p_{T} < 3.0 GeV/c"};
*/
/*
static const int ptbinmax=11;
double ptmin[ptbinmax] = {0.1,0.5,1.0,1.5,2.0,2.5,3.0,4.0,5.0,6.0,1.0};
double ptmax[ptbinmax] = {0.5,1.0,1.5,2.0,2.5,3.0,4.0,5.0,6.0,8.0,3.0};
double ptbins[ptbinmax] = {0.1,0.5,1.0,1.5,2.0,2.5,3.0,4.0,5.0,6.0,8.0};
TString pttitle[ptbinmax]={"0.1 < p_{T} < 0.5 GeV/c","0.5 < p_{T} < 1.0 GeV/c","1.0 < p_{T} < 1.5 GeV/c","1.5 < p_{T} < 2.0 GeV/c","2.0 < p_{T} < 2.5 GeV/c","2.5 < p_{T} < 3.0 GeV/c","3.0 < p_{T} < 4.0 GeV/c","4.0 < p_{T} < 5.0 GeV/c","5.0 < p_{T} < 6.0 GeV/c","6.0 < p_{T} < 8.0 GeV/c","1.0 < p_{T} < 3.0 GeV/c"};
*/

static const int nhistmax=4;
int nmin[nhistmax] = {2,35,90,110};
int nmax[nhistmax] = {35,90,110,1000};
double nhistbin[nhistmax+1] = {2,35,90,110,1000};
TString ntitle[nhistmax]={"N<35","35 #leq N<90","90 #leq N<110","N #geq 110"};
TString eventtype[nhistmax]={"PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV"};
TString tag[nhistmax]={"MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4"};

/*
static const int nhistmax=12;
int nmin[nhistmax] = {2,10,20,30,40,50,60,70,80,100,120,150};
int nmax[nhistmax] = {10,20,30,40,50,60,70,80,100,120,150,1000};
double nhistbin[nhistmax+1] = {2,10,20,30,40,50,60,70,80,100,120,150,1000};
TString ntitle[nhistmax]={"N<10","10 #leq N<20","20 #leq N<30","30 #leq N<40","40 #leq N<50","50 #leq N<60","60 #leq N<70","70 #leq N<80","80 #leq N<100","100 #leq N<120","120 #leq N<150","N #geq 150"};
TString eventtype[nhistmax]={"PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV","PAData_Minbias_5TeV"};
TString tag[nhistmax]={"MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4","MB_INCLEFF1v4"};
*/

void drawPatch(float x1, float y1, float x2, float y2, int color =0, int style=1001, char* ops = ""){
  TLegend *t1=new TLegend(x1,y1,x2,y2,NULL,ops);
  if ( color ==0) t1->SetFillColor(kWhite);
  else t1->SetFillColor(color);
  t1->SetBorderSize(0);
  t1->SetFillStyle(style);
  t1->Draw("");
}


double dphimin = 0;
double dphimax = PI/2;

void compare_flow_pPb_phi_multipad_new(double detamin, double detamax, bool IsSave=0)
{
  TH2D* h2D = new TH2D("h2D",";N;p_{T} (GeV/c)",nhistmax,nhistbin,ptbinmax-1,ptbins);
  TH1D* h[nhistmax][ptbinmax];
  TH1D* h_zyam[nhistmax][ptbinmax];
  TF1* fitfunc[nhistmax][ptbinmax];

  TGraphErrors* gr_yield_pt_paper[nhistmax];
  TGraphErrors* gr_yield_mult_paper[ptbinmax];
  for(int ihist=0;ihist<nhistmax;ihist++)
  {
    gr_yield_pt_paper[ihist] = new TGraphErrors(ptbinmax);
    gr_yield_pt_paper[ihist]->SetName(Form("gr_yield_pt_%d",ihist));
  }
  for(int iptbin=0;iptbin<ptbinmax;iptbin++)
  {
    gr_yield_mult_paper[iptbin] = new TGraphErrors(nhistmax);
    gr_yield_mult_paper[iptbin]->SetName(Form("gr_yield_mult_%d",iptbin));
  }

  for(int ihist=0;ihist<nhistmax;ihist++)
  {
    for(int iptbin=0;iptbin<ptbinmax;iptbin++)
    {
      TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root",eventtype[ihist].Data(),eventtype[ihist].Data(),tag[ihist].Data(),nmin[ihist],nmax[ihist]);
      h[ihist][iptbin] = (TH1D*)Get1DCFdPhiv3(filename.Data(),iptbin,iptbin,detamin,detamax);      
      h[ihist][iptbin]->SetName(Form("corr_%d_%d",ihist,iptbin));
      fitfunc[ihist][iptbin]=GetFitFunc_ZYAM_pp(h[ihist][iptbin]);
      h_zyam[ihist][iptbin]=GetJetCorrFunc1D_ZYAM_pp(h[ihist][iptbin]);

      h[ihist][iptbin]->SetName(Form("corr_%d_%d",ihist,iptbin));
      fitfunc[ihist][iptbin]->SetName(Form("fitfunc_%d_%d",ihist,iptbin));
      h_zyam[ihist][iptbin]->SetName(Form("corr_zyam_%d_%d",ihist,iptbin));

      TH1D* hmult = (TH1D*)GetHist(filename,Form("multrawall"));
      TH1D* hpt = (TH1D*)GetHist(filename,Form("ptcorr_signal_trg_%d",iptbin));
      double zyamminimum=fitfunc[ihist][iptbin]->GetParameter(2);
      double yielderror=0;
//      double yield_mc = h_zyam_mc[ihist][iptbin]->IntegralAndError(h_zyam_mc[ihist][iptbin]->FindBin(-zyamminimum_mc),h_zyam_mc[ihist][iptbin]->FindBin(zyamminimum_mc),yielderror_mc,"width")/2.;//zyamminimumscale;
      double yield = h_zyam[ihist][iptbin]->IntegralAndError(h_zyam[ihist][iptbin]->FindBin(-1.2),h_zyam[ihist][iptbin]->FindBin(1.2),yielderror,"width")/2.;//zyamminimumscale;
      yielderror=yielderror/2.;//zyamminimumscale; // safety factor of 2
      if(iptbin==9) yielderror=yielderror*2;
      gr_yield_pt_paper[ihist]->SetPoint(iptbin,hpt->GetMean(),yield/(ptmax[iptbin]-ptmin[iptbin]));
      gr_yield_pt_paper[ihist]->SetPointError(iptbin,0,yielderror/(ptmax[iptbin]-ptmin[iptbin]));
      gr_yield_mult_paper[iptbin]->SetPoint(ihist,hmult->GetMean(),yield);
      gr_yield_mult_paper[iptbin]->SetPointError(ihist,0,yielderror);
      h2D->SetBinContent(ihist,iptbin,yield);
      h2D->SetBinError(ihist,iptbin,yielderror);
    }
  }

  TFile* fout = new TFile("results_INCLEFF1v4_4nbins.root","recreate");
  for(int ihist=0;ihist<nhistmax;ihist++) gr_yield_pt_paper[ihist]->Write();
  for(int iptbin=0;iptbin<ptbinmax;iptbin++) gr_yield_mult_paper[iptbin]->Write();
  for(int ihist=0;ihist<nhistmax;ihist++)
    for(int iptbin=0;iptbin<ptbinmax;iptbin++)
    {
      h[ihist][iptbin]->Write();
      fitfunc[ihist][iptbin]->Write();
      h_zyam[ihist][iptbin]->Write();
    }
  h2D->Write();
  fout->Close();
}

void ppdata_zyam()
{
  TH1D* gr_corr_pp[4][4];
  TH1D* gr_corr_pp_zyam[4][4];
  
  gr_corr_pp[0][0] = GetHistogramFromFile("./paper/Figure8-panel11.dat",1,24,1,1);
  gr_corr_pp[0][1] = GetHistogramFromFile("./paper/Figure8-panel12.dat",1,24,1,1);
  gr_corr_pp[0][2] = GetHistogramFromFile("./paper/Figure8-panel13.dat",1,24,1,1);
  gr_corr_pp[0][3] = GetHistogramFromFile("./paper/Figure8-panel14.dat",1,24,1,1);
  gr_corr_pp[1][0] = GetHistogramFromFile("./paper/Figure8-panel21.dat",1,24,1,1);
  gr_corr_pp[1][1] = GetHistogramFromFile("./paper/Figure8-panel22.dat",1,24,1,1);
  gr_corr_pp[1][2] = GetHistogramFromFile("./paper/Figure8-panel23.dat",1,24,1,1);
  gr_corr_pp[1][3] = GetHistogramFromFile("./paper/Figure8-panel24.dat",1,24,1,1);
  gr_corr_pp[2][0] = GetHistogramFromFile("./paper/Figure8-panel31.dat",1,24,1,1);
  gr_corr_pp[2][1] = GetHistogramFromFile("./paper/Figure8-panel32.dat",1,24,1,1);
  gr_corr_pp[2][2] = GetHistogramFromFile("./paper/Figure8-panel33.dat",1,24,1,1);
  gr_corr_pp[2][3] = GetHistogramFromFile("./paper/Figure8-panel34.dat",1,24,1,1);
  gr_corr_pp[3][0] = GetHistogramFromFile("./paper/Figure8-panel41.dat",1,24,1,1);
  gr_corr_pp[3][1] = GetHistogramFromFile("./paper/Figure8-panel42.dat",1,24,1,1);
  gr_corr_pp[3][2] = GetHistogramFromFile("./paper/Figure8-panel43.dat",1,24,1,1);
  gr_corr_pp[3][3] = GetHistogramFromFile("./paper/Figure8-panel44.dat",1,24,1,1);

  TFile* fout = new TFile("results_pp_zyam.root","recreate");
  for(int ihist=0;ihist<4;ihist++)
  {
    for(int iptbin=0;iptbin<4;iptbin++)
    {
      gr_corr_pp_zyam[ihist][iptbin]=GetJetCorrFunc1D_ZYAM_pp(gr_corr_pp[ihist][iptbin]);
      gr_corr_pp_zyam[ihist][iptbin]->SetName(Form("corr_zyam_pp_%d_%d",ihist,iptbin));
      gr_corr_pp_zyam[ihist][iptbin]->Write();
    }
  }
  fout->Close();
}

void corr1Ddphi_4by4_paper()
{
  TString pttitle[4]={"0.1 < p_{T} < 1.0 GeV/c","1.0 < p_{T} < 2.0 GeV/c","2.0 < p_{T} < 3.0 GeV/c","3.0 < p_{T} < 4.0 GeV/c"};
  TString ntitle[4]={"N_{trk}^{offline} < 35","35 #leq N_{trk}^{offline} < 90","90 #leq N_{trk}^{offline} < 110","N_{trk}^{offline} #geq 110"};

  TCanvas* c = new TCanvas("c","",875,840);
  makeMultiPanelCanvas(c,4,4,0.02,0.02,0.3,0.2,0.15);

  TFile* fout_pPb = new TFile("results_INCLEFF1v4_4nbins.root");
  TFile* fout_pp = new TFile("results_pp_zyam.root");
  TFile* fout_hijing = new TFile("results_INCLv4_4nbins_HIJINGGEN.root");
 
  TH2D* hpedestal = (TH2D*)fout_pPb->Get("pedestal");

  double ymin=0;
  double ymax=0;
  TH1D* h[4][4];
  TH1D* h_hijing[4][4];
  TH1D* h_hijing_hydro[4][4];
  TH1D* h_hijing_hydro_zyam[4][4];

  int hijingDrawOption=1;
  //  int hijingDrawOption=2;
  
  
  TH1D* h_pp[4][4];
  TLatex* xlatex[4];
  TLatex* ylatex[4];
  TLatex* platex[4][4];
  for(int ihist=0;ihist<4;ihist++) 
    for(int iptbin=0;iptbin<4;iptbin++)
      {
      c->cd(ihist*4+iptbin+1); 
      h[ihist][iptbin]=(TH1D*)fout_pPb->Get(Form("corr_zyam_%d_%d",ihist,iptbin));
      h[ihist][iptbin]->SetMarkerColor(kRed);
      h_pp[ihist][iptbin]=(TH1D*)fout_pp->Get(Form("corr_zyam_pp_%d_%d",ihist,iptbin));
      h_pp[ihist][iptbin]->SetMarkerStyle(24);
      h_pp[ihist][iptbin]->SetMarkerSize(h_pp[ihist][iptbin]->GetMarkerSize()*0.9);
      
      h_hijing[ihist][iptbin]=(TH1D*)fout_hijing->Get(Form("corr_zyam_%d_%d",ihist,iptbin));
      //      h_hijing[ihist][iptbin]->SetMarkerStyle(24);
      h_hijing[ihist][iptbin]->SetLineStyle(7);
      
      
      if(iptbin==0)
      {
        ymin=-0.015;
        ymax=h[ihist][iptbin]->GetMaximum()*1.6;
      }
      if(ihist==0) h[ihist][iptbin]->SetAxisRange(ymin,ymax*1.8,"Y");
      else if(ihist==3) h[ihist][iptbin]->SetAxisRange(ymin,ymax*1.2,"Y");
      else h[ihist][iptbin]->SetAxisRange(ymin,ymax,"Y");
      
      fixedFontHist1D(h[ihist][iptbin],4,6);
      h[ihist][iptbin]->SetAxisRange(-0.02,0.12,"Y");
      h[ihist][iptbin]->SetYTitle("#frac{1}{N_{trig}} #frac{dN^{pair}}{d#Delta#phi} - C_{ZYAM}");
   //   h[ihist][iptbin]->SetXTitle("#Delta#phi");// (radians)");
      h[ihist][iptbin]->Draw("PE");
//      if ( ((hijingDrawOption == 1)&&(iptbin==1) ) || (  (hijingDrawOption==2)&&(iptbin==1)&&(ihist==3) ) )
        h_hijing[ihist][iptbin]->SetLineWidth(2);
//	h_hijing[ihist][iptbin]->Draw("HIST C same");

      h[ihist][iptbin]->Draw("PE same");

      if (iptbin==1)
	{
	  if(ihist==0)
	    {
	      FlowFit10 = new TF1("FlowFit10","[6]+[0]*(1-(2*[1]*[1]*cos(x))+(2*[2]*[2]*cos(2*x))+(2*[3]*[3]*cos(3*x))+(2*[4]*[4]*cos(4*x))+(2*[5]*[5]*cos(5*x)))",0,3.14159);
	      FlowFit10->SetFillColor(19);
	      FlowFit10->SetFillStyle(0);
	      FlowFit10->SetLineWidth(3);
	      FlowFit10->SetNpx(130);
	      FlowFit10->SetParameter(0,0.14);
	      FlowFit10->SetParameter(1,0.00);
	      FlowFit10->SetParameter(2,0.066);
	      FlowFit10->SetParameter(3,0.037);
	      FlowFit10->SetParameter(4,0.00);
	      FlowFit10->SetParameter(5,0.00);
	      FlowFit10->SetParameter(6,-0.141);
	      FlowFit10->Draw("same");
              h_hijing_hydro[ihist][iptbin] = (TH1D*)h_hijing[ihist][iptbin]->Clone(Form("corr_hijing_hydro_%d_%d",ihist,iptbin));
              for(int nn=1;nn<=h_hijing_hydro[ihist][iptbin]->GetNbinsX();nn++) h_hijing_hydro[ihist][iptbin]->SetBinContent(nn,h_hijing_hydro[ihist][iptbin]->GetBinContent(nn)+FlowFit10->Eval(h_hijing_hydro[ihist][iptbin]->GetBinCenter(nn)));
              h_hijing_hydro_zyam[ihist][iptbin]=GetJetCorrFunc1D_ZYAM_pp(h_hijing_hydro[ihist][iptbin]);
           //   h_hijing_hydro_zyam[ihist][iptbin]->Draw("Lsame");
	    }
	  if(ihist==1)
	    {
	      FlowFit11 = new TF1("FlowFit11","[6]+[0]*(1-(2*[1]*[1]*cos(x))+(2*[2]*[2]*cos(2*x))+(2*[3]*[3]*cos(3*x))+(2*[4]*[4]*cos(4*x))+(2*[5]*[5]*cos(5*x)))",0,3.14159);
	      FlowFit11->SetFillColor(19);
	      FlowFit11->SetFillStyle(0);
	      FlowFit11->SetLineWidth(3);
	      FlowFit11->SetNpx(130);
	      FlowFit11->SetParameter(0,0.51);
	      FlowFit11->SetParameter(1,0.00);
	      FlowFit11->SetParameter(2,0.066);
	      FlowFit11->SetParameter(3,0.037);
	      FlowFit11->SetParameter(4,0.00);
	      FlowFit11->SetParameter(5,0.00);
	      FlowFit11->SetParameter(6,-0.507);
	      FlowFit11->Draw("same");
              h_hijing_hydro[ihist][iptbin] = (TH1D*)h_hijing[ihist][iptbin]->Clone(Form("corr_hijing_hydro_%d_%d",ihist,iptbin));
              for(int nn=1;nn<=h_hijing_hydro[ihist][iptbin]->GetNbinsX();nn++) h_hijing_hydro[ihist][iptbin]->SetBinContent(nn,h_hijing_hydro[ihist][iptbin]->GetBinContent(nn)+FlowFit11->Eval(h_hijing_hydro[ihist][iptbin]->GetBinCenter(nn)));
              h_hijing_hydro_zyam[ihist][iptbin]=GetJetCorrFunc1D_ZYAM_pp(h_hijing_hydro[ihist][iptbin]);
           //   h_hijing_hydro_zyam[ihist][iptbin]->Draw("Lsame");
	    }
	  if(ihist==2)
	    {
	      FlowFit12 = new TF1("FlowFit12","[6]+[0]*(1-(2*[1]*[1]*cos(x))+(2*[2]*[2]*cos(2*x))+(2*[3]*[3]*cos(3*x))+(2*[4]*[4]*cos(4*x))+(2*[5]*[5]*cos(5*x)))",0,3.14159);
	      FlowFit12->SetFillColor(19);
	      FlowFit12->SetFillStyle(0);
	      FlowFit12->SetLineWidth(2);
	      FlowFit12->SetNpx(130);
	      FlowFit12->SetParameter(0,0.98);
	      FlowFit12->SetParameter(1,0.00);
	      FlowFit12->SetParameter(2,0.066);
	      FlowFit12->SetParameter(3,0.037);
	      FlowFit12->SetParameter(4,0.00);
	      FlowFit12->SetParameter(5,0.00);
	      FlowFit12->SetParameter(6,-0.973);
	      FlowFit12->Draw("same");
              h_hijing_hydro[ihist][iptbin] = (TH1D*)h_hijing[ihist][iptbin]->Clone(Form("corr_hijing_hydro_%d_%d",ihist,iptbin));
              for(int nn=1;nn<=h_hijing_hydro[ihist][iptbin]->GetNbinsX();nn++) h_hijing_hydro[ihist][iptbin]->SetBinContent(nn,h_hijing_hydro[ihist][iptbin]->GetBinContent(nn)+FlowFit12->Eval(h_hijing_hydro[ihist][iptbin]->GetBinCenter(nn)));
              h_hijing_hydro_zyam[ihist][iptbin]=GetJetCorrFunc1D_ZYAM_pp(h_hijing_hydro[ihist][iptbin]);
           //   h_hijing_hydro_zyam[ihist][iptbin]->Draw("Lsame");
	    }
	  if(ihist==3)
	    {
	      FlowFit = new TF1("FlowFit","[6]+[0]*(1-(2*[1]*[1]*cos(x))+(2*[2]*[2]*cos(2*x))+(2*[3]*[3]*cos(3*x))+(2*[4]*[4]*cos(4*x))+(2*[5]*[5]*cos(5*x)))",0,3.14159);
	      FlowFit->SetFillColor(19);
	      FlowFit->SetFillStyle(0);
	      FlowFit->SetLineWidth(2);
	      FlowFit->SetNpx(130);
	      FlowFit->SetParameter(0,1.348);
	      FlowFit->SetParameter(1,0.00);
	      FlowFit->SetParameter(2,0.066);
	      FlowFit->SetParameter(3,0.037);
	      FlowFit->SetParameter(4,0.00);
	      FlowFit->SetParameter(5,0.00);
	      FlowFit->SetParameter(6,-1.336);
	      FlowFit->Draw("same");
              h_hijing_hydro[ihist][iptbin] = (TH1D*)h_hijing[ihist][iptbin]->Clone(Form("corr_hijing_hydro_%d_%d",ihist,iptbin));
              for(int nn=1;nn<=h_hijing_hydro[ihist][iptbin]->GetNbinsX();nn++) h_hijing_hydro[ihist][iptbin]->SetBinContent(nn,h_hijing_hydro[ihist][iptbin]->GetBinContent(nn)+FlowFit->Eval(h_hijing_hydro[ihist][iptbin]->GetBinCenter(nn)));
              h_hijing_hydro_zyam[ihist][iptbin]=GetJetCorrFunc1D_ZYAM_pp(h_hijing_hydro[ihist][iptbin]);
          //    h_hijing_hydro_zyam[ihist][iptbin]->Draw("Lsame");
	      if  (hijingDrawOption == 2) {
		TLegend* legend15 = new TLegend(0.04199059,0.5729892,0.7325473,0.8177423,NULL,"brNDC");
 
		legend15->SetTextFont(42);
		legend15->SetFillColor(0);
		legend15->AddEntry(h_hijing[0][0],"HIJING","l");
		legend15->Draw("SAME");
	      }
	    }
	}
      
      HistogramScaleShift(h_pp[ihist][iptbin],(2*PI)*4.8,0);      
      h_pp[ihist][iptbin]->Draw("PESAME");

      if(ihist==0)
      {
        xlatex[iptbin] = new TLatex();
        xlatex[iptbin]->SetNDC();
        if(iptbin==0) xlatex[iptbin]->SetTextSize(xlatex[iptbin]->GetTextSize()*0.8);
        else xlatex[iptbin]->SetTextSize(xlatex[iptbin]->GetTextSize()*0.8);
        c->cd(ihist*4+iptbin+1);
        if(iptbin==0) xlatex[iptbin]->DrawLatex(0.35,0.91,pttitle[iptbin]);
        else xlatex[iptbin]->DrawLatex(0.07,0.91,pttitle[iptbin]);
      }

      if(iptbin==0)
      {
        ylatex[ihist] = new TLatex();
        ylatex[ihist]->SetNDC();
        if(ihist==0) ylatex[ihist]->SetTextSize(ylatex[ihist]->GetTextSize()*0.8);
        else ylatex[ihist]->SetTextSize(ylatex[ihist]->GetTextSize()*0.8);
        c->cd(ihist*4+iptbin+1);
        if ( ihist ==0) 
	  ylatex[ihist]->DrawLatex(0.35,0.48,ntitle[ihist]);
	else if ( ihist !=3) 
	  ylatex[ihist]->DrawLatex(0.35,0.63,ntitle[ihist]);
	else 
	  ylatex[ihist]->DrawLatex(0.35,0.68,ntitle[ihist]);

      }
    
      platex[ihist][iptbin] = new TLatex();
      platex[ihist][iptbin]->SetTextSize(0.8*platex[ihist][iptbin]->GetTextSize());
      platex[ihist][iptbin]->SetNDC();
      float Xzyam = 0.4 ;
      float Yzyam = 0.85 ;
      if  ( iptbin == 0 )  Xzyam = Xzyam + 0.20;
      if  ( ihist == 0 )  Yzyam = Yzyam - 0.15;
      
      platex[ihist][iptbin]->DrawLatex(Xzyam,Yzyam,Form("C_{ZYAM} = %.3f",hpedestal->GetBinContent(ihist+1,iptbin+1)));
      
      if ( ( iptbin == 1 ) && (ihist==0) ) {
	TLegend* legend11 = new TLegend(0.04738557,0.3810441,0.9645312,0.6309298,NULL,"brNDC");
    	if (hijingDrawOption==2 )
	  legend11 = new TLegend(0.04738557,0.2860441,0.9645312,0.6359298,NULL,"brNDC");

 
	legend11->SetTextFont(42);
	legend11->SetFillColor(0);
	legend11->AddEntry(h[0][0],"pPb  #sqrt{s_{NN}} = 5.02 TeV","p");
	legend11->AddEntry(h_pp[0][0],"pp  #sqrt{s} = 7 TeV","p");
	legend11->Draw("SAME");
	      
      }
      if ( ( iptbin == 1 ) && (ihist==1) ) {
	TLegend* legend11 = new TLegend(0.04738557,0.3860441,0.9645312,0.6359298,NULL,"brNDC");
    	if (hijingDrawOption==2 )
	  legend11 = new TLegend(0.04738557,0.2860441,0.9645312,0.6359298,NULL,"brNDC");

 
	legend11->SetTextFont(42);
	legend11->SetFillColor(0);
	FlowLegend = new TF1("FlowLegend","[6]+[0]*(1-(2*[1]*[1]*cos(x))+(2*[2]*[2]*cos(2*x))+(2*[3]*[3]*cos(3*x))+(2*[4]*[4]*cos(4*x))+(2*[5]*[5]*cos(5*x)))",0,3.14159);
	FlowLegend->SetFillColor(19);
	FlowLegend->SetFillStyle(0);
	FlowLegend->SetLineWidth(3);
	FlowLegend->SetNpx(130);
	legend11->AddEntry(FlowLegend,"v_{2}=0.066, v_{3}=0.037","l");
	if  ((hijingDrawOption == 1)&&(iptbin==1) )  
	  legend11->AddEntry(h_hijing[0][0],"HIJING pPb","l");
	legend11->Draw("SAME");
	      
      }
      if   ((hijingDrawOption == 1)&&(iptbin==1) )  {
	//h_hijing[ihist][iptbin]->Draw("HIST C same");
	h[ihist][iptbin]->Draw("PE same");
        h_pp[ihist][iptbin]->Draw("PESAME");
      }
      
      if ( ( iptbin == 0 ) && (ihist==0) ) {
	TLatex* cmsPre = new TLatex();
	cmsPre->SetNDC();
	cmsPre->SetTextSize(cmsPre->GetTextSize()*0.8);
	//	cmsPre->DrawLatex(0.35,0.9,"CMS");
      }
      if (iptbin == 0) {
	if ( ihist==0) {
	  drawPatch(0.1678404,0.0900449,0.2679661,0.2062086,0,1001,"ndc");
	}
	if ( ihist==1) {
	  drawPatch(0.1678404,0.1016449,0.2679661,0.2162086,0,1001,"ndc");
	}
	if ( ihist==2) {
	  drawPatch(0.1678404,0.1016449,0.2679661,0.1962086,0,1001,"ndc");
	}
	if ( ihist==3) {
	  drawPatch(0.1678404,0.2516449,0.2679661,0.4062086,0,1001,"ndc");
	}
	
      }
      
      
    }  
  
    c->cd(1);
    TLatex* cms = new TLatex();
    cms->SetNDC();
    cms->DrawLatex(0.35,0.75,"CMS");
  
    SaveCanvas(c,"pPb/corr","corr1Ddphi_4by4_paper_nohijing");


    for(int ihist=0;ihist<4;ihist++) {
      for(int iptbin=0;iptbin<4;iptbin++)
	{
	  cout << endl<<endl<<endl<<endl;
	  cout << pttitle[iptbin] << ",   "<< ntitle[ihist] <<endl;
	  cout << "C_{ZYAM} = " <<hpedestal->GetBinContent(ihist+1,iptbin+1) << endl;
	  cout << " pPb " << endl;
	  for ( int i=1 ; i <=h[ihist][iptbin]->GetNbinsX() ; i++) {
	    if ( (h[ihist][iptbin]->GetBinCenter(i) > -0.01) && ( h[ihist][iptbin]->GetBinCenter(i) < 3.2) )
	      cout << fixed << setprecision(4) << h[ihist][iptbin]->GetBinCenter(i) << " " << fixed << setprecision(4) << h[ihist][iptbin]->GetBinContent(i) << " " << fixed << setprecision(4) << h[ihist][iptbin]->GetBinError(i) << endl;
	  }
	  cout << " pp " << endl;
	  for ( int i=1 ; i <=h_pp[ihist][iptbin]->GetNbinsX() ; i++) {
	    if ( (h_pp[ihist][iptbin]->GetBinCenter(i) > -0.01) &&( h_pp[ihist][iptbin]->GetBinCenter(i) < 3.1415 ) )
	      cout << fixed << setprecision(4)  << h_pp[ihist][iptbin]->GetBinCenter(i) << " " << fixed << setprecision(4) << h_pp[ihist][iptbin]->GetBinContent(i) << " " << fixed << setprecision(4) << h_pp[ihist][iptbin]->GetBinError(i) << endl;
	  }
	}
    }
}



void corr1Ddphi_4by4_paper_preliminary()
{
  TString pttitle[4]={"0.1 < p_{T} < 1.0 GeV/c","1.0 < p_{T} < 2.0 GeV/c","2.0 < p_{T} < 3.0 GeV/c","3.0 < p_{T} < 4.0 GeV/c"};
  TString ntitle[4]={"N_{trk}^{offline} < 35","35 #leq N_{trk}^{offline} < 90","90 #leq N_{trk}^{offline} < 110","N_{trk}^{offline} #geq 110"};

  TCanvas* c = new TCanvas("c","",875,840);
  makeMultiPanelCanvas(c,4,4,0.02,0.02,0.3,0.2,0.15);

  TFile* fout_pPb = new TFile("results_INCLEFF1v4_4nbins.root");
  TFile* fout_pp = new TFile("results_pp_zyam.root");
  TFile* fout_hijing = new TFile("results_INCLv4_4nbins_HIJINGGEN.root");
 
  TH2D* hpedestal = (TH2D*)fout_pPb->Get("pedestal");

  double ymin=0;
  double ymax=0;
  TH1D* h[4][4];
  TH1D* h_hijing[4][4];
  TH1D* h_hijing_hydro[4][4];
  TH1D* h_hijing_hydro_zyam[4][4];

  int hijingDrawOption=1;
  //  int hijingDrawOption=2;
  
  
  TH1D* h_pp[4][4];
  TLatex* xlatex[4];
  TLatex* ylatex[4];
  TLatex* platex[4][4];
  for(int ihist=0;ihist<4;ihist++) 
    for(int iptbin=0;iptbin<4;iptbin++)
      {
      c->cd(ihist*4+iptbin+1); 
      h[ihist][iptbin]=(TH1D*)fout_pPb->Get(Form("corr_zyam_%d_%d",ihist,iptbin));
      h[ihist][iptbin]->SetMarkerColor(kRed);
      h_pp[ihist][iptbin]=(TH1D*)fout_pp->Get(Form("corr_zyam_pp_%d_%d",ihist,iptbin));
      h_pp[ihist][iptbin]->SetMarkerStyle(24);
      h_pp[ihist][iptbin]->SetMarkerSize(h_pp[ihist][iptbin]->GetMarkerSize()*0.9);
      
      h_hijing[ihist][iptbin]=(TH1D*)fout_hijing->Get(Form("corr_zyam_%d_%d",ihist,iptbin));
      //      h_hijing[ihist][iptbin]->SetMarkerStyle(24);
      h_hijing[ihist][iptbin]->SetLineStyle(7);
      
      
      if(iptbin==0)
      {
        ymin=-0.015;
        ymax=h[ihist][iptbin]->GetMaximum()*1.6;
      }
      if(ihist==0) h[ihist][iptbin]->SetAxisRange(ymin,ymax*1.8,"Y");
      else if(ihist==3) h[ihist][iptbin]->SetAxisRange(ymin,ymax*1.2,"Y");
      else h[ihist][iptbin]->SetAxisRange(ymin,ymax,"Y");
      
      fixedFontHist1D(h[ihist][iptbin],4,6);
      h[ihist][iptbin]->SetAxisRange(-0.02,0.12,"Y");
      h[ihist][iptbin]->SetYTitle("#frac{1}{N_{trig}} #frac{dN^{pair}}{d#Delta#phi} - C_{ZYAM}");
   //   h[ihist][iptbin]->SetXTitle("#Delta#phi");// (radians)");
      h[ihist][iptbin]->Draw("PE");
//      if ( ((hijingDrawOption == 1)&&(iptbin==1) ) || (  (hijingDrawOption==2)&&(iptbin==1)&&(ihist==3) ) )
        h_hijing[ihist][iptbin]->SetLineWidth(2);
	h_hijing[ihist][iptbin]->Draw("HIST C same");

      h[ihist][iptbin]->Draw("PE same");

      if (iptbin==1)
	{
	  if(ihist==0)
	    {
	      FlowFit10 = new TF1("FlowFit10","[6]+[0]*(1-(2*[1]*[1]*cos(x))+(2*[2]*[2]*cos(2*x))+(2*[3]*[3]*cos(3*x))+(2*[4]*[4]*cos(4*x))+(2*[5]*[5]*cos(5*x)))",0,3.14159);
	      FlowFit10->SetFillColor(19);
	      FlowFit10->SetFillStyle(0);
	      FlowFit10->SetLineWidth(2);
	      FlowFit10->SetNpx(130);
	      FlowFit10->SetParameter(0,0.14);
	      FlowFit10->SetParameter(1,0.00);
	      FlowFit10->SetParameter(2,0.066);
	      FlowFit10->SetParameter(3,0.037);
	      FlowFit10->SetParameter(4,0.00);
	      FlowFit10->SetParameter(5,0.00);
	      FlowFit10->SetParameter(6,-0.141);
	      FlowFit10->Draw("same");
              h_hijing_hydro[ihist][iptbin] = (TH1D*)h_hijing[ihist][iptbin]->Clone(Form("corr_hijing_hydro_%d_%d",ihist,iptbin));
              for(int nn=1;nn<=h_hijing_hydro[ihist][iptbin]->GetNbinsX();nn++) h_hijing_hydro[ihist][iptbin]->SetBinContent(nn,h_hijing_hydro[ihist][iptbin]->GetBinContent(nn)+FlowFit10->Eval(h_hijing_hydro[ihist][iptbin]->GetBinCenter(nn)));
              h_hijing_hydro_zyam[ihist][iptbin]=GetJetCorrFunc1D_ZYAM_pp(h_hijing_hydro[ihist][iptbin]);
           //   h_hijing_hydro_zyam[ihist][iptbin]->Draw("Lsame");
	    }
	  if(ihist==1)
	    {
	      FlowFit11 = new TF1("FlowFit11","[6]+[0]*(1-(2*[1]*[1]*cos(x))+(2*[2]*[2]*cos(2*x))+(2*[3]*[3]*cos(3*x))+(2*[4]*[4]*cos(4*x))+(2*[5]*[5]*cos(5*x)))",0,3.14159);
	      FlowFit11->SetFillColor(19);
	      FlowFit11->SetFillStyle(0);
	      FlowFit11->SetLineWidth(2);
	      FlowFit11->SetNpx(130);
	      FlowFit11->SetParameter(0,0.51);
	      FlowFit11->SetParameter(1,0.00);
	      FlowFit11->SetParameter(2,0.066);
	      FlowFit11->SetParameter(3,0.037);
	      FlowFit11->SetParameter(4,0.00);
	      FlowFit11->SetParameter(5,0.00);
	      FlowFit11->SetParameter(6,-0.507);
	      FlowFit11->Draw("same");
              h_hijing_hydro[ihist][iptbin] = (TH1D*)h_hijing[ihist][iptbin]->Clone(Form("corr_hijing_hydro_%d_%d",ihist,iptbin));
              for(int nn=1;nn<=h_hijing_hydro[ihist][iptbin]->GetNbinsX();nn++) h_hijing_hydro[ihist][iptbin]->SetBinContent(nn,h_hijing_hydro[ihist][iptbin]->GetBinContent(nn)+FlowFit11->Eval(h_hijing_hydro[ihist][iptbin]->GetBinCenter(nn)));
              h_hijing_hydro_zyam[ihist][iptbin]=GetJetCorrFunc1D_ZYAM_pp(h_hijing_hydro[ihist][iptbin]);
           //   h_hijing_hydro_zyam[ihist][iptbin]->Draw("Lsame");
	    }
	  if(ihist==2)
	    {
	      FlowFit12 = new TF1("FlowFit12","[6]+[0]*(1-(2*[1]*[1]*cos(x))+(2*[2]*[2]*cos(2*x))+(2*[3]*[3]*cos(3*x))+(2*[4]*[4]*cos(4*x))+(2*[5]*[5]*cos(5*x)))",0,3.14159);
	      FlowFit12->SetFillColor(19);
	      FlowFit12->SetFillStyle(0);
	      FlowFit12->SetLineWidth(2);
	      FlowFit12->SetNpx(130);
	      FlowFit12->SetParameter(0,0.98);
	      FlowFit12->SetParameter(1,0.00);
	      FlowFit12->SetParameter(2,0.066);
	      FlowFit12->SetParameter(3,0.037);
	      FlowFit12->SetParameter(4,0.00);
	      FlowFit12->SetParameter(5,0.00);
	      FlowFit12->SetParameter(6,-0.973);
	      FlowFit12->Draw("same");
              h_hijing_hydro[ihist][iptbin] = (TH1D*)h_hijing[ihist][iptbin]->Clone(Form("corr_hijing_hydro_%d_%d",ihist,iptbin));
              for(int nn=1;nn<=h_hijing_hydro[ihist][iptbin]->GetNbinsX();nn++) h_hijing_hydro[ihist][iptbin]->SetBinContent(nn,h_hijing_hydro[ihist][iptbin]->GetBinContent(nn)+FlowFit12->Eval(h_hijing_hydro[ihist][iptbin]->GetBinCenter(nn)));
              h_hijing_hydro_zyam[ihist][iptbin]=GetJetCorrFunc1D_ZYAM_pp(h_hijing_hydro[ihist][iptbin]);
           //   h_hijing_hydro_zyam[ihist][iptbin]->Draw("Lsame");
	    }
	  if(ihist==3)
	    {
	      FlowFit = new TF1("FlowFit","[6]+[0]*(1-(2*[1]*[1]*cos(x))+(2*[2]*[2]*cos(2*x))+(2*[3]*[3]*cos(3*x))+(2*[4]*[4]*cos(4*x))+(2*[5]*[5]*cos(5*x)))",0,3.14159);
	      FlowFit->SetFillColor(19);
	      FlowFit->SetFillStyle(0);
	      FlowFit->SetLineWidth(2);
	      FlowFit->SetNpx(130);
	      FlowFit->SetParameter(0,1.348);
	      FlowFit->SetParameter(1,0.00);
	      FlowFit->SetParameter(2,0.066);
	      FlowFit->SetParameter(3,0.037);
	      FlowFit->SetParameter(4,0.00);
	      FlowFit->SetParameter(5,0.00);
	      FlowFit->SetParameter(6,-1.336);
	      FlowFit->Draw("same");
              h_hijing_hydro[ihist][iptbin] = (TH1D*)h_hijing[ihist][iptbin]->Clone(Form("corr_hijing_hydro_%d_%d",ihist,iptbin));
              for(int nn=1;nn<=h_hijing_hydro[ihist][iptbin]->GetNbinsX();nn++) h_hijing_hydro[ihist][iptbin]->SetBinContent(nn,h_hijing_hydro[ihist][iptbin]->GetBinContent(nn)+FlowFit->Eval(h_hijing_hydro[ihist][iptbin]->GetBinCenter(nn)));
              h_hijing_hydro_zyam[ihist][iptbin]=GetJetCorrFunc1D_ZYAM_pp(h_hijing_hydro[ihist][iptbin]);
          //    h_hijing_hydro_zyam[ihist][iptbin]->Draw("Lsame");
	      if  (hijingDrawOption == 2) {
		TLegend* legend15 = new TLegend(0.04199059,0.5729892,0.7325473,0.8177423,NULL,"brNDC");
 
		legend15->SetTextFont(42);
		legend15->SetFillColor(0);
		legend15->AddEntry(h_hijing[0][0],"HIJING pPb","l");
		legend15->Draw("SAME");
	      }
	    }
	}
      
      HistogramScaleShift(h_pp[ihist][iptbin],(2*PI)*4.8,0);      
      h_pp[ihist][iptbin]->Draw("PESAME");

      if(ihist==0)
      {
        xlatex[iptbin] = new TLatex();
        xlatex[iptbin]->SetNDC();
        if(iptbin==0) xlatex[iptbin]->SetTextSize(xlatex[iptbin]->GetTextSize()*0.8);
        else xlatex[iptbin]->SetTextSize(xlatex[iptbin]->GetTextSize()*0.8);
        c->cd(ihist*4+iptbin+1);
        if(iptbin==0) xlatex[iptbin]->DrawLatex(0.35,0.91,pttitle[iptbin]);
        else xlatex[iptbin]->DrawLatex(0.07,0.91,pttitle[iptbin]);
      }

      if(iptbin==0)
      {
        ylatex[ihist] = new TLatex();
        ylatex[ihist]->SetNDC();
        if(ihist==0) ylatex[ihist]->SetTextSize(ylatex[ihist]->GetTextSize()*0.8);
        else ylatex[ihist]->SetTextSize(ylatex[ihist]->GetTextSize()*0.8);
        c->cd(ihist*4+iptbin+1);
        if ( ihist ==0) 
	  ylatex[ihist]->DrawLatex(0.35,0.48,ntitle[ihist]);
	else if ( ihist !=3) 
	  ylatex[ihist]->DrawLatex(0.35,0.63,ntitle[ihist]);
	else 
	  ylatex[ihist]->DrawLatex(0.35,0.68,ntitle[ihist]);

      }
    
      platex[ihist][iptbin] = new TLatex();
      platex[ihist][iptbin]->SetTextSize(0.8*platex[ihist][iptbin]->GetTextSize());
      platex[ihist][iptbin]->SetNDC();
      float Xzyam = 0.4 ;
      float Yzyam = 0.85 ;
      if  ( iptbin == 0 )  Xzyam = Xzyam + 0.20;
      if  ( ihist == 0 )  Yzyam = Yzyam - 0.15;
      
      platex[ihist][iptbin]->DrawLatex(Xzyam,Yzyam,Form("C_{ZYAM}=%.3f",hpedestal->GetBinContent(ihist+1,iptbin+1)));
      
      if ( ( iptbin == 1 ) && (ihist==0) ) {
	TLegend* legend11 = new TLegend(0.04738557,0.3810441,0.9645312,0.6309298,NULL,"brNDC");
    	if (hijingDrawOption==2 )
	  legend11 = new TLegend(0.04738557,0.2860441,0.9645312,0.6359298,NULL,"brNDC");

 
		legend11->SetTextFont(42);
	legend11->SetFillColor(0);
	legend11->AddEntry(h[0][0],"pPb  #sqrt{s_{NN}} = 5.02 TeV","p");
	legend11->AddEntry(h_pp[0][0],"pp  #sqrt{s} = 7 TeV","p");
	legend11->Draw("SAME");
	      
      }
      if ( ( iptbin == 1 ) && (ihist==1) ) {
	TLegend* legend11 = new TLegend(0.04738557,0.3860441,0.9645312,0.6359298,NULL,"brNDC");
    	if (hijingDrawOption==2 )
	  legend11 = new TLegend(0.04738557,0.2860441,0.9645312,0.6359298,NULL,"brNDC");

 
	legend11->SetTextFont(42);
	legend11->SetFillColor(0);
	FlowLegend = new TF1("FlowLegend","[6]+[0]*(1-(2*[1]*[1]*cos(x))+(2*[2]*[2]*cos(2*x))+(2*[3]*[3]*cos(3*x))+(2*[4]*[4]*cos(4*x))+(2*[5]*[5]*cos(5*x)))",0,3.14159);
	FlowLegend->SetFillColor(19);
	FlowLegend->SetFillStyle(0);
	FlowLegend->SetLineWidth(3);
	FlowLegend->SetNpx(130);
	legend11->AddEntry(FlowLegend,"v_{2}=0.066, v_{3}=0.037","l");
	if  ((hijingDrawOption == 1)&&(iptbin==1) )  
	  legend11->AddEntry(h_hijing[0][0],"HIJING","l");
	legend11->Draw("SAME");
	      
      }
      if   ((hijingDrawOption == 1)&&(iptbin==1) )  {
	h_pp[ihist][iptbin]->Draw("PESAME");
	h_hijing[ihist][iptbin]->Draw("HIST C same");
	h[ihist][iptbin]->Draw("PE same");
      }
      
      if ( ( iptbin == 0 ) && (ihist==0) ) {
	TLatex* cmsPre = new TLatex();
	cmsPre->SetNDC();
	cmsPre->SetTextSize(cmsPre->GetTextSize()*0.8);
	//	cmsPre->DrawLatex(0.35,0.9,"CMS");
      }
      if (iptbin == 0) {
	if ( ihist==0) {
	  drawPatch(0.1678404,0.0900449,0.2679661,0.2062086,0,1001,"ndc");
	}
	if ( ihist==1) {
	  drawPatch(0.1678404,0.1016449,0.2679661,0.2162086,0,1001,"ndc");
	}
	if ( ihist==2) {
	  drawPatch(0.1678404,0.1016449,0.2679661,0.1962086,0,1001,"ndc");
	}
	if ( ihist==3) {
	  drawPatch(0.1678404,0.2516449,0.2679661,0.4062086,0,1001,"ndc");
	}
	
      }
      
      
    }  
  
    c->cd(4);
    TLatex* cms = new TLatex();
    cms->SetNDC();
    cms->DrawLatex(0.1,0.55,"CMS Preliminary");
  
    SaveCanvas(c,"pPb/corr","corr1Ddphi_4by4_paper_preliminary");
}

void yield_paper()
{
  // QCD-10-002
  TGraphErrors* gr_yield_pt_pp = GetGraphWithSymmYErrorsFromFile("./results/Figure9a.dat",1,24,1,1);
  TGraphErrors* gr_yield_mult_pp = GetGraphWithSymmYErrorsFromFile("./results/Figure9b.dat",1,24,1,1);
  GraphScaleShift(gr_yield_pt_pp,(2*PI)*4.8/4.*0.5,0.0);
  GraphScaleShift(gr_yield_mult_pp,(2*PI)*4.8/4.*0.5,0.0);

  gr_yield_pt_pp->SetMarkerStyle(24);
  gr_yield_mult_pp->SetMarkerStyle(24);

  // HIN-12-015
  TFile* fout_mult = new TFile("./results/results_INCLEFF1v4_12nbins_new.root");
  TGraphErrors* gr_yield_mult_pPb_old = (TGraphErrors*)fout_mult->Get("gr_yield_mult_1");
  TFile* fout_pt = new TFile("./results/results_INCLEFF1v5_4nbins.root");
  TGraphErrors* gr_yield_pt_pPb_old = (TGraphErrors*)fout_pt->Get("gr_yield_pt_3");

  gr_yield_pt_pPb_old->SetMarkerStyle(25);
  gr_yield_mult_pPb_old->SetMarkerStyle(25);
  GraphScaleShift(gr_yield_pt_pPb_old,0.5,0);
  GraphScaleShift(gr_yield_mult_pPb_old,0.5,0);

  // CGC prediction
  TGraphErrors* gr_yield_cgc_1 = GetGraphWithSymmYErrorsFromFile("./data/yield_cgc_1.txt",1,24,1,1);
  TGraphErrors* gr_yield_cgc_2 = GetGraphWithSymmYErrorsFromFile("./data/yield_cgc_2.txt",1,24,1,1);
  gr_yield_cgc_2->SetLineStyle(5);

  // HIN-13-002
  TFile* fout_mult_pPb_short = new TFile("./results/pPb_yieldvsn_pt1-2_all.root");
  TGraphErrors* gr_yield_mult_pPb_short = (TGraphErrors*)fout_mult_pPb_short->Get("gr_yield_short_mult");
  TFile* fout_mult_pPb_long = new TFile("./results/pPb_yieldvsn_pt1-2_all.root");
  TGraphErrors* gr_yield_mult_pPb_long = (TGraphErrors*)fout_mult_pPb_long->Get("gr_yield_long_mult");
/*
  TFile* fout_mult_PbPb_short = new TFile("./results/PbPb_yieldvsn_pt1-2_all.root");
  TGraphErrors* gr_yield_mult_PbPb_short = (TGraphErrors*)fout_mult_PbPb_short->Get("gr_yield_short_mult");
  TFile* fout_mult_PbPb_long = new TFile("./results/PbPb_yieldvsn_pt1-2_all.root");
  TGraphErrors* gr_yield_mult_PbPb_long = (TGraphErrors*)fout_mult_PbPb_long->Get("gr_yield_long_mult");
*/
  TFile* fout_mult_PbPb_short = new TFile("./results/pPb_yieldvsn_pt1-2_hfall.root");
  TGraphErrors* gr_yield_mult_PbPb_short = (TGraphErrors*)fout_mult_PbPb_short->Get("gr_yield_short_mult");
  TFile* fout_mult_PbPb_long = new TFile("./results/pPb_yieldvsn_pt1-2_hfall.root");
  TGraphErrors* gr_yield_mult_PbPb_long = (TGraphErrors*)fout_mult_PbPb_long->Get("gr_yield_long_mult");

  TFile* fout_pt_pPb_short = new TFile("./results/pPb_yieldvspt_N220260_all.root");
  TGraphErrors* gr_yield_pt_pPb_short = (TGraphErrors*)fout_pt_pPb_short->Get("gr_yield_short_pt");
  TFile* fout_pt_pPb_long = new TFile("./results/pPb_yieldvspt_N220260_all.root");
  TGraphErrors* gr_yield_pt_pPb_long = (TGraphErrors*)fout_pt_pPb_long->Get("gr_yield_long_pt");

  TFile* fout_pt_PbPb_short = new TFile("./results/PbPb_yieldvspt_N220260_all.root");
  TGraphErrors* gr_yield_pt_PbPb_short = (TGraphErrors*)fout_pt_PbPb_short->Get("gr_yield_short_pt");
  TFile* fout_pt_PbPb_long = new TFile("./results/PbPb_yieldvspt_N220260_all.root");
  TGraphErrors* gr_yield_pt_PbPb_long = (TGraphErrors*)fout_pt_PbPb_long->Get("gr_yield_long_pt");

  gr_yield_pt_pPb_short->SetMarkerStyle(20);
  gr_yield_pt_pPb_short->SetMarkerColor(kRed);
  gr_yield_pt_pPb_long->SetMarkerStyle(20);
  gr_yield_pt_pPb_long->SetMarkerColor(kRed);
  gr_yield_pt_PbPb_short->SetMarkerStyle(21);
  gr_yield_pt_PbPb_short->SetMarkerColor(kBlue);
  gr_yield_pt_PbPb_long->SetMarkerStyle(21);
  gr_yield_pt_PbPb_long->SetMarkerColor(kBlue);
  gr_yield_mult_pPb_short->SetMarkerStyle(20);
  gr_yield_mult_pPb_short->SetMarkerColor(kRed);
  gr_yield_mult_pPb_long->SetMarkerStyle(20);
  gr_yield_mult_pPb_long->SetMarkerColor(kRed);
  gr_yield_mult_PbPb_short->SetMarkerStyle(21);
  gr_yield_mult_PbPb_short->SetMarkerColor(kBlue);
  gr_yield_mult_PbPb_long->SetMarkerStyle(21);
  gr_yield_mult_PbPb_long->SetMarkerColor(kBlue);

  TH1D* htmp_pt = new TH1D("tmp_pt",";p^{trig}_{T}(GeV/c);Associated Yield / (GeV/c)",100,-0.1,11.9);
  htmp_pt->SetLineWidth(1);
  htmp_pt->SetLineStyle(9);
  htmp_pt->GetXaxis()->CenterTitle();
  htmp_pt->GetYaxis()->CenterTitle();
  htmp_pt->SetMaximum(0.72);
  htmp_pt->SetMinimum(-0.03);
  TH1D* htmp_mult = new TH1D("tmp_mult",";N_{trk}^{offline};Associated Yield / (GeV/c)",350,-5,359);
  htmp_mult->SetLineWidth(1);
  htmp_mult->GetXaxis()->CenterTitle();
  htmp_mult->GetYaxis()->CenterTitle();
  htmp_mult->SetMaximum(0.72);
  htmp_mult->SetMinimum(-0.03);
  TH1D* htmp1_mult = new TH1D("tmp1_mult",";N_{trk}^{offline};Associated Yield / (GeV/c)",350,-5,359);
  htmp1_mult->SetLineWidth(1);
  htmp1_mult->GetXaxis()->CenterTitle();
  htmp1_mult->GetYaxis()->CenterTitle();
  htmp1_mult->SetMaximum(0.38);
  htmp1_mult->SetMinimum(-0.03);
  TH1D* htmp_mult_small = new TH1D("tmp_mult_small",";N_{trk}^{offline};Associated Yield / (GeV/c)",399,-5,130);
  htmp_mult_small->SetLineWidth(1);
  htmp_mult_small->GetXaxis()->CenterTitle();
  htmp_mult_small->GetYaxis()->CenterTitle();
  htmp_mult_small->SetMaximum(0.082);
  htmp_mult_small->SetMinimum(-0.01);
  fixedFontHist1D(htmp_pt,1.8,2.4);
  fixedFontHist1D(htmp_mult,1.8,2.4);
  fixedFontHist1D(htmp_mult_small,1.8,2.4);
/*
  htmp_mult->GetYaxis()->SetTitleOffset(htmp_mult->GetYaxis()->GetTitleOffset());
  htmp_mult->GetYaxis()->SetTitleSize(htmp_mult->GetYaxis()->GetTitleSize()*2.5);
  htmp_mult->GetXaxis()->SetTitleSize(htmp_mult->GetXaxis()->GetTitleSize()*2.5);
  htmp_pt->GetYaxis()->SetTitleOffset(htmp_pt->GetYaxis()->GetTitleOffset());
  htmp_pt->GetYaxis()->SetTitleSize(htmp_pt->GetYaxis()->GetTitleSize()*2.5);
  htmp_pt->GetXaxis()->SetTitleSize(htmp_pt->GetXaxis()->GetTitleSize()*2.5);
*/

  TCanvas* c4 = new TCanvas("c4","",790,600);
  makeMultiPanelCanvas(c4,2,2,0.02,0.02,0.15,0.15,0.01);
  c4->cd(1);
  c4->GetPad(1)->SetRightMargin(0.006);
  htmp_pt->Draw();
  drawSystBox(gr_yield_pt_pPb_short,1.038,0.003,17);
  drawSystBox(gr_yield_pt_PbPb_short,1.034,0.003,17,0.3,0,0);
  gr_yield_pt_PbPb_short->Draw("PESAME");
  gr_yield_pt_pPb_short->Draw("PESAME");
  c4->cd(3);
  c4->GetPad(3)->SetRightMargin(0.006);
  htmp_pt->Draw();
  drawSystBox(gr_yield_pt_pPb_long,1.038,0.003,17);
  drawSystBox(gr_yield_pt_PbPb_long,1.034,0.003,17,0.3,0,0);
  gr_yield_pt_PbPb_long->Draw("PESAME");
  gr_yield_pt_pPb_long->Draw("PESAME");
  c4->cd(2);
  c4->GetPad(2)->SetLeftMargin(0.006);
  htmp_mult->Draw();
  drawSystBox(gr_yield_mult_pPb_short,1.038,0.003,17,8);
  drawSystBox(gr_yield_mult_PbPb_short,1.034,0.003,17,8,0,0);
  gr_yield_mult_PbPb_short->Draw("PESAME");
  gr_yield_mult_pPb_short->Draw("PESAME");
  c4->cd(4);
  c4->GetPad(4)->SetLeftMargin(0.006);
  htmp_mult->Draw();
  drawSystBox(gr_yield_mult_pPb_long,1.038,0.003,17,8);
  drawSystBox(gr_yield_mult_PbPb_long,1.034,0.003,17,8,0,0);
  gr_yield_mult_PbPb_long->Draw("PESAME");
  gr_yield_mult_pPb_long->Draw("PESAME");
  gr_yield_mult_pPb_old->Draw("PESAME");
  gr_yield_mult_pp->Draw("PESAME");
  gr_yield_cgc_1->Draw("Lsame");
  gr_yield_cgc_2->Draw("Lsame");

  TPad *p_0_1 = new TPad("p_0_1", "p_0_1",0.05,0.55,0.62,0.89);
  p_0_1->Draw();
  p_0_1->cd();
  htmp_mult_small->SetTitle(";;;");
  htmp_mult_small->Draw();
//  drawSystBox(gr_yield_mult_pPb_long,1.061,0.003,17,8);
//  drawSystBox(gr_yield_mult_PbPb_long,1.061,0.003,17,8);
  gr_yield_mult_PbPb_long->Draw("PE");
  gr_yield_mult_pPb_long->Draw("PESAME");
  gr_yield_mult_pPb_old->Draw("PESAME");
  gr_yield_mult_pp->Draw("PESAME");

  TCanvas* c = new TCanvas("c","",790,380);
  makeMultiPanelCanvas(c,2,1,0.02,0.02,0.15,0.15,0.01);
  c->cd(1);
  htmp_pt->Draw();
  gr_yield_pt_PbPb_short->Draw("PESAME");
  gr_yield_pt_pPb_short->Draw("PESAME");
  c->cd(2);
  htmp_pt->Draw();
  gr_yield_pt_PbPb_long->Draw("PESAME");
  gr_yield_pt_pPb_long->Draw("PESAME");

  TCanvas* cc = new TCanvas("cc","",790,380);
  makeMultiPanelCanvas(cc,2,1,0.02,0.02,0.15,0.15,0.01);
  cc->cd(1);
  htmp1_mult->Draw();
  drawSystBox(gr_yield_mult_pPb_short,1.038,0.003,17,8);
  drawSystBox(gr_yield_mult_PbPb_short,1.038,0.003,17,8);
  gr_yield_mult_pPb_short->Draw("PESAME");
  gr_yield_mult_PbPb_short->Draw("PESAME");
  cc->cd(2);
  htmp1_mult->Draw();
  drawSystBox(gr_yield_mult_pPb_long,1.038,0.003,17,8);
  drawSystBox(gr_yield_mult_PbPb_long,1.038,0.003,17,8);
  gr_yield_mult_PbPb_long->Draw("PESAME");
  gr_yield_mult_pPb_long->Draw("PESAME");

  TLatex* cmsp = new TLatex();
  cmsp->SetNDC();
  cmsp->SetTextSize(cmsp->GetTextSize()*1.3);
/*
  cc->cd(1);
  cmsp->DrawLatex(0.24,0.92,"CMS");
  cmsp->DrawLatex(0.17,0.92,"(a)");
  cmsp->DrawLatex(0.5,0.92,"Jet minus Ridge (|#Delta#eta|<1)");
  cmsp->DrawLatex(0.5,0.84,"1 < p_{T}^{trig} < 2 GeV/c");
  cmsp->DrawLatex(0.5,0.775,"1 < p_{T}^{assoc} < 2 GeV/c");
  c->cd(1);
  cmsp->DrawLatex(0.24,0.92,"CMS");
  cmsp->DrawLatex(0.17,0.92,"(a)");
  cmsp->DrawLatex(0.5,0.92,"Jet minus Ridge (|#Delta#eta|<1)");
  cmsp->DrawLatex(0.2,0.83,"220 #leq N_{trk}^{offline} < 260");
  cmsp->DrawLatex(0.2,0.765,"1 < p_{T}^{assoc} < 2 GeV/c");
  cc->cd(2);
  cmsp->DrawLatex(0.03,0.92,"(b)");
  cmsp->DrawLatex(0.5,0.92,"Ridge region (|#Delta#eta|>2)");
  c->cd(2);
  cmsp->DrawLatex(0.03,0.92,"(b)");
  cmsp->DrawLatex(0.5,0.92,"Ridge region (|#Delta#eta|>2)");
*/
  c4->cd(1); 
  cmsp->DrawLatex(0.25,0.78,"CMS");
  cmsp->DrawLatex(0.19,0.92,"(a)");
  cmsp->DrawLatex(0.46,0.92,"Jet minus Ridge region");
  cmsp->DrawLatex(0.6,0.34,"220 #leq N_{trk}^{offline} < 260");
  cmsp->DrawLatex(0.6,0.245,"1 < p_{T}^{assoc} < 2 GeV/c");
  c4->cd(2);
  cmsp->DrawLatex(0.05,0.92,"(b)");
  cmsp->DrawLatex(0.4,0.92,"Jet minus Ridge region");
  cmsp->DrawLatex(0.55,0.81,"1 < p_{T}^{trig} < 2 GeV/c");
  cmsp->DrawLatex(0.55,0.71,"1 < p_{T}^{assoc} < 2 GeV/c");
  c4->cd(3);
  cmsp->DrawLatex(0.19,0.92,"(c)");
  cmsp->SetTextSize(cmsp->GetTextSize()*0.85); 
  cmsp->DrawLatex(0.5,0.92,"Ridge region (|#Delta#eta|>2)");
  c4->cd(4);
  cmsp->SetTextSize(cmsp->GetTextSize()*(1/0.85));
  cmsp->DrawLatex(0.05,0.92,"(d)");
  cmsp->SetTextSize(cmsp->GetTextSize()*0.85);
  cmsp->DrawLatex(0.4,0.92,"Ridge region (|#Delta#eta|>2)");
  cmsp->SetTextSize(cmsp->GetTextSize()*0.9);
  cmsp->DrawLatex(0.05,0.50,"CGC calculations");

  TLegend* lll  = new TLegend(0.4276526,0.62,0.9483568,0.8636585,NULL,"brNDC");
  lll->SetFillColor(0);
  lll->SetFillStyle(0);
  lll->AddEntry(gr_yield_pt_pPb_short,"pPb  #sqrt{s_{NN}} = 5.02 TeV, 2013","P");
  lll->AddEntry(gr_yield_pt_PbPb_short,"PbPb  #sqrt{s_{NN}} = 2.76 TeV","P");
  lll->AddEntry(gr_yield_pt_pPb_old,"pPb  #sqrt{s_{NN}} = 5.02 TeV, 2012","P");
  lll->AddEntry(gr_yield_pt_pp,"pp  #sqrt{s} = 7 TeV","P");
  c4->cd(3);
  lll->Draw("same");

  TLegend* l_cgc  = new TLegend(0.0276526,0.37,0.4783568,0.485585,NULL,"brNDC");
  l_cgc->SetFillColor(0);
  l_cgc->SetFillStyle(0);
  l_cgc->AddEntry(gr_yield_cgc_1,"Q_{0}^{2}(proton)=0.336 GeV^{2}","L");
  l_cgc->AddEntry(gr_yield_cgc_2,"Q_{0}^{2}(proton)=0.504 GeV^{2}","L");
  c4->cd(4);
  l_cgc->Draw("same");

  cc->cd(1);
  cmsp->DrawLatex(0.25,0.78,"CMS");
  cmsp->DrawLatex(0.46,0.92,"Jet minus Ridge region");
  cc->cd(2);
//  cmsp->SetTextSize(cmsp->GetTextSize()*0.85);
  cmsp->DrawLatex(0.5,0.92,"Ridge region (|#Delta#eta|>2)");
  cmsp->DrawLatex(0.55,0.82,"1 < p_{T}^{trig} < 2 GeV/c");
  cmsp->DrawLatex(0.55,0.74,"1 < p_{T}^{assoc} < 2 GeV/c");

  TLegend* l  = new TLegend(0.4076526,0.25,0.9583568,0.4236585,NULL,"brNDC");
  l->SetFillColor(0);
  l->SetFillStyle(0);
  l->SetHeader("Centrality cuts");
  l->AddEntry(gr_yield_pt_pPb_short,"Track Multiplicity Based","P");
  l->AddEntry(gr_yield_pt_PbPb_short,"HF sum ET based","P");
  cc->cd(1);
  l->Draw("same");
  c->cd(2);
  l->Draw("same");
  
  cmsp->SetTextSize(cmsp->GetTextSize()*0.85);
  TLatex* latex_yieldvsmult = new TLatex();
  latex_yieldvsmult->SetNDC();
//  latex_yieldvsmult->DrawLatex(0.15,0.9,"1 < p_{T} < 2 GeV/c");

  SaveCanvas(cc,"pPb/corr","yieldvsmult_hfcuts");
//  SaveCanvas(c,"pPb/corr","yieldvspt_new");
//  SaveCanvas(c4,"pPb/corr","yieldvsptvsmult_new");
}

void systematics_yield()
{
  // HIN-13-002
  TFile* fout_mult_pPb_short = new TFile("./results/pPb_yieldvsn_pt1-2_loose.root");
  TGraphErrors* gr_yield_mult_pPb_short = (TGraphErrors*)fout_mult_pPb_short->Get("gr_yield_short_mult");
  TFile* fout_mult_pPb_long = new TFile("./results/pPb_yieldvsn_pt1-2_loose.root");
  TGraphErrors* gr_yield_mult_pPb_long = (TGraphErrors*)fout_mult_pPb_long->Get("gr_yield_long_mult");

  TFile* fout_mult_PbPb_short = new TFile("./results/pPb_yieldvsn_pt1-2_tight.root");
  TGraphErrors* gr_yield_mult_PbPb_short = (TGraphErrors*)fout_mult_PbPb_short->Get("gr_yield_short_mult");
  TFile* fout_mult_PbPb_long = new TFile("./results/pPb_yieldvsn_pt1-2_tight.root");
  TGraphErrors* gr_yield_mult_PbPb_long = (TGraphErrors*)fout_mult_PbPb_long->Get("gr_yield_long_mult");

  TFile* fout_pt_pPb_short = new TFile("./results/pPb_yieldvspt_N220260.root");
  TGraphErrors* gr_yield_pt_pPb_short = (TGraphErrors*)fout_pt_pPb_short->Get("gr_yield_short_pt");
  TFile* fout_pt_pPb_long = new TFile("./results/pPb_yieldvspt_N220260.root");
  TGraphErrors* gr_yield_pt_pPb_long = (TGraphErrors*)fout_pt_pPb_long->Get("gr_yield_long_pt");

  TFile* fout_pt_PbPb_short = new TFile("./results/pPb_yieldvspt_N220260_loose.root");
  TGraphErrors* gr_yield_pt_PbPb_short = (TGraphErrors*)fout_pt_PbPb_short->Get("gr_yield_short_pt");
  TFile* fout_pt_PbPb_long = new TFile("./results/pPb_yieldvspt_N220260_loose.root");
  TGraphErrors* gr_yield_pt_PbPb_long = (TGraphErrors*)fout_pt_PbPb_long->Get("gr_yield_long_pt");
/*
  TFile* fout_mult_pPb_short_mb = new TFile("./results/pPb_yieldvsn_pt1-2_loose_mb.root");
  TGraphErrors* gr_yield_mult_pPb_short_mb = (TGraphErrors*)fout_mult_pPb_short_mb->Get("gr_yield_short_mult");
  TFile* fout_mult_pPb_long_mb = new TFile("./results/pPb_yieldvsn_pt1-2_loose_mb.root");
  TGraphErrors* gr_yield_mult_pPb_long_mb = (TGraphErrors*)fout_mult_pPb_long_mb->Get("gr_yield_long_mult");
  
  TFile* fout_mult_PbPb_short_mb = new TFile("./results/pPb_yieldvsn_pt1-2_tight_mb.root");
  TGraphErrors* gr_yield_mult_PbPb_short_mb = (TGraphErrors*)fout_mult_PbPb_short_mb->Get("gr_yield_short_mult");
  TFile* fout_mult_PbPb_long_mb = new TFile("./results/pPb_yieldvsn_pt1-2_tight_mb.root");
  TGraphErrors* gr_yield_mult_PbPb_long_mb = (TGraphErrors*)fout_mult_PbPb_long_mb->Get("gr_yield_long_mult");
*/  
  gr_yield_pt_pPb_short->SetMarkerStyle(20);
  gr_yield_pt_pPb_short->SetMarkerColor(kRed);
  gr_yield_pt_pPb_long->SetMarkerStyle(20);
  gr_yield_pt_pPb_long->SetMarkerColor(kRed);
  gr_yield_pt_PbPb_short->SetMarkerStyle(21);
  gr_yield_pt_PbPb_short->SetMarkerColor(kBlue);
  gr_yield_pt_PbPb_long->SetMarkerStyle(21);
  gr_yield_pt_PbPb_long->SetMarkerColor(kBlue);
  gr_yield_mult_pPb_short->SetMarkerStyle(20);
  gr_yield_mult_pPb_short->SetMarkerColor(kRed);
  gr_yield_mult_pPb_long->SetMarkerStyle(20);
  gr_yield_mult_pPb_long->SetMarkerColor(kRed);
  gr_yield_mult_PbPb_short->SetMarkerStyle(21);
  gr_yield_mult_PbPb_short->SetMarkerColor(kBlue);
  gr_yield_mult_PbPb_long->SetMarkerStyle(21);
  gr_yield_mult_PbPb_long->SetMarkerColor(kBlue);
/*
  gr_yield_mult_pPb_short_mb->SetMarkerStyle(20);
  gr_yield_mult_pPb_short_mb->SetMarkerColor(kRed);
  gr_yield_mult_pPb_long_mb->SetMarkerStyle(20);
  gr_yield_mult_pPb_long_mb->SetMarkerColor(kRed);
  gr_yield_mult_PbPb_short_mb->SetMarkerStyle(21);
  gr_yield_mult_PbPb_short_mb->SetMarkerColor(kBlue);
  gr_yield_mult_PbPb_long_mb->SetMarkerStyle(21);
  gr_yield_mult_PbPb_long_mb->SetMarkerColor(kBlue);
*/

  GraphScaleShift(gr_yield_pt_pPb_short,0.99,0.0);
  GraphScaleShift(gr_yield_pt_pPb_long,0.99,0.0);
  GraphScaleShift(gr_yield_mult_pPb_short,1.05,0.0);
  GraphScaleShift(gr_yield_mult_pPb_long,1.05,0.0);

  TH1D* htmp_pt = new TH1D("tmp_pt",";p^{trig}_{T}(GeV/c);Associated Yield / (GeV/c)",100,-0.3,11.9);
  htmp_pt->SetLineWidth(1);
  htmp_pt->SetLineStyle(9);
  htmp_pt->GetXaxis()->CenterTitle();
  htmp_pt->GetYaxis()->CenterTitle();
  htmp_pt->SetMaximum(0.75);
  htmp_pt->SetMinimum(-0.03);
  TH1D* htmp_mult = new TH1D("tmp_mult",";N_{trk}^{offline};Associated Yield / (GeV/c)",350,-3,349);
  htmp_mult->SetLineWidth(1);
  htmp_mult->GetXaxis()->CenterTitle();
  htmp_mult->GetYaxis()->CenterTitle();
  htmp_mult->SetMaximum(0.75);
  htmp_mult->SetMinimum(-0.03);
  TH1D* htmp_mult_small = new TH1D("tmp_mult_small",";N_{trk}^{offline};Associated Yield / (GeV/c)",399,-3,130);
  htmp_mult_small->SetLineWidth(1);
  htmp_mult_small->GetXaxis()->CenterTitle();
  htmp_mult_small->GetYaxis()->CenterTitle();
  htmp_mult_small->SetMaximum(0.1);
  htmp_mult_small->SetMinimum(-0.01);
  fixedFontHist1D(htmp_pt,1.8,2.4);
  fixedFontHist1D(htmp_mult,1.8,2.4);

  TCanvas* c4 = new TCanvas("c4","",790,600);
  makeMultiPanelCanvas(c4,2,2,0.02,0.02,0.15,0.15,0.01);
  c4->cd(1);
  htmp_pt->Draw();
  gr_yield_pt_PbPb_short->Draw("PESAME");
  gr_yield_pt_pPb_short->Draw("PESAME");
  c4->cd(3);
  htmp_pt->Draw();
  gr_yield_pt_PbPb_long->Draw("PESAME");
  gr_yield_pt_pPb_long->Draw("PESAME");
  c4->cd(2);
  htmp_mult->Draw();
  gr_yield_mult_PbPb_short->Draw("PESAME");
  gr_yield_mult_pPb_short->Draw("PESAME");
//  gr_yield_mult_PbPb_short_mb->Draw("PESAME");
//  gr_yield_mult_pPb_short_mb->Draw("PESAME");
  c4->cd(4);
  htmp_mult->Draw();
  gr_yield_mult_PbPb_long->Draw("PESAME");
  gr_yield_mult_pPb_long->Draw("PESAME");
//  gr_yield_mult_PbPb_long_mb->Draw("PESAME");
//  gr_yield_mult_pPb_long_mb->Draw("PESAME");

  TLatex* cmsp = new TLatex();
  cmsp->SetNDC();
  cmsp->SetTextSize(cmsp->GetTextSize()*1.3);
  c4->cd(1); 
  cmsp->DrawLatex(0.25,0.78,"CMS");
  cmsp->DrawLatex(0.19,0.92,"(a)");
  cmsp->DrawLatex(0.46,0.92,"Jet minus Ridge region");
  cmsp->DrawLatex(0.6,0.34,"220 #leq N_{trk}^{offline} < 260");
  cmsp->DrawLatex(0.6,0.245,"1 < p_{T}^{assoc} < 2 GeV/c");
  c4->cd(2);
  cmsp->DrawLatex(0.05,0.92,"(b)");
  cmsp->DrawLatex(0.4,0.92,"Jet minus Ridge region");
  cmsp->DrawLatex(0.55,0.81,"1 < p_{T}^{trig} < 2 GeV/c");
  cmsp->DrawLatex(0.55,0.71,"1 < p_{T}^{assoc} < 2 GeV/c");
  c4->cd(3);
  cmsp->DrawLatex(0.19,0.92,"(c)");
  cmsp->SetTextSize(cmsp->GetTextSize()*0.85); 
  cmsp->DrawLatex(0.5,0.92,"Ridge region (|#Delta#eta|>2)");
  c4->cd(4);
  cmsp->SetTextSize(cmsp->GetTextSize()*(1/0.85));
  cmsp->DrawLatex(0.05,0.92,"(d)");
  cmsp->SetTextSize(cmsp->GetTextSize()*0.85);
  cmsp->DrawLatex(0.4,0.92,"Ridge region (|#Delta#eta|>2)");

  TLegend* lll  = new TLegend(0.1276526,0.62,0.9483568,0.8236585,NULL,"brNDC");
  lll->SetFillColor(0);
  lll->SetFillStyle(0);
//  lll->AddEntry(gr_yield_pt_pPb_short,"Standard analysis","P");
//  lll->AddEntry(gr_yield_pt_PbPb_short,"# of vertices = 1","P");
//  lll->AddEntry(gr_yield_pt_pPb_short,"|v_{z}|<3 cm","P");
//  lll->AddEntry(gr_yield_pt_PbPb_short,"3<|v_{z}|<15 cm","P");
  lll->AddEntry(gr_yield_pt_pPb_short,"Looser track cuts","P");
  lll->AddEntry(gr_yield_pt_PbPb_short,"Tighter track cuts","P");
  c4->cd(3);
  lll->Draw("same");

//  SaveCanvas(c4,"pPb/corr","systematics_yieldvsptvsmult_vertexdep");
//  SaveCanvas(c4,"pPb/corr","systematics_yieldvsptvsmult_nvtx1");
  SaveCanvas(c4,"pPb/corr","systematics_yieldvsptvsmult_tracking");
}

void yield_paper_preliminary()
{
  TGraphErrors* gr_yield_pt_pp = GetGraphWithSymmYErrorsFromFile("./paper/Figure9a.dat",1,24,1,1);
  TGraphErrors* gr_yield_mult_pp = GetGraphWithSymmYErrorsFromFile("./paper/Figure9b.dat",1,24,1,1);
  GraphScaleShift(gr_yield_pt_pp,(2*PI)*4.8/4.,0.0);
  GraphScaleShift(gr_yield_mult_pp,(2*PI)*4.8/4.,0.0);

  TFile* fout_mult = new TFile("results_INCLEFF1v4_12nbins_new.root");
  TGraphErrors* gr_yield_mult_pPb = (TGraphErrors*)fout_mult->Get("gr_yield_mult_1");
//  TFile* fout_mult = new TFile("results_INCLEFF1ONEPTBIN_12nbins.root");
//  TGraphErrors* gr_yield_mult_pPb = (TGraphErrors*)fout_mult->Get("gr_yield_mult_0");
  TFile* fout_pt = new TFile("results_INCLEFF1v5_4nbins.root");
  TGraphErrors* gr_yield_pt_pPb = (TGraphErrors*)fout_pt->Get("gr_yield_pt_3");

  gr_yield_pt_pp->SetMarkerStyle(24);
  gr_yield_pt_pPb->SetMarkerStyle(20);
  gr_yield_pt_pPb->SetMarkerColor(kRed);
  gr_yield_mult_pp->SetMarkerStyle(24);
  gr_yield_mult_pPb->SetMarkerStyle(20);
  gr_yield_mult_pPb->SetMarkerColor(kRed);

  TH1D* htmp_pt = new TH1D("tmp_pt",";p_{T}(GeV/c);Associated Yield / (GeV/c)",100,-0.3,7.5);
  htmp_pt->SetLineWidth(1);
  htmp_pt->SetLineStyle(9);
  htmp_pt->GetXaxis()->CenterTitle();
  htmp_pt->GetYaxis()->CenterTitle();
  htmp_pt->SetMaximum(0.05);
  htmp_pt->SetMinimum(-0.01);
  htmp_pt->GetYaxis()->SetTitleOffset(htmp_pt->GetYaxis()->GetTitleOffset()*1.4);
  TH1D* htmp_mult = new TH1D("tmp_mult",";N_{trk}^{offline};Associated Yield / (GeV/c)",200,-1.9,195);
  htmp_mult->SetLineWidth(1);
  htmp_mult->GetXaxis()->CenterTitle();
  htmp_mult->GetYaxis()->CenterTitle();
  htmp_mult->SetMaximum(0.05);
  htmp_mult->SetMinimum(-0.01);
  htmp_mult->GetYaxis()->SetTitleOffset(htmp_mult->GetYaxis()->GetTitleOffset()*1.6);

  TCanvas* cccc = new TCanvas("cccc","",790,450);
  makeMultiPanelCanvas(cccc,2,1,0.02,0.02,0.2,0.2,0.01);
  cccc->cd(1);
  htmp_pt->Draw();
  drawSystBox(gr_yield_pt_pPb,1.054,0.0015,17);
  gr_yield_pt_pp->Draw("PESAME");
  gr_yield_pt_pPb->Draw("PESAME");
  gr_yield_pt_pp->SetMarkerSize(1.3);
  gr_yield_pt_pp->Draw("PESAME");
  TPad *p_0_0 = new TPad("p_0_0", "p_0_0",0.07,0.3,0.16,0.4);
  p_0_0->Draw();
  p_0_0->cd();

  cccc->cd(2);
  htmp_mult->Draw();
  drawSystBox(gr_yield_mult_pPb,1.054,0.0015,17,5);
  gr_yield_mult_pp->Draw("PESAME");
  gr_yield_mult_pPb->Draw("PESAME");
  gr_yield_mult_pp->SetMarkerSize(1.3);
  gr_yield_mult_pp->Draw("PESAME");
  TPad *p_0_1 = new TPad("p_0_0", "p_0_0",0 ,0.13,0.1,0.19);
  p_0_1->Draw();
  p_0_1->cd();

  cccc->cd(1);
  TLatex* latex_yieldvspt = new TLatex();
  latex_yieldvspt->SetNDC();
  latex_yieldvspt->DrawLatex(0.676767, 0.9,"N_{trk}^{offline} #geq 110");
  TLatex* cmsp = new TLatex();
  cmsp->SetNDC();
  cmsp->DrawLatex(0.3,0.92,"CMS Preliminary");

  TLatex* label = new TLatex(0.22,0.92,"(a)");
  label->SetNDC();
  label->Draw();

  TLegend* lll  = new TLegend(0.4976526,0.7,0.9483568,0.8536585,NULL,"brNDC");
   lll->SetFillColor(0);
  lll->SetTextFont(42);
  lll->AddEntry(gr_yield_pt_pPb,"pPb  #sqrt{s_{NN}} = 5.02 TeV","P");
  lll->AddEntry(gr_yield_pt_pp,"pp  #sqrt{s} = 7 TeV","P");
  lll->Draw("same");
  cccc->cd(2);
  TLatex* latex_yieldvsmult = new TLatex();
  latex_yieldvsmult->SetNDC();
  latex_yieldvsmult->DrawLatex(0.15,0.9,"1 < p_{T} < 2 GeV/c");
  
  TLatex* label = new TLatex(0.03,0.92,"(b)");
  label->SetNDC();
  label->Draw();
  
  SaveCanvas(cccc,"pPb/corr","yieldvsptvsmult_paper_preliminary");
}


template <class T>
T* compare_flow_pp_phi_multipad_pt(TString eventtype1="PPData_Minbias_7TeV", TString tag1="TRIGGER85_All_ReTracking_INCLEFF1TRG1v5NEW", int nmin=110, int nmax=1000, int centmin=-1, int centmax=-1, double detamin=2.0, double detamax=4.8,  bool IsDraw=1, bool IsSave=0, int ret=0)
{
  gStyle->SetTitleSize(0.12,"t");//  gStyle->SetTitleX(0.8);
  gStyle->SetTitleW(0.8);

  const int ntrgptbins = 9;
  const int nassptbins = 9;
  int trgptbin[ntrgptbins] = {0,1,2,3,4,5,6,7,8};
  int assptbin[nassptbins] = {0,1,2,3,4,5,6,7,8};
  double ptmin[9]={0.1,1.0,2.0,3.0,4.0,5.0,1.0,2.0,4.0};
  double ptmax[9]={1.0,2.0,3.0,4.0,5.0,6.0,3.0,4.0,6.0};

  TH1D* h_zyam[ntrgptbins][nassptbins];
  TF1*  fitfunc[ntrgptbins][nassptbins];
  TH1D*** h;
  h=new TH1D**[nassptbins];
  for(int i=0;i<ntrgptbins;i++) {
     h[i]=new TH1D*[nassptbins];
  }

  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,centmin,centmax);

  TGraphErrors* gr_yield_pt_paper = new TGraphErrors(ntrgptbins-3);

  for(int itrg = 0; itrg<ntrgptbins-2; itrg++)
  {
    for(int jass = 0; jass<nassptbins-2; jass++)
    {
//      if(jass!=1) continue;
      h[itrg][jass] = (TH1D*)Get1DCFdPhiv3(filename.Data(),trgptbin[itrg],assptbin[jass],detamin,detamax);
      h[itrg][jass]->SetMarkerColor(kRed);
      // pp ZYAM
      if(ret==1)
      {
        fitfunc[itrg][jass]=GetFitFunc_ZYAM_pp(h[itrg][jass]);
        fitfunc[itrg][jass]->SetLineColor(kRed);
        h_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM_pp(h[itrg][jass]);
        TH1D* hpt = (TH1D*)GetHist(filename,Form("ptcorr_signal_trg_%d",trgptbin[itrg]));
        double zyamminimum=fitfunc[itrg][jass]->GetParameter(2);
        double zyamminimumscale=zyamminimum;
//        if(zyamminimumscale<1.0) zyamminimumscale=1.0;
        double yielderror=0;
        double yield = h_zyam[itrg][jass]->IntegralAndError(h_zyam[itrg][jass]->FindBin(-zyamminimum),h_zyam[itrg][jass]->FindBin(zyamminimum),yielderror,"width")/2.;//zyamminimumscale;
        yielderror=yielderror/2.;//zyamminimumscale; // safety factor of 2
        if(jass==1 && itrg<6)
        {
          gr_yield_pt_paper->SetPoint(itrg,hpt->GetMean(),yield);
          gr_yield_pt_paper->SetPointError(itrg,0,yielderror);
        }
      }
    }
  }

  if(ret==0) return h;
  if(ret==1) return gr_yield_pt_paper;
}

compare_yieldvseta()
{
  gStyle->SetTextSize(15);
  gStyle->SetTextFont(43);

  const int nbins=10;
  double binwidth=0.6;
  TGraph* gr[nbins];
  TGraph* gr1[nbins];
  TGraph* gr2[nbins];
  TGraph* gr3[nbins];
  double x[nbins],y[nbins],xerr[nbins],yerr[nbins];
  double x1[nbins],y1[nbins],xerr1[nbins],yerr1[nbins];
  double x2[nbins],y2[nbins],xerr2[nbins],yerr2[nbins];
  double x3[nbins],y3[nbins],xerr3[nbins],yerr3[nbins];
  double eta[nbins];
  double etaerr[nbins]={0};
  
  for(int i=0;i<nbins;i++)
  {
    gr1[i] = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER85_All_INCLEFF1TRG1v6",110,1000,-1,-1,-0.3+binwidth*i,0.3+binwidth*i,0,0,1);

    gr1[i]->GetPoint(2,x1[i],y1[i]);

    yerr1[i]=gr1[i]->GetErrorY(2);
    eta[i]=binwidth*i;
  }
  eta[0]=0.15;
  TGraphErrors* gra1 = new TGraphErrors(nbins,eta,y1,etaerr,yerr1);
  gra1->SetMarkerSize(gra1->GetMarkerSize());
  gra1->SetMarkerColor(kRed);
  gra1->SetLineColor(kRed);
  gra1->SetLineWidth(2);
  gra1->SetMarkerSize(gra1->GetMarkerSize()*1.5);

  TH2D* h = new TH2D("h",";|#Delta#eta|; Associated Yield",100,0,4.5,100,0.001,0.53);
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.5);
  TCanvas* c = new TCanvas("c","",500,500);
  c->SetLogy();
  h->Draw();
  
  gra1->Draw("samePE");

/*
  TLegend* legend = new TLegend(0.45,0.65,0.9,0.8);
  legend->SetFillColor(0);
  legend->AddEntry(gra,"PbPb 2.76TeV, 0-5%","P");
  legend->AddEntry(gra0,"PYTHIA8 pp 2.76TeV","L");
  legend->Draw();
*/
  TLatex* latex_trg = new TLatex(0.55,0.31,"2<p^{trig}_{T}<3 GeV/c");
  latex_trg->SetNDC();
  latex_trg->SetTextSize(latex_trg->GetTextSize()*1.25);
  latex_trg->Draw();

  TLatex* latex_ass = new TLatex(0.55,0.24,"1<p^{assoc}_{T}<2 GeV/c");
  latex_ass->SetNDC();
  latex_ass->SetTextSize(latex_ass->GetTextSize()*1.25);
  latex_ass->Draw();

  TLine *l = new TLine(0,0,5.0,0);
  l->SetLineStyle(9);
  l->Draw();

  TLatex* cms = new TLatex();
  cms->SetNDC();
  cms->SetTextSize(cms->GetTextSize()*1.5);
  cms->DrawLatex(0.5,0.85,"CMS");

  TLatex* multrange = new TLatex();
  multrange->SetNDC();
  multrange->SetTextSize(multrange->GetTextSize()*1.6);
  multrange->DrawLatex(0.55,0.75,"N #geq 110");
/*
  double jeterr[nbins];
  double ridgeerr[nbins];
  double fracjet = 0.08;
  double fracridge = 0.074;
  double add = 0.012;
  for(int i=0;i<nbins-1;i++)
  {
    if(eta[i]<2) jeterr[i] = sqrt(fabs(y[i]*fracjet)*fabs(y[i]*fracjet)+add*add);
    if(eta[i]>2) jeterr[i] = sqrt(fabs(y[i]*fracridge)*fabs(y[i]*fracridge)+add*add);
    DrawTick(y[i],jeterr[i],jeterr[i],eta[i],0.004,0.1,2);
  }
*/

  double error=0.15;
  double errorzyam=0.0006;
  for(int i=0;i<nbins-2;i++)
  {
    gra1->GetPoint(i,x1[i],y1[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y1[i]*error*y1[i]*error);
    DrawTick(y1[i],errortotal,errortotal,x1[i],0.0002,0.13,kRed);
  }

//  SaveCanvas(c,"flow_pp/paper_new","yieldvseta_pp_N110_trg2_ass1");
}

compare_yieldvspt_n()
{
  gStyle->SetTextSize(18);
  gStyle->SetTextFont(43);

  TGraphErrors* gr_short_2 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",2,35,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_35 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",35,45,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_45 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",45,60,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_60 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",60,90,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_90 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER70_All_INCLEFF1TRG1v6",90,1000,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_110 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER85_All_INCLEFF1TRG1v6",110,1000,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_130 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",130,1000,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_150   = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",150,1000,-1,-1,-1.0,1.0,0,0,1);

  TGraphErrors* gr_long_2 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",2,35,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_35 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",35,45,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_45 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",45,60,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_60 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",60,90,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_90 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER70_All_INCLEFF1TRG1v6",90,1000,-1,-1,2.0,4.,0,0,1); 
  TGraphErrors* gr_long_110 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER85_All_INCLEFF1TRG1v6",110,1000,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_130 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",130,1000,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_150   = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",150,1000,-1,-1,2.0,4.,0,0,1);

  double x1_short[6],y1_short[6],x1err_short[6],y1err_short[6];
  double x2_short[6],y2_short[6],x2err_short[6],y2err_short[6];
  double x3_short[6],y3_short[6],x3err_short[6],y3err_short[6];
  double x4_short[6],y4_short[6],x4err_short[6],y4err_short[6];
  double x5_short[6],y5_short[6],x5err_short[6],y5err_short[6];
  double x6_short[6],y6_short[6],x6err_short[6],y6err_short[6];
  double x7_short[6],y7_short[6],x7err_short[6],y7err_short[6];
  double x8_short[6],y8_short[6],x8err_short[6],y8err_short[6];

  double x1_long[6],y1_long[6],x1err_long[6],y1err_long[6];
  double x2_long[6],y2_long[6],x2err_long[6],y2err_long[6];
  double x3_long[6],y3_long[6],x3err_long[6],y3err_long[6];
  double x4_long[6],y4_long[6],x4err_long[6],y4err_long[6];
  double x5_long[6],y5_long[6],x5err_long[6],y5err_long[6];
  double x6_long[6],y6_long[6],x6err_long[6],y6err_long[6];
  double x7_long[6],y7_long[6],x7err_long[6],y7err_long[6];
  double x8_long[6],y8_long[6],x8err_long[6],y8err_long[6];

  double x_short_pt0[8],y_short_pt0[8],xerr_short_pt0[8],yerr_short_pt0[8];
  double x_short_pt1[8],y_short_pt1[8],xerr_short_pt1[8],yerr_short_pt1[8];
  double x_short_pt2[8],y_short_pt2[8],xerr_short_pt2[8],yerr_short_pt2[8];
  double x_short_pt3[8],y_short_pt3[8],xerr_short_pt3[8],yerr_short_pt3[8];
  double x_short_pt4[8],y_short_pt4[8],xerr_short_pt4[8],yerr_short_pt4[8];
  double x_short_pt5[8],y_short_pt5[8],xerr_short_pt5[8],yerr_short_pt5[8];

  double x_long_pt0[8],y_long_pt0[8],xerr_long_pt0[8],yerr_long_pt0[8];
  double x_long_pt1[8],y_long_pt1[8],xerr_long_pt1[8],yerr_long_pt1[8];
  double x_long_pt2[8],y_long_pt2[8],xerr_long_pt2[8],yerr_long_pt2[8];
  double x_long_pt3[8],y_long_pt3[8],xerr_long_pt3[8],yerr_long_pt3[8];
  double x_long_pt4[8],y_long_pt4[8],xerr_long_pt4[8],yerr_long_pt4[8];
  double x_long_pt5[8],y_long_pt5[8],xerr_long_pt5[8],yerr_long_pt5[8];

  double nmult[8]={12.8,38.8,50.3,67.5,98.7,118.1,138.3,156.8};
  double nmulterr[8]={0,0,0,0,0,0,0,0};

  TGraphErrors* gr_short_pttrg2 = new TGraphErrors(8);
  gr_short_2->GetPoint(2,x_short_pt2[0],y_short_pt2[0]);
  gr_short_35->GetPoint(2,x_short_pt2[1],y_short_pt2[1]);
  gr_short_45->GetPoint(2,x_short_pt2[2],y_short_pt2[2]);
  gr_short_60->GetPoint(2,x_short_pt2[3],y_short_pt2[3]);
  gr_short_90->GetPoint(2,x_short_pt2[4],y_short_pt2[4]);
  gr_short_110->GetPoint(2,x_short_pt2[5],y_short_pt2[5]);
  gr_short_130->GetPoint(2,x_short_pt2[6],y_short_pt2[6]);
  gr_short_150->GetPoint(2,x_short_pt2[7],y_short_pt2[7]);
  xerr_short_pt2[0] = gr_short_2->GetErrorX(2);
  xerr_short_pt2[1] = gr_short_35->GetErrorX(2);
  xerr_short_pt2[2] = gr_short_45->GetErrorX(2);
  xerr_short_pt2[3] = gr_short_60->GetErrorX(2);
  xerr_short_pt2[4] = gr_short_90->GetErrorX(2);
  xerr_short_pt2[5] = gr_short_110->GetErrorX(2);
  xerr_short_pt2[6] = gr_short_130->GetErrorX(2);
  xerr_short_pt2[7] = gr_short_150->GetErrorX(2);
  yerr_short_pt2[0] = gr_short_2->GetErrorY(2);
  yerr_short_pt2[1] = gr_short_35->GetErrorY(2);
  yerr_short_pt2[2] = gr_short_45->GetErrorY(2);
  yerr_short_pt2[3] = gr_short_60->GetErrorY(2);
  yerr_short_pt2[4] = gr_short_90->GetErrorY(2);
  yerr_short_pt2[5] = gr_short_110->GetErrorY(2);
  yerr_short_pt2[6] = gr_short_130->GetErrorY(2);
  yerr_short_pt2[7] = gr_short_150->GetErrorY(2);
  TGraphErrors* gr_short_pttrg2 = new TGraphErrors(8,nmult,y_short_pt2,nmulterr,yerr_short_pt2);
  gr_short_pttrg2->SetMarkerColor(kRed);
  gr_short_pttrg2->SetLineColor(kRed);
  gr_short_pttrg2->SetMarkerSize(gr_short_pttrg2->GetMarkerSize()*1.5);

  TGraphErrors* gr_long_pttrg2 = new TGraphErrors(8);
  gr_long_2->GetPoint(2,x_long_pt2[0],y_long_pt2[0]);
  gr_long_35->GetPoint(2,x_long_pt2[1],y_long_pt2[1]);
  gr_long_45->GetPoint(2,x_long_pt2[2],y_long_pt2[2]);
  gr_long_60->GetPoint(2,x_long_pt2[3],y_long_pt2[3]);
  gr_long_90->GetPoint(2,x_long_pt2[4],y_long_pt2[4]);
  gr_long_110->GetPoint(2,x_long_pt2[5],y_long_pt2[5]);
  gr_long_130->GetPoint(2,x_long_pt2[6],y_long_pt2[6]);
  gr_long_150->GetPoint(2,x_long_pt2[7],y_long_pt2[7]);
  xerr_long_pt2[0] = gr_long_2->GetErrorX(2);
  xerr_long_pt2[1] = gr_long_35->GetErrorX(2);
  xerr_long_pt2[2] = gr_long_45->GetErrorX(2);
  xerr_long_pt2[3] = gr_long_60->GetErrorX(2);
  xerr_long_pt2[4] = gr_long_90->GetErrorX(2);
  xerr_long_pt2[5] = gr_long_110->GetErrorX(2);
  xerr_long_pt2[6] = gr_long_130->GetErrorX(2);
  xerr_long_pt2[7] = gr_long_150->GetErrorX(2);
  yerr_long_pt2[0] = gr_long_2->GetErrorY(2);
  yerr_long_pt2[1] = gr_long_35->GetErrorY(2);
  yerr_long_pt2[2] = gr_long_45->GetErrorY(2);
  yerr_long_pt2[3] = gr_long_60->GetErrorY(2);
  yerr_long_pt2[4] = gr_long_90->GetErrorY(2);
  yerr_long_pt2[5] = gr_long_110->GetErrorY(2);
  yerr_long_pt2[6] = gr_long_130->GetErrorY(2);
  yerr_long_pt2[7] = gr_long_150->GetErrorY(2);
  TGraphErrors* gr_long_pttrg2 = new TGraphErrors(8,nmult,y_long_pt2,nmulterr,yerr_long_pt2);
  gr_long_pttrg2->SetMarkerColor(kRed);
  gr_long_pttrg2->SetLineColor(kRed);
  gr_long_pttrg2->SetMarkerSize(gr_long_pttrg2->GetMarkerSize()*1.5);

  TCanvas* c_gr1 = new TCanvas("c_gr1","",1200,350);
  makeMultiPanelCanvasNew(c_gr1,5,1,0.02,0.02,0.25,0.2,0.01);
  TH2D* htmp_pt1 = new TH2D("tmp_pt1",";p^{trig}_{T}(GeV/c);Associated Yield",100,0.01,6.2,100,-0.003,0.0199);  
  fixedFontHist(htmp_pt1);
  htmp_pt1->SetLineWidth(1);
  htmp_pt1->GetXaxis()->CenterTitle();
  htmp_pt1->GetYaxis()->CenterTitle();
  gr_long_2->SetMarkerColor(kRed);
  gr_long_35->SetMarkerColor(kRed);
  gr_long_90->SetMarkerColor(kRed);
  gr_long_110->SetMarkerColor(kRed);
  gr_long_130->SetMarkerColor(kRed);
  gr_long_150->SetMarkerColor(kRed);
  gr_long_2->SetLineColor(kRed);
  gr_long_35->SetLineColor(kRed);
  gr_long_90->SetLineColor(kRed);
  gr_long_110->SetLineColor(kRed);
  gr_long_130->SetLineColor(kRed);
  gr_long_150->SetLineColor(kRed);
  c_gr1->cd(1);
  htmp_pt1->Draw("");
  gr_long_2->Draw("PESAME");
  c_gr1->cd(2);
  htmp_pt1->Draw("");
  gr_long_35->Draw("PESAME");
  c_gr1->cd(3);
  htmp_pt1->Draw("");
  gr_long_90->Draw("PESAME");
  c_gr1->cd(4);
  htmp_pt1->Draw("");
  gr_long_110->Draw("PESAME");
  c_gr1->cd(5);
  htmp_pt1->Draw("");
  gr_long_130->Draw("PESAME");

  TCanvas* c_gr2 = new TCanvas("c_gr2","",1200,350);
  makeMultiPanelCanvasNew(c_gr2,5,1,0.02,0.02,0.25,0.2,0.01);
  TH2D* htmp_pt2 = new TH2D("tmp_pt2",";p^{trig}_{T}(GeV/c);Associated Yield",100,0.01,6.2,100,-0.03,0.3199);
  fixedFontHist(htmp_pt2,0.9,1.6);
  htmp_pt2->SetLineWidth(1);
  htmp_pt2->GetXaxis()->CenterTitle();
  htmp_pt2->GetYaxis()->CenterTitle();
  gr_short_2->SetMarkerColor(kRed);
  gr_short_35->SetMarkerColor(kRed);
  gr_short_90->SetMarkerColor(kRed);
  gr_short_110->SetMarkerColor(kRed);
  gr_short_130->SetMarkerColor(kRed);
  gr_short_150->SetMarkerColor(kRed);
  gr_short_2->SetLineColor(kRed);
  gr_short_35->SetLineColor(kRed);
  gr_short_90->SetLineColor(kRed);
  gr_short_110->SetLineColor(kRed);
  gr_short_130->SetLineColor(kRed);
  gr_short_150->SetLineColor(kRed);
  c_gr2->cd(1);
  htmp_pt2->Draw("");
  gr_short_2->Draw("PESAME");
  c_gr2->cd(2);
  htmp_pt2->Draw("");
  gr_short_35->Draw("PESAME");
  c_gr2->cd(3);
  htmp_pt2->Draw("");
  gr_short_90->Draw("PESAME");
  c_gr2->cd(4);
  htmp_pt2->Draw("");
  gr_short_110->Draw("PESAME");
  c_gr2->cd(5);
  htmp_pt2->Draw("");
  gr_short_130->Draw("PESAME");

  TCanvas* cmult_gr1 = new TCanvas("cmult_gr1","",430,400);
  TH2D* htmp_mult1 = new TH2D("tmp_mult1",";N;Associated Yield",500,0.01,180,100,-0.03,0.3199);
  fixedFontHist(htmp_mult1,0.9,1.6);
  htmp_mult1->SetLineWidth(1);
  htmp_mult1->GetXaxis()->CenterTitle();
  htmp_mult1->GetYaxis()->CenterTitle();  
  htmp_mult1->Draw("");
  gr_short_pttrg2->Draw("PESAME");

  TCanvas* cmult_gr2 = new TCanvas("cmult_gr2","",430,400);
  TH2D* htmp_mult2 = new TH2D("tmp_mult2",";N;Associated Yield",500,0.01,180,100,-0.003,0.0199);
  fixedFontHist(htmp_mult2,0.9,1.7);
  htmp_mult2->SetLineWidth(1);
  htmp_mult2->GetXaxis()->CenterTitle();
  htmp_mult2->GetYaxis()->CenterTitle();
  htmp_mult2->Draw("");
  gr_long_pttrg2->Draw("PESAME");

  TLine *l = new TLine(0.0,0,6.2,0);
  l->SetLineStyle(9);
  c_gr1->cd(1);
  l->Draw();
  c_gr1->cd(2);
  l->Draw();
  c_gr1->cd(3);
  l->Draw();
  c_gr1->cd(4);
  l->Draw();
  c_gr1->cd(5);
  l->Draw();
  c_gr2->cd(1);
  l->Draw();
  c_gr2->cd(2);
  l->Draw();
  c_gr2->cd(3);
  l->Draw();
  c_gr2->cd(4);
  l->Draw();
  c_gr2->cd(5);
  l->Draw();
  TLine *lmult = new TLine(0.0,0,180,0);
  lmult->SetLineStyle(9);
  cmult_gr1->cd();
  lmult->Draw();
  cmult_gr2->cd();
  lmult->Draw();

  TLatex* multrange = new TLatex();
  multrange->SetNDC();
  c_gr1->cd(1);
  multrange->DrawLatex(0.3,0.9,"N < 35");
  c_gr1->cd(2);
  multrange->DrawLatex(0.1,0.9,"35 #leq N < 90");
  c_gr1->cd(3);
  multrange->DrawLatex(0.1,0.9,"N #geq 90");
  c_gr1->cd(4);
  multrange->DrawLatex(0.1,0.9,"N #geq 110");
  c_gr1->cd(5);
  multrange->DrawLatex(0.1,0.9,"N #geq 130");
  c_gr2->cd(1);
  multrange->DrawLatex(0.3,0.9,"N < 35");
  c_gr2->cd(2);
  multrange->DrawLatex(0.1,0.9,"35 #leq N < 90");
  c_gr2->cd(3);
  multrange->DrawLatex(0.1,0.9,"N #geq 90");
  c_gr2->cd(4);
  multrange->DrawLatex(0.1,0.9,"N #geq 110");
  c_gr2->cd(5);
  multrange->DrawLatex(0.1,0.9,"N #geq 130");

  TLatex* latex_ass = new TLatex(0.5,0.82,"1<p^{assoc}_{T}<2 GeV/c");
  latex_ass->SetNDC();
  c_gr1->cd(1);  
  latex_ass->Draw();  
  c_gr2->cd(1);
  latex_ass->Draw();  
  cmult_gr1->cd();
  latex_ass->DrawLatex(0.3,0.71,"1<p^{assoc}_{T}<2 GeV/c");
  latex_ass->DrawLatex(0.3,0.78,"2<p^{trig}_{T}<3 GeV/c");
  cmult_gr2->cd();
  latex_ass->DrawLatex(0.3,0.71,"1<p^{assoc}_{T}<2 GeV/c");
  latex_ass->DrawLatex(0.3,0.78,"2<p^{trig}_{T}<3 GeV/c");

  TLatex* latex_eta = new TLatex(0.5,0.9,"2<|#Delta#eta|<4");
  latex_eta->SetNDC();
  c_gr1->cd(1);
  latex_eta->Draw();
  cmult_gr2->cd();
  latex_eta->DrawLatex(0.3,0.85,"2<|#Delta#eta|<4");
  TLatex* latex_eta1 = new TLatex(0.5,0.9,"0<|#Delta#eta|<1");
  latex_eta1->SetNDC();
  c_gr2->cd(1);
  latex_eta1->Draw();
  cmult_gr1->cd();
  latex_eta1->DrawLatex(0.3,0.85,"0<|#Delta#eta|<1");

  TLatex* cms = new TLatex();
  cms->SetNDC();
  c_gr1->cd(5);
  cms->DrawLatex(0.38,0.9,"CMS");
  c_gr2->cd(5);
  cms->DrawLatex(0.38,0.9,"CMS");
  cmult_gr1->cd();
  cms->DrawLatex(0.6,0.85,"CMS");
  cmult_gr2->cd();
  cms->DrawLatex(0.6,0.85,"CMS");

  double error=0.15;
  double errorzyam=0.0006;
  c_gr1->cd(4);
  for(int i=0;i<6;i++)
  {
    c_gr2->cd(1);
    gr_short_2->GetPoint(i,x1_short[i],y1_short[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y1_short[i]*error*y1_short[i]*error);
    DrawTick(y1_short[i],errortotal,errortotal,x1_short[i],0.005,0.225,kRed);

    c_gr2->cd(2);
    gr_short_35->GetPoint(i,x2_short[i],y2_short[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y2_short[i]*error*y2_short[i]*error);
    DrawTick(y2_short[i],errortotal,errortotal,x2_short[i],0.005,0.225,kRed);

    c_gr2->cd(3);
    gr_short_90->GetPoint(i,x4_short[i],y4_short[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y4_short[i]*error*y4_short[i]*error);
    DrawTick(y4_short[i],errortotal,errortotal,x4_short[i],0.005,0.225,kRed);

    c_gr2->cd(4);
    gr_short_110->GetPoint(i,x5_short[i],y5_short[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y5_short[i]*error*y5_short[i]*error);
    DrawTick(y5_short[i],errortotal,errortotal,x5_short[i],0.005,0.225,kRed);

    c_gr2->cd(5);
    gr_short_130->GetPoint(i,x6_short[i],y6_short[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y6_short[i]*error*y6_short[i]*error);
    DrawTick(y6_short[i],errortotal,errortotal,x6_short[i],0.005,0.225,kRed);

    c_gr1->cd(1);
    gr_long_2->GetPoint(i,x1_long[i],y1_long[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y1_long[i]*error*y1_long[i]*error);
    DrawTick(y1_long[i],errortotal,errortotal,x1_long[i],0.0002,0.225,kRed);

    c_gr1->cd(2);
    gr_long_35->GetPoint(i,x2_long[i],y2_long[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y2_long[i]*error*y2_long[i]*error);
    DrawTick(y2_long[i],errortotal,errortotal,x2_long[i],0.0002,0.225,kRed);

    c_gr1->cd(3);
    gr_long_90->GetPoint(i,x4_long[i],y4_long[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y4_long[i]*error*y4_long[i]*error);
    DrawTick(y4_long[i],errortotal,errortotal,x4_long[i],0.0002,0.225,kRed);

    c_gr1->cd(4);
    gr_long_110->GetPoint(i,x5_long[i],y5_long[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y5_long[i]*error*y5_long[i]*error);
    DrawTick(y5_long[i],errortotal,errortotal,x5_long[i],0.0002,0.225,kRed);

    c_gr1->cd(5);
    gr_long_130->GetPoint(i,x6_long[i],y6_long[i]); 
    double errortotal = sqrt(errorzyam*errorzyam+y6_long[i]*error*y6_long[i]*error);
    DrawTick(y6_long[i],errortotal,errortotal,x6_long[i],0.0002,0.225,kRed);
  }

  for(int i=0;i<8;i++) 
  {
    cmult_gr1->cd();
    double errortotal = sqrt(errorzyam*errorzyam+y_short_pt2[i]*error*y_short_pt2[i]*error);
    DrawTick(y_short_pt2[i],errortotal,errortotal,nmult[i],0.005,5,kRed);

    cmult_gr2->cd();
    double errortotal = sqrt(errorzyam*errorzyam+y_long_pt2[i]*error*y_long_pt2[i]*error);
    DrawTick(y_long_pt2[i],errortotal,errortotal,nmult[i],0.0002,5,kRed);
  }
/*
  DrawTick(y2[0],ridgeerr[0],ridgeerr[0],x2[0],0.004,0.3,2);
  DrawTick(y2[1],ridgeerr[1],ridgeerr[1],x2[1],0.004,0.3,2);
  DrawTick(y2[2],ridgeerr[2],ridgeerr[2],x2[2],0.004,0.3,2);
  DrawTick(y2[3],ridgeerr[3],ridgeerr[3],x2[3],0.004,0.3,2);

  c_gr1->cd(1);
  DrawTick(y1[0]-y2[0],jeterr[0],jeterr[0],x2[0],0.004,0.3,2);
  DrawTick(y1[1]-y2[1],jeterr[1],jeterr[1],x2[1],0.004,0.3,2);
  DrawTick(y1[2]-y2[2],jeterr[2],jeterr[2],x2[2],0.004,0.3,2);
  DrawTick(y1[3]-y2[3],jeterr[3],jeterr[3],x2[3],0.004,0.3,2);

  c_gr1->cd(1);
  TLatex* latex1 = new TLatex();
  latex1->DrawLatex(1,0.28,"Jet Region");
  c_gr1->cd(2);
  TLatex* latex2 = new TLatex();
  latex2->SetTextSize(latex2->GetTextSize()*1.15);
  latex2->DrawLatex(1,0.28,"Ridge Region");

  TLatex* cms = new TLatex();
  c_gr1->cd(2);
  cms->DrawLatex(6,0.28,"CMS Preliminary");

  SaveCanvas(c_gr1,"HI/corr","yieldvspt_HI");


  TLegend* legend = new TLegend(0.6,0.6,0.9,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(gr_90,"90<N<110","P");
  legend->AddEntry(gr_110,"110<N<130","P");
  legend->AddEntry(gr_130,"130<N<150","P");
  legend->Draw("same");
*/
//  SaveCanvas(c_gr1,"flow_pp/paper_new","yieldvspt_pp_ass1_eta2-4");
//  SaveCanvas(c_gr2,"flow_pp/paper_new","yieldvspt_pp_ass1_eta0-1");
//  SaveCanvas(cmult_gr1,"flow_pp/paper_new","yieldvsmult_pp_trg2_ass1_eta2-4");
//  SaveCanvas(cmult_gr2,"flow_pp/paper_new","yieldvsmult_pp_trg2_ass1_eta0-1");
}

compare_yieldvspt_n()
{
  gStyle->SetTextSize(18);
  gStyle->SetTextFont(43);

  TGraphErrors* gr_short_2 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",2,35,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_35 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",35,45,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_45 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",45,60,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_60 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",60,90,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_90 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER70_All_INCLEFF1TRG1v6",90,1000,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_110 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER85_All_INCLEFF1TRG1v6",110,1000,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_130 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",130,1000,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors* gr_short_150   = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",150,1000,-1,-1,-1.0,1.0,0,0,1);

  TGraphErrors* gr_long_2 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",2,35,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_35 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",35,45,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_45 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",45,60,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_60 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",60,90,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_90 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER70_All_INCLEFF1TRG1v6",90,1000,-1,-1,2.0,4.,0,0,1); 
  TGraphErrors* gr_long_110 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER85_All_INCLEFF1TRG1v6",110,1000,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_130 = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",130,1000,-1,-1,2.0,4.,0,0,1);
  TGraphErrors* gr_long_150   = compare_flow_pp_phi_multipad_pt<TGraph>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",150,1000,-1,-1,2.0,4.,0,0,1);

  double x1_short[6],y1_short[6],x1err_short[6],y1err_short[6];
  double x2_short[6],y2_short[6],x2err_short[6],y2err_short[6];
  double x3_short[6],y3_short[6],x3err_short[6],y3err_short[6];
  double x4_short[6],y4_short[6],x4err_short[6],y4err_short[6];
  double x5_short[6],y5_short[6],x5err_short[6],y5err_short[6];
  double x6_short[6],y6_short[6],x6err_short[6],y6err_short[6];
  double x7_short[6],y7_short[6],x7err_short[6],y7err_short[6];
  double x8_short[6],y8_short[6],x8err_short[6],y8err_short[6];

  double x1_long[6],y1_long[6],x1err_long[6],y1err_long[6];
  double x2_long[6],y2_long[6],x2err_long[6],y2err_long[6];
  double x3_long[6],y3_long[6],x3err_long[6],y3err_long[6];
  double x4_long[6],y4_long[6],x4err_long[6],y4err_long[6];
  double x5_long[6],y5_long[6],x5err_long[6],y5err_long[6];
  double x6_long[6],y6_long[6],x6err_long[6],y6err_long[6];
  double x7_long[6],y7_long[6],x7err_long[6],y7err_long[6];
  double x8_long[6],y8_long[6],x8err_long[6],y8err_long[6];

  double x_short_pt0[8],y_short_pt0[8],xerr_short_pt0[8],yerr_short_pt0[8];
  double x_short_pt1[8],y_short_pt1[8],xerr_short_pt1[8],yerr_short_pt1[8];
  double x_short_pt2[8],y_short_pt2[8],xerr_short_pt2[8],yerr_short_pt2[8];
  double x_short_pt3[8],y_short_pt3[8],xerr_short_pt3[8],yerr_short_pt3[8];
  double x_short_pt4[8],y_short_pt4[8],xerr_short_pt4[8],yerr_short_pt4[8];
  double x_short_pt5[8],y_short_pt5[8],xerr_short_pt5[8],yerr_short_pt5[8];

  double x_long_pt0[8],y_long_pt0[8],xerr_long_pt0[8],yerr_long_pt0[8];
  double x_long_pt1[8],y_long_pt1[8],xerr_long_pt1[8],yerr_long_pt1[8];
  double x_long_pt2[8],y_long_pt2[8],xerr_long_pt2[8],yerr_long_pt2[8];
  double x_long_pt3[8],y_long_pt3[8],xerr_long_pt3[8],yerr_long_pt3[8];
  double x_long_pt4[8],y_long_pt4[8],xerr_long_pt4[8],yerr_long_pt4[8];
  double x_long_pt5[8],y_long_pt5[8],xerr_long_pt5[8],yerr_long_pt5[8];

  double nmult[8]={12.8,38.8,50.3,67.5,98.7,118.1,138.3,156.8};
  double nmulterr[8]={0,0,0,0,0,0,0,0};

  TGraphErrors* gr_short_pttrg2 = new TGraphErrors(8);
  gr_short_2->GetPoint(2,x_short_pt2[0],y_short_pt2[0]);
  gr_short_35->GetPoint(2,x_short_pt2[1],y_short_pt2[1]);
  gr_short_45->GetPoint(2,x_short_pt2[2],y_short_pt2[2]);
  gr_short_60->GetPoint(2,x_short_pt2[3],y_short_pt2[3]);
  gr_short_90->GetPoint(2,x_short_pt2[4],y_short_pt2[4]);
  gr_short_110->GetPoint(2,x_short_pt2[5],y_short_pt2[5]);
  gr_short_130->GetPoint(2,x_short_pt2[6],y_short_pt2[6]);
  gr_short_150->GetPoint(2,x_short_pt2[7],y_short_pt2[7]);
  xerr_short_pt2[0] = gr_short_2->GetErrorX(2);
  xerr_short_pt2[1] = gr_short_35->GetErrorX(2);
  xerr_short_pt2[2] = gr_short_45->GetErrorX(2);
  xerr_short_pt2[3] = gr_short_60->GetErrorX(2);
  xerr_short_pt2[4] = gr_short_90->GetErrorX(2);
  xerr_short_pt2[5] = gr_short_110->GetErrorX(2);
  xerr_short_pt2[6] = gr_short_130->GetErrorX(2);
  xerr_short_pt2[7] = gr_short_150->GetErrorX(2);
  yerr_short_pt2[0] = gr_short_2->GetErrorY(2);
  yerr_short_pt2[1] = gr_short_35->GetErrorY(2);
  yerr_short_pt2[2] = gr_short_45->GetErrorY(2);
  yerr_short_pt2[3] = gr_short_60->GetErrorY(2);
  yerr_short_pt2[4] = gr_short_90->GetErrorY(2);
  yerr_short_pt2[5] = gr_short_110->GetErrorY(2);
  yerr_short_pt2[6] = gr_short_130->GetErrorY(2);
  yerr_short_pt2[7] = gr_short_150->GetErrorY(2);
  TGraphErrors* gr_short_pttrg2 = new TGraphErrors(8,nmult,y_short_pt2,nmulterr,yerr_short_pt2);
  gr_short_pttrg2->SetMarkerColor(kRed);
  gr_short_pttrg2->SetLineColor(kRed);
  gr_short_pttrg2->SetMarkerSize(gr_short_pttrg2->GetMarkerSize()*1.5);

  TGraphErrors* gr_long_pttrg2 = new TGraphErrors(8);
  gr_long_2->GetPoint(2,x_long_pt2[0],y_long_pt2[0]);
  gr_long_35->GetPoint(2,x_long_pt2[1],y_long_pt2[1]);
  gr_long_45->GetPoint(2,x_long_pt2[2],y_long_pt2[2]);
  gr_long_60->GetPoint(2,x_long_pt2[3],y_long_pt2[3]);
  gr_long_90->GetPoint(2,x_long_pt2[4],y_long_pt2[4]);
  gr_long_110->GetPoint(2,x_long_pt2[5],y_long_pt2[5]);
  gr_long_130->GetPoint(2,x_long_pt2[6],y_long_pt2[6]);
  gr_long_150->GetPoint(2,x_long_pt2[7],y_long_pt2[7]);
  xerr_long_pt2[0] = gr_long_2->GetErrorX(2);
  xerr_long_pt2[1] = gr_long_35->GetErrorX(2);
  xerr_long_pt2[2] = gr_long_45->GetErrorX(2);
  xerr_long_pt2[3] = gr_long_60->GetErrorX(2);
  xerr_long_pt2[4] = gr_long_90->GetErrorX(2);
  xerr_long_pt2[5] = gr_long_110->GetErrorX(2);
  xerr_long_pt2[6] = gr_long_130->GetErrorX(2);
  xerr_long_pt2[7] = gr_long_150->GetErrorX(2);
  yerr_long_pt2[0] = gr_long_2->GetErrorY(2);
  yerr_long_pt2[1] = gr_long_35->GetErrorY(2);
  yerr_long_pt2[2] = gr_long_45->GetErrorY(2);
  yerr_long_pt2[3] = gr_long_60->GetErrorY(2);
  yerr_long_pt2[4] = gr_long_90->GetErrorY(2);
  yerr_long_pt2[5] = gr_long_110->GetErrorY(2);
  yerr_long_pt2[6] = gr_long_130->GetErrorY(2);
  yerr_long_pt2[7] = gr_long_150->GetErrorY(2);
  TGraphErrors* gr_long_pttrg2 = new TGraphErrors(8,nmult,y_long_pt2,nmulterr,yerr_long_pt2);
  gr_long_pttrg2->SetMarkerColor(kRed);
  gr_long_pttrg2->SetLineColor(kRed);
  gr_long_pttrg2->SetMarkerSize(gr_long_pttrg2->GetMarkerSize()*1.5);

  TCanvas* c_gr1 = new TCanvas("c_gr1","",1200,350);
  makeMultiPanelCanvasNew(c_gr1,5,1,0.02,0.02,0.25,0.2,0.01);
  TH2D* htmp_pt1 = new TH2D("tmp_pt1",";p^{trig}_{T}(GeV/c);Associated Yield",100,0.01,6.2,100,-0.003,0.0199);  
  fixedFontHist(htmp_pt1);
  htmp_pt1->SetLineWidth(1);
  htmp_pt1->GetXaxis()->CenterTitle();
  htmp_pt1->GetYaxis()->CenterTitle();
  gr_long_2->SetMarkerColor(kRed);
  gr_long_35->SetMarkerColor(kRed);
  gr_long_90->SetMarkerColor(kRed);
  gr_long_110->SetMarkerColor(kRed);
  gr_long_130->SetMarkerColor(kRed);
  gr_long_150->SetMarkerColor(kRed);
  gr_long_2->SetLineColor(kRed);
  gr_long_35->SetLineColor(kRed);
  gr_long_90->SetLineColor(kRed);
  gr_long_110->SetLineColor(kRed);
  gr_long_130->SetLineColor(kRed);
  gr_long_150->SetLineColor(kRed);
  c_gr1->cd(1);
  htmp_pt1->Draw("");
  gr_long_2->Draw("PESAME");
  c_gr1->cd(2);
  htmp_pt1->Draw("");
  gr_long_35->Draw("PESAME");
  c_gr1->cd(3);
  htmp_pt1->Draw("");
  gr_long_90->Draw("PESAME");
  c_gr1->cd(4);
  htmp_pt1->Draw("");
  gr_long_110->Draw("PESAME");
  c_gr1->cd(5);
  htmp_pt1->Draw("");
  gr_long_130->Draw("PESAME");

  TCanvas* c_gr2 = new TCanvas("c_gr2","",1200,350);
  makeMultiPanelCanvasNew(c_gr2,5,1,0.02,0.02,0.25,0.2,0.01);
  TH2D* htmp_pt2 = new TH2D("tmp_pt2",";p^{trig}_{T}(GeV/c);Associated Yield",100,0.01,6.2,100,-0.03,0.3199);
  fixedFontHist(htmp_pt2,0.9,1.6);
  htmp_pt2->SetLineWidth(1);
  htmp_pt2->GetXaxis()->CenterTitle();
  htmp_pt2->GetYaxis()->CenterTitle();
  gr_short_2->SetMarkerColor(kRed);
  gr_short_35->SetMarkerColor(kRed);
  gr_short_90->SetMarkerColor(kRed);
  gr_short_110->SetMarkerColor(kRed);
  gr_short_130->SetMarkerColor(kRed);
  gr_short_150->SetMarkerColor(kRed);
  gr_short_2->SetLineColor(kRed);
  gr_short_35->SetLineColor(kRed);
  gr_short_90->SetLineColor(kRed);
  gr_short_110->SetLineColor(kRed);
  gr_short_130->SetLineColor(kRed);
  gr_short_150->SetLineColor(kRed);
  c_gr2->cd(1);
  htmp_pt2->Draw("");
  gr_short_2->Draw("PESAME");
  c_gr2->cd(2);
  htmp_pt2->Draw("");
  gr_short_35->Draw("PESAME");
  c_gr2->cd(3);
  htmp_pt2->Draw("");
  gr_short_90->Draw("PESAME");
  c_gr2->cd(4);
  htmp_pt2->Draw("");
  gr_short_110->Draw("PESAME");
  c_gr2->cd(5);
  htmp_pt2->Draw("");
  gr_short_130->Draw("PESAME");

  TCanvas* cmult_gr1 = new TCanvas("cmult_gr1","",430,400);
  TH2D* htmp_mult1 = new TH2D("tmp_mult1",";N;Associated Yield",500,0.01,180,100,-0.03,0.3199);
  fixedFontHist(htmp_mult1,0.9,1.6);
  htmp_mult1->SetLineWidth(1);
  htmp_mult1->GetXaxis()->CenterTitle();
  htmp_mult1->GetYaxis()->CenterTitle();  
  htmp_mult1->Draw("");
  gr_short_pttrg2->Draw("PESAME");

  TCanvas* cmult_gr2 = new TCanvas("cmult_gr2","",430,400);
  TH2D* htmp_mult2 = new TH2D("tmp_mult2",";N;Associated Yield",500,0.01,180,100,-0.003,0.0199);
  fixedFontHist(htmp_mult2,0.9,1.7);
  htmp_mult2->SetLineWidth(1);
  htmp_mult2->GetXaxis()->CenterTitle();
  htmp_mult2->GetYaxis()->CenterTitle();
  htmp_mult2->Draw("");
  gr_long_pttrg2->Draw("PESAME");

  TLine *l = new TLine(0.0,0,6.2,0);
  l->SetLineStyle(9);
  c_gr1->cd(1);
  l->Draw();
  c_gr1->cd(2);
  l->Draw();
  c_gr1->cd(3);
  l->Draw();
  c_gr1->cd(4);
  l->Draw();
  c_gr1->cd(5);
  l->Draw();
  c_gr2->cd(1);
  l->Draw();
  c_gr2->cd(2);
  l->Draw();
  c_gr2->cd(3);
  l->Draw();
  c_gr2->cd(4);
  l->Draw();
  c_gr2->cd(5);
  l->Draw();
  TLine *lmult = new TLine(0.0,0,180,0);
  lmult->SetLineStyle(9);
  cmult_gr1->cd();
  lmult->Draw();
  cmult_gr2->cd();
  lmult->Draw();

  TLatex* multrange = new TLatex();
  multrange->SetNDC();
  c_gr1->cd(1);
  multrange->DrawLatex(0.3,0.9,"N < 35");
  c_gr1->cd(2);
  multrange->DrawLatex(0.1,0.9,"35 #leq N < 90");
  c_gr1->cd(3);
  multrange->DrawLatex(0.1,0.9,"N #geq 90");
  c_gr1->cd(4);
  multrange->DrawLatex(0.1,0.9,"N #geq 110");
  c_gr1->cd(5);
  multrange->DrawLatex(0.1,0.9,"N #geq 130");
  c_gr2->cd(1);
  multrange->DrawLatex(0.3,0.9,"N < 35");
  c_gr2->cd(2);
  multrange->DrawLatex(0.1,0.9,"35 #leq N < 90");
  c_gr2->cd(3);
  multrange->DrawLatex(0.1,0.9,"N #geq 90");
  c_gr2->cd(4);
  multrange->DrawLatex(0.1,0.9,"N #geq 110");
  c_gr2->cd(5);
  multrange->DrawLatex(0.1,0.9,"N #geq 130");

  TLatex* latex_ass = new TLatex(0.5,0.82,"1<p^{assoc}_{T}<2 GeV/c");
  latex_ass->SetNDC();
  c_gr1->cd(1);  
  latex_ass->Draw();  
  c_gr2->cd(1);
  latex_ass->Draw();  
  cmult_gr1->cd();
  latex_ass->DrawLatex(0.3,0.71,"1<p^{assoc}_{T}<2 GeV/c");
  latex_ass->DrawLatex(0.3,0.78,"2<p^{trig}_{T}<3 GeV/c");
  cmult_gr2->cd();
  latex_ass->DrawLatex(0.3,0.71,"1<p^{assoc}_{T}<2 GeV/c");
  latex_ass->DrawLatex(0.3,0.78,"2<p^{trig}_{T}<3 GeV/c");

  TLatex* latex_eta = new TLatex(0.5,0.9,"2<|#Delta#eta|<4");
  latex_eta->SetNDC();
  c_gr1->cd(1);
  latex_eta->Draw();
  cmult_gr2->cd();
  latex_eta->DrawLatex(0.3,0.85,"2<|#Delta#eta|<4");
  TLatex* latex_eta1 = new TLatex(0.5,0.9,"0<|#Delta#eta|<1");
  latex_eta1->SetNDC();
  c_gr2->cd(1);
  latex_eta1->Draw();
  cmult_gr1->cd();
  latex_eta1->DrawLatex(0.3,0.85,"0<|#Delta#eta|<1");

  TLatex* cms = new TLatex();
  cms->SetNDC();
  c_gr1->cd(5);
  cms->DrawLatex(0.38,0.9,"CMS");
  c_gr2->cd(5);
  cms->DrawLatex(0.38,0.9,"CMS");
  cmult_gr1->cd();
  cms->DrawLatex(0.6,0.85,"CMS");
  cmult_gr2->cd();
  cms->DrawLatex(0.6,0.85,"CMS");

  double error=0.15;
  double errorzyam=0.0006;
  c_gr1->cd(4);
  for(int i=0;i<6;i++)
  {
    c_gr2->cd(1);
    gr_short_2->GetPoint(i,x1_short[i],y1_short[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y1_short[i]*error*y1_short[i]*error);
    DrawTick(y1_short[i],errortotal,errortotal,x1_short[i],0.005,0.225,kRed);

    c_gr2->cd(2);
    gr_short_35->GetPoint(i,x2_short[i],y2_short[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y2_short[i]*error*y2_short[i]*error);
    DrawTick(y2_short[i],errortotal,errortotal,x2_short[i],0.005,0.225,kRed);

    c_gr2->cd(3);
    gr_short_90->GetPoint(i,x4_short[i],y4_short[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y4_short[i]*error*y4_short[i]*error);
    DrawTick(y4_short[i],errortotal,errortotal,x4_short[i],0.005,0.225,kRed);

    c_gr2->cd(4);
    gr_short_110->GetPoint(i,x5_short[i],y5_short[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y5_short[i]*error*y5_short[i]*error);
    DrawTick(y5_short[i],errortotal,errortotal,x5_short[i],0.005,0.225,kRed);

    c_gr2->cd(5);
    gr_short_130->GetPoint(i,x6_short[i],y6_short[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y6_short[i]*error*y6_short[i]*error);
    DrawTick(y6_short[i],errortotal,errortotal,x6_short[i],0.005,0.225,kRed);

    c_gr1->cd(1);
    gr_long_2->GetPoint(i,x1_long[i],y1_long[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y1_long[i]*error*y1_long[i]*error);
    DrawTick(y1_long[i],errortotal,errortotal,x1_long[i],0.0002,0.225,kRed);

    c_gr1->cd(2);
    gr_long_35->GetPoint(i,x2_long[i],y2_long[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y2_long[i]*error*y2_long[i]*error);
    DrawTick(y2_long[i],errortotal,errortotal,x2_long[i],0.0002,0.225,kRed);

    c_gr1->cd(3);
    gr_long_90->GetPoint(i,x4_long[i],y4_long[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y4_long[i]*error*y4_long[i]*error);
    DrawTick(y4_long[i],errortotal,errortotal,x4_long[i],0.0002,0.225,kRed);

    c_gr1->cd(4);
    gr_long_110->GetPoint(i,x5_long[i],y5_long[i]);
    double errortotal = sqrt(errorzyam*errorzyam+y5_long[i]*error*y5_long[i]*error);
    DrawTick(y5_long[i],errortotal,errortotal,x5_long[i],0.0002,0.225,kRed);

    c_gr1->cd(5);
    gr_long_130->GetPoint(i,x6_long[i],y6_long[i]); 
    double errortotal = sqrt(errorzyam*errorzyam+y6_long[i]*error*y6_long[i]*error);
    DrawTick(y6_long[i],errortotal,errortotal,x6_long[i],0.0002,0.225,kRed);
  }

  for(int i=0;i<8;i++) 
  {
    cmult_gr1->cd();
    double errortotal = sqrt(errorzyam*errorzyam+y_short_pt2[i]*error*y_short_pt2[i]*error);
    DrawTick(y_short_pt2[i],errortotal,errortotal,nmult[i],0.005,5,kRed);

    cmult_gr2->cd();
    double errortotal = sqrt(errorzyam*errorzyam+y_long_pt2[i]*error*y_long_pt2[i]*error);
    DrawTick(y_long_pt2[i],errortotal,errortotal,nmult[i],0.0002,5,kRed);
  }
/*
  DrawTick(y2[0],ridgeerr[0],ridgeerr[0],x2[0],0.004,0.3,2);
  DrawTick(y2[1],ridgeerr[1],ridgeerr[1],x2[1],0.004,0.3,2);
  DrawTick(y2[2],ridgeerr[2],ridgeerr[2],x2[2],0.004,0.3,2);
  DrawTick(y2[3],ridgeerr[3],ridgeerr[3],x2[3],0.004,0.3,2);

  c_gr1->cd(1);
  DrawTick(y1[0]-y2[0],jeterr[0],jeterr[0],x2[0],0.004,0.3,2);
  DrawTick(y1[1]-y2[1],jeterr[1],jeterr[1],x2[1],0.004,0.3,2);
  DrawTick(y1[2]-y2[2],jeterr[2],jeterr[2],x2[2],0.004,0.3,2);
  DrawTick(y1[3]-y2[3],jeterr[3],jeterr[3],x2[3],0.004,0.3,2);

  c_gr1->cd(1);
  TLatex* latex1 = new TLatex();
  latex1->DrawLatex(1,0.28,"Jet Region");
  c_gr1->cd(2);
  TLatex* latex2 = new TLatex();
  latex2->SetTextSize(latex2->GetTextSize()*1.15);
  latex2->DrawLatex(1,0.28,"Ridge Region");

  TLatex* cms = new TLatex();
  c_gr1->cd(2);
  cms->DrawLatex(6,0.28,"CMS Preliminary");

  SaveCanvas(c_gr1,"HI/corr","yieldvspt_HI");


  TLegend* legend = new TLegend(0.6,0.6,0.9,0.9);
  legend->SetFillColor(0);
  legend->AddEntry(gr_90,"90<N<110","P");
  legend->AddEntry(gr_110,"110<N<130","P");
  legend->AddEntry(gr_130,"130<N<150","P");
  legend->Draw("same");
*/
//  SaveCanvas(c_gr1,"flow_pp/paper_new","yieldvspt_pp_ass1_eta2-4");
//  SaveCanvas(c_gr2,"flow_pp/paper_new","yieldvspt_pp_ass1_eta0-1");
//  SaveCanvas(cmult_gr1,"flow_pp/paper_new","yieldvsmult_pp_trg2_ass1_eta2-4");
//  SaveCanvas(cmult_gr2,"flow_pp/paper_new","yieldvsmult_pp_trg2_ass1_eta0-1");
}

void figure1a_paper()
{
  gStyle->SetTextSize(20);
  gStyle->SetTextFont(43);
  
  TString filename = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_INCLEFF1ONEPTBIN_nmin0_nmax35_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root";
  TH2D* h = (TH2D*)Get2DCFv3(filename.Data(),0,0);
  
  TCanvas* c = new TCanvas("c","",530,500);
  c->SetLeftMargin(0.27);
  c->SetTheta(60.839);
  c->SetPhi(38.0172);
  h->SetAxisRange(-4.,4.,"X");
  h->SetAxisRange(0.143,0.205,"Z");
  h->GetZaxis()->SetTitleOffset(h->GetZaxis()->GetTitleOffset()*1.2);
  h->GetZaxis()->SetTitleSize(h->GetZaxis()->GetTitleSize()*0.85);
  h->GetZaxis()->SetLabelSize(h->GetZaxis()->GetLabelSize()*0.8);
  h->SetTitle("");
  h->SetYTitle("#Delta#phi");
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.2);
  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*1.2);
  h->Draw("surf1 fb");

  TLatex* mult = new TLatex(0.04,0.95,"CMS pPb  #sqrt{s_{NN}} = 5.02 TeV, N^{offline}_{trk} < 35");
  mult->SetNDC();
  mult->Draw();
  TLatex* pttrg = new TLatex(0.04,0.87,"1 < p_{T} < 3 GeV/c");
  pttrg->SetNDC();
  pttrg->Draw();
//  TLatex* ptass = new TLatex(0.04,0.79,"1 < p_{T}^{assoc} < 3 GeV/c");
//  ptass->SetNDC();
//  ptass->Draw();
  TLatex* label = new TLatex(0.945,0.935,"(a)");
  label->SetNDC();
  label->Draw();

  SaveCanvas(c,"pPb/corr","corr2D_pPb_N2_pt1-3");
}

void figure1b_paper()
{
  gStyle->SetTextSize(20);
  gStyle->SetTextFont(43);

  TString filename = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_INCLEFF1ONEPTBIN_nmin110_nmax1000_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root";
  TH2D* h = (TH2D*)Get2DCFv3(filename.Data(),0,0);

  TCanvas* c = new TCanvas("c","",530,500);
  c->SetLeftMargin(0.27);
  c->SetTheta(60.839);
  c->SetPhi(38.0172);
  h->SetAxisRange(-4.,4.,"X");
  h->SetAxisRange(1.56,1.80,"Z");
  h->GetZaxis()->SetTitleOffset(h->GetZaxis()->GetTitleOffset()*1.1);
  h->GetZaxis()->SetTitleSize(h->GetZaxis()->GetTitleSize()*0.9);
  h->GetZaxis()->SetLabelSize(h->GetZaxis()->GetLabelSize()*0.85);
  h->SetTitle("");
  h->SetYTitle("#Delta#phi");
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.2);
  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*1.2);
   h->Draw("surf1 fb");

  TLatex* mult = new TLatex(0.04,0.95,"CMS pPb  #sqrt{s_{NN}} = 5.02 TeV, N^{offline}_{trk} #geq 110");
  mult->SetNDC();
  mult->Draw();
  TLatex* pttrg = new TLatex(0.04,0.87,"1 < p_{T} < 3 GeV/c");
  pttrg->SetNDC();
  pttrg->Draw();
//  TLatex* ptass = new TLatex(0.04,0.79,"1 < p_{T}^{assoc} < 3 GeV/c");
//  ptass->SetNDC();
//  ptass->Draw();

  TLatex* label = new TLatex(0.945,0.935,"(b)");
  label->SetNDC();
  label->Draw();



  SaveCanvas(c,"pPb/corr","corr2D_pPb_N110_pt1-3");
}

void figure1a_paper_preliminary()
{
  gStyle->SetTextSize(20);
  gStyle->SetTextFont(43);
  
  TString filename = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_INCLEFF1ONEPTBIN_nmin0_nmax35_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root";
  TH2D* h = (TH2D*)Get2DCFv3(filename.Data(),0,0);
  
  TCanvas* c = new TCanvas("c","",530,500);
  c->SetLeftMargin(0.27);
  c->SetTheta(60.839);
  c->SetPhi(38.0172);
  h->SetAxisRange(-4.,4.,"X");
  h->SetAxisRange(0.143,0.205,"Z");
  h->GetZaxis()->SetTitleOffset(h->GetZaxis()->GetTitleOffset()*1.2);
  h->GetZaxis()->SetTitleSize(h->GetZaxis()->GetTitleSize()*0.85);
  h->GetZaxis()->SetLabelSize(h->GetZaxis()->GetLabelSize()*0.8);
  h->SetTitle("");
  h->SetYTitle("#Delta#phi");
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.2);
  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*1.2);
  h->Draw("surf1 fb");

  TLatex* cms  = new TLatex(0.02,0.95,"CMS Preliminary");
  cms->SetNDC(); 
  cms->Draw();
  TLatex* mult = new TLatex(0.02,0.88,"pPb  #sqrt{s_{NN}} = 5.02 TeV, N^{offline}_{trk} < 35");
  mult->SetTextSize(mult->GetTextSize()*0.95);
  mult->SetNDC();
  mult->Draw();
  TLatex* pttrg = new TLatex(0.02,0.82,"1 < p_{T} < 3 GeV/c");
  pttrg->SetTextSize(pttrg->GetTextSize()*0.95);
  pttrg->SetNDC();
  pttrg->Draw();

  SaveCanvas(c,"pPb/corr","corr2D_pPb_N2_pt1-3_preliminary");
}

void figure1b_paper_preliminary()
{
  gStyle->SetTextSize(20);
  gStyle->SetTextFont(43);

  TString filename = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_INCLEFF1ONEPTBIN_nmin110_nmax1000_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root";
  TH2D* h = (TH2D*)Get2DCFv3(filename.Data(),0,0);

  TCanvas* c = new TCanvas("c","",530,500);
  c->SetLeftMargin(0.27);
  c->SetTheta(60.839);
  c->SetPhi(38.0172);
  h->SetAxisRange(-4.,4.,"X");
  h->SetAxisRange(1.56,1.80,"Z");
  h->GetZaxis()->SetTitleOffset(h->GetZaxis()->GetTitleOffset()*1.1);
  h->GetZaxis()->SetTitleSize(h->GetZaxis()->GetTitleSize()*0.9);
  h->GetZaxis()->SetLabelSize(h->GetZaxis()->GetLabelSize()*0.85);
  h->SetTitle("");
  h->SetYTitle("#Delta#phi");
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.2);
  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*1.2);
   h->Draw("surf1 fb");

  TLatex* cms  = new TLatex(0.02,0.95,"CMS Preliminary");
  cms->SetNDC();
  cms->Draw();
  TLatex* mult = new TLatex(0.02,0.88,"pPb  #sqrt{s_{NN}} = 5.02 TeV, N^{offline}_{trk} #geq 110");
  mult->SetTextSize(mult->GetTextSize()*0.95);
  mult->SetNDC();
  mult->Draw();
  TLatex* pttrg = new TLatex(0.02,0.82,"1 < p_{T} < 3 GeV/c");
  pttrg->SetTextSize(pttrg->GetTextSize()*0.95);
  pttrg->SetNDC();
  pttrg->Draw();

  SaveCanvas(c,"pPb/corr","corr2D_pPb_N110_pt1-3_preliminary");
}

void figure1c_paper_preliminary()
{
  gStyle->SetTextSize(20);
  gStyle->SetTextFont(43);

  TString filename = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLEFF1ONEPTBIN_nmin35_nmax90_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root";
  TH2D* h = (TH2D*)Get2DCFv3(filename.Data(),0,0);

  TCanvas* c = new TCanvas("c","",530,500);
  c->SetLeftMargin(0.27);
  c->SetTheta(60.839);
  c->SetPhi(38.0172);
  h->SetAxisRange(-4.,4.,"X");
  h->SetAxisRange(0.58,0.68,"Z");
  h->GetZaxis()->SetTitleOffset(h->GetZaxis()->GetTitleOffset()*1.1);
  h->GetZaxis()->SetTitleSize(h->GetZaxis()->GetTitleSize()*0.9);
  h->GetZaxis()->SetLabelSize(h->GetZaxis()->GetLabelSize()*0.85);
  h->SetTitle("");
  h->SetYTitle("#Delta#phi");
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.2);
  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*1.2);
   h->Draw("surf1 fb");

  TLatex* cms  = new TLatex(0.02,0.95,"CMS Preliminary");
  cms->SetNDC();
  cms->Draw();
  TLatex* mult = new TLatex(0.02,0.88,"pPb  #sqrt{s_{NN}} = 5.02 TeV, 35 #leq N^{offline}_{trk} < 90");
  mult->SetTextSize(mult->GetTextSize()*0.9);
  mult->SetNDC();
  mult->Draw();
  TLatex* pttrg = new TLatex(0.02,0.82,"1 < p_{T} < 3 GeV/c");
  pttrg->SetTextSize(pttrg->GetTextSize()*0.95);
  pttrg->SetNDC();
  pttrg->Draw();

  SaveCanvas(c,"pPb/corr","corr2D_pPb_N35_pt1-3_preliminary");
}

void figure1d_paper_preliminary()
{
  gStyle->SetTextSize(20);
  gStyle->SetTextFont(43);

  TString filename = "/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLEFF1ONEPTBIN_nmin90_nmax110_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root";
  TH2D* h = (TH2D*)Get2DCFv3(filename.Data(),0,0);

  TCanvas* c = new TCanvas("c","",530,500);
  c->SetLeftMargin(0.27);
  c->SetTheta(60.839);
  c->SetPhi(38.0172);
  h->SetAxisRange(-4.,4.,"X");
  h->SetAxisRange(1.15,1.30,"Z");
  h->GetZaxis()->SetTitleOffset(h->GetZaxis()->GetTitleOffset()*1.1);
  h->GetZaxis()->SetTitleSize(h->GetZaxis()->GetTitleSize()*0.9);
  h->GetZaxis()->SetLabelSize(h->GetZaxis()->GetLabelSize()*0.85);
  h->SetTitle("");
  h->SetYTitle("#Delta#phi");
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.2);
  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*1.2);
   h->Draw("surf1 fb");

  TLatex* cms  = new TLatex(0.02,0.95,"CMS Preliminary");
  cms->SetNDC();
  cms->Draw();
  TLatex* mult = new TLatex(0.02,0.88,"pPb  #sqrt{s_{NN}} = 5.02 TeV, 90 #leq N^{offline}_{trk} < 110");
  mult->SetTextSize(mult->GetTextSize()*0.85);
  mult->SetNDC();
  mult->Draw();
  TLatex* pttrg = new TLatex(0.02,0.82,"1 < p_{T} < 3 GeV/c");
  pttrg->SetTextSize(pttrg->GetTextSize()*0.95);
  pttrg->SetNDC();
  pttrg->Draw();

  SaveCanvas(c,"pPb/corr","corr2D_pPb_N90_pt1-3_preliminary");
}

void draw_single_2D(TString eventtype1="PPData_Minbias_7TeV", TString tag1="TRIGGER85_All_INCLEFF1TRG1v6", int nmin=110, int nmax=1000, int centmin=-1, int centmax=-1, int ptmin=2, int ptmax=1, double zmin=1, double zmax=1, bool IsSave=1)
{
  gStyle->SetTextSize(20);
  gStyle->SetTextFont(43);

  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,centmin,centmax);
  TH2D* h = (TH2D*)Get2DCFv3(filename.Data(),ptmin,ptmax);
  TH2D* hsignal = (TH2D*)Get2DSignal(filename.Data(),ptmin,ptmax);
  TH2D* hbackground = (TH2D*)Get2DBackground(filename.Data(),ptmin,ptmax);
  
  TCanvas* c1 = new TCanvas("c1","c1",850,400);
  c1->Divide(2,1);
  c1->cd(1);
  hsignal->Draw("surf1");
  c1->cd(2);
  hbackground->Draw("surf1");

  TCanvas* c = new TCanvas("c","c",530,500);
  c->SetLeftMargin(0.27);
  c->SetTheta(60.839);
  c->SetPhi(38.0172);
  h->SetAxisRange(-4.,4.,"X");
  h->SetAxisRange(h->GetMinimum()*zmin,h->GetMaximum()*zmax,"Z");// N<35 pPb
//  h->SetAxisRange(1.44,1.65,"Z"); // 110,1000 pPb
//  h->SetAxisRange(1.235,1.54,"Z"); // bin 5-1
  h->GetZaxis()->SetTitleOffset(h->GetZaxis()->GetTitleOffset()*1.1);
  h->GetZaxis()->SetTitleSize(h->GetZaxis()->GetTitleSize()*0.9);
  h->GetZaxis()->SetLabelSize(h->GetZaxis()->GetLabelSize()*0.85);
//  h->GetZaxis()->UnZoom();
  h->SetTitle("");
  h->Draw("surf1 fb");

  TLatex* cms = new TLatex(0.7,0.92,"CMS");
  cms->SetNDC();
//  cms->Draw();
//  TLatex* mult = new TLatex(0.055,0.925,"pp  #sqrt{s} = 7 TeV, N #geq 110");
//  TLatex* mult = new TLatex(0.055,0.925,"CMS pPb  #sqrt{s} = 5 TeV, MinBias");
  if(nmin==2 && nmax==35) TLatex* mult = new TLatex(0.055,0.925,"CMS pPb  #sqrt{s} = 5.02 TeV, N < 35");
  if(nmin==35 && nmax==90) TLatex* mult = new TLatex(0.055,0.925,"CMS pPb  #sqrt{s} = 5.02 TeV, 35 #leq N < 90");
  if(nmin==90 && nmax==110) TLatex* mult = new TLatex(0.055,0.925,"CMS pPb  #sqrt{s} = 5.02 TeV, 90 #leq N < 110");
  if(nmin==110 && nmax==1000) TLatex* mult = new TLatex(0.055,0.925,"CMS pPb  #sqrt{s} = 5.02 TeV, N #geq 110");

  mult->SetNDC();
  mult->Draw();
  TLatex* pttrg = new TLatex(0.055,0.84,"1 < p_{T}^{trig} < 2 GeV/c");
//  TLatex* pttrg = new TLatex(0.055,0.84,"1 < p_{T}^{trig} < 3 GeV/c");
//  TLatex* pttrg = new TLatex(0.055,0.84,"5 < p_{T}^{trig} < 6 GeV/c");
  pttrg->SetNDC();
  pttrg->Draw();
//  TLatex* ptass = new TLatex(0.055,0.78,"1 < p_{T}^{assoc} < 3 GeV/c");
  TLatex* ptass = new TLatex(0.055,0.78,"1 < p_{T}^{assoc} < 2 GeV/c");
  ptass->SetNDC();
  ptass->Draw();

  if(IsSave)
  {
    SaveCanvas(c,"pPb/corr",Form("corr2D_pPb_pt%d-%d_nmin%d_nmax%d",ptmin,ptmax,nmin,nmax));
  }
}

void draw_single_dPhi(TString eventtype1="PPData_Minbias_7TeV", TString tag1="TRIGGER85_All_INCLEFF1TRG1v6", int nmin=110, int nmax=1000, int centmin=-1, int centmax=-1, int ptmin=2, int ptmax=1, double detamin=2.0, double detamax=4.0, bool IsSave=1)
{
  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg-2.4-2.4_etaass-2.4-2.4_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,centmin,centmax);
  TH1D* h = (TH1D*)Get1DCFdPhiv5(filename.Data(),ptmin,ptmax,detamin,detamax);
  TF1* fitfunc=GetFitFunc_ZYAM_poor(h);
//  h_zyam=GetJetCorrFunc1D_ZYAM(h);
/*
  TH1D* h_clone = new TH1D("h_clone","",31,+PI/32-PI/2,3*PI/2-PI/32);
  TH1D* h1_clone = new TH1D("h1_clone","",31,+PI/32-PI/2,3*PI/2-PI/32);
  for(int i=1;i<=h->GetNbinsX();i++)
  {
     h_clone->SetBinContent(i,h->GetBinContent(i)); 
     h1_clone->SetBinContent(i,fitfunc->GetParameter(0)); 
  }
*/
  TGraph* gr = new TGraph(8);
  gr->SetPoint(0,0,h->GetBinContent(h->FindBin(0)));
  gr->SetPoint(1,PI/16,h->GetBinContent(h->FindBin(PI/16)));
  gr->SetPoint(2,PI/16*2,h->GetBinContent(h->FindBin(PI/16*2)));
  gr->SetPoint(3,PI/16*3,h->GetBinContent(h->FindBin(PI/16*3)));
  gr->SetPoint(4,PI/16*4,h->GetBinContent(h->FindBin(PI/16*4)));
  gr->SetPoint(5,PI/16*5,fitfunc->GetParameter(0));
  gr->SetPoint(6,0,fitfunc->GetParameter(0));
  gr->SetPoint(7,0,h->GetBinContent(h->FindBin(0)));
  gr->SetFillColor(7);

//  h_clone->SetAxisRange(-0.5,1.02,"X");
//  h_clone->SetMinimum(fitfunc->GetParameter(0));

  h->GetYaxis()->SetTitleSize(h->GetYaxis()->GetTitleSize()*0.6);
  h->GetYaxis()->SetLabelSize(h->GetYaxis()->GetLabelSize()*0.6);
  h->GetXaxis()->SetTitleSize(h->GetXaxis()->GetTitleSize()*0.6);
  h->GetXaxis()->SetLabelSize(h->GetXaxis()->GetLabelSize()*0.6);
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.4);
  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*1.4);
  h->SetMarkerColor(kRed);
  h->SetAxisRange(1.28,1.4,"Y");
  
  TCanvas* c = new TCanvas("c","",550,500);
//  h->GetYaxis()->UnZoom();
  h->Draw("PE");
  fitfunc->Draw("Lsame");
/*
  h_clone->SetFillColor(7);
  h_clone->SetLineColor(7);
  h_clone->SetLineWidth(0);
  h_clone->Draw("LF2same");
*/
  gr->Draw("Fsame");
  fitfunc->Draw("Lsame");
  h->Draw("PESAME");  

  TLine* l = new TLine(-PI/32,fitfunc->GetParameter(0),PI+PI/32,fitfunc->GetParameter(0));
  l->SetLineStyle(9);
  l->Draw("Lsame");

  if(IsSave) SaveCanvas(c,"HI/corr","corr1Ddphi_zyamillustration");
}

void draw_compare_dPhi()
{ 
  TH1D* h = (TH1D*)Get1DCFdPhiv3("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_INCLEFF1v4_nmin110_nmax1000_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root",8,8,2.0,4.0);
//  TH1D* h1 = (TH1D*)Get1DCFdPhiv3("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_INCLEFF1NVTX1_nmin110_nmax1000_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root",0,0,2.0,4.0);
  TH1D* h1 = (TH1D*)Get1DCFdPhiv3("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_INCLNonPurity_nmin110_nmax1000_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root",0,0,2.0,4.0);
 
  TCanvas* c = new TCanvas("c","c",600,500);
  h->GetYaxis()->SetTitleSize(h->GetYaxis()->GetTitleSize()*0.7);
  h->GetXaxis()->SetTitleSize(h->GetXaxis()->GetTitleSize()*0.7);
  h->GetYaxis()->SetLabelSize(h->GetYaxis()->GetLabelSize()*0.7);
  h->GetXaxis()->SetLabelSize(h->GetXaxis()->GetLabelSize()*0.7);
  h->SetAxisRange(h->GetMinimum()*0.05,h->GetMaximum()*1.1,"Y");
  h->Draw("PE");
  h1->SetMarkerStyle(24);
  h1->Draw("PESAME");

  TLegend* legend = new TLegend(0.3,0.6,0.6,0.8);
  legend->SetTextFont(42);
  legend->SetFillColor(0);
  legend->AddEntry(h,"No N_{vtx} cut","P");
  legend->AddEntry(h1,"N_{vtx}=1","P");
//  legend->AddEntry(h,"selected tracks","P");
//  legend->AddEntry(h1,"All generalTracks","P");
  legend->Draw("SAME");

  TCanvas* c1 = new TCanvas("c1","c1",600,500);
  TH1D* h_ratio = h->Clone("ratio");
  h_ratio->Divide(h1);
  h_ratio->SetAxisRange(0.999,1.006,"Y");
  h_ratio->SetYTitle("Ratio");
  h_ratio->Draw("PE");

  //SaveCanvas(c,"pPb/corr","corr1Ddphi_compare_pileup");
  SaveCanvas(c1,"pPb/corr","corr1Ddphi_compare_pileup_ratio");
}

void draw_mult_special()
{
  gStyle->SetTextSize(18);
  gStyle->SetTextFont(43);

  TH1D ***hidata_short = compare_flow_pp_phi_multipad_pt<TH1**>("PPData_Minbias_7TeV","TRIGGER85_All_INCLEFF1TRG1v6",110,1000,-1,-1,-1.0,1.0,0,0,0);
  TH1D ***hidata_mid = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","TRIGGER85_All_INCLEFF1TRG1v6",110,1000,-1,-1,1.9,4.2,0,0,0);

//  TH1D ***hidata_short = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",130,1000,-1,-1,-1,1.0,0,0,0);
//  TH1D ***hidata_mid = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",130,1000,-1,-1,1.9,4.2,0,0,0);

//  TH1D ***hidata_short = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",150,1000,-1,-1,-1,1.0,0,0,0);
//  TH1D ***hidata_mid = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","TRIGGER100_All_INCLEFF1TRG1v6",150,1000,-1,-1,1.9,4.2,0,0,0);

//  TH1D ***hidata_short = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","TRIGGER70_All_INCLEFF1TRG1v6",90,1000,-1,-1,-1,1.0,0,0,0);
//  TH1D ***hidata_mid = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","TRIGGER70_All_INCLEFF1TRG1v6",90,1000,-1,-1,1.9,4.2,0,0,0);

//  TH1D ***hidata_short = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",35,90,-1,-1,-1,1.0,0,0,0);
//  TH1D ***hidata_mid = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",35,90,-1,-1,1.9,4.2,0,0,0);

//  TH1D ***hidata_short = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",60,90,-1,-1,-1,1.0,0,0,0);
//  TH1D ***hidata_mid = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",60,90,-1,-1,1.9,4.2,0,0,0);

//  TH1D ***hidata_short = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",2,35,-1,-1,-1,1.0,0,0,0);
//  TH1D ***hidata_mid = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",2,35,-1,-1,1.9,4.2,0,0,0);

//  TH1D ***hidata_short = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",35,60,-1,-1,-1,1.0,0,0,0);
//  TH1D ***hidata_mid = compare_flow_pp_phi_multipad_pt<TH1D**>("PPData_Minbias_7TeV","MINBIAS_All_INCLEFF1TRG1v6",35,60,-1,-1,1.9,4.2,0,0,0);

  int ntrgptbins=6;
  int nassptbins=2;
  TCanvas* c = new TCanvas("c","",1100*1.1,300*1.1);
  makeMultiPanelCanvasNew(c,ntrgptbins,1,0.01,0.02,0.32,0.2,0.1,0.3);
  TCanvas* c1 = new TCanvas("c1","",1100*1.1,300*1.1);
  makeMultiPanelCanvasNew(c1,ntrgptbins,1,0.01,0.02,0.32,0.2,0.1,0.3);

/*
  TCanvas* c2 = new TCanvas("c2","",1100,300);
  makeMultiPanelCanvasNew(c2,ntrgptbins,1,0.01,0.02,0.32,0.2,0.1,0.3);
  TCanvas* c3 = new TCanvas("c3","",1100,300);
  makeMultiPanelCanvasNew(c3,ntrgptbins,1,0.01,0.02,0.32,0.2,0.1,0.3);
*/
  double ymin_short[6];
  double ymax_short[6];
  double ymin_mid[6];
  double ymax_mid[6];
  for(int itrg = 0; itrg<6; itrg++)
  {
    ymin_short[itrg]=10000;
    ymax_short[itrg]=-10000;
    ymin_mid[itrg]=10000;
    ymax_mid[itrg]=-10000;

    for(int jass = 0; jass<6; jass++)
    {
      if(ymin_short[itrg]>hidata_short[jass][itrg]->GetMinimum()) ymin_short[itrg] = hidata_short[jass][itrg]->GetMinimum();
      if(ymax_short[itrg]<hidata_short[jass][itrg]->GetMaximum()) ymax_short[itrg] = hidata_short[jass][itrg]->GetMaximum();
      if(ymin_mid[itrg]>hidata_mid[jass][itrg]->GetMinimum()) ymin_mid[itrg] = hidata_mid[jass][itrg]->GetMinimum();
      if(ymax_mid[itrg]<hidata_mid[jass][itrg]->GetMaximum()) ymax_mid[itrg] = hidata_mid[jass][itrg]->GetMaximum();
      hidata_short[jass][itrg]->SetMarkerColor(kRed);
      hidata_mid[jass][itrg]->SetMarkerColor(kRed);
      fixedFontHist1D(hidata_short[jass][itrg]);
      fixedFontHist1D(hidata_mid[jass][itrg]);
    }
    ymin_short[itrg]=ymin_short[itrg]*0.9;
    ymax_short[itrg]=ymax_short[itrg]*1.35;
    ymin_mid[itrg]=ymin_mid[itrg]*0.93;
    ymax_mid[itrg]=ymax_mid[itrg]*1.07;
  }

  for(int itrg = 0; itrg<6; itrg++)
  {
    for(int jass = 0; jass<6; jass++)
    {
      hidata_short[jass][itrg]->GetYaxis()->SetTitleSize(22);
      hidata_mid[jass][itrg]->GetYaxis()->SetTitleSize(22);
      hidata_short[jass][itrg]->GetYaxis()->SetTitleOffset(1.5);
      hidata_mid[jass][itrg]->GetYaxis()->SetTitleOffset(1.5);
/*
      hidata_short[jass][itrg]->GetXaxis()->SetTitleSize(22);
      hidata_mid[jass][itrg]->GetXaxis()->SetTitleSize(22);
      hidata_short[jass][itrg]->GetXaxis()->SetTitleOffset(1.5);
      hidata_mid[jass][itrg]->GetXaxis()->SetTitleOffset(1.5);
*/
      hidata_short[jass][itrg]->SetAxisRange(ymin_short[itrg],ymax_short[itrg],"Y");
      hidata_mid[jass][itrg]->SetAxisRange(ymin_mid[itrg],ymax_mid[itrg],"Y");
    }
  }

  TLatex* latex_short = new TLatex(0.38,0.645,"0 < |#Delta#eta| < 1");
  TLatex* latex_mid = new TLatex(0.38,0.645,"2 < |#Delta#eta| < 4");
  TLatex* latex_trg1 = new TLatex(0.38,0.8,"0.1 < p^{trig}_{T} < 1 GeV/c");
  TLatex* latex_trg2 = new TLatex(0.14,0.8,"1 < p^{trig}_{T} < 2 GeV/c");
  TLatex* latex_trg3 = new TLatex(0.14,0.8,"2 < p^{trig}_{T} < 3 GeV/c");
  TLatex* latex_trg4 = new TLatex(0.14,0.8,"3 < p^{trig}_{T} < 4 GeV/c");
  TLatex* latex_trg5 = new TLatex(0.14,0.8,"4 < p^{trig}_{T} < 5 GeV/c");
  TLatex* latex_trg6 = new TLatex(0.14,0.8,"5 < p^{trig}_{T} < 6 GeV/c");
  TLatex* latex_ass = new TLatex(0.38,0.55,"1 < p^{assoc}_{T} < 2 GeV/c");
  TLatex* latex1_ass = new TLatex(0.38,0.55,"5 < p^{assoc}_{T} < 6 GeV/c");
  latex_short->SetNDC();
  latex_mid->SetNDC();
  latex_trg1->SetNDC();
  latex_trg2->SetNDC();
  latex_trg3->SetNDC();
  latex_trg4->SetNDC();
  latex_trg5->SetNDC();
  latex_trg6->SetNDC();
  latex_ass->SetNDC();
  latex1_ass->SetNDC();

  TLegend* l = new TLegend(0.35,0.65,0.98,0.83);
  l->SetFillColor(0);
  l->AddEntry(hidata_short[0][0],"PbPb 2.76TeV, 0-5%","P"); 
//  l->AddEntry(pppythia8_short[0][0],"PYTHIA8 pp 2.76TeV","L");          
//  l->Draw("same"); 

  c->cd(1);
  hidata_short[0][1]->Draw("PE");
  c->cd(2);
  hidata_short[1][1]->Draw("PE");
  c->cd(3);
  hidata_short[2][1]->Draw("PE");
  c->cd(4);
  hidata_short[3][1]->Draw("PE");
  c->cd(5);
  hidata_short[4][1]->Draw("PE");
  c->cd(6);
  hidata_short[5][1]->Draw("PE");

  c1->cd(1);
  hidata_mid[0][1]->Draw("PE");
  c1->cd(2);
  hidata_mid[1][1]->Draw("PE");
  c1->cd(3);
  hidata_mid[2][1]->Draw("PE");
  c1->cd(4);
  hidata_mid[3][1]->Draw("PE");
  c1->cd(5);
  hidata_mid[4][1]->Draw("PE");
  c1->cd(6);
  hidata_mid[5][1]->Draw("PE");
/*
  c2->cd(1);
  hidata_short[0][5]->Draw("PE");
  c2->cd(2);
  hidata_short[1][5]->Draw("PE");
  c2->cd(3);
  hidata_short[2][5]->Draw("PE");
  c2->cd(4);
  hidata_short[3][5]->Draw("PE");
  c2->cd(5);
  hidata_short[4][5]->Draw("PE");
  c2->cd(6);
  hidata_short[5][5]->Draw("PE");
  
  c3->cd(1);
  hidata_mid[0][5]->Draw("PE");
  c3->cd(2);
  hidata_mid[1][5]->Draw("PE");
  c3->cd(3);
  hidata_mid[2][5]->Draw("PE");
  c3->cd(4);
  hidata_mid[3][5]->Draw("PE");
  c3->cd(5);
  hidata_mid[4][5]->Draw("PE");
  c3->cd(6);
  hidata_mid[5][5]->Draw("PE");
*/
  c->cd(1);
  latex_trg1->Draw("same");
//  l->Draw("same");
  latex_ass->Draw("same");
  latex_short->Draw("same");
  c->cd(2);
  latex_trg2->Draw("same");
  c->cd(3);
  latex_trg3->Draw("same");
  c->cd(4);
  latex_trg4->Draw("same");
  c->cd(5);
  latex_trg5->Draw("same");
  c->cd(6);
  latex_trg6->Draw("same");

  c1->cd(1);
  latex_trg1->Draw("same");
//  l->Draw("same");
  latex_ass->Draw("same");
  latex_mid->Draw("same");
  c1->cd(2);
  latex_trg2->Draw("same");
  c1->cd(3);
  latex_trg3->Draw("same");
  c1->cd(4);
  latex_trg4->Draw("same");
  c1->cd(5);
  latex_trg5->Draw("same");
  c1->cd(6);
  latex_trg6->Draw("same");
/*
  c2->cd(1);
  latex_trg1->Draw("same");
//  l->Draw("same");
  latex1_ass->Draw();
  c2->cd(2);
  latex_trg2->Draw("same");
  c2->cd(3);
  latex_trg3->Draw("same");
  c2->cd(4);
  latex_trg4->Draw("same");
  c2->cd(5);
  latex_trg5->Draw("same");
  c2->cd(6);
  latex_trg6->Draw("same");
  latex_short->Draw("same");

  c3->cd(1);
  latex_trg1->Draw("same");
//  l->Draw("same");
  latex1_ass->Draw();
  c3->cd(2);
  latex_trg2->Draw("same");
  c3->cd(3);
  latex_trg3->Draw("same");
  c3->cd(4);
  latex_trg4->Draw("same");
  c3->cd(5);
  latex_trg5->Draw("same");
  c3->cd(6);
  latex_trg6->Draw("same");
  latex_mid->Draw("same");
*/
  TLatex* cms = new TLatex();
  cms->SetNDC();
  c->cd(6);
  cms->DrawLatex(0.15,0.93,"CMS");
  c1->cd(6);
  cms->DrawLatex(0.15,0.93,"CMS");
/*
  c2->cd(1);
  cms->DrawLatex(0.45,0.8,"CMS Preliminary");
  c3->cd(1);
  cms->DrawLatex(0.45,0.8,"CMS Preliminary");
*/
  TLatex* multrange = new TLatex(0.33,0.93,"pp  #sqrt{s} = 7 TeV, N #geq 110");
//  TLatex* multrange = new TLatex(0.2,0.7,"2 #leq N < 35");
  multrange->SetNDC();
  c->cd(1);
  multrange->Draw();
  c1->cd(1);
  multrange->Draw();
/*
  c2->cd(6);
  multrange->Draw();
  c3->cd(6);
  multrange->Draw(); 
*/

//  SaveCanvas(c,"flow_pp/paper_new","corr1Ddphi_pp_N110_ass1_eta0-1");
//  SaveCanvas(c1,"flow_pp/paper_new","corr1Ddphi_pp_N110_ass1_eta2-4");
//  SaveCanvas(c2,"flow_pp/paper_new","corr1Ddphi_pp_N110_ass5_eta0-1");
//  SaveCanvas(c3,"flow_pp/paper_new","corr1Ddphi_pp_N110_ass5_eta2-4");
}

void draw_mult_full()
{
  gStyle->SetTextSize(15);
  gStyle->SetTextFont(43);

  TString dataname = "PAData_Minbias_5TeV";
  TString datatag = "MB_INCLv4";
  int nmin=110;
  int nmax=1000;
 
  TH1D ***hidata_short = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname.Data(),datatag.Data(),nmin,nmax,-1,-1,-1.0,1.0,0,0,0);
  TH1D ***hidata_mid = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname.Data(),datatag.Data(),nmin,nmax,-1,-1,2.0,4.0,0,0,0);
  TF1 ***fitfunc_short = compare_flow_pp_phi_multipad_pt<TF1**>(dataname.Data(),datatag.Data(),nmin,nmax,-1,-1,-1.0,1.0,0,0,3);
  TF1 ***fitfunc_mid = compare_flow_pp_phi_multipad_pt<TF1**>(dataname.Data(),datatag.Data(),nmin,nmax,-1,-1,2.0,4.0,0,0,3);
  TGraphErrors **gr_short =  compare_flow_pp_phi_multipad_pt<TGraphErrors*>(dataname.Data(),datatag.Data(),nmin,nmax,-1,-1,-1.0,1.0,0,0,1);
  TGraphErrors **gr_mid =  compare_flow_pp_phi_multipad_pt<TGraphErrors*>(dataname.Data(),datatag.Data(),nmin,nmax,-1,-1,2.0,4.0,0,0,1);

  const int ntrgptbins=7;
  const int nassptbins=7;

  TCanvas* cc = new TCanvas("cc","",1100,1100);
  makeMultiPanelCanvasNew(cc,ntrgptbins,nassptbins,0.01,0.02,0.32,0.2,0.01,0.3);
  TCanvas* cc1 = new TCanvas("cc1","",1100,1100);
  makeMultiPanelCanvasNew(cc1,ntrgptbins,nassptbins,0.01,0.02,0.32,0.2,0.01,0.3);

  double ymin_short[nassptbins];
  double ymax_short[nassptbins];
  double ymin_mid[nassptbins];
  double ymax_mid[nassptbins];

  TString ptasstitle[nassptbins] = {"0.4<p_{T}^{trig}<1 GeV/c","1<p_{T}^{trig}<2 GeV/c","2<p_{T}^{trig}<3 GeV/c","3<p_{T}^{trig}<4 GeV/c","4<p_{T}^{trig}<5 GeV/c","5<p_{T}^{trig}<6 GeV/c","6<p_{T}^{trig}<8 GeV/c"};
  TString pttrgtitle[ntrgptbins] = {"0.4<p_{T}^{assoc}<1 GeV/c","1<p_{T}^{assoc}<2 GeV/c","2<p_{T}^{assoc}<3 GeV/c","3<p_{T}^{assoc}<4 GeV/c","4<p_{T}^{assoc}<5 GeV/c","5<p_{T}^{assoc}<6 GeV/c","6<p_{T}^{trig}<8 GeV/c"};

  for(int itrg = 0; itrg<ntrgptbins; itrg++)
  {
    ymin_short[itrg]=10000;
    ymax_short[itrg]=-10000;
    ymin_mid[itrg]=10000;
    ymax_mid[itrg]=-10000;

    for(int jass = 0; jass<nassptbins; jass++)
    {
      if(ymin_short[itrg]>hidata_short[jass][itrg]->GetMinimum()) ymin_short[itrg] = hidata_short[jass][itrg]->GetMinimum();
      if(ymax_short[itrg]<hidata_short[jass][itrg]->GetMaximum()) ymax_short[itrg] = hidata_short[jass][itrg]->GetMaximum();
      if(ymin_mid[itrg]>hidata_mid[jass][itrg]->GetMinimum()) ymin_mid[itrg] = hidata_mid[jass][itrg]->GetMinimum();
      if(ymax_mid[itrg]<hidata_mid[jass][itrg]->GetMaximum()) ymax_mid[itrg] = hidata_mid[jass][itrg]->GetMaximum();
      hidata_short[jass][itrg]->SetMarkerColor(kRed);
      hidata_mid[jass][itrg]->SetMarkerColor(kRed);
      fixedFontHist1D(hidata_short[jass][itrg],3.4,7.3);
      fixedFontHist1D(hidata_mid[jass][itrg],3.4,7.3);
    }
    ymin_short[itrg]=ymin_short[itrg]*0.8;
    ymax_short[itrg]=ymax_short[itrg]*1.2;
    ymin_mid[itrg]=ymin_mid[itrg]*0.93;
    ymax_mid[itrg]=ymax_mid[itrg]*1.07;
  }

  for(int itrg = 0; itrg<ntrgptbins; itrg++)
  {
    for(int jass = 0; jass<nassptbins; jass++)
    {
      hidata_short[jass][itrg]->SetAxisRange(ymin_short[itrg],ymax_short[itrg],"Y");
      hidata_mid[jass][itrg]->SetAxisRange(ymin_mid[itrg],ymax_mid[itrg],"Y");

      cc->cd(itrg*ntrgptbins+jass+1);
      hidata_short[jass][itrg]->Draw("PE");
      fitfunc_short[jass][itrg]->SetLineColor(1);
      fitfunc_short[jass][itrg]->Draw("LSAME");
      cc1->cd(itrg*ntrgptbins+jass+1);
      hidata_mid[jass][itrg]->Draw("PE");
      fitfunc_mid[jass][itrg]->SetLineColor(1);
      fitfunc_mid[jass][itrg]->Draw("Lsame");
    }
  }

  TLatex* latex_trg[ntrgptbins]; 
  TLatex* latex_ass[nassptbins]; 
  latex_trg[0] = new TLatex(0.45,0.85,"0.4<p^{trig}_{T}<1 GeV/c");
  latex_trg[1] = new TLatex(0.2,0.85,"1<p^{trig}_{T}<2 GeV/c");
  latex_trg[2] = new TLatex(0.2,0.85,"2<p^{trig}_{T}<3 GeV/c");
  latex_trg[3] = new TLatex(0.2,0.85,"3<p^{trig}_{T}<4 GeV/c");
  latex_trg[4] = new TLatex(0.2,0.85,"4<p^{trig}_{T}<5 GeV/c");
  latex_trg[5] = new TLatex(0.2,0.85,"5<p^{trig}_{T}<6 GeV/c");
  latex_trg[6] = new TLatex(0.2,0.85,"6<p^{trig}_{T}<8 GeV/c");
  latex_ass[0] = new TLatex(0.45,0.68,"0.4<p^{assoc}_{T}<1 GeV/c");
  latex_ass[1] = new TLatex(0.45,0.68,"1<p^{assoc}_{T}<2 GeV/c");
  latex_ass[2] = new TLatex(0.45,0.68,"2<p^{assoc}_{T}<3 GeV/c");
  latex_ass[3] = new TLatex(0.45,0.68,"3<p^{assoc}_{T}<4 GeV/c");
  latex_ass[4] = new TLatex(0.45,0.68,"4<p^{assoc}_{T}<5 GeV/c");
  latex_ass[5] = new TLatex(0.45,0.68,"5<p^{assoc}_{T}<6 GeV/c");
  latex_ass[6] = new TLatex(0.45,0.68,"6<p^{assoc}_{T}<8 GeV/c");
  latex_trg[0]->SetNDC();
  latex_trg[1]->SetNDC();
  latex_trg[2]->SetNDC();
  latex_trg[3]->SetNDC();
  latex_trg[4]->SetNDC();
  latex_trg[5]->SetNDC();
  latex_trg[6]->SetNDC();
  latex_ass[0]->SetNDC();
  latex_ass[1]->SetNDC();
  latex_ass[2]->SetNDC();
  latex_ass[3]->SetNDC();
  latex_ass[4]->SetNDC();
  latex_ass[5]->SetNDC();
  latex_ass[6]->SetNDC();
  cc->cd(1);
  latex_trg[0]->Draw();
  latex_ass[0]->Draw();
  cc->cd(2);
  latex_trg[1]->Draw();
  cc->cd(3);
  latex_trg[2]->Draw();
  cc->cd(4);
  latex_trg[3]->Draw();
  cc->cd(5);
  latex_trg[4]->Draw();
  cc->cd(6);
  latex_trg[5]->Draw();
  cc->cd(7);
  latex_trg[6]->Draw();
  cc->cd(8);
  latex_ass[1]->Draw();
  cc->cd(15);
  latex_ass[2]->Draw();
  cc->cd(22);
  latex_ass[3]->Draw();
  cc->cd(29);
  latex_ass[4]->Draw();
  cc->cd(36);
  latex_ass[5]->Draw();
  cc->cd(43);
  latex_ass[6]->Draw();
  cc1->cd(1);
  latex_trg[0]->Draw();
  latex_ass[0]->Draw();
  cc1->cd(2);
  latex_trg[1]->Draw();
  cc1->cd(3);
  latex_trg[2]->Draw();
  cc1->cd(4);
  latex_trg[3]->Draw();
  cc1->cd(5);
  latex_trg[4]->Draw();
  cc1->cd(6);
  latex_trg[5]->Draw();
  cc1->cd(7);
  latex_trg[6]->Draw();
  cc1->cd(8);
  latex_ass[1]->Draw();
  cc1->cd(15);
  latex_ass[2]->Draw();
  cc1->cd(22);
  latex_ass[3]->Draw();
  cc1->cd(29);
  latex_ass[4]->Draw();
  cc1->cd(36);
  latex_ass[5]->Draw();
  cc1->cd(43);
  latex_ass[6]->Draw();

  TLatex* latex_short = new TLatex(0.5,0.1,"0<|#Delta#eta|<1");
  TLatex* latex_mid = new TLatex(0.5,0.1,"2<|#Delta#eta|<4");
  latex_short->SetNDC();
  latex_mid->SetNDC();
  cc->cd(1);
  latex_short->Draw();
  cc1->cd(1);
  latex_mid->Draw();

  TLatex* cms = new TLatex(0.5,0.3,"CMS");
  cms->SetNDC();
  cc->cd(1);
  cms->Draw();
  cc1->cd(1);
  cms->Draw();

  TLatex* multrange = new TLatex(0.5,0.2,"105 #geq N < 125");
//  TLatex* multrange = new TLatex(0.2,0.7,"45 #leq N < 60");
  multrange->SetNDC();
  cc->cd(1);
  multrange->Draw();
  cc1->cd(1);
  multrange->Draw();

  TCanvas* c_gr = new TCanvas("c_gr","",550,500);
  TH2D* htmp = new TH2D("tmp",";p^{trig}_{T}(GeV/c);Associated Yield",100,0.01,8.2,100,-0.003,0.0199);  
  htmp->SetLineWidth(1);
  htmp->GetXaxis()->CenterTitle();
  htmp->GetYaxis()->CenterTitle();
  htmp->Draw();
  gr_mid[0]->SetMarkerColor(1);
  gr_mid[1]->SetMarkerColor(2);
  gr_mid[2]->SetMarkerColor(3);
  gr_mid[3]->SetMarkerColor(4);
  gr_mid[4]->SetMarkerColor(5);
//  gr_mid[0]->Draw("PESAME");
  gr_mid[1]->Draw("PESAME");
//  gr_mid[2]->Draw("PESAME");
//  gr_mid[3]->Draw("PESAME");
//  gr_mid[4]->Draw("PESAME");

//  SaveCanvas(cc,"flow_pp/paper_new","corr1Ddphi_pp_N110_fullmatrix_eta0-1");
//  SaveCanvas(cc1,"flow_pp/paper_new","corr1Ddphi_pp_N110_fullmatrix_eta2-4");
//  SaveCanvas(c_gr,"pPb/corr","yieldvspt_pp_N110_ass1_ridge");
}

void pileup()
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_INCLEFF1v4_nmin110_nmax1000_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TH1D* hnvtx = (TH1D*)f->Get("nvtx");
  TH1D* hvtxsep = (TH1D*)f->Get("xyzvtxsepmin");
  TH2D* hnmaxvsnsec = (TH2D*)f->Get("multmaxvssec");

  TCanvas* c = new TCanvas("c","c",800,400);
  c->Divide(2,1);
  c->cd(1);
  c->GetPad(1)->SetLogy();
  hnvtx->SetAxisRange(0,6,"X");
  hnvtx->Draw("PE");
  c->cd(2);
  hvtxsep->SetAxisRange(0,2,"X");
  hvtxsep->Draw("PE");

  TCanvas* c1 = new TCanvas("c1","c1",500,450);  
  c1->SetLogz();
  hnmaxvsnsec->SetAxisRange(0,200,"X");
  hnmaxvsnsec->SetAxisRange(0,200,"Y");
  hnmaxvsnsec->Draw("colz");

  SaveCanvas(c,"pPb/corr","pileup_pPb_nvtx");
  SaveCanvas(c1,"pPb/corr","pileup_pPb_nmaxvsnsec");
}

void drawSystBox(TGraph* gr, double percent, double constant, int fillcolor=TColor::GetColor("#ffff00"), double xwidth=0.3, double xshift=0, bool flag=true)
{   
  TBox* box;
  for(int n=0;n<gr->GetN();n++)
  {
    double x,y;
    gr->GetPoint(n,x,y);

    if(x>260 && flag) percent=1.075;
    double yerr = y*percent+constant; 
 
    box = new TBox(x+xshift-xwidth,y-fabs(y-yerr),x+xwidth,y+fabs(y-yerr));
    box->SetFillColor(fillcolor);
    box->SetLineWidth(0);
    box->Draw("Fsame");
  }
}

