#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/DiHadronCorrelationMultiBaseFWLite.h"
#include "FlowCorrAna/DiHadronCorrelationAnalyzer/interface/EventShape.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TList.h>
#include <TIterator.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TObjString.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <iostream>

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

DiHadronCorrelationMultiBaseFWLite::DiHadronCorrelationMultiBaseFWLite(fwlite::ChainEvent& Event) :
  event(Event), 
  trgID(kTrack),
  assID(kTrack),
  centFile(0),
  nCentBins(40),
  centRunnum(181502),
  hEffWeight(0),
  hTrgWeight(0),
  hPileup_distfunc(0),
  checksign(-1),
  eventClass(-1),
  hf(0),
  hft(0),
  npixel(0),
  zdc(0),
  bin(-1),
  b(0),
  npart(0),
  ncoll(0),
  nhard(0),
  phi0(0),
  nEvent(0),
  nMult(0),
  nMultAll_trg(0),
  nMultAll_ass(0),
  nMultCorr(0),
  nMultAllCorr_trg(0),
  nMultAllCorr_ass(0),
  nJets(0),
  nVertices(0),
  maxofflinetracks(0),
  secofflinetracks(0),
  thirdofflinetracks(0),
  minVtxSep(99999.9), 
  minVtxSep2(99999.9),
  NEtaBins(40),
  NPhiBins(32),
  xVtx(-99999.),
  yVtx(-99999.),
  zVtx(-99999.),	
  xVtxError(99999.),
  yVtxError(99999.),
  zVtxError(99999.),     
  xVtxSim(-99999.),
  yVtxSim(-99999.),
  zVtxSim(-99999.),
  hiCentrality(-1),
  EPIndex(-1),
  EPAngle(-9999.9),
  massTrg(0.1396),
  massAss(0.1396)
{

  TH1::SetDefaultSumw2();

  eventNtuple = new TNtuple("eventntuple","event variable ntuple","run:lumi:beamspotx:beamspoty:beamspotz:nmult:njets:nvertices:maxofflinetracks:vx:vy:vz:thrust:sphericity:recoil");
//  particleNtuple = new TNtuple("particlentuple","particle ntuple","eta:phi:pt");
  trackNtuple = new TNtuple("trackntuple","track ntuple","vx:vy:vz:dz:dxy:dzerror:dxyerror:nhits:chi2:algo:eta:phi:pt:pterror");
//  jetNtuple = new TNtuple("jetntuple","jet ntuple","eta:phi:et");
  highmultNtuple = new TNtuple("highmultntuple","","run:lumi:evtnum:nmult");
  hiGenInfoNtuple = new TNtuple("higeninfontuple","","run:b:npart:ncoll:nhard:phi0:nmult:hft:npixel:zdc:bin");

  cutPara.nmin=-1;
  cutPara.nmax=-1;
  cutPara.centmin=-1;
  cutPara.centmax=-1;
  cutPara.xvtxcenter=0.;
  cutPara.yvtxcenter=0.;
  cutPara.zvtxcenter=0.;
  cutPara.rhomin=0.;
  cutPara.rhomax=9999.;
  cutPara.zvtxmin=-9999.;
  cutPara.zvtxmax=9999.;  
  cutPara.zvtxbin=2.0;
  cutPara.vtxsepmin=0;
  cutPara.nvtxmax=100;
  cutPara.jetetmin=0;
  cutPara.jetetmax=10000;
  cutPara.jetetfraction=0.05;
  cutPara.pthard1=1.0;
  cutPara.pthard2=0.4;
  cutPara.delta=0.7;
  cutPara.IsGenMult=0;
  cutPara.IsGenVtx=0;
  cutPara.IsVtxSel=0;
  cutPara.IsInvMass=0;
  cutPara.IsCorr=1;
  cutPara.IsHI=0;
  cutPara.IsDoEventShape=0;
  cutPara.IsTrackNtuple=0;
  cutPara.IsHIGenInfoNtuple=0;
  cutPara.IsLeadTrack=0;
  cutPara.IsSubJet=0;
  cutPara.IsMonoJet=0;
  cutPara.IsFullMatrix=0;
}

DiHadronCorrelationMultiBaseFWLite::~DiHadronCorrelationMultiBaseFWLite()
{}

//
// member functions
//

void DiHadronCorrelationMultiBaseFWLite::Process()
{  	
  Init();
  MakeHists();
 
  int nEventMax = event.size();
//  int nEventMax = 10;
  for(event.toBegin(); !event.atEnd(); ++event, ++nEvent) 
  {	  
    if( nEvent == nEventMax ) break;
    if( event.id().run() < cutPara.runmin || event.id().run() > cutPara.runmax ) continue;
    if( nEvent % 100 == 0 ) cout << "Processing " << nEvent<< "th event: "
                                  << "run " << event.id().run() 
                                  << ", lumi " << event.luminosityBlock() 
                                  << ", evt " << event.id().event() << endl;
    Analyze(nEvent);
  }

  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
  { 
    ptMean_trg[itrg]=hpTCorr_Signal_trg[itrg]->GetMean();
    ptMean2_trg[itrg]=hpTCorr_Signal_trg[itrg]->GetMean()*hpTCorr_Signal_trg[itrg]->GetMean()+hpTCorr_Signal_trg[itrg]->GetRMS()*hpTCorr_Signal_trg[itrg]->GetRMS();
  } 
  for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
  {
    ptMean_ass[jass]=hpTCorr_Signal_ass[jass]->GetMean();
    ptMean2_ass[jass]=hpTCorr_Signal_ass[jass]->GetMean()*hpTCorr_Signal_ass[jass]->GetMean()+hpTCorr_Signal_ass[jass]->GetRMS()*hpTCorr_Signal_ass[jass]->GetRMS();
  }
}

// ------------ method called to for each event  ------------

