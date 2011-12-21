#include "CutAndBinCollection2011.h"
#include "photonIDEfficiency.C"

void compareIsoCuts() {
   
   int nBins = 10;
   TFile* inf = new TFile("photonPurityCollection.root");
   TH1D* finSpectra[5][10];
   TH1D* eff[5][10];
   TH1D* fluc[5];
   TH1D* hEff[5];
   
   int nBinsSB = 5;
   TH1D* finSpectraSB[5][10];
   TH1D* flucSB[5];
   
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      fluc[icent] = new TH1D(Form("fluc_icent%d",icent),"; #SigmaISO Cut (GeV); Ratio : Yield / Yield^{#SigmaISO<1GeV} ",nBins,-.5,9.5); 
      hEff[icent] = new TH1D(Form("hEff_icent%d",icent),"; #SigmaISO Cut (GeV); Isolation Efficiency ",nBins,-.5,9.5);
      
      cout << " here 1 " << endl;
      for ( int icut = 1 ; icut<=nBins ; icut++) {
	 int isoCut = icut - 1;
	 finSpectra[icent][icut] = (TH1D*)inf->Get(Form("finSpec_icent%d_sumIso_isoCut%d",icent,isoCut));
	 eff[icent][icut] = (TH1D*)inf->Get(Form("heff_icent%d_id3_isoCut%d",icent,isoCut));	
	 fluc[icent]->SetBinContent(  fluc[icent]->FindBin( isoCut),  finSpectra[icent][icut]->GetBinContent( finSpectra[icent][icut]->FindBin(65)) );
	 fluc[icent]->SetBinError( fluc[icent]->FindBin( isoCut),  finSpectra[icent][icut]->GetBinError( finSpectra[icent][icut]->FindBin(65)));
	 cout << " here 2 " << endl;
 
	 hEff[icent]->SetBinContent( hEff[icent]->FindBin( isoCut), eff[icent][icut]->GetBinContent( eff[icent][icut]->FindBin(65)));
	 hEff[icent]->SetBinError  ( hEff[icent]->FindBin( isoCut), eff[icent][icut]->GetBinError( eff[icent][icut]->FindBin(65)));
	 cout << " here 3 " << endl;
	 
      }
      
      flucSB[icent] =  new TH1D(Form("flucSB_icent%d",icent),"; #SigmaISO Sideband (GeV); Ratio : Yield / Yield_{ 10 - 20GeV band} ",nBinsSB,5.5,10.5);
      handsomeTH1(flucSB[icent]);
      flucSB[icent]->SetNdivisions(505);
      for ( int icut = 1 ; icut<=nBinsSB ; icut++) {
	 int sbCut = icut+5;
      	 finSpectraSB[icent][icut] = (TH1D*)inf->Get(Form("finSpec_icent%d_sumIso_sbisoCut%d",icent,sbCut));
      	 cout << " name = " << Form("finSpec_icent%d_sumIso_sbisoCut%d",icent,sbCut) << endl;
	 flucSB[icent]->SetBinContent(  flucSB[icent]->FindBin( sbCut),  finSpectraSB[icent][icut]->GetBinContent( finSpectraSB[icent][icut]->FindBin(65)) );
      	 flucSB[icent]->SetBinError  (  flucSB[icent]->FindBin( sbCut),  finSpectraSB[icent][icut]->GetBinError  ( finSpectraSB[icent][icut]->FindBin(65)) );
	 cout <<   flucSB[icent]->FindBin( sbCut) << ":: " <<  finSpectraSB[icent][icut]->GetBinContent( finSpectraSB[icent][icut]->FindBin(65)) << endl;
	 cout << finSpectraSB[icent][icut]->GetBinError  ( finSpectraSB[icent][icut]->FindBin(65)) << endl;
      }
      
   }
   
   TCanvas* c5  = new TCanvas("c5","",100 + 300 * nCent_std,400);
   makeMultiPanelCanvas(c5,nCent_std,1,0.0,0.0,0.2,0.15,0.02);
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      c5->cd(nCent_std - icent + 1 );
      flucSB[icent]->Scale(1./  flucSB[icent]->GetBinContent(  flucSB[icent]->FindBin(10)));                                                                
      flucSB[icent]->SetAxisRange(0.5,1.5,"Y");                                                                                                                 
      handsomeTH1(flucSB[icent]);
      flucSB[icent]->DrawCopy();
      int lowerCent = centBin_std[icent-1];
      int upperCent = centBin_std[icent]-1;
      drawText(Form("%.0f%% - %.0f%%", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),0.5680963,0.2369118);
      jumSun(5.5,1.1,10.5,1.1,2);
      jumSun(5.5,.9,10.5,.9,2);
   }
   
   cout << " here 4 " << endl;
   
   TCanvas* c2  = new TCanvas("c2","",100 + 300 * nCent_std,400);
   makeMultiPanelCanvas(c2,nCent_std,1,0.0,0.0,0.2,0.15,0.02);
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      c2->cd(nCent_std - icent + 1 );
      cout << " here 11" << endl;
      fluc[icent]->Scale(1./  fluc[icent]->GetBinContent(  fluc[icent]->FindBin(1)));
      cout << " here 10 " << endl;
      fluc[icent]->SetAxisRange(0.5,1.5,"Y");
      cout << " here 9 " << endl;
      handsomeTH1(fluc[icent]);
      cout << " here 8 " << endl;
      fluc[icent]->Draw();
      cout << " here 6 " << endl;
      int lowerCent = centBin_std[icent-1];
      cout << " here 5 " << endl;
      int upperCent = centBin_std[icent]-1;
      drawText(Form("%.0f%% - %.0f%%", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),0.5680963,0.2369118);
      jumSun(-.5,1.15,9.5,1.15,2);
      jumSun(-.5,.85,9.5,.85,2);
   }
   //   c2->SaveAs("compareYieldsInVariousIsoCut.pdf");


   TCanvas* c3  = new TCanvas("c3","",100 + 300 * nCent_std,400);
   makeMultiPanelCanvas(c3,nCent_std,1,0.0,0.0,0.2,0.15,0.02);
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      cout << " here 75 " << endl;
      c3->cd(nCent_std - icent + 1 );
      cout << " here 65 " << endl;
      hEff[icent]->SetAxisRange(0.5,1.05,"Y");
      cout << " here 55 " << endl;
      handsomeTH1(hEff[icent]);
      cout << " here 45 " << endl;
      hEff[icent]->Draw();
      cout << " here 35 " << endl;
      cout << " here 25 " << endl;
      int lowerCent = centBin_std[icent-1];
      int upperCent = centBin_std[icent]-1;
      drawText(Form("%.0f%% - %.0f%%", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),0.5680963,0.2369118);
      cout << " here 15 " << endl;
   }
   
   c3->SaveAs("compareEffciencyVariousIsoCut.pdf");




}
