// -*- C++ -*-
//
// Package:    SpikeInspector
// Class:      SpikeInspector
// 
/**\class SpikeInspector SpikeInspector.cc CmsHi/PhotonAnalysis/plugins/SpikeInspector.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
 */
//
// Original Author:  Thomas Quan-Li Roxlo,,,
//         Created:  Mon Jun 21 11:11:16 CEST 2010
// $Id: SpikeInspector.cc,v 1.5 2010/11/11 14:37:06 troxlo Exp $
//
//

#define swissCut 0.95

#define en1 3.0     //breakpoints for the energy bins
#define en2 10.0
#define en3 15.0

// system include files
#include <memory>
#include <iostream>
#include <fstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//-- My Stuff --

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "DataFormats/Common/interface/Handle.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"

#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"

#include "CLHEP/Units/GlobalPhysicalConstants.h"

using namespace edm;
using namespace std;
using namespace reco;

//--------------

//
// class declaration
//
DetId getMaximumRecHit(const reco::BasicCluster &cluster, const EcalRecHitCollection *recHits);
float recHitEnergy(DetId id, const EcalRecHitCollection *recHits);
float recHitTime(DetId id, const EcalRecHitCollection *recHits);

class SpikeInspector : public edm::EDAnalyzer {
    public:
        explicit SpikeInspector(const edm::ParameterSet&);
        ~SpikeInspector();


    private:
        virtual void beginJob() ;
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob() ;

        // ----------member data ---------------------------

        edm::InputTag ebSuperClusterCollection_;
        edm::InputTag ebReducedRecHitCollection_;
        edm::InputTag eeReducedRecHitCollection_;
        edm::InputTag photonCollection_;

        double swissCut_;
        int numEvents;

        CentralityProvider *centrality_;

        TH2D *timingSwissLow;   //en1-en2
        TH2D *timingSwissMid;   //en2-en3
        TH2D *timingSwissHigh;  //en3+

        TH2D *swissE2Low;
        TH2D *swissE2Mid;
        TH2D *swissE2High;

        TH1D *timingLow;
        TH1D *timingMid;
        TH1D *timingHigh;

        TH1D *swissLow;
        TH1D *swissMid;
        TH1D *swissHigh;
        
        TH1D *e2e9Low;
        TH1D *e2e9Mid;
        TH1D *e2e9High;

        TH1D *spikeEnergy;
        TH1D *realEnergy;

        TH1D *spikeEtaLow;
        TH1D *realEtaLow;
        TH1D *spikeEtaMid;
        TH1D *realEtaMid;
        TH1D *spikeEtaHigh;
        TH1D *realEtaHigh;

        TH1D *spikePhiLow;
        TH1D *realPhiLow;
        TH1D *spikePhiMid;
        TH1D *realPhiMid;
        TH1D *spikePhiHigh;
        TH1D *realPhiHigh;

        TH1D *spikeCentLow;
        TH1D *realCentLow;
        TH1D *spikeCentMid;
        TH1D *realCentMid;
        TH1D *spikeCentHigh;
        TH1D *realCentHigh;

        TH1D *spikeMultLow;
        TH1D *realMultLow;
        TH1D *spikeMultMid;
        TH1D *realMultMid;
        TH1D *spikeMultHigh;
        TH1D *realMultHigh;

        TH1D *NoECent;
        TH1D *NoEMult;

        TH1D *photonPtWithSpikes;
        TH1D *photonPtNoSpikes;

        TH1D *numSpikesPerEvent;
        TH1D *numSpikesPerEventCentral;

