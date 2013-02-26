#include <fstream>

void makeMultiCorr()
{
  const int ntrgptbins=5;
  const int nassptbins=5;

  TString dataname2 = "HIData_Minbias_2760GeV";
  TString datatag2 = "PPRereco_INCLEFF1v3";
  int nmin2=220;
  int nmax2=260;

  TString dataname = "PAData_Minbias_5TeV";
  TString datatag = "HM_PromptRecoNew_All_INCLEFF1v3";
  int nmin=220;
  int nmax=260;

/*
  TString dataname3 = "PPData_Minbias_7TeV";
  TString datatag3 = "TRIGGER85_All_INCLEFF1TRG1v6";
  int nmin3=110;
  int nmax3=1000;
*/
  TString dataname3 = "PAData_Minbias_5TeV";
  TString datatag3 = "HM_Express_INCLEFF1v3";
  int nmin3=120;
  int nmax3=150;

  TH1D ***hdata_long = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname.Data(),datatag.Data(),nmin,nmax,-1,-1,2.0,4.0,ntrgptbins,nassptbins,-2.4,2.4,-2.4,2.4);
  TH1D ***hdata_short = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname.Data(),datatag.Data(),nmin,nmax,-1,-1,-1.0,1.0,ntrgptbins,nassptbins,-2.4,2.4,-2.4,2.4);
  TH1D* hdata_long_zyam[ntrgptbins][nassptbins];
  TH1D* hdata_short_zyam[ntrgptbins][nassptbins];

  TH1D ***hdata2_long = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname2.Data(),datatag2.Data(),nmin2,nmax2,-1,-1,2.0,4.0,ntrgptbins,nassptbins,-2.4,2.4,-2.4,2.4);
  TH1D ***hdata2_short = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname2.Data(),datatag2.Data(),nmin2,nmax2,-1,-1,-1.0,1.0,ntrgptbins,nassptbins,-2.4,2.4,-2.4,2.4);
  TH1D* hdata2_long_zyam[ntrgptbins][nassptbins];
  TH1D* hdata2_short_zyam[ntrgptbins][nassptbins];

  TH1D ***hdata3 = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname3.Data(),datatag3.Data(),nmin3,nmax3,-1,-1,2.0,4.0,ntrgptbins,nassptbins,-2.4,2.4,-2.4,2.4);
  TH1D* hdata3_zyam[ntrgptbins][nassptbins];

  TCanvas* cc = new TCanvas("cc","",250*ntrgptbins,230*2);
  makeMultiPanelCanvas(cc,ntrgptbins,2,0.01,0.02,0.25,0.15,0.14);
  TCanvas* cc1 = new TCanvas("cc1","",250*ntrgptbins,230*2);
  makeMultiPanelCanvas(cc1,ntrgptbins,2,0.01,0.02,0.25,0.15,0.14);

    int jass=1;
    for(int itrg = 0; itrg<ntrgptbins; itrg++)
    {
      cc->cd(itrg+1);
      hdata_short[itrg][jass]->SetMarkerColor(2);     
      hdata_short[itrg][jass]->Draw("PE");
      hdata2_short[itrg][jass]->SetMarkerColor(kBlue);
      hdata2_short[itrg][jass]->SetMarkerStyle(20);
      hdata2_short[itrg][jass]->Draw("PESAME");
      cc->cd(ntrgptbins+itrg+1);
      hdata_long[itrg][jass]->SetMarkerColor(2);
      hdata_long[itrg][jass]->Draw("PE");
      hdata2_long[itrg][jass]->SetMarkerColor(kBlue);
      hdata2_long[itrg][jass]->SetMarkerStyle(20);
      hdata2_long[itrg][jass]->Draw("PESAME");
      cc1->cd(itrg+1);
      hdata2_short_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM_pp(hdata2_short[itrg][jass]);
      hdata2_short_zyam[itrg][jass]->SetAxisRange(-0.07,0.85,"Y");
      hdata2_short_zyam[itrg][jass]->SetMarkerStyle(21);
      hdata2_short_zyam[itrg][jass]->SetYTitle("#frac{1}{N_{trig}} #frac{dN^{pair}}{d#Delta#phi} - C_{ZYAM}");
      fixedFontHist1D(hdata2_short_zyam[itrg][jass]);
      hdata2_short_zyam[itrg][jass]->Draw("PE");
      hdata_short_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM_pp(hdata_short[itrg][jass]);
      hdata_short_zyam[itrg][jass]->SetMarkerStyle(20);
      hdata_short_zyam[itrg][jass]->Draw("PESAME");   
      cc1->cd(ntrgptbins+itrg+1);
      hdata2_long_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM_pp(hdata2_long[itrg][jass]);
      hdata2_long_zyam[itrg][jass]->SetAxisRange(-0.07,0.39,"Y");
      hdata2_long_zyam[itrg][jass]->SetMarkerStyle(21);
      hdata2_long_zyam[itrg][jass]->SetYTitle("#frac{1}{N_{trig}} #frac{dN^{pair}}{d#Delta#phi} - C_{ZYAM}");
      fixedFontHist1D(hdata2_long_zyam[itrg][jass]);
      hdata2_long_zyam[itrg][jass]->Draw("PE");
      hdata_long_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM_pp(hdata_long[itrg][jass]);
      hdata_long_zyam[itrg][jass]->SetMarkerStyle(20);
      hdata_long_zyam[itrg][jass]->Draw("PESAME"); 
    }

    cc1->cd(1);
    TLatex* cms = new TLatex();
    cms->SetNDC();
    cms->SetTextSize(1.6*cms->GetTextSize());
    cms->DrawLatex(0.3,0.75,"CMS");
    cms->DrawLatex(0.3,0.55,Form("%d #leq N_{trk}^{offline} < %d",nmin,nmax));
    cms->DrawLatex(0.3,0.44,"1 < p_{T}^{assoc} < 2 GeV/c");
    cms->DrawLatex(0.5,0.75,"Jet region (|#Delta#eta|<1)");
    cc1->cd(6);
    cms->DrawLatex(0.44,0.87,"Ridge region (|#Delta#eta|>2)");

    TLatex* latex_pt = new TLatex();
    latex_pt->SetNDC();
    latex_pt->SetTextSize(1.6*latex_pt->GetTextSize());    
    cc1->cd(1);
    latex_pt->DrawLatex(0.4,0.905,"0.1 < p_{T}^{trig} < 1 GeV/c");
    cc1->cd(2);
    latex_pt->DrawLatex(0.2,0.905,"1 < p_{T}^{trig} < 2 GeV/c");
    cc1->cd(3);
    latex_pt->DrawLatex(0.2,0.905,"2 < p_{T}^{trig} < 4 GeV/c");
    cc1->cd(4);
    latex_pt->DrawLatex(0.2,0.905,"4 < p_{T}^{trig} < 6 GeV/c");
    cc1->cd(5);
    latex_pt->DrawLatex(0.18,0.905,"6 < p_{T}^{trig} < 12 GeV/c");

    cc1->cd(2);
    TLegend* legend = new TLegend(0.0,0.55,0.9,0.8);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->AddEntry(hdata_long_zyam[0][jass],"pPb  #sqrt{s_{NN}} = 5.02 TeV","P");
    legend->AddEntry(hdata2_long_zyam[0][jass],"PbPb  #sqrt{s_{NN}} = 2.76 TeV","P");
    legend->Draw("same");

  SaveCanvas(cc1,"pPb/corr","corr1D_pPbvsPbPb_N220260_paper");
}


