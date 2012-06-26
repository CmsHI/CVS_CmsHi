#define TriggerPrimitivesTree_alex_cxx
#include "TriggerPrimitivesTree_alex.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>


typedef struct{
  int eta;
  int phi;
  int et;
} jet;

int sort_func_jet(const void *a, const void *b);

void print_jets(jet *clusters, int jet_length);

TH1D* TriggerPrimitivesTree_alex::Loop(int total_events, 
				       int threshhold,
				       bool PHI_AVERAGE,
				       bool cut_noise_events)
{
  const int NBINS = 200;
  const int MAX_EN = 600;
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
  
  TH1D *max_jet_energy;
  TH1D *efficiency_curve;
  //TH2I *max_jet_location;

  max_jet_energy = new TH1D("max_jet_energy",
			    "Maximum jet energy for each event",
			    NBINS,0,MAX_EN);
  
  // max_jet_location = new TH2I("max_jet_location","Location of max jet for each event",
  // 			      22,0,22,18,0,18);
  

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
    
    double fulldetector[22][18]; //[eta][phi]
    int RCTs[18][11][2]; //[region #][eta][phi]
    for(int i = 0; i < numRegions; i++)
    {
      fulldetector[caloRegionEtaIndex[i]][caloRegionPhiIndex[i]] = caloRegionEt[i];
      int rctnum = (9*(caloRegionEtaIndex[i]/11)) + (caloRegionPhiIndex[i]/2);
      RCTs[rctnum][caloRCTRegionEtaIndex[i]][caloRCTRegionPhiIndex[i]] = caloRegionEt[i];
    }


      
    if(PHI_AVERAGE)
    {
      double phi_average[22];
      for(int ieta = 0; ieta < 22; ieta++){
	phi_average[ieta] = 0;
	for(int iphi = 0; iphi < 18; iphi++){
	  phi_average[ieta] += fulldetector[ieta][iphi];
	}
	phi_average[ieta] /= 18;
      }
      
      for(int ieta = 0; ieta < 22; ieta++)
	for(int iphi = 0; iphi < 18; iphi++){
	  fulldetector[ieta][iphi] -= phi_average[ieta];
	  if(fulldetector[ieta][iphi] < 0)
	    fulldetector[ieta][iphi] = 0;
	}
    }

    jet jets[18][2][3]; //[rct #][phi][jet #]
    
    for(int i = 0; i < 18; i++)
    {
      for(int j = 0; j < 2; j++) 
	for(int k = 0; k < 3; k++)
	{
	  jets[i][j][k].et = -1;
	  jets[i][j][k].phi = -1;
	  jets[i][j][k].eta = -1;
	}
    }
    
    for(int ieta = 1; ieta < 21; ieta++)
      for(int iphi = 0; iphi < 18; iphi++){
	
	int rctnum = (9*(ieta/11))+(iphi/2);
	int rctphi = iphi%2;
	
	int plusPhi =  (iphi != 17) ? iphi + 1: 0;
	int minusPhi =  (iphi != 0) ? iphi - 1: 17;

	int cluster = fulldetector[ieta-1][minusPhi] +
	  fulldetector[ieta-1][iphi] +		
	  fulldetector[ieta-1][plusPhi] +		
	  fulldetector[ieta][minusPhi] +		
	  fulldetector[ieta][iphi] +		
	  fulldetector[ieta][plusPhi] +		
	  fulldetector[ieta+1][minusPhi] +		
	  fulldetector[ieta+1][iphi] +		
	  fulldetector[ieta+1][plusPhi];

	//if the region is a local maximum...
	if((fulldetector[ieta][iphi] >= fulldetector[ieta-1][minusPhi]) && 
	   (fulldetector[ieta][iphi] >= fulldetector[ieta-1][iphi]) &&	
	   (fulldetector[ieta][iphi] >= fulldetector[ieta-1][plusPhi]) && 
	   (fulldetector[ieta][iphi] >= fulldetector[ieta][minusPhi]) && 
	   (fulldetector[ieta][iphi] >= fulldetector[ieta][plusPhi]) &&	
	   (fulldetector[ieta][iphi] >= fulldetector[ieta+1][minusPhi]) &&
	   (fulldetector[ieta][iphi] >= fulldetector[ieta+1][iphi]) &&	
	   (fulldetector[ieta][iphi] >= fulldetector[ieta+1][plusPhi]))
	{
	  // and if the cluster is bigger than one of the jets
	  // then add the cluster to the list of jets.
	  if(cluster >= jets[rctnum][rctphi][0].et)
	  {
	    jets[rctnum][rctphi][2] = jets[rctnum][rctphi][1];
	    jets[rctnum][rctphi][1] = jets[rctnum][rctphi][0];
	    jets[rctnum][rctphi][0].et = cluster;
	    jets[rctnum][rctphi][0].eta = ieta;
	    jets[rctnum][rctphi][0].phi = iphi;
	  }
	  else if (cluster >= jets[rctnum][rctphi][1].et)
	  {
	    jets[rctnum][rctphi][2] = jets[rctnum][rctphi][1];
	    jets[rctnum][rctphi][1].et = cluster;
	    jets[rctnum][rctphi][1].eta = ieta;
	    jets[rctnum][rctphi][1].phi = iphi;
	  }
	  else if (cluster >= jets[rctnum][rctphi][2].et)
	  {
	    jets[rctnum][rctphi][2].et = cluster;
	    jets[rctnum][rctphi][2].eta = ieta;
	    jets[rctnum][rctphi][2].phi = iphi;
	  }	
	}
      }
    
    jet *head = &jets[0][0][0];
    
    qsort(head, 18*2*3, sizeof(jet), sort_func_jet);
    
    if(head[0].et > threshhold)
    {
      max_jet_energy->Fill(head[0].et);
      //max_jet_location->Fill(head[0].eta, head[0].phi);
      //max_jet_location->Fill(head[0].eta, head[0].phi, head[0].et);
    }
  }
  
  efficiency_curve = new TH1D("efficiency_curve","Fraction of passing events versus threshold",
			      NBINS,0,MAX_EN);
  double total_integral = max_jet_energy->Integral();

  for(int i = 0; i < NBINS; i++)
  {
    double j = (double)i*(double)MAX_EN/(double)NBINS;
    double integral = max_jet_energy->Integral(i, NBINS);
    efficiency_curve->Fill(j, (double)integral/total_integral);      
  }
    
  //max_jet_energy->SetTitle("max_jet_energy");
  max_jet_energy->SetXTitle("Compressed Et");
  max_jet_energy->SetYTitle("Counts");

  // max_jet_location->SetXTitle("Eta index");
  // max_jet_location->SetYTitle("Phi index");
  // max_jet_location->Draw("Lego2");

  //efficiency_curve->SetTitle("Efficiency Curve");
  efficiency_curve->SetXTitle("L1 Jet Threshold (GeV)");
  efficiency_curve->SetYTitle("Fraction of passing events");

  return(efficiency_curve);
}

int sort_func_jet(const void *a, const void *b) 
{ 
  jet *ia = (jet *)a;
  jet *ib = (jet *)b;
  return (int)(ib->et - ia->et);
} 

void print_jets(jet *clusters, int jet_length)
{
  cout << "List of jets:" << endl;
  for(int i = 0; i < jet_length; i++)
  {
    cout << clusters[i].et << " " << clusters[i].eta << " " << clusters[i].phi << endl;
  }
}
