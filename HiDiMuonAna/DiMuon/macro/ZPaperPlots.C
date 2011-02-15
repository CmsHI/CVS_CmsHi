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
  gStyle->SetErrorX(0.5);
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

///////////////////////////////////////////////////////////////////////////////////////////////////

  // Some swithes
  Bool_t dodata = true; 
  Bool_t doivan = true;
  Bool_t dobins = true;
  Bool_t dolog = false;
  Bool_t donds = false; 

  // Some cosmetics

  // Their predictions
  int ColCT= kGreen+2 ; int StyCT = 2 ;
  int ColEPS = kAzure ; int StyEPS = 4 ; int FilEPS = 3003;
  int ColnDS = kMagenta ; int StynDS = 4 ;
  int ColIso = kOrange+3 ; int StyIso = 3 ;
  int ColEl = kRed ; int StyEl = 5 ;
  int ColPow = kBlack ; int StyPow = 1 ;
  int SizTh = 3;

  // Our points
  int MarkUs = 20; 
  int ColUs = kRed;
  float SizUs = 2.8;
  int SystSiz = 12;
  int SystCol = kOrange+2;

  // Title
  float xt = 0.0375;
  float yt = 0.895;

  // Systematic uncertanity
  float Syst =0.13;

///////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *C1 = new TCanvas("ZY","Z versus rapidity",500,500);

  TH1F *dummy = new TH1F("","",30,0.,2.0);
  dummy->SetMinimum(0.);
  dummy->SetMaximum(60);
  //  TGaxis->SetMaxDigits(2);
  dummy->SetXTitle("Rapidity");
  dummy->SetYTitle("dN/dy");
  dummy->Draw();

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

  Double_t EPS09_rap[21] = {0,0.17,0.33,0.50,0.66,0.83,1.00,1.16,1.33,1.49,1.66,1.82,1.99,2.16,2.32,2.49,2.65,2.82,2.99,3.15,4};
  Double_t EPS09_sig[21] = {64.75,64.57,64.15,63.39,62.25,60.74,58.81,56.59,54.17,51.39,48.12,43.88,38.70,32.63,25.76,18.61,11.83,6.28,2.54,0.68,0.68};
  Double_t EPS09_err[21] = {4.49,4.36,4.08,3.68,3.23,2.82,2.54,2.74,2.51,2.62,2.66,2.66,2.53,2.31,1.96,1.53,1.06,0.62,0.29,0.14,0.14};

  // The results for the dimuon rapidity distribution with CT10 (only isospin effects, no nuclear effects in PDFs):

  Double_t CT10_sig[21] = {62.12,62.07,61.93,61.67,61.27,60.73,59.94,58.85,57.36,55.31,52.52,48.97,44.12,38.23,31.22,23.4,15.5,8.52,3.47,0.83,0.83};
  Double_t CT10_err[21] = {3.12,3.09,3.00,2.85,2.68,2.51,2.35,2.22,2.14,2.08,2.02,1.93,1.80,1.61,1.36,1.07,0.77,0.49,0.27,0.14,0.14};

  // Scale by AxA and 7.65 barns (and by artificial factor for the scale)

  float Norm = 208*208/7.65E12*1E8;
 
  for (int i=0;i<21;i++) {
    EPS09_sig[i] *= Norm ;
    EPS09_err[i] *= Norm ;
    CT10_sig[i]  *= Norm ;
    CT10_err[i]  *= Norm ;
  }

