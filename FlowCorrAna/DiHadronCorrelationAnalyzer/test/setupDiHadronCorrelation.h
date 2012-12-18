#ifndef setupDiHadronCorrelation_
#define setupDiHadronCorrelation_

#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TList.h>
#include <TString.h>
#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "WeisQCDAna/DiHadronCorrelationAnalyzer/interface/CutParameters.h"
#include "RunAna.C"
#endif

int gCheckSign;
int gFfrom;
int gFto;
int gNCentBins;
int gCentRunnum;
int gNEtaBins;
int gNPhiBins;
int gBkgFactor;
int gEPIndex;
CutParameters gCut;
TString gFilesetname;
TString gOutputDir;
TString gCentfilename;
TString gCenttablename;
TString gEffhistname;
TString gTrghistname;
TString gPileupdistfunchistname;
TString gEventtype;
TString gTreename;
TString gTag;

void setup(int ffrom=0, int fto=1,
      	   double zvtxmin=-1.0, double zvtxmax=1.0,
           int nmin=-1, int nmax=-1,
           int centmin=-1, int centmax=-1);

//void saveoutput(TString outputfilename, TList* output);

#endif //setupDiHadronCorrelation_
