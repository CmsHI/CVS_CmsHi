void nmult()
{
   TH1D* hmult[20];
   hmult[0] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
//   hmult[1] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130PURej2sigma_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[1] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_PromptReco_INCLMULTPURej2sigma_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[9] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[2] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT160PURejTight_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[3] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT190PURejTight_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[4] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT220PURejTight_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[5] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[6] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULTPURej3Vtx_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
//   hmult[7] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
//   hmult[8] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULTNVTX1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");

  hmult[0]->SetMarkerColor(1);
  hmult[1]->SetMarkerColor(2);
  hmult[2]->SetMarkerColor(3);
  hmult[3]->SetMarkerColor(4);
  hmult[4]->SetMarkerColor(6);
  hmult[5]->SetMarkerStyle(24);
  hmult[6]->SetMarkerStyle(25);

  hmult[0]->Rebin(5);
  hmult[1]->Rebin(5);
  hmult[2]->Rebin(5);
  hmult[3]->Rebin(5);
  hmult[4]->Rebin(5);
  hmult[5]->Rebin(5);
  hmult[6]->Rebin(5);
  hmult[9]->Rebin(5);

  hmult[6]->Scale(hmult[1]->GetBinContent(38)/hmult[5]->GetBinContent(38));
  hmult[5]->Scale(hmult[1]->GetBinContent(38)/hmult[5]->GetBinContent(38));

  TCanvas* c = new TCanvas("c","",550,500);
  c->SetLogy();
  hmult[1]->SetAxisRange(80,400,"X");
  hmult[1]->SetMaximum(hmult[5]->GetMaximum());
  hmult[1]->SetXTitle("N_{trk}^{offline}");
  hmult[1]->Draw("PE");
//  hmult[1]->Draw("PESAME");
//  hmult[2]->Draw("PESAME");
//  hmult[3]->Draw("PESAME");
//  hmult[4]->Draw("PESAME");
  hmult[5]->Draw("PESAME");
//  hmult[6]->Draw("PESAME");
  TLegend* legend = new TLegend(0.5,0.7,0.9,0.85);
  legend->SetHeader("Before PU rejection");
  legend->SetFillColor(0);
  legend->AddEntry(hmult[5],"pPb pilot","P");
  legend->AddEntry(hmult[1],"pPb HLT_Mult130","P");
  legend->Draw("PESAME");

//  SaveCanvas(c,"pPb/corr","mult_PUcompare_NoPURej");

  TCanvas* ccc = new TCanvas("ccc","",550,500);
  TH1D* hratio = (TH1D*)hmult[9]->Clone("hratio");
  hratio->SetXTitle("N_{trk}^{offline}");
  hratio->Divide(hratio,hmult[1],1,1,"");
  hratio->SetAxisRange(180,360,"X");
  hratio->SetAxisRange(0,60,"Y");
//  hratio->Scale(1./hratio->GetBinContent(1));
  hratio->Draw("PE");

  SaveCanvas(ccc,"pPb/corr","ratio_PU_pPb");

  TH1D* hmult300 = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLEFF1v3_nmin300_nmax1000_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
  hmult300->Rebin(5);
  TH1D* hmult300_clone = (TH1D*)hmult300->Clone("mult300_clone");
  hmult300_clone->Scale(250);
  hmult300_clone->SetMarkerColor(2);

  TCanvas* cc = new TCanvas("cc","",550,500);
  cc->SetLogy();
  hmult300->SetXTitle("N_{trk}^{offline}");
  hmult300->SetAxisRange(290,480,"X");
  hmult300->SetAxisRange(0.2,hmult300_clone->GetMaximum()*2,"Y");
  hmult300->Draw("PE");
  hmult300_clone->Draw("PESAME");

//  SaveCanvas(cc,"pPb/corr","mult_HM300");
}

void nvtx()
{
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
  TH2D* hNvtxVsMult1 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
  TH2D* hNvtxVsMult2 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130PURej2sigma_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");

  TH1D* hnvtx = hNvtxVsMult->ProjectionY("hnvtx",221,1000,"e");
  TH1D* hnvtx1 = hNvtxVsMult1->ProjectionY("hnvtx1",221,1000,"e");
  TH1D* hnvtx2 = hNvtxVsMult2->ProjectionY("hnvtx2",221,1000,"e");
  hnvtx->SetMarkerColor(1);
  hnvtx1->SetMarkerStyle(24);
  hnvtx2->SetMarkerColor(2);

  hnvtx->Scale(1.0/hnvtx->Integral());
  hnvtx1->Scale(1.0/hnvtx1->Integral());
  hnvtx2->Scale(1.0/hnvtx2->Integral());

  TCanvas* c = new TCanvas("c","c",550,500);
  hnvtx->SetAxisRange(1,5,"X");
  hnvtx->SetXTitle("# of vertices");
  hnvtx->Draw("PE");
  hnvtx1->Draw("PESAME");
  hnvtx2->Draw("PESAME"); 

  TLegend* legend = new TLegend(0.45,0.65,0.9,0.85);
  legend->SetHeader("N_{trk}^{offline}>=220");
  legend->SetFillColor(0);
  legend->AddEntry(hnvtx,"pPb pilot","P");
  legend->AddEntry(hnvtx1,"pPb HLT_Mult130 before PU","P");
  legend->AddEntry(hnvtx2,"pPb HLT_Mult130 after PU","P");
  legend->Draw("PESAME");

  SaveCanvas(c,"pPb/corr","nvtx_compare_HM");
}
