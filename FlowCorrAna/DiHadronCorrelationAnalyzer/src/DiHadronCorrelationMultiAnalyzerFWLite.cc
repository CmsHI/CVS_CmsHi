#include "../interface/DiHadronCorrelationMultiAnalyzerFWLite.h"
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

DiHadronCorrelationMultiAnalyzerFWLite::DiHadronCorrelationMultiAnalyzerFWLite(fwlite::ChainEvent& Event) :
  DiHadronCorrelationMultiBaseFWLite(Event),
  signalTrgEffWeight(0),
  bkgTrgEffWeight(0),
  bkgAssEffWeight(0),
  bkgFactor(10)
{
  cutPara.IsSymmetrize=0;
  cutPara.IsPtWeight=0;
  cutPara.IsHarmonics=0;
}

DiHadronCorrelationMultiAnalyzerFWLite::~DiHadronCorrelationMultiAnalyzerFWLite() 
{}

void DiHadronCorrelationMultiAnalyzerFWLite::Process()
{
  DiHadronCorrelationMultiBaseFWLite::Process();

  if(!cutPara.IsCorr) return;

  cout<< "Start sorting the events!" << endl;
  std::sort(eventcorrArray.begin(),eventcorrArray.end());
  cout<< "Finish sorting the events!" << endl;

  cout<< "Start running correlation analysis!" << endl;
  for(unsigned int i=0;i<eventcorrArray.size();i++)
  {
    if( i % 100 == 0 ) cout << "Processing " << i << "th event" << endl;
    FillHistsSignal(eventcorrArray[i]);
    unsigned int mixstart = i+1;
    unsigned int mixend = i+1+bkgFactor;
    if(mixend>eventcorrArray.size()) mixend=eventcorrArray.size();
    for(unsigned int j=mixstart;j<mixend;j++)
    {
      if(eventcorrArray[i].centbin != eventcorrArray[j].centbin) break;
      double deltazvtx = eventcorrArray[i].zvtx-eventcorrArray[j].zvtx;
      hDeltaZvtx->Fill(deltazvtx);
      FillHistsBackground(eventcorrArray[i],eventcorrArray[j]);
    }
  }
  cout<< "Finish running correlation analysis!" << endl;

  NormalizeHists();
  cout<< "Finish normalizing the histograms!" << endl;  
}

