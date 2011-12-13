#include "CutAndBinCollection2011.h"
double ytrapezoid(double *x, double *height) 
{
   if (x[0] < -0.2)
      return height[0] * ( 1 + (x[0]+0.2)/(0.3));
   else if (x[0] < 0.4)
      return height[0];
   else if (x[0] < 0.7)
      return height[0] * ( 1 + -(x[0]-0.4)/(0.3));
   else
      return -100;
}
void syscheckPhotonPurityDiff(int icent = 0, double fluc = 0.20, bool drawDiff=false);
void syscheckPhotonPurity(double fluc = 0.2) {
   
   TCanvas* c1 = new TCanvas("c1","",1000,700);
   makeMultiPanelCanvas(c1,3,2,0.0,0.0,0.2,0.15,0.02);
   c1->cd(1);
   syscheckPhotonPurityDiff(2,fluc);
   drawText("30%-100%",0.3,0.85);
   c1->cd(4);
   syscheckPhotonPurityDiff(2,fluc,true);
   TF1* yt3 = new TF1("yt3",ytrapezoid,-.5,.7,1);
   yt3->SetParameter(0,0.005);
   yt3->SetLineColor(kYellow-6);
   yt3->Draw("same l");
   TF1* yt3m = new TF1("yt3m",ytrapezoid,-.5,.7,1);
   yt3m->SetParameter(0,-0.005);
   yt3m->SetLineColor(kYellow-6);
   yt3m->Draw("same l");
   
   c1->cd(2);
   syscheckPhotonPurityDiff(1,fluc);
   drawText("10%-30%",0.3,0.85);
   c1->cd(5);
   syscheckPhotonPurityDiff(1,fluc,true);
   TF1* yt4 = new TF1("yt4",ytrapezoid,-.5,.7,1);
   yt4->SetParameter(0,0.005);
   yt4->SetLineColor(kYellow-6);
   yt4->Draw("same l");
   TF1* yt4m = new TF1("yt4m",ytrapezoid,-.5,.7,1);
   yt4m->SetParameter(0,-0.005);
   yt4m->SetLineColor(kYellow-6);
   yt4m->Draw("same l");  
   c1->cd(3);
   syscheckPhotonPurityDiff(0,fluc);
   drawText("0%-10%",0.3,0.85);
   c1->cd(6);
   syscheckPhotonPurityDiff(0,fluc,true);
   TF1* yt5 = new TF1("yt5",ytrapezoid,-.5,.7,1);
   yt5->SetParameter(0,0.012);
   yt5->SetLineColor(kYellow-6);
   yt5->Draw("same l");
   TF1* yt5m = new TF1("yt5m",ytrapezoid,-.5,.7,1);
   yt5m->SetParameter(0,-0.012);
   yt5m->SetLineColor(kYellow-6);
   yt5m->Draw("same l"); 
   
   c1->SaveAs("systematics_purity.gif");
   c1->SaveAs("systematics_purity.eps");

}
void syscheckPhotonPurityDiff(int icent, double fluc, bool drawDiff)
{
   
   TFile* infSpec = new TFile(Form("photonJet/outhists_cbin%d_output-data-Photon-v3_v9.root",icent));
   TH1D* hAll  = (TH1D*)infSpec->Get(Form("reco%dSignalAllNormScaled",icent));
   TH1D* hBkg   = (TH1D*)infSpec->Get(Form("reco%dBkgSShapeNormScaled",icent));
   TH1D* hjetBkg   = (TH1D*)infSpec->Get(Form("reco%dBkgDPhiNormScaled",icent));
   
   hAll->Add(hjetBkg,-1);   // Never change anymore
   
   TH1D* href =(TH1D*)hAll->Clone("href");
   href->Add(hBkg,-1);
   href->Scale(1./href->Integral());
   TH1D* huBound = (TH1D*)href->Clone("huBound");
   TH1D* hlBound = (TH1D*)href->Clone("hlBound");

   handsomeTH1(hAll);
   handsomeTH1(hBkg,2);
   hAll->SetAxisRange(0,0.5,"Y");
   
   int nMax = 1000;
   int nBinsX = hAll->GetNbinsX();
   TH1D* hsm = (TH1D*)hAll->Clone("hsmeared");
  
   
   for ( int i=0 ;  i<= nMax ; i++) {
      float factor = 1. + 2 * (float)fluc * ((float)i/(float)nMax - 0.5) ;
      // cout << "factor = " << factor << endl;
      hsm->Reset();
      hsm->Add(hAll);
      hsm->Add(hBkg,-factor);
      hsm->Scale(1./hsm->Integral());
      for (int iBin =1 ; iBin<= nBinsX ; iBin++) {
	 if ( hsm->GetBinContent(iBin) > huBound->GetBinContent(iBin)  )
	    huBound->SetBinContent(iBin, hsm->GetBinContent(iBin));
	 if ( hsm->GetBinContent(iBin) < hlBound->GetBinContent(iBin)  )
            hlBound->SetBinContent(iBin, hsm->GetBinContent(iBin));
      }
   }
   
   handsomeTH1(huBound,2);
   handsomeTH1(hlBound,4);
   
   hBkg->SetMarkerStyle(kOpenCircle);
   hBkg->SetMarkerColor(kGreen+2);
   hBkg->SetLineColor(kGreen+2);
   href->SetXTitle("A_{#gamma J} = (p_{T}^{#gamma}-p_{T}^{J})/(p_{T}^{#gamma}+p_{T}^{J})");
   href->SetYTitle("N_{evt}^{-1} dN/dA_{#gamma J}");
   if ( drawDiff )  
      href->SetYTitle("Fluctuation of N_{evt}^{-1} dN/dA_{#gamma J}");
   
   href->SetAxisRange(0,.5,"Y");
   handsomeTH1(href);
   
   TH1D* hTemp = (TH1D*)href->Clone("hTemp");  
   hTemp->SetAxisRange(-.05,.5,"Y");
   hTemp->SetTitleOffset(1.5,"Y");
   for ( int i=0 ; i<=hTemp->GetNbinsX();i++) hTemp->SetBinContent(i,-1000000000);
   TH1D* hFluc = (TH1D*)huBound->Clone("hFluc");
   hFluc->Add(href,-1);
   
   
   if ( drawDiff ) {
      href->Reset();
      href->SetLineStyle(9);
      hTemp->SetAxisRange(-0.049,0.049,"Y");
   }
   
   hTemp->DrawCopy();
   
 
   drawSysAbs(href,hFluc);
   href->DrawCopy("same");
   if ( !drawDiff)
      hBkg->DrawCopy("same");
   

   if ( icent == 1) {
      TLegend *t3= new TLegend(0.2998319,0.6098612,0.779229,0.8149715,NULL,"brNDC");
      easyLeg(t3,"PbPb");
      if (!drawDiff) {
	 t3->AddEntry(hsm,"Central value","pl");
	 t3->AddEntry(hBkg,"#sigma_{#eta#eta} sideband","p");
      }
      else {
	 t3= new TLegend(0.0998319,0.7098612,1.0079229,0.96149715,NULL,"brNDC");
	 easyLeg(t3,"Systematic Uncertainty");
      }
      t3->Draw();

   }
   
}
