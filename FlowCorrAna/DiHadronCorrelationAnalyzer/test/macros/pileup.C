void pileup()
{
//  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_PeripheralNew_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");
//  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULTAllPURej3Vtx_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");

  TF1* func[40];
  TGraph* xx_yy[40];
  double par0_arr[40];
  double par1_arr[40];
  double par2_arr[40];
  double dz_arr[40];
//  double binwidth=0.2;
  double binedges[16]={0.0,0.2,0.3,0.4,0.5,0.6,0.8,1.0,1.4,1.8,2.4,3.0,4.2,5.0,7.0,10.0};

  TCanvas* c16 = new TCanvas("c16","c16",800,600);
  c16->Divide(4,4);

  for(int i=0;i<15;i++)
  {
//    h->GetZaxis()->SetRange(h->GetZaxis()->FindBin(binwidth*i),h->GetZaxis()->FindBin(binwidth*i+binwidth));
    h->GetZaxis()->SetRange(h->GetZaxis()->FindBin(binedges[i]),h->GetZaxis()->FindBin(binedges[i+1]));
    h->GetYaxis()->SetRange(h->GetYaxis()->FindBin(2),h->GetYaxis()->FindBin(50));
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
  
// Hydjet
//    TF1* func = new TF1("func","[0]+[1]*(x-[2])*(x-[2])",0,500);
//    func->SetParameters(20,-0.1,150);
  func[i] = new TF1(Form("func_%d",i),"[0]*x**[1]",0,500);
  func[i]->SetParameters(1,0.5);
  func[i]->SetParLimits(0,0,10000);
  func[i]->SetParLimits(1,0,10000);
  if(i==0) func[i]->FixParameter(0,8); //pPb
//  else if(i>11) func[i]->FixParameter(0,20); //pPb
  else func[i]->FixParameter(0,2.); //pPb

//  func->FixParameter(0,5); //PbPb

//    TF1* func = new TF1("func","[0]+[1]*x",40,500);
//    double par1 = (hprof_x->GetBinContent(6)+hprof_x->GetBinError(6)-hprof_x->GetBinContent(1)-hprof_x->GetBinError(1))/(hprof_x->GetBinCenter(6)-hprof_x->GetBinCenter(1));
//    double par0 = hprof_x->GetBinContent(6)+hprof_x->GetBinError(6)-par1*hprof_x->GetBinCenter(6);
//    func->SetParameters(par0,par1);

    xx_yy[i] = new TGraph(hprof_x->GetNbinsX(),xx,yy);
    xx_yy[i]->Fit(Form("func_%d",i),"NO","",0,300);

    c16->cd(i+1);
    xx_yy[i]->Draw("AP"); 
    func[i]->SetLineColor(kRed);
    func[i]->Draw("Lsame");   

    par2_arr[i] = func[i]->GetParameter(2);    
    par1_arr[i] = func[i]->GetParameter(1);
    par0_arr[i] = func[i]->GetParameter(0);
    dz_arr[i] = (binedges[i]+binedges[i+1])/2;
  }

  TGraph* gr_par0 = new TGraph(15,dz_arr,par0_arr);
  TGraph* gr_par1 = new TGraph(15,dz_arr,par1_arr);
  TGraph* gr_par2 = new TGraph(15,dz_arr,par2_arr);

  TCanvas* cc = new TCanvas("cc","",950,400);  
  cc->Divide(3,1);
  cc->cd(1);
  gr_par0->Draw("AP");
  TF1* func_par0 = new TF1("func_par0","[2]*exp(-x**2/[0])*x**[3]+[1]",0.0,10.0);
  func_par0->SetParameters(0.2,0,5,-1);
  func_par0->FixParameter(2,0);
  gr_par0->Fit("func_par0","NO","",0.3,4.0);
  func_par0->Draw("Lsame");
  cc->cd(2);
  gr_par1->Draw("AP");
//  TF1* func_par1 = new TF1("func_par1","[2]*exp(-x**2/[0])*x**[3]+[1]",0.,10.0);
//  func_par1->SetParameters(0.2,0,-0.0005,0);
//  TF1* func_par1 = new TF1("func_par1","[2]*exp(-x/[0])*x**[3]+[1]",0.,10.0);
  TF1* func_par1 = new TF1("func_par1","[1]*exp(-x**[2]/[0])*x**[3]",0.,10.0);
  func_par1->SetParameters(0.1,0.6,2,1);
//  func_par1->FixParameter(2,1);
//  func_par1->FixParameter(3,1);

  gr_par1->Fit("func_par1","NO","",0.3,4.0);
  func_par1->Draw("Lsame");
  cc->cd(3);
  gr_par2->Draw("AP"); 
  TF1* func_par2 = new TF1("func_par2","[2]*exp(-x**2/[0])*x**[3]+[1]",0.,10.0);
  func_par2->SetParameters(1.2,170,120,1);
  gr_par2->Fit("func_par2","NO","",0.2,2.0);
  func_par2->Draw("Lsame");

cout<<Form("par0=%.2f*exp(-x**2/%.2f)*(x**%.2f)+%.2f",func_par0->GetParameter(2),func_par0->GetParameter(0),func_par0->GetParameter(3),func_par0->GetParameter(1))<<endl;
cout<<Form("par1=%.6f*exp(-x/%.6f)*(x**%.6f)+%.2f",func_par1->GetParameter(2),func_par1->GetParameter(0),func_par1->GetParameter(3),func_par1->GetParameter(1))<<endl;
cout<<Form("par2=%.2f*exp(-x**2/%.2f)*(x**%.2f)+%.2f",func_par2->GetParameter(2),func_par2->GetParameter(0),func_par2->GetParameter(3),func_par2->GetParameter(1))<<endl;

//  TF2* func2D = new TF2("func2D","[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x**2/[7])*x**[3]+[5])*y",0,1.0,0,500);
//  TF2* func2D = new TF2("func2D","[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])",0,5.0,0,500);
//  TF2* func2D = new TF2("func2D","([2]*exp(-x**2/[0])*x**[3]+[1])*y**[4]",0,10.0,0,500);
  TF2* func2D = new TF2("func2D","[0]*y**([2]*exp(-x**[3]/[1])*x**[4])",0,10.0,0,500);
  func2D->SetParameter(0,func_par0->GetParameter(1));
  func2D->SetParameter(1,func_par1->GetParameter(0));
  func2D->SetParameter(2,func_par1->GetParameter(1));
  func2D->SetParameter(3,func_par1->GetParameter(2));
  func2D->SetParameter(4,func_par1->GetParameter(3));
/*
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
*/
/*
cout<<Form("%.6f, %.6f, %.6f, %.6f,",func_par0->GetParameter(0),func_par0->GetParameter(1),func_par0->GetParameter(2),func_par0->GetParameter(3))<<endl;
cout<<Form("%.6f, %.6f, %.6f, %.6f,",func_par1->GetParameter(0),func_par1->GetParameter(1),func_par1->GetParameter(2),func_par1->GetParameter(3))<<endl;
cout<<Form("%.6f, %.6f, %.6f, %.6f,",func_par2->GetParameter(0),func_par2->GetParameter(1),func_par2->GetParameter(2),func_par2->GetParameter(3))<<endl;
*/
cout<<Form("%.6f, %.6f, %.6f, %.6f, %.6f,",func2D->GetParameter(0),func2D->GetParameter(1),func2D->GetParameter(2),func2D->GetParameter(3),func2D->GetParameter(4))<<endl;
cout<<Form("%.6f, %.6f",func[0]->GetParameter(0),func[0]->GetParameter(1))<<endl;

  TH2D* h_pileup = new TH2D("distfunc",";d (cm);N_{trk}^{primary};N_{trk}^{secondary}",500,0,50.0,50,0,500);

  for(int i=1;i<=h_pileup->GetNbinsX();i++) 
    for(int j=1;j<=h_pileup->GetNbinsY();j++)
    {

//      if(h_pileup->GetYaxis()->GetBinCenter(j)<func2D->Eval(h_pileup->GetXaxis()->GetBinCenter(i),h_pileup->GetYaxis()->GetBinCenter(j))) h_pileup->SetBinContent(i,j,h_pileup->GetYaxis()->GetBinCenter(j));
//      else if(h_pileup->GetXaxis()->GetBinCenter(i)<0.2) h_pileup->SetBinContent(i,j,func2D->Eval(0.2,h_pileup->GetYaxis()->GetBinCenter(j)));
//      else h_pileup->SetBinContent(i,j,func2D->Eval(h_pileup->GetXaxis()->GetBinCenter(i),h_pileup->GetYaxis()->GetBinCenter(j)));
      if(h_pileup->GetXaxis()->GetBinCenter(i)<0.2) h_pileup->SetBinContent(i,j,func[0]->Eval(h_pileup->GetYaxis()->GetBinCenter(j)));
      else h_pileup->SetBinContent(i,j,func2D->Eval(h_pileup->GetXaxis()->GetBinCenter(i),h_pileup->GetYaxis()->GetBinCenter(j)));
    }

/*
  for(int i=1;i<=h_pileup->GetNbinsX();i++) 
    for(int j=1;j<=h_pileup->GetNbinsY();j++)
    {
      for(int k=0;k<15;k++) 
      {
        if(h_pileup->GetXaxis()->GetBinCenter(i)>binedges[k] && h_pileup->GetXaxis()->GetBinCenter(i)<binedges[k+1]) h_pileup->SetBinContent(i,j,func[k]->Eval(h_pileup->GetYaxis()->GetBinCenter(j)));
      }
    }
*/

  TCanvas* c2D = new TCanvas("c2D","",550,500);
  c2D->SetPhi(-60);
  c2D->SetTheta(50);
  h_pileup->SetAxisRange(0,3.0,"X");
  h_pileup->GetXaxis()->CenterTitle();
  h_pileup->GetYaxis()->CenterTitle();
  h_pileup->GetZaxis()->CenterTitle();
  h_pileup->Draw("surf1"); 
  SaveCanvas(c2D,"pPb/corr","pileup_distfunc_hydjet");
return;
  TFile* fout = new TFile("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/efficiency/pileup_distfunc_pPb_1sigma_mode1.root","recreate");
  h_pileup->Write();
  fout->Close();
}