void DiHadronCorrelationMultiAnalyzerFWLite::MakeHists()
{

  double etabinwidth = (cutPara.etatrgmax-cutPara.etaassmin-cutPara.etatrgmin+cutPara.etaassmax)/NEtaBins;
  double phibinwidth = 2*PI/NPhiBins;

  hDeltaZvtx = new TH1D("deltazvtx",";#Delta z_{vtx}",200,-1.0,-1.0);

  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
    {
      hSignal[itrg][jass] = new TH2D(Form("signal_trg%d_ass%d",itrg,jass),";#Delta#eta;#Delta#phi",
                                     NEtaBins+1,cutPara.etatrgmin-cutPara.etaassmax-etabinwidth/2.,cutPara.etatrgmax-cutPara.etaassmin+etabinwidth/2.,                    
	                             NPhiBins-1,-(PI-phibinwidth)/2.0,(PI*3.0-phibinwidth)/2.0);
      hSignal[itrg][jass]->Sumw2();
      hBackground[itrg][jass] = (TH2D*)hSignal[itrg][jass]->Clone(Form("background_trg%d_ass%d",itrg,jass));
      hCorrelation[itrg][jass] = (TH2D*)hSignal[itrg][jass]->Clone(Form("correlation_trg%d_ass%d",itrg,jass));

      if(cutPara.IsHarmonics)
      {
        hSignalCosn[itrg][jass] = new TH2D(Form("signalcosn_trg%d_ass%d",itrg,jass),";cos(n#Delta#phi);n",6000,-0.3,0.3,15,0.5,15.5);
        hBackgroundCosn[itrg][jass] = new TH2D(Form("backgroundcosn_trg%d_ass%d",itrg,jass),";cos(n#Delta#phi);n",6000,-0.3,0.3,15,0.5,15.5);
        hSignalSinn[itrg][jass] = new TH2D(Form("signalsinn_trg%d_ass%d",itrg,jass),";sin(n#Delta#phi);n",6000,-0.3,0.3,15,0.5,15.5);
        hBackgroundSinn[itrg][jass] = new TH2D(Form("backgroundsinn_trg%d_ass%d",itrg,jass),";sin(n#Delta#phi);n",6000,-0.3,0.3,15,0.5,15.5);
        hSignalRhon[itrg][jass] = new TH2D(Form("signalrhon_trg%d_ass%d",itrg,jass),";#rho;n",6000,0.0,0.6,15,0.5,15.5);
        hBackgroundRhon[itrg][jass] = new TH2D(Form("backgroundrhon_trg%d_ass%d",itrg,jass),";#rho;n",6000,0.0,0.6,15,0.5,15.5);
      }

      hSignal2PEPCorrelator[itrg][jass] = new TH1D(Form("signal2pepcorrelator_trg%d_ass%d",itrg,jass),";cos(#phi_{#alpha}-3#phi_{#beta}+2#Psi_{2})",6000,-0.3,0.3);
      hBackground2PEPCorrelator[itrg][jass] = new TH1D(Form("background2pepcorrelator_trg%d_ass%d",itrg,jass),";cos(#phi_{#alpha}-3#phi_{#beta}+2#Psi_{2})",6000,-0.3,0.3);

      hSignal_eta1eta2[itrg][jass] = new TH2D(Form("signal_eta1eta2_trg%d_ass%d",itrg,jass),";#eta_{1};#eta_{2}",
                                     NEtaBins*2+1,cutPara.etatrgmin-etabinwidth/2.,cutPara.etatrgmax+etabinwidth/2.,
                                     NEtaBins*2+1,cutPara.etaassmin-etabinwidth/2.,cutPara.etaassmax+etabinwidth/2.);
      hSignal_eta1eta2[itrg][jass]->Sumw2();
      hBackground_eta1eta2[itrg][jass] = (TH2D*)hSignal_eta1eta2[itrg][jass]->Clone(Form("background_eta1eta2_trg%d_ass%d",itrg,jass));
      hCorrelation_eta1eta2[itrg][jass] = (TH2D*)hSignal_eta1eta2[itrg][jass]->Clone(Form("correlation_eta1eta2_trg%d_ass%d",itrg,jass));

      hSignal_phi1phi2[itrg][jass] = new TH2D(Form("signal_phi1phi2_trg%d_ass%d",itrg,jass),";#phi_{1};#phi_{2}",
                                     NPhiBins*2+1,-PI-phibinwidth/2.,PI+phibinwidth/2.,
                                     NPhiBins*2+1,-PI-phibinwidth/2.,PI+phibinwidth/2.);
      hSignal_phi1phi2[itrg][jass]->Sumw2();
      hBackground_phi1phi2[itrg][jass] = (TH2D*)hSignal_phi1phi2[itrg][jass]->Clone(Form("background_phi1phi2_trg%d_ass%d",itrg,jass));
      hCorrelation_phi1phi2[itrg][jass] = (TH2D*)hSignal_phi1phi2[itrg][jass]->Clone(Form("correlation_phi1phi2_trg%d_ass%d",itrg,jass));
    }
  }
