#include "makeClass.h"

void makeSetupCode(char *infname = "../merged_Run181531_HIExpressPhysics_Part.root")
{

  TFile *inf = new TFile(infname);  

  TTree *hltTree      = (TTree*) inf->Get("hltanalysis/HltTree");
  TTree *skimTree     = (TTree*) inf->Get("skimanalysis/HltTree");
  TTree *photonTree   = (TTree*) inf->Get("multiPhotonAnalyzer/photon");
  TTree *evtTree      = (TTree*) inf->Get("hiEvtAnalyzer/HiTree");
  TTree *trackTree    = (TTree*) inf->Get("anaTrack/trackTree");
  TTree *jetTree      = (TTree*) inf->Get("akPu3PFJetAnalyzer/t");
  TTree *hitTree      = (TTree*) inf->Get("rechitanalyzer/hbhe");
  TTree *metTree      = (TTree*) inf->Get("anaMET/metTree");
  TTree *pfTree      = (TTree*) inf->Get("pfcandAnalyzer/pfTree");

  Int_t phfCoincFilter;
  Int_t ppurityFractionFilter;

  // Add Dummy for skimTree
  if (skimTree)
  {
     skimTree->Branch("phfCoincFilter",&phfCoincFilter,"phfCoincFilter/I");
     skimTree->Branch("ppurityFractionFilter",&ppurityFractionFilter,"ppurityFractionFilter/I");
  }

  // hack for jet tree
  Float_t smpt[1000];
  if (jetTree) {
     jetTree->Branch("smpt",smpt,"smpt[nref]/F");
  }
  
  if (hltTree) makeClass(hltTree,"Hlt","");
  if (skimTree) makeClass(skimTree,"Skim","");
  if (photonTree) makeClass(photonTree,"Photon","");
  if (evtTree) makeClass(evtTree,"Evt","");
  if (trackTree) makeClass(trackTree,"Track","");
  if (jetTree) makeClass(jetTree,"Jet","");
  if (hitTree) makeClass(hitTree,"Hit","");
  if (metTree) makeClass(metTree,"Met","");
  if (pfTree) makeClass(pfTree,"PF","");
}