void DiHadronCorrelationMultiBaseFWLite::Analyze(int ievt)
{
  nMult=0;
  nMultCorr=0;
  nMultAll_trg=0;
  nMultAllCorr_trg=0;
  nMultAll_ass=0;
  nMultAllCorr_ass=0;

  eventcorr = new DiHadronCorrelationEvent();

  // Select trigger bit or process IDs 
  if(!SelectTriggerBit()) return; 

  // Select centrality
  hiCentrality = -1;
  if(!HFhitBinMap.empty()) hiCentrality = GetCentralityBin();
  if((hiCentrality<cutPara.centmin || hiCentrality>=cutPara.centmax) && (cutPara.centmin!=-1 || cutPara.centmax!=-1)) return;

  // Select vertex
  double zvtxbincentertmp=0;
  if(cutPara.IsVtxSel)
  {
    GetVertices();
    double zVtxtmp = zVtx-cutPara.zvtxcenter;
    double yVtxtmp = yVtx-cutPara.yvtxcenter;
    double xVtxtmp = xVtx-cutPara.xvtxcenter;
    double rhotmp = sqrt(xVtxtmp*xVtxtmp+yVtxtmp*yVtxtmp);
    zvtxbincentertmp = (int)((zVtxtmp-cutPara.zvtxmin)/cutPara.zvtxbin)*cutPara.zvtxbin+cutPara.zvtxmin+cutPara.zvtxbin/2;
    if( zVtxtmp<cutPara.zvtxmin || zVtxtmp>cutPara.zvtxmax || rhotmp<cutPara.rhomin || rhotmp>cutPara.rhomax ) return;
    if(cutPara.IsGenVtx)
    {
      GetSimVertices();
      hZVtxRecoVsSim->Fill(zVtx,zVtxSim);
      hXVtxRecoVsSim->Fill(xVtx,xVtxSim);
      hYVtxRecoVsSim->Fill(yVtx,yVtxSim);
    }

    if(nVertices>1 && minVtxSep<cutPara.vtxsepmin) return;
    if(nVertices>cutPara.nvtxmax) return;
    if(hPileup_distfunc && secofflinetracks>hPileup_distfunc->GetBinContent(hPileup_distfunc->FindBin(minVtxSep,maxofflinetracks))) return;
//    if(maxofflinetracks/300.*25 < secofflinetracks) return;
  }

  // Select multiplicity
  GetMult();
  if((nMult<cutPara.nmin || nMult>=cutPara.nmax) && (cutPara.nmin!=-1 || cutPara.nmax!=-1)) return;
  hMultRawAll->Fill(nMult);
  hNVtxVsNMult->Fill(nMult,nVertices);
  hMultCorrAll->Fill(nMultCorr,1.0/GetTrgWeight(nMult));
  hZVtx->Fill(zVtx);
  hXYVtx->Fill(xVtx,yVtx);
  hNVtx->Fill(nVertices);
  hXYZVtxSepMin->Fill(minVtxSep);
  hXYZVtxSepMin2->Fill(minVtxSep2);
  hMultMaxVsSec->Fill(maxofflinetracks,secofflinetracks);
  hMultMaxVsSecVsZVtxSep->Fill(maxofflinetracks,secofflinetracks,minVtxSep);
  hMultMaxVsThird->Fill(maxofflinetracks,thirdofflinetracks);
  hMultMaxVsThirdVsZVtxSep->Fill(maxofflinetracks,thirdofflinetracks,minVtxSep2);

  if(cutPara.IsVtxSel && cutPara.IsGenVtx)
  {
    hZVtxResVsNMult->Fill(nMult,zVtx-zVtxSim);
    hXVtxResVsNMult->Fill(nMult,xVtx-xVtxSim);
    hYVtxResVsNMult->Fill(nMult,yVtx-yVtxSim);
  }

  hCentrality->Fill((double)hiCentrality);

  if(EPIndex>=0) 
  {
    EPAngle=GetEventPlaneAngle(EPIndex);
    hEPAngle->Fill(EPAngle);
  }

  // Jet Selections 
  if(cutPara.njetsmin!=-1 || cutPara.njetsmax!=-1) GetJets();
  if((nJets<cutPara.njetsmin || nJets>=cutPara.njetsmax) && (cutPara.njetsmin!=-1 || cutPara.njetsmax!=-1)) return;

  switch (trgID)
  {
     case kGenParticle:
       LoopParticles(1);
       break;
     case kTrack:
       LoopTracks(1,cutPara.trgtrackCollection);
       break;
     case kJet:
       massTrg=0.0;
       LoopJets(1);       
       break;
     case kMuon:
       massTrg=0.1057;
       LoopMuons(1);
       break;
     case kEcalSC:
       LoopEcalSC(1); 
       break;
     case kEcalBC:
       LoopEcalBC(1);
       break;
     case kPFHadron:
       LoopPFCandidates(1,reco::PFCandidate::h);
       break;
     case kPFPhoton:
       massTrg=0.0;
       LoopPFCandidates(1,reco::PFCandidate::gamma);
       break;
     case kPFHadronPhoton:
       LoopPFCandidates(1,reco::PFCandidate::h);
       LoopPFCandidates(1,reco::PFCandidate::gamma);
       break;
     case kPFPhotonTrack:
       LoopTracks(1,cutPara.trgtrackCollection);
       LoopPFCandidates(1,reco::PFCandidate::gamma);
     case kPFElectron:
       massTrg=0.000511;
       LoopPFCandidates(1,reco::PFCandidate::e);
       break;
     case kPFMuon:
       massTrg=0.1057;
       LoopPFCandidates(1,reco::PFCandidate::mu);
       break;
     case kPFNeutral:
       LoopPFCandidates(1,reco::PFCandidate::h0);
       break;
     case kPFHadronHF:
       LoopPFCandidates(1,reco::PFCandidate::h_HF);
       break;
     case kPFEgammaHF:
       LoopPFCandidates(1,reco::PFCandidate::egamma_HF);
       break;
     case kPionZero:
       LoopPionZeros(1,0.0);
       break;
     case kPionZeroBkgUp:
       LoopPionZeros(1,0.04);
       break;
     case kPionZeroBkgDown:
       LoopPionZeros(1,-0.04);
       break;
     case kCaloTower:
       LoopCaloTower(1);
       break;
     case kKshort:
       massTrg=0.498;
       LoopV0Candidates(1, "Kshort");
       break;
     case kLambda:
       massTrg=1.116;
       LoopV0Candidates(1, "Lambda");
       break;
     default:
       break;
  }

  switch (assID)
  {
     case kGenParticle:
       LoopParticles(0);
       break;     
     case kTrack:
       LoopTracks(0,cutPara.asstrackCollection);
       break;
     case kJet:
       massAss=0.0;
       LoopJets(0);
       break;
     case kMuon:
       massAss=0.1057;
       LoopMuons(0);
       break;
     case kEcalSC:
       LoopEcalSC(0);
       break;
     case kEcalBC:
       LoopEcalBC(0);
       break;
     case kPFHadron:
       LoopPFCandidates(0,reco::PFCandidate::h);
       break;
     case kPFPhoton:
       massAss=0.0;
       LoopPFCandidates(0,reco::PFCandidate::gamma);
       break;
     case kPFHadronPhoton:
       LoopPFCandidates(0,reco::PFCandidate::h);
       LoopPFCandidates(0,reco::PFCandidate::gamma);
       break;
     case kPFPhotonTrack:
       LoopTracks(0,cutPara.asstrackCollection);
       LoopPFCandidates(0,reco::PFCandidate::gamma);
     case kPFElectron:
       massAss=0.000511;
       LoopPFCandidates(0,reco::PFCandidate::e);
       break;
     case kPFMuon:
       massAss=0.1057;
       LoopPFCandidates(0,reco::PFCandidate::mu);
       break;
     case kPFNeutral:
       LoopPFCandidates(0,reco::PFCandidate::h0);
       break;
     case kPFHadronHF:
       LoopPFCandidates(0,reco::PFCandidate::h_HF);
       break;
     case kPFEgammaHF:
       LoopPFCandidates(0,reco::PFCandidate::egamma_HF);
       break;
     case kPionZero:
       LoopPionZeros(0,0.0);
       break;
     case kPionZeroBkgUp:
       LoopPionZeros(0,0.04);
       break;
     case kPionZeroBkgDown:
       LoopPionZeros(0,-0.04);
       break;
     case kCaloTower:
       LoopCaloTower(0);
       break;
     case kKshort:
       massAss=0.498;
       LoopV0Candidates(0, "Kshort");
       break;
     case kLambda:
       massAss=1.116;
       LoopV0Candidates(0, "Lambda");
       break;
     default:
       break;
  }
  hMultRawTrigVsAssoc->Fill(nMultAll_trg,nMultAll_ass);

  // event shape
  double thrust = 0;
  double recoil = 0;
  double sphericity = 0;
  if(cutPara.IsDoEventShape)
  {
    EventShape t((eventcorr->pVect_all).begin(), (eventcorr->pVect_all).end());
    t.SetTran();
    thrust = t.thrust();
    recoil = t.recoil();
    sphericity = t.sphericity();
  }

  // Fill gen-level information ntuple
  if(cutPara.IsHIGenInfoNtuple)
  {
    fwlite::Handle<HepMCProduct> himc;
    himc.getByLabel(event,"generator");
    const HepMC::GenEvent* hievt = himc->GetEvent();
    const HepMC::HeavyIon* hi = hievt->heavy_ion();

    if(hi){
      b = hi->impact_parameter();
      npart = hi->Npart_proj()+hi->Npart_targ();
      ncoll = hi->Ncoll();
      nhard = hi->Ncoll_hard();
      phi0 = hi->event_plane_angle();
    }
    hiGenInfoNtuple->Fill(event.id().run(),b,npart,ncoll,nhard,phi0,nMult,hft,npixel,zdc,bin);
  }

  if(trgID!=kGenParticle && assID!=kGenParticle)
  {
    // get beamspot
    fwlite::Handle<reco::BeamSpot> beamspot;
    beamspot.getByLabel(event, "offlineBeamSpot");

    float ntupledata[15]={0};
    ntupledata[0] = event.id().run();
    ntupledata[1] = event.luminosityBlock();
    if(beamspot.isValid())
    {
      ntupledata[2] = beamspot->x0();
      ntupledata[3] = beamspot->y0();
      ntupledata[4] = beamspot->z0();
    }
    ntupledata[5] = nMult;
    ntupledata[6] = nJets;
    ntupledata[7] = nVertices;
    ntupledata[8] = maxofflinetracks;
    ntupledata[9] = xVtx;
    ntupledata[10] = yVtx;
    ntupledata[11] = zVtx;
    ntupledata[12] = thrust;
    ntupledata[13] = sphericity;    
    ntupledata[14] = recoil;
//    eventNtuple->Fill(ntupledata);
  }

  if(cutPara.IsInvMass) FillHistsInvariantMass(*eventcorr);

  eventcorr->nmult=nMult;
  eventcorr->centbin=hiCentrality;
  eventcorr->zvtx=zVtx;
  eventcorr->epangle=EPAngle;

  eventcorrArray.push_back(*eventcorr);

  delete eventcorr;
}


void DiHadronCorrelationMultiBaseFWLite::Init()
{
  if(centFile) HFhitBinMap = getCentralityFromFile(centFile,"makeCentralityTableTFile",centTableName.Data(),0,1000000);
  if(HFhitBinMap.empty()) cout<<"Centrality table is empty!"<<endl;
}

