#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include "TChain.h"

// Convinient Output Classes
class EvtSel {
public:
   int run,evt;
   int cBin;
   int nG,nJ,nT;
   bool trig,offlSel,noiseFilt,anaEvtSel;
   float vz,weight,npart,ncoll,sampleWeight;
};

static const int MAXTRK = 10000;

class GammaJet{
public:
   GammaJet() :
   photonEt(-99),photonEta(0),photonPhi(0),
   jetEt(-99),jetEta(0),jetPhi(0),
   deta(-99),dphi(-99), Aj(-99),
   sigmaIetaIeta(-99),
   isEle(false),
   nTrk(0)
   {}
   float photonEt,photonRawEt,photonEta,photonPhi;
   float jetEt,jetEta,jetPhi;
   float deta,dphi,Aj;
   float hovere,sigmaIetaIeta,sumIsol;
   float phoMatJetEt,phoMatJetEta,phoMatJetPhi;
   float ltrkPt,ltrkEta,ltrkPhi,ltrkJetDr;
   float jltrkPt,jltrkEta,jltrkPhi,jltrkJetDr;
   float refJetEt,refJetEta,refJetPhi;
   bool isEle;
   int nTrk;
   float trkPt[MAXTRK];
   float trkEta[MAXTRK];
   float trkPhi[MAXTRK];   
   float trkJetDr[MAXTRK];   
   void clear() {
      photonEt=-99; photonEta=-99; photonPhi=-99;
      jetEt=-99; jetEta=-99; jetPhi=-99;
      deta=-99; dphi=-99; Aj=-99;
      sigmaIetaIeta=-99;
      phoMatJetEt=-99; phoMatJetEta=-99; phoMatJetPhi=-99;
      ltrkPt=-99; ltrkEta=-99; ltrkPhi=-99; ltrkJetDr=-99;
      jltrkPt=-99; jltrkEta=-99; jltrkPhi=-99; jltrkJetDr=-99;
      refJetEt=-99; refJetEta=-99; refJetPhi=-99;
      isEle=false;
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
      tdata->Add("output-data-Photon-v4_v11.root");
      tmc->Add("output-hypho50v2_50kyongsun_v11.root");

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

float getNpart(int cBin);
float getNcoll(int cBin);

void analyzePhotonJet(
                      //TString inname="/mnt/hadoop/cms/store/user/yinglu/MC_Production/photon50/HiForest_Tree/photon50_25k.root"
                      //TString inname="/d100/velicanu/forest/merged/HiForestPhoton_v1.root",
                      //TString outname="output-data-Photon-v1_v6.root"
                      //TString inname="/d102/velicanu/forest/merged/HiForestPhoton_v2.root",
                      //TString outname="output-data-Photon-v2_v14.root",
                      TString inname="/d102/velicanu/forest/merged/HiForestPhoton_v4.root",
                      TString outname="output-data-Photon-v4_v17.root",
                      double sampleWeight = 1, // data: 1, mc: s = 0.62, b = 0.38
                      //TString inname="/mnt/hadoop/cms/store/user/yinglu/MC_Production/Photon50/HiForest_Tree2/photon50_25k_v2.root",
                      //TString inname="/d102/velicanu/forest/merged/HiForestPhoton_v3.root",
                      //TString outname="output-data-Photon-v3_v10.root",
                      //TString outname="output-hypho50v2_2_v10.root",
                      //TString inname="/net/hidsk0001/d00/scratch/jazzitup/temp/photon50New.root",
                      //TString inname="/d101/kimy/macro/hiPhotonAna2011/rootFiles/photon50_corrCentralityv12.root",
                      //TString outname="output-hypho50v2_50kyongsun_v14_frac62.root",
                      //double sampleWeight = 0.62, // data: 1, mc: s = 0.62, b = 0.38
                      //TString inname="/d101/kimy/macro/hiPhotonAna2011/rootFiles/EM_enriched_Dijet80_60k.root",
                      //TString outname="output-hyuq80em_yongsun60k_v12_frac38.root",
                      //double sampleWeight = 0.38, // data: 1, mc: s = 0.62, b = 0.38
                      //TString inname="/d101/kimy/macro/hiPhotonAna2011/rootFiles/EM_enriched_Dijet120_14k.root",
                      //TString outname="output-hyuq120em_yongsun14k_v12_frac38.root",
                      //double sampleWeight = 1, // data: 1, mc: s = 0.62, b = 0.38
                      //TString inname="/d102/velicanu/forest/merged/HiForestPhoton_v4.root",
                      //TString outname="output-data-Photon-v4_v11.root",
                      bool doCentReWeight=false
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
   c->GetEnergyScaleTable("photonEnergyScaleTable_lowPt_v4.root");
      
   // Output file
   TFile *output = new TFile(outname,"recreate");
   TTree * tgj = new TTree("tgj","gamma jet tree");
   if (doCentReWeight) {
      cw.Init(); //cw.hCentData->Draw(); cw.hCentMc->Draw("same");
   }
   
   EvtSel evt;
   GammaJet gj;
   Isolation isol;
   tgj->Branch("evt",&evt.run,"run/I:evt:cBin:nG:nJ:nT:trig/O:offlSel:noiseFilt:anaEvtSel:vz/F:weight:npart:ncoll:sampleWeight");
   TString jetleaves = "photonEt/F:photonRawEt:photonEta:photonPhi:jetEt:jetEta:jetPhi:deta:dphi:Agj:hovere:sigmaIetaIeta:sumIsol"
   ":phoMatJetEt:phoMatJetEta:phoMatJetPhi:ltrkPt:ltrkEta:ltrkPhi:ltrkJetDr:jltrkPt:jltrkEta:jltrkPhi:jltrkJetDr"
   ":refJetEt:refJetEta:refJetPhi:isEle/O";
   tgj->Branch("jet",&gj.photonEt,jetleaves);
   tgj->Branch("isolation",&isol.cc1,"cc1:cc2:cc3:cc4:cc5:cr1:cr2:cr3:cr4:cr5:ct1PtCut20:ct2PtCut20:ct3PtCut20:ct4PtCut20:ct5PtCut20");
   tgj->Branch("nTrk",&gj.nTrk,"nTrk/I");
   tgj->Branch("trkPt",gj.trkPt,"trkPt[nTrk]/F");
   tgj->Branch("trkEta",gj.trkEta,"trkEta[nTrk]/F");
   tgj->Branch("trkPhi",gj.trkPhi,"trkPhi[nTrk]/F");
   tgj->Branch("trkJetDr",gj.trkJetDr,"trkJetDr[nTrk]/F");
   
   // Main loop
   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      
      // Event Info
      evt.run = c->evt.run;
      evt.evt = c->evt.evt;
      evt.cBin = c->evt.hiBin;
      evt.nG = c->photon.nPhotons;
      evt.nJ = c->icPu5.nref;
      evt.nT = c->track.nTrk;
      evt.trig = (c->hlt.HLT_HISinglePhoton30_v2 > 0);
      evt.offlSel = (c->skim.pcollisionEventSelection > 0);
      evt.noiseFilt = (c->skim.pHBHENoiseFilter > 0);
      evt.anaEvtSel = c->selectEvent() && evt.trig;
      evt.vz = c->track.vz[1];
      // Get Centrality Weight
      if (doCentReWeight) evt.weight = cw.GetWeight(evt.cBin);
      else evt.weight = 1;
      evt.npart = getNpart(evt.cBin);
      evt.ncoll = getNcoll(evt.cBin);
      evt.sampleWeight = sampleWeight; // for different mc sample, 1 for data
      if (i%1000==0) cout <<i<<" / "<<c->GetEntries() << " run: " << evt.run << " evt: " << evt.evt << " bin: " << evt.cBin << " nT: " << evt.nT << " trig: " <<  c->hlt.HLT_HISinglePhoton30_v2 << " anaEvtSel: " << evt.anaEvtSel <<endl;
      
      // initialize
      int leadingIndex=-1;
      int awayIndex=-1;
      gj.clear();
      
      // Loop over jets to look for leading jet candidate in the event
      for (int j=0;j<c->photon.nPhotons;j++) {
         if (c->photon.pt[j]<cutphotonPt||c->photon.pt[j]>1000) continue;          // photon pT cut
         if (fabs(c->photon.eta[j])>cutphotonEta) continue; // |eta|<1.44
         if (c->isSpike(j)) continue;               // spike removal
         if (!c->isLoosePhoton(j)) continue;         // final cuts in final plot macro execpt photon isol and showershape cut
         //if (!c->isLooseEGamma(j)) continue;         // final cuts in final plot macro execpt photon isol and showershape cut, include electrons
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
         gj.isEle=c->photon.isEle[leadingIndex];
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
         float *refjet_pt  = c->akPu3PF.refpt;
         float *refjet_eta = c->akPu3PF.refeta;
         float *refjet_phi = c->akPu3PF.refphi;
         //         int nJets=c->icPu5.nref;
//         float *jet_pt  = c->icPu5.jtpt;
//         float *jet_eta = c->icPu5.jteta;
//         float *jet_phi = c->icPu5.jtphi;
         // Loop over jet tree to find a away side leading jet
         for (int j=0;j<nJets;j++) {
            if (jet_pt[j]<cutjetPt) continue;
            if (fabs(jet_eta[j])>cutjetEta) continue;
            if (fabs(deltaPhi(jet_phi[j],c->photon.phi[leadingIndex]))>0.5) {
               if (jet_pt[j]>gj.jetEt) {
                  gj.jetEt = jet_pt[j];
                  awayIndex = j;
               }
            } else { // Loop over jet tree to find a photon matching jet
               if (jet_pt[j]>gj.phoMatJetEt) {
                  gj.phoMatJetEt = jet_pt[j];
                  gj.phoMatJetEta = jet_eta[j];
                  gj.phoMatJetPhi = jet_phi[j];
               }
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
            gj.refJetEt = refjet_pt[awayIndex];
            gj.refJetEta = refjet_eta[awayIndex];
            gj.refJetPhi = refjet_phi[awayIndex];
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
         gj.trkJetDr[gj.nTrk] = deltaR(gj.trkEta[gj.nTrk],gj.trkPhi[gj.nTrk],gj.jetEta,gj.jetPhi);
         // find leading track
         if (gj.trkPt[gj.nTrk]>gj.ltrkPt) {
            gj.ltrkPt = gj.trkPt[gj.nTrk];
            gj.ltrkEta = gj.trkEta[gj.nTrk];
            gj.ltrkPhi = gj.trkPhi[gj.nTrk];
            gj.ltrkJetDr = gj.trkJetDr[gj.nTrk];
         }
         // find leading track in jet
         if (gj.trkJetDr[gj.nTrk]<0.3 && gj.trkPt[gj.nTrk]>gj.jltrkPt) {
            gj.jltrkPt = gj.trkPt[gj.nTrk];
            gj.jltrkEta = gj.trkEta[gj.nTrk];
            gj.jltrkPhi = gj.trkPhi[gj.nTrk];
            gj.jltrkJetDr = gj.trkJetDr[gj.nTrk];
         }
         ++gj.nTrk;
      }
      
      // All done
      tgj->Fill();
   }

   // After Event Loop
   tgj->SetAlias("fisherIsol","(4.5536204845644690e-01 +cc5*-1.1621087258504197e-03 +cc4*-1.3139962130657250e-02 +cc3*9.8272534188056666e-03 +cc2*-7.9659880964355362e-02 +cc1*5.6661268034678275e-02 +cr5*-1.2763802967154852e-02 +cr4*-1.2594575465310987e-03 +cr3*-1.3333157740152167e-02 +cr2*-2.5518237583408113e-02 +cr1*-1.3706749407235775e-02 +ct4PtCut20*-7.9844325658248016e-03 +ct3PtCut20*-2.5276510400767658e-03 +ct2PtCut20*-2.0741636383420897e-02 +ct1PtCut20*7.1545293456054884e-04 +ct5PtCut20*7.8080659557798627e-03)");
   // * cut at 0.3 from Yongsun's studies
   output->Write();
   output->Close();
   delete c;
}

float getNpart(int cBin) { 
   if (cBin ==0) return 393.633;
   if (cBin ==1) return 368.819;
   if (cBin ==2) return 343.073;
   if (cBin ==3) return 317.625;
   if (cBin ==4) return 292.932;
   if (cBin ==5) return 271.917;
   if (cBin ==6) return 249.851;
   if (cBin ==7) return 230.72;
   if (cBin ==8) return 212.465;
   if (cBin ==9) return 194.752;
   if (cBin ==10) return 178.571;
   if (cBin ==11) return 163.23;
   if (cBin ==12) return 149.187;
   if (cBin ==13) return 136.011;
   if (cBin ==14) return 123.414;
   if (cBin ==15) return 111.7;
   if (cBin ==16) return 100.831;
   if (cBin ==17) return 90.7831;
   if (cBin ==18) return 80.9823;
   if (cBin ==19) return 72.6236;
   if (cBin ==20) return 64.1508;
   if (cBin ==21) return 56.6284;
   if (cBin ==22) return 49.9984;
   if (cBin ==23) return 43.3034;
   if (cBin ==24) return 37.8437;
   if (cBin ==25) return 32.6659;
   if (cBin ==26) return 27.83;
   if (cBin ==27) return 23.7892;
   if (cBin ==28) return 20.1745;
   if (cBin ==29) return 16.8453;
   if (cBin ==30) return 14.0322;
   if (cBin ==31) return 11.602;
   if (cBin ==32) return 9.52528;
   if (cBin ==33) return 7.6984;
   if (cBin ==34) return 6.446;
   if (cBin ==35) return 4.96683;
   if (cBin ==36) return 4.23649;
   if (cBin ==37) return 3.50147;
   if (cBin ==38) return 3.16107;
   if (cBin ==39) return 2.7877;
   return -1;
}

float getNcoll(int cBin) { 
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
   return -1;
}
