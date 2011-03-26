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
// miscellaneous  
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "FitFunctions.h"
#include "TObjArray.h"
bool IsAccept(Double_t pt, Double_t eta); //you can define acceptance here 
double FindCenWeight(int Bin);//gives you weight according to cent
void JPsiMassFit_All(int iSpec = 3) //iSpec =1 pT, =2 Rap, =3 Cent
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
  gStyle->SetOptTitle(1); // at least most of the time
  gStyle->SetOptStat(1); // most of the time, sometimes "nemriou" might be useful to display name, 
  //number of entries, mean, rms, integral, overflow and underflow
  gStyle->SetOptFit(1); // set to 1 only if you want to display fit results

  //==================================== Define Histograms====================================================
  ofstream dataFile(Form("Eff_JPsi.txt"));
  TH1D *diMuonsInvMass_Gen = new TH1D("diMuonsInvMass_Gen","diMuonsInvMass_Gen", 100,2.6,3.5);
  TH1D *diMuonsPt_Gen = new TH1D("diMuonsPt_Gen","diMuonsPt_Gen", 100,0,30);
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
  int Nptbin;
  double pt_bound[100] = {0};
  
  if(iSpec == 1) { 
    Nptbin = 3;
    pt_bound[0] = 0;
    pt_bound[1] = 6.5;
    pt_bound[2] = 10.0;
    pt_bound[3] = 30.0;
    
    pt_bound[4] = 20.0;
    pt_bound[5] = 25.0;
    pt_bound[6] = 30.0;
    pt_bound[7] = 35;
    pt_bound[8] = 40;
    pt_bound[9] = 45;
    pt_bound[10] = 50;
  }
  
  if(iSpec == 2) { 
    Nptbin = 3;
    pt_bound[0] = 0.0; 
    pt_bound[1] = 1.2; 
    pt_bound[2] = 1.6; 
    pt_bound[3] = 2.4; 
    pt_bound[4] = 1.6; 
    pt_bound[5] = 2.4; 
    pt_bound[6] = -0.4; 
    pt_bound[7] = 0.4; 
    pt_bound[8] = 0.8; 
    pt_bound[9] = 1.2; 
    pt_bound[10] = 1.6; 
    pt_bound[11] = 1.9; 
    pt_bound[12] = 2.1; 
    pt_bound[13] = 2.4; 
  }
  
  if(iSpec == 3) {
    Nptbin = 1;
    pt_bound[0] = 0.0;//0
    pt_bound[1] = 40.0;//10
    pt_bound[2] = 8.0;//15
    pt_bound[3] = 16.0;//25
    pt_bound[4] = 40.0;//50
    
    pt_bound[5] = 20.0;//100
    pt_bound[6] = 24.0;
    pt_bound[7] = 28.0;
    pt_bound[8] = 32.0;
    pt_bound[9] = 40.0;
  }
  //X Axis error on Eff graph 
  double PT[100], DelPT[100], mom_err[100];
  for (Int_t ih = 0; ih < Nptbin; ih++) {
    //cout<<"pttt  "<<pt_bound[ih]<<endl;
    PT[ih] = (pt_bound[ih] + pt_bound[ih+1])/2.0;
    DelPT[ih] = pt_bound[ih+1] - pt_bound[ih];
    mom_err[ih] = DelPT[ih]/2.0;
    cout<<PT[ih]<<" X axis graph "<<DelPT[ih]<<endl;
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
      //cout<< "  ifile "<< nameGen[ifile]<<endl;
    }
  }
  
  //===========================================Input Root File============================================================
  char fileName[10][500];
  //scales for different pT bins
  double scale[10]={0};  
  
  scale[0]=(0.0257069/0.00005571);
  scale[1]=(0.0146199/0.00005571);
  scale[2]=(0.00393391/0.00005571);
  scale[3]=(0.000669658/0.00005571);
  scale[4]=(0.000164187/0.00005571);
  scale[5]=(0.00005571/0.00005571);
  
  //0.000139274
  // scale[0]=(0.0257069/0.0257069);
  //scale[1]=(0.0146199/0.0257069);
  //scale[2]=(0.00393391/0.0257069);
  //scale[3]=(0.000669658/0.0257069);
  //scale[4]=(0.000164187/0.0257069);
  //scale[5]=(0.00005571/0.0257069);
  

  //Prompt JPsi
  sprintf(fileName[0],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_JPsiPt03.root");
  sprintf(fileName[1],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_JPsiPt36.root");
  sprintf(fileName[2],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_JPsiPt69.root");
  sprintf(fileName[3],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_JPsiPt912.root");
  sprintf(fileName[4],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_JPsiPt1215.root");
  sprintf(fileName[5],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_JPsiPt1530.root");
    
  //Non Prompt JPsi
  //sprintf(fileName[0],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_NPJPsiPt03.root");
  //sprintf(fileName[1],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_NPJPsiPt36.root");
  //sprintf(fileName[2],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_NPJPsiPt69.root");
  //sprintf(fileName[3],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_NPJPsiPt912.root");
  //sprintf(fileName[4],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_NPJPsiPt1215.root");
  //sprintf(fileName[5],"/media/49FD-4149/JPsiData/JPsiEff/DimuonOnia2Dplots_NPJPsiPt1530.root");
  
  //for(int ifile =0; ifile <=5; ifile++){
  //cout<<fileName[ifile]<<endl;
  //}
  
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
    int muPos_found, muPos_pixeLayers, muPos_nValidMuHits;
    Char_t muPos_matches;
     //(2).Negative Muon                                     
    double muNeg_nchi2In, muNeg_dxy, muNeg_dz, muNeg_nchi2Gl;
    int muNeg_found, muNeg_pixeLayers, muNeg_nValidMuHits;
    Char_t muNeg_matches;
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
    cout<<" Total Entries in GenLevel Tree for pT range: "<<fileName[ifile]<<"  "<<   nGenEntries<< " ==============="<<endl;
    dataFile<<" Total Entries in GenLevel Tree for pT range: "<<fileName[ifile]<<"  "<<   nGenEntries<< " ==============="<<endl;
    
    for(int i=0; i< nGenEntries; i++)  {	    
      gentree->GetEntry(i);
      if(i%100000==0){
	cout<<" processing record "<<i<<endl;
	cout<<" Mass "<< GenJpsiMass<< " pT "<< GenJpsiPt << " Y " <<GenJpsiRap<<endl; 
      }
      
      bool GenPosIn=0, GenNegIn=0;
      GenmuPosPt= TMath::Sqrt(GenmuPosPx*GenmuPosPx + GenmuPosPy*GenmuPosPy); 
      GenmuNegPt= TMath::Sqrt(GenmuNegPx*GenmuNegPx + GenmuNegPy*GenmuNegPy); 
      
      diMuonsInvMass_Gen->Fill(GenJpsiMass);
      diMuonsPt_Gen->Fill(GenJpsiPt);
      
      if(IsAccept(GenmuPosPt, GenmuPosEta)) {GenPosIn=1;}
      if(IsAccept(GenmuNegPt, GenmuNegEta)) {GenNegIn=1;}
      if(GenPosIn && GenNegIn ) NAccep++;
      Bin_Gen->Fill(gbin);
      
      if(GenPosIn && GenNegIn){
	if(ifile==0){diMuonsRap_Gen0->Fill(GenJpsiRap);}
	if(ifile==1){diMuonsRap_Gen1->Fill(GenJpsiRap);}
	if(ifile==2){diMuonsRap_Gen2->Fill(GenJpsiRap);}
	if(ifile==3){diMuonsRap_Gen3->Fill(GenJpsiRap);}
	if(ifile==4){diMuonsRap_Gen4->Fill(GenJpsiRap);}
	if(ifile==5){diMuonsRap_Gen5->Fill(GenJpsiRap);}
      }
 
      double GenCenWeight =FindCenWeight(gbin);	  
      
      for (Int_t ih = 0; ih < Nptbin; ih++) {
	//adding pT of all pt bins to see diss is cont
	if(iSpec == 1) if(GenJpsiPt>pt_bound[ih] && GenJpsiPt<=pt_bound[ih+1]){diMuonsPt_GenA[ifile][ih]->Fill(GenJpsiPt);}
	if(iSpec == 1) if((GenPosIn==1 && GenNegIn==1)&&(TMath::Abs(GenJpsiRap)>1.6 && TMath::Abs(GenJpsiRap)<2.4) && (GenJpsiPt>pt_bound[ih] && GenJpsiPt<=pt_bound[ih+1])){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenCenWeight);}
	if(iSpec == 2) if((GenPosIn==1 && GenNegIn==1)&& (GenJpsiPt> 0 && GenJpsiPt<30.0) && (TMath::Abs(GenJpsiRap) > pt_bound[ih] && TMath::Abs(GenJpsiRap) <=pt_bound[ih+1])){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenCenWeight);}	
	if(iSpec == 3)  if((GenPosIn==1 && GenNegIn==1) && (gbin>pt_bound[ih] && gbin<=pt_bound[ih+1])){diMuonsInvMass_GenA[ifile][ih]->Fill(GenJpsiMass,GenCenWeight);}
      }
    }//gen loop end
    
    cout<<" accepted no "<< NAccep<<endl;
    dataFile<<" accepted no "<< NAccep<<endl;
     
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
    dataFile<<"Total Entries in reconstructed Tree for pT range "<<fileName[ifile]<<"  "<<nRecEntries<<endl;
    
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
	 && muPos_nValidMuHits > 6){PosPass=1;}	  
      if( (muNeg_found >10 && muNeg_pixeLayers >0 && muNeg_nchi2In <4.0 && muNeg_dxy < 3 && muNeg_dz < 15 && muNeg_nchi2Gl < 6 
	   && muNeg_nValidMuHits >6)){NegPass=1;}
      if((PosIn==1 &&NegIn==1) && (PosPass==1 && NegPass==1)){AllCut=1;}
      
     double RecCenWeight=FindCenWeight(rbin);	  
	  
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
      
	
      for (Int_t ih = 0; ih < Nptbin; ih++) {
	if((JpsiCharge == 0) && (JpsiVprob > 0.01)) {	  
	  //to see cont reco pT
	  if(iSpec == 1) if(JpsiPt>pt_bound[ih]  && JpsiPt<=pt_bound[ih+1])diMuonsPt_RecA[ifile][ih]->Fill(JpsiPt);
	  if(iSpec == 1) if((AllCut==1) && (TMath::Abs(JpsiRap)>1.6 && TMath::Abs(JpsiRap)<2.4) && (JpsiPt>pt_bound[ih]  && JpsiPt<=pt_bound[ih+1]))  {diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecCenWeight);}
	  if(iSpec == 2) if((AllCut==1) && (  JpsiPt > 0 &&  JpsiPt<30.0) && (TMath::Abs(JpsiRap) > pt_bound[ih] && TMath::Abs(JpsiRap) <=pt_bound[ih+1])) {diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecCenWeight);}
	  if(iSpec == 3) if((AllCut==1) &&(rbin>pt_bound[ih]  && rbin<=pt_bound[ih+1]))    {diMuonsInvMass_RecA[ifile][ih]->Fill(JpsiMass,RecCenWeight);}
	}
      }
    }
    
    //new TCanvas;
    //if(ifile==0){diMuonsRap_Gen0->Draw();gPad->Print("plots/diMuonsRap_Gen0_Pt03.png"); new TCanvas; diMuonsRap_Rec0->Draw(); gPad->Print("plots/diMuonsRap_Rec0_Pt03.png");}
    //if(ifile==1){diMuonsRap_Gen1->Draw();new TCanvas; diMuonsRap_Rec1->Draw(); gPad->Print("plots/diMuonsRap_Rec1.png");}
    //if(ifile==2){diMuonsRap_Gen2->Draw();new TCanvas; diMuonsRap_Rec2->Draw(); gPad->Print("plots/diMuonsRap_Rec2.png");}
    //if(ifile==3){diMuonsRap_Gen3->Draw();new TCanvas; diMuonsRap_Rec3->Draw();  gPad->Print("plots/diMuonsRap_Rec3.png");}
    //if(ifile==4){diMuonsRap_Gen4->Draw();new TCanvas; diMuonsRap_Rec4->Draw();  gPad->Print("plots/diMuonsRap_Rec4.png");}
    //if(ifile==5){diMuonsRap_Gen5->Draw();new TCanvas; diMuonsRap_Rec5->Draw();   gPad->Print("plots/diMuonsRap_Rec5.png");}
        
}  // file loop ends

  ///////////////////////////////////////////////////////////////////
  cout<< " adding "<<endl;
  TH1D *diMuonsInvMass_RecA1[100];
  TH1D *diMuonsInvMass_GenA1[100];
  TH1D *diMuonsPt_GenA1[100];
  TH1D *diMuonsPt_RecA1[100];
  
  for(Int_t ih = 0; ih < Nptbin; ih++){

    //diMuonsInvMass_RecA[0][ih]->Sumw2();
    //diMuonsInvMass_GenA[0][ih]->Sumw2();

    diMuonsInvMass_RecA[0][ih]->Scale(scale[0]);
    diMuonsInvMass_GenA[0][ih]->Scale(scale[0]);

    diMuonsInvMass_RecA1[ih] = diMuonsInvMass_RecA[0][ih];
    diMuonsInvMass_GenA1[ih] = diMuonsInvMass_GenA[0][ih];

    diMuonsPt_GenA[0][ih]->Scale(scale[0]);
    diMuonsPt_RecA[0][ih]->Scale(scale[0]);
    
    diMuonsPt_GenA1[ih] = diMuonsPt_GenA[0][ih];
    diMuonsPt_RecA1[ih] = diMuonsPt_RecA[0][ih];
    
    for (int ifile = 1; ifile <= 5; ifile++) {

      //diMuonsInvMass_RecA[ifile][ih]->Sumw2();
      //diMuonsInvMass_GenA[ifile][ih]->Sumw2();
     
      //scale[ifile] =1;      
      diMuonsInvMass_RecA1[ih]->Add(diMuonsInvMass_RecA[ifile][ih],scale[ifile]);
      diMuonsInvMass_GenA1[ih]->Add(diMuonsInvMass_GenA[ifile][ih],scale[ifile]);     
      
      diMuonsPt_GenA1[ih]->Add(diMuonsPt_GenA[ifile][ih],scale[ifile]); 
      diMuonsPt_RecA1[ih]->Add(diMuonsPt_RecA[ifile][ih],scale[ifile]); 
    }
  }
 
 //===========================Fitting=================================================================================//
  // Fit ranges
  double mass_low, mass_high;
  double MassJPsi, WidthJPsi;
  
  // Low mass range J/psi
  MassJPsi = 3.096; WidthJPsi = 0.030;
  mass_low = 2.9; mass_high = 3.3;  // Fit ranges
  
  // Fit Function RBW + Pol2
  TF1 *GAUSPOL = new TF1("GAUSPOL", GausPol2, 2.6, 3.5, 6);
  
  GAUSPOL->SetLineWidth(2.0);
  GAUSPOL->SetLineColor(2.0);
  GAUSPOL->SetParameter(1, MassJPsi);
  GAUSPOL->SetParameter(2, WidthJPsi);
  GAUSPOL->SetParLimits(1, 0.8*MassJPsi, 1.2*MassJPsi);
  GAUSPOL->SetParLimits(2, 0.01*WidthJPsi, 5.0*WidthJPsi);


  //=====================Loop for eff===========================================================
  //define stuff here for error on weighted samples
  double GenNo[100]={0};
  double Eff[100]={0};
  double GenError[100]={0};
  double RecError[100]={0};
  double errEff_cat_S1[100]={0};
  double errEff_cat_S2[100]={0};
  double errEff_cat_S1_1[100]={0},errEff_cat_S1_2[100]={0};
  double errEff_cat_S2_1[100]={0},errEff_cat_S2_2[100]={0};
    

    for (Int_t ih = 0; ih < Nptbin; ih++) {
      
    //int gbinlow= diMuonsInvMass_GenA1[ih]->GetXaxis()->FindBin(3.0);
    //int gbinhi= diMuonsInvMass_GenA1[ih]->GetXaxis()->FindBin(3.2);

    gen_pt[ih] = diMuonsInvMass_GenA1[ih]->IntegralAndError(1, 100, genError);
    gen_ptError[ih]= genError;
    cout<<" gen_pt[ih] "<< gen_pt[ih] <<" error   "<<  gen_ptError[ih]<<endl;
    
    new TCanvas;
    diMuonsInvMass_RecA1[ih]->Fit("GAUSPOL","LEQ", "", mass_low, mass_high);
    
    double JPsiYield = GAUSPOL->GetParameter(0);
    double JPsiMass = GAUSPOL->GetParameter(1);
    double JPsiWidth = GAUSPOL->GetParameter(2);
    
    double MassLow=(JPsiMass-3*JPsiWidth);
    double MassHigh=(JPsiMass+3*JPsiWidth);
    
    int binlow =diMuonsInvMass_RecA1[ih]->GetXaxis()->FindBin(MassLow);
    int binhi =diMuonsInvMass_RecA1[ih]->GetXaxis()->FindBin(MassHigh);
    double binwidth=diMuonsInvMass_RecA1[ih]->GetBinWidth(1);
        
    
    //yield by function 
    //rec_pt[ih] = JPsiYield/binwidth;
    //rec_ptError[ih]= TMath::Sqrt((JPsiYield/binwidth));
        
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
    errEff_cat_S1_2[ih]= (GenError[ih] * GenError[ih] ) - ( RecError[ih] * RecError[ih] );
    errEff_cat_S1[ih]= (errEff_cat_S1_1[ih] * errEff_cat_S1_2[ih]);
    errEff_cat_S2_1[ih]= ( (1 - Eff[ih])* (1 - Eff[ih]) ) / ( GenNo[ih] * GenNo[ih]);
    errEff_cat_S2_2[ih]= (RecError[ih] * RecError[ih]);
    errEff_cat_S2[ih]=errEff_cat_S2_1[ih]*errEff_cat_S2_2[ih];
    Err_Eff_cat_1[ih]=sqrt(errEff_cat_S1[ih] + errEff_cat_S2[ih]);



    //error without weight
 //Err_Eff_cat_1[ih]= Eff_cat_1[ih]*TMath::Sqrt(gen_ptError[ih]*gen_ptError[ih]/(gen_pt[ih]*gen_pt[ih]) + rec_ptError[ih]*rec_ptError[ih]/(rec_pt[ih]* rec_pt[ih]));



    




    cout<<"=================================== This is bin "<<ih<<"================================================="<<endl;
    cout<<"JPsi Yield by integral of histo:  "<< diMuonsInvMass_RecA1[ih]->IntegralAndError(binlow, binhi,recError) <<"  error "<< rec_ptError[ih]<<endl; 
    cout<<"JPsiYield by Gauss yield determ:     "<< JPsiYield/binwidth << " JPsiWidth "<< JPsiWidth<<" JPsiMass "<<JPsiMass <<endl;
    cout<<"JPsi Yield by Function integral:  "<< GAUSPOL->Integral(MassLow,MassHigh)/binwidth <<endl;
    cout<<" Bin "<<ih<< " Reco Jpsi  "<<  rec_pt[ih] <<" Gen Jpsi "<<gen_pt[ih]<<endl;
    cout<<" Eff "<< Eff_cat_1[ih]<<" Error "<<Err_Eff_cat_1[ih]<<endl;
    

    dataFile<<"=================================== This is bin "<<ih<<"============================================="<<endl;
    dataFile<<"JPsi Yield by integral of histo:  "<< diMuonsInvMass_RecA1[ih]->IntegralAndError(binlow, binhi,recError) <<"  error "<< rec_ptError[ih]<<endl; 
    dataFile<<"JPsiYield by Gauss yield det:     "<< JPsiYield/binwidth << " JPsiWidth "<< JPsiWidth<<" JPsiMass "<<JPsiMass <<endl;
    dataFile<<"JPsi Yield by Function integral:  "<< GAUSPOL->Integral(MassLow,MassHigh)/binwidth <<endl;
    dataFile<<" Bin "<<ih<< " Reco Jpsi  "<<  rec_pt[ih] <<" Gen Jpsi "<<gen_pt[ih]<<endl;
    dataFile<<" Eff "<< Eff_cat_1[ih]<<" Error "<<Err_Eff_cat_1[ih]<<endl;
   

    //Drawing histo
    new TCanvas;
    diMuonsInvMass_GenA1[ih]->Draw("EPL");
    
    if (iSpec==1){ new TCanvas; diMuonsPt_GenA1[ih]->Draw(); new TCanvas; diMuonsPt_RecA1[ih]->Draw();}
  
  }
  

  dataFile.close();
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
    
  if(iSpec==1){ gPad->Print("plots/Eff_JPsi_Pt.pdf");gPad->Print("plots/Eff_JPsi_Pt.png");}
  if(iSpec==2){ gPad->Print("plots/Eff_JPsi_Rap_Pt330.pdf");gPad->Print("plots/Eff_JPsi_Rap_Pt330.png");}
  if(iSpec==3){ gPad->Print("plots/Eff_JPsi_Cent.pdf");gPad->Print("plots/Eff_JPsi_Cent.png");}

}


bool IsAccept(Double_t pt, Double_t eta)
{
  return (fabs(eta) < 2.4 &&
	  (    ( fabs(eta) < 1.0 && pt >= 3.4 ) ||
	       (  1.0 <= fabs(eta) && fabs(eta) < 1.5 && pt >= 5.8-2.4*fabs(eta) ) ||
	       (  1.5 <= fabs(eta) && pt >= 3.3667 - 7.0/9.0*fabs(eta)) ));
}



double FindCenWeight(int Bin)
{
  double NCollArray[50]={1747.49,1566.92,1393.97,1237.02,1095.03,979.836,863.228,765.968,677.894,594.481,
			522.453,456.049,399.178,347.174,299.925,258.411,221.374,188.676,158.896,135.117,
			112.481,93.5697,77.9192,63.2538,52.0938,42.3553,33.7461,27.3213,21.8348,17.1722,
			13.5661,10.6604,8.31383,6.37662,5.12347,3.73576,3.07268,2.41358,2.10707,1.76851,};
  return(NCollArray[Bin]);
}

