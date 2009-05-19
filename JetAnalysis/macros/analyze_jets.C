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

double analyze_with_cut(int version, TTree* tsub, TTree* treco, double match = 0.25, double jetEtMin = 0, double jetEtMax = 999999, double bMin = 0, double bMax = 500, double genJetEt = 0);

void analyze_jets(char * infile = "/home/yilmaz/analysis/jets/4TeV/pythia_mixed_d20090513.root", char * outfile = "output.root"){

  TH1::SetDefaultSumw2();

  TFile* inf = new TFile(infile);
  TTree* tsub = dynamic_cast<TTree*>(inf->Get("genevent/hi"));
  TTree* treco = dynamic_cast<TTree*>(inf->Get("recoevent/hi"));

  /*
  TChain * treco = new TChain("recoevent/hi");
  TChain * tsub = new TChain("genevent/hi");
  TChain * tsig = new TChain("signalevent/hi");

  treco->Add(infile);
  tsub->Add(infile);
  tsig->Add(infile);
  */

  TFile* outf = new TFile(outfile,"recreate");

  double x[6];
  double y[6];

  double etMax = 400000;

  //  analyze_with_cut(102,tsub,treco,0.25,0,700,0,20,30);
  //  analyze_with_cut(102,tsig,treco,0.125,0,700,0,200,20);

  if(1){
    analyze_with_cut(201,tsub,treco,0.15,0,400,0,7.145,20);
    analyze_with_cut(203,tsub,treco,0.15,0,400,10.105,12.373,20);
    analyze_with_cut(205,tsub,treco,0.15,0,400,14.283,30,20);
  }

  if(1){
    analyze_with_cut(101,tsub,treco,0.15,35,40,0,20,20);    
    analyze_with_cut(102,tsub,treco,0.15,40,45,0,20,20);    
    analyze_with_cut(103,tsub,treco,0.15,45,50,0,20,20);
    analyze_with_cut(104,tsub,treco,0.15,55,60,0,20,20);
    analyze_with_cut(105,tsub,treco,0.15,65,70,0,20,20);
    analyze_with_cut(106,tsub,treco,0.15,75,80,0,20,20);
    analyze_with_cut(107,tsub,treco,0.15,80,200,0,20,20);
  }


  if(0){
    analyze_with_cut(4501,tsub,treco,0.15,45,50,0,7.145,20);
    analyze_with_cut(4502,tsub,treco,0.15,45,50,7.145,10.105,20);
    analyze_with_cut(4503,tsub,treco,0.15,45,50,10.105,12.373,20);
    analyze_with_cut(4504,tsub,treco,0.15,45,50,12.373,14.283,20);
    analyze_with_cut(4505,tsub,treco,0.15,45,50,14.283,20,20);
  }


  if(0){
    analyze_with_cut(1,tsub,treco,0.15,50,55,0,7.145,20);
    analyze_with_cut(1,tsub,treco,0.15,50,55,7.145,10.105,20);
    analyze_with_cut(1,tsub,treco,0.15,50,55,10.105,12.373,20);
    analyze_with_cut(1,tsub,treco,0.15,50,55,12.373,14.283,20);
    analyze_with_cut(1,tsub,treco,0.15,50,55,14.283,20,20);
  }

  if(1){
    analyze_with_cut(5501,tsub,treco,0.15,55,60,0,7.145,20);
    analyze_with_cut(5502,tsub,treco,0.15,55,60,7.145,10.105,20);
    analyze_with_cut(5503,tsub,treco,0.15,55,60,10.105,12.373,20);
    analyze_with_cut(5504,tsub,treco,0.15,55,60,12.373,14.283,20);
    analyze_with_cut(5505,tsub,treco,0.15,55,60,14.283,20,20);
  }

  if(0){
    analyze_with_cut(1,tsub,treco,0.15,55,60,0,7.145,20);
    analyze_with_cut(1,tsub,treco,0.15,55,60,7.145,10.105,20);
    analyze_with_cut(1,tsub,treco,0.15,55,60,10.105,12.373,20);
    analyze_with_cut(1,tsub,treco,0.15,55,60,12.373,14.283,20);
    analyze_with_cut(1,tsub,treco,0.15,55,60,14.283,20,20);
  }


  if(0){
    analyze_with_cut(21,tsub,treco,0.3,0,500,0,20,20);
    analyze_with_cut(22,tsub,treco,0.3,0,500,20,100,20);
    analyze_with_cut(23,tsub,treco,0.3,0,500,100,250,20);
    analyze_with_cut(24,tsub,treco,0.3,0,500,250,600,20);
  }

  /*

  TGraph* g1 = new TGraph(6,x,y);

  TCanvas* c1 = new TCanvas();
  g1->Draw("a*");

  g1->Write();
  c1->Write();

  TCanvas* c5 = new TCanvas("c5","c5",400,400);
  tsub->Draw("njet");
  c5->Print("nsubjets.gif");

  TCanvas* c6 = new TCanvas("c6","c6",400,400);
  treco->Draw("njet");
  c6->Print("nrecojets.gif");

  TCanvas* c7 = new TCanvas("c7","c7",400,400);
  tsub->Draw("et");
  c7->Print("subjet_et.gif");

  TCanvas* c8 = new TCanvas("c8","c8",400,400);
  treco->Draw("et");
  c8->Print("recojet_et.gif");

  */


}

