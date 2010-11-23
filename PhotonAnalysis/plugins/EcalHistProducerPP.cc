// -*- C++ -*-
//
// Package:    EcalHistProducerPP
// Class:      EcalHistProducerPP
// 
/**\class EcalHistProducerPP EcalHistProducerPP.cc CmsHi/EcalHistProducerPP/src/EcalHistProducerPP.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
 */
//
// Original Author:  Yong Kim,32 4-A08,+41227673039,
//         Created:  Fri Oct 29 12:18:14 CEST 2010
// $Id: EcalHistProducerPP.cc,v 1.15 2010/11/23 16:36:42 kimy Exp $
//
//

#define cBins 10
#define cStep 4

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "CondFormats/DataRecord/interface/EcalChannelStatusRcd.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "CondFormats/EcalObjects/interface/EcalChannelStatus.h"

#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "RecoCaloTools/MetaCollections/interface/CaloRecHitMetaCollectionV.h"
#include "RecoCaloTools/MetaCollections/interface/CaloRecHitMetaCollections.h"
#include <Math/VectorUtil.h>
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"

#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityProvider.h"

#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"


//
// class declaration
//

class EcalHistProducerPP : public edm::EDAnalyzer {
    public:
        explicit EcalHistProducerPP(const edm::ParameterSet&);
        ~EcalHistProducerPP();


    private:
        virtual void beginJob() ;
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob() ;

        // ----------member data ---------------------------

        edm::Service<TFileService> fs;

        edm::InputTag photonSrc_;
        edm::InputTag ebReducedRecHitCollection_;
        edm::InputTag eeReducedRecHitCollection_;

        edm::InputTag basicClusterBarrel_;
        edm::InputTag basicClusterEndcap_;
        int centSource_;
        bool RHCent_;
        bool SCCent_;
        bool BCCent_;
        bool doSpikeClean_;
        bool RHetaCent_;
        bool RHphiCent_;
        bool SCetaCent_;
        bool SCphiCent_;
        bool BCetaCent_;
        bool BCphiCent_;

        TH1D*  NoE ;
        TH1D*  rhEE ;
        TH1D*  rhEB ;
        TH1D   *NoEcent[cBins];
        TH1D   *rhEEcent[cBins], *rhEBcent[cBins];
        TH1D   *rhEtaCent[cBins], *rhPhiCent[cBins];


        edm::InputTag superClusterBarrel_;   
        edm::InputTag superClusterEndcap_;

        TTree* theTree;
        TTree* bcTree;

        int nPho, nBC, nRH, nSC;
        int nBCcent[cBins];
        int nSCcent[cBins];
        float energy[5000];
        float energyCent[cBins][5000];
        float et[5000];
        float etCent[cBins][5000];
        float eta[5000];
        float etaCent[cBins][5000];
        float phi[5000];
        float phiCent[cBins][5000];
        float SCenergy[1000];    
        float SCenergyCent[cBins][1000];
        float SCet[1000];    
        float SCetCent[cBins][1000];    
        float SCeta[1000];   
        float SCetaCent[cBins][1000];   
        float SCphi[1000];
        float SCphiCent[cBins][1000];
   int nBCIsc;
   float eSCIsc, etaSCIsc, phiSCIsc;
   float rawESCIsc, rawEtSCIsc;
   float energyIsc[5000];
   float etIsc[5000];
   float etaIsc[5000];
   float phiIsc[5000];
   
   double hf;
   double eb;
   double multPixel;
   double nPixelTracks;
   
