#ifndef RecoJets_JetProducers_plugins_JetAlgorithmAnalyzer_h
#define RecoJets_JetProducers_plugins_JetAlgorithmAnalyzer_h

#include "RecoJets/JetProducers/plugins/VirtualJetProducer.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TNtuple.h"

class JetAlgorithmAnalyzer : public VirtualJetProducer
{

public:
  //
  // construction/destruction
  //
  explicit JetAlgorithmAnalyzer(const edm::ParameterSet& iConfig);
  virtual ~JetAlgorithmAnalyzer();

protected:

  //
  // member functions
  //

   virtual void produce( edm::Event& iEvent, const edm::EventSetup& iSetup );
  virtual void runAlgorithm( edm::Event& iEvent, const edm::EventSetup& iSetup );
  virtual void output(  edm::Event & iEvent, edm::EventSetup const& iSetup );
  template< typename T >
  void writeBkgJets( edm::Event & iEvent, edm::EventSetup const& iSetup );

   void fillNtuple(bool output, const  std::vector<fastjet::PseudoJet>& jets, int step);
   void fillTowerNtuple(const  std::vector<fastjet::PseudoJet>& jets, int step);
   void fillJetNtuple(const  std::vector<fastjet::PseudoJet>& jets, int step);
   void fillBkgNtuple(const PileUpSubtractor* subtractor, int step);

 private:

  // trackjet clustering parameters
  bool useOnlyVertexTracks_;
  bool useOnlyOnePV_;
  float dzTrVtxMax_;

  int nFill_;
   float etaMax_;
   int iev_;
  bool avoidNegative_;

   bool doAnalysis_;

   TNtuple* ntTowers;
   TNtuple* ntJets;
   TNtuple* ntPU;
   TNtuple* ntRandom;

   const CaloGeometry *geo;
   edm::Service<TFileService> f;
};


#endif
////////////////////////////////////////////////////////////////////////////////
//
// JetAlgorithmAnalyzer
// ------------------
//
//            04/21/2009 Philipp Schieferdecker <philipp.schieferdecker@cern.ch>
////////////////////////////////////////////////////////////////////////////////

//#include "RecoJets/JetProducers/plugins/JetAlgorithmAnalyzer.h"
//#include "JetAlgorithmAnalyzer.h"

#include "RecoJets/JetProducers/interface/JetSpecific.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/CodedException.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/BasicJetCollection.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "fastjet/SISConePlugin.hh"
#include "fastjet/CMSIterativeConePlugin.hh"
#include "fastjet/ATLASConePlugin.hh"
#include "fastjet/CDFMidPointPlugin.hh"

#include "CLHEP/Random/RandomEngine.h"

#include <iostream>
#include <memory>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;
using namespace edm;

static const double pi = 3.14159265358979;

CLHEP::HepRandomEngine* randomEngine;


////////////////////////////////////////////////////////////////////////////////
// construction / destruction
////////////////////////////////////////////////////////////////////////////////

//______________________________________________________________________________
JetAlgorithmAnalyzer::JetAlgorithmAnalyzer(const edm::ParameterSet& iConfig)
   : VirtualJetProducer( iConfig ),
     nFill_(5),
     etaMax_(3),
     iev_(0),
     geo(0)
{
   edm::Service<RandomNumberGenerator> rng;
   randomEngine = &(rng->getEngine());

   doAnalysis_  = iConfig.getUntrackedParameter<bool>("doAnalysis",true);
   avoidNegative_  = iConfig.getParameter<bool>("avoidNegative");
  
  if ( iConfig.exists("UseOnlyVertexTracks") )
    useOnlyVertexTracks_ = iConfig.getParameter<bool>("UseOnlyVertexTracks");
  else 
    useOnlyVertexTracks_ = false;
  
  if ( iConfig.exists("UseOnlyOnePV") )
    useOnlyOnePV_        = iConfig.getParameter<bool>("UseOnlyOnePV");
  else
    useOnlyOnePV_ = false;

  if ( iConfig.exists("DrTrVtxMax") )
    dzTrVtxMax_          = iConfig.getParameter<double>("DzTrVtxMax");
  else
    dzTrVtxMax_ = false;

  produces<std::vector<bool> >("directions");

  if(doAnalysis_){
     ntTowers = f->make<TNtuple>("ntTowers","Algorithm Analysis Towers","eta:phi:et:step:event");
     ntJets = f->make<TNtuple>("ntJets","Algorithm Analysis Jets","eta:phi:et:step:event");
     ntPU = f->make<TNtuple>("ntPU","Algorithm Analysis Background","eta:mean:sigma:step:event");
     ntRandom = f->make<TNtuple>("ntRandom","Algorithm Analysis Background","eta:phi:et:pu:event");
  }

}


