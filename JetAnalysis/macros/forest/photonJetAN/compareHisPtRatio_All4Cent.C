#include <iostream>
#include <vector>
#include "TFile.h"
#include "TCanvas.h"

#include "commonUtility.h"
#include "npart.h"
#include "HisCompare.h"
#include "HisPhotonJet.h"
using namespace std;

void compareHisPtRatio_All4Cent()
{
   const int nBin = 4;
   float m[nBin+1] = {0,4,12,20,40};
   float npart[nBin];
   GetNPartBins("../output-data-Photon-v7_v24_akPu3PF.root", nBin, npart, m, 60,1);
   cout << "got npart" << endl;

   //TString infname="fig/02.13_paperAllHists/HisOutput_Photonv7_v24_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm1.root";
   TString infname="fig/02.13_phobkg/HisOutput_Photonv7_v24_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm1.root";
   TFile * infside = new TFile(infname);
   
   TString outfname(infname);
   outfname.ReplaceAll("HisOutput_","HisPaper_");
   cout << outfname << endl;
   //TFile* hout = new TFile(outfname,"RECREATE");
   TString outtag(infname);
   outtag.ReplaceAll(".root","");
   
   
   vector<TH1D*> vhsub;
   vector<TH1D*> vhbkg;
   vector<HisCompare*> vc;
   for (int ib=0; ib<nBin; ++ib) {
      cout << "cBin: " << ib << endl;
      vhsub.push_back((TH1D*)infside->Get(Form("dataSrc1_reco1_cent%dSubtractedExtrapExtrapNorm",ib)));
      cout << "subtracted mean: " << vhsub[ib]->GetMean() << endl;
      //vh.push_back((TH1D*)infside->Get(Form("dataSrc1_reco1_cent%dSignalAllExtrapExtrapNorm",ib)));
      //vh.push_back((TH1D*)infside->Get(Form("dataSrc1_reco1_cent%dBkgDPhiExtrapExtrapNorm",ib)));
      vhbkg.push_back((TH1D*)infside->Get(Form("dataSrc1_reco1_cent%dBkgSShapeExtrapExtrapNorm",ib)));
      cout << "bkg mean: " << vhbkg[ib]->GetMean() << endl;
      vc.push_back(new HisCompare(Form("ptratio_%d",ib),";x_{J#gamma} = p_{T}^{J}/p_{T}^{#gamma};#gamma-Jet Pair Fraction",0,2,1));
      vc[ib]->AddHist(vhsub[ib],"Subtracted","E",kRed,kFullCircle,"p");
      vc[ib]->AddHist(vhbkg[ib],"#gamma bkg","E",kGreen+2,kOpenCircle,"p");
   }
   
   

   TCanvas *c1 = new TCanvas("c1","",1000,300);
   makeMultiPanelCanvas(c1,4,1,0.0,0.0,0.2,0.2,0.02);
   //c1->Divide(4,1);
   c1->cd(1);
   vc[3]->Draw(-0.02,0.5);
   vc[3]->DrawLeg("50-100\%",0.64,0.72,0.94,0.91);
   c1->cd(2);
   vc[2]->Draw(-0.02,0.5);
   vc[2]->DrawLeg("30-50\%",0.64,0.72,0.94,0.91);
   c1->cd(3);
   vc[1]->Draw(-0.02,0.5);
   vc[1]->DrawLeg("10-30\%",0.64,0.72,0.94,0.91);
   c1->cd(4);
   vc[0]->Draw(-0.02,0.5);
   vc[0]->DrawLeg("0-10\%",0.64,0.72,0.94,0.91);
   c1->Print(outtag+"_PhoBkg.gif");
   c1->Print(outtag+"_PhoBkg.pdf");
}