   bool doSpikeRemoval_;
   double timeCut_;
   double swissCut_;
   int bin;   
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
EcalHistProducerPP::EcalHistProducerPP(const edm::ParameterSet& iConfig)

{
    //now do what ever initialization is needed
    photonSrc_                       = iConfig.getParameter<edm::InputTag>("photonProducer"); // photons                                 
    ebReducedRecHitCollection_       = iConfig.getParameter<edm::InputTag>("ebReducedRecHitCollection"); //,"reducedEcalRecHitsEB");            
    eeReducedRecHitCollection_       = iConfig.getParameter<edm::InputTag>("eeReducedRecHitCollection"); //,"reducedEcalRecHitsEE");        
    basicClusterBarrel_              = iConfig.getParameter<edm::InputTag>("basicClusterBarrel");
    basicClusterEndcap_              = iConfig.getParameter<edm::InputTag>("basicClusterEndcap");

    doSpikeClean_                    = iConfig.getUntrackedParameter<bool>("doSpikeClean",true);
    swissCut_                        = iConfig.getUntrackedParameter<double>("swissCut",0.95);
    timeCut_                         = iConfig.getUntrackedParameter<double>("timeCut",4.0);

    superClusterBarrel_                       = iConfig.getParameter<edm::InputTag>("superClusterBarrel"); // superclusters      
    superClusterEndcap_                       = iConfig.getParameter<edm::InputTag>("superClusterEndcap"); // superclusters
    
    RHCent_                         = iConfig.getUntrackedParameter<bool>("RHCent",true);
    BCCent_                         = iConfig.getUntrackedParameter<bool>("BCCent",true);
    SCCent_                         = iConfig.getUntrackedParameter<bool>("SCCent",true);

    RHetaCent_                         = iConfig.getUntrackedParameter<bool>("RHetaCent",true);
    BCetaCent_                         = iConfig.getUntrackedParameter<bool>("BCetaCent",true);
    SCetaCent_                         = iConfig.getUntrackedParameter<bool>("SCetaCent",true);

    RHphiCent_                         = iConfig.getUntrackedParameter<bool>("RHphiCent",true);
    BCphiCent_                         = iConfig.getUntrackedParameter<bool>("BCphiCent",true);
    SCphiCent_                         = iConfig.getUntrackedParameter<bool>("SCphiCent",true);
    
}


EcalHistProducerPP::~EcalHistProducerPP()
{

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
    void
EcalHistProducerPP::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;


    bin = 0;

    //grab the photon collection                                                                                                                        
    NoE->Fill(0);
    NoEcent[bin/cStep]->Fill(0);

    //grab rechits                                                                               
    edm::Handle<EcalRecHitCollection> EBReducedRecHits;
    iEvent.getByLabel(ebReducedRecHitCollection_, EBReducedRecHits);
    const EcalRecHitCollection* rechitsCollectionBarrel = EBReducedRecHits.product();
    edm::Handle<EcalRecHitCollection> EEReducedRecHits;
    iEvent.getByLabel(eeReducedRecHitCollection_, EEReducedRecHits);
    const EcalRecHitCollection* rechitsCollectionEndcap = EEReducedRecHits.product();
    //lazy tool                                                                                                                     
    EcalClusterLazyTools lazyTool(iEvent, iSetup, ebReducedRecHitCollection_, eeReducedRecHitCollection_ );

    //get the rechit geometry
    edm::ESHandle<CaloGeometry> theCaloGeom;
    iSetup.get<CaloGeometryRecord>().get(theCaloGeom);
    const CaloGeometry* caloGeom = theCaloGeom.product();

    //Barrel 
    EcalRecHitCollection::const_iterator rh;
    for (rh = (*rechitsCollectionBarrel).begin(); rh!= (*rechitsCollectionBarrel).end(); rh++){
       DetId id = rh->id();
       double swissCrx = EcalSeverityLevelAlgo::swissCross(id, *rechitsCollectionBarrel, 0.,true);
       double time     = rh->time();
       if ( (doSpikeClean_==true) && (rh->energy()>3) && ((fabs(time) > timeCut_)||(swissCrx > swissCut_)) )  
	  continue;  // This is a spike
       const GlobalPoint & position = caloGeom->getPosition(rh->id());
       double tempEt = rh->energy()/cosh(position.eta()) ;
       rhEB->Fill(tempEt);
       if(RHCent_) {
           rhEBcent[bin/cStep]->Fill(tempEt);
           if(RHetaCent_)
               rhEtaCent[bin/cStep]->Fill(position.eta(),tempEt);
           if(RHphiCent_)
               rhPhiCent[bin/cStep]->Fill(position.phi(),tempEt);
       }
       
    }
    //Endcap
    for (rh = (*rechitsCollectionEndcap).begin(); rh!= (*rechitsCollectionEndcap).end(); rh++){
        const GlobalPoint & position = caloGeom->getPosition(rh->id());
        double tempEt = rh->energy()/cosh(position.eta()) ;

        rhEE->Fill(tempEt);
        if(RHCent_) {
            rhEEcent[bin/cStep]->Fill(tempEt);
            if(RHetaCent_)
                rhEtaCent[bin/cStep]->Fill(position.eta(),tempEt);
            if(RHphiCent_)
                rhPhiCent[bin/cStep]->Fill(position.phi(),tempEt);
        }

    }

    //grab basicClusters
    Handle<reco::CaloClusterCollection> basicClusterB;
    iEvent.getByLabel(basicClusterBarrel_, basicClusterB);
    Handle<reco::CaloClusterCollection> basicClusterE;
    iEvent.getByLabel(basicClusterEndcap_, basicClusterE);

    reco::CaloClusterCollection myBCs;
    for (reco::CaloClusterCollection::const_iterator bcItr = basicClusterB->begin(); bcItr != basicClusterB->end(); ++bcItr) {
        myBCs.push_back(*bcItr);
    }
    for (reco::CaloClusterCollection::const_iterator bcItr = basicClusterE->begin(); bcItr != basicClusterE->end(); ++bcItr) {
        myBCs.push_back(*bcItr);
    }

    nBC=0;
    for(int i=0; i<cBins; i++) {
        nBCcent[i] = -1;
        for(int j=0; j<5000; j++) {
            energyCent[i][j] = -1;
            etCent[i][j] = -1;
            etaCent[i][j] = -9;
            phiCent[i][j] = -9;
        }
    }
    for (reco::CaloClusterCollection::const_iterator bcItr = myBCs.begin(); bcItr != myBCs.end(); ++bcItr) {
        energy[nBC] = bcItr->energy();
        energyCent[bin/cStep][nBCcent[bin/cStep]] = bcItr->energy();
        eta[nBC]    = bcItr->eta();
        etaCent[bin/cStep][nBCcent[bin/cStep]] = bcItr->eta();
        phi[nBC]    = bcItr->phi();
        phiCent[bin/cStep][nBCcent[bin/cStep]] = bcItr->phi();
        et[nBC]     = energy[nBC]/cosh(eta[nBC]);
        etCent[bin/cStep][nBCcent[bin/cStep]] = energyCent[bin/cStep][nBCcent[bin/cStep]]/cosh(etaCent[bin/cStep][nBCcent[bin/cStep]]);

        nBC++;
        if(nBCcent[bin/cStep] < 0)
            nBCcent[bin/cStep] = 0;
        nBCcent[bin/cStep]++;
    }

    //grab superClusters     
    Handle<reco::SuperClusterCollection> superClusterB;      
    iEvent.getByLabel(superClusterBarrel_, superClusterB);   
    Handle<reco::SuperClusterCollection> superClusterE;      
    iEvent.getByLabel(superClusterEndcap_, superClusterE);   

    reco::SuperClusterCollection mySCs;      
    for (reco::SuperClusterCollection::const_iterator scItr = superClusterB->begin(); scItr != superClusterB->end(); ++scItr) {   
        mySCs.push_back(*scItr);      
    }    
    for (reco::SuperClusterCollection::const_iterator scItr = superClusterE->begin(); scItr != superClusterE->end(); ++scItr) {     
        mySCs.push_back(*scItr);      
    }    


    nSC=0;   
    for(int i=0; i<cBins; i++) {
        nSCcent[i] = -1;
        for(int j=0; j<1000; j++) {
            SCenergyCent[i][j] = -1;
            SCetCent[i][j] = -1;
            SCetaCent[i][j] = -9;
            SCphiCent[i][j] = -9;
        }
    }
    reco::SuperClusterCollection::const_iterator maxScItr ;
    float maxEt(0);
    for (reco::SuperClusterCollection::const_iterator scItr = mySCs.begin(); scItr != mySCs.end(); ++scItr) {    
       if ( maxEt < scItr->rawEnergy()/cosh(scItr->eta()))
	  {
	     maxEt = scItr->rawEnergy()/cosh(scItr->eta());
	     maxScItr = scItr;
	  }
       SCenergy[nSC] = scItr->energy();      
       SCenergyCent[bin/cStep][nSCcent[bin/cStep]] = scItr->energy();
       SCeta[nSC]    = scItr->eta();     
       SCetaCent[bin/cStep][nSCcent[bin/cStep]] = scItr->eta();
       SCphi[nSC]    = scItr->phi();     
       SCphiCent[bin/cStep][nSCcent[bin/cStep]] = scItr->phi();
       SCet[nSC]     = SCenergy[nSC]/cosh(SCeta[nSC]);   
       SCetCent[bin/cStep][nSCcent[bin/cStep]] = SCenergyCent[bin/cStep][nSCcent[bin/cStep]]/cosh(SCetaCent[bin/cStep][nSCcent[bin/cStep]]);
       
       if(nSCcent[bin/cStep] < 0)
	  nSCcent[bin/cStep] = 0;
       nSCcent[bin/cStep]++;
        nSC++;
    }
    
    theTree->Fill();
    
    // Now fill the basiccluster tree of the leading supercluster
    
    nBCIsc=0;
    if ( maxEt > 0 ) {
       eSCIsc = maxScItr->energy();
       rawESCIsc = maxScItr->rawEnergy();
       etaSCIsc  = maxScItr->eta();
       phiSCIsc = maxScItr->phi();
       rawEtSCIsc = rawESCIsc/cosh(etaSCIsc);
       for (reco::CaloCluster_iterator bcItr = maxScItr->clustersBegin(); bcItr != maxScItr->clustersEnd(); ++bcItr) {
	  energyIsc[nBCIsc] = (*bcItr)->energy();
	  etaIsc[nBCIsc]    = (*bcItr)->eta();
	  phiIsc[nBCIsc]    = (*bcItr)->phi();
	  etIsc[nBCIsc]     = energyIsc[nBCIsc]/cosh(etaIsc[nBCIsc]);
	  nBCIsc++;
       }
    }
    bcTree->Fill();
    
}


// ------------ method called once each job just before starting event loop  ------------
    void 
EcalHistProducerPP::beginJob() 
{
    NoE      = fs->make<TH1D>( "NoE"  , "", 1,  -100., 100. );
    rhEB     = fs->make<TH1D>( "rhEB"  , "", 10100,  -1., 100. );
    rhEE     = fs->make<TH1D>( "rhEE"  , "", 10100,  -1., 100. );

    char name[200];
    char title[200];
    for(int i=0; i<cBins; i++) {
        sprintf(name,"NoEc%d",i);
        sprintf(title,"NoE Centrality Bins %d-%d",i*cStep,(i+1)*cStep-1);
        NoEcent[i] = fs->make<TH1D>(name,title,1,-100.,100.);
        if(RHCent_) {
            sprintf(name,"rhEBc%d",i);
            sprintf(title,"rhEB Centrality Bins %d-%d",i*cStep,(i+1)*cStep-1);
            rhEBcent[i] = fs->make<TH1D>(name,title,10100,-1.,100.);
            sprintf(name,"rhEEc%d",i);
            sprintf(title,"rhEE Centrality Bins %d-%d",i*cStep,(i+1)*cStep-1);
            rhEEcent[i] = fs->make<TH1D>(name,title,10100,-1.,100.);
            if(RHetaCent_) {
                sprintf(name,"rhEtac%d",i);
                sprintf(title,"rhEta Centrality Bins %d-%d",i*cStep,(i+1)*cStep-1);
                rhEtaCent[i] = fs->make<TH1D>(name,title,6000,-3.,3.);
            }
            if(RHphiCent_) {
                sprintf(name,"rhPhic%d",i);
                sprintf(title,"rhPhi Centrality Bins %d-%d",i*cStep,(i+1)*cStep-1);
                rhPhiCent[i] = fs->make<TH1D>(name,title,6000,-3.2,3.2);
            }
        }
    }

    theTree  = fs->make<TTree>("clusters","Tree of Basic Clusters");
    //   theTree->Branch("nPho",&nPho,"nPho/I");
    char format[200];
    theTree->Branch("nBC",&nBC,"nBC/I");
    theTree->Branch("nSC",&nSC,"nSC/I");
  
    theTree->Branch("BCe",energy,"BCe[nBC]/F");
    theTree->Branch("BCet",et,"BCet[nBC]/F");
    theTree->Branch("BCeta",eta,"BCeta[nBC]/F");
    theTree->Branch("BCphi",phi,"BCphi[nBC]/F");

    bcTree  = fs->make<TTree>("clustersInSC","Tree of Basic Clusters in leading raw et SC");
    bcTree->Branch("nBCIsc",&nBCIsc,"nBCIsc/I");
    bcTree->Branch("eSCIsc",&eSCIsc,"eSCIsc/F");
    bcTree->Branch("rawESCIsc",&rawESCIsc,"rawESCIsc/F");
    bcTree->Branch("rawEtSCIsc",&rawEtSCIsc,"rawEtSCIsc/F");
    bcTree->Branch("etaSCIsc",&etaSCIsc,"etaSCIsc/F");
    bcTree->Branch("phiSCIsc",&phiSCIsc,"phiSCIsc/F");
    bcTree->Branch("cBinIsc",&bin,"cBinIsc/I");
    bcTree->Branch("eIsc",energyIsc,"eIsc[nBCIsc]/F");
    bcTree->Branch("etIsc",etIsc,"etIsc[nBCIsc]/F");
    bcTree->Branch("etaIsc",etaIsc,"etaIsc[nBCIsc]/F");
    bcTree->Branch("phiIsc",phiIsc,"phiIsc[nBCIsc]/F");


    
    if(BCCent_) {
        for(int i=0; i<cBins; i++) {
            sprintf(name,"nBCcent%dto%d",i*cStep,(i+1)*cStep-1);
            sprintf(format,"nBCcent/I");
            theTree->Branch(name,&nBCcent[i],format);
            sprintf(name,"eCent%dto%d",i*cStep,(i+1)*cStep-1);
            sprintf(format,"energyCent[nBC]/F");
            theTree->Branch(name,energyCent[i],format);
            sprintf(name,"etCent%dto%d",i*cStep,(i+1)*cStep-1);
            sprintf(format,"etCent[nBC]/F");
            theTree->Branch(name,etCent[i],format);
            if(BCetaCent_) {
                sprintf(name,"etaCent%dto%d",i*cStep,(i+1)*cStep-1);
                sprintf(format,"etaCent[nBC]/F");
                theTree->Branch(name,etaCent[i],format);
            }
            if(BCphiCent_) {
                sprintf(name,"phiCent%dto%d",i*cStep,(i+1)*cStep-1);
                sprintf(format,"phiCent[nBC]/F");
                theTree->Branch(name,phiCent[i],format);
            }
        }
    }
    theTree->Branch("hf",&hf,"hf/D");
    theTree->Branch("eb",&eb,"eb/D");
    theTree->Branch("cBin",&bin,"cBin/I");

    theTree->Branch("multPixel",&multPixel,"multPixel/D");
    theTree->Branch("nPixelTracks",&nPixelTracks,"nPixelTracks/D");

    theTree->Branch("SCe",SCenergy,"SCe[nSC]/F");      
    theTree->Branch("SCet",SCet,"SCet[nSC]/F");      
    theTree->Branch("SCeta",SCeta,"SCeta[nSC]/F");   
    theTree->Branch("SCphi",SCphi,"SCphi[nSC]/F");
    if(SCCent_) {
        for(int i=0; i<cBins; i++) {
            sprintf(name,"nSCcent%dto%d",i*cStep,(i+1)*cStep-1);
            sprintf(format,"nSCcent/I");
            theTree->Branch(name,&nSCcent[i],format);
            sprintf(name,"SCeCent%dto%d",i*cStep,(i+1)*cStep-1);
            sprintf(format,"SCenergyCent[nSC]/F");
            theTree->Branch(name,SCenergyCent[i],format);
            sprintf(name,"SCetCent%dto%d",i*cStep,(i+1)*cStep-1);
            sprintf(format,"SCetCent[nSC]/F");
            theTree->Branch(name,SCetCent[i],format);
            if(SCetaCent_) {
                sprintf(name,"SCetaCent%dto%d",i*cStep,(i+1)*cStep-1);
                sprintf(format,"SCetaCent[nSC]/F");
                theTree->Branch(name,SCetaCent[i],format);
            }
            if(SCphiCent_) {
                sprintf(name,"SCphiCent%dto%d",i*cStep,(i+1)*cStep-1);
                sprintf(format,"SCphiCent[nSC]/F");
                theTree->Branch(name,SCphiCent[i],format);
            }
        }
    }

    std::cout<<"done beginjob"<<std::endl;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EcalHistProducerPP::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(EcalHistProducerPP);
