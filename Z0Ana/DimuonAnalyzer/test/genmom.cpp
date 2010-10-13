/*
Read gen di-muon's mother pid and plot di-muon mass plot with respect to their mother particle. 
*/

#include <TROOT.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TText.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Bool_t isBmeson(float pid);
Bool_t isDmeson(float pid);
Bool_t isBaryon(float pid);

int genmom()
{
  TCanvas *c = new TCanvas("draw","draw",800,600);
  
  // File processing
  const char *FNAME = "HydjetMB";
  stringstream sf;
  sf.str("");
  sf << FNAME << ".root";
  TFile *fdat = new TFile(sf.str().c_str());
  if(fdat->IsZombie()) { cout << "The root file cannot be openned.\n"; return 1; }

  TH1D *hpt[2];
  TH1D *hphi[2];
  TH1D *heta[2];
  TH1D *hgen[10];//0:23, 1:94-13, 2:B mesons, 3:D mesons, 4:B or D, 5:upsilons, 6:jpsis, 7:eta, 8:lambda+sigma, 9:other 
  TH1D *hmass;
  const char *SPNAME[2] = {"dimuon","single muon"};
  const char *HISTNAME[3] = {"pt","phi","eta"};

  // from ntuples, read dimuon
  for (int i=0; i<1; i++)
  {
    stringstream stmp;
    stmp.str("");
    stmp << SPNAME[i]<< " pt";
    hpt[i] = new TH1D(stmp.str().c_str(),stmp.str().c_str(),50,0,100);
    hpt[i]->SetMarkerStyle(20);
    hpt[i]->GetXaxis()->CenterTitle();
    hpt[i]->Sumw2();
    hpt[i]->GetXaxis()->SetTitle("p_{t}[GeV/c]");

    stmp.str("");
    stmp << SPNAME[i]<< " eta" ;
    heta[i] = new TH1D(stmp.str().c_str(),stmp.str().c_str(),30,-3,3);
    heta[i]->SetMarkerStyle(20);
    heta[i]->GetXaxis()->CenterTitle();
    heta[i]->Sumw2();
    heta[i]->GetXaxis()->SetTitle("#eta[rad]");

    stmp.str("");
    stmp << SPNAME[i]<< " phi" ;
    hphi[i] = new TH1D(stmp.str().c_str(),stmp.str().c_str(),30,-3,3);
    hphi[i]->SetMarkerStyle(20);
    hphi[i]->GetXaxis()->CenterTitle();
    hphi[i]->Sumw2();
    hphi[i]->GetXaxis()->SetTitle("#phi[rad]");
  }
  
  for (int i=0; i<10; i++)
  {
    stringstream stmp;
    stmp.str("");
    stmp << SPNAME[0]<< " mom mass " << i ;
    hgen[i] = new TH1D(stmp.str().c_str(),stmp.str().c_str(),100,0,200);
    hgen[i]->SetMarkerStyle(20);
    //if (i!=1) hgen[i]->SetMarkerColor(i+2);
    //else
    hgen[i]->SetMarkerColor(4);
    hgen[i]->GetXaxis()->CenterTitle();
    hgen[i]->Sumw2();
    hgen[i]->GetXaxis()->SetTitle("mass[GeV/c^{2}]");
  }
  hmass = new TH1D("dimuon mass","dimuon mass",100,0,200);
  hmass->SetMarkerStyle(20);
  hmass->GetXaxis()->CenterTitle();
  hmass->Sumw2();
  hmass->GetXaxis()->SetTitle("mass[GeV/c^{2}]");

  TNtuple *ntuple_dimu= (TNtuple*)fdat->Get("demo/pnDimuGenInfo");
  Float_t s_dimueta, s_dimupt, s_dimuphi, s_dimum, s_mu1c, s_mu2c, mom1, mom1stat, mom2, mom2stat;
  ntuple_dimu->SetBranchAddress("dimueta",&s_dimueta);
  ntuple_dimu->SetBranchAddress("dimupt",&s_dimupt);
  ntuple_dimu->SetBranchAddress("dimuphi",&s_dimuphi);
  ntuple_dimu->SetBranchAddress("dimum",&s_dimum);
  ntuple_dimu->SetBranchAddress("mu1pdgid",&s_mu1c);
  ntuple_dimu->SetBranchAddress("mu2pdgid",&s_mu2c);
  ntuple_dimu->SetBranchAddress("momid0_0",&mom1);
  ntuple_dimu->SetBranchAddress("momstat0_0",&mom1stat);
  ntuple_dimu->SetBranchAddress("momid1_0",&mom2);
  ntuple_dimu->SetBranchAddress("momstat1_0",&mom2stat);
  Int_t s_ntry = ntuple_dimu->GetEntries();
  for (int i=0; i<s_ntry; i++)
  {
    ntuple_dimu->GetEntry(i);
    if (s_mu1c*s_mu2c < 0)
    {
      hpt[0]->Fill(s_dimupt);
      heta[0]->Fill(s_dimueta);
      hphi[0]->Fill(s_dimuphi);
      if (s_dimupt > 12)
      {
        hmass->Fill(s_dimum);
        if (mom1 == 23 && mom2 == 23)
          hgen[0]->Fill(s_dimum);
        else if ( (abs((int)mom1)==94 && abs((int)mom2)==13 )||(abs((int)mom2)==94 && abs((int)mom1)==13) )
          hgen[1]->Fill(s_dimum); 
        else if ( isBmeson(mom1) == true && isBmeson(mom2) == true )
          hgen[2]->Fill(s_dimum);
        else if ( isDmeson(mom1) == true && isDmeson(mom2) == true )
          hgen[3]->Fill(s_dimum);
        else if ( isBmeson(mom1) || isDmeson(mom1) || isBmeson(mom2) || isDmeson(mom2) )
          hgen[4]->Fill(s_dimum);
        else if ( mom1 == 553 && mom2 == 553 )
          hgen[5]->Fill(s_dimum);
        else if ( mom1 == 443 && mom2 == 443 )
          hgen[6]->Fill(s_dimum);
        else if ( mom1 == 221 && mom2 == 221)
          hgen[7]->Fill(s_dimum);
        else if ( isBaryon(mom1) || isBaryon(mom2) )
          hgen[8]->Fill(s_dimum);
        else
          hgen[9]->Fill(s_dimum);
      }
    }
  }
  
/*  TNtuple *ntuple_sglmu = (TNtuple*)fdat->Get("demo/pnSinglemuGenInfo");
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
  
  c->cd(); hpt[0]->Draw("p");
  sf.str("");
  sf << "C:\\root\\macros\\0720\\" << FNAME << "_dimuon_pt.png";
  c->SaveAs(sf.str().c_str()); c->Clear();
  c->cd(); heta[0]->Draw("p");
  sf.str("");
  sf << "C:\\root\\macros\\0720\\" << FNAME << "_dimuon_eta.png";
  c->SaveAs(sf.str().c_str()); c->Clear();
  c->cd(); hphi[0]->Draw("p");
  sf.str("");
  sf << "C:\\root\\macros\\0720\\" << FNAME << "_dimuon_phi.png";
  c->SaveAs(sf.str().c_str()); c->Clear();*/

  c->cd(); hmass->Draw("p");
  sf.str("");
//  sf << "C:\\root\\macros\\0720\\" << FNAME << "_dimuon_mass.png";
  sf << FNAME << "_dimuon_mass.png";
  c->SaveAs(sf.str().c_str()); c->Clear();
 
  for (int i=0; i<10; i++)
  {
    c->cd(); hmass->Draw("p");
    hgen[i]->Draw("same,p");
    sf.str("");
    sf << hgen[i]->GetEntries();
    TText txt(0,0,sf.str().c_str());
    txt.SetNDC();
    txt.SetX(0.7);
    txt.SetY(0.7);
    txt.Draw();
    sf.str("");
    sf << FNAME << "_dimuon_mass_"<<i <<".png";
    c->SaveAs(sf.str().c_str()); c->Clear();
  }
  
/*  c->cd(); hpt[1]->Draw("p");
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
  c->SaveAs(sf.str().c_str()); c->Clear();*/
  
  fdat->Close();
  delete c;
  return 0;
}

Bool_t isBmeson(float pid)
{
  Int_t barray[]={511,531,521,-511,-531,-521};
  vector<float> blist(barray,barray+sizeof(barray)/sizeof(Int_t));
  vector<float>::iterator it;
  
  it = find(blist.begin(),blist.end(),pid);
  if (it == blist.end()) return false;
  else return true;
}

Bool_t isDmeson(float pid)
{
  Int_t darray[]={411,421,431,-411,-421,-431};
  vector<float> dlist(darray,darray+sizeof(darray)/sizeof(Int_t));
  vector<float>::iterator it;
  
  it = find(dlist.begin(),dlist.end(),pid);
  if (it == dlist.end()) return false;
  else return true;
}

Bool_t isBaryon(float pid)
{
  Int_t arr[]={4122,5232,5122,-4122,-5232,-5122};
  vector<float> blist(arr,arr+sizeof(arr)/sizeof(Int_t));
  vector<float>::iterator it;
  
  it = find(blist.begin(),blist.end(),pid);
  if (it == blist.end()) return false;
  else return true;
}
