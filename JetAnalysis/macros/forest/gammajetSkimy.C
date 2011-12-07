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
static const int MAXTRK = 10000;

int getNcoll(int cBin=0);

class EvtSel {
public:
   int run;
   int evt;
   int cBin;
   int nG;
   int nJ;
   int nT;
   int ncoll;
   bool trig;
   bool offlSel;
   bool noiseFilt;
   bool anaEvtSel;
   float vz;
   
};

class Isolation{
public:
   float cc1,cc2,cc3,cc4,cc5;
   float cr1,cr2,cr3,cr4,cr5;
   float ct1PtCut20,ct2PtCut20,ct3PtCut20,ct4PtCut20,ct5PtCut20;
   void Set(HiForest * c, int j) {
      cc1=c->photon.cc1[j];
      cc2=c->photon.cc2[j];
      cc3=c->photon.cc3[j];
      cc4=c->photon.cc4[j];
      cc5=c->photon.cc5[j];
      cr1=c->photon.cr1[j];
      cr2=c->photon.cr2[j];
      cr3=c->photon.cr3[j];
      cr4=c->photon.cr4[j];
      cr5=c->photon.cr5[j];
      ct1PtCut20=c->photon.ct1PtCut20[j];
      ct2PtCut20=c->photon.ct2PtCut20[j];
      ct3PtCut20=c->photon.ct3PtCut20[j];
      ct4PtCut20=c->photon.ct4PtCut20[j];
      ct5PtCut20=c->photon.ct5PtCut20[j];
   }
};

class GammaJet{
 public:
   GammaJet() :
      photonEt(-99),photonEta(0),photonPhi(0),
      jetEt(-99),jetEta(0),jetPhi(0),
      deta(-99),dphi(-99), Aj(-99),
      sigmaIetaIeta(-99),
      nTrk(0)
	 {}
      float photonEt,photonRawEt;
      float photonEta;
      float photonPhi;
      float jetEt;
      float jetEta;
      float jetPhi;
      float deta;
      float dphi;
      float Aj;
      float sigmaIetaIeta;
      int nTrk;
      float trkPt[MAXTRK];
      float trkEta[MAXTRK];
      float trkPhi[MAXTRK];
      void clear() {
	 photonEt=-99; photonEta=0; photonPhi=0;
	 jetEt=-99; jetEta=0; jetPhi=0;
	 deta=-99; dphi=-99; Aj=-99;
	 sigmaIetaIeta=-99;
	 nTrk=0;
      }
};



