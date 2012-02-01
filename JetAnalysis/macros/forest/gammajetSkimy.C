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
#include "commonUtility.h"
using namespace std;

#define PI 3.141592653589
static const int MAXTRK = 10000;

int getNcoll(int cBin=0);

class CentralityReWeight {
public:
   CentralityReWeight(TString data, TString mc,TCut s) :
      datafname(data),mcfname(mc),sel(s) {}
   void Init()
   {
      cout << "Reweight Centrality: " << endl;
      cout << "Data file: " << datafname << endl;
      cout << "MC file:   " << mcfname << endl;
      
      hCentData = new TH1D("hCentData","",40,0,40);
      hCentMc = new TH1D("hCentMc","",40,0,40);
      hReWt = new TH1D("hReWt","",40,0,40);
      
      TCut addCut = "pt[0]>60 && abs(eta[0])<1.44 && swissCrx[0]<0.9";
      TChain * tdata = new TChain("yongsunPhotonTree");
      tdata->Add(datafname);
      tdata->AddFriend("yEvt=yongsunHiEvt",datafname.Data());
      tdata->AddFriend("ySkim=yongsunSkimTree",datafname.Data());
      tdata->Draw("yEvt.hiBin>>hCentData","ySkim.pHBHENoiseFilter>0 && ySkim.pcollisionEventSelection>0" && addCut);

      TChain * tmc = new TChain("multiPhotonAnalyzer/photon");
      tmc->Add(mcfname);
      tmc->AddFriend("yEvt=hiEvtAnalyzer/HiTree",mcfname.Data());
      tmc->AddFriend("ySkim=skimanalysis/HltTree",mcfname.Data());
      tmc->Draw("yEvt.hiBin>>hCentMc","ySkim.pcollisionEventSelection>0" && addCut);
   
      hCentData->Scale(1./hCentData->Integral());
      hCentMc->Scale(1./hCentMc->Integral());
      hReWt->Divide(hCentData,hCentMc);
      
   }
  float GetWeight(int cBin) {
    int bin=cBin+1;
    if (hCentData->GetBinContent(bin)==0 || hCentMc->GetBinContent(bin)==0) {
      return 0;
    }
    return hCentData->GetBinContent(bin)/hCentMc->GetBinContent(bin);
  }
  TString datafname,mcfname;
  TCut sel;
  TH1D * hCentData;
  TH1D * hCentMc;
  TH1D * hReWt;
};



class EvtSel {
public:
  int run;
  int evt;
  int cBin;
  int nG;
  int nJ;
  int nT;
  bool trig;
  bool offlSel;
  bool noiseFilt;
  bool anaEvtSel;
  float vz;
  float reweight;
  
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
    sumIsol(-9999),
    genIso(99999),
    genMomId(-999999),
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
  float hovere,sigmaIetaIeta,sumIsol;
  float genIso;
  int genMomId;
   int nTrk;
   float trkPt[MAXTRK];
   float trkEta[MAXTRK];
   float trkPhi[MAXTRK];
   void clear() {
      photonEt=-99; photonEta=0; photonPhi=0;
      jetEt=-99; jetEta=0; jetPhi=0;
      deta=-99; dphi=-99; Aj=-99;
      sigmaIetaIeta=-99;
      genIso = 9990;
      genMomId = -999999;
      sumIsol = -99;
      nTrk=0;
   }
};




