#define TriggerPrimitivesTree_towerjet_cxx
#include "TriggerPrimitivesTree_towerjet.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>

const int NETA_TOWERS = 88;
#include "FindTowerJet.C"

TH1D* TriggerPrimitivesTree_towerjet::Loop(int total_events, 
				       int threshhold,
				       bool PHI_AVERAGE,
				       bool cut_noise_events)
{
  const int NBINS = 300;
  const int MAX_EN = 600;

  const int JET_DIAMETER = 7;
  const bool CIRCULAR_JETS = true; //otherwise square jets

  if (fChain == 0) return(0);
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  TH1D *max_towerjet_energy;
  TH1D *efficiency_curve;
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
    
    double fullDetectorTowers[NETA_TOWERS][NPHI_TOWERS]; //[eta][phi]
    for(int i = 0; i < NETA_TOWERS; i++)
      for(int j = 0; j < NPHI_TOWERS; j++)
	fullDetectorTowers[i][j]=0;
    

    //------Fills in the phi-eta matrix for total Et values using eta and phi indexes------
    //Stolen from Doga
    for (int i=0; i<hcalDetectorMapSize;i++){
      if(hcalEtaIndex[i]<0 && hcalEtaIndex[i]>-29){
	for (int j=0;j<ecalDetectorMapSize;j++){
	  if(ecalEtaIndex[j]==hcalEtaIndex[i] && ecalPhiIndex[j]==hcalPhiIndex[i]){
	    int towertotal=hcalEt[i]+ecalEt[j];
	    fullDetectorTowers[hcalEtaIndex[i]+28+16][hcalPhiIndex[i]-1]=towertotal;
	    break;
	  }
	}
      }
      if(hcalEtaIndex[i]>0 && hcalEtaIndex[i]<29){
	for (int j=0;j<ecalDetectorMapSize;j++){
	  if(ecalEtaIndex[j]==hcalEtaIndex[i] && ecalPhiIndex[j]==hcalPhiIndex[i]){
	    int towertotal=hcalEt[i]+ecalEt[j];
	    fullDetectorTowers[hcalEtaIndex[i]+27+16][hcalPhiIndex[i]-1]=towertotal;
	    break;
	  }
	}
      }
      if (hcalEtaIndex[i]<-28){
	for (int k=0; k<4; k++){
	  for (int l=0; l<4; l++){
	    double towertotal=hcalEt[i]/16.0;
	    fullDetectorTowers[(hcalEtaIndex[i]+32)*4+k][hcalPhiIndex[i]-1+l]=towertotal;
	  }
	}
	// double towertotal=hcalEt[i];
	// fullDetectorTowers[(hcalEtaIndex[i]+32)*4][hcalPhiIndex[i]-1]=towertotal;
      }
      if (hcalEtaIndex[i]>28){
	for (int k=0; k<4; k++){
	  for (int l=0; l<4; l++){
	    double towertotal=hcalEt[i]/16.0;
	    fullDetectorTowers[(hcalEtaIndex[i]-29)*4+72+k][hcalPhiIndex[i]-1+l]=towertotal;
	  }
	}
	// double towertotal=hcalEt[i];
	// fullDetectorTowers[(hcalEtaIndex[i]-29)*4+72][hcalPhiIndex[i]-1]=towertotal;
      }
    }

    // for(int i = 0; i < NETA_TOWERS; i++)
    //   for(int j = 0; j < NPHI_TOWERS; j++)
    // 	detectormap->Fill(i, j, fullDetectorTowers[i][j]);

    // TCanvas *c0 = new TCanvas();
    // detectormap->Draw("Lego2");

    if(PHI_AVERAGE)
    {
      double phiAverageTowers[NETA_TOWERS];
      for(int ieta = 0; ieta < NETA_TOWERS; ieta++){
	phiAverageTowers[ieta] = 0;
	for(int iphi = 0; iphi < NPHI_TOWERS; iphi++){
	  phiAverageTowers[ieta] += fullDetectorTowers[ieta][iphi];
	}
	phiAverageTowers[ieta] /= NPHI_TOWERS;
      }
      
      for(int ieta = 0; ieta < NETA_TOWERS; ieta++)
	for(int iphi = 0; iphi < NPHI_TOWERS; iphi++){
	  fullDetectorTowers[ieta][iphi] -= phiAverageTowers[ieta];
	  if(fullDetectorTowers[ieta][iphi] < 0)
	    fullDetectorTowers[ieta][iphi] = 0;
	}

      // for(int i = 0; i < NETA_TOWERS; i++)
      // 	for(int j = 0; j < NPHI_TOWERS; j++)
      // 	  detectormapafter->Fill(i, j, fullDetectorTowers[i][j]);

      // TCanvas *c4 = new TCanvas();
      // detectormapafter->Draw("Lego2");
    }    

    TowerJet *highestJet = findTowerJet(fullDetectorTowers, CIRCULAR_JETS, JET_DIAMETER);
    
    if(highestJet[0].sumEt > threshhold)
    {
      max_towerjet_energy->Fill(highestJet[0].sumEt);
      // max_towerjet_location->Fill(highestJet.eta_center, highestJet.phi_center);
    }
  }
  
  efficiency_curve = new TH1D("efficiency_curve","Fraction of passing events versus threshold",
			      NBINS,0,MAX_EN);
  double total_integral = max_towerjet_energy->Integral();

  for(int i = 0; i < NBINS; i++)
  {
    double j = (double)i*(double)MAX_EN/(double)NBINS;
    double integral = max_towerjet_energy->Integral(i, NBINS);
    efficiency_curve->Fill(j, (double)integral/total_integral);      
  }

  // TCanvas *c1 = new TCanvas();
  max_towerjet_energy->SetTitle("max_towerjet_energy");
  max_towerjet_energy->SetXTitle("GeV");
  max_towerjet_energy->SetYTitle("Counts");
  // max_towerjet_energy->Draw();

  // TCanvas *c2 = new TCanvas();
  // max_towerjet_location->SetXTitle("Eta index");
  // max_towerjet_location->SetYTitle("Phi index");
  // max_towerjet_location->Draw("Lego2");

  // TCanvas *c3 = new TCanvas();
  efficiency_curve->SetTitle("Efficiency Curve");
  efficiency_curve->SetXTitle("Threshold (GeV)");
  efficiency_curve->SetYTitle("Fraction of passing events");
  // efficiency_curve->Draw();

  return(efficiency_curve);
}
