#define TriggerPrimitivesTree_tower_cxx
#include "TriggerPrimitivesTree_tower.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>


typedef struct{
  int eta0;
  int phi0;
  int eta1;
  int phi1;
  int sumEt;
} highPtTrack;

TH1D* TriggerPrimitivesTree_tower::Loop(int total_events, 
				       int threshhold,
				       bool PHI_AVERAGE,
				       bool cut_noise_events)
{
  const int NBINS = 64;
  const int MAX_EN = 128;
  const int NETA = 88;
  const int NPHI = 72;

  if (fChain == 0) return(0);
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  TH1D *max_highPtTrack_energy;
  TH1D *efficiency_curve;
  //TH2I *max_highPtTrack_location;

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
  
  max_highPtTrack_energy = new TH1D("max_highPtTrack_energy",
			    "Maximum highPtTrack energy for each event",
			    NBINS,0,MAX_EN);
  
  // max_highPtTrack_location = new TH2I("max_highPtTrack_location",
  // 				      "Location of max highPtTrack for each event",
  // 				      NETA,0,NETA,NPHI,0,NPHI);
  

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

    highPtTrack highPtTrack1;
    
    highPtTrack1.sumEt = -1;
    highPtTrack1.phi0 = -1;
    highPtTrack1.eta0 = -1;
    highPtTrack1.phi1 = -1;
    highPtTrack1.eta1 = -1;
    
    for(int ieta = 0; ieta < NETA; ieta++){
      for(int iphi = 0; iphi < NPHI; iphi++){

        highPtTrack temp, subTower;
	temp.sumEt = fulldetector[ieta][iphi];
	temp.eta0 = ieta;
	temp.phi0 = iphi;

	int plusPhi, minusPhi;
	if(iphi == 0) minusPhi = NPHI-1;
	else minusPhi = iphi -1;
	if(iphi == NPHI -1) plusPhi = 0;
	else plusPhi = iphi + 1;

	int max_cluster = -1;
	int index = -1;
	int phi1 = -1;
	
	int starti = 0; if(ieta == 0) starti = 3;
	int endi = 9; if(ieta == NETA -1) endi = 6;
	for(int i = starti; i < endi; i++)
	{
	  int phi_i;
	  switch(i%3)
	  {
	  case 0:
	    phi_i = minusPhi;
	    break;
	  case 1:
	    phi_i = iphi;
	    break;
	  case 2:
	    phi_i = plusPhi;
	    break;
	  }
	  if(max_cluster < fulldetector[ieta-1 +i/3][phi_i])
	  {
	    max_cluster = fulldetector[ieta-1 +i/3][phi_i];
	    index = i;
	    phi1 = phi_i;
	  }
	}
	
	subTower.sumEt = max_cluster;
	subTower.eta1 = (ieta-1) + (index / 3);
	subTower.phi1 = phi1;    
	
	//only consider the subtowers which are less than the primary tower
	if(subTower.sumEt < temp.sumEt)
	{
	  temp.sumEt += subTower.sumEt;
	  temp.eta1 = subTower.eta1;
	  temp.phi1 = subTower.phi1;
	}
	if(temp.sumEt > highPtTrack1.sumEt)
	  highPtTrack1 = temp;
      }
    }
    
    if(highPtTrack1.sumEt > threshhold)
    {
      max_highPtTrack_energy->Fill(highPtTrack1.sumEt);
      // max_highPtTrack_location->Fill(highPtTrack1.eta0, highPtTrack1.phi0);
    }
  }
  
  efficiency_curve = new TH1D("efficiency_curve","Fraction of passing events versus threshold",
			      NBINS,0,MAX_EN);
  double total_integral = max_highPtTrack_energy->Integral();

  for(int i = 0; i < NBINS; i++)
  {
    double j = (double)i*(double)MAX_EN/(double)NBINS;
    double integral = max_highPtTrack_energy->Integral(i, NBINS);
    efficiency_curve->Fill(j, (double)integral/total_integral);      
  }

  // TCanvas *c1 = new TCanvas();
  // max_highPtTrack_energy->SetTitle("max_highPtTrack_energy");
  max_highPtTrack_energy->SetXTitle("GeV");
  max_highPtTrack_energy->SetYTitle("Counts");
  //max_highPtTrack_energy->Draw();

  // TCanvas *c2 = new TCanvas();
  // max_highPtTrack_location->SetXTitle("Eta index");
  // max_highPtTrack_location->SetYTitle("Phi index");
  // max_highPtTrack_location->Draw("Lego2");

  // TCanvas *c3 = new TCanvas();
  // efficiency_curve->SetTitle("Efficiency Curve");
  efficiency_curve->SetXTitle("Threshold (GeV)");
  efficiency_curve->SetYTitle("Fraction of passing events");
  //efficiency_curve->Draw();

  return(efficiency_curve);
}