// Same per rapidity bins and in 60-120 and with nDS too

  Double_t EPS09_bin[4] = {69.2,66.1,108.6,41.0};
  Double_t EPS09_ber[4] = {5.7,4.5,6.8,3.2};
  Double_t nDS_bin[4] = {64.5,63.0,109.1,43.8};
  Double_t nDS_ber[4] = {0,0,0,0};
  Double_t CT10_bin[4] = {66.8,65.7,116.6,49.9};
  //  Double_t CT10_ber[4] = {3.3,2.7,4.0,1.8};
  // Do not display error on CT10... 
  Double_t CT10_ber[4] = {0,0,0,0};

  // Scale by AxA
  for (int i=0;i<4;i++) {
    EPS09_bin[i] *= Norm ;
    EPS09_ber[i] *= Norm ;
    nDS_bin[i]   *= Norm ;
    nDS_ber[i]   *= Norm ;
    CT10_bin[i]  *= Norm ;
    CT10_ber[i]  *= Norm ;
  }
  // Scale by bin width
  EPS09_bin[2] /= 2 ;    EPS09_bin[3] /= 2 ;
  EPS09_ber[2] /= 2 ;    EPS09_ber[3] /= 2 ;
  nDS_bin[2]  /= 2 ;    nDS_bin[3]  /= 2 ;
  nDS_ber[2]  /= 2 ;    nDS_ber[3]  /= 2 ;
  CT10_bin[2] /= 2 ;    CT10_bin[3] /= 2 ;
  CT10_ber[2] /= 2 ;    CT10_ber[3] /= 2 ;

  double xbins[] = {0,0.5,1.0,2.0,3.0};
  TH1F *EPS09 = new TH1F("EPS09","EPS09",3,xbins);
  TH1F *nDS = new TH1F("nDS","nDS",3,xbins);
  TH1F *CT10 = new TH1F("CT10","CT10",3,xbins);
  EPS09->SetLineWidth(SizTh);
  EPS09->SetLineColor(ColEPS);
  EPS09->SetLineStyle(StyEPS);  
  nDS->SetLineWidth(SizTh);
  nDS->SetLineColor(ColnDS);
  nDS->SetLineStyle(StynDS);
  CT10->SetLineWidth(SizTh);
  CT10->SetLineColor(ColCT);
  CT10->SetLineStyle(StyCT);

  for (int i=1;i<5;i++) {
    EPS09->SetBinContent(i,EPS09_bin[i-1]);
    EPS09->SetBinError(i,EPS09_ber[i-1]);
    nDS->SetBinContent(i,nDS_bin[i-1]);
    nDS->SetBinError(i,nDS_ber[i-1]);
    CT10->SetBinContent(i,CT10_bin[i-1]);
    CT10->SetBinError(i,CT10_ber[i-1]);
    cout << "EPS09 " << i << " " << EPS09->GetBinCenter(i) << " " << EPS09->GetBinContent(i) << " " << EPS09->GetBinError(i) << endl;
    cout << "CT10  " << i << " " << CT10->GetBinCenter(i) << " " << CT10->GetBinContent(i) << " " << CT10->GetBinError(i) << endl; 
  }

  TGraphErrors *EPS09_graf = new TGraphErrors(21,EPS09_rap,EPS09_sig,0,EPS09_err); 
  EPS09_graf->SetMarkerColor(ColEPS); 
  EPS09_graf->SetFillColor(ColEPS);
  EPS09_graf->SetLineColor(ColEPS);
  EPS09_graf->SetFillStyle(1001);

  TGraphErrors *CT10_graf = new TGraphErrors(21,EPS09_rap,CT10_sig,0,CT10_err); 
  CT10_graf->SetMarkerColor(ColCT); 
  CT10_graf->SetFillColor(ColCT);
  CT10_graf->SetLineColor(ColCT);
  CT10_graf->SetFillStyle(1001);

  // From Ivan, with isospin

