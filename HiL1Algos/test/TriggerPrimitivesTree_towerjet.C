#define TriggerPrimitivesTree_towerjet_cxx
#include "TriggerPrimitivesTree_towerjet.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>


typedef struct{
  int eta_center;
  int phi_center;
  int sumEt;
} towerJet;

TH1D* TriggerPrimitivesTree_towerjet::Loop(int total_events, 
				       int threshhold,
				       bool PHI_AVERAGE,
				       bool cut_noise_events)
{
  const int NBINS = 256;
  const int MAX_EN = 512;
  const int NETA = 88;
  const int NPHI = 72;
  const int JET_RADIUS = 6;
  const int JET_DISTANCE_2 = (JET_RADIUS-1)*(JET_RADIUS-1) +
    (JET_RADIUS-1)*(JET_RADIUS-1); 
  const bool CIRCULAR_JETS = false; //otherwise square jets

  if (fChain == 0) return(0);
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  TH1D *max_towerjet_energy;
  TH1D *efficiency_curve;
  TH2I *max_towerjet_location;

  // TH2I *detectormap;
  // detectormap = new TH2I("detectormap",
  // 			 "Detector Map",
  // 			 NETA,0,NETA,NPHI,0,NPHI);
  // detectormap->SetXTitle("#eta");
  // detectormap->SetYTitle("#phi");
  
  // TH2I *detectormapafter;
  // detectormapafter = new TH2I("detectormapafter",
  // 			 "Detector Map After Subtraction",
  // 			 NETA,0,NETA,NPHI,0,NPHI);
  // detectormapafter->SetXTitle("#eta");
  // detectormapafter->SetYTitle("#phi");
  
  max_towerjet_energy = new TH1D("max_towerjet_energy",
				 "Maximum towerjet energy for each event",
				 NBINS,0,MAX_EN);
  
  max_towerjet_location = new TH2I("max_towerjet_location",
				   "Location of max towerjet for each event",
				   NETA,0,NETA,NPHI,0,NPHI);
  

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
    
    double fulldetector[NETA][NPHI]; //[eta][phi]

    //------Fills in the phi-eta matrix for total Et values using eta and phi indexes------
    //Stolen from Doga
    for (int i=0; i<hcalDetectorMapSize;i++){
      if(hcalEtaIndex[i]<0 && hcalEtaIndex[i]>-29){
	for (int j=0;j<ecalDetectorMapSize;j++){
	  if(ecalEtaIndex[j]==hcalEtaIndex[i] && ecalPhiIndex[j]==hcalPhiIndex[i]){
	    int towertotal=hcalEt[i]+ecalEt[j];
	    fulldetector[hcalEtaIndex[i]+28+16][hcalPhiIndex[i]-1]=towertotal;
	    break;
	  }
	}
      }
      if(hcalEtaIndex[i]>0 && hcalEtaIndex[i]<29){
	for (int j=0;j<ecalDetectorMapSize;j++){
	  if(ecalEtaIndex[j]==hcalEtaIndex[i] && ecalPhiIndex[j]==hcalPhiIndex[i]){
	    int towertotal=hcalEt[i]+ecalEt[j];
	    fulldetector[hcalEtaIndex[i]+27+16][hcalPhiIndex[i]-1]=towertotal;
	    break;
	  }
	}
      }
      if (hcalEtaIndex[i]<-28){
	for (int k=0; k<4; k++){
	  for (int l=0; l<4; l++){
	    int towertotal=hcalEt[i]/16.0;
	    fulldetector[(hcalEtaIndex[i]+32)*4+k][hcalPhiIndex[i]-1+l]=towertotal;
	  }
	}
      }
      if (hcalEtaIndex[i]>28){
	for (int k=0; k<4; k++){
	  for (int l=0; l<4; l++){
	    int towertotal=hcalEt[i]/16.0;
	    fulldetector[(hcalEtaIndex[i]-29)*4+72+k][hcalPhiIndex[i]-1+l]=towertotal;
	  }
	}
      }
    }

    // for(int i = 0; i < NETA; i++)
    //   for(int j = 0; j < NPHI; j++)
    // 	detectormap->Fill(i, j, fulldetector[i][j]);

    // TCanvas *c0 = new TCanvas();
    // detectormap->Draw("Lego2");

    if(PHI_AVERAGE)
    {
      double phi_average[NETA];
      for(int ieta = 0; ieta < NETA; ieta++){
	phi_average[ieta] = 0;
	for(int iphi = 0; iphi < NPHI; iphi++){
	  phi_average[ieta] += fulldetector[ieta][iphi];
	}
	phi_average[ieta] /= NPHI;
      }
      
      for(int ieta = 0; ieta < NETA; ieta++)
	for(int iphi = 0; iphi < NPHI; iphi++){
	  fulldetector[ieta][iphi] -= phi_average[ieta];
	  if(fulldetector[ieta][iphi] < 0)
	    fulldetector[ieta][iphi] = 0;
	}

      // for(int i = 0; i < NETA; i++)
      // 	for(int j = 0; j < NPHI; j++)
      // 	  detectormapafter->Fill(i, j, fulldetector[i][j]);

      // TCanvas *c4 = new TCanvas();
      // detectormapafter->Draw("Lego2");
    }    

    towerJet highestJet;
    
    highestJet.sumEt = -1;
    highestJet.phi_center = -1;
    highestJet.eta_center = -1;
    
    for(int ieta = JET_RADIUS; ieta < NETA - JET_RADIUS; ieta++){
      for(int iphi = 0; iphi < NPHI; iphi++){

        towerJet temp;
	temp.sumEt = fulldetector[ieta][iphi];
	temp.eta_center = ieta;
	temp.phi_center = iphi;

	for(int ieta_i = ieta - JET_RADIUS; ieta_i < ieta + JET_RADIUS; ieta_i++)
	{
	  for(int iphi_i = iphi - JET_RADIUS; iphi_i < iphi + JET_RADIUS; iphi_i++)
	  {
	    //cut the corners off the square
	    if(CIRCULAR_JETS)
	    {
	      int distance2 = (iphi-temp.phi_center)*(iphi-temp.phi_center) +
		(ieta-temp.eta_center)*(ieta-temp.eta_center);
	      if(distance2 >= JET_DISTANCE_2)
		continue;
	    }
	    
	    int realiphi_i;
	    (iphi_i < 0) ? realiphi_i = iphi_i + NPHI : realiphi_i = iphi_i;

	    temp.sumEt += fulldetector[ieta_i][realiphi_i];
	  }
	}

	if(temp.sumEt > highestJet.sumEt)
	  highestJet = temp;
      }
    }
    
    if(highestJet.sumEt > threshhold)
    {
      max_towerjet_energy->Fill(highestJet.sumEt);
      max_towerjet_location->Fill(highestJet.eta_center, highestJet.phi_center);
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

  TCanvas *c1 = new TCanvas();
  max_towerjet_energy->SetTitle("max_towerjet_energy");
  max_towerjet_energy->SetXTitle("GeV");
  max_towerjet_energy->SetYTitle("Counts");
  max_towerjet_energy->Draw();

  TCanvas *c2 = new TCanvas();
  max_towerjet_location->SetXTitle("Eta index");
  max_towerjet_location->SetYTitle("Phi index");
  max_towerjet_location->Draw("Lego2");

  TCanvas *c3 = new TCanvas();
  efficiency_curve->SetTitle("Efficiency Curve");
  efficiency_curve->SetXTitle("Threshold (GeV)");
  efficiency_curve->SetYTitle("Fraction of passing events");
  efficiency_curve->Draw();

  return(efficiency_curve);
}