/*
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    hMult_trg[itrg] = new TH1D(Form("mult_trg_%d",itrg),";n^{trg}",2000,0,2000);
    hMultCorr_trg[itrg] = new TH1D(Form("multcorr_trg_%d",itrg),";n^{trg}",2000,0,2000);
    hpT_Signal_trg[itrg] = new TH1D(Form("pt_signal_trg_%d",itrg),";pT(GeV)",1000,0,100.);
    hpTCorr_Signal_trg[itrg] = new TH1D(Form("ptcorr_signal_trg_%d",itrg),";pT(GeV)",1000,0,100.);
    hpT_Background_trg[itrg] = new TH1D(Form("pt_background_trg_%d",itrg),";pT(GeV)",1000,0,100.);
    hpTCorr_Background_trg[itrg] = new TH1D(Form("ptcorr_background_trg_%d",itrg),";pT(GeV)",1000,0,100.);
    hdNdetadphi_trg[itrg] = new TH2D(Form("dNdetadphi_trg_%d",itrg),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
    hdNdetadphiCorr_trg[itrg] = new TH2D(Form("dNdetadphicorr_trg_%d",itrg),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
  }

  for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
  {
    hMult_ass[jass] = new TH1D(Form("mult_ass_%d",jass),";n^{ass}",2000,0,2000);
    hMultCorr_ass[jass] = new TH1D(Form("multcorr_ass_%d",jass),";n^{ass}",2000,0,2000);
    hpT_Signal_ass[jass] = new TH1D(Form("pt_signal_ass_%d",jass),";pT(GeV)",1000,0,100.);
    hpTCorr_Signal_ass[jass] = new TH1D(Form("ptcorr_signal_ass_%d",jass),";pT(GeV)",1000,0,100.);
    hpT_Background_ass[jass] = new TH1D(Form("pt_background_ass_%d",jass),";pT(GeV)",1000,0,100.);
    hpTCorr_Background_ass[jass] = new TH1D(Form("ptcorr_background_ass_%d",jass),";pT(GeV)",1000,0,100.);
    hdNdetadphi_ass[jass] = new TH2D(Form("dNdetadphi_ass_%d",jass),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
    hdNdetadphiCorr_ass[jass] = new TH2D(Form("dNdetadphicorr_ass_%d",jass),";#eta;#phi",60,-6.0,6.0,NPhiBins,-PI,PI);
  }
*/
  DiHadronCorrelationMultiBaseFWLite::MakeHists();
}

void DiHadronCorrelationMultiAnalyzerFWLite::NormalizeHists()
{
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
    {
      DiHadronCorrelationMultiBaseFWLite::NormalizeHists(itrg,jass);

      if(hSignal[itrg][jass]->Integral()==0) continue;
      if(hBackground[itrg][jass]->Integral()==0) continue;

      double  etabinwidth = hSignal[itrg][jass]->GetXaxis()->GetBinWidth(1);
      double  phibinwidth = hSignal[itrg][jass]->GetYaxis()->GetBinWidth(1);
 
      hSignal[itrg][jass]->Scale(1.0/etabinwidth/phibinwidth);
      hSignal_eta1eta2[itrg][jass]->Scale(1.0/etabinwidth/etabinwidth);
      hSignal_phi1phi2[itrg][jass]->Scale(1.0/phibinwidth/phibinwidth);

      hBackground[itrg][jass]->Scale(1.0/etabinwidth/phibinwidth);
      hBackground_eta1eta2[itrg][jass]->Scale(1.0/etabinwidth/etabinwidth);
      hBackground_phi1phi2[itrg][jass]->Scale(1.0/phibinwidth/phibinwidth);

      hCorrelation[itrg][jass]->Add(hSignal[itrg][jass]);
      hCorrelation[itrg][jass]->Divide(hBackground[itrg][jass]);
      hCorrelation[itrg][jass]->Scale(hBackground[itrg][jass]->GetBinContent(hBackground[itrg][jass]->FindBin(0,0)));  

     if(hBackground_eta1eta2[itrg][jass]) hCorrelation_eta1eta2[itrg][jass]->Divide(hBackground_eta1eta2[itrg][jass]);
     if(hBackground_phi1phi2[itrg][jass]) hCorrelation_phi1phi2[itrg][jass]->Divide(hBackground_phi1phi2[itrg][jass]);
    }
  }
}

