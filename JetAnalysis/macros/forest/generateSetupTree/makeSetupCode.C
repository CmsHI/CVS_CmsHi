#include "makeClass.h"

void makeSetupCode(char *infname = "../merged_HI2010_SD_Jet35_prod05_full.root")
{

  TFile *inf = new TFile(infname);  

  TTree *hltTree      = (TTree*) inf->Get("hltanalysis/HltTree");
  TTree *skimTree     = (TTree*) inf->Get("skimanalysis/HltTree");
  TTree *photonTree   = (TTree*) inf->Get("NTuples/Analysis");
  TTree *trackTree    = (TTree*) inf->Get("anaTrack/trackTree");
  TTree *hitTree      = (TTree*) inf->Get("rechitanalyzer/hbhe");
  TTree *metTree      = (TTree*) inf->Get("anaMET/metTree");

  Int_t phfCoincFilter;
  Int_t ppurityFractionFilter;
  // Add Dummy for skimTree
  if (skimTree)
  {
     skimTree->Branch("phfCoincFilter",&phfCoincFilter,"phfCoincFilter/I");
     skimTree->Branch("ppurityFractionFilter",&ppurityFractionFilter,"ppurityFractionFilter/I");
  }

  if (hltTree) makeClass(hltTree,"Hlt","");
  if (skimTree) makeClass(skimTree,"Skim","");
  if (photonTree) makeClass(photonTree,"Photon","");
  if (trackTree) makeClass(trackTree,"Track","");
  if (hitTree) makeClass(hitTree,"Hit","");
  if (metTree) makeClass(metTree,"Met","");
}
