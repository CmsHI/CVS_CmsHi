
#include "RecoJets/JetAlgorithms/interface/CambridgeAlgorithmWrapper.h"
#include "RecoJets/JetAlgorithms/interface/CDFMidpointAlgorithmWrapper.h"
#include "RecoJets/JetAlgorithms/interface/CMSIterativeConeAlgorithm.h"
#include "RecoJets/JetAlgorithms/interface/CMSMidpointAlgorithm.h"
#include "RecoJets/JetAlgorithms/interface/ExtKtJetAlgorithmWrapper.h"
#include "RecoJets/JetAlgorithms/interface/FastJetBaseWrapper.h"
#include "RecoJets/JetAlgorithms/interface/KtJetAlgorithmWrapper.h"
#include "RecoJets/JetAlgorithms/interface/SISConeAlgorithmWrapper.h"

#include "CmsHi/JetAnalysis/interface/BaseHiGenJetProducer.h"

namespace cms {
   template <class T>
      class HiGenJetProducer : public BaseHiGenJetProducer 
      {
	 
      public:
	 HiGenJetProducer(const edm::ParameterSet& ps) : BaseHiGenJetProducer(ps), alg_(0) { initializeAlgo(ps);}
	 virtual ~HiGenJetProducer() { if(alg_ != 0) delete alg_;}
	 virtual bool runAlgorithm (const JetReco::InputCollection& fInput, 
				    JetReco::OutputCollection* fOutput){
	       alg_->run (fInput, fOutput);
	       return true;
	    }

	 virtual void initializeAlgo(const edm::ParameterSet& ps);
	 //	    alg_ = new T(ps);
	 //	 }

	 private :
	    T* alg_;
   };
   
 typedef HiGenJetProducer<CMSIterativeConeAlgorithm> IterativeConeHiGenJetProducer;
 typedef HiGenJetProducer<CambridgeAlgorithmWrapper> CambridgeHiGenJetProducer;
 typedef HiGenJetProducer<CDFMidpointAlgorithmWrapper> CDFMidpointHiGenJetProducer;
 typedef HiGenJetProducer<CMSMidpointAlgorithm> CMSMidpointHiGenJetProducer;
 typedef HiGenJetProducer<ExtKtJetAlgorithmWrapper> ExtKtHiGenJetProducer;
 typedef HiGenJetProducer<KtJetAlgorithmWrapper> KtHiGenJetProducer;
 typedef HiGenJetProducer<SISConeAlgorithmWrapper> SISConeHiGenJetProducer;

}


