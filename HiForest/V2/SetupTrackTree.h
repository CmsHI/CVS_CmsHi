//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun 20 12:11:32 2012 by ROOT version 5.27/06b
// from TTree trackTree/v1
// found on file: ../Pythia30_HydjetDrum_mix01_HiForest2_v19.root
//////////////////////////////////////////////////////////
#include "commonSetup.h"
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

class Tracks {
public :
   Tracks(){};
   ~Tracks(){};

   // Declaration of leaf types
   Int_t           nEv;
   Int_t           nLumi;
   Int_t           nBX;
   Int_t           nRun;
   Int_t           nv;
   Float_t         vx[4];   //[nv]
   Float_t         vy[4];   //[nv]
   Float_t         vz[4];   //[nv]
   Int_t           nTrk;
   Float_t         trkPt[6986];   //[nTrk]
   Float_t         trkPtError[6986];   //[nTrk]
   Int_t           trkNHit[6986];   //[nTrk]
   Int_t           trkNlayer[6986];   //[nTrk]
   Int_t           trkNlayer3D[6986];   //[nTrk]
   Float_t         trkEta[6986];   //[nTrk]
   Float_t         trkPhi[6986];   //[nTrk]
   Float_t         dedx[6986];   //[nTrk]
   Bool_t          highPurity[6986];   //[nTrk]
   Bool_t          highPuritySetWithPV[6986];   //[nTrk]
   Float_t         trkChi2[6986];   //[nTrk]
   Float_t         trkChi2hit1D[6986];   //[nTrk]
   Float_t         trkNdof[6986];   //[nTrk]
   Float_t         trkDz[6986];   //[nTrk]
   Float_t         trkDzError[6986];   //[nTrk]
   Float_t         trkDzError1[6986];   //[nTrk]
   Float_t         trkDzError2[6986];   //[nTrk]
   Float_t         trkDxy[6986];   //[nTrk]
   Float_t         trkDxyBS[6986];   //[nTrk]
   Float_t         trkDxy1[6986];   //[nTrk]
   Float_t         trkDxy2[6986];   //[nTrk]
   Float_t         trkDxyError[6986];   //[nTrk]
   Float_t         trkDxyErrorBS[6986];   //[nTrk]
   Float_t         trkDxyError1[6986];   //[nTrk]
   Float_t         trkDxyError2[6986];   //[nTrk]
   Float_t         trkDz1[6986];   //[nTrk]
   Float_t         trkDz2[6986];   //[nTrk]
   Float_t         trkVx[6986];   //[nTrk]
   Float_t         trkVy[6986];   //[nTrk]
   Float_t         trkVz[6986];   //[nTrk]
   Bool_t          trkFake[6986];   //[nTrk]
   Float_t         trkAlgo[6986];   //[nTrk]
   Int_t           pfType[6986];   //[nTrk]
   Float_t         pfCandPt[6986];   //[nTrk]
   Float_t         pfSumEcal[6986];   //[nTrk]
   Float_t         pfSumHcal[6986];   //[nTrk]
   Int_t           nParticle;
   Float_t         pStatus[4040];   //[nParticle]
   Float_t         pPId[4040];   //[nParticle]
   Float_t         pEta[4040];   //[nParticle]
   Float_t         pPhi[4040];   //[nParticle]
   Float_t         pPt[4040];   //[nParticle]
   Float_t         pAcc[4040];   //[nParticle]
   Float_t         pNRec[4040];   //[nParticle]
   Int_t           pNHit[4040];   //[nParticle]
   Float_t         mtrkPt[4040];   //[nParticle]
   Float_t         mtrkPtError[4040];   //[nParticle]
   Int_t           mtrkNHit[4040];   //[nParticle]
   Int_t           mtrkNlayer[4040];   //[nParticle]
   Int_t           mtrkNlayer3D[4040];   //[nParticle]
   Int_t           mtrkQual[4040];   //[nParticle]
   Float_t         mtrkChi2[4040];   //[nParticle]
   Float_t         mtrkNdof[4040];   //[nParticle]
   Float_t         mtrkDz1[4040];   //[nParticle]
   Float_t         mtrkDzError1[4040];   //[nParticle]
   Float_t         mtrkDxy1[4040];   //[nParticle]
   Float_t         mtrkDxyError1[4040];   //[nParticle]
   Float_t         mtrkAlgo[4040];   //[nParticle]
   Int_t           mtrkPfType[4040];   //[nParticle]
   Float_t         mtrkPfCandPt[4040];   //[nParticle]
   Float_t         mtrkPfSumEcal[4040];   //[nParticle]
   Float_t         mtrkPfSumHcal[4040];   //[nParticle]

