#include "TH1.h"
#include "TriggerPrimitivesTree_jetcurve.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"
#include <sstream>

#include "TriggerPrimitivesTree_jetcurve.C"

void macro5region(int total_events = -1)
{
  TriggerPrimitivesTree_jetcurve *min =
    new TriggerPrimitivesTree_jetcurve(new TFile("minbias.root"));

  bool phi_subtract[] = {false, false, false, false,
			 true,  true,  true,  true};

  //const int total_events = -1;

  TH1D* h_min[8]; 
  TCanvas *plot[4];
  TLegend *leg[4];
  stringstream title[8];
  int thresholds[] = {60, 60, 100, 100, 60, 60 ,100, 100};

  int minbin[] = {0, 20, 0, 20, 0, 20,0, 20,};
  int maxbin[] = {11, 40, 11, 40, 11, 40,11, 40,};
  
  int threshold;
  for(int i = 0; i < 8; i++)
  {
    h_min[i] = (TH1D*)min->Loop(total_events, thresholds[i],
				phi_subtract[i], minbin[i], maxbin[i])->Clone();
    if(phi_subtract[i])
      title[i] << "2015 system. Threshold " << thresholds[i] << " GeV";
    else
      title[i] << "Current system. Threshold " << thresholds[i] << " GeV";
    h_min[i]->SetTitle(title[i].str().c_str());
  }

  plot[0] = new TCanvas("c1");
  h_min[0]->Draw("p,E");
  h_min[1]->SetMarkerStyle(24);
  h_min[1]->Draw("p,E,same");
  leg[0] = new TLegend(0.6,0.2,0.9,0.4);
  leg[0]->SetFillColor(0);
  leg[0]->AddEntry(h_min[0], "Centrality 0 to 30\%","p");
  leg[0]->AddEntry(h_min[1], "Centrality 50 to 100\%","p");
  leg[0]->Draw();
  plot[0]->Update();
  plot[0]->SaveAs("jetto_current_thresh_60.C");
  plot[0]->SaveAs("jetto_current_thresh_60.gif");


  plot[1] = new TCanvas("c2");
  h_min[2]->Draw("p,E");
  h_min[3]->SetMarkerStyle(24);
  h_min[3]->Draw("p,E,same");
  leg[1] = new TLegend(0.6,0.2,0.9,0.4);
  leg[1]->SetFillColor(0);
  leg[1]->AddEntry(h_min[2], "Centrality 0 to 30\%","p");
  leg[1]->AddEntry(h_min[3], "Centrality 50 to 100\%","p");
  leg[1]->Draw();
  plot[1]->Update();
  plot[1]->SaveAs("jetto_current_thresh_100.C");
  plot[1]->SaveAs("jetto_current_thresh_100.gif");
  
  plot[2] = new TCanvas("c3");
  h_min[4]->Draw("p,E");
  h_min[5]->SetMarkerStyle(24);
  h_min[5]->Draw("p,E,same");
  leg[2] = new TLegend(0.6,0.2,0.9,0.4);
  leg[2]->SetFillColor(0);
  leg[2]->AddEntry(h_min[4], "Centrality 0 to 30\%","p");
  leg[2]->AddEntry(h_min[5], "Centrality 50 to 100\%","p");
  leg[2]->Draw();
  plot[2]->Update();
  plot[2]->SaveAs("jetto_2015_thresh_60.C");
  plot[2]->SaveAs("jetto_2015_thresh_60.gif");
  
  plot[3] = new TCanvas("c4");
  h_min[6]->Draw("p,E");
  h_min[7]->SetMarkerStyle(24);
  h_min[7]->Draw("p,E,same");
  leg[3] = new TLegend(0.6,0.2,0.9,0.4);
  leg[3]->SetFillColor(0);
  leg[3]->AddEntry(h_min[6], "Centrality 0 to 30\%","p");
  leg[3]->AddEntry(h_min[7], "Centrality 50 to 100\%","p");
  leg[3]->Draw();
  plot[3]->Update(); 
  plot[3]->SaveAs("jetto_2015_thresh_100.C");
  plot[3]->SaveAs("jetto_2015_thresh_100.gif");
}
