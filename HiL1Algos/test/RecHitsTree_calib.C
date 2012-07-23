#define RecHitsTree_calib_cxx
#include "RecHitsTree_calib.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <stdio.h>
#include <TLegend.h>
#include <TNtuple.h>
#include <TMath.h>

const int NETA_TOWERS = 82;

#include "FindTowerJet.C"
#include "FindRegionJet.C"

int numPhiTowers(int ieta);

void RecHitsTree_calib::Loop(int total_events, 
			     bool PHI_AVERAGE,
			     bool cut_noise_events)
{
  const int NBINS = 300;
  const int MAX_EN = 600;

  const int JET_DIAMETER = 9;
  const bool CIRCULAR_JETS = true; //otherwise square jets, only valid for odd jet diamater.

  const double DR_CUT = 0.8; //maximum distance a genjet can be to the L1 jet

  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();

  TH1D *dEtaTower = new TH1D("dEtaTower","dEta Circular Tower Jets",
  			40,0,6);
  TH1D *dPhiTower = new TH1D("dPhiTower","dPhi Circular Tower Jets",
  			40,0,3.5);
  TH1D *dEtTower = new TH1D("dEtTower","dEt Circular Tower Jets",
  			50,0,150);
  TH1D *dRTower = new TH1D("dR", "dr Circular Tower Jets",
  		      40, 0, 8);

  TH1D *dEtaRegion = new TH1D("dEtaRegion","dEta Region Jets",
  			40,0,6);
  TH1D *dPhiRegion = new TH1D("dPhiRegion","dPhi Region Jets",
  			40,0,3.5);
  TH1D *dEtRegion = new TH1D("dEtRegion","dEt Region Jets",
  			50,0,150);
  TH1D *dRRegion = new TH1D("dRRegion", "dr Region Jets",
  		      40, 0, 8);

  TH1D *dRJets = new TH1D("dRJets", "dr between tower jet and region jet",
  			  40, 0, 8);

  TFile *outf = new TFile("JetEnergyCorrections_pi.root", "recreate");
  
  TNtuple *matchedTowerJets = new TNtuple("matchedTowerJets","matchedTowerJets",
					  "recoIPhi:recoPhi:recoIEta:recoEta:recoEt:genPhi:genEta:genEt:correction:centBin:dr:genLeading:recoLeading");
  
  TNtuple *matchedRegionJets = new TNtuple("matchedRegionJets","matchedRegionJets",
					   "recoIPhi:recoPhi:recoIEta:recoEta:recoEt:genPhi:genEta:genEt:correction:centBin:dr:genLeading:recoLeading");
  
  int evts = 0;
  bool break_early = total_events != -1;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;
    
    fhlt->GetEntry(jentry);
    fhiinfo->GetEntry(jentry);
    fjet->GetEntry(jentry);

    if(fjet->ngen == 0) continue;

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
    int centBin = fhiinfo->hiBin;

    //in case not all towers show up, assume they are 0
    double fullDetectorTowers[NETA_TOWERS][NPHI_TOWERS]; //[eta][phi]
    for(int i = 0; i < NETA_TOWERS; i++){
      for(int j = 0; j < NPHI_TOWERS; j++){
    	fullDetectorTowers[i][j] = 0;
      }
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
      }
    }

    if(PHI_AVERAGE)
    {
      double phiAverageTowers[NETA_TOWERS];
      for(int eta_i = 0; eta_i < NETA_TOWERS; eta_i++){
    	phiAverageTowers[eta_i] = 0;
    	for(int phi_i = 0; phi_i < NPHI_TOWERS; phi_i++){
    	  phiAverageTowers[eta_i] += fullDetectorTowers[eta_i][phi_i];
    	}
    	phiAverageTowers[eta_i] /= numPhiTowers(eta_i);
      }
      
      for(int eta_i = 0; eta_i < NETA_TOWERS; eta_i++)
    	for(int phi_i = 0; phi_i < NPHI_TOWERS; phi_i++){
    	  fullDetectorTowers[eta_i][phi_i] -= phiAverageTowers[eta_i];
    	  if(fullDetectorTowers[eta_i][phi_i] < 0)
    	    fullDetectorTowers[eta_i][phi_i] = 0;
    	}
    }

    if(PHI_AVERAGE)
    {
      double phiAverageRegions[NETA_REGIONS];
      for(int eta_i = 0; eta_i < NETA_REGIONS; eta_i++){
    	phiAverageRegions[eta_i] = 0;
    	for(int phi_i = 0; phi_i < NPHI_REGIONS; phi_i++){
    	  phiAverageRegions[eta_i] += fullDetectorRegions[eta_i][phi_i];
    	}
    	phiAverageRegions[eta_i] /= NPHI_REGIONS;
      }
      
      for(int eta_i = 0; eta_i < NETA_REGIONS; eta_i++)
    	for(int phi_i = 0; phi_i < NPHI_REGIONS; phi_i++){
    	  fullDetectorRegions[eta_i][phi_i] -= phiAverageRegions[eta_i];
    	  if(fullDetectorRegions[eta_i][phi_i] < 0)
    	    fullDetectorRegions[eta_i][phi_i] = 0;
    	}
    }

    //This is really hacky, but the findJet methods return arrays of size 2.
    TowerJet *highestTowerJet;
    RegionJet *highestRegionJet;
    highestTowerJet = findTowerJet(fullDetectorTowers, CIRCULAR_JETS, JET_DIAMETER);
    highestRegionJet = findRegionJet(fullDetectorRegions);

    // if(highestTowerJet.sumEt < 50)
    //   continue;

    TowerJet genJet[2];
    genJet[0].sumEt = -1;
    genJet[1].sumEt = -1;
    double jetDistance2;
    int pairnum;

    for(int i = 0; i < fjet->ngen; i++)
    {
      if(fjet->gensubid[i] != 0) continue;
      if(fjet->genpt[i] > genJet[0].sumEt)
      {
	genJet[1] = genJet[0];
	genJet[0].sumEt = fjet->genpt[i];
	genJet[0].realEta = fjet->geneta[i];
	genJet[0].realPhi = fjet->genphi[i];
      }
      else if(fjet->genpt[i] > genJet[1].sumEt)
      {
	genJet[1].sumEt = fjet->genpt[i];
	genJet[1].realEta = fjet->geneta[i];
	genJet[1].realPhi = fjet->genphi[i];
      }
    }

    for(int j = 0; j < 2; j++)
    {
      jetDistance2 = 10000;
      // for(int i = 0; i < fjet->ngen; i++)
      // {
      // 	if(fjet->gensubid[i] != 0) continue;
      // 	double dr = (highestTowerJet[j].realEta-fjet->geneta[i]) *
      // 	  (highestTowerJet[j].realEta-fjet->geneta[i]) +
      // 	  acos(cos(highestTowerJet[j].realPhi-fjet->genphi[i])) *
      // 	  acos(cos(highestTowerJet[j].realPhi-fjet->genphi[i]));
      // 	if(dr < jetDistance2)
      // 	{
      // 	  genJetEta = fjet->geneta[i];
      // 	  genJetPhi = fjet->genphi[i];
      // 	  genJetPt = fjet->genpt[i];
      // 	  jetDistance2 = dr;
      // 	}
      // }
      pairnum = -1;
      for(int i = 0; i < 2; i++)
      {
	double dr = (highestTowerJet[j].realEta-genJet[i].realEta) *
	  (highestTowerJet[j].realEta-genJet[i].realEta) +
      	  acos(cos(highestTowerJet[j].realPhi-genJet[i].realPhi-TMath::Pi())) *
      	  acos(cos(highestTowerJet[j].realPhi-genJet[i].realPhi-TMath::Pi()));
	if(dr < jetDistance2)
	{
	  jetDistance2 = dr;
	  pairnum = i;
	}
      }
      //if(sqrt(jetDistance2) < DR_CUT)
      {
	dPhiTower->Fill(acos(cos(highestTowerJet[j].realPhi-genJet[pairnum].realPhi)));
	dEtaTower->Fill(fabs(highestTowerJet[j].realEta-genJet[pairnum].realEta));
	dRTower->Fill(sqrt(jetDistance2));
	dEtTower->Fill(fabs(genJet[pairnum].sumEt-highestTowerJet[j].sumEt));

	double correctionTower = highestTowerJet[j].sumEt/genJet[pairnum].sumEt;
	matchedTowerJets->Fill(
	  highestTowerJet[j].phi,
	  highestTowerJet[j].realPhi,
	  highestTowerJet[j].eta,
	  highestTowerJet[j].realEta,
	  highestTowerJet[j].sumEt,
	  genJet[pairnum].realPhi,
	  genJet[pairnum].realEta,
	  genJet[pairnum].sumEt,
	  correctionTower,
	  centBin,
	  sqrt(jetDistance2),
	  pairnum,
	  j
	  );
      }
      
      jetDistance2 = 10000;
      // for(int i = 0; i < fjet->ngen; i++)
      // {
      // 	if(fjet->gensubid[i] != 0) continue;
      // 	double dr = (highestRegionJet[j].realEta-fjet->geneta[i]) *
      // 	  (highestRegionJet[j].realEta-fjet->geneta[i]) +
      // 	  acos(cos(highestRegionJet[j].realPhi-fjet->genphi[i])) *
      // 	  acos(cos(highestRegionJet[j].realPhi-fjet->genphi[i]));
      // 	if (dr < jetDistance2)
      // 	{
      // 	  genJetEta = fjet->geneta[i];
      // 	  genJetPhi = fjet->genphi[i];
      // 	  genJetPt = fjet->genpt[i];
      // 	  jetDistance2 = dr;
      // 	}
      // }

      pairnum = -1;
      for(int i = 0; i < 2; i++)
      {
	double dr = (highestRegionJet[j].realEta-genJet[i].realEta) *
	  (highestRegionJet[j].realEta-genJet[i].realEta) +
      	  acos(cos(highestRegionJet[j].realPhi-genJet[i].realPhi-TMath::Pi())) *
      	  acos(cos(highestRegionJet[j].realPhi-genJet[i].realPhi-TMath::Pi()));
	if(dr < jetDistance2)
	{
	  jetDistance2 = dr;
	  pairnum = i;
	}
      }

      //if(sqrt(jetDistance2) < DR_CUT)
      {
	dPhiRegion->Fill(acos(cos(highestRegionJet[j].realPhi-genJet[pairnum].realPhi)));
	dEtaRegion->Fill(fabs(highestRegionJet[j].realEta-genJet[pairnum].realEta));
	dRRegion->Fill(sqrt(jetDistance2));
	dEtRegion->Fill(fabs(genJet[pairnum].sumEt-highestRegionJet[j].sumEt));
      
	double correctionRegion = highestRegionJet[j].sumEt/genJet[pairnum].sumEt;
	matchedRegionJets->Fill(
	  highestRegionJet[j].phi,
	  highestRegionJet[j].realPhi,
	  highestRegionJet[j].eta,
	  highestRegionJet[j].realEta,
	  highestRegionJet[j].sumEt,
	  genJet[pairnum].realPhi,
	  genJet[pairnum].realEta,
	  genJet[pairnum].sumEt,
	  correctionRegion,
	  centBin,
	  sqrt(jetDistance2),
	  pairnum,
	  j
	  );	
      }
    }
    
    if(break_early && (evts > total_events)) break;
    evts++;
  }

  TCanvas *c[10];
  TLegend *leg[5];

  c[0] = new TCanvas();
  dPhiTower->SetTitle("dPhi between L1 jet and genjet");
  dPhiTower->SetMinimum(0);
  dPhiTower->Draw();
  dPhiRegion->SetLineColor(kBlue);
  dPhiRegion->Draw("same");
  leg[0] = new TLegend(0.5, 0.5, 0.8, 0.8);
  leg[0]->SetFillColor(0);
  leg[0]->AddEntry(dPhiTower, "Tower Jets","l");
  leg[0]->AddEntry(dPhiRegion, "Region Jets", "l");
  leg[0]->Draw();
  c[0]->Update();
  
  c[1] = new TCanvas();
  dEtaTower->SetTitle("dEta between L1 jet and genjet");
  dEtaTower->SetMinimum(0);
  dEtaTower->Draw();
  dEtaRegion->SetLineColor(kBlue);
  dEtaRegion->Draw("same");
  leg[1] = new TLegend(0.5, 0.5, 0.8, 0.8);
  leg[1]->SetFillColor(0);
  leg[1]->AddEntry(dEtaTower, "Tower Jets","l");
  leg[1]->AddEntry(dEtaRegion, "Region Jets", "l");
  leg[1]->Draw();
  c[1]->Update();
  
  c[2] = new TCanvas();
  dEtTower->SetTitle("dEt between L1 jet and genjet");
  dEtTower->SetMinimum(0);
  dEtTower->Draw();
  dEtRegion->SetLineColor(kBlue);
  dEtRegion->Draw("same");
  leg[2] = new TLegend(0.5, 0.5, 0.8, 0.8);
  leg[2]->SetFillColor(0);
  leg[2]->AddEntry(dEtTower, "Tower Jets","l");
  leg[2]->AddEntry(dEtRegion, "Region Jets", "l");
  leg[2]->Draw();
  c[2]->Update();
  
  c[3] = new TCanvas();
  dRTower->SetTitle("dr between L1 jet and genjet");
  dRTower->SetMinimum(0);
  dRTower->Draw();
  dRRegion->SetLineColor(kBlue);
  dRRegion->Draw("same");
  leg[3] = new TLegend(0.5, 0.5, 0.8, 0.8);
  leg[3]->SetFillColor(0);
  leg[3]->AddEntry(dRTower, "Tower Jets","l");
  leg[3]->AddEntry(dRRegion, "Region Jets", "l");
  leg[3]->Draw();
  c[3]->Update();
  
  // c[4] = new TCanvas();
  // dRJets->SetTitle("dr between tower jet and region jet");
  // dRJets->SetMinimum(0);
  // dRJets->Draw();

  outf->cd();
  matchedTowerJets->Write();
  matchedRegionJets->Write();
  outf->Close();

  
  return;
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
