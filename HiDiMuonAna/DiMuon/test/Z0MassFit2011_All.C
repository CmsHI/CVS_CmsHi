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
#include "TF1.h"
#include "TH1I.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TVector3.h"
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
bool IsAccept(Double_t pt, Double_t eta);
double FindCenWeight(int Bin);
void Z0MassFit2011_All(int iSpec = 1, int PutWeight=1)
{
  //See pT Cut
  double PtCut= 10.0;
  
  //minbias integrated, |y|<1.2 and |y|\in[1.2,2.4], centrality [0,10][10,20][20,100]%,  pt [0,6.5], [6.5, 10] [10,20]

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
  gStyle->SetOptStat(0); // most of the time, sometimes "nemriou" might be useful to display name, 
  //number of entries, mean, rms, integral, overflow and underflow
  gStyle->SetOptFit(1); // set to 1 only if you want to display fit results
  
  //==================================== Define Histograms====================================================
  char OutTextFile[100]; 
  if(iSpec==1) sprintf(OutTextFile,"EffZ0_Pt.tex");
  if(iSpec==2) sprintf(OutTextFile,"EffZ0_Rap.tex");
  if(iSpec==3) sprintf(OutTextFile,"EffZ0_Cent.tex");
  


  // ofstream dataFile(Form("Eff_Z0_Pt.txt"));
  ofstream dataFile(Form(OutTextFile));
  

  TH1D *diMuonsInvMass_Gen = new TH1D("diMuonsInvMass_Gen","diMuonsInvMass_Gen", 100,60.0,120.0);
  TH1D *diMuonsPt_Gen = new TH1D("diMuonsPt_Gen","diMuonsPt_Gen", 100,0,30);
  TH1D *diMuonsRap_Gen = new TH1D("diMuonsRap_Gen","diMuonsRap_Gen", 100,-5,5);
  

  //Rapidity Gen
  TH1D *diMuonsRap_Gen0 = new TH1D("diMuonsRap_Gen0","diMuonsRap_Gen0", 100,-5,5);
  TH1D *diMuonsRap_Gen1 = new TH1D("diMuonsRap_Gen1","diMuonsRap_Gen1", 100,-5,5);
  TH1D *diMuonsRap_Gen2 = new TH1D("diMuonsRap_Gen2","diMuonsRap_Gen2", 100,-5,5);
  TH1D *diMuonsRap_Gen3 = new TH1D("diMuonsRap_Gen3","diMuonsRap_Gen3", 100,-5,5);
  TH1D *diMuonsRap_Gen4 = new TH1D("diMuonsRap_Gen4","diMuonsRap_Gen4", 100,-5,5);
  TH1D *diMuonsRap_Gen5 = new TH1D("diMuonsRap_Gen5","diMuonsRap_Gen5", 100,-5,5);
  



  ////Rapidity Reco
  TH1D *diMuonsRap_Rec0 = new TH1D("diMuonsRap_Rec0","diMuonsRap_Rec0", 100,-5,5);
  diMuonsRap_Rec0->SetLineColor(2);
  TH1D *diMuonsRap_Rec1 = new TH1D("diMuonsRap_Rec1","diMuonsRap_Rec1", 100,-5,5);
  diMuonsRap_Rec1->SetLineColor(2);
  TH1D *diMuonsRap_Rec2 = new TH1D("diMuonsRap_Rec2","diMuonsRap_Rec2", 100,-5,5);
  diMuonsRap_Rec2->SetLineColor(2);
  TH1D *diMuonsRap_Rec3 = new TH1D("diMuonsRap_Rec3","diMuonsRap_Rec3", 100,-5,5);
  diMuonsRap_Rec3->SetLineColor(2);
  TH1D *diMuonsRap_Rec4 = new TH1D("diMuonsRap_Rec4","diMuonsRap_Rec4", 100,-5,5);
  diMuonsRap_Rec4->SetLineColor(2);
  TH1D *diMuonsRap_Rec5 = new TH1D("diMuonsRap_Rec5","diMuonsRap_Rec5", 100,-5,5);
  diMuonsRap_Rec5->SetLineColor(2);
  TH1D *Bin_Gen = new TH1D("Bin_Gen","Bin_Gen", 40,0,40);
  


  TH1D *MuonPt_Gen = new TH1D("MuonPt_Gen","MuonPt_Gen", 100,0,20);
 
  TH1D *MuonEta_Gen = new TH1D("MuonEta_Gen","MuonEta_Gen", 100,-3,3);
 
  TH1D *MuonPhi_Gen = new TH1D("MuonPhi_Gen","MuonPhi_Gen", 100,0,4);

  TH1D *Cent_Gen = new TH1D("Cent_Gen","Cent_Gen", 50,0,50);
  Cent_Gen->GetXaxis()->SetTitle("bin");
  TH1D *Cent_Rec = new TH1D("Cent_Rec","Cent_Rec", 50,0,50);


  //==============================================Define AccEff Stuff here===========================================
  // Pt bin sizes
  int Nptbin=1;
  double pt_bound[100] = {0};
  if(iSpec == 1) { 
    Nptbin = 1;
    
   
    //for plots
    pt_bound[0] = 0.0;
    pt_bound[1] = 40.0;
    pt_bound[2] = 7.0;
    pt_bound[3] = 11.0;
    pt_bound[4] = 14.0;
    pt_bound[5] = 18.0;
    pt_bound[6] = 25.0;
    pt_bound[7] = 30.0;
    


    // pt_bound[0] = 0;
    //pt_bound[1] = 20.0;
    //pt_bound[2] = 10.0;
    //pt_bound[3] = 30.0;
    //pt_bound[4] = 10.0;
    //pt_bound[5] = 20.0;
    
    
   
  }
  
  if(iSpec == 2) { 
    Nptbin = 3;
    
    //pt_bound[0] = -2.4; 
    //pt_bound[1] = -1.6; 
    //pt_bound[2] = -1.2; 
    //pt_bound[3] = -0.8; 
    //pt_bound[4] = 0.0; 
    //pt_bound[5] = 0.8;
    //pt_bound[6] = 1.2; 
    //pt_bound[7] = 1.6; 
    //pt_bound[8] = 2.4; 

    pt_bound[0] = -2.4; 
    pt_bound[1] = -1.2; 
    pt_bound[2] = 1.2; 
    pt_bound[3] = 2.4; 
    pt_bound[4] = 0.0; 
    pt_bound[5] = 0.8;
    pt_bound[6] = 1.2; 
    pt_bound[7] = 1.6; 
    pt_bound[8] = 2.4; 

    
    //pt_bound[0] = 0.0; 
    //pt_bound[1] = 1.2; 
    //pt_bound[2] = 2.4; 
    
   
    
  }
  
  
  if(iSpec == 3) {
    Nptbin = 9;
    //for plots
    pt_bound[0] = 0.0;//0
    pt_bound[1] = 2.0;//5
    pt_bound[2] = 4.0;//10
    pt_bound[3] = 8.0;//20
    pt_bound[4] = 12.0;//30
    pt_bound[5] = 16.0;//40
    pt_bound[6] = 20.0;//50
    pt_bound[7] = 40.0;//100
    pt_bound[8] = 0.0;//100
    pt_bound[9] = 40.0;//100
    
    

  }
  //X Axis error on Eff graph 
  double PT[100], DelPT[100], mom_err[100];
  for (Int_t ih = 0; ih < Nptbin; ih++) {
    PT[ih] = (pt_bound[ih] + pt_bound[ih+1])/2.0;
    DelPT[ih] = pt_bound[ih+1] - pt_bound[ih];
    mom_err[ih] = DelPT[ih]/2.0;



  }
  



  double genError, recError;
  double gen_pt[100]={0}, gen_ptError[100]={0}; 
  double rec_pt[100]={0}, rec_ptError[100]={0}; 
  double Eff_cat_1[100]={0},Err_Eff_cat_1[100]={0};  
  
  // Histogram arrays
  TH1D *diMuonsInvMass_GenA[10][1000];
  TH1D *diMuonsInvMass_RecA[10][1000];
  TH1D *diMuonsPt_GenA[10][1000];
  TH1D *diMuonsPt_RecA[10][1000];
  char nameGen[10][500], nameRec[10][500], nameGenPt[10][500], nameRecPt[10][500];
 
  
  for (int ifile = 0; ifile <= 5; ifile++) {
    for (Int_t ih = 0; ih < Nptbin; ih++) {
      sprintf(nameGen[ifile],"DiMuonMassGen_pt_%d_%d",ih,ifile);
      sprintf(nameRec[ifile],"DiMuonMassRec_pt_%d_%d",ih,ifile);
      
      sprintf(nameGenPt[ifile],"DiMuonPtGen_pt_%d_%d",ih,ifile);
      sprintf(nameRecPt[ifile],"DiMuonPtRec_pt_%d_%d",ih,ifile);
      
      diMuonsInvMass_GenA[ifile][ih]= new TH1D(nameGen[ifile],nameGen[ifile],  100,60.0,120.0); //for eff Gen;
      diMuonsInvMass_GenA[ifile][ih]->Sumw2();
      diMuonsInvMass_GenA[ifile][ih]->SetMarkerStyle(7);
      diMuonsInvMass_GenA[ifile][ih]->SetMarkerColor(4);
      diMuonsInvMass_GenA[ifile][ih]->SetLineColor(4);
      
      diMuonsInvMass_RecA[ifile][ih] = new TH1D(nameRec[ifile],nameRec[ifile], 100,60.0,120.0); //for eff Rec;
      diMuonsInvMass_RecA[ifile][ih]->Sumw2();
      diMuonsInvMass_RecA[ifile][ih]->SetMarkerStyle(21);
      diMuonsInvMass_RecA[ifile][ih]->SetMarkerColor(1);
      diMuonsInvMass_RecA[ifile][ih]->SetLineColor(1);
      
      
      diMuonsPt_GenA[ifile][ih]= new TH1D(nameGenPt[ifile],nameGenPt[ifile],  100,0,40); //for eff Gen;
      diMuonsPt_RecA[ifile][ih]= new TH1D(nameRecPt[ifile],nameRecPt[ifile],  100,0,40); //for eff Rec;
    }
  }
  
  //===========================================Input Root File============================================================
  char fileName[10][500];
  //Scales
  double scale[10]={0};  

  //Z0 weights here 
  scale[0]=0.0554474;    // pT [0-3]    
  scale[1]=0.0612928;    // pT [3-6]
  scale[2]=0.0238773;    // pT [6-9]  
  scale[3]=0.00887936;   // pT [9-12]
  scale[4]=0.00368926*2; // pT [12-15]
  scale[5]=0.00303737*2; // pT [15-30]


  //Z0 file here
  sprintf(fileName[0],"Z0_OniaTreeTest.root");
  sprintf(fileName[1],"Z0_OniaTreeTest.root");
  sprintf(fileName[2],"Z0_OniaTreeTest.root");
  sprintf(fileName[3],"Z0_OniaTreeTest.root");
  sprintf(fileName[4],"Z0_OniaTreeTest.root");
  sprintf(fileName[5],"Z0_OniaTreeTest.root");
  



  TFile *infile;
  TTree *tree;
  TTree *gentree;
  
  //===========File loop ======================
  
  for(int ifile =0; ifile<=5; ifile++){
    
    infile=new TFile(fileName[ifile],"R");
    tree=(TTree*)infile->Get("SingleMuonTree");
    gentree=(TTree*)infile->Get("SingleGenMuonTree");
    
    //Event variables
    int eventNb,runNb,lumiBlock, gbin, rbin;
    //Jpsi Variables
    Double_t JpsiMass,JpsiPt,JpsiRap, JpsiCharge;
    Double_t JpsiVprob;
    //2.) muon variables RECO                                                                       
    double muPosPx, muPosPy, muPosPz,  muPosEta, muPosPt,muPosP;
    double muNegPx, muNegPy, muNegPz,  muNegEta, muNegPt,muNegP;
    //(1).Positive Muon                                     
    double muPos_nchi2In, muPos_dxy, muPos_dz, muPos_nchi2Gl;
    int muPos_found, muPos_pixeLayers, muPos_nValidMuHits,muPos_arbitrated;
    bool muPos_matches,muPos_tracker,muPos_global;
 
    int muPos_Trigger1, muPos_Trigger2,muPos_Trigger3,muPos_Trigger4,muPos_Trigger5;
    int muPos_Trigger6,muPos_Trigger7,muPos_Trigger8,muPos_Trigger9,muPos_Trigger10; 


    //(2).Negative Muon                                     
    double muNeg_nchi2In, muNeg_dxy, muNeg_dz, muNeg_nchi2Gl;
    int muNeg_found, muNeg_pixeLayers, muNeg_nValidMuHits,muNeg_arbitrated;
    bool muNeg_matches,muNeg_tracker,muNeg_global;

    int muNeg_Trigger1, muNeg_Trigger2,muNeg_Trigger3,muNeg_Trigger4,muNeg_Trigger5;
    int muNeg_Trigger6,muNeg_Trigger7,muNeg_Trigger8,muNeg_Trigger9,muNeg_Trigger10;


    //Gen Level variables
    //Gen JPsi Variables
    double GenJpsiMass, GenJpsiPt, GenJpsiRap;
    double GenJpsiPx, GenJpsiPy, GenJpsiPz;
    
    //2.) Gen muon variables 
    double GenmuPosPx, GenmuPosPy, GenmuPosPz,  GenmuPosEta, GenmuPosPt,GenmuPosPhi;
    double GenmuNegPx, GenmuNegPy, GenmuNegPz,  GenmuNegEta, GenmuNegPt,GenmuNegPhi;

    //Event variables
    tree->SetBranchAddress("eventNb",&eventNb);
    tree->SetBranchAddress("runNb",&runNb);
    tree->SetBranchAddress("lumiBlock",&lumiBlock);
    
    //Jpsi Variables
    tree->SetBranchAddress("JpsiCharge",&JpsiCharge);
    tree->SetBranchAddress("JpsiMass",&JpsiMass);
    tree->SetBranchAddress("JpsiPt",&JpsiPt);
    tree->SetBranchAddress("JpsiRap",&JpsiRap);
    tree->SetBranchAddress("JpsiVprob",&JpsiVprob);
    tree->SetBranchAddress("rbin",&rbin);
    
    //muon variable
    tree->SetBranchAddress("muPosPx",&muPosPx);
    tree->SetBranchAddress("muPosPy",&muPosPy);
    tree->SetBranchAddress("muPosPz",&muPosPz);
    tree->SetBranchAddress("muPosEta",&muPosEta);
    tree->SetBranchAddress("muNegPx", &muNegPx);
    tree->SetBranchAddress("muNegPy",    &muNegPy);
    tree->SetBranchAddress("muNegPz",    &muNegPz);
    tree->SetBranchAddress("muNegEta",    &muNegEta);
    //1). Positive Muon
    tree->SetBranchAddress("muPos_nchi2In", &muPos_nchi2In);
    tree->SetBranchAddress("muPos_dxy", &muPos_dxy);
    tree->SetBranchAddress("muPos_dz", &muPos_dz);
    tree->SetBranchAddress("muPos_nchi2Gl", &muPos_nchi2Gl);
    tree->SetBranchAddress("muPos_found", &muPos_found);
    tree->SetBranchAddress("muPos_pixeLayers", &muPos_pixeLayers);
    tree->SetBranchAddress("muPos_nValidMuHits", &muPos_nValidMuHits);
    tree->SetBranchAddress("muPos_matches", &muPos_matches);
    tree->SetBranchAddress("muPos_tracker", &muPos_tracker);
    tree->SetBranchAddress("muPos_global",&muPos_global);
    tree->SetBranchAddress("muPos_arbitrated", &muPos_arbitrated);

    tree->SetBranchAddress("muPos_Trigger1",&muPos_Trigger1);
    tree->SetBranchAddress("muPos_Trigger2",&muPos_Trigger2);
    tree->SetBranchAddress("muPos_Trigger3",&muPos_Trigger3);
    tree->SetBranchAddress("muPos_Trigger4",&muPos_Trigger4);
    tree->SetBranchAddress("muPos_Trigger5",&muPos_Trigger5);
    tree->SetBranchAddress("muPos_Trigger6",&muPos_Trigger6);
    tree->SetBranchAddress("muPos_Trigger7",&muPos_Trigger7);
    tree->SetBranchAddress("muPos_Trigger8",&muPos_Trigger8);
    tree->SetBranchAddress("muPos_Trigger9",&muPos_Trigger9);
    tree->SetBranchAddress("muPos_Trigger10",&muPos_Trigger10);


    //2). Negative Muon                                                                            
    tree->SetBranchAddress("muNeg_nchi2In", &muNeg_nchi2In);
    tree->SetBranchAddress("muNeg_dxy", &muNeg_dxy);
    tree->SetBranchAddress("muNeg_dz", &muNeg_dz);
    tree->SetBranchAddress("muNeg_nchi2Gl", &muNeg_nchi2Gl);
    tree->SetBranchAddress("muNeg_found", &muNeg_found);
    tree->SetBranchAddress("muNeg_pixeLayers", &muNeg_pixeLayers);
    tree->SetBranchAddress("muNeg_nValidMuHits", &muNeg_nValidMuHits);
    tree->SetBranchAddress("muNeg_matches", &muNeg_matches);
    tree->SetBranchAddress("muNeg_tracker", &muNeg_tracker);
    tree->SetBranchAddress("muNeg_global",&muNeg_global);
    tree->SetBranchAddress("muNeg_arbitrated", &muNeg_arbitrated);

    tree->SetBranchAddress("muNeg_Trigger1",&muNeg_Trigger1);
    tree->SetBranchAddress("muNeg_Trigger2",&muNeg_Trigger2);
    tree->SetBranchAddress("muNeg_Trigger3",&muNeg_Trigger3);
    tree->SetBranchAddress("muNeg_Trigger4",&muNeg_Trigger4);
    tree->SetBranchAddress("muNeg_Trigger5",&muNeg_Trigger5);
    tree->SetBranchAddress("muNeg_Trigger6",&muNeg_Trigger6);
    tree->SetBranchAddress("muNeg_Trigger7",&muNeg_Trigger7);
    tree->SetBranchAddress("muNeg_Trigger8",&muNeg_Trigger8);
    tree->SetBranchAddress("muNeg_Trigger9",&muNeg_Trigger9);
    tree->SetBranchAddress("muNeg_Trigger10",&muNeg_Trigger10);

    //HLT_HIL1DoubleMuOpen_v1 HLT_HIL1DoubleMu0_HighQ_v1 HLT_HIL2Mu3_v1 HLT_HIL2Mu3_NHitQ_v1 HLT_HIL2Mu7_v1
    //HLT_HIL2Mu15_v1 HLT_HIL2DoubleMu0_v1 HLT_HIL2DoubleMu0_NHitQ_v1 HLT_HIL2DoubleMu0_L1HighQL2NHitQ_v1 HLT_HIL2DoubleMu3_v1
    
    //====================================Gen Variables=========================================================
    //Gen Jpsi Variables
    gentree->SetBranchAddress("GenJpsiMass",   &GenJpsiMass);
    gentree->SetBranchAddress("GenJpsiPt",     &GenJpsiPt);
    gentree->SetBranchAddress("GenJpsiRap",    &GenJpsiRap);
    gentree->SetBranchAddress("GenJpsiPx",     &GenJpsiPx);
    gentree->SetBranchAddress("GenJpsiPy",     &GenJpsiPy);
    gentree->SetBranchAddress("GenJpsiPz",     &GenJpsiPz);
    gentree->SetBranchAddress("gbin",&gbin);
    //muon variable
    gentree->SetBranchAddress("GenmuPosPx",    &GenmuPosPx);
    gentree->SetBranchAddress("GenmuPosPy",    &GenmuPosPy);
    gentree->SetBranchAddress("GenmuPosPz",    &GenmuPosPz);
    gentree->SetBranchAddress("GenmuPosEta",    &GenmuPosEta);
   
    gentree->SetBranchAddress("GenmuNegPx",    &GenmuNegPx);
    gentree->SetBranchAddress("GenmuNegPy",    &GenmuNegPy);
    gentree->SetBranchAddress("GenmuNegPz",    &GenmuNegPz);
    gentree->SetBranchAddress("GenmuNegEta",    &GenmuNegEta);
    

    //====================================================== Gen tree loop ================================================
    int NAccep=0;
    int nGenEntries=gentree->GetEntries();
    cout<<" Total Entries in GenLevel Tree for pT range: "<<fileName[ifile]<<"  "<<   nGenEntries<< " ========="<<endl;
    //dataFile<<" Total Entries in GenLevel Tree for pT range: "<<fileName[ifile]<<"  "<<   nGenEntries<< " ====="<<endl;
    
    
    for(int i=0; i< nGenEntries; i++)  {	    
      gentree->GetEntry(i);
      
      if(i%10000==0){
	cout<<" processing record "<<i<<endl;
	cout<<" Mass "<< GenJpsiMass<< " pT "<< GenJpsiPt << " Y " <<GenJpsiRap<<endl; 
      }
      
      bool GenPosIn=0, GenNegIn=0,GenPosPass=0,GenNegPass=0;
      
      GenmuPosPt= TMath::Sqrt(GenmuPosPx*GenmuPosPx + GenmuPosPy*GenmuPosPy); 
      GenmuNegPt= TMath::Sqrt(GenmuNegPx*GenmuNegPx + GenmuNegPy*GenmuNegPy); 
      GenmuPosPhi=TMath::ACos(GenmuPosPx/GenmuPosPt); 
      GenmuNegPhi=TMath::ACos(GenmuNegPx/GenmuNegPt); 
      
      diMuonsInvMass_Gen->Fill(GenJpsiMass);
      Cent_Gen->Fill(gbin);
 
      if(IsAccept(GenmuPosPt, GenmuPosEta)) {GenPosIn=1;}
      if(IsAccept(GenmuNegPt, GenmuNegEta)) {GenNegIn=1;}
      
     
      if(GenPosIn && GenNegIn ) NAccep++;
      
      if(GenPosIn==1 && GenmuPosPt> PtCut) {GenPosPass=1;}
      if(GenNegIn==1 && GenmuNegPt> PtCut) {GenNegPass=1;}

      
      

      double GenCenWeight=0,GenWeight=0;
      GenCenWeight=FindCenWeight(gbin);
      Bin_Gen->Fill(gbin);
      GenWeight=GenCenWeight*scale[ifile];
      if(PutWeight==0){GenWeight=1;}
      
      if(GenPosIn && GenNegIn){
	MuonPt_Gen->Fill(GenmuPosPt);
	MuonPt_Gen->Fill(GenmuNegPt);
	MuonEta_Gen->Fill(GenmuPosEta);
	MuonEta_Gen->Fill(GenmuNegEta);
      	MuonPhi_Gen->Fill(GenmuPosPhi);
	MuonPhi_Gen->Fill(GenmuNegPhi);
	diMuonsRap_Gen->Fill(GenJpsiRap);
	diMuonsPt_Gen->Fill(GenJpsiPt,GenWeight);
      }





      // diMuonsPt_Gen->Fill(GenJpsiPt,GenWeight);
      
      if(GenPosIn && GenNegIn){
	if(ifile==0){diMuonsRap_Gen0->Fill(GenJpsiRap);}
	if(ifile==1){diMuonsRap_Gen1->Fill(GenJpsiRap);}
	if(ifile==2){diMuonsRap_Gen2->Fill(GenJpsiRap);}
	if(ifile==3){diMuonsRap_Gen3->Fill(GenJpsiRap);}
	if(ifile==4){diMuonsRap_Gen4->Fill(GenJpsiRap);}
	if(ifile==5){diMuonsRap_Gen5->Fill(GenJpsiRap);}
      

      }
      
      
      for (Int_t ih = 0; ih < Nptbin; ih++) {
	
	//adding pT of all pt bins to see diss is cont
	if(iSpec == 1)  if( (GenPosPass==1 && GenNegPass==1) && (TMath::Abs(GenJpsiRap)<2.4 ) && (GenJpsiPt>pt_bound[ih] && GenJpsiPt<=pt_bound[ih+1])){diMuonsPt_GenA[ifile][ih]->Fill(GenJpsiPt,GenWeight);}
		
	if(iSpec == 1)  if( (GenPosPass==1 && GenNegPass==1) && (TMath::Abs(GenJpsiRap)<2.4 )&&(GenJpsiPt>pt_bound[ih] && GenJpsiPt<=pt_bound[ih+1])){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenWeight);}
	//if(iSpec == 2)  if((GenPosPass==1 && GenNegPass==1) &&  (GenJpsiPt<20.0) && (TMath::Abs(GenJpsiRap) > pt_bound[ih] && TMath::Abs(GenJpsiRap) <=pt_bound[ih+1] )){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenWeight);}
	

	//for non symetric plots
	if(iSpec == 2)  if( (GenPosPass==1 && GenNegPass==1 ) &&  (GenJpsiPt < 6.0) && ((GenJpsiRap) > pt_bound[ih] && (GenJpsiRap) <=pt_bound[ih+1] )){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenWeight);}

	if(iSpec == 3)  if( (GenPosPass==1 && GenNegPass==1)  &&  (TMath::Abs(GenJpsiRap)<2.4 ) && (gbin>=pt_bound[ih] && gbin < pt_bound[ih+1])){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenWeight);}
	
      }
      
    }//gen loop end
    
    cout<<" accepted no "<< NAccep<<endl;
    //dataFile<<" accepted no "<< NAccep<<endl;
    
    //   new TCanvas;
    //diMuonsInvMass_Gen->Draw();
    //gPad->Print("plots/diMuonsInvMass_Gen.png");
    
     new TCanvas;
    diMuonsPt_Gen->Draw();
    gPad->Print("plots/diMuonsPt_Gen.png");
    
    //new TCanvas;
    //diMuonsRap_Gen0->Draw();
    //sprintf(PlotName,"plots/diMuonsRap_Gen_%d.pdf",ifile);   
    //gPad->Print(PlotName);
    
    //new TCanvas;
    //Bin_Gen->Draw();
    //gPad->Print("plots/Bin_Gen.png");
    
    
   



    
    //=============== Rec Tree Loop ==============================================================================
    
    int nRecEntries=tree->GetEntries();
    cout<<"Total Entries in reconstructed Tree for pT range "<<fileName[ifile]<<"  "<<nRecEntries<< "====="<<endl;
    //dataFile<<"Total Entries in reconstructed Tree for pT range "<<fileName[ifile]<<"  "<<nRecEntries<<endl;
    
    for(int i=0; i<nRecEntries; i++)  {	    
      tree->GetEntry(i);
      if(i%10000==0){
	cout<<" processing record "<<i<<endl;
	cout<<" processing Run  " <<runNb <<" event "<<eventNb<<" lum block "<<lumiBlock<<endl;    
	cout<<" Mass "<< JpsiMass<< " pT "<< JpsiPt << " Y " <<JpsiRap<<"  "<<JpsiVprob<<" charge "<<JpsiCharge<<endl; 
      }
      
      bool PosPass=0, NegPass=0, AllCut=0 ,PosIn=0, NegIn=0;
           
      muPosPt= TMath::Sqrt(muPosPx*muPosPx + muPosPy*muPosPy); 
      muPosP = TMath::Sqrt(muPosPx*muPosPx + muPosPy*muPosPy+ muPosPz*muPosPz); 
      muNegPt= TMath::Sqrt(muNegPx*muNegPx + muNegPy*muNegPy); 
      muNegP = TMath::Sqrt(muNegPx*muNegPx + muNegPy*muNegPy +muNegPz*muNegPz); 
    
      if(IsAccept(muPosPt, muPosEta)){PosIn=1;}
      if(IsAccept(muNegPt, muNegEta)){NegIn=1;}

     

      Cent_Rec->Fill(rbin);

  
      //bool mu_Global = ((muPos_nchi2Gl >=0) && (muNeg_nchi2Gl >=0));
      // bool mu_Tracker = ((muPos_tracker==1) && (muNeg_tracker==1));

    
      if( muPos_found > 10 && muPos_pixeLayers > 0 && TMath::Abs(muPos_nchi2In) < 4.0 && TMath::Abs(muPos_dxy) < 3 && TMath::Abs(muPos_dz) < 15 
	  && TMath::Abs(muPos_nchi2Gl) < 20 &&  muPos_arbitrated==1 && muPos_tracker==1 && muPos_global==1){PosPass=1;}	  
	 
      if( muNeg_found >10 && muNeg_pixeLayers >0 && TMath::Abs(muNeg_nchi2In) <4.0 && TMath::Abs(muNeg_dxy) < 3 && TMath::Abs(muNeg_dz) < 15 
	  && TMath::Abs(muNeg_nchi2Gl) < 20 && muNeg_arbitrated==1 &&  muNeg_tracker==1 && muNeg_global==1 ){NegPass=1;}

      

	     // cout<<muPos_matches<<"  "<<muNeg_matches<<endl;

      //if( (muPosPt > PtCut && muNegPt > PtCut) && (muPos_Trigger2==1 && muNeg_Trigger2==1) && (PosIn==1 && NegIn==1) && (PosPass==1 && NegPass==1)){AllCut=1;}
	 
	 //without muon ID cuts
	  if((muPosPt > PtCut && muNegPt > PtCut) && (muPos_matches==1 && muNeg_matches==1) && (PosIn==1 && NegIn==1)){AllCut=1;}
	 
	 //without trigger
	 //if((muPosPt > PtCut && muNegPt > PtCut) &&  (PosIn==1 && NegIn==1 )  &&   (PosPass==1 && NegPass==1)){AllCut=1;}
	
      //AllCut=1;
 	 
	 double RecCenWeight=0,RecWeight=0;
	 RecCenWeight=FindCenWeight(rbin);
	 RecWeight=RecCenWeight*scale[ifile];
	 if(PutWeight==0){RecWeight=1;}
	 
	 if(i%100000==0){
	   cout<<" eff loop for reco "<<endl;
	 }
      
	 if(AllCut==1){
	   if(ifile==0){diMuonsRap_Rec0->Fill(JpsiRap);}
	   if(ifile==1){diMuonsRap_Rec1->Fill(JpsiRap);}
	   if(ifile==2){diMuonsRap_Rec2->Fill(JpsiRap);}
	   if(ifile==3){diMuonsRap_Rec3->Fill(JpsiRap);}
	   if(ifile==4){diMuonsRap_Rec4->Fill(JpsiRap);}
	   if(ifile==5){diMuonsRap_Rec5->Fill(JpsiRap);}
	 }

	 //Eff loop for reco
	 
	 if((JpsiCharge == 0) && (JpsiVprob > 0.05)) {
	   for (Int_t ih = 0; ih < Nptbin; ih++) {
	     //to see cont reco pT
	     if(iSpec == 1)if((AllCut==1) && (TMath::Abs(JpsiRap) < 2.4) && (JpsiPt>pt_bound[ih] && JpsiPt<=pt_bound[ih+1])) {diMuonsPt_RecA[ifile][ih]->Fill(JpsiPt,RecWeight);}
	     
	     if(iSpec == 1)if((AllCut==1) && (TMath::Abs(JpsiRap)<2.4 ) && (JpsiPt > pt_bound[ih] && JpsiPt <=pt_bound[ih+1])){diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass, RecWeight);}
	     //if(iSpec == 2) if( (AllCut==1) &&  (JpsiPt<20.0) && (TMath::Abs(JpsiRap) > pt_bound[ih] && TMath::Abs(JpsiRap) <=pt_bound[ih+1])){diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecWeight);}	     
	     //for non symetric plots
	     if(iSpec == 2) if( (AllCut==1) &&  (JpsiPt<20.0) && ((JpsiRap) > pt_bound[ih] && (JpsiRap) <=pt_bound[ih+1])){diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecWeight);}
	     if(iSpec == 3) if((AllCut==1)&& (TMath::Abs(JpsiRap) < 2.4) && (rbin>=pt_bound[ih] &&  rbin < pt_bound[ih+1])){diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecWeight);}
	   }
	 }
    }
  
    /*
      new TCanvas;
      if(ifile==0){diMuonsRap_Gen0->Draw();new TCanvas; diMuonsRap_Rec0->Draw(); gPad->Print("plots/NPdiMuonsRap_Gen0.png");}
      if(ifile==1){diMuonsRap_Gen1->Draw();new TCanvas; diMuonsRap_Rec1->Draw(); gPad->Print("plots/NPdiMuonsRap_Gen1.png");}
      if(ifile==2){diMuonsRap_Gen2->Draw();new TCanvas; diMuonsRap_Rec2->Draw(); gPad->Print("plots/NPdiMuonsRap_Gen2.png");}
      if(ifile==3){diMuonsRap_Gen3->Draw();new TCanvas; diMuonsRap_Rec3->Draw(); gPad->Print("plots/NPdiMuonsRap_Gen3.png");}
      if(ifile==4){diMuonsRap_Gen4->Draw();new TCanvas; diMuonsRap_Rec4->Draw(); gPad->Print("plots/NPdiMuonsRap_Gen4.png");}
      if(ifile==5){diMuonsRap_Gen5->Draw();new TCanvas; diMuonsRap_Rec5->Draw(); gPad->Print("plots/NPdiMuonsRap_Gen5.png");}
    */
    }  // file loop ends 

  ///////////////////////////////////////////////////////////////////
  
  cout<< " adding "<<endl;
  TH1D *diMuonsInvMass_RecA1[100];
  TH1D *diMuonsInvMass_GenA1[100];
  TH1D *diMuonsPt_GenA1[100];
  TH1D *diMuonsPt_RecA1[100];
  TF1 *backfun_1;
  char namePt_1B[500];//for bkg func
 
  for(Int_t ih = 0; ih < Nptbin; ih++){
    diMuonsInvMass_RecA1[ih] = diMuonsInvMass_RecA[0][ih];
    diMuonsInvMass_GenA1[ih] = diMuonsInvMass_GenA[0][ih];
    diMuonsPt_GenA1[ih] = diMuonsPt_GenA[0][ih];
    diMuonsPt_RecA1[ih] = diMuonsPt_RecA[0][ih];
    
    for (int ifile = 1; ifile <= 5; ifile++) {
      diMuonsInvMass_RecA1[ih]->Add(diMuonsInvMass_RecA[ifile][ih]);
      diMuonsInvMass_GenA1[ih]->Add(diMuonsInvMass_GenA[ifile][ih]);     
      
      diMuonsPt_GenA1[ih]->Add(diMuonsPt_GenA[ifile][ih]); 
      diMuonsPt_RecA1[ih]->Add(diMuonsPt_RecA[ifile][ih]); 
    }
  }
  
  //===========================Fitting===================================================================//
  // Fit ranges
  double mass_low, mass_high;
  double MassZ0, WeidthZ0;
  
  // Low mass range upsilon width 54 KeV
  MassZ0 = 91.0; WeidthZ0 = 1.0;
  mass_low = 60.0; mass_high = 120.0;  // Fit ranges
  
  // Fit Function crystall ball
  TF1 *GAUSPOL = new TF1("GAUSPOL",CrystalBall,60.0,120.0,6);

  GAUSPOL->SetParNames("Yield (#varZ0)","BinWidth","Mean","Sigma","#alpha","n");

  GAUSPOL->FixParameter(2, MassZ0);
  GAUSPOL->SetParameter(3, WeidthZ0);
  GAUSPOL->SetParLimits(3, 0.1*WeidthZ0,3.0*WeidthZ0);
  GAUSPOL->SetParameter(4, 1.0);
  GAUSPOL->SetParameter(5, 2.0);
  

  GAUSPOL->SetLineWidth(2.0);
  GAUSPOL->SetLineColor(2);
  

  //=====================Loop for eff===========================================================
  double GenNo[100]={0};
  double Eff[100]={0};
  double GenError[100]={0};
  double RecError[100]={0};
  double errEff_cat_S1[100]={0};
  double errEff_cat_S2[100]={0};
  double errEff_cat_S1_1[100]={0},errEff_cat_S1_2[100]={0};
  double errEff_cat_S2_1[100]={0},errEff_cat_S2_2[100]={0};
  char PlotName[500],PlotName1[500], PlotName2[500]; 
  char GPlotName[500],GPlotName1[500], GPlotName2[500];

  for (Int_t ih = 0; ih < Nptbin; ih++) {
   
    cout<<" no of gen dimuons from diMuons Pt histo    "<<diMuonsPt_GenA1[ih]->Integral(1,100)<<endl;
    cout<<" no of gen dimuons from diMuons Mass histo  "<<diMuonsInvMass_GenA1[ih]->Integral(1,100)<<endl;
    

    //from pT histogram
    //gen_pt[ih] =diMuonsPt_GenA1[ih]->IntegralAndError(1,100,genError);
   
    gen_pt[ih] = diMuonsInvMass_GenA1[ih]->IntegralAndError(1,100,genError);
    gen_ptError[ih]= genError;
    
    if(iSpec==1) sprintf(PlotName,"plots/DiMuonMass_PtBin_%d.png",ih);
    if(iSpec==2) sprintf(PlotName,"plots/DiMuonMass_RapBin_%d.png",ih);
    if(iSpec==3) sprintf(PlotName,"plots/DiMuonMass_CentBin_%d.png",ih);
    
    if(iSpec==1) sprintf(PlotName1,"plots/DiMuonMass_PtBin_%d.pdf",ih);
    if(iSpec==2) sprintf(PlotName1,"plots/DiMuonMass_RapBin_%d.pdf",ih);
    if(iSpec==3) sprintf(PlotName1,"plots/DiMuonMass_CentBin_%d.pdf",ih);
    
    if(iSpec==1) sprintf(PlotName2,"plots/DiMuonMass_PtBin_%d.eps",ih);
    if(iSpec==2) sprintf(PlotName2,"plots/DiMuonMass_RapBin_%d.eps",ih);
    if(iSpec==3) sprintf(PlotName2,"plots/DiMuonMass_CentBin_%d.eps",ih);
 
    //giving inetial value for crystall ball fourth parameter 
    GAUSPOL->SetParameter(0, diMuonsInvMass_RecA1[ih]->Integral(0,50));
    GAUSPOL->FixParameter(1, diMuonsInvMass_RecA1[ih]->GetBinWidth(1));
    
    new TCanvas; 
    diMuonsInvMass_RecA1[ih]->Fit("GAUSPOL","LLMERQ", "", 60.0,120.0);
    
    double Z0Mass = GAUSPOL->GetParameter(2);
    double Z0Width = GAUSPOL->GetParameter(3);
   
    double Z0Yield = GAUSPOL->GetParameter(0);
    double Z0YieldError = GAUSPOL->GetParError(0);

    double par[20];
    GAUSPOL->GetParameters(par);
    sprintf(namePt_1B,"pt_1B_%d",ih);
    backfun_1 = new TF1(namePt_1B, Pol2, mass_low, mass_high, 3);
    backfun_1->SetParameters(&par[4]);
   

    double MassLow=(Z0Mass-3*Z0Width);
    double MassHigh=(Z0Mass+3*Z0Width);
    
    // double MassLow=60.0;
    //double MassHigh=120.0;


    int binlow =diMuonsInvMass_RecA1[ih]->GetXaxis()->FindBin(MassLow);
    int binhi =diMuonsInvMass_RecA1[ih]->GetXaxis()->FindBin(MassHigh);
    double binwidth=diMuonsInvMass_RecA1[ih]->GetBinWidth(1);
      

  
    //yield by function 
    //rec_pt[ih] = Z0Yield;
    //rec_ptError[ih]=Z0YieldError;

    //cout<<"Rec diMuons from Pt histo "<<diMuonsPt_RecA1[ih]->Integral(1,100)<<endl;  
    //cout<<"Rec dimuons from mass "<<diMuonsInvMass_RecA1[ih]->Integral(1,100)<<endl; 
    

      
    //from pT histo
    //rec_pt[ih]=diMuonsPt_RecA1[ih]->IntegralAndError(1, 100,recError);

    //yield by histogram integral
    rec_pt[ih] = diMuonsInvMass_RecA1[ih]->IntegralAndError(binlow, binhi,recError);
    rec_ptError[ih]= recError;
  
    //Cal eff 
    Eff_cat_1[ih] = rec_pt[ih]/gen_pt[ih]; 
  
    //calculate error on eff
    GenNo[ih]=gen_pt[ih];
    Eff[ih]= Eff_cat_1[ih];
    GenError[ih]=gen_ptError[ih];
    RecError[ih]=rec_ptError[ih];
    //error    
    errEff_cat_S1_1[ih]= ( (Eff[ih] * Eff[ih]) /(GenNo[ih] * GenNo[ih]) );
    errEff_cat_S1_2[ih]= (RecError[ih] * RecError[ih]);
    errEff_cat_S1[ih]= (errEff_cat_S1_1[ih] * errEff_cat_S1_2[ih]);
   

    errEff_cat_S2_1[ih]= ( (1 - Eff[ih])* (1 - Eff[ih]) ) / ( GenNo[ih] * GenNo[ih]);
    errEff_cat_S2_2[ih]= (GenError[ih] * GenError[ih] ) - ( RecError[ih] * RecError[ih] );


    errEff_cat_S2[ih]=errEff_cat_S2_1[ih]*errEff_cat_S2_2[ih];
    Err_Eff_cat_1[ih]=sqrt(errEff_cat_S1[ih] + errEff_cat_S2[ih]);
   
    //error for no weights
    //Err_Eff_cat_1[ih]= Eff_cat_1[ih]*TMath::Sqrt(gen_ptError[ih]*gen_ptError[ih]/(gen_pt[ih]*gen_pt[ih]) + rec_ptError[ih]*rec_ptError[ih]/(rec_pt[ih]* rec_pt[ih]));

    cout<<"Z0 Yield by integral of histo:  "<< diMuonsInvMass_RecA1[ih]->IntegralAndError(binlow, binhi,recError) <<"  error "<< rec_ptError[ih]<<endl; 
    cout<<"Z0Yield by CB    yield det:     "<< Z0Yield << " Z0Width "<< Z0Width<<" Z0Mass "<<Z0Mass <<endl;
    cout<<"Z0 Yield by Function integral:  "<< GAUSPOL->Integral(MassLow,MassHigh)/binwidth <<endl;
    cout<<" rec_pt[ih]  "<<  rec_pt[ih] <<" gen_pt[ih] "<<gen_pt[ih]<<endl;
    cout<<" eff "<< Eff_cat_1[ih]<<" error "<<Err_Eff_cat_1[ih]<<endl;
    char Spectra[100];
    if(iSpec==1) sprintf(Spectra,"Pt");
    if(iSpec==2) sprintf(Spectra,"Rap");
    if(iSpec==3) sprintf(Spectra,"Cent");

    dataFile<<"Z0 eff "<< Eff_cat_1[ih]<<" error "<<Err_Eff_cat_1[ih]<<"  "<<Spectra<<"["<<pt_bound[ih]<<" - "<<pt_bound[ih+1]<<"]"<<endl;
    
    if(iSpec==1) sprintf(GPlotName,"plots/GenDiMuonMass_PtBin_%d.png",ih);
    if(iSpec==2) sprintf(GPlotName,"plots/GenDiMuonMass_RapBin_%d.png",ih);
    if(iSpec==3) sprintf(GPlotName,"plots/GenDiMuonMass_CentBin_%d.png",ih);
    
    if(iSpec==1) sprintf(GPlotName1,"plots/GenDiMuonMass_PtBin_%d.pdf",ih);
    if(iSpec==2) sprintf(GPlotName1,"plots/GenDiMuonMass_RapBin_%d.pdf",ih);
    if(iSpec==3) sprintf(GPlotName1,"plots/GenDiMuonMass_CentBin_%d.pdf",ih);
    
    if(iSpec==1) sprintf(GPlotName2,"plots/GenDiMuonMass_PtBin_%d.eps",ih);
    if(iSpec==2) sprintf(GPlotName2,"plots/GenDiMuonMass_RapBin_%d.eps",ih);
    if(iSpec==3) sprintf(GPlotName2,"plots/GenDiMuonMass_CentBin_%d.eps",ih);
       
    backfun_1->SetLineColor(4);
    backfun_1->SetLineWidth(1);
    //backfun_1->Draw("same");
    gPad->Print(PlotName);
    gPad->Print(PlotName1);
    gPad->Print(PlotName2);

    //new TCanvas;
    //diMuonsInvMass_GenA1[ih]->Draw();
    //gPad->Print(GPlotName);
    //gPad->Print(GPlotName1);
    //gPad->Print(GPlotName2);


    // new TCanvas;
    //diMuonsPt_GenA1[ih]->Draw();
    //new TCanvas;
    //diMuonsPt_RecA1[ih]->Draw();
 
}
  dataFile.close();

  TFile *outfile;
  if(iSpec==1)outfile =new TFile("EffZ0_Pt.root","Recreate");
  if(iSpec==2)outfile =new TFile("EffZ0_Rap.root","Recreate");
  if(iSpec==3)outfile =new TFile("EffZ0_Cent.root","Recreate");
  
  TGraphErrors *Eff_Z0 = new TGraphErrors(Nptbin, PT, Eff_cat_1, mom_err,Err_Eff_cat_1);
  Eff_Z0->SetMarkerStyle(21);
  Eff_Z0->SetMarkerColor(2);
  Eff_Z0->GetYaxis()->SetTitle("Reco Eff");
 
  if(iSpec==1) Eff_Z0->GetXaxis()->SetTitle("Z0 pT (GeV/c^{2})");
  if(iSpec==2) Eff_Z0->GetXaxis()->SetTitle("Z0 rapidity");
  if(iSpec==3) Eff_Z0->GetXaxis()->SetTitle("bin");
   Eff_Z0->GetYaxis()->SetRangeUser(0,1.0);

  TLegend *legend_GP = new TLegend( 0.50,0.79,0.80,0.89);
  legend_GP->SetBorderSize(0);
  legend_GP->SetFillStyle(0);
  legend_GP->SetFillColor(0);
  legend_GP->SetTextSize(0.032);
  legend_GP->AddEntry(Eff_Z0,"PythiaEvtGen + HydjetBass", "P");
  
  new TCanvas;
  Eff_Z0->Draw("AP");
  legend_GP->Draw("Same");
    
 Eff_Z0->Write();

  if(iSpec==1){ gPad->Print("plots/Eff_Z0_Pt.pdf");gPad->Print("plots/Eff_Z0_Pt.png");gPad->Print("plots/Eff_Z0_Pt.eps");}
  if(iSpec==2){ gPad->Print("plots/Eff_Z0_Rap.pdf");gPad->Print("plots/Eff_Z0_Rap.png");  gPad->Print("plots/Eff_Z0_Rap.eps");}
  if(iSpec==3){ gPad->Print("plots/Eff_Z0_Cent.pdf");gPad->Print("plots/Eff_Z0_Cent.png"); gPad->Print("plots/Eff_Z0_Cent.eps"); }
 
  diMuonsPt_Gen->Rebin(2);
  new TCanvas;
  diMuonsPt_Gen->Draw();
  
  new TCanvas;
  diMuonsRap_Gen->Draw();

  
  new TCanvas;
  MuonPt_Gen->Draw();
  new TCanvas;
  MuonEta_Gen->Draw();
  new TCanvas;
  MuonPhi_Gen->Draw();
   
  new TCanvas;
  Cent_Rec->Draw();

  new TCanvas;
  Cent_Gen->Draw();

  diMuonsPt_Gen->Write();
  diMuonsRap_Gen->Write();
  MuonPt_Gen->Write();
  MuonEta_Gen->Write();
  MuonPhi_Gen->Write();
  Cent_Rec->Write();
  Cent_Gen->Write();

  outfile->Write();
  outfile->Close();



}


