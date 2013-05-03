#ifndef __CINT__
#endif
#include "TLatex.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TAxis.h"
#include "TH1.h"
#include "TH2.h"
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
#include "TString.h"
#include <iostream>
#include <iomanip>

Bool_t IsAccept(Double_t pt, Double_t eta);
Bool_t IsAccept_PP(Double_t pt, Double_t eta);

void UpsilonMassFit2013_PPb_All(Int_t Spec,Int_t Y);

void RunUpsilonMassFit2013_PPb_All_CVS()
{
   for(Int_t i=3;i<5;i++){
    for(Int_t j=1;j<4;j++){
      UpsilonMassFit2013_PPb_All(i,j);
    }
  }

  
}


void UpsilonMassFit2013_PPb_All(Int_t Spec, Int_t Y)
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




  Double_t Y1SEff_Pt[20],errY1SEff_Pt[20];
  Double_t Y2SEff_Pt[20],errY2SEff_Pt[20];
  Double_t Y3SEff_Pt[20],errY3SEff_Pt[20];
 
  Double_t Y1SEff_Rap[20],errY1SEff_Rap[20];
  Double_t Y2SEff_Rap[20],errY2SEff_Rap[20];
  Double_t Y3SEff_Rap[20],errY3SEff_Rap[20];

  
  Double_t Y1SEff_NTrk[20],errY1SEff_NTrk[20];
  Double_t Y2SEff_NTrk[20],errY2SEff_NTrk[20];
  Double_t Y3SEff_NTrk[20],errY3SEff_NTrk[20];


  Double_t Y1SEff_HFET[20],errY1SEff_HFET[20];
  Double_t Y2SEff_HFET[20],errY2SEff_HFET[20];
  Double_t Y3SEff_HFET[20],errY3SEff_HFET[20];





  Double_t RError(Double_t A, Double_t eA, Double_t B, Double_t eB);
  Double_t WeightRatioError(Double_t A, Double_t ErrorA, Double_t B, Double_t ErrorB);


  Double_t pmin,pmax;
  Double_t ymin,ymax;

  //DiMuRapidity Cut
  Double_t DiMuRapMin, DiMuRapMax;

  
  Int_t IsPPb =0,IsPP=0;

  Int_t IsOfficial=0;
  Int_t iSpec=0,Y1s=0,Y2s=0,Y3s=0;  
  
  //See pT Cut
  Double_t PtCut= 0.0;
  Int_t isParent=0;  

 
  IsOfficial=1;
  //IsPPb=1;
  IsPP=1;  
  
  isParent=1;
  PtCut=4.0;

  if(IsPPb ==1 ){  
  
    DiMuRapMin=-1.47;
    DiMuRapMax=0.53;

    //DiMuRapMin=-2.4;
    //DiMuRapMax=1.47;
  

  }

  
  
  if(IsPP ==1 ){  
    DiMuRapMin=-1.0;
    DiMuRapMax=1.0;
  }



  pmin=0.0;
  pmax=100.0;

  ymin=DiMuRapMin;
  ymax=DiMuRapMax;

 
  
  if(Spec==1){iSpec=1;}
  if(Spec==2){iSpec=2;}
  if(Spec==3){iSpec=3;}
  if(Spec==4){iSpec=4;}
  
  if(Y==1) {Y1s=1;}
  if(Y==2) {Y2s=1;}
  if(Y==3) {Y3s=1;}

  
   
  //================================= Define Histograms====================================//
  char OutTextFile[100]; 
  
  if( IsPPb ==1 && IsOfficial == 1){  sprintf(OutTextFile,"EffY_PPb.tex"); }
  if( IsPPb ==1 && IsOfficial == 0){  sprintf(OutTextFile,"Pri_EffY_PP.tex"); } 
  if( IsPP == 1 && IsOfficial == 1 ){  sprintf(OutTextFile,"EffY_PP276.tex"); }

 
    
  ofstream dataFile(Form(OutTextFile),ios::app);
 
  char Str1[100],Str2[100],Str3[100]; 
  sprintf(Str1,"\\hline");
  sprintf(Str2,"\\\\");
  sprintf(Str3,"\\");
 
  if(iSpec==1 && Y1s==1 ){
    dataFile<<Str3<<"documentstyle[12 pt]{article}"<<endl;
    dataFile<<Str3<<"begin{document}"<<endl<<endl;
  
  }

  TH1D *diMuonsInvMass_Gen = new TH1D("diMuonsInvMass_Gen","diMuonsInvMass_Gen", 100,8.0,12.0);
  
  TH1D *diMuonsPt_Gen = new TH1D("diMuonsPt_Gen","diMuonsPt_Gen", 100,0,100);
  diMuonsPt_Gen->Sumw2();
  TH1D *diMuonsRap_Gen = new TH1D("diMuonsRap_Gen","diMuonsRap_Gen", 100,-5,5);
  diMuonsRap_Gen->Sumw2();
  
  TH1D *diMuonsPt_rec = new TH1D("diMuonsPt_rec","diMuonsPt_rec", 100,0,100);
  diMuonsPt_rec->Sumw2();
  TH1D *diMuonsRap_rec = new TH1D("diMuonsRap_rec","diMuonsRap_rec", 100,-5,5);
  diMuonsRap_rec->Sumw2();
 
  TH1D * RatioFSR_Pt;
  TH1D *diMuonsPtB_Gen = new TH1D("diMuonsPtB_Gen","diMuonsPtB_Gen", 20,0,20);
  diMuonsPtB_Gen->Sumw2();
  TH1D *UpsilonPtB_Gen = new TH1D("UpsilonPtB_Gen","UpsilonPtB_Gen", 20,0,20);
  UpsilonPtB_Gen->Sumw2();


  TH1D *MuonPt_Gen = new TH1D("MuonPt_Gen","MuonPt_Gen", 100,0,50);
  TH1D *MuonEta_Gen = new TH1D("MuonEta_Gen","MuonEta_Gen", 100,-4.0,4.0);
  TH1D *MuonPhi_Gen = new TH1D("MuonPhi_Gen","MuonPhi_Gen", 100,-5.0,5.0);
  TH2D *MuonEtaPhi_Gen = new TH2D("MuonEtaPhi_Gen","MuonEtaPhi_Gen", 100,-4.0,4.0,100,-5.0,5.0);



  TH1D *MuonPt_Rec = new TH1D("MuonPt_Rec","MuonPt_Rec", 100,0,50);
  TH1D *MuonEta_Rec = new TH1D("MuonEta_Rec","MuonEta_Rec", 100,-4.0,4.0);
  TH1D *MuonPhi_Rec = new TH1D("MuonPhi_Rec","MuonPhi_Rec", 100,-5.0,5.0);
  TH2D *MuonEtaPhi_Rec = new TH2D("MuonEtaPhi_Rec","MuonEtaPhi_Rec", 100,-4.0,4.0,100,-5.0,5.0);



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

  
  TH1D *Bin_Gen = new TH1D("Bin_Gen","Bin_Gen", 50,0,50);
  TH1D *Bin_Rec = new TH1D("Bin_Rec","Bin_Rec", 50,0,50);
  


  TH1D *NTrk = new TH1D("NTrk","NTrk", 40,0,200);
  TH1D *AvHF_ET_Eta4 = new TH1D("AvHF_ET_Eta4","AvHF_ET_Eta4", 40,0,200);
 

  //============================Define AccEff Stuff here================================//
  // Pt bin sizes
  Int_t Nptbin=1;
  Double_t pt_bound[100] = {0};
 
  if(iSpec == 1) { 
  
    Nptbin = 11;
   
    //for plots
    pt_bound[0] = 0.0;
    pt_bound[1] = 2.0;
    pt_bound[2] = 4.0;
    pt_bound[3] = 6.0;
    pt_bound[4] = 8.0;
    pt_bound[5] = 10.0;
    pt_bound[6] = 12.0;
    pt_bound[7] = 14.0;
    pt_bound[8] = 16.0;
    pt_bound[9] = 20.0;
    pt_bound[10] = 24.0;
    pt_bound[11] = 30.0;

  
  }
  
  if(iSpec == 2) { 
    
    if(IsPPb==1){Nptbin = 1;}
    if(IsPP==1){Nptbin = 1;}
    
    if(IsPPb ==1)
      {
	pt_bound[0] = -1.47; 
	pt_bound[1] = 0.53; 
	
	pt_bound[2] = 0.53; 
	pt_bound[3] = -0.94; 
	pt_bound[4] = -0.47; 
	pt_bound[5] = 0.0;
	pt_bound[6] = 0.53; 
	pt_bound[7] = 0.73; 
	pt_bound[8] = 1.06; 
	pt_bound[9] = 1.46;
	
	pt_bound[10] = 2.0;
	pt_bound[11] = 2.4;  


      }


    if(IsPP ==1)
      {
	pt_bound[0] = -1.0; 
	pt_bound[1] = 1.0; 
	

	pt_bound[2] = 1.0; 
	pt_bound[3] =  0.0; 
	pt_bound[4] =  1.0; 
	pt_bound[5] =  1.6;
	pt_bound[6] =  2.4; 
	
	pt_bound[7] = 0.73; 
	pt_bound[8] = 1.06; 
	pt_bound[9] = 1.46;
	pt_bound[10] = 2.0;
	pt_bound[11] = 2.4;

      }

  }
  

  if(iSpec == 3) {
  
    Nptbin = 7;
    
    pt_bound[0] = 0.0;
    pt_bound[1] = 10.0;
    pt_bound[2] = 20.0;
    pt_bound[3] = 30.0;
    pt_bound[4] = 40.0;
    pt_bound[5] = 50.0;
    pt_bound[6] = 60.0;
    pt_bound[7] = 80.0;
    
    pt_bound[8] = 100.0;
    
  }


  if(iSpec == 4) {

    Nptbin = 5;
    
    pt_bound[0] = 0.0;
    pt_bound[1] = 5.0;
    pt_bound[2] = 10.0;
    pt_bound[3] = 15.0;
    pt_bound[4] = 20.0;
    pt_bound[5] = 30.0;
    
    
    pt_bound[6] = 30.0;
    pt_bound[7] = 80.0;
    pt_bound[8] = 100.0;
  
  }
  


  

  //X Axis error on Eff graph 
  Double_t PT[100], DelPT[100], mom_err[100];
  for (Int_t ih = 0; ih < Nptbin; ih++) {
    PT[ih] = (pt_bound[ih] + pt_bound[ih+1])/2.0;
    DelPT[ih] = pt_bound[ih+1] - pt_bound[ih];
    mom_err[ih] = DelPT[ih]/2.0;
  }
  
  Double_t genError, recError;

  Double_t gen_pt[100]={0}, gen_ptError[100]={0}; 
  Double_t rec_pt[100]={0}, rec_ptError[100]={0}; 
  Double_t Eff_cat_1[100]={0},Err_Eff_cat_1[100]={0};  
  
  Double_t recError_NoTrg,recError_NoID,recError_NoCut;
  Double_t Yield_NoTrg[100]={0}, errYield_NoTrg[100]={0};
  Double_t Yield_NoID[100]={0}, errYield_NoID[100]={0};
  Double_t Yield_NoCut[100]={0}, errYield_NoCut[100]={0};
  
  Double_t Eff_Trigger[100]={0},errEff_Trigger[100]={0};
  Double_t Eff_MuID[100]={0},errEff_MuID[100]={0};
  Double_t Eff_Reco[100]={0},errEff_Reco[100]={0};
 


  // Histogram arrays
  TH1D *diMuonsInvMass_GenA[10][1000];
  TH1D *diMuonsInvMass_RecA[10][1000];
  
  TH1D *diMuonsPt_GenA[10][1000];
  TH1D *diMuonsPt_RecA[10][1000];
  
  char nameGen[10][500], nameRec[10][500], nameGenPt[10][500], nameRecPt[10][500];
  
  char nameRec_NoTrg[10][500],nameRec_NoID[10][500], nameRec_NoCut[10][500];
  
  TH1D *diMuonsInvMass_RecA_NoTrg[10][1000];  
  TH1D *diMuonsInvMass_RecA_NoID[10][1000];  
  TH1D *diMuonsInvMass_RecA_NoCut[10][1000];  


    
  for (Int_t ifile = 0; ifile <= 0; ifile++) {
    for (Int_t ih = 0; ih < Nptbin; ih++) {
      sprintf(nameGen[ifile],"DiMuonMassGen_pt_%d_%d",ih,ifile);
      sprintf(nameRec[ifile],"DiMuonMassRec_pt_%d_%d",ih,ifile);
      
      sprintf(nameGenPt[ifile],"DiMuonPtGen_pt_%d_%d",ih,ifile);
      sprintf(nameRecPt[ifile],"DiMuonPtRec_pt_%d_%d",ih,ifile);

      sprintf(nameRec_NoTrg[ifile],"DiMuonMassRec_pt_NoTrg_%d_%d",ih,ifile);
      sprintf(nameRec_NoID[ifile],"DiMuonMassRec_pt_NoID_%d_%d",ih,ifile);
      sprintf(nameRec_NoCut[ifile],"DiMuonMassRec_pt_NoCut_%d_%d",ih,ifile);
      
  
      diMuonsInvMass_GenA[ifile][ih]= new TH1D(nameGen[ifile],nameGen[ifile],  100,8.0,12.0); //for eff Gen;
      diMuonsInvMass_GenA[ifile][ih]->Sumw2();
      diMuonsInvMass_GenA[ifile][ih]->SetMarkerStyle(7);
      diMuonsInvMass_GenA[ifile][ih]->SetMarkerColor(4);
      diMuonsInvMass_GenA[ifile][ih]->SetLineColor(4);
      
      diMuonsInvMass_RecA[ifile][ih] = new TH1D(nameRec[ifile],nameRec[ifile], 100,8.0,12.0); //for eff Rec;
      diMuonsInvMass_RecA[ifile][ih]->Sumw2();
      diMuonsInvMass_RecA[ifile][ih]->SetMarkerStyle(8);
      diMuonsInvMass_RecA[ifile][ih]->SetMarkerColor(4);
      diMuonsInvMass_RecA[ifile][ih]->SetLineColor(4);
      
      
      diMuonsPt_GenA[ifile][ih]= new TH1D(nameGenPt[ifile],nameGenPt[ifile],  100,0,100); //
      diMuonsPt_RecA[ifile][ih]= new TH1D(nameRecPt[ifile],nameRecPt[ifile],  100,0,100); //
    
      
      diMuonsInvMass_RecA_NoTrg[ifile][ih] = new TH1D(nameRec_NoTrg[ifile],nameRec_NoTrg[ifile], 100,8.0,12.0); //for Trg eff;
      diMuonsInvMass_RecA_NoTrg[ifile][ih]->Sumw2();
      diMuonsInvMass_RecA_NoTrg[ifile][ih]->SetMarkerStyle(8);
      diMuonsInvMass_RecA_NoTrg[ifile][ih]->SetMarkerColor(4);
      diMuonsInvMass_RecA_NoTrg[ifile][ih]->SetLineColor(4);



      diMuonsInvMass_RecA_NoID[ifile][ih] = new TH1D(nameRec_NoID[ifile],nameRec_NoID[ifile], 100,8.0,12.0); //for Trg eff;
      diMuonsInvMass_RecA_NoID[ifile][ih]->Sumw2();
      diMuonsInvMass_RecA_NoID[ifile][ih]->SetMarkerStyle(8);
      diMuonsInvMass_RecA_NoID[ifile][ih]->SetMarkerColor(4);
      diMuonsInvMass_RecA_NoID[ifile][ih]->SetLineColor(4);


      diMuonsInvMass_RecA_NoCut[ifile][ih] = new TH1D(nameRec_NoCut[ifile],nameRec_NoCut[ifile], 100,8.0,12.0); //for Trg eff;
      diMuonsInvMass_RecA_NoCut[ifile][ih]->Sumw2();
      diMuonsInvMass_RecA_NoCut[ifile][ih]->SetMarkerStyle(8);
      diMuonsInvMass_RecA_NoCut[ifile][ih]->SetMarkerColor(4);
      diMuonsInvMass_RecA_NoCut[ifile][ih]->SetLineColor(4);




    }
  }
  
  //===============Input Root File============================================//
  char fileName[10][500];
  //Scales
  Double_t scale[10]={0};  
  
  scale[0]=(1.0); // pT [0-3]


  
  
  
  //Unboosted Sample
  //if(Y1s==1 && isParent ==1){sprintf(fileName[0],"rootFiles/Y1S_DiMuTree_Official_All14032013.root");}
  
  if(IsPPb ==1 && IsOfficial == 0 && Y1s==1 ){sprintf(fileName[0],"rootFiles/Upsilon1S_OniaTree_All31Jan.root");}
  if(IsPPb ==1 && IsOfficial == 0 && Y2s==1 ){sprintf(fileName[0],"rootFiles/Upsilon2S_OniaTree_All31Jan.root");}
  if(IsPPb ==1 && IsOfficial == 0 && Y3s==1 ){sprintf(fileName[0],"rootFiles/Upsilon3S_OniaTree_All31Jan.root");}

  
  if(IsPPb ==1 && IsOfficial == 1 && Y1s==1 ){sprintf(fileName[0],"rootFiles/Y1S_DiMuTree_Official_All14032013.root");}
  if(IsPPb ==1 && IsOfficial == 1 && Y2s==1 ){sprintf(fileName[0],"rootFiles/Y2S_DiMuTree_Official_All14032013.root");}
  if(IsPPb ==1 && IsOfficial == 1 && Y3s==1 ){sprintf(fileName[0],"rootFiles/Y3S_DiMuTree_Official_All14032013.root");}
  
  

  //if(IsPP ==1 && IsOfficial == 1 && Y1s==1 ){sprintf(fileName[0],"rootFiles/Y1S_OniaTree_PriMC_NoFSR_276TeV_All30042013.root");}
  if(IsPP ==1 && IsOfficial == 1 && Y1s==1 ){sprintf(fileName[0],"rootFiles/Y1S_OniaTree_OffMC_276TeV_Cent_25042013_All.root");}
  if(IsPP ==1 && IsOfficial == 1 && Y2s==1 ){sprintf(fileName[0],"rootFiles/Y2S_OniaTree_OffMC_276TeV_Cent_25042013_All.root");}
  if(IsPP ==1 && IsOfficial == 1 && Y3s==1 ){sprintf(fileName[0],"rootFiles/Y3S_OniaTree_OffMC_276TeV_Cent_25042013_All.root");}


  TFile *infile;
  TTree *tree;
  TTree *gentree;
  
  //===========File loop ======================
  
  for(Int_t ifile =0; ifile<=0; ifile++){
    cout<<" file loop "<<endl;
    infile=new TFile(fileName[ifile],"R");
    tree=(TTree*)infile->Get("SingleMuonTree");
    gentree=(TTree*)infile->Get("SingleGenMuonTree");
    
    //Event variables
    Int_t eventNb,runNb,lumiBlock, gbin, rbin;
    
    Int_t           Npix;
    Int_t           NpixelTracks;
    Int_t           Ntracks;
    Double_t        SumET_HF;
    Double_t        SumET_HFplus;
    Double_t        SumET_HFminus;
    Double_t        SumET_HFplusEta4;
    Double_t        SumET_HFminusEta4;
    Double_t        SumET_ET;
    Double_t        SumET_EE;
    Double_t        SumET_EB;
    Double_t        SumET_EEplus;
    Double_t        SumET_EEminus;
    Double_t        SumET_ZDC;
    Double_t        SumET_ZDCplus;
    Double_t        SumET_ZDCminus;

    
    //Jpsi Variables
    Double_t JpsiMass,JpsiPt,JpsiRap, JpsiCharge;
    Double_t JpsiVprob;
    //2.) muon variables RECO                                                                       
    Double_t muPosPx, muPosPy, muPosPz,  muPosEta, muPosPt, muPosPhi;
    Double_t muNegPx, muNegPy, muNegPz,  muNegEta, muNegPt, muNegPhi;
    //(1).Positive Muon                                     
    Double_t muPos_nchi2In, muPos_dxy, muPos_dz, muPos_nchi2Gl;
    Int_t muPos_found, muPos_trackerLayers, muPos_pixeLayers, muPos_nValidMuHits,muPos_arbitrated,muPos_stationTight;
    Bool_t muPos_matches,muPos_tracker,muPos_global;
    Int_t muPos_Trigger1, muPos_Trigger2,muPos_Trigger3,muPos_Trigger4,muPos_Trigger5;
    Int_t muPos_Trigger6,muPos_Trigger7,muPos_Trigger8,muPos_Trigger9,muPos_Trigger10; 
    
    //(2).Negative Muon                                     
    Double_t muNeg_nchi2In, muNeg_dxy, muNeg_dz, muNeg_nchi2Gl;
    Int_t muNeg_found, muNeg_trackerLayers, muNeg_pixeLayers, muNeg_nValidMuHits,muNeg_arbitrated,muNeg_stationTight;
    Bool_t muNeg_matches,muNeg_tracker,muNeg_global;
    
    Int_t muNeg_Trigger1, muNeg_Trigger2,muNeg_Trigger3,muNeg_Trigger4,muNeg_Trigger5;
    Int_t muNeg_Trigger6,muNeg_Trigger7,muNeg_Trigger8,muNeg_Trigger9,muNeg_Trigger10;





    //Gen Level variables

    Int_t           Gen_Npix;
    Int_t           Gen_NpixelTracks;
    Int_t           Gen_Ntracks;
    Double_t        Gen_SumET_HF;
    Double_t        Gen_SumET_HFplus;
    Double_t        Gen_SumET_HFminus;
    Double_t        Gen_SumET_HFplusEta4;
    Double_t        Gen_SumET_HFminusEta4;
    Double_t        Gen_SumET_ET;
    Double_t        Gen_SumET_EE;
    Double_t        Gen_SumET_EB;
    Double_t        Gen_SumET_EEplus;
    Double_t        Gen_SumET_EEminus;
    Double_t        Gen_SumET_ZDC;
    Double_t        Gen_SumET_ZDCplus;
    Double_t        Gen_SumET_ZDCminus;


    //Gen Parent Variables
    Double_t GenJpsiMassP, GenJpsiPtP, GenJpsiRapP;
    Double_t GenJpsiPxP, GenJpsiPyP, GenJpsiPzP;
    


    //Gen JPsi Variables
    Double_t GenJpsiMass, GenJpsiPt, GenJpsiRap;
    Double_t GenJpsiPx, GenJpsiPy, GenJpsiPz;
    
    //2.) Gen muon variables 
    Double_t GenmuPosPx, GenmuPosPy, GenmuPosPz,  GenmuPosEta, GenmuPosPt,GenmuPosPhi;
    Double_t GenmuNegPx, GenmuNegPy, GenmuNegPz,  GenmuNegEta, GenmuNegPt,GenmuNegPhi;

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
    
    tree->SetBranchAddress("Npix",&Npix);
    tree->SetBranchAddress("NpixelTracks",&NpixelTracks);
    tree->SetBranchAddress("Ntracks",&Ntracks);
    tree->SetBranchAddress("SumET_HF",&SumET_HF);
    tree->SetBranchAddress("SumET_HFplus",&SumET_HFplus);
    tree->SetBranchAddress("SumET_HFminus",&SumET_HFminus);
    tree->SetBranchAddress("SumET_HFplusEta4",&SumET_HFplusEta4);
    tree->SetBranchAddress("SumET_HFminusEta4",&SumET_HFminusEta4);
    tree->SetBranchAddress("SumET_ET",&SumET_ET);
    tree->SetBranchAddress("SumET_EE",&SumET_EE);
    tree->SetBranchAddress("SumET_EB",&SumET_EB);
    tree->SetBranchAddress("SumET_EEplus",&SumET_EEplus);
    tree->SetBranchAddress("SumET_EEminus",&SumET_EEminus);
    tree->SetBranchAddress("SumET_ZDC",&SumET_ZDC);
    tree->SetBranchAddress("SumET_ZDCplus",&SumET_ZDCplus);
    tree->SetBranchAddress("SumET_ZDCminus",&SumET_ZDCminus);

    //muon variable
    tree->SetBranchAddress("muPosPx",&muPosPx);
    tree->SetBranchAddress("muPosPy",&muPosPy);
    tree->SetBranchAddress("muPosPz",&muPosPz);
    tree->SetBranchAddress("muPosPhi",&muPosPhi);
    tree->SetBranchAddress("muPosEta",&muPosEta);
    

    tree->SetBranchAddress("muNegPx", &muNegPx);
    tree->SetBranchAddress("muNegPy",    &muNegPy);
    tree->SetBranchAddress("muNegPz",    &muNegPz);
    tree->SetBranchAddress("muNegPhi",    &muNegPhi);
    tree->SetBranchAddress("muNegEta",    &muNegEta);
    


    //1). Positive Muon
    tree->SetBranchAddress("muPos_nchi2In", &muPos_nchi2In);
    tree->SetBranchAddress("muPos_dxy", &muPos_dxy);
    tree->SetBranchAddress("muPos_dz", &muPos_dz);
    tree->SetBranchAddress("muPos_nchi2Gl", &muPos_nchi2Gl);
    tree->SetBranchAddress("muPos_found", &muPos_found);
    tree->SetBranchAddress("muPos_pixeLayers", &muPos_pixeLayers);
    tree->SetBranchAddress("muPos_trackerLayers", &muPos_trackerLayers);
    tree->SetBranchAddress("muPos_nValidMuHits", &muPos_nValidMuHits);
    tree->SetBranchAddress("muPos_matches", &muPos_matches);
    tree->SetBranchAddress("muPos_tracker", &muPos_tracker);
    tree->SetBranchAddress("muPos_global",&muPos_global);
    tree->SetBranchAddress("muPos_arbitrated", &muPos_arbitrated);
    tree->SetBranchAddress("muPos_stationTight", &muPos_stationTight);

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
    tree->SetBranchAddress("muNeg_trackerLayers", &muNeg_trackerLayers);
    tree->SetBranchAddress("muNeg_pixeLayers", &muNeg_pixeLayers);
    tree->SetBranchAddress("muNeg_nValidMuHits", &muNeg_nValidMuHits);
    tree->SetBranchAddress("muNeg_matches", &muNeg_matches);
    tree->SetBranchAddress("muNeg_tracker", &muNeg_tracker);
    tree->SetBranchAddress("muNeg_global",&muNeg_global);
    tree->SetBranchAddress("muNeg_arbitrated", &muNeg_arbitrated);
    tree->SetBranchAddress("muNeg_stationTight", &muNeg_stationTight);


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
       
    //====================================Gen Variables=========================================================
    
    gentree->SetBranchAddress("Gen_Npix",&Gen_Npix);
    gentree->SetBranchAddress("Gen_NpixelTracks",&Gen_NpixelTracks);
    gentree->SetBranchAddress("Gen_Ntracks",&Gen_Ntracks);
    gentree->SetBranchAddress("Gen_SumET_HF",&Gen_SumET_HF);
    gentree->SetBranchAddress("Gen_SumET_HFplus",&Gen_SumET_HFplus);
    gentree->SetBranchAddress("Gen_SumET_HFminus",&Gen_SumET_HFminus);
    gentree->SetBranchAddress("Gen_SumET_HFplusEta4",&Gen_SumET_HFplusEta4);
    gentree->SetBranchAddress("Gen_SumET_HFminusEta4",&Gen_SumET_HFminusEta4);
    gentree->SetBranchAddress("Gen_SumET_ET",&Gen_SumET_ET);
    gentree->SetBranchAddress("Gen_SumET_EE",&Gen_SumET_EE);
    gentree->SetBranchAddress("Gen_SumET_EB",&Gen_SumET_EB);
    gentree->SetBranchAddress("Gen_SumET_EEplus",&Gen_SumET_EEplus);
    gentree->SetBranchAddress("Gen_SumET_EEminus",&Gen_SumET_EEminus);
    gentree->SetBranchAddress("Gen_SumET_ZDC",&Gen_SumET_ZDC);
    gentree->SetBranchAddress("Gen_SumET_ZDCplus",&Gen_SumET_ZDCplus);
    gentree->SetBranchAddress("Gen_SumET_ZDCminus",&Gen_SumET_ZDCminus);



    //if(isParent ==1){
    gentree->SetBranchAddress("GenJpsiMassP",   &GenJpsiMassP);
    gentree->SetBranchAddress("GenJpsiPtP",     &GenJpsiPtP);
    gentree->SetBranchAddress("GenJpsiRapP",    &GenJpsiRapP);
    gentree->SetBranchAddress("GenJpsiPxP",     &GenJpsiPxP);
    gentree->SetBranchAddress("GenJpsiPyP",     &GenJpsiPyP);
    gentree->SetBranchAddress("GenJpsiPzP",     &GenJpsiPzP);
      //}
    
    
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
    gentree->SetBranchAddress("GenmuPosEta",   &GenmuPosEta);
    gentree->SetBranchAddress("GenmuPosPhi",   &GenmuPosPhi);

    gentree->SetBranchAddress("GenmuNegPx",    &GenmuNegPx);
    gentree->SetBranchAddress("GenmuNegPy",    &GenmuNegPy);
    gentree->SetBranchAddress("GenmuNegPz",    &GenmuNegPz);
    gentree->SetBranchAddress("GenmuNegEta",   &GenmuNegEta);
    gentree->SetBranchAddress("GenmuNegPhi",   &GenmuNegPhi);    

    //======================================= Gen tree loop ================================================
    Int_t NAccep=0;
    Int_t nGenEntries=gentree->GetEntries();
    cout<<" Total Entries in GenLevel Tree for pT range: "<<fileName[ifile]<<"  "<<   nGenEntries<< " ========="<<endl;
    //dataFile<<" Total Entries in GenLevel Tree for pT range: "<<fileName[ifile]<<"  "<<   nGenEntries<< " ====="<<endl;
    
    
    // ===================== NTrks and SumHF ETs ==================================== //

    double pp276_MeanNTrk = 10.10;
    double pp276_MeanHFETEta4 = 4.77;

    

    for(Int_t i=0; i< nGenEntries; i++)  {	    
      gentree->GetEntry(i);
      
      if(isParent==1){
	GenJpsiMass=GenJpsiMassP; 
	GenJpsiPt=GenJpsiPtP;
	GenJpsiRap=GenJpsiRapP;
	GenJpsiPx=GenJpsiPxP;
	GenJpsiPy=GenJpsiPyP;
	GenJpsiPz=GenJpsiPzP;
      }
      
 
      double GenSumHFETEta4=0; double Norm_GenSumHFETEta4 =0; double Norm_GenNTrks=0; 
      
      GenSumHFETEta4=Gen_SumET_HFplusEta4+Gen_SumET_HFminusEta4;
    
      //Norm_GenSumHFETEta4 = (GenSumHFETEta4/pp276_MeanHFETEta4);
      //Norm_GenNTrks=(Gen_Ntracks/pp276_MeanNTrk);

      Norm_GenSumHFETEta4 = GenSumHFETEta4;
      Norm_GenNTrks= Gen_Ntracks;
      
 
      NTrk->Fill(Gen_Ntracks);
      AvHF_ET_Eta4->Fill(GenSumHFETEta4);


      if(i%100000==0){
	cout<<" processing record "<<i<<" Mass "<< GenJpsiMass << " pT "<< GenJpsiPt << " Y " <<GenJpsiRap<<endl; 
      }
      
      Bool_t GenPosIn=0, GenNegIn=0,GenPosPass=0,GenNegPass=0;
      
      GenmuPosPt= TMath::Sqrt(GenmuPosPx*GenmuPosPx + GenmuPosPy*GenmuPosPy); 
      GenmuNegPt= TMath::Sqrt(GenmuNegPx*GenmuNegPx + GenmuNegPy*GenmuNegPy); 
      
           
      //p+Pb acceptance
      if(IsPPb ==1 && IsAccept(GenmuPosPt, GenmuPosEta)) {GenPosIn=1;}
      if(IsPPb ==1 && IsAccept(GenmuNegPt, GenmuNegEta)) {GenNegIn=1;}


      //p+p acceptance
      if(IsPP ==1 && IsAccept_PP(GenmuPosPt, GenmuPosEta)) {GenPosIn=1;}
      if(IsPP ==1 && IsAccept_PP(GenmuNegPt, GenmuNegEta)) {GenNegIn=1;}
      
      
     
      
      if(GenPosIn==1 && GenmuPosPt> PtCut) {GenPosPass=1;}
      if(GenNegIn==1 && GenmuNegPt> PtCut) {GenNegPass=1;}
      
      if(GenPosPass && GenNegPass ) NAccep++;
       
      Bin_Gen->Fill(gbin);
      diMuonsInvMass_Gen->Fill(GenJpsiMass);
      
      if(GenPosPass==1 && GenNegPass==1){ 
	diMuonsPt_Gen->Fill(GenJpsiPt);
	diMuonsRap_Gen->Fill(GenJpsiRap);
      }
      
      

      if(GenPosPass==1 && GenNegPass==1 ){
	

	MuonPt_Gen->Fill(GenmuPosPt);
	MuonPt_Gen->Fill(GenmuNegPt);

	MuonEta_Gen->Fill(GenmuPosEta);
	MuonEta_Gen->Fill(GenmuNegEta);
	
	MuonPhi_Gen->Fill(GenmuPosPhi);
	MuonPhi_Gen->Fill(GenmuNegPhi);

	MuonEtaPhi_Gen->Fill(GenmuPosEta,GenmuPosPhi);
	MuonEtaPhi_Gen->Fill(GenmuNegEta,GenmuNegPhi);

      }


      if(GenPosIn && GenNegIn){
	if(ifile==0){diMuonsRap_Gen0->Fill(GenJpsiRap);}
	if(ifile==1){diMuonsRap_Gen1->Fill(GenJpsiRap);}
	if(ifile==2){diMuonsRap_Gen2->Fill(GenJpsiRap);}
	if(ifile==3){diMuonsRap_Gen3->Fill(GenJpsiRap);}
	if(ifile==4){diMuonsRap_Gen4->Fill(GenJpsiRap);}
	if(ifile==5){diMuonsRap_Gen5->Fill(GenJpsiRap);}
      }

      if( (GenPosPass==1 && GenNegPass==1) && (GenJpsiRap > DiMuRapMin && GenJpsiRap < DiMuRapMax)  ) {diMuonsPtB_Gen->Fill(GenJpsiPt);}
      if( (GenPosPass==1 && GenNegPass==1) && (GenJpsiRapP > DiMuRapMin && GenJpsiRapP < DiMuRapMax)) {UpsilonPtB_Gen->Fill(GenJpsiPtP);}
      
      
      for (Int_t ih = 0; ih < Nptbin; ih++) {
	
	//adding pT of all pt bins to see diss is cont
	if(iSpec == 1)  if( (GenPosPass==1 && GenNegPass==1) && ( GenJpsiRap > DiMuRapMin && GenJpsiRap < DiMuRapMax ) && (GenJpsiPt>pt_bound[ih] && GenJpsiPt<=pt_bound[ih+1]))
			  {diMuonsPt_GenA[ifile][ih]->Fill(GenJpsiPt);}
	
	
	if(iSpec == 1) if( (GenPosPass==1 && GenNegPass==1) && ( GenJpsiRap > DiMuRapMin && GenJpsiRap < DiMuRapMax )
			   &&(GenJpsiPt>pt_bound[ih] && GenJpsiPt<=pt_bound[ih+1])) {diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass);}

	
	//for non symetric plots
	if(iSpec == 2)  if( (GenPosPass==1 && GenNegPass==1) &&  (GenJpsiPt> 0.0 && GenJpsiRap > DiMuRapMin && GenJpsiRap < DiMuRapMax ) 
			    && ((GenJpsiRap) > pt_bound[ih] && (GenJpsiRap) <=pt_bound[ih+1] )){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass);}
	
	if(iSpec == 3)  if( (GenPosPass==1 && GenNegPass==1) && (GenJpsiPt > 0.0 && GenJpsiRap > DiMuRapMin && GenJpsiRap < DiMuRapMax ) 
			    && (  Norm_GenNTrks >= pt_bound[ih] &&  Norm_GenNTrks < pt_bound[ih+1])) {diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass);}
	
	
	if(iSpec == 4)  if( (GenPosPass==1 && GenNegPass==1) && (GenJpsiPt > 0.0 && GenJpsiRap > DiMuRapMin && GenJpsiRap < DiMuRapMax ) 
			    && (Norm_GenSumHFETEta4 >= pt_bound[ih] && Norm_GenSumHFETEta4 < pt_bound[ih+1])) {diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass);}
	
      



      }
    }//gen loop end
    
    cout<<" accepted no "<< NAccep<<endl;
    
    RatioFSR_Pt=(TH1D*)UpsilonPtB_Gen->Clone("RatioFSR_Pt");
    RatioFSR_Pt->Divide(diMuonsPtB_Gen);
  

    /*
      new TCanvas;
      diMuonsInvMass_Gen->Draw();
      gPad->Print("plots/diMuonsInvMass_Gen.png");
    

      new TCanvas;
      diMuonsPtB_Gen->Draw();
    

      new TCanvas;
      UpsilonPtB_Gen->Draw();
    
      
    
    new TCanvas;
    RatioFSR_Pt->Draw();
    */
      
    //=============== Rec Tree Loop ============================================================================//
    
    Int_t nRecEntries=tree->GetEntries();
    cout<<"Total Entries in reconstructed Tree for pT range "<<fileName[ifile]<<"  "<<nRecEntries<< "====="<<endl;
    
    for(Int_t i=0; i<nRecEntries; i++)  {	    
      tree->GetEntry(i);
      
      if(i%50000==0){
	cout<<" processing record "<<i<<" processing Run  " <<runNb <<" event "<<eventNb<<" lum block "<<lumiBlock<<endl;    
	
      }
    
      // ====================== Centrality Variables =============================================================//
      double SumHFETEta4=0; double Norm_SumHFETEta4 =0; double Norm_NTrks=0; 

      SumHFETEta4=SumET_HFplusEta4+SumET_HFminusEta4;
      

      //Norm_SumHFETEta4 = (SumHFETEta4/pp276_MeanHFETEta4);
      //Norm_NTrks=(Ntracks/pp276_MeanNTrk);
      
      Norm_SumHFETEta4 = SumHFETEta4;
      Norm_NTrks= Ntracks;
      
      muPosPt= TMath::Sqrt(muPosPx*muPosPx + muPosPy*muPosPy); 
      muNegPt= TMath::Sqrt(muNegPx*muNegPx + muNegPy*muNegPy); 
            
      Bool_t PosPass=0, NegPass=0, AllCut=0 ,PosIn=0, NegIn=0;
      Bool_t NoTrigger=0, NoID=0, NoCut=0;
      
      //p+Pb acceptance
      if(IsPPb ==1 && IsAccept(muPosPt, muPosEta)){PosIn=1;}
      if(IsPPb ==1 && IsAccept(muNegPt, muNegEta)){NegIn=1;}

      //p+p acceptance
      if(IsPP ==1 && IsAccept_PP(muPosPt, muPosEta)){PosIn=1;}
      if(IsPP ==1 && IsAccept_PP(muNegPt, muNegEta)){NegIn=1;}
      



      if( muPos_trackerLayers > 5.0 && muPos_pixeLayers > 1 && TMath::Abs(muPos_nchi2In) < 1.8 && TMath::Abs(muPos_dxy) < 3.0 && TMath::Abs(muPos_dz) < 30.0 
	  &&  muPos_arbitrated==1 && muPos_stationTight==1 && muPos_tracker==1 ){PosPass=1;}	  
      if( muNeg_trackerLayers > 5.0 && muNeg_pixeLayers >1 && TMath::Abs(muNeg_nchi2In) < 1.8 && TMath::Abs(muNeg_dxy) < 3.0 && TMath::Abs(muNeg_dz) < 30.0 
	  &&  muNeg_arbitrated==1 && muNeg_stationTight==1 && muNeg_tracker==1 ){NegPass=1;}	  
      

      //all cut
      if((muPosPt > PtCut && muNegPt > PtCut) && (muPos_Trigger1==1 && muNeg_Trigger1==1) && (PosIn==1 && NegIn==1) && (PosPass==1 && NegPass==1)){AllCut=1;}
 
      //without trigger
      if( (muPosPt > PtCut && muNegPt > PtCut) &&  (PosIn==1 && NegIn==1 )  &&   (PosPass==1 && NegPass==1) ){NoTrigger=1;}

      //without muon ID cut
      if((muPosPt > PtCut && muNegPt > PtCut) && (muPos_Trigger2==1 && muNeg_Trigger2==1) && (PosIn==1 && NegIn==1)){NoID=1;}
 
      //Without any cut
      if((muPosPt > PtCut && muNegPt > PtCut) && (PosIn==1 && NegIn==1) ) {NoCut=1;}
      
      
      Bin_Rec->Fill(rbin);
      
      
      if(AllCut==1){
	if(ifile==0){diMuonsRap_Rec0->Fill(JpsiRap);}
	if(ifile==1){diMuonsRap_Rec1->Fill(JpsiRap);}
	if(ifile==2){diMuonsRap_Rec2->Fill(JpsiRap);}
	if(ifile==3){diMuonsRap_Rec3->Fill(JpsiRap);}
	if(ifile==4){diMuonsRap_Rec4->Fill(JpsiRap);}
	if(ifile==5){diMuonsRap_Rec5->Fill(JpsiRap);}
      }

    
      
      if( (muPosPt > PtCut && muNegPt > PtCut) && (PosIn==1 && NegIn==1) && (PosPass==1 && NegPass==1)){
	diMuonsPt_rec->Fill(JpsiPt);
	diMuonsRap_rec->Fill(JpsiRap);
      }


      if(NoTrigger==1){
	
	MuonPt_Rec->Fill(muPosPt);
	MuonPt_Rec->Fill(muNegPt);
	
	MuonEta_Rec->Fill(muPosEta);
	MuonEta_Rec->Fill(muNegEta);
	
	MuonPhi_Rec->Fill(muPosPhi);
	MuonPhi_Rec->Fill(muNegPhi);
	
	MuonEtaPhi_Rec->Fill(muPosEta,muPosPhi);
	MuonEtaPhi_Rec->Fill(muNegEta,muNegPhi);
      }




      //Eff loop for reco
      if((JpsiCharge == 0) && (JpsiVprob > 0.01)) {
	
	for (Int_t ih = 0; ih < Nptbin; ih++) {
	  

	  //to see cont reco pT
	  if(iSpec == 1)if((AllCut==1) && (JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax ) && (JpsiPt>pt_bound[ih] && JpsiPt<=pt_bound[ih+1]))
			  {diMuonsPt_RecA[ifile][ih]->Fill(JpsiPt);}
	  
	 

	  //start efficiency

	  //all cuts
	  if(iSpec == 1)if((AllCut==1) && (JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax) && (JpsiPt > pt_bound[ih] && JpsiPt <=pt_bound[ih+1]))
			  {diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass);}
	  
	  //no trigger
	  if(iSpec == 1)if( (NoTrigger==1) && (JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax) && (JpsiPt > pt_bound[ih] && JpsiPt <=pt_bound[ih+1]))
			  {diMuonsInvMass_RecA_NoTrg[ifile][ih]->Fill(JpsiMass);}

	  //No ID
	  if(iSpec == 1)if( (NoID==1) && (JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax) && (JpsiPt > pt_bound[ih] && JpsiPt <=pt_bound[ih+1]))
			  {diMuonsInvMass_RecA_NoID[ifile][ih]->Fill(JpsiMass);}

	  //No Cut
	  if(iSpec == 1)if( (NoCut==1) && (JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax) && (JpsiPt > pt_bound[ih] && JpsiPt <=pt_bound[ih+1]))
			  {diMuonsInvMass_RecA_NoCut[ifile][ih]->Fill(JpsiMass);}
	  



	  //All Cuts
	  if(iSpec == 2) if( (AllCut==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax ) 
			     && ((JpsiRap) > pt_bound[ih] && (JpsiRap) <=pt_bound[ih+1])) {diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass);}
	  //No Trigger
	  if(iSpec == 2) if( (NoTrigger==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax ) 
			     && ((JpsiRap) > pt_bound[ih] && (JpsiRap) <=pt_bound[ih+1])) {diMuonsInvMass_RecA_NoTrg[ifile][ih]->Fill(JpsiMass);}

	  //No ID
	  if(iSpec == 2) if( (NoID==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax ) 
			     && ((JpsiRap) > pt_bound[ih] && (JpsiRap) <=pt_bound[ih+1])) {diMuonsInvMass_RecA_NoID[ifile][ih]->Fill(JpsiMass);}
	  //No Cut
	  if(iSpec == 2) if( (NoCut==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax ) 
			     && ((JpsiRap) > pt_bound[ih] && (JpsiRap) <=pt_bound[ih+1])) {diMuonsInvMass_RecA_NoCut[ifile][ih]->Fill(JpsiMass);}
	      
	


	  //All Cuts
	  if(iSpec == 3) if( (AllCut==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax) && (Norm_NTrks >=pt_bound[ih] && Norm_NTrks < pt_bound[ih+1]  )) 
			   {diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass);}
	  
	  //No Trigger
	  if(iSpec == 3) if( (NoTrigger==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax ) 
			     && (Norm_NTrks >=pt_bound[ih] && Norm_NTrks < pt_bound[ih+1]  )  ) {diMuonsInvMass_RecA_NoTrg[ifile][ih]->Fill(JpsiMass);}

	  //No ID
	  if(iSpec == 3) if( (NoID==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax ) 
			     && (Norm_NTrks >=pt_bound[ih] && Norm_NTrks < pt_bound[ih+1]) ) {diMuonsInvMass_RecA_NoID[ifile][ih]->Fill(JpsiMass);}
	  //No Cut
	  if(iSpec == 3) if( (NoCut==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax ) 
			     && (Norm_NTrks >=pt_bound[ih] && Norm_NTrks < pt_bound[ih+1])  ) {diMuonsInvMass_RecA_NoCut[ifile][ih]->Fill(JpsiMass);}



	  //All Cuts
	  if(iSpec == 4) if( (AllCut==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax)
			     && (Norm_SumHFETEta4 >=pt_bound[ih] && Norm_SumHFETEta4 < pt_bound[ih+1]  ))  {diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass);}
	  
	  //No Trigger
	  if(iSpec == 4) if( (NoTrigger==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax ) 
			     && (Norm_SumHFETEta4 >=pt_bound[ih] && Norm_SumHFETEta4 < pt_bound[ih+1]  )  ) {diMuonsInvMass_RecA_NoTrg[ifile][ih]->Fill(JpsiMass);}

	  //No ID
	  if(iSpec == 4) if( (NoID==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax ) 
			     && ( Norm_SumHFETEta4 >=pt_bound[ih] && Norm_SumHFETEta4 < pt_bound[ih+1]) ) {diMuonsInvMass_RecA_NoID[ifile][ih]->Fill(JpsiMass);}
	  //No Cut
	  if(iSpec == 4) if( (NoCut==1) &&  (JpsiPt>0.0 && JpsiRap > DiMuRapMin && JpsiRap < DiMuRapMax ) 
			     && (Norm_SumHFETEta4  >=pt_bound[ih] && Norm_SumHFETEta4 < pt_bound[ih+1])  ) {diMuonsInvMass_RecA_NoCut[ifile][ih]->Fill(JpsiMass);}

	}//bins
	
      }//jpsi charge and vtx prob
    

    }//rec entry loop    
  }  // file loop ends 
  
  ///////////////////////////////////////////////////////////////////

  cout<< " adding "<<endl;
  TH1D *diMuonsInvMass_RecA1[100];
  TH1D *diMuonsInvMass_GenA1[100];
  

  TH1D *diMuonsPt_GenA1[100];
  TH1D *diMuonsPt_RecA1[100];
  TF1 *backfun_1;
  char namePt_1B[500];//for bkg func
 
  TH1D *diMuonsInvMass_RecA1_NoTrg[100];
  TH1D *diMuonsInvMass_RecA1_NoID[100];
  TH1D *diMuonsInvMass_RecA1_NoCut[100];

  for(Int_t ih = 0; ih < Nptbin; ih++){
    diMuonsInvMass_RecA1[ih] = diMuonsInvMass_RecA[0][ih];
    diMuonsInvMass_GenA1[ih] = diMuonsInvMass_GenA[0][ih];
    
    diMuonsInvMass_RecA1_NoTrg[ih] =diMuonsInvMass_RecA_NoTrg[0][ih];
    diMuonsInvMass_RecA1_NoID[ih] =diMuonsInvMass_RecA_NoID[0][ih];
    diMuonsInvMass_RecA1_NoCut[ih] =diMuonsInvMass_RecA_NoCut[0][ih];
    
    diMuonsPt_GenA1[ih] = diMuonsPt_GenA[0][ih];
    diMuonsPt_RecA1[ih] = diMuonsPt_RecA[0][ih];
    
  }
  
  //===========================Fitting===================================================================//
  // Fit ranges
  Double_t mass_low, mass_high;
  Double_t MassUpsilon, WeidthUpsilon;
  
  // Low mass range upsilon width 54 KeV
  
  if(Y1s==1){MassUpsilon = 9.46; WeidthUpsilon = 0.09; mass_low = 8.0; mass_high = 10.5;}  // Fit ranges
  
  if(Y2s==1){MassUpsilon = 10.05; WeidthUpsilon = 0.09; mass_low = 9.0; mass_high = 11.0;}  // Fit ranges

   if(Y3s==1){MassUpsilon = 10.355; WeidthUpsilon = 0.09; mass_low = 9.0; mass_high = 12.0;}  // Fit ranges
  // Fit Function crystall ball
  TF1 *GAUSPOL = new TF1("GAUSPOL",CBPol1,8.0,12.0,8);
  GAUSPOL->SetParNames("Yield (#varUpsilon)","BinWidth","Mean","Sigma","#alpha","n");
  
  /*GAUSPOL->SetParameter(2, MassUpsilon);
  GAUSPOL->SetParameter(3, WeidthUpsilon);
  GAUSPOL->SetParLimits(3, 0.1*WeidthUpsilon,4.0*WeidthUpsilon);
  GAUSPOL->SetParameter(4, 1.0);
  GAUSPOL->SetParameter(5, 2.0);
  GAUSPOL->SetLineWidth(2.0);*/
 

  GAUSPOL->SetParameter(2, MassUpsilon);
  GAUSPOL->SetParLimits(2, 8.5,10.5);  

  GAUSPOL->SetParameter(3, WeidthUpsilon);
  GAUSPOL->SetParLimits(3, 0.1*WeidthUpsilon,5.0*WeidthUpsilon);
  
  GAUSPOL->SetParameter(4, 1.67);//1.0
  //GAUSPOL->SetParameter(5, 3.0);//2.0
  //GAUSPOL->FixParameter(4, 1.67);//1.0
  GAUSPOL->FixParameter(5, 2.3);//2.0



 
  if(Y1s==1) GAUSPOL->SetLineColor(2);
  if(Y2s==1) GAUSPOL->SetLineColor(1);
  if(Y3s==1) GAUSPOL->SetLineColor(4);
  

  //=====================Loop for eff=========================================================
  char PlotName[500],PlotName1[500], PlotName2[500]; 
  char GPlotName[500],GPlotName1[500], GPlotName2[500];


 

  TCanvas *CanCentR = new TCanvas("CanCentR","CanCentR",20,20,1200,950);
  CanCentR->Divide(2,5);


  TCanvas *CanCentG = new TCanvas("CanCentG","CanCentG",20,20,1200,950);
  CanCentG->Divide(2,5);



  char Spectra[100];
  if(iSpec==1) sprintf(Spectra,"Pt");
  if(iSpec==2) sprintf(Spectra,"Rap");
  if(iSpec==3) sprintf(Spectra,"NTrk");
  if(iSpec==4) sprintf(Spectra,"HFET");

  //if(Y1s==1) dataFile<<"Y(1s) PP Efficiency "<<Spectra<<" ========= "<<endl;
  //if(Y2s==1) dataFile<<"Y(2s) PP Efficiency "<<Spectra<<" ========= "<<endl;
  //if(Y3s==1) dataFile<<"Y(3s) PP Efficiency "<<Spectra<<" ========= "<<endl;


