// -*- C++ -*-
//
// Package:    DimuonAnalyzer
// Class:      DimuonAnalyzer
// 
/**\class DimuonAnalyzer DimuonAnalyzer.cc UserCode/DimuonAnalyzer/src/DimuonAnalyzer.cc

 Description: make dimuon from reco::Tracks and recoGenPArticles efficiency analysis

*/
//
// Original Author:  Camelia Mironov,40 1-A32,+41227679747,
//         Created:  Sun Feb  7 15:25:05 CET 2010
// $Id: DimuonAnalyzer.cc,v 1.2 2010/08/02 15:55:03 miheejo Exp $
//
//


// system include files
#include <memory>
#include <iostream>
#include <string>
#include <fstream>

// user include files
#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenVertex.h"
#include "HepMC/HeavyIon.h"


#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "SimDataFormats/CrossingFrame/interface/CrossingFrame.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"

// data formats
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonTrackLinks.h"
#include "DataFormats/RecoCandidate/interface/TrackAssociation.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"

// root include files
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include "TNtuple.h"
#include "TLorentzVector.h"


using namespace reco;
using namespace edm;
using namespace std;
using namespace HepMC;

const double m_mu = .105658;
const double massMu = 0.105658369;

//_______________________________________________________________________
class DimuonAnalyzer : public edm::EDAnalyzer 
{
// class declaration
public:
  explicit DimuonAnalyzer(const edm::ParameterSet&);
  ~DimuonAnalyzer();
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ----------member data ---------------------------
  TH2D *phPtY_genDimuonAll; 
  TH1D *phPt_genDimuon;   
  TH1D *phY_genDimuon; 
  TH1D *phM_genDimuon;

  TH2D *phPtY_recoDimuonAll;
  TH1D *phPt_recoDimuon;
  TH1D *phY_recoDimuon;
  TH1D *phM_recoDimuon;
  TH2D *phPtPhi_recoTrack;

  // By moon
  TH1D *nTMuTrk;

  TH1D *phPt_globalMu;
  TH1D *phEta_globalMu;
  TH1D *phPhi_globalMu;
  TH1D *nGLB;

  TH1D *phPt_staMu;
  TH1D *phEta_staMu;
  TH1D *phPhi_staMu;
  TH1D *nSTA;

  TH1D *phPt_otherMu;
  TH1D *phEta_otherMu;
  TH1D *phPhi_otherMu;
  TH1D *nOTH;
  
  TH2D *phPtEta_recoTrack;

  edm::InputTag     genparticletag;
  edm::InputTag     muontracktag; 
  edm::InputTag     muontag; 
  edm::InputTag     tracktag;
  edm::InputTag     simtracktag;  //For the MC studies
  edm::InputTag     gensignaltag;
  edm::InputTag     vtxtag;

  // cuts to be set/read in/from the configuration file 
  double                  massMax_dimuon;
  double                  massMin_dimuon;
  int                     pdg_dimuon;
  double                  ptMin_dimuon;
     
  double                  etaMax_muon;
  double                  etaMin_muon;
  double                  ptMin_muon;

  double                  etaMax_track;
  double                  etaMin_track;
  double                  ptMin_track;
  
  double                  b;

  double                  ntracks;    //trackCollection.product()->size()
  double                  nmuons;     //muonCollection.product()->size()

  Bool_t doReco;      //Centrality, RECO muons, RECO tracks
  Bool_t doSingMu;    //RECO single muon
  Bool_t doMC;        //Is GEN, SIM info included?
  Bool_t doSim;       //SIM tracks
  Bool_t doSignal;    //GEN hisignal
  Bool_t doZ0check;   //GEN Z0 daughter trace

  Bool_t acceptDimuon(Float_t pt, Float_t m);
  Bool_t acceptMuon(Float_t pt, Float_t eta);
  Bool_t acceptTrack(Float_t pt, Float_t eta);

  void ShowDaughter(const Candidate* ptl);
  
  //for centrality
  const  CentralityBins *cbins_;
  double bmean, bsigma;
  double npartmean, npartsigma;
  double ncollmean, ncollsigma;
  double hf;
  int    bin;

  //for vertex
  const reco::VertexCollection *vertices;
  int                          nvtx;
  double                       vx,vy,vz;
  
  TNtuple                      *pnEventInfo;          //RECO event informations
  TNtuple                      *pnDimuRecoInfo;       //RECO dimuon
  TNtuple                      *pnSinglemuRecoInfo;    //RECO single muon
  TNtuple                      *pnSTAmuInfo;          //RECO STA muon
  TNtuple                      *pnGLBmuInfo;          //RECO GLB muon
  TNtuple                      *pnDimuSimInfo;        //SIM dimuon
  TNtuple                      *pnDimuGenInfo;        //GEN dimuon
  TNtuple                      *pnSinglemuGenInfo;    //GEN single muon
  TNtuple                      *pnDimuGeneratorInfo;  //GEN dimuon (bkg only)
  TNtuple                      *pnZ0hiSignalInfo;     //GEN Z0 (signal only)
};


