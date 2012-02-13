#include <iostream>
#include "TFile.h"
#include "TCanvas.h"

#include "HisCompare.h"
#include "HisPhotonJet.h"

void compareHisPtRatio()
{
   //TString infname="fig/02.13_paperAllHists/HisOutput_Photonv7_v24_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm1.root";
   TString infname="fig/02.13_paperAllHists/HisOutput_Photonv7_v24_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm0.root";
   TFile * infside = new TFile(infname);
   
   TString outfname(infname);
   outfname.ReplaceAll("HisOutput_","HisPaper_");
   cout << outfname << endl;
   //TFile* hout = new TFile(outfname,"RECREATE");
   
   HisCompare hcRawBkg("RawBkg",";x;",0,2);
   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0SignalAllExtrapExtrapNorm"),"Raw","hist",kBlack,kFullCircle,"l",2);
   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0BkgDPhiExtrapExtrapNorm"),"#Delta#phi Bkg","E",kGreen+2,kOpenCircle,"p");
   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0BkgSShapeExtrapExtrapNorm"),"#gamma Bkg","E",kViolet,kOpenCircle,"p");
   hcRawBkg.AddHist((TH1D*)infside->Get("dataSrc1_reco1_cent0SubtractedExtrapExtrapNorm"),"Subtracted","E",kRed,kFullCircle,"p");

   TCanvas * c2 = new TCanvas("c2","c2",500,500);
   //hcRawBkg.Draw(-0.02,0.5);
   hcRawBkg.Draw();
   hcRawBkg.DrawLeg("0-10\%",0.64,0.72,0.94,0.91);
   //c2->Print("fig/his/dphi_Isol0_cent0_side.gif");
}
