#include "commonSetup.h"

class Hlts
{
  public:

  Hlts(){};
  ~Hlts(){};

   // Declaration of leaf types

   Float_t         Npart;
   Float_t         Ncoll;
   Float_t         Nhard;
   Float_t         phi0;
   Float_t         b;
   Int_t           Ncharged;
   Int_t           NchargedMR;
   Float_t         MeanPt;
   Float_t         MeanPtMR;
   Float_t         EtMR;
   Int_t           NchargedPtCut;
   Int_t           NchargedPtCutMR;
   Int_t           hiBin;
   Float_t         hiHF;
   Float_t         hiHFplus;
   Float_t         hiHFminus;
   Float_t         hiZDC;
   Float_t         hiZDCplus;
   Float_t         hiZDCminus;
   Float_t         hiHFhit;
   Float_t         hiHFhitPlus;
   Float_t         hiHFhitMinus;
   Float_t         hiET;
   Float_t         hiEE;
   Float_t         hiEB;
   Float_t         hiEEplus;
   Float_t         hiEEminus;
   Int_t           hiNpix;
   Int_t           hiNpixelTracks;
   Int_t           hiNtracks;
   Int_t           hiNevtPlane;
   Float_t         hiEvtPlanes;
   Int_t           hiNtracksPtCut;
   Int_t           hiNtracksEtaCut;
   Int_t           hiNtracksEtaPtCut;
   Int_t           NrecoElec;
   Float_t         L1Met;
   Float_t         L1MetPhi;
   Float_t         L1EtTot;
   Float_t         L1Mht;
   Float_t         L1MhtPhi;
   Float_t         L1EtHad;
   Int_t           L1HfRing1EtSumPositiveEta;
   Int_t           L1HfRing2EtSumPositiveEta;
   Int_t           L1HfRing1EtSumNegativeEta;
   Int_t           L1HfRing2EtSumNegativeEta;
   Int_t           L1HfTowerCountPositiveEtaRing1;
   Int_t           L1HfTowerCountNegativeEtaRing1;
   Int_t           L1HfTowerCountPositiveEtaRing2;
   Int_t           L1HfTowerCountNegativeEtaRing2;
   Int_t           recoNVrt;
   Float_t         recoVrtX[maxEntry];   //[NVrtx]
   Float_t         recoVrtY[maxEntry];   //[NVrtx]
   Float_t         recoVrtZ[maxEntry];   //[NVrtx]
   Int_t           recoVrtNtrk[maxEntry];   //[NVrtx]
   Float_t         recoVrtChi2[maxEntry];   //[NVrtx]
   Float_t         recoVrtNdof[maxEntry];   //[NVrtx]
   Int_t           Run;
   Int_t           Event;
   Int_t           LumiBlock;
   Int_t           Bx;
   Int_t           Orbit;
   Float_t         AvgInstLumi;
   Int_t           HLT_LogMonitor;
   Int_t           HLT_LogMonitor_Prescl;
   Int_t           HLT_EcalCalibration;
   Int_t           HLT_EcalCalibration_Prescl;
   Int_t           HLT_HIZeroBias;
   Int_t           HLT_HIZeroBias_Prescl;
   Int_t           HLT_HIZeroBiasPixel_SingleTrack;
   Int_t           HLT_HIZeroBiasPixel_SingleTrack_Prescl;
   Int_t           HLT_HIMinBiasZDCPixel_SingleTrack;
   Int_t           HLT_HIMinBiasZDCPixel_SingleTrack_Prescl;
   Int_t           HLT_HIZeroBiasXOR;
   Int_t           HLT_HIZeroBiasXOR_Prescl;
   Int_t           HLT_HIMinBiasBSC_OR;
   Int_t           HLT_HIMinBiasBSC_OR_Prescl;
   Int_t           HLT_HIMinBiasBSC;
   Int_t           HLT_HIMinBiasBSC_Prescl;
   Int_t           HLT_HIMinBiasHF;
   Int_t           HLT_HIMinBiasHF_Prescl;
   Int_t           HLT_HIMinBiasHF_Core;
   Int_t           HLT_HIMinBiasHF_Core_Prescl;
   Int_t           HLT_HIMinBiasHfOrBSC;
   Int_t           HLT_HIMinBiasHfOrBSC_Prescl;
   Int_t           HLT_HIMinBiasHfOrBSC_Core;
   Int_t           HLT_HIMinBiasHfOrBSC_Core_Prescl;
   Int_t           HLT_HIMinBiasPixel_SingleTrack;
   Int_t           HLT_HIMinBiasPixel_SingleTrack_Prescl;
   Int_t           HLT_HIMinBiasZDC_Calo;
   Int_t           HLT_HIMinBiasZDC_Calo_Prescl;
   Int_t           HLT_HIMinBiasZDC_Calo_PlusOrMinus;
   Int_t           HLT_HIMinBiasZDC_Calo_PlusOrMinus_Prescl;
   Int_t           HLT_HIMinBiasZDC_Scint;
   Int_t           HLT_HIMinBiasZDC_Scint_Prescl;
   Int_t           HLT_HIBptxXOR;
   Int_t           HLT_HIBptxXOR_Prescl;
   Int_t           HLT_HIL1Algo_BptxXOR_BSC_OR;
   Int_t           HLT_HIL1Algo_BptxXOR_BSC_OR_Prescl;
   Int_t           HLT_HIL1SingleMu3;
   Int_t           HLT_HIL1SingleMu3_Prescl;
   Int_t           HLT_HIL1SingleMu5;
   Int_t           HLT_HIL1SingleMu5_Prescl;
   Int_t           HLT_HIL1SingleMu7;
   Int_t           HLT_HIL1SingleMu7_Prescl;
   Int_t           HLT_HIL1DoubleMuOpen;
   Int_t           HLT_HIL1DoubleMuOpen_Prescl;
   Int_t           HLT_HIL1DoubleMuOpen_Core;
   Int_t           HLT_HIL1DoubleMuOpen_Core_Prescl;
   Int_t           HLT_HIUpcEcal;
   Int_t           HLT_HIUpcEcal_Prescl;
   Int_t           HLT_HIUpcEcal_Core;
   Int_t           HLT_HIUpcEcal_Core_Prescl;
   Int_t           HLT_HIUpcMu;
   Int_t           HLT_HIUpcMu_Prescl;
   Int_t           HLT_HIUpcMu_Core;
   Int_t           HLT_HIUpcMu_Core_Prescl;
   Int_t           HLT_HIPhoton15;
   Int_t           HLT_HIPhoton15_Prescl;
   Int_t           HLT_HIPhoton15_Core;
   Int_t           HLT_HIPhoton15_Core_Prescl;
   Int_t           HLT_HIPhoton20;
   Int_t           HLT_HIPhoton20_Prescl;
   Int_t           HLT_HIPhoton20_Core;
   Int_t           HLT_HIPhoton20_Core_Prescl;
   Int_t           HLT_HIPhoton30;
   Int_t           HLT_HIPhoton30_Prescl;
   Int_t           HLT_HIPhoton30_Core;
   Int_t           HLT_HIPhoton30_Core_Prescl;
   Int_t           HLT_HIDoublePhoton5_CEP_L1R;
   Int_t           HLT_HIDoublePhoton5_CEP_L1R_Prescl;
   Int_t           HLT_HIJet35U;
   Int_t           HLT_HIJet35U_Prescl;
   Int_t           HLT_HIJet35U_Core;
   Int_t           HLT_HIJet35U_Core_Prescl;
   Int_t           HLT_HIJet50U;
   Int_t           HLT_HIJet50U_Prescl;
   Int_t           HLT_HIJet50U_Core;
   Int_t           HLT_HIJet50U_Core_Prescl;
   Int_t           HLT_HIJet75U;
   Int_t           HLT_HIJet75U_Prescl;
   Int_t           HLT_HIJet75U_Core;
   Int_t           HLT_HIJet75U_Core_Prescl;
   Int_t           HLT_HIJet90U;
   Int_t           HLT_HIJet90U_Prescl;
   Int_t           HLT_HIJet90U_Core;
   Int_t           HLT_HIJet90U_Core_Prescl;
   Int_t           HLT_HIStoppedHSCP35;
   Int_t           HLT_HIStoppedHSCP35_Prescl;
   Int_t           HLT_HIClusterVertexCompatibility;
   Int_t           HLT_HIClusterVertexCompatibility_Prescl;
   Int_t           HLT_HICentralityVeto;
   Int_t           HLT_HICentralityVeto_Prescl;
   Int_t           HLT_HIRandom;
   Int_t           HLT_HIRandom_Prescl;
   Int_t           HLT_HcalCalibration_HI;
   Int_t           HLT_HcalCalibration_HI_Prescl;
   Int_t           HLTriggerFinalPath;
   Int_t           HLTriggerFinalPath_Prescl;
   Int_t           L1_BptxMinus;
   Int_t           L1_BptxMinus_Prescl;
   Int_t           L1_BptxMinus_5bx;
   Int_t           L1_BptxMinus_NotBptxPlus;
   Int_t           L1_BptxMinus_NotBptxPlus_Prescl;
   Int_t           L1_BptxMinus_NotBptxPlus_5bx;
   Int_t           L1_BptxPlus;
   Int_t           L1_BptxPlus_Prescl;
   Int_t           L1_BptxPlus_5bx;
   Int_t           L1_BptxPlusANDMinus;
   Int_t           L1_BptxPlusANDMinus_Prescl;
   Int_t           L1_BptxPlusANDMinus_5bx;
   Int_t           L1_BptxPlusORMinus;
   Int_t           L1_BptxPlusORMinus_Prescl;
   Int_t           L1_BptxPlusORMinus_5bx;
   Int_t           L1_BptxPlusORMinus_instance1;
   Int_t           L1_BptxPlusORMinus_instance1_Prescl;
   Int_t           L1_BptxPlusORMinus_instance1_5bx;
   Int_t           L1_BptxPlus_NotBptxMinus;
   Int_t           L1_BptxPlus_NotBptxMinus_Prescl;
   Int_t           L1_BptxPlus_NotBptxMinus_5bx;
   Int_t           L1_BptxXOR;
   Int_t           L1_BptxXOR_Prescl;
   Int_t           L1_BptxXOR_5bx;
   Int_t           L1_BptxXOR_BscMinBiasOR;
   Int_t           L1_BptxXOR_BscMinBiasOR_Prescl;
   Int_t           L1_BptxXOR_BscMinBiasOR_5bx;
   Int_t           L1_Bsc2Minus_BptxMinus;
   Int_t           L1_Bsc2Minus_BptxMinus_Prescl;
   Int_t           L1_Bsc2Minus_BptxMinus_5bx;
   Int_t           L1_Bsc2Plus_BptxPlus;
   Int_t           L1_Bsc2Plus_BptxPlus_Prescl;
   Int_t           L1_Bsc2Plus_BptxPlus_5bx;
   Int_t           L1_BscMinBiasInnerThreshold1;
   Int_t           L1_BscMinBiasInnerThreshold1_Prescl;
   Int_t           L1_BscMinBiasInnerThreshold1_5bx;
   Int_t           L1_BscMinBiasInnerThreshold1_BptxAND;
   Int_t           L1_BscMinBiasInnerThreshold1_BptxAND_Prescl;
   Int_t           L1_BscMinBiasInnerThreshold1_BptxAND_5bx;
   Int_t           L1_BscMinBiasInnerThreshold2_BptxAND;
   Int_t           L1_BscMinBiasInnerThreshold2_BptxAND_Prescl;
   Int_t           L1_BscMinBiasInnerThreshold2_BptxAND_5bx;
   Int_t           L1_BscMinBiasOR_BptxAND;
   Int_t           L1_BscMinBiasOR_BptxAND_Prescl;
   Int_t           L1_BscMinBiasOR_BptxAND_5bx;
   Int_t           L1_BscMinBiasOR_BptxPlusORMinus;
   Int_t           L1_BscMinBiasOR_BptxPlusORMinus_Prescl;
   Int_t           L1_BscMinBiasOR_BptxPlusORMinus_5bx;
   Int_t           L1_BscMinBiasThreshold1;
   Int_t           L1_BscMinBiasThreshold1_Prescl;
   Int_t           L1_BscMinBiasThreshold1_5bx;
   Int_t           L1_BscMinBiasThreshold1_BptxAND;
   Int_t           L1_BscMinBiasThreshold1_BptxAND_Prescl;
   Int_t           L1_BscMinBiasThreshold1_BptxAND_5bx;
   Int_t           L1_BscMinBiasThreshold2_BptxAND;
   Int_t           L1_BscMinBiasThreshold2_BptxAND_Prescl;
   Int_t           L1_BscMinBiasThreshold2_BptxAND_5bx;
   Int_t           L1_DoubleEG2;
   Int_t           L1_DoubleEG2_Prescl;
   Int_t           L1_DoubleEG2_5bx;
   Int_t           L1_DoubleEG5;
   Int_t           L1_DoubleEG5_Prescl;
   Int_t           L1_DoubleEG5_5bx;
   Int_t           L1_DoubleEG5_BptxAND;
   Int_t           L1_DoubleEG5_BptxAND_Prescl;
   Int_t           L1_DoubleEG5_BptxAND_5bx;
   Int_t           L1_DoubleForJet10_EtaOpp;
   Int_t           L1_DoubleForJet10_EtaOpp_Prescl;
   Int_t           L1_DoubleForJet10_EtaOpp_5bx;
   Int_t           L1_DoubleHfBitCountsRing1_P1N1;
   Int_t           L1_DoubleHfBitCountsRing1_P1N1_Prescl;
   Int_t           L1_DoubleHfBitCountsRing1_P1N1_5bx;
   Int_t           L1_DoubleHfBitCountsRing2_P1N1;
   Int_t           L1_DoubleHfBitCountsRing2_P1N1_Prescl;
   Int_t           L1_DoubleHfBitCountsRing2_P1N1_5bx;
   Int_t           L1_DoubleHfRingEtSumsRing1_P200N200;
   Int_t           L1_DoubleHfRingEtSumsRing1_P200N200_Prescl;
   Int_t           L1_DoubleHfRingEtSumsRing1_P200N200_5bx;
   Int_t           L1_DoubleHfRingEtSumsRing1_P4N4;
   Int_t           L1_DoubleHfRingEtSumsRing1_P4N4_Prescl;
   Int_t           L1_DoubleHfRingEtSumsRing1_P4N4_5bx;
   Int_t           L1_DoubleHfRingEtSumsRing2_P200N200;
   Int_t           L1_DoubleHfRingEtSumsRing2_P200N200_Prescl;
   Int_t           L1_DoubleHfRingEtSumsRing2_P200N200_5bx;
   Int_t           L1_DoubleHfRingEtSumsRing2_P4N4;
   Int_t           L1_DoubleHfRingEtSumsRing2_P4N4_Prescl;
   Int_t           L1_DoubleHfRingEtSumsRing2_P4N4_5bx;
   Int_t           L1_DoubleJet30;
   Int_t           L1_DoubleJet30_Prescl;
   Int_t           L1_DoubleJet30_5bx;
   Int_t           L1_DoubleMu3;
   Int_t           L1_DoubleMu3_Prescl;
   Int_t           L1_DoubleMu3_5bx;
   Int_t           L1_DoubleMuOpen;
   Int_t           L1_DoubleMuOpen_Prescl;
   Int_t           L1_DoubleMuOpen_5bx;
   Int_t           L1_DoubleMuOpen_BptxAND;
   Int_t           L1_DoubleMuOpen_BptxAND_Prescl;
   Int_t           L1_DoubleMuOpen_BptxAND_5bx;
   Int_t           L1_ETM12;
   Int_t           L1_ETM12_Prescl;
   Int_t           L1_ETM12_5bx;
   Int_t           L1_ETM20;
   Int_t           L1_ETM20_Prescl;
   Int_t           L1_ETM20_5bx;
   Int_t           L1_ETM30;
   Int_t           L1_ETM30_Prescl;
   Int_t           L1_ETM30_5bx;
   Int_t           L1_ETM70;
   Int_t           L1_ETM70_Prescl;
   Int_t           L1_ETM70_5bx;
   Int_t           L1_ETT100;
   Int_t           L1_ETT100_Prescl;
   Int_t           L1_ETT100_5bx;
   Int_t           L1_ETT140;
   Int_t           L1_ETT140_Prescl;
   Int_t           L1_ETT140_5bx;
   Int_t           L1_ETT30;
   Int_t           L1_ETT30_Prescl;
   Int_t           L1_ETT30_5bx;
   Int_t           L1_ETT30_BptxAND;
   Int_t           L1_ETT30_BptxAND_Prescl;
   Int_t           L1_ETT30_BptxAND_5bx;
   Int_t           L1_ETT60;
   Int_t           L1_ETT60_Prescl;
   Int_t           L1_ETT60_5bx;
   Int_t           L1_ETT60_BptxAND;
   Int_t           L1_ETT60_BptxAND_Prescl;
   Int_t           L1_ETT60_BptxAND_5bx;
   Int_t           L1_HTM30;
   Int_t           L1_HTM30_Prescl;
   Int_t           L1_HTM30_5bx;
   Int_t           L1_HTT100;
   Int_t           L1_HTT100_Prescl;
   Int_t           L1_HTT100_5bx;
   Int_t           L1_HTT200;
   Int_t           L1_HTT200_Prescl;
   Int_t           L1_HTT200_5bx;
   Int_t           L1_HTT50;
   Int_t           L1_HTT50_Prescl;
   Int_t           L1_HTT50_5bx;
   Int_t           L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND;
   Int_t           L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl;
   Int_t           L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_5bx;
   Int_t           L1_HcalHfCoincidencePm;
   Int_t           L1_HcalHfCoincidencePm_Prescl;
   Int_t           L1_HcalHfCoincidencePm_5bx;
   Int_t           L1_HcalHfCoincidencePm_BptxAND;
   Int_t           L1_HcalHfCoincidencePm_BptxAND_Prescl;
   Int_t           L1_HcalHfCoincidencePm_BptxAND_5bx;
   Int_t           L1_HcalHfMmOrPpOrPm;
   Int_t           L1_HcalHfMmOrPpOrPm_Prescl;
   Int_t           L1_HcalHfMmOrPpOrPm_5bx;
   Int_t           L1_HcalHfMmOrPpOrPm_BptxAND;
   Int_t           L1_HcalHfMmOrPpOrPm_BptxAND_Prescl;
   Int_t           L1_HcalHfMmOrPpOrPm_BptxAND_5bx;
   Int_t           L1_HcalHfMmpOrMpp;
   Int_t           L1_HcalHfMmpOrMpp_Prescl;
   Int_t           L1_HcalHfMmpOrMpp_5bx;
   Int_t           L1_HcalHfMmpOrMpp_BptxAND;
   Int_t           L1_HcalHfMmpOrMpp_BptxAND_Prescl;
   Int_t           L1_HcalHfMmpOrMpp_BptxAND_5bx;
   Int_t           L1_HcalHoTotalOR;
   Int_t           L1_HcalHoTotalOR_Prescl;
   Int_t           L1_HcalHoTotalOR_5bx;
   Int_t           L1_Mu3_EG5;
   Int_t           L1_Mu3_EG5_Prescl;
   Int_t           L1_Mu3_EG5_5bx;
   Int_t           L1_Mu3_Jet10;
   Int_t           L1_Mu3_Jet10_Prescl;
   Int_t           L1_Mu3_Jet10_5bx;
   Int_t           L1_Mu3_Jet6;
   Int_t           L1_Mu3_Jet6_Prescl;
   Int_t           L1_Mu3_Jet6_5bx;
   Int_t           L1_Mu5_Jet6;
   Int_t           L1_Mu5_Jet6_Prescl;
   Int_t           L1_Mu5_Jet6_5bx;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_Prescl;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_5bx;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_Prescl;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_5bx;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasOR;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasOR_Prescl;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasOR_5bx;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasThreshold1;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasThreshold1_Prescl;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasThreshold1_5bx;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasThreshold2;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasThreshold2_Prescl;
   Int_t           L1_NotBsc2_BptxAND_BscMinBiasThreshold2_5bx;
   Int_t           L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1;
   Int_t           L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_Prescl;
   Int_t           L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_5bx;
   Int_t           L1_NotBsc2_BptxAND_HcalHfCoincidencePm;
   Int_t           L1_NotBsc2_BptxAND_HcalHfCoincidencePm_Prescl;
   Int_t           L1_NotBsc2_BptxAND_HcalHfCoincidencePm_5bx;
   Int_t           L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm;
   Int_t           L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_Prescl;
   Int_t           L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_5bx;
   Int_t           L1_NotBsc2_BptxAND_HcalHfMmpOrMpp;
   Int_t           L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_Prescl;
   Int_t           L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_5bx;
   Int_t           L1_NotBsc2_BscMinBiasInnerThreshold1;
   Int_t           L1_NotBsc2_BscMinBiasInnerThreshold1_Prescl;
   Int_t           L1_NotBsc2_BscMinBiasInnerThreshold1_5bx;
   Int_t           L1_NotBsc2_BscMinBiasInnerThreshold2;
   Int_t           L1_NotBsc2_BscMinBiasInnerThreshold2_Prescl;
   Int_t           L1_NotBsc2_BscMinBiasInnerThreshold2_5bx;
   Int_t           L1_NotBsc2_BscMinBiasOR;
   Int_t           L1_NotBsc2_BscMinBiasOR_Prescl;
   Int_t           L1_NotBsc2_BscMinBiasOR_5bx;
   Int_t           L1_NotBsc2_BscMinBiasThreshold1;
   Int_t           L1_NotBsc2_BscMinBiasThreshold1_Prescl;
   Int_t           L1_NotBsc2_BscMinBiasThreshold1_5bx;
   Int_t           L1_NotBsc2_BscMinBiasThreshold2;
   Int_t           L1_NotBsc2_BscMinBiasThreshold2_Prescl;
   Int_t           L1_NotBsc2_BscMinBiasThreshold2_5bx;
   Int_t           L1_NotBsc2_HcalHfCoincidencePm;
   Int_t           L1_NotBsc2_HcalHfCoincidencePm_Prescl;
   Int_t           L1_NotBsc2_HcalHfCoincidencePm_5bx;
   Int_t           L1_NotBsc2_HcalHfMmOrPpOrPm;
   Int_t           L1_NotBsc2_HcalHfMmOrPpOrPm_Prescl;
   Int_t           L1_NotBsc2_HcalHfMmOrPpOrPm_5bx;
   Int_t           L1_NotBsc2_HcalHfMmpOrMpp;
   Int_t           L1_NotBsc2_HcalHfMmpOrMpp_Prescl;
   Int_t           L1_NotBsc2_HcalHfMmpOrMpp_5bx;
   Int_t           L1_QuadJet6;
   Int_t           L1_QuadJet6_Prescl;
   Int_t           L1_QuadJet6_5bx;
   Int_t           L1_QuadJet8;
   Int_t           L1_QuadJet8_Prescl;
   Int_t           L1_QuadJet8_5bx;
   Int_t           L1_SingleEG10;
   Int_t           L1_SingleEG10_Prescl;
   Int_t           L1_SingleEG10_5bx;
   Int_t           L1_SingleEG12;
   Int_t           L1_SingleEG12_Prescl;
   Int_t           L1_SingleEG12_5bx;
   Int_t           L1_SingleEG15;
   Int_t           L1_SingleEG15_Prescl;
   Int_t           L1_SingleEG15_5bx;
   Int_t           L1_SingleEG2;
   Int_t           L1_SingleEG2_Prescl;
   Int_t           L1_SingleEG2_5bx;
   Int_t           L1_SingleEG20;
   Int_t           L1_SingleEG20_Prescl;
   Int_t           L1_SingleEG20_5bx;
   Int_t           L1_SingleEG2_BptxAND;
   Int_t           L1_SingleEG2_BptxAND_Prescl;
   Int_t           L1_SingleEG2_BptxAND_5bx;
   Int_t           L1_SingleEG5;
   Int_t           L1_SingleEG5_Prescl;
   Int_t           L1_SingleEG5_5bx;
   Int_t           L1_SingleEG5_BptxAND;
   Int_t           L1_SingleEG5_BptxAND_Prescl;
   Int_t           L1_SingleEG5_BptxAND_5bx;
   Int_t           L1_SingleEG8;
   Int_t           L1_SingleEG8_Prescl;
   Int_t           L1_SingleEG8_5bx;
   Int_t           L1_SingleForJet2;
   Int_t           L1_SingleForJet2_Prescl;
   Int_t           L1_SingleForJet2_5bx;
   Int_t           L1_SingleForJet4;
   Int_t           L1_SingleForJet4_Prescl;
   Int_t           L1_SingleForJet4_5bx;
   Int_t           L1_SingleJet10;
   Int_t           L1_SingleJet10_Prescl;
   Int_t           L1_SingleJet10_5bx;
   Int_t           L1_SingleJet20;
   Int_t           L1_SingleJet20_Prescl;
   Int_t           L1_SingleJet20_5bx;
   Int_t           L1_SingleJet20_BptxAND;
   Int_t           L1_SingleJet20_BptxAND_Prescl;
   Int_t           L1_SingleJet20_BptxAND_5bx;
   Int_t           L1_SingleJet20_NotBptxOR_Ext;
   Int_t           L1_SingleJet20_NotBptxOR_Ext_Prescl;
   Int_t           L1_SingleJet20_NotBptxOR_Ext_5bx;
   Int_t           L1_SingleJet30;
   Int_t           L1_SingleJet30_Prescl;
   Int_t           L1_SingleJet30_5bx;
   Int_t           L1_SingleJet30_BptxAND;
   Int_t           L1_SingleJet30_BptxAND_Prescl;
   Int_t           L1_SingleJet30_BptxAND_5bx;
   Int_t           L1_SingleJet40;
   Int_t           L1_SingleJet40_Prescl;
   Int_t           L1_SingleJet40_5bx;
   Int_t           L1_SingleJet40_BptxAND;
   Int_t           L1_SingleJet40_BptxAND_Prescl;
   Int_t           L1_SingleJet40_BptxAND_5bx;
   Int_t           L1_SingleJet50;
   Int_t           L1_SingleJet50_Prescl;
   Int_t           L1_SingleJet50_5bx;
   Int_t           L1_SingleJet50_BptxAND;
   Int_t           L1_SingleJet50_BptxAND_Prescl;
   Int_t           L1_SingleJet50_BptxAND_5bx;
   Int_t           L1_SingleJet6;
   Int_t           L1_SingleJet6_Prescl;
   Int_t           L1_SingleJet6_5bx;
   Int_t           L1_SingleJet60;
   Int_t           L1_SingleJet60_Prescl;
   Int_t           L1_SingleJet60_5bx;
   Int_t           L1_SingleMu0;
   Int_t           L1_SingleMu0_Prescl;
   Int_t           L1_SingleMu0_5bx;
   Int_t           L1_SingleMu10;
   Int_t           L1_SingleMu10_Prescl;
   Int_t           L1_SingleMu10_5bx;
   Int_t           L1_SingleMu14;
   Int_t           L1_SingleMu14_Prescl;
   Int_t           L1_SingleMu14_5bx;
   Int_t           L1_SingleMu20;
   Int_t           L1_SingleMu20_Prescl;
   Int_t           L1_SingleMu20_5bx;
   Int_t           L1_SingleMu3;
   Int_t           L1_SingleMu3_Prescl;
   Int_t           L1_SingleMu3_5bx;
   Int_t           L1_SingleMu3_BptxAND;
   Int_t           L1_SingleMu3_BptxAND_Prescl;
   Int_t           L1_SingleMu3_BptxAND_5bx;
   Int_t           L1_SingleMu5;
   Int_t           L1_SingleMu5_Prescl;
   Int_t           L1_SingleMu5_5bx;
   Int_t           L1_SingleMu7;
   Int_t           L1_SingleMu7_Prescl;
   Int_t           L1_SingleMu7_5bx;
   Int_t           L1_SingleMuBeamHalo;
   Int_t           L1_SingleMuBeamHalo_Prescl;
   Int_t           L1_SingleMuBeamHalo_5bx;
   Int_t           L1_SingleMuOpen;
   Int_t           L1_SingleMuOpen_Prescl;
   Int_t           L1_SingleMuOpen_5bx;
   Int_t           L1_SingleTauJet50;
   Int_t           L1_SingleTauJet50_Prescl;
   Int_t           L1_SingleTauJet50_5bx;
   Int_t           L1_TripleJet14;
   Int_t           L1_TripleJet14_Prescl;
   Int_t           L1_TripleJet14_5bx;
   Int_t           L1_ZdcCaloMinus;
   Int_t           L1_ZdcCaloMinus_Prescl;
   Int_t           L1_ZdcCaloMinus_5bx;
   Int_t           L1_ZdcCaloMinus_BptxAND;
   Int_t           L1_ZdcCaloMinus_BptxAND_Prescl;
   Int_t           L1_ZdcCaloMinus_BptxAND_5bx;
   Int_t           L1_ZdcCaloPlus;
   Int_t           L1_ZdcCaloPlus_Prescl;
   Int_t           L1_ZdcCaloPlus_5bx;
   Int_t           L1_ZdcCaloPlus_BptxAND;
   Int_t           L1_ZdcCaloPlus_BptxAND_Prescl;
   Int_t           L1_ZdcCaloPlus_BptxAND_5bx;
   Int_t           L1_ZdcCaloPlus_ZdcCaloMinus;
   Int_t           L1_ZdcCaloPlus_ZdcCaloMinus_Prescl;
   Int_t           L1_ZdcCaloPlus_ZdcCaloMinus_5bx;
   Int_t           L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND;
   Int_t           L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_Prescl;
   Int_t           L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_5bx;
   Int_t           L1_ZdcScintLooseVertex;
   Int_t           L1_ZdcScintLooseVertex_Prescl;
   Int_t           L1_ZdcScintLooseVertex_5bx;
   Int_t           L1_ZdcScintLooseVertex_BptxAND;
   Int_t           L1_ZdcScintLooseVertex_BptxAND_Prescl;
   Int_t           L1_ZdcScintLooseVertex_BptxAND_5bx;
   Int_t           L1_ZdcScintMinus;
   Int_t           L1_ZdcScintMinus_Prescl;
   Int_t           L1_ZdcScintMinus_5bx;
   Int_t           L1_ZdcScintPlus;
   Int_t           L1_ZdcScintPlus_Prescl;
   Int_t           L1_ZdcScintPlus_5bx;
   Int_t           L1_ZdcScintTightVertex;
   Int_t           L1_ZdcScintTightVertex_Prescl;
   Int_t           L1_ZdcScintTightVertex_5bx;
   Int_t           L1_ZdcScintTightVertex_BptxAND;
   Int_t           L1_ZdcScintTightVertex_BptxAND_Prescl;
   Int_t           L1_ZdcScintTightVertex_BptxAND_5bx;
   Int_t           L1_ZeroBias_Ext;
   Int_t           L1_ZeroBias_Ext_Prescl;
   Int_t           L1_ZeroBias_Ext_5bx;
   Int_t           L1Tech_BPTX_minus_v0;
   Int_t           L1Tech_BPTX_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_minus_v0_5bx;
   Int_t           L1Tech_BPTX_minus_AND_not_plus_v0;
   Int_t           L1Tech_BPTX_minus_AND_not_plus_v0_Prescl;
   Int_t           L1Tech_BPTX_minus_AND_not_plus_v0_5bx;
   Int_t           L1Tech_BPTX_plus_v0;
   Int_t           L1Tech_BPTX_plus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_v0_5bx;
   Int_t           L1Tech_BPTX_plus_AND_NOT_minus_v0;
   Int_t           L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_AND_NOT_minus_v0_5bx;
   Int_t           L1Tech_BPTX_plus_AND_minus_v0;
   Int_t           L1Tech_BPTX_plus_AND_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_AND_minus_v0_5bx;
   Int_t           L1Tech_BPTX_plus_AND_minus_instance1_v0;
   Int_t           L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_AND_minus_instance1_v0_5bx;
   Int_t           L1Tech_BPTX_plus_OR_minus_v0;
   Int_t           L1Tech_BPTX_plus_OR_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_OR_minus_v0_5bx;
   Int_t           L1Tech_BPTX_quiet_v0;
   Int_t           L1Tech_BPTX_quiet_v0_Prescl;
   Int_t           L1Tech_BPTX_quiet_v0_5bx;
   Int_t           L1Tech_BSC_HighMultiplicity_v0;
   Int_t           L1Tech_BSC_HighMultiplicity_v0_Prescl;
   Int_t           L1Tech_BSC_HighMultiplicity_v0_5bx;
   Int_t           L1Tech_BSC_halo_beam1_inner_v0;
   Int_t           L1Tech_BSC_halo_beam1_inner_v0_Prescl;
   Int_t           L1Tech_BSC_halo_beam1_inner_v0_5bx;
   Int_t           L1Tech_BSC_halo_beam1_outer_v0;
   Int_t           L1Tech_BSC_halo_beam1_outer_v0_Prescl;
   Int_t           L1Tech_BSC_halo_beam1_outer_v0_5bx;
   Int_t           L1Tech_BSC_halo_beam2_inner_v0;
   Int_t           L1Tech_BSC_halo_beam2_inner_v0_Prescl;
   Int_t           L1Tech_BSC_halo_beam2_inner_v0_5bx;
   Int_t           L1Tech_BSC_halo_beam2_outer_v0;
   Int_t           L1Tech_BSC_halo_beam2_outer_v0_Prescl;
   Int_t           L1Tech_BSC_halo_beam2_outer_v0_5bx;
   Int_t           L1Tech_BSC_minBias_OR_v0;
   Int_t           L1Tech_BSC_minBias_OR_v0_Prescl;
   Int_t           L1Tech_BSC_minBias_OR_v0_5bx;
   Int_t           L1Tech_BSC_minBias_inner_threshold1_v0;
   Int_t           L1Tech_BSC_minBias_inner_threshold1_v0_Prescl;
   Int_t           L1Tech_BSC_minBias_inner_threshold1_v0_5bx;
   Int_t           L1Tech_BSC_minBias_inner_threshold2_v0;
   Int_t           L1Tech_BSC_minBias_inner_threshold2_v0_Prescl;
   Int_t           L1Tech_BSC_minBias_inner_threshold2_v0_5bx;
   Int_t           L1Tech_BSC_minBias_threshold1_v0;
   Int_t           L1Tech_BSC_minBias_threshold1_v0_Prescl;
   Int_t           L1Tech_BSC_minBias_threshold1_v0_5bx;
   Int_t           L1Tech_BSC_minBias_threshold2_v0;
   Int_t           L1Tech_BSC_minBias_threshold2_v0_Prescl;
   Int_t           L1Tech_BSC_minBias_threshold2_v0_5bx;
   Int_t           L1Tech_BSC_splash_beam1_v0;
   Int_t           L1Tech_BSC_splash_beam1_v0_Prescl;
   Int_t           L1Tech_BSC_splash_beam1_v0_5bx;
   Int_t           L1Tech_BSC_splash_beam2_v0;
   Int_t           L1Tech_BSC_splash_beam2_v0_Prescl;
   Int_t           L1Tech_BSC_splash_beam2_v0_5bx;
   Int_t           L1Tech_CASTOR_HaloMuon_v0;
   Int_t           L1Tech_CASTOR_HaloMuon_v0_Prescl;
   Int_t           L1Tech_CASTOR_HaloMuon_v0_5bx;
   Int_t           L1Tech_HCAL_HBHE_totalOR_v0;
   Int_t           L1Tech_HCAL_HBHE_totalOR_v0_Prescl;
   Int_t           L1Tech_HCAL_HBHE_totalOR_v0_5bx;
   Int_t           L1Tech_RPC_TTU_RB0_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RB0_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RB0_Cosmics_v0_5bx;
   Int_t           L1Tech_RPC_TTU_RBminus1_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RBminus1_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBminus1_Cosmics_v0_5bx;
   Int_t           L1Tech_RPC_TTU_RBminus2_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RBminus2_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBminus2_Cosmics_v0_5bx;
   Int_t           L1Tech_RPC_TTU_RBplus1_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBplus1_Cosmics_v0_5bx;
   Int_t           L1Tech_RPC_TTU_RBplus2_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBplus2_Cosmics_v0_5bx;
   Int_t           L1Tech_RPC_TTU_RBst1_collisions_v0;
   Int_t           L1Tech_RPC_TTU_RBst1_collisions_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBst1_collisions_v0_5bx;
   Int_t           L1Tech_RPC_TTU_barrel_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_barrel_Cosmics_v0_5bx;
   Int_t           L1Tech_RPC_TTU_pointing_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_pointing_Cosmics_v0_5bx;
   Int_t           L1Tech_ZDC_Scint_loose_vertex_v0;
   Int_t           L1Tech_ZDC_Scint_loose_vertex_v0_Prescl;
   Int_t           L1Tech_ZDC_Scint_loose_vertex_v0_5bx;
   Int_t           L1Tech_ZDC_Scint_minus_v0;
   Int_t           L1Tech_ZDC_Scint_minus_v0_Prescl;
   Int_t           L1Tech_ZDC_Scint_minus_v0_5bx;
   Int_t           L1Tech_ZDC_Scint_plus_v0;
   Int_t           L1Tech_ZDC_Scint_plus_v0_Prescl;
   Int_t           L1Tech_ZDC_Scint_plus_v0_5bx;
   Int_t           L1Tech_ZDC_Scint_tight_vertex_v0;
   Int_t           L1Tech_ZDC_Scint_tight_vertex_v0_Prescl;
   Int_t           L1Tech_ZDC_Scint_tight_vertex_v0_5bx;

