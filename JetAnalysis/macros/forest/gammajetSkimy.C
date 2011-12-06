#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <TMath.h>
#include "hiForest.h"
using namespace std;

#define PI 3.141592653589

int getNcoll(int cBin=0);

void gammajetSkimy(TString inputFile_="mc/photon50_25k.root", std::string outputFile = "barrelPhoton50_25k.root", float etaCut=1.44, float ptCut = 25,  bool doTrack = false)
{
   
   TString fisherVar = "6.5481e-01 +cc5*8.127033e-03 +cc4*-1.275908e-02 +cc3*-2.24332e-02 +cc2*-6.96778e-02 +cc1*4.682052e-02 +cr5*-2.35164e-02 +cr4*1.74567e-03 +cr3*-2.39334e-04 +cr2*-3.1724e-02 +cr1*-3.65306e-02 +ct4PtCut20*1.8335e-02 +ct3PtCut20*-2.609068e-02 +ct2PtCut20*-4.523171e-02 +ct1PtCut20*-1.270661e-02 +ct5PtCut20*9.218723e-03" ;  
   
   
   bool doTrigCut(false);
   std::string triggerName = "";
   
   const int nMaxPho = 3000;
   
   HiForest *yforest = new HiForest(inputFile_.Data());
   yforest->GetEnergyScaleTable("photonEnergyScaleTable_Hydjet_GammaJet.root");
   
   // now open new root file
   TFile* newfile_data = new TFile(outputFile.data(),"recreate");
   cout << "Output file " << outputFile << endl;
   
   TTree* newtree = yforest->photonTree->CloneTree(0);
   newtree->SetName("yongsunPhotonTree");
   
   TTree* newtreehlt = yforest->hltTree->CloneTree(0);
   newtreehlt->SetName("yongsunHltTree");
   
   TTree* newtreeSkim = yforest->skimTree->CloneTree(0);
   newtreeSkim->SetName("yongsunSkimTree");
   
   TTree* newtreePfjet = yforest->akPu3jetTree->CloneTree(0);
   newtreePfjet->SetName("yongsunPfjetTree");
   
   TTree* newtreeTrack = yforest->trackTree->CloneTree(0);
   newtreeTrack->SetName("yongsunTrackTree");
   
   TTree* newtreeEvt = yforest->evtTree->CloneTree(0);
   newtreeEvt->SetName("yongsunHiEvt");
   
   int isGen(false);
   TTree* newtreeGen;
   if ( yforest->genpTree !=0 ) { 
      newtreeGen = yforest->genpTree->CloneTree(0);
      newtreeGen->SetName("yongsunGen");
      isGen = true;
   }

   newtree->SetMaxTreeSize(4000000000);
   newtreehlt->SetMaxTreeSize(4000000000);
   newtreeSkim->SetMaxTreeSize(4000000000);
   newtreePfjet->SetMaxTreeSize(4000000000);
   if ( doTrack)   newtreeTrack->SetMaxTreeSize(4000000000);
   if ( isGen)     newtreeGen->SetMaxTreeSize(4000000000);
   
   
   Float_t leadingPt, leadingPhi, leadingEta, lcc4j, lcr4j, lct4j20, lsee, lhoe ;
   int ncoll;
   int order[nMaxPho];
   float newPt[nMaxPho];
   float corrPt[nMaxPho];
   float locNtrk[nMaxPho];
   
   Int_t           nTrk;
   Float_t         trkPt [2000];   //[nTrk]                                                                                                                                                                  
   Float_t         trkEta[2000];   //[nTrk]                                                                                                                                      
   Float_t         trkPhi[2000];   //[nTrk]                                                                                                                                   
    
   newtree->Branch("ncoll", &ncoll,"ncoll/I");
   newtree->Branch("corrPt", corrPt,"corrPt[nPhotons]/F");
   newtree->Branch("order",  order,  "order[nPhotons]/I");
   newtree->Branch("lPt", &leadingPt,"lpt/F");
   newtree->Branch("lEta", &leadingEta,"leta/F");
   newtree->Branch("lPhi", &leadingPhi,"lphi/F");
   newtree->Branch("lsee", &lsee,"lsee/F");
   newtree->Branch("lhoe", &lhoe,"lhoe/F");
   
   TH1D* hdr = new TH1D("hdr",";dr;Entries",100,-10,10);

   
   int nentries = yforest->GetEntries();
   cout << "number of entries = " << nentries << endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if (jentry% 10000 == 0) cout <<jentry<<" / "<<nentries<<" "<<setprecision(2)<<(double)jentry/nentries*100<<endl;

      yforest->GetEntry(jentry);

      if ( yforest->skim.pcollisionEventSelection != 1) 
	 continue;

      for (int j=0;j< yforest->photon.nPhotons;j++) {
	 order[j] = -1;
	 if ( fabs( yforest->photon.eta[j] ) < etaCut )
	    newPt[j] = yforest->getCorrEt(j);
	 else 
	    newPt[j] = - yforest->photon.pt[j] - 1000;
	 
	 corrPt[j] = newPt[j];

	 locNtrk[j] = -1000;
	 if( doTrack) {
	    if ( ( yforest->photon.pt[j] > 40) && fabs( yforest->photon.eta[j] )<1.5) {
	       locNtrk[j]=0;
	       for (int jt=0 ; jt < yforest->track.nTrk ; jt++) {
		  //  if ( trkPt[jt] < 2 ) 
		  //	  continue;
		  float dPhi = yforest->photon.phi[j] - yforest->track.trkPhi[jt];
		  if (dPhi > PI)  
		     dPhi = dPhi - 2*PI;
		  if (dPhi < -PI) 
		     dPhi = dPhi + 2*PI;
		  float dEta = yforest->photon.eta[j] - yforest->track.trkEta[jt];
		  float dR = sqrt( dPhi*dPhi + dEta*dEta);
		  //	       hdr->Fill(dPhi);
		  if ( dR < 0.5 ) 
		     locNtrk[j] = locNtrk[j] + 1;
	       }
	    }
	 }
      }
      
      
      TMath::Sort(yforest->photon.nPhotons, newPt, order);
      
      leadingPt = -100;
      leadingEta = -100;
      leadingPhi = -100;

      for (int j=0 ; j < yforest->photon.nPhotons ; j++) {
	 if ( fabs(yforest->photon.eta[j]) > etaCut ) 
	    continue;
         if ( corrPt[j] > leadingPt ) {
	    leadingPt =  corrPt[j];
	    leadingEta = yforest->photon.eta[j];
	    leadingPhi = yforest->photon.phi[j];
	    lhoe    =    yforest->photon.hadronicOverEm[j];
	    lsee    =    yforest->photon.sigmaIetaIeta[j];
	 }

      }
      
      if ( leadingPt < ptCut )   continue;
      
      // nColl
      ncoll = getNcoll(yforest->evt.hiBin);
      
      newtree->Fill();
      newtreehlt->Fill();
      newtreeSkim->Fill();
      newtreePfjet->Fill();
      if( doTrack)
	 newtreeTrack->Fill();
      newtreeEvt->Fill();
      if ( isGen )
	newtreeGen->Fill();
   }
   
   
   
   
   newfile_data->Write();
   newfile_data->Close();
   cout << " Done! "<< endl;
}