//  Double_t Ivan_rap[20] = {-3.8,-3.4,-3.0,-2.6,-2.2,-1.8,-1.4,-1.0,-0.6,-0.2, 0.2, 0.6, 1.0, 1.4, 1.8, 2.2, 2.6, 3.0,3.4,3.8};
//  Double_t Ivan_iso[20] = {0.167406,118.096,3936.74,19744.6,40108.3,54419.9,63543.2,68029.5,69047.8,70461.1,69026.1,69532.7,67613.1,63899.2,54795.5,39760.5,20085.1,3927.66,101.449,0.272322}; 
//  Double_t Ivan_el[20] = {4.18E-02,,97.721,3506.46,17893.6,36643.8,50780.1,59569.9,64532.7,65485.7,66951.2,65792,66097.6,63911.6,59984.2,51073.4,36575.5,17959,3537.15,95.1131,0.282133};

  Double_t Ivan_rap[5] = {0.25,0.75,1.5,2.5,3.5};
  Double_t Ivan_iso[5] = {69652.93,68702.67,60895.82,24726.14,830.436946};
  Double_t Ivan_el[5] = {66255.6,65163.85,57125.95,22518.741,742.992602};

  TH1F *IvanIso = new TH1F("Ivan Iso","Ivan Iso",3,xbins);
  TH1F *IvanEl = new TH1F("Ivan El","Ivan El",3,xbins);

  for (int i=1;i<6;i++) {
    Ivan_iso[i-1] *= Norm/1000 ;
    Ivan_el[i-1]  *= Norm/1000 ;
    IvanIso->SetBinContent(i,Ivan_iso[i-1]);
    IvanEl->SetBinContent(i,Ivan_el[i-1]);
  }

  // TGraphErrors *Ivan_iso_graf = new TGraphErrors(5,Ivan_rap,Ivan_iso,0,0); 
  IvanIso->SetLineWidth(SizTh);
  IvanIso->SetLineColor(ColIso);
  IvanIso->SetLineStyle(StyIso);

  // TGraphErrors *Ivan_el_graf = new TGraphErrors(5,Ivan_rap,Ivan_el,0,0); 
  IvanEl->SetLineWidth(SizTh);
  IvanEl->SetLineColor(ColEl);
  IvanEl->SetLineStyle(StyEl);

  // From Pythia
  Double_t pythia_y[] = {1038,1020,947,623};
  TH1F *Pythia_y = new TH1F("Pythia y","Pythia y",4,xbins);
  for (int i=1;i<5;i++) {
    Pythia_y->SetBinContent(i,pythia_y[i-1]);
  }
  Pythia_y->SetLineWidth(SizTh);
  Pythia_y->Scale(1/333.); // arbitrary
  // Pythia_y->SetLineColor();
  // Pythia_y->SetLineStyle();  

  // POWHEG
  TFile *powheg_file = new TFile("Acc/POWHEG.root");
  TH1F *Powheg_y = new TH1F("Powheg_y","Powheg_y",3,xbins);
  Events->Project("Powheg_y","zy","dimumass<120&&dimumass>60");
  Powheg_y->Scale(578.4/Events->GetEntries()*Norm); 
  // Total xsection is 578.4 pb according to EWK, scale it to our range
  cout << "N " << Powheg_y->GetEntries() << " " << Events->GetEntries() << endl;
  for (int i=1;i<5;i++) {
    Powheg_y->SetBinContent(i,Powheg_y->GetBinContent(i)/Powheg_y->GetBinWidth(i)); // 
    cout << "POWHEG y bin " << i << " " << Powheg_y->GetBinContent(i) << endl;
  }

  Powheg_y->SetLineStyle(StyPow); 
  Powheg_y->SetLineColor(ColPow); 
  Powheg_y->SetLineWidth(SizTh); 

  // Our data, in dN/dy
  Double_t x_rap[3] = {0.26,0.79,1.4}; // Main
  //  Double_t x_rap[3] = {0.25,0.75,1.7};
  Double_t x_rap_min[3] = {0,0.5,1.0}; 
  Double_t x_rap_max[3] = {0.5,1.0,2.0}; 
  Double_t Z_rap[3] = { 3.81E-07 , 3.56E-07 , 3.00E-07};
  Double_t Z_rap_e[3] = { 1.07E-07 , 1.04E-07 , 8.10E-08};
  Double_t Z_rap_syst_plus[3] ; Double_t Z_rap_syst_minus[3] ; 
  Double_t e_rap[3] = {0.11,0.11,0.26}; // RMS ? 
  for (int i=0;i<3;i++) {
    Z_rap[i] *= 1E8;
    Z_rap_e[i] *= 1E8;
    x_rap_min[i] = x_rap[i] - x_rap_min[i];
    x_rap_max[i] = x_rap_max[i] - x_rap[i];    
    // Z_rap[i] *= 7.650E6 ; Z_rap_e[i] *= 7.650E6 ;
    Z_rap_syst_plus[i] = Syst * Z_rap[i];
    Z_rap_syst_minus[i] = Syst * Z_rap[i];
  }

  TGraphAsymmErrors *Zrap_graf_syst = new TGraphAsymmErrors(3,x_rap,Z_rap,0,0,Z_rap_syst_plus,Z_rap_syst_minus); 
  Zrap_graf_syst->SetLineWidth(SystSiz);
  Zrap_graf_syst->SetLineColor(SystCol);

  TGraphAsymmErrors *Zrap_graf = new TGraphAsymmErrors(3,x_rap,Z_rap,x_rap_min,x_rap_max,Z_rap_e,Z_rap_e); 
  Zrap_graf->SetMarkerStyle(MarkUs);
  Zrap_graf->SetMarkerColor(ColUs);
  Zrap_graf->SetMarkerSize(SizUs);
  Zrap_graf->SetLineWidth(2);

  TH1F *h2 = (TH1F*) EPS09->Clone("EPS09bis");
  h2->SetFillColor(ColEPS-4);
  h2->SetFillStyle(FilEPS);
  h2->SetMarkerSize(0); 

  TLegend* Legend = new TLegend(0.18,0.18,0.6,0.48);
  Legend->SetFillColor(kWhite);
  Legend->SetTextSize(0.037);
  Legend->SetBorderSize(0);
  if (dodata)   Legend->AddEntry(Zrap_graf,"CMS","p"); 
  Legend->AddEntry(Powheg_y,"POWHEG + PYTHIA 6.4","l");
  if (dobins) {
    Legend->AddEntry(CT10,"Paukkunen et al., CT10+isospin","l");
    Legend->AddEntry(h2,"Paukkunen et al., idem+EPS09","lf");
    if (donds) Legend->AddEntry(nDS,"Paukkunen et al., nDS+isospin","l");
  } else {
    Legend->AddEntry(CT10_graf,"Salgado, CT10+isospin","f"); 
    Legend->AddEntry(EPS09_graf,"Salgado, EPS09+isospin","f"); 
  }
  if (doivan) {
    Legend->AddEntry(IvanIso,"Neufeld et al., MSTW+isospin","l"); 
    Legend->AddEntry(IvanEl,"Neufeld et al., idem+eloss","l"); 
  }
  //  Legend->AddEntry(Pythia_y,"Pythia, arbitrary scale","l");

  Legend->Draw(); 

  write_tex(xt*2.0,yt*60,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV, #int Ldt = 7.2 #mub^{-1}",C1,16);
  write_tex(0,60*1.008,"x10^{-8}",C1,18);
  //  write_tex(0.9,5.2E-7,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV",C1,16);
  //  write_tex(1.75,4.4E-7,"#int Ldt = 7.2 #mub^{-1}", C1,16);

  // Draw after legend to avoid hiding
  if (dobins) {
    h2->Draw("e2,same");
    EPS09->Draw("same,hist");

    if (donds) nDS->Draw("same");
    CT10->Draw("same");
  } else {
    EPS09_graf->Draw("LE4");
    CT10_graf->Draw("LE4");
  }
  if (doivan) {
    IvanIso->Draw("same");
    IvanEl->Draw("same");
  }

  Powheg_y->Draw("same");

  if (dodata) {
    Zrap_graf_syst->Draw("E");
    Zrap_graf->Draw("P");
  }

  // Pythia_y->Draw("same,h");

  C1->Print("ZY.pdf"); 
  C1->Print("ZY.jpg"); 

//
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *C2 = new TCanvas("ZPT","Z versus transverse momentum",500,500);
  if (dolog) C2->SetLogy();

  TH1F *dummy = new TH1F("","",30,0.,36.);
  if (dolog) {
    dummy->SetMinimum(2E-9); // 0.002
    dummy->SetMaximum(1E-7); // 1. 
  } else {
    dummy->SetMinimum(0); // 0.002
    dummy->SetMaximum(3.3); // 1. 
  }
  
  dummy->SetXTitle("Transverse momentum (GeV/c)");
  dummy->SetYTitle("d^{2}N/dydp_{T} (GeV/c)^{-1}");
  dummy->Draw();

 //T distribution  (we checked that at LO it is) exactly at 0 program puts it at 1 gev since the bin is 0-2 GeV, see my nt above)

  Double_t Ivan_pt[50] = {1.,3.,5.,7.,9.,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89,91,93,95,97,99};

  //  Double_t Ivan_sig_pt[50] = {5051.3,34793.,16462.,9961.2,6734.33,4895.96,3697.55,2901.74,2325.82,1916.87,1581.45,1339.24,1137.08,976.057,839.472,732.849,643.008,563.936,494.014,443.095,390.616,350.563,312.855,282.245,253.257,227.519,201.905,189.022,168.621,149.557,136.984,123.562,112.623,104.982,93.0248,85.3706,80.3332,70.4107,64.1783,58.2423,55.1995,50.1423,44.6478,41.3786,38.3456,35.0174,32.4205,29.6368,27.2063,24.8434};

  // Below is within |eta_mu| < 2.4 and pt > 10 GeV/c
  Double_t Ivancor_sig_pt[50] = {4895.43,35837.4,17001.6,10240.7,6935.48,5027.13,3843.81,2988.97,2431.89,1978.87,1639.69,1378.93,1164.79,1013.45,873.330,750.752,658.838,587.341,509.177,455.536,414.566,355.557,322.083,292.399,260.906,235.761,211.652,194.367,174.420,157.444,141.644,130.159,116.344,106.940,100.338,90.4371,80.8616,71.8951,67.1495,62.4207,56.8685,51.7799,46.6831,44.6836,39.9829,36.7482,34.2372,30.4509,28.8633,26.9952};

  // Below is for all rapidity
  Double_t Ivan_sig_pt[50] = { 12875.4,52199.9,24655.6,14879.7,10022.6,7240.39,5473.85,4275.39,3416.91,2777.21,2298.13,1921.94,1626.88,1387.46,1191.19,1033.08,894.891,783.430,688.369,605.757,532.707,473.904,420.561,375.199,335.787,300.053,268.629,242.381,217.427,196.716,176.162,159.839,144.183,131.402,118.401,107.822,97.3815,88.6694,81.1454,73.9517,66.9328,61.3405,55.8238,51.0343,46.8074,43.2040,39.1755,36.1110,33.0147,30.2259};

  // New value from Ivan, with isospin, already in |y|<2.0
  Double_t Ivan_iso_pt[50] = {1280.0,11114.2,5284.2,3196.4,2171.0,1584.3,1200.7,948.1,761.3,622.4,521.3,440.7,375.2,324.6,280.4,245.1,215.6,190.0,166.9,149.1,134.2,120.3,107.2,97.1,86.6,79.0,71.8,65.0,58.5,53.7,48.5,43.7,40.4,36.6,33.9,31.1,28.3,26.0,23.7,21.4,19.6,18.1,16.6,15.8,14.0,13.1,12.1,11.0,10.1,9.3};

  // New value from Ivan, with isospin and e-loss in |y|<2.0 
  Double_t Ivan_el_pt[50] = {2142.4,10243.2,4835.9,2935.2,1993.1,1442.5,1093.2,857.3,685.0,563.2,470.2,396.9,338.3,290.7,249.5,220.7,192.2,168.7,150.1,134.6,118.7,105.9,95.9,84.5,76.7,69.6,63.0,57.2,51.6,46.5,42.0,38.6,35.3,31.6,29.6,27.6,24.4,22.6,20.4,18.5,17.3,16.1,14.6,13.5,12.4,11.1,10.2,9.7,8.6,8.0};

  for (int i=0;i<49;i++) {
    Ivan_sig_pt[i] *= 43264/(1E9*4.8) ;
    Ivancor_sig_pt[i] *= 43264/(1E9*4.8*0.71) ; // 0.71 is the flat acceptance
    Ivan_iso_pt[i] *= Norm/1000 ;
    Ivan_el_pt[i] *= Norm/1000 ;
  }

  // Now in bins
  double xbins[] = {0,6,12,36};
  TH1F *IsoPt = new TH1F("IsoPt","IsoPt",3,xbins);
  IsoPt->SetLineWidth(SizTh);
  IsoPt->SetLineColor(ColIso);
  IsoPt->SetLineStyle(StyIso);

  TH1F *ElPt = new TH1F("ElPt","ElPt",3,xbins);
  ElPt->SetLineWidth(4);
  ElPt->SetLineColor(ColEl);
  ElPt->SetLineStyle(StyEl);

  IsoPt->Fill(3,(Ivan_iso_pt[0] + Ivan_iso_pt[1] + Ivan_iso_pt[2])/3); // [0,6]
  ElPt->Fill(3,(Ivan_el_pt[0] + Ivan_el_pt[1] + Ivan_el_pt[2])/3); 
  IsoPt->Fill(9,(Ivan_iso_pt[3] + Ivan_iso_pt[4] + Ivan_iso_pt[5])/3); // [6,12]
  ElPt->Fill(9,(Ivan_el_pt[3] + Ivan_el_pt[4] + Ivan_el_pt[5])/3); 
  float IntIso, IntEl; 
  for (int i=6;i<18;i++) { // [12,36]
    IntIso += Ivan_iso_pt[i];
    IntEl += Ivan_el_pt[i];  
  }
  IsoPt->Fill(15,IntIso/12);
  ElPt->Fill(15,IntEl/12);

  IsoPt->Print();
  ElPt->Print(); 

  TGraphErrors *Ivan_pt_graf = new TGraphErrors(49,Ivan_pt,Ivan_sig_pt,0,0); 
  Ivan_pt_graf->SetMarkerSize(SizUs);
  Ivan_pt_graf->SetLineWidth(4);
  Ivan_pt_graf->SetLineColor(ColIso);
  Ivan_pt_graf->SetMarkerColor(ColIso); 

  TGraphErrors *Ivancor_pt_graf = new TGraphErrors(49,Ivan_pt,Ivancor_sig_pt,0,0); 
  Ivancor_pt_graf->SetMarkerSize(SizUs);
  Ivancor_pt_graf->SetLineWidth(4);
  Ivancor_pt_graf->SetLineColor(ColIso);
  Ivancor_pt_graf->SetFillColor(3);
  Ivancor_pt_graf->SetMarkerColor(ColIso); 
  Ivancor_pt_graf->SetLineStyle(3);

  TGraphErrors *Ivan_iso_pt_graf = new TGraphErrors(49,Ivan_pt,Ivan_iso_pt,0,0); 
  Ivan_iso_pt_graf->SetLineWidth(4);
  Ivan_iso_pt_graf->SetLineColor(ColIso);
  Ivan_iso_pt_graf->SetLineStyle(3);

  TGraphErrors *Ivan_el_pt_graf = new TGraphErrors(49,Ivan_pt,Ivan_el_pt,0,0); 
  Ivan_el_pt_graf->SetLineWidth(4);
  Ivan_el_pt_graf->SetLineColor(ColEl);
  Ivan_iso_pt_graf->SetLineStyle(3);

  // if (doivan)  IsoPt->Draw("SAME");
  // if (doivan)  ElPt->Draw("SAME");

  // Do not draw, since not corrected for acceptance
  //  if (doivan) Ivancor_pt_graf->Draw("L");
  //  if (doivan) Ivan_pt_graf->Draw("L");

  // Pythia
  Double_t pythia[4] = {2977,2001,645}; // 146 for pt above 30 TO BE REDONE for 36 
  TH1F *Pythia = new TH1F("Pythia","Pythia",3,xbins);
  for (int i=1;i<4;i++) {
    Pythia->SetBinContent(i,pythia[i-1]);    
  }
  Pythia->Scale(1/18000.); // Arbitrary
  Pythia->SetLineWidth(SizTh); 
  //  Pythia->Draw("same");

  // NLO
  Double_t nlo[4] = {4996,3585,1161}; // 245 for pt above 30 TO BE REDONE for 36
  TH1F *Nlo = new TH1F("Nlo","Nlo",3,xbins);
  for (int i=1;i<4;i++) {
    Nlo->SetBinContent(i,nlo[i-1]);    
  }
  Nlo->Scale(1/35850.); // Arbitrary
  Nlo->SetLineStyle(2); 
  Nlo->SetLineWidth(SizTh); 
  //  Nlo->Draw("same");

  // POWHEG
  TFile *powheg_file = new TFile("Acc/POWHEG.root");
  TH1F *Powheg = new TH1F("Powheg","Powheg",3,xbins);
  Events->Project("Powheg","zpt","dimumass<120&&dimumass>60&&zy>-2.0&&zy<2.0");

  for (int i=1;i<4;i++) {
    cout << i << " " << Powheg->GetBinContent(i) << endl ;
  }
  Powheg->Scale(578.4/Events->GetEntries()*Norm/4.0); 
  // Total xsection is 578.4 pb according to EWK, scale it to our range
  cout << "N " << Powheg->GetEntries() << " " << Events->GetEntries() << endl;
  for (int i=1;i<4;i++) {
    Powheg->SetBinContent(i,Powheg->GetBinContent(i)/Powheg->GetBinWidth(i));
    cout << " POWHEG Pt bin " << i << " " << Powheg->GetBinContent(i) << endl;
  }

  Powheg->SetLineColor(ColPow); 
  Powheg->SetLineStyle(StyPow); 
  Powheg->SetLineWidth(SizTh); 

  // Our data, in d2N/dydpt
  // Double_t x_pt[3] = {3,9,31};
  Double_t x_pt[3] = {4.71,8.34,18.8}; // Mean 17.7 for 0 to 30
  Double_t x_pt_min[3] = {0,6,12}; // Mean
  Double_t x_pt_max[3] = {6,12,36}; // Mean
  Double_t e_pt[3] = {1.37,1.89,4.62}; // RMS
  Double_t Z_pt[3] = {1.65E-08,2.05E-08,4.4E-09};
  Double_t Z_pt_e[3] = {5.0E-09,5.4E-09,1.3E-09};
  Double_t Z_pt_syst_plus[3]; Double_t Z_pt_syst_minus[3]; 

  // 
  for (int i=0;i<3;i++) {
    x_pt_min[i] = x_pt[i] - x_pt_min[i];
    x_pt_max[i] = x_pt_max[i] - x_pt[i];
    Z_pt[i] *= 1E8;
    Z_pt_e[i] *= 1E8;
    // Z_pt[i] *= 7.650E6 ; Z_pt_e[i] *= 7.650E6 ;
    Z_pt_syst_plus[i] = Syst * Z_pt[i] ;
    Z_pt_syst_minus[i] = Syst * Z_pt[i] ;
  }

  TGraphAsymmErrors *Zpt_syst = new TGraphAsymmErrors(3,x_pt,Z_pt,0,0,Z_pt_syst_plus,Z_pt_syst_minus); 
  Zpt_syst->SetLineWidth(SystSiz);
  Zpt_syst->SetLineColor(SystCol);

  TGraphAsymmErrors *Zpt_graf = new TGraphAsymmErrors(3,x_pt,Z_pt,x_pt_min,x_pt_max,Z_pt_e,Z_pt_e); 
  Zpt_graf->SetMarkerStyle(MarkUs);
  Zpt_graf->SetMarkerColor(ColUs);
  Zpt_graf->SetMarkerSize(SizUs);
  Zpt_graf->SetLineWidth(2);

  TLegend* Legend = new TLegend(0.45,0.65,0.9,0.8);
  Legend->SetFillColor(0);
  Legend->SetTextSize(0.037);
  Legend->SetBorderSize(0);
  if (dodata)  Legend->AddEntry(Zpt_graf,"CMS, |y|<2.0","p"); 
  //  Legend->AddEntry(CT10_graf,"CT10, no shadowing","f"); 
  //  Legend->AddEntry(EPS09_graf,"EPS09, shadowing","f"); 
  //  if (doivan) Legend->AddEntry(IsoPt,"Vitev, MSTW+isospin","l"); 
  //  if (doivan) Legend->AddEntry(ElPt,"Vitev, idem+eloss","l"); 
  // Legend->AddEntry(Pythia,"Pythia, arbitrary scale","l");
  // Legend->AddEntry(Nlo,"MC@NLO, arbitrary scale","l");
  Legend->AddEntry(Powheg,"POWHEG + PYTHIA 6.4","l");
  Legend->Draw(); 

  if (dolog) {
    write_tex(9,6E-8,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV",C2,16);
    write_tex(0.8,0.013,"#int Ldt = 7.2 #mub^{-1}", C2,16);
  } else {
    write_tex(xt*36,yt*3.3,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV, #int Ldt = 7.2 #mub^{-1}",C2,16);
    write_tex(0,3.3*1.008,"x10^{-8}",C1,18);
    // write_tex(12,26E-9,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV",C2,16);
    // write_tex(22,15E-9,"#int Ldt = 7.2 #mub^{-1}", C2,16);
  }

  if (!dobins) {
    if (doivan) Ivan_iso_pt_graf->Draw("L");
    if (doivan) Ivan_el_pt_graf->Draw("L");
  }
  Powheg->Draw("same");
  if (dodata) {
    Zpt_syst->Draw("E");
    Zpt_graf->Draw("P");
  }

  C2->Print("ZPT.pdf"); 
  C2->Print("ZPT.jpg"); 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *C3 = new TCanvas("ZColl","Z versus centrality",500,500);

  float top = 110; 

  Double_t Npart[3] = {356,224,46}; // from most central to most peripheral
  Double_t TAB[3] = {23.2,11.6,1.45} ; // TAB (aka Ncoll / sigma_pp in mb )
  Double_t TAB_e[3] = {1.0,0.71,0.18} ;
  Double_t Z_cent[3] = {1.65E-6, 5.95E-7, 7.92E-8} ; // dN/dy
  Double_t Z_cent_e[3] = {4.0E-7, 1.6E-7, 3.00E-8} ; 
  Double_t Z_cent_syst_plus[3] ; Double_t Z_cent_syst_minus[3] ;

  Double_t Npart_MB[1] ; Npart_MB[0] = 113 ;
  Double_t TAB_MB = 5.66 ;
  Double_t TAB_MB_e = 0.30 ;
  Double_t Z_MB[1] ; Z_MB[0] = 3.46E-7 / (TAB_MB*1E-9) ; // in pb 
  Double_t Z_MB_e[1] ; Z_MB_e[0] = 5.67E-8 / (TAB_MB*1E-9) ; // in pb

  Double_t Z_MB_syst_plus[1] ; Z_MB_syst_plus[0] = Z_MB[0] * sqrt(pow(Syst,2) + pow(TAB_MB_e/TAB_MB,2) ) ;   
  Double_t Z_MB_syst_minus[1] ; Z_MB_syst_minus[0] = Z_MB[0] * sqrt(pow(Syst,2) + pow(TAB_MB_e/TAB_MB,2) ) ;   

  Double_t Ncoll_e[3] = {0.081,0.089,0.118}; // Relative error on Ncoll, not used

  for (int i=0;i<4;i++) {
    Z_cent[i] /= TAB[i]*1E-9 ; // in pb
    Z_cent_e[i] /= TAB[i]*1E-9 ; // in pb 
    Z_cent_syst_plus[i] = sqrt ( pow(Syst,2) + pow(TAB_MB_e/TAB_MB,2) )* Z_cent[i] ; 
    Z_cent_syst_minus[i] = sqrt ( pow(Syst,2) + pow(TAB_MB_e/TAB_MB,2) )* Z_cent[i] ; 
    cout << " Z_cent[i] = " <<  Z_cent[i] <<endl;
  }

  TH1F *dummy = new TH1F("","",50,0.,416.);
  dummy->SetMinimum(0.);
  dummy->SetMaximum(top);
  dummy->SetXTitle("N_{part}");
  dummy->SetYTitle("dN/dy (|y|<2.0) / T_{AB} (pb)");
  dummy->Draw();

  TGraphAsymmErrors *Zcent_graf_syst = new TGraphAsymmErrors(3,Npart,Z_cent,0,0,Z_cent_syst_plus,Z_cent_syst_minus); 
  Zcent_graf_syst->SetLineWidth(SystSiz);
  Zcent_graf_syst->SetLineColor(SystCol);
  cout << " == RAA and systematic error" << endl;
  Zcent_graf_syst->Print();

  TGraphErrors *Zcent_graf = new TGraphErrors(3,Npart,Z_cent,0,Z_cent_e); 
  Zcent_graf->SetMarkerStyle(MarkUs);
  Zcent_graf->SetMarkerColor(ColUs);
  Zcent_graf->SetMarkerSize(SizUs);
  Zcent_graf->SetLineWidth(2);

  cout << " == RAA and statistical error" << endl;
  Zcent_graf->Print();

  TGraphAsymmErrors *Z_MB_graf_syst = new TGraphAsymmErrors(1,Npart_MB,Z_MB,0,0,Z_MB_syst_plus,Z_MB_syst_minus); 
  Z_MB_graf_syst->SetLineWidth(SystSiz);
  Z_MB_graf_syst->SetLineColor(kAzure+7);

  cout << " == MB RAA and systematic error" << endl;
  Z_MB_graf_syst->Print();

  TGraphErrors *Z_MB_graf = new TGraphErrors(1,Npart_MB,Z_MB,0,Z_MB_e); 
  Z_MB_graf->SetMarkerStyle(25);
  Z_MB_graf->SetMarkerColor(kBlue);
  Z_MB_graf->SetMarkerSize(SizUs);
  Z_MB_graf->SetLineWidth(2);
  cout << " == MB RAA and systematic error" << endl;
  Z_MB_graf->Print();

  TGraphErrors *Z_MB_graf_bis = new TGraphErrors(1,Npart_MB,Z_MB,0,0); 
  Z_MB_graf_bis->SetMarkerStyle(21);
  Z_MB_graf_bis->SetMarkerColor(kWhite);
  Z_MB_graf_bis->SetMarkerSize(SizUs);

  // POWHEG
  TFile *powheg_file = new TFile("Acc/POWHEG.root");
  TH1F *Powheg_cent = new TH1F("Powheg_cent","Powheg_cent",1,0.,416.);
  // Trick to get the entries, since we cut on mass and the dum histo is 0 to 400, ok !   
  Events->Project("Powheg_cent","dimumass","dimumass<120&&dimumass>60&&zy>-2.0&&zy<2.0");
  Powheg_cent->Scale(578.4/Events->GetEntries()/4); 
  // Total xsection is 578.4 pb according to EWK, scale it to our range
  cout << "N " << Powheg_cent->GetEntries() << " " << Events->GetEntries() << endl;
  Powheg_cent->SetLineStyle(StyPow); 
  Powheg_cent->SetLineColor(ColPow); 
  Powheg_cent->SetLineWidth(SizTh); 

  cout << "POWHEG Integrated " << Powheg_cent->GetBinContent(1) << endl;  

  TH1F *EPS09_cent = new TH1F("EPS09_cent","EPS09_cent",1,0.,416.);
  EPS09_cent->SetBinContent(1,243.9/4.0);
  EPS09_cent->SetBinError(1,15./4.0);
  EPS09_cent->SetLineStyle(StyEPS); 
  EPS09_cent->SetLineColor(ColEPS); 
  EPS09_cent->SetLineWidth(SizTh); 

  TH1F *CT10_cent = new TH1F("CT10_cent","CT10_cent",1,0.,416.);
  CT10_cent->SetBinContent(1,249.0/4.0);
  // CT10_cent->SetBinError(1,9.3/4.0);
  CT10_cent->SetLineStyle(StyCT); 
  CT10_cent->SetLineColor(ColCT); 
  CT10_cent->SetLineWidth(SizTh); 

  TH1F *IvIso_cent = new TH1F("IvIso_cent","IvIso_cent",1,0.,416.);
  IvIso_cent->SetBinContent(1,62.8);
  // CT10_cent->SetBinError(1,9.3/4.0);
  IvIso_cent->SetLineStyle(StyIso); 
  IvIso_cent->SetLineColor(ColIso); 
  IvIso_cent->SetLineWidth(SizTh); 

//
  double cbins[4];
  cbins[0] = 0;
  cbins[1] = (Npart[2]+Npart[1])/2;
  cbins[2] = (Npart[1]+Npart[0])/2;
  cbins[3] = 416;
//
  TH1F *IvEl_cent = new TH1F("IvEl_cent","IvEl_cent",3,cbins);
  IvEl_cent->SetBinContent(1,62.2);
  IvEl_cent->SetBinContent(2,60.8);
  IvEl_cent->SetBinContent(3,60.4);
  IvEl_cent->SetLineStyle(StyEl); 
  IvEl_cent->SetLineColor(ColEl); 
  IvEl_cent->SetLineWidth(SizTh); 

  TH1F *h3 = (TH1F*) EPS09_cent->Clone("EPS09ter");
  h3->SetFillColor(ColEPS-4);
  h3->SetFillStyle(FilEPS);
  h3->SetMarkerSize(0); 

  TLegend* Legend1 = new TLegend(0.20,0.72,0.88,0.82);
  Legend1->SetFillColor(4000);
  Legend1->SetTextSize(0.037);
  Legend1->SetBorderSize(0);
  Legend1->AddEntry(Zcent_graf,"Centrality 30-100, 10-30, 0-10%","p"); 
  Legend1->AddEntry(Z_MB_graf,"Minimum bias 0-100%","p"); 

  TLegend* Legend = new TLegend(0.25,0.18,0.88,0.43);
  Legend->SetFillColor(0);
  Legend->SetTextSize(0.037);
  Legend->SetBorderSize(0);
  Legend->AddEntry(Powheg_cent,"POWHEG + PYTHIA 6.4","l");
  Legend->AddEntry(CT10_cent,"Paukkunen et al., CT10+isospin","l");
  Legend->AddEntry(h3,"Paukkunen et al., idem+EPS09","lf");
  Legend->AddEntry(IvIso_cent,"Neufeld et al., MSTW+isospin","l"); 
  Legend->AddEntry(IvEl_cent,"Neufeld et al., idem+eloss","l"); 

  Legend1->Draw();
  Legend->Draw();
  dummy->Draw("same");

  h3->Draw("e2,same");
  EPS09_cent->Draw("same,hist");
  CT10_cent->Draw("same");
  IvIso_cent->Draw("same");
  IvEl_cent->Draw("same");
  Powheg_cent->Draw("same");

  if (dodata) { 
    Zcent_graf_syst->Draw("E");
    Zcent_graf->Draw("P");
    Z_MB_graf_syst->Draw("E"); 
    Z_MB_graf_bis->Draw("P");
    Z_MB_graf->Draw("P");

  }

  write_tex(xt*416,yt*top,"CMS PbPb #sqrt{s_{NN}} = 2.76 TeV, #int Ldt = 7.2 #mub^{-1}",C3,16);
  //  write_tex(300,80,"#int Ldt = 7.2 #mub^{-1}",C3,16);

  C3->Print("RaaZ.pdf"); 
  C3->Print("RaaZ.jpg"); 
}
