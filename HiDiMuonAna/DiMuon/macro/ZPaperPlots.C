void ZPaperPlots()
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
  gStyle->SetStatColor(0);
  gStyle->SetStatBorderSize(1);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetPadLeftMargin(0.17);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.04);
  gROOT->ForceStyle();

  TText *tx= new TLatex(100,
			100,
			"CMS Preliminary");
  tx->SetTextAlign(22);
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *C1 = new TCanvas("ZY","Z versus rapidity",500,500);

  // From Hannu and Carlos
  // The result for the total dimuon cross-section with CT10&EPS09:
  // A = 208, Z = 82, Sqrt(s) = 2.76 TeV
  // M2 = Integrated over the interval 80-100GeV
  // Rapidity integrated over the whole phase space.

  //  Sigma total  Error CT10   Error EPS09    Error Total
  // 264.6 pb     +- 9.7 pb     +- 5.0  pb    +- 10.9 pb

  // The result for the total dimuon cross-section with CT10
  // (only isospin effects, no nuclear effects in PDFs):

  // Sigma total   Error CT10
  // 277.7 pb      +- 10.3 pb

  Double_t EPS09_rap[20] = {0,0.17,0.33,0.50,0.66,0.83,1.00,1.16,1.33,1.49,1.66,1.82,1.99,2.16,2.32,2.49,2.65,2.82,2.99,3.15};
  Double_t EPS09_sig[20] = {64.75,64.57,64.15,63.39,62.25,60.74,58.81,56.59,54.17,51.39,48.12,43.88,38.70,32.63,25.76,18.61,11.83,6.28,2.54,0.68};
  Double_t EPS09_err[20] = {4.49,4.36,4.08,3.68,3.23,2.82,2.54,2.74,2.51,2.62,2.66,2.66,2.53,2.31,1.96,1.53,1.06,0.62,0.29,0.14};

  // The results for the dimuon rapidity distribution with CT10 (only isospin effects, no nuclear effects in PDFs):

  Double_t CT10_sig[20] = {62.12,62.07,61.93,61.67,61.27,60.73,59.94,58.85,57.36,55.31,52.52,48.97,44.12,38.23,31.22,23.4,15.5,8.52,3.47,0.83};
  Double_t CT10_err[20] = {3.12,3.09,3.00,2.85,2.68,2.51,2.35,2.22,2.14,2.08,2.02,1.93,1.80,1.61,1.36,1.07,0.77,0.49,0.27,0.14};

  // Scale by AxA
  for (int i=0;i<20;i++) {
    EPS09_sig[i] *= 43264 ;    EPS09_sig[i] /= 1E6 ;
    EPS09_err[i] *= 43264 ;    EPS09_err[i] /= 1E6 ;
    CT10_sig[i] *= 43264 ;    CT10_sig[i] /= 1E6 ;
    CT10_err[i] *= 43264 ;    CT10_err[i] /= 1E6 ;
  }

  int Colpp = 1; 
  int ColIso = 7;
  int ColPbPb = 2;

  int MarkCarlos = 20;
  int MarkIvan = 21;

  TGraphErrors *EPS09_graf = new TGraphErrors(20,EPS09_rap,EPS09_sig,0,EPS09_err); 
  EPS09_graf->SetMarkerStyle(MarkCarlos);
  EPS09_graf->SetMarkerColor(ColPbPb); // Red for PbPb

  TGraphErrors *CT10_graf = new TGraphErrors(20,EPS09_rap,CT10_sig,0,CT10_err); 
  CT10_graf->SetMarkerStyle(MarkCarlos);
  CT10_graf->SetMarkerColor(Colpp); // Black for pp

  // From Ivan
  // 1. The total cross section in the specified region in the dimuon chanel: Everything s in femtobarns
  // 203251 +/-          163    fb     (203 pb)
  // The differential distribution vs y34  the rapidity of the dilepton pair.
  // Note that things should be plotted integrated histogram style with the bin symmetric around the quoted value

  Double_t Ivan_rap[16] = {-3.0,-2.6,-2.2,-1.8,-1.4,-1.0,-0.6,-0.2, 0.2, 0.6, 1.0, 1.4, 1.8, 2.2, 2.6, 3.0};
  Double_t Ivan_sig[16] = {0.00000, 0.00000, 6097.51, 23867.1, 42369.8, 55163.0, 61832.4, 64858.7, 64175.7, 62141.2, 55301.9, 42070.1, 24100.1, 6236.67, 0.00000, 0.00000};

  // Now with isospin
  // 1. sigma  209.1 pb +-.2    (+-.2 is just he MC accuracy) 
  // 2.   Dsiga dY34 (rapidity of the dilepton pair)      below it is in femtobarns

  Double_t Ivaniso_sig[16] = {0.00000,0.00000,6440.17,24743.3,43857.9,56700.4,63380.6,66207.3,65567.7,63668.0,56875.2,43582.7,25083.6,6553.41,0.00000,0.00000};

  for (int i=0;i<16;i++) {
    Ivan_sig[i] *= 43364 ; Ivan_sig[i] /= 1E9 ;
    Ivaniso_sig[i] *= 43264 ; Ivaniso_sig[i] /= 1E9 ;
    // cout << Ivan_sig[i] << endl;
  }

  TGraphErrors *Ivan_graf = new TGraphErrors(16,Ivan_rap,Ivan_sig,0,0); 
  Ivan_graf->SetMarkerStyle(MarkIvan);
  Ivan_graf->SetMarkerColor(Colpp); // Black for pp

  TGraphErrors *Ivaniso_graf = new TGraphErrors(16,Ivan_rap,Ivaniso_sig,0,0); 
  Ivaniso_graf->SetMarkerStyle(MarkIvan);
  Ivaniso_graf->SetMarkerColor(ColIso); // Purple for isospin

  TH1F *dummy = new TH1F("","",40,0.,4.);
  dummy->SetMinimum(0.);
  dummy->SetMaximum(4.);
  dummy->SetXTitle("Rapidity");
  dummy->SetYTitle("d#sigma/dy (#mub)");
  dummy->Draw();

  EPS09_graf->Draw("P");
  CT10_graf->Draw("P");
  Ivan_graf->Draw("P");
  Ivaniso_graf->Draw("P");


  // Our data, in dN/dy
  Double_t x_rap[3] = {0.25,0.75,1.7};
  Double_t Z_rap[3] = {4.22E-07,
		       3.63E-07,
		       2.60E-07
		       };
  Double_t Z_rap_e[3] = {1.17E-07,
			 1.09E-07,
			 7.22E-08
  };
  Double_t e_rap[3] = {0.25,0.25,0.7};

  // 
  for (int i=0;i<3;i++) {
    Z_rap[i] *= 7.650E6 ; Z_rap_e[i] *= 7.650E6 ;
  }

  int MarkUs = 21 ; 
  int ColUs = kGreen +2;
  int SizUs = 1.5 ;

  TGraphErrors *Zrap_graf = new TGraphErrors(3,x_rap,Z_rap,e_rap,Z_rap_e); 
  Zrap_graf->SetMarkerStyle(MarkUs);
  Zrap_graf->SetMarkerColor(ColUs);
  Zrap_graf->SetMarkerSize(SizUs);
  Zrap_graf->Draw("P");
  C1->Print("ZY.pdf"); 


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *C2 = new TCanvas("ZPT","Z versus transverse momentum",500,500);
  C2->SetLogy();

 //T distribution  (we checked that at LO it is) exactly at 0 program puts it at 1 gev since the bin is 0-2 GeV, see my nt above)

  Double_t Ivan_pt[50] = {1.,3.,5.,7.,9.,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89,91,93,95,97,99};
  Double_t Ivan_sig_pt[50] = {5051.3,34793.,16462.,9961.2,6734.33,4895.96,3697.55,2901.74,2325.82,1916.87,1581.45,1339.24,1137.08,976.057,839.472,732.849,643.008,563.936,494.014,443.095,390.616,350.563,312.855,282.245,253.257,227.519,201.905,189.022,168.621,149.557,136.984,123.562,112.623,104.982,93.0248,85.3706,80.3332,70.4107,64.1783,58.2423,55.1995,50.1423,44.6478,41.3786,38.3456,35.0174,32.4205,29.6368,27.2063,24.8434};

  Double_t Ivaniso_sig_pt[50] = {4895.43,35837.4,17001.6,10240.7,6935.48,5027.13,3843.81,2988.97,2431.89,1978.87,1639.69,1378.93,1164.79,1013.45,873.330,750.752,658.838,587.341,509.177,455.536,414.566,355.557,322.083,292.399,260.906,235.761,211.652,194.367,174.420,157.444,141.644,130.159,116.344,106.940,100.338,90.4371,80.8616,71.8951,67.1495,62.4207,56.8685,51.7799,46.6831,44.6836,39.9829,36.7482,34.2372,30.4509,28.8633,26.9952};

  for (int i=0;i<49;i++) {
    Ivan_sig_pt[i] *= 43264 ; Ivan_sig_pt[i] /= 1E9 ; Ivan_sig_pt[i] /= 4.8 ;
    Ivaniso_sig_pt[i] *= 43264 ; Ivaniso_sig_pt[i] /= 1E9 ; Ivaniso_sig_pt[i] /= 4.8 ; 
  }

  TGraphErrors *Ivan_pt_graf = new TGraphErrors(49,Ivan_pt,Ivan_sig_pt,0,0); 
  Ivan_pt_graf->SetMarkerStyle(MarkIvan);
  Ivan_pt_graf->SetMarkerColor(Colpp); // Black for pp

  TGraphErrors *Ivaniso_pt_graf = new TGraphErrors(49,Ivan_pt,Ivaniso_sig_pt,0,0); 
  Ivaniso_pt_graf->SetMarkerStyle(MarkIvan);
  Ivaniso_pt_graf->SetMarkerColor(ColIso); 

  TH1F *dummy = new TH1F("","",50,0.,50.);
  dummy->SetMinimum(0.002);
  dummy->SetMaximum(1.);
  dummy->SetXTitle("Transverse momentum (GeV/c)");
  dummy->SetYTitle("d^{2}#sigma/dydp_{T} (#mub/GeV)");
  dummy->Draw();

  Ivan_pt_graf->Draw("P");
  Ivaniso_pt_graf->Draw("P");

  // Our data, in dN/dydpt
  Double_t x_pt[3] = {3,9,31};
  Double_t e_pt[3] = {3,3,19};
  Double_t Z_pt[3] = {1.53E-08,
		      2.05E-08,
2.52E-09
};
  Double_t Z_pt_e[3] = {4.85E-09,
			5.29E-09,
			7.61E-10
};

  // 
  for (int i=0;i<3;i++) {
    Z_pt[i] *= 7.650E6 ; Z_pt_e[i] *= 7.650E6 ;
  }

  TGraphErrors *Zpt_graf = new TGraphErrors(3,x_pt,Z_pt,e_pt,Z_pt_e); 
  Zpt_graf->SetMarkerStyle(MarkUs);
  Zpt_graf->SetMarkerColor(ColUs);
  Zpt_graf->SetMarkerSize(SizUs);
  Zpt_graf->Draw("P");
  C2->Print("ZPT.pdf"); 

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *C3 = new TCanvas("ZColl","Z versus centrality",500,500);

  Double_t Npart[3] = {356,224,46};
  Double_t Ivan_cent[3] = {195.2,196.5,200.3}; // 2% effect !
  Double_t Ivan_hard_cent[3] = {178.2,180.9,189.1}; // 10% effect !

  for (i=0;i<3;i++) {
    Ivan_cent[i] *= 43264 ; Ivan_cent[i] /= 7.65E12 ; // Bring it back to dN/Ncoll
    Ivan_hard_cent[i] *= 43264 ; Ivan_hard_cent[i] /= 7.65E12 ;
    cout << "Ivan cent" << Ivan_cent[i] << " " << Ivan_hard_cent[i] << endl;;
  }

  TGraphErrors *Ivan_cent_graf = new TGraphErrors(3,Npart,Ivan_cent,0,0); 
  Ivan_cent_graf->SetMarkerStyle(MarkIvan);
  Ivan_cent_graf->SetMarkerColor(ColPbPb); 

  TGraphErrors *Ivan_hard_cent_graf = new TGraphErrors(3,Npart,Ivan_hard_cent,0,0); 
  Ivan_hard_cent_graf->SetMarkerStyle(MarkIvan);
  Ivan_hard_cent_graf->SetMarkerColor(4); 

  TH1F *dummy = new TH1F("","",50,0.,400.);
  dummy->SetMinimum(0.);
  dummy->SetMaximum(1.5E-6);
  dummy->SetXTitle("N_{part}");
  dummy->SetYTitle("dN/N_{coll}");
  dummy->Draw();

  Ivan_cent_graf->Draw("P");
  Ivan_hard_cent_graf->Draw("P");

  // Our data, in d2N/dydpt
  Double_t x_part[4] = {356,224,46,113}; //Npart
  Double_t e_cent[4] = {10,10,10,10};
  Double_t Z_cent[4] = {1.06E-09,
			8.07E-10,
			7.46E-10,8.95E-10};
  Double_t Z_cent_e[4] = {2.58E-10,
			  2.16E-10,
			  3.05E-10,1.47E-10};
  Double_t ncoll[4] = {1486,744,93,363};

  // 

  TGraphErrors *Zcent_graf = new TGraphErrors(4,x_part,Z_cent,e_cent,Z_cent_e); 
  Zcent_graf->SetMarkerStyle(MarkUs);
  Zcent_graf->SetMarkerColor(ColUs);
  Zcent_graf->Draw("P");
 C3->Print("ZNpart.pdf"); 

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *C4 = new TCanvas("RaaZ","RaaZ",500,500);

  Double_t Z_RAA[3] ; Double_t Z_RAA_e[3] ;

  Double_t Npart_MB[1] ; Npart_MB[0] = x_part[3] ;
  Double_t Z_RAA_MB[1] ; Z_RAA_MB[0] = Z_cent[3] / 8.48E-10 ; 
  Double_t Z_RAA_MB_e[1] ; Z_RAA_MB_e[0] = Z_cent_e[3] / 8.48E-10 ;  

  for (int i=0;i<4;i++) {
    Z_RAA[i] = Z_cent[i] / 8.48E-10 ; Z_RAA_e[i] = Z_cent_e[i] / 8.48E-10  ;
    cout << " Z_RAA[i]" <<  Z_RAA[i] <<endl;
  }

  Double_t Npart_30_50[1] ; Npart_30_50[0] = 108 ; 
  Double_t Z_RAA_30_50[1] ; Z_RAA_30_50[0] = Z_RAA[2] * 1.3 ; // ratio of bin width and Ncoll
  Double_t Z_RAA_30_50_e[1] ; Z_RAA_30_50_e[0] = Z_RAA_e[2] * 1.3 ; // ratio of bin width and Ncoll

  Double_t Npart_0_50[1] ; Npart_0_50[0] = 204 ; 
  Double_t Z_RAA_0_50[1] ; Z_RAA_0_50[0] = Z_RAA_MB[0] * 1.045 ; // ratio of bin width and Ncoll, miss axe
  Double_t Z_RAA_0_50_e[1] ; Z_RAA_0_50_e[0] = Z_RAA_MB_e[0] * 1.045 ; // ratio of bin width and Ncoll, miss axe

  TH1F *dummy = new TH1F("","",50,0.,400.);
  dummy->SetMinimum(0.);
  dummy->SetMaximum(2);
  dummy->SetXTitle("N_{part}");
  dummy->SetYTitle("R_{AA} (Z)");
  dummy->Draw();

  TGraphErrors *ZRAA_graf = new TGraphErrors(3,x_part,Z_RAA,e_cent,Z_RAA_e); 
  ZRAA_graf->SetMarkerStyle(MarkUs);
  ZRAA_graf->SetMarkerColor(ColUs);
  ZRAA_graf->SetMarkerSize(SizUs);
  ZRAA_graf->Draw("P");

  TGraphErrors *ZRAA_MB_graf = new TGraphErrors(1,Npart_MB,Z_RAA_MB,e_cent,Z_RAA_MB_e); 
  ZRAA_MB_graf->SetMarkerStyle(20);
  ZRAA_MB_graf->SetMarkerColor(4);
  ZRAA_MB_graf->SetMarkerSize(SizUs);
  ZRAA_MB_graf->Draw("P");

  TGraphErrors *ZRAA_30_50_graf = new TGraphErrors(1,Npart_30_50,Z_RAA_30_50,e_cent,Z_RAA_30_50_e); 
  ZRAA_30_50_graf->SetMarkerStyle(25);
  ZRAA_30_50_graf->SetMarkerColor(ColUs);
  ZRAA_30_50_graf->SetMarkerSize(SizUs);
  ZRAA_30_50_graf->Draw("P");

  TGraphErrors *ZRAA_0_50_graf = new TGraphErrors(1,Npart_0_50,Z_RAA_0_50,e_cent,Z_RAA_0_50_e); 
  ZRAA_0_50_graf->SetMarkerStyle(24);
  ZRAA_0_50_graf->SetMarkerColor(4);
  ZRAA_0_50_graf->SetMarkerSize(SizUs);
  ZRAA_0_50_graf->Draw("P");

  TLegend* Legend = new TLegend(0.25,0.2,0.9,0.4);
  Legend->SetFillColor(0);
  Legend->SetTextSize(0.037);
  Legend->SetBorderSize(0);
  Legend->AddEntry(ZRAA_graf,"30-100, 10-30, 0-30 %","p"); 
  Legend->AddEntry(ZRAA_MB_graf,"Minimum bias 0-100 %","p"); 
  Legend->AddEntry(ZRAA_30_50_graf,"Same Z as 30-100 -> 30-50 %","p"); 
  Legend->AddEntry(ZRAA_0_50_graf,"Same Z as MB -> 0-50 %","p"); 
  Legend->Draw();
//
  C4->Print("RaaZ.pdf"); 
}
