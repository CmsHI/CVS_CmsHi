/*
Plot GEN single muon and di-muon's mass, pt, phi, eta. File path is setted for Windows.
*/
#include <TROOT.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>
#include <sstream>
#include <iostream>

using namespace std;

int muonkine()
{
  TCanvas *c = new TCanvas("draw","draw",800,600);
  TStyle *style = new TStyle("Plain","plain style");
  style->SetOptStat(0);
  style->cd();
  
  // File processing
  const char *FNAME = "HE_gen_final";
  //const char *FNAME = "HydjetMBZ0Emb_final";
  stringstream sf;
  sf.str("");
  sf << "C:\\root\\macros\\0720\\" << FNAME << ".root";
  TFile *fdat = new TFile(sf.str().c_str());
  if(fdat->IsZombie()) { cout << "The root file cannot be openned.\n"; return 1; }

  TH1D *hpt[2];
  TH1D *hphi[2];
  TH1D *heta[2];
  TH1D *hmass;
  const char *SPNAME[2] = {"dimuon","single muon"};
  const char *HISTNAME[3] = {"pt","phi","eta"};

  // from ntuples, read dimuon
  for (int i=0; i<2; i++)
  {
    stringstream stmp;
    stmp.str("");
    stmp << SPNAME[i]<< " pt";
    hpt[i] = new TH1D(stmp.str().c_str(),stmp.str().c_str(),50,0,100);
    hpt[i]->SetMarkerStyle(20);
    hpt[i]->GetXaxis()->CenterTitle();
    hpt[i]->Sumw2();
    hpt[i]->GetXaxis()->SetTitle("p_{t}[GeV/c]");
    hpt[i]->Draw("p");
    stmp.str("");
    stmp << SPNAME[i]<< " eta" ;
    heta[i] = new TH1D(stmp.str().c_str(),stmp.str().c_str(),30,-3,3);
    heta[i]->SetMarkerStyle(20);
    heta[i]->GetXaxis()->CenterTitle();
    heta[i]->Sumw2();
    heta[i]->GetXaxis()->SetTitle("#eta[rad]");
    heta[i]->Draw("p");
    stmp.str("");
    stmp << SPNAME[i]<< " phi" ;
    hphi[i] = new TH1D(stmp.str().c_str(),stmp.str().c_str(),30,-3,3);
    hphi[i]->SetMarkerStyle(20);
    hphi[i]->GetXaxis()->CenterTitle();
    hphi[i]->Sumw2();
    hphi[i]->GetXaxis()->SetTitle("#phi[rad]");
    hphi[i]->Draw("p");
  }
  hmass = new TH1D("dimuon mass","dimuon mass",100,0,200);
  hmass->SetMarkerStyle(20);
  hmass->GetXaxis()->CenterTitle();
  hmass->Sumw2();
  hmass->GetXaxis()->SetTitle("mass[GeV/C^{2}]");
  hmass->Draw("p");

  TNtuple *ntuple_dimu= (TNtuple*)fdat->Get("demo/pnDimuGenInfo");
  Float_t s_dimueta, s_dimupt, s_dimuphi, s_dimum, s_mu1c, s_mu2c;
  ntuple_dimu->SetBranchAddress("dimueta",&s_dimueta);
  ntuple_dimu->SetBranchAddress("dimupt",&s_dimupt);
  ntuple_dimu->SetBranchAddress("dimuphi",&s_dimuphi);
  ntuple_dimu->SetBranchAddress("dimum",&s_dimum);
  ntuple_dimu->SetBranchAddress("mu1pdgid",&s_mu1c);
  ntuple_dimu->SetBranchAddress("mu2pdgid",&s_mu2c);
  Int_t s_ntry = ntuple_dimu->GetEntries();
  for (int i=0; i<s_ntry; i++)
  {
    ntuple_dimu->GetEntry(i);
    if (s_mu1c*s_mu2c < 0)
    {
      hmass->Fill(s_dimum);
      hpt[0]->Fill(s_dimupt);
      heta[0]->Fill(s_dimueta);
      hphi[0]->Fill(s_dimuphi);
    }
  }
  
  TNtuple *ntuple_sglmu = (TNtuple*)fdat->Get("demo/pnSinglemuGenInfo");
  Float_t s_sglmueta, s_sglmupt, s_sglmuphi, s_sglmum;
  ntuple_sglmu->SetBranchAddress("eta",&s_sglmueta);
  ntuple_sglmu->SetBranchAddress("pt",&s_sglmupt);
  ntuple_sglmu->SetBranchAddress("phi",&s_sglmuphi);
  s_ntry = ntuple_sglmu->GetEntries();
  for (int i=0; i<s_ntry; i++)
  {
    ntuple_sglmu->GetEntry(i);
    hpt[1]->Fill(s_sglmupt);
    heta[1]->Fill(s_sglmueta);
    hphi[1]->Fill(s_sglmuphi);
  }

  c->cd(); hmass->Draw("p");
  sf.str("");
  sf << "C:\\root\\macros\\" << FNAME << "_dimuon_mass.png";
  c->SaveAs(sf.str().c_str()); c->Clear();
  c->cd(); hpt[0]->Draw("p");
  sf.str("");
  sf << "C:\\root\\macros\\" << FNAME << "_dimuon_pt.png";
  c->SaveAs(sf.str().c_str()); c->Clear();
  c->cd(); heta[0]->Draw("p");
  sf.str("");
  sf << "C:\\root\\macros\\" << FNAME << "_dimuon_eta.png";
  c->SaveAs(sf.str().c_str()); c->Clear();
  c->cd(); hphi[0]->Draw("p");
  sf.str("");
  sf << "C:\\root\\macros\\" << FNAME << "_dimuon_phi.png";
  c->SaveAs(sf.str().c_str()); c->Clear();

  c->cd(); hpt[1]->Draw("p");
  sf.str("");
  sf << "C:\\root\\macros\\" << FNAME << "_singlemuon_pt.png";
  c->SaveAs(sf.str().c_str()); c->Clear();
  c->cd(); heta[1]->Draw("p");
  sf.str("");
  sf << "C:\\root\\macros\\" << FNAME << "_singlemuon_eta.png";
  c->SaveAs(sf.str().c_str()); c->Clear();
  c->cd(); hphi[1]->Draw("p");
  sf.str("");
  sf << "C:\\root\\macros\\" << FNAME << "_singlemuon_phi.png";
  c->SaveAs(sf.str().c_str()); c->Clear();
  
  fdat->Close();
  delete c;
  return 0;
}
