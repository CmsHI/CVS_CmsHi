#include "TH1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLine.h"
//#include <sstream>
#include "TString.h"

#include "RecHitsTree_jets.h"
#include "RecHitsTree_jets.C"


void RecHitsTree_macro1(int total_events = -1)
{  
  //int total_events = -1;
  RecHitsTree_jets *minbias = new RecHitsTree_jets();
  
  TCanvas* plot;
 
  bool algo[2];
  
  TH1D* h_towers[2];
  TH1D* h_regions[2];

  TLegend* leg;

  //h_towers[0] = (TH1D*)minbias->Loop(total_events, RecHitsTree_jets::TOWER_EFF, algo[0], false)->Clone();
  h_towers[1] = (TH1D*)minbias->Loop(total_events,
				     RecHitsTree_jets::TOWER_EFF,
				     true,
				     false,
				     false)->Clone();
  h_regions[0] = (TH1D*)minbias->Loop(total_events,
				      RecHitsTree_jets::REGION_EFF,
				      false,
				      false,
				      false)->Clone();
  h_regions[1] = (TH1D*)minbias->Loop(total_events,
				      RecHitsTree_jets::REGION_EFF,
				      true,
				      false,
				      false)->Clone();

  plot = new TCanvas();

  /******************************************************/
  // TLine *fivep_l[2];
  // for(int i = 0; i < 2; i++)
  // {
  //   double bin_contents;
  //   double fivep_p;
  //   int nbins = h_min[i]->GetNbinsX();
  //   double hist_max = h_min[i]->GetXaxis()->GetXmax();
  //   for(int j = 1; j < nbins; j++)
  //   {
  //     bin_contents = h_min[i]->GetBinContent(j);
  //     if(bin_contents <= 0.05)
  //     {
  //   	fivep_p = (double)j*hist_max/(double)nbins;
  //   	break;
  //     }
  //   }

  //   fivep_l[i] = new TLine(fivep_p, 0, fivep_p, 1);
  //   fivep_l[i]->SetLineWidth(3);
  //   fivep_l[i]->SetLineStyle(3);

  //   cout << "five_p " << fivep_p << endl;
  // }
  /***********************************************************/
  
  h_regions[0]->SetTitle("RecHit Tower Jets");
  h_regions[0]->SetXTitle("L1 Threshold (GeV)");
  h_regions[0]->SetYTitle("L1 Accept Fraction");
  h_regions[0]->Draw("L");
  // h_towers[0]->SetLineColor(kRed);
  // h_towers[0]->Draw("L");

  h_regions[1]->SetLineColor(kBlue);
  h_regions[1]->Draw("L,same");


  h_towers[1]->SetLineColor(kRed);
  h_towers[1]->Draw("L,same");
  // h_regions[0]->SetLineColor(kRed);


 

  // fivep_l[0]->SetLineColor(kRed);
  // fivep_l[0]->Draw("same");
  // fivep_l[1]->SetLineColor(kBlue);
  // fivep_l[1]->Draw("same");

  leg = new TLegend(0.4,0.5,0.7,0.8);

  leg->SetFillColor(0);

  //leg->AddEntry(h_towers[0],"nosub towers","l");
  leg->AddEntry(h_regions[0],"Current L1 trigger","l");
  leg->AddEntry(h_regions[1],"2015 intermediate trigger","l");
  leg->AddEntry(h_towers[1],"SLHC trigger","l");

  // leg->AddEntry(h_min[2],"Tower Level Phi-Ring Subtraction","l");
  // leg->AddEntry(fivep_l[0],"Current System 5%","l");
  // leg->AddEntry(fivep_l[1],"Phi-Ring Subtraction 5%","l");
  // leg->AddEntry(fivep_l[2],"Tower-LevelPhi-Ring Subtraction 5%","l");

  leg->Draw();
 
  plot->Update();

  plot->SaveAs("efficiency_comparison_rechits.C");
  plot->SaveAs("efficiency_comparison_rechits.gif");
}  

