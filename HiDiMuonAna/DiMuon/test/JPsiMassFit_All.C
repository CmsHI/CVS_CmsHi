//===================== Macro to calculate JPsi Eff or Acc x Eff ============================================
//read tree from DiMuonOnia2DPlots.cc
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
//iSpec =1 pT, =2 Rap, =3 Cent PutWeight = 1 means put weight
// Prompt =1 prompt JPsi prompt =2 non prompt Jpsi
bool IsAccept(Double_t pt, Double_t eta); //you can define acceptance here 
double FindCenWeight(int Bin);//gives you weight according to cent
void JPsiMassFit_All(int Prompt =3, int iSpec = 1, int PutWeight = 0)   
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
  //==================================== Define Histograms====================================================
  char OutTextFile[100]; 
  if(iSpec==1) sprintf(OutTextFile,"EffJPsi_Pt.tex");
  if(iSpec==2) sprintf(OutTextFile,"EffJPsi_Rap.tex");
  if(iSpec==3) sprintf(OutTextFile,"EffJPsi_Cent.tex");
  ofstream dataFile(Form(OutTextFile));
  
  TH1D *diMuonsInvMass_Gen = new TH1D("diMuonsInvMass_Gen","diMuonsInvMass_Gen", 100,2.6,3.5);
 
  TH1D *diMuonsPt_Gen0 = new TH1D("diMuonsPt_Gen0","diMuonsPt_Gen0", 100,0,30);
  

  TH1D *diMuonsRap_Gen0 = new TH1D("diMuonsRap_Gen0","diMuonsRap_Gen0", 100,-5,5);
  TH1D *diMuonsRap_Gen1 = new TH1D("diMuonsRap_Gen1","diMuonsRap_Gen1", 100,-5,5);
  TH1D *diMuonsRap_Gen2 = new TH1D("diMuonsRap_Gen2","diMuonsRap_Gen2", 100,-5,5);
  TH1D *diMuonsRap_Gen3 = new TH1D("diMuonsRap_Gen3","diMuonsRap_Gen3", 100,-5,5);
  TH1D *diMuonsRap_Gen4 = new TH1D("diMuonsRap_Gen4","diMuonsRap_Gen4", 100,-5,5);
  TH1D *diMuonsRap_Gen5 = new TH1D("diMuonsRap_Gen5","diMuonsRap_Gen5", 100,-5,5);
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
  //==============================================Define Acc Eff Stuff here===========================================
  // Pt bin sizes
  // 0-1.5, 1.5-3, 3-4.5, 4.5-6, 6-7.5...

  int Nptbin;
  double pt_bound[100] = {0};
  if(iSpec == 1) { 
    
    Nptbin = 1;
    
    pt_bound[0] = 0.0;
    pt_bound[1] = 20.0;
    pt_bound[2] = 6.0;
    pt_bound[3] = 9.0;
    pt_bound[4] = 12.0;
    pt_bound[5] = 15.0;
    pt_bound[6] = 30.0;
   

 
    //JPSi Plots
    //pt_bound[0] = 0.0;
    //pt_bound[1] = 4.0;
    //pt_bound[2] = 7.0;
    //pt_bound[3] = 11.0;
    //pt_bound[4] = 14.0;
    //pt_bound[5] = 18.0;
    //pt_bound[6] = 25.0;
    //pt_bound[7] = 30.0;
  }
  
  if(iSpec == 2) { 
    Nptbin = 5;
    pt_bound[0] = -2.4; 
    pt_bound[1] = -1.6; 
    pt_bound[2] = -1.2; 
    pt_bound[3] = 1.2; 
    pt_bound[4] = 1.6; 
    pt_bound[5] = 2.4;
   
    //JPsi plots
    //pt_bound[0] = -2.4; 
    //pt_bound[1] = -1.8; 
    //pt_bound[2] = -1.2; 
    //pt_bound[3] = -0.8; 
    //pt_bound[4] = 0.0; 
    //pt_bound[5] = 0.8;
    //pt_bound[6] = 1.2; 
    //pt_bound[7] = 1.8; 
    //pt_bound[8] = 2.4; 
  }
  if(iSpec == 3) {
    Nptbin = 6;
    pt_bound[0] = 0.0;  //0
    pt_bound[1] = 4.0;  //10
    pt_bound[2] = 8.0;  //20
    pt_bound[3] = 12.0; //30
    pt_bound[4] = 16.0; //40
    pt_bound[5] = 20.0;//50
    pt_bound[6] = 40.0;//100
    

    //JPsi plots
    //pt_bound[0] = 0.0;  //0
    //pt_bound[1] = 4.0;  //10
    //pt_bound[2] = 8.0;  //20
    //pt_bound[3] = 12.0; //40
    //pt_bound[4] = 16.0; //100
    //pt_bound[5] = 20.0;
    //pt_bound[6] = 24.0;
    //pt_bound[7] = 32.0;
    //pt_bound[8] = 40.0;
  }
  //X Axis error on Eff graph 
  double PT[100], DelPT[100], mom_err[100];
  for (Int_t ih = 0; ih < Nptbin; ih++) {
    PT[ih] = (pt_bound[ih] + pt_bound[ih+1])/2.0;
    DelPT[ih] = pt_bound[ih+1] - pt_bound[ih];
    mom_err[ih] = DelPT[ih]/2.0;
    cout<<PT[ih]<<" X axis graph "<<DelPT[ih]<<endl;
  }
  
  double genError, recError;
  double gen_pt[100]={0}, gen_ptError[100]={0}; 
  double rec_pt[100]={0}, rec_ptError[100]={0}; 
  double Eff_cat_1[100]={0},Err_Eff_cat_1[100]={0};  
 
  // Histogram 2D Arrays
  TH1D *diMuonsInvMass_GenA[10][1000];
  TH1D *diMuonsInvMass_RecA[10][1000];
  TH1D *diMuonsPt_GenA[10][1000];
  TH1D *diMuonsPt_RecA[10][1000];
  char nameGen[10][500], nameRec[10][500], nameGenPt[10][500], nameRecPt[10][500];
  char namePt_1B[500];//for bkg func
  

  for (int ifile = 0; ifile <= 5; ifile++) {
    
    for (Int_t ih = 0; ih < Nptbin; ih++) {
      
      sprintf(nameGen[ifile],"DiMuonMassGen_pt_%d_%d",ih,ifile);
      sprintf(nameRec[ifile],"DiMuonMassRec_pt_%d_%d",ih,ifile);
      
      sprintf(nameGenPt[ifile],"DiMuonPtGen_pt_%d_%d",ih,ifile);
      sprintf(nameRecPt[ifile],"DiMuonPtRec_pt_%d_%d",ih,ifile);
      
      diMuonsInvMass_GenA[ifile][ih]= new TH1D(nameGen[ifile],nameGen[ifile],  100,2.6,3.5); //for eff Gen;
      diMuonsInvMass_GenA[ifile][ih]->Sumw2();
      diMuonsInvMass_GenA[ifile][ih]->SetMarkerStyle(7);
      diMuonsInvMass_GenA[ifile][ih]->SetMarkerColor(4);
      diMuonsInvMass_GenA[ifile][ih]->SetLineColor(4);
      
      diMuonsInvMass_RecA[ifile][ih] = new TH1D(nameRec[ifile],nameRec[ifile], 100,2.6,3.5); //for eff Rec;
      diMuonsInvMass_RecA[ifile][ih]->Sumw2();
      diMuonsInvMass_RecA[ifile][ih]->SetMarkerStyle(8);
      diMuonsInvMass_RecA[ifile][ih]->SetMarkerColor(4);
      diMuonsInvMass_RecA[ifile][ih]->SetLineColor(4);
      
      diMuonsPt_GenA[ifile][ih]= new TH1D(nameGenPt[ifile],nameGenPt[ifile],  100,0,40); //for eff Gen;
      diMuonsPt_RecA[ifile][ih]= new TH1D(nameRecPt[ifile],nameRecPt[ifile],  100,0,40); //for eff Rec;
    }
  }
  
  //===========================================Input Root File============================================================
  char fileName[10][500];
  //scales for different pT bins
  double scale[10]={0};  
  