//_________________________________________________________________
DimuonAnalyzer::DimuonAnalyzer(const edm::ParameterSet& pset):
  genparticletag(pset.getParameter<edm::InputTag>("genParticle") ),
  muontracktag(pset.getUntrackedParameter<edm::InputTag>("muonTracks") ),
  muontag(pset.getUntrackedParameter<edm::InputTag>("muons") ),
  tracktag(pset.getUntrackedParameter<edm::InputTag>("trackTracks") ),
  simtracktag(pset.getUntrackedParameter<edm::InputTag>("simtracks") ),
  gensignaltag(pset.getUntrackedParameter<edm::InputTag>("genSignal") ),
  vtxtag(pset.getUntrackedParameter<edm::InputTag>("vertices") ),
  massMax_dimuon(pset.getParameter<double>("massMaxDimuon") ),
  massMin_dimuon(pset.getParameter<double>("massMinDimuon") ),
  pdg_dimuon(pset.getParameter<double>("pdgDimuon") ),
  ptMin_dimuon(pset.getParameter<double>("ptMinDimuon") ),
  etaMax_muon(pset.getParameter<double>("etaMaxMuon") ),
  etaMin_muon(pset.getParameter<double>("etaMinMuon") ),
  ptMin_muon(pset.getParameter<double>("ptMinMuon") ),
  etaMax_track(pset.getParameter<double>("etaMaxTrack") ),
  etaMin_track(pset.getParameter<double>("etaMinTrack") ),
  ptMin_track(pset.getParameter<double>("ptMinTrack") ),
  doReco(pset.getParameter<bool>("doReco")),
  doSingMu(pset.getParameter<bool>("doRecoSingleMuon")),
  doMC(pset.getParameter<bool>("doMC")),
  doSim(pset.getParameter<bool>("doSim")),
  doSignal(pset.getParameter<bool>("doSignal")),
  doZ0check(pset.getParameter<bool>("doZ0check")),
  cbins_(0)
{
  // constructor
}


//_________________________________________________________________
DimuonAnalyzer::~DimuonAnalyzer()
{
  // destructor
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
}


