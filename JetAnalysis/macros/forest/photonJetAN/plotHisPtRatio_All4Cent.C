#include <iostream>
#include <vector>
#include "TFile.h"
#include "TCanvas.h"

#include "commonUtility.h"
#include "npart.h"
#include "HisCompare.h"
#include "HisPhotonJet.h"
using namespace std;

void plotHisPtRatio_All4Cent(
                             int normMode=0 // 0=mean, 2=area
                             )
{
   const int nBin = 4;
   float m[nBin+1] = {0,4,12,20,40};
//   const int nBin = 1;
//   float m[nBin+1] = {0,40};
   
   vector<HisCompare*> vc;
   vector<TString> names;
   vector<TFile*> infiles;
//   names.push_back("hyphoquen_dataSrc0_reco1"); infiles.push_back(new TFile("fig/03.16_genjet_smear/HisOutput_Photonv7_v29_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm0.root");
//   names.push_back("hyphoquenmatjet_dataSrc0_reco1");
//   names.push_back("hyphoquengenjetsmear_dataSrc0_reco1"); infiles.push_back(new TFile("fig/03.16_genjet_smear/HisOutput_Photonv7_v29_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm0.root");
//   names.push_back("hyphoquengenjet_dataSrc0_reco1"); infiles.push_back(new TFile("fig/03.16_genjet_smear/HisOutput_Photonv7_v29_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm0.root");
   TString infname_x0320=Form("fig/03.20_approval/HisOutput_Photonv7_v29_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm%d.root",normMode);
   TString infname_x0320_fisher=Form("fig/03.20_approval/HisOutput_Photonv7_v29_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol2_Norm%d.root",normMode);

   names.push_back("hi_dataSrc1_reco1"); infiles.push_back(new TFile(infname_x0320));
   names.push_back("hi_dataSrc1_reco1"); infiles.push_back(new TFile(infname_x0320_fisher));
   vector<vector<TH1D*> >vh(names.size());

   for (int s=0; s<names.size(); ++s) {
      cout << "name: " << names[s] << endl;
      for (int ib=0; ib<nBin; ++ib) {
         TString hname=Form("%s_cent%dSubtractedExtrapExtrapNorm",names[s].Data(),ib);
         vh[s].push_back((TH1D*)infiles[s]->Get(hname));
         cout << vh[s][ib]->GetName() << endl;
      }
   }

   for (int ib=0; ib<nBin; ++ib) {
      if (normMode==0) vc.push_back(new HisCompare(Form("x_c%d",ib),";x_{J#gamma} = p^{Jet}_{T}/p^{#gamma-jet}_{T}; #frac{1}{N^{#gamma-jet}} #frac{dN^{#gamma-jet}}{dx_{J#gamma}}",0,2,2));
      if (normMode==2) vc.push_back(new HisCompare(Form("x_c%d",ib),";x_{J#gamma} = p^{Jet}_{T}/p^{#gamma-jet}_{T}; #frac{1}{N^{#gamma-jet}} #frac{dN^{#gamma-jet}}{dx_{J#gamma}}",0,2,0));
      for (int s=0; s<names.size(); ++s) {
         if (s==0) vc[ib]->AddHist(vh[s][ib],"Paper v9","E",kRed,kFullCircle,"p");
         if (s==1) vc[ib]->AddHist(vh[s][ib],"Fisher Isol.","E",kBlack,kOpenCircle,"p");
      }
   }
   
   

   TCanvas *c1 = new TCanvas("c1","",1000,300);
   makeMultiPanelCanvas(c1,4,1,0.0,0.0,0.2,0.2,0.02);
   float ymin=0, ymax=2.5;
   //c1->Divide(4,1);

   // first draw
   for (int ib=0; ib<nBin; ++ib) {
      c1->cd(nBin-ib);
      vc[ib]->Draw(ymin,ymax);
   }
   // labels
   c1->cd(4);
   vc[0]->DrawLeg("PbPb Data",0.45,0.71,0.92,0.93);
   for (int ib=0; ib<nBin; ++ib) {
      c1->cd(nBin-ib);
      if ( ib == 3) drawText(Form("%.0f%% - %.0f%%",m[ib]*2.5,m[ib+1]*2.5),0.72,0.5,1,16);
      else drawText(Form("%.0f%% - %.0f%%",m[ib]*2.5,m[ib+1]*2.5),0.67,0.5,1,16);
   }
   c1->Print(Form("fig/his/HisPtRatio_All4Cent_data_sumIsol_vs_fisherIsol_Norm%d.gif",normMode));
   
   //
   // Summary
   //
   float npart[nBin];
   GetNPartBins("../../ntout/output-data-Photon-v7-noDuplicate_v26_akPu3PF.root", nBin, npart, m, 60,1);
   cout << "got npart" << endl;

   TString outfname(infiles[0]->GetName());
   outfname.ReplaceAll("HisOutput_","HisSummary_");
   cout << "output file: " << outfname << endl;
   TFile* fout = new TFile(outfname,"RECREATE");   

   TCanvas * c3 = new TCanvas("c3","c3",500,500);
   TH1D *hNpartFrame = new TH1D("hNpartFrame","",100,-10,400);
   hNpartFrame->SetXTitle("N_{part}");
   if (normMode==0) {
      hNpartFrame->SetYTitle("<x_{J#gamma}>");
      hNpartFrame->SetAxisRange(0.6,1.1,"Y");
   }
   if (normMode==2) {
      hNpartFrame->SetYTitle("R_{J#gamma}");
      hNpartFrame->SetAxisRange(0.4,1,"Y");
   }
   handsomeTH1(hNpartFrame);
   hNpartFrame->Draw();
   for (int s=0; s<names.size(); ++s) {
      TGraphAsymmErrors * gSummary = getSummary(nBin,npart,vh[s],1,1,normMode);
      gSummary->SetMarkerColor(vc[0]->vh[s]->GetMarkerColor());
      gSummary->SetMarkerStyle(vc[0]->vh[s]->GetMarkerStyle());
      gSummary->Draw("psame");
      gSummary->Write();
   }
   vc[0]->DrawLeg("PbPb Data",0.45,0.71,0.92,0.93);
   fout->Write();
   
   c3->Print(Form("fig/his/HisPtRatio_Summary_data_sumIsol_vs_fisherIsol_Norm%d.gif",normMode));
}
