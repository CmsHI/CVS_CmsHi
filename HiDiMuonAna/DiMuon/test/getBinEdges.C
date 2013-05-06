#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <TF1.h>
#include <TH2D.h>
#include <TH1.h>
#include <TH1D.h>
#include <TLatex.h>
#include <TMath.h>
#include <TNtuple.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TSystem.h>

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
#include "TObjArray.h"
#include "TGaxis.h"
#include "TLine.h"
#include "TColor.h"
#include "TStyle.h"
#include <iomanip>

using namespace std;

//------------------------------------------------------------------------
void getBinEdges(const int nbins     = 3, // 100/nbins= 5     
		 int choseVar        = 7, //7: ntrks; 4: trunc sum; 5: trunc+ ... 
		 bool bSavePlots     = true,
		 int choseCase       = 1) // 0: pA; 1: pp
{
  
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptTitle(1);
  //gStyle->SetOptStat("nmr");
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetTitleFillColor(0);
  gStyle->SetStatColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameLineColor(kBlack);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetTextSize(0.04);
  gStyle->SetTextFont(42);
  gStyle->SetLabelFont(42,"xyz");
  gStyle->SetTitleFont(42,"xyz");
  gStyle->SetTitleSize(0.048,"xyz");
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.065);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetTitleXOffset(1.15);
  gStyle->SetTitleYOffset(1.2);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetCanvasDefH(600);
  gStyle->SetCanvasDefW(600);
  gStyle->SetHistMinimumZero(kTRUE);
  gStyle->SetErrorX(0); // disable if you want to draw horizontal error bars, e.g. when having variable bin size
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(0.8);
  gROOT->ForceStyle();
  













  const char* asLabels[8] = {"",
			     "HFtowers","HFtowersPlus","HFtowersMinus",
			     "HFtowersTrunc","HFtowersPlusTrunc","HFtowersMinusTrunc",
			     "Tracks"}; 
  const string label = asLabels[choseVar];

 TH1D::SetDefaultSumw2();
 bool binHF           = label.compare("HFtowers")          == 0;
 bool binHFplus       = label.compare("HFtowersPlus")      == 0;
 bool binHFminus      = label.compare("HFtowersMinus")     == 0;
 bool binHFTrunc      = label.compare("HFtowersTrunc")     == 0;
 bool binHFplusTrunc  = label.compare("HFtowersPlusTrunc") == 0;
 bool binHFminusTrunc = label.compare("HFtowersMinusTrunc")== 0;
 bool binZDC          = label.compare("ZDC")               == 0;
 bool binZDCplus      = label.compare("ZDCplus")           == 0;
 bool binZDCminus     = label.compare("ZDCminus")          == 0;
 bool binNpix         = label.compare("PixelHits")         == 0;
 bool binNpixTrks     = label.compare("PixelTracks")       == 0;
 bool binNtrks        = label.compare("Tracks")            == 0;

 //



 //Intput files with HiTrees
 const int nTrees           = 2;
 
 string inFileNames[nTrees] = {"rootFiles/pPb_MinBiasTree_v5_211256_json.root","rootFiles/pp_MinBiasTree_211792.root"};

 TChain * t                 = new TChain("hiEvtAnalyzer/HiTree");
 t->Add(inFileNames[choseCase].data());
 

 // number of bins in histogram: 
 double xmax=100;
 if(binHFTrunc) xmax = 300;
 if(binNtrks) xmax   = 500;
 int bins            = xmax;

 //============== Add some histogram arrays here =================================//
char OutTextFile[100]; 

 if(choseCase ==0) sprintf(OutTextFile,"CentValues_pPb.tex");
 if(choseCase ==1) sprintf(OutTextFile,"CentValues_pp.tex");


 ofstream dataFile(Form(OutTextFile),ios::app);
 
char Str1[100],Str2[100],Str3[100]; 
sprintf(Str1,"\\hline");
sprintf(Str2,"\\\\");
sprintf(Str3,"\\");