//______________________________________________________________________________
JetAlgorithmAnalyzer::~JetAlgorithmAnalyzer()
{
} 


void JetAlgorithmAnalyzer::fillNtuple(bool output, const  std::vector<fastjet::PseudoJet>& jets, int step){
   if(!doAnalysis_) return;

   TNtuple* nt;
   if(output) nt = ntJets;
   else nt = ntTowers;

   for(unsigned int i = 0; i < jets.size(); ++i){
      const fastjet::PseudoJet& jet = jets[i];
      nt->Fill(jet.eta(),jet.phi(),jet.perp(),step,iev_);
   }

}


void JetAlgorithmAnalyzer::fillTowerNtuple(const  std::vector<fastjet::PseudoJet>& jets, int step){
   fillNtuple(0,jets,step);
}
 
void JetAlgorithmAnalyzer::fillJetNtuple(const  std::vector<fastjet::PseudoJet>& jets, int step){
   fillNtuple(1,jets,step);
}

void JetAlgorithmAnalyzer::fillBkgNtuple(const PileUpSubtractor* subtractor, int step){
   if(!doAnalysis_) return;
   
   CaloTowerCollection col;

   for(int ieta = 1; ieta < 29; ++ieta){

      CaloTowerDetId id(ieta,0);
      const GlobalPoint& hitpoint = geo->getPosition(id);
      double eta = hitpoint.eta();
      
      //   CaloTowerDetId id(int ieta = 0, int iphi = 0);
      math::PtEtaPhiMLorentzVector p4(1,eta,0,0);
      GlobalPoint pos(1,1,1);
      CaloTower c(id,1.,1.,1.,1,1, p4, pos,pos);      
      col.push_back(c);
      reco::CandidatePtr ptr(&col,col.size() - 1);
      double mean = subtractor->getMeanAtTower(ptr);  
      double sigma = subtractor->getMeanAtTower(ptr);
      
      ntPU->Fill(eta,mean,sigma,step,iev_);
   }
}

