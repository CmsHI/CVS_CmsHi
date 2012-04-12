#define TriggerPrimitivesTree_alex_cxx
#include "TriggerPrimitivesTree_alex.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

typedef struct{
  int eta;
  int phi;
  int et;
} jet;

int sort_func_jet(const void *a, const void *b);

void print_jets(jet *clusters, int jet_length);

void TriggerPrimitivesTree_alex::Loop(int total_events, 
				      int threshhold,  
				      bool SUBTRACT_RCT_MINIMUM,
				      bool SUBTRACT_RCT_AVERAGE,
				      bool SUBTRACT_ETA_AVG)
{
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
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;

//   const int total_events = 3000;
//   const int threshhold = 30;
//   const bool SUBTRACT_RCT_MINIMUM = true;
//   const bool SUBTRACT_RCT_AVERAGE = false;
  int event_should_trigger = 0;

//   TH2I *original_map = new TH2I("original_map","Detector Map before subtraction",22,0,1,18,0,1);
//   TH2I *subtracted_map = new TH2I("subtracted_map","Detector Map after subtraction",22,0,1,18,0,1);

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    // ientry = fjet->LoadTree(jentry);
    // ientry = fhlt->LoadTree(jentry);
    // ientry = fhiinfo->LoadTree(jentry);
    // ientry = fmu->LoadTree(jentry);
    if (ientry < 0) break;
    
    //! here it loads the same event from all the trees
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //fjet->GetEntry(jentry);
    //fhlt->GetEntry(jentry);
    //fhiinfo->GetEntry(jentry);
    //fmu->GetEntry(jentry);
    // if (Cut(ientry) < 0) continue;
    
//     cout<<"ecalDetectorMapSize from trigger primitives tree: "<<ecalDetectorMapSize<<endl;
//     cout<<"nref from jet tree: "<<fjet->nref<<endl;
//     cout<<"L1EtTot from hlt tree: "<<fhlt->L1EtTot<<endl;
//     cout<<"centrality bin from hieventanalyzer: "<<fhiinfo->hiBin<<endl;
//     cout<<"Glb_nptl from muon tree: "<<fmu->Glb_nptl<<endl;

//     int totalEt = 0;
//     for(int i = 0; i < numRegions; i++)
//       {
// 	totalEt += caloRegionEt[i];
//       }

//     cout << "Total calorimeter energy for event: " << totalEt << endl;

    int fulldetector[22][18]; //[eta][phi]
    int RCTs[18][11][2]; //[region #][eta][phi]
    for(int i = 0; i < numRegions; i++)
      {
	fulldetector[caloRegionEtaIndex[i]][caloRegionPhiIndex[i]] = caloRegionEt[i];
	int rctnum = (9*(caloRegionEtaIndex[i]/11))+(caloRegionPhiIndex[i]/2);
	RCTs[rctnum][caloRCTRegionEtaIndex[i]][caloRCTRegionPhiIndex[i]] = caloRegionEt[i];
      }

   //  for(int ieta = 0; ieta < 22; ieta++)
//       for(int iphi = 0; iphi < 18; iphi++){
// 	original_map->Fill(ieta,iphi,fulldetector[ieta][iphi]);
//       }
//     original_map->Draw();


    int rct_minimums[18];
    double rct_averages[18];
    for(int i = 0; i < 18; i++)
      {
	rct_minimums[i] = 256;
	rct_averages[i] = 0;

	for(int ieta = 0; ieta < 11; ieta++)
	  for(int iphi = 0; iphi < 2; iphi++){
	    if (RCTs[i][ieta][iphi] < rct_minimums[i])
	      rct_minimums[i] = RCTs[i][ieta][iphi];
	    
	    rct_averages[i] += RCTs[i][ieta][iphi];
	  }
	rct_averages[i] /= 22;
      } 

    double eta_average[22];
    for(int ieta = 0; ieta < 22; ieta++){
      eta_average[ieta] = 0;
      for(int iphi = 0; iphi < 18; iphi++){
	eta_average[ieta] += fulldetector[ieta][iphi];
      }
      eta_average[ieta] /= 18;
    }

    if(SUBTRACT_RCT_MINIMUM)
      {
	for(int ieta = 0; ieta < 22; ieta++)
	  for(int iphi = 0; iphi < 18; iphi++){
	    int rctnum = (9*(ieta/11))+(iphi/2);
	    fulldetector[ieta][iphi] -= rct_minimums[rctnum];
	  }
      }
    
    if(SUBTRACT_RCT_AVERAGE)
      {
	for(int ieta = 0; ieta < 22; ieta++)
	  for(int iphi = 0; iphi < 18; iphi++){
	    int rctnum = (9*(ieta/11))+(iphi/2);
	    fulldetector[ieta][iphi] -= rct_averages[rctnum];
	  }
      }

    if(SUBTRACT_ETA_AVG)
      {
	for(int ieta = 0; ieta < 22; ieta++)
	  for(int iphi = 0; iphi < 18; iphi++){
	    fulldetector[ieta][iphi] -= eta_average[ieta];
	  }
      }

    // for(int ieta = 0; ieta < 22; ieta++)
// 	  for(int iphi = 0; iphi < 18; iphi++){
// 	    subtracted_map->Fill(ieta,iphi,fulldetector[ieta][iphi]);
// 	  }
//      subtracted_map->Draw();
    
    jet jets[18][2][3];

    for(int i = 0; i < 18; i++) 
      for(int j = 0; j < 2; j++) 
	for(int k = 0; k < 3; k++)
	  {
	    jets[i][j][k].et = -1;
	    jets[i][j][k].phi = -1;
	    jets[i][j][k].eta = -1;
	  }

    for(int ieta = 1; ieta < 21; ieta++)
      for(int iphi = 0; iphi < 18; iphi++){
	int rctnum = (9*(ieta/11))+(iphi/2);
	int rctphi = iphi%2;
	
	int plusPhi =  (iphi != 17) ? iphi + 1: 0;
	int minusPhi =  (iphi != 0) ? iphi - 1: 17;
	
	if((fulldetector[ieta][iphi] >= fulldetector[ieta-1][minusPhi]) && 
	   (fulldetector[ieta][iphi] >= fulldetector[ieta-1][iphi]) &&	
	   (fulldetector[ieta][iphi] >= fulldetector[ieta-1][plusPhi]) && 
	   (fulldetector[ieta][iphi] >= fulldetector[ieta][minusPhi]) && 
	   (fulldetector[ieta][iphi] >= fulldetector[ieta][plusPhi]) &&	
	   (fulldetector[ieta][iphi] >= fulldetector[ieta+1][minusPhi]) &&
	   (fulldetector[ieta][iphi] >= fulldetector[ieta+1][iphi]) &&	
	   (fulldetector[ieta][iphi] >= fulldetector[ieta+1][plusPhi]))
	  {
	    
	    
	    // 	    int cluster = fulldetector[ieta-1][minusPhi] +
	    // 	      fulldetector[ieta-1][iphi] +		
	    // 	      fulldetector[ieta-1][plusPhi] +		
	    // 	      fulldetector[ieta][minusPhi] +		
	    // 	      fulldetector[ieta][iphi] +		
	    // 	      fulldetector[ieta][plusPhi] +		
	    // 	      fulldetector[ieta+1][minusPhi] +		
	    // 	      fulldetector[ieta+1][iphi] +		
	    // 	      fulldetector[ieta+1][plusPhi];
	    
	    int cluster = fulldetector[ieta][iphi];
	    
	    if(cluster >= jets[rctnum][rctphi][0].et){
	      jets[rctnum][rctphi][2] = jets[rctnum][rctphi][1];
	      jets[rctnum][rctphi][1] = jets[rctnum][rctphi][0];
	      jets[rctnum][rctphi][0].et = cluster;
	      jets[rctnum][rctphi][0].eta = ieta;
	      jets[rctnum][rctphi][0].phi = iphi;
	    } else if (cluster >= jets[rctnum][rctphi][1].et){
	      jets[rctnum][rctphi][2] = jets[rctnum][rctphi][1];
	      jets[rctnum][rctphi][1].et = cluster;
	      jets[rctnum][rctphi][1].eta = ieta;
	      jets[rctnum][rctphi][1].phi = iphi;
	    } else if (cluster >= jets[rctnum][rctphi][2].et){
	      jets[rctnum][rctphi][2].et = cluster;
	      jets[rctnum][rctphi][2].eta = ieta;
	      jets[rctnum][rctphi][2].phi = iphi;
	    }	
	  }
	
      }
    


//     if(SUBTRACT_RCT_MINIMUM)
//       {
// 	for(int i = 0; i < 18; i++) 
// 	  for(int j = 0; j < 2; j++) 
// 	    for(int k = 0; k < 3; k++)
// 	      {
// 		jets[i][j][k].et -= rct_minimums[i];
// 	      }
//       }

//     if(SUBTRACT_RCT_AVERAGE)
//       {
// 	for(int i = 0; i < 18; i++) 
// 	  for(int j = 0; j < 2; j++) 
// 	    for(int k = 0; k < 3; k++)
// 	      {
// 		jets[i][j][k].et -= rct_averages[i];
// 	      }
//       }


    jet *head = &jets[0][0][0];

    //print_jets(head, 18*2*3);

    qsort(head, 18*2*3, sizeof(jet), sort_func_jet);

    if(jentry == total_events - 1)
      print_jets(head, 18*2*3);
    
    //cout << "Biggest jet for event: " << head[0].et << endl;

    if(head[0].et > threshhold)
      event_should_trigger++;

    if(jentry > total_events - 2) break;
  }
  cout << "Percentage of passing events: " << ((double)event_should_trigger)/total_events << endl;
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
