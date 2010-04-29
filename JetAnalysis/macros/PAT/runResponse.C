#include <string>
#include <vector>
#include <iostream>
#include <TH2D.h>
#include <TH1D.h>
#include <TFile.h>
#include <TSystem.h>
#include <TTree.h>

#if !defined(__CINT__) && !defined(__MAKECINT__)

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"

#endif

using namespace std;

static const int MAXJETS = 500;

struct etdr{
   double et;
   double dr;
};

struct JRA{

  unsigned char nref;
   int bin;
   float b;
   float hf;
   float jtpt[MAXJETS];
   float refpt[MAXJETS];
   float jteta[MAXJETS];
   float refeta[MAXJETS];
   float jtphi[MAXJETS];
   float refphi[MAXJETS];
  float jty[MAXJETS];
  float refy[MAXJETS];


   float weight;
};

bool myfunction (etdr i,etdr j) { return (i.dr<j.dr); }

void runResponseForAlgo(string algo, TFile* infile, TFile* outFile, float weight = 1., bool doFastJet = false);

void runResponse(const char* inf, const char* outf, double weight){

   TFile* infile1 = new TFile(inf,"read");
   TFile* outFile1 = new TFile(outf,"recreate");

   runResponseForAlgo("icPu5",infile1,outFile1,weight);
   runResponseForAlgo("icPu7",infile1,outFile1,weight);
   runResponseForAlgo("akPu5",infile1,outFile1,weight);
   runResponseForAlgo("akPu7",infile1,outFile1,weight);
   runResponseForAlgo("ktPu4",infile1,outFile1,weight);
   runResponseForAlgo("ktPu6",infile1,outFile1,weight);
   runResponseForAlgo("ak5",infile1,outFile1,weight,1);
   runResponseForAlgo("ak7",infile1,outFile1,weight,1);
   runResponseForAlgo("kt4",infile1,outFile1,weight,1);
   runResponseForAlgo("kt6",infile1,outFile1,weight,1);
   outFile1->Write();
   outFile1->Close();

}


void runResponseForAlgo(string algo, TFile* infile, TFile* outFile, float weight, bool doFastJet){

   const char* name = Form("%scalo",algo.data());
   const char* jetTag = Form("%spatJets",algo.data());
   const char* rhoTag = "";

   if(algo.compare("ak5") == 0) rhoTag = "akFastPu5CaloJets";
   if(algo.compare("ak7") == 0) rhoTag = "akFastPu7CaloJets";
   if(algo.compare("kt4") == 0) rhoTag = "ktFastPu4CaloJets";
   if(algo.compare("kt6") == 0) rhoTag = "ktFastPu6CaloJets";

   cout<<"Running for algorithm : "<<jetTag<<endl;
   cout<<"Saving in directory : "<<name<<endl;

   double cone = 0.5;
   double genJetPtMin = 20.;

   const int nEtaBins = 4;
   double etaMin[nEtaBins] = {0.,0.,1.,2.};
   double etaMax[nEtaBins] = {5.,1.,2.,3.};

   TFile * centFile = new TFile("~yetkin/depot/CentralityTables.root");

   infile->cd();
   fwlite::Event event(infile);
   outFile->cd();

   int nevents = event.size();
   weight = weight/nevents;

   TDirectory* dir = outFile->mkdir(name);
   dir->cd();

   JRA jets_;
   TTree* t= new TTree("t","Jet Response Analyzer");
   t->Branch("b",&jets_.b,"b/F");
   t->Branch("hf",&jets_.hf,"hf/F");
   t->Branch("nref",&jets_.nref,"nref/b");
   t->Branch("jtpt",jets_.jtpt,"jtpt[nref]/F");
   t->Branch("refpt",jets_.refpt,"refpt[nref]/F");
   t->Branch("jteta",jets_.jteta,"jteta[nref]/F");
   t->Branch("refeta",jets_.refeta,"refeta[nref]/F");
   t->Branch("jty",jets_.jty,"jty[nref]/F");
   t->Branch("refy",jets_.refy,"refy[nref]/F");

   t->Branch("jtphi",jets_.jtphi,"jtphi[nref]/F");
   t->Branch("refphi",jets_.refphi,"refphi[nref]/F");
   t->Branch("weight",&jets_.weight,"weight/F");
   t->Branch("bin",&jets_.bin,"bin/I");

   TH1D::SetDefaultSumw2();

   CentralityBins::RunMap HFhitBinMap = getCentralityFromFile(centFile,"HFhits10_MC_Hydjet2760GeV_MC_3XY_V24_v0",0,2);
   double etMax[10] = {350,250,150,120,60,40,20,10,10,10};
   double histDrMax = 6;

   // loop the events
   unsigned int iEvent=0;
   for(event.toBegin(); !event.atEnd(); ++event, ++iEvent){
      edm::EventBase const & ev = event;
      if( iEvent % 100 == 0 ) cout<<"Processing event : "<<iEvent<<endl;

      edm::Handle<edm::GenHIEvent> mc;
      ev.getByLabel(edm::InputTag("heavyIon"),mc);
      edm::Handle<reco::Centrality> cent;
      ev.getByLabel(edm::InputTag("hiCentrality"),cent);

      double b = mc->b();
      double npart = mc->Npart();
      double ncoll = mc->Ncoll();
      double nhard = mc->Nhard();
      double phi0 = mc->evtPlane();

      double hf = cent->EtHFhitSum();

      int run = ev.id().run();
      run = 1;
      int bin = HFhitBinMap[run]->getBin(hf);
      //    cout<<"Bin is : "<<bin<<endl;

      jets_.bin = bin;
      jets_.hf = hf;

      edm::Handle<pat::JetCollection> jets;
      ev.getByLabel(edm::InputTag(jetTag),jets);

      edm::Handle<double> rho;
      if(doFastJet) ev.getByLabel(edm::InputTag(rhoTag),rho);
    
      // FILL JRA TREE
      jets_.b = mc->b();
      jets_.nref = 0;
      for(int j = 0 ; j < jets->size(); ++j){
	 const pat::Jet& jet = (*jets)[j];
	 
	 if(jet.genJet() != 0){

	    if(jet.genJet()->pt() < genJetPtMin) continue;
	    jets_.refpt[jets_.nref] = jet.genJet()->pt();
	    jets_.refeta[jets_.nref] = jet.genJet()->eta();
	    jets_.refphi[jets_.nref] = jet.genJet()->phi();
            jets_.refy[jets_.nref] = jet.genJet()->eta();
	      
	    jets_.jtpt[jets_.nref] = jet.pt();

	    if(doFastJet){
	       // Fast jet PU subtraction - please check
	       // note that corrfactor is applied to background
	       // which should be equivalent to : [(raw pt) - (background)] -> correct
	       // good ???
	       jets_.jtpt[jets_.nref] = jet.pt() - (*rho)*jet.jetArea()*jet.corrFactor("abs");
	    }
	    
	    jets_.jteta[jets_.nref] = jet.eta();
	    jets_.jtphi[jets_.nref] = jet.phi();
            jets_.jty[jets_.nref] = jet.eta();
	     
	    jets_.nref++;
	      
	 }
      }
      
      jets_.weight = weight;
      t->Fill();
   }
  
   dir->cd();
   t->Write();
   dir->Write();
  
}
