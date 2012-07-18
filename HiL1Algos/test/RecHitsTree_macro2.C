#include <TFile.h>
#include <TNtuple.h>
#include <TProfile2D.h>

void RecHitsTree_macro2()
{
  TFile *infile = new TFile("JetEnergyCorrections.root");
  TNtuple *matchedRegionJets = (TNtuple*)infile->Get("matchedRegionJets");
  TNtuple *matchedTowerJets = (TNtuple*)infile->Get("matchedTowerJets");

  const double etBinsRegions[14] = {
    0,10,20,30,40,50,60,70,80,90,100, //11
    150,200,300 //3
  };
  const double etaBinsRegions[13] = {
    0, //1
    6,7,8,9,10,11,12,13,14,15,16, //11
    22 //1
  };
  
  TProfile2D *factors = new TProfile2D("factors","factors",
				       13, etBinsRegions,
				       12, etaBinsRegions);
  
  matchedRegionJets->Project("factors","correction:recoIEta:recoEt");

  factors->Draw("E");

}