void pileup1(double dzmin, double dzmax)
{
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h1 = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep"); 
  TH2D* h21 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssec");
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");

  TH1D* htrk_max1 = h1->ProjectionX();
  h1->GetZaxis()->SetRange(h1->GetZaxis()->FindBin(dzmin),h1->GetZaxis()->FindBin(dzmax));
  h1->GetYaxis()->SetRange(h1->GetYaxis()->FindBin(2),h1->GetYaxis()->FindBin(50));
  TH2D* h2D1 = (TH2D*)h1->Project3DProfile("yx100");
  h2D1->Rebin2D(5,1);
  TProfile* hprof1_x = (TProfile*)h2D1->ProfileX("hprof1_x",-1,-1,"s");
  TH1D* h1D1 = (TH1D*)h2D1->ProjectionY("h1D1",13,15,"e");
/*
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");
  TH2D* h2 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssec");
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
*/

  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_PeripheralNew_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_PeripheralNew_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");
  TH2D* h2 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_PeripheralNew_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssec");
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_PeripheralNew_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");

/*
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingReco_Minbias_2760GeV/merged/HijingReco_Minbias_2760GeV_53x_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingReco_Minbias_2760GeV/merged/HijingReco_Minbias_2760GeV_53x_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep");
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HijingReco_Minbias_2760GeV/merged/HijingReco_Minbias_2760GeV_53x_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
*/
/*
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep"); 
  TH2D* h2 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssec");
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
*/
/*
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULT220_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULT220_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep"); 
  TH2D* h2 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULT220_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssec"); 
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptSkim_INCLMULT220_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
*/
/*
  TH1D* hdz = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptRecoNew_INCLMULT220PURej2sigmaMode1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","xyzvtxsepmin");
  TH3D* h = (TH3D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptRecoNew_INCLMULT220PURej2sigmaMode1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssecvszvtxsep"); 
  TH2D* h2 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptRecoNew_INCLMULT220PURej2sigmaMode1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssec"); 
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptRecoNew_INCLMULT220PURej2sigmaMode1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
*/
  TH1D* htrk_max = h->ProjectionX();
  h->GetZaxis()->SetRange(h->GetZaxis()->FindBin(dzmin),h->GetZaxis()->FindBin(dzmax));
  h->GetYaxis()->SetRange(h->GetYaxis()->FindBin(2),h->GetYaxis()->FindBin(241));
//  h->Rebin3D(10,1);
  TH2D* h2D = (TH2D*)h->Project3DProfile("yx");
  h2D->Rebin2D(5,1);
  TProfile* hprof_x = (TProfile*)h2D->ProfileX("hprof_x",-1,-1,"s");
//  TH1D* h1D = (TH1D*)h2D->ProjectionY("h1D",h2D->GetXaxis()->FindBin(200),h2D->GetXaxis()->FindBin(220),"e");
  TH1D* h1D = (TH1D*)h2->ProjectionY("h1D",h2->GetXaxis()->FindBin(200),h2->GetXaxis()->FindBin(220),"e");
   
  double xx[1000];
  double yy[1000];
  for(int i=1;i<=hprof_x->GetNbinsX();i++)
  {
    yy[i-1] = hprof_x->GetBinContent(i)+2*hprof_x->GetBinError(i);
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
//  TF1* func = new TF1("func","[0]+[1]*(x-[2])*(x-[2])",0,500);
//  func->SetParameters(30,-0.1,150);
  TF1* func = new TF1("func","[0]*x**[1]",0,500);
  func->SetParameters(0.1,0.5);
  func->SetParLimits(0,0,10000);
  func->SetParLimits(1,0,10000);
//  func->FixParameter(0,5); small dz
  func->FixParameter(0,2);
  xx_yy->Fit("func","NO","",10,400);

  TCanvas* cc6 = new TCanvas("cc6","cc6",550,500);
  TH2D* htmp = new TH2D("htmp",";N_{trk}^{primary};N_{trk}^{secondary}",500,0,500,50,0,50);
  htmp->Draw("");
  xx_yy->Draw("Psame");
  func->SetLineColor(2);
  func->Draw("Lsame");
  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(latex->GetTextSize()*0.75);
  latex->DrawLatex(0.23,0.87,"PbPb HYDJET, 1<|dz|<2 cm");
//  SaveCanvas(cc6,"pPb/corr","NpriVsNsecProfile_2Sigma_hydjet_dz1020_ForAN");

  TCanvas* cc4 = new TCanvas("cc4","cc4",550,500);
  cc4->SetLogz();
  hNvtxVsMult->Rebin2D(10,1);
//  hNvtxVsMult->Scale(1.0/hNvtxVsMult->GetBinContent(0,0));
  hNvtxVsMult->SetAxisRange(1,5.9,"Y");
  hNvtxVsMult->SetAxisRange(0,280,"X");
  hNvtxVsMult->SetTitle(";N_{trk}^{offline};# of vertices");
  TProfile* hNvtxVsMult_prof = (TProfile*)hNvtxVsMult->ProfileX("hNvtxVsMult_prof",-1,-1,"s");
  hNvtxVsMult->Draw("colz");
//  hNvtxVsMult_prof->Draw("PEsame");
//  SaveCanvas(cc4,"pPb/corr","NvtxVsMult_PbPb2011_ForAN");

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

  TCanvas* c = new TCanvas("c","",580,500);
  c->SetLogz();
  c->SetRightMargin(0.14);

  h2D->SetTitle(";N_{trk}^{primary};N_{trk}^{secondary}");
  h2D->GetXaxis()->CenterTitle();
  h2D->GetYaxis()->CenterTitle();
  h2D->Draw("colz");
/*
  h2->SetAxisRange(2,241,"Y");
  h2->SetTitle(";N_{trk}^{primary};N_{trk}^{secondary}");
  h2->GetXaxis()->CenterTitle();
  h2->GetYaxis()->CenterTitle();
  h2->Draw("colz");
*/
  //hprof_x->Draw("PESAME");
//  func->Draw("Lsame");
  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(latex->GetTextSize()*0.75);
//  latex->DrawLatex(0.23,0.87,"PbPb data 2011");
//  latex->DrawLatex(0.23,0.87,"PbPb HYDJET, 1<|dz|<2 cm");
  latex->DrawLatex(0.23,0.87,"HLT_PAPixelTracks_Multiplicity220");
  latex->DrawLatex(0.23,0.8,"1<|dz|<2 cm, pileup rejected");
//  latex->DrawLatex(0.23,0.87,"pPb pilot");
//  SaveCanvas(c,"pPb/corr","NpriVsNsec_NoPURej_pPbTrigger220_ForAN");
//  SaveCanvas(c,"pPb/corr","NpriVsNsec_NoPURej_PbPb2011_ForAN");
//  SaveCanvas(c,"pPb/corr","NpriVsNsec_NoPURej_hydjet_ForAN_dz1020");
//  SaveCanvas(c,"pPb/corr","NpriVsNsec_PURej_pPbTrigger220_dz1020_ForAN");

  TCanvas* cc = new TCanvas("cc","",550,500);
  cc->SetLogy();
  h1D->SetTitle("");
  h1D->SetXTitle("N_{trk}^{secondary}");
  h1D->GetXaxis()->CenterTitle();
  h1D->Scale(1.0/h1D->Integral());
  htrk_max1->Scale(1.0/htrk_max1->Integral());
  htrk_max1->SetMarkerStyle(24);
  h1D->SetAxisRange(0,50,"X");
  h1D->Draw("PE");
  htrk_max1->Draw("PESAME");
  TLine* l_2sigma = new TLine(h1D->GetMean()+h1D->GetRMS()*2,0,h1D->GetMean()+h1D->GetRMS()*2,0.04);
  l_2sigma->SetLineWidth(3);
  l_2sigma->SetLineColor(2);
  l_2sigma->Draw("Lsame");
  TLatex* latex = new TLatex();
  latex->SetTextColor(2);
  latex->SetTextSize(latex->GetTextSize()*0.75);
  latex->DrawLatex(h1D->GetMean()+h1D->GetRMS()*2*0.7,0.053,"Mean+2#timesRMS");

  TLine* l_1sigma = new TLine(h1D->GetMean()+h1D->GetRMS()*1,0,h1D->GetMean()+h1D->GetRMS()*1,0.1);
  l_1sigma->SetLineWidth(3);
  l_1sigma->SetLineStyle(9);
  l_1sigma->SetLineColor(4);
  l_1sigma->Draw("Lsame");
  TLatex* latex = new TLatex();
  latex->SetTextColor(4);
  latex->SetTextSize(latex->GetTextSize()*0.75);
  latex->DrawLatex(h1D->GetMean()+h1D->GetRMS()*0.4,0.123,"Mean+1#timesRMS");

  TLatex* latex = new TLatex();
  latex->SetTextColor(1);
  latex->SetNDC();
  latex->SetTextSize(latex->GetTextSize()*0.75);
  latex->DrawLatex(0.65,0.85,"200<N_{trk}^{primary}<220");
  SaveCanvas(cc,"pPb/corr","NsecDist_PUestimate");

  TLegend* legend = new TLegend(0.4,0.58,0.9,0.68);
  legend->SetFillColor(0);
  legend->SetFillStyle(0);
  legend->AddEntry(h1D,"N_{trk}^{secondary} from PbPb Hydjet","P");
  legend->AddEntry(htrk_max1,"N_{trk}^{primary} from pPb pilot","P");
  legend->Draw();

  TH1D* hhh = new TH1D("hhh",";N_{trk}^{primary};Residual pileup (%)",25,0,500);
  for(int i=1;i<=hhh->GetNbinsX();i++)
  {
    TH1D* h1Dtmp = (TH1D*)h2->ProjectionY("h1Dtmp",h2->GetXaxis()->FindBin((i-1)*20),h2->GetXaxis()->FindBin(i*20),"e");
    double frac = htrk_max1->Integral(1,htrk_max1->FindBin(h1Dtmp->GetMean()+h1Dtmp->GetRMS()*2))*3.0;
    hhh->SetBinContent(i,frac);
  }
  TCanvas* cc4 = new TCanvas("cc4","",550,500);
  hhh->GetXaxis()->CenterTitle();
  hhh->GetYaxis()->CenterTitle();
  hhh->GetYaxis()->SetTitleOffset(hhh->GetYaxis()->GetTitleOffset()*1.3);
  hhh->Draw("hist");
  TLatex* latex = new TLatex();
  latex->SetTextColor(1);
  latex->SetNDC();
  latex->SetTextSize(latex->GetTextSize()*0.75);
  latex->DrawLatex(0.25,0.85,"Mean+2#timesRMS cut");
  SaveCanvas(cc4,"pPb/corr","ResidualPUvsNtrkpri");
}

void poiss()
{
  TF1* func = new TF1("func","TMath::Poisson(x,0.06)",0,10);
  TH1D* h = new TH1D("h",";# of collisions",11,-0.5,10.5);
  for(int i=1;i<=11;i++) h->SetBinContent(i,func->Eval(h->GetBinCenter(i)));

  TCanvas* c = new TCanvas("c","c",550,500);
  c->SetLogy();
  h->GetXaxis()->CenterTitle();
  h->Draw("hist");

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(latex->GetTextSize()*0.75);
  latex->DrawLatex(0.43,0.87,"Poisson distribution, <#mu>=6%");

  SaveCanvas(c,"pPb/corr","Poisson_mu6");
}
