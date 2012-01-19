#ifndef analyzePhotonJet_h
#define analyzePhotonJet_h

// Convinient Output Classes
class EvtSel {
public:
   int run,evt,nOccur,cBin;
   int nG,nJ,nT;
   bool trig,offlSel,noiseFilt,anaEvtSel;
   float vz,weight,npart,ncoll,sampleWeight;
   TString leaves;
   EvtSel(){
      leaves="run/I:evt:nOccur:cBin:nG:nJ:nT:trig/O:offlSel:noiseFilt:anaEvtSel:vz/F:weight:npart:ncoll:sampleWeight";
   }
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
   nTrk(0) {
      leaves = "photonEt/F:photonRawEt:photonEta:photonPhi:jetEt:jetRawEt:jetEta:jetPhi:deta:dphi:Agj:hovere:sigmaIetaIeta:sumIsol"
      ":phoMatJetEt:phoMatJetEta:phoMatJetPhi"
      ":ltrkPt:ltrkEta:ltrkPhi:ltrkJetDr:jltrkPt:jltrkEta:jltrkPhi:jltrkJetDr:jlpfPt:jlpfEta:jlpfPhi:jlpfJetDr:jlpfId"
      ":refPhoPt:refPhoEta:refPhoPhi:refPhoFlavor:refJetEt:refJetEta:refJetPhi:refPartonPt:refPartonFlavor"
      ":isEle/O";
   }
   float photonEt,photonRawEt,photonEta,photonPhi;
   float jetEt,jetRawEt,jetEta,jetPhi;
   float deta,dphi,Aj;
   float hovere,sigmaIetaIeta,sumIsol;
   float phoMatJetEt,phoMatJetEta,phoMatJetPhi;
   float ltrkPt,ltrkEta,ltrkPhi,ltrkJetDr;
   float jltrkPt,jltrkEta,jltrkPhi,jltrkJetDr;
   float jlpfPt,jlpfEta,jlpfPhi,jlpfJetDr,jlpfId;
   float refPhoPt,refPhoEta,refPhoPhi,refPhoFlavor,refJetEt,refJetEta,refJetPhi,refPartonPt,refPartonFlavor;
   bool isEle;
   int nTrk;
   float trkPt[MAXTRK];
   float trkEta[MAXTRK];
   float trkPhi[MAXTRK];   
   float trkJetDr[MAXTRK];
   TString leaves;
   void clear() {
      photonEt=-99; photonEta=-99; photonPhi=-99;
      jetEt=-99; jetRawEt=-99; jetEta=-99; jetPhi=-99;
      deta=-99; dphi=-99; Aj=-99;
      sigmaIetaIeta=-99;
      phoMatJetEt=-99; phoMatJetEta=-99; phoMatJetPhi=-99;
      ltrkPt=-99; ltrkEta=-99; ltrkPhi=-99; ltrkJetDr=-99;
      jltrkPt=-99; jltrkEta=-99; jltrkPhi=-99; jltrkJetDr=-99;
      jlpfPt=-99; jlpfEta=-99; jlpfPhi=-99; jlpfJetDr=-99; jlpfId=-99;
      refPhoPt=-99; refPhoFlavor=-99; refJetEt=-99; refJetEta=-99; refJetPhi=-99; refPartonPt=-99; refPartonFlavor=-99;
      isEle=false;
      nTrk=0;
   }
};

class Isolation{
public:
   float cc1,cc2,cc3,cc4,cc5;
   float cr1,cr2,cr3,cr4,cr5;
   float ct1PtCut20,ct2PtCut20,ct3PtCut20,ct4PtCut20,ct5PtCut20;
   TString leaves;
   Isolation() {
      leaves = "cc1:cc2:cc3:cc4:cc5:cr1:cr2:cr3:cr4:cr5:ct1PtCut20:ct2PtCut20:ct3PtCut20:ct4PtCut20:ct5PtCut20";
   }
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
   CentralityReWeight(TString data, TString mc,TCut s) : 
   datafname(data),mcfname(mc),sel(s) {}
   void Init()
   {
      cout << "Reweight Centrality: " << endl;
      cout << "Data file: " << datafname << endl;
      cout << "MC file:   " << mcfname << endl;
      TChain * tdata = new TChain("tgj");
      TChain * tmc = new TChain("tgj");
      tdata->Add(datafname);
      tmc->Add(mcfname);
      
      hCentData = new TH1D("hCentData","",40,0,40);
      hCentMc = new TH1D("hCentMc","",40,0,40);
      hReWt = new TH1D("hReWt","",40,0,40);
      
      //cout << "data: " << tdata->GetName() << " " << tdata->GetEntries() << endl;
      //cout << "mc: " << tmc->GetName() << " " << tmc->GetEntries() << endl;
      tdata->Project("hCentData","cBin",sel&&"anaEvtSel");
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
   TString datafname,mcfname;
   TCut sel;
   TH1D * hCentData;
   TH1D * hCentMc;
   TH1D * hReWt;
};

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

#endif