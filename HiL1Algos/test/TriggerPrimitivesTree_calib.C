#define TriggerPrimitivesTree_calib_cxx
#include "TriggerPrimitivesTree_calib.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <sstream>

TH1D* TriggerPrimitivesTree_calib::Loop(int total_events, int cent_bin)
{
  if (fChain == 0) return(0);
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;

  stringstream title;
  int bin_diff;
  if(cent_bin == -1)
  {
    bin_diff = 40;
    cent_bin = 0;
    title << "p-p events.";
  }
  else
  {
    bin_diff = 5;
    title << "Centrality bins " << cent_bin << " to " << cent_bin + bin_diff -1 << ".";
  }

  //int max_evts = 3000;
  int evts = 0;
  
  double averages[22][18];

  for(int i = 0; i < 22; i++)
    for(int j = 0; j < 18; j++)
    {
      averages[i][j] = 0;
    }
 
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;
    
    fhlt->GetEntry(jentry);
    fhiinfo->GetEntry(jentry);

    if( !(!(fhlt->L1Tech_BSC_halo_beam2_inner_v0 || fhlt->L1Tech_BSC_halo_beam2_outer_v0 || fhlt->L1Tech_BSC_halo_beam1_inner_v0 || fhlt->L1Tech_BSC_halo_beam1_outer_v0 ) && fhiinfo->hiNtracks>0 && fhiinfo->hiHFplus>3 && fhiinfo->hiHFminus>3 && fhiinfo->hiBin>=cent_bin && fhiinfo->hiBin<cent_bin+bin_diff))
      continue;

    evts++;
    if(evts > total_events) break;
   
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
  }

  double calibration[22][18];
  //double big_average = 0;

  TH1D *calibrationpic = new TH1D("calibrationpic", title.str().c_str(),
				  22,0,22);
  for(int i = 0; i < 22; i++)
  {
    double phi_average = 0;
    for(int j = 0; j < 18; j++)
    {
      //big_average += averages[i][j]/(22*18);
      phi_average += averages[i][j]/18;
    }
    calibrationpic->Fill(i, phi_average);
  }
  
  // cout << "calibrations!" << endl;
  // cout << "{";
  // for(int i = 0; i < 22; i++)
  // {
  //   cout << "{";
  //   for(int j = 0; j < 18; j++)
  //   {
  //     calibration[i][j] = big_average/averages[i][j];
  //     cout << calibration[i][j];
  //     if(j != 17) cout << ",";
  //   }
  //   cout << "}";
  //   if(i != 21) cout << ",";
  // }
  // cout << "}"<< endl;

  calibrationpic->SetXTitle("#eta");
  calibrationpic->SetYTitle("Compressed Et");
  //calibrationpic->Draw();

  return(calibrationpic);
  
}