void yieldvspt()
{
  const int nptbins = 12;
/*
  TString dataname = "PAData_Minbias_5TeV";
  TString datatag = "HM_PromptRecoNew_Reverse_INCLEFF1v6";
*/

  TString dataname = "PAData_Minbias_5TeV";
  TString datatag = "HM_PromptRecoNew_All_INCLEFF1v61";

/*
  TString dataname = "HIData_Minbias_2760GeV";
  TString datatag = "PPRereco_INCLEFF1v61";
*/
  TH1D *hdata_short[nptbins];
  TH1D *hdata_short_zyam[nptbins];
  TH1D *hdata_long[nptbins];
  TH1D *hdata_long_zyam[nptbins];
  TF1  *fitfunc_short[nptbins];
  TF1  *fitfunc_long[nptbins];
  TF1  *fitfunc_vn[nptbins];

  int nmultmin=220;
  int nmultmax=260;
  int ptbin_ref=0;
  TGraphErrors* gr_yield_short_pt = new TGraphErrors(nptbins);
  TGraphErrors* gr_yield_long_pt = new TGraphErrors(nptbins);

  TString filename_ref = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",dataname.Data(),dataname.Data(),"HM_PromptRecoNew_All_INCLEFF1ONEPTBINv11",nmultmin,nmultmax,-1,-1,-2.4,2.4,-2.4,2.4);
//  TString filename_ref = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",dataname.Data(),dataname.Data(),"HM_PromptRecoNew_All_INCLEFF1ONEPTBINv1",nmultmin,nmultmax,-1,-1,-2.4,2.4,-2.4,2.4);
//  TString filename_ref = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",dataname.Data(),dataname.Data(),"HM_PromptRecoNew_INCLEFF1ONEPTBINv1NVTX1",nmultmin,nmultmax,-1,-1,-2.4,2.4,-2.4,2.4);
//  TString filename_ref = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",dataname.Data(),dataname.Data(),"HM_PromptRecoNew_INCLEFF1ONEPTBINv1",nmultmin,nmultmax,-1,-1,-2.4,2.4,-2.4,2.4);
//  TString filename_ref = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",dataname.Data(),dataname.Data(),"PPRereco_INCLEFF1ONEPTBINv1",nmultmin,nmultmax,-1,-1,-2.4,2.4,-2.4,2.4);
//  TString filename_ref = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",dataname.Data(),dataname.Data(),"PPRereco_INCLEFF1ONEPTBINv11",nmultmin,nmultmax,-1,-1,-2.4,2.4,-2.4,2.4);

  hdata_long_ref = (TH1D*)Get1DCFdPhiv3(filename_ref.Data(),0,0,2,4);
  TF1* fitfunc_vn_ref = FitVnFunc(hdata_long_ref);
  double v2_ref = sqrt(fabs(fitfunc_vn_ref->GetParameter(2)));
  double v3_ref = sqrt(fabs(fitfunc_vn_ref->GetParameter(3)));
  double v2_ref_err = fitfunc_vn_ref->GetParError(2)/fitfunc_vn_ref->GetParameter(2)*v2_ref;
  double v3_ref_err = fitfunc_vn_ref->GetParError(3)/fitfunc_vn_ref->GetParameter(3)*v3_ref;

  double v2[nptbins];
  double v3[nptbins];
  double v2_err[nptbins];
  double v3_err[nptbins];
  double ptbins[nptbins];

  for(int ibin = 0; ibin<nptbins; ibin++)
  {
    TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",dataname.Data(),dataname.Data(),datatag.Data(),nmultmin,nmultmax,-1,-1,-2.4,2.4,-2.4,2.4);
    hdata_short[ibin] = (TH1D*)Get1DCFdPhiv3(filename.Data(),ibin,ptbin_ref,-1.0,1.0);
    hdata_long[ibin] = (TH1D*)Get1DCFdPhiv3(filename.Data(),ibin,ptbin_ref,2,4);
    fitfunc_short[ibin]=GetFitFunc_ZYAM_pp(hdata_short[ibin]);
    fitfunc_long[ibin]=GetFitFunc_ZYAM_pp(hdata_long[ibin]);
    fitfunc_vn[ibin] = FitVnFunc(hdata_long[ibin]);
    hdata_short_zyam[ibin]=GetJetCorrFunc1D_ZYAM_pp(hdata_short[ibin]);
    hdata_long_zyam[ibin]=GetJetCorrFunc1D_ZYAM_pp(hdata_long[ibin]);
    TH1D* hpt = (TH1D*)GetHist(filename,Form("ptcorr_signal_trg_%d",ibin));

    double yielderror_long=0;
    double yield_long = hdata_long_zyam[ibin]->IntegralAndError(hdata_long_zyam[ibin]->FindBin(-1.2),hdata_long_zyam[ibin]->FindBin(1.2),yielderror_long,"width");//zyamminimumscale;
 //   yielderror_short=yielderror_short/2;
    yielderror_long=sqrt(yielderror_long*yielderror_long+fitfunc_long[ibin]->GetParError(0)*fitfunc_long[ibin]->GetParError(0)*2.4*2.4);
    gr_yield_long_pt->SetPoint(ibin,hpt->GetMean(),yield_long);
    gr_yield_long_pt->SetPointError(ibin,0,yielderror_long);

    double yielderror_short=0;
    double yield_short = hdata_short_zyam[ibin]->IntegralAndError(hdata_short_zyam[ibin]->FindBin(-1.2),hdata_short_zyam[ibin]->FindBin(1.2),yielderror_short,"width");//zyamminimumscale;
 //   yielderror_short=yielderror_short/2;
    yielderror_short=sqrt(yielderror_short*yielderror_short+fitfunc_short[ibin]->GetParError(0)*fitfunc_short[ibin]->GetParError(0)*2.4*2.4);
    gr_yield_short_pt->SetPoint(ibin,hpt->GetMean(),yield_short-yield_long);
    gr_yield_short_pt->SetPointError(ibin,0,sqrt(yielderror_short*yielderror_short+yielderror_long*yielderror_long));
//    gr_yield_short_pt->SetPoint(ibin,hpt->GetMean(),yield_short);
//    gr_yield_short_pt->SetPointError(ibin,0,yielderror_short);

    ptbins[ibin]=hpt->GetMean();

// Fourier decomposition
    v2[ibin] = fitfunc_vn[ibin]->GetParameter(2)/v2_ref;
    v3[ibin] = fitfunc_vn[ibin]->GetParameter(3)/v3_ref;
    v2_err[ibin] = sqrt((fitfunc_vn[ibin]->GetParError(2)/fitfunc_vn[ibin]->GetParameter(2))**2+(v2_ref_err/v2_ref)**2)*v2[ibin];
    v3_err[ibin] = sqrt((fitfunc_vn[ibin]->GetParError(3)/fitfunc_vn[ibin]->GetParameter(3))**2+(v3_ref_err/v3_ref)**2)*v3[ibin];
  }

  TCanvas* c1D_short = new TCanvas("c1D_short","c1D_short",800,800);
  c1D_short->Divide(4,4);
  TCanvas* c1D_long = new TCanvas("c1D_long","c1D_long",800,800);
  c1D_long->Divide(4,4);

  for(int i=1;i<=nptbins;i++) 
  {
    c1D_short->cd(i);
    hdata_short_zyam[i-1]->Draw("PE");
    fitfunc_short[i-1]->SetLineColor(2);
    fitfunc_short[i-1]->Draw("Lsame");
    c1D_long->cd(i);
    hdata_long_zyam[i-1]->Draw("PE");
    fitfunc_long[i-1]->SetLineColor(2);
    fitfunc_long[i-1]->Draw("Lsame");
  }

  ofstream fcout(Form("data/v2v3vspt_%s_N%d%d_all_ptass033.txt",dataname.Data(),nmultmin,nmultmax));
//  ofstream fcout(Form("data/v2v3vspt_%s_N%d%d_Trigger160.txt",dataname.Data(),nmultmin,nmultmax));
//  ofstream fcout(Form("data/v2v3vspt_%s_N%d%d_nvtx1.txt",dataname.Data(),nmultmin,nmultmax));
//  ofstream fcout(Form("data/v2v3vspt_%s_N%d%d.txt",dataname.Data(),nmultmin,nmultmax));
  fcout << "N    v_2    v_2 err." << endl;
  for(int i = 0; i<nptbins; i++) fcout << ptbins[i] << " "<< v2[i] << " " << v2_err[i] <<endl;
  fcout<<endl<<endl;
  fcout << "N    v_3    v_3 err." << endl;
  for(int i = 0; i<nptbins; i++) fcout << ptbins[i] << " "<< v3[i] << " " << v3_err[i] <<endl;
  fcout<<endl<<endl; 
return;
  TFile* fout = new TFile(Form("results/pPb_yieldvspt_N%d%d_all.root",nmultmin,nmultmax),"recreate");
//  TFile* fout = new TFile(Form("results/pPb_yieldvspt_N%d%d_Trigger160.root",nmultmin,nmultmax),"recreate");
//  TFile* fout = new TFile(Form("results/pPb_yieldvspt_N%d%d_nvtx1.root",nmultmin,nmultmax),"recreate");
//  TFile* fout = new TFile(Form("results/pPb_yieldvspt_N%d%d.root",nmultmin,nmultmax),"recreate");
//  TFile* fout = new TFile(Form("results/PbPb_yieldvspt_N%d%d_all.root",nmultmin,nmultmax),"recreate");
  gr_yield_short_pt->SetName("gr_yield_short_pt");
  gr_yield_long_pt->SetName("gr_yield_long_pt");
  gr_yield_short_pt->Write();
  gr_yield_long_pt->Write();
  fout->Close();
}

