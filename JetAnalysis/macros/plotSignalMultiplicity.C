#include "weightMix.C"


TProfile* getMult(int isample = 2, string var = "pt2/pt1"){

  TH1::SetDefaultSumw2();

  TChain* ntdijet;

  if(var == "pt2/pt1"){
    ntdijet = new TChain("ntmatch");
  }else{
    ntdijet = new TChain("ntdijet");
  }

  TChain* ntevt = new TChain("ntevt");
  TChain* ntw;

  if(isample == 0){
    ntdijet->Add("/d101/yetkin/analysis/d0128/data_pPb.root");
    ntevt->Add("/d101/yetkin/analysis/d0128/data_pPb.root");
  }

  if(isample == 1){
    ntdijet->Add("/d101/yetkin/analysis/d0128/data_PbPb.root");
    ntevt->Add("/d101/yetkin/analysis/d0128/data_PbPb.root");
  }

  if(isample == 2){
    ntw = new TChain("ntw");

    ntdijet->Add("/d101/yetkin/analysis/d0128/mix_hijing.root");
    ntevt->Add("/d101/yetkin/analysis/d0128/mix_hijing.root");
    ntw->Add("/d101/yetkin/analysis/d0128/mix_hijing.root");
  }

  if(isample == 3){
    ntw = new TChain("ntw");

    ntdijet->Add("/d101/yetkin/analysis/d0128/mix_hydjet.root");
    ntevt->Add("/d101/yetkin/analysis/d0128/mix_hydjet.root");
    ntw->Add("/d101/yetkin/analysis/d0128/mix_hydjet.root");
  }

  string varName = "NNNNN";
  if(var == "ngen30") varName = "N_{GenJet}(p_{T}>30)";
  if(var == "njet30") varName = "N_{RecoJet}(p_{T}>30)";
  if(var == "jtpt2/jtpt1") varName = "p_{T,2}/p_{T,1}";
  if(var == "pt2/pt1"){
    varName = "True (GenJet) p_{T,2}/p_{T,1}";    
  }

  ntdijet->AddFriend(ntevt);
  if(isample > 1) ntdijet->AddFriend(ntw);

  TH2D* h[20];
  TProfile* p[20];

  int nmax = 200;
  if(isample == 2) nmax = 500;

  for(int i = 0; i < 5; ++i){
    h[i] = new TH2D(Form("h%d",i),"",nmax/10,0,nmax,10,0,10);
  }
  
  TH2D* hn = new TH2D(Form("hn%d",isample),"",nmax/10,0,nmax,100,0,2.);

  TCut dijet("jtpt1 > 120 && jtpt2 > 30 && acos(cos(jtphi1-jtphi2))> 2.0944");
  TCut weight("weight");
  if(isample < 2) weight = "jtpt1 > -999";


  ntdijet->SetAlias("var",var.data());


  TCanvas* c2 = new TCanvas("c2","",600,600);
  ntdijet->Draw(Form("var:ntrk>>h%d",0),weight*dijet,"colz");

  if(isample > 1){

    TCanvas* c1 = new TCanvas("c1","",600,600);
    ntdijet->Draw(Form("nps/npb:ntrk>>hn%d",isample),weight*dijet,"colz");
    hn->ProfileX(Form("phn_%d",isample))->Draw("same");
    
    TCanvas* c3 = new TCanvas("c3","",600,600);
    ntdijet->Draw(Form("var:npb+nps>>h%d",1),weight*dijet,"colz");
    
    TCanvas* c4 = new TCanvas("c4","",600,600);
    ntdijet->Draw(Form("var:nps>>h%d",2),weight*dijet,"colz");
    
    TCanvas* c5 = new TCanvas("c5","",600,600);
    ntdijet->Draw(Form("var:npb>>h%d",3),weight*dijet,"colz");
  
  }

  TCanvas* cc1 = new TCanvas("cc1","",600,600);
  for(int i = 0; i < 4; ++i){
    p[i] = h[i]->ProfileX(Form("p%d_%d",i,isample));
  }

  p[2]->SetMarkerColor(2);
  p[2]->SetLineColor(2);

  p[3]->SetMarkerColor(4);
  p[3]->SetLineColor(4);

  p[1]->SetMaximum(5);
  p[1]->SetMinimum(0);

  p[1]->Draw("hist");
  p[0]->Draw("same");

  p[2]->Draw("same");
  p[3]->Draw("same");

  p[0]->GetXaxis()->SetTitle("N_{trk}^{offline}");
  p[0]->GetYaxis()->SetTitle(varName.data());
  p[0]->GetXaxis()->CenterTitle();
  p[0]->GetYaxis()->CenterTitle();

  return p[0];

}


void plotSignalMultiplicity(string var = "njet30"){

  //  getSignalBias(2,var);
  //  return;

  TProfile* p[4];

  for(int i = 0; i < 4; ++i){
    p[i] = getMult(i,var);
    p[i]->SetName(Form("pp%d",i));
    p[i]->SetDirectory(0);
  }


  p[1]->SetMarkerStyle(25);
  p[1]->SetMarkerColor(4);
  p[1]->SetLineColor(4);

  p[3]->SetLineColor(4);

  p[1]->Draw("");
  p[0]->Draw("same");
  p[2]->Draw("hist same");
  p[3]->Draw("hist same");

  TLegend *t3=new TLegend(0.26,0.6,0.53,0.85);
  t3->SetFillColor(0);
  t3->SetBorderSize(0);
  t3->SetFillStyle(0);
  t3->SetTextFont(63);
  t3->SetTextSize(20);
  t3->AddEntry(p[0],"pPb data","p");
  t3->AddEntry(p[1],"PbPb data","p");
  t3->AddEntry(p[2],"pPb Hijing + Pythia","l");
  t3->AddEntry(p[3],"PbPb Hydjet + Pythia","l");

  t3->Draw();


}





