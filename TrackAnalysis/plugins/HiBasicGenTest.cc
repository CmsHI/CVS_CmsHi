#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "CmsHi/TrackAnalysis/plugins/HiBasicGenTest.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "HepMC/GenEvent.h"
#include "HepMC/HeavyIon.h"

#include <TString.h>

using namespace edm;

HiBasicGenTest::HiBasicGenTest(const edm::ParameterSet& iPSet)
{
  dbe = 0;
  dbe = edm::Service<DQMStore>().operator->();
}

HiBasicGenTest::~HiBasicGenTest() {}

void HiBasicGenTest::beginJob()
{
  if(dbe){
    ///Setting the DQM top directories
    dbe->setCurrentFolder("Generator/Particles");
    
    ///Booking the ME's
    for(int ibin=0; ibin<3; ibin++) {
      dnchdeta[ibin] = dbe->book1D(Form("dnchdeta%d",ibin), ";#eta;dN^{ch}/d#eta", 100, -6.0, 6.0);
      dnchdpt[ibin] = dbe->book1D(Form("dnchdpt%d",ibin), ";p_{T};dN^{ch}/dp_{T}", 200, 0.0, 100.0);
      b[ibin] = dbe->book1D(Form("b%d",ibin),";b[fm];events",100, 0.0, 20.0);
      dnchdphi[ibin] = dbe->book1D(Form("dnchdphi%d",ibin),";#phi;dN^{ch}/d#phi",100, -3.2, 3.2);

      dbe->tag(dnchdeta[ibin]->getFullname(),1+ibin*4);
      dbe->tag(dnchdpt[ibin]->getFullname(),2+ibin*4);
      dbe->tag(b[ibin]->getFullname(),3+ibin*4);
      dbe->tag(dnchdphi[ibin]->getFullname(),4+ibin*4);
    }

    rp = dbe->book1D("phi0",";#phi_{RP};events",100,-3.2,3.2);
    dbe->tag(rp->getFullname(),13);


 }
  return;
}

void HiBasicGenTest::endJob(){return;}
void HiBasicGenTest::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void HiBasicGenTest::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void HiBasicGenTest::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 

  Handle<HepMCProduct> mc;
  iEvent.getByLabel("generator",mc);
  const HepMC::GenEvent *evt = mc->GetEvent();
  const HepMC::HeavyIon *hi = evt->heavy_ion();
  
  double ip = hi->impact_parameter();
  double phi0 = hi->event_plane_angle();

  rp->Fill(phi0);
  
  int cbin=-1;

  if(ip < 5.045) cbin=0;
  else if (ip < 7.145 && ip > 5.045) cbin=1;
  else if (ip < 15.202 && ip > 14.283) cbin=2;

  if(cbin>=0) {

    b[cbin]->Fill(ip);


  }


}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(HiBasicGenTest);


