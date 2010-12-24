void write_tex( double x, double y, char* label , TCanvas* c1, int a=18){
 TLatex *   tex = new TLatex(x,y,label);
 tex->SetTextFont(63);
 tex->SetLineWidth(2);
 tex->SetTextSize(a);
 tex->Draw();
 c1->Update();
}
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
  gStyle->SetMarkerSize(1.25);
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

  TText *tx= new TLatex(100,100,"CMS Preliminary");
  tx->SetTextAlign(22);
///////////////////////////////////////////////////////////////////////////////////////////////////

  Bool_t dodata = true; 
  Bool_t doivan = true;

  TCanvas *C1 = new TCanvas("ZY","Z versus rapidity",500,500);

  // From Hannu and Carlos
  // The result for the total dimuon cross-section with CT10&EPS09:
  // A = 208, Z = 82, Sqrt(s) = 2.76 TeV
  // M2 = Integrated over the interval 80-100GeV
  // Rapidity integrated over the whole phase space.

  //  Sigma total  Error CT10   Error EPS09    Error Total
  // 264.6 pb     +- 9.7 pb     +- 5.0  pb    +- 10.9 pb

  // Th result for the total dimuon cross-section with CT10
  // (only isospin effects, no nuclear effects in PDFs):

  // Sigma total   Error CT10
  // 277.7 pb      +- 10.3 pb

  Double_t EPS09_rap[21] = {0,0.17,0.33,0.50,0.66,0.83,1.00,1.16,1.33,1.49,1.66,1.82,1.99,2.16,2.32,2.49,2.65,2.82,2.99,3.15,4};
  Double_t EPS09_sig[21] = {64.75,64.57,64.15,63.39,62.25,60.74,58.81,56.59,54.17,51.39,48.12,43.88,38.70,32.63,25.76,18.61,11.83,6.28,2.54,0.68,0.68}; // au lieu de 0.68
  Double_t EPS09_err[21] = {4.49,4.36,4.08,3.68,3.23,2.82,2.54,2.74,2.51,2.62,2.66,2.66,2.53,2.31,1.96,1.53,1.06,0.62,0.29,0.14,0.14}; // au lieu de 0.14

  // The results for the dimuon rapidity distribution with CT10 (only isospin effects, no nuclear effects in PDFs):

  Double_t CT10_sig[21] = {62.12,62.07,61.93,61.67,61.27,60.73,59.94,58.85,57.36,55.31,52.52,48.97,44.12,38.23,31.22,23.4,15.5,8.52,3.47,0.83,0.83};
  Double_t CT10_err[21] = {3.12,3.09,3.00,2.85,2.68,2.51,2.35,2.22,2.14,2.08,2.02,1.93,1.80,1.61,1.36,1.07,0.77,0.49,0.27,0.14,0.14};

  // Scale by AxA
  for (int i=0;i<21;i++) {
    EPS09_sig[i] *= 43264 ;    EPS09_sig[i] /= 1E6 ;
    EPS09_err[i] *= 43264 ;    EPS09_err[i] /= 1E6 ;
    CT10_sig[i] *= 43264 ;    CT10_sig[i] /= 1E6 ;
    CT10_err[i] *= 43264 ;    CT10_err[i] /= 1E6 ;
  }

  int Colpp = kAzure ; 
  int ColIso = kGreen+2 ;
  int ColPbPb = kMagenta ;

  int MarkCarlos = 20;  
  int MarkIvan = 21;

  int MarkUs = 20; 
  int ColUs = kRed;
  float SizUs = 2.2;

  int SystSiz = 12;
  int SystCol = kOrange;

  TGraphErrors *EPS09_graf = new TGraphErrors(21,EPS09_rap,EPS09_sig,0,EPS09_err); 
  EPS09_graf->SetMarkerStyle(MarkCarlos);
  EPS09_graf->SetMarkerColor(ColPbPb); // Red for PbPb
  EPS09_graf->SetFillColor(ColPbPb);
  EPS09_graf->SetLineColor(ColPbPb);
  EPS09_graf->SetFillStyle(1001);

  TGraphErrors *CT10_graf = new TGraphErrors(21,EPS09_rap,CT10_sig,0,CT10_err); 
  CT10_graf->SetMarkerStyle(MarkCarlos);
  CT10_graf->SetMarkerColor(Colpp); // Black for pp
  CT10_graf->SetFillColor(Colpp);
  CT10_graf->SetLineColor(Colpp);
  CT10_graf->SetFillStyle(1001);

  // From Ivan, with isospin

  Double_t Ivan_rap[20] = {-3.8,-3.4,-3.0,-2.6,-2.2,-1.8,-1.4,-1.0,-0.6,-0.2, 0.2, 0.6, 1.0, 1.4, 1.8, 2.2, 2.6, 3.0,3.4,3.8};
  Double_t Ivan_sig[20] = { 0.167406,
			     118.096,
			     3936.74,
			     19744.6,
			     40108.3,
			     54419.9,
			     63543.2,
			     68029.5,
			     69047.8,
			     70461.1,
			     69026.1,
			     69532.7,
			     67613.1,
			     63899.2,
			     54795.5,
			     39760.5,
			     20085.1,
			     3927.66,
			     101.449,
			    0.272322}; 

  for (int i=0;i<20;i++) {
    Ivan_sig[i] *= 43364 ; Ivan_sig[i] /= 1E9 ;
    // cout << Ivan_sig[i] << endl;
  }

  TGraphErrors *Ivan_graf = new TGraphErrors(20,Ivan_rap,Ivan_sig,0,0); 
  Ivan_graf->SetMarkerStyle(MarkIvan);
  Ivan_graf->SetMarkerSize(SizUs);
  Ivan_graf->SetLineWidth(4);
  Ivan_graf->SetLineColor(ColIso);
  Ivan_graf->SetMarkerColor(ColIso); 

  TH1F *dummy = new TH1F("","",30,0.,3.15);
  dummy->SetMinimum(0.);
  dummy->SetMaximum(4.);
  dummy->SetXTitle("Rapidity");
  dummy->SetYTitle("B x d#sigma/dy (#mub)");
  dummy->Draw();

  EPS09_graf->Draw("LE4");
  CT10_graf->Draw("LE4");
  if (doivan) Ivan_graf->Draw("L");

  // Our data, in dN/dy
  Double_t x_rap[3] = {0.25,0.77,1.38}; // Main
  //  Double_t x_rap[3] = {0.25,0.75,1.7};
  Double_t x_rap_min[3] = {0,0.5,1}; 
  Double_t x_rap_max[3] = {0.5,1,2.4}; 
  Double_t Z_rap[3] = { 4.13E-07 , 3.55E-07 , 2.55E-07};
  Double_t Z_rap_e[3] = { 1.15E-07 , 1.08E-07 , 7.24E-08};
  Double_t Z_rap_syst_plus[3] ; Double_t Z_rap_syst_minus[3] ; 
  Double_t e_rap[3] = {0.11,0.11,0.26}; // RMS ? 

  for (int i=0;i<3;i++) {
    x_rap_min[i] = x_rap[i] - x_rap_min[i];
    x_rap_max[i] = x_rap_max[i] - x_rap[i];    
    Z_rap[i] *= 7.650E6 ; Z_rap_e[i] *= 7.650E6 ;
    Z_rap_syst_plus[i] = 0.095 * Z_rap[i];
    Z_rap_syst_minus[i] = 0.102 * Z_rap[i];
  }

  TGraphAsymmErrors *Zrap_graf_syst = new TGraphAsymmErrors(3,x_rap,Z_rap,0,0,Z_rap_syst_plus,Z_rap_syst_minus); 
  Zrap_graf_syst->SetLineWidth(SystSiz);
  Zrap_graf_syst->SetLineColor(SystCol);
  if (dodata) Zrap_graf_syst->Draw("E");

  TGraphAsymmErrors *Zrap_graf = new TGraphAsymmErrors(3,x_rap,Z_rap,x_rap_min,x_rap_max,Z_rap_e,Z_rap_e); 
  Zrap_graf->SetMarkerStyle(MarkUs);
  Zrap_graf->SetMarkerColor(ColUs);
  Zrap_graf->SetMarkerSize(SizUs);
  Zrap_graf->SetLineWidth(2);
  if (dodata) Zrap_graf->Draw("P");

  TLegend* Legend = new TLegend(0.2,0.2,0.6,0.4);
  Legend->SetFillColor(0);
  Legend->SetTextSize(0.037);
  Legend->SetBorderSize(0);
  if (dodata)   Legend->AddEntry(Zrap_graf,"CMS","p"); 
  Legend->AddEntry(CT10_graf,"Salgado, CT10+isospin","f"); 
  Legend->AddEntry(EPS09_graf,"Salgado, EPS09+isospin","f"); 
  if (doivan) Legend->AddEntry(Ivan_graf,"Vitev, MSTW+isospin","l"); 
  Legend->Draw(); 

  write_tex(0.9,3.6,"CMS Pb+Pb #sqrt{s_{NN}} = 2.76 TeV",C1);
  write_tex(1.8,3.1,"#int Ldt = 6.6 #mub^{-1}", C1,18);

  C1->Print("ZY.pdf"); 

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *C2 = new TCanvas("ZPT","Z versus transverse momentum",500,500);
  C2->SetLogy();

 //T distribution  (we checked that at LO it is) exactly at 0 program puts it at 1 gev since the bin is 0-2 GeV, see my nt above)

  Double_t Ivan_pt[50] = {1.,3.,5.,7.,9.,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89,91,93,95,97,99};

  //  Double_t Ivan_sig_pt[50] = {5051.3,34793.,16462.,9961.2,6734.33,4895.96,3697.55,2901.74,2325.82,1916.87,1581.45,1339.24,1137.08,976.057,839.472,732.849,643.008,563.936,494.014,443.095,390.616,350.563,312.855,282.245,253.257,227.519,201.905,189.022,168.621,149.557,136.984,123.562,112.623,104.982,93.0248,85.3706,80.3332,70.4107,64.1783,58.2423,55.1995,50.1423,44.6478,41.3786,38.3456,35.0174,32.4205,29.6368,27.2063,24.8434};

  // Below is within |eta_mu| < 2.4 and pt > 10 GeV/c
  Double_t Ivancor_sig_pt[50] = {4895.43,35837.4,17001.6,10240.7,6935.48,5027.13,3843.81,2988.97,2431.89,1978.87,1639.69,1378.93,1164.79,1013.45,873.330,750.752,658.838,587.341,509.177,455.536,414.566,355.557,322.083,292.399,260.906,235.761,211.652,194.367,174.420,157.444,141.644,130.159,116.344,106.940,100.338,90.4371,80.8616,71.8951,67.1495,62.4207,56.8685,51.7799,46.6831,44.6836,39.9829,36.7482,34.2372,30.4509,28.8633,26.9952};

  // Below is for all rapidity
  Double_t Ivan_sig_pt[50] = { 12875.4,
			       52199.9,
			       24655.6,
			       14879.7,
			       10022.6,
			       7240.39,
			       5473.85,
			       4275.39,
			       3416.91,
			       2777.21,
			       2298.13,
			       1921.94,
			       1626.88,
			       1387.46,
			       1191.19,
			       1033.08,
			       894.891,
			       783.430,
			       688.369,
			       605.757,
			       532.707,
			       473.904,
			       420.561,
			       375.199,
			       335.787,
			       300.053,
			       268.629,
			       242.381,
			       217.427,
			       196.716,
			       176.162,
			       159.839,
			       144.183,
			       131.402,
			       118.401,
			       107.822,
			       97.3815,
			       88.6694,
			       81.1454,
			       73.9517,
			       66.9328,
			       61.3405,
			       55.8238,
			       51.0343,
			       46.8074,
			       43.2040,
			       39.1755,
			       36.1110,
			       33.0147,
			       30.2259};

  for (int i=0;i<49;i++) {
    Ivan_sig_pt[i] *= 43264 ; Ivan_sig_pt[i] /= 1E9 ; Ivan_sig_pt[i] /= 4.8 ;
    Ivancor_sig_pt[i] *= 43264 ; Ivancor_sig_pt[i] /= 1E9 ; Ivancor_sig_pt[i] /= 4.8 ; Ivancor_sig_pt[i] /= 0.71  ; 
    // 0.7 is the flat acceptance
  }

  double xbins[] = {0,6,12,30};
  TH1F *h1 = new TH1F("h1","h1",3,xbins);
  h1->SetLineWidth(4);
  h1->SetLineColor(ColIso);

  cout << "Integral" << endl;  
  h1->Fill(3,(Ivancor_sig_pt[0] + Ivancor_sig_pt[1] + Ivancor_sig_pt[2])/3); 
  h1->Fill(9,(Ivancor_sig_pt[3] + Ivancor_sig_pt[4] + Ivancor_sig_pt[5])/3); 
  float integral = 0; 
  for (int i=6;i<25;i++) {
    integral += Ivancor_sig_pt[i];  
  }
  h1->Fill(15,integral/19);
  h1->Print(); 
  cout << integral/19 << endl;

  TGraphErrors *Ivan_pt_graf = new TGraphErrors(49,Ivan_pt,Ivan_sig_pt,0,0); 
  Ivan_pt_graf->SetMarkerStyle(MarkIvan);
  Ivan_pt_graf->SetMarkerSize(SizUs);
  Ivan_pt_graf->SetLineWidth(4);
  Ivan_pt_graf->SetLineColor(ColIso);
  Ivan_pt_graf->SetMarkerColor(ColIso); 

  TGraphErrors *Ivancor_pt_graf = new TGraphErrors(49,Ivan_pt,Ivancor_sig_pt,0,0); 
  Ivancor_pt_graf->SetMarkerStyle(MarkIvan);
  Ivancor_pt_graf->SetMarkerSize(SizUs);
  Ivancor_pt_graf->SetLineWidth(4);
  Ivancor_pt_graf->SetLineColor(ColIso);
  Ivancor_pt_graf->SetFillColor(3);
  Ivancor_pt_graf->SetMarkerColor(ColIso); 
  Ivancor_pt_graf->SetLineStyle(3);

  TH1F *dummy = new TH1F("","",30,0.,30.);
  dummy->SetMinimum(0.01); // 0.002
  dummy->SetMaximum(0.5); // 1. 
  dummy->SetXTitle("Transverse momentum (GeV/c)");
  dummy->SetYTitle("B x d^{2}#sigma/dydp_{T} (#mub/(GeV/c))");
  dummy->Draw();

  if (doivan)  h1->Draw("SAME");

  // Do not draw, since not corrected for acceptance
  //  if (doivan) Ivancor_pt_graf->Draw("L");
  // Ivan_pt_graf->Draw("L");

  // Our data, in dN/dydpt
  // Double_t x_pt[3] = {3,9,31};
  Double_t x_pt[3] = {4.31,8.30,17.72}; // Mean
  Double_t x_pt_min[3] = {0,6,12}; // Mean
  Double_t x_pt_max[3] = {6,12,50}; // Mean
  Double_t e_pt[3] = {1.37,1.89,4.62}; // RMS
  Double_t Z_pt[3] = {1.51E-08,2.00E-08,2.47E-09};
  Double_t Z_pt_e[3] = {4.85E-09,5.29E-09,7.61E-10};
  Double_t Z_pt_syst_plus[3]; Double_t Z_pt_syst_minus[3]; 

  // 
  for (int i=0;i<3;i++) {
    x_pt_min[i] = x_pt[i] - x_pt_min[i];
    x_pt_max[i] = x_pt_max[i] - x_pt[i];
    Z_pt[i] *= 7.650E6 ; Z_pt_e[i] *= 7.650E6 ;
    Z_pt_syst_plus[i] = 0.095 * Z_pt[i] ;
    Z_pt_syst_minus[i] = 0.102 * Z_pt[i] ;
  }

  TGraphAsymmErrors *Zpt_syst = new TGraphAsymmErrors(3,x_pt,Z_pt,0,0,Z_pt_syst_plus,Z_pt_syst_minus); 
  Zpt_syst->SetLineWidth(SystSiz);
  Zpt_syst->SetLineColor(SystCol);
  if (dodata)  Zpt_syst->Draw("E");

  TGraphAsymmErrors *Zpt_graf = new TGraphAsymmErrors(3,x_pt,Z_pt,x_pt_min,x_pt_max,Z_pt_e,Z_pt_e); 
  Zpt_graf->SetMarkerStyle(MarkUs);
  Zpt_graf->SetMarkerColor(ColUs);
  Zpt_graf->SetMarkerSize(SizUs);
  Zpt_graf->SetLineWidth(2);
  if (dodata)  Zpt_graf->Draw("P");

  TLegend* Legend = new TLegend(0.5,0.72,0.9,0.82);
  Legend->SetFillColor(0);
  Legend->SetTextSize(0.037);
  Legend->SetBorderSize(0);
  if (dodata)  Legend->AddEntry(Zpt_graf,"CMS, |y|<2.4","p"); 
  //  Legend->AddEntry(CT10_graf,"CT10, no shadowing","f"); 
  //  Legend->AddEntry(EPS09_graf,"EPS09, shadowing","f"); 
  if (doivan) Legend->AddEntry(h1,"Vitev, MSTW+isospin","l"); 
  Legend->Draw(); 

  write_tex(9,0.32,"CMS Pb+Pb #sqrt{s_{NN}} = 2.76 TeV",C2);
  write_tex(0.8,0.013,"#int Ldt = 6.6 #mub^{-1}", C2,18);

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

  // Our data, in dN/dy / Ncoll
  Double_t x_part[4] = {356,224,46,113}; //Npart
  Double_t e_cent[4] = {10,10,10,10};
  Double_t Z_cent[4] = {1.04E-09,
			7.90E-10,
			7.30E-10,8.75E-10};
  Double_t Z_cent_e[4] = {2.57E-10,
			  2.13E-10,
			  2.99E-10,1.45E-10};
  Double_t ncoll[4] = {1486,744,93,363};

  // 

  TGraphErrors *Zcent_graf = new TGraphErrors(4,x_part,Z_cent,e_cent,Z_cent_e); 
  Zcent_graf->SetMarkerStyle(MarkUs);
  Zcent_graf->SetMarkerColor(ColUs);
  Zcent_graf->Draw("P");
  C3->Print("ZNpart.pdf"); 

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *C4 = new TCanvas("RaaZ","RaaZ",500,500);

  Double_t Z_RAA[3] ; Double_t Z_RAA_e[3] ; Double_t Z_RAA_syst_plus[3] ; Double_t Z_RAA_syst_minus[3] ;

  Double_t Npart_MB[1] ; Npart_MB[0] = x_part[3] ;
  Double_t Z_RAA_MB[1] ; Z_RAA_MB[0] = 1.00 ; // This is not a joke 
  Double_t Z_RAA_MB_e[1] ; Z_RAA_MB_e[0] = 0.17 ;  
  Double_t Z_RAA_MB_syst_plus[1] ; Z_RAA_MB_syst_plus[0] = Z_RAA_MB[0] * sqrt(0.095*0.095 + 0.01) ; // Ncoll = 10% for now  
  Double_t Z_RAA_MB_syst_minus[1] ; Z_RAA_MB_syst_minus[0] = Z_RAA_MB[0] * sqrt(0.102*0.102 + 0.01) ; // Ncoll = 10% for now     

  Double_t Ncoll_e[3] = {0.081,0.089,0.118}; // Relative error on Ncoll

  for (int i=0;i<4;i++) {
    Z_RAA[i] = Z_cent[i] / 8.48E-10 ; Z_RAA_e[i] = Z_cent_e[i] / 8.48E-10  ;
    Z_RAA_syst_plus[i] = sqrt ( 0.095*0.095 + Ncoll_e[i]*Ncoll_e[i] )* Z_RAA[i] ; 
    Z_RAA_syst_minus[i] = sqrt ( 0.103*0.103 + Ncoll_e[i]*Ncoll_e[i] )* Z_RAA[i] ;  
    // cout << " Z_RAA[i]" <<  Z_RAA[i] <<endl;
  }

  Double_t Npart_30_50[1] ; Npart_30_50[0] = 108 ; 
  Double_t Z_RAA_30_50[1] ; Z_RAA_30_50[0] = Z_RAA[2] * 1.3 ; // ratio of bin width and Ncoll
  Double_t Z_RAA_30_50_e[1] ; Z_RAA_30_50_e[0] = Z_RAA_e[2] * 1.3 ; // ratio of bin width and Ncoll

  Double_t Npart_0_50[1] ; Npart_0_50[0] = 204 ; 
  Double_t Z_RAA_0_50[1] ; Z_RAA_0_50[0] = Z_RAA_MB[0] * 1.045 ; // ratio of bin width and Ncoll, miss axe
  Double_t Z_RAA_0_50_e[1] ; Z_RAA_0_50_e[0] = Z_RAA_MB_e[0] * 1.045 ; // ratio of bin width and Ncoll, miss axe

  TH1F *dummy = new TH1F("","",50,0.,400.);
  dummy->SetMinimum(0.);
  dummy->SetMaximum(1.6);
  dummy->SetXTitle("N_{part}");
  dummy->SetYTitle("R_{AA} (Z)");
  dummy->Draw();

  TGraphAsymmErrors *ZRAA_graf_syst = new TGraphAsymmErrors(3,x_part,Z_RAA,0,0,Z_RAA_syst_plus,Z_RAA_syst_minus); 
  ZRAA_graf_syst->SetLineWidth(SystSiz);
  ZRAA_graf_syst->SetLineColor(SystCol);
  if (dodata) ZRAA_graf_syst->Draw("E");
  cout << " == RAA and systematic error" << endl;
  ZRAA_graf_syst->Print();

  TGraphErrors *ZRAA_graf = new TGraphErrors(3,x_part,Z_RAA,0,Z_RAA_e); 
  ZRAA_graf->SetMarkerStyle(MarkUs);
  ZRAA_graf->SetMarkerColor(ColUs);
  ZRAA_graf->SetMarkerSize(SizUs);
  ZRAA_graf->SetLineWidth(2);
  if (dodata) ZRAA_graf->Draw("P");
  cout << " == RAA and statistical error" << endl;
  ZRAA_graf->Print();

  TGraphAsymmErrors *ZRAA_graf_MB_syst = new TGraphAsymmErrors(1,Npart_MB,Z_RAA_MB,0,0,Z_RAA_MB_syst_plus,Z_RAA_MB_syst_minus); 
  ZRAA_graf_MB_syst->SetLineWidth(SystSiz);
  ZRAA_graf_MB_syst->SetLineColor(kAzure+7);
  if (dodata) ZRAA_graf_MB_syst->Draw("E");
  cout << " == MB RAA and systematic error" << endl;
  ZRAA_graf_MB_syst->Print();

  TGraphErrors *ZRAA_MB_graf = new TGraphErrors(1,Npart_MB,Z_RAA_MB,0,Z_RAA_MB_e); 
  ZRAA_MB_graf->SetMarkerStyle(20);
  ZRAA_MB_graf->SetMarkerColor(kBlue);
  ZRAA_MB_graf->SetMarkerSize(SizUs);
  ZRAA_MB_graf->SetLineWidth(2);
  if (dodata) ZRAA_MB_graf->Draw("P");
  cout << " == MB RAA and systematic error" << endl;
  ZRAA_MB_graf->Print();

  // TGraphErrors *ZRAA_30_50_graf = new TGraphErrors(1,Npart_30_50,Z_RAA_30_50,e_cent,Z_RAA_30_50_e); 
  // ZRAA_30_50_graf->SetMarkerStyle(25);
  // ZRAA_30_50_graf->SetMarkerColor(ColUs);
  // ZRAA_30_50_graf->SetMarkerSize(SizUs);
  // ZRAA_30_50_graf->Draw("P");

  // TGraphErrors *ZRAA_0_50_graf = new TGraphErrors(1,Npart_0_50,Z_RAA_0_50,e_cent,Z_RAA_0_50_e); 
  // ZRAA_0_50_graf->SetMarkerStyle(24);
  // ZRAA_0_50_graf->SetMarkerColor(4);
  // ZRAA_0_50_graf->SetMarkerSize(SizUs);
  // ZRAA_0_50_graf->Draw("P");

  TLine* RaaOne = new TLine(0,1,400,1);
  RaaOne->SetLineStyle(2);
  RaaOne->Draw();

  TLegend* Legend = new TLegend(0.3,0.20,0.9,0.30);
  Legend->SetFillColor(0);
  Legend->SetTextSize(0.037);
  Legend->SetBorderSize(0);
  Legend->AddEntry(ZRAA_graf,"30-100, 10-30, 0-10 %","p"); 
  Legend->AddEntry(ZRAA_MB_graf,"Minimum bias 0-100 %","p"); 
  //  Legend->AddEntry(ZRAA_30_50_graf,"Same Z as 30-100 -> 30-50 %","p"); 
  //  Legend->AddEntry(ZRAA_0_50_graf,"Same Z as MB -> 0-50 %","p"); 
  Legend->Draw();
//
  write_tex(20,1.4,"CMS Pb+Pb #sqrt{s_{NN}} = 2.76 TeV",C2);
  write_tex(100,0.4,"#int Ldt = 6.6 #mub^{-1}", C2,18);
//
  C4->Print("RaaZ.pdf"); 
}
