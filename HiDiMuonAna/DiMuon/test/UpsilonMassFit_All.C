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
void UpsilonMassFit_All(int iSpec = 3, int PutWeight=1)
{

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
  gStyle->SetOptTitle(1); // at least most of the time
  gStyle->SetOptStat(1); // most of the time, sometimes "nemriou" might be useful to display name, 
  //number of entries, mean, rms, integral, overflow and underflow
  gStyle->SetOptFit(1); // set to 1 only if you want to display fit results

  //==================================== Define Histograms====================================================
  ofstream dataFile(Form("Eff_Upsilon.txt"));
  
  TH1D *diMuonsInvMass_Gen = new TH1D("diMuonsInvMass_Gen","diMuonsInvMass_Gen", 100,8.0,12.0);
  TH1D *diMuonsPt_Gen = new TH1D("diMuonsPt_Gen","diMuonsPt_Gen", 100,0,30);
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

  //==============================================Define AccEff Stuff here===========================================
  // Pt bin sizes
  int Nptbin=1;
  double pt_bound[100] = {0};
  if(iSpec == 1) { 
    Nptbin = 3;
    pt_bound[0] = 0;
    pt_bound[1] = 6.5;
    pt_bound[2] = 10.0;
    pt_bound[3] = 20.0;
   
    pt_bound[4] = 20.0;
    pt_bound[5] = 25.0;
    pt_bound[6] = 30.0;
    pt_bound[7] = 35;
    pt_bound[8] = 40;
    pt_bound[9] = 45;
    pt_bound[10] = 50;
  }
  
  if(iSpec == 2) { 
    Nptbin = 2;
    pt_bound[0] = 0.0; 
    pt_bound[1] = 1.2; 
    pt_bound[2] = 2.4; 
    
    pt_bound[3] = 0.0; 
    pt_bound[4] = 0.8; 
    pt_bound[5] = 1.8; 
    //pt_bound[7] = 2.0; 
    pt_bound[6] = 2.4; 
  
  }
  
  
  if(iSpec == 3) {
    Nptbin = 3;
    //for plots
    pt_bound[0] = 0.0;//0
    pt_bound[1] = 4.0;//10
    pt_bound[2] = 8.0;//20
    pt_bound[3] = 20.0;//25
    pt_bound[4] = 16.0;//50
    pt_bound[5] = 20.0;//100
    pt_bound[6] = 24.0;
    pt_bound[7] = 32.0;
    pt_bound[8] = 40.0;
    pt_bound[9] = 40.0;
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


      diMuonsPt_GenA[ifile][ih]= new TH1D(nameGenPt[ifile],nameGenPt[ifile],  100,0,40); //for eff Gen;
      diMuonsPt_RecA[ifile][ih]= new TH1D(nameRecPt[ifile],nameRecPt[ifile],  100,0,40); //for eff Rec;
    }
  }
  
  //===========================================Input Root File============================================================
  char fileName[10][500];
  //0.0380228 	0.0480769 	0.0293255 	0.0125156 	0.00336587 	0.00276319*2/5 = 0.001105276
  //Scales
  double scale[10]={0};  
  scale[0]=(0.0380228/0.001105276);
  scale[1]=(0.0480769/0.001105276);
  scale[2]=(0.0293255/0.001105276);
  scale[3]=(0.0125156/0.001105276);
  scale[4]=(0.00336587/0.001105276);
  scale[5]=(0.001105276/0.001105276);
 
  //34.55 , 43.70 , 26.65 , 11.37 , 3.05 , 1



  sprintf(fileName[0],"/home/vineet/HiData/UpsilonData/UpsilonEff/DimuonOnia2Dplots_UpsilonPt03.root");
  sprintf(fileName[1],"/home/vineet/HiData/UpsilonData/UpsilonEff/DimuonOnia2Dplots_UpsilonPt36.root");
  sprintf(fileName[2],"/home/vineet/HiData/UpsilonData/UpsilonEff/DimuonOnia2Dplots_UpsilonPt69.root");
  sprintf(fileName[3],"/home/vineet/HiData/UpsilonData/UpsilonEff/DimuonOnia2Dplots_UpsilonPt912.root");
  sprintf(fileName[4],"/home/vineet/HiData/UpsilonData/UpsilonEff/DimuonOnia2Dplots_UpsilonPt1215.root");
  sprintf(fileName[5],"/home/vineet/HiData/UpsilonData/UpsilonEff/DimuonOnia2Dplots_UpsilonPt1530.root");
  
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
    int muPos_found, muPos_pixeLayers, muPos_nValidMuHits;
    bool muPos_matches;
    //(2).Negative Muon                                     
    double muNeg_nchi2In, muNeg_dxy, muNeg_dz, muNeg_nchi2Gl;
    int muNeg_found, muNeg_pixeLayers, muNeg_nValidMuHits;
    bool muNeg_matches;
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
    //2). Negative Muon                                                                            
    tree->SetBranchAddress("muNeg_nchi2In", &muNeg_nchi2In);
    tree->SetBranchAddress("muNeg_dxy", &muNeg_dxy);
    tree->SetBranchAddress("muNeg_dz", &muNeg_dz);
    tree->SetBranchAddress("muNeg_nchi2Gl", &muNeg_nchi2Gl);
    tree->SetBranchAddress("muNeg_found", &muNeg_found);
    tree->SetBranchAddress("muNeg_pixeLayers", &muNeg_pixeLayers);
    tree->SetBranchAddress("muNeg_nValidMuHits", &muNeg_nValidMuHits);
    tree->SetBranchAddress("muNeg_matches", &muNeg_matches);
    
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
      
      if(i%1000==0){
	cout<<" processing record "<<i<<endl;
	cout<<" Mass "<< GenJpsiMass<< " pT "<< GenJpsiPt << " Y " <<GenJpsiRap<<endl; 
      }
      
      bool GenPosIn=0, GenNegIn=0,GenPosPass=0,GenNegPass=0;

      GenmuPosPt= TMath::Sqrt(GenmuPosPx*GenmuPosPx + GenmuPosPy*GenmuPosPy); 
      GenmuNegPt= TMath::Sqrt(GenmuNegPx*GenmuNegPx + GenmuNegPy*GenmuNegPy); 
            
      diMuonsInvMass_Gen->Fill(GenJpsiMass);
      diMuonsPt_Gen->Fill(GenJpsiPt);
 
      if(IsAccept(GenmuPosPt, GenmuPosEta)) {GenPosIn=1;}
      if(IsAccept(GenmuNegPt, GenmuNegEta)) {GenNegIn=1;}
  

    
      if(GenPosIn && GenNegIn ) NAccep++;
      
      if(GenPosIn==1 && GenmuPosPt>4.0 ) {GenPosPass=1;}
      if(GenNegIn==1 && GenmuNegPt>4.0 ) {GenNegPass=1;}

      double GenCenWeight=0,GenWeight=0;
      GenCenWeight=FindCenWeight(gbin);
      Bin_Gen->Fill(gbin);
      GenWeight=GenCenWeight*scale[ifile];
      if(PutWeight==0){GenWeight=1;}

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
	if(iSpec == 2)  if((GenPosPass==1 && GenNegPass==1) &&  (GenJpsiPt<20.0) && (TMath::Abs(GenJpsiRap) > pt_bound[ih] && TMath::Abs(GenJpsiRap) <=pt_bound[ih+1] )){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenWeight);}
	if(iSpec == 3)  if( (GenPosPass==1 && GenNegPass==1) && (GenJpsiPt < 20.0) &&  (TMath::Abs(GenJpsiRap)<2.4 ) && (gbin>=pt_bound[ih] && gbin<pt_bound[ih+1])){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenWeight);}
      

      }

    }//gen loop end
    
    cout<<" accepted no "<< NAccep<<endl;
    //dataFile<<" accepted no "<< NAccep<<endl;
     
    //   new TCanvas;
    //diMuonsInvMass_Gen->Draw();
    //gPad->Print("plots/diMuonsInvMass_Gen.png");
    
    //new TCanvas;
    //diMuonsPt_Gen->Draw();
    //gPad->Print("plots/diMuonsPt_Gen.png");
  
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
      if(i%100000==0){
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

      if(muPos_found > 10 && muPos_pixeLayers > 0 && muPos_nchi2In < 4.0 && muPos_dxy < 3 && muPos_dz < 15 && muPos_nchi2Gl < 6 
	 && muPos_nValidMuHits > 6 && muPosPt>4.0){PosPass=1;}	  
      
      if( (muNeg_found >10 && muNeg_pixeLayers >0 && muNeg_nchi2In <4.0 && muNeg_dxy < 3 && muNeg_dz < 15 && muNeg_nchi2Gl < 6 
	   && muNeg_nValidMuHits >6 &&  muNegPt>4.0)){NegPass=1;}

      // cout<<muPos_matches<<"  "<<muNeg_matches<<endl;
      
      if((muPos_matches==1 && muNeg_matches==1) && (PosIn==1 && NegIn==1 )  &&   (PosPass==1 && NegPass==1)){AllCut=1;}
    
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
      if((JpsiCharge == 0) && (JpsiVprob > 0.01)) {
	for (Int_t ih = 0; ih < Nptbin; ih++) {
	  //to see cont reco pT
	  if(iSpec == 1)if((AllCut==1) && (TMath::Abs(JpsiRap) < 2.4) && (JpsiPt>pt_bound[ih] && JpsiPt<=pt_bound[ih+1])) {diMuonsPt_RecA[ifile][ih]->Fill(JpsiPt,RecWeight);}
	  
	  if(iSpec == 1)if((AllCut==1) && (TMath::Abs(JpsiRap)<2.4 ) && (JpsiPt > pt_bound[ih] && JpsiPt <=pt_bound[ih+1])){diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass, RecWeight);}
	  if(iSpec == 2) if( (AllCut==1) &&  (JpsiPt<20.0) && (TMath::Abs(JpsiRap) > pt_bound[ih] && TMath::Abs(JpsiRap) <=pt_bound[ih+1])){diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecWeight);}
	  if(iSpec == 3) if((AllCut==1) &&  (JpsiPt<20.0) && (TMath::Abs(JpsiRap) < 2.4) && (rbin>=pt_bound[ih] &&  rbin < pt_bound[ih+1])){diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecWeight);}
	



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
  double MassUpsilon, WeidthUpsilon;
  
  // Low mass range upsilon width 54 KeV
  MassUpsilon = 9.46; WeidthUpsilon = 0.052;
  mass_low = 8.9; mass_high = 9.7;  // Fit ranges
  
  
  // Fit Function crystall ball
  TF1 *GAUSPOL = new TF1("GAUSPOL",CrystalBall,8.0,12.0,5);
  
  // TF1 *GAUSPOL = new TF1("GAUSPOL",CBPol1,8.0,12.0,6);
  
  GAUSPOL->SetParNames("#alpha","n","Mean","#sigma","N");
  
  GAUSPOL->SetLineWidth(2.0);
  GAUSPOL->SetLineColor(2);
  GAUSPOL->SetParameter(0, 1.756);
  GAUSPOL->SetParameter(1, 2.636);
  GAUSPOL->SetParameter(2, MassUpsilon);
  GAUSPOL->SetParameter(3, WeidthUpsilon);
 
  

  GAUSPOL->SetParLimits(2, 0.1*MassUpsilon,2.0*MassUpsilon);
  GAUSPOL->SetParLimits(3, 0.1*WeidthUpsilon,2.0*WeidthUpsilon);



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
    diMuonsInvMass_RecA1[ih]->Rebin(2);
    GAUSPOL->SetParameter(4, diMuonsInvMass_RecA1[ih]->GetMaximum());
    
    new TCanvas; 
    diMuonsInvMass_RecA1[ih]->Fit("GAUSPOL","LLQ", "", mass_low, mass_high);
   
    double UpsilonMass = GAUSPOL->GetParameter(2);
    double UpsilonWidth = GAUSPOL->GetParameter(3);
   
    double UpsilonYield = GAUSPOL->GetParameter(4);
 
    double par[20];
    GAUSPOL->GetParameters(par);
    sprintf(namePt_1B,"pt_1B_%d",ih);
    backfun_1 = new TF1(namePt_1B, Pol2, mass_low, mass_high, 3);
    backfun_1->SetParameters(&par[4]);
   

    double MassLow=(UpsilonMass-3*UpsilonWidth);
    double MassHigh=(UpsilonMass+3*UpsilonWidth);
    
    int binlow =diMuonsInvMass_RecA1[ih]->GetXaxis()->FindBin(MassLow);
    int binhi =diMuonsInvMass_RecA1[ih]->GetXaxis()->FindBin(MassHigh);
    double binwidth=diMuonsInvMass_RecA1[ih]->GetBinWidth(1);
        
    //yield by function 
    //rec_pt[ih] = UpsilonYield/binwidth;
    //rec_ptError[ih]= TMath::Sqrt((UpsilonYield/binwidth));

    cout<<"Rec diMuons from Pt histo "<<diMuonsPt_RecA1[ih]->Integral(1,100)<<endl;  
    cout<<"Rec dimuons from mass "<<diMuonsInvMass_RecA1[ih]->Integral(1,100)<<endl; 
    

      
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

    cout<<"Upsilon Yield by integral of histo:  "<< diMuonsInvMass_RecA1[ih]->IntegralAndError(binlow, binhi,recError) <<"  error "<< rec_ptError[ih]<<endl; 
    cout<<"UpsilonYield by Gauss yield det:     "<< UpsilonYield/binwidth << " UpsilonWidth "<< UpsilonWidth<<" UpsilonMass "<<UpsilonMass <<endl;
    cout<<"Upsilon Yield by Function integral:  "<< GAUSPOL->Integral(MassLow,MassHigh)/binwidth <<endl;
    cout<<" rec_pt[ih]  "<<  rec_pt[ih] <<" gen_pt[ih] "<<gen_pt[ih]<<endl;
    //dataFile<<" rec_pt[ih]  "<<  rec_pt[ih] <<" gen_pt[ih] "<<gen_pt[ih]<<endl;
    cout<<" eff "<< Eff_cat_1[ih]<<" error "<<Err_Eff_cat_1[ih]<<endl;
    
    dataFile<<"ih " <<ih<<" eff "<< Eff_cat_1[ih]<<" error "<<Err_Eff_cat_1[ih]<<endl;
    
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

    new TCanvas;
    diMuonsInvMass_GenA1[ih]->Draw();
    gPad->Print(GPlotName);
    gPad->Print(GPlotName1);
    gPad->Print(GPlotName2);


    //new TCanvas;
    //diMuonsPt_GenA1[ih]->Draw();
    //new TCanvas;
    //diMuonsPt_RecA1[ih]->Draw();
 
}
  dataFile.close();

  TGraphErrors *Eff_Upsilon = new TGraphErrors(Nptbin, PT, Eff_cat_1, mom_err,Err_Eff_cat_1);
  Eff_Upsilon->SetMarkerStyle(21);
  Eff_Upsilon->SetMarkerColor(2);
  Eff_Upsilon->GetYaxis()->SetTitle("Reco Eff");
 
  if(iSpec==1) Eff_Upsilon->GetXaxis()->SetTitle("#Upsilon pT (GeV/c^{2})");
  if(iSpec==2) Eff_Upsilon->GetXaxis()->SetTitle("#Upsilon rapidity");
  if(iSpec==3) Eff_Upsilon->GetXaxis()->SetTitle("bin");
   Eff_Upsilon->GetYaxis()->SetRangeUser(0,1.0);

  TLegend *legend_GP = new TLegend( 0.50,0.79,0.80,0.89);
  legend_GP->SetBorderSize(0);
  legend_GP->SetFillStyle(0);
  legend_GP->SetFillColor(0);
  legend_GP->SetTextSize(0.032);
  legend_GP->AddEntry(Eff_Upsilon,"PythiaEvtGen + HydjetBass", "P");
  
  new TCanvas;
  Eff_Upsilon->Draw("AP");
  legend_GP->Draw("Same");
    
  if(iSpec==1){ gPad->Print("plots/Eff_Upsilon_Pt.pdf");gPad->Print("plots/Eff_Upsilon_Pt.png");gPad->Print("plots/Eff_Upsilon_Pt.eps");}
  if(iSpec==2){ gPad->Print("plots/Eff_Upsilon_Rap.pdf");gPad->Print("plots/Eff_Upsilon_Rap.png");  gPad->Print("plots/Eff_Upsilon_Rap.eps");}
  if(iSpec==3){ gPad->Print("plots/Eff_Upsilon_Cent.pdf");gPad->Print("plots/Eff_Upsilon_Cent.png"); gPad->Print("plots/Eff_Upsilon_Cent.eps"); }

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
  double NCollArray[50]={1563.03, 1370.41, 1204.05, 1063.45, 943.5,
834.12, 736.223, 654.913, 576.466, 507.757, 443.05, 386.802, 334.48,
290.097, 247.779, 211.762, 179.834, 153.509, 127.75, 106.59, 88.1189,
72.3836, 59.1049, 47.3574, 37.7951, 30.1705, 23.6861, 18.6918, 14.2287,
10.9705, 8.76148, 6.57459, 5.01557, 3.78525, 2.9123, 2.12377, 1.5,
			 0.922951, 0.581967, 0.503279,};
  return(NCollArray[Bin]);
}






// mu_innerTrack_Hits > 10
//mu_pixelLayers > 0
//mu_innerTrack_chi2NDOF < 4.0
//mu_dxy < 3.0 cm
// mu_dz < 15. cm
//mu_globalTrack_chi2NDOF < 6
//mu_validMuHits > 6
//vProb > 0.01
