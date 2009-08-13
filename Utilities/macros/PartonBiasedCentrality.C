#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TNtuple.h"
#include "TLegend.h"
#include "TF1.h"

#include "TGraphAsymmErrors.h"
using namespace std;

void PartonBiasedCentrality(double pttrig = 100, int etabin = 2, int nBins = 40){

TFile* inf = new TFile("hydjet_b.root");

 TNtuple * nt = dynamic_cast<TNtuple*>(inf->Get("ana/nt"));

  TH1D* hB = new TH1D("hB",";b[fm];events",nBins,0,20);
  
  TH1D* hJet = new TH1D(Form("hJet%d",(int)pttrig),";b[fm];events",nBins,0,20);
  
  TH1D* hJetWeight = new TH1D(Form("hJetWeight%d",(int)pttrig),";b[fm];events",nBins,0,20);
  TH1D* hJetTrigger = new TH1D(Form("hJetTrigger%d",(int)pttrig),";b[fm];events",nBins,0,20);

  TH1D* hNhard = new TProfile("hNhard",";b[fm];N_{hard}",nBins,0,20);

  TF1 *fJetWeight = new TF1(Form("fJetWeight%d",(int)pttrig),"gaus",0,20);
  TF1 *fJetTrigger = new TF1(Form("fJetTrigger%d",(int)pttrig),"gaus",0,20);

 hJet->SetLineColor(4);
 hJetWeight->SetLineColor(4);
 hJetTrigger->SetLineColor(4);
 fJetWeight->SetLineColor(4);
 fJetTrigger->SetLineColor(4);

 nt->Draw("b>>hB","");
 nt->Draw("nhard:b>>hNhard","","prof");
 nt->Draw(Form("b>>%s",hJet->GetName()),Form("parton%d > %f",etabin,pttrig));

 hJetWeight->Add(hJet);
 hJetWeight->Divide(hB);
 hJetTrigger->Add(hJetWeight);

 int binmax = hJet->GetMaximumBin();
 int binmax2 = hJetWeight->GetMaximumBin();
 double jetWeightMax = hJetWeight->GetMaximum();

 hJet->Scale(hB->GetBinContent(binmax)/hJet->GetBinContent(binmax));
 hJetTrigger->Scale(hNhard->GetBinContent(binmax)/hJetTrigger->GetBinContent(binmax));
 hJetWeight->Scale(1./jetWeightMax);

 hJetWeight->Fit(fJetWeight);
 hJetTrigger->Fit(fJetTrigger);

 jetWeightMax = fJetWeight->GetMaximum();
 hJetWeight->Scale(1./jetWeightMax);
 hJetWeight->Fit(fJetWeight);

 // cout<<"Max 1 : "<<binmax<<" Max 2 : "<<binmax2<<endl;

 TLegend* leg1 = new TLegend(0.13,0.68,0.44,0.88,NULL,"brNDC");
 leg1->SetFillColor(0);
 leg1->SetTextSize(0.028);
 leg1->SetBorderSize(0);
 leg1->AddEntry(hB,Form("Min Bias b distribution"),"l");
 leg1->AddEntry(hJet,Form("Jet Biased b distribution"),"l");
 leg1->AddEntry(hB,Form("(Arbitrary Normalization)"),"");

 TLegend* leg2 = new TLegend(0.46,0.68,0.77,0.88,NULL,"brNDC");
 leg2->SetFillColor(0);
 leg2->SetTextSize(0.028);
 leg2->SetBorderSize(0);
 leg2->AddEntry(hNhard,Form("N_{hard} vs b"),"l");
 leg2->AddEntry(hJetTrigger,Form("p(b)^{Jet Bias} / p(b)^{Min Bias}"),"l");
 leg2->AddEntry(hNhard,Form("(Arbitrary Normalization)"),"");


 TCanvas* c1 = new TCanvas("c1","c1",400,400);
 hB->Draw();
 hJet->Draw("same");
 leg1->Draw();
 c1->Print(Form("impact_parameter_pt%d_nbins%d.gif",(int)pttrig,nBins));

 TCanvas* c2 = new TCanvas("c2","c2",400,400);
 hNhard->Draw("hist");
 hJetTrigger->Draw("same");
 leg2->Draw();
 c2->Print(Form("jet_bias_nhard_pt%d_nbins%d.gif",(int)pttrig,nBins));


 TCanvas* c3 = new TCanvas("c3","c3",400,400);
 hJetWeight->Draw("");
 c3->Print(Form("jet_bias_pt%d_nbins%d.gif",(int)pttrig,nBins));


 // Wrong, it also scales with f(b)
 // double eff = hJetWeight->Integral()/hJetWeight->GetNbinsX();

 double eff = hJet->Integral()/hB->Integral();

 // Report parameters

 cout<<"__________________________________"<<endl;

 cout<<"Using the Fit Function : "<<endl;
 cout<<fJetWeight->GetExpFormula()<<endl;
 cout<<"__________________________________"<<endl;

 cout<<"The parameters of the fit are : "<<endl;

 for(int ip = 0; ip < fJetWeight->GetNpar(); ++ip){
   cout<<fJetWeight->GetParameter(ip)<<",";
 }
 
 cout<<endl;
 cout<<"__________________________________"<<endl;

 cout<<"Expected Filter Efficiency : "<<endl;
 cout<<"                              "<<eff<<endl;
 cout<<endl;
 cout<<"__________________________________"<<endl;




}

