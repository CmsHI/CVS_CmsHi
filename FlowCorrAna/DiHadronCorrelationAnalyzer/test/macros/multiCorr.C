#include <fstream>

void makeMultiCorr()
{
  const int ntrgptbins=4;
  const int nassptbins=5;

  TString dataname2 = "HIData_Minbias_2760GeV";
  TString datatag2 = "PPRereco_INCLEFF1v4";
  int nmin2=185;
  int nmax2=220;

  TString dataname = "PAData_Minbias_5TeV";
  TString datatag = "HM_PromptSkim_INCLEFF1v6NVTX1";
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

  TH1D ***hdata = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname.Data(),datatag.Data(),nmin,nmax,-1,-1,2.0,4.0,ntrgptbins,nassptbins,-2.4,2.4,-2.4,2.4);
  TH1D* hdata_zyam[ntrgptbins][nassptbins];

  TH1D ***hdata2 = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname2.Data(),datatag2.Data(),nmin2,nmax2,-1,-1,2.0,4.0,ntrgptbins,nassptbins,-2.4,2.4,-2.4,2.4);
  TH1D* hdata2_zyam[ntrgptbins][nassptbins];

  TH1D ***hdata3 = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname3.Data(),datatag3.Data(),nmin3,nmax3,-1,-1,2.0,4.0,ntrgptbins,nassptbins,-2.4,2.4,-2.4,2.4);
  TH1D* hdata3_zyam[ntrgptbins][nassptbins];

  TCanvas* cc = new TCanvas("cc","",250*ntrgptbins,250*(nassptbins-2));
  makeMultiPanelCanvas(cc,ntrgptbins,nassptbins-2,0.01,0.02,0.32,0.2,0.01);
  TCanvas* cc1 = new TCanvas("cc1","",250*ntrgptbins,250*(nassptbins-2));
  makeMultiPanelCanvas(cc1,ntrgptbins,nassptbins-2,0.01,0.02,0.32,0.2,0.01);

  for(int jass = 0; jass<nassptbins-2; jass++)
  {
    for(int itrg = 0; itrg<ntrgptbins; itrg++)
    {
      cc->cd(jass*ntrgptbins+itrg+1);
      hdata[itrg][jass]->SetMarkerColor(kGreen);     
      hdata[itrg][jass]->Draw("PE");
      hdata2[itrg][jass]->SetMarkerColor(kBlue);
      hdata2[itrg][jass]->SetMarkerStyle(20);
      hdata2[itrg][jass]->Draw("PESAME");
//      hdata3[itrg][jass]->SetMarkerColor(2);
//      hdata3[itrg][jass]->Draw("PESAME");
      cc1->cd(jass*ntrgptbins+itrg+1);
      hdata_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM_pp(hdata[itrg][jass]);
      if(jass==0) hdata_zyam[itrg][jass]->SetAxisRange(-0.05,0.7,"Y");
      if(jass==1) hdata_zyam[itrg][jass]->SetAxisRange(-0.05,0.37,"Y");
      if(jass==2) hdata_zyam[itrg][jass]->SetAxisRange(-0.02,0.12,"Y");
      hdata_zyam[itrg][jass]->Draw("PE");
      hdata2_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM_pp(hdata2[itrg][jass]);
      hdata2_zyam[itrg][jass]->SetMarkerStyle(20);
      hdata2_zyam[itrg][jass]->Draw("PESAME");   
//      hdata3_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM_pp(hdata3[itrg][jass]);
//      hdata3_zyam[itrg][jass]->SetMarkerColor(2);
//      hdata3_zyam[itrg][jass]->Draw("PESAME");   
    }
  }

  SaveCanvas(cc1,"pPb/corr","corr1D_pPbvsPbPb_N220260");
}


