#define TriggerPrimitivesTree_jetcurve_centrality_cxx
#include "TriggerPrimitivesTree_jetcurve_centrality.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TProfile.h>
#include <iostream>
#include <sstream>


typedef struct{
  int eta;
  int phi;
  int et;
} jet;

int sort_func_jet(const void *a, const void *b);

void print_jets(jet *clusters, int jet_length);

TH1D* TriggerPrimitivesTree_jetcurve_centrality::Loop(int threshold,
				      enum SUBTRACT_ALGORITHM algorithm)
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
  
  const int nbins = 30; //number of jet pt bins from 0 to MAX_JET_EN
  const int MAX_JET_EN = 300;
  const int cenhists = 1;
  const int etabins = 1;
  
  TH1D* jet_curve[cenhists][etabins];
  TH1I* total_in_bin[cenhists][etabins];

  string method;
  switch(algorithm)
  {
  case RCT_MINIMUM:
    method = "minsub";
    break;
  case RCT_AVERAGE:
    method = "avgsub";
    break;
  case PHI_AVERAGE:
    method = "phisub";
    break;
  case MIN_3X3:
    method = "3x3sub";
    break;
  default:
    method = "nosub";
    break;
  }

  double centrality[cenhists+1];
  for(int i = 0; i <= cenhists; i++)
    centrality[i] = (double)i/cenhists*100.;
  // double mineta[etabins] = {-4.5, -3.6, -2, -1, 1, 2, 3.6};
  // double maxeta[etabins] = {-3.6, -2, -1, 1, 2, 3.6, 4.5};

  for(int i = 0; i < cenhists; i++)
  {
    for(int j = 0; j < etabins; j++)
    {
      stringstream name1,name2,name3;
      name1 << method
	    << ". Threshold:" << threshold
	    << ". Centrality:"<< centrality[i] << "% to " << centrality[i+1] << "%";
      //<< ". Eta: " << mineta[j] << " to " << maxeta[j];
      name2 << "total_in_bin_" << i << j;
      name3 << "jet_curve_centrality_"<< i << j;
      jet_curve[i][j] = new TH1D(name3.str().c_str(), name1.str().c_str(),
				 nbins,0, MAX_JET_EN);
      total_in_bin[i][j] = new TH1I(name2.str().c_str(),name2.str().c_str(),
				    nbins,0, MAX_JET_EN);
    }
  }

  int evts = 0;  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    
    fhlt->GetEntry(jentry);
    fhiinfo->GetEntry(jentry);

    // If the event has halo, no tracks, or energy less than 3GeV in
    // both forward calorimeters than skip it.
    if(!(
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

    fjet->GetEntry(jentry);
    // If there are no jets in the event skip it.
    if (fjet->nref <= 0) continue;
    // cut some noise events from the jet sample
    if (fjet->jtpt[0] < 95) continue;

    evts++;

    float_t realJetPt = fjet->jtpt[0];
    
    int jetCentBin = fhiinfo->hiBin;
    int jetCentHist = jetCentBin*cenhists/40;
    
    float_t realJetEta = fjet->jteta[0];
    if( realJetEta < -1 || realJetEta > 1) continue;
    int jetEtaBin = 0;
    // if(realJetEta < -3.6) jetEtaBin = 0;
    // else if(realJetEta < -2) jetEtaBin = 1;
    // else if(realJetEta < -1) jetEtaBin = 2;
    // else if(realJetEta < 1) jetEtaBin = 3;
    // else if(realJetEta < 2) jetEtaBin = 4;
    // else if(realJetEta < 3.6) jetEtaBin = 5;
    // else jetEtaBin = 6;
    
    fChain->GetEntry(jentry);

    double fulldetector[22][18]; //[eta][phi]
    int RCTs[18][11][2]; //[region #][eta][phi]
    for(int i = 0; i < numRegions; i++)
    {
      fulldetector[caloRegionEtaIndex[i]][caloRegionPhiIndex[i]] = caloRegionEt[i];
      int rctnum = (9*(caloRegionEtaIndex[i]/11)) + (caloRegionPhiIndex[i]/2);
      RCTs[rctnum][caloRCTRegionEtaIndex[i]][caloRCTRegionPhiIndex[i]] = caloRegionEt[i];
    }

    switch(algorithm)
    {
    case RCT_MINIMUM:
      int rct_minimums[18];
      for(int i = 0; i < 18; i++)
      {
	rct_minimums[i] = 500;
	for(int ieta = 0; ieta < 11; ieta++)
	  for(int iphi = 0; iphi < 2; iphi++){
	    if (RCTs[i][ieta][iphi] < rct_minimums[i])
	      rct_minimums[i] = RCTs[i][ieta][iphi];
	  }
      }
      
      for(int ieta = 0; ieta < 22; ieta++)
	for(int iphi = 0; iphi < 18; iphi++){
	  int rctnum = (9*(ieta/11))+(iphi/2);
	  fulldetector[ieta][iphi] -= rct_minimums[rctnum];
	  if(fulldetector[ieta][iphi] < 0)
	    fulldetector[ieta][iphi] = 0;
	}
      break;
      
    case RCT_AVERAGE:
      double rct_averages[18];
      for(int i = 0; i < 18; i++)
      {
	rct_averages[i] = 0;
	
	for(int ieta = 0; ieta < 11; ieta++)
	  for(int iphi = 0; iphi < 2; iphi++){
	    rct_averages[i] += RCTs[i][ieta][iphi];
	  }
	rct_averages[i] /= 22;
      } 
      
      for(int ieta = 0; ieta < 22; ieta++)
	for(int iphi = 0; iphi < 18; iphi++){
	  int rctnum = (9*(ieta/11))+(iphi/2);
	  fulldetector[ieta][iphi] -= rct_averages[rctnum];
	  if(fulldetector[ieta][iphi] < 0)
	    fulldetector[ieta][iphi] = 0;
	}
      break;
      
    case PHI_AVERAGE:

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
      break;
      
    default:
      break;
    }    

    jet jets[18][2][3]; //[rct #][phi][jet #]
    int min_3x3[18];    //[rct #]    
    for(int i = 0; i < 18; i++)
    {
      for(int j = 0; j < 2; j++) 
	for(int k = 0; k < 3; k++)
	{
	  jets[i][j][k].et = -1;
	  jets[i][j][k].phi = -1;
	  jets[i][j][k].eta = -1;
	}
      min_3x3[i] = 65535;
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

	// however, if the cluster is the smallest in the RCT then save it.
	if(cluster < min_3x3[rctnum])
	  min_3x3[rctnum] = cluster;

      }

    if(algorithm == MIN_3X3)
    {
      for(int i = 0; i < 18; i++)
	for(int j = 0; j < 2; j++) 
	  for(int k = 0; k < 3; k++)
	  {
	    jets[i][j][k].et -= min_3x3[i];
	    if(jets[i][j][k].et < 0)
	      jets[i][j][k].et = 0;
	  }
    }
    
    jet *head = &jets[0][0][0];    
    qsort(head, 18*2*3, sizeof(jet), sort_func_jet);
    
    if(head[0].et > threshold)
      jet_curve[jetCentHist][jetEtaBin]->Fill(realJetPt);
    // else
    //   jet_curve[jetCentHist]->Fill(realJetPt,0);
    
    total_in_bin[jetCentHist][jetEtaBin]->Fill(realJetPt);
  }

  cout << "Total Events: " << evts << endl;

  TCanvas *plots[cenhists][etabins];
  for(int i = 0; i < cenhists; i++)
  {
    for(int j = 0; j < etabins; j++)
    {
      stringstream filename;
      filename << "jetto_" << method << "_" << threshold
	       << "_" << i <<"_"<< j << ".gif";
      
      plots[i][j] = new TCanvas();
      jet_curve[i][j]->Divide(total_in_bin[i][j]);
  
      jet_curve[i][j]->SetXTitle("Real Jet Pt (GeV)");
      jet_curve[i][j]->SetYTitle("Fraction Accepted");
      
      jet_curve[i][j]->GetYaxis()->SetRangeUser(0,1);
      jet_curve[i][j]->Draw("E");
      
      plots[i][j]->SaveAs(filename.str().c_str());
    }
  }
  
  return(jet_curve[0][0]);
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