   // List of branches
   TBranch        *b_nEv;   //!
   TBranch        *b_nLumi;   //!
   TBranch        *b_nBX;   //!
   TBranch        *b_nRun;   //!
   TBranch        *b_nv;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_nTrk;   //!
   TBranch        *b_trkPt;   //!
   TBranch        *b_trkPtError;   //!
   TBranch        *b_trkNHit;   //!
   TBranch        *b_trkNlayer;   //!
   TBranch        *b_trkNlayer3D;   //!
   TBranch        *b_trkEta;   //!
   TBranch        *b_trkPhi;   //!
   TBranch        *b_dedx;   //!
   TBranch        *b_highPurity;   //!
   TBranch        *b_highPuritySetWithPV;   //!
   TBranch        *b_trkChi2;   //!
   TBranch        *b_trkChi2hit1D;   //!
   TBranch        *b_trkNdof;   //!
   TBranch        *b_trkDz;   //!
   TBranch        *b_trkDzError;   //!
   TBranch        *b_trkDzError1;   //!
   TBranch        *b_trkDzError2;   //!
   TBranch        *b_trkDxy;   //!
   TBranch        *b_trkDxyBS;   //!
   TBranch        *b_trkDxy1;   //!
   TBranch        *b_trkDxy2;   //!
   TBranch        *b_trkDxyError;   //!
   TBranch        *b_trkDxyErrorBS;   //!
   TBranch        *b_trkDxyError1;   //!
   TBranch        *b_trkDxyError2;   //!
   TBranch        *b_trkDz1;   //!
   TBranch        *b_trkDz2;   //!
   TBranch        *b_trkVx;   //!
   TBranch        *b_trkVy;   //!
   TBranch        *b_trkVz;   //!
   TBranch        *b_trkFake;   //!
   TBranch        *b_trkAlgo;   //!
   TBranch        *b_pfType;   //!
   TBranch        *b_pfCandPt;   //!
   TBranch        *b_pfSumEcal;   //!
   TBranch        *b_pfSumHcal;   //!
   TBranch        *b_nParticle;   //!
   TBranch        *b_pStatus;   //!
   TBranch        *b_pPId;   //!
   TBranch        *b_pEta;   //!
   TBranch        *b_pPhi;   //!
   TBranch        *b_pPt;   //!
   TBranch        *b_pAcc;   //!
   TBranch        *b_pNRec;   //!
   TBranch        *b_pNHit;   //!
   TBranch        *b_mtrkPt;   //!
   TBranch        *b_mtrkPtError;   //!
   TBranch        *b_mtrkNHit;   //!
   TBranch        *b_mtrkNlayer;   //!
   TBranch        *b_mtrkNlayer3D;   //!
   TBranch        *b_mtrkQual;   //!
   TBranch        *b_mtrkChi2;   //!
   TBranch        *b_mtrkNdof;   //!
   TBranch        *b_mtrkDz1;   //!
   TBranch        *b_mtrkDzError1;   //!
   TBranch        *b_mtrkDxy1;   //!
   TBranch        *b_mtrkDxyError1;   //!
   TBranch        *b_mtrkAlgo;   //!
   TBranch        *b_mtrkPfType;   //!
   TBranch        *b_mtrkPfCandPt;   //!
   TBranch        *b_mtrkPfSumEcal;   //!
   TBranch        *b_mtrkPfSumHcal;   //!

};


