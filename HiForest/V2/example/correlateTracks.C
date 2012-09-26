


#include "hiForest.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TNtuple.h"
#include "TMath.h"

#include "TCut.h"
#include <string>

using namespace std;

void correlateTracks(
		 const char* infname = "/mnt/hadoop/cms/store/user/yilmaz/HiForest2_pPb_v5/PAPhysics/pPb_hiForest2_43_1_Dxz.root",
                 const char* outname = "output.root"
		 ){

   double pi = TMath::Pi();

  TFile* outf = new TFile( outname, "recreate");
  TH2D* hpt2D = new TH2D("hpt2D",";p_{T}^{Lead} (GeV/c);p_{T}^{SubLead} (GeV/c)",100,0,1000,100,0,1000);
  TNtuple* nt = new TNtuple("nt","","ass:bkg:jet:n:hf:hfp:hfm");
  TH2D* h2D = new TH2D("h2D",";;",50,-5,5,50,-pi,pi);

  HiForest * t = new HiForest(infname,"",cPPb);
  // Here goes more up to date tracking correction instructions
  t->InitTree();

  int maxEvents = t->GetEntries();
  for(int iev = 0; iev < maxEvents; ++iev){
    if(iev%1000==0)cout<<"Processing entry : "<<iev<<" / "<<t->GetEntries()<<endl;
    t->GetEntry(iev);

    if(!t->selectEvent()) continue;
    int evt = t->hlt.Event;
    int run = t->hlt.Run;

    double hf = t->evt.hiHF;
    double hfp = t->evt.hiHFplus;
    double hfm = t->evt.hiHFminus;

    double ass = 0;
    double jet = 0;
    double bkg = 0;
    double n = 0;

    // Track Loop
    for(int i = 0; i < t->track.nTrk; ++i){

       if(!t->selectTrack(i)) continue;

      double pt1 =  t->track.trkPt[i];
      double eta1 = t->track.trkEta[i];
      double phi1 =  t->track.trkPhi[i];

      n++;

      if(pt1 < 1) continue;
      if(pt1 > 3) continue;

      for(int j = i+1; j < t->track.nTrk; ++j){

	 if(!t->selectTrack(j)) continue;

	 double pt2 =  t->track.trkPt[j];
	 double eta2 = t->track.trkEta[j];
	 double phi2 =  t->track.trkPhi[j];

	 if(pt2 < 1) continue;
	 if(pt2 > 3) continue;

	 double deta = fabs(eta1-eta2);
         double dphi = fabs(deltaPhi(phi1,phi2));

	 h2D->Fill(deta,dphi);
         h2D->Fill(deta,-dphi);
         h2D->Fill(-deta,dphi);
         h2D->Fill(-deta,-dphi);

	 if(deta > 2 && dphi < 1) ass++;
         if(deta < 1 && dphi < 1) jet++;
         if(deta > 2 && dphi > 1 && dphi < 2) bkg++;

      }

    }

    nt->Fill(ass,bkg,jet,n,hf,hfp,hfm);


    /*
    // SimTrack Loop
    for(int i = 0; i < t->track.nParticle; ++i){
      double trkPt =  t->track.pPt[i];
    }
    // GenParticle loop
    for(int i = 0; i < t->genparticle.nPar; ++i){
      double trkPt =  t->genparticle.et[i];
    }
    */


  }

  outf->Write();

}