void gammajetSkimy(TString inputFile_="mc/photon50_25k.root", std::string outname = "barrelPhoton50_25k.root",float cutphotonPt  = 45, bool needReweight=true, int maxEvents=-1, TString MinbiasFname="", bool isMC=false) {  // isMC is used for the HbHe noise in MB mixing
  
  
  
  // Data weighting funcition                                                                                                
  TString datafname  = "barrelHiForestPhotonV7-noDupl.root";
  
  float cutphotonEta = 1.44;
  float preCutPhotonEt = 25;
  double cutjetPt = 20;
  double cutjetEta = 2;
  double cutEtaTrk = 2.4;
  
   
   bool doTrigCut(false);
   std::string triggerName = "";
   
   const int nMaxPho = 3000;
   
   HiForest *c = new HiForest(inputFile_.Data());
   c->GetEnergyScaleTable("photonEnergyScaleTable_Hydjet_GammaJet.root");
   
   // now open new root file
   TFile* newfile_data = new TFile(outname.data(),"recreate");
   cout << "Output file " << outname << endl;
   
   TTree* newtree = c->photonTree->CloneTree(0);
   newtree->SetName("yongsunPhotonTree");
   
   TTree* newtreehlt = c->hltTree->CloneTree(0);
   newtreehlt->SetName("yongsunHltTree");
   
   TTree* newtreeSkim = c->skimTree->CloneTree(0);
   newtreeSkim->SetName("yongsunSkimTree");
   
   TTree* newtreeAk3Jet = c->akPu3jetTree->CloneTree(0);
   newtreeAk3Jet->SetName("yongsunJetakPu3PF");
   
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
   newtreeEvt->SetMaxTreeSize(4000000000);
   newtreeAk3Jet->SetMaxTreeSize(4000000000);
   if ( isGen)     newtreeGen->SetMaxTreeSize(4000000000);
   

   
   int ncoll;
   int isLeading[nMaxPho];
   int order[nMaxPho];
   float corrPt[nMaxPho];
   float newPt[nMaxPho];
   float locNtrk[nMaxPho];
   Int_t           nTrk;
   Float_t         trkPt [2000];   //[nTrk] 
   Float_t         trkEta[2000];   //[nTrk] 
   Float_t         trkPhi[2000];   //[nTrk] 

   newtree->Branch("ncoll", &ncoll,"ncoll/I");
   newtree->Branch("order",  order, "order[nPhotons]/I");
   newtree->Branch("corrPt", corrPt,"corrPt[nPhotons]/F");
   newtree->Branch("leading",isLeading,"leading[nPhotons]/I");
   

   // For centrality reweighting
   CentralityReWeight cw(datafname,inputFile_,"");
   if (needReweight ) cw.Init();

   // Output file  // the best photon and best jet should go here.   
   TTree * tgj = new TTree("tgj","gamma jet tree");
   
   GammaJet gj;
   Isolation isol;
   EvtSel evt;
   tgj->Branch("evt",&evt.run,"run/I:evt:cBin:nG:nJ:nT:trig/O:offlSel:noiseFilt:anaEvtSel:vz/F:reweight/F");
   tgj->Branch("jet",&gj.photonEt,"photonEt/F:photonRawEt:photonEta:photonPhi:jetEt:jetEta:jetPhi:deta:dphi:Agj:hovere:sigmaIetaIeta:sumIsol:genIso:genMomId/I");
   tgj->Branch("isolation",&isol.cc1,"cc1:cc2:cc3:cc4:cc5:cr1:cr2:cr3:cr4:cr5:ct1PtCut20:ct2PtCut20:ct3PtCut20:ct4PtCut20:ct5PtCut20");
   tgj->Branch("nTrk",&gj.nTrk,"nTrk/I");
   tgj->Branch("trkPt",gj.trkPt,"trkPt[nTrk]/F");
   tgj->Branch("trkEta",gj.trkEta,"trkEta[nTrk]/F");
   tgj->Branch("trkPhi",gj.trkPhi,"trkPhi[nTrk]/F");
   
   
   TTree * tmixJet = new TTree("tmixJet","jets from minbias events");
   int nmjet;
   float ptMjet[400];
   float etaMjet[400];
   float phiMjet[400];
   tmixJet->Branch("njet",&nmjet,"njet/I");
   tmixJet->Branch("pt",&ptMjet,"pt[njet]/F");
   tmixJet->Branch("eta",&etaMjet,"eta[njet]/F");
   tmixJet->Branch("phi",&phiMjet,"phi[njet]/F");
   
   //For the MB mixing
   const int nMixing = 5;
   TH1D* hrand;
   TChain *tjmb;
   Int_t           nimbj;
   Float_t         imbjpt[200];
   Float_t         imbjeta[200];
   Float_t         imbjphi[200];
   Int_t           ipcoll;
   Int_t           iphcal;
   Int_t           imbcent;
   TBranch        *b_nimbj;
   TBranch        *b_imbjpt;
   TBranch        *b_imbjphi;
   TBranch        *b_imbjeta;
   TBranch        *b_ipcoll;
   TBranch        *b_iphcal;
   TBranch        *b_imbcent;
   
   if ( MinbiasFname !="") {
     tjmb = new TChain("yongsunJetakPu3PF");
     tjmb->Add(MinbiasFname);
     tjmb->AddFriend("yongsunSkimTree",MinbiasFname.Data());
     tjmb->AddFriend("yongsunHiEvt",MinbiasFname.Data());
     tjmb->SetBranchAddress("nref", &nimbj ,&b_nimbj);
     tjmb->SetBranchAddress("jtpt", imbjpt, &b_imbjpt);
     tjmb->SetBranchAddress("jteta", imbjeta, &b_imbjeta);
     tjmb->SetBranchAddress("jtphi", imbjphi, &b_imbjphi);
     tjmb->SetBranchAddress("yongsunSkimTree.pcollisionEventSelection", &ipcoll, &b_ipcoll);
     tjmb->SetBranchAddress("yongsunSkimTree.pHBHENoiseFilter",         &iphcal, &b_iphcal);
     tjmb->SetBranchAddress("yongsunHiEvt.hiBin",                  &imbcent,    &b_imbcent);
     hrand = new TH1D("hrand","",1, 1, tjmb->GetEntries()-1);
     hrand->Fill(2);
     cout << "mb Entries = " << tjmb->GetEntries();
   }
   
   
   /// LOOP!!
   int nentries = c->GetEntries();
   if (maxEvents > 0 ) 
     nentries = maxEvents;
   
   cout << "number of entries = " << nentries << endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     // for (Long64_t jentry=0; jentry<5000;jentry++) {
     if (jentry% 10000 == 0) cout <<jentry<<" / "<<nentries<<" "<<setprecision(2)<<(double)jentry/nentries*100<<endl;
     
      c->GetEntry(jentry);
      // Event Info                                                                                                                                                                                                 
      evt.run = c->evt.run;
      evt.evt = c->evt.evt;
      evt.cBin = c->evt.hiBin;
      evt.nG = c->photon.nPhotons;
      evt.nJ = c->icPu5.nref;
      evt.nT = c->track.nTrk;
      evt.reweight = 1;
      if (needReweight) evt.reweight = cw.GetWeight(c->evt.hiBin);
      evt.trig = (c->hlt.HLT_HISinglePhoton30_v2 > 0);
      evt.offlSel = (c->skim.pcollisionEventSelection > 0);
      evt.noiseFilt = (c->skim.pHBHENoiseFilter > 0);
      evt.anaEvtSel = c->selectEvent() && evt.trig;
      evt.vz = c->track.vz[1];
      
      // calculate corrected pt
      for (int j=0;j< c->photon.nPhotons;j++) {
	
	if (   ( c->photon.pt[j] > preCutPhotonEt )  && ( fabs( c->photon.eta[j] ) < cutphotonEta ) )
	  newPt[j] = c->getCorrEt(j);
	else 
	  newPt[j]  =  c->photon.pt[j] - 10000;
	
	corrPt[j] = newPt[j];

	//  Count out spikes, HoE < 0.2   These should be always synchrinized with the loose cut below. 
	if ( (c->isSpike(j)) || (c->photon.hadronicOverEm[j]>0.2) ||  (c->photon.isEle[j]) )
	  newPt[j] = newPt[j] - 5000;
      }
      // sort the order of photon pt
      TMath::Sort(c->photon.nPhotons, newPt, order);
      
      int leadingIndex=-1;
      int awayIndex=-1;
      
      gj.clear();
      
      for (int j=0;j<c->photon.nPhotons;j++) {
	if ( c->photon.pt[j]  < preCutPhotonEt ) continue;          // photon pT cut   
	if ( fabs(c->photon.eta[j]) > cutphotonEta ) continue;

	// further loose cuts 
	if (c->isSpike(j)) continue;               // spike removal                                  
	if (c->photon.hadronicOverEm[j]>0.2) continue;
	if (c->photon.isEle[j]) continue;
	
	// sort using corrected photon pt                                                                                                                                                     
	float theCorrPt= corrPt[j];
	if ( theCorrPt> gj.photonEt) {
	  gj.photonEt = theCorrPt;
	  leadingIndex = j;
	}
      }
      
      if ( cutphotonPt > 0 ) {   // otherwise we don't cut any events!!
	 if ( gj.photonEt < cutphotonPt ) 
	    continue;
      }
      
      // give the leading bit to the photon candidates 
      for (int j=0;j<c->photon.nPhotons;j++) {
	if ( j==leadingIndex)       isLeading[j] = 1; 
	else                        isLeading[j] = 0;
      }
      
      
      if (leadingIndex!=-1) {
	// set leading photon                                                                                                               
	gj.photonRawEt=c->photon.pt[leadingIndex];
	gj.photonEta=c->photon.eta[leadingIndex];
	gj.photonPhi=c->photon.phi[leadingIndex];
	gj.hovere=c->photon.hadronicOverEm[leadingIndex];
	gj.sigmaIetaIeta=c->photon.sigmaIetaIeta[leadingIndex];
	gj.genIso   = c->photon.genCalIsoDR04[leadingIndex];
	gj.genMomId = c->photon.genMomId[leadingIndex];
	gj.sumIsol=(c->photon.cr4[leadingIndex]+c->photon.cc4[leadingIndex]+c->photon.ct4PtCut20[leadingIndex]);
	isol.Set(c,leadingIndex);
	
	// intialize jet variables                                                                                                                                                                                 
	int nJets=c->akPu3PF.nref;
	float *jet_pt  = c->akPu3PF.jtpt;
	float *jet_eta = c->akPu3PF.jteta;
	float *jet_phi = c->akPu3PF.jtphi;
	// Loop over jet tree to find a away side leading jet                                                                                                                                                      
	for (int j=0;j<nJets;j++) {
	  if (jet_pt[j]<cutjetPt) continue;
	  if (fabs(jet_eta[j])>cutjetEta) continue;
	  if (fabs(deltaPhi(jet_phi[j],c->photon.phi[leadingIndex]))<0.3) continue;
	  if (jet_pt[j]>gj.jetEt) {
	    gj.jetEt = jet_pt[j];
	    awayIndex = j;
	  }
	}
	
	// Found an away jet!                                                                                                                                                                                      
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
      gj.nTrk=0;
      for (int it=0; it<c->track.nTrk; ++it) {
	if (c->track.trkPt[it] < 4) continue;
	if (fabs(c->track.trkEta[it]) > cutEtaTrk) continue;
	gj.trkPt[gj.nTrk] = c->track.trkPt[it];
	gj.trkEta[gj.nTrk] = c->track.trkEta[it];
	gj.trkPhi[gj.nTrk] = c->track.trkPhi[it];
	++gj.nTrk;
      }

      // Add MB jet 
      int iCounter=0;
      nmjet =0;
      while ( (MinbiasFname !="") && (iCounter<nMixing) ) {
	int theEntry = hrand->GetRandom();
	tjmb->GetEntry(theEntry);
	if ( ipcoll == 0 )   
	  continue;
	if ( (!isMC) && ( iphcal == 0  )) 
	  continue;  
	if ( evt.cBin != imbcent ) 
	  continue;
	
	// Now, this is clean minbias events with centrality matched
	// nimbj    imbjpt, imbjeta, imbjphi
	for (int ij = 0 ; ij<nimbj ; ij++) {
	  ptMjet[nmjet] =  imbjpt[ij];
	  etaMjet[nmjet] =  imbjeta[ij];
          phiMjet[nmjet] =  imbjphi[ij];
	  nmjet++;
	}
	//	cout << iCounter<<"th mb events" << endl;
	iCounter++;
      }
      
      //	tjmb->AddFriend("mbSkim=yongsunSkimTree",MinbiasFname.Data());
      //	cout << "mb entreis = " << tjmb->GetEntries();
      //	for ( int jj =  0 ; jj<=20 ; jj++)
      //  cout << " rand = " << (int)hrand->GetRandom() << endl;
      
      ncoll = getNcoll(evt.cBin);
      

      tgj->Fill();
      newtree->Fill();;
      newtreehlt->Fill();
      newtreeSkim->Fill();
      newtreeEvt->Fill();
      newtreeAk3Jet->Fill();
      if ( isGen )
	newtreeGen->Fill();

      if (MinbiasFname !="")
	tmixJet->Fill();
      
   }
   
   
   // After Event Loop                                                                                                                       
   tgj->SetAlias("optIsol","(6.5481e-01 +cc5*8.127033e-03 +cc4*-1.275908e-02 +cc3*-2.24332e-02 +cc2*-6.96778e-02 +cc1*4.682052e-02 +cr5*-2.35164e-02 +cr4*1.74567e-03 +cr3*-2.39334e-04 +cr2*-3.1724e-02 +cr1*-3.65306e-02 +ct4PtCut20*1.8335e-02 +ct3PtCut20*-2.609068e-02 +ct2PtCut20*-4.523171e-02 +ct1PtCut20*-1.270661e-02 +ct5PtCut20*9.218723e-03)");
   tgj->SetAlias("sumIso","(cc4+cr4+ct4PtCut20)/0.9");
   
   
   newfile_data->Write();
   //newfile_data->Close();
   tgj->Draw("offlSel");
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
