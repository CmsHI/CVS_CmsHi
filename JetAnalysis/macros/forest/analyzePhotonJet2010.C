#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include "TChain.h"

// Convinient Output Classes
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
   float vz,weight;
};

static const int MAXTRK = 10000;

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
   float hovere,sigmaIetaIeta,sumIsol;
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

class CentralityReWeight {
public:
   CentralityReWeight(TCut s) : sel(s) {}
   void Init()
   {
      TChain * tdata = new TChain("tgj");
      TChain * tmc = new TChain("tgj");
      tdata->Add("output-data-Photon-v3_v9.root");
      tmc->Add("output-hypho50v2_50kyongsun_v10_noreweight.root");

      hCentData = new TH1D("hCentData","",40,0,40);
      hCentMc = new TH1D("hCentMc","",40,0,40);
      hReWt = new TH1D("hReWt","",40,0,40);

      //cout << "data: " << tdata->GetName() << " " << tdata->GetEntries() << endl;
      //cout << "mc: " << tmc->GetName() << " " << tmc->GetEntries() << endl;
      tdata->Project("hCentData","cBin",sel&&"trig&&noiseFilt");
      tmc->Project("hCentMc","cBin",sel);
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
   TCut sel;
   TH1D * hCentData;
   TH1D * hCentMc;
   TH1D * hReWt;
};

void analyzePhotonJet2010(
                          //TString inname="/d100/yjlee/hiForest/merged_HI2010_SD_Photon40_prod02.root",
                          //TString outname="output-data-HI2010-Photon40_prod02_v10.root",
                          TString inname="/d100/yjlee/hiForest/merged_pp2760_AllPhysics_Part_Prod03.root",
                          TString outname="output-data-pp2010-prod3-photon_v10.root",
                          bool doCentReWeight=false,
                          bool isPp=true
    )
{
   double cutphotonPt = 40; // highest photon trigger is 20, also photon correction valid for photon pt > 40
   double cutjetPt = 20;
   double cutphotonEta = 1.44;
   double cutjetEta = 2;
   double cutEtaTrk = 2.4;	

   // Centrality reweiting
   CentralityReWeight cw("offlSel&&photonEt>50");

   // Define the input file and HiForest
   HiForest *c = new HiForest(inname);
   c->GetEnergyScaleTable("photonEnergyScaleTable_Hydjet_GammaJet.root");
      
   // Output file
   TFile *output = new TFile(outname,"recreate");
   TTree * tgj = new TTree("tgj","gamma jet tree");
   if (doCentReWeight) {
      cw.Init(); //cw.hCentData->Draw(); cw.hCentMc->Draw("same");
   }
   
   EvtSel evt;
   GammaJet gj;
   Isolation isol;
   tgj->Branch("evt",&evt.run,"run/I:evt:cBin:nG:nJ:nT:trig/O:offlSel:noiseFilt:anaEvtSel:vz/F:weight");
   tgj->Branch("jet",&gj.photonEt,"photonEt/F:photonRawEt:photonEta:photonPhi:jetEt:jetEta:jetPhi:deta:dphi:Agj:hovere:sigmaIetaIeta:sumIsol");
   tgj->Branch("isolation",&isol.cc1,"cc1:cc2:cc3:cc4:cc5:cr1:cr2:cr3:cr4:cr5:ct1PtCut20:ct2PtCut20:ct3PtCut20:ct4PtCut20:ct5PtCut20");
   tgj->Branch("nTrk",&gj.nTrk,"nTrk/I");
   tgj->Branch("trkPt",gj.trkPt,"trkPt[nTrk]/F");
   tgj->Branch("trkEta",gj.trkEta,"trkEta[nTrk]/F");
   tgj->Branch("trkPhi",gj.trkPhi,"trkPhi[nTrk]/F");
   
   int runNum=-1,evtNum=-1,centBin=-1,HLT_Photon15_CaloIdVL_v1=0;
   int phfCoincFilter=0,ppurityFractionFilter=0,pHBHENoiseFilter=0;
   c->hltTree->SetBranchAddress("Run",&runNum);
   c->hltTree->SetBranchAddress("Event",&evtNum);
   c->hltTree->SetBranchAddress("hiBin",&centBin);
   if (isPp) {
      c->hltTree->SetBranchAddress("HLT_Photon15_CaloIdVL_v1",&HLT_Photon15_CaloIdVL_v1);
      c->skimTree->SetBranchAddress("phfCoincFilter",&phfCoincFilter);
      c->skimTree->SetBranchAddress("ppurityFractionFilter",&ppurityFractionFilter);
      c->skimTree->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter);
   }
   // Main loop
   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      
      // Event Info
      evt.run = runNum;
      evt.evt = evtNum;
      evt.cBin = centBin;
      evt.nG = c->photon.nPhotons;
      evt.nJ = c->icPu5.nref;
      evt.nT = c->track.nTrk;
      evt.trig = (c->hlt.HLT_HISinglePhoton30_v2 > 0);
      evt.offlSel = (c->skim.pcollisionEventSelection > 0);
      evt.noiseFilt = (c->skim.pHBHENoiseFilter > 0);
      evt.anaEvtSel = c->selectEvent() && evt.trig;
      if (isPp) {
         evt.trig = (HLT_Photon15_CaloIdVL_v1>0);
         evt.offlSel = phfCoincFilter && ppurityFractionFilter && pHBHENoiseFilter;
         evt.anaEvtSel = evt.offlSel && evt.trig;
      }
      evt.vz = c->track.vz[1];
      // Get Centrality Weight
      if (doCentReWeight) evt.weight = cw.GetWeight(evt.cBin);
      else evt.weight = 1;
      if (i%10000==0) cout <<i<<" / "<<c->GetEntries() << " run: " << evt.run << " evt: " << evt.evt << " bin: " << evt.cBin << " nT: " << evt.nT << " trig: " <<  evt.trig << " offlSel: " << evt.offlSel <<endl;
      if (!evt.trig) continue;
      
