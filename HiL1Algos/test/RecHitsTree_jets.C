#define RecHitsTree_jets_cxx
#include "RecHitsTree_jets.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <stdio.h>

#include "FindTowerJet.C"
#include "FindRegionJet.C"

int getEtaIndex(double eta);
int getPhiIndex(double phi, double eta);
int numPhiTowers(int ieta);

TH1D* RecHitsTree_jets::Loop(int total_events, 
			     returnHist whichReturn,
			     bool PHI_AVERAGE,
			     bool cut_noise_events)
{
  const int NBINS = 300;
  const int MAX_EN = 600;

  const int NETA_TOWERS2 = 82; //Why not 88?

  const int JET_RADIUS = 6; //radius = 6 about equals area for region jets for square,
                            //radius = 7 about equals area for region jets for circle
  const bool CIRCULAR_JETS = false; //otherwise square jets

  if (fChain == 0) return(0);
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  TH1D *max_towerjet_energy, *max_regionjet_energy;
  TH1D *efficiency_curve_tower, *efficiency_curve_region;
  // TH2I *max_towerjet_location;
  
  // TH2I *detectormapafter;
  // detectormapafter = new TH2I("detectormapafter",
  // 			 "Detector Map After Subtraction",
  // 			 NETA_TOWERS2,0,NETA_TOWERS2,NPHI_TOWERS,0,NPHI_TOWERS);
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
  // 				   NETA_TOWERS2,0,NETA_TOWERS2,NPHI_TOWERS,0,NPHI_TOWERS);
  

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
    double fullDetectorTowers[NETA_TOWERS2][NPHI_TOWERS]; //[eta][phi]
    for(int i = 0; i < NETA_TOWERS2; i++) for(int j = 0; j < NPHI_TOWERS; j++){
	fullDetectorTowers[i][j]=0;
      }

    for(int i = 0; i < n; i++)
    {
      //printf("%lf\t%lf\n", eta[i], phi[i]);
      int ieta = getEtaIndex(eta[i]);
      int iphi = getPhiIndex(phi[i], eta[i]);
      fullDetectorTowers[ieta][iphi] = et[i];
      //printf("%lf %d %lf %d\n",eta[i],ieta,phi[i],iphi);
    }
  
    //printf("Initialized Towers. Moving on to Regions...\n");
    //initialize and fill the regions from the towers
    double fullDetectorRegions[NETA_REGIONS][NPHI_REGIONS];
    for(int i = 0; i < NETA_REGIONS; i++){
      for(int j = 0; j < NPHI_REGIONS; j++){
  	fullDetectorRegions[i][j] = 0;
      }
    }
    //printf("Regions zeroed.\n");
    for(int i = 0; i < NETA_TOWERS2; i++){
      for(int j = 0; j < NPHI_TOWERS; j++){
  	int regionEta;
	if(i == 0) regionEta = i;
	else if(i == 81) regionEta = NETA_REGIONS-1;
	else regionEta =  (i-1)/4 + 1;
  	int regionPhi = j/4;
	
  	fullDetectorRegions[regionEta][regionPhi] += fullDetectorTowers[i][j];
	//printf("%d %d %lf\n",regionEta,regionPhi,fullDetectorTowers[i][j]);
      }
    }
    //printf("Finished Regions. Now drawing.\n");
    
    // TH2D *detectormap;
    // detectormap = new TH2D("detectormap",
    // 			   "Detector Map",
    // 			   //NETA_TOWERS2,0,NETA_TOWERS2,NPHI_TOWERS,0,NPHI_TOWERS);
    // 			   NETA_REGIONS,0,NETA_REGIONS,NPHI_REGIONS,0,NPHI_REGIONS);
    // detectormap->SetXTitle("#eta");
    // detectormap->SetYTitle("#phi");
    // for(int i = 0; i < NETA_REGIONS; i++)
    //   for(int j = 0; j < NPHI_REGIONS; j++)
    // 	detectormap->Fill(i, j, fullDetectorRegions[i][j]);
    // TCanvas *c0 = new TCanvas();
    // detectormap->Draw("Lego2");

    if(PHI_AVERAGE)
    {
      double phiAverageTowers[NETA_TOWERS2];
      for(int ieta = 0; ieta < NETA_TOWERS2; ieta++){
  	phiAverageTowers[ieta] = 0;
  	for(int iphi = 0; iphi < NPHI_TOWERS; iphi++){
  	  phiAverageTowers[ieta] += fullDetectorTowers[ieta][iphi];
  	}
  	phiAverageTowers[ieta] /= numPhiTowers(ieta);
      }
      
      for(int ieta = 0; ieta < NETA_TOWERS2; ieta++)
  	for(int iphi = 0; iphi < NPHI_TOWERS; iphi++){
  	  fullDetectorTowers[ieta][iphi] -= phiAverageTowers[ieta];
  	  if(fullDetectorTowers[ieta][iphi] < 0)
  	    fullDetectorTowers[ieta][iphi] = 0;
  	}

      // for(int i = 0; i < NETA_TOWERS2; i++)
      // 	for(int j = 0; j < NPHI_TOWERS; j++)
      // 	  detectormapafter->Fill(i, j, fullDetectorTowers[i][j]);

      // TCanvas *c4 = new TCanvas();
      // detectormapafter->Draw("Lego2");
    }

    if(PHI_AVERAGE)
    {
      double phiAverageRegions[NETA_REGIONS];
      for(int ieta = 0; ieta < NETA_REGIONS; ieta++){
  	phiAverageRegions[ieta] = 0;
  	for(int iphi = 0; iphi < NPHI_REGIONS; iphi++){
  	  phiAverageRegions[ieta] += fullDetectorRegions[ieta][iphi];
  	}
  	phiAverageRegions[ieta] /= NPHI_REGIONS;
      }
      
      for(int ieta = 0; ieta < NETA_REGIONS; ieta++)
  	for(int iphi = 0; iphi < NPHI_REGIONS; iphi++){
  	  fullDetectorRegions[ieta][iphi] -= phiAverageRegions[ieta];
  	  if(fullDetectorRegions[ieta][iphi] < 0)
  	    fullDetectorRegions[ieta][iphi] = 0;
  	}

      // for(int i = 0; i < NETA_REGIONS; i++)
      // 	for(int j = 0; j < NPHI_REGIONS; j++)
      // 	  detectormapafter->Fill(i, j, fullDetectorRegions[i][j]);

      // TCanvas *c4 = new TCanvas();
      // detectormapafter->Draw("Lego2");
    }

    TowerJet highestTowerJet = findTowerJet(fullDetectorTowers, CIRCULAR_JETS, JET_RADIUS);
    RegionJet highestRegionJet = findRegionJet(fullDetectorRegions);
    
    //if(highestJet.sumEt > threshhold)
    {
      max_towerjet_energy->Fill(highestTowerJet.sumEt);
      max_regionjet_energy->Fill(highestRegionJet.et);
      // max_towerjet_location->Fill(highestJet.eta_center, highestJet.phi_center);
    }
  }
  
  efficiency_curve_tower = new TH1D("efficiency_curve_tower","Towerjet Efficiency",
  				    NBINS,0,MAX_EN);
  efficiency_curve_region = new TH1D("efficiency_curve_region","Reigonjet Efficiency",
  				    NBINS,0,MAX_EN);
  
  double total_integral_tower = max_towerjet_energy->Integral();
  double total_integral_region = max_regionjet_energy->Integral();

  for(int i = 0; i < NBINS; i++)
  {
    double j = (double)i*(double)MAX_EN/(double)NBINS;
    
    double integral_tower = max_towerjet_energy->Integral(i, NBINS);
    double integral_region = max_regionjet_energy->Integral(i, NBINS);
  
    efficiency_curve_tower->Fill(j, (double)integral_tower/total_integral_tower);      
    efficiency_curve_region->Fill(j, (double)integral_region/total_integral_region);      
  }

  // TCanvas *c1 = new TCanvas();
  // max_towerjet_energy->SetTitle("max_towerjet_energy");
  max_towerjet_energy->SetXTitle("GeV");
  max_towerjet_energy->SetYTitle("Counts");
  // max_towerjet_energy->SetLineColor(kRed);
  
  // max_regionjet_energy->SetTitle("max_regionjet_energy");
  max_regionjet_energy->SetXTitle("GeV");
  max_regionjet_energy->SetYTitle("Counts");
  // max_regionjet_energy->SetLineColor(kBlue);
  
  // max_towerjet_energy->Draw();
  // max_regionjet_energy->Draw("same");
  
  // TCanvas *c2 = new TCanvas();
  // max_towerjet_location->SetXTitle("Eta index");
  // max_towerjet_location->SetYTitle("Phi index");
  // max_towerjet_location->Draw("Lego2");

  // TCanvas *c3 = new TCanvas();
  efficiency_curve_tower->SetXTitle("Threshold (GeV)");
  efficiency_curve_tower->SetYTitle("Fraction of passing events");
  // efficiency_curve_tower->SetLineColor(kRed);

  efficiency_curve_region->SetXTitle("Threshold (GeV)");
  efficiency_curve_region->SetYTitle("Fraction of passing events");
  // efficiency_curve_region->SetLineColor(kBlue);

  // efficiency_curve_tower->Draw();
  // efficiency_curve_region->Draw("same");

  switch(whichReturn)
  {
  case TOWER_ENERGY:
    return(max_towerjet_energy);
    break;
  case TOWER_EFF:
    return(efficiency_curve_tower);
    break;
  case REGION_ENERGY:
    return(max_regionjet_energy);
    break;
  case REGION_EFF:
    return(efficiency_curve_region);
    break;
  }    
}

