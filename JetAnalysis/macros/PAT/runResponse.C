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

  int nref;
  int bin;
  float b;
  float hf;
  float jtpt[MAXJETS];
  float refpt[MAXJETS];
  float jteta[MAXJETS];
  float refeta[MAXJETS];
  float jtphi[MAXJETS];
  float refphi[MAXJETS];

  float weight;
};

bool myfunction (etdr i,etdr j) { return (i.dr<j.dr); }

void runResponseForAlgo(const char* algo, TFile* infile, TFile* outFile, float weight = 1.);

void runResponse(){

  TFile* infile = new TFile("./pat_jets_50to80.root","read");
  TFile* outFile = new TFile("./jra_50to80.root","recreate");

  float weight = 2096.;
  runResponseForAlgo("icPu5",infile,outFile,weight);
  runResponseForAlgo("icPu7",infile,outFile,weight);
  runResponseForAlgo("akPu5",infile,outFile,weight);
  runResponseForAlgo("akPu7",infile,outFile,weight);
  runResponseForAlgo("ktPu4",infile,outFile,weight);
  runResponseForAlgo("ktPu6",infile,outFile,weight);
  runResponseForAlgo("ak5",infile,outFile,weight);
  runResponseForAlgo("ak7",infile,outFile,weight);
  runResponseForAlgo("kt4",infile,outFile,weight);
  runResponseForAlgo("kt6",infile,outFile,weight);
  outFile->Close();

  weight = 224.0;
  infile = new TFile("./pat_jets_80to120.root","read");
  outFile = new TFile("./jra_80to120.root","recreate");
  runResponseForAlgo("icPu5",infile,outFile,weight);
  runResponseForAlgo("icPu7",infile,outFile,weight);
  runResponseForAlgo("akPu5",infile,outFile,weight);
  runResponseForAlgo("akPu7",infile,outFile,weight);
  runResponseForAlgo("ktPu4",infile,outFile,weight);
  runResponseForAlgo("ktPu6",infile,outFile,weight);
  runResponseForAlgo("ak5",infile,outFile,weight);
  runResponseForAlgo("ak7",infile,outFile,weight);
  runResponseForAlgo("kt4",infile,outFile,weight);
  runResponseForAlgo("kt6",infile,outFile,weight);
  outFile->Close();

  weight = 28.46;
  infile = new TFile("./pat_jets_120to170.root","read");
  outFile = new TFile("./jra_120to170.root","recreate");
  runResponseForAlgo("icPu5",infile,outFile,weight);
  runResponseForAlgo("icPu7",infile,outFile,weight);
  runResponseForAlgo("akPu5",infile,outFile,weight);
  runResponseForAlgo("akPu7",infile,outFile,weight);
  runResponseForAlgo("ktPu4",infile,outFile,weight);
  runResponseForAlgo("ktPu6",infile,outFile,weight);
  runResponseForAlgo("ak5",infile,outFile,weight);
  runResponseForAlgo("ak7",infile,outFile,weight);
  runResponseForAlgo("kt4",infile,outFile,weight);
  runResponseForAlgo("kt6",infile,outFile,weight);
  outFile->Close();

}









void runResponseForAlgo(const char* algo, TFile* infile, TFile* outFile, float weight){

  const char* name = Form("%scalo",algo);
  const char* jetTag = Form("%spatJets",algo);

  cout<<"Running for algorithm : "<<jetTag<<endl;
  cout<<"Saving in directory : "<<name<<endl;

  double cone = 0.5;
  double genJetPtMin = 20.;

  const int nEtaBins = 4;
  double etaMin[nEtaBins] = {0.,0.,1.,2.};
  double etaMax[nEtaBins] = {5.,1.,2.,3.};

  TFile * centFile = new TFile("/home/yilmaz/CMSSW_3_5_4/src/RecoHI/HiCentralityAlgos/data/CentralityTables.root");

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
  t->Branch("nref",&jets_.nref,"nref/I");
  t->Branch("jtpt",jets_.jtpt,"jtpt[nref]/F");
  t->Branch("refpt",jets_.refpt,"refpt[nref]/F");
  t->Branch("jteta",jets_.jteta,"jteta[nref]/F");
  t->Branch("refeta",jets_.refeta,"refeta[nref]/F");
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
	  
	  jets_.jtpt[jets_.nref] = jet.pt();
	  jets_.jteta[jets_.nref] = jet.eta();
	  jets_.jtphi[jets_.nref] = jet.phi();
	 
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
