#include "commonSetup.h"

class Skims
{
  public:

  Skims(){};
  ~Skims(){};

   Int_t           NohBJetL2;
   Float_t         ohBJetL2Energy[maxEntry];   //[NohBJetL2]
   Float_t         ohBJetL2Et[maxEntry];   //[NohBJetL2]
   Float_t         ohBJetL2Pt[maxEntry];   //[NohBJetL2]
   Float_t         ohBJetL2Eta[maxEntry];   //[NohBJetL2]
   Float_t         ohBJetL2Phi[maxEntry];   //[NohBJetL2]
   Int_t           NohBJetL2Corrected;
   Float_t         ohBJetL2CorrectedEnergy[maxEntry];   //[NohBJetL2Corrected]
   Float_t         ohBJetL2CorrectedEt[maxEntry];   //[NohBJetL2Corrected]
   Float_t         ohBJetL2CorrectedPt[maxEntry];   //[NohBJetL2Corrected]
   Float_t         ohBJetL2CorrectedEta[maxEntry];   //[NohBJetL2Corrected]
   Float_t         ohBJetL2CorrectedPhi[maxEntry];   //[NohBJetL2Corrected]
   Float_t         ohBJetIPL25Tag[maxEntry];   //[NohBJetL2]
   Float_t         ohBJetIPL3Tag[maxEntry];   //[NohBJetL2]
   Float_t         ohBJetIPLooseL25Tag[maxEntry];   //[NohBJetL2]
   Float_t         ohBJetIPLooseL3Tag[maxEntry];   //[NohBJetL2]
   Int_t           ohBJetMuL25Tag[maxEntry];   //[NohBJetL2]
   Float_t         ohBJetMuL3Tag[maxEntry];   //[NohBJetL2]
   Int_t           ohBJetPerfL25Tag[maxEntry];   //[NohBJetL2]
   Int_t           ohBJetPerfL3Tag[maxEntry];   //[NohBJetL2]
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
   Float_t         recoElecPt[maxEntry];   //[NrecoElec]
   Float_t         recoElecPhi[maxEntry];   //[NrecoElec]
   Float_t         recoElecEta[maxEntry];   //[NrecoElec]
   Float_t         recoElecEt[maxEntry];   //[NrecoElec]
   Float_t         recoElecE[maxEntry];   //[NrecoElec]
   Int_t           recoElecEleID[maxEntry];   //[NrecoElec]
   Int_t           NrecoPhot;
   Float_t         recoPhotPt[maxEntry];   //[NrecoPhot]
   Float_t         recoPhotPhi[maxEntry];   //[NrecoPhot]
   Float_t         recoPhotEta[maxEntry];   //[NrecoPhot]
   Float_t         recoPhotEt[maxEntry];   //[NrecoPhot]
   Float_t         recoPhotE[maxEntry];   //[NrecoPhot]
   Int_t           NrecoSC;
   Float_t         recoSCPt[maxEntry];   //[NrecoSC]
   Float_t         recoSCPhi[maxEntry];   //[NrecoSC]
   Float_t         recoSCEta[maxEntry];   //[NrecoSC]
   Float_t         recoSCEt[maxEntry];   //[NrecoSC]
   Float_t         recoSCE[maxEntry];   //[NrecoSC]
   Int_t           NohPhot;
   Float_t         ohPhotEt[maxEntry];   //[NohPhot]
   Float_t         ohPhotEta[maxEntry];   //[NohPhot]
   Float_t         ohPhotPhi[maxEntry];   //[NohPhot]
   Float_t         ohPhotEiso[maxEntry];   //[NohPhot]
   Float_t         ohPhotHiso[maxEntry];   //[NohPhot]
   Float_t         ohPhotTiso[maxEntry];   //[NohPhot]
   Int_t           ohPhotL1iso[maxEntry];   //[NohPhot]
   Float_t         ohPhotClusShap[maxEntry];   //[NohPhot]
   Int_t           NL1IsolEm;
   Float_t         L1IsolEmEt[maxEntry];   //[NL1IsolEm]
   Float_t         L1IsolEmE[maxEntry];   //[NL1IsolEm]
   Float_t         L1IsolEmEta[maxEntry];   //[NL1IsolEm]
   Float_t         L1IsolEmPhi[maxEntry];   //[NL1IsolEm]
   Int_t           NL1NIsolEm;
   Float_t         L1NIsolEmEt[maxEntry];   //[NL1NIsolEm]
   Float_t         L1NIsolEmE[maxEntry];   //[NL1NIsolEm]
   Float_t         L1NIsolEmEta[maxEntry];   //[NL1NIsolEm]
   Float_t         L1NIsolEmPhi[maxEntry];   //[NL1NIsolEm]
   Int_t           NL1Mu;
   Float_t         L1MuPt[maxEntry];   //[NL1Mu]
   Float_t         L1MuE[maxEntry];   //[NL1Mu]
   Float_t         L1MuEta[maxEntry];   //[NL1Mu]
   Float_t         L1MuPhi[maxEntry];   //[NL1Mu]
   Int_t           L1MuIsol[maxEntry];   //[NL1Mu]
   Int_t           L1MuMip[maxEntry];   //[NL1Mu]
   Int_t           L1MuFor[maxEntry];   //[NL1Mu]
   Int_t           L1MuRPC[maxEntry];   //[NL1Mu]
   Int_t           L1MuQal[maxEntry];   //[NL1Mu]
   Int_t           NL1CenJet;
   Float_t         L1CenJetEt[maxEntry];   //[NL1CenJet]
   Float_t         L1CenJetE[maxEntry];   //[NL1CenJet]
   Float_t         L1CenJetEta[maxEntry];   //[NL1CenJet]
   Float_t         L1CenJetPhi[maxEntry];   //[NL1CenJet]
   Int_t           NL1ForJet;
   Float_t         L1ForJetEt[maxEntry];   //[NL1ForJet]
   Float_t         L1ForJetE[maxEntry];   //[NL1ForJet]
   Float_t         L1ForJetEta[maxEntry];   //[NL1ForJet]
   Float_t         L1ForJetPhi[maxEntry];   //[NL1ForJet]
   Int_t           NL1Tau;
   Float_t         L1TauEt[maxEntry];   //[NL1Tau]
   Float_t         L1TauE[maxEntry];   //[NL1Tau]
   Float_t         L1TauEta[maxEntry];   //[NL1Tau]
   Float_t         L1TauPhi[maxEntry];   //[NL1Tau]
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
   Int_t           reco_extra;
   Int_t           reco_extra_Prescl;
   Int_t           reco_extra_jet;
   Int_t           reco_extra_jet_Prescl;
   Int_t           pat_step;
   Int_t           pat_step_Prescl;
   Int_t           ana_step;
   Int_t           ana_step_Prescl;
   Int_t           phltJetHI;
   Int_t           phltJetHI_Prescl;

   Int_t           phfCoincFilter;
   Int_t           ppurityFractionFilter;