if(Prompt==1){
  cout<<" prompt weight "<<endl;
  scale[0]=(8.7897); // pT [0-3]
  scale[1]=(6.4009); // pT [3-6]
  scale[2]=(4.0352); // pT [6-9]
  scale[3]=(0.7755); // pT [9-12] 
  scale[4]=(2.9473); // pT [12-15] 
  scale[5]=(1.0000); // pT [15-30]
 }

 if(Prompt==2){
   cout<<" Non prompt weight "<<endl;
   scale[0]=(0.9990); // pT [0-3]
   scale[1]=(2.7773); // pT [3-6]
   scale[2]=(3.8646); // pT [6-9]
   scale[3]=(2*0.6330); // pT [9-12] 
  //scale[3]=(0.6330); // pT [9-12] original
   scale[4]=(5.0430); // pT [12-15] 
  scale[5]=(1.0000); // pT [15-30]
  
  //scale[0]=(5*0.000227562/105)/1.08E-05;     
  //scale[1]=(5*0.000578402/96)/1.08E-05;   
  //scale[2]=(5*0.000259902/31)/1.08E-05;    
  //scale[3]=(10*3.85E-05/28)/1.08E-05;         
  //scale[4]=(5*2.19E-05/2)/1.08E-05;         
  //scale[5]=(1.08E-05/1.08E-05);       
  
 }
  if(PutWeight==0){scale[0]=(1);scale[1]=(1);scale[2]=(1);scale[3]=(1);scale[4]=(1);scale[5]=(1);}
  
  if(Prompt ==1){
    cout<<"==================Prompt JPsi================================================"<<endl;
    sprintf(fileName[0],"rootFiles/JPsi_SkimV9_OniaPlots_Pt03_All27Apr.root");
    sprintf(fileName[1],"rootFiles/JPsi_SkimV9_OniaPlots_Pt36_All27Apr.root");
    sprintf(fileName[2],"rootFiles/JPsi_SkimV9_OniaPlots_Pt69_All27Apr.root");
    sprintf(fileName[3],"rootFiles/JPsi_SkimV9_OniaPlots_Pt912_All27Apr.root");
    sprintf(fileName[4],"rootFiles/JPsi_SkimV9_OniaPlots_Pt1215_All27Apr.root");
    sprintf(fileName[5],"rootFiles/JPsi_SkimV9_OniaPlots_Pt1530_All27Apr.root");
  }
  

  if(Prompt ==2){
    cout<<"================== Non Prompt JPsi============================================="<<endl;
    sprintf(fileName[0],"rootFiles/NPJPsi_SkimV9_OniaPlots_Pt03_All27Apr.root");
    sprintf(fileName[1],"rootFiles/NPJPsi_SkimV9_OniaPlots_Pt36_All27Apr.root");
    sprintf(fileName[2],"rootFiles/NPJPsi_SkimV9_OniaPlots_Pt69_All27Apr.root");
    sprintf(fileName[3],"rootFiles/NPJPsi_SkimV9_OniaPlots_Pt912_All27Apr.root");
    sprintf(fileName[4],"rootFiles/NPJPsi_SkimV9_OniaPlots_Pt1215_All27Apr.root");
    sprintf(fileName[5],"rootFiles/NPJPsi_SkimV9_OniaPlots_Pt1530_All27Apr.root");
  }
  

  if(Prompt ==3){
    cout<<"================== Test JPsi============================================="<<endl;
    sprintf(fileName[0],"rootFiles/DimuonOnia2Dplots_JPsiPt_PP_test.root");
    sprintf(fileName[1],"rootFiles/DimuonOnia2Dplots_JPsiPt_PP_test.root");
    sprintf(fileName[2],"rootFiles/DimuonOnia2Dplots_JPsiPt_PP_test.root");
    sprintf(fileName[3],"rootFiles/DimuonOnia2Dplots_JPsiPt_PP_test.root");
    sprintf(fileName[4],"rootFiles/DimuonOnia2Dplots_JPsiPt_PP_test.root");
    sprintf(fileName[5],"rootFiles/DimuonOnia2Dplots_JPsiPt_PP_test.root");
 }
  
  TFile *infile;
  TTree *tree;
  TTree *gentree;
  
  //======================  File loop Starts ============================
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
    bool muPos_matches,muPos_tracker;
    //(2).Negative Muon                                     
    double muNeg_nchi2In, muNeg_dxy, muNeg_dz, muNeg_nchi2Gl;
    int muNeg_found, muNeg_pixeLayers, muNeg_nValidMuHits,muNeg_arbitrated;
    bool muNeg_matches,muNeg_tracker;
    //Gen Level variables
    //Gen JPsi Variables
    double GenJpsiMass, GenJpsiPt, GenJpsiRap;
    double GenJpsiPx, GenJpsiPy, GenJpsiPz;
    
    //2.) Gen muon variables 
    double GenmuPosPx, GenmuPosPy, GenmuPosPz,  GenmuPosEta, GenmuPosPt;
    double GenmuNegPx, GenmuNegPy, GenmuNegPz,  GenmuNegEta, GenmuNegPt;
    
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
    tree->SetBranchAddress("muPos_arbitrated", &muPos_arbitrated);
    
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
    tree->SetBranchAddress("muNeg_arbitrated", &muNeg_arbitrated);
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
    
    cout<<" Total Entries in GenLevel Tree for pT range: "<<fileName[ifile]<<"  "<<   nGenEntries<< " ==============="<<endl;
    
    for(int i=0; i< nGenEntries; i++)  {	    
      gentree->GetEntry(i);
      
      //Only printing 
      if(i%100000==0)
	{
	  cout<<" processing record "<<i<<endl;
	  cout<<" Mass "<< GenJpsiMass<< " pT "<< GenJpsiPt << " Y " <<GenJpsiRap<<endl;}
      
      bool GenPosIn=0, GenNegIn=0;
      GenmuPosPt= TMath::Sqrt(GenmuPosPx*GenmuPosPx + GenmuPosPy*GenmuPosPy); 
      GenmuNegPt= TMath::Sqrt(GenmuNegPx*GenmuNegPx + GenmuNegPy*GenmuNegPy); 
      
      

      diMuonsInvMass_Gen->Fill(GenJpsiMass);
      diMuonsPt_Gen0->Fill(GenJpsiPt);
      diMuonsRap_Gen0->Fill(GenJpsiRap);
      
      

      if(IsAccept(GenmuPosPt, GenmuPosEta)) {GenPosIn=1;}
      if(IsAccept(GenmuNegPt, GenmuNegEta)) {GenNegIn=1;}
      
      if((GenPosIn ==1 && GenNegIn==1)) NAccep++;
      
      
      Bin_Gen->Fill(gbin);
      
      
      //if(GenPosIn && GenNegIn){
      //if(ifile==0){diMuonsRap_Gen0->Fill(GenJpsiRap);}
      //if(ifile==1){diMuonsRap_Gen1->Fill(GenJpsiRap);}
      //if(ifile==2){diMuonsRap_Gen2->Fill(GenJpsiRap);}
      //if(ifile==3){diMuonsRap_Gen3->Fill(GenJpsiRap);}
      //if(ifile==4){diMuonsRap_Gen4->Fill(GenJpsiRap);}
      //if(ifile==5){diMuonsRap_Gen5->Fill(GenJpsiRap);}
      //}
      
      double GenCenWeight =0, GenWeight =0;
      GenCenWeight=FindCenWeight(gbin);	  
      GenWeight=GenCenWeight*scale[ifile];
      
      if(PutWeight==0) GenWeight=1; 
      
      
      for (Int_t ih = 0; ih < Nptbin; ih++) {
	


	
	//adding pT of all pt bins to see diss is cont
	//	if(iSpec == 1) if((GenJpsiPt>pt_bound[ih] && GenJpsiPt<=pt_bound[ih+1])){diMuonsPt_GenA[ifile][ih]->Fill(GenJpsiPt,GenWeight);}
	
	
	if(iSpec == 1) if((GenPosIn==1 && GenNegIn==1) && (TMath::Abs(GenJpsiRap)>0.0 && TMath::Abs(GenJpsiRap)<2.4) && (GenJpsiPt>pt_bound[ih] && GenJpsiPt<=pt_bound[ih+1])){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenWeight);}
	
	//if(iSpec == 1) if((GenPosIn==1 && GenNegIn==1) && (GenJpsiPt>pt_bound[ih] && GenJpsiPt<=pt_bound[ih+1])){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass);}
	//if(iSpec == 2) if((GenPosIn==1 && GenNegIn==1)&& (GenJpsiPt> 0.0 && GenJpsiPt<30.0) && (TMath::Abs(GenJpsiRap) > pt_bound[ih] && TMath::Abs(GenJpsiRap) <=pt_bound[ih+1])){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenWeight);}	
	//for non symetric plots
	if(iSpec == 2) if((GenPosIn==1 && GenNegIn==1)&& (GenJpsiPt> 6.5 && GenJpsiPt<30.0) && ((GenJpsiRap) > pt_bound[ih] && (GenJpsiRap) <=pt_bound[ih+1])){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenWeight);}	
	if(iSpec == 3)  if((GenPosIn==1 && GenNegIn==1) &&  (GenJpsiPt > 6.5 &&  GenJpsiPt<30.0) &&   (TMath::Abs(GenJpsiRap)<2.4) && (gbin >= pt_bound[ih] && gbin< pt_bound[ih+1])){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenWeight);}
      }
    
    }//gen loop end
    
    

    cout<<" accepted no "<< NAccep<<endl;
    dataFile<<" accepted no "<< NAccep<<endl;
    
    //dataFile<<" accepted no "<< NAccep<<endl;
    
    cout<<" ifile ========== "<<ifile<<endl<<endl;
    
    
    
      
      new TCanvas;
      diMuonsInvMass_Gen->Draw();
      gPad->SaveAs("plots/diMuonsInvMass_Gen.png");
      
      new TCanvas;
      diMuonsPt_Gen0->Draw();
      gPad->SaveAs("plots/diMuonsPt_Gen.png");
      
      new TCanvas;
      diMuonsRap_Gen0->Draw();
      gPad->SaveAs("plots/diMuonsRap_Gen.png");
      
    
    
    

    //new TCanvas;
    //Bin_Gen->Draw();
    //gPad->SaveAs("plots/Bin_Gen.png");
    
    

    
    //=============== Rec Tree Loop ==============================================================================
    
    int nRecEntries=tree->GetEntries();
    cout<<"Total Entries in reconstructed Tree for pT range "<<fileName[ifile]<<"  "<<nRecEntries<< "====="<<endl;
    for(int i=0; i<nRecEntries; i++)  {	    
      tree->GetEntry(i);
      //Only printing 
      if(i%10000==0){
	cout<<" processing record "<<i<<endl;
	//cout<<" processing Run  " <<runNb <<" event "<<eventNb<<" lum block "<<lumiBlock<<endl;    
	//cout<<" Mass "<< JpsiMass<< " pT "<< JpsiPt << " Y " <<JpsiRap<<"  "<<JpsiVprob<<" charge "<<JpsiCharge<<" rbin "<<rbin<<endl; 
      }
      bool PosPass=0, NegPass=0, AllCut=0 ,PosIn=0, NegIn=0;
      muPosPt= TMath::Sqrt(muPosPx*muPosPx + muPosPy*muPosPy); 
      muPosP = TMath::Sqrt(muPosPx*muPosPx + muPosPy*muPosPy+ muPosPz*muPosPz); 
      muNegPt= TMath::Sqrt(muNegPx*muNegPx + muNegPy*muNegPy); 
      muNegP = TMath::Sqrt(muNegPx*muNegPx + muNegPy*muNegPy +muNegPz*muNegPz); 
      
      if(IsAccept(muPosPt, muPosEta)){PosIn=1;}
      if(IsAccept(muNegPt, muNegEta)){NegIn=1;}
      
      bool mu_Global = ((muPos_nchi2Gl >=0) && (muNeg_nchi2Gl >=0));
      bool mu_Tracker = ((muPos_tracker==1) && (muNeg_tracker==1));
      
      if(muPos_found > 10 && muPos_pixeLayers > 0 && muPos_nchi2In < 4.0 && muPos_dxy < 3 && muPos_dz < 15 && muPos_nchi2Gl < 20  && muPos_arbitrated==1 && muPos_tracker==1){PosPass=1;}	  
      
      if(muNeg_found >10 && muNeg_pixeLayers >0 && muNeg_nchi2In <4.0 && muNeg_dxy < 3 && muNeg_dz < 15 && muNeg_nchi2Gl < 20 && muNeg_arbitrated==1 && muNeg_tracker==1){NegPass=1;}
      
      
      //if((muPos_matches==1 && muNeg_matches==1) && (PosIn==1 && NegIn==1) && (PosPass==1 && NegPass==1)&& mu_Global && mu_Tracker){AllCut=1;}
      


      //without ID cut
      // if((muPos_matches==1 && muNeg_matches==1) && (PosIn==1 && NegIn==1) && mu_Global && mu_Tracker){AllCut=1;}
      
      //without trigger matched
      if((PosIn==1 && NegIn==1) && (PosPass==1 && NegPass==1)&& mu_Global && mu_Tracker){AllCut=1;}
      
      double RecCenWeight=0,RecWeight=0;
      RecCenWeight=FindCenWeight(rbin);	  
      RecWeight=RecCenWeight*scale[ifile];
      
      if(PutWeight==0)RecWeight=1;
      
      if(AllCut==1){
	if(ifile==0){diMuonsRap_Rec0->Fill(JpsiRap);}
	if(ifile==1){diMuonsRap_Rec1->Fill(JpsiRap);}
	if(ifile==2){diMuonsRap_Rec2->Fill(JpsiRap);}
	if(ifile==3){diMuonsRap_Rec3->Fill(JpsiRap);}
	if(ifile==4){diMuonsRap_Rec4->Fill(JpsiRap);}
	if(ifile==5){diMuonsRap_Rec5->Fill(JpsiRap);}
      }
      
      //Eff loop for reco
      for (Int_t ih = 0; ih < Nptbin; ih++) {
	if((JpsiCharge == 0) && (JpsiVprob > 0.01)) {	  
	  
	 	  
	  //to see cont reco pT
	  if(iSpec == 1) if((JpsiPt>pt_bound[ih]  && JpsiPt<=pt_bound[ih+1]))diMuonsPt_RecA[ifile][ih]->Fill(JpsiPt,RecWeight);
	  
	  if(iSpec == 1) if((AllCut==1) && (TMath::Abs(JpsiRap)> 0.0 && TMath::Abs(JpsiRap)<2.4) && (JpsiPt>pt_bound[ih]  && JpsiPt<=pt_bound[ih+1]))  {diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecWeight);}
	  //if(iSpec == 2) if((AllCut==1) && (JpsiPt > 0.0 &&  JpsiPt<30.0) && (TMath::Abs(JpsiRap) > pt_bound[ih] && TMath::Abs(JpsiRap) <=pt_bound[ih+1])){diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecWeight);}
	  //for non symetric plots
	  if(iSpec == 2) if((AllCut==1) && (JpsiPt > 6.5 &&  JpsiPt<30.0) && ((JpsiRap) > pt_bound[ih] && (JpsiRap) <=pt_bound[ih+1])){diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecWeight);}
	  if(iSpec == 3) if( (AllCut==1) && (JpsiPt> 6.5 && JpsiPt<30.0) &&  (TMath::Abs(JpsiRap)<2.4) && (rbin>=pt_bound[ih]  && rbin<pt_bound[ih+1])){diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecWeight);}
	}
      }
    }//rec tree loop ends
    
    //new TCanvas;
    //if(ifile==0){diMuonsRap_Gen0->Draw();gPad->SaveAs("plots/diMuonsRap_Gen0_Pt03.png"); new TCanvas; diMuonsRap_Rec0->Draw(); gPad->SaveAs("plots/diMuonsRap_Rec0_Pt03.png");}
    //if(ifile==1){diMuonsRap_Gen1->Draw();new TCanvas; diMuonsRap_Rec1->Draw(); gPad->SaveAs("plots/diMuonsRap_Rec1.png");}
    //if(ifile==2){diMuonsRap_Gen2->Draw();new TCanvas; diMuonsRap_Rec2->Draw(); gPad->SaveAs("plots/diMuonsRap_Rec2.png");}
    //if(ifile==3){diMuonsRap_Gen3->Draw();new TCanvas; diMuonsRap_Rec3->Draw();  gPad->SaveAs("plots/diMuonsRap_Rec3.png");}
    //if(ifile==4){diMuonsRap_Gen4->Draw();new TCanvas; diMuonsRap_Rec4->Draw();  gPad->SaveAs("plots/diMuonsRap_Rec4.png");}
    //if(ifile==5){diMuonsRap_Gen5->Draw();new TCanvas; diMuonsRap_Rec5->Draw();   gPad->SaveAs("plots/diMuonsRap_Rec5.png");}
        
  }  // file loop ends
  
  ///////////////////////////////////////////////////////////////////
  cout<< " adding "<<endl;
  TH1D *diMuonsInvMass_RecA1[100];
  TH1D *diMuonsInvMass_GenA1[100];
  TH1D *diMuonsPt_GenA1[100];
  TH1D *diMuonsPt_RecA1[100];
  TF1 *backfun_1;
  
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
  //===========================Fitting=================================================================================//
  // Fit ranges
  double mass_low, mass_high;
  double MassJPsi, WeidthJPsi;
  // Fit Function crystall ball
  TF1 *GAUSPOL = new TF1("GAUSPOL",CrystalBall,2.4,3.8,6);
  GAUSPOL->SetParNames("Yield (J/#psi)","BinWidth","Mean","Sigma","#alpha","n");
  // Low mass range J/psi
  MassJPsi = 3.096; WeidthJPsi = 0.028;
  //mass_low = 2.945; mass_high = 3.24;  // Fit ranges
  mass_low = 2.92; mass_high = 3.24;  // Fit ranges

  GAUSPOL->SetParameter(2, MassJPsi);
  GAUSPOL->SetParameter(3, WeidthJPsi);
  //GAUSPOL->SetParLimits(3, 0.1*WeidthJPsi,2.0*WeidthJPsi);
  GAUSPOL->SetParameter(4, 1.2);
  GAUSPOL->SetParameter(5, 20.0); //for prompt jpsi
  // GAUSPOL->SetParameter(5, 100.0); //for non prompt
  GAUSPOL->SetLineWidth(2.0);
  GAUSPOL->SetLineColor(2);
  
  // Fit Function crystall ball_1
  // TF1 *GAUSPOL_1 = new TF1("GAUSPOL_1",CrystalBall_1,2.4,3.8,5);
  // GAUSPOL_1->SetParNames("#alpha","n","Mean","#sigma","N");
  // GAUSPOL_1->SetParameter(2, MassJPsi);
  // GAUSPOL_1->SetParameter(3, WeidthJPsi);
  // GAUSPOL_1->SetParLimits(3, 0.1*WeidthJPsi,2*WeidthJPsi);
  //GAUSPOL_1->SetParameter(0, 1.54);
  //GAUSPOL_1->SetParameter(1, 149.0);
  //GAUSPOL_1->SetLineWidth(2.0);
  //GAUSPOL_1->SetLineColor(4);
  //=====================Loop for eff========================================================================================//
  //define stuff here for error on weighted samples
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
   
    gen_pt[ih] = diMuonsInvMass_GenA1[ih]->IntegralAndError(1, 100, genError);
    gen_ptError[ih]= genError;
    cout<<" gen_pt[ih] "<< gen_pt[ih] <<" error   "<<  gen_ptError[ih]<<endl;
   
    if(Prompt ==1){
      
      if(iSpec==1) sprintf(PlotName,"plots/DiMuonMass_PtBin_%d.png",ih);
      if(iSpec==2) sprintf(PlotName,"plots/DiMuonMass_RapBin_%d.png",ih);
      if(iSpec==3) sprintf(PlotName,"plots/DiMuonMass_CentBin_%d.png",ih);
      
      if(iSpec==1) sprintf(PlotName1,"plots/DiMuonMass_PtBin_%d.pdf",ih);
      if(iSpec==2) sprintf(PlotName1,"plots/DiMuonMass_RapBin_%d.pdf",ih);
      if(iSpec==3) sprintf(PlotName1,"plots/DiMuonMass_CentBin_%d.pdf",ih);
    
      if(iSpec==1) sprintf(PlotName2,"plots/DiMuonMass_PtBin_%d.eps",ih);
      if(iSpec==2) sprintf(PlotName2,"plots/DiMuonMass_RapBin_%d.eps",ih);
      if(iSpec==3) sprintf(PlotName2,"plots/DiMuonMass_CentBin_%d.eps",ih); 
    }
    
    if(Prompt ==2){
      
      if(iSpec==1) sprintf(PlotName,"npplots/DiMuonMass_PtBin_%d.png",ih);
      if(iSpec==2) sprintf(PlotName,"npplots/DiMuonMass_RapBin_%d.png",ih);
      if(iSpec==3) sprintf(PlotName,"npplots/DiMuonMass_CentBin_%d.png",ih);
      
      if(iSpec==1) sprintf(PlotName1,"npplots/DiMuonMass_PtBin_%d.pdf",ih);
      if(iSpec==2) sprintf(PlotName1,"npplots/DiMuonMass_RapBin_%d.pdf",ih);
      if(iSpec==3) sprintf(PlotName1,"npplots/DiMuonMass_CentBin_%d.pdf",ih);
      
      if(iSpec==1) sprintf(PlotName2,"npplots/DiMuonMass_PtBin_%d.eps",ih);
      if(iSpec==2) sprintf(PlotName2,"npplots/DiMuonMass_RapBin_%d.eps",ih);
      if(iSpec==3) sprintf(PlotName2,"npplots/DiMuonMass_CentBin_%d.eps",ih); 
    }
    

    // cout<<" *********************** "<<diMuonsInvMass_RecA1[ih]->GetMaximum()<<endl;
    //giving inetial value for crystall ball fourth parameter 
    diMuonsInvMass_RecA1[ih]->Rebin(2);
    GAUSPOL->SetParameter(0, diMuonsInvMass_RecA1[ih]->Integral(0,50));
    GAUSPOL->FixParameter(1, diMuonsInvMass_RecA1[ih]->GetBinWidth(1));
    //GAUSPOL->SetParameter(0, diMuonsInvMass_RecA1[ih]->GetMaximum());
    //new TCanvas;
    //diMuonsInvMass_RecA1[ih]->Draw();
    
    new TCanvas;
    diMuonsInvMass_RecA1[ih]->Fit("GAUSPOL","LLMER", "", mass_low, mass_high);
    diMuonsInvMass_RecA1[ih]->DrawCopy("EPLsame");
    
    // new TCanvas;
    //diMuonsInvMass_RecA1[ih]->Fit("GAUSPOL_1","LLMER", "", mass_low, mass_high);
    //diMuonsInvMass_RecA1[ih]->DrawCopy("EPLsame");
    gPad->SaveAs(PlotName);
    gPad->SaveAs(PlotName1);
    gPad->SaveAs(PlotName2);
    
    //  cout << GAUSPOL_1->GetChisquare()<<endl;
    //for(int i=0;i<=100;i++) {cout<<i<<"  "<<diMuonsInvMass_RecA1[ih]->GetBinContent(i)<<endl;}
    //return;
    //double JPsiMass = GAUSPOL_1->GetParameter(2);
    //double JPsiWidth = GAUSPOL_1->GetParameter(3);
    //double JPsiYield = GAUSPOL_1->GetParameter(4); 


    double JPsiMass = GAUSPOL->GetParameter(2);
    double JPsiWidth = GAUSPOL->GetParameter(3);
    
    double JPsiYield = GAUSPOL->GetParameter(0); 
    Double_t JPsiYieldError = GAUSPOL->GetParError(0); 
    
    //cout<<JPsiYieldError<<"*****************"<<endl;

    //if(TMath::IsNan(JPsiYieldError)=1) {JPsiYieldError=TMath::Sqrt(JPsiYield);}

    double par[20];
    GAUSPOL->GetParameters(par);
    sprintf(namePt_1B,"pt_1B_%d",ih);
    
    backfun_1 = new TF1(namePt_1B, Pol2, mass_low, mass_high, 3);
    backfun_1->SetParameters(&par[3]);

    double MassLow=(JPsiMass-3*JPsiWidth);
    double MassHigh=(JPsiMass+3*JPsiWidth);
   

    int binlow =diMuonsInvMass_RecA1[ih]->GetXaxis()->FindBin(MassLow);
    int binhi =diMuonsInvMass_RecA1[ih]->GetXaxis()->FindBin(MassHigh);
    
    //double binwidth=diMuonsInvMass_RecA1[ih]->GetBinWidth(1);
    //yield by function 
    //rec_pt[ih] = JPsiYield;
    //rec_ptError[ih]= JPsiYieldError;
   
    //yield by histogram integral
    rec_pt[ih] = diMuonsInvMass_RecA1[ih]->IntegralAndError(binlow, binhi,recError);
    rec_ptError[ih]= recError;
    
    //calculate Eff         
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
        
    //error without weight
    if(PutWeight==0){Err_Eff_cat_1[ih]= Eff_cat_1[ih]*TMath::Sqrt(gen_ptError[ih]*gen_ptError[ih]/(gen_pt[ih]*gen_pt[ih]) + rec_ptError[ih]*rec_ptError[ih]/(rec_pt[ih]* rec_pt[ih]));}
    cout<<"=================================== This is bin "<<ih<<"================================================="<<endl;
    cout<<"JPsi Yield by integral of histo:  "<< diMuonsInvMass_RecA1[ih]->IntegralAndError(binlow, binhi,recError) <<"  error "<< rec_ptError[ih]<<endl; 
    cout<<"JPsiYield by CB yield determ:     "<< JPsiYield << " JPsiWidth "<< JPsiWidth<<" JPsiMass "<<JPsiMass <<" error "<< TMath::Sqrt((JPsiYield))<<endl;
    cout<<"JPsi Yield by Function integral:  "<< GAUSPOL->Integral(MassLow,MassHigh)<<endl;
    cout<<" Bin "<<ih<< " Reco Jpsi  "<<  rec_pt[ih] <<" Gen Jpsi "<<gen_pt[ih]<<endl;
    cout<<" Eff "<< Eff_cat_1[ih]<<" Error "<<Err_Eff_cat_1[ih]<<endl;

    char Spectra[100];
    if(iSpec==1) sprintf(Spectra,"Pt");
    if(iSpec==2) sprintf(Spectra,"Rap");
    if(iSpec==3) sprintf(Spectra,"Cent");
     
    dataFile<<"--------------------------------------------------------------------------------------------------------------------"<<endl;
    dataFile<<"Gen JPsi "<< gen_pt[ih] <<" rec JPsi "<<rec_pt[ih] <<"  "<<Spectra<<"["<<pt_bound[ih]<<" - "<<pt_bound[ih+1]<<"]"<<endl;
    dataFile<<"JPsi eff "<< Eff_cat_1[ih]<<" error "<<Err_Eff_cat_1[ih]<<"  "<<Spectra<<"["<<pt_bound[ih]<<" - "<<pt_bound[ih+1]<<"]"<<endl;

    backfun_1->SetLineColor(4);
    backfun_1->SetLineWidth(1);
    //backfun_1->Draw("same");
   
    if (Prompt==1){ 
      if(iSpec==1) sprintf(GPlotName,"plots/DiMuonGenMass_PtBin_%d.png",ih);
      if(iSpec==2) sprintf(GPlotName,"plots/DiMuonGenMass_RapBin_%d.png",ih);
      if(iSpec==3) sprintf(GPlotName,"plots/DiMuonGenMass_CentBin_%d.png",ih);
      
      if(iSpec==1) sprintf(GPlotName1,"plots/DiMuonGenMass_PtBin_%d.pdf",ih);
      if(iSpec==2) sprintf(GPlotName1,"plots/DiMuonGenMass_RapBin_%d.pdf",ih);
      if(iSpec==3) sprintf(GPlotName1,"plots/DiMuonGenMass_CentBin_%d.pdf",ih);
      
      if(iSpec==1) sprintf(GPlotName2,"plots/DiMuonGenMass_PtBin_%d.eps",ih);
      if(iSpec==2) sprintf(GPlotName2,"plots/DiMuonGenMass_RapBin_%d.eps",ih);
      if(iSpec==3) sprintf(GPlotName2,"plots/DiMuonGenMass_CentBin_%d.eps",ih);
    }
    
    if (Prompt==2){ 
      if(iSpec==1) sprintf(GPlotName,"npplots/NPDiMuonGenMass_PtBin_%d.png",ih);
      if(iSpec==2) sprintf(GPlotName,"npplots/NPDiMuonGenMass_RapBin_%d.png",ih);
      if(iSpec==3) sprintf(GPlotName,"npplots/NPDiMuonGenMass_CentBin_%d.png",ih);
      
      if(iSpec==1) sprintf(GPlotName1,"npplots/NPDiMuonGenMass_PtBin_%d.pdf",ih);
      if(iSpec==2) sprintf(GPlotName1,"npplots/NPDiMuonGenMass_RapBin_%d.pdf",ih);
      if(iSpec==3) sprintf(GPlotName1,"npplots/NPDiMuonGenMass_CentBin_%d.pdf",ih);
      
      if(iSpec==1) sprintf(GPlotName2,"npplots/NPDiMuonGenMass_PtBin_%d.eps",ih);
      if(iSpec==2) sprintf(GPlotName2,"npplots/NPDiMuonGenMass_RapBin_%d.eps",ih);
      if(iSpec==3) sprintf(GPlotName2,"npplots/NPDiMuonGenMass_CentBin_%d.eps",ih);
    }
    

    
    //Drawing histo
    new TCanvas;
    diMuonsInvMass_GenA1[ih]->Draw("EPL");
    gPad->SaveAs(GPlotName);
    gPad->SaveAs(GPlotName1);
    gPad->SaveAs(GPlotName2);
    //  if (iSpec==1){ new TCanvas; diMuonsPt_GenA1[ih]->Draw(); new TCanvas; diMuonsPt_RecA1[ih]->Draw();}
  }
  
  dataFile.close();
  TFile *outfile;
  if(Prompt==1){
    if(iSpec==1)outfile =new TFile("EffJPsi_Pt.root","Recreate");
    if(iSpec==2)outfile =new TFile("EffJPsi_Rap.root","Recreate");
    if(iSpec==3)outfile =new TFile("EffJPsi_Cent.root","Recreate");
  }

  if(Prompt==2){
    if(iSpec==1)outfile =new TFile("EffNPJPsi_Pt.root","Recreate");
    if(iSpec==2)outfile =new TFile("EffNPJPsi_Rap.root","Recreate");
    if(iSpec==3)outfile =new TFile("EffNPJPsi_Cent.root","Recreate");
  }
  
 if(Prompt==3){
    if(iSpec==1)outfile =new TFile("EffJPsi_Pt_test.root","Recreate");
    if(iSpec==2)outfile =new TFile("EffJPsi_Rap_test.root","Recreate");
    if(iSpec==3)outfile =new TFile("EffJPsi_Cent_test.root","Recreate");
  }


  TGraphErrors *Eff_JPsi = new TGraphErrors(Nptbin, PT, Eff_cat_1, mom_err,Err_Eff_cat_1);
  Eff_JPsi->SetMarkerStyle(21);
  Eff_JPsi->SetMarkerColor(2);
  Eff_JPsi->GetYaxis()->SetTitle("Reco Eff");
  if(iSpec==1) Eff_JPsi->GetXaxis()->SetTitle("J/#psi pT (GeV/c^{2})");
  if(iSpec==2) Eff_JPsi->GetXaxis()->SetTitle("J/#psi rapidity");
  if(iSpec==3) Eff_JPsi->GetXaxis()->SetTitle("bin");
  Eff_JPsi->GetYaxis()->SetRangeUser(0,1.0);

  TLegend *legend_GP = new TLegend( 0.50,0.79,0.80,0.89);
  legend_GP->SetBorderSize(0);
  legend_GP->SetFillStyle(0);
  legend_GP->SetFillColor(0);
  legend_GP->SetTextSize(0.032);
  legend_GP->AddEntry(Eff_JPsi,"PythiaEvtGen + HydjetBass", "P");
  
  new TCanvas;
  Eff_JPsi->Draw("AP");
  legend_GP->Draw("Same");
  Eff_JPsi->Write();
  
  if(Prompt==1){    
    if(iSpec==1){ gPad->SaveAs("plots/Eff_JPsi_Pt.pdf");gPad->SaveAs("plots/Eff_JPsi_Pt.png");gPad->SaveAs("plots/Eff_JPsi_Pt.eps");}
    if(iSpec==2){ gPad->SaveAs("plots/Eff_JPsi_Rap.pdf");gPad->SaveAs("plots/Eff_JPsi_Rap.png");gPad->SaveAs("plots/Eff_JPsi_Rap.eps");}
    if(iSpec==3){ gPad->SaveAs("plots/Eff_JPsi_Cent.pdf");gPad->SaveAs("plots/Eff_JPsi_Cent.png");gPad->SaveAs("plots/Eff_JPsi_Cent.eps");}
  }
  
  if(Prompt==2){   
    if(iSpec==1){ gPad->SaveAs("npplots/Eff_NPJPsi_Pt.pdf");gPad->SaveAs("npplots/Eff_NPJPsi_Pt.png");gPad->SaveAs("npplots/Eff_NPJPsi_Pt.eps");}
    if(iSpec==2){ gPad->SaveAs("npplots/Eff_NPJPsi_Rap.pdf");gPad->SaveAs("npplots/Eff_NPJPsi_Rap.png");gPad->SaveAs("npplots/Eff_NPJPsi_Rap.eps");}
    if(iSpec==3){ gPad->SaveAs("npplots/Eff_NPJPsi_Cent.pdf");gPad->SaveAs("npplots/Eff_NPJPsi_Cent.png");gPad->SaveAs("npplots/Eff_NPJPsi_Cent.eps");}
  }

  outfile->Write();
  outfile->Close();
  }