//_________________________________________________________________
void DimuonAnalyzer::analyze(const edm::Event& ev, const edm::EventSetup& iSetup)
{
  using namespace std;
  using namespace edm;

  // method called to for each event 
  edm::LogInfo("DimuonAnalyzer")<<"Start analyzing event ...";

  if(doReco)
  {
    //-------- Get vertices
    edm::Handle<reco::VertexCollection> vertexCollection;
    ev.getByLabel(vtxtag,vertexCollection);
    vertices = vertexCollection.product();
    edm::LogInfo("DimuonAnalyzer::analyze()")<<"Number of vertices in the event = "<< vertexCollection.product()->size();
    bool vertexAvailable =  ev.getByLabel(vtxtag,vertexCollection);
    if (!vertexAvailable)
    {
      ev.getByLabel("pixelVertices",vertexCollection);
      edm::LogInfo("DimuonAnalyzer::analyze()")<<"Using the pp vertex collection: pixelVertices ";
    }
    nvtx = vertices->size();
    vx = vertices->begin()->position().x();
    vy = vertices->begin()->position().y();
    vz = vertices->begin()->position().z();
    
    const reco::Vertex *vtx = &(vertices->at(0));

    //------- reco::Track loop
    edm::Handle<edm::View<reco::Track> >  trackCollection;
    ev.getByLabel(tracktag, trackCollection); 
    if( trackCollection.isValid() )
    {
      for(edm::View<reco::Track> ::size_type i=0; i < trackCollection.product()->size(); i++)
      {
        edm::RefToBase<reco::Track> recTrack(trackCollection, i);
        if ( recTrack.isNull() ) continue;
        if( !( acceptTrack(recTrack->pt(),recTrack->eta()) ) ) continue;
        phPtEta_recoTrack->Fill(recTrack->pt(),recTrack->eta());
        phPtPhi_recoTrack->Fill(recTrack->pt(),recTrack->phi());
      }
      ntracks = trackCollection.product()->size(); 
    }
    else
    {
      LogDebug("DimuonAnalyzer::analyze()") << "##### NO TrackCollection found for reconstructed tracks!";
      ntracks = 0;
    }
   
    // ---- Centrality
    cbins_ = 0;
    if (!cbins_) cbins_ = getCentralityBinsFromDB(iSetup);
    edm::Handle<reco::Centrality> cent;
    ev.getByLabel(InputTag("hiCentrality"),cent);
    hf = cent->EtHFhitSum();
    bin = cbins_->getBin(hf);
    bmean = cbins_->bMeanOfBin(bin);
    bsigma = cbins_->bSigmaOfBin(bin);
    npartmean = cbins_->NpartMeanOfBin(bin);
    npartsigma = cbins_->NpartSigmaOfBin(bin);
    ncollmean = cbins_->NcollMeanOfBin(bin);
    ncollsigma = cbins_->NcollSigmaOfBin(bin);

    // ----- reco::Track->MUON loop
    // for all reco muons info by Moon
    if (doSingMu)
    {
     // edm::Handle<CandidateView> muons;
      edm::Handle<edm::View<reco::Muon> >muons;
      ev.getByLabel(muontag,muons);
      int nTMu = 0; int ngMu = 0; int nsMu = 0; int noMu = 0;
      for(unsigned int j = 0; j < muons->size(); ++j){
       //   CandidateBaseRef muCandRef = muons->refAt(j);
          edm::RefToBase<reco::Muon> muCandRef(muons, j);
          if ( muCandRef.isNull() ) continue;
      
          nTMu++;   // count number of total muons
          if(muCandRef->isGlobalMuon()){
              double pt = muCandRef->globalTrack()->pt();
              double eta = muCandRef->globalTrack()->eta();
              double phi = muCandRef->globalTrack()->phi();
              double dxy = muCandRef->globalTrack()->dxy(vtx->position());
              double sigmaDxy = sqrt(muCandRef->globalTrack()->dxyError()*muCandRef->globalTrack()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
              double dz = muCandRef->globalTrack()->dz(vtx->position());
              double sigmaDz = sqrt(muCandRef->globalTrack()->dzError()*muCandRef->globalTrack()->dzError()+vtx->zError()*vtx->zError());
              
              pnGLBmuInfo->Fill(pt,eta,phi,dxy,dz,sigmaDxy,sigmaDz); 
              ngMu++;
              
              // single muon cuts for histogram
              if( !( acceptMuon(pt,eta)) ) continue;
              phPt_globalMu->Fill(pt);
              phEta_globalMu->Fill(eta);
              phPhi_globalMu->Fill(phi);
          }
          if(muCandRef->isStandAloneMuon()){
              double pt = muCandRef->standAloneMuon()->pt();
              double eta = muCandRef->standAloneMuon()->eta();
              double phi = muCandRef->standAloneMuon()->phi();
              double dxy = muCandRef->standAloneMuon()->dxy(vtx->position());
              double sigmaDxy = sqrt(muCandRef->standAloneMuon()->dxyError()*muCandRef->standAloneMuon()->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
              double dz = muCandRef->standAloneMuon()->dz(vtx->position());
              double sigmaDz = sqrt(muCandRef->standAloneMuon()->dzError()*muCandRef->standAloneMuon()->dzError()+vtx->zError()*vtx->zError());
              
              pnSTAmuInfo->Fill(pt,eta,phi,dxy,dz,sigmaDxy,sigmaDz);
              nsMu++;
              
              // single muon cuts for histogram
              if( !( acceptMuon(pt,eta)) ) continue;
              phPt_staMu->Fill(pt);
              phEta_staMu->Fill(eta);
              phPhi_staMu->Fill(phi);
          }
          if(muCandRef->isTrackerMuon()){
              // single muon cuts for histogram
              if( !( acceptMuon(muCandRef->track()->pt(),muCandRef->track()->eta()) ) ) continue;
              phPt_otherMu->Fill(muCandRef->track()->pt());
              phEta_otherMu->Fill(muCandRef->track()->eta());
              phPhi_otherMu->Fill(muCandRef->track()->phi());
              noMu++;
          }
      }// end of reco::Muon loop
      nTMuTrk->Fill(nTMu);nGLB->Fill(ngMu);nSTA->Fill(nsMu);nOTH->Fill(noMu);
      pnSinglemuRecoInfo->Fill(nTMu,ngMu,nsMu,noMu);
    }//end of doSingMu

    //------ Get muon track's closest vertex distance (dxy, dz)
    edm::Handle<edm::View<reco::Track> >muonCollection;
    ev.getByLabel(muontracktag,muonCollection);
    if(muonCollection.isValid() && muonCollection.product()->size() >1 )
    {
      nmuons = muonCollection.product()->size();
      for(edm::View<reco::Track> ::size_type i=0; i < muonCollection.product()->size()-1; i++)
      {
        edm::RefToBase<reco::Track> muTrack1(muonCollection, i);
        if ( muTrack1.isNull() ) continue;

        // single muon cuts
        if( !( acceptMuon(muTrack1->pt(),muTrack1->eta()) ) ) continue;

        for(edm::View<reco::Track> ::size_type j=i+1; j < muonCollection.product()->size(); j++)
        {
          edm::RefToBase<reco::Track> muTrack2(muonCollection, j);
          if ( muTrack2.isNull() ) continue;
          // single muon cuts
          if( !( acceptMuon(muTrack2->pt(),muTrack2->eta()) ) ) continue;
          
          TLorentzVector kid1, kid2;
          double en1 = sqrt(muTrack1->p()*muTrack1->p()+m_mu*m_mu);
          double en2 = sqrt(muTrack2->p()*muTrack2->p()+m_mu*m_mu);
          
          kid1.SetPxPyPzE(muTrack1->px(),muTrack1->py(),muTrack1->pz(),en1);
          kid2.SetPxPyPzE(muTrack2->px(),muTrack2->py(),muTrack2->pz(),en2);
          
          TLorentzVector dimuon;
          dimuon = kid1 + kid2;
          
          // Save single muon's closest vertex distance
          double dxy1 = muTrack1->dxy(vtx->position());
          double sigmadxy1 = sqrt(muTrack1->dxyError()*muTrack1->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
          double dz1 = muTrack1->dz(vtx->position());
          double sigmadz1 = sqrt(muTrack1->dzError()*muTrack1->dzError()+vtx->zError()*vtx->zError());
          double dxy2 = muTrack2->dxy(vtx->position());
          double sigmadxy2 = sqrt(muTrack2->dxyError()*muTrack2->dxyError() + vtx->yError()*vtx->yError()+vtx->xError()*vtx->xError());
          double dz2 = muTrack2->dz(vtx->position());
          double sigmadz2 = sqrt(muTrack2->dzError()*muTrack2->dzError()+vtx->zError()*vtx->zError());

          vector<float> dimupair;
          dimupair.push_back(muTrack1->charge());
          dimupair.push_back(muTrack1->pt());
          dimupair.push_back(muTrack1->eta());
          dimupair.push_back(dxy1);
          dimupair.push_back(sigmadxy1);
          dimupair.push_back(dz1);
          dimupair.push_back(sigmadz1);
          dimupair.push_back(muTrack2->charge());
          dimupair.push_back(muTrack2->pt());
          dimupair.push_back(muTrack2->eta());
          dimupair.push_back(dxy2);
          dimupair.push_back(sigmadxy2);
          dimupair.push_back(dz2);
          dimupair.push_back(sigmadz2);
          dimupair.push_back(dimuon.Pt());
          dimupair.push_back(dimuon.Rapidity());
          dimupair.push_back(dimuon.M());
          pnDimuRecoInfo->Fill(&dimupair[0]);
          dimupair.clear();

          // only opposite sign dimuons
          if(muTrack1->charge() * muTrack2->charge()>0) continue;
          phPtY_recoDimuonAll->Fill(dimuon.Pt(),dimuon.Rapidity());
          
          if ( !(acceptDimuon(dimuon.Pt(),dimuon.M())) ) continue;
          LogInfo("DimuonAnalyzer:RecoMuonLoop:") << "RecoKid0: pt="<<kid1.Pt()<<"\t eta = "<< kid1.Eta();
          LogInfo("DimuonAnalyzer:RecoMuonLoop")  << "RecoKid1: pt="<<kid2.Pt()<<"\t eta = "<< kid2.Eta();	   
          phPt_recoDimuon->Fill(dimuon.Pt());
          phY_recoDimuon->Fill(dimuon.Rapidity());
          phM_recoDimuon->Fill(dimuon.M());

        }//2nd muon loop
      }// 1st muon loop
    }// muonCollection is valid and has more than 2 muons reconstructed
    else{
      LogDebug("DimuonAnalyzer::analyze()") << "##### NO TrackCollection found for recoMuons or size<2!";
      nmuons = 0;
    }
  }// doReco is turned on
  else  // If doReco isn't turned on
  {
    ntracks = nmuons = -1;
    hf = bin = bmean = bsigma = npartmean = npartsigma = ncollmean = ncollsigma = -1;
    nvtx = vx = vy = vz = -1;
  }
 
  if(doMC){
    //------ recoGenParticle loop
    // Check all GEN muons info & its mom
    edm::Handle<reco::GenParticleCollection> genCollection;
    ev.getByLabel(genparticletag,genCollection);
    if( genCollection.isValid() )
    {
        int muons=0;
        int smuons=0;
        for(reco::GenParticleCollection::size_type i=0; i < genCollection.product()->size(); i++)
        {
            const GenParticleRef genPart1(genCollection,i);
            
            //Check all gen particles from Z0
            if (doZ0check && genPart1->pdgId() == 23)
            {
              Int_t ndau = genPart1->numberOfDaughters();
              for (int d=0; d<ndau; d++)
              {
                cout << "--Z0 daughter " << d+1 << endl;
                const Candidate *dau = genPart1->daughter(d);
                ShowDaughter(dau);
              }
            }
            
            if( abs(genPart1->pdgId()) != 13 ) continue;
            muons++;

            if( genPart1->status() != 1) continue;
            smuons++;
            //if( abs(genPart1->pdgId()) != 13 || genPart1->status() != 1) continue;
            //if( !(acceptMuon(genPart1->pt(),genPart1->eta())) ) continue;
            
            vector<float> gensingle;
            gensingle.push_back(genPart1->pdgId());
            gensingle.push_back(genPart1->pt());
            gensingle.push_back(genPart1->pz());
            gensingle.push_back(genPart1->eta());
            gensingle.push_back(genPart1->phi());
            pnSinglemuGenInfo->Fill(&gensingle[0]);
            gensingle.clear();
                        
            for(reco::GenParticleCollection::size_type j=i+1; j < genCollection.product()->size(); j++)
            {
              const GenParticleRef genPart2(genCollection,j);
              if( abs(genPart2->pdgId()) != 13 || genPart2->status() != 1) continue;
              //if( !(acceptMuon(genPart2->pt(),genPart2->eta())) ) continue;

              float genPart1_e = sqrt(genPart1->p()*genPart1->p()+massMu*massMu);
              float genPart2_e = sqrt(genPart2->p()*genPart2->p()+massMu*massMu);

              TLorentzVector kid1, kid2;
              kid1.SetPxPyPzE(genPart1->px(),genPart1->py(),genPart1->pz(),genPart1_e);
              kid2.SetPxPyPzE(genPart2->px(),genPart2->py(),genPart2->pz(),genPart2_e);

              TLorentzVector dimuon;
              dimuon = kid1+kid2;

              float momid1[2]={10}, momstat1[2]={10};
              int numMom = genPart1->numberOfMothers();
              if(numMom > 0)
              {
                const Candidate *mom = genPart1->mother(0);
                momid1[0] = mom->pdgId();
                momstat1[0] = mom->status();
                if (doZ0check)
                {
                  cout << "\t1st: " << genPart1->numberOfMothers()<<" "<< genPart1->pdgId()
                       << " " << genPart1->pt() <<" "<< genPart1->status()<<endl;
                  cout << "\t     " << mom->numberOfMothers() << " " << mom->pdgId() << " "
                       <<  mom->pt() << " " << mom->status() << endl;
                }
                for (int a=0; mom->numberOfMothers()>0 ;a++)
                {
                  mom = mom->mother(0);
                  momid1[1] = mom->pdgId();
                  momstat1[1] = mom->status();
                  if (doZ0check)
                    cout<<mom->numberOfMothers()<<" "<<mom->pdgId()<<" "<<mom->pt()<<" "<<mom->status() << endl;
                }
              }
              if (doZ0check)
                cout << "end 1st muon:" << momid1[0] << " " << momid1[1] << endl;
  
              float momid2[2]={10}, momstat2[2]={10};
              numMom = genPart2->numberOfMothers();
              if(numMom > 0)
              {
                const Candidate *mom = genPart2->mother(0);
                momid2[0] = mom->pdgId();
                momstat2[0] = mom->status();
                if (doZ0check)
                {
                  cout << "\t2nd: " << genPart2->numberOfMothers()<<" "<<genPart2->pdgId()
                       << " " << genPart2->pt() << " "<<genPart2->status() << endl;
                  cout << "\t     " << mom->numberOfMothers() << " " << mom->pdgId()
                       << " " <<  mom->pt() << " " << mom->status()<< endl;
                }
                for (int a=0; mom->numberOfMothers()>0 ;a++)
                {
                  mom = mom->mother(0);
                  momid2[1] = mom->pdgId();
                  momstat2[1] = mom->status();
                  if (doZ0check)
                    cout<<mom->numberOfMothers()<<" "<<mom->pdgId()<<" "<<mom->pt()<<" "<<mom->status() << endl;
                }
              }
              if (doZ0check)
              {
                cout <<"end 2nd muon:" << momid2[0] << " " << momid2[1] << endl;
                cout << "\t\tDimuon " << genPart1->pdgId()*genPart2->pdgId()/169 << ": " << dimuon.Pt() << " " << dimuon.Mag() << endl;
              }
              
              vector<float> geninfo;
              geninfo.push_back(genPart1->pdgId());
              geninfo.push_back(genPart1->pt());
              geninfo.push_back(genPart1->pz());
              geninfo.push_back(genPart1->eta());
              geninfo.push_back(genPart1->phi());
              geninfo.push_back(momid1[0]);
              geninfo.push_back(momstat1[0]);
              geninfo.push_back(momid1[1]);
              geninfo.push_back(momstat1[1]);
              geninfo.push_back(genPart2->pdgId());
              geninfo.push_back(genPart2->pt());
              geninfo.push_back(genPart2->pz());
              geninfo.push_back(genPart2->eta());
              geninfo.push_back(genPart2->phi());
              geninfo.push_back(momid2[0]);
              geninfo.push_back(momstat2[0]);
              geninfo.push_back(momid2[1]);
              geninfo.push_back(momstat2[1]);
              geninfo.push_back(dimuon.Pt());
              geninfo.push_back(dimuon.Pz());
              geninfo.push_back(dimuon.Rapidity());
              geninfo.push_back(dimuon.Eta());
              geninfo.push_back(dimuon.Phi());
              geninfo.push_back(dimuon.Mag());

              pnDimuGenInfo->Fill(&geninfo[0]);
              geninfo.clear();
              
              //dimuon gen cuts
              if( genPart1->pdgId()*genPart2->pdgId()>0) continue;
              phPtY_genDimuonAll->Fill(dimuon.Pt(),dimuon.Rapidity());
              
              if( !acceptDimuon(dimuon.Pt(),dimuon.Mag()) ) continue;
              phPt_genDimuon->Fill(dimuon.Pt());
              phY_genDimuon->Fill(dimuon.Rapidity());
              phM_genDimuon->Fill(dimuon.Mag());
            }//genparticle 2nd loop
        }//genparticle 1st loop
        if (doZ0check)
          cout << "All single muons : " << muons << " " << smuons << endl;
    }//------ recoGenParticle loop end
    else  LogDebug("DimuonAnalyzer::analyze()") << "##### NO genPArticleCollectino found!";

    // ---------- event information:
    edm::Handle<edm::HepMCProduct> hepEv;
    ev.getByLabel("generator",hepEv);

    const HepMC::HeavyIon* hi = hepEv->GetEvent()->heavy_ion();
    if(hi!=NULL) b = hi->impact_parameter();
    else b = -99.;

    // For dimuons from background only
    for (HepMC::GenEvent::particle_const_iterator i = hepEv->GetEvent()->particles_begin(); i != hepEv->GetEvent()->particles_end(); ++i)
    {
      HepMC::GenParticle *muon1 = *i;

      if( muon1->status() != 1 || abs(muon1->pdg_id()) != 13) continue;
      float muon1_pt = sqrt(muon1->momentum().px()*muon1->momentum().px()+muon1->momentum().py()*muon1->momentum().py());
      if( !(acceptMuon(muon1_pt,muon1->momentum().eta())) ) continue;
      
      for (HepMC::GenEvent::particle_const_iterator j = i; j != hepEv->GetEvent()->particles_end(); ++j)
      {
        if (j == i) continue;
        HepMC::GenParticle *muon2 = *j;

        if(muon2->status() != 1 || abs(muon2->pdg_id()) != 13) continue;
        float muon2_pt = sqrt(muon2->momentum().px()*muon2->momentum().px()+muon2->momentum().py()*muon2->momentum().py());
        if( !(acceptMuon(muon2_pt,muon2->momentum().eta())) ) continue;
        // Save all pairs (do not regarding like sign or oppisite sign)
        
        TLorentzVector kid1, kid2;
        kid1.SetPxPyPzE(muon1->momentum().px(),muon1->momentum().py(),muon1->momentum().pz(),muon1->momentum().e());
        kid1.SetPxPyPzE(muon2->momentum().px(),muon2->momentum().py(),muon2->momentum().pz(),muon2->momentum().e());
        
        TLorentzVector dimuon;
        dimuon = kid1 + kid2;

        vector<float> geninfo;
        geninfo.push_back(muon1->pdg_id());
        geninfo.push_back(muon1_pt);
        geninfo.push_back(muon1->momentum().pz());
        geninfo.push_back(muon1->momentum().eta());
        geninfo.push_back(muon2->momentum().phi());
        geninfo.push_back(muon2->pdg_id());
        geninfo.push_back(muon2_pt);
        geninfo.push_back(muon2->momentum().pz());
        geninfo.push_back(muon2->momentum().eta());
        geninfo.push_back(muon2->momentum().phi());
        geninfo.push_back(dimuon.Pt());
        geninfo.push_back(dimuon.Pz());
        geninfo.push_back(dimuon.Rapidity());
        geninfo.push_back(dimuon.Eta());
        geninfo.push_back(dimuon.Phi());
        geninfo.push_back(dimuon.M());
        
        pnDimuGeneratorInfo->Fill(&geninfo[0]);
        geninfo.clear();
      } //2nd muon loop
    } //1st muon loop

    // Get gen information of hiSignal
    if (doSignal)
    {
      edm::Handle<edm::HepMCProduct> hepEv_s;
      ev.getByLabel(gensignaltag,hepEv_s);
      // For dimuons from signal only
      for (HepMC::GenEvent::particle_const_iterator i = hepEv_s->GetEvent()->particles_begin(); i != hepEv_s->GetEvent()->particles_end(); ++i)
      {
        HepMC::GenParticle *ptl = *i;

        //if( abs(ptl->pdg_id()) != 23) continue;
        if( ptl->status() != 3 || abs(ptl->pdg_id()) != 23) continue;
        
        TLorentzVector genZ0;
        genZ0.SetPxPyPzE(ptl->momentum().px(),ptl->momentum().py(),ptl->momentum().pz(),ptl->momentum().e());
        float ptl_pt = sqrt(ptl->momentum().px()*ptl->momentum().px()+ptl->momentum().py()*ptl->momentum().py());
        
        vector<float> hisinfo;
        hisinfo.push_back(ptl->status());
        hisinfo.push_back(ptl_pt);
        hisinfo.push_back(ptl->momentum().pz());
        hisinfo.push_back(genZ0.Rapidity());
        hisinfo.push_back(ptl->momentum().phi());
        hisinfo.push_back(ptl->generated_mass());
        pnZ0hiSignalInfo->Fill(&hisinfo[0]);

        hisinfo.clear();
      } 
    }
     
    // Simtrack's loop
    if(doSim)
    {
      edm::Handle<TrackingParticleCollection> simCollection ;
      ev.getByLabel(simtracktag,simCollection);
      for(TrackingParticleCollection::size_type i=0; i < simCollection.product()->size()-1; i++)
      {
        const TrackingParticleRef simTrack1(simCollection, i);
        if( simTrack1.isNull() ) continue;
        // single muon cuts
        if( !( acceptMuon(simTrack1->pt(),simTrack1->eta()) ) ) continue;
        
        if(abs(simTrack1->pdgId())==13 && simTrack1->status() == 1)
        {
          TVector3 S3Muon1(simTrack1->px(),simTrack1->py(),simTrack1->pz());
          double SMuonE1 =sqrt((S3Muon1.Mag()*S3Muon1.Mag())+(massMu*massMu));
          TLorentzVector SMuon1(S3Muon1,SMuonE1);
          
          for(TrackingParticleCollection::size_type j=i+1; j < simCollection.product()->size(); j++)
          {
            const TrackingParticleRef simTrack2(simCollection, j);
            if( simTrack2.isNull() ) continue;
            // single muon cuts
            if( !( acceptMuon(simTrack2->pt(),simTrack2->eta()) ) ) continue;
            
            if(abs(simTrack2->pdgId())==13 && simTrack2->status() == 1)
            {
              TVector3 S3Muon2(simTrack2->px(),simTrack2->py(),simTrack2->pz());
              double SMuonE2 =sqrt(((S3Muon2.Mag())*(S3Muon2.Mag()))+(massMu*massMu));
              TLorentzVector SMuon2(S3Muon2,SMuonE2);
              TLorentzVector SdiMuon = SMuon1 + SMuon2;
              
              vector<float> simdimu;
              simdimu.push_back(simTrack1->pdgId());
              simdimu.push_back(SMuon1.Pt());
              simdimu.push_back(SMuon1.Pz());
              simdimu.push_back(SMuon1.Eta());
              simdimu.push_back(simTrack2->pdgId());
              simdimu.push_back(SMuon2.Pt());
              simdimu.push_back(SMuon2.Pz());
              simdimu.push_back(SMuon2.Eta());
              simdimu.push_back(SdiMuon.Pt());
              simdimu.push_back(SdiMuon.Pz());
              simdimu.push_back((0.5)*log((SdiMuon.E()+SdiMuon.Pz())/(SdiMuon.E()-SdiMuon.Pz())));    //rapidity
              simdimu.push_back(SdiMuon.Eta());
              simdimu.push_back(SdiMuon.M());   //mass

              pnDimuSimInfo->Fill(&simdimu[0]);
              simdimu.clear();
            }//only for muons
          }//end of 2nd simtrack
        }//only for muons
      }//end of 1st simtrack
    }//only for doSim is turned on
  }
  else  //If don't turn on doMC
    b = -99.;

  // fill event info tuple for reco
  pnEventInfo->Fill(ntracks,nmuons,bmean,bsigma,npartmean,npartsigma,ncollmean,ncollsigma,bin,hf,b,nvtx,vx,vy,vz);

  edm::LogInfo("DimuonAnalyzer")<<"Finished analyzing event ...";  
}

//_________________________________________________________________
void DimuonAnalyzer::beginJob()
{
  //method called once each job just before starting event loop
  edm::LogInfo("DimuonAnalyzer::beginJob()")<<"Begin initialization in beginJob()";
  edm::Service<TFileService> fs;

  // all dimuons, without any cuts
  phPtY_genDimuonAll  = fs->make<TH2D>("phPtY_genDimuonAll",";p_{T}[GeV/c];rapidity (y)",200,0,100,10,-5.,5.) ;

  // gen dimuons that passed single muon and dimuon cuts
  phPt_genDimuon      = fs->make<TH1D>("phPt_genDimuon",";p_{T}[GeV/c]",200,0,100);           phPt_genDimuon->Sumw2();
  phY_genDimuon       = fs->make<TH1D>("phY_genDimuon",";rapidity (y)",50,-2.5,2.5);          phY_genDimuon->Sumw2();
  phM_genDimuon       = fs->make<TH1D>("phM_genDimuon",";M[GeV/c^2]",400,0.,200);             phM_genDimuon->Sumw2();

  phPtY_recoDimuonAll = fs->make<TH2D>("phPtY_recoDimuonAll",";p_{T}[GeV/c];rapidity (y)",200,0,100,10,-5.,5.) ;
  phPt_recoDimuon     = fs->make<TH1D>("phPt_recoDimuon",";p_{T}[GeV/c]",200,0,100);          phPt_recoDimuon->Sumw2();
  phY_recoDimuon      = fs->make<TH1D>("phY_recoDimuon",";rapidity (y)",50,-2.5,2.5);         phY_recoDimuon->Sumw2();
  phM_recoDimuon      = fs->make<TH1D>("phM_recoDimuon",";M[GeV/c^2]",400,0.,200);            phM_recoDimuon->Sumw2();

  phPt_globalMu       = fs->make<TH1D>("phPt_globalMu",";p_{T}[GeV/c]",200,0,100);            phPt_globalMu->Sumw2();
  phPhi_globalMu      = fs->make<TH1D>("phPhi_globalMu",";#phi [rad]",100,-4,4);              phPhi_globalMu->Sumw2();
  phEta_globalMu      = fs->make<TH1D>("phEta_globalMu",";#eta [rad]",100,-4,4);              phEta_globalMu->Sumw2();
  
  phPt_staMu          = fs->make<TH1D>("phPt_staMu",";p_{T}[GeV/c]",200,0,100);               phPt_staMu->Sumw2();
  phPhi_staMu         = fs->make<TH1D>("phPhi_staMu",";#phi [rad]",100,-4,4);                 phPhi_staMu->Sumw2();
  phEta_staMu         = fs->make<TH1D>("phEta_staMu",";#eta [rad]",100,-4,4);                 phEta_staMu->Sumw2();

  phPt_otherMu        = fs->make<TH1D>("phPt_otherMu",";p_{T}[GeV/c]",200,0,100);             phPt_otherMu->Sumw2();
  phPhi_otherMu       = fs->make<TH1D>("phPhi_otherMu",";#phi [rad]",100,-4,4);               phPhi_otherMu->Sumw2();
  phEta_otherMu       = fs->make<TH1D>("phEta_otherMu",";#eta [rad]",100,-4,4);               phEta_otherMu->Sumw2();
  
  nTMuTrk             = fs->make<TH1D>("nTMuTrk",";number of all Muons",100,0,5);
  nGLB                = fs->make<TH1D>("nGLB",";number of global Muons",100,0,5);
  nSTA                = fs->make<TH1D>("nSTA",";number of sta Muons",100,0,5);
  nOTH                = fs->make<TH1D>("nOTH",";number of other Muons",100,0,5);

  phPtEta_recoTrack   = fs->make<TH2D>("phPtEta_recoTrack",";p_{T}[GeV/c];#eta",200,0,100,50,-2.5,2.5) ;    
  phPtPhi_recoTrack   = fs->make<TH2D>("phPtPhi_recoTrack",";p_{T}[GeV/c];#phi",200,0,100,100,-4.,4.) ;    

  pnEventInfo         = fs->make<TNtuple>("pnEventInfo","pnEventInfo","ntrk:nmu:bmean:bsigma:npartmean:npartsigma:ncollmean:ncollsigma:bin:hf:b_gen:nvtx:vx:vy:vz");
  pnSinglemuRecoInfo  = fs->make<TNtuple>("pnSinglemuRecoInfo","pnSinglemuRecoInfo","nTotMu:nGLB:nSTA:nTRK");
  pnDimuRecoInfo      = fs->make<TNtuple>("pnDimuRecoInfo","pnDimuRecoInfo","mu1charge:mu1pt:mu1eta:dxy1:sigmaDxy1:dz1:sigmaDz1:mu2charge:mu2pt:mu2eta:dxy2:sigmaDxy2:dz2:sigmaDz2:dimupt:dimuy:dimum");
  pnSTAmuInfo         = fs->make<TNtuple>("pnSTAmuInfo","pnSTAmuInfo","pt:eta:phi:dxy:dz:sigmaDxy:sigmaDz");
  pnGLBmuInfo         = fs->make<TNtuple>("pnGLBmuInfo","pnGLBmuInfo","pt:eta:phi:dxy:dz:sigmaDxy:sigmaDz");
  pnDimuGenInfo       = fs->make<TNtuple>("pnDimuGenInfo","pnDimuGenInfo","mu1pdgid:mu1pt:mu1pz:mu1eta:mu1phi:momid0_0:momstat0_0:momid0_1:momstat0_1:mu2pdgid:mu2pt:mu2pz:mu2eta:mu1phi:momid1_0:momstat1_0:momid1_1:momstat1_1:dimupt:dimupz:dimuy:dimueta:dimuphi:dimum");
  pnSinglemuGenInfo   = fs->make<TNtuple>("pnSinglemuGenInfo","pnSinglemuGenInfo","pdgid:pt:pz:eta:phi");
  pnDimuGeneratorInfo = fs->make<TNtuple>("pnDimuGeneratorInfo","pnDimuGeneratorInfo","mu1pdgid:mu1pt:mu1pz:mu1eta:mu1phi:mu2pdgid:mu2pt:mu2pz:mu2eta:mu2phi:dimupt:dimupz:dimuy:dimueta:dimuphi:dimum");
  pnZ0hiSignalInfo    = fs->make<TNtuple>("pnZ0hiSignalInfo","pnZ0hiSignalInfo","status:pt:pz:y:phi:mass");
  pnDimuSimInfo       = fs->make<TNtuple>("pnDimuSimInfo","pnDimuSimInfo","mu1pdgid:mu1pt:mu1pz:mu1eta:mu2pdgid:mu2pt:mu2pz:mu2eta:dimupt:dimupz:dimuy:dimueta:dimum");
 
  edm::LogInfo("DimuonAnalyzer::beginJob()")<<"Done beginJob()";
  return ;
}

//_________________________________________________________________
void DimuonAnalyzer::endJob() 
{
  //method called once each job just after ending the event loop
}


//_________________________________________________________________________
Bool_t DimuonAnalyzer::acceptDimuon(Float_t pt, Float_t m)
{
  // cuts on the dimuon; pt and mass
  Bool_t ok = false;
  Bool_t okmass = ( massMin_dimuon<=m ) && ( m<=massMax_dimuon );
  Bool_t okpt = pt>ptMin_dimuon;

  if( okmass && okpt ) ok = true;

  return ok;
}


//_______________________________________________________________________
Bool_t DimuonAnalyzer::acceptMuon(Float_t pt, Float_t eta)
{
  // cuts on single muon: pt and eta
  Bool_t ok = false;
  Bool_t oketa = ( etaMin_muon<=eta ) && ( eta<=etaMax_muon );
  Bool_t okpt = pt>ptMin_muon;
  
  if ( oketa && okpt ) ok = true;

  return ok;
}


//_________________________________________________________________
Bool_t DimuonAnalyzer::acceptTrack(Float_t pt, Float_t eta)
{
  // cuts on reco::Track: pt and eta
  Bool_t ok = false;
  Bool_t oketa = ( etaMin_track<=eta ) && ( eta<=etaMax_track );
  Bool_t okpt = pt>ptMin_track;
  
  if ( oketa && okpt ) ok = true;

  return ok;
}

void DimuonAnalyzer::ShowDaughter(const Candidate* ptl)
{
  int dnum = ptl->numberOfDaughters();
  cout << "---ptl: " <<ptl->pdgId()<<" "<<ptl->pt()<<" "<<ptl->status()<<endl;
  cout << "----daus: " << dnum << endl;
  
  for (int i=0; i<dnum; i++) ShowDaughter(ptl->daughter(i));
}
//_________________________________________________________________
//define this as a plug-in
DEFINE_FWK_MODULE(DimuonAnalyzer);
