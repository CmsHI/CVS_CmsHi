#include <iostream>
#include "TFile.h"
#include "TCanvas.h"

#include "HisCompare.h"

void compareHisDPhi()
{
   TFile * infside = new TFile("fig/02.13_dphiVal_side/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_Isol0_Norm0.root");
   TFile * infmix = new TFile("fig/02.13_phobkg/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_Isol0_Norm0.root");
   
//   HisCompare hcRawBkg("RawBkg",";|#Delta#phi|;",0,3.1415926,0);
//   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0SignalAllExtrapExtrapNorm"),"Raw","hist",kBlack,kFullCircle,"l",2);
//   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0BkgDPhiExtrapExtrapNorm"),"#Delta#phi Bkg","E",kGreen+2,kOpenCircle,"p");
//   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0BkgSShapeExtrapExtrapNorm"),"#Delta#phi Bkg","E",kViolet,kOpenCircle,"p");
//   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Subtracted","E",kRed,kFullCircle,"p");
//
//   TCanvas * c2 = new TCanvas("c2","c2",500,500);
//   hcRawBkg.Draw(-40,400);
//   hcRawBkg.DrawLeg("Sideband #Delta#phi Bkg",0.25,0.71,0.63,0.87);
//   c2->Print("fig/his/dphi_Isol0_cent0_side.gif");

   
   HisCompare hcRawBkgMix("RawBkgMix",";|#Delta#phi|;",0,3.1415926,0);
   hcRawBkgMix.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0SignalAllExtrapExtrapNorm"),"Raw","hist",kBlack,kFullCircle,"l",2);
   hcRawBkgMix.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0BkgDPhiExtrapExtrapNorm"),"#Delta#phi Bkg","E",kGreen+2,kOpenCircle,"p");
   hcRawBkgMix.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0BkgSShapeExtrapExtrapNorm"),"#gamma Bkg","E",kViolet,kOpenCircle,"p");
   hcRawBkgMix.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Subtracted","E",kRed,kFullCircle,"p");
   
   TCanvas * c3 = new TCanvas("c3","c3",500,500);
   hcRawBkgMix.Draw(-40,400);
   hcRawBkgMix.DrawLeg("Mixed #Delta#phi Bkg",0.25,0.71,0.63,0.87);
   c3->Print("fig/his/dphi_Isol0_cent0_mix.gif");
//
//   HisCompare hcRawBkg2Meth("RawBkg2Meth",";|#Delta#phi|;",0,3.1415926,0);
//   hcRawBkg2Meth.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Sideband #Delta#phi Bkg","E",kRed,kFullCircle,"p");
//   hcRawBkg2Meth.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Mixed #Delta#phi Bkg","E",kRed,kOpenCircle,"p");
//   TCanvas * c4 = new TCanvas("c4","c4",500,500);
//   hcRawBkg2Meth.Draw(-40,400);
//   hcRawBkg2Meth.DrawLeg("Subtracted",0.25,0.71,0.63,0.87);
//   c4->Print("fig/his/dphi_Isol0_cent0_side_vs_mix.gif");
}
