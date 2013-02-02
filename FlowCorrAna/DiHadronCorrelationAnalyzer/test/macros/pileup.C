void pileup()
{
//  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_Peripheral_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");
//  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULTAllPURej3Vtx_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");

  double par0_arr[40];
  double par1_arr[40];
  double par2_arr[40];
  double dz_arr[40];
  double binwidth=0.1;
  for(int i=0;i<40;i++)
  {
    h->GetZaxis()->SetRange(h->GetZaxis()->FindBin(binwidth*i),h->GetZaxis()->FindBin(binwidth*i+binwidth));
    h->GetYaxis()->SetRange(h->GetYaxis()->FindBin(2),h->GetYaxis()->FindBin(60));
    TH2D* h2D = (TH2D*)h->Project3DProfile(Form("yx%d",i));
    h2D->Rebin2D(10,1);
    TProfile* hprof_x = (TProfile*)h2D->ProfileX("hprof_x",-1,-1,"s");
    double xx[500];
    double yy[500];
    for(int ibin=1;ibin<=hprof_x->GetNbinsX();ibin++)
    {
      yy[ibin-1] = hprof_x->GetBinContent(ibin)+2*hprof_x->GetBinError(ibin);
      xx[ibin-1] = hprof_x->GetBinCenter(ibin);
    }
  
    TF1* func = new TF1("func","[0]+[1]*(x-[2])*(x-[2])",0,500);
    func->SetParameters(20,-0.1,150);

//    TF1* func = new TF1("func","[0]+[1]*x",40,500);
//    double par1 = (hprof_x->GetBinContent(6)+hprof_x->GetBinError(6)-hprof_x->GetBinContent(1)-hprof_x->GetBinError(1))/(hprof_x->GetBinCenter(6)-hprof_x->GetBinCenter(1));
//    double par0 = hprof_x->GetBinContent(6)+hprof_x->GetBinError(6)-par1*hprof_x->GetBinCenter(6);
//    func->SetParameters(par0,par1);

    TGraph* xx_yy = new TGraph(hprof_x->GetNbinsX(),xx,yy);
    xx_yy->Fit("func","RNO");

    par2_arr[i] = func->GetParameter(2);    
    par1_arr[i] = func->GetParameter(1);
    par0_arr[i] = func->GetParameter(0);
    dz_arr[i] = binwidth*i+binwidth;
  }

  TGraph* gr_par0 = new TGraph(40,dz_arr,par0_arr);
  TGraph* gr_par1 = new TGraph(40,dz_arr,par1_arr);
  TGraph* gr_par2 = new TGraph(40,dz_arr,par2_arr);

  TCanvas* cc = new TCanvas("cc","",950,400);  
  cc->Divide(3,1);
  cc->cd(1);
  gr_par0->Draw("AP");
  TF1* func_par0 = new TF1("func_par0","[2]*exp(-x**2/[0])*x**[3]+[1]",0.0,10.0);
  func_par0->SetParameters(0.2,0,5,-1);
  gr_par0->Fit("func_par0","NO","",0.2,4.0);
  func_par0->Draw("Lsame");
  cc->cd(2);
  gr_par1->Draw("AP");
//  TF1* func_par1 = new TF1("func_par1","[2]*exp(-x**2/[0])*x**[3]+[1]",0.,10.0);
//  func_par1->SetParameters(0.2,0,-0.0005,0);
  TF1* func_par1 = new TF1("func_par1","[2]*exp(-x/[0])*x**[3]+[1]",0.,10.0);
  func_par1->SetParameters(0.4,-0.0001,-0.0003,0);
  gr_par1->Fit("func_par1","NO","",0.2,4.0);
  func_par1->Draw("Lsame");
  cc->cd(3);
  gr_par2->Draw("AP"); 
  TF1* func_par2 = new TF1("func_par2","[2]*exp(-x**2/[0])*x**[3]+[1]",0.,10.0);
  func_par2->SetParameters(1.2,170,120,1);
  gr_par2->Fit("func_par2","NO","",0.2,4.0);
  func_par2->Draw("Lsame");

cout<<Form("par0=%.2f*exp(-x**2/%.2f)*(x**%.2f)+%.2f",func_par0->GetParameter(2),func_par0->GetParameter(0),func_par0->GetParameter(3),func_par0->GetParameter(1))<<endl;
cout<<Form("par1=%.6f*exp(-x/%.6f)*(x**%.6f)+%.2f",func_par1->GetParameter(2),func_par1->GetParameter(0),func_par1->GetParameter(3),func_par1->GetParameter(1))<<endl;
cout<<Form("par2=%.2f*exp(-x**2/%.2f)*(x**%.2f)+%.2f",func_par2->GetParameter(2),func_par2->GetParameter(0),func_par2->GetParameter(3),func_par2->GetParameter(1))<<endl;

//  TF2* func2D = new TF2("func2D","[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x**2/[7])*x**[3]+[5])*y",0,1.0,0,500);
  TF2* func2D = new TF2("func2D","[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])",0,5.0,0,500);

  func2D->SetParameter(0,func_par0->GetParameter(0));
  func2D->SetParameter(1,func_par0->GetParameter(1));
  func2D->SetParameter(2,func_par0->GetParameter(2));
  func2D->SetParameter(3,func_par0->GetParameter(3));
  func2D->SetParameter(4,func_par1->GetParameter(0));
  func2D->SetParameter(5,func_par1->GetParameter(1));
  func2D->SetParameter(6,func_par1->GetParameter(2));
  func2D->SetParameter(7,func_par1->GetParameter(3));
  func2D->SetParameter(8,func_par2->GetParameter(0));
  func2D->SetParameter(9,func_par2->GetParameter(1));
  func2D->SetParameter(10,func_par2->GetParameter(2));
  func2D->SetParameter(11,func_par2->GetParameter(3));

cout<<Form("%.6f, %.6f, %.6f, %.6f,",func_par0->GetParameter(0),func_par0->GetParameter(1),func_par0->GetParameter(2),func_par0->GetParameter(3))<<endl;
cout<<Form("%.6f, %.6f, %.6f, %.6f,",func_par1->GetParameter(0),func_par1->GetParameter(1),func_par1->GetParameter(2),func_par1->GetParameter(3))<<endl;
cout<<Form("%.6f, %.6f, %.6f, %.6f,",func_par2->GetParameter(0),func_par2->GetParameter(1),func_par2->GetParameter(2),func_par2->GetParameter(3))<<endl;


  TH2D* h_pileup = new TH2D("distfunc",";d (cm);N_{trk}^{primary};N_{trk}^{secondary}",500,0,50.0,50,0,500);
  for(int i=1;i<=h_pileup->GetNbinsX();i++) 
    for(int j=1;j<=h_pileup->GetNbinsY();j++)
    {
      if(h_pileup->GetXaxis()->GetBinCenter(i)<0.2) h_pileup->SetBinContent(i,j,func2D->Eval(0.2,h_pileup->GetYaxis()->GetBinCenter(j)));
      else h_pileup->SetBinContent(i,j,func2D->Eval(h_pileup->GetXaxis()->GetBinCenter(i),h_pileup->GetYaxis()->GetBinCenter(j)));
    }

  TCanvas* c2D = new TCanvas("c2D","",550,500);
  h_pileup->SetAxisRange(0,5.0,"X");
  h_pileup->Draw("surf1"); 
//  SaveCanvas(c2D,"pPb/corr","pileup_distfunc_pPb");
return;
  TFile* fout = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/efficiency/pileup_distfunc_pPb_2sigma.root","recreate");
  h_pileup->Write();
  fout->Close();
}