for (Int_t ih = 0; ih < Nptbin; ih++) {
  
  CanCentR->cd(ih+1);
  
  
  cout<<" no of gen dimuons from diMuons Pt histo    "<<diMuonsPt_GenA1[ih]->Integral(1,100)<<endl;
  cout<<" no of gen dimuons from diMuons Mass histo  "<<diMuonsInvMass_GenA1[ih]->Integral(1,100)<<endl;
    

    //from pT histogram
    //gen_pt[ih] =diMuonsPt_GenA1[ih]->IntegralAndError(1,100,genError);
   
    gen_pt[ih] = diMuonsInvMass_GenA1[ih]->IntegralAndError(1,100,genError);
    gen_ptError[ih]= genError;
    
    if(iSpec==1) sprintf(PlotName,"plots/DiMuonMass_PtBin_%d.png",ih);
    if(iSpec==2) sprintf(PlotName,"plots/DiMuonMass_RapBin_%d.png",ih);
    if(iSpec==3) sprintf(PlotName,"plots/DiMuonMass_NTrkBin_%d.png",ih);
    if(iSpec==4) sprintf(PlotName,"plots/DiMuonMass_HFETBin_%d.png",ih);
    
    if(iSpec==1) sprintf(PlotName1,"plots/DiMuonMass_PtBin_%d.pdf",ih);
    if(iSpec==2) sprintf(PlotName1,"plots/DiMuonMass_RapBin_%d.pdf",ih);
    if(iSpec==3) sprintf(PlotName1,"plots/DiMuonMass_NTrkBin_%d.pdf",ih);
    if(iSpec==4) sprintf(PlotName1,"plots/DiMuonMass_HFETBin_%d.pdf",ih);
    
    if(iSpec==1) sprintf(PlotName2,"plots/DiMuonMass_PtBin_%d.eps",ih);
    if(iSpec==2) sprintf(PlotName2,"plots/DiMuonMass_RapBin_%d.eps",ih);
    if(iSpec==3) sprintf(PlotName2,"plots/DiMuonMass_NTrkBin_%d.eps",ih);
    if(iSpec==4) sprintf(PlotName2,"plots/DiMuonMass_HFETBin_%d.eps",ih);
 


    //giving inetial value for crystall ball fourth parameter 
    diMuonsInvMass_RecA1[ih]->Rebin(2);

    diMuonsInvMass_RecA1_NoTrg[ih]->Rebin(2);
    diMuonsInvMass_RecA1_NoID[ih]->Rebin(2);
    diMuonsInvMass_RecA1_NoCut[ih]->Rebin(2);


    //GAUSPOL->SetParameter(0, diMuonsInvMass_RecA1[ih]->GetMaximum());
    GAUSPOL->SetParameter(0, diMuonsInvMass_RecA1[ih]->Integral(0,50));
    GAUSPOL->FixParameter(1, diMuonsInvMass_RecA1[ih]->GetBinWidth(1));
    
    //new TCanvas; 
    diMuonsInvMass_RecA1[ih]->Fit("GAUSPOL","LLMERQ", "", mass_low, mass_high);
    
    Double_t UpsilonMass = GAUSPOL->GetParameter(2);
    Double_t UpsilonWidth = GAUSPOL->GetParameter(3);
    
    Double_t UpsilonYield = GAUSPOL->GetParameter(0);
    
    Double_t UpsilonYieldError = GAUSPOL->GetParError(0);

    Double_t par[20];
    GAUSPOL->GetParameters(par);
    sprintf(namePt_1B,"pt_1B_%d",ih);
    backfun_1 = new TF1(namePt_1B, Pol1, mass_low, mass_high, 2);
    backfun_1->SetParameters(&par[6]);
    
    diMuonsInvMass_RecA1[ih]->Draw();
    backfun_1->Draw("same");

    Double_t MassLow,MassHigh;

    //Double_t MassLow=(UpsilonMass-3*UpsilonWidth);
    //Double_t MassHigh=(UpsilonMass+3*UpsilonWidth);
    

    if(Y1s==1){MassLow=9.0; MassHigh=10.0;}
    if(Y2s==1){MassLow=9.5; MassHigh=10.5;}
    if(Y3s==1){MassLow=9.8; MassHigh=10.8;}


    Int_t binlow =diMuonsInvMass_RecA1[ih]->GetXaxis()->FindBin(MassLow);
    Int_t binhi =diMuonsInvMass_RecA1[ih]->GetXaxis()->FindBin(MassHigh);
    Double_t binwidth=diMuonsInvMass_RecA1[ih]->GetBinWidth(1);
        
  
    cout<<"Rec diMuons from Pt histo "<<diMuonsPt_RecA1[ih]->Integral(1,100)<<endl;  
    cout<<"Rec dimuons from mass "<<diMuonsInvMass_RecA1[ih]->Integral(1,100)<<endl; 
    
    //from pT histo
    //rec_pt[ih]=diMuonsPt_RecA1[ih]->IntegralAndError(1, 100,recError);
    
    //yield by function 
    //rec_pt[ih] = UpsilonYield;
    //rec_ptError[ih]=UpsilonYieldError;


    //yield by histogram integral
    rec_pt[ih] = diMuonsInvMass_RecA1[ih]->IntegralAndError(binlow, binhi,recError);
    rec_ptError[ih]= recError;
   
    Yield_NoTrg[ih]=diMuonsInvMass_RecA1_NoTrg[ih]->IntegralAndError(binlow, binhi,recError_NoTrg);
    errYield_NoTrg[ih]=recError_NoTrg;

    Yield_NoID[ih]=diMuonsInvMass_RecA1_NoID[ih]->IntegralAndError(binlow, binhi,recError_NoID);
    errYield_NoID[ih]=recError_NoID;
    
    Yield_NoCut[ih]=diMuonsInvMass_RecA1_NoCut[ih]->IntegralAndError(binlow, binhi,recError_NoCut);
    errYield_NoCut[ih]=recError_NoCut;
    
    //dataFile<<(backfun_1->Integral(9,10)/diMuonsInvMass_RecA1[ih]->GetBinWidth(1)/rec_pt[ih])*100<<" % "<<endl;

    //Cal eff 
    Eff_cat_1[ih] = rec_pt[ih]/gen_pt[ih]; 
    Err_Eff_cat_1[ih]=RError(rec_pt[ih], rec_ptError[ih], gen_pt[ih], gen_ptError[ih]);
    
    Eff_Trigger[ih]=rec_pt[ih]/Yield_NoTrg[ih];
    errEff_Trigger[ih]=RError(rec_pt[ih], rec_ptError[ih],Yield_NoTrg[ih],errYield_NoTrg[ih]);

    Eff_MuID[ih]=rec_pt[ih]/Yield_NoID[ih];
    errEff_MuID[ih]=RError(rec_pt[ih], rec_ptError[ih],Yield_NoID[ih],errYield_NoID[ih]);


    Eff_Reco[ih]=Yield_NoCut[ih]/gen_pt[ih];
    errEff_Reco[ih]=RError(Yield_NoCut[ih], errYield_NoCut[ih], gen_pt[ih], gen_ptError[ih]);


    cout<<"Upsilon Yield by integral of histo:  "<< diMuonsInvMass_RecA1[ih]->IntegralAndError(binlow, binhi,recError) <<"  error "<< rec_ptError[ih]<<endl; 
    cout<<"UpsilonYield by CB    yield det:     "<< UpsilonYield <<" /pm  "<<UpsilonYieldError<<" UpsilonWidth "<< UpsilonWidth<<" UpsilonMass "<<UpsilonMass <<endl;
    

    cout<<"Upsilon Yield by Function integral:  "<< GAUSPOL->Integral(MassLow,MassHigh)/binwidth <<endl;
    cout<<" rec_pt[ih]  "<<  rec_pt[ih] <<" gen_pt[ih] "<<gen_pt[ih]<<endl;
    cout<<" eff "<< Eff_cat_1[ih]<<" error "<<Err_Eff_cat_1[ih]<<endl;
   

   
    if(iSpec==1 && Y1s==1)
      {
	Y1SEff_Pt[ih]=Eff_cat_1[ih];
	errY1SEff_Pt[ih]=Err_Eff_cat_1[ih];
      }

    if(iSpec==1 && Y2s==1)
      {
	Y2SEff_Pt[ih]=Eff_cat_1[ih];
	errY2SEff_Pt[ih]=Err_Eff_cat_1[ih];
      }

    if(iSpec==1 && Y3s==1)
      {
	Y3SEff_Pt[ih]=Eff_cat_1[ih];
	errY3SEff_Pt[ih]=Err_Eff_cat_1[ih];
      }


    if(iSpec==2 && Y1s==1)
      {
	Y1SEff_Rap[ih]=Eff_cat_1[ih];
	errY1SEff_Rap[ih]=Err_Eff_cat_1[ih];
      }

    
    if(iSpec==2 && Y2s==1)
      {
	Y2SEff_Rap[ih]=Eff_cat_1[ih];
	errY2SEff_Rap[ih]=Err_Eff_cat_1[ih];
      }


    if(iSpec==2 && Y3s==1)
      {
	Y3SEff_Rap[ih]=Eff_cat_1[ih];
	errY3SEff_Rap[ih]=Err_Eff_cat_1[ih];
      }



    if(iSpec==3 && Y1s==1)
      {
	Y1SEff_NTrk[ih]=Eff_cat_1[ih];
	errY1SEff_NTrk[ih]=Err_Eff_cat_1[ih];
      }
    
    
    if(iSpec==3 && Y2s==1)
      {
	Y2SEff_NTrk[ih]=Eff_cat_1[ih];
	errY2SEff_NTrk[ih]=Err_Eff_cat_1[ih];
      }
    
    
    if(iSpec==3 && Y3s==1)
      {
	Y3SEff_NTrk[ih]=Eff_cat_1[ih];
	errY3SEff_NTrk[ih]=Err_Eff_cat_1[ih];
      }


    if(iSpec==4 && Y1s==1)
      {
	Y1SEff_HFET[ih]=Eff_cat_1[ih];
	errY1SEff_HFET[ih]=Err_Eff_cat_1[ih];
      }
    
    
    if(iSpec==4 && Y2s==1)
      {
	Y2SEff_HFET[ih]=Eff_cat_1[ih];
	errY2SEff_HFET[ih]=Err_Eff_cat_1[ih];
      }
    
    
    if(iSpec== 4 && Y3s==1)
      {
	Y3SEff_HFET[ih]=Eff_cat_1[ih];
	errY3SEff_HFET[ih]=Err_Eff_cat_1[ih];
      }



    if(iSpec==1) sprintf(GPlotName,"plots/GenDiMuonMass_PtBin_%d.png",ih);
    if(iSpec==2) sprintf(GPlotName,"plots/GenDiMuonMass_RapBin_%d.png",ih);
    if(iSpec==3) sprintf(GPlotName,"plots/GenDiMuonMass_NTrkBin_%d.png",ih);
    if(iSpec==4) sprintf(GPlotName,"plots/GenDiMuonMass_HFETBin_%d.png",ih);
    
    if(iSpec==1) sprintf(GPlotName1,"plots/GenDiMuonMass_PtBin_%d.pdf",ih);
    if(iSpec==2) sprintf(GPlotName1,"plots/GenDiMuonMass_RapBin_%d.pdf",ih);
    if(iSpec==3) sprintf(GPlotName1,"plots/GenDiMuonMass_NTrkBin_%d.pdf",ih);
    if(iSpec==4) sprintf(GPlotName1,"plots/GenDiMuonMass_HFETBin_%d.pdf",ih);
    
    if(iSpec==1) sprintf(GPlotName2,"plots/GenDiMuonMass_PtBin_%d.eps",ih);
    if(iSpec==2) sprintf(GPlotName2,"plots/GenDiMuonMass_RapBin_%d.eps",ih);
    if(iSpec==3) sprintf(GPlotName2,"plots/GenDiMuonMass_NTrkBin_%d.eps",ih);
    if(iSpec==4) sprintf(GPlotName2,"plots/GenDiMuonMass_HFETBin_%d.eps",ih);
       

    backfun_1->SetLineColor(4);
    backfun_1->SetLineWidth(1);
    //backfun_1->Draw("same");
    gPad->Print(PlotName);
    gPad->Print(PlotName1);
    gPad->Print(PlotName2);

    CanCentG->cd(ih+1);
    //new TCanvas;
    diMuonsInvMass_GenA1[ih]->Draw();
    gPad->Print(GPlotName);
    gPad->Print(GPlotName1);
    gPad->Print(GPlotName2);

   //new TCanvas;
    //diMuonsPt_GenA1[ih]->Draw();
    //new TCanvas;
    //diMuonsPt_RecA1[ih]->Draw();
 
 }//efficiency bins



  
 cout<<"Y1S:  "<<" Y2S: "<<" Y3S: "<<endl;
 
 