dataFile<<Str3<<"documentstyle[12 pt]{article}"<<endl;
dataFile<<Str3<<"begin{document}"<<endl<<endl;
  

 //Centrality Histogram array
 char nameCent[10][500];
 
 char nameAvHF[10][500];
 char nameNTrk[10][500];


 char nameAvHF_1[10][500];
 char nameNTrk_1[10][500];

 char nameAvHF_2[10][500];
 char nameNTrk_2[10][500];


 char nameAvHF_3[10][500];
 char nameNTrk_3[10][500];
  
  
 TH1D *DiMuonCent[20];
 
 TH1D *DiMuonAvHF[20];
 TH1D *DiMuonNTrk[20];

 TH1D *DiMuonAvHF_1[20];
 TH1D *DiMuonNTrk_1[20];

 TH1D *DiMuonAvHF_2[20];
 TH1D *DiMuonNTrk_2[20];

 TH1D *DiMuonAvHF_3[20];
 TH1D *DiMuonNTrk_3[20];
 
 
 Int_t Nptbin =4;

 for (Int_t ih = 1; ih < Nptbin; ih++) {
   sprintf(nameCent[ih],"DiMuonCent_%d",ih);
   
   sprintf(nameAvHF[ih],"DiMuonAvHF_%d",ih);
   sprintf(nameNTrk[ih],"DiMuonNTrk_%d",ih);

   sprintf(nameAvHF_1[ih],"DiMuonAvHF_1_%d",ih);
   sprintf(nameNTrk_1[ih],"DiMuonNTrk_1_%d",ih);


   sprintf(nameAvHF_2[ih],"DiMuonAvHF_2_%d",ih);
   sprintf(nameNTrk_2[ih],"DiMuonNTrk_2_%d",ih);


   sprintf(nameAvHF_3[ih],"DiMuonAvHF_3_%d",ih);
   sprintf(nameNTrk_3[ih],"DiMuonNTrk_3_%d",ih);
   


   cout<<" Name "<<nameCent[ih]<<"  "<<nameAvHF[ih]<<"    "<<nameNTrk[ih]<<endl;

   cout<<" Name "<<nameCent[ih]<<"  "<<nameAvHF_1[ih]<<"    "<<nameNTrk_1[ih]<<endl;

   cout<<" Name "<<nameCent[ih]<<"  "<<nameAvHF_2[ih]<<"    "<<nameNTrk_2[ih]<<endl;

   cout<<" Name "<<nameCent[ih]<<"  "<<nameAvHF_3[ih]<<"    "<<nameNTrk_3[ih]<<endl;
   


   DiMuonCent[ih]= new TH1D(nameCent[ih],nameCent[ih], 100,0.0,100.0); 
   DiMuonCent[ih]->GetXaxis()->SetTitle("Centrality");
   DiMuonCent[ih]->GetYaxis()->SetTitle("Events");
   
   DiMuonAvHF[ih]= new TH1D(nameAvHF[ih],nameAvHF[ih], 100,0.0,100.0); 
   DiMuonAvHF[ih]->GetXaxis()->SetTitle("sum ET HF |#eta| > 4");
   DiMuonAvHF[ih]->GetYaxis()->SetTitle("Events");
   
   DiMuonNTrk[ih]= new TH1D(nameNTrk[ih],nameNTrk[ih], 300,0.0,300.0); 
   DiMuonNTrk[ih]->GetXaxis()->SetTitle("Tracks");
   DiMuonNTrk[ih]->GetYaxis()->SetTitle("Events");




   DiMuonAvHF_1[ih]= new TH1D(nameAvHF_1[ih],nameAvHF_1[ih], 100,0.0,100.0); 
   DiMuonAvHF_1[ih]->GetXaxis()->SetTitle("1 sum ET HF |#eta| > 4");
   DiMuonAvHF_1[ih]->GetYaxis()->SetTitle("1 Events");
   
   DiMuonNTrk_1[ih]= new TH1D(nameNTrk_1[ih],nameNTrk_1[ih], 300,0.0,300.0); 
   DiMuonNTrk_1[ih]->GetXaxis()->SetTitle("1 Tracks");
   DiMuonNTrk_1[ih]->GetYaxis()->SetTitle("1 Events");





   DiMuonAvHF_2[ih]= new TH1D(nameAvHF_2[ih],nameAvHF_2[ih], 100,0.0,10.0); 
   DiMuonAvHF_2[ih]->GetXaxis()->SetTitle("2 sum ET HF |#eta| > 4");
   DiMuonAvHF_2[ih]->GetYaxis()->SetTitle("2 Events");
   
   DiMuonNTrk_2[ih]= new TH1D(nameNTrk_2[ih],nameNTrk_2[ih], 100,0.0,10.0); 
   DiMuonNTrk_2[ih]->GetXaxis()->SetTitle("2 Tracks");
   DiMuonNTrk_2[ih]->GetYaxis()->SetTitle("2 Events");



   DiMuonAvHF_3[ih]= new TH1D(nameAvHF_3[ih],nameAvHF_3[ih], 100,0.0,10.0); 
   DiMuonAvHF_3[ih]->GetXaxis()->SetTitle("3 sum ET HF |#eta| > 4");
   DiMuonAvHF_3[ih]->GetYaxis()->SetTitle("3 Events");
   
   DiMuonNTrk_3[ih]= new TH1D(nameNTrk_3[ih],nameNTrk_3[ih], 100,0.0,10.0); 
   DiMuonNTrk_3[ih]->GetXaxis()->SetTitle("3 Tracks");
   DiMuonNTrk_3[ih]->GetYaxis()->SetTitle("3 Events");
    



  }
  


 DiMuonAvHF[1]->SetLineColor(2);
 DiMuonAvHF[1]->SetMarkerColor(2);

 DiMuonAvHF[2]->SetLineColor(1);
 DiMuonAvHF[2]->SetMarkerColor(1);

 DiMuonAvHF[3]->SetLineColor(4);
 DiMuonAvHF[3]->SetMarkerColor(4);


 DiMuonNTrk[1]->SetLineColor(2);
 DiMuonNTrk[1]->SetMarkerColor(2);

 DiMuonNTrk[2]->SetLineColor(1);
 DiMuonNTrk[2]->SetMarkerColor(1);

 DiMuonNTrk[3]->SetLineColor(4);
 DiMuonNTrk[3]->SetMarkerColor(4);


 DiMuonAvHF_1[1]->SetLineColor(2);
 DiMuonAvHF_1[1]->SetMarkerColor(2);

 DiMuonAvHF_1[2]->SetLineColor(1);
 DiMuonAvHF_1[2]->SetMarkerColor(1);

 DiMuonAvHF_1[3]->SetLineColor(4);
 DiMuonAvHF_1[3]->SetMarkerColor(4);


 DiMuonNTrk_1[1]->SetLineColor(2);
 DiMuonNTrk_1[1]->SetMarkerColor(2);

 DiMuonNTrk_1[2]->SetLineColor(1);
 DiMuonNTrk_1[2]->SetMarkerColor(1);

 DiMuonNTrk_1[3]->SetLineColor(4);
 DiMuonNTrk_1[3]->SetMarkerColor(4);



 DiMuonAvHF_2[1]->SetLineColor(2);
 DiMuonAvHF_2[1]->SetMarkerColor(2);

 DiMuonAvHF_2[2]->SetLineColor(1);
 DiMuonAvHF_2[2]->SetMarkerColor(1);

 DiMuonAvHF_2[3]->SetLineColor(4);
 DiMuonAvHF_2[3]->SetMarkerColor(4);


 DiMuonNTrk_2[1]->SetLineColor(2);
 DiMuonNTrk_2[1]->SetMarkerColor(2);

 DiMuonNTrk_2[2]->SetLineColor(1);
 DiMuonNTrk_2[2]->SetMarkerColor(1);

 DiMuonNTrk_2[3]->SetLineColor(4);
 DiMuonNTrk_2[3]->SetMarkerColor(4);



 DiMuonAvHF_3[1]->SetLineColor(2);
 DiMuonAvHF_3[1]->SetMarkerColor(2);

 DiMuonAvHF_3[2]->SetLineColor(1);
 DiMuonAvHF_3[2]->SetMarkerColor(1);

 DiMuonAvHF_3[3]->SetLineColor(4);
 DiMuonAvHF_3[3]->SetMarkerColor(4);


 DiMuonNTrk_3[1]->SetLineColor(2);
 DiMuonNTrk_3[1]->SetMarkerColor(2);

 DiMuonNTrk_3[2]->SetLineColor(1);
 DiMuonNTrk_3[2]->SetMarkerColor(1);

 DiMuonNTrk_3[3]->SetLineColor(4);
 DiMuonNTrk_3[3]->SetMarkerColor(4);






  TH1D *NTrk = new TH1D("NTrk","NTrk",300,0,300);
  NTrk->GetXaxis()->SetTitle("# Tracks");


  TH1D *HFEtTr = new TH1D("HFEtTr","HFEtTr",100,0,100);
  HFEtTr->GetXaxis()->SetTitle("HF Et");
  

  
 TH1 *phVar = new TH1D("phVar","phVar",bins,0,xmax);
 phVar->SetDirectory(0);


 //Output files and tables

 ofstream txtfile(Form("out/%s_bins%d_doPa%d.txt",asLabels[choseVar],nbins,choseCase));

 txtfile << "First input tree: " << inFileNames[choseCase].data() << endl;



 //Setting up variables and branches
 vector<float> values;
 vector<float> values_norm;

 float vtxZ, hf, hfplus, hfpluseta4, hfminuseta4, hfminus, hfhit, ee, eb, zdc, zdcplus, zdcminus;
 int run, lumi, npix, npixtrks, ntrks;
 t->SetBranchAddress("vz",&vtxZ);
 t->SetBranchAddress("run",&run);
 t->SetBranchAddress("lumi",&lumi);

 t->SetBranchAddress("hiHF",		&hf);
 t->SetBranchAddress("hiHFplus",	&hfplus);
 t->SetBranchAddress("hiHFplusEta4",	&hfpluseta4);
 t->SetBranchAddress("hiHFminus",	&hfminus);
 t->SetBranchAddress("hiHFminusEta4",	&hfminuseta4);
 t->SetBranchAddress("hiHFhit",		&hfhit);
 t->SetBranchAddress("hiZDC",		&zdc);
 t->SetBranchAddress("hiZDCplus",	&zdcplus);
 t->SetBranchAddress("hiZDCminus",	&zdcminus);
 t->SetBranchAddress("hiEE",		&ee);
 t->SetBranchAddress("hiEB",		&eb);
 t->SetBranchAddress("hiNpix",		&npix);
 t->SetBranchAddress("hiNpixelTracks",	&npixtrks);
 t->SetBranchAddress("hiNtracks",	&ntrks);

 TChain *tskim = new TChain("skimanalysis/HltTree");
 tskim->Add(inFileNames[choseCase].data());

 int selHFp=0;	tskim->SetBranchAddress("phfPosFilter1", &selHFp);
 int selHFm=0;	tskim->SetBranchAddress("phfNegFilter1", &selHFm);
 int selVtx=0;	tskim->SetBranchAddress("pprimaryvertexFilter", &selVtx);
 int selBS=0;	tskim->SetBranchAddress("pBeamScrapingFilter", &selBS);
 int selNoPU=0; tskim->SetBranchAddress("pVertexFilterCutGplus", &selNoPU);

 //TChain * thlt = new TChain("hltanalysis/HltTree");
 //thlt->Add(inFileNames[0].data());
 //int trig1;	thlt->SetBranchAddress("HLT_PAZeroBiasPixel_SingleTrack_v1", &trig1);


 //Event loop
 unsigned int Nevents = t->GetEntries();
 txtfile << "Number of events = " << Nevents << endl << endl;
 
 Double_t HFTrunc;
 Double_t AvHFTrunc_pa = 14.73;
 Double_t AvNTrk_pa = 40.58;

 Double_t AvHFTrunc_pp = 3.55;
 Double_t AvNTrk_pp= 10.24;
 
 Double_t AvHFTrunc;
 Double_t AvNTrk;

 Int_t Bin1_NTrk,Bin2_NTrk,Bin3_NTrk;
 Int_t Bin1_HF,Bin2_HF,Bin3_HF;

 
 if(choseCase ==0) {AvHFTrunc = AvHFTrunc_pa; AvNTrk = AvNTrk_pa;}
 if(choseCase ==1) {AvHFTrunc = AvHFTrunc_pp; AvNTrk = AvNTrk_pp;}






 for(unsigned int iev = 0; iev < Nevents; iev++) 
   {
     
     HFTrunc =0;

     Bin1_NTrk=0;
     Bin2_NTrk=0;
     Bin3_NTrk=0;

     Bin1_HF=0;
     Bin2_HF=0;
     Bin3_HF=0;


     if(iev%100000 == 0) cout<<"Processing event: " << iev << endl;
     t->GetEntry(iev);
     //thlt->GetEntry(iev);
     tskim->GetEntry(iev);
     
     float parameter = -1;
     if(binHF)    parameter = hf;
     if(binHFplus)  parameter = hfplus;
     if(binHFminus) parameter = hfminus;
     if(binHFTrunc) parameter = hfpluseta4+hfminuseta4;
     if(binHFplusTrunc)  parameter = hfpluseta4;
     if(binHFminusTrunc) parameter = hfminuseta4;
     if(binZDC)      parameter = zdc;
     if(binZDCplus)  parameter = zdcplus;
     if(binZDCminus) parameter = zdcminus;
     if(binNpix)     parameter = npix;
     if(binNpixTrks) parameter = npixtrks;
     if(binNtrks)    parameter = ntrks;
     
     
     
     HFTrunc =hfpluseta4+hfminuseta4;
     

     if( (HFTrunc/AvHFTrunc) >= 0 && (HFTrunc/AvHFTrunc)   <1.0 ){Bin1_HF=1;}else{Bin1_HF=0;}
     if( (HFTrunc/AvHFTrunc) >=1.0 && (HFTrunc/AvHFTrunc)   <2.0 ){Bin2_HF=1;}else{Bin2_HF=0;}
     if( (HFTrunc/AvHFTrunc) >=2.0 ){Bin3_HF=1;}else{Bin3_HF=0;}
       

     if( (ntrks/AvNTrk) >= 0 &&  (ntrks/AvNTrk) <1.0 ){ Bin1_NTrk= 1;}else{Bin1_NTrk= 0;}
     if( (ntrks/AvNTrk) >= 1.0 &&  (ntrks/AvNTrk) <2.0 ){ Bin2_NTrk= 1;}else{Bin2_NTrk= 0;}
     if( (ntrks/AvNTrk) >=2.0){ Bin3_NTrk= 1;}else{Bin3_NTrk= 0;}




     if(selBS==1 && selVtx==1 && selHFm==1 && selHFp==1 && selNoPU==1) // event selection
       {

	 NTrk->Fill(ntrks);
	 HFEtTr->Fill(HFTrunc);


	 
	 if(Bin1_HF==1){DiMuonNTrk[1]->Fill(ntrks);}
	 if(Bin2_HF==1){DiMuonNTrk[2]->Fill(ntrks);}
	 if(Bin3_HF==1){DiMuonNTrk[3]->Fill(ntrks);}
	 

	
	 if(Bin1_NTrk==1){DiMuonAvHF[1]->Fill(HFTrunc);}
	 if(Bin2_NTrk==1){DiMuonAvHF[2]->Fill(HFTrunc);}
	 if(Bin3_NTrk==1){DiMuonAvHF[3]->Fill(HFTrunc);}
	 







	 if(Bin1_NTrk==1){DiMuonNTrk_1[1]->Fill(ntrks);}
	 if(Bin2_NTrk==1){DiMuonNTrk_1[2]->Fill(ntrks);}
	 if(Bin3_NTrk==1){DiMuonNTrk_1[3]->Fill(ntrks);}
	 

	
	 if(Bin1_HF==1){DiMuonAvHF_1[1]->Fill(HFTrunc);}
	 if(Bin2_HF==1){DiMuonAvHF_1[2]->Fill(HFTrunc);}
	 if(Bin3_HF==1){DiMuonAvHF_1[3]->Fill(HFTrunc);}

	 // Double_t AvHFTrunc=14.73;
	 // Double_t AvNTrk=40.58;

	 Double_t Trk_t,HF_t;

	 Trk_t=ntrks/AvNTrk;
	 HF_t=HFTrunc/AvHFTrunc;


	 if(Bin1_HF==1){DiMuonNTrk_2[1]->Fill(Trk_t);}
	 if(Bin2_HF==1){DiMuonNTrk_2[2]->Fill(Trk_t);}
	 if(Bin3_HF==1){DiMuonNTrk_2[3]->Fill(Trk_t);}
	 

	
	 if(Bin1_NTrk==1){DiMuonAvHF_2[1]->Fill(HF_t);}
	 if(Bin2_NTrk==1){DiMuonAvHF_2[2]->Fill(HF_t);}
	 if(Bin3_NTrk==1){DiMuonAvHF_2[3]->Fill(HF_t);}



	 //=======================
	 if(Bin1_HF==1){DiMuonAvHF_3[1]->Fill(HF_t);}
	 if(Bin2_HF==1){DiMuonAvHF_3[2]->Fill(HF_t);}
	 if(Bin3_HF==1){DiMuonAvHF_3[3]->Fill(HF_t);}
	 

	 if(Bin1_NTrk==1){DiMuonNTrk_3[1]->Fill(Trk_t);}
	 if(Bin2_NTrk==1){DiMuonNTrk_3[2]->Fill(Trk_t);}
	 if(Bin3_NTrk==1){DiMuonNTrk_3[3]->Fill(Trk_t);}
	 

	 values.push_back(parameter);
	 phVar->Fill(parameter);
       



       }//event selection
   }// event loop





 //================================ Get All histos ================================//

 for(int i=1;i<4;i++){
   new TCanvas;
   gPad->SetLogy(1);
   DiMuonNTrk_1[i]->Draw();
 }
 


 for(int i=1;i<4;i++){
   
   new TCanvas;
   gPad->SetLogy(1);
   DiMuonAvHF_1[i]->Draw();
 }
 
 



