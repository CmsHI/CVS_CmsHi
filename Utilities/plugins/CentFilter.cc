
//
// Package:    CentFilter
// Class:      CentFilter
// 
/**\class CentFilter CentFilter.cc simplaAnlzer/CentFilter/src/CentFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Yongsun Kim
//         Created:  Fri May 22 12:57:09 EDT 2009
// $Id: CentFilter.cc,v 1.2 2009/06/25 11:53:43 yilmaz Exp $
//
//


// system include files
#include <memory>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

using namespace std;

int getBin(double input, vector<double>& edges, int sign = 1){

   int bin = -9;
   int ibin = -9;

   for(int i = 0; i< edges.size(); i++){
      double min = edges[i];

      if(input >= min) ibin  = i+1;
      if(input < min ) break;    
   }
   if(sign == -1)bin = ibin+1;
   else bin = edges.size() - ibin;
  
   if(ibin < 0) cout<<"Warning : Bin not determined correctly - "<<bin<<endl;

   return bin;
}





//
// class declaration
//

class CentFilter : public edm::EDFilter {
   public:
      explicit CentFilter(const edm::ParameterSet&);
      ~CentFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------

   string cutBase_;
   vector<double> bCuts_;
   vector<double> hfCuts_;
   vector<double> hfGenCuts_;
   vector<double> nPartCuts_;
   vector<int> selectedBins_;
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
CentFilter::CentFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed

   if(cutBase_ == "b"){
      bCuts_  = iConfig.getParameter<vector<double> >("bCuts");
   }
   if(cutBase_ == "hf"){
      hfCuts_  = iConfig.getParameter<vector<double> >("hfCuts");
   }
   if(cutBase_ == "gen"){
      hfGenCuts_  = iConfig.getParameter<vector<double> >("hfGenCuts");
   }
   if(cutBase_ == "npart"){
      nPartCuts_  = iConfig.getParameter<vector<double> >("nPartCuts");
   }

   selectedBins_ = iConfig.getParameter<vector<int> >("selectBins");
  
} 


CentFilter::~CentFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
CentFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;
   using namespace HepMC;
   
   int bin = -1;

   if(cutBase_ == "b" || cutBase_ == "npart"){
      const GenEvent *evt;

   Handle<HepMCProduct> mc;
   iEvent.getByLabel("generator",mc);
   evt = mc->GetEvent();

   const HeavyIon* hi = evt->heavy_ion();
   //int nPart = hi->Npart_proj()+hi->Npart_targ();
   double b = hi->impact_parameter();
   double npart = hi->Npart_proj()+hi->Npart_targ();

   if(cutBase_ == "b")
      bin = getBin(b,bCuts_);
   if(cutBase_ == "npart")
      bin = getBin(npart,nPartCuts_);
   
   }else{
      Handle<Centrality> cent;
      if(cutBase_ == "gen"){
	 iEvent.getByLabel(InputTag("hiCentrality","genBased"),cent);
	 bin = getBin(cent->HFEnergy(),hfGenCuts_);
      }
      if(cutBase_ == "hf"){
	 iEvent.getByLabel(InputTag("hiCentrality","recoBased"),cent);
      bin = getBin(cent->HFEnergy(),hfCuts_);
      }
   }
   
   for(int i = 0; i < selectedBins_.size(); ++i){
      if(bin == selectedBins_[i]) return true;
   }

   return false;
   
}

// ------------ method called once each job just before starting event loop  ------------
void 
CentFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CentFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(CentFilter);
