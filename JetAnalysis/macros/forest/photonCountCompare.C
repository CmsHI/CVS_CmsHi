#include "CutAndBinCollection2011.h"
void photonCountCompare() {
   TFile* inf = new TFile("photonPurityCollection.root");
   TH1D* isoSum = (TH1D*)inf->Get("hN_sumIso");
   TH1D* iso3d = (TH1D*)inf->Get("hN_3dIso");
   TH1D* isoFisher = (TH1D*)inf->Get("hN_fisherIso");
   TCanvas* c1 = new TCanvas("c1","",500,500);
   handsomeTH1(isoFisher,1);
   handsomeTH1(isoSum,2);
   handsomeTH1(iso3d,4);
   isoSum->SetMarkerStyle(kOpenCircle);
   iso3d->SetMarkerStyle(25);
   
   char *cents[3] = {"0-10%","10-30%","30-100%"};
   isoSum->GetXaxis()->SetBinLabel(1,cents[0]);
   isoSum->GetXaxis()->SetBinLabel(2,cents[1]);
   isoSum->GetXaxis()->SetBinLabel(3,cents[2]);
   isoSum->GetXaxis()->SetLabelSize(0.07);
   isoSum->SetXTitle("Centrality");
   isoSum->SetAxisRange(0,800,"Y");
   isoSum->SetYTitle("Number of Photons");
   isoSum->Draw();
   iso3d->Draw("same");
   isoFisher->Draw("same");

      
   // for (Int_t i=0;i<6;i++) {
   //    t->DrawText(-0.42,y[i],labels[i]);
   // }
   
   TLegend* leg1 =  new TLegend(0.2012097,0.7084746,1,0.9300847,NULL,"brNDC");
   easyLeg(leg1,"signals/efficiency");
   leg1->AddEntry(isoFisher,"Fisher method");
   leg1->AddEntry(isoSum,"#SigmaISO method");
   leg1->AddEntry(iso3d, "separate ISO method");
   leg1->Draw();


   c1->SaveAs("comparePhotonCounts.gif");
   c1->SaveAs("comparePhotonCounts.pdf");

   
}