bool IsAccept(Double_t pt, Double_t eta)
{
  
  //return(1);
  //return (fabs(eta) < 2.4); 
  
  return (fabs(eta) < 2.4 &&
	  (    ( fabs(eta) < 1.0 && pt >= 3.4 ) ||
	       (  1.0 <= fabs(eta) && fabs(eta) < 1.5 && pt >= 5.8-2.4*fabs(eta) ) ||
	       (  1.5 <= fabs(eta) && pt >= 3.3667 - 7.0/9.0*fabs(eta)) ));
}



double FindCenWeight(int Bin)
{
  double NCollArray[50]={
    1563.03, 1370.41, 1204.05, 1063.45, 943.5,
    834.12, 736.223, 654.913, 576.466, 507.757, 443.05, 386.802, 334.48,
    290.097, 247.779, 211.762, 179.834, 153.509, 127.75, 106.59, 88.1189,
    72.3836, 59.1049, 47.3574, 37.7951, 30.1705, 23.6861, 18.6918, 14.2287,
    10.9705, 8.76148, 6.57459, 5.01557, 3.78525, 2.9123, 2.12377, 1.5,
    0.922951, 0.581967, 0.503279,
  };
  return(NCollArray[Bin]);
}






/*
//Old weights
if(Prompt==1){
  cout<<" prompt weight "<<endl;
  scale[0]=(1.285345e-02/0.00005571);
  scale[1]=(7.309949e-03/0.00005571);
  scale[2]=(0.00393391/0.00005571);
  scale[3]=(0.000669658/0.00005571);
  scale[4]=(0.000164187/0.00005571);
  scale[5]=(0.00005571/0.00005571);
  
 }
  

if(Prompt==2){
  cout<<" Non prompt weight "<<endl;
  scale[0]=(1.137e-04/4.339e-06);
  scale[1]=(2.892e-04/4.339e-06);
  scale[2]=(2.59902e-04/4.339e-06);
  scale[3]=(3.84506e-05/4.339e-06);
  scale[4]=(2.18806e-05/4.339e-06);
  scale[5]=(4.339e-06/4.339e-06);

 }
PromptJpsiPt03: 105000  0.0257069       8.7897
PromptJpsiPt36: 82000   0.0146199       6.4009
PromptJpsiPt69: 35000   0.00393391      4.0352
PromptJpsiPt912:31000   0.00066966      0.7755
PromptJpsiPt1215:2000    0.00016419      2.9473
PromptJpsiPt1530:5000    0.00013927      1.0000

NonPromptJpsiPt03:      105000  0.000227562     0.9990
NonPromptJpsiPt36:      96000   0.000578402     2.7773
NonPromptJpsiPt69:      31000   0.000259902     3.8646
NonPromptJpsiPt912:     28000   3.85E-05        0.6330
NonPromptJpsiPt1215:    2000    2.19E-05        5.0430
NonPromptJpsiPt1530:    5000    1.08E-05        1.0000




NonPromptJpsiPt03:      105000  ((5/105*(0.000227562))/1.08E-05)     0.9990
NonPromptJpsiPt36:      96000   ((5/96*(0.000578402))/1.08E-05)     2.7773
NonPromptJpsiPt69:      31000   ((5/31*(0.000259902))/1.08E-05)       3.8646
NonPromptJpsiPt912:     28000   ((5/28*(3.85E-05))/1.08E-05)          0.6330
NonPromptJpsiPt1215:    2000   ((5/2*(2.19E-05))/1.08E-05)          5.0430
NonPromptJpsiPt1530:    5000    (1.08E-05/1.08E-05)          1.0000



UpsilonPt03A:   10000   0.0380228       6.8802
UpsilonPt36A:   10000   0.0480769       8.6995
UpsilonPt69A:   10000   0.0293255       5.3065
UpsilonPt912A:  10000   0.0125156       2.2647
UpsilonPt1215:  2000    0.00336587      3.0453
UpsilonPt1530:  5000    0.00276319      1.0000
*/
