#include "../interface/EventPlaneAnalyzerFWLite.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TMath.h>
#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>
#include <TList.h>
#include <TIterator.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TVector3.h>
#include <vector> 
#include <iostream>
#include "Math/Vector3D.h"

using namespace std;

EventPlaneAnalyzerFWLite::EventPlaneAnalyzerFWLite(fwlite::ChainEvent& Event) :
  DiHadronCorrelationMultiBaseFWLite(Event)
{}

EventPlaneAnalyzerFWLite::~EventPlaneAnalyzerFWLite() 
{}

void EventPlaneAnalyzerFWLite::Process()
{
  DiHadronCorrelationMultiBaseFWLite::Process();

  cout<< "Start sorting the events!" << endl;
  std::sort(eventcorrArray.begin(),eventcorrArray.end());
  cout<< "Finish sorting the events!" << endl;

  cout<< "Start running event plane analysis!" << endl;
  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsSignal(eventcorrArray[i]);
  }
  cout<< "Finish running event plane analysis!" << endl;

  NormalizeHists();
  cout<< "Finish normalizing the histograms!" << endl;  

}

void EventPlaneAnalyzerFWLite::MakeHists()
{
  double etabinwidth = (cutPara.etatrgmax-cutPara.etaassmin-cutPara.etatrgmin+cutPara.etaassmax)/NEtaBins;
  double phibinwidth = 2*PI/NPhiBins;

  for(int i=0;i<(int)(cutPara.pttrgmin.size());i++)
  {
      hSignal[i] = new TH2D(Form("signal_%d",i),";#eta;#Delta#phi",
                                     NEtaBins,cutPara.etatrgmin,cutPara.etatrgmax,                    
	                             NPhiBins,-PI,PI);
      hSignal[i]->Sumw2();
      hPsi = new TH1D("psi",";#Psi_{1}",100,-PI,PI);
  }

  DiHadronCorrelationMultiBaseFWLite::MakeHists();
}

void EventPlaneAnalyzerFWLite::NormalizeHists()
{}

void EventPlaneAnalyzerFWLite::DeleteHists()
{
  DiHadronCorrelationMultiBaseFWLite::DeleteHists();	

  for(int i=0;i<(int)(cutPara.pttrgmin.size());i++)
  {
      delete hSignal[i];
  }
}

//--------------- Calculate signal distributions ----------------------
void EventPlaneAnalyzerFWLite::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
   //calculate event plane angle
   double sumcos=0;
   double sumsin=0;
   unsigned int nasssize = eventcorr.pVect_ass[0].size();
   for(unsigned int n=0;n<nasssize;n++)
   {
     TVector3 pvector = (eventcorr.pVect_ass[0])[n];
     double eta = pvector.Eta();
     double phi = pvector.Phi();
     double pt  = pvector.Pt();
//     sumcos += (pt-ptMean2_ass[0]/ptMean_ass[0]) * cos(phi);
//     sumsin += (pt-ptMean2_ass[0]/ptMean_ass[0]) * sin(phi);
     sumcos += cos(phi);
     sumsin += sin(phi);
   }
   double psi1 = atan2(sumsin,sumcos);
   hPsi->Fill(psi1);

   for(unsigned int i=0;i<cutPara.pttrgmin.size();i++)
   {
     unsigned int ntrgsize = eventcorr.pVect_trg[i].size();

     for(unsigned int n=0;n<ntrgsize;n++)
     {
       TVector3 pvector = (eventcorr.pVect_trg[i])[n];	  
       double effweight = (eventcorr.effVect_trg[i])[n];
       double chg = (eventcorr.chgVect_trg[i])[n];
       double eta = pvector.Eta();
       double phi = pvector.Phi();
       double pt = pvector.Pt();
//       double deltaPhi = phi-eventcorr.epangle;
       double deltaPhi = phi-psi1;
       if(deltaPhi>PI) deltaPhi=deltaPhi-2*PI;
       if(deltaPhi<-PI) deltaPhi=2*PI+deltaPhi;

       hSignal[i]->Fill(eta,deltaPhi);
     }
   }
}

TList* EventPlaneAnalyzerFWLite::GetOutputs()
{
  TList* outputlist = (TList*)DiHadronCorrelationMultiBaseFWLite::GetOutputs();

  for(int i=0;i<(int)(cutPara.pttrgmin.size());i++)
  {
        outputlist->Add(hSignal[i]);
        outputlist->Add(hPsi);
  }

  return outputlist;
}
