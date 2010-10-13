/*
1. Superimpose 3 root files with reco object.
2. Superimpose sim and reco object from the MC sample.
*/
#include <TROOT.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TText.h>
#include <TLegend.h>
#include <sstream>
#include <iostream>

using namespace std;

int superimp ()
{
  TStyle *style = new TStyle("Plain","plain style");
  style->SetOptStat(0);
  style->cd();

  TCanvas *c[3];
  TFile *fdat[3];
  const char *FNAME[3] = {"HydjetMBZ0Emb","MinBias_skim0","HardEnriched_vtxcor_ZS_skim0"};
  
  // histgram : hpt[HE,MB,HYD][glb,sta,trk]
  TH1D *hpt[3][3];
  TH1D *hphi[3][3];
  TH1D *heta[3][3];
  double max[3]={0};
  const char *MUNAME[3] = {"global","sta","other"};
  const char *MUNAME2[3] = {"Global","Standalone","Tracker"};
  const char *SPNAME[3] = {"Hydjet Z0 embedding","Minbias skim0","Hard Enrchied ZS skim0"};
  const char *HISTNAME[3] = {"pt","phi","eta"};
  
  // from dimuon ntuples
  TH1D *hreco_diMLike[3];
  TH1D *hreco_diMUlike[3];
  TH1D *hsim_diMUlike[3];
  for (int i=0; i<3; i++)
  {
    stringstream stmp;
    stmp.str("");
    stmp << "Dimuon mass like reco " << SPNAME[i];
    hreco_diMLike[i] = new TH1D(stmp.str().c_str(),"",100,0,200);
    stmp.str("");
    stmp << "Dimuon mass unlike reco " << SPNAME[i];
    hreco_diMUlike[i] = new TH1D(stmp.str().c_str(),"",100,0,200);
    stmp.str("");
    stmp << "Dimuon mass unlike sim " << SPNAME[i];
    hsim_diMUlike[i] = new TH1D(stmp.str().c_str(),"",100,0,200);
  }

  // File processing
  for (int f=0; f<3; f++)
  {
    stringstream sf;
    sf.str("");
    sf << "C:\\root\\macros\\" << FNAME[f] << "_withgen.root";
    fdat[f] = new TFile(sf.str().c_str());
    if(fdat[f]->IsZombie()) { cout << "The root file cannot be openned.\n"; return 1; }

    //glb,sta,trk single muon loop
    for (int i=0; i<3; i++)
    {
      stringstream stmp;
      stmp.str("");
      stmp << "demo/phPt_" << MUNAME[i] << "Mu";
      fdat[f]->GetObject(stmp.str().c_str(),hpt[f][i]);
      hpt[f][i]->SetLineColor(f+1);
      if (f == 2) hpt[f][i]->SetLineColor(4);
      hpt[f][i]->SetMarkerColor(f+1);
      if (f == 2) hpt[f][i]->SetMarkerColor(4);
      hpt[f][i]->SetMarkerStyle(f+20);
      hpt[f][i]->Rebin(2);
      hpt[f][i]->Scale(1/hpt[f][i]->GetEntries());
      if (hpt[f][i]->GetMaximum() > max[0]) max[0] = hpt[f][i]->GetMaximum();

      stmp.str("");
      stmp << "demo/phPhi_" << MUNAME[i] << "Mu";
      fdat[f]->GetObject(stmp.str().c_str(),hphi[f][i]);
      hphi[f][i]->SetLineColor(f+1);
      if (f == 2) hphi[f][i]->SetLineColor(4);
      hphi[f][i]->SetMarkerColor(f+1);
      if (f == 2) hphi[f][i]->SetMarkerColor(4);
      hphi[f][i]->SetMarkerStyle(f+20);
      hphi[f][i]->Rebin(2);
      hphi[f][i]->Scale(1/hphi[f][i]->GetEntries());
      if (hphi[f][i]->GetMaximum() > max[1]) max[1] = hphi[f][i]->GetMaximum();

      stmp.str("");
      stmp << "demo/phEta_" << MUNAME[i] << "Mu";
      fdat[f]->GetObject(stmp.str().c_str(),heta[f][i]);
      heta[f][i]->SetLineColor(f+1);
      if (f == 2) heta[f][i]->SetLineColor(4);
      heta[f][i]->SetMarkerColor(f+1);
      if (f == 2) heta[f][i]->SetMarkerColor(4);
      heta[f][i]->SetMarkerStyle(f+20);
      heta[f][i]->Scale(1/heta[f][i]->GetEntries());
      if (heta[f][i]->GetMaximum() > max[2]) max[2] = heta[f][i]->GetMaximum();
    }

    //reco::dimuon ntuples
    TNtuple *ntuple_reco = (TNtuple*)fdat[f]->Get("demo/pnDimuPairInfo");
    Float_t r_dimupt, r_dimum, r_mu1c, r_mu2c;
    ntuple_reco->SetBranchAddress("dimupt",&r_dimupt);
    ntuple_reco->SetBranchAddress("dimum",&r_dimum);
    ntuple_reco->SetBranchAddress("mu1charge",&r_mu1c);
    ntuple_reco->SetBranchAddress("mu2charge",&r_mu2c);
    Int_t r_ntry = ntuple_reco->GetEntries();
    for (int i=0; i<r_ntry; i++)
    {
      ntuple_reco->GetEntry(i);
      if (r_dimupt > 12)
      {
        if (r_mu1c*r_mu2c > 0)  //like sign
          hreco_diMLike[f]->Fill(r_dimum);
        else //unlike sign
          hreco_diMUlike[f]->Fill(r_dimum);
      }
    }
    
    //sim dimuon ntuples
    TNtuple *ntuple_sim = (TNtuple*)fdat[f]->Get("demo/pnDimuSimInfo");
    Float_t s_dimupt, s_dimum, s_mu1c, s_mu2c;
    ntuple_sim->SetBranchAddress("dimupt",&s_dimupt);
    ntuple_sim->SetBranchAddress("dimum",&s_dimum);
    ntuple_sim->SetBranchAddress("mu1pdgid",&s_mu1c);
    ntuple_sim->SetBranchAddress("mu2pdgid",&s_mu2c);
    Int_t s_ntry = ntuple_sim->GetEntries();
    for (int i=0; i<s_ntry; i++)
    {
      ntuple_sim->GetEntry(i);
      if (s_dimupt > 12)
      {
        if (s_mu1c*s_mu2c < 0)  //unlike sign
          hsim_diMUlike[f]->Fill(s_dimum);
      }
    }
    
    delete ntuple_sim;
    delete ntuple_reco;
  } //end of read objects in the root file

  // Draw single muon distributions
  for (int i=0; i<3; i++) //glb,sta,trk loop
  {
    TLegend *leg_pt, *leg_phi, *leg_eta;
    stringstream stmp;
    
    c[0] = new TCanvas("pt","pt",800,600);
    c[0]->SetLogy();
    c[0]->cd(); leg_pt = new TLegend(0.58,0.68,0.86,0.8);
    leg_pt->SetTextSize(0.035);
    leg_pt->SetFillColor(10); leg_pt->SetBorderSize(0);
    hpt[0][i]->SetMaximum(max[0]*2); hpt[0][i]->GetXaxis()->CenterTitle();
    stmp.str(""); stmp << MUNAME2[i];
    hpt[0][i]->SetTitle(stmp.str().c_str()); hpt[0][i]->Draw();
    leg_pt->AddEntry(hpt[0][i],SPNAME[0],"lp");

    c[1] = new TCanvas("phi","phi",800,600);
    c[1]->cd(); leg_phi = new TLegend(0.58,0.31,0.86,0.43);
    leg_phi->SetTextSize(0.035);
    leg_phi->SetFillColor(10); leg_phi->SetBorderSize(0);
    hphi[0][i]->SetMaximum(max[1]*1.2); hphi[0][i]->GetXaxis()->CenterTitle();
    stmp.str(""); stmp << MUNAME2[i];
    hphi[0][i]->SetTitle(stmp.str().c_str()); hphi[0][i]->Draw();
    leg_phi->AddEntry(hphi[0][i],SPNAME[0],"lp");

    c[2] = new TCanvas("mass","mass",800,600);
    c[2]->cd(); leg_eta = new TLegend(0.58,0.75,0.86,0.87);
    leg_eta->SetTextSize(0.035);
    leg_eta->SetFillColor(10); leg_eta->SetBorderSize(0);
    heta[0][i]->SetMaximum(max[2]*1.2); heta[0][i]->GetXaxis()->CenterTitle();
    stmp.str(""); stmp << MUNAME2[i];
    heta[0][i]->SetTitle(stmp.str().c_str());
    heta[0][i]->Draw();
    leg_eta->AddEntry(heta[0][i],SPNAME[0],"lp");

    for (int f=1; f<3; f++) //file loop
    {
      c[0]->cd(); hpt[f][i]->Draw("same");
      c[1]->cd(); hphi[f][i]->Draw("same");
      c[2]->cd(); heta[f][i]->Draw("same");
      
      stmp.str(""); stmp << SPNAME[f];
      leg_pt->AddEntry(hpt[f][i],stmp.str().c_str(),"lp");
      leg_phi->AddEntry(hphi[f][i],stmp.str().c_str(),"lp");
      leg_eta->AddEntry(heta[f][i],stmp.str().c_str(),"lp");
    }    
    c[0]->cd(); leg_pt->Draw();
    c[1]->cd(); leg_phi->Draw();
    c[2]->cd(); leg_eta->Draw();
    
    for (int j=0; j<3; j++)
    {     
      stmp.str("");
      stmp << "C:\\root\\macros\\" << MUNAME[i] << "_" << HISTNAME[j] << ".png";
      c[j]->SaveAs(stmp.str().c_str());
      c[j]->Clear();
      delete c[j];
    }
    delete leg_pt;
    delete leg_phi;
    delete leg_eta;
  }
  
  // Draw dimuon mass distributions from reco
  for (int f=0; f<3; f++)
  {
    double max1 = 0;
    if (hreco_diMLike[f]->GetMaximum() > hreco_diMUlike[f]->GetMaximum())
      max1 = hreco_diMLike[f]->GetMaximum();
    else max1 = hreco_diMUlike[f]->GetMaximum();
    
    TLegend *leg = new TLegend(0.58,0.75,0.86,0.87);
    leg->SetFillColor(10); leg->SetBorderSize(0);
    leg->SetTextSize(0.035);
    c[f] = new TCanvas(SPNAME[f],"",800,600); c[f]->cd();
    hreco_diMLike[f]->SetLineColor(2);
    hreco_diMLike[f]->SetMarkerColor(2);
    hreco_diMLike[f]->SetMarkerStyle(20);
    hreco_diMLike[f]->SetTitle(SPNAME[f]);
    hreco_diMLike[f]->GetXaxis()->SetTitle("dimuon mass [GeV/c^{2}]");
    hreco_diMLike[f]->GetXaxis()->CenterTitle();
    hreco_diMLike[f]->SetMaximum(max1*1.2);
    hreco_diMLike[f]->Sumw2();
    hreco_diMLike[f]->Draw("p");
    hreco_diMUlike[f]->SetMarkerStyle(21);
    hreco_diMUlike[f]->Sumw2();
    hreco_diMUlike[f]->Draw("same,p");
    leg->AddEntry(hreco_diMLike[f],"Like sign reco dimuon","lp");
    leg->AddEntry(hreco_diMUlike[f],"Unlike sign reco dimuon","lp");
    leg->Draw();
    
    stringstream stmp;
    stmp.str("");
    stmp << "C:\\root\\macros\\" << SPNAME[f] << "_recoDimuon.png";
    c[f]->SaveAs(stmp.str().c_str());
    c[f]->Clear();
    delete c[f];
  }

  // Draw dimuon mass distributions from reco and sim
  for (int f=0; f<1; f++)
  {
    double max1=0;
    if (hsim_diMUlike[f]->GetMaximum() > hreco_diMUlike[f]->GetMaximum())
      max1 = hsim_diMUlike[f]->GetMaximum();
    else max1 = hreco_diMUlike[f]->GetMaximum();

    TLegend *leg = new TLegend(0.58,0.75,0.86,0.87);
    leg->SetFillColor(10); leg->SetBorderSize(0);
    leg->SetTextSize(0.035);
    c[f] = new TCanvas(SPNAME[f],"",800,600); c[f]->cd();
    hsim_diMUlike[f]->SetLineColor(2);
    hsim_diMUlike[f]->SetMarkerColor(2);
    hsim_diMUlike[f]->SetMarkerStyle(20);
    hsim_diMUlike[f]->GetXaxis()->SetTitle("dimuon mass [GeV/c^{2}]");
    hsim_diMUlike[f]->GetXaxis()->CenterTitle();
    hsim_diMUlike[f]->SetMaximum(max1*1.2);
    hsim_diMUlike[f]->SetTitle(SPNAME[f]);
    hsim_diMUlike[f]->Sumw2();
    hsim_diMUlike[f]->Draw("p");
    hreco_diMUlike[f]->SetMarkerStyle(21);
    hreco_diMUlike[f]->Sumw2();
    hreco_diMUlike[f]->Draw("same,p");
    leg->AddEntry(hsim_diMUlike[f],"Unlike sign sim dimuon","lp");
    leg->AddEntry(hreco_diMUlike[f],"Unlike sign reco dimuon","lp");
    leg->Draw();
    
    stringstream stmp;
    stmp.str("");
    stmp << "C:\\root\\macros\\" << SPNAME[f] << "_simDimuon.png";
    c[f]->SaveAs(stmp.str().c_str());
    c[f]->Clear();
    delete c[f];
  }

  
  for (int i=0; i<3; i++)
  { fdat[i]->Close(); }
  
  return 0;
}
