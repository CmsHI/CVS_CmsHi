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
This macro is used to get the "effSig" and "rejBkg" for every
cut individually. Need to include the macro "fitPeak.cc" 
to fit the Jpsi Mass distributions, and get the quantities we need.

Author : Linlin Zhang
-------------------------------*/
using namespace RooFit;

void cutAnaWeight_Other(int CT=11)
{
  
      gROOT->Reset();
      Long_t nEntries, nData=0;
      const int nBin=3;
      const ifile=6;
	
	/* ---------------------CT: Cut Type, num: value numbers for this cut------------------------ */
	char cutVar[100]; //cut Variables
	if(CT == 1) 
	{
		sprintf(cutVar,"mu_innerTrack_Hits");
		
	}
	if(CT == 2) 
	{
		sprintf(cutVar,"mu_pixeLayers");
		
	}
	if(CT == 3) 
	{
		sprintf(cutVar,"mu_nValidMuHits");
		
	}
	if(CT == 4) 
	{	
		sprintf(cutVar,"mu_innerTrack_chi2NDOF");
		
	}
	if(CT == 5) 
	{
		sprintf(cutVar,"mu_dxy");
		
	}
	if(CT == 6) 
	{
		sprintf(cutVar,"mu_dz");
		
	}
	if(CT == 7) 
	{
		sprintf(cutVar,"mu_globalTrack_chi2NDOF");
		
	}
	if(CT == 8) 
	{
		sprintf(cutVar,"vProb");
		
	}
	if(CT == 9) 
        {
	         sprintf(cutVar,"arbitration");
		
	}
	if(CT == 10) 
	{
		sprintf(cutVar,"mu_lastStationAngTight");
		
	}
	if(CT == 11) 
	{
		sprintf(cutVar,"Total");
		
	}


	cout<<"selection cut: "<<cutVar<<endl;

	double cutVal,Weight; //cut Values
	double nFoundSigRaw[nBin], nFoundBkgRaw[nBin];  // number of the signal and background with noCut
	double nFoundSig[nBin],nFoundBkg[nBin]; //num in the +-2sigma(signal) && out4sigma sideband(background)
	double nFoundSigFull[nBin],nFoundBkgFull[nBin];//num of signal yield && background
	double effSig[nBin], rejBkg[nBin];  //efficiency of keeping signal  && fraction of rejected background
	
	char fileName[ifile][500];
	char name[100];
	char outName[500];
	sprintf(name,
			"runs148819-149182_MuOnia"
			);
	sprintf(outName,
			Form("/home/abdulla/Desktop/new_m4/WeightMC/%s_%s.txt",name,cutVar));
	
	ofstream outTxt(outName);
	ofstream dataFile(Form("WeightMC/other_effi/%s_OtherEff_Wt.txt",cutVar));

	outTxt<<"cut Type: "<<cutVar<<endl;
	dataFile<<"cut Type "<<cutVar<<endl<<endl;
	
	Double_t massMin,massMax;
	massMin=2.6;
	massMax=3.5;
	RooRealVar *mass=new RooRealVar("mass","dimuon mass(GeV/c^{2})",2.6,3.5);
	RooRealVar *evtWeight= new RooRealVar("evtWeight","event weight",0.0,500.0);
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
	
	//Jpsi Variables
	Double_t JpsiMass,JpsiPt,JpsiRap;
	Double_t JpsiVprob;
	//(1).Positive Muon                                     
	double muPos_nchi2In, muPos_dxy, muPos_dz, muPos_nchi2Gl;
	int muPos_arbitrated, muPos_oneStationTight,muPos_lastStationAngTight;
	int muPos_found, muPos_pixeLayers, muPos_nValidMuHits,mu_Pos_SegMatch ;
	//(2).Negative Muon                                     
	double muNeg_nchi2In, muNeg_dxy, muNeg_dz, muNeg_nchi2Gl;
	int muNeg_arbitrated, muNeg_oneStationTight,muNeg_lastStationAngTight;
	int muNeg_found, muNeg_pixeLayers, muNeg_nValidMuHits,mu_Neg_SegMatch ;
	//Trigger Information                                   
	int HLT_L1DoubleMuOpen, HLT_Mu0_TkMu0_Jpsi, HLT_Mu0_TkMu0_OST_Jpsi_Tight_v2;
	
	//these to initialize the parameters of mass distribution,see "fitPeak.cc"
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


		double norm = 100;

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
			if(CT == 11) cutPass = muPos_found > 10 && muNeg_found > 10
				       &&muPos_pixeLayers > 0 && muNeg_pixeLayers > 0
				       //&&(muPos_nValidMuHits < -100 || (muPos_nValidMuHits > -100 && muPos_nValidMuHits > 6))
				       //&&(muNeg_nValidMuHits < -100 || (muNeg_nValidMuHits > -100 && muNeg_nValidMuHits > 6))
			             && muPos_nchi2In < 4.  && muNeg_nchi2In < 4. 
			             && fabs(muPos_dxy) < 3.  && fabs(muNeg_dxy) < 3. 
			             && fabs(muPos_dz) < 15.  && fabs(muNeg_dz) < 15. 
		                     && (muPos_nchi2Gl < -100. || (muPos_nchi2Gl > -100. && muPos_nchi2Gl < 6 ))
		                     && (muNeg_nchi2Gl < -100. || (muNeg_nchi2Gl > -100. && muNeg_nchi2Gl < 6 )) 
		                      && JpsiVprob > 0.01
				     && muPos_arbitrated == 1 && muNeg_arbitrated == 1;
					
			//--------------------------------------------------------------------------
			
			if(JpsiMass> massMin && JpsiMass< massMax)
			  {	
			    //Vineet
			    if(fabs(JpsiRap)<1.2 )
			      {
				mass.setVal(JpsiMass);
				dataRaw[0]->add(variables, Weight);
				
				if(cutPass)
				  {
				    data[0]->add(variables, Weight);
				    nData++;
				  }
			      }  
			    if(fabs(JpsiRap)>1.2 && fabs(JpsiRap)<1.6)
			      {
				mass.setVal(JpsiMass);
				dataRaw[1]->add(variables, Weight);
				if(cutPass)
				  {
				    //data[1]->add(mass);
				    data[1]->add(variables, Weight);
				    nData++;
				  }
			      }
			    if(fabs(JpsiRap)>1.6 && fabs(JpsiRap)<2.4)
			      {
				mass.setVal(JpsiMass);
				dataRaw[2]->add(variables,Weight);
				if(cutPass)
				  {
				    data[2]->add(variables,Weight);
				    nData++;
				  }
			      }
			    
			  }//if
		}//nEntries
	      }//ifile
	    
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
			nFoundSig[i]=sigBkg[i][4];
			nFoundBkg[i]=sigBkg[i][5];
			nFoundSigFull[i]=sigBkg[i][6];
			nFoundBkgFull[i]=sigBkg[i][5];
			//==============================================================================

				//------------Draw the Latex---------------
			Double_t left=0.12, top=0.83, textSize=0.033;
			TLatex *latex=new TLatex();
			latex->SetTextFont(42);
			latex->SetNDC(kTRUE);
			latex->SetTextSize(textSize);
			Double_t step=textSize*1.5;

			
			//Vineet
			if(i==0) latex->DrawLatex(left,top,Form("|y|<%.1f, P_{T}>%.1f",1.2,0.0));
			
			//if(i==0) latex->DrawLatex(left,top,Form("|y|<%.1f, P_{T}>%.1f",2.4,6.0));
			
			if(i==1) latex->DrawLatex(left,top,Form("%.1f<|y|<%.1f, P_{T}>%.1f",1.2,1.6,0.0));
			if(i==2) latex->DrawLatex(left,top,Form("%.1f<|y|<%.1f, P_{T}>%.1f",1.6,2.4,0.0));
			top-=step;
			
			//latex->DrawLatex(left,top,"HLT_Mu0_TkMu0_OST_Jpsi_Tight_v2");
			//latex->DrawLatex(left,top,"no trigger match");
			latex->DrawLatex(left,top,"HLT_HIL1DoubleMuOpen trigger");
			top-=step;
			latex->DrawLatex(left,top,Form("S / B(#pm2.0#sigma_{M})= %.1f",sigBkg[i][2]));
			top-=step;
			latex->DrawLatex(left,top,Form("S / sqrt(S+B)(#pm2.0#sigma_{M})= %.1f",sigBkg[i][3]));

			c1[i]->Modified();
			c1[i]->Update();

			//===for int type cut
			if(CT <= 3) 
			{
				c1[i]->Print(Form("WeightMC/other_effi/pic/DT/%s/etaBin%d_%s%d.eps",cutVar,i,cutVar));
				c1[i]->Print(Form("WeightMC/other_effi/pic/DT/%s/etaBin%d_%s%d.gif",cutVar,i,cutVar));
			}
			//===for double type cut
			if(CT >=4)
			{
				c1[i]->Print(Form("WeightMC/other_effi/pic/DT/%s/etaBin%d_%s%d_cut%d.eps",cutVar,i,cutVar));
				c1[i]->Print(Form("WeightMC/other_effi/pic/DT/%s/etaBin%d_%s%d_cut%d.gif",cutVar,i,cutVar));
			}
		}
		//}
	cout<<"----------------------------------------------------------------------------------------------"<<endl;
	cout<<"--------------------------------Loop on all cut DONE------------------------------------------"<<endl;
	cout<<"-----------------------------------------------------------------------------------------------"<<endl;

	vector<double> sigBkgRaw[nBin];
	TCanvas *c2[nBin];
	for(int i=0; i<nBin; i++)
	{
		c2[i]=new TCanvas(Form("c2_%d",i),"");
		sigBkgRaw[i].clear();
		//fit the mass to get the number of signal & bkg without CUT
		sigBkgRaw[i]=fitPeak_old(*mass,0,nPeak,0,dataRaw[i],fMean,dfMean,fSigma,dfSigma,0.5);
		nFoundSigRaw[i]=(double)sigBkgRaw[i][6];
		nFoundBkgRaw[i]=(double)sigBkgRaw[i][5];
		cout<<"=============nFoundSigRaw "<<i<<" :"<<nFoundSigRaw[i]<<"================="<<endl;
		cout<<"=============nFoundBkgRaw "<<i<<" :"<<nFoundBkgRaw[i]<<"================="<<endl;
	}

	for(int i=0; i<nBin; i++)
	  {
			//compute the effSig & rejBkg
			if(nFoundSigRaw[i]!=0.)
				effSig[i]=nFoundSigFull[i]/nFoundSigRaw[i]*100.;  //"100" means change to percent
			if(nFoundBkgRaw[i]!=0)
				rejBkg[i]=(nFoundBkgRaw[i]-nFoundBkgFull[i])/nFoundBkgRaw[i]*100.;
			//if(effSig[i] > 100.) effSig[i]=100.;
			//if(nFoundSigRaw[i]==0.) effSig[i]=0.;
			//if(rejBkg[i] < 0.) rejBkg[i] =0.;
			//if(nFoundBkgRaw[i]==0.) rejBkg[i] =100.;
			/*
			cout<<"===================================================================================="<<endl;
			cout<<"eta Bin "<<i<<" entries of signal(2sigma):"<<nFoundSig[i][k]<<endl;
			cout<<"eta Bin "<<i<<" entries of bkg(out4sigma):"<<nFoundBkg[i][k]<<endl;
			cout<<"eta Bin "<<i<<" entries of signalRaw:"<<nFoundSigRaw[i]<<endl;
			cout<<"eta Bin "<<i<<" entries of bkgRaw:"<<nFoundBkgRaw[i]<<endl;
			cout<<"eta Bin "<<i<<" entries of signalFull:"<<nFoundSigFull[i][k]<<endl;
			cout<<"eta Bin "<<i<<" entries of bkgFull:"<<nFoundBkgFull[i][k]<<endl;
			cout<<"eta Bin "<<i<<" efficency of signal(%):"<<effSig[i][k]<<endl;
			cout<<"eta Bin "<<i<<" rejection of bkg(%):"<<rejBkg[i][k]<<endl;
			cout<<endl;
			*/
			outTxt<<"===================================================================================="<<endl;
			outTxt<<"eta Bin "<<i<<" entries of signal(2sigma):"<<nFoundSig[i]<<endl;
			outTxt<<"eta Bin "<<i<<" entries of bkg(out4sigma):"<<nFoundBkg[i]<<endl;
			outTxt<<"eta Bin "<<i<<" entries of signalRaw:"<<nFoundSigRaw[i]<<endl;
			outTxt<<"eta Bin "<<i<<" entries of bkgRaw:"<<nFoundBkgRaw[i]<<endl;
			outTxt<<"eta Bin "<<i<<" entries of signalFull:"<<nFoundSigFull[i]<<endl;
			outTxt<<"eta Bin "<<i<<" entries of bkgFull:"<<nFoundBkgFull[i]<<endl;
			outTxt<<"eta Bin "<<i<<" efficency of signal(%):"<<effSig[i]<<endl;
			outTxt<<"eta Bin "<<i<<" rejection of bkg(%):"<<rejBkg[i]<<endl;

			//cout<<"eta Bin "<<i<<" entries of signal(2sigma):"<<nFoundSig[i]<<endl;
			//cout<<"eta Bin "<<i<<" entries of bkg(out4sigma):"<<nFoundBkg[i]<<endl;
			//cout<<"eta Bin "<<i<<" entries of signalRaw:"<<nFoundSigRaw[i]<<endl;
			//cout<<"eta Bin "<<i<<" entries of bkgRaw:"<<nFoundBkgRaw[i]<<endl;
			//cout<<"eta Bin "<<i<<" entries of signalFull:"<<nFoundSigFull[i]<<endl;
			//cout<<"eta Bin "<<i<<" entries of bkgFull:"<<nFoundBkgFull[i]<<endl;

			cout<<"eta Bin "<<i<<" efficency of signal(%):"<<effSig[i]<<endl;
			cout<<"eta Bin "<<i<<" rejection of bkg(%):"<<rejBkg[i]<<endl;
			outTxt<<endl;
	  }
	
	//generate a data file convenient to make data table
	for(int i=0; i<nBin; i++)
	{
	  cout<<"eta Bin: "<<i<<endl;
	  outTxt<<"eta Bin: "<<i<<endl;

	  //dataFile<<"etaBin"<<i<<" eff "<<effSig[i]<<endl;
	  //cout<<endl;
	  dataFile<<"&signal "<<"&"<<effSig[i]<<"\t";
	  //cout<<endl;
	  //dataFile<<"etaBin"<<i<<" rej "<<rejBkg[i]<<endl;
	}
	for(int i=0; i<nBin; i++)
	{
	  dataFile<<"&Rejbkg "<<"&"<<rejBkg[i]<<"\t";
	}
		cout<<endl;
		outTxt<<endl;
		dataFile<<endl;
       

	//draw effSig and rejBkg
		/*
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

		TGraph *effSignal=new TGraph(i,cutVar,effSig[i]);
		effSignal->SetMarkerColor(2);
		effSignal->SetMarkerStyle(21);
		effSignal->SetMarkerSize(1.5);
		effSignal->SetLineColor(2);
		effSignal->GetXaxis()->SetTitle(cutVar);
		effSignal->GetXaxis()->CenterTitle();
		effSignal->GetYaxis()->SetTitle("efficency (%)");
		effSignal->GetYaxis()->CenterTitle();

		TGraph *rejBackground=new TGraph(i,cutVar,rejBkg[i]);
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
		c4[i]->Print(Form("WeightMC/pic/DT/%s/EffRejec_etaBin%d.eps",cutVar,i));
		c4[i]->Print(Form("WeightMC/pic/DT/%s/EffRejec_etaBin%d.C",cutVar,i));
		c4[i]->Print(Form("WeightMC/pic/DT/%s/EffRejec_etaBin%d.gif",cutVar,i));
	}
	
		*/
	outTxt.close();
	dataFile.close();
	//}
	return;

}