double analyze_with_cut(int version, TTree* tsub, TTree* treco, double match, double jetEtMin, double jetEtMax, double bMin, double bMax, double genJetEt){
  cout<<"Begin"<<endl;

  double jetEtCutMax = 9999999;
  double jetEtCutMin = 0;

  double bBins[6] = {0,7.145,10.105,12.373,14.283,17};

  double cone = 0.5;

  int maxEvents = 100000;

  double etaMax = 3; //2.5;
  double etaMin = 2; //1.5;

  double etMax = 150;
  double binEt = 5;

  int nsize[3] = {20,10,5}; 

   TH1F* h1 = new TH1F(Form("h1_et%02d",(int)(version)),"Di-Jet Correlation;#Delta R;jets",200,0,6);
   TH1F* h2 = new TH1F(Form("h2_et%02d",(int)(version)),"#Delta R between RecoJets and GenJets;#Delta R;jet pairs",100,0,1);

   TH2F* hEtR = new TH2F(Form("hEtR%02d",(int)(version)),"#Delta E_{T} vs #Delta R between RecoJets and GenJets;#Delta R;(E_{T}^{GenJet} - E_{T}^{RecoJet})/E_{T}^{GenJet}",100,0,0.5,100,-2.5,2.5);//-etMax/1.2,etMax/1.2);

   TH1F* hres = new TH1F(Form("hres_et%02d",(int)(version)),"Jet Energy Resolution;E_{T}^{CaloJet}-E_{T}^{GenJet}/E_{T}^{GenJet};jets",200,-2.5,2.5);

   TH1F* hVtx = new TH1F(Form("Vertex",(int)(version)),"Vertex;v_{z}[cm];events",40,-20,20);
   TH1F* hB = new TH1F(Form("ImpactParameter",(int)(version)),"Impact Parameter;b[fm];events",50,0,20);

   //   TH2F* het = new TH2F(Form("het_et%02d",(int)(version)),";E_{T}^{GenJet};E_{T}^{CaloJet} [GeV]",50,0,200,50,0,200);
   TH2F* het = new TH2F(Form("het_et%02d",(int)(version)),";E_{T}^{GenJet};E_{T}^{CaloJet} [GeV]",100,0,etMax,100,0,etMax);
   TH2F* hnjet = new TH2F(Form("hnjet_et%02d",(int)(version)),";#_{GenJet};#_{CaloJet} [GeV]",100,0,50,100,0,50);

   TH1F* heff1 = new TH1F(Form("heff1_et%02d",(int)(version)),"Jet Finding Efficiency;GenJet E_{T} [GeV];efficiency",(int)(etMax/binEt),0,etMax);
   TH1F* heff2 = new TH1F(Form("heff2_et%02d",(int)(version)),"Jet Finding Efficiency;GenJet E_{T} [GeV];efficiency",(int)(etMax/binEt),0,etMax);
   TH1F* heff3 = new TH1F(Form("heff3_et%02d",(int)(version)),"Ratio of efficiencies;GenJet E_{T} [GeV];ratio",(int)(etMax/binEt),0,etMax);

   TH1F* hEffPad = new TH1F(Form("hEffPad_et%02d",(int)(version)),"Jet Finding Efficiency;GenJet E_{T} [GeV];efficiency",(int)(etMax/binEt),0,etMax);
   TH1F* hFakePad = new TH1F(Form("hFakePad_et%02d",(int)(version)),"Fake Jets;CaloJet E_{T} [GeV];N_{Fake Jets}/N_{CaloJets}",(int)(etMax/binEt),0,etMax);


   TH1F* hfake1 = new TH1F(Form("hfake1_et%02d",(int)(version)),"N_{Fake Jets}/N_{CaloJets};CaloJet E_{T} [GeV];fake",(int)(etMax/binEt),0,etMax);

   TH1F* hcaloet = new TH1F(Form("hcaloet_et%02d",(int)(version)),";E_{T} [GeV];jets",(int)(etMax/binEt),0,etMax);
   TH1F* hgenet = new TH1F(Form("hgenet_et%02d",(int)(version)),";E_{T} [GeV];jets",(int)(etMax/binEt),0,etMax);

   TH1F* bMatched = new TH1F(Form("hbMatched_et%02d",(int)(version)),";b [fm];jets",10,0,20);
   TH1F* bAll = new TH1F(Form("hbAll_et%02d",(int)(version)),";b [fm];jets",10,0,20);

   TH1F* nPartMatched = new TH1F(Form("hNpartMatched_et%02d",(int)(version)),";N_{part};efficiency",10,0,400);
   TH1F* nPartAll = new TH1F(Form("hNpartAll_et%02d",(int)(version)),";N_{part};efficiency",10,0,400);


   TH1F* bPad = new TH1F(Form("hbPad_et%02d",(int)(version)),";b [fm];efficiency",10,0,20);
   TH1F* nPartPad = new TH1F(Form("hNpartPad_et%02d",(int)(version)),";N_{part};efficiency",10,0,400);

   bMatched->SetBins(5,bBins);
   bAll->SetBins(5,bBins);
   bPad->SetBins(5,bBins);


   TH2F* hEff2D = new TH2F(Form("hEff2D_et%02d",(int)(version)),";Npart;E_{T}^{GenJet} [GeV]",10,0,400,10,0,etMax);
   TH2F* hAll2D = new TH2F(Form("hAll2D_et%02d",(int)(version)),";Npart;E_{T}^{GenJet} [GeV]",10,0,400,10,0,etMax);

   TH2F* hFake2D = new TH2F(Form("hFake2D_et%02d",(int)(version)),";Npart;E_{T}^{CaloJet} [GeV]",10,0,400,10,0,etMax);
   TH2F* hCalo2D = new TH2F(Form("hCalo2D_et%02d",(int)(version)),";Npart;E_{T}^{CaloJet} [GeV]",10,0,400,10,0,etMax);

   Jets recojet; //RecoJets
   Jets genjet; //GenJets

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


   // Event Loop
   int nevents = tsub->GetEntries();
   cout<<"Number of Events : "<<nevents<<endl;
      for(int i = 0; i< nevents && i < maxEvents; ++i){    
     tsub->GetEntry(i);
     treco->GetEntry(i);
     int ngenjet = 0;
     int nrecojet = 0;
     bool counted = false;
     int jetmatch[MAXJETS];

     if (i % 1000 == 0) cout <<"Event "<<i<<endl;    
     // Selection on Events

     if(event.b > bMax || event.b < bMin ) continue;
     hVtx->Fill(event.vz);
     hB->Fill(event.b);

     // Loop over RecoJets
     for(int j = 0; j < recojet.njet; ++j){
       //       if(recojet.et[j] < jetEtCutMin) continue;
       //       if(recojet.et[j] < jetEtCutMax) continue;

       hcaloet->Fill(recojet.et[j]);
       hCalo2D->Fill(event.npart,recojet.et[j]);

       nrecojet++;
  
       for(int j1 = 0; j1< recojet.njet; ++j1){
         double dR = deltaR(recojet.eta[j],recojet.phi[j],recojet.eta[j1],recojet.phi[j1]);

	 if(dR != 0) 
	   h1->Fill(dR);
         if(dR < cone){

         }
       }
       int j2match = -99;
       double etmatch = 0;
       for(int j2 = 0; j2< genjet.njet; ++j2){

	 // Ignore genjets below et cut
	 if( genjet.et[j2] < genJetEt ) continue;

	 double dR = deltaR(recojet.eta[j],recojet.phi[j],genjet.eta[j2],genjet.phi[j2]);
         h2->Fill(dR);
         double dET = genjet.et[j2] - recojet.et[j];

	 if((genjet.et[j2] > jetEtMin) && (genjet.et[j2] < jetEtMax)){
	   hEtR->Fill(dR,dET/genjet.et[j2]);
	 }

	 if(dR < match && genjet.et[j2] > etmatch){ 
	   j2match = j2;	 
	   etmatch = genjet.et[j2match];
	 }
       }
       jetmatch[j] = j2match;
       if(j2match > -99){
	 het->Fill(genjet.et[j2match],recojet.et[j]);
	 hres->Fill((recojet.et[j]-genjet.et[j2match])/genjet.et[j2match]);
       }else{
	 //Jet is a fake
	 hfake1->Fill(recojet.et[j]);
	 hFake2D->Fill(event.npart,recojet.et[j]);
       }      
     }
 
     //Second Loop over GenJets
     for(int j2 = 0; j2< genjet.njet; ++j2){
       if(genjet.et[j2] < genJetEt) continue;

       if(genjet.et[j2] < jetEtMin) continue;
       if(genjet.et[j2] > jetEtMax) continue;

       if(fabs(genjet.eta[j2]) > etaMax) continue;
       if(fabs(genjet.eta[j2]) < etaMin) continue;

       hAll2D->Fill(event.npart,genjet.et[j2]);
       bAll->Fill(event.b);
       nPartAll->Fill(event.npart); 

       hgenet->Fill(genjet.et[j2]);
       ngenjet++;
       int counter  = 0;       
       int j1match = -99;
       double etmatch = 0;
       for(int j1 = 0; j1< recojet.njet; ++j1){
	 //	 if(recojet.et[j1] < jetEtCutMin) continue;       
	 double dR = deltaR(recojet.eta[j1],recojet.phi[j1],genjet.eta[j2],genjet.phi[j2]);
	 if(dR < match && genjet.et[j2] > etmatch){
	   j1match = j1;
	   etmatch = recojet.et[j1match];
	 }

	 // If RecoJet and GenJet match correctly and energy is reasonable                 
	 //         if(jetmatch[j1] == j2 && recojet.et[j1] < genjet.et[j2] ){
	 if(jetmatch[j1] == j2 ){ 
	   heff2->Fill(genjet.et[j2]);
	   hEff2D->Fill(event.npart,genjet.et[j2]);
	     bMatched->Fill(event.b);
	     nPartMatched->Fill(event.npart);

	   counter++;
	   if(counter > 1){
	   cout<<"j2 is "<<j2<<endl;
	   cout<<" Jet Energy is "<<genjet.et[j2]<<endl;
	   }
	   break;
	 }
       }     
       if(j1match > -99){
	 //	 cout<<"j2 matched is "<<j2<<endl;
         heff1->Fill(genjet.et[j2]);
       }else{

       }
     }

     hnjet->Fill(ngenjet,nrecojet);
   }

      hEffPad->SetMaximum(1.1);
      hFakePad->SetMaximum(1.1);

      nPartPad->SetMaximum(1.1);
      bPad->SetMaximum(1.1);

      TGraphAsymmErrors *gEff = new TGraphAsymmErrors();
      TGraphAsymmErrors *gFake = new TGraphAsymmErrors();
      TGraphAsymmErrors *gB = new TGraphAsymmErrors();
      TGraphAsymmErrors *gNpart = new TGraphAsymmErrors();

      gFake->BayesDivide(hfake1,hcaloet);
      gEff->BayesDivide(heff2,hgenet);
      gB->BayesDivide(bMatched,bAll);
      gNpart->BayesDivide(nPartMatched,nPartAll);

      hEff2D->Divide(hAll2D);
      hFake2D->Divide(hCalo2D);
      
      heff3->Divide(heff2,heff1,1,1,"B");

      
   cout<<"End."<<endl;

   TLegend *etLeg = new TLegend(0.43,0.24,0.90,0.36,NULL,"brNDC");
   etLeg->AddEntry(heff2,Form("%d<E_{T}^{GenJet}<%d [GeV]",(int)jetEtMin,(int)jetEtMax),"");
   etLeg->AddEntry(heff2,Form("%0.01f<b<%0.01f [fm]",bMin,bMax),"");
   etLeg->SetFillColor(0);
   etLeg->SetTextSize(0.04);
   etLeg->SetBorderSize(0);
   //   etLeg->Draw("");


   TLegend *bLeg = new TLegend(0.45,0.43,0.92,0.55,NULL,"brNDC");
   bLeg->AddEntry(heff2,Form("%0.01f<b<%0.01f [fm]",bMin,bMax),"");
   bLeg->SetFillColor(0);
   bLeg->SetTextSize(0.04);
   bLeg->SetBorderSize(0);
   //   bLeg->Draw("");



   if(0){
     TCanvas* e1 = new TCanvas(Form("Event Vertex",(int)(version)),Form("Event Vertex",(int)(version)),400,400);
     hVtx->Draw();
     TCanvas* e2 = new TCanvas(Form("Impact Parameter",(int)(version)),Form("Impact Parameter",(int)(version)),400,400);
     hB->Draw();
   }

   if(0){

   TCanvas* c1 = new TCanvas(Form("c1_et%02d",(int)(version)),Form("c1_et%02d",(int)(version)),400,400);
   h1->Draw();

   TCanvas* c2 = new TCanvas(Form("c2_et%02d",(int)(version)),Form("c2_et%02d",(int)(version)),400,400);
   h2->Draw();
   }

   if(1){


   TCanvas* c1_1 = new TCanvas(Form("DeltaR_deltaET_v%02d",(int)(version)),Form("DeltaR_deltaET_v%02d",(int)(version)),400,400);
   hEtR->Draw("colz");
   c1_1->Print(Form("DeltaR_deltaET_b%02dto%02d_Et%02dto%02dforGen%02d.gif",(int)(bMin),(int)(bMax),(int)(jetEtMin),(int)(jetEtMax),(int)(genJetEt)));

   }

   if(1){

   TCanvas* c3 = new TCanvas(Form("c3_et%02d",(int)(version)),Form("c3_et%02d",(int)(version)),400,400);
   het->Draw("colz");
   c3->Print(Form("EnergyScatter_et%02d.gif",(int)(version)));

   }

   if(0){

   TCanvas* c4 = new TCanvas(Form("c4_et%02d",(int)(version)),Form("c4_et%02d",(int)(version)),400,400);
   hres->Draw("");
   c4->Print(Form("EnergyResolution_et%02d.gif",(int)(version)));

   TCanvas* c5 = new TCanvas(Form("c5_et%02d",(int)(version)),Form("NumberOfJets_et%02d",(int)(version)),400,400);
   hnjet->Draw("colz");
   c5->Print(Form("NumberOfJets_et%02d.gif",(int)(version)));

   TCanvas* c6 = new TCanvas(Form("Efficiency1_et%02d",(int)(version)),Form("Efficiency1_et%02d",(int)(version)),400,400);
   heff1->Draw("");
   c6->Print(Form("JetEfficiency_et%02d.gif",(int)(version)));

   }

   if(1){

   TCanvas* c7 = new TCanvas(Form("Fake1_et%02d",(int)(version)),Form("Fake1_et%02d",(int)(version)),400,400);
   hFakePad->Draw();
   gFake->Draw("P same");
   bLeg->Draw();
   c7->Print(Form("JetFakes_et%02d.gif",(int)(version)));

   TCanvas* c8 = new TCanvas(Form("Efficiency2_et%02d",(int)(version)),Form("Efficiency2_et%02d",(int)(version)),400,400);

   hEffPad->Draw();
   gEff->Draw("P same");
   bLeg->Draw();
   c8->Print(Form("JetEfficiency_v%02d.gif",(int)(version)));

   }

   if(0){

   TCanvas* c9 = new TCanvas(Form("Ratio_et%02d",(int)(version)),Form("Ratio_et%02d",(int)(version)),400,400);
   heff3->Draw("");
   c9->Print(Form("JetEfficiencyComparison_et%02d.gif",(int)(version)));

   }

   if(1){

   TCanvas* c10 = new TCanvas(Form("Efficiency_vs_b_v%02d",(int)(version)),Form("Efficiency_vs_b",(int)(version)),400,400);
   bPad->Draw();
   gB->Draw("P");
   etLeg->Draw();
   c10->Print(Form("Efficiency_vs_b_v%02d.gif",(int)(version)));

   TCanvas* c11 = new TCanvas(Form("Efficiency_vs_Npart_v%02d",(int)(version)),Form("Efficiency_vs_Npart",(int)(version)),400,400);
   nPartPad->Draw();
   gNpart->Draw("P same");
   etLeg->Draw();
   c11->Print(Form("Efficiency_vs_Npart_v%02d.gif",(int)(version)));

   }
   if(0){


   TCanvas* c12 = new TCanvas(Form("ImpactParameter_et%02d",(int)(version)),Form("ImpactParameter",(int)(version)),400,400);
   bAll->Draw("");
   }

   if(1){

   TCanvas* c13 = new TCanvas(Form("Efficiency2D_et%02d",(int)(version)),Form("Efficiency2D",(int)(version)),400,400);
   hEff2D->Draw("colz");
   c13->Print(Form("Efficiency_2D_v%02d.gif",(int)(version)));

   TCanvas* c14 = new TCanvas(Form("Fakes2D_et%02d",(int)(version)),Form("Fake2D",(int)(version)),400,400);
   hFake2D->Draw("colz");
   c14->Print(Form("Fakes_2D_v%02d.gif",(int)(version)));


   }




   /*
   c1->Write();
   c2->Write();
   c3->Write();
   c4->Write();
   c5->Write();
   */

   h1->Write();
   h2->Write();
   het->Write();
   hres->Write();
   hnjet->Write();

   double overlap = h1->Integral(0,cone/(h1->GetBinWidth(1)));
   overlap /= h1->Integral();

   return overlap;
}