void DiHadronCorrelationMultiBaseFWLite::MakeHists()
{

  // pt bins
  std::vector<double> ptBins;
/*
  const double small = 1e-3;
  double ptb;

  // simple rebinning possible with a rebinning facto n = 2, 3, 6 !

  for(ptb =   0  ; ptb <   1.2-small; ptb +=  0.05) ptBins.push_back(ptb); // 24 bins
  for(ptb =   1.2; ptb <   2.4-small; ptb +=  0.1 ) ptBins.push_back(ptb); // 12 bins
  for(ptb =   2.4; ptb <   7.2-small; ptb +=  0.4 ) ptBins.push_back(ptb); // 12 bins
  for(ptb =   7.2; ptb <  14.4-small; ptb +=  1.2 ) ptBins.push_back(ptb); // 6 bins
  for(ptb =  14.4; ptb <  28.8-small; ptb +=  2.4 ) ptBins.push_back(ptb); // 6 bins 
  for(ptb =  28.8; ptb <  48.0-small; ptb +=  3.2 ) ptBins.push_back(ptb); // 6 bins
  for(ptb =  48.0; ptb <  86.4-small; ptb +=  6.4 ) ptBins.push_back(ptb); // 6 bins
  for(ptb =  86.4; ptb < 189.6-small; ptb +=  8.6 ) ptBins.push_back(ptb); // 6 bins
  ptBins.push_back(189.6);
*/
  ptBins.push_back(0.0);
  ptBins.push_back(0.3);
  ptBins.push_back(0.5);
  ptBins.push_back(0.7);
  ptBins.push_back(1.0);
  ptBins.push_back(1.3);
  ptBins.push_back(1.6);
  ptBins.push_back(2.0);
  ptBins.push_back(2.5);
  ptBins.push_back(3.0);
  ptBins.push_back(3.5);
  ptBins.push_back(4.0);
  ptBins.push_back(5.0);
  ptBins.push_back(6.0);
  ptBins.push_back(7.0);
  ptBins.push_back(8.0);

  hPtAll_trg = new TH1D("ptall_trg",";p_{T}(GeV/c)",ptBins.size()-1, &ptBins[0]);

  hNVtx = new TH1D("nvtx",";nVertices",51,-0.5,50.5);
  hNVtxVsNMult = new TH2D("nvtxvsnmult",";nMult;nVertices",500,0,500,50,0,50);
  hZVtx = new TH1D("zvtx",";z_{vtx} (cm)",160,-20,20);
  hXYVtx = new TH2D("xyvtx",";x_{vtx} (cm);y_{vtx} (cm)",1000,-1,1,1000,-1,1);
  hZVtxSep = new TH1D("zvtxsep",";z_{vtx}-z^{max}_{vtx} (cm)",2000,-20,20);
  hXVtxSep = new TH1D("xvtxsep",";x_{vtx}-x^{max}_{vtx} (cm)",2000,-20,20);
  hYVtxSep = new TH1D("yvtxsep",";y_{vtx}-y^{max}_{vtx} (cm)",2000,-20,20);
  hXYZVtxSep = new TH1D("xyzvtxsep",";xyz_{vtx}-xyz^{max}_{vtx} (cm)",2000,0,40);
  hXYZVtxSepMin = new TH1D("xyzvtxsepmin",";(xyz_{vtx}-xyz^{max}_{vtx})_{min} (cm)",2000,0,40);
  hXYZVtxSepMin2 = new TH1D("xyzvtxsepmin2",";(xyz_{vtx}-xyz^{max}_{vtx})_{min} (cm)",2000,0,40);
  hZVtxSim = new TH1D("zvtxsim",";z_{vtx} (cm)",160,-20,20);
  hXYVtxSim = new TH2D("xyvtxsim",";x_{vtx} (cm);y_{vtx} (cm)",1000,-1,1,1000,-1,1);
  hZVtxRecoVsSim = new TH2D("zvtxrecovssim",";z^{SIM}_{vtx} (cm);z^{RECO}_{vtx} (cm)",160,-20,20,160,-20,20);
  hXVtxRecoVsSim = new TH2D("xvtxrecovssim",";x^{SIM}_{vtx} (cm);x^{RECO}_{vtx} (cm)",1000,-1,1,1000,-1,1);
  hYVtxRecoVsSim = new TH2D("yvtxrecovssim",";y^{SIM}_{vtx} (cm);y^{RECO}_{vtx} (cm)",1000,-1,1,1000,-1,1);
  hZVtxResVsNMult = new TH2D("zvtxresvsnmult",";nMult;z^{RECO}_{vtx}-z^{SIM}_{vtx} (cm)",500,0,500,1000,-1,1);
  hXVtxResVsNMult = new TH2D("xvtxresvsnmult",";nMult;x^{RECO}_{vtx}-x^{SIM}_{vtx} (cm)",500,0,500,1000,-1,1);
  hYVtxResVsNMult = new TH2D("yvtxresvsnmult",";nMult;y^{RECO}_{vtx}-y^{SIM}_{vtx} (cm)",500,0,500,1000,-1,1);
  hTrkZVtxRes = new TH1D("trkzvtxres",";z^{trk}_{vtx}-z^{RECO}_{vtx} (cm)",1000,-2,2);
  hTrkXYVtxRes = new TH2D("trkxyvtxres",";x^{trk}_{vtx}-x^{RECO}_{vtx} (cm);y^{trk}_{vtx}-y^{RECO}_{vtx} (cm)",1000,-1,1,1000,-1,1);
  hTrkZVtxResSig = new TH1D("trkzvtxressig",";dz^{trk}_{vtx}/#sigma_{z}",1000,-5,5);
  hTrkXYVtxResSig = new TH2D("trkxyvtxressig",";dx^{trk}_{vtx}/#sigma_{x};dy^{trk}_{vtx}/#sigma_{y}",1000,-5,5,1000,-5,5);
  hTrkZVtxResVsNMult = new TH2D("trkzvtxresvsnmult",";nMult;z^{trk}_{vtx}-z^{RECO}_{vtx} (cm)",500,0,500,1000,-1,1);
  hTrkXVtxResVsNMult = new TH2D("trkxvtxresvsnmult",";nMult;x^{trk}_{vtx}-x^{RECO}_{vtx} (cm)",500,0,500,1000,-1,1);
  hTrkYVtxResVsNMult = new TH2D("trkyvtxresvsnmult",";nMult;y^{trk}_{vtx}-y^{RECO}_{vtx} (cm)",500,0,500,1000,-1,1);
  hTrkZVtxResVsPt = new TH2D("trkzvtxresvspt",";p_{T}(GeV/c);z^{trk}_{vtx}-z^{RECO}_{vtx} (cm)",25,0,5,1000,-1,1);
  hTrkXVtxResVsPt = new TH2D("trkxvtxresvspt",";p_{T}(GeV/c);x^{trk}_{vtx}-x^{RECO}_{vtx} (cm)",25,0,5,1000,-1,1);
  hTrkYVtxResVsPt = new TH2D("trkyvtxresvspt",";p_{T}(GeV/c);y^{trk}_{vtx}-y^{RECO}_{vtx} (cm)",25,0,5,1000,-1,1);
  hTrkZVtxSimResVsNMult = new TH2D("trkzvtxsimresvsnmult",";nMult;z^{trk}_{vtx}-z^{SIM}_{vtx} (cm)",500,0,500,1000,-1,1);
  hTrkXVtxSimResVsNMult = new TH2D("trkxvtxsimresvsnmult",";nMult;x^{trk}_{vtx}-x^{SIM}_{vtx} (cm)",500,0,500,1000,-1,1);
  hTrkYVtxSimResVsNMult = new TH2D("trkyvtxsimresvsnmult",";nMult;y^{trk}_{vtx}-y^{SIM}_{vtx} (cm)",500,0,500,1000,-1,1);
  hMultRawAll = new TH1D("multrawall",";n",10000,0,10000);
  hMultCorrAll = new TH1D("multcorrall",";n",10000,0,10000);
  hMultRawTrigVsAssoc = new TH2D("multrawtrigvsassoc",";n_{trig};n_{assoc}",500,0,500,500,0,500);
  hMultMaxVsSec = new TH2D("multmaxvssec",";n_{max};n_{sec}",500,0,500,500,0,500);
  hMultMaxVsThird = new TH2D("multmaxvsthird",";n_{max};n_{third}",500,0,500,500,0,500);
  hMultMaxVsSecVsZVtxSep = new TH3D("multmaxvssecvszvtxsep",";n_{max};n_{sec};|z_{vtx}-z^{max}_{vtx}| (cm)",500,0,500,500,0,500,20,0,4.0);
  hMultMaxVsThirdVsZVtxSep = new TH3D("multmaxvsthirdvszvtxsep",";n_{max};n_{third};|z_{vtx}-z^{max}_{vtx}| (cm)",500,0,500,500,0,500,20,0,4.0);
//  hPtAll_trg = new TH1D("ptall_trg",";p_{T}(GeV/c)",1000,0,250);
  hdNdetadptAll_trg = new TH2D("dNdetadptall_trg",";#eta;pT(GeV)",40,-6.0,6.0,20,0,10.0);
  hdNdetadphiAll_trg = new TH2D("dNdetadphiall_trg",";#eta;#phi",40,-6.0,6.0,32,-PI,PI);
  hPtAll_ass = new TH1D("ptall_ass",";p_{T}(GeV/c)",2000,0,200);
  hdNdetadptAll_ass = new TH2D("dNdetadptall_ass",";#eta;pT(GeV)",40,-6.0,6.0,20,0,10.0);
  hdNdetadphiAll_ass = new TH2D("dNdetadphiall_ass",";#eta;#phi",40,-6.0,6.0,32,-PI,PI);
  hPtCorrAll_trg = new TH1D("ptcorrall_trg",";p_{T}(GeV/c)",ptBins.size()-1, &ptBins[0]);
  hdNdetadptCorrAll_trg = new TH2D("dNdetadptcorrall_trg",";#eta;pT(GeV)",40,-6.0,6.0,20,0,10.0);
  hdNdetadphiCorrAll_trg = new TH2D("dNdetadphicorrall_trg",";#eta;#phi",40,-6.0,6.0,32,-PI,PI);
  hPtCorrAll_ass = new TH1D("ptcorrall_ass",";p_{T}(GeV/c)",1000,0,100);
  hdNdetadptCorrAll_ass = new TH2D("dNdetadptcorrall_ass",";#eta;pT(GeV)",60,-6.0,6.0,20,0,10.0);
  hdNdetadphiCorrAll_ass = new TH2D("dNdetadphicorrall_ass",";#eta;#phi",60,-6.0,6.0,32,-PI,PI);
  hdNJetsAll = new TH1D("dNjetsall",";nJets",200,0,200);
  hPtJetsAll = new TH1D("ptjetsall",";p_{T}(GeV/c)",250,0,250);
  hdNdetadphiJetsAll = new TH2D("dNdetadphiJetsAll",";#eta;#phi",40,-6.0,6.0,32,-PI,PI);
  hCentrality = new TH1D("centrality",";centbin",nCentBins+1,-1,nCentBins);
  hEPAngle = new TH1D("epangle",";#Psi_{2}",100,-2*PI,2*PI);
  hHFTowerSum = new TH1D("hftowersum",";HF Sum E_{T}",600,0,6000);
  hHFvsNpixel = new TH2D("hfvsnpixel",";HF Sum E_{T}; Npixel;",600,0,6000,1000,0,80000);
  hHFvsZDC = new TH2D("hfvszdc",";HF Sum E_{T}; ZDC Sum E_{T};",600,0,6000,1000,0,80000);
  hNpart = new TH1D("Npart",";N_{part}",500,0,500);
  hHLTPaths = new TH1D("hHLTPaths","HLT Paths",4,0,4);
  hHLTPaths->SetBit(TH1::kCanRebin);

  hEtTot = new TH1D("ettot",";Total ET (GeV)",2500,0,5000);
  hInvMass = new TH1D("invmass",";Invariant Mass (GeV)",10000,0,100);
  hMissEt = new TH1D("misset",";Missing ET (GeV)",1000,0,1000);
  hMeanPtVsMult = new TH2D("meanptvsmult",";n;<p_{T}>",2000,0,2000,100,0,10);
  hImbalance = new TH1D("imbalance",";(p_{T}^{j1}-p_{T}^{j2})/(p_{T}^{j1}+p_{T}^{j2})",100,0,1.0);
  hdNdPtdcostheta = new TH2D("dNdPtdcostheta",";#theta;p_{T}(GeV/c);dN/dp_{T}dcos#theta",32,0,PI,100,0,10);
  hBetaVsP = new TH2D("BetaVsP",";p(GeV/c);1/#beta",100,0,10,150,0.5,2.0);
  hLeadTrackPt = new TH1D("leadtrackpt",";p^{lead}_{T}(GeV/c)",1000,0,250); 
 
  hInvMass_Signal = new TH1D("invmass_signal",";Invariant Mass (GeV)",10000,0,100);
  hInvMassVsPt_Signal = new TH2D("invmassvspt_signal",";p_{T}(GeV);Invariant Mass (GeV)",200,0,10,1000,0,2);
  hOpenAngleVsPt_Signal = new TH2D("openanglevspt_signal",";p_{T}(GeV);Opening angle (rads)",200,0,10,100,0,0.5);
  hInvMass_Background = new TH1D("invmass_background",";Invariant Mass (GeV)",10000,0,100);
  hInvMassVsPt_Background = new TH2D("invmassvspt_background",";p_{T}(GeV);Invariant Mass (GeV)",200,0,10,1000,0,2);
  hOpenAngleVsPt_Background = new TH2D("openanglevspt_background",";p_{T}(GeV);Opening angle (rads)",200,0,10,100,0,0.5);
  hInvMass_diphoton = new TH1D("invmass_diphoton",";Invariant Mass (GeV)",10000,0,100);
  hInvMassVsPt_diphoton = new TH2D("invmassvspt_diphoton",";p_{T}(GeV);Invariant Mass (GeV)",200,0,10,1000,0,2);
  hOpenAngleVsPt_diphoton = new TH2D("openanglevspt_diphoton",";p_{T}(GeV);Opening angle (rads)",200,0,10,100,0,0.5);
  hV0InvMassVsPt = new TH2D("v0invmassvspt",";p_{T}(GeV);Invariant Mass (GeV)",200,0,20,1000,0,5);

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
}

