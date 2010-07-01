#include <string>
#include <vector>
#include <iostream>

#include <TH2D.h>
#include <TH1D.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TSystem.h>
#include "CmsHiFunctions.h"

#if !defined(__CINT__) && !defined(__MAKECINT__)

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#endif

using namespace std;


struct etdr{
  double et;
  double dr;
};

bool myfunction (etdr i,etdr j) { return (i.dr<j.dr); }


void analyzeJetEfficiencyAndFakes(){

  bool debug = false;

  double Et_Min = 1000;
  double Et_Max = 1500;
  double iEtamax =11.5;

  const char* jetTag = "icPu5patJets";
  const char* genTag = "iterativeCone5HiGenJets";

  int histBins = 250;
  int histPtMax = 250;

  const int nEtaBins = 4;
  double etaMin[nEtaBins] = {0.,0.,1.,2.};
  double etaMax[nEtaBins] = {5.,1.,2.,3.};
  double phiMin[4] = {0,0,PI/3.,2*PI/3};
  double phiMax[4] = {5,PI/3.,2*PI/3,5};

  TFile * centFile = new TFile("/home/yilmaz/CMSSW_3_5_6/src/RecoHI/HiCentralityAlgos/data/CentralityTables.root");
  TFile* infile = new TFile("SignalQuenchedDijet80to120_runs1to100.root");

  fwlite::Event event(infile);
  TFile* outFile = new TFile("efficiency.root","recreate");

  TH1D::SetDefaultSumw2();
  CentralityBins::RunMap HFhitBinMap = getCentralityFromFile(centFile,"HFhits10_MC_Hydjet2760GeV_MC_3XY_V24_v0",0,2);

  TH1D* hPTcaloAll[11][4];
  TH1D* hPTgenAll[11][4];
  TH1D* hPTcaloUnmatched[11][4];
  TH1D* hPTgenMatched[11][4];

  TNtuple* nt = new TNtuple("nt","","eta1:eta2:phi1:phi2:pt1:pt2:bin:et:pu:subt:sign:njet:njet20:njet30:ncons:area");

  for(int i = 0; i < 11; ++i){
    for(int j = 0; j < 4; ++j){
      hPTgenAll[i][j] = new TH1D(Form("hPTgenAll_%d_%d",i,j),"",histBins,0,histPtMax);
      hPTgenMatched[i][j] = new TH1D(Form("hPTgenMatched_%d_%d",i,j),"",histBins,0,histPtMax);
      hPTcaloAll[i][j] = new TH1D(Form("hPTcaloAll_%d_%d",i,j),"",histBins,0,histPtMax);
      hPTcaloUnmatched[i][j] = new TH1D(Form("hPTcaloUnmatched_%d_%d",i,j),"",histBins,0,histPtMax);
    }
  }
  
  // loop the events
  unsigned int iEvent=0;
  int maxEvents = -1;
  for(event.toBegin(); !event.atEnd() && (maxEvents < 0 || iEvent < maxEvents); ++event, ++iEvent){
     edm::EventBase const & ev = event;
     //     if(iEvent < 1000) continue;
    if( iEvent % 500 == 0 ) cout<<"Processing event : "<<iEvent<<endl;

    edm::Handle<edm::GenHIEvent> mc;
    //    ev.getByLabel(edm::InputTag("heavyIon"),mc);

    edm::Handle<reco::Centrality> cent;
    ev.getByLabel(edm::InputTag("hiCentrality","","RECO"),cent);

    if(0){
      double b = mc->b();
      double npart = mc->Npart();
      double ncoll = mc->Ncoll();
      double nhard = mc->Nhard();
      double phi0 = mc->evtPlane();
    }

    double hf = cent->EtHFhitSum();

    int run = ev.id().run();
    run = 1;
    int bin = HFhitBinMap[run]->getBin(hf);

    //    if(bin== 0) debug = true;
    //    else debug = false;

    if(debug)  cout<<"Centrality bin is : "<<bin<<endl;
    
    edm::Handle<pat::JetCollection> jets;
    ev.getByLabel(edm::InputTag(jetTag),jets);
    edm::Handle<reco::GenJetCollection> genjets;
    ev.getByLabel(edm::InputTag(genTag,"","RECO"),genjets);
    
    for(int j = 0 ; j < jets->size(); ++j){
      const pat::Jet& jet = (*jets)[j];
      for(int ie = 0; ie < nEtaBins; ++ie){
	if(fabs(jet.eta()) < etaMin[ie] || fabs(jet.eta()) > etaMax[ie]) continue;
	hPTcaloAll[bin][ie]->Fill(jet.pt());
      }
      const reco::GenJet* matchedGen = jet.genJet();
      if(matchedGen){
	for(int ie = 0; ie < nEtaBins; ++ie){
          if(fabs(matchedGen->eta()) < etaMin[ie] || fabs(matchedGen->eta()) > etaMax[ie]) continue;
	  hPTgenMatched[bin][ie]->Fill(matchedGen->pt());
	}
      }else{
	for(int ie = 0; ie < nEtaBins; ++ie){
          if(fabs(jet.eta()) < etaMin[ie] || fabs(jet.eta()) > etaMax[ie]) continue;
          hPTcaloUnmatched[bin][ie]->Fill(jet.pt());
        }
      }
      
    }
    
    for(int j = 0 ; j < genjets->size(); ++j){
      const reco::GenJet& jet = (*genjets)[j];
      for(int ie = 0; ie < nEtaBins; ++ie){
	if(fabs(jet.eta()) < etaMin[ie] || fabs(jet.eta()) > etaMax[ie]) continue;
	hPTgenAll[bin][ie]->Fill(jet.pt());
      }
    }
  }
  
  outFile->cd();

  for(int i = 0; i < 11; ++i){
    for(int ip = 0; ip < nEtaBins; ++ip){
      
      TH1D* hEff = (TH1D*)hPTgenMatched[i][ip]->Clone(Form("hEff_%d_%d",i,ip));
      TH1D* hFake = (TH1D*)hPTcaloUnmatched[i][ip]->Clone(Form("hFake_%d_%d",i,ip));

      hEff->Divide(hPTgenMatched[i][ip],hPTgenAll[i][ip],1,1,"B");
      hFake->Divide(hPTcaloUnmatched[i][ip],hPTcaloAll[i][ip],1,1,"B");

      hEff->Write();
      hFake->Write();

      hPTgenMatched[i][ip]->Write();
      hPTgenAll[i][ip]->Write();
      hPTcaloUnmatched[i][ip]->Write();
      hPTcaloAll[i][ip]->Write();
    }
  }

  nt->Write();

  outFile->Write();
  
}
