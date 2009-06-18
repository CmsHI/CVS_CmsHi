#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

#include "TH1D.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TNtuple.h"
#include "TLegend.h"

#include "TGraphAsymmErrors.h"
#include "CmsHiFunctions.h"

#define MAXPARTICLES 50000
#define MAXJETS 5000
#define MAXHITS 5000
#define MAXVTX 100
#define ETABINS 3 

using namespace std;

int getBin(double input, int size, const double* edges){

  int bin = -9;

  for(int i = 0; i< size; i++){
    double min = edges[i];

    if(input >= min) bin  = i;
    if(input < min ) break;    
  }
  
  if(bin < 0) cout<<"Warning : Bin not determined correctly - "<<bin<<endl;
  return bin;
}


struct Event{
  
  int event;
  float b;
  float npart;
  float ncoll;
  float nhard;
  
  int n[ETABINS];
   float ptav[ETABINS];
  
  int algos;

  float vx;
  float vy;
  float vz;
  float vr;



};

struct Particles{

  int np;
  float pt[MAXPARTICLES];
  float eta[MAXPARTICLES];
  float phi[MAXPARTICLES];
  int pdg[MAXPARTICLES];
  int chg[MAXPARTICLES];
  
};

struct Jets{
  
  int njet;

  float et[MAXJETS];
  float eta[MAXJETS];
  float phi[MAXJETS];
  float area[MAXJETS];
  
};

void analyze_events(char * infile = "/home/yilmaz/analysis/jets/4TeV/uncorrected/pythia_mixed_d20090513.root", char * outfile = "output.root"){

  int version = 0;
  double match = 0.15;
  double genJetEt = 20;
  
  TH1::SetDefaultSumw2();

  TFile* inf = new TFile(infile);
  TTree* tsub = dynamic_cast<TTree*>(inf->Get("genevent/hi"));
  TTree* treco = dynamic_cast<TTree*>(inf->Get("recoevent/hi"));

  TFile* outf = new TFile(outfile,"recreate");

  double x[6];
  double y[6];

  double etMax = 400000;

  cout<<"Begin"<<endl;

  const int nbBins = 1;
  const int nEtBins = 11;
  const int nEtaBins = 10;

  int color[17] = {1,6,2,3,4,1,2,2,1,1,4,4};

  int etStep = 3;
  int bStep = 2;

  int bBegin = 0;
  int etBegin = 3;

  double bBins[nbBins + 1] = {0,30};
  //  double bBins[nbBins + 1] = {0,7.145,10.105,12.373,14.283,17};
  double etBins[nEtBins + 1] = {0,40,45,50,55,60,65,70,75,80,100,200};
  double etaBins[nEtaBins + 1] = {0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5};

  double cone = 0.5;

  int maxEvents = 10000000;

  double etaMax = 3; //2.5;
  double etaMin = 2; //1.5;

  double binEt = 5;

  int nsize[3] = {20,10,5}; 

  TH1F* h1[nbBins];
  TH1F* h2[nbBins];


  for(int i1 = 0; i1 < nbBins; ++i1){
    
    h1[i1] = new TH1F(Form("h1_et%02d",i1,(int)(version)),";E_{T} [GeV];GenJets",200,0,120);
    h2[i1] = new TH1F(Form("h2_et%02d",i1,(int)(version)),";#eta;GenJets",100,-5,5);  
  }
  

  Jets recojet;
   Jets genjet;

   Particles par;

   Event event;

   // Event Info - Same for both jet collections
   treco->SetBranchAddress("b",&event.b);
 
   treco->SetBranchAddress("npart",&event.npart);
   treco->SetBranchAddress("ncoll",&event.ncoll);
   treco->SetBranchAddress("nhard",&event.nhard);

   treco->SetBranchAddress("vx",&event.vx);
   treco->SetBranchAddress("vy",&event.vy);
   treco->SetBranchAddress("vz",&event.vz);
   treco->SetBranchAddress("vr",&event.vr);

   treco->SetBranchAddress("n",event.n);
   treco->SetBranchAddress("ptav",event.ptav);


   // MC Info - Same for both jet collections 

   treco->SetBranchAddress("np",&par.np);
   treco->SetBranchAddress("par_pt",par.pt);
   treco->SetBranchAddress("par_eta",par.eta);
   treco->SetBranchAddress("par_phi",par.phi);
   treco->SetBranchAddress("pdg",par.pdg);
   treco->SetBranchAddress("chg",par.chg);

   // Reconstructed Jets
   treco->SetBranchAddress("njet",&recojet.njet);
   treco->SetBranchAddress("et",recojet.et);
   treco->SetBranchAddress("eta",recojet.eta);
   treco->SetBranchAddress("phi",recojet.phi);
   treco->SetBranchAddress("area",recojet.area);

   // Gen Jets
   tsub->SetBranchAddress("njet",&genjet.njet);
   tsub->SetBranchAddress("et",genjet.et);
   tsub->SetBranchAddress("eta",genjet.eta);
   tsub->SetBranchAddress("phi",genjet.phi);
   tsub->SetBranchAddress("area",genjet.area);

   double ptCut = 0;

   // Event Loop
   int nevents = tsub->GetEntries();
   cout<<"Number of Events : "<<nevents<<endl;
   for(int i = 0; i< nevents && i < maxEvents; ++i){    
     tsub->GetEntry(i);
     treco->GetEntry(i);
     
     int bbin = getBin(event.b,nbBins,bBins);

     //Loop over Particles
     for(int j2 = 0; j2< genjet.njet; ++j2){
       if(genjet.et[j2] < genJetEt) continue;
       
       //       if(par.chg == 0) continue;
       double et = genjet.et[j2];
       double eta = genjet.eta[j2];
	 
       h1[bbin]->Fill(et);
       h2[bbin]->Fill(eta);
     }
   }
   
   for(int i1 = 0; i1 < nbBins; ++i1){

     h2[i1]->SetMarkerColor(color[i1]);
     h1[i1]->Scale(nbBins*1./(nevents*h1[i1]->GetBinWidth(5)));
     h2[i1]->Scale(nbBins*1./(nevents*h2[i1]->GetBinWidth(5)));
   }

   TCanvas* c1 = new TCanvas(Form("c1_et%02d",(int)(version)),Form("c1_et%02d",(int)(version)),400,400);

   //   h2[0]->SetMaximum(3000);

   h2[0]->SetMinimum(0);

   h1[0]->Draw();

   for(int i1 = 0; i1 < nbBins; ++i1){
     h1[i1]->Draw("same");

   }

   TCanvas* c3 = new TCanvas(Form("c3_et%02d",(int)(version)),Form("c3_et%02d",(int)(version)),400,400);


   h2[0]->Draw();

   for(int i1 = 0; i1 < nbBins; ++i1){
     h2[i1]->Draw("same");     
   }

}