void setupTrackTree(TTree *t,Tracks &tTracks,bool doCheck = 0)
{
   // Set branch addresses and branch pointers
   if (t->GetBranch("nEv")) t->SetBranchAddress("nEv", &tTracks.nEv, &tTracks.b_nEv);
   if (t->GetBranch("nLumi")) t->SetBranchAddress("nLumi", &tTracks.nLumi, &tTracks.b_nLumi);
   if (t->GetBranch("nBX")) t->SetBranchAddress("nBX", &tTracks.nBX, &tTracks.b_nBX);
   if (t->GetBranch("nRun")) t->SetBranchAddress("nRun", &tTracks.nRun, &tTracks.b_nRun);
   if (t->GetBranch("nv")) t->SetBranchAddress("nv", &tTracks.nv, &tTracks.b_nv);
   if (t->GetBranch("vx")) t->SetBranchAddress("vx", tTracks.vx, &tTracks.b_vx);
   if (t->GetBranch("vy")) t->SetBranchAddress("vy", tTracks.vy, &tTracks.b_vy);
   if (t->GetBranch("vz")) t->SetBranchAddress("vz", tTracks.vz, &tTracks.b_vz);
   if (t->GetBranch("nTrk")) t->SetBranchAddress("nTrk", &tTracks.nTrk, &tTracks.b_nTrk);
   if (t->GetBranch("trkPt")) t->SetBranchAddress("trkPt", tTracks.trkPt, &tTracks.b_trkPt);
   if (t->GetBranch("trkPtError")) t->SetBranchAddress("trkPtError", tTracks.trkPtError, &tTracks.b_trkPtError);
   if (t->GetBranch("trkNHit")) t->SetBranchAddress("trkNHit", tTracks.trkNHit, &tTracks.b_trkNHit);
   if (t->GetBranch("trkNlayer")) t->SetBranchAddress("trkNlayer", tTracks.trkNlayer, &tTracks.b_trkNlayer);
   if (t->GetBranch("trkNlayer3D")) t->SetBranchAddress("trkNlayer3D", tTracks.trkNlayer3D, &tTracks.b_trkNlayer3D);
   if (t->GetBranch("trkEta")) t->SetBranchAddress("trkEta", tTracks.trkEta, &tTracks.b_trkEta);
   if (t->GetBranch("trkPhi")) t->SetBranchAddress("trkPhi", tTracks.trkPhi, &tTracks.b_trkPhi);
   if (t->GetBranch("dedx")) t->SetBranchAddress("dedx", tTracks.dedx, &tTracks.b_dedx);
   if (t->GetBranch("highPurity")) t->SetBranchAddress("highPurity", tTracks.highPurity, &tTracks.b_highPurity);
   if (t->GetBranch("highPuritySetWithPV")) t->SetBranchAddress("highPuritySetWithPV", tTracks.highPuritySetWithPV, &tTracks.b_highPuritySetWithPV);
   if (t->GetBranch("trkChi2")) t->SetBranchAddress("trkChi2", tTracks.trkChi2, &tTracks.b_trkChi2);
   if (t->GetBranch("trkChi2hit1D")) t->SetBranchAddress("trkChi2hit1D", tTracks.trkChi2hit1D, &tTracks.b_trkChi2hit1D);
   if (t->GetBranch("trkNdof")) t->SetBranchAddress("trkNdof", tTracks.trkNdof, &tTracks.b_trkNdof);
   if (t->GetBranch("trkDz")) t->SetBranchAddress("trkDz", tTracks.trkDz, &tTracks.b_trkDz);
   if (t->GetBranch("trkDzError")) t->SetBranchAddress("trkDzError", tTracks.trkDzError, &tTracks.b_trkDzError);
   if (t->GetBranch("trkDzError1")) t->SetBranchAddress("trkDzError1", tTracks.trkDzError1, &tTracks.b_trkDzError1);
   if (t->GetBranch("trkDzError2")) t->SetBranchAddress("trkDzError2", tTracks.trkDzError2, &tTracks.b_trkDzError2);
   if (t->GetBranch("trkDxy")) t->SetBranchAddress("trkDxy", tTracks.trkDxy, &tTracks.b_trkDxy);
   if (t->GetBranch("trkDxyBS")) t->SetBranchAddress("trkDxyBS", tTracks.trkDxyBS, &tTracks.b_trkDxyBS);
   if (t->GetBranch("trkDxy1")) t->SetBranchAddress("trkDxy1", tTracks.trkDxy1, &tTracks.b_trkDxy1);
   if (t->GetBranch("trkDxy2")) t->SetBranchAddress("trkDxy2", tTracks.trkDxy2, &tTracks.b_trkDxy2);
   if (t->GetBranch("trkDxyError")) t->SetBranchAddress("trkDxyError", tTracks.trkDxyError, &tTracks.b_trkDxyError);
   if (t->GetBranch("trkDxyErrorBS")) t->SetBranchAddress("trkDxyErrorBS", tTracks.trkDxyErrorBS, &tTracks.b_trkDxyErrorBS);
   if (t->GetBranch("trkDxyError1")) t->SetBranchAddress("trkDxyError1", tTracks.trkDxyError1, &tTracks.b_trkDxyError1);
   if (t->GetBranch("trkDxyError2")) t->SetBranchAddress("trkDxyError2", tTracks.trkDxyError2, &tTracks.b_trkDxyError2);
   if (t->GetBranch("trkDz1")) t->SetBranchAddress("trkDz1", tTracks.trkDz1, &tTracks.b_trkDz1);
   if (t->GetBranch("trkDz2")) t->SetBranchAddress("trkDz2", tTracks.trkDz2, &tTracks.b_trkDz2);
   if (t->GetBranch("trkVx")) t->SetBranchAddress("trkVx", tTracks.trkVx, &tTracks.b_trkVx);
   if (t->GetBranch("trkVy")) t->SetBranchAddress("trkVy", tTracks.trkVy, &tTracks.b_trkVy);
   if (t->GetBranch("trkVz")) t->SetBranchAddress("trkVz", tTracks.trkVz, &tTracks.b_trkVz);
   if (t->GetBranch("trkFake")) t->SetBranchAddress("trkFake", tTracks.trkFake, &tTracks.b_trkFake);
   if (t->GetBranch("trkAlgo")) t->SetBranchAddress("trkAlgo", tTracks.trkAlgo, &tTracks.b_trkAlgo);
   if (t->GetBranch("pfType")) t->SetBranchAddress("pfType", tTracks.pfType, &tTracks.b_pfType);
   if (t->GetBranch("pfCandPt")) t->SetBranchAddress("pfCandPt", tTracks.pfCandPt, &tTracks.b_pfCandPt);
   if (t->GetBranch("pfSumEcal")) t->SetBranchAddress("pfSumEcal", tTracks.pfSumEcal, &tTracks.b_pfSumEcal);
   if (t->GetBranch("pfSumHcal")) t->SetBranchAddress("pfSumHcal", tTracks.pfSumHcal, &tTracks.b_pfSumHcal);
   if (t->GetBranch("nParticle")) t->SetBranchAddress("nParticle", &tTracks.nParticle, &tTracks.b_nParticle);
   if (t->GetBranch("pStatus")) t->SetBranchAddress("pStatus", tTracks.pStatus, &tTracks.b_pStatus);
   if (t->GetBranch("pPId")) t->SetBranchAddress("pPId", tTracks.pPId, &tTracks.b_pPId);
   if (t->GetBranch("pEta")) t->SetBranchAddress("pEta", tTracks.pEta, &tTracks.b_pEta);
   if (t->GetBranch("pPhi")) t->SetBranchAddress("pPhi", tTracks.pPhi, &tTracks.b_pPhi);
   if (t->GetBranch("pPt")) t->SetBranchAddress("pPt", tTracks.pPt, &tTracks.b_pPt);
   if (t->GetBranch("pAcc")) t->SetBranchAddress("pAcc", tTracks.pAcc, &tTracks.b_pAcc);
   if (t->GetBranch("pNRec")) t->SetBranchAddress("pNRec", tTracks.pNRec, &tTracks.b_pNRec);
   if (t->GetBranch("pNHit")) t->SetBranchAddress("pNHit", tTracks.pNHit, &tTracks.b_pNHit);
   if (t->GetBranch("mtrkPt")) t->SetBranchAddress("mtrkPt", tTracks.mtrkPt, &tTracks.b_mtrkPt);
   if (t->GetBranch("mtrkPtError")) t->SetBranchAddress("mtrkPtError", tTracks.mtrkPtError, &tTracks.b_mtrkPtError);
   if (t->GetBranch("mtrkNHit")) t->SetBranchAddress("mtrkNHit", tTracks.mtrkNHit, &tTracks.b_mtrkNHit);
   if (t->GetBranch("mtrkNlayer")) t->SetBranchAddress("mtrkNlayer", tTracks.mtrkNlayer, &tTracks.b_mtrkNlayer);
   if (t->GetBranch("mtrkNlayer3D")) t->SetBranchAddress("mtrkNlayer3D", tTracks.mtrkNlayer3D, &tTracks.b_mtrkNlayer3D);
   if (t->GetBranch("mtrkQual")) t->SetBranchAddress("mtrkQual", tTracks.mtrkQual, &tTracks.b_mtrkQual);
   if (t->GetBranch("mtrkChi2")) t->SetBranchAddress("mtrkChi2", tTracks.mtrkChi2, &tTracks.b_mtrkChi2);
   if (t->GetBranch("mtrkNdof")) t->SetBranchAddress("mtrkNdof", tTracks.mtrkNdof, &tTracks.b_mtrkNdof);
   if (t->GetBranch("mtrkDz1")) t->SetBranchAddress("mtrkDz1", tTracks.mtrkDz1, &tTracks.b_mtrkDz1);
   if (t->GetBranch("mtrkDzError1")) t->SetBranchAddress("mtrkDzError1", tTracks.mtrkDzError1, &tTracks.b_mtrkDzError1);
   if (t->GetBranch("mtrkDxy1")) t->SetBranchAddress("mtrkDxy1", tTracks.mtrkDxy1, &tTracks.b_mtrkDxy1);
   if (t->GetBranch("mtrkDxyError1")) t->SetBranchAddress("mtrkDxyError1", tTracks.mtrkDxyError1, &tTracks.b_mtrkDxyError1);
   if (t->GetBranch("mtrkAlgo")) t->SetBranchAddress("mtrkAlgo", tTracks.mtrkAlgo, &tTracks.b_mtrkAlgo);
   if (t->GetBranch("mtrkPfType")) t->SetBranchAddress("mtrkPfType", tTracks.mtrkPfType, &tTracks.b_mtrkPfType);
   if (t->GetBranch("mtrkPfCandPt")) t->SetBranchAddress("mtrkPfCandPt", tTracks.mtrkPfCandPt, &tTracks.b_mtrkPfCandPt);
   if (t->GetBranch("mtrkPfSumEcal")) t->SetBranchAddress("mtrkPfSumEcal", tTracks.mtrkPfSumEcal, &tTracks.b_mtrkPfSumEcal);
   if (t->GetBranch("mtrkPfSumHcal")) t->SetBranchAddress("mtrkPfSumHcal", tTracks.mtrkPfSumHcal, &tTracks.b_mtrkPfSumHcal);
   if (doCheck) {
      if (t->GetMaximum("nv")>4) cout <<"FATAL ERROR: Arrary size of nv too small!!!  "<<t->GetMaximum("nv")<<endl;
      if (t->GetMaximum("nTrk")>6986) cout <<"FATAL ERROR: Arrary size of nTrk too small!!!  "<<t->GetMaximum("nTrk")<<endl;
      if (t->GetMaximum("nParticle")>4040) cout <<"FATAL ERROR: Arrary size of nParticle too small!!!  "<<t->GetMaximum("nParticle")<<endl;
   }
}

