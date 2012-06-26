#include <TROOT.h>
#include <TFile.h>
#include "TH1.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TLegend.h"
//#include "TString.h"


void L1Emul_macro()
{
  //TH1::SetDefaultSumw2();
  TFile *file[2];
  TTree *HltTree[2];
   
  file[0] = new TFile("/net/hidsk0001/d00/scratch/luck/data/HiForest.root");
  HltTree[0] = (TTree*)file[0]->Get("hltanalysis/HltTree");
  HltTree[0]->AddFriend("t=icPu5JetAnalyzer/t","/net/hidsk0001/d00/scratch/luck/data/HiForest.root");

  file[1] = new TFile("/net/hisrv0001/home/icali/hadoop/HIMinBiasUPC_skimmed/MinBias-reTracking-merged/MinBias_Merged_tracking_v4.root");
  HltTree[1] = (TTree*)file[1]->Get("hltanalysis/HltTree");
  HltTree[1]->AddFriend("t=icPu5JetAnalyzer/t","/net/hisrv0001/home/icali/hadoop/HIMinBiasUPC_skimmed/MinBias-reTracking-merged/MinBias_Merged_tracking_v4.root");

  TString L1_SingleJet = "L1_SingleJet";
  TString thresholds[] = {"16", "36_BptxAND", "52_BptxAND",
			  "68_BptxAND", "80_BptxAND", "92_BptxAND",
			  "128_BptxAND"};
  int thresholdi[] = {16, 36, 52, 68, 80, 92, 128};


  
  // TH1D *hist_bottom = new TH1D("hist_bottom","Denominator", 30, 0, 120);
  // HltTree->Project("hist_bottom","t.jtpt[0]");

  // for(int i = 0; i < 6; i++)
  // {  
  //   TH1D *hist = new TH1D(L1_SingleJet+thresholds[i],
  // 			  L1_SingleJet+thresholds[i],
  // 			  30, 0, 120);
  //   HltTree->Project(L1_SingleJet+thresholds[i],
  // 		     "t.jtpt[0]",
  // 		     L1_SingleJet+thresholds[i]);
  //   hist->Divide(hist, hist_bottom, 1, 1, "b");
  //   TCanvas *co = new TCanvas();
  //   hist->GetYaxis()->SetRangeUser(0,1);
  //   hist->Draw("p,E");
  // }


  Double_t xbins[9] = {-2,2,30,42,62,74,86,98,158};
  TH1D *efficiency_curve[2];
  efficiency_curve[0] = new TH1D("efficiency_curve","Efficiency",
				    8,xbins);
  efficiency_curve[1] = new TH1D("efficiency_curve","Efficiency",
				    8,xbins);
  for(int i = 0; i < 2; i++)
  {
    efficiency_curve[i]->SetXTitle("L1 Jet Trigger Threshold");
    efficiency_curve[i]->SetYTitle("Fraction of Passing Events");
    efficiency_curve[i]->Fill(0.,1.);

    for(int j = 0; j < 7; j++)
    {
      TH1D *hist = new TH1D(L1_SingleJet+thresholds[j],
			    L1_SingleJet+thresholds[j],
			    2, -0.5, 1.5);
      HltTree[i]->Project(L1_SingleJet+thresholds[j],
			  L1_SingleJet+thresholds[j]);

      efficiency_curve[i]->Fill(thresholdi[j],hist->GetBinContent(2)/hist->GetEntries());
    }
    efficiency_curve[i]->GetYaxis()->SetRangeUser(0,1);
    efficiency_curve[i]->GetXaxis()->SetRangeUser(0,130);
  }
  

  TCanvas *c0 = new TCanvas();
  efficiency_curve[0]->SetLineColor(kRed);
  efficiency_curve[1]->SetLineColor(kBlue);
  efficiency_curve[0]->Draw("L");
  efficiency_curve[1]->Draw("L,same");

  TLegend *leg = new TLegend(0.5,0.5,0.8,0.7);
  leg->SetFillColor(0);
  leg->AddEntry(efficiency_curve[0],"Phi-Ring Subtraction at L1, minbias","l");
  leg->AddEntry(efficiency_curve[1],"Current L1 System, minbias","l");
  leg->Draw();
 
  c0->Update();

}