if(iSpec==1 && Y3s==1){
 
  dataFile<<Str3<<"begin{table}[htbH]"<<endl;
  dataFile<<Str3<<"begin{center}"<<endl;
  dataFile<<Str3<<"caption{}"<<endl; 
  dataFile<<Str3<<"label{}"<<endl;
  dataFile<<Str3<<"begin{tabular}{c|c|c|c|c}"<<endl;
  dataFile<<Str1<<endl;
  dataFile<<" pT  "<< "      &y  " << "&$\\Upsilon$(1S) "<< "&$\\Upsilon$(2S) "<<"&$\\Upsilon$(3S) "<<Str2<<endl;
  dataFile<<Str1<<endl;

for(Int_t ih = 0; ih < Nptbin; ih++)
   {


     cout<<"$["<<pt_bound[ih] <<","<<pt_bound[ih+1]<<"]$ & $["<<ymin<<","<<ymax<<"]$ "<<setprecision(3)<<
     Y1SEff_Pt[ih]<<"  pm "<<setprecision(3)<<errY1SEff_Pt[ih]<<"     "<<setprecision(3)<<Y2SEff_Pt[ih]
     	 <<"  pm "<<setprecision(3)<<errY2SEff_Pt[ih]
     	 <<setprecision(3)<< "  "<<Y3SEff_Pt[ih]<<"  pm "<<setprecision(3)<<errY3SEff_Pt[ih]<<endl; 


     dataFile<<"$["<<pt_bound[ih] <<","<<pt_bound[ih+1]<<"]$ & $["<<ymin<<","<<ymax<<"]$ &"<<setprecision(3)<<
       Y1SEff_Pt[ih]<<"  $\\pm$ "<<setprecision(3)<<errY1SEff_Pt[ih]<<"   & "<<setprecision(3)<<Y2SEff_Pt[ih]
	     <<" $\\pm$  "<<setprecision(3)<<errY2SEff_Pt[ih]
	     <<setprecision(3)<< " & "<<Y3SEff_Pt[ih]<<" $\\pm$ "<<setprecision(3)<<errY3SEff_Pt[ih]<<Str2<<endl; 

   }
 
 
 dataFile<<Str1<<endl;
 dataFile<<Str3<<"end{tabular}"<<endl;
 dataFile<<Str3<<"end{center}"<<endl;
 dataFile<<Str3<<"end{table}"<<endl;
 dataFile<<endl<<endl<<endl;
 } 
 

 
 
 if(iSpec==2 && Y3s==1){
   
  dataFile<<Str3<<"begin{table}[htbH]"<<endl;
  dataFile<<Str3<<"begin{center}"<<endl;
  dataFile<<Str3<<"caption{}"<<endl; 
  dataFile<<Str3<<"label{}"<<endl;
  dataFile<<Str3<<"begin{tabular}{c|c|c|c|c}"<<endl;
  dataFile<<Str1<<endl;
  dataFile<<" pT  "<< "      &y  " << "&$\\Upsilon$(1S) "<< "&$\\Upsilon$(2S) "<<"&$\\Upsilon$(3S) "<<Str2<<endl;
  dataFile<<Str1<<endl;

  for(Int_t ih = 0; ih < Nptbin; ih++)
   {
     dataFile<<"$["<<pmin <<","<<pmax<<"]$ & $["<<pt_bound[ih]<<","<<pt_bound[ih+1]<<"]$ &"<<setprecision(3)<<
       Y1SEff_Rap[ih]<<"  $\\pm$ "<<setprecision(3)<<errY1SEff_Rap[ih]<<"   & "<<setprecision(3)<<Y2SEff_Rap[ih]
	     <<" $\\pm$  "<<setprecision(3)<<errY2SEff_Rap[ih]
	     <<setprecision(3)<< " & "<<Y3SEff_Rap[ih]<<" $\\pm$ "<<setprecision(3)<<errY3SEff_Rap[ih]<<Str2<<endl; 
   }
 
  
  dataFile<<Str1<<endl;
  dataFile<<Str3<<"end{tabular}"<<endl;
  dataFile<<Str3<<"end{center}"<<endl;
  dataFile<<Str3<<"end{table}"<<endl;
  dataFile<<endl<<endl<<endl;
 } 


 
 if(iSpec== 3 && Y3s==1){
   
   dataFile<<Str3<<"begin{table}[htbH]"<<endl;
   dataFile<<Str3<<"begin{center}"<<endl;
   dataFile<<Str3<<"caption{}"<<endl; 
   dataFile<<Str3<<"label{}"<<endl;
   dataFile<<Str3<<"begin{tabular}{c|c|c|c|c|c}"<<endl;
   dataFile<<Str1<<endl;
   dataFile<<" pT  "<< "      &y  " <<" &$(N_{Trk}/<N_{Trk}>)$  "<<"  &$\\Upsilon$(1S) "<< "&$\\Upsilon$(2S) "<<"&$\\Upsilon$(3S) "<<Str2<<endl;
   dataFile<<Str1<<endl;
   
   for(Int_t ih = 0; ih < Nptbin; ih++)
     {
       dataFile<<"$["<<pmin <<","<<pmax<<"]$ &$[" <<ymin<<", "<<ymax<<"]$ &$["<<pt_bound[ih]<<","<<pt_bound[ih+1]<<"]$ &"<<setprecision(3)<<
	 Y1SEff_NTrk[ih]<<"  $\\pm$ "<<setprecision(3)<<errY1SEff_NTrk[ih]<<"   & "<<setprecision(3)<<Y2SEff_NTrk[ih]
	       <<" $\\pm$  "<<setprecision(3)<<errY2SEff_NTrk[ih]
	       <<setprecision(3)<< " & "<<Y3SEff_NTrk[ih]<<" $\\pm$ "<<setprecision(3)<<errY3SEff_NTrk[ih]<<Str2<<endl; 
     }
 
  
   dataFile<<Str1<<endl;
   dataFile<<Str3<<"end{tabular}"<<endl;
   dataFile<<Str3<<"end{center}"<<endl;
   dataFile<<Str3<<"end{table}"<<endl;
   dataFile<<endl<<endl<<endl;
 } 






 if(iSpec== 4 && Y3s==1){
   
   dataFile<<Str3<<"begin{table}[htbH]"<<endl;
   dataFile<<Str3<<"begin{center}"<<endl;
   dataFile<<Str3<<"caption{}"<<endl; 
   dataFile<<Str3<<"label{}"<<endl;
   dataFile<<Str3<<"begin{tabular}{c|c|c|c|c|c}"<<endl;
   dataFile<<Str1<<endl;
   dataFile<<" pT  "<< "      &y  " <<" &$(SumHFET |\\eta > 4| /<SumHFET |\\eta > 4|>)$  "<<"  &$\\Upsilon$(1S) "<< "&$\\Upsilon$(2S) "<<"&$\\Upsilon$(3S) "<<Str2<<endl;
   dataFile<<Str1<<endl;
   
   for(Int_t ih = 0; ih < Nptbin; ih++)
     {
       dataFile<<"$["<<pmin <<","<<pmax<<"]$ &$[" <<ymin<<", "<<ymax<<"]$ &$["<<pt_bound[ih]<<","<<pt_bound[ih+1]<<"]$ &"<<setprecision(3)<<
	 Y1SEff_HFET[ih]<<"  $\\pm$ "<<setprecision(3)<<errY1SEff_HFET[ih]<<"   & "<<setprecision(3)<<Y2SEff_HFET[ih]
	       <<" $\\pm$  "<<setprecision(3)<<errY2SEff_HFET[ih]
	       <<setprecision(3)<< " & "<<Y3SEff_HFET[ih]<<" $\\pm$ "<<setprecision(3)<<errY3SEff_HFET[ih]<<Str2<<endl; 
     }
 
  
   dataFile<<Str1<<endl;
   dataFile<<Str3<<"end{tabular}"<<endl;
   dataFile<<Str3<<"end{center}"<<endl;
   dataFile<<Str3<<"end{table}"<<endl;
   dataFile<<endl<<endl<<endl;
 } 