      // initialize
      int leadingIndex=-1;
      int awayIndex=-1;
      gj.clear();
      
      // Loop over jets to look for leading jet candidate in the event
      for (int j=0;j<c->photon.nPhotons;j++) {
         if (c->photon.pt[j]<cutphotonPt) continue;          // photon pT cut
         if (fabs(c->photon.eta[j])>cutphotonEta) continue; // |eta|<1.44
         if (c->isSpike(j)) continue;               // spike removal
         if (!c->isLoosePhoton(j)) continue;         // final cuts in final plot macro
         // sort using corrected photon pt
         float corrPt=c->getCorrEt(j);
         if (corrPt>gj.photonEt) {
            gj.photonEt = corrPt;
            leadingIndex = j;
         }
      }
      
      // Found a leading jet which passed basic quality cut!
      if (leadingIndex!=-1) {
         // set leading photon
         gj.photonRawEt=c->photon.pt[leadingIndex];
         gj.photonEta=c->photon.eta[leadingIndex];
         gj.photonPhi=c->photon.phi[leadingIndex];
         gj.hovere=c->photon.hadronicOverEm[leadingIndex];
         gj.sigmaIetaIeta=c->photon.sigmaIetaIeta[leadingIndex];
         gj.sumIsol=(c->photon.cr4[leadingIndex]+c->photon.cc4[leadingIndex]+c->photon.ct4PtCut20[leadingIndex]);
         isol.Set(c,leadingIndex);
         
         // intialize jet variables
         int nJets=c->akPu3PF.nref;
         float *jet_pt  = c->akPu3PF.jtpt;
         float *jet_eta = c->akPu3PF.jteta;
         float *jet_phi = c->akPu3PF.jtphi;
//         int nJets=c->icPu5.nref;
//         float *jet_pt  = c->icPu5.jtpt;
//         float *jet_eta = c->icPu5.jteta;
//         float *jet_phi = c->icPu5.jtphi;
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
      
      // xcheck with tracks
      gj.nTrk=0;
      for (int it=0; it<c->track.nTrk; ++it) {
         if (c->track.trkPt[it] < 4) continue;
         if (fabs(c->track.trkEta[it]) > cutEtaTrk) continue;
         gj.trkPt[gj.nTrk] = c->track.trkPt[it];
         gj.trkEta[gj.nTrk] = c->track.trkEta[it];
         gj.trkPhi[gj.nTrk] = c->track.trkPhi[it];
         ++gj.nTrk;
      }
      
      // All done
      tgj->Fill();
   }

   // After Event Loop
   tgj->SetAlias("optIsol","(6.5481e-01 +cc5*8.127033e-03 +cc4*-1.275908e-02 +cc3*-2.24332e-02 +cc2*-6.96778e-02 +cc1*4.682052e-02 +cr5*-2.35164e-02 +cr4*1.74567e-03 +cr3*-2.39334e-04 +cr2*-3.1724e-02 +cr1*-3.65306e-02 +ct4PtCut20*1.8335e-02 +ct3PtCut20*-2.609068e-02 +ct2PtCut20*-4.523171e-02 +ct1PtCut20*-1.270661e-02 +ct5PtCut20*9.218723e-03)");
   // * cut at 0.3 from Yongsun's studies
   output->Write();
   output->Close();
   delete c;
}