void JetAlgorithmAnalyzer::produce(edm::Event& iEvent,const edm::EventSetup& iSetup)
{
   if(!geo){
      edm::ESHandle<CaloGeometry> pGeo;
      iSetup.get<CaloGeometryRecord>().get(pGeo);
      geo = pGeo.product();
   }

   LogDebug("VirtualJetProducer") << "Entered produce\n";
   //determine signal vertex
   vertex_=reco::Jet::Point(0,0,0);
   if (makeCaloJet(jetTypeE)&&doPVCorrection_) {
      LogDebug("VirtualJetProducer") << "Adding PV info\n";
      edm::Handle<reco::VertexCollection> pvCollection;
      iEvent.getByLabel(srcPVs_,pvCollection);
      if (pvCollection->size()>0) vertex_=pvCollection->begin()->position();
   }

   // For Pileup subtraction using offset correction:
   // set up geometry map
   if ( doPUOffsetCorr_ ) {
      subtractor_->setupGeometryMap(iEvent, iSetup);
   }

   // clear data
   LogDebug("VirtualJetProducer") << "Clear data\n";
   fjInputs_.clear();
   fjJets_.clear();
   inputs_.clear();  
  
   // get inputs and convert them to the fastjet format (fastjet::PeudoJet)
   edm::Handle<reco::CandidateView> inputsHandle;
   iEvent.getByLabel(src_,inputsHandle);
   for (size_t i = 0; i < inputsHandle->size(); ++i) {
      inputs_.push_back(inputsHandle->ptrAt(i));
   }
   LogDebug("VirtualJetProducer") << "Got inputs\n";
  
   // Convert candidates to fastjet::PseudoJets.
   // Also correct to Primary Vertex. Will modify fjInputs_
   // and use inputs_
   fjInputs_.reserve(inputs_.size());
   inputTowers();
   LogDebug("VirtualJetProducer") << "Inputted towers\n";

   fillTowerNtuple(fjInputs_,0);
   fillBkgNtuple(subtractor_.get(),0);

   // For Pileup subtraction using offset correction:
   // Subtract pedestal. 
   if ( doPUOffsetCorr_ ) {
      subtractor_->calculatePedestal(fjInputs_); 

      fillTowerNtuple(fjInputs_,1);
      fillBkgNtuple(subtractor_.get(),1);

      subtractor_->subtractPedestal(fjInputs_);    

      fillTowerNtuple(fjInputs_,2);
      fillBkgNtuple(subtractor_.get(),2);

      LogDebug("VirtualJetProducer") << "Subtracted pedestal\n";
   }

   // Run algorithm. Will modify fjJets_ and allocate fjClusterSeq_. 
   // This will use fjInputs_
   runAlgorithm( iEvent, iSetup );

   fillTowerNtuple(fjInputs_,3);
   fillBkgNtuple(subtractor_.get(),3);
   fillJetNtuple(fjJets_,3);

   if ( doPUOffsetCorr_ ) {
      subtractor_->setAlgorithm(fjClusterSeq_);
   }

   LogDebug("VirtualJetProducer") << "Ran algorithm\n";

   // For Pileup subtraction using offset correction:
   // Now we find jets and need to recalculate their energy,
   // mark towers participated in jet,
   // remove occupied towers from the list and recalculate mean and sigma
   // put the initial towers collection to the jet,   
   // and subtract from initial towers in jet recalculated mean and sigma of towers 
   if ( doPUOffsetCorr_ ) {
      vector<fastjet::PseudoJet> orphanInput;
      subtractor_->calculateOrphanInput(orphanInput);
      fillTowerNtuple(orphanInput,4);
      fillBkgNtuple(subtractor_.get(),4);
      fillJetNtuple(fjJets_,4);

      subtractor_->calculatePedestal(orphanInput);
      fillTowerNtuple(orphanInput,5);
      fillBkgNtuple(subtractor_.get(),5);
      fillJetNtuple(fjJets_,5);

      subtractor_->offsetCorrectJets();
      fillTowerNtuple(orphanInput,6);
      fillBkgNtuple(subtractor_.get(),6);
      fillJetNtuple(fjJets_,6);

   }
  
   // Write the output jets.
   // This will (by default) call the member function template
   // "writeJets", but can be overridden. 
   // this will use inputs_
   output( iEvent, iSetup );
   fillBkgNtuple(subtractor_.get(),7);
   fillJetNtuple(fjJets_,7);

   LogDebug("VirtualJetProducer") << "Wrote jets\n";

   ++iev_;
  
   return;
}

void JetAlgorithmAnalyzer::output(edm::Event & iEvent, edm::EventSetup const& iSetup)
{
   // Write jets and constitutents. Will use fjJets_, inputs_                          
   // and fjClusterSeq_                                                                
   switch( jetTypeE ) {
   case JetType::CaloJet :
      writeBkgJets<reco::CaloJet>( iEvent, iSetup);
      break;
   case JetType::PFJet :
      writeBkgJets<reco::PFJet>( iEvent, iSetup);
      break;
   case JetType::GenJet :
      writeBkgJets<reco::GenJet>( iEvent, iSetup);
      break;
   case JetType::TrackJet :
      writeBkgJets<reco::TrackJet>( iEvent, iSetup);
      break;
   case JetType::BasicJet :
      writeBkgJets<reco::BasicJet>( iEvent, iSetup);
      break;
   default:
      edm::LogError("InvalidInput") << " invalid jet type in VirtualJetProducer\n";
      break;
   };

}