void DiHadronCorrelationMultiBaseFWLite::NormalizeHists(int itrg, int jass){}

void DiHadronCorrelationMultiBaseFWLite::DeleteHists()
{
  delete hNVtx;
  delete hNVtxVsNMult;
  delete hZVtx;
  delete hXYVtx;
  delete hZVtxSep;
  delete hXVtxSep;
  delete hYVtxSep;
  delete hXYZVtxSep;
  delete hXYZVtxSepMin;
  delete hXYZVtxSepMin2;
  delete hZVtxSim;
  delete hXYVtxSim;
  delete hZVtxRecoVsSim;
  delete hXVtxRecoVsSim;
  delete hYVtxRecoVsSim;
  delete hZVtxResVsNMult;
  delete hXVtxResVsNMult;
  delete hYVtxResVsNMult;
  delete hTrkZVtxRes;
  delete hTrkXYVtxRes; 
  delete hTrkZVtxResSig;
  delete hTrkXYVtxResSig;
  delete hTrkZVtxResVsNMult;
  delete hTrkXVtxResVsNMult;
  delete hTrkYVtxResVsNMult;
  delete hTrkZVtxResVsPt;
  delete hTrkXVtxResVsPt;
  delete hTrkYVtxResVsPt;
  delete hTrkZVtxSimResVsNMult;
  delete hTrkXVtxSimResVsNMult;
  delete hTrkYVtxSimResVsNMult;
  delete hMultRawAll;
  delete hMultCorrAll;
  delete hMultRawTrigVsAssoc;
  delete hMultMaxVsSec;
  delete hMultMaxVsThird;
  delete hMultMaxVsSecVsZVtxSep;
  delete hMultMaxVsThirdVsZVtxSep;
  delete hPtAll_trg;
  delete hdNdetadptAll_trg;
  delete hdNdetadphiAll_trg;
  delete hPtAll_ass;
  delete hdNdetadptAll_ass;
  delete hdNdetadphiAll_ass;
  delete hPtCorrAll_trg;
  delete hdNdetadptCorrAll_trg;
  delete hdNdetadphiCorrAll_trg;
  delete hPtCorrAll_ass;
  delete hdNdetadptCorrAll_ass;
  delete hdNdetadphiCorrAll_ass;
  delete hdNJetsAll;
  delete hPtJetsAll;
  delete hdNdetadphiJetsAll;

  delete hCentrality;
  delete hEPAngle;
  delete hHFTowerSum;
  delete hHFvsNpixel;
  delete hHFvsZDC;
  delete hHLTPaths;

  delete hEtTot;
  delete hInvMass;
  delete hMissEt;
  delete hMeanPtVsMult;
  delete hImbalance;
  delete hdNdPtdcostheta;
  delete hBetaVsP;
  delete hLeadTrackPt;
  delete hInvMass_Signal;
  delete hInvMassVsPt_Signal;
  delete hOpenAngleVsPt_Signal;
  delete hInvMass_Background;
  delete hInvMassVsPt_Background;
  delete hOpenAngleVsPt_Background;
  delete hInvMass_diphoton;
  delete hInvMassVsPt_diphoton;
  delete hOpenAngleVsPt_diphoton;
  delete hV0InvMassVsPt;
}

// ---------------------------------------------------------------
void DiHadronCorrelationMultiBaseFWLite::GetMult()
{
   if(!cutPara.IsGenMult) 
   {
     //----- loop over tracks -----
     fwlite::Handle<std::vector<reco::Track> > tracks;
     tracks.getByLabel(event,cutPara.trgtrackCollection.Data());
//     tracks.getByLabel(event,"selectTracks");
     if(!tracks.isValid()) return;

     for(unsigned it=0; it<tracks->size(); ++it){

       const reco::Track & trk = (*tracks)[it];

       if(trk.pt()<0.0001) continue;

       // select tracks based on proximity to best vertex 
       math::XYZPoint bestvtx(xVtx,yVtx,zVtx);

       double dzvtx = trk.dz(bestvtx);
       double dxyvtx = trk.dxy(bestvtx);      
       double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
       double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);
       int nhits = trk.numberOfValidHits();
       double chi2n = trk.normalizedChi2();
       int nlayers = trk.hitPattern().trackerLayersWithMeasurement();
       // standard quality cuts

       if(cutPara.IsTrkQuality)
       {
         if(!trk.quality(reco::TrackBase::highPurity)) continue;
         if(fabs(trk.ptError())/trk.pt()>0.10) continue;
         if(fabs(dzvtx/dzerror) > 3) continue;
         if(fabs(dxyvtx/dxyerror) > 3) continue;
       }
//       if(fabs(dzvtx) > 0.1) continue;
//       if(fabs(dxyvtx) > 0.05) continue;
//       if(nhits<5) continue;
//       if (chi2n > 0.15*nlayers) continue;

       double eta = trk.eta();
       double pt  = trk.pt();

       double effweight = GetEffWeight(eta,pt,0.5*(cutPara.zvtxmax+cutPara.zvtxmin),hiCentrality);

       if(eta>=cutPara.etamultmin && eta<=cutPara.etamultmax && pt>=cutPara.ptmultmin && pt<=cutPara.ptmultmax) { nMult++; nMultCorr=nMultCorr+1.0/effweight; }
     }
   }
   else
   {
     //----- loop over particles -----
     fwlite::Handle<std::vector<reco::GenParticle> > genTracks;
     genTracks.getByLabel(event,cutPara.genParticleCollection.Data());
     if(!genTracks.isValid()) { cout<<"Invalid or empty genParticle collection!"<<endl; return; }

     for(unsigned ip=0; ip<genTracks->size(); ++ip){
       const reco::GenParticle & p = (*genTracks)[ip];
       if(p.status() != 1) continue;
       if(p.charge() == 0) continue;

       double eta = p.eta();
       double pt  = p.pt();

       if(eta>=cutPara.etamultmin && eta<=cutPara.etamultmax && pt>=cutPara.ptmultmin && pt<=cutPara.ptmultmax) { nMult++; nMultCorr++; }
     }
   }
}

void DiHadronCorrelationMultiBaseFWLite::GetJets()
{  
   nJets=0;
   fwlite::Handle<std::vector<pat::Jet> > jets;
   jets.getByLabel(event,cutPara.jetCollection.Data());
   if(!jets.isValid()) { cout<<"Invalid or empty jet collection!"<<endl; return; }
     
   for(unsigned it=0; it<jets->size(); ++it){

     const pat::Jet & jet = (*jets)[it];

     double eta = jet.eta();
     double phi = jet.phi();
     double et  = jet.et();

     hPtJetsAll->Fill(et);
     hdNdetadphiJetsAll->Fill(eta,phi);
     if(et>=cutPara.jetetmin && et<=cutPara.jetetmax) nJets++;
   }

   hdNJetsAll->Fill(nJets);
}   

// ------------- Loop over all the particles ---------------------
void DiHadronCorrelationMultiBaseFWLite::LoopParticles(bool istrg)
{
   //----- loop over particles -----
   fwlite::Handle<std::vector<reco::GenParticle> > genTracks;
   genTracks.getByLabel(event,cutPara.genParticleCollection.Data());
   if(!genTracks.isValid()) { cout<<"Invalid or empty genParticle collection!"<<endl; return; }

   for(unsigned ip=0; ip<genTracks->size(); ++ip){
     const reco::GenParticle & p = (*genTracks)[ip];
     if(p.status() != 1) continue;
     if(p.charge() == 0) continue;

     double eta = p.eta();
     double phi = p.phi();
     double pt  = p.pt();
     double charge = p.charge();

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(pt,eta,phi,charge,effweight);
     else AssignAssPtBins(pt,eta,phi,charge,effweight);
   }
}

