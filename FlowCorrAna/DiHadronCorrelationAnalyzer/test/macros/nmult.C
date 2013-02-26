void nmult()
{
   TH1D* hmult[20];
   hmult[0] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[1] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptRecoNew_INCLMULT130TrkQual_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
//   hmult[1] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_PromptReco_INCLMULTPURej2sigma_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[9] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130NVTX1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[2] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130PURej2sigma_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[3] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130PURej1sigmaMode1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[4] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130PURej1sigma_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[5] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULTPURej2sigmaMode1_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[6] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_PromptRecoNew_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[7] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MB_PromptRecoNoPURej_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");
   hmult[10] = (TH1D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multrawall");

  hmult[0]->SetMarkerColor(1);
  hmult[1]->SetMarkerColor(2);
  hmult[2]->SetMarkerColor(3);
  hmult[3]->SetMarkerColor(4);
  hmult[4]->SetMarkerColor(6);
  hmult[9]->SetMarkerColor(7);
  hmult[5]->SetMarkerStyle(24);
  hmult[6]->SetMarkerStyle(22);
  hmult[7]->SetMarkerStyle(23);
  hmult[10]->SetMarkerStyle(24);

  hmult[0]->Rebin(5);
  hmult[1]->Rebin(5);
  hmult[2]->Rebin(5);
  hmult[3]->Rebin(5);
  hmult[4]->Rebin(5);
  hmult[5]->Rebin(5);
  hmult[6]->Rebin(5);
  hmult[7]->Rebin(5);
  hmult[9]->Rebin(5);
  hmult[10]->Rebin(5);

  hmult[5]->Scale(hmult[1]->GetBinContent(38)/hmult[5]->GetBinContent(38));
  hmult[6]->Scale(hmult[5]->GetBinContent(38)/hmult[6]->GetBinContent(38));
  hmult[7]->Scale(hmult[5]->GetBinContent(38)/hmult[7]->GetBinContent(38));
  hmult[10]->Scale(hmult[6]->Integral()/hmult[10]->Integral());

  TCanvas* c = new TCanvas("c","",550,500);
  c->SetLogy();
  hmult[1]->SetAxisRange(0,400,"X");
  hmult[1]->SetMaximum(hmult[5]->GetMaximum()*50);
  hmult[1]->SetTitle(";N_{trk}^{offline};a.u.");
  hmult[1]->GetXaxis()->CenterTitle();
  hmult[1]->GetYaxis()->CenterTitle();
  hmult[1]->Draw("PE");
/*
  hmult[2]->Draw("PESAME");
  hmult[3]->Draw("PESAME");
  hmult[4]->Draw("PESAME");
  hmult[9]->Draw("PESAME");
*/
  hmult[5]->Draw("PESAME");
//  hmult[6]->Draw("PESAME");
  hmult[6]->Draw("PESAME");
  TLegend* legend = new TLegend(0.35,0.74,0.95,0.9);
  legend->SetHeader("After PU rejection");
  legend->SetFillColor(0);
  legend->SetFillStyle(0);
  legend->AddEntry(hmult[5],"pPb MinBias, pilot","P");
  legend->AddEntry(hmult[6],"pPb MinBias","P");
  legend->AddEntry(hmult[1],"pPb HLT_PAPixelTracks_Multiplicity130","P");
  legend->Draw("PESAME");

//  SaveCanvas(c,"pPb/corr","mult_PUcompare_PURej");

  TCanvas* c1 = new TCanvas("c1","",550,500);
  c1->SetLogy();
  hmult[10]->SetAxisRange(0,700,"X");
  hmult[10]->SetXTitle("N_{trk}^{offline}");
  hmult[10]->GetXaxis()->CenterTitle();
  hmult[10]->Draw("PE");
  hmult[6]->Draw("PESAME");
  TLegend* legend1 = new TLegend(0.55,0.8,0.95,0.9);
//  legend1->SetHeader("After PU rejection");
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->AddEntry(hmult[6],"pPb MinBias","P");
  legend1->AddEntry(hmult[10],"PbPb 50-100%","P");
  legend1->Draw("PESAME");

  SaveCanvas(c1,"pPb/corr","mult_compare_pPbvsPbPb");
return;
  TH1D* hratio[10];
  TCanvas* ccc = new TCanvas("ccc","",550,500);
  hratio[1] = (TH1D*)hmult[1]->Clone("hratio1");
  hratio[2] = (TH1D*)hmult[2]->Clone("hratio2");
  hratio[3] = (TH1D*)hmult[3]->Clone("hratio3");
  hratio[4] = (TH1D*)hmult[4]->Clone("hratio4");
  hratio[9] = (TH1D*)hmult[9]->Clone("hratio9");
  
  hratio[2]->SetXTitle("N_{trk}^{offline}");
  hratio[2]->Divide(hratio[2],hratio[1],1,1,"b");
  hratio[3]->Divide(hratio[3],hratio[1],1,1,"b");
  hratio[4]->Divide(hratio[4],hratio[1],1,1,"b");
  hratio[9]->Divide(hratio[9],hratio[1],1,1,"b");
  hratio[2]->SetAxisRange(0,360,"X");
  hratio[2]->SetAxisRange(0,1.2,"Y");
  hratio[2]->Draw("PE");
  hratio[3]->Draw("PESAME");
  hratio[4]->Draw("PESAME");
  hratio[9]->Draw("PESAME");
  TLegend* legend1 = new TLegend(0.5,0.7,0.9,0.85);
  legend1->SetFillColor(0);
  legend1->AddEntry(hratio[2],"PURej2sigma","P");
  legend1->AddEntry(hratio[3],"PURej1sigmaMode1","P");
  legend1->AddEntry(hratio[4],"PURej1sigma","P");
  legend1->AddEntry(hratio[9],"NVTX1","P");
  legend1->Draw("PESAME");

//  SaveCanvas(ccc,"pPb/corr","ratio_PU_pPb");

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

void nsec()
{
  TH2D* h = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_PeripheralNew_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssec");
  TH2D* h2 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssec");
  TH2D* h3 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","multmaxvssec");

  TH1D* hprof = h->ProjectionY("hprof",201,220,"e");
  TH1D* hprof2 = h2->ProjectionY("hprof2",201,220,"e");
  TH1D* hprof3 = h3->ProjectionY("hprof3",201,220,"e");

  hprof->SetMarkerColor(4);
  hprof2->SetMarkerColor(2);
  hprof3->SetMarkerColor(3);
  hprof->Scale(1.0/hprof->Integral());
  hprof2->Scale(1.0/hprof2->Integral());
  hprof3->Scale(1.0/hprof3->Integral());

  TCanvas* c = new TCanvas("c","c",550,500);
  c->SetLogy();
  hprof->SetXTitle("N_{trk}^{secondary}");
  hprof->GetXaxis()->CenterTitle();
  hprof->SetAxisRange(0,50,"X");
  hprof->Draw("PE");
  hprof2->Draw("PESAME");

  TLegend* legend = new TLegend(0.5,0.74,0.95,0.9);
  legend->SetHeader("200<N_{trk}^{primary}<220");
  legend->SetFillColor(0);
  legend->SetFillStyle(0);
  legend->AddEntry(hprof2,"pPb pilot","P");
  legend->AddEntry(hprof,"PbPb Hydjet","P");
  legend->Draw("PESAME");

  SaveCanvas(c,"pPb/corr","nsec_compare_npri200220");
}


void nvtx()
{
  TH2D* hNvtxVsMult = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_MBNEW_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
  TH2D* hNvtxVsMult1 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
  TH2D* hNvtxVsMult2 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/PAData_Minbias_5TeV/merged/PAData_Minbias_5TeV_HM_PromptReco_INCLMULT130PURej2sigma_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
  TH2D* hNvtxVsMult3 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HIData_Minbias_2760GeV/merged/HIData_Minbias_2760GeV_PPRereco_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");
  TH2D* hNvtxVsMult4 = (TH2D*)GetHist("/net/hisrv0001/home/davidlw/scratch1/DiHadronCorrelations/outputs_312/HydjetReco_Minbias_2760GeV/merged/HydjetReco_Minbias_2760GeV_PeripheralNew_INCLMULT_nmin-1_nmax-1_etatrg-2.4-2.4_etaass-2.4-2.4_centmin-1_centmax-1.root","nvtxvsnmult");

  TH1D* hnvtx = hNvtxVsMult->ProjectionY("hnvtx",201,220,"e");
  TH1D* hnvtx1 = hNvtxVsMult1->ProjectionY("hnvtx1",201,220,"e");
  TH1D* hnvtx2 = hNvtxVsMult2->ProjectionY("hnvtx2",201,220,"e");
  TH1D* hnvtx3 = hNvtxVsMult3->ProjectionY("hnvtx3",221,225,"e");
  TH1D* hnvtx4 = hNvtxVsMult4->ProjectionY("hnvtx4",221,222,"e");

  hnvtx->SetMarkerColor(1);
  hnvtx->SetMarkerStyle(24);
  hnvtx2->SetMarkerStyle(22);
  hnvtx1->SetMarkerColor(2);
  hnvtx3->SetMarkerColor(4);
  hnvtx4->SetMarkerColor(3);


  hnvtx->Scale(1.0/hnvtx->Integral());
  hnvtx1->Scale(1.0/hnvtx1->Integral());
  hnvtx2->Scale(1.0/hnvtx2->Integral());
  hnvtx3->Scale(1.0/hnvtx3->Integral());
  hnvtx4->Scale(1.0/hnvtx4->Integral());

  TCanvas* c = new TCanvas("c","c",550,500);
  hnvtx->SetAxisRange(1,5,"X");
  hnvtx->SetXTitle("# of vertices");
  hnvtx->Draw("PE");
  hnvtx1->Draw("PESAME");
  hnvtx2->Draw("PESAME");

  TLegend* legend = new TLegend(0.3,0.73,0.9,0.91);
  legend->SetHeader("N_{trk}^{offline}>=220");
  legend->SetFillColor(0);
  legend->AddEntry(hnvtx,"pPb pilot","P");
  legend->AddEntry(hnvtx1,"HLT_PAPixelTracks_Multiplicity130 w/o PU","P");
  legend->AddEntry(hnvtx2,"HLT_PAPixelTracks_Multiplicity130 with PU","P");
  legend->Draw("PESAME");

  SaveCanvas(c,"pPb/corr","nvtx_compare_HM");
}
