#include "TH1.h"
#include "TriggerPrimitivesTree_alex.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"
#include <sstream>

void macro3()
{
  int total_events = 3000;
  TriggerPrimitivesTree_alex *min =
    new TriggerPrimitivesTree_alex(new TFile("minbias.root"));
  TriggerPrimitivesTree_alex *jet =
    new TriggerPrimitivesTree_alex(new TFile("jet.root"));
  TriggerPrimitivesTree_alex *cen =
    new TriggerPrimitivesTree_alex(new TFile("central.root"));
  TriggerPrimitivesTree_alex *pp =
    new TriggerPrimitivesTree_alex(new TFile("pp.root"));

  TCanvas *plot = new TCanvas("plot","Efficiency Curves");
  plot->Divide(2,2);

  TriggerPrimitivesTree_alex::SUBTRACT_ALGORITHM algo;
  TriggerPrimitivesTree_alex::CALIBRATION_TYPE cal;
  
  TH1D* h_min[4]; 
  TH1D* h_jet[4];
  TH1D* h_cen[4];
  TH1D* h_pp[4];

  TLegend* leg[4];
  TLatex* tit[4];

  stringstream title[4];
  title[0] << "No Subtraction";
  title[1] << "Minimum RCT Region Subtraction";
  title[2] << "Minimum RCT 3x3 Region Subtraction";
  title[3] << "Minimum RCT 3x3 Region Subtraction with Digital Calibration";

  for(int i = 0; i < 4; i++)
  {
    switch(i)
    {
    case 0:
      algo = TriggerPrimitivesTree_alex::NONE; 
      cal = TriggerPrimitivesTree_alex::NO;
      break;
    case 1:
      algo = TriggerPrimitivesTree_alex::RCT_MINIMUM;
      cal = TriggerPrimitivesTree_alex::NO;
      break;
    case 2:
      algo = TriggerPrimitivesTree_alex::MIN_3X3;
      cal = TriggerPrimitivesTree_alex::NO;
      break;
    case 3:
      algo = TriggerPrimitivesTree_alex::MIN_3X3;
      cal = TriggerPrimitivesTree_alex::DIGITAL;
      break;
    }    


    h_min[i] = (TH1D*)min->Loop(total_events, 0, cal, algo, true, "Minbias Sample")->Clone();
    h_jet[i] = (TH1D*)jet->Loop(total_events, 0, cal, algo, true, "Jet95 Sample")->Clone();
    h_cen[i] = (TH1D*)cen->Loop(total_events, 0, cal, algo, true, "Central Sample")->Clone();
    h_pp[i] =  (TH1D*)pp->Loop(total_events, 0, cal, algo, true, "p-p Sample")->Clone();


    plot->cd(i+1);
    h_min[i]->SetLineColor(kRed);
    h_min[i]->Draw("L");

    h_jet[i]->SetLineColor(kBlue);
    h_jet[i]->Draw("L,same");

    h_cen[i]->SetLineColor(46);
    h_cen[i]->Draw("L,same");

    h_pp[i]->Draw("L,same");

    leg[i] = new TLegend(0.5,0.5,0.8,0.7);
    tit[i] = new TLatex();
    tit[i]->SetTextSize(0.04);
    tit[i]->DrawText(0.3,1.2,title[i].str().c_str());
    leg[i]->SetFillColor(0);
    //leg[i]->SetHeader(title[i].str().c_str());
    leg[i]->AddEntry(h_min[i],"Minbias Sample","l");
    leg[i]->AddEntry(h_jet[i],"Jet95 Sample","l");
    leg[i]->AddEntry(h_cen[i],"Central Sample","l");
    leg[i]->AddEntry(h_pp[i],"p-p Sample","l");
    leg[i]->Draw();
 
    //plot->SetTitle(title[i].str().c_str());
    plot->Update();
  }

  // plot->cd(2);
  // TLegend *legend = new TLegend(); //plot->BuildLegend();
  // legend->SetFillColor(0);
  // legend->AddEntry(h_min[0],
  // legend->Draw();
  // plot->Update();
  
}
