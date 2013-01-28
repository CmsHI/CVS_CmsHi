void distfunc(double threshold=0.05)
{
  TFile* f = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULT220NVTX1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root");
  TH1D* trkzvtxres = (TH1D*)f->Get("trkzvtxres");
  TH1D* distfunc = new TH1D("distfunc",";d (cm)",250,0,1);

  double integral_total = trkzvtxres->Integral();
  for(int i=1;i<=distfunc->GetNbinsX();i++)
  {
    double frac = trkzvtxres->Integral(trkzvtxres->FindBin(distfunc->GetBinCenter(i)-0.1),trkzvtxres->FindBin(distfunc->GetBinCenter(i)+0.1))/integral_total/threshold;
    distfunc->SetBinContent(i,frac);
  }

  TCanvas* c = new TCanvas("c","",550,500);
  distfunc->Draw("PE");

  TFile* f = new TFile(Form("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/efficiency/pileup_distfunc_%d_pPb.root",(int)(threshold*100)),"recreate");
  distfunc->Write();
  f->Close();
}
