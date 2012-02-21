#include <iostream>
#include "TFile.h"
#include "TCanvas.h"

#include "HisCompare.h"

void compareHisPtRatio()
{
   TFile * infpaper = new TFile("fig/02.08_paper/HisOutput_Photonv7_v24_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm1.root");
   TFile * infmix0213 = new TFile("fig/02.13_phobkg/HisOutput_Photonv7_v24_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm0.root");
   TFile * infmixfin = new TFile("fig/02.15_preapproval/HisOutput_Photonv7_v24_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm1.root");
   
   HisCompare hcRawBkgYS("RawBkgYS",";x_{J#gamma} = p_{T}^{J}/p_{T}^{#gamma}; #gamma-Jet Pair Fraction",0,2,0);
   hcRawBkgYS.AddHist((TH1D*)infpaper->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Paper 02/10","E",kBlack,kOpenSquare,"p");
   hcRawBkgYS.AddHist((TH1D*)infmix0213->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Mixed Evt. Bkg","E",kBlue,kOpenCircle,"p");
   hcRawBkgYS.AddHist((TH1D*)infmixfin->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Updated #gamma Energy Scale","E",kRed,kFullCircle,"p");
   hcRawBkgYS.vh[0]->Scale(1./hcRawBkgYS.vh[0]->Integral());
   hcRawBkgYS.vh[1]->Scale(1./hcRawBkgYS.vh[1]->Integral());
   hcRawBkgYS.vh[2]->Scale(1./hcRawBkgYS.vh[2]->Integral());
   TCanvas * c5 = new TCanvas("c5","c5",500,500);
   hcRawBkgYS.Draw(-0.02,0.37);
   hcRawBkgYS.DrawLeg("0-10%",0.45,0.76,0.83,0.92);
   c5->Print("fig/his/ptratio_cent0_mix_SubAll_Changes_since_Paper.gif");
}
