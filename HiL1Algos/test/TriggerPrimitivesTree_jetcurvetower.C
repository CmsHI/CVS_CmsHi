#define TriggerPrimitivesTree_jetcurvetower_cxx
#include "TriggerPrimitivesTree_jetcurvetower.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TProfile.h>
#include <iostream>
#include <sstream>

using namespace std;

typedef struct{
  int eta_center;
  int phi_center;
  int sumEt;
} towerJet;

TH1D* TriggerPrimitivesTree_jetcurvetower::Loop(int total_events,
					   int threshold,
					   bool PHI_AVERAGE,
					   int minCentBin,
					   int maxCentBin)
{
  TH1::SetDefaultSumw2();
  
  //   In a ROOT session, you can do:
  //      Root > .L TriggerPrimitivesTree.C
  //      Root > TriggerPrimitivesTree t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return(0);
  
  Long64_t nentries = fChain->GetEntriesFast();

  const int NBINS = 64;
  const int MAX_EN = 128;
  const int NETA = 88;
  const int NPHI = 72;
  const int JET_RADIUS = 6;
  const int JET_DISTANCE_2 = (JET_RADIUS-1)*(JET_RADIUS-1) +
    (JET_RADIUS-1)*(JET_RADIUS-1); 
  const bool CIRCULAR_JETS = false; //otherwise square jets
  
  TH1D* jet_curve;
  TH1I* total_in_bin;

  jet_curve = new TH1D("jet_curve","Jet Curve, Tower Level",
		       NBINS,0,MAX_EN);
  total_in_bin = new TH1I("total_in_bin","total_in_bin",
			  NBINS,0,MAX_EN);

  int evts = 0;
  bool break_early = total_events != -1;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    
    fhlt->GetEntry(jentry);
    fhiinfo->GetEntry(jentry);

    // If the event has halo, no tracks, or energy less than 3GeV in
    // both forward calorimeters than skip it.
    if( !(!(fhlt->L1Tech_BSC_halo_beam2_inner_v0 ||
	    fhlt->L1Tech_BSC_halo_beam2_outer_v0 ||
	    fhlt->L1Tech_BSC_halo_beam1_inner_v0 ||
	    fhlt->L1Tech_BSC_halo_beam1_outer_v0 )
	  && fhiinfo->hiNtracks>0
	  && fhiinfo->hiHFplus>3
	  && fhiinfo->hiHFminus>3))
      continue;

    fjet->GetEntry(jentry);
    // If there are no jets in the event skip it.
    if (fjet->nref <= 0) continue;
    float_t realJetPt = fjet->jtpt[0];
    int centBin = fhiinfo->hiBin;
    if(centBin < minCentBin || centBin > maxCentBin) continue;

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
    
    if(highestJet.sumEt > threshold)
      jet_curve->Fill(realJetPt);

    total_in_bin->Fill(realJetPt);
  }
  
  TCanvas *plot;

  //stringstream filename;
  //filename << "jetto_" << threshold << ".gif";
  plot = new TCanvas();
  //jet_curve->Divide(total_in_bin);
  jet_curve->Divide(jet_curve, total_in_bin, 1, 1, "b");
  jet_curve->SetXTitle("HLT Jet Pt (GeV)");
  jet_curve->SetYTitle("Fraction Accepted");

  jet_curve->GetYaxis()->SetRangeUser(0,1);
  jet_curve->Draw("E");

//plots[i]->SaveAs(filename.str().c_str());
  
  return(jet_curve);
}