   Int_t           pcollisionEventSelection;
   Int_t           pcollisionEventSelection_Prescl;
   Int_t           phbheReflagNewTimeEnv;
   Int_t           phbheReflagNewTimeEnv_Prescl;
   Int_t           phcalTimingFilter;
   Int_t           phcalTimingFilter_Prescl;
   Int_t           pHBHENoiseFilter;
   Int_t           pHBHENoiseFilter_Prescl;
   Int_t           phiEcalRecHitSpikeFilter;
   Int_t           phiEcalRecHitSpikeFilter_Prescl;
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
   TBranch        *b_reco_extra;   //!
   TBranch        *b_reco_extra_Prescl;   //!
   TBranch        *b_reco_extra_jet;   //!
   TBranch        *b_reco_extra_jet_Prescl;   //!
   TBranch        *b_pat_step;   //!
   TBranch        *b_pat_step_Prescl;   //!
   TBranch        *b_ana_step;   //!
   TBranch        *b_ana_step_Prescl;   //!
   TBranch        *b_phltJetHI;   //!
   TBranch        *b_phltJetHI_Prescl;   //!
   TBranch        *b_phfCoincFilter;
   TBranch        *b_ppurityFractionFilter;
   TBranch        *b_pcollisionEventSelection;   //!
   TBranch        *b_pcollisionEventSelection_Prescl;   //!
   TBranch        *b_phbheReflagNewTimeEnv;   //!
   TBranch        *b_phbheReflagNewTimeEnv_Prescl;   //!
   TBranch        *b_phcalTimingFilter;   //!
   TBranch        *b_phcalTimingFilter_Prescl;   //!
   TBranch        *b_pHBHENoiseFilter;   //!
   TBranch        *b_pHBHENoiseFilter_Prescl;   //!
   TBranch        *b_phiEcalRecHitSpikeFilter;   //!
   TBranch        *b_phiEcalRecHitSpikeFilter_Prescl;   //!
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

void setupSkimTree(TTree *t, Skims &skims)
{
  t->SetBranchAddress("NohBJetL2", &skims.NohBJetL2, &skims.b_NohBJetL2);
  t->SetBranchAddress("ohBJetL2Energy", &skims.ohBJetL2Energy, &skims.b_ohBJetL2Energy);
  t->SetBranchAddress("ohBJetL2Et", &skims.ohBJetL2Et, &skims.b_ohBJetL2Et);
  t->SetBranchAddress("ohBJetL2Pt", &skims.ohBJetL2Pt, &skims.b_ohBJetL2Pt);
  t->SetBranchAddress("ohBJetL2Eta", &skims.ohBJetL2Eta, &skims.b_ohBJetL2Eta);
  t->SetBranchAddress("ohBJetL2Phi", &skims.ohBJetL2Phi, &skims.b_ohBJetL2Phi);
  t->SetBranchAddress("NohBJetL2Corrected", &skims.NohBJetL2Corrected, &skims.b_NohBJetL2Corrected);
  t->SetBranchAddress("ohBJetL2CorrectedEnergy", &skims.ohBJetL2CorrectedEnergy, &skims.b_ohBJetL2CorrectedEnergy);
  t->SetBranchAddress("ohBJetL2CorrectedEt", &skims.ohBJetL2CorrectedEt, &skims.b_ohBJetL2CorrectedEt);
  t->SetBranchAddress("ohBJetL2CorrectedPt", &skims.ohBJetL2CorrectedPt, &skims.b_ohBJetL2CorrectedPt);
  t->SetBranchAddress("ohBJetL2CorrectedEta", &skims.ohBJetL2CorrectedEta, &skims.b_ohBJetL2CorrectedEta);
  t->SetBranchAddress("ohBJetL2CorrectedPhi", &skims.ohBJetL2CorrectedPhi, &skims.b_ohBJetL2CorrectedPhi);
  t->SetBranchAddress("ohBJetIPL25Tag", &skims.ohBJetIPL25Tag, &skims.b_ohBJetIPL25Tag);
  t->SetBranchAddress("ohBJetIPL3Tag", &skims.ohBJetIPL3Tag, &skims.b_ohBJetIPL3Tag);
  t->SetBranchAddress("ohBJetIPLooseL25Tag", &skims.ohBJetIPLooseL25Tag, &skims.b_ohBJetIPLooseL25Tag);
  t->SetBranchAddress("ohBJetIPLooseL3Tag", &skims.ohBJetIPLooseL3Tag, &skims.b_ohBJetIPLooseL3Tag);
  t->SetBranchAddress("ohBJetMuL25Tag", &skims.ohBJetMuL25Tag, &skims.b_ohBJetMuL25Tag);
  t->SetBranchAddress("ohBJetMuL3Tag", &skims.ohBJetMuL3Tag, &skims.b_ohBJetMuL3Tag);
  t->SetBranchAddress("ohBJetPerfL25Tag", &skims.ohBJetPerfL25Tag, &skims.b_ohBJetPerfL25Tag);
  t->SetBranchAddress("ohBJetPerfL3Tag", &skims.ohBJetPerfL3Tag, &skims.b_ohBJetPerfL3Tag);
  t->SetBranchAddress("Npart", &skims.Npart, &skims.b_Npart);
  t->SetBranchAddress("Ncoll", &skims.Ncoll, &skims.b_Ncoll);
  t->SetBranchAddress("Nhard", &skims.Nhard, &skims.b_Nhard);
  t->SetBranchAddress("phi0", &skims.phi0, &skims.b_NPhi0);
  t->SetBranchAddress("b", &skims.b, &skims.b_b);
  t->SetBranchAddress("Ncharged", &skims.Ncharged, &skims.b_Ncharged);
  t->SetBranchAddress("NchargedMR", &skims.NchargedMR, &skims.b_NchargedMR);
  t->SetBranchAddress("MeanPt", &skims.MeanPt, &skims.b_MeanPt);
  t->SetBranchAddress("MeanPtMR", &skims.MeanPtMR, &skims.b_MeanPtMR);
  t->SetBranchAddress("EtMR", &skims.EtMR, &skims.b_EtMR);
  t->SetBranchAddress("NchargedPtCut", &skims.NchargedPtCut, &skims.b_NchargedPtCut);
  t->SetBranchAddress("NchargedPtCutMR", &skims.NchargedPtCutMR, &skims.b_NchargedPtCutMR);
  t->SetBranchAddress("hiBin", &skims.hiBin, &skims.b_hiBin);
  t->SetBranchAddress("hiHF", &skims.hiHF, &skims.b_hiHF);
  t->SetBranchAddress("hiHFplus", &skims.hiHFplus, &skims.b_hiHFplus);
  t->SetBranchAddress("hiHFminus", &skims.hiHFminus, &skims.b_hiHFminus);
  t->SetBranchAddress("hiZDC", &skims.hiZDC, &skims.b_hiZDC);
  t->SetBranchAddress("hiZDCplus", &skims.hiZDCplus, &skims.b_hiZDCplus);
  t->SetBranchAddress("hiZDCminus", &skims.hiZDCminus, &skims.b_hiZDCminus);
  t->SetBranchAddress("hiHFhit", &skims.hiHFhit, &skims.b_hiHFhit);
  t->SetBranchAddress("hiHFhitPlus", &skims.hiHFhitPlus, &skims.b_hiHFhitPlus);
  t->SetBranchAddress("hiHFhitMinus", &skims.hiHFhitMinus, &skims.b_hiHFhitMinus);
  t->SetBranchAddress("hiET", &skims.hiET, &skims.b_hiET);
  t->SetBranchAddress("hiEE", &skims.hiEE, &skims.b_hiEE);
  t->SetBranchAddress("hiEB", &skims.hiEB, &skims.b_hiEB);
  t->SetBranchAddress("hiEEplus", &skims.hiEEplus, &skims.b_hiEEplus);
  t->SetBranchAddress("hiEEminus", &skims.hiEEminus, &skims.b_hiEEminus);
  t->SetBranchAddress("hiNpix", &skims.hiNpix, &skims.b_hiNpix);
  t->SetBranchAddress("hiNpixelTracks", &skims.hiNpixelTracks, &skims.b_hiNpixelTracks);
  t->SetBranchAddress("hiNtracks", &skims.hiNtracks, &skims.b_hiNtracks);
  t->SetBranchAddress("hiNevtPlane", &skims.hiNevtPlane, &skims.b_hiNevtPlane);
  t->SetBranchAddress("hiEvtPlanes", &skims.hiEvtPlanes, &skims.b_hiEvtPlanes);
  t->SetBranchAddress("hiNtracksPtCut", &skims.hiNtracksPtCut, &skims.b_hiNtracksPtCut);
  t->SetBranchAddress("hiNtracksEtaCut", &skims.hiNtracksEtaCut, &skims.b_hiNtracksEtaCut);
  t->SetBranchAddress("hiNtracksEtaPtCut", &skims.hiNtracksEtaPtCut, &skims.b_hiNtracksEtaPtCut);
  t->SetBranchAddress("NrecoElec", &skims.NrecoElec, &skims.b_NrecoElec);
  t->SetBranchAddress("recoElecPt", &skims.recoElecPt, &skims.b_recoElecPt);
  t->SetBranchAddress("recoElecPhi", &skims.recoElecPhi, &skims.b_recoElecPhi);
  t->SetBranchAddress("recoElecEta", &skims.recoElecEta, &skims.b_recoElecEta);
  t->SetBranchAddress("recoElecEt", &skims.recoElecEt, &skims.b_recoElecEt);
  t->SetBranchAddress("recoElecE", &skims.recoElecE, &skims.b_recoElecE);
  t->SetBranchAddress("recoElecEleID", &skims.recoElecEleID, &skims.b_recoElecEleID);
  t->SetBranchAddress("NrecoPhot", &skims.NrecoPhot, &skims.b_NrecoPhot);
  t->SetBranchAddress("recoPhotPt", skims.recoPhotPt, &skims.b_recoPhotPt);
  t->SetBranchAddress("recoPhotPhi", skims.recoPhotPhi, &skims.b_recoPhotPhi);
  t->SetBranchAddress("recoPhotEta", skims.recoPhotEta, &skims.b_recoPhotEta);
  t->SetBranchAddress("recoPhotEt", skims.recoPhotEt, &skims.b_recoPhotEt);
  t->SetBranchAddress("recoPhotE", skims.recoPhotE, &skims.b_recoPhotE);
  t->SetBranchAddress("NrecoSC", &skims.NrecoSC, &skims.b_NrecoSC);
  t->SetBranchAddress("recoSCPt", skims.recoSCPt, &skims.b_recoSCPt);
  t->SetBranchAddress("recoSCPhi", skims.recoSCPhi, &skims.b_recoSCPhi);
  t->SetBranchAddress("recoSCEta", skims.recoSCEta, &skims.b_recoSCEta);
  t->SetBranchAddress("recoSCEt", skims.recoSCEt, &skims.b_recoSCEt);
  t->SetBranchAddress("recoSCE", skims.recoSCE, &skims.b_recoSCE);
  t->SetBranchAddress("NohPhot", &skims.NohPhot, &skims.b_NohPhot);
  t->SetBranchAddress("ohPhotEt", &skims.ohPhotEt, &skims.b_ohPhotEt);
  t->SetBranchAddress("ohPhotEta", &skims.ohPhotEta, &skims.b_ohPhotEta);
  t->SetBranchAddress("ohPhotPhi", &skims.ohPhotPhi, &skims.b_ohPhotPhi);
  t->SetBranchAddress("ohPhotEiso", &skims.ohPhotEiso, &skims.b_ohPhotEiso);
  t->SetBranchAddress("ohPhotHiso", &skims.ohPhotHiso, &skims.b_ohPhotHiso);
  t->SetBranchAddress("ohPhotTiso", &skims.ohPhotTiso, &skims.b_ohPhotTiso);
  t->SetBranchAddress("ohPhotL1iso", &skims.ohPhotL1iso, &skims.b_ohPhotL1iso);
  t->SetBranchAddress("ohPhotClusShap", &skims.ohPhotClusShap, &skims.b_ohPhotClusShap);
  t->SetBranchAddress("NL1IsolEm", &skims.NL1IsolEm, &skims.b_NL1IsolEm);
  t->SetBranchAddress("L1IsolEmEt", &skims.L1IsolEmEt, &skims.b_L1IsolEmEt);
  t->SetBranchAddress("L1IsolEmE", &skims.L1IsolEmE, &skims.b_L1IsolEmE);
  t->SetBranchAddress("L1IsolEmEta", &skims.L1IsolEmEta, &skims.b_L1IsolEmEta);
  t->SetBranchAddress("L1IsolEmPhi", &skims.L1IsolEmPhi, &skims.b_L1IsolEmPhi);
  t->SetBranchAddress("NL1NIsolEm", &skims.NL1NIsolEm, &skims.b_NL1NIsolEm);
  t->SetBranchAddress("L1NIsolEmEt", &skims.L1NIsolEmEt, &skims.b_L1NIsolEmEt);
  t->SetBranchAddress("L1NIsolEmE", &skims.L1NIsolEmE, &skims.b_L1NIsolEmE);
  t->SetBranchAddress("L1NIsolEmEta", &skims.L1NIsolEmEta, &skims.b_L1NIsolEmEta);
  t->SetBranchAddress("L1NIsolEmPhi", &skims.L1NIsolEmPhi, &skims.b_L1NIsolEmPhi);
  t->SetBranchAddress("NL1Mu", &skims.NL1Mu, &skims.b_NL1Mu);
  t->SetBranchAddress("L1MuPt", &skims.L1MuPt, &skims.b_L1MuPt);
  t->SetBranchAddress("L1MuE", &skims.L1MuE, &skims.b_L1MuE);
  t->SetBranchAddress("L1MuEta", &skims.L1MuEta, &skims.b_L1MuEta);
  t->SetBranchAddress("L1MuPhi", &skims.L1MuPhi, &skims.b_L1MuPhi);
  t->SetBranchAddress("L1MuIsol", &skims.L1MuIsol, &skims.b_L1MuIsol);
  t->SetBranchAddress("L1MuMip", &skims.L1MuMip, &skims.b_L1MuMip);
  t->SetBranchAddress("L1MuFor", &skims.L1MuFor, &skims.b_L1MuFor);
  t->SetBranchAddress("L1MuRPC", &skims.L1MuRPC, &skims.b_L1MuRPC);
  t->SetBranchAddress("L1MuQal", &skims.L1MuQal, &skims.b_L1MuQal);
  t->SetBranchAddress("NL1CenJet", &skims.NL1CenJet, &skims.b_NL1CenJet);
  t->SetBranchAddress("L1CenJetEt", &skims.L1CenJetEt, &skims.b_L1CenJetEt);
  t->SetBranchAddress("L1CenJetE", &skims.L1CenJetE, &skims.b_L1CenJetE);
  t->SetBranchAddress("L1CenJetEta", &skims.L1CenJetEta, &skims.b_L1CenJetEta);
  t->SetBranchAddress("L1CenJetPhi", &skims.L1CenJetPhi, &skims.b_L1CenJetPhi);
  t->SetBranchAddress("NL1ForJet", &skims.NL1ForJet, &skims.b_NL1ForJet);
  t->SetBranchAddress("L1ForJetEt", &skims.L1ForJetEt, &skims.b_L1ForJetEt);
  t->SetBranchAddress("L1ForJetE", &skims.L1ForJetE, &skims.b_L1ForJetE);
  t->SetBranchAddress("L1ForJetEta", &skims.L1ForJetEta, &skims.b_L1ForJetEta);
  t->SetBranchAddress("L1ForJetPhi", &skims.L1ForJetPhi, &skims.b_L1ForJetPhi);
  t->SetBranchAddress("NL1Tau", &skims.NL1Tau, &skims.b_NL1Tau);
  t->SetBranchAddress("L1TauEt", &skims.L1TauEt, &skims.b_L1TauEt);
  t->SetBranchAddress("L1TauE", &skims.L1TauE, &skims.b_L1TauE);
  t->SetBranchAddress("L1TauEta", &skims.L1TauEta, &skims.b_L1TauEta);
  t->SetBranchAddress("L1TauPhi", &skims.L1TauPhi, &skims.b_L1TauPhi);
  t->SetBranchAddress("L1Met", &skims.L1Met, &skims.b_L1Met);
  t->SetBranchAddress("L1MetPhi", &skims.L1MetPhi, &skims.b_L1MetPhi);
  t->SetBranchAddress("L1EtTot", &skims.L1EtTot, &skims.b_L1EtTot);
  t->SetBranchAddress("L1Mht", &skims.L1Mht, &skims.b_L1Mht);
  t->SetBranchAddress("L1MhtPhi", &skims.L1MhtPhi, &skims.b_L1MhtPhi);
  t->SetBranchAddress("L1EtHad", &skims.L1EtHad, &skims.b_L1EtHad);
  t->SetBranchAddress("L1HfRing1EtSumPositiveEta", &skims.L1HfRing1EtSumPositiveEta, &skims.b_L1HfRing1EtSumPositiveEta);
  t->SetBranchAddress("L1HfRing2EtSumPositiveEta", &skims.L1HfRing2EtSumPositiveEta, &skims.b_L1HfRing2EtSumPositiveEta);
  t->SetBranchAddress("L1HfRing1EtSumNegativeEta", &skims.L1HfRing1EtSumNegativeEta, &skims.b_L1HfRing1EtSumNegativeEta);
  t->SetBranchAddress("L1HfRing2EtSumNegativeEta", &skims.L1HfRing2EtSumNegativeEta, &skims.b_L1HfRing2EtSumNegativeEta);
  t->SetBranchAddress("L1HfTowerCountPositiveEtaRing1", &skims.L1HfTowerCountPositiveEtaRing1, &skims.b_L1HfTowerCountPositiveEtaRing1);
  t->SetBranchAddress("L1HfTowerCountNegativeEtaRing1", &skims.L1HfTowerCountNegativeEtaRing1, &skims.b_L1HfTowerCountNegativeEtaRing1);
  t->SetBranchAddress("L1HfTowerCountPositiveEtaRing2", &skims.L1HfTowerCountPositiveEtaRing2, &skims.b_L1HfTowerCountPositiveEtaRing2);
  t->SetBranchAddress("L1HfTowerCountNegativeEtaRing2", &skims.L1HfTowerCountNegativeEtaRing2, &skims.b_L1HfTowerCountNegativeEtaRing2);
  t->SetBranchAddress("recoNVrt", &skims.recoNVrt, &skims.b_NVrtx);
  t->SetBranchAddress("recoVrtX", skims.recoVrtX, &skims.b_recoVrtX);
  t->SetBranchAddress("recoVrtY", skims.recoVrtY, &skims.b_recoVrtY);
  t->SetBranchAddress("recoVrtZ", skims.recoVrtZ, &skims.b_recoVrtZ);
  t->SetBranchAddress("recoVrtNtrk", skims.recoVrtNtrk, &skims.b_recoVrtNtrk);
  t->SetBranchAddress("recoVrtChi2", skims.recoVrtChi2, &skims.b_recoVrtChi2);
  t->SetBranchAddress("recoVrtNdof", skims.recoVrtNdof, &skims.b_recoVrtNdof);
  t->SetBranchAddress("Run", &skims.Run, &skims.b_Run);
  t->SetBranchAddress("Event", &skims.Event, &skims.b_Event);
  t->SetBranchAddress("LumiBlock", &skims.LumiBlock, &skims.b_LumiBlock);
  t->SetBranchAddress("Bx", &skims.Bx, &skims.b_Bx);
  t->SetBranchAddress("Orbit", &skims.Orbit, &skims.b_Orbit);
  t->SetBranchAddress("AvgInstLumi", &skims.AvgInstLumi, &skims.b_AvgInstLumi);
  t->SetBranchAddress("reco_extra", &skims.reco_extra, &skims.b_reco_extra);
  t->SetBranchAddress("reco_extra_Prescl", &skims.reco_extra_Prescl, &skims.b_reco_extra_Prescl);
  t->SetBranchAddress("reco_extra_jet", &skims.reco_extra_jet, &skims.b_reco_extra_jet);
  t->SetBranchAddress("reco_extra_jet_Prescl", &skims.reco_extra_jet_Prescl, &skims.b_reco_extra_jet_Prescl);
  t->SetBranchAddress("pat_step", &skims.pat_step, &skims.b_pat_step);
  t->SetBranchAddress("pat_step_Prescl", &skims.pat_step_Prescl, &skims.b_pat_step_Prescl);
  t->SetBranchAddress("ana_step", &skims.ana_step, &skims.b_ana_step);
  t->SetBranchAddress("ana_step_Prescl", &skims.ana_step_Prescl, &skims.b_ana_step_Prescl);
  t->SetBranchAddress("phltJetHI", &skims.phltJetHI, &skims.b_phltJetHI);
  t->SetBranchAddress("phltJetHI_Prescl", &skims.phltJetHI_Prescl, &skims.b_phltJetHI_Prescl);
  t->SetBranchAddress("pcollisionEventSelection", &skims.pcollisionEventSelection, &skims.b_pcollisionEventSelection);

  t->SetBranchAddress("phfCoincFilter", &skims.phfCoincFilter, &skims.b_phfCoincFilter);
  t->SetBranchAddress("ppurityFractionFilter", &skims.ppurityFractionFilter, &skims.b_ppurityFractionFilter);

  t->SetBranchAddress("pcollisionEventSelection_Prescl", &skims.pcollisionEventSelection_Prescl, &skims.b_pcollisionEventSelection_Prescl);
  t->SetBranchAddress("phbheReflagNewTimeEnv", &skims.phbheReflagNewTimeEnv, &skims.b_phbheReflagNewTimeEnv);
  t->SetBranchAddress("phbheReflagNewTimeEnv_Prescl", &skims.phbheReflagNewTimeEnv_Prescl, &skims.b_phbheReflagNewTimeEnv_Prescl);
  t->SetBranchAddress("phcalTimingFilter", &skims.phcalTimingFilter, &skims.b_phcalTimingFilter);
  t->SetBranchAddress("phcalTimingFilter_Prescl", &skims.phcalTimingFilter_Prescl, &skims.b_phcalTimingFilter_Prescl);
  t->SetBranchAddress("pHBHENoiseFilter", &skims.pHBHENoiseFilter, &skims.b_pHBHENoiseFilter);
  t->SetBranchAddress("pHBHENoiseFilter_Prescl", &skims.pHBHENoiseFilter_Prescl, &skims.b_pHBHENoiseFilter_Prescl);
  t->SetBranchAddress("phiEcalRecHitSpikeFilter", &skims.phiEcalRecHitSpikeFilter, &skims.b_phiEcalRecHitSpikeFilter);
  t->SetBranchAddress("phiEcalRecHitSpikeFilter_Prescl", &skims.phiEcalRecHitSpikeFilter_Prescl, &skims.b_phiEcalRecHitSpikeFilter_Prescl);
  t->SetBranchAddress("L1_BptxMinus", &skims.L1_BptxMinus, &skims.b_L1_BptxMinus);
  t->SetBranchAddress("L1_BptxMinus_Prescl", &skims.L1_BptxMinus_Prescl, &skims.b_L1_BptxMinus_Prescl);
  t->SetBranchAddress("L1_BptxMinus_5bx", &skims.L1_BptxMinus_5bx, &skims.b_L1_BptxMinus_5bx);
  t->SetBranchAddress("L1_BptxMinus_NotBptxPlus", &skims.L1_BptxMinus_NotBptxPlus, &skims.b_L1_BptxMinus_NotBptxPlus);
  t->SetBranchAddress("L1_BptxMinus_NotBptxPlus_Prescl", &skims.L1_BptxMinus_NotBptxPlus_Prescl, &skims.b_L1_BptxMinus_NotBptxPlus_Prescl);
  t->SetBranchAddress("L1_BptxMinus_NotBptxPlus_5bx", &skims.L1_BptxMinus_NotBptxPlus_5bx, &skims.b_L1_BptxMinus_NotBptxPlus_5bx);
  t->SetBranchAddress("L1_BptxPlus", &skims.L1_BptxPlus, &skims.b_L1_BptxPlus);
  t->SetBranchAddress("L1_BptxPlus_Prescl", &skims.L1_BptxPlus_Prescl, &skims.b_L1_BptxPlus_Prescl);
  t->SetBranchAddress("L1_BptxPlus_5bx", &skims.L1_BptxPlus_5bx, &skims.b_L1_BptxPlus_5bx);
  t->SetBranchAddress("L1_BptxPlusANDMinus", &skims.L1_BptxPlusANDMinus, &skims.b_L1_BptxPlusANDMinus);
  t->SetBranchAddress("L1_BptxPlusANDMinus_Prescl", &skims.L1_BptxPlusANDMinus_Prescl, &skims.b_L1_BptxPlusANDMinus_Prescl);
  t->SetBranchAddress("L1_BptxPlusANDMinus_5bx", &skims.L1_BptxPlusANDMinus_5bx, &skims.b_L1_BptxPlusANDMinus_5bx);
  t->SetBranchAddress("L1_BptxPlusORMinus", &skims.L1_BptxPlusORMinus, &skims.b_L1_BptxPlusORMinus);
  t->SetBranchAddress("L1_BptxPlusORMinus_Prescl", &skims.L1_BptxPlusORMinus_Prescl, &skims.b_L1_BptxPlusORMinus_Prescl);
  t->SetBranchAddress("L1_BptxPlusORMinus_5bx", &skims.L1_BptxPlusORMinus_5bx, &skims.b_L1_BptxPlusORMinus_5bx);
  t->SetBranchAddress("L1_BptxPlusORMinus_instance1", &skims.L1_BptxPlusORMinus_instance1, &skims.b_L1_BptxPlusORMinus_instance1);
  t->SetBranchAddress("L1_BptxPlusORMinus_instance1_Prescl", &skims.L1_BptxPlusORMinus_instance1_Prescl, &skims.b_L1_BptxPlusORMinus_instance1_Prescl);
  t->SetBranchAddress("L1_BptxPlusORMinus_instance1_5bx", &skims.L1_BptxPlusORMinus_instance1_5bx, &skims.b_L1_BptxPlusORMinus_instance1_5bx);
  t->SetBranchAddress("L1_BptxPlus_NotBptxMinus", &skims.L1_BptxPlus_NotBptxMinus, &skims.b_L1_BptxPlus_NotBptxMinus);
  t->SetBranchAddress("L1_BptxPlus_NotBptxMinus_Prescl", &skims.L1_BptxPlus_NotBptxMinus_Prescl, &skims.b_L1_BptxPlus_NotBptxMinus_Prescl);
  t->SetBranchAddress("L1_BptxPlus_NotBptxMinus_5bx", &skims.L1_BptxPlus_NotBptxMinus_5bx, &skims.b_L1_BptxPlus_NotBptxMinus_5bx);
  t->SetBranchAddress("L1_BptxXOR", &skims.L1_BptxXOR, &skims.b_L1_BptxXOR);
  t->SetBranchAddress("L1_BptxXOR_Prescl", &skims.L1_BptxXOR_Prescl, &skims.b_L1_BptxXOR_Prescl);
  t->SetBranchAddress("L1_BptxXOR_5bx", &skims.L1_BptxXOR_5bx, &skims.b_L1_BptxXOR_5bx);
  t->SetBranchAddress("L1_BptxXOR_BscMinBiasOR", &skims.L1_BptxXOR_BscMinBiasOR, &skims.b_L1_BptxXOR_BscMinBiasOR);
  t->SetBranchAddress("L1_BptxXOR_BscMinBiasOR_Prescl", &skims.L1_BptxXOR_BscMinBiasOR_Prescl, &skims.b_L1_BptxXOR_BscMinBiasOR_Prescl);
  t->SetBranchAddress("L1_BptxXOR_BscMinBiasOR_5bx", &skims.L1_BptxXOR_BscMinBiasOR_5bx, &skims.b_L1_BptxXOR_BscMinBiasOR_5bx);
  t->SetBranchAddress("L1_Bsc2Minus_BptxMinus", &skims.L1_Bsc2Minus_BptxMinus, &skims.b_L1_Bsc2Minus_BptxMinus);
  t->SetBranchAddress("L1_Bsc2Minus_BptxMinus_Prescl", &skims.L1_Bsc2Minus_BptxMinus_Prescl, &skims.b_L1_Bsc2Minus_BptxMinus_Prescl);
  t->SetBranchAddress("L1_Bsc2Minus_BptxMinus_5bx", &skims.L1_Bsc2Minus_BptxMinus_5bx, &skims.b_L1_Bsc2Minus_BptxMinus_5bx);
  t->SetBranchAddress("L1_Bsc2Plus_BptxPlus", &skims.L1_Bsc2Plus_BptxPlus, &skims.b_L1_Bsc2Plus_BptxPlus);
  t->SetBranchAddress("L1_Bsc2Plus_BptxPlus_Prescl", &skims.L1_Bsc2Plus_BptxPlus_Prescl, &skims.b_L1_Bsc2Plus_BptxPlus_Prescl);
  t->SetBranchAddress("L1_Bsc2Plus_BptxPlus_5bx", &skims.L1_Bsc2Plus_BptxPlus_5bx, &skims.b_L1_Bsc2Plus_BptxPlus_5bx);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1", &skims.L1_BscMinBiasInnerThreshold1, &skims.b_L1_BscMinBiasInnerThreshold1);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1_Prescl", &skims.L1_BscMinBiasInnerThreshold1_Prescl, &skims.b_L1_BscMinBiasInnerThreshold1_Prescl);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1_5bx", &skims.L1_BscMinBiasInnerThreshold1_5bx, &skims.b_L1_BscMinBiasInnerThreshold1_5bx);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1_BptxAND", &skims.L1_BscMinBiasInnerThreshold1_BptxAND, &skims.b_L1_BscMinBiasInnerThreshold1_BptxAND);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1_BptxAND_Prescl", &skims.L1_BscMinBiasInnerThreshold1_BptxAND_Prescl, &skims.b_L1_BscMinBiasInnerThreshold1_BptxAND_Prescl);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold1_BptxAND_5bx", &skims.L1_BscMinBiasInnerThreshold1_BptxAND_5bx, &skims.b_L1_BscMinBiasInnerThreshold1_BptxAND_5bx);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold2_BptxAND", &skims.L1_BscMinBiasInnerThreshold2_BptxAND, &skims.b_L1_BscMinBiasInnerThreshold2_BptxAND);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold2_BptxAND_Prescl", &skims.L1_BscMinBiasInnerThreshold2_BptxAND_Prescl, &skims.b_L1_BscMinBiasInnerThreshold2_BptxAND_Prescl);
  t->SetBranchAddress("L1_BscMinBiasInnerThreshold2_BptxAND_5bx", &skims.L1_BscMinBiasInnerThreshold2_BptxAND_5bx, &skims.b_L1_BscMinBiasInnerThreshold2_BptxAND_5bx);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxAND", &skims.L1_BscMinBiasOR_BptxAND, &skims.b_L1_BscMinBiasOR_BptxAND);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxAND_Prescl", &skims.L1_BscMinBiasOR_BptxAND_Prescl, &skims.b_L1_BscMinBiasOR_BptxAND_Prescl);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxAND_5bx", &skims.L1_BscMinBiasOR_BptxAND_5bx, &skims.b_L1_BscMinBiasOR_BptxAND_5bx);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxPlusORMinus", &skims.L1_BscMinBiasOR_BptxPlusORMinus, &skims.b_L1_BscMinBiasOR_BptxPlusORMinus);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxPlusORMinus_Prescl", &skims.L1_BscMinBiasOR_BptxPlusORMinus_Prescl, &skims.b_L1_BscMinBiasOR_BptxPlusORMinus_Prescl);
  t->SetBranchAddress("L1_BscMinBiasOR_BptxPlusORMinus_5bx", &skims.L1_BscMinBiasOR_BptxPlusORMinus_5bx, &skims.b_L1_BscMinBiasOR_BptxPlusORMinus_5bx);
  t->SetBranchAddress("L1_BscMinBiasThreshold1", &skims.L1_BscMinBiasThreshold1, &skims.b_L1_BscMinBiasThreshold1);
  t->SetBranchAddress("L1_BscMinBiasThreshold1_Prescl", &skims.L1_BscMinBiasThreshold1_Prescl, &skims.b_L1_BscMinBiasThreshold1_Prescl);
  t->SetBranchAddress("L1_BscMinBiasThreshold1_5bx", &skims.L1_BscMinBiasThreshold1_5bx, &skims.b_L1_BscMinBiasThreshold1_5bx);
  t->SetBranchAddress("L1_BscMinBiasThreshold1_BptxAND", &skims.L1_BscMinBiasThreshold1_BptxAND, &skims.b_L1_BscMinBiasThreshold1_BptxAND);
  t->SetBranchAddress("L1_BscMinBiasThreshold1_BptxAND_Prescl", &skims.L1_BscMinBiasThreshold1_BptxAND_Prescl, &skims.b_L1_BscMinBiasThreshold1_BptxAND_Prescl);
  t->SetBranchAddress("L1_BscMinBiasThreshold1_BptxAND_5bx", &skims.L1_BscMinBiasThreshold1_BptxAND_5bx, &skims.b_L1_BscMinBiasThreshold1_BptxAND_5bx);
  t->SetBranchAddress("L1_BscMinBiasThreshold2_BptxAND", &skims.L1_BscMinBiasThreshold2_BptxAND, &skims.b_L1_BscMinBiasThreshold2_BptxAND);
  t->SetBranchAddress("L1_BscMinBiasThreshold2_BptxAND_Prescl", &skims.L1_BscMinBiasThreshold2_BptxAND_Prescl, &skims.b_L1_BscMinBiasThreshold2_BptxAND_Prescl);
  t->SetBranchAddress("L1_BscMinBiasThreshold2_BptxAND_5bx", &skims.L1_BscMinBiasThreshold2_BptxAND_5bx, &skims.b_L1_BscMinBiasThreshold2_BptxAND_5bx);
  t->SetBranchAddress("L1_DoubleEG2", &skims.L1_DoubleEG2, &skims.b_L1_DoubleEG2);
  t->SetBranchAddress("L1_DoubleEG2_Prescl", &skims.L1_DoubleEG2_Prescl, &skims.b_L1_DoubleEG2_Prescl);
  t->SetBranchAddress("L1_DoubleEG2_5bx", &skims.L1_DoubleEG2_5bx, &skims.b_L1_DoubleEG2_5bx);
  t->SetBranchAddress("L1_DoubleEG5", &skims.L1_DoubleEG5, &skims.b_L1_DoubleEG5);
  t->SetBranchAddress("L1_DoubleEG5_Prescl", &skims.L1_DoubleEG5_Prescl, &skims.b_L1_DoubleEG5_Prescl);
  t->SetBranchAddress("L1_DoubleEG5_5bx", &skims.L1_DoubleEG5_5bx, &skims.b_L1_DoubleEG5_5bx);
  t->SetBranchAddress("L1_DoubleEG5_BptxAND", &skims.L1_DoubleEG5_BptxAND, &skims.b_L1_DoubleEG5_BptxAND);
  t->SetBranchAddress("L1_DoubleEG5_BptxAND_Prescl", &skims.L1_DoubleEG5_BptxAND_Prescl, &skims.b_L1_DoubleEG5_BptxAND_Prescl);
  t->SetBranchAddress("L1_DoubleEG5_BptxAND_5bx", &skims.L1_DoubleEG5_BptxAND_5bx, &skims.b_L1_DoubleEG5_BptxAND_5bx);
  t->SetBranchAddress("L1_DoubleForJet10_EtaOpp", &skims.L1_DoubleForJet10_EtaOpp, &skims.b_L1_DoubleForJet10_EtaOpp);
  t->SetBranchAddress("L1_DoubleForJet10_EtaOpp_Prescl", &skims.L1_DoubleForJet10_EtaOpp_Prescl, &skims.b_L1_DoubleForJet10_EtaOpp_Prescl);
  t->SetBranchAddress("L1_DoubleForJet10_EtaOpp_5bx", &skims.L1_DoubleForJet10_EtaOpp_5bx, &skims.b_L1_DoubleForJet10_EtaOpp_5bx);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing1_P1N1", &skims.L1_DoubleHfBitCountsRing1_P1N1, &skims.b_L1_DoubleHfBitCountsRing1_P1N1);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing1_P1N1_Prescl", &skims.L1_DoubleHfBitCountsRing1_P1N1_Prescl, &skims.b_L1_DoubleHfBitCountsRing1_P1N1_Prescl);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing1_P1N1_5bx", &skims.L1_DoubleHfBitCountsRing1_P1N1_5bx, &skims.b_L1_DoubleHfBitCountsRing1_P1N1_5bx);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing2_P1N1", &skims.L1_DoubleHfBitCountsRing2_P1N1, &skims.b_L1_DoubleHfBitCountsRing2_P1N1);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing2_P1N1_Prescl", &skims.L1_DoubleHfBitCountsRing2_P1N1_Prescl, &skims.b_L1_DoubleHfBitCountsRing2_P1N1_Prescl);
  t->SetBranchAddress("L1_DoubleHfBitCountsRing2_P1N1_5bx", &skims.L1_DoubleHfBitCountsRing2_P1N1_5bx, &skims.b_L1_DoubleHfBitCountsRing2_P1N1_5bx);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P200N200", &skims.L1_DoubleHfRingEtSumsRing1_P200N200, &skims.b_L1_DoubleHfRingEtSumsRing1_P200N200);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P200N200_Prescl", &skims.L1_DoubleHfRingEtSumsRing1_P200N200_Prescl, &skims.b_L1_DoubleHfRingEtSumsRing1_P200N200_Prescl);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P200N200_5bx", &skims.L1_DoubleHfRingEtSumsRing1_P200N200_5bx, &skims.b_L1_DoubleHfRingEtSumsRing1_P200N200_5bx);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P4N4", &skims.L1_DoubleHfRingEtSumsRing1_P4N4, &skims.b_L1_DoubleHfRingEtSumsRing1_P4N4);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P4N4_Prescl", &skims.L1_DoubleHfRingEtSumsRing1_P4N4_Prescl, &skims.b_L1_DoubleHfRingEtSumsRing1_P4N4_Prescl);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing1_P4N4_5bx", &skims.L1_DoubleHfRingEtSumsRing1_P4N4_5bx, &skims.b_L1_DoubleHfRingEtSumsRing1_P4N4_5bx);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P200N200", &skims.L1_DoubleHfRingEtSumsRing2_P200N200, &skims.b_L1_DoubleHfRingEtSumsRing2_P200N200);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P200N200_Prescl", &skims.L1_DoubleHfRingEtSumsRing2_P200N200_Prescl, &skims.b_L1_DoubleHfRingEtSumsRing2_P200N200_Prescl);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P200N200_5bx", &skims.L1_DoubleHfRingEtSumsRing2_P200N200_5bx, &skims.b_L1_DoubleHfRingEtSumsRing2_P200N200_5bx);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P4N4", &skims.L1_DoubleHfRingEtSumsRing2_P4N4, &skims.b_L1_DoubleHfRingEtSumsRing2_P4N4);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P4N4_Prescl", &skims.L1_DoubleHfRingEtSumsRing2_P4N4_Prescl, &skims.b_L1_DoubleHfRingEtSumsRing2_P4N4_Prescl);
  t->SetBranchAddress("L1_DoubleHfRingEtSumsRing2_P4N4_5bx", &skims.L1_DoubleHfRingEtSumsRing2_P4N4_5bx, &skims.b_L1_DoubleHfRingEtSumsRing2_P4N4_5bx);
  t->SetBranchAddress("L1_DoubleJet30", &skims.L1_DoubleJet30, &skims.b_L1_DoubleJet30);
  t->SetBranchAddress("L1_DoubleJet30_Prescl", &skims.L1_DoubleJet30_Prescl, &skims.b_L1_DoubleJet30_Prescl);
  t->SetBranchAddress("L1_DoubleJet30_5bx", &skims.L1_DoubleJet30_5bx, &skims.b_L1_DoubleJet30_5bx);
  t->SetBranchAddress("L1_DoubleMu3", &skims.L1_DoubleMu3, &skims.b_L1_DoubleMu3);
  t->SetBranchAddress("L1_DoubleMu3_Prescl", &skims.L1_DoubleMu3_Prescl, &skims.b_L1_DoubleMu3_Prescl);
  t->SetBranchAddress("L1_DoubleMu3_5bx", &skims.L1_DoubleMu3_5bx, &skims.b_L1_DoubleMu3_5bx);
  t->SetBranchAddress("L1_DoubleMuOpen", &skims.L1_DoubleMuOpen, &skims.b_L1_DoubleMuOpen);
  t->SetBranchAddress("L1_DoubleMuOpen_Prescl", &skims.L1_DoubleMuOpen_Prescl, &skims.b_L1_DoubleMuOpen_Prescl);
  t->SetBranchAddress("L1_DoubleMuOpen_5bx", &skims.L1_DoubleMuOpen_5bx, &skims.b_L1_DoubleMuOpen_5bx);
  t->SetBranchAddress("L1_DoubleMuOpen_BptxAND", &skims.L1_DoubleMuOpen_BptxAND, &skims.b_L1_DoubleMuOpen_BptxAND);
  t->SetBranchAddress("L1_DoubleMuOpen_BptxAND_Prescl", &skims.L1_DoubleMuOpen_BptxAND_Prescl, &skims.b_L1_DoubleMuOpen_BptxAND_Prescl);
  t->SetBranchAddress("L1_DoubleMuOpen_BptxAND_5bx", &skims.L1_DoubleMuOpen_BptxAND_5bx, &skims.b_L1_DoubleMuOpen_BptxAND_5bx);
  t->SetBranchAddress("L1_ETM12", &skims.L1_ETM12, &skims.b_L1_ETM12);
  t->SetBranchAddress("L1_ETM12_Prescl", &skims.L1_ETM12_Prescl, &skims.b_L1_ETM12_Prescl);
  t->SetBranchAddress("L1_ETM12_5bx", &skims.L1_ETM12_5bx, &skims.b_L1_ETM12_5bx);
  t->SetBranchAddress("L1_ETM20", &skims.L1_ETM20, &skims.b_L1_ETM20);
  t->SetBranchAddress("L1_ETM20_Prescl", &skims.L1_ETM20_Prescl, &skims.b_L1_ETM20_Prescl);
  t->SetBranchAddress("L1_ETM20_5bx", &skims.L1_ETM20_5bx, &skims.b_L1_ETM20_5bx);
  t->SetBranchAddress("L1_ETM30", &skims.L1_ETM30, &skims.b_L1_ETM30);
  t->SetBranchAddress("L1_ETM30_Prescl", &skims.L1_ETM30_Prescl, &skims.b_L1_ETM30_Prescl);
  t->SetBranchAddress("L1_ETM30_5bx", &skims.L1_ETM30_5bx, &skims.b_L1_ETM30_5bx);
  t->SetBranchAddress("L1_ETM70", &skims.L1_ETM70, &skims.b_L1_ETM70);
  t->SetBranchAddress("L1_ETM70_Prescl", &skims.L1_ETM70_Prescl, &skims.b_L1_ETM70_Prescl);
  t->SetBranchAddress("L1_ETM70_5bx", &skims.L1_ETM70_5bx, &skims.b_L1_ETM70_5bx);
  t->SetBranchAddress("L1_ETT100", &skims.L1_ETT100, &skims.b_L1_ETT100);
  t->SetBranchAddress("L1_ETT100_Prescl", &skims.L1_ETT100_Prescl, &skims.b_L1_ETT100_Prescl);
  t->SetBranchAddress("L1_ETT100_5bx", &skims.L1_ETT100_5bx, &skims.b_L1_ETT100_5bx);
  t->SetBranchAddress("L1_ETT140", &skims.L1_ETT140, &skims.b_L1_ETT140);
  t->SetBranchAddress("L1_ETT140_Prescl", &skims.L1_ETT140_Prescl, &skims.b_L1_ETT140_Prescl);
  t->SetBranchAddress("L1_ETT140_5bx", &skims.L1_ETT140_5bx, &skims.b_L1_ETT140_5bx);
  t->SetBranchAddress("L1_ETT30", &skims.L1_ETT30, &skims.b_L1_ETT30);
  t->SetBranchAddress("L1_ETT30_Prescl", &skims.L1_ETT30_Prescl, &skims.b_L1_ETT30_Prescl);
  t->SetBranchAddress("L1_ETT30_5bx", &skims.L1_ETT30_5bx, &skims.b_L1_ETT30_5bx);
  t->SetBranchAddress("L1_ETT30_BptxAND", &skims.L1_ETT30_BptxAND, &skims.b_L1_ETT30_BptxAND);
  t->SetBranchAddress("L1_ETT30_BptxAND_Prescl", &skims.L1_ETT30_BptxAND_Prescl, &skims.b_L1_ETT30_BptxAND_Prescl);
  t->SetBranchAddress("L1_ETT30_BptxAND_5bx", &skims.L1_ETT30_BptxAND_5bx, &skims.b_L1_ETT30_BptxAND_5bx);
  t->SetBranchAddress("L1_ETT60", &skims.L1_ETT60, &skims.b_L1_ETT60);
  t->SetBranchAddress("L1_ETT60_Prescl", &skims.L1_ETT60_Prescl, &skims.b_L1_ETT60_Prescl);
  t->SetBranchAddress("L1_ETT60_5bx", &skims.L1_ETT60_5bx, &skims.b_L1_ETT60_5bx);
  t->SetBranchAddress("L1_ETT60_BptxAND", &skims.L1_ETT60_BptxAND, &skims.b_L1_ETT60_BptxAND);
  t->SetBranchAddress("L1_ETT60_BptxAND_Prescl", &skims.L1_ETT60_BptxAND_Prescl, &skims.b_L1_ETT60_BptxAND_Prescl);
  t->SetBranchAddress("L1_ETT60_BptxAND_5bx", &skims.L1_ETT60_BptxAND_5bx, &skims.b_L1_ETT60_BptxAND_5bx);
  t->SetBranchAddress("L1_HTM30", &skims.L1_HTM30, &skims.b_L1_HTM30);
  t->SetBranchAddress("L1_HTM30_Prescl", &skims.L1_HTM30_Prescl, &skims.b_L1_HTM30_Prescl);
  t->SetBranchAddress("L1_HTM30_5bx", &skims.L1_HTM30_5bx, &skims.b_L1_HTM30_5bx);
  t->SetBranchAddress("L1_HTT100", &skims.L1_HTT100, &skims.b_L1_HTT100);
  t->SetBranchAddress("L1_HTT100_Prescl", &skims.L1_HTT100_Prescl, &skims.b_L1_HTT100_Prescl);
  t->SetBranchAddress("L1_HTT100_5bx", &skims.L1_HTT100_5bx, &skims.b_L1_HTT100_5bx);
  t->SetBranchAddress("L1_HTT200", &skims.L1_HTT200, &skims.b_L1_HTT200);
  t->SetBranchAddress("L1_HTT200_Prescl", &skims.L1_HTT200_Prescl, &skims.b_L1_HTT200_Prescl);
  t->SetBranchAddress("L1_HTT200_5bx", &skims.L1_HTT200_5bx, &skims.b_L1_HTT200_5bx);
  t->SetBranchAddress("L1_HTT50", &skims.L1_HTT50, &skims.b_L1_HTT50);
  t->SetBranchAddress("L1_HTT50_Prescl", &skims.L1_HTT50_Prescl, &skims.b_L1_HTT50_Prescl);
  t->SetBranchAddress("L1_HTT50_5bx", &skims.L1_HTT50_5bx, &skims.b_L1_HTT50_5bx);
  t->SetBranchAddress("L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND", &skims.L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND, &skims.b_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND);
  t->SetBranchAddress("L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl", &skims.L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl, &skims.b_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_Prescl);
  t->SetBranchAddress("L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_5bx", &skims.L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_5bx, &skims.b_L1_HcalHfCoincPmORBscMinBiasThresh1_BptxAND_5bx);
  t->SetBranchAddress("L1_HcalHfCoincidencePm", &skims.L1_HcalHfCoincidencePm, &skims.b_L1_HcalHfCoincidencePm);
  t->SetBranchAddress("L1_HcalHfCoincidencePm_Prescl", &skims.L1_HcalHfCoincidencePm_Prescl, &skims.b_L1_HcalHfCoincidencePm_Prescl);
  t->SetBranchAddress("L1_HcalHfCoincidencePm_5bx", &skims.L1_HcalHfCoincidencePm_5bx, &skims.b_L1_HcalHfCoincidencePm_5bx);
  t->SetBranchAddress("L1_HcalHfCoincidencePm_BptxAND", &skims.L1_HcalHfCoincidencePm_BptxAND, &skims.b_L1_HcalHfCoincidencePm_BptxAND);
  t->SetBranchAddress("L1_HcalHfCoincidencePm_BptxAND_Prescl", &skims.L1_HcalHfCoincidencePm_BptxAND_Prescl, &skims.b_L1_HcalHfCoincidencePm_BptxAND_Prescl);
  t->SetBranchAddress("L1_HcalHfCoincidencePm_BptxAND_5bx", &skims.L1_HcalHfCoincidencePm_BptxAND_5bx, &skims.b_L1_HcalHfCoincidencePm_BptxAND_5bx);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm", &skims.L1_HcalHfMmOrPpOrPm, &skims.b_L1_HcalHfMmOrPpOrPm);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm_Prescl", &skims.L1_HcalHfMmOrPpOrPm_Prescl, &skims.b_L1_HcalHfMmOrPpOrPm_Prescl);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm_5bx", &skims.L1_HcalHfMmOrPpOrPm_5bx, &skims.b_L1_HcalHfMmOrPpOrPm_5bx);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm_BptxAND", &skims.L1_HcalHfMmOrPpOrPm_BptxAND, &skims.b_L1_HcalHfMmOrPpOrPm_BptxAND);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm_BptxAND_Prescl", &skims.L1_HcalHfMmOrPpOrPm_BptxAND_Prescl, &skims.b_L1_HcalHfMmOrPpOrPm_BptxAND_Prescl);
  t->SetBranchAddress("L1_HcalHfMmOrPpOrPm_BptxAND_5bx", &skims.L1_HcalHfMmOrPpOrPm_BptxAND_5bx, &skims.b_L1_HcalHfMmOrPpOrPm_BptxAND_5bx);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp", &skims.L1_HcalHfMmpOrMpp, &skims.b_L1_HcalHfMmpOrMpp);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp_Prescl", &skims.L1_HcalHfMmpOrMpp_Prescl, &skims.b_L1_HcalHfMmpOrMpp_Prescl);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp_5bx", &skims.L1_HcalHfMmpOrMpp_5bx, &skims.b_L1_HcalHfMmpOrMpp_5bx);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp_BptxAND", &skims.L1_HcalHfMmpOrMpp_BptxAND, &skims.b_L1_HcalHfMmpOrMpp_BptxAND);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp_BptxAND_Prescl", &skims.L1_HcalHfMmpOrMpp_BptxAND_Prescl, &skims.b_L1_HcalHfMmpOrMpp_BptxAND_Prescl);
  t->SetBranchAddress("L1_HcalHfMmpOrMpp_BptxAND_5bx", &skims.L1_HcalHfMmpOrMpp_BptxAND_5bx, &skims.b_L1_HcalHfMmpOrMpp_BptxAND_5bx);
  t->SetBranchAddress("L1_HcalHoTotalOR", &skims.L1_HcalHoTotalOR, &skims.b_L1_HcalHoTotalOR);
  t->SetBranchAddress("L1_HcalHoTotalOR_Prescl", &skims.L1_HcalHoTotalOR_Prescl, &skims.b_L1_HcalHoTotalOR_Prescl);
  t->SetBranchAddress("L1_HcalHoTotalOR_5bx", &skims.L1_HcalHoTotalOR_5bx, &skims.b_L1_HcalHoTotalOR_5bx);
  t->SetBranchAddress("L1_Mu3_EG5", &skims.L1_Mu3_EG5, &skims.b_L1_Mu3_EG5);
  t->SetBranchAddress("L1_Mu3_EG5_Prescl", &skims.L1_Mu3_EG5_Prescl, &skims.b_L1_Mu3_EG5_Prescl);
  t->SetBranchAddress("L1_Mu3_EG5_5bx", &skims.L1_Mu3_EG5_5bx, &skims.b_L1_Mu3_EG5_5bx);
  t->SetBranchAddress("L1_Mu3_Jet10", &skims.L1_Mu3_Jet10, &skims.b_L1_Mu3_Jet10);
  t->SetBranchAddress("L1_Mu3_Jet10_Prescl", &skims.L1_Mu3_Jet10_Prescl, &skims.b_L1_Mu3_Jet10_Prescl);
  t->SetBranchAddress("L1_Mu3_Jet10_5bx", &skims.L1_Mu3_Jet10_5bx, &skims.b_L1_Mu3_Jet10_5bx);
  t->SetBranchAddress("L1_Mu3_Jet6", &skims.L1_Mu3_Jet6, &skims.b_L1_Mu3_Jet6);
  t->SetBranchAddress("L1_Mu3_Jet6_Prescl", &skims.L1_Mu3_Jet6_Prescl, &skims.b_L1_Mu3_Jet6_Prescl);
  t->SetBranchAddress("L1_Mu3_Jet6_5bx", &skims.L1_Mu3_Jet6_5bx, &skims.b_L1_Mu3_Jet6_5bx);
  t->SetBranchAddress("L1_Mu5_Jet6", &skims.L1_Mu5_Jet6, &skims.b_L1_Mu5_Jet6);
  t->SetBranchAddress("L1_Mu5_Jet6_Prescl", &skims.L1_Mu5_Jet6_Prescl, &skims.b_L1_Mu5_Jet6_Prescl);
  t->SetBranchAddress("L1_Mu5_Jet6_5bx", &skims.L1_Mu5_Jet6_5bx, &skims.b_L1_Mu5_Jet6_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1", &skims.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_Prescl", &skims.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_Prescl, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_5bx", &skims.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_5bx, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold1_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2", &skims.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_Prescl", &skims.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_Prescl, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_5bx", &skims.L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_5bx, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasInnerThreshold2_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasOR", &skims.L1_NotBsc2_BptxAND_BscMinBiasOR, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasOR);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasOR_Prescl", &skims.L1_NotBsc2_BptxAND_BscMinBiasOR_Prescl, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasOR_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasOR_5bx", &skims.L1_NotBsc2_BptxAND_BscMinBiasOR_5bx, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasOR_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold1", &skims.L1_NotBsc2_BptxAND_BscMinBiasThreshold1, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold1);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold1_Prescl", &skims.L1_NotBsc2_BptxAND_BscMinBiasThreshold1_Prescl, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold1_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold1_5bx", &skims.L1_NotBsc2_BptxAND_BscMinBiasThreshold1_5bx, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold1_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold2", &skims.L1_NotBsc2_BptxAND_BscMinBiasThreshold2, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold2);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold2_Prescl", &skims.L1_NotBsc2_BptxAND_BscMinBiasThreshold2_Prescl, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold2_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_BscMinBiasThreshold2_5bx", &skims.L1_NotBsc2_BptxAND_BscMinBiasThreshold2_5bx, &skims.b_L1_NotBsc2_BptxAND_BscMinBiasThreshold2_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1", &skims.L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1, &skims.b_L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_Prescl", &skims.L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_Prescl, &skims.b_L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_5bx", &skims.L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_5bx, &skims.b_L1_NotBsc2_BptxAND_HcalHfCoincPmORBscMinBiasThresh1_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincidencePm", &skims.L1_NotBsc2_BptxAND_HcalHfCoincidencePm, &skims.b_L1_NotBsc2_BptxAND_HcalHfCoincidencePm);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincidencePm_Prescl", &skims.L1_NotBsc2_BptxAND_HcalHfCoincidencePm_Prescl, &skims.b_L1_NotBsc2_BptxAND_HcalHfCoincidencePm_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfCoincidencePm_5bx", &skims.L1_NotBsc2_BptxAND_HcalHfCoincidencePm_5bx, &skims.b_L1_NotBsc2_BptxAND_HcalHfCoincidencePm_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm", &skims.L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm, &skims.b_L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_Prescl", &skims.L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_Prescl, &skims.b_L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_5bx", &skims.L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_5bx, &skims.b_L1_NotBsc2_BptxAND_HcalHfMmOrPpOrPm_5bx);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmpOrMpp", &skims.L1_NotBsc2_BptxAND_HcalHfMmpOrMpp, &skims.b_L1_NotBsc2_BptxAND_HcalHfMmpOrMpp);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_Prescl", &skims.L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_Prescl, &skims.b_L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_5bx", &skims.L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_5bx, &skims.b_L1_NotBsc2_BptxAND_HcalHfMmpOrMpp_5bx);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold1", &skims.L1_NotBsc2_BscMinBiasInnerThreshold1, &skims.b_L1_NotBsc2_BscMinBiasInnerThreshold1);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold1_Prescl", &skims.L1_NotBsc2_BscMinBiasInnerThreshold1_Prescl, &skims.b_L1_NotBsc2_BscMinBiasInnerThreshold1_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold1_5bx", &skims.L1_NotBsc2_BscMinBiasInnerThreshold1_5bx, &skims.b_L1_NotBsc2_BscMinBiasInnerThreshold1_5bx);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold2", &skims.L1_NotBsc2_BscMinBiasInnerThreshold2, &skims.b_L1_NotBsc2_BscMinBiasInnerThreshold2);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold2_Prescl", &skims.L1_NotBsc2_BscMinBiasInnerThreshold2_Prescl, &skims.b_L1_NotBsc2_BscMinBiasInnerThreshold2_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasInnerThreshold2_5bx", &skims.L1_NotBsc2_BscMinBiasInnerThreshold2_5bx, &skims.b_L1_NotBsc2_BscMinBiasInnerThreshold2_5bx);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasOR", &skims.L1_NotBsc2_BscMinBiasOR, &skims.b_L1_NotBsc2_BscMinBiasOR);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasOR_Prescl", &skims.L1_NotBsc2_BscMinBiasOR_Prescl, &skims.b_L1_NotBsc2_BscMinBiasOR_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasOR_5bx", &skims.L1_NotBsc2_BscMinBiasOR_5bx, &skims.b_L1_NotBsc2_BscMinBiasOR_5bx);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold1", &skims.L1_NotBsc2_BscMinBiasThreshold1, &skims.b_L1_NotBsc2_BscMinBiasThreshold1);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold1_Prescl", &skims.L1_NotBsc2_BscMinBiasThreshold1_Prescl, &skims.b_L1_NotBsc2_BscMinBiasThreshold1_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold1_5bx", &skims.L1_NotBsc2_BscMinBiasThreshold1_5bx, &skims.b_L1_NotBsc2_BscMinBiasThreshold1_5bx);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold2", &skims.L1_NotBsc2_BscMinBiasThreshold2, &skims.b_L1_NotBsc2_BscMinBiasThreshold2);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold2_Prescl", &skims.L1_NotBsc2_BscMinBiasThreshold2_Prescl, &skims.b_L1_NotBsc2_BscMinBiasThreshold2_Prescl);
  t->SetBranchAddress("L1_NotBsc2_BscMinBiasThreshold2_5bx", &skims.L1_NotBsc2_BscMinBiasThreshold2_5bx, &skims.b_L1_NotBsc2_BscMinBiasThreshold2_5bx);
  t->SetBranchAddress("L1_NotBsc2_HcalHfCoincidencePm", &skims.L1_NotBsc2_HcalHfCoincidencePm, &skims.b_L1_NotBsc2_HcalHfCoincidencePm);
  t->SetBranchAddress("L1_NotBsc2_HcalHfCoincidencePm_Prescl", &skims.L1_NotBsc2_HcalHfCoincidencePm_Prescl, &skims.b_L1_NotBsc2_HcalHfCoincidencePm_Prescl);
  t->SetBranchAddress("L1_NotBsc2_HcalHfCoincidencePm_5bx", &skims.L1_NotBsc2_HcalHfCoincidencePm_5bx, &skims.b_L1_NotBsc2_HcalHfCoincidencePm_5bx);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmOrPpOrPm", &skims.L1_NotBsc2_HcalHfMmOrPpOrPm, &skims.b_L1_NotBsc2_HcalHfMmOrPpOrPm);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmOrPpOrPm_Prescl", &skims.L1_NotBsc2_HcalHfMmOrPpOrPm_Prescl, &skims.b_L1_NotBsc2_HcalHfMmOrPpOrPm_Prescl);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmOrPpOrPm_5bx", &skims.L1_NotBsc2_HcalHfMmOrPpOrPm_5bx, &skims.b_L1_NotBsc2_HcalHfMmOrPpOrPm_5bx);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmpOrMpp", &skims.L1_NotBsc2_HcalHfMmpOrMpp, &skims.b_L1_NotBsc2_HcalHfMmpOrMpp);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmpOrMpp_Prescl", &skims.L1_NotBsc2_HcalHfMmpOrMpp_Prescl, &skims.b_L1_NotBsc2_HcalHfMmpOrMpp_Prescl);
  t->SetBranchAddress("L1_NotBsc2_HcalHfMmpOrMpp_5bx", &skims.L1_NotBsc2_HcalHfMmpOrMpp_5bx, &skims.b_L1_NotBsc2_HcalHfMmpOrMpp_5bx);
  t->SetBranchAddress("L1_QuadJet6", &skims.L1_QuadJet6, &skims.b_L1_QuadJet6);
  t->SetBranchAddress("L1_QuadJet6_Prescl", &skims.L1_QuadJet6_Prescl, &skims.b_L1_QuadJet6_Prescl);
  t->SetBranchAddress("L1_QuadJet6_5bx", &skims.L1_QuadJet6_5bx, &skims.b_L1_QuadJet6_5bx);
  t->SetBranchAddress("L1_QuadJet8", &skims.L1_QuadJet8, &skims.b_L1_QuadJet8);
  t->SetBranchAddress("L1_QuadJet8_Prescl", &skims.L1_QuadJet8_Prescl, &skims.b_L1_QuadJet8_Prescl);
  t->SetBranchAddress("L1_QuadJet8_5bx", &skims.L1_QuadJet8_5bx, &skims.b_L1_QuadJet8_5bx);
  t->SetBranchAddress("L1_SingleEG10", &skims.L1_SingleEG10, &skims.b_L1_SingleEG10);
  t->SetBranchAddress("L1_SingleEG10_Prescl", &skims.L1_SingleEG10_Prescl, &skims.b_L1_SingleEG10_Prescl);
  t->SetBranchAddress("L1_SingleEG10_5bx", &skims.L1_SingleEG10_5bx, &skims.b_L1_SingleEG10_5bx);
  t->SetBranchAddress("L1_SingleEG12", &skims.L1_SingleEG12, &skims.b_L1_SingleEG12);
  t->SetBranchAddress("L1_SingleEG12_Prescl", &skims.L1_SingleEG12_Prescl, &skims.b_L1_SingleEG12_Prescl);
  t->SetBranchAddress("L1_SingleEG12_5bx", &skims.L1_SingleEG12_5bx, &skims.b_L1_SingleEG12_5bx);
  t->SetBranchAddress("L1_SingleEG15", &skims.L1_SingleEG15, &skims.b_L1_SingleEG15);
  t->SetBranchAddress("L1_SingleEG15_Prescl", &skims.L1_SingleEG15_Prescl, &skims.b_L1_SingleEG15_Prescl);
  t->SetBranchAddress("L1_SingleEG15_5bx", &skims.L1_SingleEG15_5bx, &skims.b_L1_SingleEG15_5bx);
  t->SetBranchAddress("L1_SingleEG2", &skims.L1_SingleEG2, &skims.b_L1_SingleEG2);
  t->SetBranchAddress("L1_SingleEG2_Prescl", &skims.L1_SingleEG2_Prescl, &skims.b_L1_SingleEG2_Prescl);
  t->SetBranchAddress("L1_SingleEG2_5bx", &skims.L1_SingleEG2_5bx, &skims.b_L1_SingleEG2_5bx);
  t->SetBranchAddress("L1_SingleEG20", &skims.L1_SingleEG20, &skims.b_L1_SingleEG20);
  t->SetBranchAddress("L1_SingleEG20_Prescl", &skims.L1_SingleEG20_Prescl, &skims.b_L1_SingleEG20_Prescl);
  t->SetBranchAddress("L1_SingleEG20_5bx", &skims.L1_SingleEG20_5bx, &skims.b_L1_SingleEG20_5bx);
  t->SetBranchAddress("L1_SingleEG2_BptxAND", &skims.L1_SingleEG2_BptxAND, &skims.b_L1_SingleEG2_BptxAND);
  t->SetBranchAddress("L1_SingleEG2_BptxAND_Prescl", &skims.L1_SingleEG2_BptxAND_Prescl, &skims.b_L1_SingleEG2_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleEG2_BptxAND_5bx", &skims.L1_SingleEG2_BptxAND_5bx, &skims.b_L1_SingleEG2_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleEG5", &skims.L1_SingleEG5, &skims.b_L1_SingleEG5);
  t->SetBranchAddress("L1_SingleEG5_Prescl", &skims.L1_SingleEG5_Prescl, &skims.b_L1_SingleEG5_Prescl);
  t->SetBranchAddress("L1_SingleEG5_5bx", &skims.L1_SingleEG5_5bx, &skims.b_L1_SingleEG5_5bx);
  t->SetBranchAddress("L1_SingleEG5_BptxAND", &skims.L1_SingleEG5_BptxAND, &skims.b_L1_SingleEG5_BptxAND);
  t->SetBranchAddress("L1_SingleEG5_BptxAND_Prescl", &skims.L1_SingleEG5_BptxAND_Prescl, &skims.b_L1_SingleEG5_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleEG5_BptxAND_5bx", &skims.L1_SingleEG5_BptxAND_5bx, &skims.b_L1_SingleEG5_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleEG8", &skims.L1_SingleEG8, &skims.b_L1_SingleEG8);
  t->SetBranchAddress("L1_SingleEG8_Prescl", &skims.L1_SingleEG8_Prescl, &skims.b_L1_SingleEG8_Prescl);
  t->SetBranchAddress("L1_SingleEG8_5bx", &skims.L1_SingleEG8_5bx, &skims.b_L1_SingleEG8_5bx);
  t->SetBranchAddress("L1_SingleForJet2", &skims.L1_SingleForJet2, &skims.b_L1_SingleForJet2);
  t->SetBranchAddress("L1_SingleForJet2_Prescl", &skims.L1_SingleForJet2_Prescl, &skims.b_L1_SingleForJet2_Prescl);
  t->SetBranchAddress("L1_SingleForJet2_5bx", &skims.L1_SingleForJet2_5bx, &skims.b_L1_SingleForJet2_5bx);
  t->SetBranchAddress("L1_SingleForJet4", &skims.L1_SingleForJet4, &skims.b_L1_SingleForJet4);
  t->SetBranchAddress("L1_SingleForJet4_Prescl", &skims.L1_SingleForJet4_Prescl, &skims.b_L1_SingleForJet4_Prescl);
  t->SetBranchAddress("L1_SingleForJet4_5bx", &skims.L1_SingleForJet4_5bx, &skims.b_L1_SingleForJet4_5bx);
  t->SetBranchAddress("L1_SingleJet10", &skims.L1_SingleJet10, &skims.b_L1_SingleJet10);
  t->SetBranchAddress("L1_SingleJet10_Prescl", &skims.L1_SingleJet10_Prescl, &skims.b_L1_SingleJet10_Prescl);
  t->SetBranchAddress("L1_SingleJet10_5bx", &skims.L1_SingleJet10_5bx, &skims.b_L1_SingleJet10_5bx);
  t->SetBranchAddress("L1_SingleJet20", &skims.L1_SingleJet20, &skims.b_L1_SingleJet20);
  t->SetBranchAddress("L1_SingleJet20_Prescl", &skims.L1_SingleJet20_Prescl, &skims.b_L1_SingleJet20_Prescl);
  t->SetBranchAddress("L1_SingleJet20_5bx", &skims.L1_SingleJet20_5bx, &skims.b_L1_SingleJet20_5bx);
  t->SetBranchAddress("L1_SingleJet20_BptxAND", &skims.L1_SingleJet20_BptxAND, &skims.b_L1_SingleJet20_BptxAND);
  t->SetBranchAddress("L1_SingleJet20_BptxAND_Prescl", &skims.L1_SingleJet20_BptxAND_Prescl, &skims.b_L1_SingleJet20_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleJet20_BptxAND_5bx", &skims.L1_SingleJet20_BptxAND_5bx, &skims.b_L1_SingleJet20_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleJet20_NotBptxOR_Ext", &skims.L1_SingleJet20_NotBptxOR_Ext, &skims.b_L1_SingleJet20_NotBptxOR_Ext);
  t->SetBranchAddress("L1_SingleJet20_NotBptxOR_Ext_Prescl", &skims.L1_SingleJet20_NotBptxOR_Ext_Prescl, &skims.b_L1_SingleJet20_NotBptxOR_Ext_Prescl);
  t->SetBranchAddress("L1_SingleJet20_NotBptxOR_Ext_5bx", &skims.L1_SingleJet20_NotBptxOR_Ext_5bx, &skims.b_L1_SingleJet20_NotBptxOR_Ext_5bx);
  t->SetBranchAddress("L1_SingleJet30", &skims.L1_SingleJet30, &skims.b_L1_SingleJet30);
  t->SetBranchAddress("L1_SingleJet30_Prescl", &skims.L1_SingleJet30_Prescl, &skims.b_L1_SingleJet30_Prescl);
  t->SetBranchAddress("L1_SingleJet30_5bx", &skims.L1_SingleJet30_5bx, &skims.b_L1_SingleJet30_5bx);
  t->SetBranchAddress("L1_SingleJet30_BptxAND", &skims.L1_SingleJet30_BptxAND, &skims.b_L1_SingleJet30_BptxAND);
  t->SetBranchAddress("L1_SingleJet30_BptxAND_Prescl", &skims.L1_SingleJet30_BptxAND_Prescl, &skims.b_L1_SingleJet30_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleJet30_BptxAND_5bx", &skims.L1_SingleJet30_BptxAND_5bx, &skims.b_L1_SingleJet30_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleJet40", &skims.L1_SingleJet40, &skims.b_L1_SingleJet40);
  t->SetBranchAddress("L1_SingleJet40_Prescl", &skims.L1_SingleJet40_Prescl, &skims.b_L1_SingleJet40_Prescl);
  t->SetBranchAddress("L1_SingleJet40_5bx", &skims.L1_SingleJet40_5bx, &skims.b_L1_SingleJet40_5bx);
  t->SetBranchAddress("L1_SingleJet40_BptxAND", &skims.L1_SingleJet40_BptxAND, &skims.b_L1_SingleJet40_BptxAND);
  t->SetBranchAddress("L1_SingleJet40_BptxAND_Prescl", &skims.L1_SingleJet40_BptxAND_Prescl, &skims.b_L1_SingleJet40_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleJet40_BptxAND_5bx", &skims.L1_SingleJet40_BptxAND_5bx, &skims.b_L1_SingleJet40_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleJet50", &skims.L1_SingleJet50, &skims.b_L1_SingleJet50);
  t->SetBranchAddress("L1_SingleJet50_Prescl", &skims.L1_SingleJet50_Prescl, &skims.b_L1_SingleJet50_Prescl);
  t->SetBranchAddress("L1_SingleJet50_5bx", &skims.L1_SingleJet50_5bx, &skims.b_L1_SingleJet50_5bx);
  t->SetBranchAddress("L1_SingleJet50_BptxAND", &skims.L1_SingleJet50_BptxAND, &skims.b_L1_SingleJet50_BptxAND);
  t->SetBranchAddress("L1_SingleJet50_BptxAND_Prescl", &skims.L1_SingleJet50_BptxAND_Prescl, &skims.b_L1_SingleJet50_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleJet50_BptxAND_5bx", &skims.L1_SingleJet50_BptxAND_5bx, &skims.b_L1_SingleJet50_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleJet6", &skims.L1_SingleJet6, &skims.b_L1_SingleJet6);
  t->SetBranchAddress("L1_SingleJet6_Prescl", &skims.L1_SingleJet6_Prescl, &skims.b_L1_SingleJet6_Prescl);
  t->SetBranchAddress("L1_SingleJet6_5bx", &skims.L1_SingleJet6_5bx, &skims.b_L1_SingleJet6_5bx);
  t->SetBranchAddress("L1_SingleJet60", &skims.L1_SingleJet60, &skims.b_L1_SingleJet60);
  t->SetBranchAddress("L1_SingleJet60_Prescl", &skims.L1_SingleJet60_Prescl, &skims.b_L1_SingleJet60_Prescl);
  t->SetBranchAddress("L1_SingleJet60_5bx", &skims.L1_SingleJet60_5bx, &skims.b_L1_SingleJet60_5bx);
  t->SetBranchAddress("L1_SingleMu0", &skims.L1_SingleMu0, &skims.b_L1_SingleMu0);
  t->SetBranchAddress("L1_SingleMu0_Prescl", &skims.L1_SingleMu0_Prescl, &skims.b_L1_SingleMu0_Prescl);
  t->SetBranchAddress("L1_SingleMu0_5bx", &skims.L1_SingleMu0_5bx, &skims.b_L1_SingleMu0_5bx);
  t->SetBranchAddress("L1_SingleMu10", &skims.L1_SingleMu10, &skims.b_L1_SingleMu10);
  t->SetBranchAddress("L1_SingleMu10_Prescl", &skims.L1_SingleMu10_Prescl, &skims.b_L1_SingleMu10_Prescl);
  t->SetBranchAddress("L1_SingleMu10_5bx", &skims.L1_SingleMu10_5bx, &skims.b_L1_SingleMu10_5bx);
  t->SetBranchAddress("L1_SingleMu14", &skims.L1_SingleMu14, &skims.b_L1_SingleMu14);
  t->SetBranchAddress("L1_SingleMu14_Prescl", &skims.L1_SingleMu14_Prescl, &skims.b_L1_SingleMu14_Prescl);
  t->SetBranchAddress("L1_SingleMu14_5bx", &skims.L1_SingleMu14_5bx, &skims.b_L1_SingleMu14_5bx);
  t->SetBranchAddress("L1_SingleMu20", &skims.L1_SingleMu20, &skims.b_L1_SingleMu20);
  t->SetBranchAddress("L1_SingleMu20_Prescl", &skims.L1_SingleMu20_Prescl, &skims.b_L1_SingleMu20_Prescl);
  t->SetBranchAddress("L1_SingleMu20_5bx", &skims.L1_SingleMu20_5bx, &skims.b_L1_SingleMu20_5bx);
  t->SetBranchAddress("L1_SingleMu3", &skims.L1_SingleMu3, &skims.b_L1_SingleMu3);
  t->SetBranchAddress("L1_SingleMu3_Prescl", &skims.L1_SingleMu3_Prescl, &skims.b_L1_SingleMu3_Prescl);
  t->SetBranchAddress("L1_SingleMu3_5bx", &skims.L1_SingleMu3_5bx, &skims.b_L1_SingleMu3_5bx);
  t->SetBranchAddress("L1_SingleMu3_BptxAND", &skims.L1_SingleMu3_BptxAND, &skims.b_L1_SingleMu3_BptxAND);
  t->SetBranchAddress("L1_SingleMu3_BptxAND_Prescl", &skims.L1_SingleMu3_BptxAND_Prescl, &skims.b_L1_SingleMu3_BptxAND_Prescl);
  t->SetBranchAddress("L1_SingleMu3_BptxAND_5bx", &skims.L1_SingleMu3_BptxAND_5bx, &skims.b_L1_SingleMu3_BptxAND_5bx);
  t->SetBranchAddress("L1_SingleMu5", &skims.L1_SingleMu5, &skims.b_L1_SingleMu5);
  t->SetBranchAddress("L1_SingleMu5_Prescl", &skims.L1_SingleMu5_Prescl, &skims.b_L1_SingleMu5_Prescl);
  t->SetBranchAddress("L1_SingleMu5_5bx", &skims.L1_SingleMu5_5bx, &skims.b_L1_SingleMu5_5bx);
  t->SetBranchAddress("L1_SingleMu7", &skims.L1_SingleMu7, &skims.b_L1_SingleMu7);
  t->SetBranchAddress("L1_SingleMu7_Prescl", &skims.L1_SingleMu7_Prescl, &skims.b_L1_SingleMu7_Prescl);
  t->SetBranchAddress("L1_SingleMu7_5bx", &skims.L1_SingleMu7_5bx, &skims.b_L1_SingleMu7_5bx);
  t->SetBranchAddress("L1_SingleMuBeamHalo", &skims.L1_SingleMuBeamHalo, &skims.b_L1_SingleMuBeamHalo);
  t->SetBranchAddress("L1_SingleMuBeamHalo_Prescl", &skims.L1_SingleMuBeamHalo_Prescl, &skims.b_L1_SingleMuBeamHalo_Prescl);
  t->SetBranchAddress("L1_SingleMuBeamHalo_5bx", &skims.L1_SingleMuBeamHalo_5bx, &skims.b_L1_SingleMuBeamHalo_5bx);
  t->SetBranchAddress("L1_SingleMuOpen", &skims.L1_SingleMuOpen, &skims.b_L1_SingleMuOpen);
  t->SetBranchAddress("L1_SingleMuOpen_Prescl", &skims.L1_SingleMuOpen_Prescl, &skims.b_L1_SingleMuOpen_Prescl);
  t->SetBranchAddress("L1_SingleMuOpen_5bx", &skims.L1_SingleMuOpen_5bx, &skims.b_L1_SingleMuOpen_5bx);
  t->SetBranchAddress("L1_SingleTauJet50", &skims.L1_SingleTauJet50, &skims.b_L1_SingleTauJet50);
  t->SetBranchAddress("L1_SingleTauJet50_Prescl", &skims.L1_SingleTauJet50_Prescl, &skims.b_L1_SingleTauJet50_Prescl);
  t->SetBranchAddress("L1_SingleTauJet50_5bx", &skims.L1_SingleTauJet50_5bx, &skims.b_L1_SingleTauJet50_5bx);
  t->SetBranchAddress("L1_TripleJet14", &skims.L1_TripleJet14, &skims.b_L1_TripleJet14);
  t->SetBranchAddress("L1_TripleJet14_Prescl", &skims.L1_TripleJet14_Prescl, &skims.b_L1_TripleJet14_Prescl);
  t->SetBranchAddress("L1_TripleJet14_5bx", &skims.L1_TripleJet14_5bx, &skims.b_L1_TripleJet14_5bx);
  t->SetBranchAddress("L1_ZdcCaloMinus", &skims.L1_ZdcCaloMinus, &skims.b_L1_ZdcCaloMinus);
  t->SetBranchAddress("L1_ZdcCaloMinus_Prescl", &skims.L1_ZdcCaloMinus_Prescl, &skims.b_L1_ZdcCaloMinus_Prescl);
  t->SetBranchAddress("L1_ZdcCaloMinus_5bx", &skims.L1_ZdcCaloMinus_5bx, &skims.b_L1_ZdcCaloMinus_5bx);
  t->SetBranchAddress("L1_ZdcCaloMinus_BptxAND", &skims.L1_ZdcCaloMinus_BptxAND, &skims.b_L1_ZdcCaloMinus_BptxAND);
  t->SetBranchAddress("L1_ZdcCaloMinus_BptxAND_Prescl", &skims.L1_ZdcCaloMinus_BptxAND_Prescl, &skims.b_L1_ZdcCaloMinus_BptxAND_Prescl);
  t->SetBranchAddress("L1_ZdcCaloMinus_BptxAND_5bx", &skims.L1_ZdcCaloMinus_BptxAND_5bx, &skims.b_L1_ZdcCaloMinus_BptxAND_5bx);
  t->SetBranchAddress("L1_ZdcCaloPlus", &skims.L1_ZdcCaloPlus, &skims.b_L1_ZdcCaloPlus);
  t->SetBranchAddress("L1_ZdcCaloPlus_Prescl", &skims.L1_ZdcCaloPlus_Prescl, &skims.b_L1_ZdcCaloPlus_Prescl);
  t->SetBranchAddress("L1_ZdcCaloPlus_5bx", &skims.L1_ZdcCaloPlus_5bx, &skims.b_L1_ZdcCaloPlus_5bx);
  t->SetBranchAddress("L1_ZdcCaloPlus_BptxAND", &skims.L1_ZdcCaloPlus_BptxAND, &skims.b_L1_ZdcCaloPlus_BptxAND);
  t->SetBranchAddress("L1_ZdcCaloPlus_BptxAND_Prescl", &skims.L1_ZdcCaloPlus_BptxAND_Prescl, &skims.b_L1_ZdcCaloPlus_BptxAND_Prescl);
  t->SetBranchAddress("L1_ZdcCaloPlus_BptxAND_5bx", &skims.L1_ZdcCaloPlus_BptxAND_5bx, &skims.b_L1_ZdcCaloPlus_BptxAND_5bx);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus", &skims.L1_ZdcCaloPlus_ZdcCaloMinus, &skims.b_L1_ZdcCaloPlus_ZdcCaloMinus);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus_Prescl", &skims.L1_ZdcCaloPlus_ZdcCaloMinus_Prescl, &skims.b_L1_ZdcCaloPlus_ZdcCaloMinus_Prescl);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus_5bx", &skims.L1_ZdcCaloPlus_ZdcCaloMinus_5bx, &skims.b_L1_ZdcCaloPlus_ZdcCaloMinus_5bx);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND", &skims.L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND, &skims.b_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_Prescl", &skims.L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_Prescl, &skims.b_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_Prescl);
  t->SetBranchAddress("L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_5bx", &skims.L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_5bx, &skims.b_L1_ZdcCaloPlus_ZdcCaloMinus_BptxAND_5bx);
  t->SetBranchAddress("L1_ZdcScintLooseVertex", &skims.L1_ZdcScintLooseVertex, &skims.b_L1_ZdcScintLooseVertex);
  t->SetBranchAddress("L1_ZdcScintLooseVertex_Prescl", &skims.L1_ZdcScintLooseVertex_Prescl, &skims.b_L1_ZdcScintLooseVertex_Prescl);
  t->SetBranchAddress("L1_ZdcScintLooseVertex_5bx", &skims.L1_ZdcScintLooseVertex_5bx, &skims.b_L1_ZdcScintLooseVertex_5bx);
  t->SetBranchAddress("L1_ZdcScintLooseVertex_BptxAND", &skims.L1_ZdcScintLooseVertex_BptxAND, &skims.b_L1_ZdcScintLooseVertex_BptxAND);
  t->SetBranchAddress("L1_ZdcScintLooseVertex_BptxAND_Prescl", &skims.L1_ZdcScintLooseVertex_BptxAND_Prescl, &skims.b_L1_ZdcScintLooseVertex_BptxAND_Prescl);
  t->SetBranchAddress("L1_ZdcScintLooseVertex_BptxAND_5bx", &skims.L1_ZdcScintLooseVertex_BptxAND_5bx, &skims.b_L1_ZdcScintLooseVertex_BptxAND_5bx);
  t->SetBranchAddress("L1_ZdcScintMinus", &skims.L1_ZdcScintMinus, &skims.b_L1_ZdcScintMinus);
  t->SetBranchAddress("L1_ZdcScintMinus_Prescl", &skims.L1_ZdcScintMinus_Prescl, &skims.b_L1_ZdcScintMinus_Prescl);
  t->SetBranchAddress("L1_ZdcScintMinus_5bx", &skims.L1_ZdcScintMinus_5bx, &skims.b_L1_ZdcScintMinus_5bx);
  t->SetBranchAddress("L1_ZdcScintPlus", &skims.L1_ZdcScintPlus, &skims.b_L1_ZdcScintPlus);
  t->SetBranchAddress("L1_ZdcScintPlus_Prescl", &skims.L1_ZdcScintPlus_Prescl, &skims.b_L1_ZdcScintPlus_Prescl);
  t->SetBranchAddress("L1_ZdcScintPlus_5bx", &skims.L1_ZdcScintPlus_5bx, &skims.b_L1_ZdcScintPlus_5bx);
  t->SetBranchAddress("L1_ZdcScintTightVertex", &skims.L1_ZdcScintTightVertex, &skims.b_L1_ZdcScintTightVertex);
  t->SetBranchAddress("L1_ZdcScintTightVertex_Prescl", &skims.L1_ZdcScintTightVertex_Prescl, &skims.b_L1_ZdcScintTightVertex_Prescl);
  t->SetBranchAddress("L1_ZdcScintTightVertex_5bx", &skims.L1_ZdcScintTightVertex_5bx, &skims.b_L1_ZdcScintTightVertex_5bx);
  t->SetBranchAddress("L1_ZdcScintTightVertex_BptxAND", &skims.L1_ZdcScintTightVertex_BptxAND, &skims.b_L1_ZdcScintTightVertex_BptxAND);
  t->SetBranchAddress("L1_ZdcScintTightVertex_BptxAND_Prescl", &skims.L1_ZdcScintTightVertex_BptxAND_Prescl, &skims.b_L1_ZdcScintTightVertex_BptxAND_Prescl);
  t->SetBranchAddress("L1_ZdcScintTightVertex_BptxAND_5bx", &skims.L1_ZdcScintTightVertex_BptxAND_5bx, &skims.b_L1_ZdcScintTightVertex_BptxAND_5bx);
  t->SetBranchAddress("L1_ZeroBias_Ext", &skims.L1_ZeroBias_Ext, &skims.b_L1_ZeroBias_Ext);
  t->SetBranchAddress("L1_ZeroBias_Ext_Prescl", &skims.L1_ZeroBias_Ext_Prescl, &skims.b_L1_ZeroBias_Ext_Prescl);
  t->SetBranchAddress("L1_ZeroBias_Ext_5bx", &skims.L1_ZeroBias_Ext_5bx, &skims.b_L1_ZeroBias_Ext_5bx);
  t->SetBranchAddress("L1Tech_BPTX_minus.v0", &skims.L1Tech_BPTX_minus_v0, &skims.b_L1Tech_BPTX_minus_v0);
  t->SetBranchAddress("L1Tech_BPTX_minus.v0_Prescl", &skims.L1Tech_BPTX_minus_v0_Prescl, &skims.b_L1Tech_BPTX_minus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_minus.v0_5bx", &skims.L1Tech_BPTX_minus_v0_5bx, &skims.b_L1Tech_BPTX_minus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_minus_AND_not_plus.v0", &skims.L1Tech_BPTX_minus_AND_not_plus_v0, &skims.b_L1Tech_BPTX_minus_AND_not_plus_v0);
  t->SetBranchAddress("L1Tech_BPTX_minus_AND_not_plus.v0_Prescl", &skims.L1Tech_BPTX_minus_AND_not_plus_v0_Prescl, &skims.b_L1Tech_BPTX_minus_AND_not_plus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_minus_AND_not_plus.v0_5bx", &skims.L1Tech_BPTX_minus_AND_not_plus_v0_5bx, &skims.b_L1Tech_BPTX_minus_AND_not_plus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_plus.v0", &skims.L1Tech_BPTX_plus_v0, &skims.b_L1Tech_BPTX_plus_v0);
  t->SetBranchAddress("L1Tech_BPTX_plus.v0_Prescl", &skims.L1Tech_BPTX_plus_v0_Prescl, &skims.b_L1Tech_BPTX_plus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_plus.v0_5bx", &skims.L1Tech_BPTX_plus_v0_5bx, &skims.b_L1Tech_BPTX_plus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_NOT_minus.v0", &skims.L1Tech_BPTX_plus_AND_NOT_minus_v0, &skims.b_L1Tech_BPTX_plus_AND_NOT_minus_v0);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_NOT_minus.v0_Prescl", &skims.L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl, &skims.b_L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_NOT_minus.v0_5bx", &skims.L1Tech_BPTX_plus_AND_NOT_minus_v0_5bx, &skims.b_L1Tech_BPTX_plus_AND_NOT_minus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus.v0", &skims.L1Tech_BPTX_plus_AND_minus_v0, &skims.b_L1Tech_BPTX_plus_AND_minus_v0);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus.v0_Prescl", &skims.L1Tech_BPTX_plus_AND_minus_v0_Prescl, &skims.b_L1Tech_BPTX_plus_AND_minus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus.v0_5bx", &skims.L1Tech_BPTX_plus_AND_minus_v0_5bx, &skims.b_L1Tech_BPTX_plus_AND_minus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus_instance1.v0", &skims.L1Tech_BPTX_plus_AND_minus_instance1_v0, &skims.b_L1Tech_BPTX_plus_AND_minus_instance1_v0);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus_instance1.v0_Prescl", &skims.L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl, &skims.b_L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_plus_AND_minus_instance1.v0_5bx", &skims.L1Tech_BPTX_plus_AND_minus_instance1_v0_5bx, &skims.b_L1Tech_BPTX_plus_AND_minus_instance1_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_plus_OR_minus.v0", &skims.L1Tech_BPTX_plus_OR_minus_v0, &skims.b_L1Tech_BPTX_plus_OR_minus_v0);
  t->SetBranchAddress("L1Tech_BPTX_plus_OR_minus.v0_Prescl", &skims.L1Tech_BPTX_plus_OR_minus_v0_Prescl, &skims.b_L1Tech_BPTX_plus_OR_minus_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_plus_OR_minus.v0_5bx", &skims.L1Tech_BPTX_plus_OR_minus_v0_5bx, &skims.b_L1Tech_BPTX_plus_OR_minus_v0_5bx);
  t->SetBranchAddress("L1Tech_BPTX_quiet.v0", &skims.L1Tech_BPTX_quiet_v0, &skims.b_L1Tech_BPTX_quiet_v0);
  t->SetBranchAddress("L1Tech_BPTX_quiet.v0_Prescl", &skims.L1Tech_BPTX_quiet_v0_Prescl, &skims.b_L1Tech_BPTX_quiet_v0_Prescl);
  t->SetBranchAddress("L1Tech_BPTX_quiet.v0_5bx", &skims.L1Tech_BPTX_quiet_v0_5bx, &skims.b_L1Tech_BPTX_quiet_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_HighMultiplicity.v0", &skims.L1Tech_BSC_HighMultiplicity_v0, &skims.b_L1Tech_BSC_HighMultiplicity_v0);
  t->SetBranchAddress("L1Tech_BSC_HighMultiplicity.v0_Prescl", &skims.L1Tech_BSC_HighMultiplicity_v0_Prescl, &skims.b_L1Tech_BSC_HighMultiplicity_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_HighMultiplicity.v0_5bx", &skims.L1Tech_BSC_HighMultiplicity_v0_5bx, &skims.b_L1Tech_BSC_HighMultiplicity_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_inner.v0", &skims.L1Tech_BSC_halo_beam1_inner_v0, &skims.b_L1Tech_BSC_halo_beam1_inner_v0);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_inner.v0_Prescl", &skims.L1Tech_BSC_halo_beam1_inner_v0_Prescl, &skims.b_L1Tech_BSC_halo_beam1_inner_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_inner.v0_5bx", &skims.L1Tech_BSC_halo_beam1_inner_v0_5bx, &skims.b_L1Tech_BSC_halo_beam1_inner_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_outer.v0", &skims.L1Tech_BSC_halo_beam1_outer_v0, &skims.b_L1Tech_BSC_halo_beam1_outer_v0);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_outer.v0_Prescl", &skims.L1Tech_BSC_halo_beam1_outer_v0_Prescl, &skims.b_L1Tech_BSC_halo_beam1_outer_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_halo_beam1_outer.v0_5bx", &skims.L1Tech_BSC_halo_beam1_outer_v0_5bx, &skims.b_L1Tech_BSC_halo_beam1_outer_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_inner.v0", &skims.L1Tech_BSC_halo_beam2_inner_v0, &skims.b_L1Tech_BSC_halo_beam2_inner_v0);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_inner.v0_Prescl", &skims.L1Tech_BSC_halo_beam2_inner_v0_Prescl, &skims.b_L1Tech_BSC_halo_beam2_inner_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_inner.v0_5bx", &skims.L1Tech_BSC_halo_beam2_inner_v0_5bx, &skims.b_L1Tech_BSC_halo_beam2_inner_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_outer.v0", &skims.L1Tech_BSC_halo_beam2_outer_v0, &skims.b_L1Tech_BSC_halo_beam2_outer_v0);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_outer.v0_Prescl", &skims.L1Tech_BSC_halo_beam2_outer_v0_Prescl, &skims.b_L1Tech_BSC_halo_beam2_outer_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_halo_beam2_outer.v0_5bx", &skims.L1Tech_BSC_halo_beam2_outer_v0_5bx, &skims.b_L1Tech_BSC_halo_beam2_outer_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_minBias_OR.v0", &skims.L1Tech_BSC_minBias_OR_v0, &skims.b_L1Tech_BSC_minBias_OR_v0);
  t->SetBranchAddress("L1Tech_BSC_minBias_OR.v0_Prescl", &skims.L1Tech_BSC_minBias_OR_v0_Prescl, &skims.b_L1Tech_BSC_minBias_OR_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_minBias_OR.v0_5bx", &skims.L1Tech_BSC_minBias_OR_v0_5bx, &skims.b_L1Tech_BSC_minBias_OR_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold1.v0", &skims.L1Tech_BSC_minBias_inner_threshold1_v0, &skims.b_L1Tech_BSC_minBias_inner_threshold1_v0);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold1.v0_Prescl", &skims.L1Tech_BSC_minBias_inner_threshold1_v0_Prescl, &skims.b_L1Tech_BSC_minBias_inner_threshold1_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold1.v0_5bx", &skims.L1Tech_BSC_minBias_inner_threshold1_v0_5bx, &skims.b_L1Tech_BSC_minBias_inner_threshold1_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold2.v0", &skims.L1Tech_BSC_minBias_inner_threshold2_v0, &skims.b_L1Tech_BSC_minBias_inner_threshold2_v0);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold2.v0_Prescl", &skims.L1Tech_BSC_minBias_inner_threshold2_v0_Prescl, &skims.b_L1Tech_BSC_minBias_inner_threshold2_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold2.v0_5bx", &skims.L1Tech_BSC_minBias_inner_threshold2_v0_5bx, &skims.b_L1Tech_BSC_minBias_inner_threshold2_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold1.v0", &skims.L1Tech_BSC_minBias_threshold1_v0, &skims.b_L1Tech_BSC_minBias_threshold1_v0);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold1.v0_Prescl", &skims.L1Tech_BSC_minBias_threshold1_v0_Prescl, &skims.b_L1Tech_BSC_minBias_threshold1_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold1.v0_5bx", &skims.L1Tech_BSC_minBias_threshold1_v0_5bx, &skims.b_L1Tech_BSC_minBias_threshold1_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold2.v0", &skims.L1Tech_BSC_minBias_threshold2_v0, &skims.b_L1Tech_BSC_minBias_threshold2_v0);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold2.v0_Prescl", &skims.L1Tech_BSC_minBias_threshold2_v0_Prescl, &skims.b_L1Tech_BSC_minBias_threshold2_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_minBias_threshold2.v0_5bx", &skims.L1Tech_BSC_minBias_threshold2_v0_5bx, &skims.b_L1Tech_BSC_minBias_threshold2_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_splash_beam1.v0", &skims.L1Tech_BSC_splash_beam1_v0, &skims.b_L1Tech_BSC_splash_beam1_v0);
  t->SetBranchAddress("L1Tech_BSC_splash_beam1.v0_Prescl", &skims.L1Tech_BSC_splash_beam1_v0_Prescl, &skims.b_L1Tech_BSC_splash_beam1_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_splash_beam1.v0_5bx", &skims.L1Tech_BSC_splash_beam1_v0_5bx, &skims.b_L1Tech_BSC_splash_beam1_v0_5bx);
  t->SetBranchAddress("L1Tech_BSC_splash_beam2.v0", &skims.L1Tech_BSC_splash_beam2_v0, &skims.b_L1Tech_BSC_splash_beam2_v0);
  t->SetBranchAddress("L1Tech_BSC_splash_beam2.v0_Prescl", &skims.L1Tech_BSC_splash_beam2_v0_Prescl, &skims.b_L1Tech_BSC_splash_beam2_v0_Prescl);
  t->SetBranchAddress("L1Tech_BSC_splash_beam2.v0_5bx", &skims.L1Tech_BSC_splash_beam2_v0_5bx, &skims.b_L1Tech_BSC_splash_beam2_v0_5bx);
  t->SetBranchAddress("L1Tech_CASTOR_HaloMuon.v0", &skims.L1Tech_CASTOR_HaloMuon_v0, &skims.b_L1Tech_CASTOR_HaloMuon_v0);
  t->SetBranchAddress("L1Tech_CASTOR_HaloMuon.v0_Prescl", &skims.L1Tech_CASTOR_HaloMuon_v0_Prescl, &skims.b_L1Tech_CASTOR_HaloMuon_v0_Prescl);
  t->SetBranchAddress("L1Tech_CASTOR_HaloMuon.v0_5bx", &skims.L1Tech_CASTOR_HaloMuon_v0_5bx, &skims.b_L1Tech_CASTOR_HaloMuon_v0_5bx);
  t->SetBranchAddress("L1Tech_HCAL_HBHE_totalOR.v0", &skims.L1Tech_HCAL_HBHE_totalOR_v0, &skims.b_L1Tech_HCAL_HBHE_totalOR_v0);
  t->SetBranchAddress("L1Tech_HCAL_HBHE_totalOR.v0_Prescl", &skims.L1Tech_HCAL_HBHE_totalOR_v0_Prescl, &skims.b_L1Tech_HCAL_HBHE_totalOR_v0_Prescl);
  t->SetBranchAddress("L1Tech_HCAL_HBHE_totalOR.v0_5bx", &skims.L1Tech_HCAL_HBHE_totalOR_v0_5bx, &skims.b_L1Tech_HCAL_HBHE_totalOR_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RB0_Cosmics.v0", &skims.L1Tech_RPC_TTU_RB0_Cosmics_v0, &skims.b_L1Tech_RPC_TTU_RB0_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RB0_Cosmics.v0_Prescl", &skims.L1Tech_RPC_TTU_RB0_Cosmics_v0_Prescl, &skims.b_L1Tech_RPC_TTU_RB0_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RB0_Cosmics.v0_5bx", &skims.L1Tech_RPC_TTU_RB0_Cosmics_v0_5bx, &skims.b_L1Tech_RPC_TTU_RB0_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus1_Cosmics.v0", &skims.L1Tech_RPC_TTU_RBminus1_Cosmics_v0, &skims.b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus1_Cosmics.v0_Prescl", &skims.L1Tech_RPC_TTU_RBminus1_Cosmics_v0_Prescl, &skims.b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus1_Cosmics.v0_5bx", &skims.L1Tech_RPC_TTU_RBminus1_Cosmics_v0_5bx, &skims.b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus2_Cosmics.v0", &skims.L1Tech_RPC_TTU_RBminus2_Cosmics_v0, &skims.b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus2_Cosmics.v0_Prescl", &skims.L1Tech_RPC_TTU_RBminus2_Cosmics_v0_Prescl, &skims.b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBminus2_Cosmics.v0_5bx", &skims.L1Tech_RPC_TTU_RBminus2_Cosmics_v0_5bx, &skims.b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus1_Cosmics.v0", &skims.L1Tech_RPC_TTU_RBplus1_Cosmics_v0, &skims.b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus1_Cosmics.v0_Prescl", &skims.L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl, &skims.b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus1_Cosmics.v0_5bx", &skims.L1Tech_RPC_TTU_RBplus1_Cosmics_v0_5bx, &skims.b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus2_Cosmics.v0", &skims.L1Tech_RPC_TTU_RBplus2_Cosmics_v0, &skims.b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus2_Cosmics.v0_Prescl", &skims.L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl, &skims.b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBplus2_Cosmics.v0_5bx", &skims.L1Tech_RPC_TTU_RBplus2_Cosmics_v0_5bx, &skims.b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBst1_collisions.v0", &skims.L1Tech_RPC_TTU_RBst1_collisions_v0, &skims.b_L1Tech_RPC_TTU_RBst1_collisions_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBst1_collisions.v0_Prescl", &skims.L1Tech_RPC_TTU_RBst1_collisions_v0_Prescl, &skims.b_L1Tech_RPC_TTU_RBst1_collisions_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_RBst1_collisions.v0_5bx", &skims.L1Tech_RPC_TTU_RBst1_collisions_v0_5bx, &skims.b_L1Tech_RPC_TTU_RBst1_collisions_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_barrel_Cosmics.v0", &skims.L1Tech_RPC_TTU_barrel_Cosmics_v0, &skims.b_L1Tech_RPC_TTU_barrel_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_barrel_Cosmics.v0_Prescl", &skims.L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl, &skims.b_L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_barrel_Cosmics.v0_5bx", &skims.L1Tech_RPC_TTU_barrel_Cosmics_v0_5bx, &skims.b_L1Tech_RPC_TTU_barrel_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_RPC_TTU_pointing_Cosmics.v0", &skims.L1Tech_RPC_TTU_pointing_Cosmics_v0, &skims.b_L1Tech_RPC_TTU_pointing_Cosmics_v0);
  t->SetBranchAddress("L1Tech_RPC_TTU_pointing_Cosmics.v0_Prescl", &skims.L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl, &skims.b_L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl);
  t->SetBranchAddress("L1Tech_RPC_TTU_pointing_Cosmics.v0_5bx", &skims.L1Tech_RPC_TTU_pointing_Cosmics_v0_5bx, &skims.b_L1Tech_RPC_TTU_pointing_Cosmics_v0_5bx);
  t->SetBranchAddress("L1Tech_ZDC_Scint_loose_vertex.v0", &skims.L1Tech_ZDC_Scint_loose_vertex_v0, &skims.b_L1Tech_ZDC_Scint_loose_vertex_v0);
  t->SetBranchAddress("L1Tech_ZDC_Scint_loose_vertex.v0_Prescl", &skims.L1Tech_ZDC_Scint_loose_vertex_v0_Prescl, &skims.b_L1Tech_ZDC_Scint_loose_vertex_v0_Prescl);
  t->SetBranchAddress("L1Tech_ZDC_Scint_loose_vertex.v0_5bx", &skims.L1Tech_ZDC_Scint_loose_vertex_v0_5bx, &skims.b_L1Tech_ZDC_Scint_loose_vertex_v0_5bx);
  t->SetBranchAddress("L1Tech_ZDC_Scint_minus.v0", &skims.L1Tech_ZDC_Scint_minus_v0, &skims.b_L1Tech_ZDC_Scint_minus_v0);
  t->SetBranchAddress("L1Tech_ZDC_Scint_minus.v0_Prescl", &skims.L1Tech_ZDC_Scint_minus_v0_Prescl, &skims.b_L1Tech_ZDC_Scint_minus_v0_Prescl);
  t->SetBranchAddress("L1Tech_ZDC_Scint_minus.v0_5bx", &skims.L1Tech_ZDC_Scint_minus_v0_5bx, &skims.b_L1Tech_ZDC_Scint_minus_v0_5bx);
  t->SetBranchAddress("L1Tech_ZDC_Scint_plus.v0", &skims.L1Tech_ZDC_Scint_plus_v0, &skims.b_L1Tech_ZDC_Scint_plus_v0);
  t->SetBranchAddress("L1Tech_ZDC_Scint_plus.v0_Prescl", &skims.L1Tech_ZDC_Scint_plus_v0_Prescl, &skims.b_L1Tech_ZDC_Scint_plus_v0_Prescl);
  t->SetBranchAddress("L1Tech_ZDC_Scint_plus.v0_5bx", &skims.L1Tech_ZDC_Scint_plus_v0_5bx, &skims.b_L1Tech_ZDC_Scint_plus_v0_5bx);
  t->SetBranchAddress("L1Tech_ZDC_Scint_tight_vertex.v0", &skims.L1Tech_ZDC_Scint_tight_vertex_v0, &skims.b_L1Tech_ZDC_Scint_tight_vertex_v0);
  t->SetBranchAddress("L1Tech_ZDC_Scint_tight_vertex.v0_Prescl", &skims.L1Tech_ZDC_Scint_tight_vertex_v0_Prescl, &skims.b_L1Tech_ZDC_Scint_tight_vertex_v0_Prescl);
  t->SetBranchAddress("L1Tech_ZDC_Scint_tight_vertex.v0_5bx", &skims.L1Tech_ZDC_Scint_tight_vertex_v0_5bx, &skims.b_L1Tech_ZDC_Scint_tight_vertex_v0_5bx);

}
