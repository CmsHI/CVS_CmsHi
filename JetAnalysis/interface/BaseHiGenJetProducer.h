#ifndef JetProducers_BaseHiGenJetProducer_h
#define JetProducers_BaseHiGenJetProducer_h

/** \class BaseHiGenJetProducer
 *
 * BaseHiGenJetProducer is a base class for JetProducers.
 * It handles generic manipulations of input and output collections
 *
 * \author Fedor Ratnikov (UMd) Aug. 22, 2006
 * $Id: BaseHiGenJetProducer.h,v 1.4 2009/06/16 12:36:11 yilmaz Exp $
 *
 ************************************************************/

#include "FWCore/Framework/interface/EDProducer.h"
#include "DataFormats/Common/interface/EDProductfwd.h"
#include "RecoJets/JetAlgorithms/interface/JetRecoTypes.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

namespace cms
{
  class BaseHiGenJetProducer : public edm::EDProducer
  {
  public:

    BaseHiGenJetProducer(const edm::ParameterSet& ps);

    /**Default destructor*/
    virtual ~BaseHiGenJetProducer();
    /**Produces the EDM products*/
    virtual void beginJob(const edm::EventSetup& c);
    virtual void produce(edm::Event& e, const edm::EventSetup& c);
    /** jet type */
    std::string jetType () const {return mJetType;}

    // abstract method to be set up in actual implementations
    /** run algorithm itself */
    virtual bool runAlgorithm (const JetReco::InputCollection& fInput, JetReco::OutputCollection* fOutput) = 0;

  private:
    edm::InputTag mSrc;
    edm::InputTag mapSrc;
    std::string mJetType;
    bool mVerbose;
    double mEtInputCut;
    double mEInputCut;
    double mJetPtMin;
    double nMax_;
    bool ignoreHydro_;
    edm::ESHandle < ParticleDataTable > mPdt;

  };
}

#endif