int getEtaIndex(double eta)
{
  const double epsilon = 0.01;
  double HBetaBounds[20] = {
    0.043500,
    0.130500,
    0.217500,
    0.304500,
    0.391500,
    0.478500,
    0.565500,
    0.652500,
    0.739500,
    0.826500,
    0.913500,
    1.000500,
    1.087500,
    1.174500,
    1.261500,
    1.348500,
    1.435500,
    1.522500,
    1.609500,
    1.696500
  };

  double HEetaBounds[19] = {
    1.785000,
    1.880000,
    1.986500,
    2.107500,
    2.252000,
    2.416000,
    2.575000,
    2.759000,
    2.934000,
    3.051500,
    3.226500,
    3.401500,
    3.576500,
    3.751500,
    3.926000,
    4.102000,
    4.277000,
    4.450500,
    4.627000
  };

  double HFetaBounds[2] = {
    4.802500,
    5.040000
  };

  double aeta = fabs(eta);
  int sign = (eta > 0) ? 1: -1;
  int index = -1;
  
  if(aeta < 1.785000)
  {
    for(int i = 0; i < 20; i++)
    {
      if(fabs(aeta - HBetaBounds[i]) < epsilon)
      {
	index = i;
	break;
      }
    }
  }
  else if (aeta < 4.802500)
  {
    for(int i = 0; i < 19; i++)
    {
      if(fabs(aeta - HEetaBounds[i]) < epsilon)
      {
	index = i + 20;
	break;
      }
    }
  }
  else
  {
    for(int i = 0; i < 2; i++)
    {
      if(fabs(aeta - HFetaBounds[i]) < epsilon)
      {
	index = i + 39;
	break;
      }
    }
  }
  if(sign>0) index++;
  return (40 + sign*index);
}