/*
 for(int i=1;i<4;i++){
   
   new TCanvas;
   gPad->SetLogy(1);
   DiMuonAvHF[i]->Draw();
 }
 
 for(int i=1;i<4;i++){
   new TCanvas;
   gPad->SetLogy(1);
   DiMuonNTrk[i]->Draw();
   
 }



 for(int i=1;i<4;i++){
   DiMuonAvHF_2[i]->GetXaxis()->SetRangeUser(0,10.0);
   new TCanvas;
   gPad->SetLogy(1);
   DiMuonAvHF_2[i]->Draw();
 }
 
 for(int i=1;i<4;i++){
   DiMuonNTrk_2[i]->GetXaxis()->SetRangeUser(0,10.0);
   new TCanvas;
   gPad->SetLogy(1);
   DiMuonNTrk_2[i]->Draw();
   
 }
 */




 new TCanvas;
 gPad->SetLogy(1);
 NTrk->Draw();
 
 new TCanvas;
 gPad->SetLogy(1);
 HFEtTr->Draw();

 //================================================================================//
 //Get values 


 // ==================================== Tables Start ================================ //


 txtfile <<" NTrk/<NTrk>   "<< " % Entry "<<" <HF_Bin>     "<<endl;



 dataFile<<Str3<<"begin{table}[htbH]"<<endl;
 dataFile<<Str3<<"begin{center}"<<endl;
 dataFile<<Str3<<"caption{}"<<endl; 
 dataFile<<Str3<<"label{}"<<endl;
 dataFile<<Str3<<"begin{tabular}{c|c|c|c|c}"<<endl;
 dataFile<<Str1<<endl;
 dataFile<<" $N_{Trk}/<N_{Trk}>$ "<< "  &$\\% \\, of \\, events $  " << "&$\\sigma$ tracks  "<<"&$<HF E_{T}>$"<< "&$HF E_{T}/<HF E_{T}>$"<<Str2<<endl;
 dataFile<<Str1<<endl;

 Double_t SumEntries_NTrk =0;