   // List of branches
   TBranch        *b_NohBJetL2;   //!
   TBranch        *b_ohBJetL2Energy;   //!
   TBranch        *b_ohBJetL2Et;   //!
   TBranch        *b_ohBJetL2Pt;   //!
   TBranch        *b_ohBJetL2Eta;   //!
   TBranch        *b_ohBJetL2Phi;   //!
   TBranch        *b_NohBJetL2Corrected;   //!
   TBranch        *b_ohBJetL2CorrectedEnergy;   //!
   TBranch        *b_ohBJetL2CorrectedEt;   //!
   TBranch        *b_ohBJetL2CorrectedPt;   //!
   TBranch        *b_ohBJetL2CorrectedEta;   //!
   TBranch        *b_ohBJetL2CorrectedPhi;   //!
   TBranch        *b_ohBJetIPL25Tag;   //!
   TBranch        *b_ohBJetIPL3Tag;   //!
   TBranch        *b_ohBJetIPLooseL25Tag;   //!
   TBranch        *b_ohBJetIPLooseL3Tag;   //!
   TBranch        *b_ohBJetMuL25Tag;   //!
   TBranch        *b_ohBJetMuL3Tag;   //!
   TBranch        *b_ohBJetPerfL25Tag;   //!
   TBranch        *b_ohBJetPerfL3Tag;   //!
   TBranch        *b_Npart;   //!
   TBranch        *b_Ncoll;   //!
   TBranch        *b_Nhard;   //!
   TBranch        *b_NPhi0;   //!
   TBranch        *b_b;   //!
   TBranch        *b_Ncharged;   //!
   TBranch        *b_NchargedMR;   //!
   TBranch        *b_MeanPt;   //!
   TBranch        *b_MeanPtMR;   //!
   TBranch        *b_EtMR;   //!
   TBranch        *b_NchargedPtCut;   //!
   TBranch        *b_NchargedPtCutMR;   //!
   TBranch        *b_hiBin;   //!
   TBranch        *b_hiHF;   //!
   TBranch        *b_hiHFplus;   //!
   TBranch        *b_hiHFminus;   //!
   TBranch        *b_hiZDC;   //!
   TBranch        *b_hiZDCplus;   //!
   TBranch        *b_hiZDCminus;   //!
   TBranch        *b_hiHFhit;   //!
   TBranch        *b_hiHFhitPlus;   //!
   TBranch        *b_hiHFhitMinus;   //!
   TBranch        *b_hiET;   //!
   TBranch        *b_hiEE;   //!
   TBranch        *b_hiEB;   //!
   TBranch        *b_hiEEplus;   //!
   TBranch        *b_hiEEminus;   //!
   TBranch        *b_hiNpix;   //!
   TBranch        *b_hiNpixelTracks;   //!
   TBranch        *b_hiNtracks;   //!
   TBranch        *b_hiNevtPlane;   //!
   TBranch        *b_hiEvtPlanes;   //!
   TBranch        *b_hiNtracksPtCut;   //!
   TBranch        *b_hiNtracksEtaCut;   //!
   TBranch        *b_hiNtracksEtaPtCut;   //!
   TBranch        *b_NrecoElec;   //!
   TBranch        *b_recoElecPt;   //!
   TBranch        *b_recoElecPhi;   //!
   TBranch        *b_recoElecEta;   //!
   TBranch        *b_recoElecEt;   //!
   TBranch        *b_recoElecE;   //!
   TBranch        *b_recoElecEleID;   //!
   TBranch        *b_NrecoPhot;   //!
   TBranch        *b_recoPhotPt;   //!
   TBranch        *b_recoPhotPhi;   //!
   TBranch        *b_recoPhotEta;   //!
   TBranch        *b_recoPhotEt;   //!
   TBranch        *b_recoPhotE;   //!
   TBranch        *b_NrecoSC;   //!
   TBranch        *b_recoSCPt;   //!
   TBranch        *b_recoSCPhi;   //!
   TBranch        *b_recoSCEta;   //!
   TBranch        *b_recoSCEt;   //!
   TBranch        *b_recoSCE;   //!
   TBranch        *b_NohPhot;   //!
   TBranch        *b_ohPhotEt;   //!
   TBranch        *b_ohPhotEta;   //!
   TBranch        *b_ohPhotPhi;   //!
   TBranch        *b_ohPhotEiso;   //!
   TBranch        *b_ohPhotHiso;   //!
   TBranch        *b_ohPhotTiso;   //!
   TBranch        *b_ohPhotL1iso;   //!
   TBranch        *b_ohPhotClusShap;   //!
   TBranch        *b_NL1IsolEm;   //!
   TBranch        *b_L1IsolEmEt;   //!
   TBranch        *b_L1IsolEmE;   //!
   TBranch        *b_L1IsolEmEta;   //!
   TBranch        *b_L1IsolEmPhi;   //!
   TBranch        *b_NL1NIsolEm;   //!
   TBranch        *b_L1NIsolEmEt;   //!
   TBranch        *b_L1NIsolEmE;   //!
   TBranch        *b_L1NIsolEmEta;   //!
   TBranch        *b_L1NIsolEmPhi;   //!
   TBranch        *b_NL1Mu;   //!
   TBranch        *b_L1MuPt;   //!
   TBranch        *b_L1MuE;   //!
   TBranch        *b_L1MuEta;   //!
   TBranch        *b_L1MuPhi;   //!
   TBranch        *b_L1MuIsol;   //!
   TBranch        *b_L1MuMip;   //!
   TBranch        *b_L1MuFor;   //!
   TBranch        *b_L1MuRPC;   //!
   TBranch        *b_L1MuQal;   //!
   TBranch        *b_NL1CenJet;   //!
   TBranch        *b_L1CenJetEt;   //!
   TBranch        *b_L1CenJetE;   //!
   TBranch        *b_L1CenJetEta;   //!
   TBranch        *b_L1CenJetPhi;   //!
   TBranch        *b_NL1ForJet;   //!
   TBranch        *b_L1ForJetEt;   //!
   TBranch        *b_L1ForJetE;   //!
   TBranch        *b_L1ForJetEta;   //!
   TBranch        *b_L1ForJetPhi;   //!
   TBranch        *b_NL1Tau;   //!
   TBranch        *b_L1TauEt;   //!
   TBranch        *b_L1TauE;   //!
   TBranch        *b_L1TauEta;   //!
   TBranch        *b_L1TauPhi;   //!
   TBranch        *b_L1Met;   //!
   TBranch        *b_L1MetPhi;   //!
   TBranch        *b_L1EtTot;   //!
   TBranch        *b_L1Mht;   //!
   TBranch        *b_L1MhtPhi;   //!
   TBranch        *b_L1EtHad;   //!
   TBranch        *b_L1HfRing1EtSumPositiveEta;   //!
   TBranch        *b_L1HfRing2EtSumPositiveEta;   //!
   TBranch        *b_L1HfRing1EtSumNegativeEta;   //!
   TBranch        *b_L1HfRing2EtSumNegativeEta;   //!
   TBranch        *b_L1HfTowerCountPositiveEtaRing1;   //!
   TBranch        *b_L1HfTowerCountNegativeEtaRing1;   //!
   TBranch        *b_L1HfTowerCountPositiveEtaRing2;   //!
   TBranch        *b_L1HfTowerCountNegativeEtaRing2;   //!
   TBranch        *b_NVrtx;   //!
   TBranch        *b_recoVrtX;   //!
   TBranch        *b_recoVrtY;   //!
   TBranch        *b_recoVrtZ;   //!
   TBranch        *b_recoVrtNtrk;   //!
   TBranch        *b_recoVrtChi2;   //!
   TBranch        *b_recoVrtNdof;   //!
   TBranch        *b_Run;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_LumiBlock;   //!
   TBranch        *b_Bx;   //!
   TBranch        *b_Orbit;   //!
   TBranch        *b_AvgInstLumi;   //!
   TBranch        *b_HLT_LogMonitor;   //!
   TBranch        *b_HLT_LogMonitor_Prescl;   //!
   TBranch        *b_HLT_EcalCalibration;   //!
   TBranch        *b_HLT_EcalCalibration_Prescl;   //!
   TBranch        *b_HLT_HIZeroBias;   //!
   TBranch        *b_HLT_HIZeroBias_Prescl;   //!
   TBranch        *b_HLT_HIZeroBiasPixel_SingleTrack;   //!
   TBranch        *b_HLT_HIZeroBiasPixel_SingleTrack_Prescl;   //!
   TBranch        *b_HLT_HIMinBiasZDCPixel_SingleTrack;   //!
   TBranch        *b_HLT_HIMinBiasZDCPixel_SingleTrack_Prescl;   //!
   TBranch        *b_HLT_HIZeroBiasXOR;   //!
   TBranch        *b_HLT_HIZeroBiasXOR_Prescl;   //!
   TBranch        *b_HLT_HIMinBiasBSC_OR;   //!
   TBranch        *b_HLT_HIMinBiasBSC_OR_Prescl;   //!
   TBranch        *b_HLT_HIMinBiasBSC;   //!
   TBranch        *b_HLT_HIMinBiasBSC_Prescl;   //!
   TBranch        *b_HLT_HIMinBiasHF;   //!
   TBranch        *b_HLT_HIMinBiasHF_Prescl;   //!
   TBranch        *b_HLT_HIMinBiasHF_Core;   //!
   TBranch        *b_HLT_HIMinBiasHF_Core_Prescl;   //!
   TBranch        *b_HLT_HIMinBiasHfOrBSC;   //!
   TBranch        *b_HLT_HIMinBiasHfOrBSC_Prescl;   //!
   TBranch        *b_HLT_HIMinBiasHfOrBSC_Core;   //!
   TBranch        *b_HLT_HIMinBiasHfOrBSC_Core_Prescl;   //!
   TBranch        *b_HLT_HIMinBiasPixel_SingleTrack;   //!
   TBranch        *b_HLT_HIMinBiasPixel_SingleTrack_Prescl;   //!
   TBranch        *b_HLT_HIMinBiasZDC_Calo;   //!
   TBranch        *b_HLT_HIMinBiasZDC_Calo_Prescl;   //!
   TBranch        *b_HLT_HIMinBiasZDC_Calo_PlusOrMinus;   //!
   TBranch        *b_HLT_HIMinBiasZDC_Calo_PlusOrMinus_Prescl;   //!
   TBranch        *b_HLT_HIMinBiasZDC_Scint;   //!
   TBranch        *b_HLT_HIMinBiasZDC_Scint_Prescl;   //!
   TBranch        *b_HLT_HIBptxXOR;   //!
   TBranch        *b_HLT_HIBptxXOR_Prescl;   //!
   TBranch        *b_HLT_HIL1Algo_BptxXOR_BSC_OR;   //!
   TBranch        *b_HLT_HIL1Algo_BptxXOR_BSC_OR_Prescl;   //!
   TBranch        *b_HLT_HIL1SingleMu3;   //!
   TBranch        *b_HLT_HIL1SingleMu3_Prescl;   //!
   TBranch        *b_HLT_HIL1SingleMu5;   //!
   TBranch        *b_HLT_HIL1SingleMu5_Prescl;   //!
   TBranch        *b_HLT_HIL1SingleMu7;   //!
   TBranch        *b_HLT_HIL1SingleMu7_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMuOpen;   //!
   TBranch        *b_HLT_HIL1DoubleMuOpen_Prescl;   //!
   TBranch        *b_HLT_HIL1DoubleMuOpen_Core;   //!
   TBranch        *b_HLT_HIL1DoubleMuOpen_Core_Prescl;   //!
   TBranch        *b_HLT_HIUpcEcal;   //!
   TBranch        *b_HLT_HIUpcEcal_Prescl;   //!
   TBranch        *b_HLT_HIUpcEcal_Core;   //!
   TBranch        *b_HLT_HIUpcEcal_Core_Prescl;   //!
   TBranch        *b_HLT_HIUpcMu;   //!
   TBranch        *b_HLT_HIUpcMu_Prescl;   //!
   TBranch        *b_HLT_HIUpcMu_Core;   //!
   TBranch        *b_HLT_HIUpcMu_Core_Prescl;   //!
   TBranch        *b_HLT_HIPhoton15;   //!
   TBranch        *b_HLT_HIPhoton15_Prescl;   //!
   TBranch        *b_HLT_HIPhoton15_Core;   //!
   TBranch        *b_HLT_HIPhoton15_Core_Prescl;   //!
   TBranch        *b_HLT_HIPhoton20;   //!
   TBranch        *b_HLT_HIPhoton20_Prescl;   //!
   TBranch        *b_HLT_HIPhoton20_Core;   //!
   TBranch        *b_HLT_HIPhoton20_Core_Prescl;   //!
   TBranch        *b_HLT_HIPhoton30;   //!
   TBranch        *b_HLT_HIPhoton30_Prescl;   //!
   TBranch        *b_HLT_HIPhoton30_Core;   //!
   TBranch        *b_HLT_HIPhoton30_Core_Prescl;   //!
   TBranch        *b_HLT_HIDoublePhoton5_CEP_L1R;   //!
   TBranch        *b_HLT_HIDoublePhoton5_CEP_L1R_Prescl;   //!
   TBranch        *b_HLT_HIJet35U;   //!
   TBranch        *b_HLT_HIJet35U_Prescl;   //!
   TBranch        *b_HLT_HIJet35U_Core;   //!
   TBranch        *b_HLT_HIJet35U_Core_Prescl;   //!
   TBranch        *b_HLT_HIJet50U;   //!
   TBranch        *b_HLT_HIJet50U_Prescl;   //!
   TBranch        *b_HLT_HIJet50U_Core;   //!
   TBranch        *b_HLT_HIJet50U_Core_Prescl;   //!
   TBranch        *b_HLT_HIJet75U;   //!
   TBranch        *b_HLT_HIJet75U_Prescl;   //!
   TBranch        *b_HLT_HIJet75U_Core;   //!
   TBranch        *b_HLT_HIJet75U_Core_Prescl;   //!
   TBranch        *b_HLT_HIJet90U;   //!
   TBranch        *b_HLT_HIJet90U_Prescl;   //!
   TBranch        *b_HLT_HIJet90U_Core;   //!
   TBranch        *b_HLT_HIJet90U_Core_Prescl;   //!
   TBranch        *b_HLT_HIStoppedHSCP35;   //!
   TBranch        *b_HLT_HIStoppedHSCP35_Prescl;   //!
   TBranch        *b_HLT_HIClusterVertexCompatibility;   //!
   TBranch        *b_HLT_HIClusterVertexCompatibility_Prescl;   //!
   TBranch        *b_HLT_HICentralityVeto;   //!
   TBranch        *b_HLT_HICentralityVeto_Prescl;   //!
   TBranch        *b_HLT_HIRandom;   //!
   TBranch        *b_HLT_HIRandom_Prescl;   //!
   TBranch        *b_HLT_HcalCalibration_HI;   //!
   TBranch        *b_HLT_HcalCalibration_HI_Prescl;   //!
   TBranch        *b_HLTriggerFinalPath;   //!
   TBranch        *b_HLTriggerFinalPath_Prescl;   //!
   TBranch        *b_L1_BptxMinus;   //!
   TBranch        *b_L1_BptxMinus_Prescl;   //!
   TBranch        *b_L1_BptxMinus_5bx;   //!
   TBranch        *b_L1_BptxMinus_NotBptxPlus;   //!
   TBranch        *b_L1_BptxMinus_NotBptxPlus_Prescl;   //!
   TBranch        *b_L1_BptxMinus_NotBptxPlus_5bx;   //!
   TBranch        *b_L1_BptxPlus;   //!
   TBranch        *b_L1_BptxPlus_Prescl;   //!
   TBranch        *b_L1_BptxPlus_5bx;   //!
   TBranch        *b_L1_BptxPlusANDMinus;   //!
   TBranch        *b_L1_BptxPlusANDMinus_Prescl;   //!
   TBranch        *b_L1_BptxPlusANDMinus_5bx;   //!
   TBranch        *b_L1_BptxPlusORMinus;   //!
   TBranch        *b_L1_BptxPlusORMinus_Prescl;   //!
   TBranch        *b_L1_BptxPlusORMinus_5bx;   //!
   TBranch        *b_L1_BptxPlusORMinus_instance1;   //!
   TBranch        *b_L1_BptxPlusORMinus_instance1_Prescl;   //!
   TBranch        *b_L1_BptxPlusORMinus_instance1_5bx;   //!
   TBranch        *b_L1_BptxPlus_NotBptxMinus;   //!
   TBranch        *b_L1_BptxPlus_NotBptxMinus_Prescl;   //!
   TBranch        *b_L1_BptxPlus_NotBptxMinus_5bx;   //!
   TBranch        *b_L1_BptxXOR;   //!
   TBranch        *b_L1_BptxXOR_Prescl;   //!
   TBranch        *b_L1_BptxXOR_5bx;   //!
   TBranch        *b_L1_BptxXOR_BscMinBiasOR;   //!
   TBranch        *b_L1_BptxXOR_BscMinBiasOR_Prescl;   //!
   TBranch        *b_L1_BptxXOR_BscMinBiasOR_5bx;   //!
   TBranch        *b_L1_Bsc2Minus_BptxMinus;   //!
   TBranch        *b_L1_Bsc2Minus_BptxMinus_Prescl;   //!
   TBranch        *b_L1_Bsc2Minus_BptxMinus_5bx;   //!
   TBranch        *b_L1_Bsc2Plus_BptxPlus;   //!
   TBranch        *b_L1_Bsc2Plus_BptxPlus_Prescl;   //!
   TBranch        *b_L1_Bsc2Plus_BptxPlus_5bx;   //!
   TBranch        *b_L1_BscMinBiasInnerThreshold1;   //!
   TBranch        *b_L1_BscMinBiasInnerThreshold1_Prescl;   //!
   TBranch        *b_L1_BscMinBiasInnerThreshold1_5bx;   //!
   TBranch        *b_L1_BscMinBiasInnerThreshold1_BptxAND;   //!
   TBranch        *b_L1_BscMinBiasInnerThreshold1_BptxAND_Prescl;   //!
   TBranch        *b_L1_BscMinBiasInnerThreshold1_BptxAND_5bx;   //!
   TBranch        *b_L1_BscMinBiasInnerThreshold2_BptxAND;   //!
   TBranch        *b_L1_BscMinBiasInnerThreshold2_BptxAND_Prescl;   //!
   TBranch        *b_L1_BscMinBiasInnerThreshold2_BptxAND_5bx;   //!
   TBranch        *b_L1_BscMinBiasOR_BptxAND;   //!
   TBranch        *b_L1_BscMinBiasOR_BptxAND_Prescl;   //!
   TBranch        *b_L1_BscMinBiasOR_BptxAND_5bx;   //!
   TBranch        *b_L1_BscMinBiasOR_BptxPlusORMinus;   //!
   TBranch        *b_L1_BscMinBiasOR_BptxPlusORMinus_Prescl;   //!
   TBranch        *b_L1_BscMinBiasOR_BptxPlusORMinus_5bx;   //!
   TBranch        *b_L1_BscMinBiasThreshold1;   //!
   TBranch        *b_L1_BscMinBiasThreshold1_Prescl;   //!
   TBranch        *b_L1_BscMinBiasThreshold1_5bx;   //!
   TBranch        *b_L1_BscMinBiasThreshold1_BptxAND;   //!
   TBranch        *b_L1_BscMinBiasThreshold1_BptxAND_Prescl;   //!
   TBranch        *b_L1_BscMinBiasThreshold1_BptxAND_5bx;   //!
   TBranch        *b_L1_BscMinBiasThreshold2_BptxAND;   //!
   TBranch        *b_L1_BscMinBiasThreshold2_BptxAND_Prescl;   //!
   TBranch        *b_L1_BscMinBiasThreshold2_BptxAND_5bx;   //!
   TBranch        *b_L1_DoubleEG2;   //!
   TBranch        *b_L1_DoubleEG2_Prescl;   //!
   TBranch        *b_L1_DoubleEG2_5bx;   //!
   TBranch        *b_L1_DoubleEG5;   //!
   TBranch        *b_L1_DoubleEG5_Prescl;   //!
   TBranch        *b_L1_DoubleEG5_5bx;   //!
   TBranch        *b_L1_DoubleEG5_BptxAND;   //!
   TBranch        *b_L1_DoubleEG5_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleEG5_BptxAND_5bx;   //!
   TBranch        *b_L1_DoubleForJet10_EtaOpp;   //!
   TBranch        *b_L1_DoubleForJet10_EtaOpp_Prescl;   //!
   TBranch        *b_L1_DoubleForJet10_EtaOpp_5bx;   //!
   TBranch        *b_L1_DoubleHfBitCountsRing1_P1N1;   //!
   TBranch        *b_L1_DoubleHfBitCountsRing1_P1N1_Prescl;   //!
   TBranch        *b_L1_DoubleHfBitCountsRing1_P1N1_5bx;   //!
   TBranch        *b_L1_DoubleHfBitCountsRing2_P1N1;   //!
   TBranch        *b_L1_DoubleHfBitCountsRing2_P1N1_Prescl;   //!
   TBranch        *b_L1_DoubleHfBitCountsRing2_P1N1_5bx;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing1_P200N200;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing1_P200N200_Prescl;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing1_P200N200_5bx;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing1_P4N4;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing1_P4N4_Prescl;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing1_P4N4_5bx;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing2_P200N200;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing2_P200N200_Prescl;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing2_P200N200_5bx;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing2_P4N4;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing2_P4N4_Prescl;   //!
   TBranch        *b_L1_DoubleHfRingEtSumsRing2_P4N4_5bx;   //!
   TBranch        *b_L1_DoubleJet30;   //!
   TBranch        *b_L1_DoubleJet30_Prescl;   //!
   TBranch        *b_L1_DoubleJet30_5bx;   //!
   TBranch        *b_L1_DoubleMu3;   //!
   TBranch        *b_L1_DoubleMu3_Prescl;   //!
   TBranch        *b_L1_DoubleMu3_5bx;   //!
   TBranch        *b_L1_DoubleMuOpen;   //!
   TBranch        *b_L1_DoubleMuOpen_Prescl;   //!
   TBranch        *b_L1_DoubleMuOpen_5bx;   //!
   TBranch        *b_L1_DoubleMuOpen_BptxAND;   //!
   TBranch        *b_L1_DoubleMuOpen_BptxAND_Prescl;   //!
   TBranch        *b_L1_DoubleMuOpen_BptxAND_5bx;   //!
   TBranch        *b_L1_ETM12;   //!
   TBranch        *b_L1_ETM12_Prescl;   //!
   TBranch        *b_L1_ETM12_5bx;   //!
   TBranch        *b_L1_ETM20;   //!
   TBranch        *b_L1_ETM20_Prescl;   //!
   TBranch        *b_L1_ETM20_5bx;   //!
   TBranch        *b_L1_ETM30;   //!
   TBranch        *b_L1_ETM30_Prescl;   //!
   TBranch        *b_L1_ETM30_5bx;   //!
   TBranch        *b_L1_ETM70;   //!
   TBranch        *b_L1_ETM70_Prescl;   //!
   TBranch        *b_L1_ETM70_5bx;   //!
   TBranch        *b_L1_ETT100;   //!
   TBranch        *b_L1_ETT100_Prescl;   //!
   TBranch        *b_L1_ETT100_5bx;   //!
   TBranch        *b_L1_ETT140;   //!
   TBranch        *b_L1_ETT140_Prescl;   //!
   TBranch        *b_L1_ETT140_5bx;   //!
   TBranch        *b_L1_ETT30;   //!
   TBranch        *b_L1_ETT30_Prescl;   //!
   TBranch        *b_L1_ETT30_5bx;   //!
   TBranch        *b_L1_ETT30_BptxAND;   //!
   TBranch        *b_L1_ETT30_BptxAND_Prescl;   //!
   TBranch        *b_L1_ETT30_BptxAND_5bx;   //!
   TBranch        *b_L1_ETT60;   //!
   TBranch        *b_L1_ETT60_Prescl;   //!
   TBranch        *b_L1_ETT60_5bx;   //!
   TBranch        *b_L1_ETT60_BptxAND;   //!
   TBranch        *b_L1_ETT60_BptxAND_Prescl;   //!
   TBranch        *b_L1_ETT60_BptxAND_5bx;   //!
   TBranch        *b_L1_HTM30;   //!
   TBranch        *b_L1_HTM30_Prescl;   //!
   TBranch        *b_L1_HTM30_5bx;   //!
   TBranch        *b_L1_HTT100;   //!
   TBranch        *b_L1_HTT100_Prescl;   //!
   TBranch        *b_L1_HTT100_5bx;   //!
   TBranch        *b_L1_HTT200;   //!
   TBranch        *b_L1_HTT200_Prescl;   //!
   TBranch        *b_L1_HTT200_5bx;   //!
   TBranch        *b_L1_HTT50;   //!
   TBranch        *b_L1_HTT50_Prescl;   //!
   TBranch        *b_L1_HTT50_5bx;   //!
   TBranch        *b_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND;   //!
   TBranch        *b_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl;   //!
   TBranch        *b_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_5bx;   //!
   TBranch        *b_L1_HcalHfCoincidencePm;   //!
   TBranch        *b_L1_HcalHfCoincidencePm_Prescl;   //!
   TBranch        *b_L1_HcalHfCoincidencePm_5bx;   //!
   TBranch        *b_L1_HcalHfCoincidencePm_BptxAND;   //!
   TBranch        *b_L1_HcalHfCoincidencePm_BptxAND_Prescl;   //!
   TBranch        *b_L1_HcalHfCoincidencePm_BptxAND_5bx;   //!
   TBranch        *b_L1_HcalHfMmOrPpOrPm;   //!
   TBranch        *b_L1_HcalHfMmOrPpOrPm_Prescl;   //!
   TBranch        *b_L1_HcalHfMmOrPpOrPm_5bx;   //!
   TBranch        *b_L1_HcalHfMmOrPpOrPm_BptxAND;   //!
   TBranch        *b_L1_HcalHfMmOrPpOrPm_BptxAND_Prescl;   //!
   TBranch        *b_L1_HcalHfMmOrPpOrPm_BptxAND_5bx;   //!
   TBranch        *b_L1_HcalHfMmpOrMpp;   //!
   TBranch        *b_L1_HcalHfMmpOrMpp_Prescl;   //!
   TBranch        *b_L1_HcalHfMmpOrMpp_5bx;   //!
   TBranch        *b_L1_HcalHfMmpOrMpp_BptxAND;   //!
   TBranch        *b_L1_HcalHfMmpOrMpp_BptxAND_Prescl;   //!
   TBranch        *b_L1_HcalHfMmpOrMpp_BptxAND_5bx;   //!
   TBranch        *b_L1_HcalHoTotalOR;   //!
   TBranch        *b_L1_HcalHoTotalOR_Prescl;   //!
   TBranch        *b_L1_HcalHoTotalOR_5bx;   //!
   TBranch        *b_L1_Mu3_EG5;   //!
   TBranch        *b_L1_Mu3_EG5_Prescl;   //!
   TBranch        *b_L1_Mu3_EG5_5bx;   //!
   TBranch        *b_L1_Mu3_Jet10;   //!
   TBranch        *b_L1_Mu3_Jet10_Prescl;   //!
   TBranch        *b_L1_Mu3_Jet10_5bx;   //!
   TBranch        *b_L1_Mu3_Jet6;   //!
   TBranch        *b_L1_Mu3_Jet6_Prescl;   //!
   TBranch        *b_L1_Mu3_Jet6_5bx;   //!
   TBranch        *b_L1_Mu5_Jet6;   //!
   TBranch        *b_L1_Mu5_Jet6_Prescl;   //!
   TBranch        *b_L1_Mu5_Jet6_5bx;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_5bx;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_5bx;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasOR;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasOR_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasOR_5bx;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasThreshold1;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasThreshold1_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasThreshold1_5bx;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasThreshold2;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasThreshold2_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_BscMinBiasThreshold2_5bx;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_5bx;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfCoincidencePm;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfCoincidencePm_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfCoincidencePm_5bx;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_5bx;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfMmpOrMpp;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_5bx;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasInnerThreshold1;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasInnerThreshold1_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasInnerThreshold1_5bx;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasInnerThreshold2;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasInnerThreshold2_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasInnerThreshold2_5bx;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasOR;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasOR_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasOR_5bx;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasThreshold1;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasThreshold1_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasThreshold1_5bx;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasThreshold2;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasThreshold2_Prescl;   //!
   TBranch        *b_L1_NotBsc2_BscMinBiasThreshold2_5bx;   //!
   TBranch        *b_L1_NotBsc2_HcalHfCoincidencePm;   //!
   TBranch        *b_L1_NotBsc2_HcalHfCoincidencePm_Prescl;   //!
   TBranch        *b_L1_NotBsc2_HcalHfCoincidencePm_5bx;   //!
   TBranch        *b_L1_NotBsc2_HcalHfMmOrPpOrPm;   //!
   TBranch        *b_L1_NotBsc2_HcalHfMmOrPpOrPm_Prescl;   //!
   TBranch        *b_L1_NotBsc2_HcalHfMmOrPpOrPm_5bx;   //!
   TBranch        *b_L1_NotBsc2_HcalHfMmpOrMpp;   //!
   TBranch        *b_L1_NotBsc2_HcalHfMmpOrMpp_Prescl;   //!
   TBranch        *b_L1_NotBsc2_HcalHfMmpOrMpp_5bx;   //!
   TBranch        *b_L1_QuadJet6;   //!
   TBranch        *b_L1_QuadJet6_Prescl;   //!
   TBranch        *b_L1_QuadJet6_5bx;   //!
   TBranch        *b_L1_QuadJet8;   //!
   TBranch        *b_L1_QuadJet8_Prescl;   //!
   TBranch        *b_L1_QuadJet8_5bx;   //!
   TBranch        *b_L1_SingleEG10;   //!
   TBranch        *b_L1_SingleEG10_Prescl;   //!
   TBranch        *b_L1_SingleEG10_5bx;   //!
   TBranch        *b_L1_SingleEG12;   //!
   TBranch        *b_L1_SingleEG12_Prescl;   //!
   TBranch        *b_L1_SingleEG12_5bx;   //!
   TBranch        *b_L1_SingleEG15;   //!
   TBranch        *b_L1_SingleEG15_Prescl;   //!
   TBranch        *b_L1_SingleEG15_5bx;   //!
   TBranch        *b_L1_SingleEG2;   //!
   TBranch        *b_L1_SingleEG2_Prescl;   //!
   TBranch        *b_L1_SingleEG2_5bx;   //!
   TBranch        *b_L1_SingleEG20;   //!
   TBranch        *b_L1_SingleEG20_Prescl;   //!
   TBranch        *b_L1_SingleEG20_5bx;   //!
   TBranch        *b_L1_SingleEG2_BptxAND;   //!
   TBranch        *b_L1_SingleEG2_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG2_BptxAND_5bx;   //!
   TBranch        *b_L1_SingleEG5;   //!
   TBranch        *b_L1_SingleEG5_Prescl;   //!
   TBranch        *b_L1_SingleEG5_5bx;   //!
   TBranch        *b_L1_SingleEG5_BptxAND;   //!
   TBranch        *b_L1_SingleEG5_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleEG5_BptxAND_5bx;   //!
   TBranch        *b_L1_SingleEG8;   //!
   TBranch        *b_L1_SingleEG8_Prescl;   //!
   TBranch        *b_L1_SingleEG8_5bx;   //!
   TBranch        *b_L1_SingleForJet2;   //!
   TBranch        *b_L1_SingleForJet2_Prescl;   //!
   TBranch        *b_L1_SingleForJet2_5bx;   //!
   TBranch        *b_L1_SingleForJet4;   //!
   TBranch        *b_L1_SingleForJet4_Prescl;   //!
   TBranch        *b_L1_SingleForJet4_5bx;   //!
   TBranch        *b_L1_SingleJet10;   //!
   TBranch        *b_L1_SingleJet10_Prescl;   //!
   TBranch        *b_L1_SingleJet10_5bx;   //!
   TBranch        *b_L1_SingleJet20;   //!
   TBranch        *b_L1_SingleJet20_Prescl;   //!
   TBranch        *b_L1_SingleJet20_5bx;   //!
   TBranch        *b_L1_SingleJet20_BptxAND;   //!
   TBranch        *b_L1_SingleJet20_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleJet20_BptxAND_5bx;   //!
   TBranch        *b_L1_SingleJet20_NotBptxOR_Ext;   //!
   TBranch        *b_L1_SingleJet20_NotBptxOR_Ext_Prescl;   //!
   TBranch        *b_L1_SingleJet20_NotBptxOR_Ext_5bx;   //!
   TBranch        *b_L1_SingleJet30;   //!
   TBranch        *b_L1_SingleJet30_Prescl;   //!
   TBranch        *b_L1_SingleJet30_5bx;   //!
   TBranch        *b_L1_SingleJet30_BptxAND;   //!
   TBranch        *b_L1_SingleJet30_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleJet30_BptxAND_5bx;   //!
   TBranch        *b_L1_SingleJet40;   //!
   TBranch        *b_L1_SingleJet40_Prescl;   //!
   TBranch        *b_L1_SingleJet40_5bx;   //!
   TBranch        *b_L1_SingleJet40_BptxAND;   //!
   TBranch        *b_L1_SingleJet40_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleJet40_BptxAND_5bx;   //!
   TBranch        *b_L1_SingleJet50;   //!
   TBranch        *b_L1_SingleJet50_Prescl;   //!
   TBranch        *b_L1_SingleJet50_5bx;   //!
   TBranch        *b_L1_SingleJet50_BptxAND;   //!
   TBranch        *b_L1_SingleJet50_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleJet50_BptxAND_5bx;   //!
   TBranch        *b_L1_SingleJet6;   //!
   TBranch        *b_L1_SingleJet6_Prescl;   //!
   TBranch        *b_L1_SingleJet6_5bx;   //!
   TBranch        *b_L1_SingleJet60;   //!
   TBranch        *b_L1_SingleJet60_Prescl;   //!
   TBranch        *b_L1_SingleJet60_5bx;   //!
   TBranch        *b_L1_SingleMu0;   //!
   TBranch        *b_L1_SingleMu0_Prescl;   //!
   TBranch        *b_L1_SingleMu0_5bx;   //!
   TBranch        *b_L1_SingleMu10;   //!
   TBranch        *b_L1_SingleMu10_Prescl;   //!
   TBranch        *b_L1_SingleMu10_5bx;   //!
   TBranch        *b_L1_SingleMu14;   //!
   TBranch        *b_L1_SingleMu14_Prescl;   //!
   TBranch        *b_L1_SingleMu14_5bx;   //!
   TBranch        *b_L1_SingleMu20;   //!
   TBranch        *b_L1_SingleMu20_Prescl;   //!
   TBranch        *b_L1_SingleMu20_5bx;   //!
   TBranch        *b_L1_SingleMu3;   //!
   TBranch        *b_L1_SingleMu3_Prescl;   //!
   TBranch        *b_L1_SingleMu3_5bx;   //!
   TBranch        *b_L1_SingleMu3_BptxAND;   //!
   TBranch        *b_L1_SingleMu3_BptxAND_Prescl;   //!
   TBranch        *b_L1_SingleMu3_BptxAND_5bx;   //!
   TBranch        *b_L1_SingleMu5;   //!
   TBranch        *b_L1_SingleMu5_Prescl;   //!
   TBranch        *b_L1_SingleMu5_5bx;   //!
   TBranch        *b_L1_SingleMu7;   //!
   TBranch        *b_L1_SingleMu7_Prescl;   //!
   TBranch        *b_L1_SingleMu7_5bx;   //!
   TBranch        *b_L1_SingleMuBeamHalo;   //!
   TBranch        *b_L1_SingleMuBeamHalo_Prescl;   //!
   TBranch        *b_L1_SingleMuBeamHalo_5bx;   //!
   TBranch        *b_L1_SingleMuOpen;   //!
   TBranch        *b_L1_SingleMuOpen_Prescl;   //!
   TBranch        *b_L1_SingleMuOpen_5bx;   //!
   TBranch        *b_L1_SingleTauJet50;   //!
   TBranch        *b_L1_SingleTauJet50_Prescl;   //!
   TBranch        *b_L1_SingleTauJet50_5bx;   //!
   TBranch        *b_L1_TripleJet14;   //!
   TBranch        *b_L1_TripleJet14_Prescl;   //!
   TBranch        *b_L1_TripleJet14_5bx;   //!
   TBranch        *b_L1_ZdcCaloMinus;   //!
   TBranch        *b_L1_ZdcCaloMinus_Prescl;   //!
   TBranch        *b_L1_ZdcCaloMinus_5bx;   //!
   TBranch        *b_L1_ZdcCaloMinus_BptxAND;   //!
   TBranch        *b_L1_ZdcCaloMinus_BptxAND_Prescl;   //!
   TBranch        *b_L1_ZdcCaloMinus_BptxAND_5bx;   //!
   TBranch        *b_L1_ZdcCaloPlus;   //!
   TBranch        *b_L1_ZdcCaloPlus_Prescl;   //!
   TBranch        *b_L1_ZdcCaloPlus_5bx;   //!
   TBranch        *b_L1_ZdcCaloPlus_BptxAND;   //!
   TBranch        *b_L1_ZdcCaloPlus_BptxAND_Prescl;   //!
   TBranch        *b_L1_ZdcCaloPlus_BptxAND_5bx;   //!
   TBranch        *b_L1_ZdcCaloPlus_ZdcCaloMinus;   //!
   TBranch        *b_L1_ZdcCaloPlus_ZdcCaloMinus_Prescl;   //!
   TBranch        *b_L1_ZdcCaloPlus_ZdcCaloMinus_5bx;   //!
   TBranch        *b_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND;   //!
   TBranch        *b_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_Prescl;   //!
   TBranch        *b_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_5bx;   //!
   TBranch        *b_L1_ZdcScintLooseVertex;   //!
   TBranch        *b_L1_ZdcScintLooseVertex_Prescl;   //!
   TBranch        *b_L1_ZdcScintLooseVertex_5bx;   //!
   TBranch        *b_L1_ZdcScintLooseVertex_BptxAND;   //!
   TBranch        *b_L1_ZdcScintLooseVertex_BptxAND_Prescl;   //!
   TBranch        *b_L1_ZdcScintLooseVertex_BptxAND_5bx;   //!
   TBranch        *b_L1_ZdcScintMinus;   //!
   TBranch        *b_L1_ZdcScintMinus_Prescl;   //!
   TBranch        *b_L1_ZdcScintMinus_5bx;   //!
   TBranch        *b_L1_ZdcScintPlus;   //!
   TBranch        *b_L1_ZdcScintPlus_Prescl;   //!
   TBranch        *b_L1_ZdcScintPlus_5bx;   //!
   TBranch        *b_L1_ZdcScintTightVertex;   //!
   TBranch        *b_L1_ZdcScintTightVertex_Prescl;   //!
   TBranch        *b_L1_ZdcScintTightVertex_5bx;   //!
   TBranch        *b_L1_ZdcScintTightVertex_BptxAND;   //!
   TBranch        *b_L1_ZdcScintTightVertex_BptxAND_Prescl;   //!
   TBranch        *b_L1_ZdcScintTightVertex_BptxAND_5bx;   //!
   TBranch        *b_L1_ZeroBias_Ext;   //!
   TBranch        *b_L1_ZeroBias_Ext_Prescl;   //!
   TBranch        *b_L1_ZeroBias_Ext_5bx;   //!
   TBranch        *b_L1Tech_BPTX_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_minus_v0_5bx;   //!
   TBranch        *b_L1Tech_BPTX_minus_AND_not_plus_v0;   //!
   TBranch        *b_L1Tech_BPTX_minus_AND_not_plus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_minus_AND_not_plus_v0_5bx;   //!
   TBranch        *b_L1Tech_BPTX_plus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_v0_5bx;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_NOT_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_NOT_minus_v0_5bx;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_v0_5bx;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_instance1_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_instance1_v0_5bx;   //!
   TBranch        *b_L1Tech_BPTX_plus_OR_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_OR_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_OR_minus_v0_5bx;   //!
   TBranch        *b_L1Tech_BPTX_quiet_v0;   //!
   TBranch        *b_L1Tech_BPTX_quiet_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_quiet_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_HighMultiplicity_v0;   //!
   TBranch        *b_L1Tech_BSC_HighMultiplicity_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_HighMultiplicity_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_halo_beam1_inner_v0;   //!
   TBranch        *b_L1Tech_BSC_halo_beam1_inner_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_halo_beam1_inner_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_halo_beam1_outer_v0;   //!
   TBranch        *b_L1Tech_BSC_halo_beam1_outer_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_halo_beam1_outer_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_halo_beam2_inner_v0;   //!
   TBranch        *b_L1Tech_BSC_halo_beam2_inner_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_halo_beam2_inner_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_halo_beam2_outer_v0;   //!
   TBranch        *b_L1Tech_BSC_halo_beam2_outer_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_halo_beam2_outer_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_minBias_OR_v0;   //!
   TBranch        *b_L1Tech_BSC_minBias_OR_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_minBias_OR_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_minBias_inner_threshold1_v0;   //!
   TBranch        *b_L1Tech_BSC_minBias_inner_threshold1_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_minBias_inner_threshold1_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_minBias_inner_threshold2_v0;   //!
   TBranch        *b_L1Tech_BSC_minBias_inner_threshold2_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_minBias_inner_threshold2_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_minBias_threshold1_v0;   //!
   TBranch        *b_L1Tech_BSC_minBias_threshold1_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_minBias_threshold1_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_minBias_threshold2_v0;   //!
   TBranch        *b_L1Tech_BSC_minBias_threshold2_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_minBias_threshold2_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_splash_beam1_v0;   //!
   TBranch        *b_L1Tech_BSC_splash_beam1_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_splash_beam1_v0_5bx;   //!
   TBranch        *b_L1Tech_BSC_splash_beam2_v0;   //!
   TBranch        *b_L1Tech_BSC_splash_beam2_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_splash_beam2_v0_5bx;   //!
   TBranch        *b_L1Tech_CASTOR_HaloMuon_v0;   //!
   TBranch        *b_L1Tech_CASTOR_HaloMuon_v0_Prescl;   //!
   TBranch        *b_L1Tech_CASTOR_HaloMuon_v0_5bx;   //!
   TBranch        *b_L1Tech_HCAL_HBHE_totalOR_v0;   //!
   TBranch        *b_L1Tech_HCAL_HBHE_totalOR_v0_Prescl;   //!
   TBranch        *b_L1Tech_HCAL_HBHE_totalOR_v0_5bx;   //!
   TBranch        *b_L1Tech_RPC_TTU_RB0_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RB0_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RB0_Cosmics_v0_5bx;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0_5bx;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0_5bx;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0_5bx;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0_5bx;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBst1_collisions_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBst1_collisions_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBst1_collisions_v0_5bx;   //!
   TBranch        *b_L1Tech_RPC_TTU_barrel_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_barrel_Cosmics_v0_5bx;   //!
   TBranch        *b_L1Tech_RPC_TTU_pointing_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_pointing_Cosmics_v0_5bx;   //!
   TBranch        *b_L1Tech_ZDC_Scint_loose_vertex_v0;   //!
   TBranch        *b_L1Tech_ZDC_Scint_loose_vertex_v0_Prescl;   //!
   TBranch        *b_L1Tech_ZDC_Scint_loose_vertex_v0_5bx;   //!
   TBranch        *b_L1Tech_ZDC_Scint_minus_v0;   //!
   TBranch        *b_L1Tech_ZDC_Scint_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_ZDC_Scint_minus_v0_5bx;   //!
   TBranch        *b_L1Tech_ZDC_Scint_plus_v0;   //!
   TBranch        *b_L1Tech_ZDC_Scint_plus_v0_Prescl;   //!
   TBranch        *b_L1Tech_ZDC_Scint_plus_v0_5bx;   //!
   TBranch        *b_L1Tech_ZDC_Scint_tight_vertex_v0;   //!
   TBranch        *b_L1Tech_ZDC_Scint_tight_vertex_v0_Prescl;   //!
   TBranch        *b_L1Tech_ZDC_Scint_tight_vertex_v0_5bx;   //!
  
};