void yieldvspt()
{

  const int nptbins = 8;
/*
  TString dataname = "PAData_Minbias_5TeV";
  TString datatag = "HM_PromptSkim_INCLEFF1v6NVTX1";
*/

  TString dataname = "HIData_Minbias_2760GeV";
  TString datatag = "PPRereco_INCLEFF1v4";

  TH1D *hdata[nptbins];
  TH1D *hdata_zyam[nptbins];

  int nmultmin=220;
  int nmultmax=260;
  int ptbin_ref=1;
  TGraphErrors* gr_yield_pt = new TGraphErrors(nptbins);

  for(int ibin = 0; ibin<nptbins; ibin++)
  {
    TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",dataname.Data(),dataname.Data(),datatag.Data(),nmultmin,nmultmax,-1,-1,-2.4,2.4,-2.4,2.4);
    hdata[ibin] = (TH1D*)Get1DCFdPhiv3(filename.Data(),ibin,ptbin_ref,2,4);
    hdata_zyam[ibin]=GetJetCorrFunc1D_ZYAM_pp(hdata[ibin]);
    TH1D* hpt = (TH1D*)GetHist(filename,Form("ptcorr_signal_trg_%d",ibin));

    double yielderror=0;
    double yield = hdata_zyam[ibin]->IntegralAndError(hdata_zyam[ibin]->FindBin(-1.2),hdata_zyam[ibin]->FindBin(1.2),yielderror,"width")/2.;//zyamminimumscale;
    yielderror=yielderror/2.;
    gr_yield_pt->SetPoint(ibin,hpt->GetMean(),yield);
    gr_yield_pt->SetPointError(ibin,0,yielderror);
  }

  TFile* fout = new TFile("results/PbPb_yieldvspt_N220260.root","recreate");
  gr_yield_pt->Write();
  fout->Close();
}

void yieldvsn()
{
/*
  const int nmultbin = 9;

  TString dataname = "HIData_Minbias_2760GeV";
  TString datatag = "PPRereco_INCLEFF1v4";

  int nmin[nmultbin] = {0,35,90,110,120,150,185,220,260};
  int nmax[nmultbin] = {35,90,110,120,150,185,220,260,300};
*/
  const int nmultbin = 7;

  TString dataname = "PAData_Minbias_5TeV";
//  TString datatag = "HM_PromptReco_INCLEFF1ONEPTBINPURejTight";
  TString datatag = "HM_PromptSkim_INCLEFF1ONEPTBINNVTX1";
                    
  int nmin[nmultbin] = {220,240,260,270,290,310,340};
  int nmax[nmultbin] = {240,260,270,290,310,340,1000};

  TH1D *hdata[nmultbin];
  TH1D *hdata_zyam[nmultbin];

  int ptbin=0;
  TGraphErrors* gr_yield_mult = new TGraphErrors(nmultbin);

  for(int ibin = 0; ibin<nmultbin; ibin++)
  { 
    TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",dataname.Data(),dataname.Data(),datatag.Data(),nmin[ibin],nmax[ibin],-1,-1,-2.4,2.4,-2.4,2.4);
    hdata[ibin] = (TH1D*)Get1DCFdPhiv3(filename.Data(),ptbin,ptbin,2,4);
    hdata_zyam[ibin]=GetJetCorrFunc1D_ZYAM_pp(hdata[ibin]);
cout<<ibin<<endl;
    TH1D* hmult = (TH1D*)GetHist(filename,Form("multrawall"));
cout<<ibin<<endl;
    
    double yielderror=0;
    double yield = hdata_zyam[ibin]->IntegralAndError(hdata_zyam[ibin]->FindBin(-1.2),hdata_zyam[ibin]->FindBin(1.2),yielderror,"width")/2.;//zyamminimumscale;
    yielderror=yielderror/2.;
    gr_yield_mult->SetPoint(ibin,hmult->GetMean(),yield);
    gr_yield_mult->SetPointError(ibin,0,yielderror);
cout<<hmult->GetMean()<<endl;
  }     

  TFile* fout = new TFile("results/pPb_yieldvsn_pt1-2_nvtx1.root","recreate");
  gr_yield_mult->Write();
  fout->Close();
}
