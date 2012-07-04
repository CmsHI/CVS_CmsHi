#include "TH1.h"
#include "TriggerPrimitivesTree_alex.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLine.h"
//#include <sstream>
#include "TString.h"

#include "TriggerPrimitivesTree_alex.C"

using namespace std;

void macro4()
{  
  int total_events = -1;
  TriggerPrimitivesTree_alex *min =
    new TriggerPrimitivesTree_alex(new TFile("minbias_v2.root"));
  // TriggerPrimitivesTree_alex *jet =
  //   new TriggerPrimitivesTree_alex(new TFile("jet.root"));
  
  TCanvas* plot;
 
  bool algo[2];
  
  TH1D* h_min[3];
  //TH1D* h_jet[2];

  TLegend* leg;

  TString title = "Efficiency";

  algo[0] = false;  
  algo[1] = true;

  h_min[0] = (TH1D*)min->Loop(total_events, 0, algo[0], false)->Clone();
  h_min[1] = (TH1D*)min->Loop(total_events, 0, algo[1], false)->Clone();

  // h_jet[0] = (TH1D*)jet->Loop(total_events, 0, algo[0], true)->Clone();
  // h_jet[1] = (TH1D*)jet->Loop(total_events, 0, algo[1], true)->Clone();

  /************** Doga File *************************/
  // TH1D* hmb=new TH1D();
  // TFile *f1 = new TFile("/net/hisrv0001/home/dgulhan/L1Trigger/newEtHist_mb.root");
  // hmb = (TH1D*)f1->Get("LargestEt");

  // int nbins_doga = hmb->GetNbinsX();
  // int max_en_doga = hmb->GetXaxis()->GetXmax();
  // h_min[2] = new TH1D("efficiency_curve","Fraction of passing events versus threshold",
  // 			      nbins_doga,0,max_en_doga);
  // double total_integral = hmb->Integral();
  // for(int i = 0; i < nbins_doga; i++)
  // {
  //   double j = (double)i*(double)max_en_doga/(double)nbins_doga;
  //   double integral = hmb->Integral(i, nbins_doga);
  //   h_min[2]->Fill(j, (double)integral/total_integral);      
  // }
  /*****************************************************/

  plot = new TCanvas();

  /******************************************************/
  TLine *fivep_l[3];
  for(int i = 0; i < 2; i++)
  {
    double bin_contents;
    double fivep_p;
    int nbins = h_min[i]->GetNbinsX();
    double hist_max = h_min[i]->GetXaxis()->GetXmax();
    for(int j = 1; j < nbins; j++)
    {
      bin_contents = h_min[i]->GetBinContent(j);
      if(bin_contents <= 0.05)
      {
    	fivep_p = (double)j*hist_max/(double)nbins;
    	break;
      }
    }

    fivep_l[i] = new TLine(fivep_p, 0, fivep_p, 1);
    fivep_l[i]->SetLineWidth(3);
    fivep_l[i]->SetLineStyle(3);

    cout << "five_p " << fivep_p << endl;
  }
  /***********************************************************/
  h_min[0]->SetLineColor(kRed);
  h_min[0]->SetTitle(title);
  h_min[0]->Draw("L");

  h_min[1]->SetLineColor(kBlue);
  h_min[1]->Draw("L,same");

  // h_min[2]->Draw("L,same");

  // h_jet[0]->Draw("L,same");
  // h_jet[1]->SetLineColor(kGreen);
  // h_jet[1]->Draw("L,same");

  fivep_l[0]->SetLineColor(kRed);
  fivep_l[0]->Draw("same");
  
  fivep_l[1]->SetLineColor(kBlue);
  fivep_l[1]->Draw("same");

//   fivep_l[2]->Draw("same");

  leg = new TLegend(0.5,0.5,0.8,0.7);

  leg->SetFillColor(0);

  leg->AddEntry(h_min[0],"Current L1 System","l");
  leg->AddEntry(h_min[1],"Phi-Ring Subtraction","l");
  // leg->AddEntry(h_min[2],"Tower Level Phi-Ring Subtraction","l");
  leg->AddEntry(fivep_l[0],"Current System 5%","l");
  leg->AddEntry(fivep_l[1],"Phi-Ring Subtraction 5%","l");
//   leg->AddEntry(fivep_l[2],"Tower-LevelPhi-Ring Subtraction 5%","l");

  // leg->AddEntry(h_jet[0],"Current L1 System Jet","l");
  // leg->AddEntry(h_jet[1],"Phi-Ring Subtraction Jet","l");
  
  leg->Draw();
 
  plot->Update();
}  

