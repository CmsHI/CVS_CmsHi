#include <TFile.h>
#include <TNtuple.h>
#include <TProfile.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TString.h>
#include <TBranch.h>

void RecHitsTree_macro2()
{
  TFile *infile = new TFile("JetEnergyCorrections_pi.root");
  TNtuple *matchedRegionJets = (TNtuple*)infile->Get("matchedRegionJets");
  TNtuple *matchedTowerJets = (TNtuple*)infile->Get("matchedTowerJets");

  TFile *outf = new TFile("JetEnergyCorrectionsTable.root", "recreate");

  const double etBinsRegions[12] = {
    0,20,30,40,50,60,70,80,90,100,
    125,150
  };
  const double etBinsTowers[13] = {
    0,20,30,40,50,60,70,80,90,100,
    125,150,200
  };

  const double etaBinsRegions[15] = {
    0, //1
    5,6,7,8,9,10,11,12,13,14,15,16, //12
    17,22 //2
  };
  const double etaBinsTowers[15] = {
    0, //1
    17,21,25,29,33,37,41,45,49,53,57,61, //12
    65,82 //2
  };

  Float_t recoEt, genEt, dr;
  Float_t recoIEta;
  //TBranch *b_recoEt, *b_genEt, *b_dr, *b_recoIEta;
  TTree *fChain = matchedRegionJets;
  fChain->SetBranchAddress("recoEt", &recoEt);
  fChain->SetBranchAddress("genEt", &genEt);
  fChain->SetBranchAddress("recoIEta", &recoIEta);
  fChain->SetBranchAddress("dr", &dr);
  
  TH2D *regionL1JetEnergyCorrection = new TH2D("regionL1JetEnergyCorrection",
					       "regionL1JetEnergyCorrection",
					       11, etBinsRegions,
					       14, etaBinsRegions);
  TH2D *regionCounter = new TH2D("regionCounter",
				 "regionCounter",
				 11, etBinsRegions,
				 14, etaBinsRegions);
  // matchedRegionJets->Project("regionL1JetEnergyCorrection",
  // 			     "correction:recoIEta:recoEt",
  // 			     "dr<0.5");

  Long64_t nentries = fChain->GetEntriesFast();
  //printf("nentries: %d\n",nentries);
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    fChain->GetEntry(jentry);
    if(dr > 0.5) continue;
    regionL1JetEnergyCorrection->Fill(recoEt,recoIEta,recoEt/genEt);
    regionCounter->Fill(recoEt,recoIEta);
  }
  regionL1JetEnergyCorrection->Divide(regionCounter);
  
  regionL1JetEnergyCorrection->SetMinimum(0);

  TCanvas *c1 = new TCanvas();
  regionL1JetEnergyCorrection->Draw("Lego2");

  fChain = matchedTowerJets;
  fChain->SetBranchAddress("recoEt", &recoEt);
  fChain->SetBranchAddress("genEt", &genEt);
  fChain->SetBranchAddress("recoIEta", &recoIEta);
  fChain->SetBranchAddress("dr", &dr);
  
  TH2D *towerL1JetEnergyCorrection = new TH2D("towerL1JetEnergyCorrection",
					       "towerL1JetEnergyCorrection",
					       12, etBinsTowers,
					       14, etaBinsTowers);
  TH2D *towerCounter = new TH2D("towerCounter",
				 "towerCounter",
				 12, etBinsTowers,
				 14, etaBinsTowers);
  // matchedTowerJets->Project("towerL1JetEnergyCorrection",
  // 			     "correction:recoIEta:recoEt",
  // 			     "dr<0.5");

  nentries = fChain->GetEntriesFast();
  //printf("nentries: %d\n",nentries);
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    fChain->GetEntry(jentry);
    if(dr > 0.5) continue;
    towerL1JetEnergyCorrection->Fill(recoEt,recoIEta,recoEt/genEt);
    towerCounter->Fill(recoEt,recoIEta);
  }
  towerL1JetEnergyCorrection->Divide(towerCounter);
  
  towerL1JetEnergyCorrection->SetMinimum(0);

  TCanvas *c2 = new TCanvas();
  towerL1JetEnergyCorrection->Draw("Lego2");
  
  // TH2D *towerL1JetEnergyCorrection = new TH2D("towerL1JetEnergyCorrection",
  // 					      "towerL1JetEnergyCorrection",
  // 					      12, etBinsTowers,
  // 					      14, etaBinsTowers);
  
  // matchedTowerJets->Project("towerL1JetEnergyCorrection",
  // 			    "recoIEta:recoEt",
  // 			    "dr<0.5");
  // towerL1JetEnergyCorrection->SetMinimum(0);

  // TCanvas *c2 = new TCanvas();
  // towerL1JetEnergyCorrection->Draw("col");

  //TString cut = "(recoIEta>80 && genEt<100)";

  // TProfile *regionL1JetEnergyCorrection1d = new TProfile("regionL1JetEnergyCorrection1d",
  // 							 "regionL1JetEnergyCorrection1d",
  // 							 11, etBinsRegions);
  // regionL1JetEnergyCorrection1d->SetXTitle("recoEt");
  // regionL1JetEnergyCorrection1d->SetYTitle("genEt");
  // regionL1JetEnergyCorrection1d->SetTitle("Regions ");

  // matchedRegionJets->Project("regionL1JetEnergyCorrection1d",
  // 			     "genEt:recoEt",
  // 			     "dr<0.5&&recoIEta==11");

  // TCanvas *c3 = new TCanvas();
  // regionL1JetEnergyCorrection1d->Draw("E");

  
  // TProfile *towerL1JetEnergyCorrection1d = new TProfile("towerL1JetEnergyCorrection1d",
  // 							"towerL1JetEnergyCorrection1d",
  // 							12, etBinsTowers);
  // towerL1JetEnergyCorrection1d->SetXTitle("recoEt");
  // towerL1JetEnergyCorrection1d->SetYTitle("genEt");
  // towerL1JetEnergyCorrection1d->SetTitle("Towers recoIEta>=33&&recoIEta<37");

  // matchedTowerJets->Project("towerL1JetEnergyCorrection1d",
  // 			    "genEt:recoEt",
  // 			    "dr<0.5&&recoIEta>=33&&recoIEta<37");

  // TCanvas *c4 = new TCanvas();
  // towerL1JetEnergyCorrection1d->Draw("E");

  outf->cd();
  regionL1JetEnergyCorrection->Write();
  towerL1JetEnergyCorrection->Write();
  outf->Close();
  
}