void DiHadronCorrelationMultiAnalyzerFWLite::DeleteHists()
{
  DiHadronCorrelationMultiBaseFWLite::DeleteHists();	

  delete hDeltaZvtx;
  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
    {
      delete hSignal[itrg][jass];
      delete hBackground[itrg][jass];
      delete hCorrelation[itrg][jass];
      if(cutPara.IsHarmonics)
      {
        delete hSignalCosn[itrg][jass];
        delete hBackgroundCosn[itrg][jass];
        delete hSignalSinn[itrg][jass];
        delete hBackgroundSinn[itrg][jass];
        delete hSignalRhon[itrg][jass];
        delete hBackgroundRhon[itrg][jass];
      }
      delete hSignal2PEPCorrelator[itrg][jass];
      delete hBackground2PEPCorrelator[itrg][jass];
      delete hSignal_eta1eta2[itrg][jass];
      delete hBackground_eta1eta2[itrg][jass];
      delete hCorrelation_eta1eta2[itrg][jass];
      delete hSignal_phi1phi2[itrg][jass];
      delete hBackground_phi1phi2[itrg][jass];
      delete hCorrelation_phi1phi2[itrg][jass];

      if(cutPara.IsHI || !cutPara.IsCorr) return;

      delete hSignal_eta[itrg][jass];
      delete hBackground_eta[itrg][jass];
      delete hCorrelation_eta[itrg][jass];
      delete hSignal_phi[itrg][jass];
      delete hBackground_phi[itrg][jass];
      delete hCorrelation_phi[itrg][jass];
      delete hSignal_phi_short[itrg][jass];
      delete hBackground_phi_short[itrg][jass];
      delete hCorrelation_phi_short[itrg][jass];
      delete hSignal_phi_long[itrg][jass];
      delete hBackground_phi_long[itrg][jass];
      delete hCorrelation_phi_long[itrg][jass];
      delete hSignal_eta_near[itrg][jass];
      delete hBackground_eta_near[itrg][jass];
      delete hCorrelation_eta_near[itrg][jass];
      delete hSignal_eta_away[itrg][jass];
      delete hBackground_eta_away[itrg][jass];
      delete hCorrelation_eta_away[itrg][jass];
    }
  }

  for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
  {
    delete hMult_trg[itrg];
    delete hMultCorr_trg[itrg];
    delete hpT_Signal_trg[itrg];
    delete hpTCorr_Signal_trg[itrg];
    delete hpT_Background_trg[itrg];
    delete hpTCorr_Background_trg[itrg];
    delete hdNdetadphi_trg[itrg];
    delete hdNdetadphiCorr_trg[itrg];
  }
  
  for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
  { 
    delete hMult_ass[jass];
    delete hMultCorr_ass[jass];
    delete hpT_Signal_ass[jass];
    delete hpTCorr_Signal_ass[jass];
    delete hpT_Background_ass[jass];
    delete hpTCorr_Background_ass[jass];
    delete hdNdetadphi_ass[jass];
    delete hdNdetadphiCorr_ass[jass];
  }
}

