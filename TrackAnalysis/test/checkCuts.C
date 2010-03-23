void checkCuts() {

  TFile *f = new TFile("outputTree_testAnalyzer_numEvent1.root");
  TTree *t = (TTree*) f->Get("RecoStudyTree");

  //d0
  t->Draw("RecTracks.fD0>>hD0m(41,-0.2,0.2)","RecTracks.iMatches>0");
  t->Draw("RecTracks.fD0>>hD0f(41,-0.2,0.2)","RecTracks.iMatches==0"); 
  t->Draw("SimTracks.fMD0>>hD0s(41,-0.2,0.2)","SimTracks.iMatches>0"); 

  t->Draw("fD0/fD0Err>>hD0Nm(41,-10,10)","RecTracks.iMatches>0");
  t->Draw("fD0/fD0Err>>hD0Nf(41,-10,10)","RecTracks.iMatches==0"); 
  t->Draw("SimTracks.fMD0/SimTracks.fMD0Err>>hD0Ns(41,-10,10)","SimTracks.iMatches>0");

  //dz
  t->Draw("RecTracks.fZ>>hDZm(41,-0.2,0.2)","RecTracks.iMatches>0");
  t->Draw("RecTracks.fZ>>hDZf(41,-0.2,0.2)","RecTracks.iMatches==0"); 
  t->Draw("SimTracks.fMZ>>hDZs(41,-0.2,0.2)","SimTracks.iMatches>0"); 

  t->Draw("fZ/fZErr>>hDZNm(41,-10,10)","RecTracks.iMatches>0");
  t->Draw("fZ/fZErr>>hDZNf(41,-10,10)","RecTracks.iMatches==0"); 
  t->Draw("SimTracks.fMZ/SimTracks.fMZErr>>hDZNs(41,-10,10)","SimTracks.iMatches>0");

  //chi2
  t->Draw("RecTracks.fChi2>>hChi2m(41,0.,1000.)","RecTracks.iMatches>0");
  t->Draw("RecTracks.fChi2>>hChi2f(41,0.,1000.)","RecTracks.iMatches==0"); 
  t->Draw("SimTracks.fMChi2>>hChi2s(41,0.,1000.)","SimTracks.iMatches>0"); 

  t->Draw("RecTracks.fChi2Norm>>hChi2Nm(41,0.,1000.)","RecTracks.iMatches>0");
  t->Draw("RecTracks.fChi2Norm>>hChi2Nf(41,0.,1000.)","RecTracks.iMatches==0"); 
  t->Draw("SimTracks.fMChi2Norm>>hChi2Ns(41,0.,1000.)","SimTracks.iMatches>0"); 

  /////////////

  TCanvas *c1 = new TCanvas("c1","c1");
  c1->cd();
  hD0s->SetLineColor(4);
  hD0f->SetLineColor(2);
  hD0s->Draw();
  hD0f->Draw("same");

  TCanvas *c2 = new TCanvas("c2","c2");
  c2->cd();
  hD0Ns->SetLineColor(4);
  hD0Nf->SetLineColor(2);
  hD0Ns->Draw();
  hD0Nf->Draw("same");

  TCanvas *c3 = new TCanvas("c3","c3");
  c3->cd();
  hDZs->SetLineColor(4);
  hDZf->SetLineColor(2);
  hDZs->Draw();
  hDZf->Draw("same");

  TCanvas *c4 = new TCanvas("c4","c4");
  c4->cd();
  hDZNs->SetLineColor(4);
  hDZNf->SetLineColor(2);
  hDZNs->Draw();
  hDZNf->Draw("same");

  TCanvas *c5 = new TCanvas("c5","c5");
  c5->cd();
  hChi2s->SetLineColor(4);
  hChi2f->SetLineColor(2);
  hChi2s->Draw();
  hChi2f->Draw("same");

  TCanvas *c6 = new TCanvas("c6","c6");
  c6->cd();
  hChi2Ns->SetLineColor(4);
  hChi2Nf->SetLineColor(2);
  hChi2Ns->Draw();
  hChi2Nf->Draw("same");

}
