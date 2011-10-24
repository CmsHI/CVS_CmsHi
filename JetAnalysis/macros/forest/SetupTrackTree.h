#include "commonSetup.h"

class Tracks
{
  public:

  Tracks(){};
  ~Tracks(){};

   Int_t           nEv;
   Int_t           nLumi;
   Int_t           nBX;
   Int_t           nRun;
   Int_t           nv;
   Float_t         vx[2];   //[nv]
   Float_t         vy[2];   //[nv]
   Float_t         vz[2];   //[nv]
   Int_t           nTrk;
   Float_t         trkPt[maxEntryTrack];   //[nTrk]
   Float_t         trkPtError[maxEntryTrack];   //[nTrk]
   Int_t           trkNHit[maxEntryTrack];   //[nTrk]
   Int_t           trkNlayer[maxEntryTrack];   //[nTrk]
   Int_t           trkNlayer3D[maxEntryTrack];   //[nTrk]
   Float_t         trkEta[maxEntryTrack];   //[nTrk]
   Float_t         trkPhi[maxEntryTrack];   //[nTrk]
   Int_t           trkQual[maxEntryTrack];   //[nTrk]
   Float_t         trkChi2[maxEntryTrack];   //[nTrk]
   Float_t         trkChi2hit1D[maxEntryTrack];   //[nTrk]
   Float_t         trkNdof[maxEntryTrack];   //[nTrk]
   Float_t         trkDz[maxEntryTrack];   //[nTrk]
   Float_t         trkDzError[maxEntryTrack];   //[nTrk]
   Float_t         trkDzError1[maxEntryTrack];   //[nTrk]
   Float_t         trkDzError2[maxEntryTrack];   //[nTrk]
   Float_t         trkDxy[maxEntryTrack];   //[nTrk]
   Float_t         trkDxyBS[maxEntryTrack];   //[nTrk]
   Float_t         trkDxy1[maxEntryTrack];   //[nTrk]
   Float_t         trkDxy2[maxEntryTrack];   //[nTrk]
   Float_t         trkDxyError[maxEntryTrack];   //[nTrk]
   Float_t         trkDxyErrorBS[maxEntryTrack];   //[nTrk]
   Float_t         trkDxyError1[maxEntryTrack];   //[nTrk]
   Float_t         trkDxyError2[maxEntryTrack];   //[nTrk]
   Float_t         trkDz1[maxEntryTrack];   //[nTrk]
   Float_t         trkDz2[maxEntryTrack];   //[nTrk]
   Float_t         trkVx[maxEntryTrack];   //[nTrk]
   Float_t         trkVy[maxEntryTrack];   //[nTrk]
   Float_t         trkVz[maxEntryTrack];   //[nTrk]
   Bool_t          trkFake[maxEntryTrack];   //[nTrk]
   Float_t         trkAlgo[maxEntryTrack];   //[nTrk]

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
   TBranch        *b_trkQual;   //!
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

};

void setupTrackTree(TTree *t, Tracks &tracks)
{
  t->SetBranchAddress("nEv", &tracks.nEv, &tracks.b_nEv);
  t->SetBranchAddress("nLumi", &tracks.nLumi, &tracks.b_nLumi);
  t->SetBranchAddress("nBX", &tracks.nBX, &tracks.b_nBX);
  t->SetBranchAddress("nRun", &tracks.nRun, &tracks.b_nRun);
  t->SetBranchAddress("nv", &tracks.nv, &tracks.b_nv);
  t->SetBranchAddress("vx", tracks.vx, &tracks.b_vx);
  t->SetBranchAddress("vy", tracks.vy, &tracks.b_vy);
  t->SetBranchAddress("vz", tracks.vz, &tracks.b_vz);
  t->SetBranchAddress("nTrk", &tracks.nTrk, &tracks.b_nTrk);
  t->SetBranchAddress("trkPt", tracks.trkPt, &tracks.b_trkPt);
  t->SetBranchAddress("trkPtError", tracks.trkPtError, &tracks.b_trkPtError);
  t->SetBranchAddress("trkNHit", tracks.trkNHit, &tracks.b_trkNHit);
  t->SetBranchAddress("trkNlayer", tracks.trkNlayer, &tracks.b_trkNlayer);
  t->SetBranchAddress("trkNlayer3D", tracks.trkNlayer3D, &tracks.b_trkNlayer3D);
  t->SetBranchAddress("trkEta", tracks.trkEta, &tracks.b_trkEta);
  t->SetBranchAddress("trkPhi", tracks.trkPhi, &tracks.b_trkPhi);
  t->SetBranchAddress("trkQual", tracks.trkQual, &tracks.b_trkQual);
  t->SetBranchAddress("trkChi2", tracks.trkChi2, &tracks.b_trkChi2);
  t->SetBranchAddress("trkChi2hit1D", tracks.trkChi2hit1D, &tracks.b_trkChi2hit1D);
  t->SetBranchAddress("trkNdof", tracks.trkNdof, &tracks.b_trkNdof);
  t->SetBranchAddress("trkDz", tracks.trkDz, &tracks.b_trkDz);
  t->SetBranchAddress("trkDzError", tracks.trkDzError, &tracks.b_trkDzError);
  t->SetBranchAddress("trkDzError1", tracks.trkDzError1, &tracks.b_trkDzError1);
  t->SetBranchAddress("trkDzError2", tracks.trkDzError2, &tracks.b_trkDzError2);
  t->SetBranchAddress("trkDxy", tracks.trkDxy, &tracks.b_trkDxy);
  t->SetBranchAddress("trkDxyBS", tracks.trkDxyBS, &tracks.b_trkDxyBS);
  t->SetBranchAddress("trkDxy1", tracks.trkDxy1, &tracks.b_trkDxy1);
  t->SetBranchAddress("trkDxy2", tracks.trkDxy2, &tracks.b_trkDxy2);
  t->SetBranchAddress("trkDxyError", tracks.trkDxyError, &tracks.b_trkDxyError);
  t->SetBranchAddress("trkDxyErrorBS", tracks.trkDxyErrorBS, &tracks.b_trkDxyErrorBS);
  t->SetBranchAddress("trkDxyError1", tracks.trkDxyError1, &tracks.b_trkDxyError1);
  t->SetBranchAddress("trkDxyError2", tracks.trkDxyError2, &tracks.b_trkDxyError2);
  t->SetBranchAddress("trkDz1", tracks.trkDz1, &tracks.b_trkDz1);
  t->SetBranchAddress("trkDz2", tracks.trkDz2, &tracks.b_trkDz2);
  t->SetBranchAddress("trkVx", tracks.trkVx, &tracks.b_trkVx);
  t->SetBranchAddress("trkVy", tracks.trkVy, &tracks.b_trkVy);
  t->SetBranchAddress("trkVz", tracks.trkVz, &tracks.b_trkVz);
  t->SetBranchAddress("trkFake", tracks.trkFake, &tracks.b_trkFake);
  t->SetBranchAddress("trkAlgo", tracks.trkAlgo, &tracks.b_trkAlgo);

} 