for(int i=1;i<4;i++){

  dataFile <<"$[ "<<i-1<<" - "<<i<<")$    &"<<setprecision(3)<<100.0*(DiMuonNTrk_1[i]->GetEntries()/NTrk->GetEntries())<<" &"<<setprecision(3)<<DiMuonNTrk_3[i]->GetMean()<<
    "   &"<<setprecision(3)<<DiMuonAvHF[i]->GetMean()<<" & "<<DiMuonAvHF_2[i]->GetMean()<<Str2<<endl;
  SumEntries_NTrk = SumEntries_NTrk +  (DiMuonNTrk_1[i]->GetEntries()/NTrk->GetEntries());
 
}

 cout<<"SumEntries Trk: "<<SumEntries_NTrk<<endl;

 dataFile<<Str1<<endl;
 dataFile<<Str3<<"end{tabular}"<<endl;
 dataFile<<Str3<<"end{center}"<<endl;
 dataFile<<Str3<<"end{table}"<<endl;
 dataFile<<endl<<endl<<endl;






 dataFile<<Str3<<"begin{table}[htbH]"<<endl;
 dataFile<<Str3<<"begin{center}"<<endl;
 dataFile<<Str3<<"caption{}"<<endl; 
 dataFile<<Str3<<"label{}"<<endl;
 dataFile<<Str3<<"begin{tabular}{c|c|c|c|c}"<<endl;
 dataFile<<Str1<<endl;
 dataFile<<" $E_{T}/<E_{T}>$ "<< "  &$\\% \\, of \\, events$  " << "&$\\sigma$ E$_{T}$ " <<"&$<N_{Trk}>$"<< "&$N_{Trk}/<N_{Trk}>$"<<          Str2<<endl;
 dataFile<<Str1<<endl;

 Double_t SumEntries_HF =0;

 for(int i=1;i<4;i++){
     
   dataFile <<"$[ "<<i-1<<" - "<<i<<")$    &"<<setprecision(3)<<100.0*(DiMuonAvHF_1[i]->GetEntries()/HFEtTr->GetEntries())<<" &"<<setprecision(3)<<DiMuonAvHF_3[i]->GetMean()<<
     "   &"<<setprecision(3)<<DiMuonNTrk[i]->GetMean()<<" &"<<DiMuonNTrk_2[i]->GetMean()<<Str2<<endl;

   SumEntries_HF=SumEntries_HF+(DiMuonAvHF_1[i]->GetEntries()/HFEtTr->GetEntries());

 }

 dataFile<<Str1<<endl;
 dataFile<<Str3<<"end{tabular}"<<endl;
 dataFile<<Str3<<"end{center}"<<endl;
 dataFile<<Str3<<"end{table}"<<endl;
 dataFile<<endl<<endl<<endl;


 cout<<" SumEntries HF "<<SumEntries_HF<<endl;











 /*

 dataFile<<Str3<<"begin{table}[htbH]"<<endl;
 dataFile<<Str3<<"begin{center}"<<endl;
 dataFile<<Str3<<"caption{}"<<endl; 
 dataFile<<Str3<<"label{}"<<endl;
 dataFile<<Str3<<"begin{tabular}{c|c|c}"<<endl;
 dataFile<<Str1<<endl;
 dataFile<<" $N_{Trk}/<N_{Trk}>$ "<< "  &$\\% of events$  " << "& $<N_{Trk}>$"<<Str2<<endl;
 dataFile<<Str1<<endl;

for(int i=1;i<4;i++){


  dataFile <<"$[ "<<i-1<<" - "<<i<<")$    &"<<setprecision(3)<<(DiMuonNTrk_1[i]->GetEntries()/NTrk->GetEntries())<<"   &"<<setprecision(3)<<DiMuonNTrk_1[i]->GetMean()<<
    Str2<<endl;

 
}

 dataFile<<Str1<<endl;
 dataFile<<Str3<<"end{tabular}"<<endl;
 dataFile<<Str3<<"end{center}"<<endl;
 dataFile<<Str3<<"end{table}"<<endl;
 dataFile<<endl<<endl<<endl;




 txtfile<<endl<<endl;
 
 txtfile <<" HF/<HF>   "<<    "% Entry "<<" <NTrk_Bin> "<<endl;
 
 



















 dataFile<<Str3<<"begin{table}[htbH]"<<endl;
 dataFile<<Str3<<"begin{center}"<<endl;
 dataFile<<Str3<<"caption{}"<<endl; 
 dataFile<<Str3<<"label{}"<<endl;
 dataFile<<Str3<<"begin{tabular}{c|c|c}"<<endl;
 dataFile<<Str1<<endl;
 dataFile<<" $E_{T}/<E_{T}>$ "<< "  &$Frac_{Events}$  " << "&$<E_{T}>$"<<Str2<<endl;
 dataFile<<Str1<<endl;

 for(int i=1;i<4;i++){
  
   txtfile << "[ "<<i-1<<" - "<<i<<")    "<<(DiMuonNTrk[i]->GetEntries()/NTrk->GetEntries())<<"   "<<DiMuonNTrk[i]->GetMean()<<"   "<<endl;
   
   dataFile <<"$[ "<<i-1<<" - "<<i<<")$    &"<<setprecision(3)<<(DiMuonAvHF_1[i]->GetEntries()/HFEtTr->GetEntries())<<"   &"<<setprecision(3)<<DiMuonAvHF[i]->GetMean()<<
     Str2<<endl;

 }

 dataFile<<Str1<<endl;
 dataFile<<Str3<<"end{tabular}"<<endl;
 dataFile<<Str3<<"end{center}"<<endl;
 dataFile<<Str3<<"end{table}"<<endl;
 dataFile<<endl<<endl<<endl;

 */



 //=================== Tables End ==================================================//




 TLegend *lcat1;
 lcat1 = new TLegend(.44, .78, .88, .93);
 lcat1->SetBorderSize(0);
 lcat1->SetFillStyle(1001);
 lcat1->SetFillColor(10);
 lcat1-> SetTextSize(0.040);

 lcat1->AddEntry(DiMuonAvHF[1],"E_{T} if N_{Trk}/<N_{Trk}> [0,1)", "P");
 lcat1->AddEntry(DiMuonAvHF[2],"E_{T} if N_{Trk}/<N_{Trk}> [1,2)", "P");
 lcat1->AddEntry(DiMuonAvHF[3],"E_{T} if N_{Trk}/<N_{Trk}> [2,)", "P");
  

 TLatex *tb = new TLatex();
 tb->SetNDC(); 
 tb->SetTextAlign(12);
 tb->SetTextColor(1);
 tb->SetTextSize(0.040);
 


 new TCanvas;
 if(choseCase ==1){DiMuonAvHF[1]->GetXaxis()->SetRangeUser(0.0,50);}
 DiMuonAvHF[1]->GetYaxis()->SetRangeUser(1.0,10000000);
 gPad->SetLogy(1);

 DiMuonAvHF[1]->Draw();
 DiMuonAvHF[2]->Draw("same");
 DiMuonAvHF[3]->Draw("same");
 lcat1->Draw("same");
 
 char chNTrk1[1000];
 char chNTrk2[1000];
 char chNTrk3[1000];

 
 
 sprintf(chNTrk1,"[0-1)    %0.2f",DiMuonAvHF[1]->GetMean()); 
 sprintf(chNTrk2,"[0-2)    %0.2f",DiMuonAvHF[2]->GetMean()); 
 sprintf(chNTrk3,"[2- )    %0.2f",DiMuonAvHF[3]->GetMean()); 

 tb->DrawLatex(0.22,0.90,"#frac{N_{Trk}}{<N_{Trk}>}  <HF E_{T}>");
 tb->DrawLatex(0.22,0.82,chNTrk1);
 tb->DrawLatex(0.22,0.77,chNTrk2);
 tb->DrawLatex(0.22,0.72,chNTrk3);


