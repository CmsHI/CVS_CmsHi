#define TriggerPrimitivesTree_jetcurve_cxx
#include "TriggerPrimitivesTree_jetcurve.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TProfile.h>
#include <iostream>
#include <sstream>

#include "FindRegionJet.C"

using namespace std;

TH1D* TriggerPrimitivesTree_jetcurve::Loop(int total_events,
					   int threshold,
					   bool PHI_AVERAGE,
					   int minCentBin,
					   int maxCentBin)
{
  TH1::SetDefaultSumw2();

  if (fChain == 0) return(0);
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  const int nbins = 40; //number of jet pt bins
  const int MAX_JET_EN = 200; //max energy shown by the histogram, in GeV
  
  TH1D* jet_curve;
  TH1I* total_in_bin;

  TString method;
  TString method_s;

  if(PHI_AVERAGE)
  {
    method = "Region-Level Phi-Ring Subtraction";
    method_s = "phisub";
  }
  else
  {
    method = "Current L1 System";
    method_s = "nosub";
  }

  stringstream name1,name2,name3;
  name1 << "Jet Turn-On. "<< method <<  " Threshold:" << threshold;
  name2 << "total_in_bin";
  name3 << "jet_curve";
  jet_curve = new TH1D(name3.str().c_str(), name1.str().c_str(),
		       nbins,0,MAX_JET_EN);
  total_in_bin = new TH1I(name2.str().c_str(),name2.str().c_str(),
			  nbins,0,MAX_JET_EN);

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

    double fulldetector[NETA_REGIONS][NPHI_REGIONS]; //[eta][phi]
    for(int i = 0; i < numRegions; i++)
    {
      fulldetector[caloRegionEtaIndex[i]][caloRegionPhiIndex[i]] = caloRegionEt[i];
    }
      
    if(PHI_AVERAGE)
    {
      double phi_average[NETA_REGIONS];
      for(int ieta = 0; ieta < NETA_REGIONS; ieta++){
	phi_average[ieta] = 0;
	for(int iphi = 0; iphi < NPHI_REGIONS; iphi++){
	  phi_average[ieta] += fulldetector[ieta][iphi];
	}
	phi_average[ieta] /= NPHI_REGIONS;
      }
      
      for(int ieta = 0; ieta < NETA_REGIONS; ieta++)
	for(int iphi = 0; iphi < NPHI_REGIONS; iphi++){
	  fulldetector[ieta][iphi] -= phi_average[ieta];
	  if(fulldetector[ieta][iphi] < 0)
	    fulldetector[ieta][iphi] = 0;
	}
    }    

    RegionJet highestJet = findRegionJet(fulldetector);
    
    if(highestJet.et > threshold)
      jet_curve->Fill(realJetPt);
    
    total_in_bin->Fill(realJetPt);
  }
  
//TCanvas *plot;

  stringstream filename;
  filename << "jetto_" << method_s << "_" << threshold << ".gif";
//plot = new TCanvas();
  //jet_curve->Divide(total_in_bin);
  jet_curve->Divide(jet_curve, total_in_bin, 1, 1, "b");
  jet_curve->SetXTitle("HLT Jet Pt (GeV)");
  jet_curve->SetYTitle("Fraction Accepted");

  jet_curve->GetYaxis()->SetRangeUser(0,1);
  //jet_curve->Draw("E");

//plots[i]->SaveAs(filename.str().c_str());
  
  return(jet_curve);
}