// ------------- Loop over all the tracks ---------------------
void DiHadronCorrelationMultiBaseFWLite::LoopTracks(bool istrg, TString input)
{	
/*
   double mass = 0.141;
   double pxtot = 0;
   double pytot = 0;
   double pztot = 0;
   double etxtot = 0;
   double etytot = 0;
   double ettot  = 0;
   double etot  = 0;
   double pttot = 0;
   double leadpt = 0;
   double leadeta = 0;
   double leadphi = 0;
   double leadcharge = 0;
*/
   int nMultTmp = 0;

   //----- loop over tracks -----
   fwlite::Handle<std::vector<reco::Track> > tracks;
   tracks.getByLabel(event,input.Data());
   if(!tracks.isValid()) { cout<<"Invalid or empty track collection!"<<endl; return; }
 
   for(unsigned it=0; it<tracks->size(); ++it){     
 
     const reco::Track & trk = (*tracks)[it];

     double pt  = trk.pt();
     if(pt<0.0001) continue;
     double eta = trk.eta();
     double phi = trk.phi();
/*
     double px  = pt*cos(phi);
     double py  = pt*sin(phi);
     double pz  = trk.pz(); 
     double et  = sqrt(pt*pt+mass*mass);
     double etx = et*cos(phi);
     double ety = et*sin(phi);
*/
     // tracks' proximity to best vertex
     math::XYZPoint bestvtx(xVtx,yVtx,zVtx);
     double dz = trk.dz(bestvtx);
     double dxy = trk.dxy(bestvtx);
     double dzerror = sqrt(trk.dzError()*trk.dzError()+zVtxError*zVtxError);
     double dxyerror = sqrt(trk.d0Error()*trk.d0Error()+xVtxError*yVtxError);
     double pterror = trk.ptError();
     double vx = trk.vx();
     double vy = trk.vy();
     double vz = trk.vz();
     int nhits = trk.numberOfValidHits();
     int algo = trk.algo();
     double chi2 = trk.chi2();
     double charge = trk.charge();
     double chi2n = trk.normalizedChi2();
     int nlayers = trk.hitPattern().trackerLayersWithMeasurement();
// standard track quality cuts  
     if(cutPara.IsTrkQuality)
     {
       if(!trk.quality(reco::TrackBase::highPurity)) continue;
       if(fabs(trk.ptError())/trk.pt()>0.10) continue;
       if(fabs(dz/dzerror) > 3) continue;
       if(fabs(dxy/dxyerror) > 3) continue;
     }  
//     if(fabs(dz) > 0.1) continue;
//     if(fabs(dxy) > 0.05) continue;
//     if(nhits<5) continue;
//     if(chi2n > 0.15*nlayers) continue;

/*
     if(pt>0.4 && fabs(eta)<2.4)
     {  
       pxtot += px;
       pytot += py;
       pztot += pz;
       etxtot += etx;
       etytot += ety;
       ettot  += sqrt(px*px+py*py+mass*mass);
       etot  += sqrt(px*px+py*py+pz*pz+mass*mass);
       pttot += pt;
       if(leadpt<pt) { leadpt = pt; leadeta = eta; leadphi = phi; leadcharge = charge; }
       nMultTmp++;
     }
     hdNdPtdcostheta->Fill(trk.theta(),pt,1.0/fabs(sin(trk.theta())));
*/
     if(cutPara.IsVtxSel)
     {
       hTrkZVtxRes->Fill(vz-zVtx);
       hTrkXYVtxRes->Fill(vx-xVtx,vy-yVtx);
       hTrkZVtxResSig->Fill((vz-zVtx)/dzerror);
       hTrkXYVtxResSig->Fill((vx-xVtx)/dxyerror,(vy-yVtx)/dxyerror);
       hTrkZVtxResVsNMult->Fill(nMult,vz-zVtx);
       hTrkXVtxResVsNMult->Fill(nMult,vx-xVtx);
       hTrkYVtxResVsNMult->Fill(nMult,vy-yVtx);
       hTrkZVtxResVsPt->Fill(pt,vz-zVtx);
       hTrkXVtxResVsPt->Fill(pt,vx-xVtx);
       hTrkYVtxResVsPt->Fill(pt,vy-yVtx);
       if(cutPara.IsGenVtx)
       {
         hTrkZVtxSimResVsNMult->Fill(nMult,vz-zVtxSim);
         hTrkXVtxSimResVsNMult->Fill(nMult,vx-xVtxSim);
         hTrkYVtxSimResVsNMult->Fill(nMult,vy-yVtxSim);
       }
     }
     if(cutPara.IsTrackNtuple) trackNtuple->Fill(vx,vy,vz,dz,dxy,sqrt(dzerror*dzerror+zVtxError*zVtxError),sqrt(dxyerror*dxyerror+xVtxError*yVtxError),nhits,chi2,algo,eta,phi,pt,pterror);

     double effweight = GetEffWeight(eta,pt,0.5*(cutPara.zvtxmax+cutPara.zvtxmin),hiCentrality);
     double trgweight = GetTrgWeight(nMult);

     if(istrg && !cutPara.IsLeadTrack) AssignTrgPtBins(pt,eta,phi,charge,effweight*trgweight);
     else AssignAssPtBins(pt,eta,phi,charge,effweight*trgweight);
   }
/*
   if(cutPara.IsLeadTrack && istrg) 
   {
     double effweight = GetEffWeight(leadeta,leadpt,0.5*(cutPara.zvtxmax+cutPara.zvtxmin),hiCentrality);
     AssignTrgPtBins(leadpt,leadeta,leadphi,leadcharge,effweight);
   } 
   
   hEtTot->Fill(ettot);
   double invmass = sqrt(etot*etot-pxtot*pxtot-pytot*pytot-pztot*pztot);
   hInvMass->Fill(invmass);
   double misset = sqrt(etxtot*etxtot+etytot*etytot);
   hMissEt->Fill(misset);
   hMeanPtVsMult->Fill(nMult,pttot/nMultTmp);
   hLeadTrackPt->Fill(leadpt);
*/
}

// ------------- Loop over all the ECAL Superclusters ---------------------
void DiHadronCorrelationMultiBaseFWLite::LoopEcalSC(bool istrg)
{
   //----- loop over clusters -----
   fwlite::Handle<std::vector<reco::SuperCluster> > superclusters;
   superclusters.getByLabel(event,cutPara.superClusterCollection.Data());
   if(!superclusters.isValid()) { cout<<"Invalid or empty ECAL barrel SC collection!"<<endl; return; }
   for(unsigned it=0; it<superclusters->size(); ++it){
     const reco::SuperCluster & supercluster = (*superclusters)[it];
     double charge = 0;
     double eta = supercluster.eta();
     double phi = supercluster.phi();
     double et  = supercluster.energy()/cosh(eta);

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(et,eta,phi,charge,effweight);
     else AssignAssPtBins(et,eta,phi,charge,effweight);
   }

   fwlite::Handle<std::vector<reco::SuperCluster> > superclustersfwd;
   superclustersfwd.getByLabel(event,cutPara.superClusterFwdCollection.Data());
   if(!superclustersfwd.isValid()) { cout<<"Invalid or empty ECAL endcap SC collection!"<<endl; return; }
   for(unsigned it=0; it<superclustersfwd->size(); ++it){
     const reco::SuperCluster & superclusterfwd = (*superclustersfwd)[it];
     double charge = 0;
     double eta = superclusterfwd.eta();
     double phi = superclusterfwd.phi();
     double et  = superclusterfwd.energy()/cosh(eta);

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(et,eta,phi,charge,effweight);
     else AssignAssPtBins(et,eta,phi,charge,effweight);
   }
}

void DiHadronCorrelationMultiBaseFWLite::LoopEcalBC(bool istrg) 
{
   //----- loop over clusters -----
   fwlite::Handle<std::vector<reco::BasicCluster> > basicclusters;
   basicclusters.getByLabel(event,"hybridSuperClusters","hybridBarrelBasicClusters");
   if(!basicclusters.isValid()) { cout<<"Invalid or empty ECAL barrel BC collection!"<<endl; return; }
   for(unsigned it=0; it<basicclusters->size(); ++it){
     const reco::BasicCluster & basiccluster = (*basicclusters)[it];
     double charge = 0;
     double eta = basiccluster.eta();
     double phi = basiccluster.phi();
     double et  = basiccluster.energy()/cosh(eta);
     
     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(et,eta,phi,charge,effweight);
     else AssignAssPtBins(et,eta,phi,charge,effweight);
   } 

   fwlite::Handle<std::vector<reco::BasicCluster> > basicclustersfwd;
   basicclustersfwd.getByLabel(event,"multi5x5BasicClusters","multi5x5EndcapBasicClusters");
   if(!basicclustersfwd.isValid()) { cout<<"Invalid or empty ECAL endcap BC collection!"<<endl; return; }
   for(unsigned it=0; it<basicclustersfwd->size(); ++it){
     const reco::BasicCluster & basicclusterfwd = (*basicclustersfwd)[it];
     double charge = 0;
     double eta = basicclusterfwd.eta();
     double phi = basicclusterfwd.phi();
     double et  = basicclusterfwd.energy()/cosh(eta);

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(et,eta,phi,charge,effweight);
     else AssignAssPtBins(et,eta,phi,charge,effweight);
   }
}

void DiHadronCorrelationMultiBaseFWLite::LoopJets(bool istrg)
{
   fwlite::Handle<std::vector<pat::Jet> > jets;
   jets.getByLabel(event,cutPara.jetCollection.Data());        
   if(!jets.isValid()) { cout<<"Invalid or empty jet collection!"<<endl; return; }

   for(unsigned it=0; it<jets->size(); ++it){

     // select leading jets
//     if(it>0) break;

     const pat::Jet & jet = (*jets)[it];
     
     double eta = jet.eta();
     double phi = jet.phi();
     double et  = jet.et();
     double charge = 0; 

     // sub-leading jet
     if(cutPara.IsSubJet && jets->size()>1)
     {
       if(fabs(eta)<2 && et>cutPara.leadjetetmin)
       {
         const pat::Jet & jet1 = (*jets)[it+1];
         double eta1 = jet1.eta();
         double phi1 = jet1.phi();
         double et1 = jet1.et();
         double charge1 = 0; 
         double deltaPhi = GetDeltaPhi(phi,phi1);
         if(fabs(deltaPhi-PI)>(PI-2.5)) break;
         double imbalance = (et-et1)/(et+et1);
         hImbalance->Fill(imbalance);
         eta = eta1;
         phi = phi1;
         et = et1;
         charge = charge1;
       }
       else break;
     }

     if(cutPara.IsMonoJet)
     {
       if(fabs(eta)<2 && et>cutPara.leadjetetmin)
       {
         const pat::Jet & jet1 = (*jets)[it+1];
         double eta1 = jet1.eta();
         double phi1 = jet1.phi();
         double et1 = jet1.et();
//         double charge1 = 0;
         double deltaPhi = GetDeltaPhi(phi,phi1);
         if(fabs(eta1)<2 && abs(deltaPhi-PI)<(PI-2.5) && et1>cutPara.subjetetmin) break;
       }
       else break;       
     }

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(et,eta,phi,charge,effweight);
     else AssignAssPtBins(et,eta,phi,charge,effweight);
   } 
}

void DiHadronCorrelationMultiBaseFWLite::LoopMuons(bool istrg)
{
   fwlite::Handle<std::vector<reco::Muon> > muons;
   muons.getByLabel(event,"muons");
   if(!muons.isValid()) return;

   for(unsigned it=0; it<muons->size(); ++it){

     const reco::Muon & muon = (*muons)[it];
     double eta = muon.eta();
     double phi = muon.phi();
     double pt  = muon.pt();
     double charge = muon.charge();

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(pt,eta,phi,charge,effweight);
     else AssignAssPtBins(pt,eta,phi,charge,effweight);
   }
}