if(choseCase ==0){
 gPad->SaveAs("HFET_4NTrk.png");
 gPad->SaveAs("HFET_4NTrk.pdf");
 }


 if(choseCase ==1){
   gPad->SaveAs("pp_HFET_4NTrk.png");
   gPad->SaveAs("pp_HFET_4NTrk.pdf");
 }

 

 TLegend *lcat2;
 lcat2 = new TLegend(.44, .78, .88, .93);
 lcat2->SetBorderSize(0);
 lcat2->SetFillStyle(1001);
 lcat2->SetFillColor(10);
 lcat2-> SetTextSize(0.040);

 lcat2->AddEntry(DiMuonAvHF[1],"N_{Trk} if E_{T}/<E_{T}> [0,1)", "P");
 lcat2->AddEntry(DiMuonAvHF[2],"N_{Trk} if E_{T}/<E_{T}> [1,2)", "P");
 lcat2->AddEntry(DiMuonAvHF[3],"N_{Trk} if E_{T}/<E_{T}> [2,)", "P");


 sprintf(chNTrk1,"[0-1)    %0.2f",DiMuonNTrk[1]->GetMean()); 
 sprintf(chNTrk2,"[0-2)    %0.2f",DiMuonNTrk[2]->GetMean()); 
 sprintf(chNTrk3,"[2- )    %0.2f",DiMuonNTrk[3]->GetMean()); 
    
 new TCanvas;
 gPad->SetLogy(1);
 if(choseCase ==1){DiMuonNTrk[1]->GetXaxis()->SetRangeUser(0.0,100);}
 DiMuonNTrk[1]->GetYaxis()->SetRangeUser(1.0,10000000);
 DiMuonNTrk[1]->Draw();
 DiMuonNTrk[2]->Draw("same");
 DiMuonNTrk[3]->Draw("same");
 lcat2->Draw("same");

 tb->DrawLatex(0.18,0.90,"#frac{HFE_{T}}{<HF E_{T}>}  <N_{Trk}>");
 tb->DrawLatex(0.22,0.82,chNTrk1);
 tb->DrawLatex(0.22,0.77,chNTrk2);
 tb->DrawLatex(0.22,0.72,chNTrk3);



 if(choseCase ==0){
   gPad->SaveAs("NTrks_4HFET.png");
   gPad->SaveAs("NTrks_4HFET.pdf");
 }

 if(choseCase ==1){
   gPad->SaveAs("pp_NTrks_4HFET.png");
   gPad->SaveAs("pp_NTrks_4HFET.pdf");

 }


 TLegend *lcat3;
 lcat3 = new TLegend(.34, .78, .88, .93);
 lcat3->SetBorderSize(0);
 lcat3->SetFillStyle(1001);
 lcat3->SetFillColor(10);
 lcat3-> SetTextSize(0.040);

 lcat3->AddEntry(DiMuonAvHF_2[1],"E_{T}/<E_{T}> if N_{Trk}/<N_{Trk}> [0,1)", "P");
 lcat3->AddEntry(DiMuonAvHF_2[2],"E_{T}/<E_{T}> if N_{Trk}/<N_{Trk}> [1,2)", "P");
 lcat3->AddEntry(DiMuonAvHF_2[3],"E_{T}/<E_{T}> if N_{Trk}/<N_{Trk}> [2,)", "P");


 new TCanvas;
 gPad->SetLogy(1);

 DiMuonAvHF_2[1]->GetXaxis()->SetRangeUser(0.0,10.0);
 DiMuonAvHF_2[1]->GetXaxis()->SetTitle("HF E_{T}/<HF E_{T}>");
 DiMuonAvHF_2[1]->GetYaxis()->SetTitle("Events");

 DiMuonAvHF_2[1]->Draw();
 DiMuonAvHF_2[2]->Draw("same");
 DiMuonAvHF_2[3]->Draw("same");
 lcat3->Draw("same");


 sprintf(chNTrk1,"[0-1)     %0.2f",DiMuonAvHF_2[1]->GetMean()); 
 sprintf(chNTrk2,"[0-2)     %0.2f",DiMuonAvHF_2[2]->GetMean()); 
 sprintf(chNTrk3,"[2- )     %0.2f",DiMuonAvHF_2[3]->GetMean()); 

 tb->DrawLatex(0.57,0.70,"#frac{N_{Trk}}{<N_{Trk}>}   #frac{HF E_{T}}{<HF E_{T}>}");
 tb->DrawLatex(0.58,0.63,chNTrk1);
 tb->DrawLatex(0.58,0.58,chNTrk2);
 tb->DrawLatex(0.58,0.53,chNTrk3);






