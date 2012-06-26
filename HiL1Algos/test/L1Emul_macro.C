#include <TROOT.h>
#include <TFile.h>
#include "TH1.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TLegend.h"
#include <sstream>
//#include "TString.h"
#include "TriggerPrimitivesTree_alex.h"


void L1Emul_macro()
{
  //TH1::SetDefaultSumw2();
  TFile *file[2];
  TTree *HltTree[2];

  TString L1Emul_data = "/net/hidsk0001/d00/scratch/luck/data/HiForest.root";
  TString Minbias_data = "/net/hisrv0001/home/icali/hadoop/HIMinBiasUPC_skimmed/MinBias-reTracking-merged/MinBias_Merged_tracking_all.root";
   
  file[0] = new TFile(L1Emul_data);
  HltTree[0] = (TTree*)file[0]->Get("hltanalysis/HltTree");
  HltTree[0]->AddFriend("t=icPu5JetAnalyzer/t",L1Emul_data);

  file[1] = new TFile(Minbias_data);
  HltTree[1] = (TTree*)file[1]->Get("hltanalysis/HltTree");
  HltTree[1]->AddFriend("t=icPu5JetAnalyzer/t",Minbias_data);

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
  TH1D *efficiency_curve[4];
  efficiency_curve[0] = new TH1D("efficiency_curve_0","Efficiency",
				    8,xbins);
  efficiency_curve[1] = new TH1D("efficiency_curve_1","Efficiency",
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
      delete hist;
    }
    efficiency_curve[i]->GetYaxis()->SetRangeUser(0,1);
    efficiency_curve[i]->GetXaxis()->SetRangeUser(0,130);
  }

  TriggerPrimitivesTree_alex *min =
    new TriggerPrimitivesTree_alex(new TFile("minbias.root"));
  int total_events = 5000;
  TH1D *temp[2];
  temp[0] = (TH1D*)min->Loop(total_events, 0,
		     false, false)->Clone();
  temp[1] = (TH1D*)min->Loop(total_events, 0,
		     true, false)->Clone();
  for(int j = 0; j < 2; j++)
  {
    stringstream s;
    s << "efficiency_curve_" << j+2;
    efficiency_curve[j+2] = new TH1D(s.str().c_str(),"efficiency_curve",
				     temp[j]->GetNbinsX(),0,temp[j]->GetXaxis()->GetXmax());
    for(int i = 0; i < temp[j]->GetNbinsX(); i++)
    {
      efficiency_curve[j+2]->Fill(temp[j]->GetBinCenter(i), temp[j]->GetBinContent(i));
    }
  }
  

  TCanvas *c0 = new TCanvas();
  efficiency_curve[0]->SetLineColor(kRed);
  efficiency_curve[1]->SetLineColor(kBlue);
  efficiency_curve[2]->SetLineColor(40);
  efficiency_curve[3]->SetLineColor(30);
  
  efficiency_curve[0]->Draw("L");
  efficiency_curve[1]->Draw("L,same");
  efficiency_curve[2]->Draw("L,same");
  efficiency_curve[3]->Draw("L,same");

  TLegend *leg = new TLegend(0.5,0.5,0.8,0.7);
  leg->SetFillColor(0);
  leg->AddEntry(efficiency_curve[1],"Current L1 System, official","l");
  leg->AddEntry(efficiency_curve[2],"Current L1 System, ntuples","l");
  leg->AddEntry(efficiency_curve[0],"Phi-Ring Subtraction at L1, official","l");
  leg->AddEntry(efficiency_curve[3],"Phi-Ring Subtraction at L1, ntuples","l");
  leg->Draw();
 
  c0->Update();

}