//--------------- Calculate signal distributions ----------------------
void DiHadronCorrelationMultiAnalyzerFWLite::FillHistsSignal(const DiHadronCorrelationEvent& eventcorr)
{
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    nMult_trg[itrg]=eventcorr.pVect_trg[itrg].size();
    nMultCorr_trg[itrg]=0;
    for(unsigned int ntrg=0;ntrg<nMult_trg[itrg];ntrg++) nMultCorr_trg[itrg] = nMultCorr_trg[itrg] + 1.0/(eventcorr.effVect_trg[itrg])[ntrg];
  }

  for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
  {
    nMult_ass[jass]=eventcorr.pVect_ass[jass].size();
    nMultCorr_ass[jass]=0;
    for(unsigned int nass=0;nass<nMult_ass[jass];nass++) nMultCorr_ass[jass] = nMultCorr_ass[jass] + 1.0/(eventcorr.effVect_ass[jass])[nass];
  }

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
    for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
    {
      unsigned int ntrgsize = eventcorr.pVect_trg[itrg].size();
      unsigned int nasssize = eventcorr.pVect_ass[jass].size();

      double sumcosn[15]={0};
      double sumsinn[15]={0};
      double sumrhon[15]={0};
      double npairs[15]={0};
      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TVector3 pvector_trg = (eventcorr.pVect_trg[itrg])[ntrg];	  
        TLorentzVector part_trg(pvector_trg,sqrt(massTrg*massTrg+pvector_trg.Mag()*pvector_trg.Mag()));
        double effweight_trg = (eventcorr.effVect_trg[itrg])[ntrg];
        double chg_trg = (eventcorr.chgVect_trg[itrg])[ntrg];
        double eta_trg = pvector_trg.Eta();
        double phi_trg = pvector_trg.Phi();
        double pt_trg = pvector_trg.Pt();

        for(unsigned int nass=0;nass<nasssize;nass++)
        {
          TVector3 pvector_ass = (eventcorr.pVect_ass[jass])[nass];   
          TLorentzVector part_ass(pvector_ass,sqrt(massAss*massAss+pvector_ass.Mag()*pvector_ass.Mag()));
          double effweight_ass = (eventcorr.effVect_ass[jass])[nass];
          double chg_ass = (eventcorr.chgVect_ass[jass])[nass];
          double eta_ass = pvector_ass.Eta();
          double phi_ass = pvector_ass.Phi();
          double pt_ass = pvector_ass.Pt();

          // check charge sign
          if( (checksign == 0) && (chg_trg != chg_ass)) continue;
          if( (checksign == 1) && (chg_trg == chg_ass)) continue;

          double deltaPhi=GetDeltaPhi(phi_trg,phi_ass);
          double deltaEta=GetDeltaEta(eta_trg,eta_ass);

//          if(deltaEta==0.0 && deltaPhi==0.0) continue; // two particles are identical
          if(fabs(deltaEta)<0.028 && fabs(deltaPhi)<0.02) continue; // two particles are close 

          TLorentzVector part_total = part_ass + part_trg;
          double massInv = part_total.M();
          double openAngle = part_trg.Angle(part_ass.Vect());

          if(massTrg==0 && massAss==0 && openAngle>(0.22/part_total.Pt()-0.07/part_total.Pt()/part_total.Pt()) && openAngle<(0.65/part_total.Pt()-0.3/part_total.Pt()/part_total.Pt())) 
          {
            hInvMass_Signal->Fill(massInv);
            hInvMassVsPt_Signal->Fill(part_total.Pt(),massInv);
          }
          hOpenAngleVsPt_Signal->Fill(part_total.Pt(),openAngle);

          // total weight
          double effweight = effweight_trg * effweight_ass;
          if(cutPara.IsPtWeight) effweight = effweight / (pt_ass-ptMean2_ass[jass]/ptMean_ass[jass]) / (pt_trg-ptMean2_trg[itrg]/ptMean_trg[itrg]);
//          if(cutPara.IsPtWeight) effweight = effweight / pt_ass / pt_trg;

          // Direct calculation of Fourier harmonics for pairs
          if(cutPara.IsHarmonics && fabs(deltaEta)>2) 
          {
            for(int nn = 0; nn<15; nn++)
            {
//              if(nn==0) effweight = effweight * pt_ass * pt_trg / (pt_ass-ptMean2_ass[jass]/ptMean_ass[jass]) / (pt_trg-ptMean2_trg[itrg]/ptMean_trg[itrg])
              sumcosn[nn] = sumcosn[nn] + cos((nn+1)*fabs(deltaPhi))/effweight;
              sumsinn[nn] = sumsinn[nn] + sin((nn+1)*fabs(deltaPhi))/effweight;
              sumrhon[nn] = sumrhon[nn] + sqrt(sin((nn+1)*fabs(deltaPhi))*sin((nn+1)*fabs(deltaPhi))+cos((nn+1)*fabs(deltaPhi))*cos((nn+1)*fabs(deltaPhi)))/effweight;
              npairs[nn] += 1.0/effweight;
            }
          }

          // three particle correlators
          hSignal2PEPCorrelator[itrg][jass]->Fill(TMath::Cos(phi_trg-3*phi_ass+2*EPAngle),1.0/effweight);

          // Fill dihadron correlation functions
          if(!cutPara.IsSymmetrize)
          {
            hSignal[itrg][jass]->Fill(deltaEta,deltaPhi,1.0/effweight/nMultCorr_trg[itrg]);
            hSignal_eta1eta2[itrg][jass]->Fill(eta_trg,eta_ass,1.0/effweight/nMultCorr_trg[itrg]);
            hSignal_phi1phi2[itrg][jass]->Fill(phi_trg,phi_ass,1.0/effweight/nMultCorr_trg[itrg]);
          }
          else
          {
            hSignal[itrg][jass]->Fill(fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg[itrg]);
            hSignal[itrg][jass]->Fill(-fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg[itrg]);
            hSignal[itrg][jass]->Fill(fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg[itrg]);
            hSignal[itrg][jass]->Fill(-fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg[itrg]);
            hSignal[itrg][jass]->Fill(fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg[itrg]);
            hSignal[itrg][jass]->Fill(-fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight/nMultCorr_trg[itrg]);
          }
        }
      }

      if(cutPara.IsHarmonics) 
      { 
        for(int nn = 0; nn<15; nn++) 
        {
          if(!npairs[nn]) continue;
          hSignalCosn[itrg][jass]->Fill(sumcosn[nn]/npairs[nn],nn+1);
          hSignalSinn[itrg][jass]->Fill(sumsinn[nn]/npairs[nn],nn+1);
          hSignalRhon[itrg][jass]->Fill(sumrhon[nn]/npairs[nn],nn+1);
        }
      }
    } 

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  {
    hMult_trg[itrg]->Fill(nMult_trg[itrg]);
    hMultCorr_trg[itrg]->Fill(nMultCorr_trg[itrg]);
  }

  for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
  {
    hMult_ass[jass]->Fill(nMult_ass[jass]);
    hMultCorr_ass[jass]->Fill(nMultCorr_ass[jass]);
  }
}