void DiHadronCorrelationMultiBaseFWLite::LoopPFCandidates(bool istrg, reco::PFCandidate::ParticleType pfID)
{       
   fwlite::Handle<std::vector<reco::PFCandidate> > pfcandidate;
   pfcandidate.getByLabel(event,"particleFlow");
   if(!pfcandidate.isValid()) return;

   for(unsigned it=0; it<pfcandidate->size(); ++it){
 
     const reco::PFCandidate & pfCand = (*pfcandidate)[it];
     double eta = pfCand.eta();
     double phi = pfCand.phi();
     double pt  = pfCand.pt();
     double p   = pfCand.p();
     double etot = pfCand.ecalEnergy()+pfCand.hcalEnergy();
//     double etot = pfCand.hcalEnergy();
     double charge = pfCand.charge();

     if(reco::PFCandidate::ParticleType(pfCand.particleId())!=pfID) continue;

     // PID via velocity
     hBetaVsP->Fill(p,p/etot);

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(pt,eta,phi,charge,effweight);
     else AssignAssPtBins(pt,eta,phi,charge,effweight);
   }
}

void DiHadronCorrelationMultiBaseFWLite::LoopPionZeros(bool istrg, double massShift)
{
   //----- loop over tracks -----
   fwlite::Handle<std::vector<reco::PFCandidate> > pfcandidate;
   pfcandidate.getByLabel(event,"particleFlow");
   if(!pfcandidate.isValid()) return;

   for(unsigned it=0; it<pfcandidate->size(); ++it){

     const reco::PFCandidate & pfCand1 = (*pfcandidate)[it];
     if(reco::PFCandidate::ParticleType(pfCand1.particleId())!=reco::PFCandidate::gamma) continue;

     double eta1 = pfCand1.eta();
     double phi1 = pfCand1.phi();
     double pt1  = pfCand1.pt();

     if(pt1<0.4 || fabs(eta1)>1.5) continue;

     TVector3 pvector1;
     pvector1.SetPtEtaPhi(pt1,eta1,phi1);
     TLorentzVector photon1(pvector1,pvector1.Mag());
     for(unsigned jt=it+1; jt<pfcandidate->size(); ++jt){

       const reco::PFCandidate & pfCand2 = (*pfcandidate)[jt];
       if(reco::PFCandidate::ParticleType(pfCand2.particleId())!=reco::PFCandidate::gamma) continue;

       double eta2 = pfCand2.eta();
       double phi2 = pfCand2.phi();
       double pt2  = pfCand2.pt();

       if(pt2<0.4 || fabs(eta2)>1.5) continue;

       TVector3 pvector2;
       pvector2.SetPtEtaPhi(pt2,eta2,phi2);
       TLorentzVector photon2(pvector2,pvector2.Mag());
    
       TLorentzVector pionzero = photon1 + photon2;
       double massInv = pionzero.M();
       double eta_pionzero = pionzero.Eta();
       double phi_pionzero = pionzero.Phi();
       double pt_pionzero = pionzero.Pt();
       double openAngle = photon1.Angle(photon2.Vect());

       if(openAngle>(0.22/pt_pionzero-0.07/pt_pionzero/pt_pionzero) && openAngle<(0.65/pt_pionzero-0.3/pt_pionzero/pt_pionzero))
       {
         hInvMass_diphoton->Fill(massInv);
         hInvMassVsPt_diphoton->Fill(pt_pionzero,massInv);
       }
       
       double mass = 0.14*(1-TMath::Exp(-TMath::Power(pt_pionzero,0.37)/0.36))+massShift;
       double width =  0.001/(1-TMath::Exp(-TMath::Power(pt_pionzero,0.32)/16.7));
       if(massInv>(mass-2*width) && massInv<(mass+2*width)) hOpenAngleVsPt_diphoton->Fill(pt_pionzero,openAngle);
       if(massInv<(mass-2*width) || massInv>(mass+2*width) || openAngle<(0.22/pt_pionzero-0.07/pt_pionzero/pt_pionzero) || openAngle>(0.65/pt_pionzero-0.3/pt_pionzero/pt_pionzero)) continue;

       double effweight = 1.0;
       if(istrg) AssignTrgPtBins(pt_pionzero,eta_pionzero,phi_pionzero,0,effweight);
       else AssignAssPtBins(pt_pionzero,eta_pionzero,phi_pionzero,0,effweight);
     }
   }
}
void DiHadronCorrelationMultiBaseFWLite::LoopCaloTower(bool istrg)
{
//   fwlite::Handle<std::vector<CaloTower> > calotowers;
   fwlite::Handle<CaloTowerCollection> calotowers;
   calotowers.getByLabel(event,"towerMaker");
   if(!calotowers.isValid()) { cout<<"Invalid or empty calotower collection!"<<endl; return; }

   for(unsigned it=0; it<calotowers->size(); ++it){

     //const reco::Candidate & calotower = (*calotowers)[it];
     const CaloTower & calotower = (*calotowers)[it];

     double eta = calotower.eta();
     double phi = calotower.phi();
     double et  = calotower.et();
     double charge = 0;
     
     double effweight = 1.0/et;
     if(istrg) AssignTrgPtBins(et,eta,phi,charge,effweight);
     else AssignAssPtBins(et,eta,phi,charge,effweight);
   }
}

void DiHadronCorrelationMultiBaseFWLite::LoopEcalRecHits(bool istrg)
{
/*
   //----- loop over ecal rechits -----
   fwlite::Handle<std::vector<EcalRecHit> > ecalrechitseb;
   ecalrechitseb.getByLabel(event,"ecalRecHit","EcalRecHitsEB");
   if(!ecalrechitseb.isValid()) { cout<<"Invalid or empty Barrel EcalRecHit collection!"<<endl; return; }
   for(unsigned it=0; it<ecalrechitseb->size(); ++it){
     const EcalRecHit & ecalrechiteb = (*ecalrechitseb)[it];
     double charge = 0;
     double eta = ecalrechiteb.id().ieta();
     double phi = ecalrechiteb.id().iphi();
     double et  = ecalrechiteb.id().ienergy()/cosh(eta);
     
     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(et,eta,phi,charge,effweight);
     else AssignAssPtBins(et,eta,phi,charge,effweight);
   }

   fwlite::Handle<std::vector<EcalRecHit> > ecalrechitsee;
   ecalrechitsee.getByLabel(event,"ecalRecHit","EcalRecHitsEE");
   if(!ecalrechitsee.isValid()) { cout<<"Invalid or empty Endcap EcalRecHit collection!"<<endl; return; }
   for(unsigned it=0; it<ecalrechitsee->size(); ++it){
     const EcalRecHit & ecalrechitee = (*ecalrechitsee)[it];
     double charge = 0;
     double eta = ecalrechitee.id().ieta();
     double phi = ecalrechitee.id().iphi();
     double et  = ecalrechitee.id().ienergy()/cosh(eta);
     
     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(et,eta,phi,charge,effweight);
     else AssignAssPtBins(et,eta,phi,charge,effweight);
   }
*/
}

void DiHadronCorrelationMultiBaseFWLite::LoopHcalRecHits(bool istrg){}

void DiHadronCorrelationMultiBaseFWLite::LoopV0Candidates(bool istrg, TString candtype)
{
   fwlite::Handle<std::vector<reco::VertexCompositeCandidate> > v0candidates;
   v0candidates.getByLabel(event,"generalV0Candidates",candtype.Data());
   if(!v0candidates.isValid()) return;

   for(unsigned it=0; it<v0candidates->size(); ++it){

     const VertexCompositeCandidate& v0candidate = (*v0candidates)[it];

     double eta = v0candidate.eta();
     double phi = v0candidate.phi();
     double pt  = v0candidate.pt();
     double mass = v0candidate.mass();
     double charge = v0candidate.charge();

     hV0InvMassVsPt->Fill(pt,mass);

     double effweight = 1.0;
     if(istrg) AssignTrgPtBins(pt,eta,phi,charge,effweight);
     else AssignAssPtBins(pt,eta,phi,charge,effweight);
   }
}

// ------------- Fill Vertex distribution ---------------------
void DiHadronCorrelationMultiBaseFWLite::GetVertices()
{
    nVertices=0;
    maxofflinetracks=0;
    secofflinetracks=0;
    thirdofflinetracks=0;
    xVtx = -99999.9;
    yVtx = -99999.9;
    zVtx = -99999.9;
    xVtxError = -99999.9;

    zVtxError = -99999.9;

    fwlite::Handle<std::vector<reco::Vertex> > vertices;
    vertices.getByLabel(event,cutPara.vertexCollection.Data());
    if(!vertices.isValid()) { cout<<"Invalid or empty vertex collection!"<<endl; return; }
    
    for(unsigned int iv=0; iv<vertices->size(); ++iv)
    {
      const reco::Vertex & vtx = (*vertices)[iv];
      if(!vtx.isFake() && vtx.tracksSize()>=2) 
      { 
        nVertices++;
        if(vtx.tracksSize()>=maxofflinetracks)
        {
          xVtx = vtx.x();
          yVtx = vtx.y();
          zVtx = vtx.z();
          xVtxError = vtx.xError();
          yVtxError = vtx.yError();
          zVtxError = vtx.zError();
          maxofflinetracks = vtx.tracksSize();
        }
      }
    }

    minVtxSep=99999.9;
    double xVtx2 = -99999.9;
    double yVtx2 = -99999.9;
    double zVtx2 = -99999.9;

    for(unsigned int iv=0; iv<vertices->size(); ++iv)
    {
      const reco::Vertex & vtx = (*vertices)[iv];
      if(!vtx.isFake() && vtx.tracksSize()>=2)
      {
        xVtx2 = vtx.x();
        yVtx2 = vtx.y();
        zVtx2 = vtx.z();
        if(zVtx2==zVtx && xVtx2==xVtx && yVtx2==yVtx) continue;
        double zsep=zVtx2-zVtx;
        double xsep=xVtx2-xVtx;
        double ysep=yVtx2-yVtx;
        double xyzsep=fabs(zVtx2-zVtx);
        hZVtxSep->Fill(zsep); 
        hXVtxSep->Fill(xsep);
        hYVtxSep->Fill(ysep);
        hXYZVtxSep->Fill(xyzsep);
        if(xyzsep<=minVtxSep)
        {
          minVtxSep=xyzsep;
          secofflinetracks = vtx.tracksSize();
        }
      }
    }

    minVtxSep2=99999.9;
    double xVtx3 = -99999.9;
    double yVtx3 = -99999.9;
    double zVtx3 = -99999.9;

    for(unsigned int iv=0; iv<vertices->size(); ++iv)
    {
      const reco::Vertex & vtx = (*vertices)[iv];
      if(!vtx.isFake() && vtx.tracksSize()>=2)
      {
        xVtx3 = vtx.x();
        yVtx3 = vtx.y();
        zVtx3 = vtx.z();
        if(zVtx3==zVtx && xVtx3==xVtx && yVtx3==yVtx) continue;
        if(zVtx3==zVtx2 && xVtx3==xVtx2 && yVtx3==yVtx2) continue;
        double xyzsep=fabs(zVtx3-zVtx);
        if(xyzsep<=minVtxSep2)
        {
          minVtxSep2=xyzsep;
          thirdofflinetracks = vtx.tracksSize();
        }
      }
    }
}