int getPhiIndex(double phi, double eta)
{
  const double epsilon = 0.01;
  double HBphiBounds[36] = {
    0.043633,
    0.130900,
    0.218166,
    0.305433,
    0.392699,
    0.479966,
    0.567232,
    0.654498,
    0.741765,
    0.829031,
    0.916298,
    1.003564,
    1.090831,
    1.178097,
    1.265364,
    1.352630,
    1.439897,
    1.527163,
    1.614429,
    1.701696,
    1.788962,
    1.876229,
    1.963495,
    2.050762,
    2.138028,
    2.225295,
    2.312561,
    2.399828,
    2.487094,
    2.574361,
    2.661627,
    2.748893,
    2.836160,
    2.923427,
    3.010693,
    3.097960    
  };

  double HEphiBounds[18] = {
    0.087266,
    0.261799,
    0.436332,
    0.610865,
    0.785398,
    0.959931,
    1.134464,
    1.308997,
    1.483530,
    1.658063,
    1.832596,
    2.007129,
    2.181662,
    2.356194,
    2.530727,
    2.705260,
    2.879793,
    3.054326
  };

  double HFphiBounds[18] = {
    -3.141593,
    -2.792527,
    -2.443461,
    -2.094395,
    -1.745329,
    -1.396263,
    -1.047198,
    -0.698132,
    -0.349066,
    -0.000000,   
    0.349066,
    0.698132,
    1.047198,
    1.396263,
    1.745329,
    2.094395,
    2.443461,
    2.792527
  };

  double aeta = fabs(eta);
  double aphi = fabs(phi);
  int sign = (phi > 0) ? 1: -1;
  int plus = (phi > 0) ? 0: 1;
  
  if(aeta < 1.785000)
  {
    for(int i = 0; i < 36; i++)
    {
      if(fabs(aphi - HBphiBounds[i]) < epsilon)
	return(35 + sign*i + plus);
    }
  }
  else if (aeta < 4.802500)
  {
    for(int i = 0; i < 18; i++)
    {
      if(fabs(aphi - HEphiBounds[i]) < epsilon)
	return(34 +  2*(sign*i + plus));
    }
  }
  else
  {
    for(int i = 0; i < 18; i++)
    {
      if(fabs(phi - HFphiBounds[i]) < epsilon)
	return(i*4);
    }
  }
}

int numPhiTowers(int ieta)
{
  if(ieta < 2 || ieta > 79)
    return(18);
  else if(ieta < 21 || ieta > 60)
    return(36);
  else
    return(72);
}