        TH2D *swissE1E9High;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
SpikeInspector::SpikeInspector(const edm::ParameterSet& iConfig)

{
    numEvents = 0;
    //now do what ever initialization is needed
    ebSuperClusterCollection_        = iConfig.getUntrackedParameter<edm::InputTag>("ebSuperClusterCollection",edm::InputTag("correctedIslandBarrelSuperClusters"));
    ebReducedRecHitCollection_       = iConfig.getUntrackedParameter<edm::InputTag>("ebReducedRecHitCollection");
    eeReducedRecHitCollection_       = iConfig.getUntrackedParameter<edm::InputTag>("eeReducedRecHitCollection");
    photonCollection_                = iConfig.getUntrackedParameter<edm::InputTag>("photonCollection");
    swissCut_                        = iConfig.getUntrackedParameter<double>("swissCut",0.95);

    edm::Service<TFileService> fs;
    timingSwissLow = fs->make<TH2D>("timing-Swiss 3-10 GeV","timing-Swiss 3-10 GeV",80,-20,20,120,0,1.2);
    timingSwissLow->GetXaxis()->SetTitle("Timing (ns)");
    timingSwissLow->GetYaxis()->SetTitle("1-E4/E1");
    timingSwissLow->Sumw2();
    timingSwissMid = fs->make<TH2D>("timing-Swiss 10-15 GeV","timing-Swiss 10-15 GeV",80,-20,20,120,0,1.2);
    timingSwissMid->GetXaxis()->SetTitle("Timing (ns)");
    timingSwissMid->GetYaxis()->SetTitle("1-E4/E1");
    timingSwissMid->Sumw2();
    timingSwissHigh = fs->make<TH2D>("timing-Swiss 15+ GeV","timing-Swiss 15+ GeV",80,-20,20,120,0,1.2);
    timingSwissHigh->GetXaxis()->SetTitle("Timing (ns)");
    timingSwissHigh->GetYaxis()->SetTitle("1-E4/E1");
    timingSwissHigh->Sumw2();

    swissE2Low = fs->make<TH2D>("Swiss-E2E9 3-10 GeV","Swiss-E2/E9 3-10 GeV",120,0,1.2,120,0,1.2);
    swissE2Low->GetYaxis()->SetTitle("E2/E9");
    swissE2Low->GetXaxis()->SetTitle("1-E4/E1");
    swissE2Low->Sumw2();
    swissE2Mid = fs->make<TH2D>("Swiss-E2E9 10-15 GeV","Swiss-E2/E9 10-15 GeV",120,0,1.2,120,0,1.2);
    swissE2Mid->GetYaxis()->SetTitle("E2/E9");
    swissE2Mid->GetXaxis()->SetTitle("1-E4/E1");
    swissE2Mid->Sumw2();
    swissE2High = fs->make<TH2D>("Swiss-E2E9 15+ GeV","Swiss-E2/E9 15+ GeV",120,0,1.2,120,0,1.2);
    swissE2High->GetYaxis()->SetTitle("E2/E9");
    swissE2High->GetXaxis()->SetTitle("1-E4/E1");
    swissE2High->Sumw2();

    timingLow = fs->make<TH1D>("timing 3-10 GeV","timing 3-10 GeV",80,-20,20);
    timingLow->GetXaxis()->SetTitle("Timing (ns)");
    timingMid = fs->make<TH1D>("timing 10-15 GeV","timing 10-15 GeV",80,-20,20);
    timingMid->GetXaxis()->SetTitle("Timing (ns)");
    timingHigh = fs->make<TH1D>("timing 15+ GeV","timing 15+ GeV",80,-20,20);
    timingHigh->GetXaxis()->SetTitle("Timing (ns)");

    swissLow = fs->make<TH1D>("swiss 3-10 GeV","swiss 3-10 GeV",120,0,1.2);
    swissLow->GetXaxis()->SetTitle("1-E4/E1");
    swissMid = fs->make<TH1D>("swiss 10-15 GeV","swiss 10-15 GeV",120,0,1.2);
    swissMid->GetXaxis()->SetTitle("1-E4/E1");
    swissHigh = fs->make<TH1D>("swiss 15+ GeV","swiss 15+ GeV",120,0,1.2);
    swissHigh->GetXaxis()->SetTitle("1-E4/E1");

    e2e9Low = fs->make<TH1D>("E2E9 3-10 GeV","E2/E9 3-10 GeV",120,0,1.2);
    e2e9Low->GetXaxis()->SetTitle("1-E4/E1");
    e2e9Mid = fs->make<TH1D>("E2E9 10-15 GeV","E2/E9 10-15 GeV",120,0,1.2);
    e2e9Mid->GetXaxis()->SetTitle("1-E4/E1");
    e2e9High = fs->make<TH1D>("E2E9 15+ GeV","E2/E9 15+ GeV",120,0,1.2);
    e2e9High->GetXaxis()->SetTitle("1-E4/E1");

    spikeEnergy = fs->make<TH1D>("Spike Energy","Spike Energy",100,0,100);
    spikeEnergy->GetXaxis()->SetTitle("E");
    spikeEnergy->SetLineColor(kRed);
    realEnergy = fs->make<TH1D>("real Energy","Non-Spike Energy",100,0,100);
    realEnergy->GetXaxis()->SetTitle("E");

    spikeEtaLow = fs->make<TH1D>("Spike Eta 3-10 GeV","Spike Eta 3-10 GeV",60,-1.5,1.5);
    spikeEtaLow->GetXaxis()->SetTitle("#eta");
    spikeEtaLow->SetLineColor(kRed);
    realEtaLow = fs->make<TH1D>("real Eta 3-10 GeV","Non-Spike Eta 3-10 GeV",60,-1.5,1.5);
    realEtaLow->GetXaxis()->SetTitle("#eta");

    spikeEtaMid = fs->make<TH1D>("Spike Eta 10-15 GeV","Spike Eta 10-15 GeV",60,-1.5,1.5);
    spikeEtaMid->GetXaxis()->SetTitle("#eta");
    spikeEtaMid->SetLineColor(kRed);
    realEtaMid = fs->make<TH1D>("real Eta 10-15 GeV","Non-Spike Eta 10-15 GeV",60,-1.5,1.5);
    realEtaMid->GetXaxis()->SetTitle("#eta");

    spikeEtaHigh = fs->make<TH1D>("Spike Eta 15+ GeV","Spike Eta 15+ GeV",60,-1.5,1.5);
    spikeEtaHigh->GetXaxis()->SetTitle("#eta");
    spikeEtaHigh->SetLineColor(kRed);
    realEtaHigh = fs->make<TH1D>("real Eta 15+ GeV","Non-Spike Eta 15+ GeV",60,-1.5,1.5);
    realEtaHigh->GetXaxis()->SetTitle("#eta");

    spikePhiLow = fs->make<TH1D>("Spike Phi 3-10 GeV","Spike Phi 3-10 GeV",60,-3.15,3.15);
    spikePhiLow->GetXaxis()->SetTitle("#phi");
    spikePhiLow->SetLineColor(kRed);
    realPhiLow = fs->make<TH1D>("real Phi 3-10 GeV","Non-Spike Phi 3-10 GeV",60,-3.15,3.15);
    realPhiLow->GetXaxis()->SetTitle("#phi");

    spikePhiMid = fs->make<TH1D>("Spike Phi 10-15 GeV","Spike Phi 10-15 GeV",60,-3.15,3.15);
    spikePhiMid->GetXaxis()->SetTitle("#phi");
    spikePhiMid->SetLineColor(kRed);
    realPhiMid = fs->make<TH1D>("real Phi 10-15 GeV","Non-Spike Phi 10-15 GeV",60,-3.15,3.15);
    realPhiMid->GetXaxis()->SetTitle("#phi");

    spikePhiHigh = fs->make<TH1D>("Spike Phi 15+ GeV","Spike Phi 15+ GeV",60,-3.15,3.15);
    spikePhiHigh->GetXaxis()->SetTitle("#phi");
    spikePhiHigh->SetLineColor(kRed);
    realPhiHigh = fs->make<TH1D>("real Phi 15+ GeV","Non-Spike Phi 15+ GeV",60,-3.15,3.15);
    realPhiHigh->GetXaxis()->SetTitle("#phi");

    spikeCentLow = fs->make<TH1D>("Spike Cent 3-10 GeV","Spike Cent 3-10 GeV",40,0,40);
    spikeCentLow->GetXaxis()->SetTitle("Centrality Bin");
    spikeCentLow->SetLineColor(kRed);
    realCentLow = fs->make<TH1D>("real Cent 3-10 GeV","Non-Spike Cent 3-10 GeV",40,0,40);
    realCentLow->GetXaxis()->SetTitle("Centrality Bin");

    spikeCentMid = fs->make<TH1D>("Spike Cent 10-15 GeV","Spike Cent 10-15 GeV",40,0,40);
    spikeCentMid->GetXaxis()->SetTitle("Centrality Bin");
    spikeCentMid->SetLineColor(kRed);
    realCentMid = fs->make<TH1D>("real Cent 10-15 GeV","Non-Spike Cent 10-15 GeV",40,0,40);
    realCentMid->GetXaxis()->SetTitle("Centrality Bin");

    spikeCentHigh = fs->make<TH1D>("Spike Cent 15+ GeV","Spike Cent 15+ GeV",40,0,40);
    spikeCentHigh->GetXaxis()->SetTitle("Centrality Bin");
    spikeCentHigh->SetLineColor(kRed);
    realCentHigh = fs->make<TH1D>("real Cent 15+ GeV","Non-Spike Cent 15+ GeV",40,0,40);
    realCentHigh->GetXaxis()->SetTitle("Centrality Bin");

    spikeMultLow = fs->make<TH1D>("Spike Mult 3-10 GeV","Spike Mult 3-10 GeV",100,0,160000);
    spikeMultLow->GetXaxis()->SetTitle("#sum E_{HF hits}");
    spikeMultLow->SetLineColor(kRed);
    realMultLow = fs->make<TH1D>("real Mult 3-10 GeV","Non-Spike Mult 3-10 GeV",100,0,160000);
    realMultLow->GetXaxis()->SetTitle("#sum E_{HF hits}");

    spikeMultMid = fs->make<TH1D>("Spike Mult 10-15 GeV","Spike Mult 10-15 GeV",100,0,160000);
    spikeMultMid->GetXaxis()->SetTitle("#sum E_{HF hits}");
    spikeMultMid->SetLineColor(kRed);
    realMultMid = fs->make<TH1D>("real Mult 10-15 GeV","Non-Spike Mult 10-15 GeV",100,0,160000);
    realMultMid->GetXaxis()->SetTitle("#sum E_{HF hits}");

    spikeMultHigh = fs->make<TH1D>("Spike Mult 15+ GeV","Spike Mult 15+ GeV",100,0,160000);
    spikeMultHigh->GetXaxis()->SetTitle("#sum E_{HF hits}");
    spikeMultHigh->SetLineColor(kRed);
    realMultHigh = fs->make<TH1D>("real Mult 15+ GeV","Non-Spike Mult 15+ GeV",100,0,160000);
    realMultHigh->GetXaxis()->SetTitle("#sum E_{HF hits}");

    NoECent = fs->make<TH1D>("#events Cent","#events Cent",40,0,40);
    NoECent->GetXaxis()->SetTitle("Centrality Bin");
    NoEMult = fs->make<TH1D>("#events Mult","#events Mult",100,0,160000);
    NoEMult->GetXaxis()->SetTitle("#sum E_{HF hits}");

    photonPtWithSpikes = fs->make<TH1D>("photon pt with spikes","Photon Pt with Spikes",100,0,100);
    photonPtWithSpikes->GetXaxis()->SetTitle("P_{t}");
    photonPtNoSpikes = fs->make<TH1D>("photon pt no spikes","Photon Pt no Spikes",100,0,100);
    photonPtNoSpikes->GetXaxis()->SetTitle("P_{t}");

    numSpikesPerEvent = fs->make<TH1D>("num spikes per event","num spikes per event",20,0,20);
    numSpikesPerEventCentral = fs->make<TH1D>("num spikes per event 10% most central","num spikes per event 10% most central",20,0,20);

    swissE1E9High = fs->make<TH2D>("Swiss vs E1E9","1-E4/E1 vs. E1/E9",120,0,1.2,120,0,1.2);
}


SpikeInspector::~SpikeInspector()
{

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called to for each event  ------------
    void
SpikeInspector::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    numEvents++;
    int numSpikes = 0;
    using namespace edm;
    if(!centrality_) centrality_ = new CentralityProvider(iSetup);

    centrality_->newEvent(iEvent,iSetup);
    const reco::Centrality *cent = centrality_->raw();

    double hf = cent->EtHFhitSum();

    int bin = 0;
    bin = centrality_->getBin();

    NoECent->Fill(bin);
    NoEMult->Fill(hf);

    Handle<EcalRecHitCollection> barrelRecHitsHandle;
    iEvent.getByLabel(ebReducedRecHitCollection_,barrelRecHitsHandle);
    const EcalRecHitCollection* ecalRecHits = 0;
    if(!barrelRecHitsHandle.isValid()) {
        LogDebug("SpikeInspector") << "Error! Can't get barrelRecHitsHandle product!" << std::endl;
    } else {
        ecalRecHits = barrelRecHitsHandle.product();
    }

    Handle<reco::SuperClusterCollection> superClusterHandle;
    iEvent.getByLabel(ebSuperClusterCollection_, superClusterHandle);
    const reco::SuperClusterCollection* superClusterCollection = 0;
    if(!superClusterHandle.isValid()) {
        LogDebug("SpikeInspector") << "Error! Can't get superClusterHandle product!" << std::endl;
    } else {
        superClusterCollection = superClusterHandle.product();
    }

    Handle<reco::PhotonCollection> photonHandle;
    iEvent.getByLabel(photonCollection_, photonHandle);
    const reco::PhotonCollection* photonCollection = 0;
    if(!photonHandle.isValid()) {
        LogDebug("SpikeInspector") << "Error! Can't get photonHandle product!" << std::endl;
    } else {
        photonCollection = photonHandle.product();
    }

    double swiss = 0;
    double e2e9 = 0;
    double e1e9 = 0;
    bool spike = 0;
    double time;
    double et;
    if(photonCollection) {
        for(reco::PhotonCollection::const_iterator it=photonCollection->begin(); it!=photonCollection->end(); it++) {
            DetId id = getMaximumRecHit(*(it->superCluster()->seed()),ecalRecHits);

            time = recHitTime(id,ecalRecHits);
            swiss = EcalSeverityLevelAlgo::swissCross(id,*ecalRecHits,0,true);
            e2e9 = EcalSeverityLevelAlgo::E2overE9(id, *ecalRecHits, 0, 0, true);
            spike = (swiss > swissCut || abs(time) > 3);

            if(it->isEB()) {
                photonPtWithSpikes->Fill(it->pt());
                if(!spike)
                    photonPtNoSpikes->Fill(it->pt());
            }
        }
    }

    if(superClusterCollection) {
        reco::SuperClusterCollection::const_iterator it;
        for(it=superClusterCollection->begin(); it!=superClusterCollection->end(); it++) {
            DetId id = getMaximumRecHit(*(it->seed()),ecalRecHits);

            time = recHitTime(id,ecalRecHits);
            swiss = EcalSeverityLevelAlgo::swissCross(id,*ecalRecHits,0,true);
            e2e9 = EcalSeverityLevelAlgo::E2overE9(id, *ecalRecHits, 0, 0, true);
            e1e9 = EcalSeverityLevelAlgo::E1OverE9(id, *ecalRecHits, 0);
            spike = (swiss > swissCut || abs(time) > 3);
            et = it->energy()/cosh(it->eta());
            if(spike && et >= en3)
                numSpikes++;
            if(et >= en1 && it->energy() < en2) {
                timingSwissLow->Fill(time,swiss);
                swissE2Low->Fill(swiss,e2e9);
                timingLow->Fill(time);
                swissLow->Fill(swiss);
                e2e9Low->Fill(e2e9);
                if(spike) {
                    spikeEtaLow->Fill(it->eta());
                    spikePhiLow->Fill(it->phi());
                    spikeCentLow->Fill(bin);
                    spikeMultLow->Fill(hf);
                }
                else {
                    realEtaLow->Fill(it->eta());
                    realPhiLow->Fill(it->phi());
                    realCentLow->Fill(bin);
                    realMultLow->Fill(hf);
                }
            }
            else if(et >= en2 && it->energy() < en3) {
                timingSwissMid->Fill(time,swiss);
                swissE2Mid->Fill(swiss,e2e9);
                timingMid->Fill(time);
                swissMid->Fill(swiss);
                e2e9Mid->Fill(e2e9);
                if(spike) {
                    spikeEtaMid->Fill(it->eta());
                    spikePhiMid->Fill(it->phi());
                    spikeCentMid->Fill(bin);
                    spikeMultMid->Fill(hf);
                }
                else {
                    realEtaMid->Fill(it->eta());
                    realPhiMid->Fill(it->phi());
                    realCentMid->Fill(bin);
                    realMultMid->Fill(hf);
                }
            }
            else if(et >= en3) {
                timingSwissHigh->Fill(time,swiss);
                swissE2High->Fill(swiss,e2e9);
                swissE1E9High->Fill(swiss,e1e9);
                timingHigh->Fill(time);
                swissHigh->Fill(swiss);
                e2e9High->Fill(e2e9);
                if(spike) {
                    spikeEtaHigh->Fill(it->eta());
                    spikePhiHigh->Fill(it->phi());
                    spikeCentHigh->Fill(bin);
                    spikeMultHigh->Fill(hf);
                }
                else {
                    realEtaHigh->Fill(it->eta());
                    realPhiHigh->Fill(it->phi());
                    realCentHigh->Fill(bin);
                    realMultHigh->Fill(hf);
                }
            }
            if(spike) {
                spikeEnergy->Fill(it->energy());
            }
            else {
                realEnergy->Fill(it->energy());
            }
        }
    }

    numSpikesPerEvent->Fill(numSpikes);
    if(bin < 4)
        numSpikesPerEventCentral->Fill(numSpikes);

#ifdef THIS_IS_AN_EVENT_EXAMPLE
    Handle<ExampleData> pIn;
    iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
    ESHandle<SetupData> pSetup;
    iSetup.get<SetupRecord>().get(pSetup);
#endif
}

//I can't use lazyTools because for some reason I crash on polui trying to load the geometry information.
//Therefore, I have to make my own getMaximum method (copied more or less from EcalClusterTools)
DetId getMaximumRecHit(const reco::BasicCluster &cluster, const EcalRecHitCollection *recHits) {
    const std::vector<std::pair<DetId, float> > &v_id = cluster.hitsAndFractions();
    float max = 0;
    DetId id(0);
    for ( size_t i = 0; i < v_id.size(); ++i ) {
        float energy = recHitEnergy( v_id[i].first, recHits ) * v_id[i].second;
        if ( energy > max ) {
            max = energy;
            id = v_id[i].first;
        }
    }
    return id;
}

//recHitEnergy method copied from EcalClusterTools
float recHitEnergy(DetId id, const EcalRecHitCollection *recHits) {
    if ( id == DetId(0) ) {
        return 0;
    } else {
        EcalRecHitCollection::const_iterator it = recHits->find( id );
        if ( it != recHits->end() ) {
            return (*it).energy();
        } else {
            //throw cms::Exception("EcalRecHitNotFound") << "The recHit corresponding to the DetId" << id.rawId() << " not found in the EcalRecHitCollection";
            // the recHit is not in the collection (hopefully zero suppressed)
            return 0;
        }
    }
    return 0;
}

float recHitTime(DetId id, const EcalRecHitCollection *recHits) {
    if ( id == DetId(0) ) {
        return 0;
    } else {
        EcalRecHitCollection::const_iterator it = recHits->find( id );
        if ( it != recHits->end() ) {
            return (*it).time();
        } else {
            //throw cms::Exception("EcalRecHitNotFound") << "The recHit corresponding to the DetId" << id.rawId() << " not found in the EcalRecHitCollection";
            // the recHit is not in the collection (hopefully zero suppressed)
            return 0;
        }
    }
    return 0;
}

// ------------ method called once each job just before starting event loop  ------------
    void 
SpikeInspector::beginJob()
{
    centrality_ = 0;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SpikeInspector::endJob() {
    spikeMultLow->Divide(NoEMult);
    spikeMultMid->Divide(NoEMult);
    spikeMultHigh->Divide(NoEMult);
    realMultLow->Divide(NoEMult);
    realMultMid->Divide(NoEMult);
    realMultHigh->Divide(NoEMult);
    spikeCentLow->Divide(NoECent);
    spikeCentMid->Divide(NoECent);
    spikeCentHigh->Divide(NoECent);
    realCentLow->Divide(NoECent);
    realCentMid->Divide(NoECent);
    realCentHigh->Divide(NoECent);
    spikeEtaLow->Scale(1./numEvents);
    spikeEtaMid->Scale(1./numEvents);
    spikeEtaHigh->Scale(1./numEvents);
    realEtaLow->Scale(1./numEvents);
    realEtaMid->Scale(1./numEvents);
    realEtaHigh->Scale(1./numEvents);
    spikePhiLow->Scale(1./numEvents);
    spikePhiMid->Scale(1./numEvents);
    spikePhiHigh->Scale(1./numEvents);
    realPhiLow->Scale(1./numEvents);
    realPhiMid->Scale(1./numEvents);
    realPhiHigh->Scale(1./numEvents);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SpikeInspector);