//Calculate Ratios of Efficiencies

//Ratio Arrays
 Double_t R13_Pt[20],errR13_Pt[20];
 Double_t R12_Pt[20],errR12_Pt[20];
 Double_t R23_Pt[20],errR23_Pt[20];


 if(iSpec==1 && Y3s==1){
 
   dataFile<<Str3<<"begin{table}[htbH]"<<endl;
   dataFile<<Str3<<"begin{center}"<<endl;
   dataFile<<Str3<<"caption{}"<<endl; 
   dataFile<<Str3<<"label{}"<<endl;
   dataFile<<Str3<<"begin{tabular}{c|c|c|c|c}"<<endl;
   dataFile<<Str1<<endl;
   dataFile<<" pT  "<< "      &y  " << "&$\\Upsilon(1S)/\\Upsilon(3S)$ "<< "&$\\Upsilon(1S)/\\Upsilon(2S)$ "<<"&$\\Upsilon(2S)/\\Upsilon(3S)$ "<<Str2<<endl;
   dataFile<<Str1<<endl;
   
   for(Int_t ih = 0; ih < Nptbin; ih++)
     {
       
       R13_Pt[ih]=Y1SEff_Pt[ih]/Y3SEff_Pt[ih];
       errR13_Pt[ih]=RError(Y1SEff_Pt[ih],errY1SEff_Pt[ih],Y3SEff_Pt[ih],errY3SEff_Pt[ih]);
       

       R12_Pt[ih]=Y1SEff_Pt[ih]/Y2SEff_Pt[ih];
       errR12_Pt[ih]=RError(Y1SEff_Pt[ih],errY1SEff_Pt[ih],Y2SEff_Pt[ih],errY2SEff_Pt[ih]);



       R23_Pt[ih]=Y2SEff_Pt[ih]/Y3SEff_Pt[ih];
       errR23_Pt[ih]=RError(Y2SEff_Pt[ih],errY2SEff_Pt[ih],Y3SEff_Pt[ih],errY3SEff_Pt[ih]);

     
       cout<<"$["<<pt_bound[ih] <<","<<pt_bound[ih+1]<<"]$ & $["<<ymin<<","<<ymax<<"]$ "<<setprecision(3)<<
	 R13_Pt[ih]<<"  pm "<<setprecision(3)<<errR13_Pt[ih]<<"     "<<setprecision(3)<<R12_Pt[ih]
	   <<"  pm "<<setprecision(3)<<errR12_Pt[ih]
	   <<setprecision(3)<< "  "<<R23_Pt[ih]<<"  pm "<<setprecision(3)<<errR23_Pt[ih]<<endl; 


       dataFile<<"$["<<pt_bound[ih] <<","<<pt_bound[ih+1]<<"]$ & $["<<ymin<<","<<ymax<<"]$ &"<<setprecision(3)<<
	 R13_Pt[ih]<<"  $\\pm$ "<<setprecision(3)<<errR13_Pt[ih]<<"   & "<<setprecision(3)<<R12_Pt[ih]
	       <<" $\\pm$  "<<setprecision(3)<<errR12_Pt[ih]
	       <<setprecision(3)<< " & "<<R23_Pt[ih]<<" $\\pm$ "<<setprecision(3)<<errR23_Pt[ih]<<Str2<<endl; 

     }
   



   dataFile<<Str1<<endl;
   dataFile<<Str3<<"end{tabular}"<<endl;
   dataFile<<Str3<<"end{center}"<<endl;
   dataFile<<Str3<<"end{table}"<<endl;
   dataFile<<endl<<endl<<endl;
 } 
 



