#define TriggerPrimitivesTree_calib_cxx
#include "TriggerPrimitivesTree_calib.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void TriggerPrimitivesTree_calib::Loop(int total_events)
{
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  
  double averages[22][18];

  for(int i = 0; i < 22; i++)
    for(int j = 0; j < 18; j++)
    {
      averages[i][j] = 0;
    }
 
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;
    
    //! here it loads the same event from all the trees
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    int fulldetector[22][18]; //[eta][phi]

    for(int i = 0; i < numRegions; i++)
    {
      fulldetector[caloRegionEtaIndex[i]][caloRegionPhiIndex[i]] = caloRegionEt[i];
    }

    for(int i = 0; i < 22; i++)
      for(int j = 0; j < 18; j++)
      {
	averages[i][j] += (double)fulldetector[i][j]/total_events;
      }

    
    if(jentry > total_events - 2) break;
  }

  double calibration[22][18];
  double big_average = 0;

  for(int i = 0; i < 22; i++)
    for(int j = 0; j < 18; j++)
    {
      big_average += averages[i][j]/(22*18);
    }

  TH2D *calibrationpic = new TH2D("calibrationpic", "Average Response of each region",
				  22,0,22,18,0,18);
  
  cout << "calibrations!" << endl;
  cout << "{";
  for(int i = 0; i < 22; i++)
  {
    cout << "{";
    for(int j = 0; j < 18; j++)
    {
      calibration[i][j] = big_average/averages[i][j];
      calibrationpic->Fill(i, j, averages[i][j]);
      cout << calibration[i][j];
      if(j != 17) cout << ",";
    }
    cout << "}";
    if(i != 21) cout << ",";
  }
  cout << "}"<< endl;

  calibrationpic->Draw("Lego2");
  
}