bool IsAccept(Double_t pt, Double_t eta)
{
  //return (fabs(eta) < 2.4);


  return (fabs(eta) < 2.4 &&
  	  (    ( fabs(eta) < 1.0 && pt >= 3.4 ) ||
  	       (  1.0 <= fabs(eta) && fabs(eta) < 1.5 && pt >= 5.8-2.4*fabs(eta) ) ||
  	       (  1.5 <= fabs(eta) && pt >= 3.3667 - 7.0/9.0*fabs(eta)) ));
}



double FindCenWeight(int Bin)
{

double NCollArray[40]={1747.8600, 1567.5300, 1388.3900, 1231.7700, 1098.2000, 980.4390, 861.6090, 766.0420, 676.5150, 593.4730,
                       521.9120, 456.5420, 398.5460, 346.6470, 299.3050, 258.3440, 221.2160, 188.6770, 158.9860, 134.7000,
                       112.5470, 93.4537, 77.9314, 63.5031, 52.0469, 42.3542, 33.9204, 27.3163, 21.8028, 17.2037,
                       13.5881, 10.6538, 8.3555, 6.4089, 5.1334, 3.7322, 3.0663, 2.4193, 2.1190, 1.7695};
return(NCollArray[Bin]);
}




// scale[0]=(0.0380228/0.001105276);
//  scale[1]=(0.0480769/0.001105276);
//  scale[2]=(0.0293255/0.001105276);
//  scale[3]=(0.0125156/0.001105276);
//  scale[4]=(0.00336587/0.001105276);
//  scale[5]=(0.001105276/0.001105276);
// mu_innerTrack_Hits > 10
//mu_pixelLayers > 0
//mu_innerTrack_chi2NDOF < 4.0
//mu_dxy < 3.0 cm
// mu_dz < 15. cm
//mu_globalTrack_chi2NDOF < 6
//mu_validMuHits > 6
//vProb > 0.01