//Ratio Arrays
 Double_t R13_Rap[20],errR13_Rap[20];
 Double_t R12_Rap[20],errR12_Rap[20];
 Double_t R23_Rap[20],errR23_Rap[20];






 if(iSpec==2 && Y3s==1){
 
   dataFile<<Str3<<"begin{table}[htbH]"<<endl;
   dataFile<<Str3<<"begin{center}"<<endl;
   dataFile<<Str3<<"caption{}"<<endl; 
   dataFile<<Str3<<"label{}"<<endl;
   dataFile<<Str3<<"begin{tabular}{c|c|c|c|c}"<<endl;
   dataFile<<Str1<<endl;
   dataFile<<" pT  "<< "      &y  " << "&$\\Upsilon(1S)/\\Upsilon(3S)$"<< "&$\\Upsilon(1S)/\\Upsilon(2S)$ "<<"&$\\Upsilon(2S)/\\Upsilon(3S)$ "<<Str2<<endl;
   dataFile<<Str1<<endl;
   
   for(Int_t ih = 0; ih < Nptbin; ih++)
     {
       
       R13_Rap[ih]=Y1SEff_Rap[ih]/Y3SEff_Rap[ih];
       errR13_Rap[ih]=RError(Y1SEff_Rap[ih],errY1SEff_Rap[ih],Y3SEff_Rap[ih],errY3SEff_Rap[ih]);
       

       R12_Rap[ih]=Y1SEff_Rap[ih]/Y2SEff_Rap[ih];
       errR12_Rap[ih]=RError(Y1SEff_Rap[ih],errY1SEff_Rap[ih],Y2SEff_Rap[ih],errY2SEff_Rap[ih]);
       
       
       
       R23_Rap[ih]=Y2SEff_Rap[ih]/Y3SEff_Rap[ih];
       errR23_Rap[ih]=RError(Y2SEff_Rap[ih],errY2SEff_Rap[ih],Y3SEff_Rap[ih],errY3SEff_Rap[ih]);
       
       
       cout<<"$["<<pt_bound[ih] <<","<<pt_bound[ih+1]<<"]$ & $["<<pmin<<","<<pmax<<"]$ "<<setprecision(3)<<
	 R13_Rap[ih]<<"  pm "<<setprecision(3)<<errR13_Rap[ih]<<"     "<<setprecision(3)<<R12_Rap[ih]
	   <<"  pm "<<setprecision(3)<<errR12_Rap[ih]
	   <<setprecision(3)<< "  "<<R23_Rap[ih]<<"  pm "<<setprecision(3)<<errR23_Rap[ih]<<endl; 
       

       dataFile<<"$["<<pmin<<","<<pmax<<"]$ &$["<<pt_bound[ih] <<","<<pt_bound[ih+1]<<"]$ &" <<setprecision(3)<<
	 R13_Rap[ih]<<"  $\\pm$ "<<setprecision(3)<<errR13_Rap[ih]<<"   & "<<setprecision(3)<<R12_Rap[ih]
	       <<" $\\pm$  "<<setprecision(3)<<errR12_Rap[ih]
	       <<setprecision(3)<< " & "<<R23_Rap[ih]<<" $\\pm$ "<<setprecision(3)<<errR23_Rap[ih]<<Str2<<endl; 
       
     }
   



   dataFile<<Str1<<endl;
   dataFile<<Str3<<"end{tabular}"<<endl;
   dataFile<<Str3<<"end{center}"<<endl;
   dataFile<<Str3<<"end{table}"<<endl;
   dataFile<<endl<<endl<<endl;
 } 






 //Ratio Arrays
 Double_t R13_NTrk[20],errR13_NTrk[20];
 Double_t R12_NTrk[20],errR12_NTrk[20];
 Double_t R23_NTrk[20],errR23_NTrk[20];
 

 
 


 if(iSpec==3 && Y3s==1){
   
   dataFile<<Str3<<"begin{table}[htbH]"<<endl;
   dataFile<<Str3<<"begin{center}"<<endl;
   dataFile<<Str3<<"caption{}"<<endl; 
   dataFile<<Str3<<"label{}"<<endl;
   dataFile<<Str3<<"begin{tabular}{c|c|c|c|c|c}"<<endl;
   dataFile<<Str1<<endl;
   dataFile<<" pT  "<< "      &y  " << " &$N_{Trk}/<N_{Trk}>$  " <<"&$\\Upsilon(1S)/\\Upsilon(3S)$"<< "&$\\Upsilon(1S)/\\Upsilon(2S)$ "<<"&$\\Upsilon(2S)/\\Upsilon(3S)$ "<<Str2<<endl;
   dataFile<<Str1<<endl;
   
   for(Int_t ih = 0; ih < Nptbin; ih++)
     {
       
       R13_NTrk[ih]=Y1SEff_NTrk[ih]/Y3SEff_NTrk[ih];
       errR13_NTrk[ih]=RError(Y1SEff_NTrk[ih],errY1SEff_NTrk[ih],Y3SEff_NTrk[ih],errY3SEff_NTrk[ih]);
       

       R12_NTrk[ih]=Y1SEff_NTrk[ih]/Y2SEff_NTrk[ih];
       errR12_NTrk[ih]=RError(Y1SEff_NTrk[ih],errY1SEff_NTrk[ih],Y2SEff_NTrk[ih],errY2SEff_NTrk[ih]);
       
       
       
       R23_NTrk[ih]=Y2SEff_NTrk[ih]/Y3SEff_NTrk[ih];
       errR23_NTrk[ih]=RError(Y2SEff_NTrk[ih],errY2SEff_NTrk[ih],Y3SEff_NTrk[ih],errY3SEff_NTrk[ih]);
       
       
       cout<<"$["<<pt_bound[ih] <<","<<pt_bound[ih+1]<<"]$ & $["<<pmin<<","<<pmax<<"]$ "<<setprecision(3)<<
	 R13_NTrk[ih]<<"  pm "<<setprecision(3)<<errR13_NTrk[ih]<<"     "<<setprecision(3)<<R12_NTrk[ih]
	   <<"  pm "<<setprecision(3)<<errR12_NTrk[ih]
	   <<setprecision(3)<< "  "<<R23_NTrk[ih]<<"  pm "<<setprecision(3)<<errR23_NTrk[ih]<<endl; 
       

       dataFile<<"$["<<pmin<<","<<pmax<<"]$  &$[ "<<ymin<<","<<ymax<<"]$ &$["<<pt_bound[ih] <<","<<pt_bound[ih+1]<<"]$ &" <<setprecision(3)<<
	 R13_NTrk[ih]<<"  $\\pm$ "<<setprecision(3)<<errR13_NTrk[ih]<<"   & "<<setprecision(3)<<R12_NTrk[ih]
	       <<" $\\pm$  "<<setprecision(3)<<errR12_NTrk[ih]
	       <<setprecision(3)<< " & "<<R23_NTrk[ih]<<" $\\pm$ "<<setprecision(3)<<errR23_NTrk[ih]<<Str2<<endl; 
       
     }
   



   dataFile<<Str1<<endl;
   dataFile<<Str3<<"end{tabular}"<<endl;
   dataFile<<Str3<<"end{center}"<<endl;
   dataFile<<Str3<<"end{table}"<<endl;
   dataFile<<endl<<endl<<endl;
 } 






 //Ratio Arrays
 Double_t R13_HFET[20],errR13_HFET[20];
 Double_t R12_HFET[20],errR12_HFET[20];
 Double_t R23_HFET[20],errR23_HFET[20];
 

 
 

 
 if(iSpec==4 && Y3s==1){
   
   dataFile<<Str3<<"begin{table}[htbH]"<<endl;
   dataFile<<Str3<<"begin{center}"<<endl;
   dataFile<<Str3<<"caption{}"<<endl; 
   dataFile<<Str3<<"label{}"<<endl;
   dataFile<<Str3<<"begin{tabular}{c|c|c|c|c|c}"<<endl;
   dataFile<<Str1<<endl;
   dataFile<<" pT  "<< "      &y  " << " &$HFET/<HFET>$  " <<"&$\\Upsilon(1S)/\\Upsilon(3S)$"<< "&$\\Upsilon(1S)/\\Upsilon(2S)$ "<<"&$\\Upsilon(2S)/\\Upsilon(3S)$ "<<Str2<<endl;
   dataFile<<Str1<<endl;
   
   for(Int_t ih = 0; ih < Nptbin; ih++)
     {
       
       R13_HFET[ih]=Y1SEff_HFET[ih]/Y3SEff_HFET[ih];
       errR13_HFET[ih]=RError(Y1SEff_HFET[ih],errY1SEff_HFET[ih],Y3SEff_HFET[ih],errY3SEff_HFET[ih]);
       

       R12_HFET[ih]=Y1SEff_HFET[ih]/Y2SEff_HFET[ih];
       errR12_HFET[ih]=RError(Y1SEff_HFET[ih],errY1SEff_HFET[ih],Y2SEff_HFET[ih],errY2SEff_HFET[ih]);
       
       
       
       R23_HFET[ih]=Y2SEff_HFET[ih]/Y3SEff_HFET[ih];
       errR23_HFET[ih]=RError(Y2SEff_HFET[ih],errY2SEff_HFET[ih],Y3SEff_HFET[ih],errY3SEff_HFET[ih]);
       
       
       cout<<"$["<<pt_bound[ih] <<","<<pt_bound[ih+1]<<"]$ & $["<<pmin<<","<<pmax<<"]$ "<<setprecision(3)<<
	 R13_HFET[ih]<<"  pm "<<setprecision(3)<<errR13_HFET[ih]<<"     "<<setprecision(3)<<R12_HFET[ih]
	   <<"  pm "<<setprecision(3)<<errR12_HFET[ih]
	   <<setprecision(3)<< "  "<<R23_HFET[ih]<<"  pm "<<setprecision(3)<<errR23_HFET[ih]<<endl; 
       

       dataFile<<"$["<<pmin<<","<<pmax<<"]$  &$[ "<<ymin<<","<<ymax<<"]$ &$["<<pt_bound[ih] <<","<<pt_bound[ih+1]<<"]$ &" <<setprecision(3)<<
	 R13_HFET[ih]<<"  $\\pm$ "<<setprecision(3)<<errR13_HFET[ih]<<"   & "<<setprecision(3)<<R12_HFET[ih]
	       <<" $\\pm$  "<<setprecision(3)<<errR12_HFET[ih]
	       <<setprecision(3)<< " & "<<R23_HFET[ih]<<" $\\pm$ "<<setprecision(3)<<errR23_HFET[ih]<<Str2<<endl; 
       
     }
   



   dataFile<<Str1<<endl;
   dataFile<<Str3<<"end{tabular}"<<endl;
   dataFile<<Str3<<"end{center}"<<endl;
   dataFile<<Str3<<"end{table}"<<endl;
   dataFile<<endl<<endl<<endl;
 } 



 dataFile<<endl<<endl; 
 dataFile.close();

 
 
 

 
 
 TFile *outfile;
 
 
 if(IsPPb ==1 && IsOfficial ==1 ){
   
   
   if(Y1s==1){
     
     if(iSpec==1)outfile =new TFile("EffUpsilon1spp_Pt.root","Recreate");
     if(iSpec==2)outfile =new TFile("EffUpsilon1spp_Rap.root","Recreate");
     if(iSpec==3)outfile =new TFile("EffUpsilon1spp_NTrk.root","Recreate");
     if(iSpec==4)outfile =new TFile("EffUpsilon1spp_HFET.root","Recreate");
     
   }
   
   
   if(Y2s==1){
     if(iSpec==1)outfile =new TFile("EffUpsilon2spp_Pt.root","Recreate");
     if(iSpec==2)outfile =new TFile("EffUpsilon2spp_Rap.root","Recreate");
     if(iSpec==3)outfile =new TFile("EffUpsilon2spp_NTrk.root","Recreate");
     if(iSpec==4)outfile =new TFile("EffUpsilon2spp_HFET.root","Recreate");

   }
   
   
   if(Y3s==1){
     if(iSpec==1)outfile =new TFile("EffUpsilon3spp_Pt.root","Recreate");
     if(iSpec==2)outfile =new TFile("EffUpsilon3spp_Rap.root","Recreate");
     if(iSpec==3)outfile =new TFile("EffUpsilon3spp_NTrk.root","Recreate");
     if(iSpec==4)outfile =new TFile("EffUpsilon3spp_HFET.root","Recreate");
   }
 }




 if(IsPPb ==1 && IsOfficial ==0 ){
   if(Y1s==1){
     
     if(iSpec==1)outfile =new TFile("Pri_EffUpsilon1spp_Pt.root","Recreate");
     if(iSpec==2)outfile =new TFile("Pri_EffUpsilon1spp_Rap.root","Recreate");
     if(iSpec==3)outfile =new TFile("Pri_EffUpsilon1spp_NTrk.root","Recreate");
     if(iSpec==4)outfile =new TFile("Pri_EffUpsilon1spp_HFET.root","Recreate");
    
   }
   
   
   if(Y2s==1){
     if(iSpec==1)outfile =new TFile("Pri_EffUpsilon2spp_Pt.root","Recreate");
     if(iSpec==2)outfile =new TFile("Pri_EffUpsilon2spp_Rap.root","Recreate");
     if(iSpec==3)outfile =new TFile("Pri_EffUpsilon2spp_NTrk.root","Recreate");
     if(iSpec==4)outfile =new TFile("Pri_EffUpsilon2spp_HFET.root","Recreate");
   }
   
   
   if(Y3s==1){
     if(iSpec==1)outfile =new TFile("Pri_EffUpsilon3spp_Pt.root","Recreate");
     if(iSpec==2)outfile =new TFile("Pri_EffUpsilon3spp_Rap.root","Recreate");
     if(iSpec==3)outfile =new TFile("Pri_EffUpsilon3spp_NTrk.root","Recreate");
     if(iSpec==4)outfile =new TFile("Pri_EffUpsilon3spp_HFET.root","Recreate");

   }
 }





 if(IsPP==1 && IsOfficial ==1 ){
   
   if(Y1s==1){
     
     if(iSpec==1)outfile =new TFile("pp276_EffUpsilon1spp_Pt.root","Recreate");
     //if(iSpec==1)outfile =new TFile("pp276_EffUpsilon1spp_Pt_NoFSR.root","Recreate");
     if(iSpec==2)outfile =new TFile("pp276_EffUpsilon1spp_Rap.root","Recreate");
     if(iSpec==3)outfile =new TFile("pp276_EffUpsilon1spp_NTrk.root","Recreate");
     if(iSpec==4)outfile =new TFile("pp276_EffUpsilon1spp_HFET.root","Recreate");
   
   }
   
   
   if(Y2s==1){
     if(iSpec==1)outfile =new TFile("pp276_EffUpsilon2spp_Pt.root","Recreate");
     if(iSpec==2)outfile =new TFile("pp276_EffUpsilon2spp_Rap.root","Recreate");
     if(iSpec==3)outfile =new TFile("pp276_EffUpsilon2spp_NTrk.root","Recreate");
     if(iSpec==4)outfile =new TFile("pp276_EffUpsilon2spp_HFET.root","Recreate");

   }
   
   
   if(Y3s==1){
     if(iSpec==1)outfile =new TFile("pp276_EffUpsilon3spp_Pt.root","Recreate");
     if(iSpec==2)outfile =new TFile("pp276_EffUpsilon3spp_Rap.root","Recreate");
     if(iSpec==3)outfile =new TFile("pp276_EffUpsilon3spp_NTrk.root","Recreate");
     if(iSpec==4)outfile =new TFile("pp276_EffUpsilon3spp_HFET.root","Recreate");

   }
 }


  TGraphErrors *Eff_Upsilon = new TGraphErrors(Nptbin, PT, Eff_cat_1, mom_err,Err_Eff_cat_1);
  Eff_Upsilon->SetName("TotalEfficiency");
  Eff_Upsilon->SetMarkerStyle(21);

  if(Y1s==1)  Eff_Upsilon->SetMarkerColor(2);
  if(Y2s==1)  Eff_Upsilon->SetMarkerColor(1);
  if(Y3s==1)  Eff_Upsilon->SetMarkerColor(4);
  
  Eff_Upsilon->GetYaxis()->SetTitle("Total Efficiency");
  

  if(iSpec==1) Eff_Upsilon->GetXaxis()->SetTitle("#Upsilon pT (GeV/c^{2})");
  if(iSpec==2) Eff_Upsilon->GetXaxis()->SetTitle("#Upsilon rapidity");
  if(iSpec==3) Eff_Upsilon->GetXaxis()->SetTitle("bin");
  Eff_Upsilon->GetYaxis()->SetRangeUser(0,1.0);
  
  TLegend *legend_GP = new TLegend( 0.50,0.79,0.80,0.89);
  legend_GP->SetBorderSize(0);
  legend_GP->SetFillStyle(0);
  legend_GP->SetFillColor(0);
  legend_GP->SetTextSize(0.032);
  legend_GP->AddEntry(Eff_Upsilon,"PythiaEvtGen PP", "P");
  
  new TCanvas;
  Eff_Upsilon->Draw("AP");
  legend_GP->Draw("Same");
    
  Eff_Upsilon->Write();

  if(iSpec==1){ gPad->Print("plots/Eff_Upsilon_Pt.pdf");gPad->Print("plots/Eff_Upsilon_Pt.png");gPad->Print("plots/Eff_Upsilon_Pt.eps");}
  if(iSpec==2){ gPad->Print("plots/Eff_Upsilon_Rap.pdf");gPad->Print("plots/Eff_Upsilon_Rap.png");  gPad->Print("plots/Eff_Upsilon_Rap.eps");}
  if(iSpec==3){ gPad->Print("plots/Eff_Upsilon_Cent.pdf");gPad->Print("plots/Eff_Upsilon_Cent.png"); gPad->Print("plots/Eff_Upsilon_Cent.eps"); }
 
  

  TGraphErrors *Eff_Upsilon_Trigger = new TGraphErrors(Nptbin, PT, Eff_Trigger, mom_err,errEff_Trigger);
  Eff_Upsilon_Trigger->SetName("TriggerEfficiency");
  Eff_Upsilon_Trigger->SetMarkerStyle(24);

  if(Y1s==1)  Eff_Upsilon_Trigger->SetMarkerColor(2);
  if(Y2s==1)  Eff_Upsilon_Trigger->SetMarkerColor(1);
  if(Y3s==1)  Eff_Upsilon_Trigger->SetMarkerColor(4);
  
  Eff_Upsilon_Trigger->GetYaxis()->SetTitle("Trigger Efficiency");
  

  if(iSpec==1) Eff_Upsilon_Trigger->GetXaxis()->SetTitle("#Upsilon pT (GeV/c^{2})");
  if(iSpec==2) Eff_Upsilon_Trigger->GetXaxis()->SetTitle("#Upsilon rapidity");
  if(iSpec==3) Eff_Upsilon_Trigger->GetXaxis()->SetTitle("bin");
  Eff_Upsilon_Trigger->GetYaxis()->SetRangeUser(0,1.0);
  
  new TCanvas;
  Eff_Upsilon_Trigger->Draw("AP");
  legend_GP->Draw("Same");
  Eff_Upsilon_Trigger->Write();



  TGraphErrors *Eff_Upsilon_MuID = new TGraphErrors(Nptbin, PT, Eff_MuID, mom_err,errEff_MuID);
  Eff_Upsilon_MuID->SetName("MuIDEfficiency");
  Eff_Upsilon_MuID->SetMarkerStyle(26);
  
  if(Y1s==1)  Eff_Upsilon_MuID->SetMarkerColor(2);
  if(Y2s==1)  Eff_Upsilon_MuID->SetMarkerColor(1);
  if(Y3s==1)  Eff_Upsilon_MuID->SetMarkerColor(4);
   
  Eff_Upsilon_MuID->GetYaxis()->SetTitle("MuID Efficiency");
   
   
  if(iSpec==1) Eff_Upsilon_MuID->GetXaxis()->SetTitle("#Upsilon pT (GeV/c^{2})");
  if(iSpec==2) Eff_Upsilon_MuID->GetXaxis()->SetTitle("#Upsilon rapidity");
  if(iSpec==3) Eff_Upsilon_MuID->GetXaxis()->SetTitle("bin");
  Eff_Upsilon_MuID->GetYaxis()->SetRangeUser(0,1.0);
  
  new TCanvas;
  Eff_Upsilon_MuID->Draw("AP");
  legend_GP->Draw("Same");
  Eff_Upsilon_MuID->Write();



  TGraphErrors *Eff_Upsilon_Reco = new TGraphErrors(Nptbin, PT, Eff_Reco, mom_err,errEff_Reco);
  Eff_Upsilon_Reco->SetName("RecoOnly");
  Eff_Upsilon_Reco->SetMarkerStyle(28);
   
  if(Y1s==1)  Eff_Upsilon_Reco->SetMarkerColor(2);
  if(Y2s==1)  Eff_Upsilon_Reco->SetMarkerColor(1);
  if(Y3s==1)  Eff_Upsilon_Reco->SetMarkerColor(4);
   
  Eff_Upsilon_Reco->GetYaxis()->SetTitle("Only Reco Eff");
   
   
  if(iSpec==1) Eff_Upsilon_Reco->GetXaxis()->SetTitle("#Upsilon pT (GeV/c^{2})");
  if(iSpec==2) Eff_Upsilon_Reco->GetXaxis()->SetTitle("#Upsilon rapidity");
  if(iSpec==3) Eff_Upsilon_Reco->GetXaxis()->SetTitle("bin");
  Eff_Upsilon_Reco->GetYaxis()->SetRangeUser(0,1.0);
  
  new TCanvas;
  Eff_Upsilon_Reco->Draw("AP");
  legend_GP->Draw("Same");
  Eff_Upsilon_Reco->Write();
  
  diMuonsPt_Gen->Write();
  diMuonsRap_Gen->Write();
  
  MuonPt_Gen->Write();
  MuonEta_Gen->Write();
  MuonPhi_Gen->Write();
  
  
  diMuonsPt_rec->Write();
  diMuonsRap_rec->Write();
  MuonPt_Rec->Write();
  MuonEta_Rec->Write();
  MuonPhi_Rec->Write();
  
  diMuonsPtB_Gen->Write();
  UpsilonPtB_Gen->Write();
  RatioFSR_Pt->Write();
   

  outfile->Write();
  outfile->Close();
  
  
  /*
    new TCanvas;
    diMuonsPt_Gen->Draw();
    gPad->SaveAs("plots/UpsilonPtGen_PP.png");
    
    new TCanvas;
    diMuonsRap_Gen->Draw();
    gPad->SaveAs("plots/UpsilonRapGen_PP.png");



    new TCanvas;
    diMuonsPt_rec->Draw();
    gPad->SaveAs("plots/UpsilonPt_PP.png");

    new TCanvas;
    diMuonsRap_rec->Draw();
    gPad->SaveAs("plots/UpsilonRap_PP.png");




    new TCanvas;
    MuonPt_Rec->Draw();
    gPad->SaveAs("plots/MuonPt_Rec.png");
    new TCanvas;
    MuonEta_Rec->Draw();
    gPad->SaveAs("plots/MuonEta_Rec.png");
    new TCanvas;
    MuonPhi_Rec->Draw();
    gPad->SaveAs("plots/MuonPhi_Rec.png");
    new TCanvas;
    MuonEtaPhi_Rec->Draw("Colz");
    gPad->SaveAs("plots/MuonEtaPhi_Rec.png");



    new TCanvas;
    MuonPt_Gen->Draw();
    gPad->SaveAs("plots/MuonPt_Gen.png");
    new TCanvas;
    MuonEta_Gen->Draw();
    gPad->SaveAs("plots/MuonEta_Gen.png");
    new TCanvas;
    MuonPhi_Gen->Draw();
    gPad->SaveAs("plots/MuonPhi_Gen.png");
    new TCanvas;
    MuonEtaPhi_Gen->Draw("Colz");
    gPad->SaveAs("plots/MuonEtaPhi_Gen.png");
    
    
  */








}



