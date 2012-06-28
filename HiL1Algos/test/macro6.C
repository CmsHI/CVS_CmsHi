#include "TH1.h"
#include "TriggerPrimitivesTree_tower.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLine.h"
//#include <sstream>
#include "TString.h"

using namespace std;

void macro6()
{
  int total_events = 5000;
  TriggerPrimitivesTree_tower *min =
    new TriggerPrimitivesTree_tower(new TFile("prod/HiForest.root"));
  // TriggerPrimitivesTree_tower *jet =
  //   new TriggerPrimitivesTree_tower(new TFile("jet.root"));
  
  TCanvas* plot;
 
  bool phi_subtract[] = {false, true};
  
  TH1D* h_min[2];
  // TH1D* h_jet[2];

  // TLegend* leg;

  TString title = "High Pt Tracks Rate vs. Threshold";

  h_min[0] = (TH1D*)min->Loop(total_events, 0, phi_subtract[0], false)->Clone();
  // h_min[1] = (TH1D*)min->Loop(total_events, 0, phi_subtract[1], false)->Clone();

  // h_jet[0] = (TH1D*)jet->Loop(total_events, 0, phi_subtract[0], true)->Clone();
  // h_jet[1] = (TH1D*)jet->Loop(total_events, 0, phi_subtract[1], true)->Clone();

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
  //h_min[0]->SetLineColor(kRed);
  h_min[0]->SetTitle(title);
  h_min[0]->Draw("L");

  // h_min[1]->SetLineColor(kBlue);
  // h_min[1]->Draw("L,same");

  // h_jet[0]->Draw("L,same");
  // h_jet[1]->SetLineColor(kGreen);
  // h_jet[1]->Draw("L,same");

  // fivep_l[0]->SetLineColor(kRed);
  // fivep_l[0]->Draw("same");
  
  // fivep_l[1]->SetLineColor(kBlue);
  // fivep_l[1]->Draw("same");  

  // leg = new TLegend(0.5,0.5,0.8,0.7);

  // leg->SetFillColor(0);

  // leg->AddEntry(h_min[0],"Current L1 System","l");
  // leg->AddEntry(h_min[1],"Phi-Ring Subtraction","l");
  // leg->AddEntry(fivep_l[0],"Current System 5%","l");
  // leg->AddEntry(fivep_l[1],"Phi-Ring Subtraction 5%","l");

  // leg->AddEntry(h_jet[0],"Current L1 System Jet","l");
  // leg->AddEntry(h_jet[1],"Phi-Ring Subtraction Jet","l");
  
  // leg->Draw();
 
  plot->Update();
}  