void DiHadronCorrelationMultiAnalyzerFWLite::FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass)
{
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
    for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
    {
      unsigned int ntrgsize = eventcorr_trg.pVect_trg[itrg].size();
      unsigned int nasssize = eventcorr_ass.pVect_ass[jass].size();

      double sumcosn[15]={0};
      double sumsinn[15]={0};
      double sumrhon[15]={0};
      double npairs[15]={0};
      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TVector3 pvector_trg = (eventcorr_trg.pVect_trg[itrg])[ntrg];	  
        TLorentzVector part_trg(pvector_trg,sqrt(massTrg*massTrg+pvector_trg.Mag()*pvector_trg.Mag()));
        double effweight_trg = (eventcorr_trg.effVect_trg[itrg])[ntrg];
        double chg_trg = (eventcorr_trg.chgVect_trg[itrg])[ntrg];
        double eta_trg = pvector_trg.Eta();
        double phi_trg = pvector_trg.Phi();
        double pt_trg = pvector_trg.Pt();

        for(unsigned int nass=0;nass<nasssize;nass++)
        {
          TVector3 pvector_ass = (eventcorr_ass.pVect_ass[jass])[nass];   
          TLorentzVector part_ass(pvector_ass,sqrt(massAss*massAss+pvector_ass.Mag()*pvector_ass.Mag()));
          double effweight_ass = (eventcorr_ass.effVect_ass[jass])[nass];
          double chg_ass = (eventcorr_ass.chgVect_ass[jass])[nass];
          double eta_ass = pvector_ass.Eta();
          double phi_ass = pvector_ass.Phi();
          double pt_ass = pvector_ass.Pt();

          // check charge sign
          if( (checksign == 0) && (chg_trg != chg_ass)) continue;
          if( (checksign == 1) && (chg_trg == chg_ass)) continue;

          double deltaPhi=GetDeltaPhi(phi_trg,phi_ass);
          double deltaEta=GetDeltaEta(eta_trg,eta_ass);

          if(fabs(deltaEta)<0.028 && fabs(deltaPhi)<0.02) continue; // two particles are close 

          TLorentzVector part_total = part_ass + part_trg;
          double massInv = part_total.M();
          double openAngle = part_trg.Angle(part_ass.Vect());

          if(massTrg==0 && massAss==0 && openAngle>(0.22/part_total.Pt()-0.07/part_total.Pt()/part_total.Pt()) && openAngle<(0.65/part_total.Pt()-0.3/part_total.Pt()/part_total.Pt()))
          {
            hInvMass_Background->Fill(massInv);
            hInvMassVsPt_Background->Fill(part_total.Pt(),massInv);
          }
          hOpenAngleVsPt_Background->Fill(part_total.Pt(),openAngle);

          // total weight
          double effweight = effweight_trg * effweight_ass;
          if(cutPara.IsPtWeight) effweight = effweight / (pt_ass-ptMean2_ass[jass]/ptMean_ass[jass]) / (pt_trg-ptMean2_trg[itrg]/ptMean_trg[itrg]);
//          if(cutPara.IsPtWeight) effweight = effweight / pt_ass / pt_trg;

          // Direct calculation of Fourier harmonics for pairs
          if(cutPara.IsHarmonics && fabs(deltaEta)>2) 
          {
            for(int nn = 0; nn<15; nn++)
            {
//              if(nn==0) effweight = effweight * pt_ass * pt_trg / (pt_ass-ptMean2_ass[jass]/ptMean_ass[jass]) / (pt_trg-ptMean2_trg[itrg]/ptMean_trg[itrg]);
              sumcosn[nn] = sumcosn[nn] + cos((nn+1)*fabs(deltaPhi))/effweight;
              sumsinn[nn] = sumsinn[nn] + sin((nn+1)*fabs(deltaPhi))/effweight;
              sumrhon[nn] = sumrhon[nn] + sqrt(sin((nn+1)*fabs(deltaPhi))*sin((nn+1)*fabs(deltaPhi))+cos((nn+1)*fabs(deltaPhi))*cos((nn+1)*fabs(deltaPhi)))/effweight;
              npairs[nn] += 1.0/effweight;
            }
          }

          // three particle correlators
          hBackground2PEPCorrelator[itrg][jass]->Fill(TMath::Cos(phi_trg-3*phi_ass+2*EPAngle));

          // Fill dihadron correlation functions
          if(!cutPara.IsSymmetrize)
          {
            hBackground[itrg][jass]->Fill(deltaEta,deltaPhi,1.0/effweight);
            hBackground_eta1eta2[itrg][jass]->Fill(eta_trg,eta_ass,1.0/effweight);
            hBackground_phi1phi2[itrg][jass]->Fill(phi_trg,phi_ass,1.0/effweight);
          }
          else
          {
            hBackground[itrg][jass]->Fill(fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[itrg][jass]->Fill(-fabs(deltaEta),fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[itrg][jass]->Fill(fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[itrg][jass]->Fill(-fabs(deltaEta),-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[itrg][jass]->Fill(fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight);
            hBackground[itrg][jass]->Fill(-fabs(deltaEta),2*PI-fabs(deltaPhi),1.0/4.0/effweight);
          }
        }
      }

      if(cutPara.IsHarmonics)
      {
        for(int nn = 0; nn<15; nn++)
        {
          if(!npairs[nn]) continue;
          hBackgroundCosn[itrg][jass]->Fill(sumcosn[nn]/npairs[nn],nn+1);
          hBackgroundSinn[itrg][jass]->Fill(sumsinn[nn]/npairs[nn],nn+1);
          hBackgroundRhon[itrg][jass]->Fill(sumrhon[nn]/npairs[nn],nn+1);
        }
      }
    } 
}

TList* DiHadronCorrelationMultiAnalyzerFWLite::GetOutputs()
{
  TList* outputlist;

  if(cutPara.IsCorr)
  { 
    outputlist = new TList();
    outputlist->Add(hMultRawAll);
    outputlist->Add(hMultCorrAll);
    outputlist->Add(hDeltaZvtx);
    for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
    {
      for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
      {
        if(!cutPara.IsFullMatrix && itrg<jass) continue;
/*
        outputlist->Add(hSignal_eta1eta2[itrg][jass]);
        outputlist->Add(hBackground_eta1eta2[itrg][jass]);
        outputlist->Add(hCorrelation_eta1eta2[itrg][jass]);
        outputlist->Add(hSignal_phi1phi2[itrg][jass]);
        outputlist->Add(hBackground_phi1phi2[itrg][jass]);
        outputlist->Add(hCorrelation_phi1phi2[itrg][jass]);
*/
        outputlist->Add(hSignal[itrg][jass]);
        outputlist->Add(hBackground[itrg][jass]);
        outputlist->Add(hCorrelation[itrg][jass]);
        if(cutPara.IsHarmonics) 
        {
          outputlist->Add(hSignalCosn[itrg][jass]);
          outputlist->Add(hBackgroundCosn[itrg][jass]);
          outputlist->Add(hSignalSinn[itrg][jass]);
          outputlist->Add(hBackgroundSinn[itrg][jass]);
          outputlist->Add(hSignalRhon[itrg][jass]);
          outputlist->Add(hBackgroundRhon[itrg][jass]);
        }
        outputlist->Add(hSignal2PEPCorrelator[itrg][jass]);
        outputlist->Add(hBackground2PEPCorrelator[itrg][jass]);
/*
        outputlist->Add(hSignal_eta[itrg][jass]);
        outputlist->Add(hBackground_eta[itrg][jass]);
        outputlist->Add(hCorrelation_eta[itrg][jass]);
        outputlist->Add(hSignal_phi[itrg][jass]);
        outputlist->Add(hBackground_phi[itrg][jass]);
        outputlist->Add(hCorrelation_phi[itrg][jass]);
        outputlist->Add(hSignal_phi_short[itrg][jass]);
        outputlist->Add(hBackground_phi_short[itrg][jass]);
        outputlist->Add(hCorrelation_phi_short[itrg][jass]);
        outputlist->Add(hSignal_phi_long[itrg][jass]);
        outputlist->Add(hBackground_phi_long[itrg][jass]);
        outputlist->Add(hCorrelation_phi_long[itrg][jass]);
        outputlist->Add(hSignal_eta_near[itrg][jass]);
        outputlist->Add(hBackground_eta_near[itrg][jass]);
        outputlist->Add(hCorrelation_eta_near[itrg][jass]);
        outputlist->Add(hSignal_eta_away[itrg][jass]);
        outputlist->Add(hBackground_eta_away[itrg][jass]);
        outputlist->Add(hCorrelation_eta_away[itrg][jass]);
        outputlist->Add(hMultSignalPair[itrg][jass]);
        outputlist->Add(hMultBackgroundPair[itrg][jass]);
        outputlist->Add(hSignalPhiTotal[itrg][jass]);
        outputlist->Add(hBackgroundPhiTotal[itrg][jass]);
        outputlist->Add(hMultSignalPairVsPhiTotal[itrg][jass]);
        outputlist->Add(hMultBackgroundPairVsPhiTotal[itrg][jass]);
*/
      }
    }

    for(int itrg=0;itrg<(int)(cutPara.pttrgmin.size());itrg++)
    {
      outputlist->Add(hMult_trg[itrg]);
      outputlist->Add(hMultCorr_trg[itrg]);
      outputlist->Add(hpT_Signal_trg[itrg]);
      outputlist->Add(hpTCorr_Signal_trg[itrg]);
      outputlist->Add(hpT_Background_trg[itrg]);
      outputlist->Add(hpTCorr_Background_trg[itrg]);
      outputlist->Add(hdNdetadphi_trg[itrg]);
      outputlist->Add(hdNdetadphiCorr_trg[itrg]);
    } 
  
    for(int jass=0;jass<(int)(cutPara.ptassmin.size());jass++)
    {
      outputlist->Add(hMult_ass[jass]);
      outputlist->Add(hMultCorr_ass[jass]);
      outputlist->Add(hpT_Signal_ass[jass]);
      outputlist->Add(hpTCorr_Signal_ass[jass]);
      outputlist->Add(hpT_Background_ass[jass]);
      outputlist->Add(hpTCorr_Background_ass[jass]);
      outputlist->Add(hdNdetadphi_ass[jass]);
      outputlist->Add(hdNdetadphiCorr_ass[jass]);
    }
  }
  else outputlist = (TList*)DiHadronCorrelationMultiBaseFWLite::GetOutputs();

  return outputlist;
}
