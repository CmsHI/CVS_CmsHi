#include "/net/hisrv0001/home/davidlw/useful_macros/CF.C"
#include "/net/hisrv0001/home/davidlw/useful_macros/GetMultiJetCorrFunc.C"

void drawCorr_2D(TString eventtype1="PPData_Minbias_7TeV", TString tag1="TRIGGER85_All_INCLEFF1TRG1v6", int nmin=110, int nmax=1000, int centmin=-1, int centmax=-1, int ptmin=2, int ptmax=1, double zmin=0.95, double zmax=1.05, double etatrgmin=-2.4, double etatrgmax=2.4, double etaassmin=-2.4, double etaassmax=2.4)
{
  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,etatrgmin,etatrgmax,etaassmin,etaassmax,centmin,centmax);
  TH2D* h = (TH2D*)Get2DCFv3(filename.Data(),ptmin,ptmax);

  h->SetAxisRange(h->GetMinimum()*zmin,h->GetMaximum()*zmax,"Z");

  TCanvas* c = new TCanvas("c","",550,500);
  c->SetBottomMargin(0.08);
  c->SetTheta(60.839);
  c->SetPhi(38.0172);
  h->SetAxisRange(-4.5,4.5,"X");
  h->GetXaxis()->SetTitleSize(h->GetXaxis()->GetTitleSize()*1.4);
  h->GetYaxis()->SetTitleSize(h->GetYaxis()->GetTitleSize()*1.4);
  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*0.85);
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*0.85);
  h->Draw("surf1 fb");

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.8*latex->GetTextSize());
//  latex->DrawLatex(0.045,0.95,Form("CMS pPb  #sqrt{s_{NN}} = 5.02 TeV, %d #leq N < %d",nmin,nmax));
  latex->DrawLatex(0.045,0.95,Form("CMS PbPb  #sqrt{s_{NN}} = 2.76 TeV, %d #leq N < %d",nmin,nmax));
  latex->DrawLatex(0.045,0.86,"1 < p_{T}^{trig} < 3 GeV/c");
  latex->DrawLatex(0.045,0.8,"1 < p_{T}^{assoc} < 3 GeV/c");

//  SaveCanvas(c,"pPb/corr",Form("corr2D_pPbNew_pt%d-%d_nmin%d_nmax%d",ptmin,ptmax,nmin,nmax));
  SaveCanvas(c,"pPb/corr",Form("corr2D_PbPb_pt%d-%d_nmin%d_nmax%d",ptmin,ptmax,nmin,nmax));

  TH2D* h_signal = (TH2D*)Get2DSignal(filename.Data(),ptmin,ptmax);
  TH2D* h_background = (TH2D*)Get2DBackground(filename.Data(),ptmin,ptmax);
  
  TCanvas* c_signal = new TCanvas("c_signal","c_signal",550,500);
  h_signal->Draw("surf1");
  TCanvas* c_background = new TCanvas("c_background","c_background",550,500);
  h_background->Draw("surf1");

  TFile* fout = new TFile(Form("results/results_2D_N%d%d_eff.root",nmin,nmax),"recreate");
//  TFile* fout = new TFile(Form("results/results_2D_HF170_noeff.root",nmin,nmax),"recreate");
  h->Write();
  h_signal->Write();
  h_background->Write();
  fout->Close();
}

void drawCorr_dphi(TString eventtype1="PPData_Minbias_7TeV", TString tag1="TRIGGER85_All_INCLEFF1TRG1v6", int nmin=110, int nmax=1000, int centmin=-1, int centmax=-1, int ptmin=2, int ptmax=1, double detamin=2.0, double detamax=4.0, double ymin=0.95, double ymax=1.05, double etatrgmin=-2.4, double etatrgmax=2.4, double etaassmin=-2.4, double etaassmax=2.4)
{ 
  TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin,nmax,etatrgmin,etatrgmax,etaassmin,etaassmax,centmin,centmax);
  TH1D* h = (TH1D*)Get1DCFdPhiv3(filename.Data(),ptmin,ptmax,detamin,detamax);

/*  
  h->GetYaxis()->SetTitleSize(h->GetYaxis()->GetTitleSize()*0.6);
  h->GetYaxis()->SetLabelSize(h->GetYaxis()->GetLabelSize()*0.6);
  h->GetXaxis()->SetTitleSize(h->GetXaxis()->GetTitleSize()*0.6);
  h->GetXaxis()->SetLabelSize(h->GetXaxis()->GetLabelSize()*0.6);
  h->GetYaxis()->SetTitleOffset(h->GetYaxis()->GetTitleOffset()*1.4);
  h->GetXaxis()->SetTitleOffset(h->GetXaxis()->GetTitleOffset()*1.4);
  h->SetMarkerColor(kRed);
*/
  h->SetAxisRange(h->GetMinimum()*ymin,h->GetMaximum()*ymax,"Y");

  TCanvas* c = new TCanvas("c","",550,500);
  h->Draw("PE");
}

void compareCorr_dphi(double ymin=0.95, double ymax=1.05)
{
  TString eventtype1="PAData_Minbias_5TeV";
  TString tag1="HM_PromptRecoNew_All_INCLEFF1ONEPTBINv1VZ03";
  int nmin1=300;
  int nmax1=350;
  int centmin1=-1;
  int centmax1=-1;
  double etatrgmin1=-2.4;
  double etatrgmax1=2.4;
  double etaassmin1=-2.4;
  double etaassmax1=2.4; 

  TString eventtype2="PAData_Minbias_5TeV";
  TString tag2="HM_PromptRecoNew_All_INCLEFF1ONEPTBINv1VZ315";
  int nmin2=300; 
  int nmax2=350;
  int centmin2=-1; 
  int centmax2=-1;
  double etatrgmin2=-2.4;
  double etatrgmax2=2.4;
  double etaassmin2=-2.4;
  double etaassmax2=2.4;

  TString filename1 = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",eventtype1.Data(),eventtype1.Data(),tag1.Data(),nmin1,nmax1,etatrgmin1,etatrgmax1,etaassmin1,etaassmax1,centmin1,centmax1);
  TString filename2 = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",eventtype2.Data(),eventtype2.Data(),tag2.Data(),nmin2,nmax2,etatrgmin2,etatrgmax2,etaassmin2,etaassmax2,centmin2,centmax2);

  int ptmin1=0;
  int ptmax1=0;
  double detamin1=-1;
  double detamax1=1;

  int ptmin2=0;
  int ptmax2=0;
  double detamin2=-1;
  double detamax2=1;

  TH1D* h1 = (TH1D*)Get1DCFdPhiv3(filename1.Data(),ptmin1,ptmax1,detamin1,detamax1);
  TH1D* h1_zyam=GetJetCorrFunc1D_ZYAM_pp(h1);
  h1_zyam->SetAxisRange(h1_zyam->GetMinimum()*ymin,h1_zyam->GetMaximum()*ymax,"Y");

  TH1D* h2 = (TH1D*)Get1DCFdPhiv3(filename2.Data(),ptmin2,ptmax2,detamin2,detamax2);
  TH1D* h2_zyam=GetJetCorrFunc1D_ZYAM_pp(h2);
  h2_zyam->SetAxisRange(h2_zyam->GetMinimum()*ymin,h2_zyam->GetMaximum()*ymax,"Y");

  TCanvas* c = new TCanvas("c","",550,500);
  h1_zyam->Draw("PE");
  h2_zyam->SetMarkerStyle(24);
  h2_zyam->Draw("PESAME");
}