Bool_t IsAccept(Double_t pt, Double_t eta)
{
  //return (TMath::Abs(eta) < 2.4 && pt > 0.0 );
  
  //return ( eta > -2.4 && eta < 1.46 && pt > 0.0 );
  
  return ( eta > -1.47 && eta < 0.53 && pt > 0.0 );
  
}


Bool_t IsAccept_PP(Double_t pt, Double_t eta)
{
  //return (TMath::Abs(eta) < 2.4 && pt > 0.0 );
  return (TMath::Abs(eta) < 1.0 && pt > 0.0 );

}


//Ratio Error
Double_t RError(Double_t A, Double_t eA, Double_t B, Double_t eB){
  Double_t eR =0.0;
  Double_t f=0;
  Double_t fA=0;
  Double_t fB=0;
  f=A/B;
  fA=eA/A;
  fB=eB/B;
  eR=  f*sqrt(fA*fA + fB*fB );
  //cout<<"eR: "<<eR<<endl;
  return eR;
}

//Weighted Ratio Error
Double_t WeightRatioError(Double_t A, Double_t ErrorA, Double_t B, Double_t ErrorB)
{
  //R = A/B 
  Double_t R=0.0;
  Double_t E=0.0;
  Double_t R2,B2;
  R=A/B;
  R2=R*R;
  B2=B*B;

  E = TMath::Sqrt(  ( (R2/B2)*(ErrorA*ErrorA)) +(  ((1-R)*(1-R)/(B2))*(ErrorB*ErrorB -ErrorA*ErrorA) ) );
  return E;
}
