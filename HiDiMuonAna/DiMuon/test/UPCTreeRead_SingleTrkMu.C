#ifndef __CINT__
#endif
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TAxis.h"
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TH1I.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TString.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "FitFunctions.h"
#include "TObjArray.h"
void UPCTreeRead_SingleTrkMu()   
{
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetOptTitle(0); // at least most of the time
  gStyle->SetOptStat(1); // most of the time, sometimes "nemriou" might be useful to display name, 
  //number of entries, mean, rms, integral, overflow and underflow
  gStyle->SetOptFit(1); // set to 1 only if you want to display fit results

  Double_t massMu=0.105658;
  Bool_t isTrk =0;
  cout<<" tracks are "<<isTrk<<endl;
  TFile *infile;
  TTree *EventTree;
  char fileName[100];
  //  sprintf(fileName,"rootFiles/DiMuon_UPCTree_All29Aug_2trk.root");
  sprintf(fileName,"rootFiles/DiMuon_UPCTree_TrkMu_All5ep.root");
  
  cout<<" ===================================================================== "<<endl;
  cout<<" opening root file : "<<fileName<<endl;

  infile=new TFile(fileName,"R");
  EventTree=(TTree*)infile->Get("EventTree");


  Int_t           eventNb;
  Int_t           runNb;
  Int_t           lumiBlock;
  Int_t           rbin;

  Int_t           vertexNb;
  Double_t        vertexTrk;
  Bool_t          isVtxFake;
  
  Double_t        vertexX;
  Double_t        vertexY;
  Double_t        vertexZ;
  Double_t        vertexRho;
  Double_t        ZDCEn[18];
  Int_t           glbMuNb;
  Int_t           trackNb;

  Int_t           TrackSize;
  Double_t        TrackPx[10];
  Double_t        TrackPy[10];
  Double_t        TrackPz[10];
  Double_t        TrackEta[10];
  Double_t        TrackPhi[10];
  Double_t        TrackCharge[10];

 

  Int_t           TrackMuSize;
  Double_t        TrackMuPx[100];
  Double_t        TrackMuPy[100];
  Double_t        TrackMuPz[100];
  Double_t        TrackMuEta[100];
  Double_t        TrackMuPhi[100];
  Double_t        TrackMuCharge[100];
  Double_t        TrackMu_nchi2In[100];
  Double_t        TrackMu_dxy[100];
  Double_t        TrackMu_dz[100];
  Int_t           TrackMu_found[100];
  Int_t           TrackMu_pixeLayers[100];
  Int_t           TrackMu_arbitrated[100];
  Int_t           TrackMu_global[100];








 
  Bool_t          eventTrigger0;
  Bool_t          eventTrigger1;
  Bool_t          eventTrigger2;
  Bool_t          eventTrigger3;
  Bool_t          eventTrigger4;
  Bool_t          eventTrigger5;
  Bool_t          eventTrigger6;
  Bool_t          eventTrigger7;
  Bool_t          eventTrigger8;
  Bool_t          eventTrigger9;
  Bool_t          eventTrigger10;

  Int_t           DiMuSize;
  Double_t        DiMuCharge[100];
  Double_t        DiMuMass[100];
  Double_t        DiMuPt[100];
  Double_t        DiMuRap[100];
  Double_t        DiMuPx[100];
  Double_t        DiMuPy[100];
  Double_t        DiMuPz[100];
  Double_t        Mu1Charge[100];
  Double_t        Mu1Mass[100];
  Double_t        Mu1Pt[100];
  Double_t        Mu1Eta[100];
  Double_t        Mu1Px[100];
  Double_t        Mu1Py[100];
  Double_t        Mu1Pz[100];
  Double_t        Mu1Phi[100];
  Double_t        Mu1_nchi2In[100];
  Double_t        Mu1_dxy[100];
  Double_t        Mu1_dz[100];
  Double_t        Mu1_nchi2Gl[100];
  Int_t           Mu1_found[100];
  Int_t           Mu1_pixeLayers[100];
  Int_t           Mu1_nValidMuHits[100];
  Int_t           Mu1_arbitrated[100];
  Int_t          Mu1_tracker[100];
  Int_t          Mu1_global[100];
  Int_t          Mu1_standalone[100];
  Int_t          Mu1_trigger1[100];
  Int_t          Mu1_trigger2[100];
  Int_t          Mu1_trigger3[100];
  Double_t        Mu2Charge[100];
  Double_t        Mu2Mass[100];
  Double_t        Mu2Pt[100];
  Double_t        Mu2Eta[100];
  Double_t        Mu2Px[100];
  Double_t        Mu2Py[100];
  Double_t        Mu2Pz[100];
  Double_t        Mu2Phi[100];
  Double_t        Mu2_nchi2In[100];
  Double_t        Mu2_dxy[100];
  Double_t        Mu2_dz[100];
  Double_t        Mu2_nchi2Gl[100];
  Int_t           Mu2_found[100];
  Int_t           Mu2_pixeLayers[100];
  Int_t           Mu2_nValidMuHits[100];
  Int_t           Mu2_arbitrated[100];
  Int_t          Mu2_tracker[100];
  Int_t          Mu2_global[100];
  Int_t          Mu2_standalone[100];
  Int_t          Mu2_trigger1[100];
  Int_t          Mu2_trigger2[100];
  Int_t          Mu2_trigger3[100];

   // Set branch addresses.
   EventTree->SetBranchAddress("eventNb",&eventNb);
   EventTree->SetBranchAddress("runNb",&runNb);
   EventTree->SetBranchAddress("lumiBlock",&lumiBlock);
   EventTree->SetBranchAddress("rbin",&rbin);

  
   EventTree->SetBranchAddress("vertexNb",&vertexNb);
   EventTree->SetBranchAddress("vertexTrk",&vertexTrk);
   EventTree->SetBranchAddress("isVtxFake",&isVtxFake);
   EventTree->SetBranchAddress("vertexX",&vertexX);
   EventTree->SetBranchAddress("vertexY",&vertexY);
   EventTree->SetBranchAddress("vertexZ",&vertexZ);
   EventTree->SetBranchAddress("vertexRho",&vertexRho);
   EventTree->SetBranchAddress("ZDCEn",ZDCEn);
   EventTree->SetBranchAddress("glbMuNb",&glbMuNb);

    
   EventTree->SetBranchAddress("trackNb",&trackNb);
   EventTree->SetBranchAddress("TrackSize",&TrackSize);
   EventTree->SetBranchAddress("TrackPx",TrackPx);
   EventTree->SetBranchAddress("TrackPy",TrackPy);
   EventTree->SetBranchAddress("TrackPz",TrackPz);
   EventTree->SetBranchAddress("TrackEta",TrackEta);
   EventTree->SetBranchAddress("TrackPhi",TrackPhi);
   EventTree->SetBranchAddress("TrackCharge",TrackCharge);
       
   EventTree->SetBranchAddress("TrackMuSize",&TrackMuSize);
   EventTree->SetBranchAddress("TrackMuPx",TrackMuPx);
   EventTree->SetBranchAddress("TrackMuPy",TrackMuPy);
   EventTree->SetBranchAddress("TrackMuPz",TrackMuPz);
   EventTree->SetBranchAddress("TrackMuEta",TrackMuEta);
   EventTree->SetBranchAddress("TrackMuPhi",TrackMuPhi);
   EventTree->SetBranchAddress("TrackMuCharge",TrackMuCharge);
   EventTree->SetBranchAddress("TrackMu_nchi2In",TrackMu_nchi2In);
   EventTree->SetBranchAddress("TrackMu_dxy",TrackMu_dxy);
   EventTree->SetBranchAddress("TrackMu_dz",TrackMu_dz);
   EventTree->SetBranchAddress("TrackMu_found",TrackMu_found);
   EventTree->SetBranchAddress("TrackMu_pixeLayers",TrackMu_pixeLayers);
   EventTree->SetBranchAddress("TrackMu_arbitrated",TrackMu_arbitrated);
   EventTree->SetBranchAddress("TrackMu_global",TrackMu_global);

   
   EventTree->SetBranchAddress("eventTrigger0",&eventTrigger0);//Double Mu Open
   EventTree->SetBranchAddress("eventTrigger1",&eventTrigger1);//single Mu 3
   EventTree->SetBranchAddress("eventTrigger2",&eventTrigger2);//UPC Mu
   EventTree->SetBranchAddress("eventTrigger3",&eventTrigger3);//HLT_HIZeroBiasPixel_SingleTrack
   EventTree->SetBranchAddress("eventTrigger4",&eventTrigger4);//HLT_HIMinBiasZDC_Calo
   EventTree->SetBranchAddress("eventTrigger5",&eventTrigger5);//HLT_HIMinBiasZDC_Calo_PlusOrMinus
   EventTree->SetBranchAddress("eventTrigger6",&eventTrigger6);//HLT_HIMinBiasZDC_Scint
   EventTree->SetBranchAddress("eventTrigger7",&eventTrigger7);//HLT_HIMinBiasZDCPixel_SingleTrack
   EventTree->SetBranchAddress("eventTrigger8",&eventTrigger8);//HLT_HIL1ETT30
   EventTree->SetBranchAddress("eventTrigger9",&eventTrigger9);//HLT_HIL1ETT60
   EventTree->SetBranchAddress("eventTrigger10",&eventTrigger10);//HLT_HIActivityHF_Coincidence3

   EventTree->SetBranchAddress("DiMuSize",&DiMuSize);
   EventTree->SetBranchAddress("DiMuCharge",DiMuCharge);
   EventTree->SetBranchAddress("DiMuMass",DiMuMass);
   EventTree->SetBranchAddress("DiMuPt",DiMuPt);
   EventTree->SetBranchAddress("DiMuRap",DiMuRap);
   EventTree->SetBranchAddress("DiMuPx",DiMuPx);
   EventTree->SetBranchAddress("DiMuPy",DiMuPy);
   EventTree->SetBranchAddress("DiMuPz",DiMuPz);
   EventTree->SetBranchAddress("Mu1Charge",Mu1Charge);
   EventTree->SetBranchAddress("Mu1Mass",Mu1Mass);
   EventTree->SetBranchAddress("Mu1Pt",Mu1Pt);
   EventTree->SetBranchAddress("Mu1Eta",Mu1Eta);
   EventTree->SetBranchAddress("Mu1Px",Mu1Px);
   EventTree->SetBranchAddress("Mu1Py",Mu1Py);
   EventTree->SetBranchAddress("Mu1Pz",Mu1Pz);
   EventTree->SetBranchAddress("Mu1Phi",Mu1Phi);
   EventTree->SetBranchAddress("Mu1_nchi2In",Mu1_nchi2In);
   EventTree->SetBranchAddress("Mu1_dxy",Mu1_dxy);
   EventTree->SetBranchAddress("Mu1_dz",Mu1_dz);
   EventTree->SetBranchAddress("Mu1_nchi2Gl",Mu1_nchi2Gl);
   EventTree->SetBranchAddress("Mu1_found",Mu1_found);
   EventTree->SetBranchAddress("Mu1_pixeLayers",Mu1_pixeLayers);
   EventTree->SetBranchAddress("Mu1_nValidMuHits",Mu1_nValidMuHits);
   EventTree->SetBranchAddress("Mu1_arbitrated",Mu1_arbitrated);
   EventTree->SetBranchAddress("Mu1_trigger1",Mu1_trigger1);
   EventTree->SetBranchAddress("Mu1_trigger2",Mu1_trigger2);
   EventTree->SetBranchAddress("Mu1_trigger3",Mu1_trigger3);
   EventTree->SetBranchAddress("Mu1_tracker",Mu1_tracker);
   EventTree->SetBranchAddress("Mu1_global",Mu1_global);
   EventTree->SetBranchAddress("Mu1_standalone",Mu1_standalone);
   EventTree->SetBranchAddress("Mu2Charge",Mu2Charge);
   EventTree->SetBranchAddress("Mu2Mass",Mu2Mass);
   EventTree->SetBranchAddress("Mu2Pt",Mu2Pt);
   EventTree->SetBranchAddress("Mu2Eta",Mu2Eta);
   EventTree->SetBranchAddress("Mu2Px",Mu2Px);
   EventTree->SetBranchAddress("Mu2Py",Mu2Py);
   EventTree->SetBranchAddress("Mu2Pz",Mu2Pz);
   EventTree->SetBranchAddress("Mu2Phi",Mu2Phi);
   EventTree->SetBranchAddress("Mu2_nchi2In",Mu2_nchi2In);
   EventTree->SetBranchAddress("Mu2_dxy",Mu2_dxy);
   EventTree->SetBranchAddress("Mu2_dz",Mu2_dz);
   EventTree->SetBranchAddress("Mu2_nchi2Gl",Mu2_nchi2Gl);
   EventTree->SetBranchAddress("Mu2_found",Mu2_found);
   EventTree->SetBranchAddress("Mu2_pixeLayers",Mu2_pixeLayers);
   EventTree->SetBranchAddress("Mu2_nValidMuHits",Mu2_nValidMuHits);
   EventTree->SetBranchAddress("Mu2_arbitrated",Mu2_arbitrated);
   EventTree->SetBranchAddress("Mu2_trigger1",Mu1_trigger1);
   EventTree->SetBranchAddress("Mu2_trigger2",Mu1_trigger2);
   EventTree->SetBranchAddress("Mu2_trigger3",Mu1_trigger3);
   EventTree->SetBranchAddress("Mu2_tracker",Mu2_tracker);
   EventTree->SetBranchAddress("Mu2_global",Mu2_global);
   EventTree->SetBranchAddress("Mu2_standalone",Mu2_standalone);
   
   //================================= Define Histogram =============================================//
  

   TH1D *diTrkInvMass = new TH1D("diTrkInvMass","diTrkInvMass", 100,0,10.0);
   TH1D *diTrkInvMass_SC = new TH1D("diTrkInvMass_SC","diTrkInvMass_SC", 100,0,10.0);

   TH1D *diTrkInvMass1 = new TH1D("diTrkInvMass1","diTrkInvMass1", 100,0,10.0);
   TH1D *diTrkInvMass1_SC = new TH1D("diTrkInvMass1_SC","diTrkInvMass1_SC", 100,0,10.0);

   TH1D *trkAngle= new TH1D("trkAngle","trkAngle", 100,-8.0,8.0);
   TH1D *trkDPt= new TH1D("trkDPt","trkDPt", 100,-8.0,8.0);
   TH1D *trkDPhi= new TH1D("trkDPhi","trkDPhi", 100,-8.0,8.0);





   TH1D *diTrkMuInvMass = new TH1D("diTrkMuInvMass","diTrkMuInvMass", 100,0,10.0);
   TH1D *diTrkMuInvMass_SC = new TH1D("diTrkMuInvMass_SC","diTrkMuInvMass_SC", 100,0,10.0);
   
   TH1D *diTrkMuInvMass1 = new TH1D("diTrkMuInvMass1","diTrkMuInvMass1", 100,0,10.0);
   TH1D *diTrkMuInvMass1_SC = new TH1D("diTrkMuInvMass1_SC","diTrkMuInvMass1_SC", 100,0,10.0);










   TH1D *diMuInvMass = new TH1D("diMuInvMass","diMuInvMass", 100,0,10.0);
   TH1D *diMuInvMass0 = new TH1D("diMuInvMass0","diMuInvMass0", 100,0,10.0);
   diMuInvMass0->GetXaxis()->SetTitle("M_{#mu^{+}#mu^{-}}"); 
   diMuInvMass0->GetYaxis()->SetTitle("Events (0.1 GeV)^{-1}");
   TH1D *diMuInvMass1 = new TH1D("diMuInvMass1","diMuInvMass1", 100,0,10.0);
   TH1D *diMuInvMass2 = new TH1D("diMuInvMass2","diMuInvMass2", 100,0,10.0);
   diMuInvMass2->GetXaxis()->SetTitle("M_{#mu^{+}#mu^{-}}"); 
   diMuInvMass2->GetYaxis()->SetTitle("Events (0.1 GeV)^{-1}");

   TH1D *diMuInvMass3 = new TH1D("diMuInvMass3","diMuInvMass3", 100,0,10.0);
   TH1D *diMuInvMass4 = new TH1D("diMuInvMass4","diMuInvMass4", 100,0,10.0);
    diMuInvMass4->GetXaxis()->SetTitle("M_{#mu^{+}#mu^{-}}");
    diMuInvMass4->GetYaxis()->SetTitle("Events (0.1 GeV)^{-1}");
   TH1D *diMuInvMass5 = new TH1D("diMuInvMass5","diMuInvMass5", 100,0,10.0);
   TH1D *diMuInvMass6 = new TH1D("diMuInvMass6","diMuInvMass6", 100,0,10.0);
   diMuInvMass6->GetXaxis()->SetTitle("M_{#mu^{+}#mu^{-}}");
   TH1D *diMuInvMass7 = new TH1D("diMuInvMass7","diMuInvMass7", 100,0,10.0);
   TH1D *diMuInvMass8 = new TH1D("diMuInvMass8","diMuInvMass8", 100,0,10.0);
   TH1D *diMuInvMass_SC = new TH1D("diMuInvMass_SC","diMuInvMass_SC", 100,0,10.0);


   TH1D *diMuPt = new TH1D("diMuPt","diMuPt", 100,0,1.0);
   TH1D *diMuRap = new TH1D("diMuRap","diMuRap", 100,-5.0,5.0);

   TH1D *muPt = new TH1D("muPt","muPt", 100,0,20.0);
   TH1D *muEta = new TH1D("muEta","muEta", 100,-10.0,10.0);
   TH1D *muPhi = new TH1D("muPhi","muPhi", 100,-5.0,5.0);

   TH1D *muDPt = new TH1D("muDPt","muDPt", 100,0,20.0);
   muDPt->GetXaxis()->SetTitle("#Delta p_{T}");
 
   TH1D *muDPt1 = new TH1D("muDPt1","muDPt1", 100,0,20.0);
   muDPt1->GetXaxis()->SetTitle("#Delta p_{T}");

   TH1D *muDPhi = new TH1D("muDPhi","muDPhi", 100,0.0,7.0);
   muDPhi->GetXaxis()->SetTitle("#Delta #phi"); 
    
   TH1D *muDPhi1 = new TH1D("muDPhi1","muDPhi1", 100,0.0,7.0);
   muDPhi1->GetXaxis()->SetTitle("#Delta #phi"); 

   TH1D *mu3DAngle = new TH1D("mu3DAngle","mu3DAngle", 100,-5.0,5.0);
   mu3DAngle->GetXaxis()->SetTitle("Opening angle");

   TH1D *mu3DAngle1 = new TH1D("mu3DAngle1","mu3DAngle1", 100,-5.0,5.0);
   mu3DAngle1->GetXaxis()->SetTitle("Opening angle");

   TH1D *muTrigger1 = new TH1D("muTrigger1","muTrigger1", 100,0.0,10.0);
   TH1D *muTrigger2 = new TH1D("muTrigger2","muTrigger2", 100,0.0,10.0);
   TH1D *muTrigger3 = new TH1D("muTrigger3","muTrigger3", 100,0.0,10.0);


   //muon cut variables histograms
   TH1D *muChi2In = new TH1D("muChi2In","muChi2In", 100, 0.0,10.0);
   TH1D *muChi2Gl = new TH1D("muChi2Gl","muChi2Gl", 100, 0.0,40.0);
   TH1D *muNTrackHit = new TH1D("muNTrackHit","muNTrackHit", 100,0.0,20.0);
   TH1D *muNPixelLayers = new TH1D("muNPixelLayers","muNPixelLayers", 100,0.0,20.0);
   TH1D *muNValidMuHits = new TH1D("muNValidMuHits","muNValidMuHits", 100,0.0,20.0);
   TH1D *muDxy = new TH1D("muDxy","muDxy", 200,-1.0,1.0);
   TH1D *muDz =  new TH1D("muDz","muDz", 200,-2.0,2.0);


   TH1D *evTrigger0 = new TH1D("evTrigger0","evTrigger0", 100,0.0,10.0);  
   TH1D *evTrigger1 = new TH1D("evTrigger1","evTrigger1", 100,0.0,10.0);
   TH1D *evTrigger2 = new TH1D("evTrigger2","evTrigger2", 100,0.0,10.0);
   TH1D *evTrigger3 = new TH1D("evTrigger3","evTrigger3", 100,0.0,10.0);
   TH1D *evTrigger4 = new TH1D("evTrigger4","evTrigger4", 100,0.0,10.0);
   TH1D *evTrigger5 = new TH1D("evTrigger5","evTrigger5", 100,0.0,10.0);
   TH1D *evTrigger6 = new TH1D("evTrigger6","evTrigger6", 100,0.0,10.0);
   TH1D *evTrigger7 = new TH1D("evTrigger7","evTrigger7", 100,0.0,10.0);
   TH1D *evTrigger8 = new TH1D("evTrigger8","evTrigger8", 100,0.0,10.0);
   TH1D *evTrigger9 = new TH1D("evTrigger9","evTrigger9", 100,0.0,10.0);
   TH1D *evTrigger10 = new TH1D("evTrigger10","evTrigger10", 100,0.0,10.0);


   TH1D *nTrack = new TH1D("nTrack","nTrack", 100,0,20.0);
   TH1D *nBin = new TH1D("nBin","nBin", 100,0,40.0);
   
   TH1D *nPVtx = new TH1D("nPVtx","nPVtx", 100,0,40.0);
   TH1D *nPVtxTrk = new TH1D("nPVtxTrk","nPVtxTrk", 1000,0,1000.0);
   TH1D *nPVtxX = new TH1D("nPVtxX","nPVtxX", 100,0.0,0.2);
   TH1D *nPVtxY = new TH1D("nPVtxY","nPVtxY", 100,0.0,0.2);
   TH1D *nPVtxZ = new TH1D("nPVtxZ","nPVtxZ", 100,-40,40.0);
   TH1D *nPVtxRho = new TH1D("nPVtxRho","nPVtxRho", 100,0.0,0.2);


   TH2D *TrackVsBin = new TH2D("TrackVsBin","TrackVsBin",2000,0.,1500.,40,0.,40.);


   TH1D *ZdcEnEM_P = new TH1D("ZdcEnEM_P","ZdcEnEM_P", 100,0,2000.0);
   TH1D *ZdcEnHd_P = new TH1D("ZdcEnHd_P","ZdcEnHd_P", 100,0,40000.0);
   TH1D *ZdcEnN_P = new TH1D("ZdcEnN_P","ZdcEnN_P", 100,0,10000.0);
   
   TH2D *ZDCEnCor_P = new TH2D("ZDCEnCor_P","ZDCEnCor_P",100,0.,2000.,100,0.,100000.);
   ZDCEnCor_P->GetXaxis()->SetTitle("EM Energy");
   ZDCEnCor_P->GetYaxis()->SetTitle("Hd Energy");
   
 
   TH1D *ZdcEnEM_M = new TH1D("ZdcEnEM_M","ZdcEnEM_M", 100,0,2000.0);
   TH1D *ZdcEnHd_M = new TH1D("ZdcEnHd_M","ZdcEnHd_M", 100,0,40000.0);
   TH1D *ZdcEnN_M = new TH1D("ZdcEnN_M","ZdcEnN_M", 100,0,100000.0);
   
   TH2D *ZDCEnCor_M = new TH2D("ZDCEnCor_M","ZDCEnCor_M",100,0.,2000.,100,0.,100000.);
   ZDCEnCor_M->GetXaxis()->SetTitle("EM Energy");
   ZDCEnCor_M->GetYaxis()->SetTitle("Hd Energy");



  //=======================================Read Tree===================================================//
   
   Int_t nentries = EventTree->GetEntries();
   // nentries=100;
   for (Int_t j=0; j<nentries;j++) {   //event loop
     EventTree->GetEntry(j);
     
     if(j%25000==0)cout<<" processing record " <<j<<" "<< "Run "<<runNb <<" event "<<eventNb<<" lum block "<<lumiBlock<<endl;
     
     Double_t ZdcEmEn_P=0.0,ZdcHdEn_P=0.0,ZdcNEn_P=0.0;
     Double_t ZdcEmEn_M=0.0,ZdcHdEn_M=0.0,ZdcNEn_M=0.0;
     
    
     //for( Int_t k =0; k<18;k++){
     //if(ZDCEn[k]<0)
     //	 {
     //	   ZDCEn[k]=0;
     //	 } 
     //}
     
     if(runNb >= 151350){
     ZdcEmEn_P=ZDCEn[0]+ZDCEn[1]+ZDCEn[2]+ZDCEn[3]+ZDCEn[4];
     ZdcHdEn_P=ZDCEn[5]+ZDCEn[6]+ZDCEn[7]+ZDCEn[8];
     ZdcNEn_P= (ZdcEmEn_P * (0.78283/0.025514))+ZdcHdEn_P;
    
     ZdcEmEn_M=ZDCEn[9]+ZDCEn[10]+ZDCEn[11]+ZDCEn[12]+ZDCEn[13];
     ZdcHdEn_M=ZDCEn[14]+ZDCEn[15]+ZDCEn[16]+ZDCEn[17];
     ZdcNEn_M= (ZdcEmEn_M * (0.78283/0.025514))+ZdcHdEn_M;
     }

     //ZdcEmEn_P= ZdcEmEn_P * (0.78283/0.025514);
     //ZdcEmEn_P= ZdcEmEn_P * (0.78283/0.025514);
    
     //alpha * Sum(EnergyEM) * (0.78283/0.025514) + Sum(EnergyHAD)   

     //for (Int_t k=0; k<18;k++) {cout<<" ZDC En ch # "<<k<<" Energy : "<<ZDCEn[k]<<endl;}
     //cout<<vertexX<<"  "<<vertexY<<" "<<vertexRho<<endl;;

     Int_t nGlobal=0;
     
     nPVtx->Fill(vertexNb); 
     nPVtxTrk->Fill(vertexTrk); 
     nPVtxX->Fill(vertexX); 
     nPVtxY->Fill(vertexY);
     nPVtxZ->Fill(vertexZ); 
     nPVtxRho->Fill(vertexRho); 

     //if(trackNb==2){
     ZdcEnEM_P->Fill(ZdcEmEn_P);
     ZdcEnHd_P->Fill(ZdcHdEn_P);
     ZdcEnN_P->Fill(ZdcNEn_P);
     ZDCEnCor_P->Fill(ZdcEmEn_P,ZdcNEn_P);
     
     ZdcEnEM_M->Fill(ZdcEmEn_M);
     ZdcEnHd_M->Fill(ZdcHdEn_M);
     ZdcEnN_M->Fill(ZdcNEn_M);
     ZDCEnCor_M->Fill(ZdcEmEn_M,ZdcNEn_M);

     //}

     Bool_t passEv = 0;
     if(eventTrigger0==1 && vertexNb==1 && (!isVtxFake) && TMath::Abs(vertexZ)<=25 && vertexRho < 2) passEv =1;
     // cout<<" no of rec tracks : "<<TrackSize<<endl;
     
     //Track loop
     for (Int_t trk1=0; trk1<TrackSize;trk1++){
       for (Int_t trk2=trk1+1; trk2<TrackSize;trk2++){ 
	 TVector3 vtrk1(TrackPx[trk1],TrackPy[trk1],TrackPz[trk1]);
	 Double_t trk1_e =sqrt( (vtrk1.Mag()*vtrk1.Mag() ) + (massMu*massMu) );
	 TLorentzVector ltrk1(vtrk1,trk1_e);
	 TVector3 vtrk2(TrackPx[trk2],TrackPy[trk2],TrackPz[trk2]);
	 Double_t trk2_e =sqrt((vtrk2.Mag()*vtrk2.Mag())+(massMu*massMu));
	 TLorentzVector ltrk2(vtrk2,trk2_e);
	 TLorentzVector ditrk = ltrk1+ltrk2;
	 
	 Double_t TrkAngle = vtrk1.Angle(vtrk2);
	 Double_t TrkDPhi=TMath::Abs( TrackPhi[trk1] - TrackPhi[trk2] );
	 Double_t TrkDPt= TMath::Sqrt( (TrackPx[trk1]*TrackPx[trk1] - TrackPx[trk2]*TrackPx[trk2]) + (TrackPy[trk1]*TrackPy[trk1]-TrackPy[trk2]*TrackPy[trk2]));

	 Int_t  DiTrkChrage =TrackCharge[trk1]+TrackCharge[trk2];
	 Double_t DiTrkMass= ditrk.M();
	 Double_t DiTrkPt=ditrk.Pt();
	 Double_t DiTrkRap=ditrk.Rapidity();
	 Double_t DiTrkPx=ditrk.Px();
	 Double_t DiTrkPy=ditrk.Py();
	 Double_t DiTrkPz=ditrk.Pz();
	 
	 if(passEv && TrackSize==2) trkAngle->Fill(TrkAngle);
	 if(passEv && TrackSize==2) trkDPt->Fill(TrkDPt);
	 if(passEv && TrackSize==2) trkDPhi->Fill(TrkDPhi);


	 if(passEv && TrackSize==2 && DiTrkChrage==0) diTrkInvMass->Fill(DiTrkMass); 
	 if(passEv && TrackSize==2 && (DiTrkChrage==2 || DiTrkChrage==-2) ) diTrkInvMass_SC->Fill(DiTrkMass);
      

	 Bool_t PassTrkEx=0; 
	 if( (TrkDPhi > TMath::Pi()*0.9 && TrkDPhi<TMath::Pi()*1.1) && (TrkAngle < 0.95*TMath::Pi()) && (TrkDPt<=0.6))PassTrkEx=1;
	
	 if( passEv && TrackSize==2 && DiTrkChrage==0 && PassTrkEx) diTrkInvMass1->Fill(DiTrkMass); 
	    
	   
	 
	 if(passEv && TrackSize==2 && (DiTrkChrage==2 || DiTrkChrage==-2) && PassTrkEx )diTrkInvMass1_SC->Fill(DiTrkMass);

       }
     }


     //Track Mu loop


     cout<<" trk mu size "<<TrackMuSize<<endl;
     for (Int_t trkmu1=0; trkmu1<TrackMuSize;trkmu1++){
       for (Int_t trkmu2=trkmu1+1; trkmu2<TrackMuSize;trkmu2++){ 
	 

	 TVector3 vtrkmu1(TrackMuPx[trkmu1],TrackMuPy[trkmu1],TrackMuPz[trkmu1]);
	 Double_t trkmu1_e =sqrt( (vtrkmu1.Mag()*vtrkmu1.Mag() ) + (massMu*massMu) );
	 TLorentzVector ltrkmu1(vtrkmu1,trkmu1_e);
	 TVector3 vtrkmu2(TrackMuPx[trkmu2],TrackMuPy[trkmu2],TrackMuPz[trkmu2]);
	 Double_t trkmu2_e =sqrt((vtrkmu2.Mag()*vtrkmu2.Mag())+(massMu*massMu));
	 TLorentzVector ltrkmu2(vtrkmu2,trkmu2_e);
	 TLorentzVector ditrkmu = ltrkmu1+ltrkmu2;
	 
	 Double_t TrkMuAngle = vtrkmu1.Angle(vtrkmu2);
	 Double_t TrkMuDPhi=TMath::Abs( TrackMuPhi[trkmu1] - TrackMuPhi[trkmu2] );
	 Double_t TrkMuDPt= TMath::Sqrt( (TrackMuPx[trkmu1]*TrackMuPx[trkmu1] - TrackMuPx[trkmu2]*TrackMuPx[trkmu2]) + (TrackMuPy[trkmu1]*TrackMuPy[trkmu1]-TrackMuPy[trkmu2]*TrackMuPy[trkmu2]));

	 Int_t  DiTrkMuChrage =TrackMuCharge[trkmu1]+TrackMuCharge[trkmu2];
	 Double_t DiTrkMuMass= ditrkmu.M();
	 Double_t DiTrkMuPt=ditrkmu.Pt();
	 Double_t DiTrkMuRap=ditrkmu.Rapidity();
	 Double_t DiTrkMuPx=ditrkmu.Px();
	 Double_t DiTrkMuPy=ditrkmu.Py();
	 Double_t DiTrkMuPz=ditrkmu.Pz();
	 // cout<<" trk mu "<<DiTrkMuMass<<" mass "<<DiTrkMuChrage<<" charge "<<endl;
	 if(passEv && TrackMuSize==2 && DiTrkMuChrage==0)diTrkMuInvMass->Fill(DiTrkMuMass);
	 if(passEv && TrackMuSize==2 && (DiTrkMuChrage==2 ||DiTrkMuChrage==-2))diTrkMuInvMass_SC->Fill(DiTrkMuMass);

       }
 }















     
     nBin->Fill(rbin);
     TrackVsBin->Fill(trackNb,rbin);
     evTrigger0->Fill(eventTrigger0);
     evTrigger1->Fill(eventTrigger1);
     evTrigger2->Fill(eventTrigger2);
     evTrigger3->Fill(eventTrigger3);
     evTrigger4->Fill(eventTrigger4);
     evTrigger5->Fill(eventTrigger5);
     evTrigger6->Fill(eventTrigger6);
     evTrigger7->Fill(eventTrigger7);
     evTrigger8->Fill(eventTrigger8);
     evTrigger9->Fill(eventTrigger9);
     evTrigger10->Fill(eventTrigger10);

     int NGoodPairs =0;
     int Mu1Good=0;
     int Mu2Good=0;

     for (Int_t i=0; i<DiMuSize;i++) {     
       if(Mu1_tracker[i]==1 && Mu1_found[i] > 10 && Mu1_pixeLayers[i] > 0 && Mu1_nchi2In[i] < 4.0 && Mu1_dxy[i] < 3 && Mu1_dz[i] < 3 ) Mu1Good=1;
       if(Mu2_tracker[i]==1 && Mu2_found[i] > 10 && Mu2_pixeLayers[i] > 0 && Mu2_nchi2In[i] < 4.0 && Mu2_dxy[i] < 3 && Mu2_dz[i] < 3 )  Mu2Good=1;
       if( Mu1Good==1 && Mu2Good==1) NGoodPairs++; 
     }
     
     //dimuon loop
     for (Int_t i=0; i<DiMuSize;i++) 
       {   
       	 if( Mu1_global[i] &&  Mu2_global[i] ) nGlobal=1;
      	 muTrigger1->Fill(Mu1_trigger1[i]);
	 muTrigger2->Fill(Mu1_trigger2[i]);
	 muTrigger3->Fill(Mu1_trigger3[i]);
	 muTrigger1->Fill(Mu2_trigger1[i]);
	 muTrigger2->Fill(Mu2_trigger2[i]);
	 muTrigger3->Fill(Mu2_trigger3[i]);
	 
	 muChi2In->Fill(Mu1_nchi2In[i]); 
	 muChi2Gl->Fill(Mu1_nchi2Gl[i]);  
	 muNTrackHit->Fill(Mu1_found[i]);  
	 muNPixelLayers->Fill(Mu1_pixeLayers[i]);  
	 muNValidMuHits->Fill(Mu1_nValidMuHits[i]);  
	 muDxy->Fill(Mu1_dxy[i]);  
	 muDz->Fill(Mu1_dz[i]);  

	 muChi2In->Fill(Mu2_nchi2In[i]); 
	 muChi2Gl->Fill(Mu2_nchi2Gl[i]);  
	 muNTrackHit->Fill(Mu2_found[i]);  
	 muNPixelLayers->Fill(Mu2_pixeLayers[i]);  
	 muNValidMuHits->Fill(Mu2_nValidMuHits[i]);  
	 muDxy->Fill(Mu2_dxy[i]);  
	 muDz->Fill(Mu2_dz[i]);  



	 TVector3 vMu1(Mu1Px[i],Mu1Py[i],Mu1Pz[i]);
	 TVector3 vMu2(Mu2Px[i],Mu2Py[i],Mu2Pz[i]);
       
	 Double_t Angle = vMu1.Angle(vMu2);
	 Double_t MuDPhi=TMath::Abs(Mu1Phi[i]-Mu2Phi[i]);
	 //Double_t MuDPt= TMath::Abs(Mu1Pt[i]-Mu2Pt[i]);
	 Double_t MuDPt= TMath::Sqrt((Mu1Px[i]*Mu1Px[i]-Mu2Px[i]*Mu2Px[i]) + (Mu1Py[i]*Mu1Py[i]-Mu2Py[i]*Mu2Py[i]));
	 
	 int Mu1Pass=0;
	 int Mu2Pass=0;
       
	 // cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),

	 //if(Mu1_tracker[i]==1 && Mu1_global[i]==1 && Mu1_found[i] > 10 && Mu1_pixeLayers[i] > 0 && Mu1_nchi2In[i] < 4.0 && Mu1_dxy[i] < 3 && Mu1_dz[i] < 15 && Mu1_nchi2Gl[i] < 20 && Mu1Eta[i]<=2.4 ) Mu1Pass=1;
	 //if(Mu2_tracker[i]==1 && Mu2_global[i]==1 && Mu2_found[i] > 10 && Mu2_pixeLayers[i] > 0 && Mu2_nchi2In[i] < 4.0 && Mu2_dxy[i] < 3 && Mu2_dz[i] < 15 && Mu2_nchi2Gl[i] < 20 && Mu2Eta[i]<=2.4)  Mu2Pass=1;

	 if(Mu1_tracker[i]==1 && Mu1_found[i] > 10 && Mu1_pixeLayers[i] > 0 && Mu1_nchi2In[i] < 4.0 && Mu1_dxy[i] < 3 && Mu1_dz[i] < 3 ) Mu1Pass=1;
	 if(Mu2_tracker[i]==1 && Mu2_found[i] > 10 && Mu2_pixeLayers[i] > 0 && Mu2_nchi2In[i] < 4.0 && Mu2_dxy[i] < 3 && Mu2_dz[i] < 3 ) Mu2Pass=1;
	
	 Bool_t pass0 = eventTrigger0==1 && vertexNb==1 && (!isVtxFake) && TMath::Abs(vertexZ)<=25 && vertexRho < 2 ;

	 Bool_t pass1 = pass0 && (Mu1Pass==1 && Mu2Pass==1) && (TMath::Abs(Mu1Eta[i]) < 2.4 && TMath::Abs(Mu2Eta[i])< 2.4);

	 Bool_t pass2 = pass1 &&  trackNb==2;

	 Bool_t pass3 = pass2 && (MuDPhi > TMath::Pi()*0.9 && MuDPhi < TMath::Pi()*1.1 ) && Angle<0.95*TMath::Pi();

	 Bool_t pass4 = pass3 && (MuDPt<=0.6);
    
	 // Bool_t barrel = (Mu1Eta[i] < 0.8 && Mu2Eta[i] < 0.8);
	 //Bool_t endcap = (Mu1Eta[i] > 0.8 && Mu2Eta[i] > 0.8);

	 Bool_t passSame = eventTrigger0==1 && vertexNb==1 &&vertexTrk==2 && (!isVtxFake) && (DiMuCharge[i]==2 || DiMuCharge[i]== -2) && (Mu1Pass==1 && Mu2Pass==1);

	 if(pass0) diMuInvMass0->Fill(DiMuMass[i]); 

	 if(pass1) diMuInvMass1->Fill(DiMuMass[i]); 
	 
	 if(pass2 && DiMuCharge[i]==0 ) diMuInvMass2->Fill(DiMuMass[i]); 

	 if(pass2 && ( DiMuCharge[i]==2 || DiMuCharge[i]== -2 ) ) diMuInvMass3->Fill(DiMuMass[i]); 

	 if(pass4 && (DiMuCharge[i]==0) ) diMuInvMass4->Fill(DiMuMass[i]); 

	 if( pass4 && ( DiMuCharge[i]==2 || DiMuCharge[i]== -2 ) ) diMuInvMass5->Fill(DiMuMass[i]);
 
	 // if(pass3 && (MuDPt<=0.4) ) {
	  if(pass4 && (DiMuCharge[i]==0) ) {
	    cout<<" mu D "<<MuDPt<<endl;
	   diMuInvMass6->Fill(DiMuMass[i]); 
	   cout << DiMuMass[i] << endl;
	   cout << Mu1Pt[i] <<"    " << Mu2Pt[i] << endl;
	   cout << Mu1Eta[i] <<"    " << Mu2Eta[i] << endl;
	   cout << Mu1Phi[i] <<"    " << Mu2Phi[i] << endl;
	  
	   cout<<"Run "<<runNb <<" event "<<eventNb<<" lum block "<<lumiBlock<<endl;

	   
	   //cout<< ZdcNEn_P<<"      "<<ZdcNEn_M<<endl;
	   //cout<<ZDCEn[0]<<" "<<ZDCEn[1]<<" "<<ZDCEn[2]<<" "<<ZDCEn[3]<<" "<<ZDCEn[4]<<endl;
	   //cout<<ZDCEn[5]<<" "<<ZDCEn[6]<<" "<<ZDCEn[7]<<" "<<ZDCEn[8]<<endl;

	 }



	 //if((DiMuCharge[i]==0) && vertexNb==1 && eventTrigger0 == 1 && trackNb==2 && ( Mu1Pt[i]>0 && Mu2Pt[i]>0) && (Mu1Pass==1 && Mu2Pass==1)&&(MuDPhi> TMath::Pi()*0.9)&& (Angle <0.95*TMath::Pi()) ) diMuInvMass5->Fill(DiMuMass[i]); 
	

	 if(pass4  && (DiMuCharge[i]==0) ) {
	     // diMuInvMass7->Fill(DiMuMass[i]); 
	     diMuInvMass->Fill(DiMuMass[i]);
	     diMuPt->Fill(DiMuPt[i]);
	     diMuRap->Fill(DiMuRap[i]);
	     muPt->Fill(Mu1Pt[i]);
	     muPt->Fill(Mu2Pt[i]);
	     
	     muEta->Fill(Mu1Eta[i]);
	     muEta->Fill(Mu2Eta[i]);
	     muPhi->Fill(Mu1Phi[i]);
	     muPhi->Fill(Mu2Phi[i]);
	     
	   }

	   if(passSame &&  trackNb==2 && (MuDPhi > TMath::Pi()*0.9) && Angle<0.95*TMath::Pi() && (MuDPt<=1.0) ) 
	   { 
	     diMuInvMass_SC->Fill(DiMuMass[i]);     
	   }

     
	 // if((eventTrigger2==1 && trackNb >0) && (DiMuCharge[i]==2 ||DiMuCharge[i]== -2) && ( Mu1_global[i] && Mu1_found[i] > 10 && Mu1_pixeLayers[i] > 0 && Mu1_nchi2In[i] < 4.0 && Mu1_dxy[i] < 3 && Mu1_dz[i] < 15 && Mu1_nchi2Gl[i] < 20) && (Mu2_global[i] && Mu2_found[i] > 10 && Mu2_pixeLayers[i] > 0 && Mu2_nchi2In[i] < 4.0 && Mu2_dxy[i] < 3 && Mu2_dz[i] < 15 && Mu2_nchi2Gl[i] < 20)     )
	 
	 if (pass1)
	   { 
	     muDPt->Fill(MuDPt);
	     muDPhi->Fill(MuDPhi);
	     mu3DAngle->Fill(Angle);
	   }

	
	 if(pass3){
	   muDPt1->Fill(MuDPt);
	   muDPhi1->Fill(MuDPhi);
	   mu3DAngle1->Fill(Angle);
	   }

	 
       }//dimuon loop

     if(nGlobal==1) {nTrack->Fill(trackNb);}
     
    
   

   } //event loop 
   
   
   new TCanvas;
   diTrkMuInvMass->Draw();
   diTrkMuInvMass_SC->SetLineColor(2);
   diTrkMuInvMass_SC->Draw("same");
   gPad->SaveAs("plots/diTrkMuInvMass.png");



   new TCanvas;
   diTrkInvMass->Draw();
   diTrkInvMass_SC->SetLineColor(2);
   diTrkInvMass_SC->Draw("same");
   gPad->SaveAs("plots/diTrkInvMass.png");

   new TCanvas;
   trkAngle->Draw();
   new TCanvas;
   trkDPt->Draw();
   new TCanvas;
   trkDPhi->Draw();

   new TCanvas;
   diTrkInvMass1->Draw();
   diTrkInvMass1_SC->SetLineColor(2);
   diTrkInvMass1_SC->Draw("same");
   gPad->SaveAs("plots/diTrkInvMass1.png");



   new TCanvas;
   diMuInvMass2->Draw();
   


   //return;

   new TCanvas;
   nPVtx->Draw();
   new TCanvas;
   nPVtxTrk->Draw(); 
   new TCanvas;
   nPVtxX->Draw();
   new TCanvas;    
   nPVtxY->Draw();
   new TCanvas;    
   nPVtxZ->Draw();

   new TCanvas;    
   nPVtxRho->Draw();

      
   new TCanvas;
   ZdcEnEM_P->Draw();
   gPad->SaveAs("plots/ZdcEnEm_P.png");

   new TCanvas;
   ZdcEnHd_P->Draw();
   gPad->SaveAs("plots/ZdcEnHd_P.png");
  
   new TCanvas;
   ZdcEnN_P->Draw();
   gPad->SaveAs("plots/ZdcEnN_P.png");
 
   new TCanvas;
   ZDCEnCor_P->Draw("Colz");
   gPad->SaveAs("plots/ZdcEnCor_P.png");


   new TCanvas;
   ZdcEnEM_M->Draw();
   gPad->SaveAs("plots/ZdcEnEm_M.png");

   new TCanvas;
   ZdcEnHd_M->Draw();
   gPad->SaveAs("plots/ZdcEnHd_M.png");
   
   new TCanvas;
   ZdcEnN_M->Draw();
   gPad->SaveAs("plots/ZdcEnN_M.png");


   new TCanvas;
   ZDCEnCor_M->Draw("Colz");
   gPad->SaveAs("plots/ZdcEnCor_M.png");

   



   new TCanvas;    
   nBin->Draw();
   new TCanvas;    
   TrackVsBin->Draw("Colz");
   // return;

   new TCanvas;
   diMuInvMass0->Draw();
   gPad->SaveAs("plots/DiMuMass0.png");
   new TCanvas;
   diMuInvMass1->Draw();
   
   new TCanvas;
   diMuInvMass2->Draw();
   diMuInvMass3->SetLineColor(2);
   diMuInvMass3->Draw("same");
   gPad->SaveAs("plots/DiMuMass2.png");
   
   new TCanvas;
   diMuInvMass3->Draw();
   
   new TCanvas;
   diMuInvMass4->Draw();
   diMuInvMass5->SetLineColor(2);
   diMuInvMass5->Draw("same");
   gPad->SaveAs("plots/DiMuMass4.png");
   
   new TCanvas;

   diMuInvMass5->Draw();
  
   new TCanvas;
   //diMuInvMass6->SetLineColor(2);
   diMuInvMass6->Draw();
  
   new TCanvas;
   diMuInvMass7->Draw();
   gPad->SaveAs("plots/DiMuMass7.png");
 
   new TCanvas;
   diMuInvMass8->Draw();
  
   new TCanvas;
   diMuInvMass->Draw();
   diMuInvMass_SC->SetLineColor(2);
   diMuInvMass_SC->Draw("same");
   gPad->SaveAs("plots/DiMuMass.png");
 
   TCanvas *CPT = new TCanvas;
   CPT->SetLogy();
   diMuPt->Draw();
   gPad->SaveAs("plots/DiMuPt.png");

   new TCanvas;
   diMuRap->Draw();
   gPad->SaveAs("plots/DiMuRap.png");

   TCanvas *C2 = new TCanvas;
   C2->SetLogy();
   nTrack->Draw();
   gPad->SaveAs("plots/NTrack.png");
   
  
   
   new TCanvas;
   muDPhi->Draw();
   gPad->SaveAs("plots/muDPhi.png");
   new TCanvas;
   mu3DAngle->Draw();
   gPad->SaveAs("plots/mu3DAngle.png");
   new TCanvas;
   muDPt->Draw();
   gPad->SaveAs("plots/muDPt.png");
   
   new TCanvas;
   muDPhi1->Draw();
    gPad->SaveAs("plots/muDPhi1.png");
   new TCanvas;
   mu3DAngle1->Draw();
   gPad->SaveAs("plots/mu3DAngle1.png");
   new TCanvas;
   muDPt1->Draw();
   gPad->SaveAs("plots/muDPt1.png");
    
     
   new TCanvas;
   muPt->Draw();


   new TCanvas;
   muDPt->Draw();

   new TCanvas;
   muEta->Draw();

   new TCanvas;
   muPhi->Draw();

   new TCanvas;
   muDPhi->Draw();


   TCanvas *Ct = new TCanvas;
   Ct->SetLogy();
   nTrack->Draw();
   gPad->SaveAs("plots/NTrack.png");
   
   TCanvas *C1 = new TCanvas;
   C1->SetLogy();
   nBin->Draw();
   gPad->SaveAs("plots/NBin.png");

   new TCanvas;
   TrackVsBin->Draw("colz");
   


   new TCanvas;
   mu3DAngle->Draw();


   




   /*
   new TCanvas;
   muChi2In->Draw();
   new TCanvas;
   muChi2Gl->Draw();
   new TCanvas;
   muNTrackHit->Draw();
   new TCanvas;
   muNPixelLayers->Draw();
   new TCanvas;
   muNValidMuHits->Draw();
   new TCanvas;
   muDxy->Draw();
   new TCanvas;
   muDz->Draw();
   


  
   



   new TCanvas;
   muTrigger1->Draw();
   new TCanvas;
   muTrigger2->Draw();
   new TCanvas;
   muTrigger3->Draw();
    

   new TCanvas;
   evTrigger0->Draw();
   
   new TCanvas;
   evTrigger1->Draw();
   
   new TCanvas;
   evTrigger2->Draw();
   
   new TCanvas;
   evTrigger3->Draw();
   
   new TCanvas;
   evTrigger4->Draw();
 
   new TCanvas;
   evTrigger5->Draw();

   new TCanvas;
   evTrigger6->Draw();
   
   new TCanvas;
   evTrigger7->Draw();
   
   new TCanvas;
   evTrigger8->Draw();

   new TCanvas;
   evTrigger9->Draw();

   new TCanvas;
   evTrigger10->Draw();
   
   */

}


//For the PbPb 2010 data taking, run # 151350 corresponds to the first run taken with the changed gain for ZDC data
//(Gains were changed from pp settings to those appropriate for PbPb). reference
//From ZdcRecHits: Energyneutron = alpha * Sum(EnergyEM) * (0.78283/0.025514) + Sum(EnergyHAD), where alpha = 1, 
//Sum is over all channels of that type. (Calculate one energy per event per ZDC side (as selected above))
//For the latest calibration recommendation, see the ZDC hypernews or ZDC Wednesday meetings. 
//(alpha = 1.35, total Energy modified by dividing by 1.48). 
