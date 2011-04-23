#ifndef __CINT__
#include <RooGlobalFunc.h>
#endif

#include "TLatex.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooFitResult.h"
#include "RooLandau.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
#include "RooDataHist.h"
#include "RooVoigtian.h"
#include "RooCBShape.h"
#include "RooFitResult.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooEllipse.h"
#include "RooRandom.h"
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
#include "vector.h"
#include "TString.h"
#include "iostream.h"
#include "fstream.h"
#include "TLegend.h"
#include "TStyle.h"

#include "/home/abdulla/Desktop/new_m4/fitPeak_old.cc"
#include "/home/abdulla/Desktop/new_m4/myStyle.h"
/*-----------------------------
This macro is used to get the "effSig" and "rejBkg" for 
realistic MC adding proper weight for every
cut individually . Need to include the macro "fitPeak_old.cc" 
to fit the Jpsi Mass distributions, and get the quantities we need.


-------------------------------*/
using namespace RooFit;

void cutAnaWeight(int CT=7)
{
  //for(int CT=1;CT<9;CT++)
  //{
	gROOT->Reset();
	Long_t nEntries, nData=0;
	const int nBin=3;  
	const int ifile=6;

	/* ---------------------CT: Cut Type, num: value numbers for this cut------------------------ */
	char cutVar[100]; //cut Variables
	if(CT == 1) 
    	{
		sprintf(cutVar,"mu_innerTrack_Hits");
		const int num=18;
	}
	if(CT == 2) 
	{
		sprintf(cutVar,"mu_pixeLayers");
		const int num=5;
	}
	if(CT == 3) 
	{
		sprintf(cutVar,"mu_nValidMuHits");
		const int num=10;
	}
	if(CT == 4) 
	{	
		sprintf(cutVar,"mu_innerTrack_chi2NDOF");
		const int num=16;
	}
	if(CT == 5) 
	{
		sprintf(cutVar,"mu_dxy");
		const int num=8;
	}
	if(CT == 6) 
	{
		sprintf(cutVar,"mu_dz");
		const int num=10;
	}
	if(CT == 7) 
	{
		sprintf(cutVar,"mu_globalTrack_chi2NDOF");
		const int num=10;
	}
	if(CT == 8) 
	{
		sprintf(cutVar,"vProb");
		const int num=10;
	}
	if(CT == 9) 
	{
		sprintf(cutVar,"arbitration");
		const int num=2;
	}
	if(CT == 10) 
	{
		sprintf(cutVar,"mu_lastStationAngTight");
		const int num=2;
	}
	if(CT == 11) 
	{
		sprintf(cutVar,"mu_Segment");
		const int num=8;
	}
	

	cout<<"selection cut: "<<cutVar<<endl;

	double cutVal[num]; //cut Values
	double nFoundSigRaw[nBin], nFoundBkgRaw[nBin],errorR[nBin][num];  // number of the signal and background with noCut
	double nFoundSig[nBin][num],nFoundBkg[nBin][num]; //num in the +-2sigma(signal) && out4sigma sideband(background)
	double nFoundSigFull[nBin][num],nFoundBkgFull[nBin][num];//num of signal yield && background
	double effSig[nBin][num], rejBkg[nBin][num];  //efficiency of keeping signal  && fraction of rejected background
	double SGF[nBin][num],ratiopeak[nBin][num], ratiobkg[nBin][num];
	double err_sig[nBin][num],err_sig_raw[nBin],err_effi[nBin][num];
	double err_rpeak[nBin][num], err_rbkg[nBin][num], err_sgf[nBin][num];
	double err_bkg[nBin][num],err_bkg_raw[nBin],err_rejbkg[nBin][num];
	//define the selection Cut value
	for(int i=0; i<num; i++)
	{
		if(CT == 1) cutVal[i]=(double)i;      //mu_innerTrack_Hits 4---17   num=14

		if(CT == 2) cutVal[i]=(double)i;        //mu_pixeLayers=0,1,2,3,4 num=5

		if(CT == 3) cutVal[i]=(double)i*2.;        //mu_nValidMuHits=0,2,4,...,18 num=10

		//cutVal[i]=(double)i*0.5+1.;  //mu_nchi2In 1.0, 1.5,...,6.5  num=12
		if(CT == 4) cutVal[i]=(double)i*0.2+1.;  //mu_nchi2In 1.0, 1.2,...,4  num=16

		if(CT == 5) 
		{
			if(i>1 && i<7) cutVal[i]=(double)(i-1)*0.2-0.1;   //mu_dxy 0.02,0.06,0.1,0.3,0.5,0.7,0.9,3.0  num=8
			if(i==0) cutVal[i]=0.02;
			if(i==1) cutVal[i]=0.06;
			if(i==7) cutVal[i]=3.0;
		}

		if(CT == 6) cutVal[i]=(double)i*2.+1.;     //mu_dz 1,3,5,...,19  num=10

		if(CT == 7) 
		{
			if(i==0) cutVal[i]=1.;
			if(i==1) cutVal[i]=1.5;
			if(i>=2 && i<=4) cutVal[i]=(double)i*2.-2.;
			if(i>=5) cutVal[i]=(double)i*4.-8.;  //nchi2Gl, 1., 1.5, 2., 4., 6., 12., 16., 20., 24, 28.. num=10;
		}

		if(CT == 8) 
		{
			if(i==0) cutVal[i]=0.001;
			if(i>0) cutVal[i]=(double)i*0.004+0.002;  //vProb 0.001,0.002,0.006,...,0.040  num=10
		}
		if(CT == 9) 
		{
			if(i==0) cutVal[i]=0;
			if(i==1) cutVal[i]=1;

		}
		if(CT == 10) 
		{
			if(i==0) cutVal[i]=0;
			if(i==1) cutVal[i]=1;

		}
		if(CT == 11) cutVal[i]=(double)i;   
		
		cout<<"===============cutVal: "<<cutVal[i]<<"================="<<endl;
	}
	
	Double_t massMin,massMax;
	massMin=2.6;
	massMax=3.5;
	RooRealVar *mass=new RooRealVar("mass","dimuon mass(GeV/c^{2})",2.6,3.5);
	RooRealVar *evtWeight= new RooRealVar("evtWeight","event weight",0.0,500.0);
	//RooArgList varlist(mass,*evtWeight);
	RooArgSet variables;
	variables.add(*mass);
	variables.add(*evtWeight);

	RooDataSet *dataRaw[nBin];
	RooDataSet *data[nBin];
	for(int i=0;i<nBin;i++)
	  {
	    data[i]= new RooDataSet(Form("data%d",i),"weighted dataset",variables,RooFit::WeightVar("evtWeight"));
	    dataRaw[i]= new RooDataSet(Form("dataRaw%d",i),"weighted dataset",variables,RooFit::WeightVar("evtWeight"));
	  }
	
	char fileName[10][500];
	char name[100];
	char outName[500];

	//Jpsi Variables
	Double_t JpsiMass,JpsiPt,JpsiRap;
	Double_t JpsiVprob;
	//(1).Positive Muon                                     
	double muPos_nchi2In, muPos_dxy, muPos_dz, muPos_nchi2Gl;
	int muPos_arbitrated, muPos_oneStationTight,muPos_lastStationAngTight;
	int muPos_found, muPos_pixeLayers, muPos_nValidMuHits, mu_Pos_SegMatch;
	//(2).Negative Muon                                     
	double muNeg_nchi2In, muNeg_dxy, muNeg_dz, muNeg_nchi2Gl;
	int muNeg_arbitrated, muNeg_oneStationTight,muNeg_lastStationAngTight;
	int muNeg_found, muNeg_pixeLayers, muNeg_nValidMuHits, mu_Neg_SegMatch;
	//Trigger Information                                   
	int HLT_L1DoubleMuOpen, HLT_Mu0_TkMu0_Jpsi, HLT_Mu0_TkMu0_OST_Jpsi_Tight_v2;


	sprintf(name,
		"runs148819-149182_MuOnia"
		);
	sprintf(outName,
		Form("/home/abdulla/Desktop/new_m4/WeightMC/%s_%s.txt",name,cutVar));
	
	ofstream outTxt(outName);
	ofstream dataFile(Form("WeightMC/%s_ana_sumw2.txt",cutVar));
	
	outTxt<<"cut Type: "<<cutVar<<endl;
	dataFile<<"cut Type "<<cutVar<<endl<<endl;
	for(int i=0; i<num; i++)
	  {
	    dataFile<<cutVal[i]<<" ";
	  }
	dataFile<<endl<<endl;
	
	
	cout<<"===============total Entries in Tree: "<<nEntries<<"==============="<<endl;
	outTxt<<"===============total Entries in Tree: "<<nEntries<<"==============="<<endl;
	
	//these to initialize the parameters of mass distribution,see "fitPeak_old.cc"
	vector<double> sigBkg[nBin];
	Int_t nPeak=1; //signal peak number
	vector<Double_t> fMean,dfMean,fSigma,dfSigma;
	fMean.push_back(3.09); //Jpsi Mass mean
	dfMean.push_back(0.01); //deviation of mass mean
	fSigma.push_back(0.04); //Jpsi mass sigma
	dfSigma.push_back(0.04); //deviation of mass sigma
	
	cout<<"----------------------------------------------------------------------------------------"<<endl;
	cout<<"-----------------------starting Loop all the selection Cut------------------------------"<<endl;
	cout<<"----------------------------------------------------------------------------------------"<<endl;
	for(int k=0; k<num; k++)
	  {
	    cout<<endl<<"==================="<<cutVar<<" "<<k<<" Value: "<<cutVal[k]<<"==============="<<endl;
	    //reset the dataset
	    for(int i=0; i<nBin; i++)
	      {
		data[i]->reset();
		
	      }
	    
	    for (int ifile = 0; ifile < 6; ifile++)
	      {
		
		if(ifile==0){sprintf(fileName[ifile],"/home/abdulla/Desktop/new_m4/PromptJpsiPt03.root");}
		if(ifile==1){sprintf(fileName[ifile],"/home/abdulla/Desktop/new_m4/PromptJpsiPt36.root");}
		if(ifile==2){sprintf(fileName[ifile],"/home/abdulla/Desktop/new_m4/PromptJpsiPt69.root");}
		if(ifile==3){sprintf(fileName[ifile],"/home/abdulla/Desktop/new_m4/PromptJpsiPt912.root");}
		if(ifile==4){sprintf(fileName[ifile],"/home/abdulla/Desktop/new_m4/PromptJpsiPt1215.root");}
		if(ifile==5){sprintf(fileName[ifile],"/home/abdulla/Desktop/new_m4/PromptJpsiPt1530.root");}
		
		double norm=100;

		if(ifile==0){Weight=(0.0257069/0.00005571)/norm;}
		if(ifile==1){Weight=(0.0146199/0.00005571)/norm;}
		if(ifile==2){Weight=(0.00393391/0.00005571)/norm;}
		if(ifile==3){Weight=(0.000669658/0.00005571)/norm;}
		if(ifile==4){Weight=(0.000164187/0.00005571)/norm;}
		if(ifile==5){Weight=(0.00005571/0.00005571)/norm;}
		
		TFile *infile=new TFile(fileName[ifile],"R");
		TTree *tree=(TTree*)infile->Get("data");
		//Jpsi Variables
		tree->SetBranchAddress("JpsiMass",&JpsiMass);
		tree->SetBranchAddress("JpsiPt",&JpsiPt);
		tree->SetBranchAddress("JpsiRap",&JpsiRap);
		tree->SetBranchAddress("JpsiVprob",&JpsiVprob);
		//Trigger information
		//tree->SetBranchAddress("HLT_L1DoubleMuOpen",&HLT_L1DoubleMuOpen);
		//tree->SetBranchAddress("HLT_Mu0_TkMu0_Jpsi",&HLT_Mu0_TkMu0_Jpsi);
		//tree->SetBranchAddress("HLT_Mu0_TkMu0_OST_Jpsi_Tight_v2",&HLT_Mu0_TkMu0_OST_Jpsi_Tight_v2);
		//1) Positive Muon                                      
		tree->SetBranchAddress("muPos_nchi2In", &muPos_nchi2In);
		tree->SetBranchAddress("muPos_dxy", &muPos_dxy);
		tree->SetBranchAddress("muPos_dz", &muPos_dz);
		tree->SetBranchAddress("muPos_nchi2Gl", &muPos_nchi2Gl);
		tree->SetBranchAddress("muPos_arbitrated", &muPos_arbitrated);
		tree->SetBranchAddress("muPos_oneStationTight", &muPos_oneStationTight);
		tree->SetBranchAddress("muPos_found", &muPos_found);
		tree->SetBranchAddress("muPos_pixeLayers", &muPos_pixeLayers);
		tree->SetBranchAddress("muPos_nValidMuHits", &muPos_nValidMuHits);
		tree->SetBranchAddress("muPos_lastStationAngTight",&muPos_lastStationAngTight);
		tree->SetBranchAddress("mu_Pos_SegMatch",&mu_Pos_SegMatch);
		
		//2) Negative Muon                                      
		tree->SetBranchAddress("muNeg_nchi2In", &muNeg_nchi2In);
		tree->SetBranchAddress("muNeg_dxy", &muNeg_dxy);
		tree->SetBranchAddress("muNeg_dz", &muNeg_dz);
		tree->SetBranchAddress("muNeg_nchi2Gl", &muNeg_nchi2Gl);
		tree->SetBranchAddress("muNeg_arbitrated", &muNeg_arbitrated);
		tree->SetBranchAddress("muNeg_oneStationTight", &muNeg_oneStationTight);
		tree->SetBranchAddress("muNeg_found", &muNeg_found);
		tree->SetBranchAddress("muNeg_pixeLayers", &muNeg_pixeLayers);
		tree->SetBranchAddress("muNeg_nValidMuHits", &muNeg_nValidMuHits);
		tree->SetBranchAddress("muNeg_lastStationAngTight",&muNeg_lastStationAngTight);
		tree->SetBranchAddress("mu_Neg_SegMatch",&mu_Neg_SegMatch);
		
		nEntries=tree->GetEntries();		
		
		bool cutPass;
		for(int i=0; i<nEntries; i++)
		  {
		    tree->GetEntry(i);
		    
		    //-----------------------------define the Cut Variable----------------------
		    if(CT == 1) cutPass = muPos_found > (int)cutVal[k] && muNeg_found > (int)cutVal[k] ;
		    if(CT == 2) cutPass = muPos_pixeLayers > (int)cutVal[k] && muNeg_pixeLayers > (int)cutVal[k] ; 
		    if(CT == 3) cutPass = (muPos_nValidMuHits < -100 || (muPos_nValidMuHits > -100 && muPos_nValidMuHits > (int)cutVal[k]))
		      && (muNeg_nValidMuHits < -100 || (muNeg_nValidMuHits > -100 && muNeg_nValidMuHits > (int)cutVal[k])); 
		    if(CT == 4) cutPass =	muPos_nchi2In < cutVal[k]  && muNeg_nchi2In < cutVal[k] ;
		    if(CT == 5) cutPass = fabs(muPos_dxy) < cutVal[k]  && fabs(muNeg_dxy) < cutVal[k] ;
		    if(CT == 6) cutPass = fabs(muPos_dz) < cutVal[k]  && fabs(muNeg_dz) < cutVal[k] ;
		    if(CT == 7) cutPass = (muPos_nchi2Gl < -100. || (muPos_nchi2Gl > -100. && muPos_nchi2Gl < cutVal[k] ))
		      && (muNeg_nchi2Gl < -100. || (muNeg_nchi2Gl > -100. && muNeg_nchi2Gl < cutVal[k] )) ;
		    if(CT == 8) cutPass =	JpsiVprob > cutVal[k] ; 
		    
		    if(CT == 9) cutPass =  muPos_arbitrated == cutVal[k] && muNeg_arbitrated == cutVal[k];
		    if(CT == 10) cutPass =	muPos_lastStationAngTight == cutVal[k] && muNeg_lastStationAngTight == cutVal[k];
		    
		    if(CT == 11) cutPass = (mu_Pos_SegMatch >(int)cutVal[k] && mu_Neg_SegMatch >(int)cutVal[k]);
		    
		    //cout<<" cut***** "<<muPos_lastStationAngTight <<"   " <<cutVal[k]<<endl;
		    
		    //--------------------------------------------------------------------------
		    
		    if(JpsiMass> massMin && JpsiMass< massMax)
		      {	
			//Vineet
			if(fabs(JpsiRap)<1.2 )
			  {
			    mass.setVal(JpsiMass);
			    if(k==0)
			      {
				//dataRaw[0]->add(mass);
				dataRaw[0]->add(variables,Weight);
				
			      }
			    
			    if(cutPass)
			      {
				//data[0]->add(mass);
				data[0]->add(variables,Weight);
				nData++;
			      }
			  }  
			if(fabs(JpsiRap)>1.2 && fabs(JpsiRap)<1.6)
			  {
			    mass.setVal(JpsiMass);
			    if(k==0)
			      {
				//dataRaw[1]->add(mass);
				dataRaw[1]->add(variables,Weight);
			      }
			    if(cutPass)
			      {
				//data[1]->add(mass);
				data[1]->add(variables,Weight);
				nData++;
			      }
			  }
			if(fabs(JpsiRap)>1.6 && fabs(JpsiRap)<2.4)
			  {
			    mass.setVal(JpsiMass);
			    if(k==0)
			      {
				//dataRaw[2]->add(mass);
				dataRaw[2]->add(variables,Weight);
			      }
			    if(cutPass)
			      {
				//data[2]->add(mass);
				data[2]->add(variables,Weight);
				nData++;
			      }
			  }
			
		      }
		  }// nEntries
	      }// ifile
	    
	    TCanvas *c1[nBin];
	    for(int i=0; i<nBin; i++)
	      {
		c1[i]=new TCanvas(Form("c1_%d",i),"");
		c1[i]->SetFillColor(10);
		
		//SetMyStyle();
		gPad->SetLeftMargin(0.10);
		gPad->SetBottomMargin(0.10);
		gPad->SetRightMargin(0.10);
		gPad->SetTopMargin(0.10);
		
		sigBkg[i].clear();
		//fit the mass distribution in dataSet
		sigBkg[i]=fitPeak_old(*mass,0,nPeak,0,data[i],fMean,dfMean,fSigma,dfSigma,0.5);
		//===========get the total number of sig && bkg in the cut value================
		nFoundSig[i][k]=sigBkg[i][4];
		nFoundBkg[i][k]=sigBkg[i][5];
		nFoundSigFull[i][k]=sigBkg[i][6];
		nFoundBkgFull[i][k]=sigBkg[i][5];
		errorR[i][k]=sigBkg[i][10];
		//SGF[i][k]=sigBkg[i][3];
		//ratiopeak[i][k]= sigBkg[i][8];
		//ratiobkg[i][k] = sigBkg[i][9];
		err_sig[i][k]= sqrt(nFoundSigFull[i][k]);
		//err_bkg[i][k]= sqrt(nFoundBkgFull[i][k]);
		//err_rpeak[i][k]= sqrt(ratiopeak[i][k]);
		//err_rbkg[i][k]= sqrt(ratiobkg[i][k]);
		//err_sgf[i][k]= sqrt(ratiopeak[i][k]*(ratiopeak[i][k] + 4*ratiobkg[i][k]))/(2*(ratiopeak[i][k]+ratiobkg[i][k]));
		//err_sgf[i][k]= sqrt((ratiopeak[i][k]+2*ratiobkg[i][k])**2/(4*(ratiopeak[i][k]+ratiobkg[i][k])**3)*err_rpeak[i][k]*err_rpeak[i][k] + ratiopeak[i][k]*ratiopeak[i][k]/(4*(ratiopeak[i][k]+ratiobkg[i][k])**3)*err_rbkg[i][k]*err_rbkg[i][k]);
		
		//==============================================================================
		
		//------------Draw the Latex---------------
		Double_t left=0.12, top=0.83, textSize=0.033;
		TLatex *latex=new TLatex();
		latex->SetTextFont(42);
		latex->SetNDC(kTRUE);
		latex->SetTextSize(textSize);
		Double_t step=textSize*1.5;
		
		//===for int type cut
		if(CT <= 3) latex->DrawLatex(left,top,Form("%s>%d",cutVar,(int)cutVal[k]));
		if(CT >= 4) latex->DrawLatex(left,top,Form("%s<%.2f",cutVar,cutVal[k]));
		top-=step;
		if(i==0) latex->DrawLatex(left,top,Form("|y|<%.1f, P_{T}>%.1f",1.2,0.0));
		if(i==1) latex->DrawLatex(left,top,Form("%.1f<|y|<%.1f, P_{T}>%.1f",1.2,1.6,0.0));
		if(i==2) latex->DrawLatex(left,top,Form("%.1f<|y|<%.1f, P_{T}>%.1f",1.6,2.4,0.0));
		top-=step;
		
		c1[i]->Modified();
		c1[i]->Update();
		
		//===for int type cut
		if(CT <= 3) 
		  {
		    c1[i]->Print(Form("WeightMC/pic/MC/%s/etaBin%d_%s%d.eps",cutVar,i,cutVar,(int)cutVal[k]));
		    c1[i]->Print(Form("WeightMC/pic/MC/%s/etaBin%d_%s%d.gif",cutVar,i,cutVar,(int)cutVal[k]));
		  }
		//===for double type cut
		if(CT >=4)
		  {
		    c1[i]->Print(Form("WeightMC/pic/MC/%s/etaBin%d_%s%d_cut%d.eps",cutVar,i,cutVar,(int)cutVal[k],k));
		    c1[i]->Print(Form("WeightMC/pic/MC/%s/etaBin%d_%s%d_cut%d.gif",cutVar,i,cutVar,(int)cutVal[k],k));
		  }
	      }//for i
	  }//for num
	cout<<"----------------------------------------------------------------------------------------------"<<endl;
	cout<<"--------------------------------Loop on all cut DONE------------------------------------------"<<endl;
	cout<<"-----------------------------------------------------------------------------------------------"<<endl;
	
	vector<double> sigBkgRaw[nBin];
	TCanvas *c2[nBin];
	for(int i=0; i<nBin; i++)
	  {
	    c2[i]=new TCanvas(Form("c2_%d",i),"");
	    sigBkgRaw[i].clear();
	    
	    sigBkgRaw[i]=fitPeak_old(*mass,0,nPeak,0,dataRaw[i],fMean,dfMean,fSigma,dfSigma,0.5);
	    nFoundSigRaw[i]=(double)sigBkgRaw[i][6];
	    nFoundBkgRaw[i]=(double)sigBkgRaw[i][5];
	    err_sig_raw[i] = sqrt(nFoundSigRaw[i]);
	    err_bkg_raw[i] = sqrt(nFoundBkgRaw)[i]);
	    cout<<"=============nFoundSigRaw "<<i<<" :"<<nFoundSigRaw[i]<<"================="<<endl;
	    cout<<"=============nFoundBkgRaw "<<i<<" :"<<nFoundBkgRaw[i]<<"================="<<endl;
          }

       for(int k=0; k< num; k++)
	 {
	   cout<<"=============================="<<endl;
	   cout<<"======Cut Value: "<<cutVal[k]<<"======="<<endl;
	   cout<<"=============================="<<endl;
	   outTxt<<"=============================="<<endl;
	   outTxt<<"======Cut Value: "<<cutVal[k]<<"======="<<endl;
	   outTxt<<"=============================="<<endl;
	   
	   for(int i=0; i<nBin; i++)
	     {
	       //compute the effSig & rejBkg
	       if(nFoundSigRaw[i]!=0.)
		 {
		   effSig[i][k]=nFoundSigFull[i][k]/nFoundSigRaw[i]*100.;  //"100" means change to percent
		   //err_effi[i][k] =  effSig[i][k]*sqrt( err_sig[i][k]*err_sig[i][k]/(nFoundSigFull[i][k]*nFoundSigFull[i][k]) + err_sig_raw[i]*err_sig_raw[i]/(nFoundSigRaw[i]* nFoundSigRaw[i]));
		 }
	       if(nFoundBkgRaw[i]!=0)
		 {
		   rejBkg[i][k]=(nFoundBkgRaw[i]-nFoundBkgFull[i][k])/nFoundBkgRaw[i]*100.;
		   //err_rejbkg[i][k] =  rejBkg[i][k]*sqrt( err_bkg[i][k]*err_bkg[i][k]/(nFoundBkgFull[i][k]*nFoundBkgFull[i][k]) + err_bkg_raw[i]*err_bkg_raw[i]/(nFoundBkgRaw[i]* nFoundBkgRaw[i]));
		 }
	       if(effSig[i][k] > 100.) effSig[i][k]=100.;
	       if(nFoundSigRaw[i]==0.) effSig[i][k]=0.;
	       if(rejBkg[i][k] < 0.) rejBkg[i][k] =0.;
	       if(nFoundBkgRaw==0.) rejBkg[i][k] =100.;
	       /*
		        cout<<"===================================================================================="<<endl;
			cout<<"eta Bin "<<i<<" entries of signal(2sigma):"<<nFoundSig[i][k]<<endl;
			cout<<"eta Bin "<<i<<" entries of bkg(out4sigma):"<<nFoundBkg[i][k]<<endl;
			cout<<"eta Bin "<<i<<" entries of signalRaw:"<<nFoundSigRaw[i]<<endl;
			cout<<"eta Bin "<<i<<" entries of bkgRaw:"<<nFoundBkgRaw[i]<<endl;
			cout<<"eta Bin "<<i<<" entries of signalFull:"<<nFoundSigFull[i][k]<<endl;
			cout<<"eta Bin "<<i<<" entries of bkgFull:"<<nFoundBkgFull[i][k]<<endl;
			*/
			cout<<"eta Bin "<<i<<" efficency of signal(%):"<<effSig[i][k]<<endl;
			cout<<"eta Bin "<<i<<" rejection of bkg(%):"<<rejBkg[i][k]<<endl;
			cout<<endl;
			
			outTxt<<"===================================================================================="<<endl;
			//outTxt<<"eta Bin "<<i<<" entries of signal(2sigma):"<<nFoundSig[i][k]<<endl;
			//outTxt<<"eta Bin "<<i<<" entries of bkg(out4sigma):"<<nFoundBkg[i][k]<<endl;
			//outTxt<<"eta Bin "<<i<<" entries of signalRaw:"<<nFoundSigRaw[i]<<endl;
			//outTxt<<"eta Bin "<<i<<" entries of bkgRaw:"<<nFoundBkgRaw[i]<<endl;
			//outTxt<<"eta Bin "<<i<<" entries of signalFull:"<<nFoundSigFull[i][k]<<endl;
			//outTxt<<"eta Bin "<<i<<" entries of bkgFull:"<<nFoundBkgFull[i][k]<<endl;
			outTxt<<"eta Bin "<<i<<" efficency of signal(%):"<<effSig[i][k]<<endl;
			outTxt<<"eta Bin "<<i<<" rejection of bkg(%):"<<rejBkg[i][k]<<endl;
			outTxt<<endl;
	     }
	 }

          //generate a data file convenient to make data table
       	    for(int i=0; i<nBin; i++)
	      {
		cout<<"eta Bin: "<<i<<endl;
		outTxt<<"eta Bin: "<<i<<endl;
		for(int j=0; j<num; j++)
		{
		  //dataFile<<"bn["<<i+1<<"]="<<"&signal "<<"&"<<effSig[i][j]<<"\t";
		  dataFile<<"etaBin"<<i<<" errorM "<<err_sig[i][j]<<endl;
		  cout<<endl;
		  dataFile<<"etaBin"<<i<<" errorR "<<errorR[i][j]<<endl;
		}
		cout<<endl;
		/*
		for(int j=0; j<num; j++)
		{
		  dataFile<<"bin["<<i+1<<"]="<<"&RejBkg "<<"&"<<rejBkg[i][j]<<"\t";
		}
		*/
		cout<<endl;
		outTxt<<endl;
		dataFile<<endl;
	      }
	


         
           //draw effSig and rejBkg
             TCanvas *c4[nBin];
             for(int i=0; i<nBin; i++)
	       {
		  c4[i]=new TCanvas(Form("c4_%d",i),"");
		  c4[i]->SetFillColor(10);
		  
		  //SetMyStyle();
		  gStyle->SetTitleXOffset(1.2); 
		  gStyle->SetTitleYOffset(1.3); 
		  gPad->SetLeftMargin(0.12);  
		  gPad->SetBottomMargin(0.12);
		  gPad->SetRightMargin(0.12); 
		  gPad->SetTopMargin(0.12); 
		  
		  TGraph *effSignal=new TGraph(num,cutVal,effSig[i]);
		  //TGraphErrors *effSignal=new TGraphErrors(num,cutVal,effSigs[i],0,err_effi[i]);
		  effSignal->SetMarkerColor(2);
		  effSignal->SetMarkerStyle(21);
		  effSignal->SetMarkerSize(1.5);
		  effSignal->SetLineColor(2);
		  effSignal->GetXaxis()->SetTitle(cutVar);
		  effSignal->GetXaxis()->CenterTitle();
		  effSignal->GetYaxis()->SetTitle("efficency (%)");
		  effSignal->GetYaxis()->CenterTitle();
		  
		  TGraph *rejBackground=new TGraph(num,cutVal,rejBkg[i]);
		  //TGraphErrors *rejBackground=new TGraphErrors(num,cutVal,rejBkg[i],0,err_rejbkg[i]);
		  rejBackground->SetMarkerColor(4);
		  rejBackground->SetMarkerStyle(23);
		  rejBackground->SetMarkerSize(1.5);
		  rejBackground->SetLineColor(4);
		  
		  //Vineet
		  if(i==0) effSignal->SetTitle(Form("|y|<%.1f, P_{T}>%.1f",1.2,0.0));
		  //if(i==0) effSignal->SetTitle(Form("|y|<%.1f, P_{T}>%.1f",2.4,6.0));
		  
		  
		  if(i==1) effSignal->SetTitle(Form("%.1f<|y|<%.1f, P_{T}>%.1f",1.2,1.6,0.0));
		  if(i==2) effSignal->SetTitle(Form("%.1f<|y|<%.1f, P_{T}>%.1f",1.6,2.4,0.0));
		  effSignal->GetYaxis()->SetRangeUser(0.,120.);
		  effSignal->Draw("ALP");
		  rejBackground->Draw("PL");
		  
		  TLegend *leg = new TLegend(0.80,0.80,0.95,0.93);
		  leg->AddEntry(effSignal,"effSig","p");
		  leg->AddEntry(rejBackground,"rejectBkg","p");
		  leg->Draw();
		  c4[i]->Update();
		  c4[i]->Print(Form("WeightMC/pic/MC/%s/EffRejec_etaBin%d.eps",cutVar,i));
		  c4[i]->Print(Form("WeightMC/pic/MC/%s/EffRejec_etaBin%d.C",cutVar,i));
		  c4[i]->Print(Form("WeightMC/pic/MC/%s/EffRejec_etaBin%d.gif",cutVar,i));
		}
	      /*
		TCanvas *c5[nBin];
		for(int i=0; i<nBin; i++)
	      {
	      c5[i]=new TCanvas(Form("c5_%d",i),"");
	      c5[i]->SetFillColor(10);
	      
	      //SetMyStyle();
	      gStyle->SetTitleXOffset(1.2); 
	      gStyle->SetTitleYOffset(1.3); 
	      gPad->SetLeftMargin(0.12);  
	      gPad->SetBottomMargin(0.12);
	      gPad->SetRightMargin(0.12); 
	      gPad->SetTopMargin(0.12); 
	      
	      //TGraph *Significance=new TGraph(num,cutVal,SGF[i]);
	      TGraphErrors *Significance=new TGraphErrors(num,cutVal,SGF[i],0,err_sgf[i]);
	      Significance->SetMarkerColor(2);
	      Significance->SetMarkerStyle(21);
	      Significance->SetMarkerSize(1.5);
	      Significance->SetLineColor(2);
	      Significance->GetXaxis()->SetTitle(cutVar);
	      Significance->GetXaxis()->CenterTitle();
	      Significance->GetYaxis()->SetTitle("Significance");
	      Significance->GetYaxis()->CenterTitle();
	      
	      //TGraph *rejBackground=new TGraph(num,cutVal,rejBkg[i]);
	      //rejBackground->SetMarkerColor(4);
	      //rejBackground->SetMarkerStyle(23);
	      //rejBackground->SetMarkerSize(1.5);
	      //rejBackground->SetLineColor(4);
	      
	      if(i==0) Significance->SetTitle(Form("|y|<%.1f, P_{T}>%.1f",1.2,0.0));
	      //if(i==0) Significance->SetTitle(Form("|y|<%.1f, P_{T}>%.1f",2.4,6.0));
	      
	      
	      if(i==1) Significance->SetTitle(Form("%.1f<|y|<%.1f, P_{T}>%.1f",1.2,1.6,0.0));
	      if(i==2) Significance->SetTitle(Form("%.1f<|y|<%.1f, P_{T}>%.1f",1.6,2.4,0.0));
	      
	      Significance->GetYaxis()->SetRangeUser(0.,15.);
	      Significance->Draw("ALP");
	      
	      
	      TLegend *leg = new TLegend(0.80,0.80,0.95,0.93);
	      leg->AddEntry(Significance,"SGF","p");
	      //leg->AddEntry(rejBackground,"rejectBkg","p");
	      leg->Draw();
	      
	      c5[i]->Update();
	      c5[i]->Print(Form("pic/DT/%s/SGF_etaBin%d.eps",cutVar,i));
	      c5[i]->Print(Form("pic/DT/%s/SGF_etaBin%d.C",cutVar,i));
	      c5[i]->Print(Form("pic/DT/%s/SGF_etaBin%d.gif",cutVar,i));
	      }
	    */
  
	    outTxt.close();
	    dataFile.close();
            return;
//}//CT
}


