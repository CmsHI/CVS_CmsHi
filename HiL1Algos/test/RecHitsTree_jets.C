#define RecHitsTree_jets_cxx
#include "RecHitsTree_jets.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>

#include "FindTowerJet.C"
#include "FindRegionJet.C"

int getEtaIndex(double eta);
int getPhiIndex(double phi);

TH1D* RecHitsTree_jets::Loop(int total_events, 
				       int threshhold,
				       bool PHI_AVERAGE,
				       bool cut_noise_events)
{
  const int NBINS = 300;
  const int MAX_EN = 600;

  const int JET_RADIUS = 6; //radius = 6 about equals area for region jets for square,
                            //radius = 7 about equals area for region jets for circle
  const bool CIRCULAR_JETS = false; //otherwise square jets

  if (fChain == 0) return(0);
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  TH1D *max_towerjet_energy, *max_regionjet_energy;
  TH1D *efficiency_curve_tower, *efficiency_curve_region;
  // TH2I *max_towerjet_location;

  // TH2I *detectormap;
  // detectormap = new TH2I("detectormap",
  // 			 "Detector Map",
  // 			 NETA_TOWERS,0,NETA_TOWERS,NPHI_TOWERS,0,NPHI_TOWERS);
  // detectormap->SetXTitle("#eta");
  // detectormap->SetYTitle("#phi");
  
  // TH2I *detectormapafter;
  // detectormapafter = new TH2I("detectormapafter",
  // 			 "Detector Map After Subtraction",
  // 			 NETA_TOWERS,0,NETA_TOWERS,NPHI_TOWERS,0,NPHI_TOWERS);
  // detectormapafter->SetXTitle("#eta");
  // detectormapafter->SetYTitle("#phi");
  
  max_towerjet_energy = new TH1D("max_towerjet_energy",
				 "Maximum towerjet energy for each event",
				 NBINS,0,MAX_EN);
  
  max_regionjet_energy = new TH1D("max_regionjet_energy",
				  "Maximum regionjet energy for each event",
				  NBINS,0,MAX_EN);
  
  // max_towerjet_location = new TH2I("max_towerjet_location",
  // 				   "Location of max towerjet for each event",
  // 				   NETA_TOWERS,0,NETA_TOWERS,NPHI_TOWERS,0,NPHI_TOWERS);
  

  int evts = 0;
  bool break_early = total_events != -1;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;
    
    fhlt->GetEntry(jentry);
    fhiinfo->GetEntry(jentry);

    if(cut_noise_events)
    if( !(
	  !(fhlt->L1Tech_BSC_halo_beam2_inner_v0 ||
	    fhlt->L1Tech_BSC_halo_beam2_outer_v0 ||
	    fhlt->L1Tech_BSC_halo_beam1_inner_v0 ||
	    fhlt->L1Tech_BSC_halo_beam1_outer_v0 )
	  && fhiinfo->hiNtracks>0
	  && fhiinfo->hiHFplus>3
	  && fhiinfo->hiHFminus>3
	  )
      )
      continue;

    evts++;
    if(break_early && (evts > total_events)) break;

    fChain->GetEntry(jentry);

    //in case not all towers show up, assume they are 0
    double fullDetectorTowers[NETA_TOWERS][NPHI_TOWERS]; //[eta][phi]
    for(i = 0; i < NETA_TOWERS; i++) for(j = 0; j < NPHI_TOWERS; j++){
	fullDetectorTowers[i][j]=0;
      }

    for(int i = 0; i < n; i++)
    {
      cout << eta[i] << endl;
      //int ieta = getEtaIndex(eta[i]);
      //int iphi = getPhiIndex(iphi[i]);
      //fullDetectorTowers[ieta][iphi] = et[i];
    }

  //   //initialize and fill the regions from the towers
  //   double fullDetectorRegions[NETA_REGIONS][NPHI_REGIONS];
  //   for(i = 0; i < NETA_REGIONS; i++) for(j = 0; j < NPHI_REGIONS; j++){
  // 	fullDetectorRegions[i][j] = 0;
  //     }
  //   for(i = 0; i < NETA_TOWERS; i++) for(j = 0; j < NPHI_TOWERS; j++){
  // 	regionEta = i/4;
  // 	regionPhi = j/4;
  // 	fullDetectorRegions[regionEta][regionPhi] += fullDetectorTowers[i][j];
  //     }

  //   // for(int i = 0; i < NETA_TOWERS; i++)
  //   //   for(int j = 0; j < NPHI_TOWERS; j++)
  //   // 	detectormap->Fill(i, j, fullDetectorTowers[i][j]);

  //   // TCanvas *c0 = new TCanvas();
  //   // detectormap->Draw("Lego2");

  //   if(PHI_AVERAGE)
  //   {
  //     double phiAverageTowers[NETA_TOWERS];
  //     for(int ieta = 0; ieta < NETA_TOWERS; ieta++){
  // 	phiAverageTowers[ieta] = 0;
  // 	for(int iphi = 0; iphi < NPHI_TOWERS; iphi++){
  // 	  phiAverageTowers[ieta] += fullDetectorTowers[ieta][iphi];
  // 	}
  // 	phiAverageTowers[ieta] /= NPHI_TOWERS;
  //     }
      
  //     for(int ieta = 0; ieta < NETA_TOWERS; ieta++)
  // 	for(int iphi = 0; iphi < NPHI_TOWERS; iphi++){
  // 	  fullDetectorTowers[ieta][iphi] -= phiAverageTowers[ieta];
  // 	  if(fullDetectorTowers[ieta][iphi] < 0)
  // 	    fullDetectorTowers[ieta][iphi] = 0;
  // 	}

  //     // for(int i = 0; i < NETA_TOWERS; i++)
  //     // 	for(int j = 0; j < NPHI_TOWERS; j++)
  //     // 	  detectormapafter->Fill(i, j, fullDetectorTowers[i][j]);

  //     // TCanvas *c4 = new TCanvas();
  //     // detectormapafter->Draw("Lego2");
  //   }

  //   if(PHI_AVERAGE)
  //   {
  //     double phiAverageRegions[NETA_REGIONS];
  //     for(int ieta = 0; ieta < NETA_REGIONS; ieta++){
  // 	phiAverageRegions[ieta] = 0;
  // 	for(int iphi = 0; iphi < NPHI_REGIONS; iphi++){
  // 	  phiAverageRegions[ieta] += fullDetectorRegions[ieta][iphi];
  // 	}
  // 	phiAverageRegions[ieta] /= NPHI_REGIONS;
  //     }
      
  //     for(int ieta = 0; ieta < NETA_REGIONS; ieta++)
  // 	for(int iphi = 0; iphi < NPHI_REGIONS; iphi++){
  // 	  fullDetectorRegions[ieta][iphi] -= phiAverageRegions[ieta];
  // 	  if(fullDetectorRegions[ieta][iphi] < 0)
  // 	    fullDetectorRegions[ieta][iphi] = 0;
  // 	}

  //     // for(int i = 0; i < NETA_REGIONS; i++)
  //     // 	for(int j = 0; j < NPHI_REGIONS; j++)
  //     // 	  detectormapafter->Fill(i, j, fullDetectorRegions[i][j]);

  //     // TCanvas *c4 = new TCanvas();
  //     // detectormapafter->Draw("Lego2");
  //   }

  //   TowerJet highestTowerJet = findTowerJet(fullDetectorTowers, CIRCULAR_JETS, JET_RADIUS);
  //   RegionJet highestRegionJet = findRegionJet(fullDetectorRegions);
    
  //   //if(highestJet.sumEt > threshhold)
  //   {
  //     max_towerjet_energy->Fill(highestTowerJet.sumEt);
  //     max_regionjet_energy->Fill(highestRegionJet.sumEt);
  //     // max_towerjet_location->Fill(highestJet.eta_center, highestJet.phi_center);
  //   }
  // }
  
  // efficiency_curve_tower = new TH1D("efficiency_curve_tower","Towerjet Efficiency",
  // 				    NBINS,0,MAX_EN);
  // efficiency_curve_region = new TH1D("efficiency_curve_region","Reigonjet Efficiency",
  // 				    NBINS,0,MAX_EN);
  
  // double total_integral_tower = max_towerjet_energy->Integral();
  // double total_integral_region = max_regionjet_energy->Integral();

  // for(int i = 0; i < NBINS; i++)
  // {
  //   double j = (double)i*(double)MAX_EN/(double)NBINS;
    
  //   double integral_tower = max_towerjet_energy->Integral(i, NBINS);
  //   double integral_region = max_regionjet_energy->Integral(i, NBINS);
    
  //   efficiency_curve_tower->Fill(j, (double)integral_tower/total_integral);      
  //   efficiency_curve_region->Fill(j, (double)integral_region/total_integral);      
  // }

  // TCanvas *c1 = new TCanvas();
  // max_towerjet_energy->SetTitle("max_towerjet_energy");
  // max_towerjet_energy->SetXTitle("GeV");
  // max_towerjet_energy->SetYTitle("Counts");

  // max_regionjet_energy->SetTitle("max_regionjet_energy");
  // max_regionjet_energy->SetXTitle("GeV");
  // max_regionjet_energy->SetYTitle("Counts");
  
  // max_towerjet_energy->Draw();
  // max_regionjet_energy->Draw("same");
  
  // // TCanvas *c2 = new TCanvas();
  // // max_towerjet_location->SetXTitle("Eta index");
  // // max_towerjet_location->SetYTitle("Phi index");
  // // max_towerjet_location->Draw("Lego2");

  // TCanvas *c3 = new TCanvas();
  // efficiency_curve_tower->SetXTitle("Threshold (GeV)");
  // efficiency_curve_tower->SetYTitle("Fraction of passing events");

  // efficiency_curve_region->SetXTitle("Threshold (GeV)");
  // efficiency_curve_region->SetYTitle("Fraction of passing events");

  // efficiency_curve_tower->Draw();
  // efficiency_curve_region->Draw("same");

  return(max_towerjet_energy);
}

int getEtaIndex(double eta)
{
  double etaBounds[] = {
    
  }
}

int getPhiIndex(double phi)
{
  double phiBounds[] = {
}
