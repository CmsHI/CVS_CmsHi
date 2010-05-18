

{
  
  TFile * inf = TFile::Open("root://castorcms//castor/cern.ch/user/y/yilmaz/pat/CMSSW_3_6_0/UnquenchedDijet80to120_runs1to500.root");
  
  Events->SetAlias("cent","recoCentrality_hiCentrality__RECO.obj");
  
  if(0){
    Events->SetAlias("jets","recoCaloJets_iterativeConePu5CaloJets__RECO");
    Events->SetAlias("bkgjets","recoCaloJets_bkg5Jets__RECO");
    Events->SetAlias("genjets","recoGenJets_iterativeCone5HiGenJets__RECO");
  }

  Events->SetAlias("patjets","patJets_patJets__PAT");
  Events->SetAlias("njets","Sum$(patjets.pt() > -200 )");
  Events->SetAlias("hf","cent->EtHFhitSum()");

  Events->SetAlias("genjet","patjets.genJet()");
  Events->Draw("patjets.pt():genjet.pt()","","colz");

}


