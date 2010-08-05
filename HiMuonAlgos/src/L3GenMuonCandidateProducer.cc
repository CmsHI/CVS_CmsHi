// -*- C++ -*-
//
// Package:    L3GenMuonCandidateProducer
// Class:      L3GenMuonCandidateProducer
// 
/**\class L3GenMuonCandidateProducer L3GenMuonCandidateProducer.cc CmsHi/HiMuonAlgos/src/L3GenMuonCandidateProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Dong Ho Moon,587 R-029,+41227670285,
//         Created:  Thu Aug  5 15:56:49 CEST 2010
// $Id$
//
// L3MuonCandidateProducer with Gen Info, instead of L3Muon object


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidateFwd.h"

#include <string>

using namespace edm;
using namespace std;
using namespace reco;


//
// class declaration
//

class L3GenMuonCandidateProducer : public edm::EDProducer {
   public:
      explicit L3GenMuonCandidateProducer(const edm::ParameterSet&);
      ~L3GenMuonCandidateProducer();

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      edm::InputTag triggerResults_;
      string HLT_Path_;
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
L3GenMuonCandidateProducer::L3GenMuonCandidateProducer(const edm::ParameterSet& iConfig)
{
   //now do what ever other initialization is needed
   triggerResults_ = iConfig.getParameter<edm::InputTag>("TriggerResults");
   HLT_Path_ = iConfig.getParameter<string>("HLT_Path");
   produces<RecoChargedCandidateCollection>();
   //cout<<"L3 Gen Muon Candidate producer "<<endl;
}


L3GenMuonCandidateProducer::~L3GenMuonCandidateProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
L3GenMuonCandidateProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    const string metname = "RecoHI|HiMuonAlgos|L3GenMuonCandidate";

    Handle<GenParticleCollection> mctruth;
    iEvent.getByLabel("hiGenParticles", mctruth);

    Handle<TriggerResults> hltresults;
    iEvent.getByLabel(triggerResults_,hltresults);
    //iEvent.getByLabel("TriggerResults",hltresults);

    auto_ptr<RecoChargedCandidateCollection> candidates( new RecoChargedCandidateCollection());

    std::string PathName;
    //PathName = "HLT_HIDoubleMu";
    //PathName = "L1_DoubleMuOpen";
    PathName = HLT_Path_;

    if (hltresults.isValid()) {
        int ntrigs = hltresults->size();
        if (ntrigs==0){std::cout << "%HLTInfo -- No trigger name given in TriggerResults of the input " << std::endl;}
        //cout<<"ntrigs : "<<ntrigs<<endl;
        edm::TriggerNames const& triggerNames_ = iEvent.triggerNames(*hltresults);
        for (int itrig = 0; itrig != ntrigs; ++itrig){
            string trigName=triggerNames_.triggerName(itrig);
            //cout<<"Trigger Name : "<<trigName<<endl;
            bool accept = hltresults->accept(itrig);

            if(accept == 1 && trigName == PathName){
                //std::cout<<"%%%%% HLT_HIDoubleMu Fired %%%%%"<<std::endl;
                //std::cout<<"%%%%% L3 Muons filling up with Gen Muons %%%%%"<<std::endl;
                if (mctruth.isValid()){
                    for(size_t i = 0; i < mctruth->size(); ++ i) {
                        const Candidate & p = (*mctruth)[i];
                        int id = p.pdgId();
                        if(abs(id) == 13) {
                            Particle::Charge q = p.charge();
                            Particle::LorentzVector p4(p.px(), p.py(), p.pz(), p.p());
                            Particle::Point vtx(p.vx(), p.vy(), p.vz());
                            int pid = 13;
                            if(abs(q)==1) pid = q <0 ? 13 : -13;
                            else LogWarning(metname) << "L3GenMuonCandidate has charge : "<<q;
                            RecoChargedCandidate cand(q, p4, vtx, pid);

                            //cand.setTrack(p);
                            candidates->push_back(cand);

                        }
                    }
                }
            }
        } 
    }
    iEvent.put(candidates);

}

// ------------ method called once each job just before starting event loop  ------------
void 
L3GenMuonCandidateProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
L3GenMuonCandidateProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(L3GenMuonCandidateProducer);
