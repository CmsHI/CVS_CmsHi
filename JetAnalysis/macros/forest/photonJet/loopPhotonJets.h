#ifndef loopPhotonJets_h
#define loopPhotonJets_h

// Convinient Output Classes
class EvtSel {
public:
   int run,evt,nOccur,cBin;
   int nG,nJ,nT;
   bool trig,offlSel,noiseFilt,anaEvtSel;
   float vz,weight,npart,ncoll,sampleWeight,evtPlane,pthat,samplePtHat;
   TString leaves;
   EvtSel(){
      leaves="run/I:evt:nOccur:cBin:nG:nJ:nT:trig/O:offlSel:noiseFilt:anaEvtSel:vz/F:weight:npart:ncoll:sampleWeight:evtPlane:pthat:samplePtHat";
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
   nTrk(0),nJet(0) {
      leaves = "photonEt/F:photonRawEt:photonEta:photonPhi:jetEt:jetRawEt:jetEta:jetPhi:deta:dphi:Agj:hovere:sigmaIetaIeta:sumIsol"
      ":phoMatJetEt:phoMatJetEta:phoMatJetPhi"
      ":ltrkPt:ltrkEta:ltrkPhi:ltrkJetDr:jltrkPt:jltrkEta:jltrkPhi:jltrkJetDr"
      ":jlpfPt:jlpfEta:jlpfPhi:jlpfJetDr:jlpfId:pfPhoPt"
      ":refPhoPt:refPhoEta:refPhoPhi:refPhoFlavor:genCalIsoDR04:refJetEt:refJetEta:refJetPhi:refPartonPt:refPartonFlavor"
      ":genPhoPt:genPhoEta:genPhoPhi:genJetPt:genJetEta:genJetPhi"
      ":isEle/O";
   }
   float photonEt,photonRawEt,photonEta,photonPhi;
   float jetEt,jetRawEt,jetEta,jetPhi;
   float deta,dphi,Aj;
   float hovere,sigmaIetaIeta,sumIsol;
   float phoMatJetEt,phoMatJetEta,phoMatJetPhi;
   float ltrkPt,ltrkEta,ltrkPhi,ltrkJetDr,jltrkPt,jltrkEta,jltrkPhi,jltrkJetDr;
   float jlpfPt,jlpfEta,jlpfPhi,jlpfJetDr,jlpfId,pfPhoPt;
   float refPhoPt,refPhoEta,refPhoPhi,refPhoFlavor,genCalIsoDR04,refJetEt,refJetEta,refJetPhi,refPartonPt,refPartonFlavor;
   float genPhoPt,genPhoEta,genPhoPhi,genJetPt,genJetEta,genJetPhi;
   bool isEle;
   int nTrk;
   float trkPt[MAXTRK];
   float trkEta[MAXTRK];
   float trkPhi[MAXTRK];   
   float trkJetDr[MAXTRK];
   int nJet;
   float inclJetPt[MAXTRK];
   float inclJetEta[MAXTRK];
   float inclJetPhi[MAXTRK];   
   float inclJetRefPt[MAXTRK];
   float inclJetRefPartonPt[MAXTRK];
   float inclJetRefResp[MAXTRK];
   int nGenJet;
   float inclGenJetPt[MAXTRK];
   float inclGenJetEta[MAXTRK];
   float inclGenJetPhi[MAXTRK];   
   float inclGenJetResp[MAXTRK];
   int nPf;
   float pfPt[MAXTRK];
   float pfEta[MAXTRK];
   float pfPhi[MAXTRK];
   int pfId[MAXTRK];
   int nGenp;
   float genpPt[MAXTRK];
   float genpEta[MAXTRK];
   float genpPhi[MAXTRK];
   int genpCh[MAXTRK];
   TString leaves;
   void clear() {
      photonEt=-99; photonEta=-99; photonPhi=-99;
      jetEt=-99; jetRawEt=-99; jetEta=-99; jetPhi=-99;
      deta=-99; dphi=-99; Aj=-99;
      sigmaIetaIeta=-99;
      phoMatJetEt=-99; phoMatJetEta=-99; phoMatJetPhi=-99;
      ltrkPt=-99; ltrkEta=-99; ltrkPhi=-99; ltrkJetDr=-99;
      jltrkPt=-99; jltrkEta=-99; jltrkPhi=-99; jltrkJetDr=-99;
      jlpfPt=-99; jlpfEta=-99; jlpfPhi=-99; jlpfJetDr=-99; jlpfId=-99; pfPhoPt=0;
      refPhoPt=-99; refPhoFlavor=-99; refJetEt=-99; refJetEta=-99; refJetPhi=-99; refPartonPt=-99; refPartonFlavor=-99;
      genPhoPt=-99; genPhoEta=-99; genPhoPhi=-99; genJetPt=-99; genJetEta=-99; genJetPhi=-99;
      isEle=false;
      nTrk=0; nJet=0; nGenJet=0; nPf=0; nGenp=0;
   }
};

void LoadGJBranches(TTree * tgj, EvtSel & evt, GammaJet & gj) {
   tgj->SetBranchAddress("evt",&evt.run);
   tgj->SetBranchAddress("jet",&gj.photonEt);
   tgj->SetBranchAddress("nJet",&gj.nJet);
   tgj->SetBranchAddress("inclJetPt",gj.inclJetPt);
   tgj->SetBranchAddress("inclJetEta",gj.inclJetEta);
   tgj->SetBranchAddress("inclJetPhi",gj.inclJetPhi);
   tgj->SetBranchAddress("nPf",&gj.nPf);
   tgj->SetBranchAddress("pfPt",gj.pfPt);
   tgj->SetBranchAddress("pfEta",gj.pfEta);
   tgj->SetBranchAddress("pfPhi",gj.pfPhi);
   tgj->SetBranchAddress("pfId",gj.pfId);
}


#endif