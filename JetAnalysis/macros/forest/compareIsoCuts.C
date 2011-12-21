#include "CutAndBinCollection2011.h"
#include "photonIDEfficiency.C"

void compareIsoCuts() {
   
   int nBins = 10;
   TFile* inf = new TFile("photonPurityCollection.root");
   TH1D* finSpectra[5][10];
   TH1D* eff[5][10];
   TH1D* fluc[5];
   TH1D* hEff[5];
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      fluc[icent] = new TH1D(Form("fluc_icent%d",icent),"; #SigmaISO Cut (GeV); Ratio : Yield / Yield^{#SigmaISO<1GeV} ",nBins,-.5,9.5); 
      hEff[icent] = new TH1D(Form("hEff_icent%d",icent),"; #SigmaISO Cut (GeV); Isolation Efficiency ",nBins,-.5,9.5);
      
      for ( int icut = 1 ; icut<=nBins ; icut++) {
	 int isoCut = icut - 1;
	 finSpectra[icent][icut] = (TH1D*)inf->Get(Form("finSpec_icent%d_sumIso_isoCut%d",icent,isoCut));
	 eff[icent][icut] = (TH1D*)inf->Get(Form("heff_icent%d_id3_isoCut%d",icent,isoCut));	
	 fluc[icent]->SetBinContent(  fluc[icent]->FindBin( isoCut),  finSpectra[icent][icut]->GetBinContent( finSpectra[icent][icut]->FindBin(65)) );
	 fluc[icent]->SetBinError( fluc[icent]->FindBin( isoCut),  finSpectra[icent][icut]->GetBinError( finSpectra[icent][icut]->FindBin(65)));
	  hEff[icent]->SetBinContent( hEff[icent]->FindBin( isoCut), eff[icent][icut]->GetBinContent( eff[icent][icut]->FindBin(65)));
	  hEff[icent]->SetBinError  ( hEff[icent]->FindBin( isoCut), eff[icent][icut]->GetBinError( eff[icent][icut]->FindBin(65)));
	 
      }
   }
   
   TCanvas* c2  = new TCanvas("c2","",100 + 300 * nCent_std,400);
   makeMultiPanelCanvas(c2,nCent_std,1,0.0,0.0,0.2,0.15,0.02);
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      c2->cd(nCent_std - icent + 1 );
      fluc[icent]->Scale(1./  fluc[icent]->GetBinContent(  fluc[icent]->FindBin(1)));
      fluc[icent]->SetAxisRange(0.5,1.5,"Y");
      handsomeTH1(fluc[icent]);
      fluc[icent]->Draw();
      int lowerCent = centBin_std[icent-1];
      int upperCent = centBin_std[icent]-1;
      drawText(Form("%.0f%% - %.0f%%", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),0.5680963,0.2369118);
      jumSun(-.5,1.15,9.5,1.15,2);
      jumSun(-.5,.85,9.5,.85,2);
   }
   c2->SaveAs("compareYieldsInVariousIsoCut.pdf");


   TCanvas* c3  = new TCanvas("c3","",100 + 300 * nCent_std,400);
   makeMultiPanelCanvas(c3,nCent_std,1,0.0,0.0,0.2,0.15,0.02);
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      c3->cd(nCent_std - icent + 1 );
      hEff[icent]->SetAxisRange(0.5,1.05,"Y");
      handsomeTH1(hEff[icent]);
      hEff[icent]->Draw();
      int lowerCent = centBin_std[icent-1];
      int upperCent = centBin_std[icent]-1;
      drawText(Form("%.0f%% - %.0f%%", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),0.5680963,0.2369118);
   }
   
   c3->SaveAs("compareEffciencyVariousIsoCut.pdf");
}
