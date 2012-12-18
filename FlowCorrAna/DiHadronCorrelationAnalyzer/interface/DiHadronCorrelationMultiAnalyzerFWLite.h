#ifndef DiHadronCorrelationMultiAnalyzerFWLite_
#define DiHadronCorrelationMultiAnalyzerFWLite_

#ifndef DiHadronCorrelationMultiBaseFWLite_
#include "DiHadronCorrelationMultiBaseFWLite.h"
#endif 

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class DiHadronCorrelationMultiAnalyzerFWLite : public DiHadronCorrelationMultiBaseFWLite {
   
 protected:

   // histograms
   TH1D*  hDeltaZvtx;
/*
   TH2D*  hdNdetadphi_trg[MAXPTTRGBINS];
   TH2D*  hdNdetadphi_ass[MAXPTASSBINS];
   TH2D*  hdNdetadphiCorr_trg[MAXPTTRGBINS];
   TH2D*  hdNdetadphiCorr_ass[MAXPTASSBINS];
   TH1D*  hMult_trg[MAXPTTRGBINS];
   TH1D*  hMult_ass[MAXPTASSBINS];
   TH1D*  hMultCorr_trg[MAXPTTRGBINS];
   TH1D*  hMultCorr_ass[MAXPTASSBINS];
   TH1D*  hpT_Signal_trg[MAXPTTRGBINS];
   TH1D*  hpT_Signal_ass[MAXPTASSBINS];
   TH1D*  hpTCorr_Signal_trg[MAXPTTRGBINS];
   TH1D*  hpTCorr_Signal_ass[MAXPTASSBINS];
   TH1D*  hpT_Background_trg[MAXPTTRGBINS];
   TH1D*  hpT_Background_ass[MAXPTASSBINS];
   TH1D*  hpTCorr_Background_trg[MAXPTTRGBINS];
   TH1D*  hpTCorr_Background_ass[MAXPTASSBINS];
*/
   TH2D* hSignal[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hBackground[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hCorrelation[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hSignalCosn[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hBackgroundCosn[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignal2PEPCorrelator[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackground2PEPCorrelator[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hSignal_eta1eta2[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hBackground_eta1eta2[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hCorrelation_eta1eta2[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hSignal_phi1phi2[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hBackground_phi1phi2[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hCorrelation_phi1phi2[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignal_eta[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackground_eta[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hCorrelation_eta[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignal_phi[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackground_phi[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hCorrelation_phi[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignal_phi_short[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackground_phi_short[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hCorrelation_phi_short[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignal_phi_long[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackground_phi_long[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hCorrelation_phi_long[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignal_eta_near[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackground_eta_near[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hCorrelation_eta_near[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignal_eta_away[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackground_eta_away[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hCorrelation_eta_away[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hMultSignalPair[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hMultBackgroundPair[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hSignalPhiTotal[MAXPTTRGBINS][MAXPTASSBINS];
   TH1D* hBackgroundPhiTotal[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hMultSignalPairVsPhiTotal[MAXPTTRGBINS][MAXPTASSBINS];
   TH2D* hMultBackgroundPairVsPhiTotal[MAXPTTRGBINS][MAXPTASSBINS];

   // parameters
   bool IsSymmetrize;
   bool IsPtWeight;
   bool IsHarmonics;
   double signalTrgEffWeight;
   double bkgTrgEffWeight;
   double bkgAssEffWeight;
   int  bkgFactor;
/*
   unsigned int nMult_trg[MAXPTTRGBINS];
   unsigned int nMult_ass[MAXPTASSBINS];
   double nMultCorr_trg[MAXPTTRGBINS];
   double nMultCorr_ass[MAXPTASSBINS];
   double ptMean_trg[MAXPTTRGBINS];
   double ptMean_ass[MAXPTASSBINS];
   double ptMean2_trg[MAXPTTRGBINS];
   double ptMean2_ass[MAXPTASSBINS];
*/
   virtual void Process(); 
   virtual void MakeHists();
   virtual void NormalizeHists();
   virtual void DeleteHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual void FillHistsBackground(const DiHadronCorrelationEvent& eventcorr_trg, const DiHadronCorrelationEvent& eventcorr_ass);
   virtual TList* GetOutputs();
   
 public:
   DiHadronCorrelationMultiAnalyzerFWLite(fwlite::ChainEvent&);
   virtual ~DiHadronCorrelationMultiAnalyzerFWLite();

   void SetSymmetrize() {IsSymmetrize = 1;}
   void SetPtWeight() {IsPtWeight = 1;}
   void SetHarmonics() {IsHarmonics = 1;}
   void SetBkgFactor(int bkgfactor) {bkgFactor = bkgfactor;}
};
#endif  // DiHadronCorrelationMultiAnalyzerFWLite_

