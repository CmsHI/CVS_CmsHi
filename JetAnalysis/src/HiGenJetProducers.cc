//Hello

#include "CmsHi/JetAnalysis/interface/HiGenJetProducers.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"


using namespace cms;

/*
template <>
void HiGenJetProducer<>::initializeAlgo(const edm::ParameterSet& ps){
   alg_ = new (ps);
}
*/

template <>
void HiGenJetProducer<CMSIterativeConeAlgorithm>::initializeAlgo(const edm::ParameterSet& ps){
   alg_ = new CMSIterativeConeAlgorithm(ps.getParameter<double>("seedThreshold"),
					ps.getParameter<double>("coneRadius"));
}

template <>
void HiGenJetProducer<CambridgeAlgorithmWrapper>::initializeAlgo(const edm::ParameterSet& ps){
   alg_ = new CambridgeAlgorithmWrapper(ps);
}


template <>
void HiGenJetProducer<CDFMidpointAlgorithmWrapper>::initializeAlgo(const edm::ParameterSet& ps){
   alg_ = new CDFMidpointAlgorithmWrapper(ps);
}


template <>
void HiGenJetProducer<CMSMidpointAlgorithm>::initializeAlgo(const edm::ParameterSet& conf){
   alg_ = new CMSMidpointAlgorithm(conf.getParameter<double>("seedThreshold"),
				   conf.getParameter<double>("coneRadius"),
				   conf.getParameter<double>("coneAreaFraction"),
				   conf.getParameter<int>("maxPairSize"),
				   conf.getParameter<int>("maxIterations"),
				   conf.getParameter<double>("overlapThreshold"),
				   conf.getUntrackedParameter<int>("debugLevel",0));
}


template <>
void HiGenJetProducer<ExtKtJetAlgorithmWrapper>::initializeAlgo(const edm::ParameterSet& ps){
   alg_ = new ExtKtJetAlgorithmWrapper(ps);
}


template <>
void HiGenJetProducer<KtJetAlgorithmWrapper>::initializeAlgo(const edm::ParameterSet& ps){
   alg_ = new KtJetAlgorithmWrapper(ps);
}

template <>
void HiGenJetProducer<SISConeAlgorithmWrapper>::initializeAlgo(const edm::ParameterSet& ps){
   alg_ = new SISConeAlgorithmWrapper(ps);
}

using cms::IterativeConeHiGenJetProducer;
using cms::CambridgeHiGenJetProducer;
using cms::CDFMidpointHiGenJetProducer;
using cms::CMSMidpointHiGenJetProducer;
using cms::ExtKtHiGenJetProducer;
using cms::KtHiGenJetProducer;
using cms::SISConeHiGenJetProducer;

DEFINE_ANOTHER_FWK_MODULE(IterativeConeHiGenJetProducer);
DEFINE_ANOTHER_FWK_MODULE(CambridgeHiGenJetProducer);
DEFINE_ANOTHER_FWK_MODULE(CDFMidpointHiGenJetProducer);
DEFINE_ANOTHER_FWK_MODULE(CMSMidpointHiGenJetProducer);
DEFINE_ANOTHER_FWK_MODULE(ExtKtHiGenJetProducer);
DEFINE_ANOTHER_FWK_MODULE(KtHiGenJetProducer);
DEFINE_ANOTHER_FWK_MODULE(SISConeHiGenJetProducer);




