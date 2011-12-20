#include "CutAndBinCollection2011.h"
#include "photonIDEfficiency.C"

void compareIsoCuts() {
   
   int nBins = 10;
   TFile* inf = new TFile("photonPurityCollection.root");
   TH1D* finSpectra[5][10];
   TH1D* fluc[5];
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      fluc[icent] = new TH1D(Form("fluc_icent%d",icent),"; #SigmaISO Cut (GeV); Ratio : Yield / Yield^{#SigmaISO<1GeV} ",nBins,-.5,9.5); 
      for ( int icut = 1 ; icut<=nBins ; icut++) {
	 int isoCut = icut - 1;
	 finSpectra[icent][icut] = (TH1D*)inf->Get(Form("finSpec_icent%d_sumIso_isoCut%d",icent,isoCut));
	 fluc[icent]->SetBinContent(  fluc[icent]->FindBin( isoCut),  finSpectra[icent][icut]->GetBinContent( finSpectra[icent][icut]->FindBin(65)) );
	 fluc[icent]->SetBinError( fluc[icent]->FindBin( isoCut),  finSpectra[icent][icut]->GetBinError( finSpectra[icent][icut]->FindBin(65)));
	 
      }
   }
   
   TCanvas* c2  = new TCanvas("c2","",100 + 300 * nCent_std,400);
   makeMultiPanelCanvas(c2,nCent_std,1,0.0,0.0,0.2,0.15,0.02);
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      c2->cd(nCent_std - icent + 1 );
      fluc[icent]->Scale(1./  fluc[icent]->GetBinContent(  fluc[icent]->FindBin(1)));
      fluc[icent]->SetAxisRange(0.8,1.2,"Y");
      handsomeTH1(fluc[icent]);
      fluc[icent]->Draw();
      int lowerCent = centBin_std[icent-1];
      int upperCent = centBin_std[icent]-1;
      drawText(Form("%.0f%% - %.0f%%", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),0.5680963,0.2369118);

      
   }
   c2->SaveAs("compareYieldsInVariousIsoCut.pdf");
   
}
