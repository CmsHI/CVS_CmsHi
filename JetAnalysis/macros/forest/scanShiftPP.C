#include "CutAndBinCollection2011.h"
#include "photonIDEfficiency.C"


void scanShiftPP() {
  TH1D* hPurity = new TH1D("hShift",";Shifted amount of #sigma_{#eta#eta};Purity",19,-0.00019999,0.00018001);
  TH1D* hChisq    = (TH1D*)hPurity->Clone("hChi");
  hChisq->SetTitle(";Shifted amount of #sigma_{#eta#eta};#Chi^{2}/n_{dof}");
  hPurity->Sumw2();
  hChisq->Sumw2();
  hChisq->SetBinContent ( hChisq->FindBin(0 ), 3.14364);
  hPurity->SetBinContent( hPurity->FindBin(0 ), 0.789137);
  hChisq->SetBinContent ( hChisq->FindBin(-2e-05 ), 2.6314);
  hPurity->SetBinContent( hPurity->FindBin(-2e-05 ), 0.790882);
  hChisq->SetBinContent ( hChisq->FindBin(-4e-05 ), 2.22616);
  hPurity->SetBinContent( hPurity->FindBin(-4e-05 ), 0.791533);
  hChisq->SetBinContent ( hChisq->FindBin(-6e-05 ), 2.01238);
  hPurity->SetBinContent( hPurity->FindBin(-6e-05 ), 0.791114);
  hChisq->SetBinContent ( hChisq->FindBin(-8e-05 ), 1.73617);
  hPurity->SetBinContent( hPurity->FindBin(-8e-05 ), 0.791389);
  hChisq->SetBinContent ( hChisq->FindBin(-0.0001 ), 1.61071);
  hPurity->SetBinContent( hPurity->FindBin(-0.0001 ), 0.789835);
    hChisq->SetBinContent ( hChisq->FindBin(-0.00012 ), 1.56843);
    hPurity->SetBinContent( hPurity->FindBin(-0.00012 ), 0.788627);
    hChisq->SetBinContent ( hChisq->FindBin(-0.00014 ), 1.66491);
    hPurity->SetBinContent( hPurity->FindBin(-0.00014 ), 0.78527);
    hChisq->SetBinContent ( hChisq->FindBin(-0.00016 ), 1.8285);
    hPurity->SetBinContent( hPurity->FindBin(-0.00016 ), 0.783879);
    hChisq->SetBinContent ( hChisq->FindBin(-0.00018 ), 2.21563);
    hPurity->SetBinContent( hPurity->FindBin(-0.00018 ), 0.781957);
    hChisq->SetBinContent ( hChisq->FindBin(2e-05 ), 3.52338);
    hPurity->SetBinContent( hPurity->FindBin(2e-05 ), 0.789721);
    hChisq->SetBinContent ( hChisq->FindBin(4e-05 ), 3.9675);
    hPurity->SetBinContent( hPurity->FindBin(4e-05 ), 0.78906);
    hChisq->SetBinContent ( hChisq->FindBin(6e-05 ), 4.69765);
    hPurity->SetBinContent( hPurity->FindBin(6e-05 ), 0.786095);
    hChisq->SetBinContent ( hChisq->FindBin(8e-05 ), 5.30316);
    hPurity->SetBinContent( hPurity->FindBin(8e-05 ), 0.783875);
    hChisq->SetBinContent ( hChisq->FindBin(0.0001 ), 6.19072);
    hPurity->SetBinContent( hPurity->FindBin(0.0001 ), 0.780226);
    hChisq->SetBinContent ( hChisq->FindBin(0.00012 ), 6.93422);
    hPurity->SetBinContent( hPurity->FindBin(0.00012 ), 0.775868);
    hChisq->SetBinContent ( hChisq->FindBin(0.00014 ), 7.82672);
    hPurity->SetBinContent( hPurity->FindBin(0.00014 ), 0.77079);
    hChisq->SetBinContent ( hChisq->FindBin(0.00016 ), 8.31059);
    hPurity->SetBinContent( hPurity->FindBin(0.00016 ), 0.76845);
    hChisq->SetBinContent ( hChisq->FindBin(0.00018 ), 9.50914);
    hPurity->SetBinContent( hPurity->FindBin(0.00018 ), 0.759951);
    

    TCanvas* c1 = new TCanvas("c1","",400,400);
    hChisq->SetAxisRange(0,10,"Y");
    handsomeTH1(hChisq);
    hChisq->Draw();
    jumSun(-.000138,0,-0.000138,10,2);
    gPad->SetRightMargin(0.12);
    c1->SaveAs("scanShiftSigTemplate1.pdf");

    TCanvas* c2 = new TCanvas("c2","",400,400);
    hPurity->SetAxisRange(0,1,"Y");
    handsomeTH1(hPurity);
    hPurity->Draw();
    jumSun(-.000138,0,-.000138,1,2);
    gPad->SetRightMargin(0.12);
    c2->SaveAs("scanShiftSigTemplate2.pdf");


}