void yieldvsn()
{

  const int nmultbin = 14;
  TString dataname = "PAData_Minbias_5TeV";
  TString datatag[nmultbin] = {"MBCent","MBCent","MBCent","MBCent","MBCent","MBCent","MBCent","HFHMCent","HFHMCent","HFHMCent","HFHMCent","HFHMCent","HFHMCent","HFHMCent"};
  for(int i=0;i<nmultbin;i++) 
    datatag[i].Append("_PromptRecoNew_Reverse_INCLEFF1ONEPTBINv1");
  int nmin[nmultbin] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  int nmax[nmultbin] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  int centmin[nmultbin] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
  int centmax[nmultbin] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};

/*
  const int nmultbin = 10;
  TString dataname = "PAData_Minbias_5TeV";
  TString datatag[nmultbin] = {"MB","MB","MB","MB","HM","HM","HM","HM","HM","HM"};
  for(int i=0;i<nmultbin;i++) 
    if(i<4) datatag[i].Append("_PromptRecoNew_All_INCLEFF1ONEPTBINv1Tight");
    else datatag[i].Append("_PromptRecoNew_INCLEFF1ONEPTBINv1Tight");
  int nmin[nmultbin] = {0,20,50,80,120,150,185,220,260,300};
  int nmax[nmultbin] = {20,50,80,120,150,185,220,260,300,350};
*/
/*
  const int nmultbin = 1;
  TString dataname = "PAData_Minbias_5TeV";
  TString datatag[nmultbin] = {"HFHM"};
  for(int i=0;i<nmultbin;i++) 
    datatag[i].Append("_PromptRecoNew_Reverse_INCLEFF1ONEPTBINv1");       
  int nmin[nmultbin] = {-1};
  int nmax[nmultbin] = {-1};
*/
/*
  const int nmultbin = 6;
  TString dataname = "PAData_Minbias_5TeV";
  TString datatag[nmultbin] = {"HM","HM","HM","HM","HM","HM220"};
  for(int i=0;i<nmultbin;i++) 
    if(i==(nmultbin-1)) datatag[i].Append("_PromptRecoNew_All_INCLEFF1ONEPTBINv1VZ03");       
    else datatag[i].Append("_PromptRecoNew_INCLEFF1ONEPTBINv1VZ03");
  int nmin[nmultbin] = {120,150,185,220,260,300};
  int nmax[nmultbin] = {150,185,220,260,300,350};
*/
/*
  const int nmultbin = 19;
  TString dataname = "PAData_Minbias_5TeV";
  TString datatag[nmultbin] = {"MB","MB","MB","MB","MB","MB","MB","MB","MB","MB","HM","HM","HM","HM","HM","HM","HM","HM220","HM220"};
  for(int i=0;i<nmultbin;i++) 
  {
//    if(i<nmultbin-9) datatag[i].Append("_PromptRecoNew_INCLEFF1ONEPTBINv1");                
//    else datatag[i].Append("_PromptRecoNew_All_INCLEFF1ONEPTBINv1");
//    datatag[i].Append("_PromptRecoNew_All_INCLEFF1ONEPTBINv12");
    datatag[i].Append("_PromptRecoNew_INCLEFF1ONEPTBINv12");
  }      
  int nmin[nmultbin] = {0,5,10,20,30,40,50,60,80,100,120,150,185,220,240,260,280,300,320};
  int nmax[nmultbin] = {5,10,20,30,40,50,60,80,100,120,150,185,220,240,260,280,300,320,350};
*/
/*
  const int nmultbin = 19;
  TString dataname = "HIData_Minbias_2760GeV";
  TString datatag[nmultbin];
  for(int i=0;i<nmultbin;i++) datatag[i] = "PPRereco_INCLEFF1ONEPTBINv1";
  int nmin[nmultbin] = {0,5,10,20,30,40,50,60,80,100,120,150,185,220,240,260,280,300,320};
  int nmax[nmultbin] = {5,10,20,30,40,50,60,80,100,120,150,185,220,240,260,280,300,320,350};
*/
  TH1D *hdata_short[nmultbin];
  TH1D *hdata_short_zyam[nmultbin];
  TH1D *hdata_long[nmultbin];
  TH1D *hdata_long_zyam[nmultbin];
  TF1  *fitfunc_short[nmultbin];
  TF1  *fitfunc_long[nmultbin];
  TF1  *fitfunc_vn[nmultbin]; 

  double v2[nmultbin];
  double v3[nmultbin];
  double v2_err[nmultbin];
  double v3_err[nmultbin];
  double nmult[nmultbin];
  int ptbin=0;
  TGraphErrors* gr_yield_short_mult = new TGraphErrors(nmultbin);
  TGraphErrors* gr_yield_long_mult = new TGraphErrors(nmultbin);

  for(int ibin = 0; ibin<nmultbin; ibin++)
  { 
    TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",dataname.Data(),dataname.Data(),datatag[ibin].Data(),nmin[ibin],nmax[ibin],centmin[ibin],centmax[ibin],-2.4,2.4,-2.4,2.4);
    hdata_short[ibin] = (TH1D*)Get1DCFdPhiv3(filename.Data(),ptbin,ptbin,-1.,1.);
    hdata_long[ibin] = (TH1D*)Get1DCFdPhiv3(filename.Data(),ptbin,ptbin,2,4);
//    hdata_short[ibin]->Add(hdata_long[ibin],-1);
    hdata_short_zyam[ibin]=GetJetCorrFunc1D_ZYAM_pp(hdata_short[ibin]);
    hdata_long_zyam[ibin]=GetJetCorrFunc1D_ZYAM_pp(hdata_long[ibin]);
    fitfunc_short[ibin]=GetFitFunc_ZYAM_pp(hdata_short[ibin]);
    fitfunc_long[ibin]=GetFitFunc_ZYAM_pp(hdata_long[ibin]);
// for pPb low stat.
//    if(ibin>=(nmultbin-2)) hdata_long_zyam[ibin]=SimpleZYAM1D(hdata_long[ibin],1.4);
//    if(ibin>=(nmultbin-1)) hdata_long_zyam[ibin]=SimpleZYAM1D(hdata_long[ibin],1.4);
//    if(ibin>=(nmultbin-1)) hdata_short_zyam[ibin]=SimpleZYAM1D(hdata_short[ibin],1.4);

    fitfunc_vn[ibin] = FitVnFunc(hdata_long[ibin]);
    TH1D* hmult = (TH1D*)GetHist(filename,Form("multrawall"));
    
    double yielderror_long=0;
    double yield_long = hdata_long_zyam[ibin]->IntegralAndError(hdata_long_zyam[ibin]->FindBin(-1.2),hdata_long_zyam[ibin]->FindBin(1.2),yielderror_long,"width");//zyamminimumscale;
    yielderror_long=sqrt(yielderror_long*yielderror_long+fitfunc_long[ibin]->GetParError(0)*fitfunc_long[ibin]->GetParError(0)*2.4*2.4);
    gr_yield_long_mult->SetPoint(ibin,hmult->GetMean(),yield_long);
    gr_yield_long_mult->SetPointError(ibin,0,yielderror_long);

    double yielderror_short=0;
    double yield_short = hdata_short_zyam[ibin]->IntegralAndError(hdata_short_zyam[ibin]->FindBin(-1.2),hdata_short_zyam[ibin]->FindBin(1.2),yielderror_short,"width");//zyamminimumscale;
    yielderror_short=sqrt(yielderror_short*yielderror_short+fitfunc_short[ibin]->GetParError(0)*fitfunc_short[ibin]->GetParError(0)*2.4*2.4);
    gr_yield_short_mult->SetPoint(ibin,hmult->GetMean(),yield_short-yield_long);
    gr_yield_short_mult->SetPointError(ibin,0,sqrt(yielderror_short*yielderror_short+yielderror_long*yielderror_long));

//    gr_yield_short_mult->SetPoint(ibin,hmult->GetMean(),yield_short);
//    gr_yield_short_mult->SetPointError(ibin,0,yielderror_short);

    nmult[ibin] = hmult->GetMean();

// Fourier decomposition
    v2[ibin] = fitfunc_vn[ibin]->GetParameter(2)/sqrt(fabs(fitfunc_vn[ibin]->GetParameter(2)));
    v3[ibin] = fitfunc_vn[ibin]->GetParameter(3)/sqrt(fabs(fitfunc_vn[ibin]->GetParameter(3)));
    v2_err[ibin] = fitfunc_vn[ibin]->GetParError(2)/fitfunc_vn[ibin]->GetParameter(2)*v2[ibin];
    v3_err[ibin] = fitfunc_vn[ibin]->GetParError(3)/fitfunc_vn[ibin]->GetParameter(3)*v3[ibin];
  }

  TCanvas* c1D_short = new TCanvas("c1D_short","c1D_short",1000,800);
  c1D_short->Divide(5,3);
  TCanvas* c1D_long = new TCanvas("c1D_long","c1D_long",1000,800);
  c1D_long->Divide(5,3);

  for(int i=1;i<=nmultbin;i++) 
  {
    c1D_short->cd(i);
//    hdata_short_zyam[i-1]->Add(hdata_long_zyam[i-1],-1);
    hdata_short_zyam[i-1]->SetAxisRange(-0.05,0.3,"Y");
    hdata_short_zyam[i-1]->Draw("PE");
    fitfunc_short[i-1]->SetLineColor(2);
//    fitfunc_short[i-1]->Draw("Lsame");
    c1D_long->cd(i);
    hdata_long_zyam[i-1]->SetAxisRange(-0.05,0.2,"Y");
    hdata_long_zyam[i-1]->Draw("PE");
    fitfunc_long[i-1]->SetLineColor(2);
//    fitfunc_long[i-1]->Draw("Lsame");
  }
  
  SaveCanvas(c1D_long,"pPb/corr","corr1D_pPb_allHFbins_longrange");
  SaveCanvas(c1D_short,"pPb/corr","corr1D_pPb_allHFbins_shortrange");

  ofstream fcout(Form("data/v2v3vsN_%s_pt1-2_hfall.txt",dataname.Data()));
  fcout << "N    v_2    v_2 err." << endl;
  for(int i = 0; i<nmultbin; i++) fcout << nmult[i] << " "<< v2[i] << " " << v2_err[i] <<endl;
  fcout<<endl<<endl;
  fcout << "N    v_3    v_3 err." << endl;
  for(int i = 0; i<nmultbin; i++) fcout << nmult[i] << " "<< v3[i] << " " << v3_err[i] <<endl;
  fcout<<endl<<endl;    

  TFile* fout = new TFile("results/pPb_yieldvsn_pt1-2_hfall.root","recreate");
//  TFile* fout = new TFile("results/PbPb_yieldvsn_pt03-3_all.root","recreate");
//  TFile* fout = new TFile("results/pPb_yieldvsn_pt1-2.root","recreate");
  gr_yield_short_mult->SetName("gr_yield_short_mult");
  gr_yield_long_mult->SetName("gr_yield_long_mult");
  gr_yield_short_mult->Write();
  gr_yield_long_mult->Write();
  fout->Close();
}