void DiHadronCorrelationMultiBaseFWLite::GetSimVertices()
{
    fwlite::Handle<std::vector<SimVertex> > simvertices;
    simvertices.getByLabel(event,"g4SimHits");
    if(!simvertices.isValid()) { cout<<"Invalid or empty sim vertex collection!"<<endl; return; }

    const SimVertex & simvtx = (*simvertices)[0];
    xVtxSim = simvtx.position().x();
    yVtxSim = simvtx.position().y();
    zVtxSim = simvtx.position().z();

    hZVtxSim->Fill(zVtxSim);
    hXYVtxSim->Fill(xVtxSim,yVtxSim);
}

//--------------- Calculate two-particle invariant mass distributions ----------
void DiHadronCorrelationMultiBaseFWLite::FillHistsInvariantMass(const DiHadronCorrelationEvent& eventcorr)
{     
  for(unsigned int itrg=0;itrg<cutPara.pttrgmin.size();itrg++)
    for(unsigned int jass=0;jass<cutPara.ptassmin.size();jass++)
    {   
      unsigned int ntrgsize = eventcorr.pVect_trg[itrg].size();
      unsigned int nasssize = eventcorr.pVect_ass[jass].size();
        
      for(unsigned int ntrg=0;ntrg<ntrgsize;ntrg++)
      {
        TVector3 pvector_trg = (eventcorr.pVect_trg[itrg])[ntrg];
        TLorentzVector part_trg(pvector_trg,sqrt(massTrg*massTrg+pvector_trg.Mag()*pvector_trg.Mag()));
        double chg_trg = (eventcorr.chgVect_trg[itrg])[ntrg];
          
        for(unsigned int nass=0;nass<nasssize;nass++)
        {
          TVector3 pvector_ass = (eventcorr.pVect_ass[jass])[nass];
          TLorentzVector part_ass(pvector_ass,sqrt(massAss*massAss+pvector_ass.Mag()*pvector_ass.Mag()));
          double chg_ass = (eventcorr.chgVect_ass[jass])[nass];

          // check charge sign
          if( (checksign == 0) && (chg_trg != chg_ass)) continue;
          if( (checksign == 1) && (chg_trg == chg_ass)) continue;

          TLorentzVector part_total = part_ass + part_trg;
          double massInv = part_total.M();
/*
          if(massInv>0.01)
          {
            hInvMass_pair->Fill(massInv);
            hInvMassVsPt_pair->Fill(part_total.Pt(),massInv);
          }
*/
        }
      }
    }
}

void DiHadronCorrelationMultiBaseFWLite::AssignTrgPtBins(double pt, double eta, double phi, double charge, double effweight)
{
   hdNdetadphiAll_trg->Fill(eta,phi);
   hdNdetadptAll_trg->Fill(eta,pt);
   hdNdetadphiCorrAll_trg->Fill(eta,phi,1.0/effweight);
   hdNdetadptCorrAll_trg->Fill(eta,pt,1.0/effweight);
   hPtAll_trg->Fill(pt,1.0/hPtAll_trg->GetBinWidth(hPtAll_trg->FindBin(pt)));
   hPtCorrAll_trg->Fill(pt,1./effweight/hPtAll_trg->GetBinWidth(hPtAll_trg->FindBin(pt)));

   TVector3 pvector;
   pvector.SetPtEtaPhi(pt,eta,phi);
   if(pt>0.4 && fabs(eta)<2.4) (eventcorr->pVect_all).push_back(pvector);
   for(int pttrgbin=0;pttrgbin<(int)(cutPara.pttrgmin.size());pttrgbin++)
   {
     if(GetPttrgBin(pt,eta,pttrgbin))
     {
       hpT_Signal_trg[pttrgbin]->Fill(pt);
       hpTCorr_Signal_trg[pttrgbin]->Fill(pt,1.0/effweight);
       hpT_Background_trg[pttrgbin]->Fill(pt);
       hpTCorr_Background_trg[pttrgbin]->Fill(pt,1.0/effweight);
       hdNdetadphi_trg[pttrgbin]->Fill(eta,phi);
       hdNdetadphiCorr_trg[pttrgbin]->Fill(eta,phi,1.0/effweight);

       nMultAll_trg++; nMultAllCorr_trg = nMultAllCorr_trg + 1.0/effweight;
       (eventcorr->pVect_trg[pttrgbin]).push_back(pvector);
       (eventcorr->chgVect_trg[pttrgbin]).push_back(charge);
       (eventcorr->effVect_trg[pttrgbin]).push_back(effweight);
    }
   }
}

void DiHadronCorrelationMultiBaseFWLite::AssignAssPtBins(double pt, double eta, double phi, double charge, double effweight)
{
   hdNdetadphiAll_ass->Fill(eta,phi);
   hdNdetadptAll_ass->Fill(eta,pt);
   hdNdetadphiCorrAll_ass->Fill(eta,phi,effweight);
   hdNdetadptCorrAll_ass->Fill(eta,pt,effweight);
   hPtAll_ass->Fill(pt);
   hPtCorrAll_ass->Fill(pt,effweight);

   TVector3 pvector;
   pvector.SetPtEtaPhi(pt,eta,phi);
   for(int ptassbin=0;ptassbin<(int)(cutPara.ptassmin.size());ptassbin++)
   {
     if(GetPtassBin(pt,eta,ptassbin))
     {
       hpT_Signal_ass[ptassbin]->Fill(pt);
       hpTCorr_Signal_ass[ptassbin]->Fill(pt,1.0/effweight);
       hpT_Background_ass[ptassbin]->Fill(pt);
       hpTCorr_Background_ass[ptassbin]->Fill(pt,1.0/effweight);
       hdNdetadphi_ass[ptassbin]->Fill(eta,phi);
       hdNdetadphiCorr_ass[ptassbin]->Fill(eta,phi,1.0/effweight);

       nMultAll_ass++; nMultAllCorr_ass = nMultAllCorr_ass + 1.0/effweight;
       (eventcorr->pVect_ass[ptassbin]).push_back(pvector); 
       (eventcorr->chgVect_ass[ptassbin]).push_back(charge);
       (eventcorr->effVect_ass[ptassbin]).push_back(effweight);
     }
   }
}

bool DiHadronCorrelationMultiBaseFWLite::SelectTriggerBit()
{
  // get hlt bits
  const int nTrigs = cutPara.triggernames.size();
  if(!nTrigs) return kTRUE;

  fwlite::Handle<edm::TriggerResults> trgRes;
  trgRes.getByLabel(event,"TriggerResults","","HLT");
  if(!trgRes.isValid()) return kFALSE;
  const edm::TriggerNames & triggerNames = event.triggerNames(*trgRes);
  bool accept = kFALSE;
  for(int i=0; i<nTrigs; i++) {
    unsigned int triggerIndex = triggerNames.triggerIndex(cutPara.triggernames[i].Data());
    if(triggerIndex>=triggerNames.size()) continue;
    if(trgRes->accept(triggerIndex))
    {
      hHLTPaths->Fill(cutPara.triggernames[i].Data(),1);
      accept=kTRUE;
    } 
  }

  bool veto = kFALSE;
  const int nVetos = cutPara.vetonames.size();
  if(nVetos)
  { 
    for(int i=0; i<nVetos; i++) {
      unsigned int vetoIndex = triggerNames.triggerIndex(cutPara.vetonames[i].Data());
      if(vetoIndex>=triggerNames.size()) continue;
      if(trgRes->accept(vetoIndex)) veto = kTRUE;
    }
  }
  else veto = kFALSE;

  return (accept && !veto);
}

int DiHadronCorrelationMultiBaseFWLite::GetCentralityBin()
{
  fwlite::Handle<reco::Centrality> cent;
  cent.getByLabel(event,"hiCentrality");

  hf = cent->EtHFhitSum();
  hft = cent->EtHFtowerSum();
  npixel = cent->multiplicityPixel();
  zdc = cent->zdcSum();
//  double eb = cent->EtEBSum();
//  double eep = cent->EtEESumPlus();
//  double eem = cent->EtEESumMinus();

  hHFTowerSum->Fill(hft);
  hHFvsNpixel->Fill(hft,npixel);
  hHFvsZDC->Fill(hft,zdc);

  int run = event.id().run();

  run = centRunnum;

  if(centTableName.Contains("HFhits")) bin = HFhitBinMap[run]->getBin(hf);
  if(centTableName.Contains("HFtowers")) bin = HFhitBinMap[run]->getBin(hft);

//  double npartMean = HFhitBinMap[run]->NpartMean(hf);
//  double npartSigma = HFhitBinMap[run]->NpartSigma(hf);
//  hNpart->Fill(npartMean);

  if(hft>3260 && npixel>51400 && cutPara.centmin==100 && cutPara.centmax == 1000) bin=100;
  if(hft>3400 && hft<3600 && npixel>51000 && npixel<57000 && cutPara.centmin==200 && cutPara.centmax == 1000) bin=200;
  if(hft>3400 && hft<3600 && npixel>51000 && npixel<57000 && zdc<2000 && cutPara.centmin==300 && cutPara.centmax == 1000) bin=300;
  if(hft>3129.3 && cutPara.centmin==50 && cutPara.centmax == 1000) bin=50;
  if(hft>3094.3 && npixel>48787 && cutPara.centmin==51 && cutPara.centmax == 1000) bin=51;
  if((7.0*hft+zdc)<36000 && cutPara.centmin==500 && cutPara.centmax == 1000) bin=500;
  if((7.0*hft+zdc)<36000 && hft>3260 && npixel>51400 && cutPara.centmin==110 && cutPara.centmax == 1000) bin=110;
  if((7.0*hft+zdc)<36000 && 1.15*hft>zdc && hft>3260 && npixel>51400 && cutPara.centmin==120 && cutPara.centmax == 1000) bin=120;
  if((7.0*hft+zdc)<36000 && hft>3393 && npixel>53450 && cutPara.centmin==210 && cutPara.centmax == 1000) bin=210;
  if((7.0*hft+zdc)<36000 && 1.15*hft>zdc && hft>3393 && npixel>53450 && cutPara.centmin==220 && cutPara.centmax == 1000) bin=220;

  return bin;
}