/*

  In fitpeak.cc.

  “igPeak” is the probability in mass range (Mean-2*Sigma, Mean+2*Sigma), which signed "sig0" in the code,  for the peak PDF. 
  Not including the background.
  "ratioPeak" is signal events in the mass range "igPeak".
  "ratioBkg" is background events in the mass range "igPeak".
  "ratioSB1" is the mass width, which defined as  S/sqrt(S+B).
  
  "num0" is events in the mass range (Mean-2*Sigma, Mean+2*Sigma),  including both the signal and background.
  "num1" is events in the mass range (2.6GeV, Mean-4.*Sigma)  && (Mean+4*Sigma, 3.5GeV),  including both the signal and background. 
  
  In cutAna.cc,
  
  "nFoundSig" is events of "num0", including signal and background.
  "nFoundFull" is the total number of signals calclulated by fitting the mass distribution.  It is the value "areaPeak[0]->getVal()" in fitpeak.cc.
  From their definition,  we can know the difference between them. 
  
*/


/*

First, at the time of the construction of the RooDataSet you have to specify the variable which should be used to store the event weight, e.g.:

  RooRealVar *mass = new RooRealVar("mass","mass",0.0,10.0,"GeV/c^{2}");
  RooRealVar *evtWeight = new RooRealVar("evtWeight","event weight",0.0,100.0);
  RooArgList varlist(*mass, *evtWeight);
  RooDataSet *data = new RooDataSet("data","weighted dataset",varlist,RooFit::WeightVar("evtWeight"));

(or you can add that column afterwards using the addColumn() and setWeightVar() functions)

When you plot it, you should specify the error type to be "SumW2" to be sure it's calculating the proper error, which RooFit should pick automatically once you use non-integer weights:

  data->plotOn(tf,RooFit::DataError(RooAbsData::SumW2));

and I believe for the fitting one would need to enable "SumW2Error(kTRUE)" as well.

  model->fitTo(*data,RooFit::Extended(kTRUE),RooFit::Minos(kTRUE),RooFit::SumW2Error(kTRUE));

but in my test example I wasn't able to get the proper error on the fit result, while the plotted error seemed to be fine:

*/