if(choseCase ==0){
 gPad->SaveAs("HFET_4NTrk_2.png");
 gPad->SaveAs("HFET_4NTrk_2.pdf");
 }


 if(choseCase ==1){
   gPad->SaveAs("pp_HFET_4NTrk_2.png");
   gPad->SaveAs("pp_HFET_4NTrk_2.pdf");
 }




 TLegend *lcat4;
 lcat4 = new TLegend(.34, .78, .88, .93);
 lcat4->SetBorderSize(0);
 lcat4->SetFillStyle(1001);
 lcat4->SetFillColor(10);
 lcat4-> SetTextSize(0.040);

 lcat4->AddEntry(DiMuonAvHF[1],"N_{Trk}/<N_{Trk}> if E_{T}/<E_{T}> [0,1)", "P");
 lcat4->AddEntry(DiMuonAvHF[2],"N_{Trk}/<N_{Trk}> if E_{T}/<E_{T}> [1,2)", "P");
 lcat4->AddEntry(DiMuonAvHF[3],"N_{Trk}/<N_{Trk}> if E_{T}/<E_{T}> [2,)", "P");


   
 new TCanvas;
 gPad->SetLogy(1);
 DiMuonNTrk_2[1]->GetXaxis()->SetRangeUser(0.0,10.0);

 DiMuonNTrk_2[1]->GetXaxis()->SetTitle("Tracks/<Tracks>");
 DiMuonNTrk_2[1]->GetYaxis()->SetTitle("Events");

 DiMuonNTrk_2[1]->Draw();
 DiMuonNTrk_2[2]->Draw("same");
 DiMuonNTrk_2[3]->Draw("same");
 lcat4->Draw("same");



 sprintf(chNTrk1,"[0-1)     %0.2f",DiMuonNTrk_2[1]->GetMean()); 
 sprintf(chNTrk2,"[0-2)     %0.2f",DiMuonNTrk_2[2]->GetMean()); 
 sprintf(chNTrk3,"[2- )     %0.2f",DiMuonNTrk_2[3]->GetMean()); 

 tb->DrawLatex(0.57,0.70,"#frac{HF E_{T}}{<HF E_{T}>}   #frac{N_{Trk}}{<N_{Trk}>}");
 tb->DrawLatex(0.58,0.63,chNTrk1);
 tb->DrawLatex(0.58,0.58,chNTrk2);
 tb->DrawLatex(0.58,0.53,chNTrk3);




 if(choseCase ==0){
   gPad->SaveAs("NTrks_4HFET_2.png");
   gPad->SaveAs("NTrks_4HFET_2.pdf");
 }

 if(choseCase ==1){
   gPad->SaveAs("pp_NTrks_4HFET_2.png");
   gPad->SaveAs("pp_NTrks_4HFET_2.pdf");

 }




 dataFile<<Str3<<"end{document}"<<endl<<endl;
 dataFile.close();

 
 return;
















 //Sorting variable vector
 double binboundaries[nbins+1];
 int size             = values.size();

 sort(values.begin(),values.end());
 binboundaries[nbins] = values[size-1];
 txtfile << "-------------------------------------" << endl;
 txtfile << label.data() << " Base edges are: " << endl;
 
 for(int i = 0; i < nbins; i++) 
   {
     int entry = (int)(i*(size/nbins));
     if(entry < 0 || i == 0) binboundaries[i] = 0;
     else binboundaries[i] = values[entry];
   }
   






 for(int i = 0; i <= nbins; i++) 
 {
   if(binboundaries[i] < 0) binboundaries[i] = 0;
   txtfile << Form("%.2f",binboundaries[i]) << endl;
 }
 txtfile << "-------------------------------------" << endl;

 //normalized values
 //normalize:
 float fMean     = phVar->GetMean();
 float fMean_rms = phVar->GetRMS();

 TH1 *phVar_norm = new TH1D("phVar_norm","phVar_norm",150,0,15);
 phVar_norm->SetDirectory(0);
 TH1 *phVar_norm01 = new TH1D("phVar_norm01","phVar_norm01",150,0,15);
 phVar_norm01->SetDirectory(0);
 TH1 *phVar_norm12 = new TH1D("phVar_norm12","phVar_norm12",150,0,15);
 phVar_norm12->SetDirectory(0);
 TH1 *phVar_norm23 = new TH1D("phVar_norm23","phVar_norm23",150,0,15);
 phVar_norm23->SetDirectory(0);
 TH1 *phVar_norm215 = new TH1D("phVar_norm215","phVar_norm215",150,0,15);
 phVar_norm215->SetDirectory(0);
 TH1 *phVar_norm315 = new TH1D("phVar_norm315","phVar_norm315",150,0,15);
 phVar_norm315->SetDirectory(0);

 for(int i=0; i<size;i++)
   {
     values_norm.push_back(values[i]/fMean);
     phVar_norm->Fill(values[i]/fMean);
     if( (values[i]/fMean )<1 ) phVar_norm01->Fill(values[i]/fMean);
     if( 1<=(values[i]/fMean ) && (values[i]/fMean )<2) phVar_norm12->Fill(values[i]/fMean);
     if( 2<=(values[i]/fMean ) && (values[i]/fMean )<3) phVar_norm23->Fill(values[i]/fMean);
     if( 2<=(values[i]/fMean ) && (values[i]/fMean )<15) phVar_norm215->Fill(values[i]/fMean);
     if( 3<=(values[i]/fMean ) && (values[i]/fMean )<15) phVar_norm315->Fill(values[i]/fMean);
   }

 sort(values_norm.begin(),values_norm.end());
 double binboundaries_norm[nbins+1];
 binboundaries_norm[nbins] = values_norm[size-1];

 for(int i = 0; i < nbins; i++) 
   {
     int entry = (int)(i*(size/nbins));
     if(entry < 0 || i == 0) binboundaries_norm[i] = 0;
     else binboundaries_norm[i] = values_norm[entry];
   }

 txtfile << "-------------------------------------" << endl;
 txtfile << label.data() << "Normalized ("<< fMean<<" #pm "<<fMean_rms<<") edges are: " << endl;

 for(int i = 0; i <= nbins; i++) 
 {
  txtfile << Form("%.2f",binboundaries_norm[i]) << endl;
 }
 txtfile << endl << "-------------------------------------" << endl;
 txtfile << endl << "Histograms X_MB / <X>_MB" << endl;
 txtfile << " [0,1) = "<<phVar_norm01->GetMean()<<"#pm"<<phVar_norm01->GetMeanError()<<endl;
 txtfile << " [1,2) = "<<phVar_norm12->GetMean()<<"#pm"<<phVar_norm12->GetMeanError()<<endl;
 txtfile << " [2,3) = "<<phVar_norm23->GetMean()<<"#pm"<<phVar_norm23->GetMeanError()<<endl;
 txtfile << " [2,15) = "<<phVar_norm215->GetMean()<<"#pm"<<phVar_norm215->GetMeanError()<<endl;
 txtfile << " [3,15) = "<<phVar_norm315->GetMean()<<"#pm"<<phVar_norm315->GetMeanError()<<endl;
 txtfile << " all = "<<phVar_norm->GetMean()<<"#pm"<<phVar_norm->GetMeanError()<<endl;
 txtfile << endl << "-------------------------------------" << endl;
 
 //txtfile.write();
 
 txtfile.close();

 if(bSavePlots)
   {
 // get the mean of the bins with x/<x> >2
     TCanvas *pc3 = new TCanvas("pc3","pc3",1000,800);
     pc3->Divide(3,2);
     pc3->cd(1);gPad->SetLogy();
     phVar_norm01->Draw("hist ");

     pc3->cd(2);gPad->SetLogy();
     phVar_norm12->Draw("hist ");

     pc3->cd(3);gPad->SetLogy();
     phVar_norm23->Draw("hist ");

     pc3->cd(4);gPad->SetLogy();
     phVar_norm215->Draw("hist ");
     
     pc3->cd(5);gPad->SetLogy();
     phVar_norm315->Draw("hist ");

     pc3->cd(6);gPad->SetLogy();
     phVar_norm->Draw("hist ");

     pc3->SaveAs(Form("%s_hist_means_doPa%d.png",asLabels[choseVar],choseCase));
     pc3->SaveAs(Form("%s_hist_means_doPa%d.pdf",asLabels[choseVar],choseCase));
   }
 if(bSavePlots)
   {
     TCanvas *pc1 = new TCanvas("pc1","pc1");
     pc1->cd();
     phVar->Draw();
     gPad->SetLogy();
     pc1->SaveAs(Form("%s_hist_doPa%d.png",asLabels[choseVar],choseCase));
     pc1->SaveAs(Form("%s_hist_doPa%d.pdf",asLabels[choseVar],choseCase));

     TCanvas *pc2 = new TCanvas("pc2","pc2");
     pc2->cd();
     phVar_norm->Draw();
     gPad->SetLogy();
     pc2->SaveAs(Form("%s_hist_norm_doPa%d.png",asLabels[choseVar],choseCase));
     pc2->SaveAs(Form("%s_hist_norm_doPa%d.pdf",asLabels[choseVar],choseCase));
   }


}
