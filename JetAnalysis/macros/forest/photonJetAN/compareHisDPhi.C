#include <iostream>
#include "TFile.h"
#include "TCanvas.h"

#include "HisCompare.h"

void compareHisDPhi()
{
   TFile * infpaper = new TFile("fig/02.10_dphiFix/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig700_Isol0_Norm1.root");
   TFile * infside = new TFile("fig/02.14_phoscale_side/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_Isol0_Norm0.root");
   TFile * infmix0213 = new TFile("fig/02.13_phobkg/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_Isol0_Norm0.root");
   TFile * infmix = new TFile("fig/02.14_phoscale_mix/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_Isol0_Norm0.root");
   TFile * infmix_subJ0SS1 = new TFile("fig/02.14_phoscale_mix/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_subJ0SS1_Isol0_Norm0.root");
   TFile * infmix_subJ1SS0 = new TFile("fig/02.14_phoscale_mix/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_subJ1SS0_Isol0_Norm0.root");
   TFile * infmixep = new TFile("fig/02.15_updatedES/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_subJ1SS1_Isol0_Norm0.root");
//   TFile * infmix_ys = new TFile("yongsun/gammaJetOutputsYongsun.root");
   TFile * infmix_ys = new TFile("yongsun/gammaJetOutputsYongsun40mixing.root");
   TFile * infmixfin = new TFile("fig/02.15_preapproval/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma60jet30dphiSig628_subJ1SS1_Isol0_Norm0.root");
   
//   HisCompare hcRawBkg("RawBkg",";|#Delta#phi|;",0,3.1415926,0);
//   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0SignalAllExtrapExtrapNorm"),"Raw","hist",kBlack,kFullCircle,"l",2);
//   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0BkgDPhiExtrapExtrapNorm"),"#Delta#phi Bkg","E",kGreen+2,kOpenCircle,"p");
//   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0BkgSShapeExtrapExtrapNorm"),"#Delta#phi Bkg","E",kViolet,kOpenCircle,"p");
//   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Subtracted","E",kRed,kFullCircle,"p");
//
//   TCanvas * c2 = new TCanvas("c2","c2",500,500);
//   hcRawBkg.Draw(-40,400);
//   hcRawBkg.DrawLeg("Sideband #Delta#phi Bkg",0.25,0.71,0.63,0.87);
////   c2->Print("fig/his/dphi_Isol0_cent0_side.gif");
//
//   
//   HisCompare hcRawBkgMix("RawBkgMix",";|#Delta#phi|;",0,3.1415926,0);
//   hcRawBkgMix.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0SignalAllExtrapExtrapNorm"),"Raw","hist",kBlack,kFullCircle,"l",2);
//   hcRawBkgMix.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0BkgDPhiExtrapExtrapNorm"),"#Delta#phi Bkg","E",kGreen+2,kOpenCircle,"p");
//   hcRawBkgMix.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0BkgSShapeExtrapExtrapNorm"),"#gamma Bkg","E",kViolet,kOpenCircle,"p");
//   hcRawBkgMix.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Subtracted","E",kRed,kFullCircle,"p");
//   
//   TCanvas * c3 = new TCanvas("c3","c3",500,500);
//   hcRawBkgMix.Draw(-40,400);
//   hcRawBkgMix.DrawLeg("Mixed #Delta#phi Bkg",0.25,0.71,0.63,0.87);
////   c3->Print("fig/his/dphi_Isol0_cent0_mix.gif");
//
//   HisCompare hcRawBkg2Meth("RawBkg2Meth",";|#Delta#phi|;",0,3.1415926,0);
//   hcRawBkg2Meth.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Sideband #Delta#phi Bkg","E",kRed,kFullCircle,"p");
//   hcRawBkg2Meth.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Mixed #Delta#phi Bkg","E",kRed,kOpenCircle,"p");
//   TCanvas * c4 = new TCanvas("c4","c4",500,500);
//   hcRawBkg2Meth.Draw(-40,400);
//   hcRawBkg2Meth.DrawLeg("Subtracted",0.25,0.71,0.63,0.87);
////   c4->Print("fig/his/dphi_Isol0_cent0_side_vs_mix.gif");

   // compare with yongsun
   HisCompare hcRawBkgYS("RawBkgYS",";|#Delta#phi|; # #gamma-Jet Pairs",0,3.1415926,0);
//   HisCompare hcRawBkgYS("RawBkgYS",";|#Delta#phi|; # Bkg Jet per Photon",0,3.1415926,0);
//   hcRawBkgYS.AddHist((TH1D*)infpaper->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Paper 02/10","E",kBlack,kOpenSquare,"p");
//   HisCompare hcRawBkgYS("RawBkgYS",";|#Delta#phi|;#gamma-Jet pair fraction",0,3.1415926,0);
//   hcRawBkgYS.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0SignalAllExtrapExtrapNorm"),"Frank","E",kRed,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmixep->Get("dataSrc1_reco1_cent0BkgDPhiExtrapExtrapNorm"),"Frank","E",kRed,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0BkgSShapeExtrapExtrapNorm"),"Frank","E",kRed,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix_subJ0SS1->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Frank","E",kRed,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix_subJ1SS0->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Frank","E",kRed,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Frank","E",kRed,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmixfin->Get("dataSrc1_reco1_cent0BkgDPhiExtrapExtrapNorm"),"Frank Mix 02/16","E",kRed,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmixep->Get("dataSrc1_reco1_cent0BkgDPhiExtrapExtrapNorm"),"Mix EP","E",kBlue,kOpenStar,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix_ys->Get("data_icent1_jetDphi"),"Yongsun","E",kBlue,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix_ys->Get("data_icent1_jetDphiPureJNIpho"),"Yongsun","E",kBlue,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix_ys->Get("data_icent1_jetDphiPureJ"),"Yongsun","E",kBlue,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix_ys->Get("data_icent1_jetDphiPureJPurePho"),"Yongsun Mix 02/16","E",kBlue,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix_ys->Get("data_icent1_jetDphiPurePho"),"Yongsun","E",kBlue,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix_ys->Get("data_icent1_jetDphiPureJ"),"Yongsun","E",kBlue,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix_ys->Get("data_icent1_jetDphiMix"),"Yongsun Mix 02/16","E",kBlue,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmix0213->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Mixed Evt. Bkg","E",kBlue,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"In Paper","E",kBlack,kOpenCircle,"p");
//   hcRawBkgYS.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Frankside","E",kBlack,kOpenSquare,"p");
//   hcRawBkgYS.AddHist((TH1D*)infmixfin->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Updated #gamma Energy Scale","E",kRed,kFullCircle,"p");
   hcRawBkgYS.AddHist((TH1D*)infmixfin->Get("dataSrc1_reco1_cent0SignalAllExtrapExtrapNorm"),"Raw Signal","hist",kBlack,0,"l",2);
   hcRawBkgYS.AddHist((TH1D*)infmixfin->Get("dataSrc1_reco1_cent0BkgDPhiExtrapExtrapNorm"),"Jet Bkg","E",kGreen+2,kOpenCircle,"p");
   hcRawBkgYS.AddHist((TH1D*)infmixfin->Get("dataSrc1_reco1_cent0BkgSShapeExtrapExtrapNorm"),"Photon Bkg","E",kViolet,kOpenCircle,"p");
   hcRawBkgYS.AddHist((TH1D*)infmixfin->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Fully Subtracted","E",kRed,kFullCircle,"p");
//   hcRawBkgYS.vh[0]->Scale(1./813);
//   hcRawBkgYS.vh[0]->Scale(1./hcRawBkgYS.vh[0]->Integral(7,20));
//   hcRawBkgYS.vh[1]->Scale(1./hcRawBkgYS.vh[1]->Integral(7,20));
//   hcRawBkgYS.vh[2]->Scale(1./hcRawBkgYS.vh[2]->Integral(7,20));
   TCanvas * c5 = new TCanvas("c5","c5",500,500);
//   hcRawBkgYS.Draw(-0.1,0.6);
//   hcRawBkgYS.Draw(-0.1,0.15);
   hcRawBkgYS.Draw(-30,430);
   hcRawBkgYS.DrawLeg("0-10%",0.25,0.71,0.63,0.87);
//   hcRawBkgYS.DrawLeg("Jet Bkg 0-10%",0.25,0.71,0.63,0.87);
//   c5->Print("fig/his/dphi_Isol0_cent0_mix_bkg_yongsun_vs_frank_0216.gif");
//   c5->Print("fig/his/dphi_Isol0_cent0_mix_SubAll_yongsun_vs_frank_0216.gif");
//   c5->Print("fig/his/dphi_cent0_mix_SubAll_Changes_since_Paper.gif");
   c5->Print("fig/his/dphi_cent0_mix_SubSteps_illustration.gif");
   c5->Print("fig/his/dphi_cent0_mix_SubSteps_illustration.pdf");
}
