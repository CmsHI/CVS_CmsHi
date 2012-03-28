#include <iostream>
#include <vector>
#include "TFile.h"
#include "TCanvas.h"

#include "commonUtility.h"
#include "npart.h"
#include "HisCompare.h"
#include "HisPhotonJet.h"
using namespace std;

void plotHisDPhi_All4Cent_Closure()
{
   const int nBin = 4;
   float m[nBin+1] = {0,4,12,20,40};
//   const int nBin = 1;
//   float m[nBin+1] = {0,40};

   vector<HisCompare*> vc;
   vector<TString> names;
   vector<TFile*> infiles;
//   TString infname_x0320="fig/03.20_approval_pyquen/HisOutput_Photonv7_v29_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_Isol0_Norm0.root";
   TString infname_0327="fig/03.27_closure_pythia_genPhoIsol/HisOutput_Photonv7_v29_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_Isol0_Norm0.root";

   names.push_back("hyphoclos_dataSrc0_reco1"); infiles.push_back(new TFile(infname_0327));
   names.push_back("hyphoclosgenjet_dataSrc0_reco0"); infiles.push_back(new TFile(infname_0327));
   names.push_back("hyphoclosgenjetsmear_dataSrc0_reco0"); infiles.push_back(new TFile(infname_0327));
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
      vc.push_back(new HisCompare(Form("dphi_c%d",ib),";#Delta#phi_{J#gamma};Pair Fraction",0,3.1415926,1));
      for (int s=0; s<names.size(); ++s) {
         if (s==0) vc[ib]->AddHist(vh[s][ib],"RecoJet (Subtracted)","E",kBlack,kFullCircle,"p");
         if (s==1) vc[ib]->AddHist(vh[s][ib],"GenJet","E",kRed,kOpenCircle,"p");
         if (s==2) vc[ib]->AddHist(vh[s][ib],"GenJet Smear","E",kBlue,kOpenSquare,"p");
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
         vc[0]->DrawLeg("",0.21,0.76,0.68,0.98);
      } else drawText(Form("%.0f%% - %.0f%%",m[ib]*2.5,m[ib+1]*2.5),0.1,0.6,1,16);
      if ( ib == 2) drawText("PYTHIA+HYDJET",0.4,0.88,0,15);
      if ( ib == 1) {
         drawText(Form("p^{#gamma}_{T} > %dGeV/c     |#eta^{#gamma}| < 1.44",60),0.15,0.9,0,15);
         drawText(Form("p^{Jet}_{T} > %dGeV/c    |#eta^{Jet}| < 1.6",30),0.15,0.8,0,15);
      }
      if ( ib == 0 ) {
         drawText("CMS",0.8,0.9,1);
      }
   }
   c1->Print("fig/his/HisDeltaPhi_pythia_Closure_Norm1_GenJet_PhoIsol.gif");
   
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
   vc[0]->DrawLeg("",0.45,0.71,0.92,0.93);
   fout->Write();
   
   c3->Print("fig/his/HisDeltaPhi_Summary_pythia_Closure_Norm1_GenJet_PhoIsol.gif");
}
