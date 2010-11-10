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
// $Id: SpikeInspector.cc,v 1.2 2010/11/06 13:56:11 troxlo Exp $
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

        double swissCut_;

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
    //now do what ever initialization is needed
    ebSuperClusterCollection_        = iConfig.getUntrackedParameter<edm::InputTag>("ebSuperClusterCollection",edm::InputTag("correctedIslandBarrelSuperClusters"));
    ebReducedRecHitCollection_       = iConfig.getUntrackedParameter<edm::InputTag>("ebReducedRecHitCollection");
    eeReducedRecHitCollection_       = iConfig.getUntrackedParameter<edm::InputTag>("eeReducedRecHitCollection");
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

    if(superClusterCollection) {
        reco::SuperClusterCollection::const_iterator it;
        double swiss = 0;
        double e2e9 = 0;
        for(it=superClusterCollection->begin(); it!=superClusterCollection->end(); it++) {
            DetId id = getMaximumRecHit(*(it->seed()),ecalRecHits);

            double time = recHitTime(id,ecalRecHits);
            swiss = EcalSeverityLevelAlgo::swissCross(id,*ecalRecHits,0,true);
            e2e9 = EcalSeverityLevelAlgo::E2overE9(id, *ecalRecHits, 0, 0, true);
            double theEt = it->energy() / cosh(it->eta() ) ;
	    if((theEt >= en1) && (theEt < en2)) {
                timingSwissLow->Fill(time,swiss);
                swissE2Low->Fill(swiss,e2e9);
                timingLow->Fill(time);
                swissLow->Fill(swiss);
                e2e9Low->Fill(e2e9);
            }
            else if ( (theEt >= en2) && (theEt < en3)) {
                timingSwissMid->Fill(time,swiss);
                swissE2Mid->Fill(swiss,e2e9);
                timingMid->Fill(time);
                swissMid->Fill(swiss);
                e2e9Mid->Fill(e2e9);
            }
            else if( theEt >= en3) {
                timingSwissHigh->Fill(time,swiss);
                swissE2High->Fill(swiss,e2e9);
                timingHigh->Fill(time);
                swissHigh->Fill(swiss);
                e2e9High->Fill(e2e9);
            }
        }
    }

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
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SpikeInspector::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(SpikeInspector);
