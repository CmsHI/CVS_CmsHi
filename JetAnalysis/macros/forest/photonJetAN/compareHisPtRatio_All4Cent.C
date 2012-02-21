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
   GetNPartBins("../output-data-Photon-v7-noDuplicate_v26_akPu3PF.root", nBin, npart, m, 60,1);
   cout << "got npart" << endl;

   TString infname="fig/02.15_preapproval/HisOutput_Photonv7_v24_akPu3PF_InclPtRatio_gamma60jet30dphiSig2749_Isol0_Norm0.root";
   TFile * infside = new TFile(infname);
   
   TString outfname(infname);
   outfname.ReplaceAll("HisOutput_","HisPaper_");
   cout << outfname << endl;
   //TFile* hout = new TFile(outfname,"RECREATE");
   TString outtag(infname);
   outtag.ReplaceAll(".root","");
   
   vector<TH1D*> vhnorm;
   for (int ib=0; ib<nBin; ++ib) {
//      TString hname=Form("dataSrc1_reco1_cent%dSignalAllPho",ib);
      TString hname=Form("dataSrc0_reco1_cent%dSignalAllPho",ib);
      cout << hname;
      vhnorm.push_back((TH1D*)infside->Get(hname));
      cout << "norm: " << 1./vhnorm[ib]->Integral();
   }
   vector<HisCompare*> vc;
   vector<TString> steps;
   steps.push_back("SignalAll");
   steps.push_back("BkgDPhi");
   steps.push_back("BkgSShape");
   steps.push_back("BkgSShapeDPhi");
   steps.push_back("Subtracted");
   vector<vector<TH1D*> >vh(steps.size());
   for (int s=0; s<steps.size(); ++s) {
      cout << steps[s] << endl;
      for (int ib=0; ib<nBin; ++ib) {
//         TString hname=Form("dataSrc1_reco1_cent%d%sExtrapExtrapNorm",ib,steps[s].Data());
         TString hname=Form("dataSrc0_reco1_cent%d%sExtrapExtrapNorm",ib,steps[s].Data());
         cout << hname;
         vh[s].push_back((TH1D*)infside->Get(hname));
//         vh[s][ib]->Scale(1./vhnorm[ib]->Integral());
         cout << " mean: " << vh[s][ib]->GetMean() << endl;
      }
   }

   for (int ib=0; ib<nBin; ++ib) {
      vc.push_back(new HisCompare(Form("ptratio_%d",ib),";x_{J#gamma}; Pair Fraction",0,2,1));
      vc[ib]->AddHist(vh[steps.size()-1][ib],"Subtracted","E",kRed,kFullCircle,"p");
//      vc.push_back(new HisCompare(Form("dphi_%d",ib),";x_{J#gamma};# #gamma-Jet Pairs",0,2));
//      vc.push_back(new HisCompare(Form("dphi_%d",ib),";x_{J#gamma};# #gamma-Jet Pairs (weighted)",0,2));
//      vc[ib]->AddHist(vh[0][ib],"Raw","hist",kBlack,0,"l",2);
      vc[ib]->AddHist(vh[1][ib],"Jet bkg","E",kGreen+2,kOpenCircle,"p");
//      vc[ib]->AddHist(vh[2][ib],"#gamma bkg","E",kViolet,kOpenCircle,"p");
   }
   
   

   TCanvas *c1 = new TCanvas("c1","",1000,300);
   makeMultiPanelCanvas(c1,4,1,0.0,0.0,0.2,0.2,0.02);
   float ymin=-0.02,ymax=0.5;
//   float ymin=-50,ymax=200;
//   float ymin=-0.002,ymax=0.03;
//   float ymin=0,ymax=4000;
   //c1->Divide(4,1);
   c1->cd(1);
   vc[3]->Draw(ymin,ymax);
   drawText("50-100\%",0.3,0.85);
   vc[3]->DrawLeg("PYTHIA+HYDJET",0.63,0.65,0.95,0.88);
//   vc[3]->DrawLeg("PbPb Data",0.63,0.65,0.95,0.88);
   c1->cd(2);
   vc[2]->Draw(ymin,ymax);
   drawText("30-50\%",0.2,0.85);
   c1->cd(3);
   vc[1]->Draw(ymin,ymax);
   drawText("10-30\%",0.2,0.85);
   c1->cd(4);
   vc[0]->Draw(ymin,ymax);
   drawText("0-10\%",0.2,0.85);
   
//   c1->Print("fig/his/ptratio_BkgSShape_data.gif");
//   c1->Print("fig/his/ptratio_BkgSShape_data.pdf");
//   c1->Print("fig/his/ptratio_BkgJet_data.gif");
//   c1->Print("fig/his/ptratio_BkgJet_data.pdf");

   TCanvas *c2 = new TCanvas("c2","",500,500);
   ymin=-0.02; ymax=0.3;
   HisCompare hAllCent("ptratio_allcent",";x_{J#gamma}; Pair Fraction",0,2,1);
   hAllCent.AddHist(vh[steps.size()-1][0],"0-10%","E",kRed,kOpenCircle,"p");
   hAllCent.AddHist(vh[steps.size()-1][1],"10-30%","E",kGreen+2,kOpenCircle,"p");
   hAllCent.AddHist(vh[steps.size()-1][2],"30-50%","E",kBlue,kOpenCircle,"p");
   hAllCent.AddHist(vh[steps.size()-1][3],"50-100%","E",kBlack,kOpenCircle,"p");
   hAllCent.Draw(ymin,ymax);
   hAllCent.DrawLeg("PYTHIA+HYDJET",0.60,0.71,0.95,0.92);
   c2->Print("fig/his/ptratio_subAll_AllCent_mc.gif");
   c2->Print("fig/his/ptratio_subAll_AllCent_mc.pdf");
}