template< typename T >
void JetAlgorithmAnalyzer::writeBkgJets( edm::Event & iEvent, edm::EventSetup const& iSetup )
{
   // produce output jet collection

   using namespace reco;

   std::vector<fastjet::PseudoJet> fjFakeJets_;
   std::vector<std::vector<reco::CandidatePtr> > constituents_;
   vector<double> phiRandom;
   vector<double> etaRandom;
   vector<double> et;
   vector<double> pileUp;
   std::auto_ptr<std::vector<bool> > directions(new std::vector<bool>());
   directions->reserve(nFill_);

   phiRandom.reserve(nFill_);
   etaRandom.reserve(nFill_);
   et.reserve(nFill_);
   pileUp.reserve(nFill_);

   fjFakeJets_.reserve(nFill_);
   constituents_.reserve(nFill_);

   constituents_.reserve(nFill_);
   for(int ijet = 0; ijet < nFill_; ++ijet){
      vector<reco::CandidatePtr> vec;
      constituents_.push_back(vec);
      directions->push_back(true);
   }

   for(int ijet = 0; ijet < nFill_; ++ijet){
      phiRandom[ijet] = 2*pi*randomEngine->flat() - pi;
      etaRandom[ijet] = 2*etaMax_*randomEngine->flat() - etaMax_;
      et[ijet] = 0;
      pileUp[ijet] = 0;
   }

   for (vector<fastjet::PseudoJet>::const_iterator input_object = fjInputs_.begin (),
	   fjInputsEnd = fjInputs_.end();
	input_object != fjInputsEnd; ++input_object) {

      const reco::CandidatePtr & tower=inputs_[input_object->user_index()];
      for(int ir = 0; ir < nFill_; ++ir){
	 if(reco::deltaR(tower->eta(),tower->phi(),etaRandom[ir],phiRandom[ir]) > rParam_) continue;

	 constituents_[ir].push_back(tower);

	 double towet = tower->et();
	 double putow = subtractor_->getPileUpAtTower(tower);
	 double etadd = towet - putow; 
	 if(avoidNegative_ && etadd < 0.) etadd = 0;
	 et[ir] += etadd;
	 pileUp[ir] += towet - etadd;
      }
   }
   cout<<"Start filling jets"<<endl;

   for(int ir = 0; ir < nFill_; ++ir){

      if(doAnalysis_) ntRandom->Fill(etaRandom[ir],phiRandom[ir],et[ir],pileUp[ir],iev_);

      if(et[ir] < 0){
	 cout<<"Flipping vector"<<endl;
	 (*directions)[ir] = false;
	 et[ir] = -et[ir];
      }else{
         cout<<"Keep vector same"<<endl;
         (*directions)[ir] = true;
      }
      cout<<"Lorentz"<<endl;

      math::PtEtaPhiMLorentzVector p(et[ir],etaRandom[ir],phiRandom[ir],0);
      fastjet::PseudoJet jet(p.px(),p.py(),p.pz(),p.energy());
      fjFakeJets_.push_back(jet);
   }

   std::auto_ptr<std::vector<T> > jets(new std::vector<T>() );
   jets->reserve(fjFakeJets_.size());
      
   for (unsigned int ijet=0;ijet<fjFakeJets_.size();++ijet) {
      // allocate this jet
      T jet;
      // get the fastjet jet
      const fastjet::PseudoJet& fjJet = fjFakeJets_[ijet];

      // convert them to CandidatePtr vector
      std::vector<CandidatePtr> constituents =
	 constituents_[ijet];

      writeSpecific(jet,
		    Particle::LorentzVector(fjJet.px(),
					    fjJet.py(),
					    fjJet.pz(),
					    fjJet.E()),
		    vertex_,
		    constituents, iSetup);
      
      // calcuate the jet area
      double jetArea=0.0;
      jet.setJetArea (jetArea);
      if(doPUOffsetCorr_){
	 jet.setPileup(pileUp[ijet]);
      }else{
	 jet.setPileup (0.0);
      }

      // add to the list
      jets->push_back(jet);
   }
  
   // put the jets in the collection
   iEvent.put(jets);
   iEvent.put(directions,"directions");
   // calculate rho (median pT per unit area, for PU&UE subtraction down the line
   std::auto_ptr<double> rho(new double(0.0));
   std::auto_ptr<double> sigma(new double(0.0));

   if (doRhoFastjet_) {
      fastjet::ClusterSequenceArea const * clusterSequenceWithArea =
	 dynamic_cast<fastjet::ClusterSequenceArea const *> ( &*fjClusterSeq_ );
      double mean_area = 0;
      clusterSequenceWithArea->get_median_rho_and_sigma(*fjRangeDef_,false,*rho,*sigma,mean_area);
      iEvent.put(rho,"rho");
      iEvent.put(sigma,"sigma");
   }
}

void JetAlgorithmAnalyzer::runAlgorithm( edm::Event & iEvent, edm::EventSetup const& iSetup)
{
   if ( !doAreaFastjet_ && !doRhoFastjet_) {
      fjClusterSeq_ = ClusterSequencePtr( new fastjet::ClusterSequence( fjInputs_, *fjJetDefinition_ ) );
   } else {
      fjClusterSeq_ = ClusterSequencePtr( new fastjet::ClusterSequenceArea( fjInputs_, *fjJetDefinition_ , *fjActiveArea_ ) );
   }
   fjJets_ = fastjet::sorted_by_pt(fjClusterSeq_->inclusive_jets(jetPtMin_));

}





////////////////////////////////////////////////////////////////////////////////
// define as cmssw plugin
////////////////////////////////////////////////////////////////////////////////

DEFINE_FWK_MODULE(JetAlgorithmAnalyzer);