double DiHadronCorrelationMultiBaseFWLite::GetEventPlaneAngle(unsigned int index)
{
  fwlite::Handle<std::vector<reco::EvtPlane> > evtPlanes;
  evtPlanes.getByLabel(event,"hiEvtPlane","recoLevel");

  if(!evtPlanes.isValid()) {cout<<"Event Plane not found!"<<endl; return -9999.9;}

  const reco::EvtPlane & ep = (*evtPlanes)[index];
  return ep.angle();
}

double DiHadronCorrelationMultiBaseFWLite::GetDeltaEta(double eta_trg, double eta_ass)
{
        double deltaEta=eta_ass-eta_trg;
        return deltaEta;
}

double DiHadronCorrelationMultiBaseFWLite::GetDeltaPhi(double phi_trg, double phi_ass)
{     
        double deltaPhi=phi_ass-phi_trg;
        if(deltaPhi>PI)
          deltaPhi=deltaPhi-2*PI;
        if(deltaPhi<-PI/2)
          deltaPhi=deltaPhi+2*PI;
        return deltaPhi;
}

bool DiHadronCorrelationMultiBaseFWLite::GetPttrgBin(double pt, double eta, int itrg)
{
    if(pt>=cutPara.pttrgmin[itrg] && pt<=cutPara.pttrgmax[itrg] && eta>=cutPara.etatrgmin && eta<=cutPara.etatrgmax) 
      return kTRUE; 
    else 
      return kFALSE;
}

bool DiHadronCorrelationMultiBaseFWLite::GetPtassBin(double pt, double eta, int jass)
{
    if(pt>=cutPara.ptassmin[jass] && pt<=cutPara.ptassmax[jass] && eta>=cutPara.etaassmin && eta<=cutPara.etaassmax) 
      return kTRUE;
    else 
      return kFALSE;
}

double DiHadronCorrelationMultiBaseFWLite::GetTrgWeight(double nmult)
{
  double trgweight=1.0;
  if(hTrgWeight) trgweight = hTrgWeight->GetBinContent(hTrgWeight->FindBin(nmult));
  return trgweight;
}

double DiHadronCorrelationMultiBaseFWLite::GetEffWeight(double eta, double pt, double zvtx, int centbin)
{
//  if(pt>10) pt=10;
  double effweight = 1.0;
  if(!hEffWeight) return effweight;
  if(!cutPara.IsHI) effweight = hEffWeight->GetBinContent(hEffWeight->FindBin(eta,pt));
  else effweight = hEffWeight->GetBinContent(hEffWeight->FindBin(eta,pt,centbin));
  if(effweight<0.01) effweight=1.0;
  return effweight;
}

TList* DiHadronCorrelationMultiBaseFWLite::GetOutputs() 
{
  TList* outputlist = new TList();  	
  outputlist->Add(hNVtx);
  outputlist->Add(hNVtxVsNMult);
  outputlist->Add(hZVtx);
  outputlist->Add(hXYVtx);
  outputlist->Add(hZVtxSep);
  outputlist->Add(hXVtxSep);
  outputlist->Add(hYVtxSep);
  outputlist->Add(hXYZVtxSep);
  outputlist->Add(hXYZVtxSepMin);
  outputlist->Add(hXYZVtxSepMin2);
  outputlist->Add(hZVtxSim);
  outputlist->Add(hXYVtxSim);
  outputlist->Add(hZVtxRecoVsSim);
  outputlist->Add(hXVtxRecoVsSim);
  outputlist->Add(hYVtxRecoVsSim);
  outputlist->Add(hZVtxResVsNMult);
  outputlist->Add(hXVtxResVsNMult);
  outputlist->Add(hYVtxResVsNMult);
  outputlist->Add(hTrkZVtxRes);
  outputlist->Add(hTrkXYVtxRes);
  outputlist->Add(hTrkZVtxResSig);
  outputlist->Add(hTrkXYVtxResSig);
  outputlist->Add(hTrkZVtxResVsNMult);
  outputlist->Add(hTrkXVtxResVsNMult);
  outputlist->Add(hTrkYVtxResVsNMult);
  outputlist->Add(hTrkZVtxResVsPt);
  outputlist->Add(hTrkXVtxResVsPt);
  outputlist->Add(hTrkYVtxResVsPt);
  outputlist->Add(hTrkZVtxSimResVsNMult);
  outputlist->Add(hTrkXVtxSimResVsNMult);
  outputlist->Add(hTrkYVtxSimResVsNMult);
  outputlist->Add(hMultRawAll);
  outputlist->Add(hMultCorrAll);
  outputlist->Add(hMultRawTrigVsAssoc);
  outputlist->Add(hMultMaxVsSec);
  outputlist->Add(hMultMaxVsThird);
  outputlist->Add(hMultMaxVsSecVsZVtxSep);
  outputlist->Add(hMultMaxVsThirdVsZVtxSep);
  outputlist->Add(hPtAll_trg);
  outputlist->Add(hdNdetadptAll_trg);
  outputlist->Add(hdNdetadphiAll_trg);
  outputlist->Add(hPtAll_ass);
  outputlist->Add(hdNdetadptAll_ass);
  outputlist->Add(hdNdetadphiAll_ass);
  outputlist->Add(hPtCorrAll_trg);
  outputlist->Add(hdNdetadptCorrAll_trg);
  outputlist->Add(hdNdetadphiCorrAll_trg);
  outputlist->Add(hPtCorrAll_ass);
  outputlist->Add(hdNdetadptCorrAll_ass);
  outputlist->Add(hdNdetadphiCorrAll_ass);
  outputlist->Add(hdNJetsAll);
  outputlist->Add(hPtJetsAll);
  outputlist->Add(hdNdetadphiJetsAll);
  outputlist->Add(hCentrality);
  outputlist->Add(hEPAngle);
  outputlist->Add(hHFTowerSum);
  outputlist->Add(hHFvsNpixel);
  outputlist->Add(hHFvsZDC);
  hHLTPaths->LabelsDeflate();
  outputlist->Add(hHLTPaths);
/*
  outputlist->Add(hEtTot); 
  outputlist->Add(hInvMass); 
  outputlist->Add(hMissEt); 
  outputlist->Add(hMeanPtVsMult);
  outputlist->Add(hImbalance); 
  outputlist->Add(hdNdPtdcostheta);
  outputlist->Add(hBetaVsP);
  outputlist->Add(hLeadTrackPt);
*/
  outputlist->Add(hInvMass_Signal);
  outputlist->Add(hInvMassVsPt_Signal);
  outputlist->Add(hOpenAngleVsPt_Signal);
  outputlist->Add(hInvMass_Background);
  outputlist->Add(hInvMassVsPt_Background);
  outputlist->Add(hOpenAngleVsPt_Background);
  outputlist->Add(hInvMass_diphoton);
  outputlist->Add(hInvMassVsPt_diphoton);
  outputlist->Add(hOpenAngleVsPt_diphoton);
  outputlist->Add(hV0InvMassVsPt);

  outputlist->Add(eventNtuple);
  outputlist->Add(highmultNtuple);
  if(cutPara.IsTrackNtuple) outputlist->Add(trackNtuple);
  outputlist->Add(hiGenInfoNtuple);

  return outputlist;
}

DiHadronCorrelationMultiBaseFWLite::ParticleType DiHadronCorrelationMultiBaseFWLite::GetParticleID(TString particleid)
{
  ParticleType type;
  if(particleid == "GenParticle")
    type=kGenParticle;
  else if(particleid == "Track")
    type=kTrack;
  else if(particleid == "Jet")
    type=kJet;
  else if(particleid == "Muon")
    type=kMuon;
  else if(particleid == "Photon")
    type=kPhoton;
  else if(particleid == "EcalSC")
    type=kEcalSC;
  else if(particleid == "EcalBC")
    type=kEcalBC;
  else if(particleid == "PFHadron")
    type=kPFHadron;
  else if(particleid == "PFPhoton")
    type=kPFPhoton;  
  else if(particleid == "PFHadronPhoton")
    type=kPFHadronPhoton;
  else if(particleid == "PFPhotonTrack")
    type=kPFPhotonTrack;
  else if(particleid == "PFElectron")
    type=kPFElectron;
  else if(particleid == "PFMuon")
    type=kPFMuon;
  else if(particleid == "PFNeutral")
    type=kPFNeutral;
  else if(particleid == "PFHadronHF")
    type=kPFHadronHF;
  else if(particleid == "PFEgammaHF")
    type=kPFEgammaHF;
  else if(particleid == "PionZero")
    type=kPionZero;
  else if(particleid == "PionZeroBkgUp")
    type=kPionZeroBkgUp;
  else if(particleid == "PionZeroBkgDown")
    type=kPionZeroBkgDown;
  else if(particleid == "CaloTower")
    type=kCaloTower;
  else if(particleid == "EcalRecHit")
    type=kEcalRecHit;
  else if(particleid == "HcalRecHit")
    type=kHcalRecHit;
  else if(particleid == "Kshort")
    type=kKshort;
  else if(particleid == "Lambda")
    type=kLambda;
  return type;
}
