#include "TH1.h"
#include "TriggerPrimitivesTree_alex.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLine.h"
#include <sstream>

void macro4()
{
  int total_events = 10000;
  TriggerPrimitivesTree_alex *min =
    new TriggerPrimitivesTree_alex(new TFile("minbias.root"));
  TriggerPrimitivesTree_alex *jet =
    new TriggerPrimitivesTree_alex(new TFile("jet.root"));
  TriggerPrimitivesTree_alex *cen =
    new TriggerPrimitivesTree_alex(new TFile("central.root"));
  // TriggerPrimitivesTree_alex *pp =
  //   new TriggerPrimitivesTree_alex(new TFile("pp.root"));

  TCanvas* plot[2];
 
  TriggerPrimitivesTree_alex::SUBTRACT_ALGORITHM algo;
  TriggerPrimitivesTree_alex::CALIBRATION_TYPE cal;
  
  TH1D* h_min[2]; 
  TH1D* h_jet[2];
  TH1D* h_cen[2];
  //TH1D* h_pp[4];

  TLegend* leg[2];
  // TLatex* tit[4];

  stringstream title[2];
  title[0] << "No Subtraction";
//  title[1] << "Minimum RCT Region Subtraction";
//  title[2] << "Minimum RCT 3x3 Region Subtraction";
  title[1] << "phi-ring subtraction";

  for(int i = 0; i < 2; i++)
  {
    switch(i)
    {
    case 0:
      algo = TriggerPrimitivesTree_alex::NONE; 
      cal = TriggerPrimitivesTree_alex::NO;
      break;
    case 1:
      algo = TriggerPrimitivesTree_alex::PHI_AVERAGE;
      cal = TriggerPrimitivesTree_alex::NO;
      break;
    // case 2:
    //   algo = TriggerPrimitivesTree_alex::MIN_3X3;
    //   cal = TriggerPrimitivesTree_alex::NO;
    //   break;
    // case 3:
    //   algo = TriggerPrimitivesTree_alex::MIN_3X3;
    //   cal = TriggerPrimitivesTree_alex::DIGITAL;
    //   break;
    }    


    h_min[i] = (TH1D*)min->Loop(total_events, 0, cal, algo, true, "Minbias Sample")->Clone();
    h_jet[i] = (TH1D*)jet->Loop(total_events, 0, cal, algo, true, "Jet95 Sample")->Clone();
    h_cen[i] = (TH1D*)cen->Loop(total_events, 0, cal, algo, true, "Central Sample")->Clone();
    //h_pp[i] =  (TH1D*)pp->Loop(total_events, 0, cal, algo, true, "p-p Sample")->Clone();


    plot[i] = new TCanvas();

    /******************************************************/
    double bin_contents;
    double fivep_p;
    for(int j = 1; j < 180; j++)
    {
      bin_contents = h_min[i]->GetBinContent(j);
      if(bin_contents <= 0.05)
      {
    	fivep_p = (double)j*600./180.;
    	break;
      }
    }

    TLine *fivep_l = new TLine(fivep_p, 0, fivep_p, 1);
    fivep_l->SetLineWidth(3);
    fivep_l->SetLineStyle(3);


    /***********************************************************/
    h_min[i]->SetLineColor(kRed);
    h_min[i]->SetTitle(title[i].str().c_str());
    h_min[i]->Draw("L");

    fivep_l->Draw("same");

    h_jet[i]->SetLineColor(kBlue);
    h_jet[i]->Draw("L,same");

    h_cen[i]->SetLineColor(46);
    h_cen[i]->Draw("L,same");

    //h_pp[i]->Draw("L,same");

    leg[i] = new TLegend(0.5,0.5,0.8,0.7);

    leg[i]->SetFillColor(0);
    //leg[i]->SetHeader(title[i].str().c_str());
    leg[i]->AddEntry(h_min[i],"Minbias Sample","l");
    leg[i]->AddEntry(h_jet[i],"Jet95 Sample","l");
    leg[i]->AddEntry(h_cen[i],"Central Sample","l");    
    //leg[i]->AddEntry(h_pp[i],"p-p Sample","l");
    leg[i]->AddEntry(fivep_l,"Minbias 5%","l");
    leg[i]->Draw();
 
    plot[i]->Update();
  }  
}
