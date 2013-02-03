#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TCanvas.h"
#include "TROOT.h"
#include "TAxis.h"
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1I.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TVector3.h"
#include "TString.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TEfficiency.h"
#include "iostream"
#include "TGraphAsymmErrors.h"
bool IsAccept(Double_t pt, Double_t eta);

void ReadPatMuWT(){

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
  
  TFile *infile;
  TTree *SingleWTPATMuonTree;
   char fileName[100];
   //boosted sample
   //sprintf(fileName,"../Upsilon1S_OniaTree_All02Feb.root");
   //un boosted sample
   sprintf(fileName,"test_Coll_Unboosted.root");
   
   cout<<" ===================================================================== "<<endl;
   cout<<" opening root file : "<<fileName<<endl;
   
  infile=new TFile(fileName,"R");
  SingleWTPATMuonTree=(TTree*)infile->Get("SingleWTPATMuonTree");



   //Declaration of leaves types
   Int_t           eventNbWTPAT;
   Int_t           runNbWTPAT;
   Int_t           lumiBlockWTPAT;
   Int_t           rbinWTPAT;
   
   Int_t           PAT_vertexNbEv;
   Double_t        PAT_vertexTrkEv;
   Bool_t          PAT_isVtxFakeEv;
   Double_t        PAT_vertexXEv;
   Double_t        PAT_vertexYEv;
   Double_t        PAT_vertexZEv;
   Double_t        PAT_vertexRhoEv;
   Int_t           PAT_eventTrigger1;
   Int_t           PAT_eventTrigger2;
   Int_t           PAT_eventTrigger3;
   Int_t           PAT_eventTrigger4;
   Int_t           PAT_eventTrigger5;
   Int_t           PAT_eventTrigger6;




   Int_t           PAT_GenParNo;
   Int_t           PAT_GenParSize;
   Double_t        PAT_GenvertexXEv;
   Double_t        PAT_GenvertexYEv;
   Double_t        PAT_GenvertexZEv;
   Double_t        PAT_GenParPx[10];
   Double_t        PAT_GenParPy[10];
   Double_t        PAT_GenParPz[10];
   Double_t        PAT_GenParPt[10];
   Double_t        PAT_GenParEta[10];
   Double_t        PAT_GenParPhi[10];
   Double_t        PAT_GenParRap[10];
   Double_t        PAT_GenParCharge[10];
   Double_t        PAT_GenParId[10];
   Double_t        PAT_GenParStatus[10];
   Double_t        PAT_GenParMomId[10];
   Double_t        PAT_GenParMomStatus[10];


   Int_t           WTPATMuSize;
   Double_t        WTPATMuPx[11];
   Double_t        WTPATMuPy[11];
   Double_t        WTPATMuPz[11];
   Double_t        WTPATMuPt[11];
   Double_t        WTPATMuEta[11];
   Double_t        WTPATMuPhi[11];
   Double_t        WTPATMuCharge[11];
   
   Double_t        WTPATMu_found[11];
   Double_t        WTPATMu_nchi2In[11];
   Double_t        WTPATMu_arbitrated[11];
   Double_t        WTPATMu_stationTight[11];
   Double_t        WTPATMu_trackerLayers[11];
   Double_t        WTPATMu_pixeLayers[11];
   Double_t        WTPATMu_dxy[11];
   Double_t        WTPATMu_dz[11];
   
   Double_t        WTPATMu_nValidMuHits[11];
   Double_t        WTPATMu_nchi2Gl[11];
   Int_t           WTPATMu_Trigger1[11];
   Int_t           WTPATMu_Trigger2[11];
   Int_t           WTPATMu_Trigger3[11];
   Int_t           WTPATMu_Trigger4[11];
   Int_t           WTPATMu_Trigger5[11];
   Int_t           WTPATMu_Trigger6[11];
   Int_t           WTPATMu_Trigger7[11];
   Int_t           WTPATMu_Trigger8[11];
   Int_t           WTPATMu_Trigger9[11];
   Int_t           WTPATMu_Trigger10[11];
   Int_t           WTPATMu_Trigger11[11];
   Int_t           WTPATMu_Trigger12[11];
 


   Int_t           WTPATMu_global[11];
   Int_t           WTPATMu_tracker[11];
   Int_t           WTPATMu_sta[11];
   Int_t           WTPATMu_sta_noglb[11];




   // Set branch addresses.
   SingleWTPATMuonTree->SetBranchAddress("eventNbWTPAT",&eventNbWTPAT);
   SingleWTPATMuonTree->SetBranchAddress("runNbWTPAT",&runNbWTPAT);
   SingleWTPATMuonTree->SetBranchAddress("lumiBlockWTPAT",&lumiBlockWTPAT);
   SingleWTPATMuonTree->SetBranchAddress("rbinWTPAT",&rbinWTPAT);

   SingleWTPATMuonTree->SetBranchAddress("PAT_vertexNbEv",&PAT_vertexNbEv);
   SingleWTPATMuonTree->SetBranchAddress("PAT_vertexTrkEv",&PAT_vertexTrkEv);
   SingleWTPATMuonTree->SetBranchAddress("PAT_isVtxFakeEv",&PAT_isVtxFakeEv);
   SingleWTPATMuonTree->SetBranchAddress("PAT_vertexXEv",&PAT_vertexXEv);
   SingleWTPATMuonTree->SetBranchAddress("PAT_vertexYEv",&PAT_vertexYEv);
   SingleWTPATMuonTree->SetBranchAddress("PAT_vertexZEv",&PAT_vertexZEv);
   SingleWTPATMuonTree->SetBranchAddress("PAT_vertexRhoEv",&PAT_vertexRhoEv);
   
   SingleWTPATMuonTree->SetBranchAddress("PAT_eventTrigger1",&PAT_eventTrigger1);
   SingleWTPATMuonTree->SetBranchAddress("PAT_eventTrigger2",&PAT_eventTrigger2);
   SingleWTPATMuonTree->SetBranchAddress("PAT_eventTrigger3",&PAT_eventTrigger3);
   SingleWTPATMuonTree->SetBranchAddress("PAT_eventTrigger4",&PAT_eventTrigger4);
   SingleWTPATMuonTree->SetBranchAddress("PAT_eventTrigger5",&PAT_eventTrigger5);
   SingleWTPATMuonTree->SetBranchAddress("PAT_eventTrigger6",&PAT_eventTrigger6);




   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParNo",&PAT_GenParNo);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParSize",&PAT_GenParSize);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenvertexXEv",&PAT_GenvertexXEv);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenvertexYEv",&PAT_GenvertexYEv);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenvertexZEv",&PAT_GenvertexZEv);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParPx",PAT_GenParPx);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParPy",PAT_GenParPy);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParPz",PAT_GenParPz);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParPt",PAT_GenParPt);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParEta",PAT_GenParEta);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParPhi",PAT_GenParPhi);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParRap",PAT_GenParRap);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParCharge",PAT_GenParCharge);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParId",PAT_GenParId);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParStatus",PAT_GenParStatus);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParMomId",PAT_GenParMomId);
   SingleWTPATMuonTree->SetBranchAddress("PAT_GenParMomStatus",PAT_GenParMomStatus);


   SingleWTPATMuonTree->SetBranchAddress("WTPATMuSize",&WTPATMuSize);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMuPx",WTPATMuPx);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMuPy",WTPATMuPy);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMuPz",WTPATMuPz);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMuPt",WTPATMuPt);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMuEta",WTPATMuEta);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMuPhi",WTPATMuPhi);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMuCharge",WTPATMuCharge);
   
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_found",WTPATMu_found);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_nchi2In",WTPATMu_nchi2In);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_arbitrated",WTPATMu_arbitrated);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_stationTight",WTPATMu_stationTight);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_trackerLayers",WTPATMu_trackerLayers);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_pixeLayers",WTPATMu_pixeLayers);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_dxy",WTPATMu_dxy);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_dz",WTPATMu_dz);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_nValidMuHits",WTPATMu_nValidMuHits);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_nchi2Gl",WTPATMu_nchi2Gl);
   
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger1",WTPATMu_Trigger1);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger2",WTPATMu_Trigger2);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger3",WTPATMu_Trigger3);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger4",WTPATMu_Trigger4);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger5",WTPATMu_Trigger5);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger6",WTPATMu_Trigger6);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger7",WTPATMu_Trigger7);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger8",WTPATMu_Trigger8);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger9",WTPATMu_Trigger9);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger10",WTPATMu_Trigger10);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger11",WTPATMu_Trigger11);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_Trigger12",WTPATMu_Trigger12);
   
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_global",WTPATMu_global);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_tracker",WTPATMu_tracker);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_sta",WTPATMu_sta);
   SingleWTPATMuonTree->SetBranchAddress("WTPATMu_sta_noglb",WTPATMu_sta_noglb);

   




   TH1D *muPt = new TH1D("muPt","muPt", 100,0,10.0);
   muPt->Sumw2();
   
   TH1D *muEta = new TH1D("muEta","muEta", 100,-3.0,3.0);
   muEta->Sumw2();


   TH1D *muPtWT = new TH1D("muPtWT","muPtWT", 100,0,10.0);
   muPtWT->Sumw2();
   
   TH1D *muEtaWT = new TH1D("muEtaWT","muEtaWT", 100,-3.0,3.0);
   muEtaWT->Sumw2();
   

   TH1D *muPhi = new TH1D("muPhi","muPhi", 100,-5.0,5.0);
   muPhi->Sumw2();

   TH1D *muDxy = new TH1D("muDxy","muDxy", 100,-30.0,30.0);
   TH1D *muDz = new TH1D("muDz","muDz", 100,-50.0,50.0);



   TH1D *VtxX = new TH1D("VtxX","VtxX", 100,-30.0,30.0);
   TH1D *VtxY = new TH1D("VtxY","VtxY", 100,-30.0,30.0);
   TH1D *VtxZ = new TH1D("VtxZ","VtxZ", 100,-50.0,50.0);


   TH1D *genmuPt = new TH1D("genmuPt","genmuPt", 100,0,10.0);
   genmuPt->Sumw2();
   TH1D *genmuEta = new TH1D("genmuEta","genmuEta", 100,-3.0,3.0);
   genmuEta->Sumw2();
   TH1D *genmuPhi = new TH1D("genmuPhi","genmuPhi", 100,-5.0,5.0);
   genmuPhi->Sumw2();

   

   Long64_t nentries = SingleWTPATMuonTree->GetEntries();
   
   for (Long64_t i=0; i<nentries;i++) {
     
     SingleWTPATMuonTree->GetEntry(i);
     
     if(i%25000==0){cout<<i<<endl;}

     VtxX->Fill(PAT_vertexXEv); 
     VtxY->Fill(PAT_vertexYEv); 
     VtxZ->Fill(PAT_vertexZEv);

     
     if(PAT_GenParSize>0){
              
       for (Int_t genpar1=0; genpar1<PAT_GenParSize;genpar1++){
	 
	 int genmuIn=0;

	 if(TMath::Abs(PAT_GenParId[genpar1])==13 && IsAccept(PAT_GenParPt[genpar1], PAT_GenParEta[genpar1]) ){genmuIn=1;}else{genmuIn=0;}
	
	   if(TMath::Abs(PAT_GenParId[genpar1])==13 && genmuIn==1 ){
	 genmuPt->Fill(PAT_GenParPt[genpar1]);
	 genmuEta->Fill(PAT_GenParEta[genpar1]);
	 genmuPhi->Fill(PAT_GenParPhi[genpar1]);
	 }
       }
     
     }//gen par size >0


     if(WTPATMuSize>0){
       //cout<<" PAT mu size "<<WTPATMuSize<<endl;
       for (Int_t patmu1=0; patmu1<WTPATMuSize;patmu1++){
	 //cout<<"PatMu Eta: "<<WTPATMuEta[patmu1]<<endl;	 
	    
	 int patmuPass=0;
	 int patmuIn=0;

	 if( WTPATMu_trackerLayers[patmu1] > 5.0 && TMath::Abs(WTPATMu_nchi2In[patmu1]) < 1.8 && TMath::Abs(WTPATMu_dxy[patmu1]) < 3.0 
	     && TMath::Abs(WTPATMu_dz[patmu1]) < 30.0 &&  WTPATMu_arbitrated[patmu1]==1 && WTPATMu_stationTight[patmu1]==1 
	     && WTPATMu_tracker[patmu1]==1 ){patmuPass=1;}else{patmuPass=0;}	  

	 if(IsAccept(WTPATMuPt[patmu1],WTPATMuEta[patmu1])){patmuIn=1;}else{patmuIn=0;}


	 if( WTPATMu_tracker[patmu1]==1){
	   muDxy->Fill(WTPATMu_dxy[patmu1]);
	   muDz->Fill(WTPATMu_dz[patmu1]);
	 }
	 
	 //patmuPass=1;
	 //patmuIn=1;


	 if(patmuPass==1 && patmuIn==1 ){
	   
	   muPt->Fill(WTPATMuPt[patmu1]);
	   muEta->Fill(WTPATMuEta[patmu1]);
	   muPhi->Fill(WTPATMuPhi[patmu1]);
	   }


	 if(patmuPass==1 && patmuIn==1 && WTPATMu_Trigger1[patmu1]==1){

	 //if(patmuPass==1 && patmuIn==1 && PAT_eventTrigger4==1){
	   muPtWT->Fill(WTPATMuPt[patmu1]);
	   muEtaWT->Fill(WTPATMuEta[patmu1]);
	   
	 }

	 //for (Int_t patmu2=patmu1+1; patmu2<WTPATMuSize;patmu2++){ 
	 //}
       }
     }

   }
   
   //TEfficeincy *t=new TEfficiency(muEta,genmuEta);
   //new TCanvas;
   //t->Draw();

   //TH1D *hratio1 = (TH1D*)h2->Clone("ratio")
   
   

   new TCanvas;
   genmuPt->Draw();
   gPad->SaveAs("genmuPt.png");
   new TCanvas;
   genmuEta->Draw();
   gPad->SaveAs("genmuEta.png");
   new TCanvas;
   genmuPhi->Draw();
   gPad->SaveAs("genmuPhi.png");

   new TCanvas;
   muPt->Draw();
   gPad->SaveAs("muPt.png");

   new TCanvas;
   muEta->Draw();
   gPad->SaveAs("muEta.png");

   new TCanvas;
   muPhi->Draw();
   gPad->SaveAs("muPhi.png");





   new TCanvas;
   muPtWT->Draw();
   gPad->SaveAs("muPtWT.png");

   new TCanvas;
   muEtaWT->Draw();
   gPad->SaveAs("muEtaWT.png");

   



   TH1D* RatioEta=(TH1D*)muEta->Clone("ratioEta");
   RatioEta->Divide(genmuEta);
   new TCanvas;
   RatioEta->Draw("E");



   TH1D* RatioPt=(TH1D*)muPt->Clone("ratioPt");
   RatioPt->Divide(genmuPt);
   new TCanvas;
   RatioPt->Draw("E");



   TH1D* RatioEtaT=(TH1D*)muEtaWT->Clone("ratioEtaT");
   RatioEtaT->Divide(muEta);
   new TCanvas;
   RatioEtaT->Draw("E");



   TH1D* RatioPtT=(TH1D*)muPtWT->Clone("ratioPtT");
   RatioPtT->Divide(muPt);
   RatioPtT->GetYaxis()->SetRangeUser(0.0,1.0);
   new TCanvas;
   RatioPtT->Draw("E");
   /*
   TEfficiency* ptEff = 0;
   ptEff = new TEfficiency(*muPtWT,*muPt);
   new TCanvas;
   //ptEff->GetYaxis()->SetRangeUser(0.0,1.0);
   ptEff->Draw("AP");
   RatioPtT->Draw("same");

   TEfficiency* EtaEff = 0;
   EtaEff = new TEfficiency(*muEtaWT,*muEta);
   new TCanvas;
   EtaEff->Draw("AP");
   */

   //TGraphAsymmErrors::TGraphAsymmErrors(const TH1* pass,const TH1* total,Option_t* opt) 
   TGraphAsymmErrors *GrfTrgPt=0;

   GrfTrgPt=new TGraphAsymmErrors(muPtWT,muPt);
   GrfTrgPt->GetYaxis()->SetRangeUser(0.0,1.0);
   GrfTrgPt->GetXaxis()->SetTitle("#mu p_{T}");
   new TCanvas;
   GrfTrgPt->Draw("AP");
   gPad->SaveAs("TrgEffPt.png");
   
   TGraphAsymmErrors *GrfTrgEta=0;
   GrfTrgEta=new TGraphAsymmErrors(muEtaWT,muEta);
   GrfTrgEta->GetYaxis()->SetRangeUser(0.0,1.0);
   GrfTrgEta->GetXaxis()->SetTitle("#eta^{#mu}");
   new TCanvas;
   GrfTrgEta->Draw("AP");
   gPad->SaveAs("TrgEffEta.png");


   return;



   TCanvas *CanVtxX=new TCanvas;
   CanVtxX->SetLogy();
   VtxX->Draw();
   gPad->SaveAs("VtxX.png");


   TCanvas *CanVtxY=new TCanvas;
   CanVtxY->SetLogy();
   VtxY->Draw();
   gPad->SaveAs("VtxY.png");



   TCanvas *CanVtxZ=new TCanvas;
   CanVtxZ->SetLogy();
   VtxZ->Draw();
   gPad->SaveAs("VtxZ.png");



   TCanvas *CanDxy=new TCanvas;
   CanDxy->SetLogy();
   muDxy->Draw();
   gPad->SaveAs("muDxy.png");

   TCanvas *CanDz=new TCanvas;
   CanDz->SetLogy();
   muDz->Draw();
   gPad->SaveAs("muDz.png");





}




bool IsAccept(Double_t pt, Double_t eta)
{
  return (TMath::Abs(eta) < 2.4 && pt > 4.0 );
  //return ( eta > -2.4 && eta < 1.46 && pt > 4.0 );
}