void setupHltTree(TTree *t, Hlts &hlts)
{
  t->SetBranchAddress("Npart", &hlts.Npart, &hlts.b_Npart);
  t->SetBranchAddress("Ncoll", &hlts.Ncoll, &hlts.b_Ncoll);
  t->SetBranchAddress("Nhard", &hlts.Nhard, &hlts.b_Nhard);
  t->SetBranchAddress("phi0", &hlts.phi0, &hlts.b_NPhi0);
  t->SetBranchAddress("b", &hlts.b, &hlts.b_b);
  t->SetBranchAddress("Ncharged", &hlts.Ncharged, &hlts.b_Ncharged);
  t->SetBranchAddress("NchargedMR", &hlts.NchargedMR, &hlts.b_NchargedMR);
  t->SetBranchAddress("MeanPt", &hlts.MeanPt, &hlts.b_MeanPt);
  t->SetBranchAddress("MeanPtMR", &hlts.MeanPtMR, &hlts.b_MeanPtMR);
  t->SetBranchAddress("EtMR", &hlts.EtMR, &hlts.b_EtMR);
  t->SetBranchAddress("NchargedPtCut", &hlts.NchargedPtCut, &hlts.b_NchargedPtCut);
  t->SetBranchAddress("NchargedPtCutMR", &hlts.NchargedPtCutMR, &hlts.b_NchargedPtCutMR);
  t->SetBranchAddress("hiBin", &hlts.hiBin, &hlts.b_hiBin);
  t->SetBranchAddress("hiHF", &hlts.hiHF, &hlts.b_hiHF);
  t->SetBranchAddress("hiHFplus", &hlts.hiHFplus, &hlts.b_hiHFplus);
  t->SetBranchAddress("hiHFminus", &hlts.hiHFminus, &hlts.b_hiHFminus);
  t->SetBranchAddress("hiZDC", &hlts.hiZDC, &hlts.b_hiZDC);
  t->SetBranchAddress("hiZDCplus", &hlts.hiZDCplus, &hlts.b_hiZDCplus);
  t->SetBranchAddress("hiZDCminus", &hlts.hiZDCminus, &hlts.b_hiZDCminus);
  t->SetBranchAddress("hiHFhit", &hlts.hiHFhit, &hlts.b_hiHFhit);
  t->SetBranchAddress("hiHFhitPlus", &hlts.hiHFhitPlus, &hlts.b_hiHFhitPlus);
  t->SetBranchAddress("hiHFhitMinus", &hlts.hiHFhitMinus, &hlts.b_hiHFhitMinus);
  t->SetBranchAddress("hiET", &hlts.hiET, &hlts.b_hiET);
  t->SetBranchAddress("hiEE", &hlts.hiEE, &hlts.b_hiEE);
  t->SetBranchAddress("hiEB", &hlts.hiEB, &hlts.b_hiEB);
  t->SetBranchAddress("hiEEplus", &hlts.hiEEplus, &hlts.b_hiEEplus);
  t->SetBranchAddress("hiEEminus", &hlts.hiEEminus, &hlts.b_hiEEminus);
  t->SetBranchAddress("hiNpix", &hlts.hiNpix, &hlts.b_hiNpix);
  t->SetBranchAddress("hiNpixelTracks", &hlts.hiNpixelTracks, &hlts.b_hiNpixelTracks);
  t->SetBranchAddress("hiNtracks", &hlts.hiNtracks, &hlts.b_hiNtracks);
  t->SetBranchAddress("hiNevtPlane", &hlts.hiNevtPlane, &hlts.b_hiNevtPlane);
  t->SetBranchAddress("hiEvtPlanes", &hlts.hiEvtPlanes, &hlts.b_hiEvtPlanes);
  t->SetBranchAddress("hiNtracksPtCut", &hlts.hiNtracksPtCut, &hlts.b_hiNtracksPtCut);
  t->SetBranchAddress("hiNtracksEtaCut", &hlts.hiNtracksEtaCut, &hlts.b_hiNtracksEtaCut);
  t->SetBranchAddress("hiNtracksEtaPtCut", &hlts.hiNtracksEtaPtCut, &hlts.b_hiNtracksEtaPtCut);
  t->SetBranchAddress("L1HfRing1EtSumPositiveEta", &hlts.L1HfRing1EtSumPositiveEta, &hlts.b_L1HfRing1EtSumPositiveEta);
  t->SetBranchAddress("L1HfRing2EtSumPositiveEta", &hlts.L1HfRing2EtSumPositiveEta, &hlts.b_L1HfRing2EtSumPositiveEta);
  t->SetBranchAddress("L1HfRing1EtSumNegativeEta", &hlts.L1HfRing1EtSumNegativeEta, &hlts.b_L1HfRing1EtSumNegativeEta);
  t->SetBranchAddress("L1HfRing2EtSumNegativeEta", &hlts.L1HfRing2EtSumNegativeEta, &hlts.b_L1HfRing2EtSumNegativeEta);
  t->SetBranchAddress("L1HfTowerCountPositiveEtaRing1", &hlts.L1HfTowerCountPositiveEtaRing1, &hlts.b_L1HfTowerCountPositiveEtaRing1);
  t->SetBranchAddress("L1HfTowerCountNegativeEtaRing1", &hlts.L1HfTowerCountNegativeEtaRing1, &hlts.b_L1HfTowerCountNegativeEtaRing1);
  t->SetBranchAddress("L1HfTowerCountPositiveEtaRing2", &hlts.L1HfTowerCountPositiveEtaRing2, &hlts.b_L1HfTowerCountPositiveEtaRing2);
  t->SetBranchAddress("L1HfTowerCountNegativeEtaRing2", &hlts.L1HfTowerCountNegativeEtaRing2, &hlts.b_L1HfTowerCountNegativeEtaRing2);
  t->SetBranchAddress("recoNVrt", &hlts.recoNVrt, &hlts.b_NVrtx);
  t->SetBranchAddress("recoVrtX", hlts.recoVrtX, &hlts.b_recoVrtX);
  t->SetBranchAddress("recoVrtY", hlts.recoVrtY, &hlts.b_recoVrtY);
  t->SetBranchAddress("recoVrtZ", hlts.recoVrtZ, &hlts.b_recoVrtZ);
  t->SetBranchAddress("recoVrtNtrk", hlts.recoVrtNtrk, &hlts.b_recoVrtNtrk);
  t->SetBranchAddress("recoVrtChi2", hlts.recoVrtChi2, &hlts.b_recoVrtChi2);
  t->SetBranchAddress("recoVrtNdof", hlts.recoVrtNdof, &hlts.b_recoVrtNdof);
  t->SetBranchAddress("Run", &hlts.Run, &hlts.b_Run);
  t->SetBranchAddress("Event", &hlts.Event, &hlts.b_Event);
  t->SetBranchAddress("LumiBlock", &hlts.LumiBlock, &hlts.b_LumiBlock);
  t->SetBranchAddress("Bx", &hlts.Bx, &hlts.b_Bx);
  t->SetBranchAddress("Orbit", &hlts.Orbit, &hlts.b_Orbit);
  t->SetBranchAddress("AvgInstLumi", &hlts.AvgInstLumi, &hlts.b_AvgInstLumi);
  t->SetBranchAddress("HLT_LogMonitor", &hlts.HLT_LogMonitor, &hlts.b_HLT_LogMonitor);
  t->SetBranchAddress("HLT_LogMonitor_Prescl", &hlts.HLT_LogMonitor_Prescl, &hlts.b_HLT_LogMonitor_Prescl);
  t->SetBranchAddress("HLT_EcalCalibration", &hlts.HLT_EcalCalibration, &hlts.b_HLT_EcalCalibration);
  t->SetBranchAddress("HLT_EcalCalibration_Prescl", &hlts.HLT_EcalCalibration_Prescl, &hlts.b_HLT_EcalCalibration_Prescl);
  t->SetBranchAddress("HLT_HIZeroBias", &hlts.HLT_HIZeroBias, &hlts.b_HLT_HIZeroBias);
  t->SetBranchAddress("HLT_HIZeroBias_Prescl", &hlts.HLT_HIZeroBias_Prescl, &hlts.b_HLT_HIZeroBias_Prescl);
  t->SetBranchAddress("HLT_HIZeroBiasPixel_SingleTrack", &hlts.HLT_HIZeroBiasPixel_SingleTrack, &hlts.b_HLT_HIZeroBiasPixel_SingleTrack);
  t->SetBranchAddress("HLT_HIZeroBiasPixel_SingleTrack_Prescl", &hlts.HLT_HIZeroBiasPixel_SingleTrack_Prescl, &hlts.b_HLT_HIZeroBiasPixel_SingleTrack_Prescl);
  t->SetBranchAddress("HLT_HIMinBiasZDCPixel_SingleTrack", &hlts.HLT_HIMinBiasZDCPixel_SingleTrack, &hlts.b_HLT_HIMinBiasZDCPixel_SingleTrack);
  t->SetBranchAddress("HLT_HIMinBiasZDCPixel_SingleTrack_Prescl", &hlts.HLT_HIMinBiasZDCPixel_SingleTrack_Prescl, &hlts.b_HLT_HIMinBiasZDCPixel_SingleTrack_Prescl);
  t->SetBranchAddress("HLT_HIZeroBiasXOR", &hlts.HLT_HIZeroBiasXOR, &hlts.b_HLT_HIZeroBiasXOR);
  t->SetBranchAddress("HLT_HIZeroBiasXOR_Prescl", &hlts.HLT_HIZeroBiasXOR_Prescl, &hlts.b_HLT_HIZeroBiasXOR_Prescl);
  t->SetBranchAddress("HLT_HIMinBiasBSC_OR", &hlts.HLT_HIMinBiasBSC_OR, &hlts.b_HLT_HIMinBiasBSC_OR);
  t->SetBranchAddress("HLT_HIMinBiasBSC_OR_Prescl", &hlts.HLT_HIMinBiasBSC_OR_Prescl, &hlts.b_HLT_HIMinBiasBSC_OR_Prescl);
  t->SetBranchAddress("HLT_HIMinBiasBSC", &hlts.HLT_HIMinBiasBSC, &hlts.b_HLT_HIMinBiasBSC);
  t->SetBranchAddress("HLT_HIMinBiasBSC_Prescl", &hlts.HLT_HIMinBiasBSC_Prescl, &hlts.b_HLT_HIMinBiasBSC_Prescl);
  t->SetBranchAddress("HLT_HIMinBiasHF", &hlts.HLT_HIMinBiasHF, &hlts.b_HLT_HIMinBiasHF);
  t->SetBranchAddress("HLT_HIMinBiasHF_Prescl", &hlts.HLT_HIMinBiasHF_Prescl, &hlts.b_HLT_HIMinBiasHF_Prescl);
  t->SetBranchAddress("HLT_HIMinBiasHF_Core", &hlts.HLT_HIMinBiasHF_Core, &hlts.b_HLT_HIMinBiasHF_Core);
  t->SetBranchAddress("HLT_HIMinBiasHF_Core_Prescl", &hlts.HLT_HIMinBiasHF_Core_Prescl, &hlts.b_HLT_HIMinBiasHF_Core_Prescl);
  t->SetBranchAddress("HLT_HIMinBiasHfOrBSC", &hlts.HLT_HIMinBiasHfOrBSC, &hlts.b_HLT_HIMinBiasHfOrBSC);
  t->SetBranchAddress("HLT_HIMinBiasHfOrBSC_Prescl", &hlts.HLT_HIMinBiasHfOrBSC_Prescl, &hlts.b_HLT_HIMinBiasHfOrBSC_Prescl);
  t->SetBranchAddress("HLT_HIMinBiasHfOrBSC_Core", &hlts.HLT_HIMinBiasHfOrBSC_Core, &hlts.b_HLT_HIMinBiasHfOrBSC_Core);
  t->SetBranchAddress("HLT_HIMinBiasHfOrBSC_Core_Prescl", &hlts.HLT_HIMinBiasHfOrBSC_Core_Prescl, &hlts.b_HLT_HIMinBiasHfOrBSC_Core_Prescl);
  t->SetBranchAddress("HLT_HIMinBiasPixel_SingleTrack", &hlts.HLT_HIMinBiasPixel_SingleTrack, &hlts.b_HLT_HIMinBiasPixel_SingleTrack);
  t->SetBranchAddress("HLT_HIMinBiasPixel_SingleTrack_Prescl", &hlts.HLT_HIMinBiasPixel_SingleTrack_Prescl, &hlts.b_HLT_HIMinBiasPixel_SingleTrack_Prescl);
  t->SetBranchAddress("HLT_HIMinBiasZDC_Calo", &hlts.HLT_HIMinBiasZDC_Calo, &hlts.b_HLT_HIMinBiasZDC_Calo);
  t->SetBranchAddress("HLT_HIMinBiasZDC_Calo_Prescl", &hlts.HLT_HIMinBiasZDC_Calo_Prescl, &hlts.b_HLT_HIMinBiasZDC_Calo_Prescl);
  t->SetBranchAddress("HLT_HIMinBiasZDC_Calo_PlusOrMinus", &hlts.HLT_HIMinBiasZDC_Calo_PlusOrMinus, &hlts.b_HLT_HIMinBiasZDC_Calo_PlusOrMinus);
  t->SetBranchAddress("HLT_HIMinBiasZDC_Calo_PlusOrMinus_Prescl", &hlts.HLT_HIMinBiasZDC_Calo_PlusOrMinus_Prescl, &hlts.b_HLT_HIMinBiasZDC_Calo_PlusOrMinus_Prescl);
  t->SetBranchAddress("HLT_HIMinBiasZDC_Scint", &hlts.HLT_HIMinBiasZDC_Scint, &hlts.b_HLT_HIMinBiasZDC_Scint);
  t->SetBranchAddress("HLT_HIMinBiasZDC_Scint_Prescl", &hlts.HLT_HIMinBiasZDC_Scint_Prescl, &hlts.b_HLT_HIMinBiasZDC_Scint_Prescl);
  t->SetBranchAddress("HLT_HIBptxXOR", &hlts.HLT_HIBptxXOR, &hlts.b_HLT_HIBptxXOR);
  t->SetBranchAddress("HLT_HIBptxXOR_Prescl", &hlts.HLT_HIBptxXOR_Prescl, &hlts.b_HLT_HIBptxXOR_Prescl);
  t->SetBranchAddress("HLT_HIL1Algo_BptxXOR_BSC_OR", &hlts.HLT_HIL1Algo_BptxXOR_BSC_OR, &hlts.b_HLT_HIL1Algo_BptxXOR_BSC_OR);
  t->SetBranchAddress("HLT_HIL1Algo_BptxXOR_BSC_OR_Prescl", &hlts.HLT_HIL1Algo_BptxXOR_BSC_OR_Prescl, &hlts.b_HLT_HIL1Algo_BptxXOR_BSC_OR_Prescl);
  t->SetBranchAddress("HLT_HIL1SingleMu3", &hlts.HLT_HIL1SingleMu3, &hlts.b_HLT_HIL1SingleMu3);
  t->SetBranchAddress("HLT_HIL1SingleMu3_Prescl", &hlts.HLT_HIL1SingleMu3_Prescl, &hlts.b_HLT_HIL1SingleMu3_Prescl);
  t->SetBranchAddress("HLT_HIL1SingleMu5", &hlts.HLT_HIL1SingleMu5, &hlts.b_HLT_HIL1SingleMu5);
  t->SetBranchAddress("HLT_HIL1SingleMu5_Prescl", &hlts.HLT_HIL1SingleMu5_Prescl, &hlts.b_HLT_HIL1SingleMu5_Prescl);
  t->SetBranchAddress("HLT_HIL1SingleMu7", &hlts.HLT_HIL1SingleMu7, &hlts.b_HLT_HIL1SingleMu7);
  t->SetBranchAddress("HLT_HIL1SingleMu7_Prescl", &hlts.HLT_HIL1SingleMu7_Prescl, &hlts.b_HLT_HIL1SingleMu7_Prescl);
  t->SetBranchAddress("HLT_HIL1DoubleMuOpen", &hlts.HLT_HIL1DoubleMuOpen, &hlts.b_HLT_HIL1DoubleMuOpen);
  t->SetBranchAddress("HLT_HIL1DoubleMuOpen_Prescl", &hlts.HLT_HIL1DoubleMuOpen_Prescl, &hlts.b_HLT_HIL1DoubleMuOpen_Prescl);
  t->SetBranchAddress("HLT_HIL1DoubleMuOpen_Core", &hlts.HLT_HIL1DoubleMuOpen_Core, &hlts.b_HLT_HIL1DoubleMuOpen_Core);
  t->SetBranchAddress("HLT_HIL1DoubleMuOpen_Core_Prescl", &hlts.HLT_HIL1DoubleMuOpen_Core_Prescl, &hlts.b_HLT_HIL1DoubleMuOpen_Core_Prescl);
  t->SetBranchAddress("HLT_HIUpcEcal", &hlts.HLT_HIUpcEcal, &hlts.b_HLT_HIUpcEcal);
  t->SetBranchAddress("HLT_HIUpcEcal_Prescl", &hlts.HLT_HIUpcEcal_Prescl, &hlts.b_HLT_HIUpcEcal_Prescl);
  t->SetBranchAddress("HLT_HIUpcEcal_Core", &hlts.HLT_HIUpcEcal_Core, &hlts.b_HLT_HIUpcEcal_Core);
  t->SetBranchAddress("HLT_HIUpcEcal_Core_Prescl", &hlts.HLT_HIUpcEcal_Core_Prescl, &hlts.b_HLT_HIUpcEcal_Core_Prescl);
  t->SetBranchAddress("HLT_HIUpcMu", &hlts.HLT_HIUpcMu, &hlts.b_HLT_HIUpcMu);
  t->SetBranchAddress("HLT_HIUpcMu_Prescl", &hlts.HLT_HIUpcMu_Prescl, &hlts.b_HLT_HIUpcMu_Prescl);
  t->SetBranchAddress("HLT_HIUpcMu_Core", &hlts.HLT_HIUpcMu_Core, &hlts.b_HLT_HIUpcMu_Core);
  t->SetBranchAddress("HLT_HIUpcMu_Core_Prescl", &hlts.HLT_HIUpcMu_Core_Prescl, &hlts.b_HLT_HIUpcMu_Core_Prescl);
  t->SetBranchAddress("HLT_HIPhoton15", &hlts.HLT_HIPhoton15, &hlts.b_HLT_HIPhoton15);
  t->SetBranchAddress("HLT_HIPhoton15_Prescl", &hlts.HLT_HIPhoton15_Prescl, &hlts.b_HLT_HIPhoton15_Prescl);
  t->SetBranchAddress("HLT_HIPhoton15_Core", &hlts.HLT_HIPhoton15_Core, &hlts.b_HLT_HIPhoton15_Core);
  t->SetBranchAddress("HLT_HIPhoton15_Core_Prescl", &hlts.HLT_HIPhoton15_Core_Prescl, &hlts.b_HLT_HIPhoton15_Core_Prescl);
  t->SetBranchAddress("HLT_HIPhoton20", &hlts.HLT_HIPhoton20, &hlts.b_HLT_HIPhoton20);
  t->SetBranchAddress("HLT_HIPhoton20_Prescl", &hlts.HLT_HIPhoton20_Prescl, &hlts.b_HLT_HIPhoton20_Prescl);
  t->SetBranchAddress("HLT_HIPhoton20_Core", &hlts.HLT_HIPhoton20_Core, &hlts.b_HLT_HIPhoton20_Core);
  t->SetBranchAddress("HLT_HIPhoton20_Core_Prescl", &hlts.HLT_HIPhoton20_Core_Prescl, &hlts.b_HLT_HIPhoton20_Core_Prescl);
  t->SetBranchAddress("HLT_HIPhoton30", &hlts.HLT_HIPhoton30, &hlts.b_HLT_HIPhoton30);
  t->SetBranchAddress("HLT_HIPhoton30_Prescl", &hlts.HLT_HIPhoton30_Prescl, &hlts.b_HLT_HIPhoton30_Prescl);
  t->SetBranchAddress("HLT_HIPhoton30_Core", &hlts.HLT_HIPhoton30_Core, &hlts.b_HLT_HIPhoton30_Core);
  t->SetBranchAddress("HLT_HIPhoton30_Core_Prescl", &hlts.HLT_HIPhoton30_Core_Prescl, &hlts.b_HLT_HIPhoton30_Core_Prescl);
  t->SetBranchAddress("HLT_HIDoublePhoton5_CEP_L1R", &hlts.HLT_HIDoublePhoton5_CEP_L1R, &hlts.b_HLT_HIDoublePhoton5_CEP_L1R);
  t->SetBranchAddress("HLT_HIDoublePhoton5_CEP_L1R_Prescl", &hlts.HLT_HIDoublePhoton5_CEP_L1R_Prescl, &hlts.b_HLT_HIDoublePhoton5_CEP_L1R_Prescl);
  t->SetBranchAddress("HLT_HIJet35U", &hlts.HLT_HIJet35U, &hlts.b_HLT_HIJet35U);
  t->SetBranchAddress("HLT_HIJet35U_Prescl", &hlts.HLT_HIJet35U_Prescl, &hlts.b_HLT_HIJet35U_Prescl);
  t->SetBranchAddress("HLT_HIJet35U_Core", &hlts.HLT_HIJet35U_Core, &hlts.b_HLT_HIJet35U_Core);
  t->SetBranchAddress("HLT_HIJet35U_Core_Prescl", &hlts.HLT_HIJet35U_Core_Prescl, &hlts.b_HLT_HIJet35U_Core_Prescl);
  t->SetBranchAddress("HLT_HIJet50U", &hlts.HLT_HIJet50U, &hlts.b_HLT_HIJet50U);
  t->SetBranchAddress("HLT_HIJet50U_Prescl", &hlts.HLT_HIJet50U_Prescl, &hlts.b_HLT_HIJet50U_Prescl);
  t->SetBranchAddress("HLT_HIJet50U_Core", &hlts.HLT_HIJet50U_Core, &hlts.b_HLT_HIJet50U_Core);
  t->SetBranchAddress("HLT_HIJet50U_Core_Prescl", &hlts.HLT_HIJet50U_Core_Prescl, &hlts.b_HLT_HIJet50U_Core_Prescl);
  t->SetBranchAddress("HLT_HIJet75U", &hlts.HLT_HIJet75U, &hlts.b_HLT_HIJet75U);
  t->SetBranchAddress("HLT_HIJet75U_Prescl", &hlts.HLT_HIJet75U_Prescl, &hlts.b_HLT_HIJet75U_Prescl);
  t->SetBranchAddress("HLT_HIJet75U_Core", &hlts.HLT_HIJet75U_Core, &hlts.b_HLT_HIJet75U_Core);
  t->SetBranchAddress("HLT_HIJet75U_Core_Prescl", &hlts.HLT_HIJet75U_Core_Prescl, &hlts.b_HLT_HIJet75U_Core_Prescl);
  t->SetBranchAddress("HLT_HIJet90U", &hlts.HLT_HIJet90U, &hlts.b_HLT_HIJet90U);
  t->SetBranchAddress("HLT_HIJet90U_Prescl", &hlts.HLT_HIJet90U_Prescl, &hlts.b_HLT_HIJet90U_Prescl);
  t->SetBranchAddress("HLT_HIJet90U_Core", &hlts.HLT_HIJet90U_Core, &hlts.b_HLT_HIJet90U_Core);
  t->SetBranchAddress("HLT_HIJet90U_Core_Prescl", &hlts.HLT_HIJet90U_Core_Prescl, &hlts.b_HLT_HIJet90U_Core_Prescl);
  t->SetBranchAddress("HLT_HIStoppedHSCP35", &hlts.HLT_HIStoppedHSCP35, &hlts.b_HLT_HIStoppedHSCP35);
  t->SetBranchAddress("HLT_HIStoppedHSCP35_Prescl", &hlts.HLT_HIStoppedHSCP35_Prescl, &hlts.b_HLT_HIStoppedHSCP35_Prescl);
  t->SetBranchAddress("HLT_HIClusterVertexCompatibility", &hlts.HLT_HIClusterVertexCompatibility, &hlts.b_HLT_HIClusterVertexCompatibility);
  t->SetBranchAddress("HLT_HIClusterVertexCompatibility_Prescl", &hlts.HLT_HIClusterVertexCompatibility_Prescl, &hlts.b_HLT_HIClusterVertexCompatibility_Prescl);
  t->SetBranchAddress("HLT_HICentralityVeto", &hlts.HLT_HICentralityVeto, &hlts.b_HLT_HICentralityVeto);
  t->SetBranchAddress("HLT_HICentralityVeto_Prescl", &hlts.HLT_HICentralityVeto_Prescl, &hlts.b_HLT_HICentralityVeto_Prescl);
  t->SetBranchAddress("HLT_HIRandom", &hlts.HLT_HIRandom, &hlts.b_HLT_HIRandom);
  t->SetBranchAddress("HLT_HIRandom_Prescl", &hlts.HLT_HIRandom_Prescl, &hlts.b_HLT_HIRandom_Prescl);
  t->SetBranchAddress("HLT_HcalCalibration_HI", &hlts.HLT_HcalCalibration_HI, &hlts.b_HLT_HcalCalibration_HI);
  t->SetBranchAddress("HLT_HcalCalibration_HI_Prescl", &hlts.HLT_HcalCalibration_HI_Prescl, &hlts.b_HLT_HcalCalibration_HI_Prescl);
  t->SetBranchAddress("HLTriggerFinalPath", &hlts.HLTriggerFinalPath, &hlts.b_HLTriggerFinalPath);
  t->SetBranchAddress("HLTriggerFinalPath_Prescl", &hlts.HLTriggerFinalPath_Prescl, &hlts.b_HLTriggerFinalPath_Prescl);
  t->SetBranchAddress("L1_BptxMinus", &hlts.L1_BptxMinus, &hlts.b_L1_BptxMinus);
  t->SetBranchAddress("L1_BptxMinus_Prescl", &hlts.L1_BptxMinus_Prescl, &hlts.b_L1_BptxMinus_Prescl);
  t->SetBranchAddress("L1_BptxMinus_5bx", &hlts.L1_BptxMinus_5bx, &hlts.b_L1_BptxMinus_5bx);
  t->SetBranchAddress("L1_BptxMinus_NotBptxPlus", &hlts.L1_BptxMinus_NotBptxPlus, &hlts.b_L1_BptxMinus_NotBptxPlus);
  t->SetBranchAddress("L1_BptxMinus_NotBptxPlus_Prescl", &hlts.L1_BptxMinus_NotBptxPlus_Prescl, &hlts.b_L1_BptxMinus_NotBptxPlus_Prescl);
  t->SetBranchAddress("L1_BptxMinus_NotBptxPlus_5bx", &hlts.L1_BptxMinus_NotBptxPlus_5bx, &hlts.b_L1_BptxMinus_NotBptxPlus_5bx);
  t->SetBranchAddress("L1_BptxPlus", &hlts.L1_BptxPlus, &hlts.b_L1_BptxPlus);
  t->SetBranchAddress("L1_BptxPlus_Prescl", &hlts.L1_BptxPlus_Prescl, &hlts.b_L1_BptxPlus_Prescl);
  t->SetBranchAddress("L1_BptxPlus_5bx", &hlts.L1_BptxPlus_5bx, &hlts.b_L1_BptxPlus_5bx);
  t->SetBranchAddress("L1_BptxPlusANDMinus", &hlts.L1_BptxPlusANDMinus, &hlts.b_L1_BptxPlusANDMinus);
  t->SetBranchAddress("L1_BptxPlusANDMinus_Prescl", &hlts.L1_BptxPlusANDMinus_Prescl, &hlts.b_L1_BptxPlusANDMinus_Prescl);
  t->SetBranchAddress("L1_BptxPlusANDMinus_5bx", &hlts.L1_BptxPlusANDMinus_5bx, &hlts.b_L1_BptxPlusANDMinus_5bx);
  t->SetBranchAddress("L1_BptxPlusORMinus", &hlts.L1_BptxPlusORMinus, &hlts.b_L1_BptxPlusORMinus);
  t->SetBranchAddress("L1_BptxPlusORMinus_Prescl", &hlts.L1_BptxPlusORMinus_Prescl, &hlts.b_L1_BptxPlusORMinus_Prescl);
  t->SetBranchAddress("L1_BptxPlusORMinus_5bx", &hlts.L1_BptxPlusORMinus_5bx, &hlts.b_L1_BptxPlusORMinus_5bx);
  t->SetBranchAddress("L1_BptxPlusORMinus_instance1", &hlts.L1_BptxPlusORMinus_instance1, &hlts.b_L1_BptxPlusORMinus_instance1);
  t->SetBranchAddress("L1_BptxPlusORMinus_instance1_Prescl", &hlts.L1_BptxPlusORMinus_instance1_Prescl, &hlts.b_L1_BptxPlusORMinus_instance1_Prescl);
  t->SetBranchAddress("L1_BptxPlusORMinus_instance1_5bx", &hlts.L1_BptxPlusORMinus_instance1_5bx, &hlts.b_L1_BptxPlusORMinus_instance1_5bx);
  t->SetBranchAddress("L1_BptxPlus_NotBptxMinus", &hlts.L1_BptxPlus_NotBptxMinus, &hlts.b_L1_BptxPlus_NotBptxMinus);
  t->SetBranchAddress("L1_BptxPlus_NotBptxMinus_Prescl", &hlts.L1_BptxPlus_NotBptxMinus_Prescl, &hlts.b_L1_BptxPlus_NotBptxMinus_Prescl);
  t->SetBranchAddress("L1_BptxPlus_NotBptxMinus_5bx", &hlts.L1_BptxPlus_NotBptxMinus_5bx, &hlts.b_L1_BptxPlus_NotBptxMinus_5bx);
  t->SetBranchAddress("L1_BptxXOR", &hlts.L1_BptxXOR, &hlts.b_L1_BptxXOR);
  t->SetBranchAddress("L1_BptxXOR_Prescl", &hlts.L1_BptxXOR_Prescl, &hlts.b_L1_BptxXOR_Prescl);
  t->SetBranchAddress("L1_BptxXOR_5bx", &hlts.L1_BptxXOR_5bx, &hlts.b_L1_BptxXOR_5bx);
  t->SetBranchAddress("L1_BptxXOR_BscMinBiasOR", &hlts.L1_BptxXOR_BscMinBiasOR, &hlts.b_L1_BptxXOR_BscMinBiasOR);
  t->SetBranchAddress("L1_BptxXOR_BscMinBiasOR_Prescl", &hlts.L1_BptxXOR_BscMinBiasOR_Prescl, &hlts.b_L1_BptxXOR_BscMinBiasOR_Prescl);
  t->SetBranchAddress("L1_BptxXOR_BscMinBiasOR_5bx", &hlts.L1_BptxXOR_BscMinBiasOR_5bx, &hlts.b_L1_BptxXOR_BscMinBiasOR_5bx);
  t->SetBranchAddress("L1_Bsc2Minus_BptxMinus", &hlts.L1_Bsc2Minus_BptxMinus, &hlts.b_L1_Bsc2Minus_BptxMinus);
  t->SetBranchAddress("L1_Bsc2Minus_BptxMinus_Prescl", &hlts.L1_Bsc2Minus_BptxMinus_Prescl, &hlts.b_L1_Bsc2Minus_BptxMinus_Prescl);
  t->SetBranchAddress("L1_Bsc2Minus_BptxMinus_5bx", &hlts.L1_Bsc2Minus_BptxMinus_5bx, &hlts.b_L1_Bsc2Minus_BptxMinus_5bx);
  t->SetBranchAddress("L1_Bsc2Plus_BptxPlus", &hlts.L1_Bsc2Plus_BptxPlus, &hlts.b_L1_Bsc2Plus_BptxPlus);
  t->SetBranchAddress("L1_Bsc2Plus_BptxPlus_Prescl", &hlts.L1_Bsc2Plus_BptxPlus_Prescl, &hlts.b_L1_Bsc2Plus_BptxPlus_Prescl);
  t->SetBranchAddress("L1_Bsc2Plus_BptxPlus_5bx", &hlts.L1_Bsc2Plus_BptxPlus_5bx, &hlts.b_L1_Bsc2Plus_BptxPlus_5bx);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1", &hlts.L1_BscMinBiasInnerThreshold1, &hlts.b_L1_BscMinBiasInnerThreshold1);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1_Prescl", &hlts.L1_BscMinBiasInnerThreshold1_Prescl, &hlts.b_L1_BscMinBiasInnerThreshold1_Prescl);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1_5bx", &hlts.L1_BscMinBiasInnerThreshold1_5bx, &hlts.b_L1_BscMinBiasInnerThreshold1_5bx);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1_BptxAND", &hlts.L1_BscMinBiasInnerThreshold1_BptxAND, &hlts.b_L1_BscMinBiasInnerThreshold1_BptxAND);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1_BptxAND_Prescl", &hlts.L1_BscMinBiasInnerThreshold1_BptxAND_Prescl, &hlts.b_L1_BscMinBiasInnerThreshold1_BptxAND_Prescl);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1_BptxAND_5bx", &hlts.L1_BscMinBiasInnerThreshold1_BptxAND_5bx, &hlts.b_L1_BscMinBiasInnerThreshold1_BptxAND_5bx);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold2_BptxAND", &hlts.L1_BscMinBiasInnerThreshold2_BptxAND, &hlts.b_L1_BscMinBiasInnerThreshold2_BptxAND);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold2_BptxAND_Prescl", &hlts.L1_BscMinBiasInnerThreshold2_BptxAND_Prescl, &hlts.b_L1_BscMinBiasInnerThreshold2_BptxAND_Prescl);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold2_BptxAND_5bx", &hlts.L1_BscMinBiasInnerThreshold2_BptxAND_5bx, &hlts.b_L1_BscMinBiasInnerThreshold2_BptxAND_5bx);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxAND", &hlts.L1_BscMinBiasOR_BptxAND, &hlts.b_L1_BscMinBiasOR_BptxAND);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxAND_Prescl", &hlts.L1_BscMinBiasOR_BptxAND_Prescl, &hlts.b_L1_BscMinBiasOR_BptxAND_Prescl);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxAND_5bx", &hlts.L1_BscMinBiasOR_BptxAND_5bx, &hlts.b_L1_BscMinBiasOR_BptxAND_5bx);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxPlusORMinus", &hlts.L1_BscMinBiasOR_BptxPlusORMinus, &hlts.b_L1_BscMinBiasOR_BptxPlusORMinus);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxPlusORMinus_Prescl", &hlts.L1_BscMinBiasOR_BptxPlusORMinus_Prescl, &hlts.b_L1_BscMinBiasOR_BptxPlusORMinus_Prescl);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxPlusORMinus_5bx", &hlts.L1_BscMinBiasOR_BptxPlusORMinus_5bx, &hlts.b_L1_BscMinBiasOR_BptxPlusORMinus_5bx);
  t->SetBranchAddress("L1_BscMinBiasThreshold1", &hlts.L1_BscMinBiasThreshold1, &hlts.b_L1_BscMinBiasThreshold1);
  t->SetBranchAddress("L1_BscMinBiasThreshold1_Prescl", &hlts.L1_BscMinBiasThreshold1_Prescl, &hlts.b_L1_BscMinBiasThreshold1_Prescl);
  t->SetBranchAddress("L1_BscMinBiasThreshold1_5bx", &hlts.L1_BscMinBiasThreshold1_5bx, &hlts.b_L1_BscMinBiasThreshold1_5bx);
  t->SetBranchAddress("L1_BscMinBiasThreshold1_BptxAND", &hlts.L1_BscMinBiasThreshold1_BptxAND, &hlts.b_L1_BscMinBiasThreshold1_BptxAND);
  t->SetBranchAddress("L1_BscMinBiasThreshold1_BptxAND_Prescl", &hlts.L1_BscMinBiasThreshold1_BptxAND_Prescl, &hlts.b_L1_BscMinBiasThreshold1_BptxAND_Prescl);
  t->SetBranchAddress("L1_BscMinBiasThreshold1_BptxAND_5bx", &hlts.L1_BscMinBiasThreshold1_BptxAND_5bx, &hlts.b_L1_BscMinBiasThreshold1_BptxAND_5bx);
  t->SetBranchAddress("L1_BscMinBiasThreshold2_BptxAND", &hlts.L1_BscMinBiasThreshold2_BptxAND, &hlts.b_L1_BscMinBiasThreshold2_BptxAND);
  t->SetBranchAddress("L1_BscMinBiasThreshold2_BptxAND_Prescl", &hlts.L1_BscMinBiasThreshold2_BptxAND_Prescl, &hlts.b_L1_BscMinBiasThreshold2_BptxAND_Prescl);
  t->SetBranchAddress("L1_BscMinBiasThreshold2_BptxAND_5bx", &hlts.L1_BscMinBiasThreshold2_BptxAND_5bx, &hlts.b_L1_BscMinBiasThreshold2_BptxAND_5bx);
  t->SetBranchAddress("L1_DoubleEG2", &hlts.L1_DoubleEG2, &hlts.b_L1_DoubleEG2);
  t->SetBranchAddress("L1_DoubleEG2_Prescl", &hlts.L1_DoubleEG2_Prescl, &hlts.b_L1_DoubleEG2_Prescl);
  t->SetBranchAddress("L1_DoubleEG2_5bx", &hlts.L1_DoubleEG2_5bx, &hlts.b_L1_DoubleEG2_5bx);
  t->SetBranchAddress("L1_DoubleEG5", &hlts.L1_DoubleEG5, &hlts.b_L1_DoubleEG5);
  t->SetBranchAddress("L1_DoubleEG5_Prescl", &hlts.L1_DoubleEG5_Prescl, &hlts.b_L1_DoubleEG5_Prescl);
  t->SetBranchAddress("L1_DoubleEG5_5bx", &hlts.L1_DoubleEG5_5bx, &hlts.b_L1_DoubleEG5_5bx);
  t->SetBranchAddress("L1_DoubleEG5_BptxAND", &hlts.L1_DoubleEG5_BptxAND, &hlts.b_L1_DoubleEG5_BptxAND);
  t->SetBranchAddress("L1_DoubleEG5_BptxAND_Prescl", &hlts.L1_DoubleEG5_BptxAND_Prescl, &hlts.b_L1_DoubleEG5_BptxAND_Prescl);
  t->SetBranchAddress("L1_DoubleEG5_BptxAND_5bx", &hlts.L1_DoubleEG5_BptxAND_5bx, &hlts.b_L1_DoubleEG5_BptxAND_5bx);
  t->SetBranchAddress("L1_DoubleForJet10_EtaOpp", &hlts.L1_DoubleForJet10_EtaOpp, &hlts.b_L1_DoubleForJet10_EtaOpp);
  t->SetBranchAddress("L1_DoubleForJet10_EtaOpp_Prescl", &hlts.L1_DoubleForJet10_EtaOpp_Prescl, &hlts.b_L1_DoubleForJet10_EtaOpp_Prescl);
  t->SetBranchAddress("L1_DoubleForJet10_EtaOpp_5bx", &hlts.L1_DoubleForJet10_EtaOpp_5bx, &hlts.b_L1_DoubleForJet10_EtaOpp_5bx);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing1_P1N1", &hlts.L1_DoubleHfBitCountsRing1_P1N1, &hlts.b_L1_DoubleHfBitCountsRing1_P1N1);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing1_P1N1_Prescl", &hlts.L1_DoubleHfBitCountsRing1_P1N1_Prescl, &hlts.b_L1_DoubleHfBitCountsRing1_P1N1_Prescl);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing1_P1N1_5bx", &hlts.L1_DoubleHfBitCountsRing1_P1N1_5bx, &hlts.b_L1_DoubleHfBitCountsRing1_P1N1_5bx);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing2_P1N1", &hlts.L1_DoubleHfBitCountsRing2_P1N1, &hlts.b_L1_DoubleHfBitCountsRing2_P1N1);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing2_P1N1_Prescl", &hlts.L1_DoubleHfBitCountsRing2_P1N1_Prescl, &hlts.b_L1_DoubleHfBitCountsRing2_P1N1_Prescl);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing2_P1N1_5bx", &hlts.L1_DoubleHfBitCountsRing2_P1N1_5bx, &hlts.b_L1_DoubleHfBitCountsRing2_P1N1_5bx);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P200N200", &hlts.L1_DoubleHfRingEtSumsRing1_P200N200, &hlts.b_L1_DoubleHfRingEtSumsRing1_P200N200);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P200N200_Prescl", &hlts.L1_DoubleHfRingEtSumsRing1_P200N200_Prescl, &hlts.b_L1_DoubleHfRingEtSumsRing1_P200N200_Prescl);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P200N200_5bx", &hlts.L1_DoubleHfRingEtSumsRing1_P200N200_5bx, &hlts.b_L1_DoubleHfRingEtSumsRing1_P200N200_5bx);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P4N4", &hlts.L1_DoubleHfRingEtSumsRing1_P4N4, &hlts.b_L1_DoubleHfRingEtSumsRing1_P4N4);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P4N4_Prescl", &hlts.L1_DoubleHfRingEtSumsRing1_P4N4_Prescl, &hlts.b_L1_DoubleHfRingEtSumsRing1_P4N4_Prescl);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P4N4_5bx", &hlts.L1_DoubleHfRingEtSumsRing1_P4N4_5bx, &hlts.b_L1_DoubleHfRingEtSumsRing1_P4N4_5bx);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P200N200", &hlts.L1_DoubleHfRingEtSumsRing2_P200N200, &hlts.b_L1_DoubleHfRingEtSumsRing2_P200N200);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P200N200_Prescl", &hlts.L1_DoubleHfRingEtSumsRing2_P200N200_Prescl, &hlts.b_L1_DoubleHfRingEtSumsRing2_P200N200_Prescl);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P200N200_5bx", &hlts.L1_DoubleHfRingEtSumsRing2_P200N200_5bx, &hlts.b_L1_DoubleHfRingEtSumsRing2_P200N200_5bx);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P4N4", &hlts.L1_DoubleHfRingEtSumsRing2_P4N4, &hlts.b_L1_DoubleHfRingEtSumsRing2_P4N4);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P4N4_Prescl", &hlts.L1_DoubleHfRingEtSumsRing2_P4N4_Prescl, &hlts.b_L1_DoubleHfRingEtSumsRing2_P4N4_Prescl);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P4N4_5bx", &hlts.L1_DoubleHfRingEtSumsRing2_P4N4_5bx, &hlts.b_L1_DoubleHfRingEtSumsRing2_P4N4_5bx);
  t->SetBranchAddress("L1_DoubleJet30", &hlts.L1_DoubleJet30, &hlts.b_L1_DoubleJet30);
  t->SetBranchAddress("L1_DoubleJet30_Prescl", &hlts.L1_DoubleJet30_Prescl, &hlts.b_L1_DoubleJet30_Prescl);
  t->SetBranchAddress("L1_DoubleJet30_5bx", &hlts.L1_DoubleJet30_5bx, &hlts.b_L1_DoubleJet30_5bx);
  t->SetBranchAddress("L1_DoubleMu3", &hlts.L1_DoubleMu3, &hlts.b_L1_DoubleMu3);
  t->SetBranchAddress("L1_DoubleMu3_Prescl", &hlts.L1_DoubleMu3_Prescl, &hlts.b_L1_DoubleMu3_Prescl);
  t->SetBranchAddress("L1_DoubleMu3_5bx", &hlts.L1_DoubleMu3_5bx, &hlts.b_L1_DoubleMu3_5bx);
  t->SetBranchAddress("L1_DoubleMuOpen", &hlts.L1_DoubleMuOpen, &hlts.b_L1_DoubleMuOpen);
  t->SetBranchAddress("L1_DoubleMuOpen_Prescl", &hlts.L1_DoubleMuOpen_Prescl, &hlts.b_L1_DoubleMuOpen_Prescl);
  t->SetBranchAddress("L1_DoubleMuOpen_5bx", &hlts.L1_DoubleMuOpen_5bx, &hlts.b_L1_DoubleMuOpen_5bx);
  t->SetBranchAddress("L1_DoubleMuOpen_BptxAND", &hlts.L1_DoubleMuOpen_BptxAND, &hlts.b_L1_DoubleMuOpen_BptxAND);
  t->SetBranchAddress("L1_DoubleMuOpen_BptxAND_Prescl", &hlts.L1_DoubleMuOpen_BptxAND_Prescl, &hlts.b_L1_DoubleMuOpen_BptxAND_Prescl);
  t->SetBranchAddress("L1_DoubleMuOpen_BptxAND_5bx", &hlts.L1_DoubleMuOpen_BptxAND_5bx, &hlts.b_L1_DoubleMuOpen_BptxAND_5bx);
  t->SetBranchAddress("L1_ETM12", &hlts.L1_ETM12, &hlts.b_L1_ETM12);
  t->SetBranchAddress("L1_ETM12_Prescl", &hlts.L1_ETM12_Prescl, &hlts.b_L1_ETM12_Prescl);
  t->SetBranchAddress("L1_ETM12_5bx", &hlts.L1_ETM12_5bx, &hlts.b_L1_ETM12_5bx);
  t->SetBranchAddress("L1_ETM20", &hlts.L1_ETM20, &hlts.b_L1_ETM20);
  t->SetBranchAddress("L1_ETM20_Prescl", &hlts.L1_ETM20_Prescl, &hlts.b_L1_ETM20_Prescl);
  t->SetBranchAddress("L1_ETM20_5bx", &hlts.L1_ETM20_5bx, &hlts.b_L1_ETM20_5bx);
  t->SetBranchAddress("L1_ETM30", &hlts.L1_ETM30, &hlts.b_L1_ETM30);
  t->SetBranchAddress("L1_ETM30_Prescl", &hlts.L1_ETM30_Prescl, &hlts.b_L1_ETM30_Prescl);
  t->SetBranchAddress("L1_ETM30_5bx", &hlts.L1_ETM30_5bx, &hlts.b_L1_ETM30_5bx);
  t->SetBranchAddress("L1_ETM70", &hlts.L1_ETM70, &hlts.b_L1_ETM70);
  t->SetBranchAddress("L1_ETM70_Prescl", &hlts.L1_ETM70_Prescl, &hlts.b_L1_ETM70_Prescl);
  t->SetBranchAddress("L1_ETM70_5bx", &hlts.L1_ETM70_5bx, &hlts.b_L1_ETM70_5bx);
  t->SetBranchAddress("L1_ETT100", &hlts.L1_ETT100, &hlts.b_L1_ETT100);
  t->SetBranchAddress("L1_ETT100_Prescl", &hlts.L1_ETT100_Prescl, &hlts.b_L1_ETT100_Prescl);
  t->SetBranchAddress("L1_ETT100_5bx", &hlts.L1_ETT100_5bx, &hlts.b_L1_ETT100_5bx);
  t->SetBranchAddress("L1_ETT140", &hlts.L1_ETT140, &hlts.b_L1_ETT140);
  t->SetBranchAddress("L1_ETT140_Prescl", &hlts.L1_ETT140_Prescl, &hlts.b_L1_ETT140_Prescl);
  t->SetBranchAddress("L1_ETT140_5bx", &hlts.L1_ETT140_5bx, &hlts.b_L1_ETT140_5bx);
  t->SetBranchAddress("L1_ETT30", &hlts.L1_ETT30, &hlts.b_L1_ETT30);
  t->SetBranchAddress("L1_ETT30_Prescl", &hlts.L1_ETT30_Prescl, &hlts.b_L1_ETT30_Prescl);
  t->SetBranchAddress("L1_ETT30_5bx", &hlts.L1_ETT30_5bx, &hlts.b_L1_ETT30_5bx);
  t->SetBranchAddress("L1_ETT30_BptxAND", &hlts.L1_ETT30_BptxAND, &hlts.b_L1_ETT30_BptxAND);
  t->SetBranchAddress("L1_ETT30_BptxAND_Prescl", &hlts.L1_ETT30_BptxAND_Prescl, &hlts.b_L1_ETT30_BptxAND_Prescl);
  t->SetBranchAddress("L1_ETT30_BptxAND_5bx", &hlts.L1_ETT30_BptxAND_5bx, &hlts.b_L1_ETT30_BptxAND_5bx);
  t->SetBranchAddress("L1_ETT60", &hlts.L1_ETT60, &hlts.b_L1_ETT60);
  t->SetBranchAddress("L1_ETT60_Prescl", &hlts.L1_ETT60_Prescl, &hlts.b_L1_ETT60_Prescl);
  t->SetBranchAddress("L1_ETT60_5bx", &hlts.L1_ETT60_5bx, &hlts.b_L1_ETT60_5bx);
  t->SetBranchAddress("L1_ETT60_BptxAND", &hlts.L1_ETT60_BptxAND, &hlts.b_L1_ETT60_BptxAND);
  t->SetBranchAddress("L1_ETT60_BptxAND_Prescl", &hlts.L1_ETT60_BptxAND_Prescl, &hlts.b_L1_ETT60_BptxAND_Prescl);
  t->SetBranchAddress("L1_ETT60_BptxAND_5bx", &hlts.L1_ETT60_BptxAND_5bx, &hlts.b_L1_ETT60_BptxAND_5bx);
  t->SetBranchAddress("L1_HTM30", &hlts.L1_HTM30, &hlts.b_L1_HTM30);
  t->SetBranchAddress("L1_HTM30_Prescl", &hlts.L1_HTM30_Prescl, &hlts.b_L1_HTM30_Prescl);
  t->SetBranchAddress("L1_HTM30_5bx", &hlts.L1_HTM30_5bx, &hlts.b_L1_HTM30_5bx);
  t->SetBranchAddress("L1_HTT100", &hlts.L1_HTT100, &hlts.b_L1_HTT100);
  t->SetBranchAddress("L1_HTT100_Prescl", &hlts.L1_HTT100_Prescl, &hlts.b_L1_HTT100_Prescl);
  t->SetBranchAddress("L1_HTT100_5bx", &hlts.L1_HTT100_5bx, &hlts.b_L1_HTT100_5bx);
  t->SetBranchAddress("L1_HTT200", &hlts.L1_HTT200, &hlts.b_L1_HTT200);
  t->SetBranchAddress("L1_HTT200_Prescl", &hlts.L1_HTT200_Prescl, &hlts.b_L1_HTT200_Prescl);
  t->SetBranchAddress("L1_HTT200_5bx", &hlts.L1_HTT200_5bx, &hlts.b_L1_HTT200_5bx);
  t->SetBranchAddress("L1_HTT50", &hlts.L1_HTT50, &hlts.b_L1_HTT50);
  t->SetBranchAddress("L1_HTT50_Prescl", &hlts.L1_HTT50_Prescl, &hlts.b_L1_HTT50_Prescl);
  t->SetBranchAddress("L1_HTT50_5bx", &hlts.L1_HTT50_5bx, &hlts.b_L1_HTT50_5bx);
  t->SetBranchAddress("L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND", &hlts.L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND, &hlts.b_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND);
  t->SetBranchAddress("L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl", &hlts.L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl, &hlts.b_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl);
  t->SetBranchAddress("L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_5bx", &hlts.L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_5bx, &hlts.b_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_5bx);
  t->SetBranchAddress("L1_HcalHfCoincidencePm", &hlts.L1_HcalHfCoincidencePm, &hlts.b_L1_HcalHfCoincidencePm);
  t->SetBranchAddress("L1_HcalHfCoincidencePm_Prescl", &hlts.L1_HcalHfCoincidencePm_Prescl, &hlts.b_L1_HcalHfCoincidencePm_Prescl);
  t->SetBranchAddress("L1_HcalHfCoincidencePm_5bx", &hlts.L1_HcalHfCoincidencePm_5bx, &hlts.b_L1_HcalHfCoincidencePm_5bx);
  t->SetBranchAddress("L1_HcalHfCoincidencePm_BptxAND", &hlts.L1_HcalHfCoincidencePm_BptxAND, &hlts.b_L1_HcalHfCoincidencePm_BptxAND);
  t->SetBranchAddress("L1_HcalHfCoincidencePm_BptxAND_Prescl", &hlts.L1_HcalHfCoincidencePm_BptxAND_Prescl, &hlts.b_L1_HcalHfCoincidencePm_BptxAND_Prescl);
  t->SetBranchAddress("L1_HcalHfCoincidencePm_BptxAND_5bx", &hlts.L1_HcalHfCoincidencePm_BptxAND_5bx, &hlts.b_L1_HcalHfCoincidencePm_BptxAND_5bx);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm", &hlts.L1_HcalHfMmOrPpOrPm, &hlts.b_L1_HcalHfMmOrPpOrPm);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm_Prescl", &hlts.L1_HcalHfMmOrPpOrPm_Prescl, &hlts.b_L1_HcalHfMmOrPpOrPm_Prescl);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm_5bx", &hlts.L1_HcalHfMmOrPpOrPm_5bx, &hlts.b_L1_HcalHfMmOrPpOrPm_5bx);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm_BptxAND", &hlts.L1_HcalHfMmOrPpOrPm_BptxAND, &hlts.b_L1_HcalHfMmOrPpOrPm_BptxAND);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm_BptxAND_Prescl", &hlts.L1_HcalHfMmOrPpOrPm_BptxAND_Prescl, &hlts.b_L1_HcalHfMmOrPpOrPm_BptxAND_Prescl);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm_BptxAND_5bx", &hlts.L1_HcalHfMmOrPpOrPm_BptxAND_5bx, &hlts.b_L1_HcalHfMmOrPpOrPm_BptxAND_5bx);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp", &hlts.L1_HcalHfMmpOrMpp, &hlts.b_L1_HcalHfMmpOrMpp);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp_Prescl", &hlts.L1_HcalHfMmpOrMpp_Prescl, &hlts.b_L1_HcalHfMmpOrMpp_Prescl);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp_5bx", &hlts.L1_HcalHfMmpOrMpp_5bx, &hlts.b_L1_HcalHfMmpOrMpp_5bx);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp_BptxAND", &hlts.L1_HcalHfMmpOrMpp_BptxAND, &hlts.b_L1_HcalHfMmpOrMpp_BptxAND);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp_BptxAND_Prescl", &hlts.L1_HcalHfMmpOrMpp_BptxAND_Prescl, &hlts.b_L1_HcalHfMmpOrMpp_BptxAND_Prescl);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp_BptxAND_5bx", &hlts.L1_HcalHfMmpOrMpp_BptxAND_5bx, &hlts.b_L1_HcalHfMmpOrMpp_BptxAND_5bx);
  t->SetBranchAddress("L1_HcalHoTotalOR", &hlts.L1_HcalHoTotalOR, &hlts.b_L1_HcalHoTotalOR);
  t->SetBranchAddress("L1_HcalHoTotalOR_Prescl", &hlts.L1_HcalHoTotalOR_Prescl, &hlts.b_L1_HcalHoTotalOR_Prescl);
  t->SetBranchAddress("L1_HcalHoTotalOR_5bx", &hlts.L1_HcalHoTotalOR_5bx, &hlts.b_L1_HcalHoTotalOR_5bx);
  t->SetBranchAddress("L1_Mu3_EG5", &hlts.L1_Mu3_EG5, &hlts.b_L1_Mu3_EG5);
  t->SetBranchAddress("L1_Mu3_EG5_Prescl", &hlts.L1_Mu3_EG5_Prescl, &hlts.b_L1_Mu3_EG5_Prescl);
  t->SetBranchAddress("L1_Mu3_EG5_5bx", &hlts.L1_Mu3_EG5_5bx, &hlts.b_L1_Mu3_EG5_5bx);
  t->SetBranchAddress("L1_Mu3_Jet10", &hlts.L1_Mu3_Jet10, &hlts.b_L1_Mu3_Jet10);
  t->SetBranchAddress("L1_Mu3_Jet10_Prescl", &hlts.L1_Mu3_Jet10_Prescl, &hlts.b_L1_Mu3_Jet10_Prescl);
  t->SetBranchAddress("L1_Mu3_Jet10_5bx", &hlts.L1_Mu3_Jet10_5bx, &hlts.b_L1_Mu3_Jet10_5bx);
  t->SetBranchAddress("L1_Mu3_Jet6", &hlts.L1_Mu3_Jet6, &hlts.b_L1_Mu3_Jet6);
  t->SetBranchAddress("L1_Mu3_Jet6_Prescl", &hlts.L1_Mu3_Jet6_Prescl, &hlts.b_L1_Mu3_Jet6_Prescl);
  t->SetBranchAddress("L1_Mu3_Jet6_5bx", &hlts.L1_Mu3_Jet6_5bx, &hlts.b_L1_Mu3_Jet6_5bx);
  t->SetBranchAddress("L1_Mu5_Jet6", &hlts.L1_Mu5_Jet6, &hlts.b_L1_Mu5_Jet6);
  t->SetBranchAddress("L1_Mu5_Jet6_Prescl", &hlts.L1_Mu5_Jet6_Prescl, &hlts.b_L1_Mu5_Jet6_Prescl);
  t->SetBranchAddress("L1_Mu5_Jet6_5bx", &hlts.L1_Mu5_Jet6_5bx, &hlts.b_L1_Mu5_Jet6_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1", &hlts.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_Prescl", &hlts.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_Prescl, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_5bx", &hlts.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_5bx, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2", &hlts.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_Prescl", &hlts.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_Prescl, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_5bx", &hlts.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_5bx, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasOR", &hlts.L1_NotBsc2_BptxAND_BscMinBiasOR, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasOR);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasOR_Prescl", &hlts.L1_NotBsc2_BptxAND_BscMinBiasOR_Prescl, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasOR_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasOR_5bx", &hlts.L1_NotBsc2_BptxAND_BscMinBiasOR_5bx, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasOR_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold1", &hlts.L1_NotBsc2_BptxAND_BscMinBiasThreshold1, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold1);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold1_Prescl", &hlts.L1_NotBsc2_BptxAND_BscMinBiasThreshold1_Prescl, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold1_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold1_5bx", &hlts.L1_NotBsc2_BptxAND_BscMinBiasThreshold1_5bx, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold1_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold2", &hlts.L1_NotBsc2_BptxAND_BscMinBiasThreshold2, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold2);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold2_Prescl", &hlts.L1_NotBsc2_BptxAND_BscMinBiasThreshold2_Prescl, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold2_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold2_5bx", &hlts.L1_NotBsc2_BptxAND_BscMinBiasThreshold2_5bx, &hlts.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold2_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1", &hlts.L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1, &hlts.b_L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_Prescl", &hlts.L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_Prescl, &hlts.b_L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_5bx", &hlts.L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_5bx, &hlts.b_L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincidencePm", &hlts.L1_NotBsc2_BptxAND_HcalHfCoincidencePm, &hlts.b_L1_NotBsc2_BptxAND_HcalHfCoincidencePm);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincidencePm_Prescl", &hlts.L1_NotBsc2_BptxAND_HcalHfCoincidencePm_Prescl, &hlts.b_L1_NotBsc2_BptxAND_HcalHfCoincidencePm_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincidencePm_5bx", &hlts.L1_NotBsc2_BptxAND_HcalHfCoincidencePm_5bx, &hlts.b_L1_NotBsc2_BptxAND_HcalHfCoincidencePm_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm", &hlts.L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm, &hlts.b_L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_Prescl", &hlts.L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_Prescl, &hlts.b_L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_5bx", &hlts.L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_5bx, &hlts.b_L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmpOrMpp", &hlts.L1_NotBsc2_BptxAND_HcalHfMmpOrMpp, &hlts.b_L1_NotBsc2_BptxAND_HcalHfMmpOrMpp);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_Prescl", &hlts.L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_Prescl, &hlts.b_L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_5bx", &hlts.L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_5bx, &hlts.b_L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_5bx);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold1", &hlts.L1_NotBsc2_BscMinBiasInnerThreshold1, &hlts.b_L1_NotBsc2_BscMinBiasInnerThreshold1);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold1_Prescl", &hlts.L1_NotBsc2_BscMinBiasInnerThreshold1_Prescl, &hlts.b_L1_NotBsc2_BscMinBiasInnerThreshold1_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold1_5bx", &hlts.L1_NotBsc2_BscMinBiasInnerThreshold1_5bx, &hlts.b_L1_NotBsc2_BscMinBiasInnerThreshold1_5bx);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold2", &hlts.L1_NotBsc2_BscMinBiasInnerThreshold2, &hlts.b_L1_NotBsc2_BscMinBiasInnerThreshold2);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold2_Prescl", &hlts.L1_NotBsc2_BscMinBiasInnerThreshold2_Prescl, &hlts.b_L1_NotBsc2_BscMinBiasInnerThreshold2_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold2_5bx", &hlts.L1_NotBsc2_BscMinBiasInnerThreshold2_5bx, &hlts.b_L1_NotBsc2_BscMinBiasInnerThreshold2_5bx);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasOR", &hlts.L1_NotBsc2_BscMinBiasOR, &hlts.b_L1_NotBsc2_BscMinBiasOR);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasOR_Prescl", &hlts.L1_NotBsc2_BscMinBiasOR_Prescl, &hlts.b_L1_NotBsc2_BscMinBiasOR_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasOR_5bx", &hlts.L1_NotBsc2_BscMinBiasOR_5bx, &hlts.b_L1_NotBsc2_BscMinBiasOR_5bx);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold1", &hlts.L1_NotBsc2_BscMinBiasThreshold1, &hlts.b_L1_NotBsc2_BscMinBiasThreshold1);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold1_Prescl", &hlts.L1_NotBsc2_BscMinBiasThreshold1_Prescl, &hlts.b_L1_NotBsc2_BscMinBiasThreshold1_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold1_5bx", &hlts.L1_NotBsc2_BscMinBiasThreshold1_5bx, &hlts.b_L1_NotBsc2_BscMinBiasThreshold1_5bx);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold2", &hlts.L1_NotBsc2_BscMinBiasThreshold2, &hlts.b_L1_NotBsc2_BscMinBiasThreshold2);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold2_Prescl", &hlts.L1_NotBsc2_BscMinBiasThreshold2_Prescl, &hlts.b_L1_NotBsc2_BscMinBiasThreshold2_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold2_5bx", &hlts.L1_NotBsc2_BscMinBiasThreshold2_5bx, &hlts.b_L1_NotBsc2_BscMinBiasThreshold2_5bx);
  t->SetBranchAddress("L1_NotBsc2_HcalHfCoincidencePm", &hlts.L1_NotBsc2_HcalHfCoincidencePm, &hlts.b_L1_NotBsc2_HcalHfCoincidencePm);
  t->SetBranchAddress("L1_NotBsc2_HcalHfCoincidencePm_Prescl", &hlts.L1_NotBsc2_HcalHfCoincidencePm_Prescl, &hlts.b_L1_NotBsc2_HcalHfCoincidencePm_Prescl);
  t->SetBranchAddress("L1_NotBsc2_HcalHfCoincidencePm_5bx", &hlts.L1_NotBsc2_HcalHfCoincidencePm_5bx, &hlts.b_L1_NotBsc2_HcalHfCoincidencePm_5bx);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmOrPpOrPm", &hlts.L1_NotBsc2_HcalHfMmOrPpOrPm, &hlts.b_L1_NotBsc2_HcalHfMmOrPpOrPm);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmOrPpOrPm_Prescl", &hlts.L1_NotBsc2_HcalHfMmOrPpOrPm_Prescl, &hlts.b_L1_NotBsc2_HcalHfMmOrPpOrPm_Prescl);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmOrPpOrPm_5bx", &hlts.L1_NotBsc2_HcalHfMmOrPpOrPm_5bx, &hlts.b_L1_NotBsc2_HcalHfMmOrPpOrPm_5bx);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmpOrMpp", &hlts.L1_NotBsc2_HcalHfMmpOrMpp, &hlts.b_L1_NotBsc2_HcalHfMmpOrMpp);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmpOrMpp_Prescl", &hlts.L1_NotBsc2_HcalHfMmpOrMpp_Prescl, &hlts.b_L1_NotBsc2_HcalHfMmpOrMpp_Prescl);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmpOrMpp_5bx", &hlts.L1_NotBsc2_HcalHfMmpOrMpp_5bx, &hlts.b_L1_NotBsc2_HcalHfMmpOrMpp_5bx);
  t->SetBranchAddress("L1_QuadJet6", &hlts.L1_QuadJet6, &hlts.b_L1_QuadJet6);
  t->SetBranchAddress("L1_QuadJet6_Prescl", &hlts.L1_QuadJet6_Prescl, &hlts.b_L1_QuadJet6_Prescl);
  t->SetBranchAddress("L1_QuadJet6_5bx", &hlts.L1_QuadJet6_5bx, &hlts.b_L1_QuadJet6_5bx);
  t->SetBranchAddress("L1_QuadJet8", &hlts.L1_QuadJet8, &hlts.b_L1_QuadJet8);
  t->SetBranchAddress("L1_QuadJet8_Prescl", &hlts.L1_QuadJet8_Prescl, &hlts.b_L1_QuadJet8_Prescl);
  t->SetBranchAddress("L1_QuadJet8_5bx", &hlts.L1_QuadJet8_5bx, &hlts.b_L1_QuadJet8_5bx);
  t->SetBranchAddress("L1_SingleEG10", &hlts.L1_SingleEG10, &hlts.b_L1_SingleEG10);
  t->SetBranchAddress("L1_SingleEG10_Prescl", &hlts.L1_SingleEG10_Prescl, &hlts.b_L1_SingleEG10_Prescl);
  t->SetBranchAddress("L1_SingleEG10_5bx", &hlts.L1_SingleEG10_5bx, &hlts.b_L1_SingleEG10_5bx);
  t->SetBranchAddress("L1_SingleEG12", &hlts.L1_SingleEG12, &hlts.b_L1_SingleEG12);
  t->SetBranchAddress("L1_SingleEG12_Prescl", &hlts.L1_SingleEG12_Prescl, &hlts.b_L1_SingleEG12_Prescl);
  t->SetBranchAddress("L1_SingleEG12_5bx", &hlts.L1_SingleEG12_5bx, &hlts.b_L1_SingleEG12_5bx);
  t->SetBranchAddress("L1_SingleEG15", &hlts.L1_SingleEG15, &hlts.b_L1_SingleEG15);
  t->SetBranchAddress("L1_SingleEG15_Prescl", &hlts.L1_SingleEG15_Prescl, &hlts.b_L1_SingleEG15_Prescl);
  t->SetBranchAddress("L1_SingleEG15_5bx", &hlts.L1_SingleEG15_5bx, &hlts.b_L1_SingleEG15_5bx);
  t->SetBranchAddress("L1_SingleEG2", &hlts.L1_SingleEG2, &hlts.b_L1_SingleEG2);
  t->SetBranchAddress("L1_SingleEG2_Prescl", &hlts.L1_SingleEG2_Prescl, &hlts.b_L1_SingleEG2_Prescl);
  t->SetBranchAddress("L1_SingleEG2_5bx", &hlts.L1_SingleEG2_5bx, &hlts.b_L1_SingleEG2_5bx);
  t->SetBranchAddress("L1_SingleEG20", &hlts.L1_SingleEG20, &hlts.b_L1_SingleEG20);
  t->SetBranchAddress("L1_SingleEG20_Prescl", &hlts.L1_SingleEG20_Prescl, &hlts.b_L1_SingleEG20_Prescl);
  t->SetBranchAddress("L1_SingleEG20_5bx", &hlts.L1_SingleEG20_5bx, &hlts.b_L1_SingleEG20_5bx);
  t->SetBranchAddress("L1_SingleEG2_BptxAND", &hlts.L1_SingleEG2_BptxAND, &hlts.b_L1_SingleEG2_BptxAND);
  t->SetBranchAddress("L1_SingleEG2_BptxAND_Prescl", &hlts.L1_SingleEG2_BptxAND_Prescl, &hlts.b_L1_SingleEG2_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleEG2_BptxAND_5bx", &hlts.L1_SingleEG2_BptxAND_5bx, &hlts.b_L1_SingleEG2_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleEG5", &hlts.L1_SingleEG5, &hlts.b_L1_SingleEG5);
  t->SetBranchAddress("L1_SingleEG5_Prescl", &hlts.L1_SingleEG5_Prescl, &hlts.b_L1_SingleEG5_Prescl);
  t->SetBranchAddress("L1_SingleEG5_5bx", &hlts.L1_SingleEG5_5bx, &hlts.b_L1_SingleEG5_5bx);
  t->SetBranchAddress("L1_SingleEG5_BptxAND", &hlts.L1_SingleEG5_BptxAND, &hlts.b_L1_SingleEG5_BptxAND);
  t->SetBranchAddress("L1_SingleEG5_BptxAND_Prescl", &hlts.L1_SingleEG5_BptxAND_Prescl, &hlts.b_L1_SingleEG5_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleEG5_BptxAND_5bx", &hlts.L1_SingleEG5_BptxAND_5bx, &hlts.b_L1_SingleEG5_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleEG8", &hlts.L1_SingleEG8, &hlts.b_L1_SingleEG8);
  t->SetBranchAddress("L1_SingleEG8_Prescl", &hlts.L1_SingleEG8_Prescl, &hlts.b_L1_SingleEG8_Prescl);
  t->SetBranchAddress("L1_SingleEG8_5bx", &hlts.L1_SingleEG8_5bx, &hlts.b_L1_SingleEG8_5bx);
  t->SetBranchAddress("L1_SingleForJet2", &hlts.L1_SingleForJet2, &hlts.b_L1_SingleForJet2);
  t->SetBranchAddress("L1_SingleForJet2_Prescl", &hlts.L1_SingleForJet2_Prescl, &hlts.b_L1_SingleForJet2_Prescl);
  t->SetBranchAddress("L1_SingleForJet2_5bx", &hlts.L1_SingleForJet2_5bx, &hlts.b_L1_SingleForJet2_5bx);
  t->SetBranchAddress("L1_SingleForJet4", &hlts.L1_SingleForJet4, &hlts.b_L1_SingleForJet4);
  t->SetBranchAddress("L1_SingleForJet4_Prescl", &hlts.L1_SingleForJet4_Prescl, &hlts.b_L1_SingleForJet4_Prescl);
  t->SetBranchAddress("L1_SingleForJet4_5bx", &hlts.L1_SingleForJet4_5bx, &hlts.b_L1_SingleForJet4_5bx);
  t->SetBranchAddress("L1_SingleJet10", &hlts.L1_SingleJet10, &hlts.b_L1_SingleJet10);
  t->SetBranchAddress("L1_SingleJet10_Prescl", &hlts.L1_SingleJet10_Prescl, &hlts.b_L1_SingleJet10_Prescl);
  t->SetBranchAddress("L1_SingleJet10_5bx", &hlts.L1_SingleJet10_5bx, &hlts.b_L1_SingleJet10_5bx);
  t->SetBranchAddress("L1_SingleJet20", &hlts.L1_SingleJet20, &hlts.b_L1_SingleJet20);
  t->SetBranchAddress("L1_SingleJet20_Prescl", &hlts.L1_SingleJet20_Prescl, &hlts.b_L1_SingleJet20_Prescl);
  t->SetBranchAddress("L1_SingleJet20_5bx", &hlts.L1_SingleJet20_5bx, &hlts.b_L1_SingleJet20_5bx);
  t->SetBranchAddress("L1_SingleJet20_BptxAND", &hlts.L1_SingleJet20_BptxAND, &hlts.b_L1_SingleJet20_BptxAND);
  t->SetBranchAddress("L1_SingleJet20_BptxAND_Prescl", &hlts.L1_SingleJet20_BptxAND_Prescl, &hlts.b_L1_SingleJet20_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleJet20_BptxAND_5bx", &hlts.L1_SingleJet20_BptxAND_5bx, &hlts.b_L1_SingleJet20_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleJet20_NotBptxOR_Ext", &hlts.L1_SingleJet20_NotBptxOR_Ext, &hlts.b_L1_SingleJet20_NotBptxOR_Ext);
  t->SetBranchAddress("L1_SingleJet20_NotBptxOR_Ext_Prescl", &hlts.L1_SingleJet20_NotBptxOR_Ext_Prescl, &hlts.b_L1_SingleJet20_NotBptxOR_Ext_Prescl);
  t->SetBranchAddress("L1_SingleJet20_NotBptxOR_Ext_5bx", &hlts.L1_SingleJet20_NotBptxOR_Ext_5bx, &hlts.b_L1_SingleJet20_NotBptxOR_Ext_5bx);
  t->SetBranchAddress("L1_SingleJet30", &hlts.L1_SingleJet30, &hlts.b_L1_SingleJet30);
  t->SetBranchAddress("L1_SingleJet30_Prescl", &hlts.L1_SingleJet30_Prescl, &hlts.b_L1_SingleJet30_Prescl);
  t->SetBranchAddress("L1_SingleJet30_5bx", &hlts.L1_SingleJet30_5bx, &hlts.b_L1_SingleJet30_5bx);
  t->SetBranchAddress("L1_SingleJet30_BptxAND", &hlts.L1_SingleJet30_BptxAND, &hlts.b_L1_SingleJet30_BptxAND);
  t->SetBranchAddress("L1_SingleJet30_BptxAND_Prescl", &hlts.L1_SingleJet30_BptxAND_Prescl, &hlts.b_L1_SingleJet30_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleJet30_BptxAND_5bx", &hlts.L1_SingleJet30_BptxAND_5bx, &hlts.b_L1_SingleJet30_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleJet40", &hlts.L1_SingleJet40, &hlts.b_L1_SingleJet40);
  t->SetBranchAddress("L1_SingleJet40_Prescl", &hlts.L1_SingleJet40_Prescl, &hlts.b_L1_SingleJet40_Prescl);
  t->SetBranchAddress("L1_SingleJet40_5bx", &hlts.L1_SingleJet40_5bx, &hlts.b_L1_SingleJet40_5bx);
  t->SetBranchAddress("L1_SingleJet40_BptxAND", &hlts.L1_SingleJet40_BptxAND, &hlts.b_L1_SingleJet40_BptxAND);
  t->SetBranchAddress("L1_SingleJet40_BptxAND_Prescl", &hlts.L1_SingleJet40_BptxAND_Prescl, &hlts.b_L1_SingleJet40_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleJet40_BptxAND_5bx", &hlts.L1_SingleJet40_BptxAND_5bx, &hlts.b_L1_SingleJet40_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleJet50", &hlts.L1_SingleJet50, &hlts.b_L1_SingleJet50);
  t->SetBranchAddress("L1_SingleJet50_Prescl", &hlts.L1_SingleJet50_Prescl, &hlts.b_L1_SingleJet50_Prescl);
  t->SetBranchAddress("L1_SingleJet50_5bx", &hlts.L1_SingleJet50_5bx, &hlts.b_L1_SingleJet50_5bx);
  t->SetBranchAddress("L1_SingleJet50_BptxAND", &hlts.L1_SingleJet50_BptxAND, &hlts.b_L1_SingleJet50_BptxAND);
  t->SetBranchAddress("L1_SingleJet50_BptxAND_Prescl", &hlts.L1_SingleJet50_BptxAND_Prescl, &hlts.b_L1_SingleJet50_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleJet50_BptxAND_5bx", &hlts.L1_SingleJet50_BptxAND_5bx, &hlts.b_L1_SingleJet50_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleJet6", &hlts.L1_SingleJet6, &hlts.b_L1_SingleJet6);
  t->SetBranchAddress("L1_SingleJet6_Prescl", &hlts.L1_SingleJet6_Prescl, &hlts.b_L1_SingleJet6_Prescl);
  t->SetBranchAddress("L1_SingleJet6_5bx", &hlts.L1_SingleJet6_5bx, &hlts.b_L1_SingleJet6_5bx);
  t->SetBranchAddress("L1_SingleJet60", &hlts.L1_SingleJet60, &hlts.b_L1_SingleJet60);
  t->SetBranchAddress("L1_SingleJet60_Prescl", &hlts.L1_SingleJet60_Prescl, &hlts.b_L1_SingleJet60_Prescl);
  t->SetBranchAddress("L1_SingleJet60_5bx", &hlts.L1_SingleJet60_5bx, &hlts.b_L1_SingleJet60_5bx);
  t->SetBranchAddress("L1_SingleMu0", &hlts.L1_SingleMu0, &hlts.b_L1_SingleMu0);
  t->SetBranchAddress("L1_SingleMu0_Prescl", &hlts.L1_SingleMu0_Prescl, &hlts.b_L1_SingleMu0_Prescl);
  t->SetBranchAddress("L1_SingleMu0_5bx", &hlts.L1_SingleMu0_5bx, &hlts.b_L1_SingleMu0_5bx);
  t->SetBranchAddress("L1_SingleMu10", &hlts.L1_SingleMu10, &hlts.b_L1_SingleMu10);
  t->SetBranchAddress("L1_SingleMu10_Prescl", &hlts.L1_SingleMu10_Prescl, &hlts.b_L1_SingleMu10_Prescl);
  t->SetBranchAddress("L1_SingleMu10_5bx", &hlts.L1_SingleMu10_5bx, &hlts.b_L1_SingleMu10_5bx);
  t->SetBranchAddress("L1_SingleMu14", &hlts.L1_SingleMu14, &hlts.b_L1_SingleMu14);
  t->SetBranchAddress("L1_SingleMu14_Prescl", &hlts.L1_SingleMu14_Prescl, &hlts.b_L1_SingleMu14_Prescl);
  t->SetBranchAddress("L1_SingleMu14_5bx", &hlts.L1_SingleMu14_5bx, &hlts.b_L1_SingleMu14_5bx);
  t->SetBranchAddress("L1_SingleMu20", &hlts.L1_SingleMu20, &hlts.b_L1_SingleMu20);
  t->SetBranchAddress("L1_SingleMu20_Prescl", &hlts.L1_SingleMu20_Prescl, &hlts.b_L1_SingleMu20_Prescl);
  t->SetBranchAddress("L1_SingleMu20_5bx", &hlts.L1_SingleMu20_5bx, &hlts.b_L1_SingleMu20_5bx);
  t->SetBranchAddress("L1_SingleMu3", &hlts.L1_SingleMu3, &hlts.b_L1_SingleMu3);
  t->SetBranchAddress("L1_SingleMu3_Prescl", &hlts.L1_SingleMu3_Prescl, &hlts.b_L1_SingleMu3_Prescl);
  t->SetBranchAddress("L1_SingleMu3_5bx", &hlts.L1_SingleMu3_5bx, &hlts.b_L1_SingleMu3_5bx);
  t->SetBranchAddress("L1_SingleMu3_BptxAND", &hlts.L1_SingleMu3_BptxAND, &hlts.b_L1_SingleMu3_BptxAND);
  t->SetBranchAddress("L1_SingleMu3_BptxAND_Prescl", &hlts.L1_SingleMu3_BptxAND_Prescl, &hlts.b_L1_SingleMu3_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleMu3_BptxAND_5bx", &hlts.L1_SingleMu3_BptxAND_5bx, &hlts.b_L1_SingleMu3_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleMu5", &hlts.L1_SingleMu5, &hlts.b_L1_SingleMu5);
  t->SetBranchAddress("L1_SingleMu5_Prescl", &hlts.L1_SingleMu5_Prescl, &hlts.b_L1_SingleMu5_Prescl);
  t->SetBranchAddress("L1_SingleMu5_5bx", &hlts.L1_SingleMu5_5bx, &hlts.b_L1_SingleMu5_5bx);
  t->SetBranchAddress("L1_SingleMu7", &hlts.L1_SingleMu7, &hlts.b_L1_SingleMu7);
  t->SetBranchAddress("L1_SingleMu7_Prescl", &hlts.L1_SingleMu7_Prescl, &hlts.b_L1_SingleMu7_Prescl);
  t->SetBranchAddress("L1_SingleMu7_5bx", &hlts.L1_SingleMu7_5bx, &hlts.b_L1_SingleMu7_5bx);
  t->SetBranchAddress("L1_SingleMuBeamHalo", &hlts.L1_SingleMuBeamHalo, &hlts.b_L1_SingleMuBeamHalo);
  t->SetBranchAddress("L1_SingleMuBeamHalo_Prescl", &hlts.L1_SingleMuBeamHalo_Prescl, &hlts.b_L1_SingleMuBeamHalo_Prescl);
  t->SetBranchAddress("L1_SingleMuBeamHalo_5bx", &hlts.L1_SingleMuBeamHalo_5bx, &hlts.b_L1_SingleMuBeamHalo_5bx);
  t->SetBranchAddress("L1_SingleMuOpen", &hlts.L1_SingleMuOpen, &hlts.b_L1_SingleMuOpen);
  t->SetBranchAddress("L1_SingleMuOpen_Prescl", &hlts.L1_SingleMuOpen_Prescl, &hlts.b_L1_SingleMuOpen_Prescl);
  t->SetBranchAddress("L1_SingleMuOpen_5bx", &hlts.L1_SingleMuOpen_5bx, &hlts.b_L1_SingleMuOpen_5bx);
  t->SetBranchAddress("L1_SingleTauJet50", &hlts.L1_SingleTauJet50, &hlts.b_L1_SingleTauJet50);
  t->SetBranchAddress("L1_SingleTauJet50_Prescl", &hlts.L1_SingleTauJet50_Prescl, &hlts.b_L1_SingleTauJet50_Prescl);
  t->SetBranchAddress("L1_SingleTauJet50_5bx", &hlts.L1_SingleTauJet50_5bx, &hlts.b_L1_SingleTauJet50_5bx);
  t->SetBranchAddress("L1_TripleJet14", &hlts.L1_TripleJet14, &hlts.b_L1_TripleJet14);
  t->SetBranchAddress("L1_TripleJet14_Prescl", &hlts.L1_TripleJet14_Prescl, &hlts.b_L1_TripleJet14_Prescl);
  t->SetBranchAddress("L1_TripleJet14_5bx", &hlts.L1_TripleJet14_5bx, &hlts.b_L1_TripleJet14_5bx);
  t->SetBranchAddress("L1_ZdcCaloMinus", &hlts.L1_ZdcCaloMinus, &hlts.b_L1_ZdcCaloMinus);
  t->SetBranchAddress("L1_ZdcCaloMinus_Prescl", &hlts.L1_ZdcCaloMinus_Prescl, &hlts.b_L1_ZdcCaloMinus_Prescl);
  t->SetBranchAddress("L1_ZdcCaloMinus_5bx", &hlts.L1_ZdcCaloMinus_5bx, &hlts.b_L1_ZdcCaloMinus_5bx);
  t->SetBranchAddress("L1_ZdcCaloMinus_BptxAND", &hlts.L1_ZdcCaloMinus_BptxAND, &hlts.b_L1_ZdcCaloMinus_BptxAND);
  t->SetBranchAddress("L1_ZdcCaloMinus_BptxAND_Prescl", &hlts.L1_ZdcCaloMinus_BptxAND_Prescl, &hlts.b_L1_ZdcCaloMinus_BptxAND_Prescl);
  t->SetBranchAddress("L1_ZdcCaloMinus_BptxAND_5bx", &hlts.L1_ZdcCaloMinus_BptxAND_5bx, &hlts.b_L1_ZdcCaloMinus_BptxAND_5bx);
  t->SetBranchAddress("L1_ZdcCaloPlus", &hlts.L1_ZdcCaloPlus, &hlts.b_L1_ZdcCaloPlus);
  t->SetBranchAddress("L1_ZdcCaloPlus_Prescl", &hlts.L1_ZdcCaloPlus_Prescl, &hlts.b_L1_ZdcCaloPlus_Prescl);
  t->SetBranchAddress("L1_ZdcCaloPlus_5bx", &hlts.L1_ZdcCaloPlus_5bx, &hlts.b_L1_ZdcCaloPlus_5bx);
  t->SetBranchAddress("L1_ZdcCaloPlus_BptxAND", &hlts.L1_ZdcCaloPlus_BptxAND, &hlts.b_L1_ZdcCaloPlus_BptxAND);
  t->SetBranchAddress("L1_ZdcCaloPlus_BptxAND_Prescl", &hlts.L1_ZdcCaloPlus_BptxAND_Prescl, &hlts.b_L1_ZdcCaloPlus_BptxAND_Prescl);
  t->SetBranchAddress("L1_ZdcCaloPlus_BptxAND_5bx", &hlts.L1_ZdcCaloPlus_BptxAND_5bx, &hlts.b_L1_ZdcCaloPlus_BptxAND_5bx);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus", &hlts.L1_ZdcCaloPlus_ZdcCaloMinus, &hlts.b_L1_ZdcCaloPlus_ZdcCaloMinus);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus_Prescl", &hlts.L1_ZdcCaloPlus_ZdcCaloMinus_Prescl, &hlts.b_L1_ZdcCaloPlus_ZdcCaloMinus_Prescl);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus_5bx", &hlts.L1_ZdcCaloPlus_ZdcCaloMinus_5bx, &hlts.b_L1_ZdcCaloPlus_ZdcCaloMinus_5bx);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND", &hlts.L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND, &hlts.b_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_Prescl", &hlts.L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_Prescl, &hlts.b_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_Prescl);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_5bx", &hlts.L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_5bx, &hlts.b_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_5bx);
  t->SetBranchAddress("L1_ZdcScintLooseVertex", &hlts.L1_ZdcScintLooseVertex, &hlts.b_L1_ZdcScintLooseVertex);
  t->SetBranchAddress("L1_ZdcScintLooseVertex_Prescl", &hlts.L1_ZdcScintLooseVertex_Prescl, &hlts.b_L1_ZdcScintLooseVertex_Prescl);
  t->SetBranchAddress("L1_ZdcScintLooseVertex_5bx", &hlts.L1_ZdcScintLooseVertex_5bx, &hlts.b_L1_ZdcScintLooseVertex_5bx);
  t->SetBranchAddress("L1_ZdcScintLooseVertex_BptxAND", &hlts.L1_ZdcScintLooseVertex_BptxAND, &hlts.b_L1_ZdcScintLooseVertex_BptxAND);
  t->SetBranchAddress("L1_ZdcScintLooseVertex_BptxAND_Prescl", &hlts.L1_ZdcScintLooseVertex_BptxAND_Prescl, &hlts.b_L1_ZdcScintLooseVertex_BptxAND_Prescl);
  t->SetBranchAddress("L1_ZdcScintLooseVertex_BptxAND_5bx", &hlts.L1_ZdcScintLooseVertex_BptxAND_5bx, &hlts.b_L1_ZdcScintLooseVertex_BptxAND_5bx);
  t->SetBranchAddress("L1_ZdcScintMinus", &hlts.L1_ZdcScintMinus, &hlts.b_L1_ZdcScintMinus);
  t->SetBranchAddress("L1_ZdcScintMinus_Prescl", &hlts.L1_ZdcScintMinus_Prescl, &hlts.b_L1_ZdcScintMinus_Prescl);
  t->SetBranchAddress("L1_ZdcScintMinus_5bx", &hlts.L1_ZdcScintMinus_5bx, &hlts.b_L1_ZdcScintMinus_5bx);
  t->SetBranchAddress("L1_ZdcScintPlus", &hlts.L1_ZdcScintPlus, &hlts.b_L1_ZdcScintPlus);
  t->SetBranchAddress("L1_ZdcScintPlus_Prescl", &hlts.L1_ZdcScintPlus_Prescl, &hlts.b_L1_ZdcScintPlus_Prescl);
  t->SetBranchAddress("L1_ZdcScintPlus_5bx", &hlts.L1_ZdcScintPlus_5bx, &hlts.b_L1_ZdcScintPlus_5bx);
  t->SetBranchAddress("L1_ZdcScintTightVertex", &hlts.L1_ZdcScintTightVertex, &hlts.b_L1_ZdcScintTightVertex);
  t->SetBranchAddress("L1_ZdcScintTightVertex_Prescl", &hlts.L1_ZdcScintTightVertex_Prescl, &hlts.b_L1_ZdcScintTightVertex_Prescl);
  t->SetBranchAddress("L1_ZdcScintTightVertex_5bx", &hlts.L1_ZdcScintTightVertex_5bx, &hlts.b_L1_ZdcScintTightVertex_5bx);
  t->SetBranchAddress("L1_ZdcScintTightVertex_BptxAND", &hlts.L1_ZdcScintTightVertex_BptxAND, &hlts.b_L1_ZdcScintTightVertex_BptxAND);
  t->SetBranchAddress("L1_ZdcScintTightVertex_BptxAND_Prescl", &hlts.L1_ZdcScintTightVertex_BptxAND_Prescl, &hlts.b_L1_ZdcScintTightVertex_BptxAND_Prescl);
  t->SetBranchAddress("L1_ZdcScintTightVertex_BptxAND_5bx", &hlts.L1_ZdcScintTightVertex_BptxAND_5bx, &hlts.b_L1_ZdcScintTightVertex_BptxAND_5bx);
  t->SetBranchAddress("L1_ZeroBias_Ext", &hlts.L1_ZeroBias_Ext, &hlts.b_L1_ZeroBias_Ext);
  t->SetBranchAddress("L1_ZeroBias_Ext_Prescl", &hlts.L1_ZeroBias_Ext_Prescl, &hlts.b_L1_ZeroBias_Ext_Prescl);
  t->SetBranchAddress("L1_ZeroBias_Ext_5bx", &hlts.L1_ZeroBias_Ext_5bx, &hlts.b_L1_ZeroBias_Ext_5bx);
  t->SetBranchAddress("L1Tech_BPTX_minus.v0", &hlts.L1Tech_BPTX_minus_v0, &hlts.b_L1Tech_BPTX_minus_v0);
  t->SetBranchAddress("L1Tech_BPTX_minus.v0_Prescl", &hlts.L1Tech_BPTX_minus_v0_Prescl, &hlts.b_L1Tech_BPTX_minus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_minus.v0_5bx", &hlts.L1Tech_BPTX_minus_v0_5bx, &hlts.b_L1Tech_BPTX_minus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_minus_AND_not_plus.v0", &hlts.L1Tech_BPTX_minus_AND_not_plus_v0, &hlts.b_L1Tech_BPTX_minus_AND_not_plus_v0);
  t->SetBranchAddress("L1Tech_BPTX_minus_AND_not_plus.v0_Prescl", &hlts.L1Tech_BPTX_minus_AND_not_plus_v0_Prescl, &hlts.b_L1Tech_BPTX_minus_AND_not_plus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_minus_AND_not_plus.v0_5bx", &hlts.L1Tech_BPTX_minus_AND_not_plus_v0_5bx, &hlts.b_L1Tech_BPTX_minus_AND_not_plus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_plus.v0", &hlts.L1Tech_BPTX_plus_v0, &hlts.b_L1Tech_BPTX_plus_v0);
  t->SetBranchAddress("L1Tech_BPTX_plus.v0_Prescl", &hlts.L1Tech_BPTX_plus_v0_Prescl, &hlts.b_L1Tech_BPTX_plus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_plus.v0_5bx", &hlts.L1Tech_BPTX_plus_v0_5bx, &hlts.b_L1Tech_BPTX_plus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_NOT_minus.v0", &hlts.L1Tech_BPTX_plus_AND_NOT_minus_v0, &hlts.b_L1Tech_BPTX_plus_AND_NOT_minus_v0);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_NOT_minus.v0_Prescl", &hlts.L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl, &hlts.b_L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_NOT_minus.v0_5bx", &hlts.L1Tech_BPTX_plus_AND_NOT_minus_v0_5bx, &hlts.b_L1Tech_BPTX_plus_AND_NOT_minus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus.v0", &hlts.L1Tech_BPTX_plus_AND_minus_v0, &hlts.b_L1Tech_BPTX_plus_AND_minus_v0);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus.v0_Prescl", &hlts.L1Tech_BPTX_plus_AND_minus_v0_Prescl, &hlts.b_L1Tech_BPTX_plus_AND_minus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus.v0_5bx", &hlts.L1Tech_BPTX_plus_AND_minus_v0_5bx, &hlts.b_L1Tech_BPTX_plus_AND_minus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus_instance1.v0", &hlts.L1Tech_BPTX_plus_AND_minus_instance1_v0, &hlts.b_L1Tech_BPTX_plus_AND_minus_instance1_v0);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus_instance1.v0_Prescl", &hlts.L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl, &hlts.b_L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus_instance1.v0_5bx", &hlts.L1Tech_BPTX_plus_AND_minus_instance1_v0_5bx, &hlts.b_L1Tech_BPTX_plus_AND_minus_instance1_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_plus_OR_minus.v0", &hlts.L1Tech_BPTX_plus_OR_minus_v0, &hlts.b_L1Tech_BPTX_plus_OR_minus_v0);
  t->SetBranchAddress("L1Tech_BPTX_plus_OR_minus.v0_Prescl", &hlts.L1Tech_BPTX_plus_OR_minus_v0_Prescl, &hlts.b_L1Tech_BPTX_plus_OR_minus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_plus_OR_minus.v0_5bx", &hlts.L1Tech_BPTX_plus_OR_minus_v0_5bx, &hlts.b_L1Tech_BPTX_plus_OR_minus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_quiet.v0", &hlts.L1Tech_BPTX_quiet_v0, &hlts.b_L1Tech_BPTX_quiet_v0);
  t->SetBranchAddress("L1Tech_BPTX_quiet.v0_Prescl", &hlts.L1Tech_BPTX_quiet_v0_Prescl, &hlts.b_L1Tech_BPTX_quiet_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_quiet.v0_5bx", &hlts.L1Tech_BPTX_quiet_v0_5bx, &hlts.b_L1Tech_BPTX_quiet_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_HighMultiplicity.v0", &hlts.L1Tech_BSC_HighMultiplicity_v0, &hlts.b_L1Tech_BSC_HighMultiplicity_v0);
  t->SetBranchAddress("L1Tech_BSC_HighMultiplicity.v0_Prescl", &hlts.L1Tech_BSC_HighMultiplicity_v0_Prescl, &hlts.b_L1Tech_BSC_HighMultiplicity_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_HighMultiplicity.v0_5bx", &hlts.L1Tech_BSC_HighMultiplicity_v0_5bx, &hlts.b_L1Tech_BSC_HighMultiplicity_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_inner.v0", &hlts.L1Tech_BSC_halo_beam1_inner_v0, &hlts.b_L1Tech_BSC_halo_beam1_inner_v0);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_inner.v0_Prescl", &hlts.L1Tech_BSC_halo_beam1_inner_v0_Prescl, &hlts.b_L1Tech_BSC_halo_beam1_inner_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_inner.v0_5bx", &hlts.L1Tech_BSC_halo_beam1_inner_v0_5bx, &hlts.b_L1Tech_BSC_halo_beam1_inner_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_outer.v0", &hlts.L1Tech_BSC_halo_beam1_outer_v0, &hlts.b_L1Tech_BSC_halo_beam1_outer_v0);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_outer.v0_Prescl", &hlts.L1Tech_BSC_halo_beam1_outer_v0_Prescl, &hlts.b_L1Tech_BSC_halo_beam1_outer_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_outer.v0_5bx", &hlts.L1Tech_BSC_halo_beam1_outer_v0_5bx, &hlts.b_L1Tech_BSC_halo_beam1_outer_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_inner.v0", &hlts.L1Tech_BSC_halo_beam2_inner_v0, &hlts.b_L1Tech_BSC_halo_beam2_inner_v0);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_inner.v0_Prescl", &hlts.L1Tech_BSC_halo_beam2_inner_v0_Prescl, &hlts.b_L1Tech_BSC_halo_beam2_inner_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_inner.v0_5bx", &hlts.L1Tech_BSC_halo_beam2_inner_v0_5bx, &hlts.b_L1Tech_BSC_halo_beam2_inner_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_outer.v0", &hlts.L1Tech_BSC_halo_beam2_outer_v0, &hlts.b_L1Tech_BSC_halo_beam2_outer_v0);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_outer.v0_Prescl", &hlts.L1Tech_BSC_halo_beam2_outer_v0_Prescl, &hlts.b_L1Tech_BSC_halo_beam2_outer_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_outer.v0_5bx", &hlts.L1Tech_BSC_halo_beam2_outer_v0_5bx, &hlts.b_L1Tech_BSC_halo_beam2_outer_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_minBias_OR.v0", &hlts.L1Tech_BSC_minBias_OR_v0, &hlts.b_L1Tech_BSC_minBias_OR_v0);
  t->SetBranchAddress("L1Tech_BSC_minBias_OR.v0_Prescl", &hlts.L1Tech_BSC_minBias_OR_v0_Prescl, &hlts.b_L1Tech_BSC_minBias_OR_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_minBias_OR.v0_5bx", &hlts.L1Tech_BSC_minBias_OR_v0_5bx, &hlts.b_L1Tech_BSC_minBias_OR_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold1.v0", &hlts.L1Tech_BSC_minBias_inner_threshold1_v0, &hlts.b_L1Tech_BSC_minBias_inner_threshold1_v0);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold1.v0_Prescl", &hlts.L1Tech_BSC_minBias_inner_threshold1_v0_Prescl, &hlts.b_L1Tech_BSC_minBias_inner_threshold1_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold1.v0_5bx", &hlts.L1Tech_BSC_minBias_inner_threshold1_v0_5bx, &hlts.b_L1Tech_BSC_minBias_inner_threshold1_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold2.v0", &hlts.L1Tech_BSC_minBias_inner_threshold2_v0, &hlts.b_L1Tech_BSC_minBias_inner_threshold2_v0);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold2.v0_Prescl", &hlts.L1Tech_BSC_minBias_inner_threshold2_v0_Prescl, &hlts.b_L1Tech_BSC_minBias_inner_threshold2_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold2.v0_5bx", &hlts.L1Tech_BSC_minBias_inner_threshold2_v0_5bx, &hlts.b_L1Tech_BSC_minBias_inner_threshold2_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold1.v0", &hlts.L1Tech_BSC_minBias_threshold1_v0, &hlts.b_L1Tech_BSC_minBias_threshold1_v0);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold1.v0_Prescl", &hlts.L1Tech_BSC_minBias_threshold1_v0_Prescl, &hlts.b_L1Tech_BSC_minBias_threshold1_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold1.v0_5bx", &hlts.L1Tech_BSC_minBias_threshold1_v0_5bx, &hlts.b_L1Tech_BSC_minBias_threshold1_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold2.v0", &hlts.L1Tech_BSC_minBias_threshold2_v0, &hlts.b_L1Tech_BSC_minBias_threshold2_v0);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold2.v0_Prescl", &hlts.L1Tech_BSC_minBias_threshold2_v0_Prescl, &hlts.b_L1Tech_BSC_minBias_threshold2_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold2.v0_5bx", &hlts.L1Tech_BSC_minBias_threshold2_v0_5bx, &hlts.b_L1Tech_BSC_minBias_threshold2_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_splash_beam1.v0", &hlts.L1Tech_BSC_splash_beam1_v0, &hlts.b_L1Tech_BSC_splash_beam1_v0);
  t->SetBranchAddress("L1Tech_BSC_splash_beam1.v0_Prescl", &hlts.L1Tech_BSC_splash_beam1_v0_Prescl, &hlts.b_L1Tech_BSC_splash_beam1_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_splash_beam1.v0_5bx", &hlts.L1Tech_BSC_splash_beam1_v0_5bx, &hlts.b_L1Tech_BSC_splash_beam1_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_splash_beam2.v0", &hlts.L1Tech_BSC_splash_beam2_v0, &hlts.b_L1Tech_BSC_splash_beam2_v0);
  t->SetBranchAddress("L1Tech_BSC_splash_beam2.v0_Prescl", &hlts.L1Tech_BSC_splash_beam2_v0_Prescl, &hlts.b_L1Tech_BSC_splash_beam2_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_splash_beam2.v0_5bx", &hlts.L1Tech_BSC_splash_beam2_v0_5bx, &hlts.b_L1Tech_BSC_splash_beam2_v0_5bx);
  t->SetBranchAddress("L1Tech_CASTOR_HaloMuon.v0", &hlts.L1Tech_CASTOR_HaloMuon_v0, &hlts.b_L1Tech_CASTOR_HaloMuon_v0);
  t->SetBranchAddress("L1Tech_CASTOR_HaloMuon.v0_Prescl", &hlts.L1Tech_CASTOR_HaloMuon_v0_Prescl, &hlts.b_L1Tech_CASTOR_HaloMuon_v0_Prescl);
  t->SetBranchAddress("L1Tech_CASTOR_HaloMuon.v0_5bx", &hlts.L1Tech_CASTOR_HaloMuon_v0_5bx, &hlts.b_L1Tech_CASTOR_HaloMuon_v0_5bx);
  t->SetBranchAddress("L1Tech_HCAL_HBHE_totalOR.v0", &hlts.L1Tech_HCAL_HBHE_totalOR_v0, &hlts.b_L1Tech_HCAL_HBHE_totalOR_v0);
  t->SetBranchAddress("L1Tech_HCAL_HBHE_totalOR.v0_Prescl", &hlts.L1Tech_HCAL_HBHE_totalOR_v0_Prescl, &hlts.b_L1Tech_HCAL_HBHE_totalOR_v0_Prescl);
  t->SetBranchAddress("L1Tech_HCAL_HBHE_totalOR.v0_5bx", &hlts.L1Tech_HCAL_HBHE_totalOR_v0_5bx, &hlts.b_L1Tech_HCAL_HBHE_totalOR_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RB0_Cosmics.v0", &hlts.L1Tech_RPC_TTU_RB0_Cosmics_v0, &hlts.b_L1Tech_RPC_TTU_RB0_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RB0_Cosmics.v0_Prescl", &hlts.L1Tech_RPC_TTU_RB0_Cosmics_v0_Prescl, &hlts.b_L1Tech_RPC_TTU_RB0_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RB0_Cosmics.v0_5bx", &hlts.L1Tech_RPC_TTU_RB0_Cosmics_v0_5bx, &hlts.b_L1Tech_RPC_TTU_RB0_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus1_Cosmics.v0", &hlts.L1Tech_RPC_TTU_RBminus1_Cosmics_v0, &hlts.b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus1_Cosmics.v0_Prescl", &hlts.L1Tech_RPC_TTU_RBminus1_Cosmics_v0_Prescl, &hlts.b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus1_Cosmics.v0_5bx", &hlts.L1Tech_RPC_TTU_RBminus1_Cosmics_v0_5bx, &hlts.b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus2_Cosmics.v0", &hlts.L1Tech_RPC_TTU_RBminus2_Cosmics_v0, &hlts.b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus2_Cosmics.v0_Prescl", &hlts.L1Tech_RPC_TTU_RBminus2_Cosmics_v0_Prescl, &hlts.b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus2_Cosmics.v0_5bx", &hlts.L1Tech_RPC_TTU_RBminus2_Cosmics_v0_5bx, &hlts.b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus1_Cosmics.v0", &hlts.L1Tech_RPC_TTU_RBplus1_Cosmics_v0, &hlts.b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus1_Cosmics.v0_Prescl", &hlts.L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl, &hlts.b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus1_Cosmics.v0_5bx", &hlts.L1Tech_RPC_TTU_RBplus1_Cosmics_v0_5bx, &hlts.b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus2_Cosmics.v0", &hlts.L1Tech_RPC_TTU_RBplus2_Cosmics_v0, &hlts.b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus2_Cosmics.v0_Prescl", &hlts.L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl, &hlts.b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus2_Cosmics.v0_5bx", &hlts.L1Tech_RPC_TTU_RBplus2_Cosmics_v0_5bx, &hlts.b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBst1_collisions.v0", &hlts.L1Tech_RPC_TTU_RBst1_collisions_v0, &hlts.b_L1Tech_RPC_TTU_RBst1_collisions_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBst1_collisions.v0_Prescl", &hlts.L1Tech_RPC_TTU_RBst1_collisions_v0_Prescl, &hlts.b_L1Tech_RPC_TTU_RBst1_collisions_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBst1_collisions.v0_5bx", &hlts.L1Tech_RPC_TTU_RBst1_collisions_v0_5bx, &hlts.b_L1Tech_RPC_TTU_RBst1_collisions_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_barrel_Cosmics.v0", &hlts.L1Tech_RPC_TTU_barrel_Cosmics_v0, &hlts.b_L1Tech_RPC_TTU_barrel_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_barrel_Cosmics.v0_Prescl", &hlts.L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl, &hlts.b_L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_barrel_Cosmics.v0_5bx", &hlts.L1Tech_RPC_TTU_barrel_Cosmics_v0_5bx, &hlts.b_L1Tech_RPC_TTU_barrel_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_pointing_Cosmics.v0", &hlts.L1Tech_RPC_TTU_pointing_Cosmics_v0, &hlts.b_L1Tech_RPC_TTU_pointing_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_pointing_Cosmics.v0_Prescl", &hlts.L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl, &hlts.b_L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_pointing_Cosmics.v0_5bx", &hlts.L1Tech_RPC_TTU_pointing_Cosmics_v0_5bx, &hlts.b_L1Tech_RPC_TTU_pointing_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_ZDC_Scint_loose_vertex.v0", &hlts.L1Tech_ZDC_Scint_loose_vertex_v0, &hlts.b_L1Tech_ZDC_Scint_loose_vertex_v0);
  t->SetBranchAddress("L1Tech_ZDC_Scint_loose_vertex.v0_Prescl", &hlts.L1Tech_ZDC_Scint_loose_vertex_v0_Prescl, &hlts.b_L1Tech_ZDC_Scint_loose_vertex_v0_Prescl);
  t->SetBranchAddress("L1Tech_ZDC_Scint_loose_vertex.v0_5bx", &hlts.L1Tech_ZDC_Scint_loose_vertex_v0_5bx, &hlts.b_L1Tech_ZDC_Scint_loose_vertex_v0_5bx);
  t->SetBranchAddress("L1Tech_ZDC_Scint_minus.v0", &hlts.L1Tech_ZDC_Scint_minus_v0, &hlts.b_L1Tech_ZDC_Scint_minus_v0);
  t->SetBranchAddress("L1Tech_ZDC_Scint_minus.v0_Prescl", &hlts.L1Tech_ZDC_Scint_minus_v0_Prescl, &hlts.b_L1Tech_ZDC_Scint_minus_v0_Prescl);
  t->SetBranchAddress("L1Tech_ZDC_Scint_minus.v0_5bx", &hlts.L1Tech_ZDC_Scint_minus_v0_5bx, &hlts.b_L1Tech_ZDC_Scint_minus_v0_5bx);
  t->SetBranchAddress("L1Tech_ZDC_Scint_plus.v0", &hlts.L1Tech_ZDC_Scint_plus_v0, &hlts.b_L1Tech_ZDC_Scint_plus_v0);
  t->SetBranchAddress("L1Tech_ZDC_Scint_plus.v0_Prescl", &hlts.L1Tech_ZDC_Scint_plus_v0_Prescl, &hlts.b_L1Tech_ZDC_Scint_plus_v0_Prescl);
  t->SetBranchAddress("L1Tech_ZDC_Scint_plus.v0_5bx", &hlts.L1Tech_ZDC_Scint_plus_v0_5bx, &hlts.b_L1Tech_ZDC_Scint_plus_v0_5bx);
  t->SetBranchAddress("L1Tech_ZDC_Scint_tight_vertex.v0", &hlts.L1Tech_ZDC_Scint_tight_vertex_v0, &hlts.b_L1Tech_ZDC_Scint_tight_vertex_v0);
  t->SetBranchAddress("L1Tech_ZDC_Scint_tight_vertex.v0_Prescl", &hlts.L1Tech_ZDC_Scint_tight_vertex_v0_Prescl, &hlts.b_L1Tech_ZDC_Scint_tight_vertex_v0_Prescl);
  t->SetBranchAddress("L1Tech_ZDC_Scint_tight_vertex.v0_5bx", &hlts.L1Tech_ZDC_Scint_tight_vertex_v0_5bx, &hlts.b_L1Tech_ZDC_Scint_tight_vertex_v0_5bx);
 
}
