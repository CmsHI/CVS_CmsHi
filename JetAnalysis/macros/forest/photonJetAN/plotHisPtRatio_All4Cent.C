#include <iostream>
#include <vector>
#include "TFile.h"
#include "TCanvas.h"
#include "TCut.h"
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
   TString infname_x0320=Form("fig/03.20_approval/HisOutput_Photonv7_v29_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm0.root");
   TString infname_x0320_fisher=Form("fig/03.20_approval/HisOutput_Photonv7_v29_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol2_Norm0.root");
   // Photon purity
   float PhotonPurity_sumIsol[4] = {0.74,0.77,0.79,0.83};
   float PhotonPurity_fisherIsol[4] = {0.77,0.75,0.72,0.76};
   vector<float*> PhotonPurities;
   
   
   names.push_back("hi_dataSrc1_reco1"); infiles.push_back(new TFile(infname_x0320)); PhotonPurities.push_back(PhotonPurity_sumIsol);
   names.push_back("hi_dataSrc1_reco1"); infiles.push_back(new TFile(infname_x0320_fisher)); PhotonPurities.push_back(PhotonPurity_fisherIsol);
   vector<vector<TH1D*> >vh(names.size());
   vector<vector<TH1D*> >vhnorm(names.size());
      
   for (int s=0; s<names.size(); ++s) {
      cout << "name: " << names[s] << endl;
      for (int ib=0; ib<nBin; ++ib) {
         vh[s].push_back((TH1D*)infiles[s]->Get(Form("%s_cent%dSubtractedExtrapExtrapNorm",names[s].Data(),ib)));
         if (normMode==2) {
            vhnorm[s].push_back((TH1D*)infiles[s]->Get(Form("%s_cent%dSignalAllPho",names[s].Data(),ib)));
            vhnorm[s][ib]->Scale(PhotonPurities[s][ib]);
            float nJets = vh[s][ib]->Integral();
            float nPho = vhnorm[s][ib]->Integral();
            cout << vh[s][ib]->GetName() << " # jet: " << nJets << ", " << vhnorm[s][ib]->GetName() << " # photon: " << nPho << " Purity: " << PhotonPurities[s][ib] << endl;
            vh[s][ib]->Scale(1./vhnorm[s][ib]->Integral()/vh[s][ib]->GetBinWidth(1));
            vh[s][ib]->SetEntries(nJets);
         }
      }
   }

   for (int ib=0; ib<nBin; ++ib) {
      if (normMode==0) vc.push_back(new HisCompare(Form("x_c%d",ib),";x_{J#gamma} = p^{Jet}_{T}/p^{#gamma-jet}_{T}; #frac{1}{N^{#gamma-jet}} #frac{dN^{#gamma-jet}}{dx_{J#gamma}}",0,2,2));
      if (normMode==2) vc.push_back(new HisCompare(Form("x_c%d",ib),";x_{J#gamma} = p^{Jet}_{T}/p^{#gamma-jet}_{T}; #frac{1}{N^{#gamma-jet}} #frac{dN^{#gamma-jet}}{dx_{J#gamma}}",0,2,0));
      for (int s=0; s<names.size(); ++s) {
         if (s==0) vc[ib]->AddHist(vh[s][ib],"Paper v9","E",kRed,kFullCircle,"p");
         if (s==1) vc[ib]->AddHist(vh[s][ib],"Fisher Isol.","E",kBlack,kOpenCircle,"p",2);
      }
   }
   
   

   TCanvas *c1 = new TCanvas("c1","",1100,330);
   makeMultiPanelCanvas(c1,4,1,0.0,0.0,0.23,0.21,0.02);
   float ymin=-0.2, ymax=2.5;
   //c1->Divide(4,1);

   // first draw
   for (int ib=0; ib<nBin; ++ib) {
      c1->cd(nBin-ib);
      vc[ib]->Draw(ymin,ymax);
   }
   // labels
   c1->cd(4);
   for (int ib=0; ib<nBin; ++ib) {
      c1->cd(nBin-ib);
      if ( ib == 3) {
         drawText(Form("%.0f%% - %.0f%%",m[ib]*2.5,m[ib+1]*2.5),0.72,0.5,1,16);
         vc[0]->DrawLeg("",0.61,0.76,0.95,0.98);
      } else drawText(Form("%.0f%% - %.0f%%",m[ib]*2.5,m[ib+1]*2.5),0.67,0.5,1,16);
      if ( ib == 0) {
         drawText("CMS",0.8,0.9,1);
         drawText("#sqrt{s_{NN}}=2.76TeV ",0.35,0.88,0,15);
         drawText("#int L dt = 150 #mub^{-1}",0.35,0.75,0,15);
      }
      if ( ib == 1) {
         drawText(Form("p^{#gamma}_{T} > %dGeV/c     |#eta^{#gamma}| < 1.44",60),0.2,0.9,0,15);
         drawText(Form("p^{Jet}_{T} > %dGeV/c    |#eta^{Jet}| < 1.6",30),0.2,0.8,0,15);
         drawText("#Delta#phi_{J#gamma} > #frac{7}{8}#pi",0.6,0.7,0,15);
      }
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
      gSummary->SetLineColor(vc[0]->vh[s]->GetMarkerColor());
      gSummary->SetLineStyle(vc[0]->vh[s]->GetLineStyle());
      gSummary->Draw("psame");
      gSummary->Write();
   }
   vc[0]->DrawLeg("",0.61,0.76,0.95,0.98);
   fout->Write();
   
   c3->Print(Form("fig/his/HisPtRatio_Summary_data_sumIsol_vs_fisherIsol_Norm%d.gif",normMode));
}