int getNcoll(int cBin) { 
   if (cBin == 0) return  1747.86 ;
   if (cBin == 1) return  1567.53 ;
   if (cBin == 2) return  1388.39 ;
   if (cBin == 3) return  1231.77 ;
   if (cBin == 4) return  1098.2 ;
   if (cBin == 5) return  980.439 ;
   if (cBin == 6) return  861.609 ;
   if (cBin == 7) return  766.042 ;
   if (cBin == 8) return  676.515 ;
   if (cBin == 9) return  593.473 ;
   if (cBin == 10) return  521.912 ;
   if (cBin == 11) return  456.542 ;
   if (cBin == 12) return  398.546 ;
   if (cBin == 13) return  346.647 ;
   if (cBin == 14) return  299.305 ;
   if (cBin == 15) return  258.344 ;
   if (cBin == 16) return  221.216 ;
   if (cBin == 17) return  188.677 ;
   if (cBin == 18) return  158.986 ;
   if (cBin == 19) return  134.7 ;
   if (cBin == 20) return  112.547 ;
   if (cBin == 21) return  93.4537 ;
   if (cBin == 22) return  77.9314 ;
   if (cBin == 23) return  63.5031 ;
   if (cBin == 24) return  52.0469 ;
   if (cBin == 25) return  42.3542 ;
   if (cBin == 26) return  33.9204 ;
   if (cBin == 27) return  27.3163 ;
   if (cBin == 28) return  21.8028 ;
   if (cBin == 29) return  17.2037 ;
   if (cBin == 30) return  13.5881 ;
   if (cBin == 31) return  10.6538 ;
   if (cBin == 32) return  8.35553 ;
   if (cBin == 33) return  6.40891 ;
   if (cBin == 34) return  5.13343 ;
   if (cBin == 35) return  3.73215 ;
   if (cBin == 36) return  3.06627 ;
   if (cBin == 37) return  2.41926 ;
   if (cBin == 38) return  2.11898 ;
   if (cBin == 39) return  1.76953 ;
   return -100000;
}
