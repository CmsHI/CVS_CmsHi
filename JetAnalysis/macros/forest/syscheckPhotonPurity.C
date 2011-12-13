#include "CutAndBinCollection2011.h"
void syscheckPhotonPurityDiff(int icent = 0, double fluc = 0.20, bool drawAll=true);
void syscheckPhotonPurity(double fluc = 0.2) {
   TH1D* sys2 = new TH1D("h3sys","A_{gj};Event Fraction",20,-1,1);
   sys2->SetBinContent(6,0.0003);
   sys2->SetBinContent(7,0.0004);
   sys2->SetBinContent(8,0.002);
   sys2->SetBinContent(9,0.006);
   sys2->SetBinContent(10,0.0056);
   sys2->SetBinContent(11,0.0052);
   sys2->SetBinContent(12,0.0048);
   sys2->SetBinContent(13,0.0044);
   sys2->SetBinContent(14,0.004);
   sys2->SetBinContent(15,0.0026);
   sys2->SetBinContent(16,0.0013);
   sys2->SetBinContent(17,0.000);

   TH1D* sys21 = (TH1D*)sys2->Clone("sys21");
   sys21->Add(sys2,-2);
   
   TH1D* sys1 = new TH1D("h11sys","A_{gj};Event Fraction",20,-1,1);
   sys1->SetBinContent(6,0.0003);
   sys1->SetBinContent(7,0.002);
   sys1->SetBinContent(8,0.004);
   sys1->SetBinContent(9,0.005);
   sys1->SetBinContent(10,0.0046);
   sys1->SetBinContent(11,0.0042);
   sys1->SetBinContent(12,0.0038);
   sys1->SetBinContent(13,0.0034);
   sys1->SetBinContent(14,0.003);
   sys1->SetBinContent(15,0.0028);
   sys1->SetBinContent(16,0.0016);
   sys1->SetBinContent(17,0.000);
   TH1D* sys11 = (TH1D*)sys1->Clone("sys31");
   sys11->Add(sys1,-2);

   TH1D* sys0 = new TH1D("h3sys0","A_{gj};Event Fraction",20,-1,1);
   sys0->SetBinContent(6,0.001);
   sys0->SetBinContent(7,0.002);
   sys0->SetBinContent(8,0.006);
   sys0->SetBinContent(9,0.012);
   sys0->SetBinContent(10,0.011);
   sys0->SetBinContent(11,0.010);
   sys0->SetBinContent(12,0.009);
   sys0->SetBinContent(13,0.008);
   sys0->SetBinContent(14,0.0075);
   sys0->SetBinContent(15,0.005);
   sys0->SetBinContent(16,0.002);
   sys0->SetBinContent(17,0.000);

   TH1D* sys01 = (TH1D*)sys0->Clone("sys01");
   sys01->Add(sys0,-2);

   sys0->SetLineWidth(2);
   sys1->SetLineWidth(2);
   sys2->SetLineWidth(2);
   sys01->SetLineWidth(2);
   sys11->SetLineWidth(2);
   sys21->SetLineWidth(2);
   
   TCanvas* c1 = new TCanvas("c1","",1000,700);
   makeMultiPanelCanvas(c1,3,2,0.0,0.0,0.2,0.15,0.02);
   c1->cd(1);
   syscheckPhotonPurityDiff(2,fluc);
   drawText("30%-100%",0.3,0.85);
   c1->cd(4);
   syscheckPhotonPurityDiff(2,fluc,false);
   sys2->Draw("c f  same");
   sys21->Draw("c f same");
   c1->cd(2);
   syscheckPhotonPurityDiff(1,fluc);
   drawText("10%-30%",0.3,0.85);
   c1->cd(5);
   syscheckPhotonPurityDiff(1,fluc,false);
   sys1->Draw("c f same");
   sys11->Draw("c f same");
   c1->cd(3);
   syscheckPhotonPurityDiff(0,fluc);
   drawText("0%-10%",0.3,0.85);
   c1->cd(6);
   syscheckPhotonPurityDiff(0,fluc,false);
   sys0->Draw("c f same");
   sys01->Draw("c f same");
   c1->SaveAs("systematics_purity.gif");
   c1->SaveAs("systematics_purity.eps");

}
void syscheckPhotonPurityDiff(int icent, double fluc, bool drawAll) 
{
   
   TFile* infSpec = new TFile(Form("photonJet/outhists_cbin%d_output-data-Photon-v3_v9.root",icent));
   TH1D* hAll  = (TH1D*)infSpec->Get(Form("reco%dSignalAllNormScaled",icent));
   TH1D* hBkg   = (TH1D*)infSpec->Get(Form("reco%dBkgSShapeNormScaled",icent));
   TH1D* hjetBkg   = (TH1D*)infSpec->Get(Form("reco%dBkgDPhiNormScaled",icent));
   handsomeTH1(hAll);
   handsomeTH1(hBkg,2);
   hAll->SetXTitle("A_{gj}");
   hAll->SetAxisRange(0,0.5,"Y");
   
   hAll->Add(hjetBkg,-1);
   int nBinsX = hAll->GetNbinsX();
   
   TH2D* smeared = new TH2D("smeared",";A_{gj};Entries", nBinsX, hAll->GetBinLowEdge(1), hAll->GetBinLowEdge(nBinsX) + hAll->GetBinWidth(1), 400,-.04,0.5);
   
   TH2D* fraction = new TH2D("fraction",";A_{gj};Entries", nBinsX, hAll->GetBinLowEdge(1), hAll->GetBinLowEdge(nBinsX) + hAll->GetBinWidth(1), 300,-.03,.03);   
   int nMax = 1000;
   TH1D* hsm = (TH1D*)hAll->Clone("hsmeared");
   TH1D* href =(TH1D*)hAll->Clone("href");
   href->Add(hBkg,-1);
   href->Scale(1./href->Integral());
   
   for ( int i=0 ;  i<= nMax ; i++) {
      float factor = 1. + 2 * (float)fluc * ((float)i/(float)nMax - 0.5) ;
      // cout << "factor = " << factor << endl;
      hsm->Reset();
      hsm->Add(hAll);
      hsm->Add(hBkg,-factor);
      hsm->Scale(1./hsm->Integral());
      for (int iBin =1 ; iBin<= nBinsX ; iBin++) {
	 smeared->Fill( hsm->GetBinCenter(iBin),  hsm->GetBinContent(iBin));
	 fraction->Fill(hsm->GetBinCenter(iBin),  hsm->GetBinContent(iBin) - href->GetBinContent(iBin)  ); 
      }
   }
   handsomeTH1(smeared);
   smeared->SetAxisRange(0,0.5,"Z");
   smeared->DrawCopy("col");
   hBkg->SetMarkerStyle(kOpenCircle);
   hBkg->SetMarkerColor(kGreen+2);
   hBkg->SetLineColor(kGreen+2);
   hBkg->DrawCopy("same p");
   hsm->DrawCopy("same");
   
   if (!drawAll) {
      fraction->SetAxisRange(0,0.5,"Z");
      fraction->Draw("col");
   }
   if ( icent == 1) {
      TLegend *t3= new TLegend(0.2998319,0.6098612,0.779229,0.8149715,NULL,"brNDC");
      easyLeg(t3,"PbPb");
      if (drawAll) {
	 t3->AddEntry(hsm,"Central value","pl");
	 t3->AddEntry(hBkg,"#sigma_{#eta#eta} sideband","p");
      }
      else {
	 t3= new TLegend(0.2998319,0.7098612,0.779229,0.96149715,NULL,"brNDC");
	 easyLeg(t3,"fluctuation");
      }
      t3->Draw();
      
   }
   
}
