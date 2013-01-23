#include <fstream>

void makeMultiCorr()
{
  const int ntrgptbins=6;
  const int nassptbins=6;

  TString dataname = "HIData_Minbias_2760GeV";
  TString datatag = "PPRereco_INCLEFF1v4";
  int nmin=110;
  int nmax=120;

  TString dataname2 = "PAData_Minbias_5TeV";
  TString datatag2 = "MB_INCLEFF1v4";
  int nmin2=110;
  int nmax2=1000;

  TString dataname3 = "PPData_Minbias_7TeV";
  TString datatag3 = "TRIGGER85_All_INCLEFF1TRG1v6";
  int nmin3=110;
  int nmax3=1000;

  TH1D ***hdata = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname.Data(),datatag.Data(),nmin,nmax,-1,-1,2.0,4.0,ntrgptbins,nassptbins,-2.4,2.4,-2.4,2.4);
  TH1D* hdata_zyam[ntrgptbins][nassptbins];

  TH1D ***hdata2 = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname2.Data(),datatag2.Data(),nmin2,nmax2,-1,-1,2.0,4.0,ntrgptbins,nassptbins,-2.4,2.4,-2.4,2.4);
  TH1D* hdata2_zyam[ntrgptbins][nassptbins];

  TH1D ***hdata3 = compare_flow_pp_phi_multipad_pt<TH1D**>(dataname3.Data(),datatag3.Data(),nmin3,nmax3,-1,-1,2.0,4.0,ntrgptbins,nassptbins,-2.4,2.4,-2.4,2.4);
  TH1D* hdata3_zyam[ntrgptbins][nassptbins];

  TCanvas* cc = new TCanvas("cc","",250*ntrgptbins,250*(nassptbins-4));
  makeMultiPanelCanvas(cc,ntrgptbins,ntrgptbins,0.01,0.02,0.32,0.2,0.01);
  TCanvas* cc1 = new TCanvas("cc1","",250*ntrgptbins,250*(nassptbins-4));
  makeMultiPanelCanvas(cc1,ntrgptbins,nassptbins-4,0.01,0.02,0.32,0.2,0.01);

  for(int jass = 0; jass<nassptbins-4; jass++)
  {
    for(int itrg = 0; itrg<ntrgptbins; itrg++)
    {
      cc->cd(jass*ntrgptbins+itrg+1);
      hdata[itrg][jass]->Draw("PE");
      hdata2[itrg][jass]->SetMarkerStyle(24);
      hdata2[itrg][jass]->Draw("PESAME");
      hdata3[itrg][jass]->SetMarkerColor(1);
      hdata3[itrg][jass]->Draw("PESAME");
      cc1->cd(jass*ntrgptbins+itrg+1);
      hdata_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM_pp(hdata[itrg][jass]);
      if(jass==0) hdata_zyam[itrg][jass]->SetAxisRange(-0.05,0.4,"Y");
      if(jass==1) hdata_zyam[itrg][jass]->SetAxisRange(-0.05,0.2,"Y");
      hdata_zyam[itrg][jass]->Draw("PE");
      hdata2_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM_pp(hdata2[itrg][jass]);
      hdata2_zyam[itrg][jass]->SetMarkerStyle(24);
      hdata2_zyam[itrg][jass]->Draw("PESAME");   
      hdata3_zyam[itrg][jass]=GetJetCorrFunc1D_ZYAM_pp(hdata3[itrg][jass]);
      hdata3_zyam[itrg][jass]->SetMarkerColor(1);
      hdata3_zyam[itrg][jass]->Draw("PESAME");   
    }
  }

/*
  double pttrg[ntrgptbins] = {0.0};
  double pttrg_err[ntrgptbins] = {0.0};

  TH1D* hpt[ntrgptbins];
  for(int itrg = 0; itrg<ntrgptbins; itrg++)
  {
    TString filename = Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/%s/merged/%s_%s_nmin%d_nmax%d_etatrg%.1f-%.1f_etaass%.1f-%.1f_centmin%d_centmax%d.root",dataname.Data(),dataname.Data(),datatag.Data(),nmin,nmax,-1,-1,-2.4,2.4,-2.4,2.4);    
    hpt[itrg] = (TH1D*)GetHist(filename,Form("ptcorr_signal_trg_%d",itrg));
    pttrg[itrg] = hpt[itrg]->GetMean();
  }
*/
}
