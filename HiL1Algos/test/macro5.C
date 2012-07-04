#include "TH1.h"
#include "TriggerPrimitivesTree_jetcurve.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"
#include <sstream>

#include "TriggerPrimitivesTree_jetcurve.C"

void macro5()
{
  TriggerPrimitivesTree_jetcurve *min =
    new TriggerPrimitivesTree_jetcurve(new TFile("minbias_v2.root"));

  bool phi_subtract;

  const int total_events = -1;
  const int current_5p_threshold = 372;
  const int improved_5p_threshold = 75;
  
  TH1D* h_min[6]; 
  //stringstream title[4];
  TCanvas *plot[3];
  TLegend *leg[3];
  stringstream title[6];
  
  int threshold;
  int minCentBin, maxCentBin;
  for(int i = 0; i < 6; i++)
  {
    switch(i)
    {
    case 0:
      title[i] << "Current L1 System, Threshold " << current_5p_threshold << " GeV";
      minCentBin = 0;
      maxCentBin = 11;
      phi_subtract = false;
      threshold = current_5p_threshold;
      break;
    case 1:
      title[i] << "Current L1 System, Threshold " << current_5p_threshold << " GeV";
      minCentBin = 20;
      maxCentBin = 40;
      phi_subtract = false;
      threshold = current_5p_threshold;
      break;      
    case 2:
      title[i] << "Region-Level Phi-Ring Subtraction, Threshold " << improved_5p_threshold << " GeV";
      minCentBin = 0;
      maxCentBin = 11;     
      phi_subtract = true;
      threshold = improved_5p_threshold;
      break;
    case 3:
      title[i] << "Region-Level Phi-Ring Subtraction, Threshold " << improved_5p_threshold << " GeV";
      minCentBin = 20;
      maxCentBin = 40;     
      phi_subtract = true;
      threshold = improved_5p_threshold;
      break;
    case 4:
      title[i] << "Current L1 System, Threshold " << improved_5p_threshold << " GeV";
      minCentBin = 0;
      maxCentBin = 11;
      phi_subtract = false;
      threshold = improved_5p_threshold;
      break;
    case 5:
      title[i] << "Current L1 System, Threshold " << improved_5p_threshold << " GeV";
      minCentBin = 20;
      maxCentBin = 40;
      phi_subtract = false;
      threshold = improved_5p_threshold;
      break;
    }    

    h_min[i] = (TH1D*)min->Loop(total_events, threshold, phi_subtract, minCentBin, maxCentBin)->Clone();
    h_min[i]->SetTitle(title[i].str().c_str());
    //h_min[i]->Draw("E");
  }

  plot[0] = new TCanvas();
  h_min[0]->Draw("p,E");
  h_min[1]->SetMarkerStyle(24);
  h_min[1]->Draw("p,E,same");
  leg[0] = new TLegend(0.2,0.5,0.5,0.7);
  leg[0]->SetFillColor(0);
  leg[0]->AddEntry(h_min[0],"0-30\% Centrality","p");
  leg[0]->AddEntry(h_min[1],"50-100\% Centrality","p");
  leg[0]->Draw();
  plot[0]->Update();

  plot[1] = new TCanvas();
  h_min[2]->Draw("p,E");
  h_min[3]->SetMarkerStyle(24);
  h_min[3]->Draw("p,E,same");
  leg[1] = new TLegend(0.6,0.4,0.9,0.6);
  leg[1]->SetFillColor(0);
  leg[1]->AddEntry(h_min[2],"0-30\% Centrality","p");
  leg[1]->AddEntry(h_min[3],"50-100\% Centrality","p");
  leg[1]->Draw();
  plot[1]->Update();

  plot[2] = new TCanvas();
  h_min[4]->Draw("p,E");
  h_min[5]->SetMarkerStyle(24);
  h_min[5]->Draw("p,E,same");
  leg[2] = new TLegend(0.6,0.4,0.9,0.6);
  leg[2]->SetFillColor(0);
  leg[2]->AddEntry(h_min[4],"0-30\% Centrality","p");
  leg[2]->AddEntry(h_min[5],"50-100\% Centrality","p");
  leg[2]->Draw();
  plot[2]->Update();
}
