
#include "TLegend.h"

void ZAcc_syst()
{
// Matt's rootlogon
  gStyle->SetErrorX(0);
  gStyle->SetPalette(1,0);
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameLineColor(0);
  gStyle->SetTitleColor(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetPalette(1,0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameLineColor(0);
  gStyle->SetTextFont(62);
  gStyle->SetLabelFont(42,"XYZ");
  gStyle->SetTitleFont(42,"XYZ");
  gStyle->SetTitleColor(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleXSize(.055);
  //gStyle->SetTitleYSize(.055);
  //gStyle->SetTitleXSize(.075);
  gStyle->SetTitleYSize(.075);
  gStyle->SetTitleXOffset(1.0);
  gStyle->SetTitleYOffset(1.0);
  gStyle->SetLabelSize(0.045,"XYZ");
  gStyle->SetLabelOffset(0.01,"X");
  gStyle->SetLabelOffset(0.01,"Y");
  gStyle->SetTitleColor(1,"XYZ");
  gStyle->SetHistFillColor(1);
  gStyle->SetHistFillStyle(0);
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(3);
  gStyle->SetHistLineWidth(1);
  gStyle->SetEndErrorSize(0);
  gStyle->SetErrorX(0);
  gStyle->SetMarkerStyle(20);
  //gStyle->SetMarkerSize(1.25);
  gStyle->SetMarkerSize(.8);
  gStyle->SetOptFit(1111);
  gStyle->SetOptFit(0);
  gStyle->SetStatColor(0);
  gStyle->SetStatBorderSize(1);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(111);
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadTopMargin(0.14);
  gStyle->SetPadRightMargin(0.14);
  gROOT->ForceStyle();

  TText *tx= new TLatex(100,
			100,
			"CMS Preliminary");
  tx->SetTextAlign(22);
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  //  TFile *In = new TFile("pythiaZ0_nofilter_CTEQ6L1_re6_totevt100000_2DAllDimu.root");
  //  TFile *In = new TFile("MCNLOZ0_nofilter_CTEQ6M_re9_totevt100000_2DAllDimu_yz24_pt10cut_v2.root");
  TFile *In = new TFile("pythiaZ0_nofilter_CTEQ6L1_re6_totevt100000_2DAllDimu.root");
  //TFile *In = new TFile("/afs/cern.ch/user/h/hckim/public/AccStudy/pythiaZ0_nofilter_CTEQ6L1_re6_totevt100000_ckin1_20_ZmmAnav3_yz20_pt10cut_v3.root");

 double syst = 0.3;


 double  ymin = TwoNeuDimuYPt->GetXaxis()->FindBin(-2.0+0.0001);
 double  ymax = TwoNeuDimuYPt->GetXaxis()->FindBin(2.0-0.0001);
 //double  ymin = TwoNeuDimuYPt->GetXaxis()->FindBin(-5+0.0001);
 //double  ymax = TwoNeuDimuYPt->GetXaxis()->FindBin(5-0.0001);
double  ptmin = TwoNeuDimuYPt->GetYaxis()->FindBin(0.0+0.0001);
double  ptmax = TwoNeuDimuYPt->GetYaxis()->FindBin(50.0-0.0001);
 cout << " ==== REC int limit " << ymin<<","<<ymax<<","<<ptmin<<","<<ptmax<< endl;
  cout << "----- Int " << TwoNeuDimuYPt->Integral(ymin,ymax,ptmin,ptmax)<<endl;

  double ymin = TwoDenDimuYPt->GetXaxis()->FindBin(-2.0+0.0001);
  double ymax = TwoDenDimuYPt->GetXaxis()->FindBin(2.-0.0001);
  double ptmin = TwoDenDimuYPt->GetYaxis()->FindBin(0.0+0.0001);
  double ptmax = TwoDenDimuYPt->GetYaxis()->FindBin(50.0-0.0001);
 cout << " ==== GEN int limit " << ymin<<","<<ymax<<","<<ptmin<<","<<ptmax<< endl;
cout << "----- Int " << TwoDenDimuYPt->Integral(ymin,ymax,ptmin,ptmax)<<endl;
 cout << "*********"<<endl;

  double pt_min = TwoDenDimuYPt->GetYaxis()->FindBin(0);
  double pt_max = TwoDenDimuYPt->GetYaxis()->FindBin(50);
  cout << "pt min " << pt_min<< " max " << pt_max << endl;

  TH1D* ProjGenY = TwoDenDimuYPt->ProjectionX("ProjGenY",pt_min, pt_max, "e");  
  ProjGenY->Sumw2();

  //    double ybins[] = {-2.4,-1.,-0.5,0.5,1.,2.4};
  //   double nybins=5;
  double ybins[] = {-2,2};
    double nybins=1;

 ProjGenY->DrawCopy("same");
    
    TH1F* RebinRap = ProjGenY->Rebin(nybins,"GenRebinRap",ybins);
    for (int i=1;i<nybins+1;i++) {
      RebinRap->SetBinContent(i,RebinRap->GetBinContent(i)/RebinRap->GetBinWidth(i)/10);
      RebinRap->SetBinError(i,RebinRap->GetBinError(i)/RebinRap->GetBinWidth(i)/10);
      if(PrintAll)   cout << RebinRap->GetBinContent(i) << "/" << RebinRap->GetBinWidth(i) << endl;
    }
    
    RebinRap->SetLineColor(2);
    RebinRap->SetMarkerColor(2);
    RebinRap->DrawCopy("same");
    
    TH1F* SystRap_down = ProjGenY->Clone();
    SystRap_down->Sumw2();
    TH1F* SystRap_up = ProjGenY->Clone();
    SystRap_up->Sumw2();
   
 for (int i=1;i<ProjGenY->GetNbinsX();i++) {
    
      double abs_x = fabs(ProjGenY->GetXaxis()->GetBinCenter(i));
      double syst_down =syst*(-abs_x+1);
      double weight = (1+syst_down);
      if(PrintAll)   cout << "bin " << ProjGenY->GetXaxis()->GetBinCenter(i) << " abs" << abs_x << "init"<< ProjGenY->GetBinContent(i)<<"final" <<ProjGenY->GetBinContent(i)*weight <<endl;
      
      SystRap_down->SetBinContent(i,ProjGenY->GetBinContent(i)*weight);
    double syst_up =syst*(abs_x-1);
    double weight_up = (1+syst_up);
    SystRap_up->SetBinContent(i,ProjGenY->GetBinContent(i)*weight_up);
  }

  SystRap_up->SetLineColor(3);
  SystRap_up->SetMarkerColor(3);
 SystRap_up->DrawCopy("same");

  SystRap_down->SetLineColor(4);
  SystRap_down->SetMarkerColor(4);
 SystRap_down->DrawCopy("same");
  
  TLegend * legend_3 = new TLegend(.3, .2, .7, 0.4,NULL,"brNDC");
  legend_3->AddEntry(ProjGenY,"Pythia 6", "LP");
  legend_3->AddEntry(RebinRap,"Rebinned", "LP");
  legend_3->AddEntry(SystRap_up,"+20%", "LP");
  legend_3->AddEntry(SystRap_down,"-20%", "LP");
  legend_3->SetBorderSize(0);
  legend_3->SetFillStyle(0);
  legend_3->SetFillColor(0);
  legend_3->SetTextSize(0.04);
  legend_3->Draw();
  
  C5->Print("Gen_y.pdf");  

 /// Reco
 // Plotting y distributions and weighting
  TCanvas *CRec = new TCanvas ("RecY","RecY",600,600);

  TH1D* dummyRec = new TH1D("","",50,-2.5,2.5);
  dummyRec->SetMinimum(0.);
   dummyRec->SetMaximum(1500.);
  dummyRec->SetXTitle("Rapidity"); 
  dummyRec->SetYTitle("Rec");
   dummyRec->Draw();

  TH1D* ProjRecY = TwoNeuDimuYPt->ProjectionX("ProjRecY", pt_min, pt_max, "e");  
  ProjRecY->Sumw2();
  ProjRecY->DrawCopy("same");



  TH1F* RecbinRap = ProjRecY->Rebin(nybins,"RecRebinRap",ybins);
  for (int i=1;i<nybins+1;i++) {
    RecbinRap->SetBinContent(i,RecbinRap->GetBinContent(i)/RecbinRap->GetBinWidth(i)/10);
    RecbinRap->SetBinError(i,RecbinRap->GetBinError(i)/RecbinRap->GetBinWidth(i)/10);
    if(PrintAll)   cout << RecbinRap->GetBinContent(i) << "/" << RecbinRap->GetBinWidth(i) << endl;
  }

  RecbinRap->SetLineColor(2);
  RecbinRap->SetMarkerColor(2);
  RecbinRap->DrawCopy("same");

  TH1F* SystRap_down_rec = ProjRecY->Clone();
  SystRap_down_rec->Sumw2();
  TH1F* SystRap_up_rec = ProjRecY->Clone();
  SystRap_up_rec->Sumw2();
  for (int i=1;i<ProjRecY->GetNbinsX();i++) {
    
    double abs_x = fabs(ProjRecY->GetXaxis()->GetBinCenter(i));
    double syst_down =syst*(-abs_x+1);
    double weight = (1+syst_down);
    if(PrintAll)    cout << "bin " << ProjRecY->GetXaxis()->GetBinCenter(i) << " abs" << abs_x << "init"<< ProjRecY->GetBinContent(i)<<"final" <<ProjRecY->GetBinContent(i)*weight <<endl;

    SystRap_down_rec->SetBinContent(i,ProjRecY->GetBinContent(i)*weight);
    double syst_up =syst*(abs_x-1);
    double weight_up = (1+syst_up);
    SystRap_up_rec->SetBinContent(i,ProjRecY->GetBinContent(i)*weight_up);
  }
  SystRap_up_rec->SetLineColor(3);
  SystRap_up_rec->SetMarkerColor(3);
  SystRap_up_rec->DrawCopy("same");
  
  SystRap_down_rec->SetLineColor(4);
  SystRap_down_rec->SetMarkerColor(4);
  SystRap_down_rec->DrawCopy("same");
    
  TLegend * legend_2 = new TLegend(.3, .2, .7, 0.4,NULL,"brNDC");
  legend_2->AddEntry(ProjRecY,"Pythia 6", "LP");
  legend_2->AddEntry(RecbinRap,"Rebinned", "LP");
  legend_2->AddEntry(SystRap_up_rec,"+20%", "LP");
  legend_2->AddEntry(SystRap_down_rec,"-20%", "LP");
  legend_2->SetBorderSize(0);
  legend_2->SetFillStyle(0);
  legend_2->SetFillColor(0);
  legend_2->SetTextSize(0.04);
  legend_2->Draw();

  CRec->Print("Rec_y.pdf");  

  
  ///////// Acc vs. y
  TCanvas *C4 = new TCanvas("AccVsY","Z acceptance syst vs y, |eta|<2.0 and p_T>10 GeV  ",600,600);

  TH1D* dummy2 = new TH1D("","",50,-2.5,2.5);
  dummy2->SetMinimum(0.);
  dummy2->SetMaximum(1.);
  dummy2->SetXTitle("Rapidity"); 
  dummy2->SetYTitle("Acceptance");
  dummy2->Draw();

  TH1F* ProjAccY =   ProjRecY->Clone();
  if(PrintAll)cout << " bin rec : " << ProjRecY->GetNbinsX()<< " /bin gen " << ProjGenY->GetNbinsX()<<endl; 

  for (int i=1;i<ProjGenY->GetNbinsX();i++) {
    if(ProjGenY->GetBinContent(i)!=0){
      if(PrintAll)  cout << "i " << i << " rec " <<ProjRecY->GetBinContent(i) << " gen "<<ProjGenY->GetBinContent(i);
      if(PrintAll)cout << " acc " << ProjRecY->GetBinContent(i) /ProjGenY->GetBinContent(i)<<endl;
    }}

  ProjAccY->Divide(ProjRecY,ProjGenY,1,1,"B"); 
  ProjAccY->Draw("SAME,E");
       
  TH1F* ProjAccY_rebin =   RebinRap->Clone();
  ProjAccY_rebin->Sumw2();
  for (int i=1;i<RebinRap->GetNbinsX();i++) {
     if(RebinRap->GetBinContent(i)!=0){
  if(PrintAll)   cout << "i " << i << " rec " <<RecbinRap->GetBinContent(i) << " gen "<<RebinRap->GetBinContent(i);
       
     }}
    
  ProjAccY_rebin->Divide(RecbinRap,RebinRap,1,1,"B"); 
  ProjAccY_rebin->SetMarkerColor(2);
  ProjAccY_rebin->SetLineColor(2);
  ProjAccY_rebin->Draw("SAME,E");

  TH1F* SystRap_up_rebin =   SystRap_up->Rebin(nybins,"SystRap_up_rebin",ybins);//Clone();
  TH1F* SystRap_up_rec_rebin =   SystRap_up_rec->Rebin(nybins,"SystRap_up_rec_rebin",ybins);//Clone();
  for (int i=1;i<nybins+1;i++) {
       SystRap_up_rebin->SetBinContent(i,SystRap_up_rebin->GetBinContent(i)/SystRap_up_rebin->GetBinWidth(i)/10);
       SystRap_up_rebin->SetBinError(i,SystRap_up_rebin->GetBinError(i)/SystRap_up_rebin->GetBinWidth(i)/10);
      if(PrintAll)   cout << SystRap_up_rebin->GetBinContent(i) << "/" << SystRap_up_rebin->GetBinWidth(i) << endl;
       SystRap_up_rec_rebin->SetBinContent(i,SystRap_up_rec_rebin->GetBinContent(i)/SystRap_up_rec_rebin->GetBinWidth(i)/10);
       SystRap_up_rec_rebin->SetBinError(i,SystRap_up_rec_rebin->GetBinError(i)/SystRap_up_rec_rebin->GetBinWidth(i)/10);
       if(PrintAll)   cout << SystRap_up_rec_rebin->GetBinContent(i) << "/" << SystRap_up_rec_rebin->GetBinWidth(i) << endl;
  }
  TH1F * ProjAccY_rebin_up= SystRap_up_rebin->Clone();

  ProjAccY_rebin_up->Divide(SystRap_up_rec_rebin,SystRap_up_rebin,1,1,"B"); 
  ProjAccY_rebin_up->SetMarkerColor(3);
  ProjAccY_rebin_up->SetLineColor(3);
  ProjAccY_rebin_up->Draw("SAME,E");
    
  TH1F* SystRap_down_rebin =   SystRap_down->Rebin(nybins,"SystRap_down_rebin",ybins);//Clone();
  TH1F* SystRap_down_rec_rebin =   SystRap_down_rec->Rebin(nybins,"SystRap_down_rec_rebin",ybins);//Clone();
  for (int i=1;i<nybins+1;i++) {
       SystRap_down_rebin->SetBinContent(i,SystRap_down_rebin->GetBinContent(i)/SystRap_down_rebin->GetBinWidth(i)/10);
       SystRap_down_rebin->SetBinError(i,SystRap_down_rebin->GetBinError(i)/SystRap_down_rebin->GetBinWidth(i)/10);
       if(PrintAll)   cout << SystRap_down_rebin->GetBinContent(i) << "/" << SystRap_down_rebin->GetBinWidth(i) << endl;
       SystRap_down_rec_rebin->SetBinContent(i,SystRap_down_rec_rebin->GetBinContent(i)/SystRap_down_rec_rebin->GetBinWidth(i)/10);
       SystRap_down_rec_rebin->SetBinError(i,SystRap_down_rec_rebin->GetBinError(i)/SystRap_down_rec_rebin->GetBinWidth(i)/10);
       if(PrintAll)   cout << SystRap_down_rec_rebin->GetBinContent(i) << "/" << SystRap_down_rec_rebin->GetBinWidth(i) << endl;
  }
  TH1F * ProjAccY_rebin_down= SystRap_down_rebin->Clone();

  ProjAccY_rebin_down->Divide(SystRap_down_rec_rebin,SystRap_down_rebin,1,1,"B"); 
  ProjAccY_rebin_down->SetMarkerColor(4);
  ProjAccY_rebin_down->SetLineColor(4);
    ProjAccY_rebin_down->Draw("SAME,E");



 TLegend * legend_1 = new TLegend(.3, .2, .7, 0.4,NULL,"brNDC");
 legend_1->AddEntry(ProjAccY,"Acc Pythia 6", "LP");
 //legend_1->AddEntry(ProjAccY_rebin,"Rebinned", "LP");
 //legend_1->AddEntry(ProjAccY_rebin_up,"+20%", "LP");
 //legend_1->AddEntry(ProjAccY_rebin_down,"-20%", "LP");
 legend_1->SetBorderSize(0);
 legend_1->SetFillStyle(0);
 legend_1->SetFillColor(0);
 legend_1->SetTextSize(0.04);
 legend_1->Draw();

  C4->Print("Acc_y.pdf");  

  cout << "bin & acc default & up & down \\"<<endl;
  for(int i=1;i<nybins+1;i++){
    char name[500];
    sprintf(name,"%.1f",(ProjAccY_rebin->GetBinContent(i))*100);
    char nameErr[500];
    sprintf(nameErr,"%.1f",(ProjAccY_rebin->GetBinError(i))*100);
    char nameup[500];
    sprintf(nameup,"%.1f",(ProjAccY_rebin_up->GetBinContent(i))*100);
    char nameErrup[500];
    sprintf(nameErrup,"%.1f",(ProjAccY_rebin_up->GetBinError(i))*100);
    char namedown[500];
    sprintf(namedown,"%.1f",(ProjAccY_rebin_down->GetBinContent(i))*100);
    char nameErrdown[500];
    sprintf(nameErrdown,"%.1f",(ProjAccY_rebin_down->GetBinError(i))*100);
    cout << i<< " & " << name << " \pm "  << nameErr<<" & " << nameup << " \pm "  << nameErrup<<" & " << namedown << " \pm "  << nameErrdown<<" \\ "<< endl;
  }
  //////// pt now 
  
  // Plotting y distributions and weighting
  TCanvas *C9 = new TCanvas ("GenPt","GenPt",600,600);

  TH1D* dummy1 = new TH1D("","",50,0,50);
  dummy1->SetMinimum(0.);
  dummy1->SetMaximum(4000);
  dummy1->SetXTitle("Pt"); 
   dummy1->SetYTitle("Gen");
  dummy1->Draw();

  double y_min = TwoDenDimuYPt->GetXaxis()->FindBin(-2);
  double y_max = TwoDenDimuYPt->GetXaxis()->FindBin(2);
  if(PrintAll)cout << "y min " << y_min<< " max " << y_max << endl;

  TH1D* ProjGenPt = TwoDenDimuYPt->ProjectionY("ProjGenPt", y_min, y_max, "e");  
  ProjGenPt->Sumw2();

  //  double ptbins[] = {0.,6.,12.,50.};
  //double nptbins =3;
  double ptbins[] = {0.,50.};
  double nptbins =1;
  ProjGenPt->DrawCopy("same");

  TH1F* RebinPt = ProjGenPt->Rebin(nptbins,"GenRebinPt",ptbins);
  for (int i=1;i<nptbins+1;i++) {
    RebinPt->SetBinContent(i,RebinPt->GetBinContent(i)/RebinPt->GetBinWidth(i));
    RebinPt->SetBinError(i,RebinPt->GetBinError(i)/RebinPt->GetBinWidth(i));
    if(PrintAll)cout << RebinPt->GetBinContent(i) << "/" << RebinPt->GetBinWidth(i) << " err:"<< RebinPt->GetBinError(i) <<endl;
  }

  RebinPt->SetLineColor(2);
  RebinPt->SetMarkerColor(2);
  RebinPt->DrawCopy("same");

  TH1F* SystPt_down = ProjGenPt->Clone();
  TH1F* SystPt_up = ProjGenPt->Clone();
  for (int i=1;i<ProjGenPt->GetNbinsX();i++) {
    
    double abs_x = fabs(ProjGenPt->GetXaxis()->GetBinCenter(i));
    double syst_down =syst*(-0.04*abs_x+1);
    double weight = (1+syst_down);
  if(PrintAll)   cout << "bin " << ProjGenPt->GetXaxis()->GetBinCenter(i) << " abs" << abs_x << "init"<< ProjGenPt->GetBinContent(i)<<"final" <<ProjGenPt->GetBinContent(i)*weight <<endl;

    SystPt_down->SetBinContent(i,ProjGenPt->GetBinContent(i)*weight);
    double syst_up =syst*(0.04*abs_x-1);
    double weight_up = (1+syst_up);
    SystPt_up->SetBinContent(i,ProjGenPt->GetBinContent(i)*weight_up);
  }
  SystPt_up->SetLineColor(3);
  SystPt_up->SetMarkerColor(3);
 SystPt_up->DrawCopy("same");

  SystPt_down->SetLineColor(4);
  SystPt_down->SetMarkerColor(4);
 SystPt_down->DrawCopy("same");
  
  TLegend * legend_3Pt = new TLegend(.5, .6, .8, 0.8,NULL,"brNDC");
  legend_3Pt->AddEntry(ProjGenPt,"Pythia 6", "LP");
  legend_3Pt->AddEntry(RebinPt,"Rebinned", "LP");
  legend_3Pt->AddEntry(SystPt_up,"+20%", "LP");
  legend_3Pt->AddEntry(SystPt_down,"-20%", "LP");
  legend_3Pt->SetBorderSize(0);
  legend_3Pt->SetFillStyle(0);
  legend_3Pt->SetFillColor(0);
  legend_3Pt->SetTextSize(0.04);
  legend_3Pt->Draw();
  C9->Print("Gen_pt.pdf");  

 /// Reco
 // Plotting y distributions and weighting
  TCanvas *CRecPt = new TCanvas ("RecPt","RecPt",600,600);

  TH1D* dummyRec = new TH1D("","",50,0,50);
  dummyRec->SetMinimum(0.);
   dummyRec->SetMaximum(4000.);
  dummyRec->SetXTitle("Pt"); 
  dummyRec->SetYTitle("Rec");
   dummyRec->Draw();


   if(PrintAll)  cout << "y min " << y_min<< " max " << y_max << endl;
   //TH1D* ProjRecPt = TwoNeuDimuYPt->ProjectionY(); 
    TH1D* ProjRecPt = TwoNeuDimuYPt->ProjectionY("ProjRecPt", y_min, y_max, "e"); 
  ProjRecPt->Sumw2();

  ProjRecPt->DrawCopy("same");
  
  TH1F* RecbinPt = ProjRecPt->Rebin(nptbins,"RecRebinPt",ptbins);
  for (int i=1;i<nptbins+1;i++) {
    RecbinPt->SetBinContent(i,RecbinPt->GetBinContent(i)/RecbinPt->GetBinWidth(i));
    RecbinPt->SetBinError(i,RecbinPt->GetBinError(i)/RecbinPt->GetBinWidth(i));
    if(PrintAll)  cout << RecbinPt->GetBinContent(i) << "/" << RecbinPt->GetBinWidth(i) << endl;
  }

  RecbinPt->SetLineColor(2);
  RecbinPt->SetMarkerColor(2);
  RecbinPt->DrawCopy("same");
  
 TH1F* SystPt_down_rec = ProjRecPt->Clone();
  TH1F* SystPt_up_rec = ProjRecPt->Clone();
  for (int i=1;i<ProjRecPt->GetNbinsX();i++) {
    
    double abs_x = fabs(ProjRecPt->GetXaxis()->GetBinCenter(i));
    double syst_down =syst*(-0.04*abs_x+1);
    double weight = (1+syst_down);
    if(PrintAll)    cout << "bin " << ProjRecY->GetXaxis()->GetBinCenter(i) << " abs" << abs_x << "init"<< ProjRecY->GetBinContent(i)<<"final" <<ProjRecY->GetBinContent(i)*weight <<endl;

    SystPt_down_rec->SetBinContent(i,ProjRecPt->GetBinContent(i)*weight);
    double syst_up =syst*(0.04*abs_x-1);
    double weight_up = (1+syst_up);
    SystPt_up_rec->SetBinContent(i,ProjRecPt->GetBinContent(i)*weight_up);
  }
  SystPt_up_rec->SetLineColor(3);
  SystPt_up_rec->SetMarkerColor(3);
  SystPt_up_rec->DrawCopy("same");
  
  SystPt_down_rec->SetLineColor(4);
  SystPt_down_rec->SetMarkerColor(4);
  SystPt_down_rec->DrawCopy("same");
    
  TLegend * legend_2Pt = new TLegend(.5, .6, .8, 0.8,NULL,"brNDC");
  legend_2Pt->AddEntry(ProjRecY,"Pythia 6", "LP");
  legend_2Pt->AddEntry(RecbinPt,"Rebinned", "LP");
  legend_2Pt->AddEntry(SystPt_up_rec,"+20%", "LP");
  legend_2Pt->AddEntry(SystPt_down_rec,"-20%", "LP");
  legend_2Pt->SetBorderSize(0);
  legend_2Pt->SetFillStyle(0);
  legend_2Pt->SetFillColor(0);
  legend_2Pt->SetTextSize(0.04);
  legend_2Pt->Draw();

  CRecPt->Print("Rec_pt.pdf");  

  
  ///////// Acc vs. y
  TCanvas *C4Pt = new TCanvas("AccVsPt","Z acceptance syst vs Pt, |eta|<2.0 and p_T>10 GeV  ",600,600);


  TH1D* dummy1 = new TH1D("","",50,0,50);
  dummy1->SetMinimum(0.);
  dummy1->SetMaximum(1.);
  dummy1->SetXTitle("pt"); 
  dummy1->SetYTitle("Acceptance");
  dummy1->Draw();

  TH1F* ProjAccPt =   ProjRecPt->Clone();
  for (int i=1;i<ProjGenPt->GetNbinsX();i++) {
    if(ProjGenPt->GetBinContent(i)!=0){
      if(PrintAll)       cout << "i " << i << " rec " <<ProjRecPt->GetBinContent(i) << " gen "<<ProjGenPt->GetBinContent(i);
      if(PrintAll)          cout << " acc " << ProjRecPt->GetBinContent(i) /ProjGenPt->GetBinContent(i)<<endl;
    }}
  
  ProjAccPt->Divide(ProjRecPt,ProjGenPt,1,1,"B"); 
  ProjAccPt->Draw("SAME,E");
 
       
  TH1F* ProjAccPt_rebin =   RebinPt->Clone();
  for (int i=1;i<RebinPt->GetNbinsX();i++) {
     if(RebinPt->GetBinContent(i)!=0){
       if(PrintAll)    cout << "i " << i << " rec " <<RecbinPt->GetBinContent(i) << " gen "<<RebinPt->GetBinContent(i);
       if(PrintAll) cout << " acc " << RecbinPt->GetBinContent(i) /RebinPt->GetBinContent(i)<<endl;
     }}
  ProjAccPt_rebin->Divide(RecbinPt,RebinPt,1,1,"B"); 
  ProjAccPt_rebin->SetMarkerColor(2);
  ProjAccPt_rebin->SetLineColor(2);
  ProjAccPt_rebin->Draw("SAME,E");

 
  TH1F* SystPt_up_rebin =   SystPt_up->Rebin(nptbins,"SystPt_up_rebin",ptbins);//Clone();
  TH1F* SystPt_up_rec_rebin =   SystPt_up_rec->Rebin(nptbins,"SystPt_up_rec_rebin",ptbins);//Clone();
  for (int i=1;i<nptbins+1;i++) {
       SystPt_up_rebin->SetBinContent(i,SystPt_up_rebin->GetBinContent(i)/SystPt_up_rebin->GetBinWidth(i));
       SystPt_up_rebin->SetBinError(i,SystPt_up_rebin->GetBinError(i)/SystPt_up_rebin->GetBinWidth(i));
       if(PrintAll)        cout << SystPt_up_rebin->GetBinContent(i) << "/" << SystPt_up_rebin->GetBinWidth(i) << " ="<<SystPt_up_rebin->GetBinContent(i) / SystPt_up_rebin->GetBinWidth(i) << "err:" <<  SystPt_up_rebin->GetBinError(i)<< endl;
       
       SystPt_up_rec_rebin->SetBinContent(i,SystPt_up_rec_rebin->GetBinContent(i)/SystPt_up_rec_rebin->GetBinWidth(i)); 
       SystPt_up_rec_rebin->SetBinError(i,SystPt_up_rec_rebin->GetBinError(i)/SystPt_up_rec_rebin->GetBinWidth(i));
       if(PrintAll)  cout << SystPt_up_rec_rebin->GetBinContent(i) << "/" << SystPt_up_rec_rebin->GetBinWidth(i)  << " ="<<SystPt_up_rec_rebin->GetBinContent(i) / SystPt_up_rec_rebin->GetBinWidth(i) <<" err:" <<  SystPt_up_rec_rebin->GetBinError(i)<< endl;
  }
  TH1F * ProjAccPt_rebin_up= SystPt_up_rebin->Clone();

  ProjAccPt_rebin_up->Divide(SystPt_up_rec_rebin,SystPt_up_rebin,1,1,"B"); 
  ProjAccPt_rebin_up->SetMarkerColor(3);
  ProjAccPt_rebin_up->SetLineColor(3);
  ProjAccPt_rebin_up->Draw("SAME,E");

 TH1F* SystPt_down_rebin =   SystPt_down->Rebin(nptbins,"SystPt_down_rebin",ptbins);//Clone();
  TH1F* SystPt_down_rec_rebin =   SystPt_down_rec->Rebin(nptbins,"SystPt_down_rec_rebin",ptbins);//Clone();
  for (int i=1;i<nptbins+1;i++) {
	SystPt_down_rebin->SetBinContent(i,SystPt_down_rebin->GetBinContent(i)/SystPt_down_rebin->GetBinWidth(i));
	SystPt_down_rebin->SetBinError(i,SystPt_down_rebin->GetBinError(i)/SystPt_down_rebin->GetBinWidth(i));
	if(PrintAll)    cout << SystPt_down_rebin->GetBinContent(i) << "/" << SystPt_down_rebin->GetBinWidth(i) << endl;
	SystPt_down_rec_rebin->SetBinContent(i,SystPt_down_rec_rebin->GetBinContent(i)/SystPt_down_rec_rebin->GetBinWidth(i));
	SystPt_down_rec_rebin->SetBinError(i,SystPt_down_rec_rebin->GetBinError(i)/SystPt_down_rec_rebin->GetBinWidth(i));
	if(PrintAll)   cout << SystPt_down_rec_rebin->GetBinContent(i) << "/" << SystPt_down_rec_rebin->GetBinWidth(i) << endl;
  }
  TH1F * ProjAccPt_rebin_down= SystPt_down_rebin->Clone();

  ProjAccPt_rebin_down->Divide(SystPt_down_rec_rebin,SystPt_down_rebin,1,1,"B"); 
  ProjAccPt_rebin_down->SetMarkerColor(4);
  ProjAccPt_rebin_down->SetLineColor(4);
  ProjAccPt_rebin_down->Draw("SAME,E");




 TLegend * legend_1Pt = new TLegend(.3, .2, .7, 0.4,NULL,"brNDC");
 legend_1Pt->AddEntry(ProjAccPt,"Acc Pythia 6", "LP");
 // legend_1Pt->AddEntry(ProjAccPt_rebin,"Rebinned", "LP");
 //legend_1Pt->AddEntry(ProjAccPt_rebin_up,"+20%", "LP");
 //legend_1Pt->AddEntry(ProjAccPt_rebin_down,"-20%", "LP");
 legend_1Pt->SetBorderSize(0);
 legend_1Pt->SetFillStyle(0);
 legend_1Pt->SetFillColor(0);
 legend_1Pt->SetTextSize(0.04);
 legend_1Pt->Draw();
 
 bool dofit=true;
 if(dofit){
   ProjAccPt->Fit("pol0","","");
   ProjAccPt_rebin->Fit("pol0","","");
  ProjAccPt_rebin_up->Fit("pol0","","");
  ProjAccPt_rebin_down->Fit("pol0","","");
 }
  
  C4Pt->Print("Acc_pt.pdf");  

  cout << "bin & acc default & up & down \\"<<endl;
  for(int i=1;i<nptbins+1;i++){
    char name[500];
    sprintf(name,"%.1f",(ProjAccPt_rebin->GetBinContent(i))*100);
    char nameErr[500];
    sprintf(nameErr,"%.1f",(ProjAccPt_rebin->GetBinError(i))*100);
    char nameup[500];
    sprintf(nameup,"%.1f",(ProjAccPt_rebin_up->GetBinContent(i))*100);
    char nameErrup[500];
    sprintf(nameErrup,"%.1f",(ProjAccPt_rebin_up->GetBinError(i))*100);
    char namedown[500];
    sprintf(namedown,"%.1f",(ProjAccPt_rebin_down->GetBinContent(i))*100);
    char nameErrdown[500];
    sprintf(nameErrdown,"%.1f",(ProjAccPt_rebin_down->GetBinError(i))*100);
    cout << i<< " & " << name << " \pm "  << nameErr<<" & " << nameup << " \pm "  << nameErrup<<" & " << namedown << " \pm "  << nameErrdown<<" \\ "<< endl;
  }
 


}