void gammajetSkimy(TString inputFile_="mc/photon50_25k.root", std::string outputFile = "barrelPhoton50_25k.root") {
   
   float etaCut=1.44;
   float ptCut = 50;
   
   double cutjetPt = 20;
   double cutjetEta = 2;
   
   
   bool doTrigCut(false);
   std::string triggerName = "";
   
   const int nMaxPho = 3000;
   
   HiForest *c = new HiForest(inputFile_.Data());
   c->GetEnergyScaleTable("photonEnergyScaleTable_Hydjet_GammaJet.root");
   
   // now open new root file
   TFile* newfile_data = new TFile(outputFile.data(),"recreate");
   cout << "Output file " << outputFile << endl;
   
   TTree* newtree = c->photonTree->CloneTree(0);
   newtree->SetName("yongsunPhotonTree");
   
   TTree* newtreehlt = c->hltTree->CloneTree(0);
   newtreehlt->SetName("yongsunHltTree");
   
   TTree* newtreeSkim = c->skimTree->CloneTree(0);
   newtreeSkim->SetName("yongsunSkimTree");
   
   TTree* newtreePfjet = c->akPu3jetTree->CloneTree(0);
   newtreePfjet->SetName("yongsunPfjetTree");
   
   TTree* newtreeTrack = c->trackTree->CloneTree(0);
   newtreeTrack->SetName("yongsunTrackTree");
   
   TTree* newtreeEvt = c->evtTree->CloneTree(0);
   newtreeEvt->SetName("yongsunHiEvt");
   
   int isGen(false);
   TTree* newtreeGen;
   if ( c->genpTree !=0 ) { 
      newtreeGen = c->genpTree->CloneTree(0);
      newtreeGen->SetName("yongsunGen");
      isGen = true;
   }

   newtree->SetMaxTreeSize(4000000000);
   newtreehlt->SetMaxTreeSize(4000000000);
   newtreeSkim->SetMaxTreeSize(4000000000);
   newtreePfjet->SetMaxTreeSize(4000000000);
   if ( doTrack)   newtreeTrack->SetMaxTreeSize(4000000000);
   if ( isGen)     newtreeGen->SetMaxTreeSize(4000000000);

   
   
   int ncoll;
   float corrPt[nMaxPho];
   float locNtrk[nMaxPho];
   Int_t           nTrk;
   Float_t         trkPt [2000];   //[nTrk] 
   Float_t         trkEta[2000];   //[nTrk] 
   Float_t         trkPhi[2000];   //[nTrk] 

   int    isoSumBit(0);
   int    optFishBit(0);
   int    iso3dBit(0);

   // Output file                                                                                                                            
   TFile *output = new TFile(outname,"recreate");
   TTree * tgj = new TTree("tgj","gamma jet tree");
   
   GammaJet gj;
   Isolation isol;
   EvtSel evt;
   tgj->Branch("evt",&evt.run,"run/I:evt:cBin:nG:nJ:nT:trig/O:offlSel:noiseFilt:anaEvtSel:vz/F");
   tgj->Branch("jet",&gj.photonEt,"photonEt/F:photonRawEt:photonEta:photonPhi:jetEt:jetEta:jetPhi:deta:dphi:Agj:hovere:sigmaIetaIeta:sumIsol");
   tgj->Branch("isolation",&isol.cc1,"cc1:cc2:cc3:cc4:cc5:cr1:cr2:cr3:cr4:cr5:ct1PtCut20:ct2PtCut20:ct3PtCut20:ct4PtCut20:ct5PtCut20");
   tgj->Branch("nTrk",&gj.nTrk,"nTrk/I");
   tgj->Branch("trkPt",gj.trkPt,"trkPt[nTrk]/F");
   tgj->Branch("trkEta",gj.trkEta,"trkEta[nTrk]/F");
   tgj->Branch("trkPhi",gj.trkPhi,"trkPhi[nTrk]/F");

    
   int nentries = c->GetEntries();
   cout << "number of entries = " << nentries << endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if (jentry% 10000 == 0) cout <<jentry<<" / "<<nentries<<" "<<setprecision(2)<<(double)jentry/nentries*100<<endl;

      c->GetEntry(jentry);

      if ( c->skim.pcollisionEventSelection != 1) 
	 continue;

      for (int j=0;j< c->photon.nPhotons;j++) {
	 order[j] = -1;
	 if ( fabs( c->photon.eta[j] ) < etaCut )
	    newPt[j] = c->getCorrEt(j);
	 else 
	    newPt[j] = - c->photon.pt[j] - 1000;
	 
	 corrPt[j] = newPt[j];
	 
      }
      
   
      
      
      TMath::Sort(c->photon.nPhotons, newPt, order);
      
      
      
      float leadingPt = -100;
      int leadingIndex=-1;
      int awayIndex=-1;
      gj.clear();
      
      for (int j=0 ; j < c->photon.nPhotons ; j++) {
	 if ( fabs(c->photon.eta[j]) > etaCut )    continue;
	 if ( corrPt[j] < ptCut) continue;          // photon pT cut                           
	 if ( c->isSpike(j)) continue;               // spike removal            
	 if (!c->isLoosePhoton(j)) continue;         // final cuts in final plot macro        
	 
	 if ( corrPt[j] > leadingPt ) {
	    leadingIndex = j;
	    leadingPt =  corrPt[j];
	 }
	 
      }
      
      if (leadingIndex!=-1) {
         // set leading photon                                                                                                               
         
	 gj.photonEt=corrPt[leadingIndex];
	 
	 gj.photonRawEt=c->photon.pt[leadingIndex];
         gj.photonEta=c->photon.eta[leadingIndex];
         gj.photonPhi=c->photon.phi[leadingIndex];
         gj.sigmaIetaIeta=c->photon.sigmaIetaIeta[leadingIndex];
	 isol.Set(c,leadingIndex);
	 int nJets=c->akPu3PF.nref;
         float *jet_pt  = c->akPu3PF.jtpt;
         float *jet_eta = c->akPu3PF.jteta;
         float *jet_phi = c->akPu3PF.jtphi;
         for (int j=0;j<nJets;j++) {
            if (jet_pt[j]<cutjetPt) continue;
            if (fabs(jet_eta[j])>cutjetEta) continue;
            if (fabs(deltaPhi(jet_phi[j],c->photon.phi[leadingIndex]))<0.3) continue;
            if (jet_pt[j]>gj.jetEt) {
               gj.jetEt = jet_pt[j];
               awayIndex = j;
            }
         }
	 
	 if (awayIndex !=-1) {
            double photonEt = c->photon.pt[leadingIndex];
            double jetEt = jet_pt[awayIndex];
            double Agj = (photonEt-jetEt)/(photonEt+jetEt);
            gj.jetEt  = jetEt;
            gj.jetEta = jet_eta[awayIndex];
            gj.jetPhi = jet_phi[awayIndex];
            gj.deta = jet_eta[awayIndex] - c->photon.eta[leadingIndex];
            gj.dphi = deltaPhi(jet_phi[awayIndex],c->photon.phi[leadingIndex]);
            gj.Aj   = Agj;
         }
      }
      
      tgj->Fill();
      
   
      
      
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
   

   // After Event Loop                                                                                                                       
   tgj->SetAlias("optIsol","(6.5481e-01 +cc5*8.127033e-03 +cc4*-1.275908e-02 +cc3*-2.24332e-02 +cc2*-6.96778e-02 +cc1*4.682052e-02 +cr5*-2.35164e-02 +cr4*1.74567e-03 +cr3*-2.39334e-04 +cr2*-3.1724e-02 +cr1*-3.65306e-02 +ct4PtCut20*1.8335e-02 +ct3PtCut20*-2.609068e-02 +ct2PtCut20*-4.523171e-02 +ct1PtCut20*-1.270661e-02 +ct5PtCut20*9.218723e-03)");
   tgj->SetAlias("sumIso","(cc4+cr4+ct4PtCut20)/0.9");
   
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
