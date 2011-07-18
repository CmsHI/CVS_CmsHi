//July 11, 2011: Gives Accept Fraction as a function of uncorrected Jet pt


#include "TChain.h"
#include "TH1.h"
#include "TCut.h"
#include "TCanvas.h"
#include <iostream>


void RateEstimateVpt(TString infile="alldatacleaned.root")
//(TString infile="/net/hidsk0001/d00/scratch/frankma/data/HAZS/hazsv2-run152791to152957-unfiltered-jetoh-v1/merge/all.root")
//(TString infile="/net/hidsk0001/d00/scratch/frankma/data/HAZS/hazsv2-run152791to152957-unfiltered-jetoh-v1/merge/all.root")
{
   TChain * tree = new TChain("icPu5JetAnalyzer_clean/t");
  tree->Add(infile);
	tree->AddFriend("hltanalysis_clean/HltTree",infile);
	//  cout << "Total: " << tree->GetEntries() << endl; 

  TCut evtSel("Run==152957&&HLT_HIMinBiasHfOrBSC&&hiBin<40&&abs(jteta[0])<2");

  //TCut evtSel("HLT_HIMinBiasHfOrBSC&&hiBin<40");
   
   TCanvas *e1 = new TCanvas("e1","Rate Estimate vs. Threshold",200,10,700,500);
   TH1D * RJetPt = new TH1D("RJetPt",";Leading Jet p_{T} (GeV/c);count;",300,0,300);
   TH1D * JetPt = new TH1D("JetPt",";Leading Jet p_{T} (GeV/c);count;",300,0,300);
   tree->Draw("rawpt[0]>>RJetPt",evtSel,"goff");
   tree->Draw("jtpt[0]>>JetPt",evtSel,"goff");
   cout << "Integral: " << JetPt->Integral(0,101) << endl;

   TH1F * h4 = new TH1F("h4","",50,0,300);
   tree->Draw("LumiBlock>>h4",evtSel,"goff");
   Float_t R = 2000 ;

  Float_t TA = h4->GetEntries();


  const Int_t q= 3; 
  Double_t s[] = { .0360074, .00385337, .000838772};
  Double_t u[] = { 35, 50, 70 };
  TGraph *gt = new TGraph(q,u,s);

  const Int_t l= 3; 
  Double_t e[] = { .0190445, .00235729, .000490376 };
  Double_t r[] = { 35, 50, 70 };
  TGraph *gi = new TGraph(q,u,s);


   const Int_t n = 61;
   Float_t x[n], y[n], z[n], w[n], t[n];
   for (Int_t i=0;i<n;i++) {
     x[i] = 300-i*5; 
     y[i] = RJetPt->Integral(x[i],301);
     z[i] = R*y[i]/TA;
      w[i] = JetPt->Integral(x[i],301);
      t[i] = R*w[i]/TA;
     printf(" i %i %f %f %f \n",i,x[i],y[i],z[i]);
   }
   gr = new TGraph(n,x,z);
    gs = new TGraph(n,x,t);
     gr->SetLineColor(kRed);
     gs->SetLineColor(kBlue);

  gr->GetYaxis()->SetRangeUser(0.001,5000);
  // gr->SetLineWidth(2);
    gr->SetMarkerColor(kRed);
   gr->SetMarkerStyle(kOpenCircle);
   gs->SetMarkerColor(kBlue);
    gs->SetMarkerStyle(kOpenCircle);
   gr->SetTitle("");
   gr->GetXaxis()->SetTitle("Jet Pt Threshold (GeV/c)");
   gr->GetYaxis()->SetTitle("Rate Estimate (Hz)");
    gr->Draw("LAP");
  gt->SetMarkerStyle(kOpenSquare);
  // gt->Draw("LP");
  gt->SetMarkerColor(kBlue);

    gs->Draw("LP");

    e1->SetLogy();   

    TLatex Tl;
   Tl.SetTextSize(0.03);  
   float o, x1, x2;
   o = 0.90; x1 = 0.97; x2 = x1+0.2;

  
   //Tl.DrawLatex(82, 1550, "|#eta| < 2");

   TLegend *L = new TLegend(0.52292,0.675103,0.932471,0.919831);
   L->SetHeader("AllPhysics, |#eta| < 2, All Centrality" );
   L->SetBorderSize(0);
   L->SetFillStyle(0);
   L->AddEntry(gr,"Uncorrected p_{T}","pl");
   // L->AddEntry(gi,"HLT_HIJet (RelVal)","pl");
   L->AddEntry(gs,"Corrected p_{T}","pl");
   // L->AddEntry(gt,"HLT_HIJet","pl");
   L->Draw();

//Discussion: If we compare this macro the the "Accept Fraction" macro we see an apparent inconsistency. In particluar our delimiting left point values for this macro end in 1 or 6 (for example "21" for i = 4), however the integrated result is the same as that associated with the left point delimiting values (consisting of the multiples of 10) in the Accept Fraction Macro. For example, our i=4 lower jet energy is 21 Gev which yields an accept fraction of 0.116321. On the "Accept Fraction" Macro the lower jet energy is 20 GeV but this also yields an accept fraction of 0.116321. Moreoever if we tried to make the limiting energies the same in each macro (for example, by making ou i=4 correspond to 20 GeV) then we don't obtain consistent results between the macros at all. What is the problem? Well, in the "Accept Fraction" macro, energy is defined in discrete steps. So, although we define out lower limit as 20 GeV, we obtain our first point when the jet energy is greater than or equal to 21 GeV. Essentially by definining rawjtpt[0]>20, we have told the program to only accept/integrate values beyond 21. This is why the two are equal.  
}
