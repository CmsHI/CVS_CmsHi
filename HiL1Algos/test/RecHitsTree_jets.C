#define RecHitsTree_jets_cxx
#include "RecHitsTree_jets.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <stdio.h>
#include <TH2.h>
#include <TNtuple.h>

const int NETA_TOWERS = 82; //Why not 88?

#include "FindTowerJet.C"
#include "FindRegionJet.C"

int getEtaIndex(double eta);
int getPhiIndex(double phi, double eta);
int numPhiTowers(int ieta);

TH1D* RecHitsTree_jets::Loop(int total_events, 
			     returnHist whichReturn,
			     bool PHI_AVERAGE,
			     bool cut_noise_events,
			     bool DO_JET_ENERGY_CORRECTIONS)
{
  const int NBINS = 300;
  const int MAX_EN = 600;

  //towerjet parameters. diamater = 9 and circular jets for the
  //correction table.
  const int JET_DIAMETER = 5;
  const bool CIRCULAR_JETS = true; //otherwise square jets

  if (fChain == 0) return(0);
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  TH1D *max_towerjet_energy, *max_regionjet_energy;
  TH1D *efficiency_curve_tower, *efficiency_curve_region;

  
  // TFile *outf = new TFile("L1vsOffline.root", "recreate");
  // TNtuple *matchedTowerJets =
  //   new TNtuple("TowerJets","TowerJets",
  // 		"L1IPhi:L1Phi:L1IEta:L1Eta:L1correctedEt:L1uncorrectedEt:offlineEta:offlinePhi:offlinePt");  
  // TNtuple *matchedRegionJets =
  //   new TNtuple("RegionJets","RegionJets",
  // 		"L1IPhi:L1Phi:L1IEta:L1Eta:L1correctedEt:L1uncorrectedEt:offlineEta:offlinePhi:offlinePt");  


  // TH2I *max_towerjet_location;
  
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
  
  // TH1D *max_regionjet_location = new TH1D("max_regionjet_location",
  // 					  "Eta Location of max regionjet, offlinejet jet 1<eta<2",
  // 					  4*NETA_REGIONS,-4.5,4.5);

  // TH1D *max_towerjet_location = new TH1D("max_towerjet_location",
  // 					 "Eta Location of max towerjet, offlinejet jet 1<eta<2",
  // 					 4*NETA_TOWERS,-4.5,4.5);


  TH2D *regionL1JetEnergyCorrection;
  TH2D *towerL1JetEnergyCorrection;
  if(DO_JET_ENERGY_CORRECTIONS)
  {
    TFile *infile = new TFile("JetEnergyCorrectionsTable.root");
    regionL1JetEnergyCorrection =
      (TH2D*)infile->Get("regionL1JetEnergyCorrection");
    towerL1JetEnergyCorrection =
      (TH2D*)infile->Get("towerL1JetEnergyCorrection");
  }

  int evts = 0;
  bool break_early = total_events != -1;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;

    fhlt->GetEntry(jentry);
    fhiinfo->GetEntry(jentry);
    fjet->GetEntry(jentry);

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

    fChain->GetEntry(jentry);

    if(fjet->nref < 1) continue;
    //if(fabs(fabs(fjet->jteta[0])-3) > 1.0) continue;

    //in case not all towers show up, assume they are 0
    double fullDetectorTowers[NETA_TOWERS][NPHI_TOWERS]; //[eta][phi]
    for(int i = 0; i < NETA_TOWERS; i++) for(int j = 0; j < NPHI_TOWERS; j++){
	fullDetectorTowers[i][j]=0;
      }

    for (int i = 0; i < n; i++)
    {
      if(ieta[i] < 0)
	fullDetectorTowers[ ieta[i]+41 ][ iphi[i]-1 ] = et[i];
      else
	fullDetectorTowers[ ieta[i]+40 ][ iphi[i]-1 ] = et[i];
    }
  
    //initialize and fill the regions from the towers
    double fullDetectorRegions[NETA_REGIONS][NPHI_REGIONS];
    for(int i = 0; i < NETA_REGIONS; i++){
      for(int j = 0; j < NPHI_REGIONS; j++){
    	fullDetectorRegions[i][j] = 0;
      }
    }
    for(int i = 0; i < NETA_TOWERS; i++){
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
    // 			   //NETA_TOWERS,0,NETA_TOWERS,NPHI_TOWERS,0,NPHI_TOWERS);
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
      double phiAverageTowers[NETA_TOWERS];
      for(int ieta_i = 0; ieta_i < NETA_TOWERS; ieta_i++){
    	phiAverageTowers[ieta_i] = 0;
    	for(int iphi_i = 0; iphi_i < NPHI_TOWERS; iphi_i++){
    	  phiAverageTowers[ieta_i] += fullDetectorTowers[ieta_i][iphi_i];
    	}
    	phiAverageTowers[ieta_i] /= numPhiTowers(ieta_i);
      }
      
      for(int ieta_i = 0; ieta_i < NETA_TOWERS; ieta_i++)
    	for(int iphi_i = 0; iphi_i < NPHI_TOWERS; iphi_i++){
    	  fullDetectorTowers[ieta_i][iphi_i] -= phiAverageTowers[ieta_i];
    	  if(fullDetectorTowers[ieta_i][iphi_i] < 0)
    	    fullDetectorTowers[ieta_i][iphi_i] = 0;
    	}

      // for(int i = 0; i < NETA_TOWERS; i++)
      // 	for(int j = 0; j < NPHI_TOWERS; j++)
      // 	  detectormapafter->Fill(i, j, fullDetectorTowers[i][j]);

      // TCanvas *c4 = new TCanvas();
      // detectormapafter->Draw("Lego2");
    }

    if(PHI_AVERAGE)
    {
      double phiAverageRegions[NETA_REGIONS];
      for(int ieta_i = 0; ieta_i < NETA_REGIONS; ieta_i++){
    	phiAverageRegions[ieta_i] = 0;
    	for(int iphi_i = 0; iphi_i < NPHI_REGIONS; iphi_i++){
    	  phiAverageRegions[ieta_i] += fullDetectorRegions[ieta_i][iphi_i];
    	}
    	phiAverageRegions[ieta_i] /= NPHI_REGIONS;
      }
      
      for(int ieta_i = 0; ieta_i < NETA_REGIONS; ieta_i++)
    	for(int iphi_i = 0; iphi_i < NPHI_REGIONS; iphi_i++){
    	  fullDetectorRegions[ieta_i][iphi_i] -= phiAverageRegions[ieta_i];
    	  if(fullDetectorRegions[ieta_i][iphi_i] < 0)
    	    fullDetectorRegions[ieta_i][iphi_i] = 0;
    	}

      // for(int i = 0; i < NETA_REGIONS; i++)
      // 	for(int j = 0; j < NPHI_REGIONS; j++)
      // 	  detectormapafter->Fill(i, j, fullDetectorRegions[i][j]);

      // TCanvas *c4 = new TCanvas();
      // detectormapafter->Draw("Lego2");
    }

    TowerJet *highestTowerJet = findTowerJet(fullDetectorTowers,
					     CIRCULAR_JETS,
					     JET_DIAMETER);
    RegionJet *highestRegionJet = findRegionJet(fullDetectorRegions);

    for(int i = 0; i < 1; i ++)
    {
      double uncoTowerEt, uncoRegionEt;
      if(DO_JET_ENERGY_CORRECTIONS)
      {
	int correctionBin =
	  towerL1JetEnergyCorrection->FindBin(highestTowerJet[i].sumEt,
					      highestTowerJet[i].eta);
	double correctionFactor =
	  towerL1JetEnergyCorrection->GetBinContent(correctionBin);
	uncoTowerEt = highestTowerJet[i].sumEt;
	highestTowerJet[i].sumEt /= correctionFactor;

	correctionBin =
	  regionL1JetEnergyCorrection->FindBin(highestRegionJet[i].sumEt,
					       highestRegionJet[i].eta);
	correctionFactor =
	  regionL1JetEnergyCorrection->GetBinContent(correctionBin);
	uncoRegionEt = highestRegionJet[i].sumEt;
	highestRegionJet[i].sumEt /= correctionFactor;
      }
      // matchedTowerJets->Fill(
      // 	highestTowerJet[i].phi,
      // 	highestTowerJet[i].realPhi,
      // 	highestTowerJet[i].eta,
      // 	highestTowerJet[i].realEta,
      // 	highestTowerJet[i].sumEt,
      // 	uncoTowerEt,
      // 	fjet->jteta[0],
      // 	fjet->jtphi[0],
      // 	fjet->jtpt[0]
      // 	);

      // matchedRegionJets->Fill(
      // 	highestRegionJet[i].phi,
      // 	highestRegionJet[i].realPhi,
      // 	highestRegionJet[i].eta,
      // 	highestRegionJet[i].realEta,
      // 	highestRegionJet[i].sumEt,
      // 	uncoRegionEt,
      // 	fjet->jteta[0],
      // 	fjet->jtphi[0],
      // 	fjet->jtpt[0]
      // 	);


      max_towerjet_energy->Fill(highestTowerJet[i].sumEt);
      max_regionjet_energy->Fill(highestRegionJet[i].sumEt);

      // max_regionjet_location->Fill(highestRegionJet[i].realEta);
      // max_towerjet_location->Fill(highestTowerJet[i].realEta);
    }

    if(break_early && (evts > total_events)) break;
    evts++;
  }
  
  efficiency_curve_tower = new TH1D("efficiency_curve_tower",
  				    "Towerjet Efficiency",
  				    NBINS,0,MAX_EN);
  efficiency_curve_region = new TH1D("efficiency_curve_region",
  				     "Reigonjet Efficiency",
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
  // max_towerjet_energy->SetXTitle("GeV");
  // max_towerjet_energy->SetYTitle("Counts");
  // max_towerjet_energy->SetLineColor(kRed);
  
  // max_regionjet_energy->SetTitle("max_regionjet_energy");
  // max_regionjet_energy->SetXTitle("GeV");
  // max_regionjet_energy->SetYTitle("Counts");
  // max_regionjet_energy->SetLineColor(kBlue);
  
  // max_towerjet_energy->Draw();
  // max_regionjet_energy->Draw("same");
  
  // TCanvas *c2 = new TCanvas();
  // max_towerjet_location->SetLineColor(kRed);
  // max_towerjet_location->Draw();

  // max_regionjet_location->SetLineColor(kBlue);
  // max_regionjet_location->Draw("same");

  // TCanvas *c3 = new TCanvas();
  // efficiency_curve_tower->SetTitle("RecHit Tower Jets");
  // efficiency_curve_tower->SetXTitle("L1 Threshold (GeV)");
  // efficiency_curve_tower->SetYTitle("L1 Accept Fraction");
  // efficiency_curve_tower->SetLineColor(kRed);

  // efficiency_curve_region->SetXTitle("Threshold (GeV)");
  // efficiency_curve_region->SetYTitle("Fraction of passing events");
  // efficiency_curve_region->SetLineColor(kBlue);

  // efficiency_curve_tower->Draw();
  // efficiency_curve_region->Draw("same");

  // avg_energy_eta->Divide(num_hits_eta);
  // avg_energy_eta->Draw();

  // outf->cd();
  // matchedTowerJets->Write();
  // matchedRegionJets->Write();
  // outf->Close();

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
  
  if(aeta < 1.785000-epsilon)
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
  else if (aeta < 4.802500-epsilon)
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
  
  if(aeta < 1.785000-epsilon)
  {
    for(int i = 0; i < 36; i++)
    {
      if(fabs(aphi - HBphiBounds[i]) < epsilon)
	return(35 + sign*i + plus);
    }
  }
  else if (aeta < 4.802500-epsilon)
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
