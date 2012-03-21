#include <iostream>
#include <vector>
#include "TFile.h"
#include "TCanvas.h"

#include "commonUtility.h"
#include "npart.h"
#include "HisCompare.h"
#include "HisPhotonJet.h"
using namespace std;

void plotHisDPhi_All4Cent()
{
   const int nBin = 4;
   float m[nBin+1] = {0,4,12,20,40};
//   const int nBin = 1;
//   float m[nBin+1] = {0,40};

   vector<HisCompare*> vc;
   vector<TString> names;
   vector<TFile*> infiles;
   TString infname_x0320="fig/03.20_approval/HisOutput_Photonv7_v29_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_Isol0_Norm0.root";
   TString infname_x0320_fisher="fig/03.20_approval/HisOutput_Photonv7_v29_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_Isol2_Norm0.root";

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
      vc.push_back(new HisCompare(Form("x_c%d",ib),";#Delta#phi_{J#gamma};Pair Fraction",0,3.1415926,1));
      for (int s=0; s<names.size(); ++s) {
         if (s==0) vc[ib]->AddHist(vh[s][ib],"Paper v9","E",kRed,kFullCircle,"p");
         if (s==1) vc[ib]->AddHist(vh[s][ib],"Fisher Isol.","E",kBlack,kOpenCircle,"p"),2;
      }
   }
   
   

   TCanvas *c1 = new TCanvas("c1dphi","",1100,330);
   makeMultiPanelCanvas(c1,4,1,0.0,0.0,0.2,0.18,0.02);
   float ymin=1.e-3, ymax=1;
   //c1->Divide(4,1);

   // first draw
   for (int ib=0; ib<nBin; ++ib) {
      c1->cd(nBin-ib);
      gPad->SetLogy();
      vc[ib]->Draw(ymin,ymax);
   }
   // labels
   c1->cd(4);
   for (int ib=0; ib<nBin; ++ib) {
      c1->cd(nBin-ib);
      if ( ib == 3) {
         drawText(Form("%.0f%% - %.0f%%",m[ib]*2.5,m[ib+1]*2.5),0.25,0.6,1,16);
         vc[0]->DrawLeg("PbPb Data",0.21,0.76,0.68,0.98);
      } else drawText(Form("%.0f%% - %.0f%%",m[ib]*2.5,m[ib+1]*2.5),0.1,0.6,1,16);
      if ( ib == 2) {
         drawText("#sqrt{s_{NN}}=2.76TeV ",0.4,0.88,0,15);
         drawText("#int L dt = 150 #mub^{-1}",0.4,0.75,0,15);
      }
      if ( ib == 1) {
         drawText(Form("p^{#gamma}_{T} > %dGeV/c     |#eta^{#gamma}| < 1.44",60),0.15,0.9,0,15);
         drawText(Form("p^{Jet}_{T} > %dGeV/c    |#eta^{Jet}| < 1.6",30),0.15,0.8,0,15);
      }
      if ( ib == 0 ) {
         drawText("CMS",0.8,0.9,1);
      }
   }
   c1->Print("fig/his/HisDeltaPhi_All4Cent_data_sumIsol_vs_fisherIsol.gif");
   
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
   hNpartFrame->SetYTitle("#sigma(#Delta#phi_{J#gamma})");
   hNpartFrame->SetAxisRange(0,0.5,"Y");
   handsomeTH1(hNpartFrame);
   hNpartFrame->Draw();
   for (int s=0; s<names.size(); ++s) {
      TGraphAsymmErrors * gSummary = getSummary(nBin,npart,vh[s],1,1,1);
      gSummary->SetMarkerColor(vc[0]->vh[s]->GetMarkerColor());
      gSummary->SetMarkerStyle(vc[0]->vh[s]->GetMarkerStyle());
      gSummary->SetLineColor(vc[0]->vh[s]->GetMarkerColor());
      gSummary->SetLineStyle(vc[0]->vh[s]->GetLineStyle());
      gSummary->Draw("psame");
      gSummary->Write();
   }
   vc[0]->DrawLeg("PbPb Data",0.45,0.71,0.92,0.93);
   fout->Write();
   
   c3->Print("fig/his/HisDeltaPhi_Summary_data_sumIsol_vs_fisherIsol.gif");
}