void pileup1(double dzmin, double dzmax)
{
//  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep"); 
//  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULT190_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep"); 

  TH1D* hdz1 = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLEFF1ONEPTBINPURejTight_nmin320_nmax1000_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h1 = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLEFF1ONEPTBINPURejTight_nmin320_nmax1000_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep"); 
//  TH3D* h1 = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULT190_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep"); 
  h1->GetZaxis()->SetRange(h1->GetZaxis()->FindBin(dzmin),h1->GetZaxis()->FindBin(dzmax));
  h1->GetYaxis()->SetRange(h1->GetYaxis()->FindBin(0),h1->GetYaxis()->FindBin(200));
  TH2D* h2D1 = (TH2D*)h1->Project3DProfile("yx100");
  h2D1->Rebin2D(5,1);
  TProfile* hprof1_x = (TProfile*)h2D1->ProfileX("hprof1_x",-1,-1,"s");
  TH1D* h1D1 = (TH1D*)h2D1->ProjectionY("h1D1",13,15,"e");
/*
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
*/
/*
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_Peripheral_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_Peripheral_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_Peripheral_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
*/
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingReco_Minbias_2760GeV/merged/HijingReco_Minbias_2760GeV_53x_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingReco_Minbias_2760GeV/merged/HijingReco_Minbias_2760GeV_53x_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingReco_Minbias_2760GeV/merged/HijingReco_Minbias_2760GeV_53x_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");

/*
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep"); 
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
*/
/*
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULTAllPURej2sigma_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULTAllPURej2sigma_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep"); 
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULTAllPURej2sigma_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
*/
/*
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULTPURej3Vtx_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULTPURej3Vtx_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep"); 
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULTPURej3Vtx_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
*/
  TH1D* htrk_max = h->ProjectionX();
  h->GetZaxis()->SetRange(h->GetZaxis()->FindBin(dzmin),h->GetZaxis()->FindBin(dzmax));
  h->GetYaxis()->SetRange(h->GetYaxis()->FindBin(2),h->GetYaxis()->FindBin(60));
  TH2D* h2D = (TH2D*)h->Project3DProfile("yx");
  h2D->Rebin2D(10,1);
  TProfile* hprof_x = (TProfile*)h2D->ProfileX("hprof_x",-1,-1,"s");
  TH1D* h1D = (TH1D*)h2D->ProjectionY("h1D",h2D->GetXaxis()->FindBin(100),h2D->GetXaxis()->FindBin(150),"e");
    
  double xx[100];
  double yy[100];
  for(int i=1;i<=hprof_x->GetNbinsX();i++)
  {
    yy[i-1] = hprof_x->GetBinContent(i)+hprof_x->GetBinError(i);
    xx[i-1] = hprof_x->GetBinCenter(i);
  }

  TGraph* xx_yy = new TGraph(hprof_x->GetNbinsX(),xx,yy);

  int ibin = hprof_x->GetXaxis()->FindBin(200);
/*
  TF1* func = new TF1("func","[0]+[1]*x",0,500);
  double par1 = (hprof_x->GetBinContent(ibin)+hprof_x->GetBinError(ibin)-hprof_x->GetBinContent(1)-hprof_x->GetBinError(1))/(hprof_x->GetBinCenter(ibin)-hprof_x->GetBinCenter(1));
  double par0 = hprof_x->GetBinContent(ibin)+hprof_x->GetBinError(ibin)-par1*hprof_x->GetBinCenter(ibin);
  func->SetParameters(par0,par1);
*/
  TF1* func = new TF1("func","[0]+[1]*(x-[2])*(x-[2])",0,500);
  func->SetParameters(30,-0.1,150);

  xx_yy->Fit("func","RNO");

  TCanvas* cc6 = new TCanvas("cc6","cc6",550,500);
  xx_yy->Draw("AP");
  func->Draw("Lsame");

  TCanvas* cc4 = new TCanvas("cc4","cc4",550,500);
  cc4->SetLogz();
  hNvtxVsMult->Rebin2D(10,1);
  hNvtxVsMult->SetAxisRange(1,5.9,"Y");
  hNvtxVsMult->SetAxisRange(0,280,"X");
  hNvtxVsMult->SetTitle(";N_{trk}^{offline};# of vertices");
  TProfile* hNvtxVsMult_prof = (TProfile*)hNvtxVsMult->ProfileX("hNvtxVsMult_prof",-1,-1,"s");
  hNvtxVsMult->Draw("colz");
//  hNvtxVsMult_prof->Draw("PEsame");
//  SaveCanvas(cc4,"pPb/corr","NvtxVsMult_pPbPURej3");

  TCanvas* cc5 = new TCanvas("cc5","cc5",550,500);
  TH1D* hNvtxVsMult_1D = hNvtxVsMult->ProjectionY("hNvtxVsMult_1D",23,23,"e");
  hNvtxVsMult_1D->Draw("PE");

//  TCanvas* cc3 = new TCanvas("cc3","cc3",550,500);
//  htrk_max->SetAxisRange(-1.5,1.5,"X");
//  htrk_max->Draw("PE");

  TCanvas* cc1 = new TCanvas("cc1","cc1",550,500);
  hdz->SetAxisRange(-1.5,1.5,"X");
  hdz->Draw("PE");
//  SaveCanvas(cc1,"pPb/corr","dz_pPbPURej3");

  TCanvas* c = new TCanvas("c","",550,500);
//  c->SetLogz();
  h2D->SetTitle(";N_{trk}^{primary};N_{trk}^{secondary}");
  h2D->Draw("colz");
  hprof_x->Draw("PESAME");
//  func->Draw("Lsame");
//  SaveCanvas(c,"pPb/corr",Form("NpriVsNsec_pPbPURej3_dzmin%.1f_dzmax%.1f",dzmin,dzmax));

  TCanvas* cc = new TCanvas("cc","",550,500);
  h1D->Scale(1.0/h1D->Integral());
  htrk_max->Scale(1.0/htrk_max->Integral());
  htrk_max->SetMarkerStyle(24);
  h1D->Draw("PE");
  htrk_max->Draw("PESAME");
//  SaveCanvas(cc,"pPb/corr",Form("NsecDist_pPbPURej3_dzmin%.1f_dzmax%.1f",dzmin,dzmax));
}
