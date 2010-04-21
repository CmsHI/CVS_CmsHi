

{

  TFile * inf = new TFile("jets_pat_120to170.root");

  Events->SetAlias("cent","recoCentrality_hiCentrality__RECO.obj");
  Events->SetAlias("jets","recoCaloJets_iterativeConePu5CaloJets__RECO");
  Events->SetAlias("bkgjets","recoCaloJets_bkg5Jets__RECO");
  Events->SetAlias("genjets","recoGenJets_iterativeCone5HiGenJets__RECO");

  Events->SetAlias("patjets","patJets_ic5patJets__MATCH.obj");
  Events->SetAlias("njets","Sum$(patjets.pt() > -200 )");

  Events->SetAlias("hf","cent->EtHFhitSum()");

  Events->SetAlias("genjet","patjets.genJet()");
  Events->Draw("patjets.pt():genjet.pt()","","colz");

}


