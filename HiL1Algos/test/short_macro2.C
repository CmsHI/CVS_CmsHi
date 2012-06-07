#include <sstream>
#include "TriggerPrimitivesTree_calib.h"
#include "TH1.h"
#include "TFile.h"

void short_macro2()
{
  //.L TriggerPrimitivesTree_calib.C+;

  TriggerPrimitivesTree_calib *t = new TriggerPrimitivesTree_calib(new TFile("minbias.root"));
  TriggerPrimitivesTree_calib *q = new TriggerPrimitivesTree_calib(new TFile("pp.root"));

  TH1D* histos[9];
  
  for (int i = 0; i<8; i++)
  {
    int bin = i*5;

    stringstream name;
    name << "histos" << i;
    histos[i] = (TH1D*)t->Loop(3000, bin)->Clone(name.str().c_str());
  }

  stringstream namepp;
  namepp << "p-p events";
  histos[8] = (TH1D*)q->Loop(3000, -1)->Clone(namepp.str().c_str());

  TCanvas* plot[9];
 
  //plot->Divide(3,3);
  //TFile f("histos.root","recreate");
  for (int j = 0; j<9; j++)
  {
    //plot->cd(j+2);
    plot[j] = new TCanvas();
    histos[j]->Draw();
    //plot->Modified();
  }
  //plot->cd(1);
  // plot[9] = new TC
  // histos[8]->Draw();

  //plot->Update();
}
