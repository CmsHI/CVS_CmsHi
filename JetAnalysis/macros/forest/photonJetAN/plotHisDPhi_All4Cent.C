#include <iostream>
#include <vector>
#include "TFile.h"
#include "TCanvas.h"

#include "commonUtility.h"
#include "npart.h"
#include "HisCompare.h"
#include "HisPhotonJet.h"
using namespace std;

void plotHisDPhi_All4Cent(
                             int dataSrcType=1, // 0=mc, 1=pbpb data, 2= pp data, 10 = pp mc
                             int dataType=1 // 0=mc gen, 1=reco
                             )
{
   const int nBin = 4;
   float m[nBin+1] = {0,4,12,20,40};
//   const int nBin = 1;
//   float m[nBin+1] = {0,40};

//   TString infname="fig/02.15_preapproval/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_subJ1SS1_Isol0_Norm0.root";
   TString infname="jet16plotsHIN_11_010/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_subJ1SS1_Isol0_Norm1.root";
   TFile * infside = new TFile(infname);
   
   vector<HisCompare*> vc;
   vector<int> dataSrcTypes;
   dataSrcTypes.push_back(0);
   dataSrcTypes.push_back(1);
   dataSrcTypes.push_back(2);
   dataSrcTypes.push_back(10);
   vector<vector<TH1D*> >vh(dataSrcTypes.size());

   for (int s=0; s<dataSrcTypes.size(); ++s) {
      cout << "datasrc: " << dataSrcTypes[s] << endl;
      for (int ib=0; ib<nBin; ++ib) {
         if (dataSrcTypes[s]>1&&ib>0) continue;
         TString hname=Form("dataSrc%d_reco1_cent%dSubtractedExtrapExtrapNorm",dataSrcTypes[s],ib);
         vh[s].push_back((TH1D*)infside->Get(hname));
         cout << vh[s][ib]->GetName() << endl;
      }
   }

   for (int ib=0; ib<nBin; ++ib) {
      for (int s=0; s<dataSrcTypes.size(); ++s) {
         if (dataSrcTypes[s]>1&&ib>0) continue;
         int mkcolor=kRed;
         int mkstyle=kFullCircle;
         if (dataSrcTypes[s]==0) {mkcolor=kBlue;mkstyle=kOpenCircle;}
         if (dataSrcTypes[s]==2) {mkcolor=kBlack;mkstyle=kOpenSquare;}
         if (dataSrcTypes[s]==10) {mkcolor=kBlue;mkstyle=kOpenSquare;}
         vc.push_back(new HisCompare(Form("dphi_%d_%d",dataSrcTypes[s],ib),";|#Delta#phi_{J#gamma}|;Pair Fraction",0,3.1415926,1));
         vc[ib]->AddHist(vh[s][ib],"Subtracted","E",mkcolor,mkstyle,"p");
      }
   }
   
   

   TCanvas *c1 = new TCanvas("c1","",1000,300);
   makeMultiPanelCanvas(c1,4,1,0.0,0.0,0.2,0.2,0.02);
   float ymin=1e-3, ymax=1;
   //c1->Divide(4,1);
   TF1 *fdphi = new TF1("fdphi","(TMath::Pi()/20.0)*exp(-(TMath::Pi()-x)/[0])/([0]*(1-exp(-TMath::Pi()/[0])))",2.0*TMath::Pi()/3.0,TMath::Pi());
   fdphi->SetParameter(0,1);
   
   // first draw
   for (int ib=0; ib<nBin; ++ib) {
      c1->cd(nBin-ib);
      gPad->SetLogy();
      vc[ib]->Draw(ymin,ymax);
   }
   
   //
   // Summary
   //
   float npart[nBin];
   GetNPartBins("../../ntout/output-data-Photon-v7-noDuplicate_v26_akPu3PF.root", nBin, npart, m, 60,1);
   cout << "got npart" << endl;

   TString outfname(infname);
   outfname.ReplaceAll("HisOutput_","HisSummary_");
   cout << "output file: " << outfname << endl;
   TFile* fout = new TFile(outfname,"RECREATE");   

   TCanvas * c3 = new TCanvas("c3","c3",500,500);
   TH1D *hNpartFrame = new TH1D("hNpartFrame","",100,-10,400);
   hNpartFrame->SetXTitle("N_{part}");
   hNpartFrame->SetYTitle("#sigma(|#Delta#phi|)");
   hNpartFrame->SetAxisRange(0,0.5,"Y");
   hNpartFrame->Draw();
   for (int s=0; s<dataSrcTypes.size(); ++s) {
      TGraphAsymmErrors * gSummary = getSummary(nBin,npart,vh[s],dataSrcTypes[s],1,1);
      if (dataSrcTypes[s]==0) {gSummary->SetMarkerColor(kBlue);gSummary->SetMarkerStyle(kOpenCircle);}
      if (dataSrcTypes[s]==1) {gSummary->SetMarkerColor(kRed);}
      if (dataSrcTypes[s]==2) {gSummary->SetMarkerColor(kRed);gSummary->SetMarkerStyle(kOpenSquare);}
      if (dataSrcTypes[s]==10) {gSummary->SetMarkerColor(kBlue);gSummary->SetMarkerStyle(kOpenSquare);}
      gSummary->Draw("psame");
      gSummary->Write();
   }
   fout->Write();
}
