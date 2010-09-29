/** QCDPhotonAnalysis/DataAnalyzers/plugin/MultiPhotonAnalyzer.h
 *
 * Description: 
 * Analysis code of the QCD Photons group;
 * Data Analyzer for the single photon (inclusive isolated photons and photon plus jets) cross section measurement; 
 * Store in ntuple run conditions and missing ET information for each event;
 * Makes ntuple of the photon and jet arrays in each event;
 * Store in ntuple trigger and vertexing information for each event;
 * Makes ntuple for the generator prompt photon kinematics and genealogy;
 * Perform the MC truth matching for the reconstructed photon;
 * Fill number of DQM histograms 
 *
 * \author Serguei Ganjour,     CEA-Saclay/IRFU, FR
 * \author Ted Ritchie Kolberg, University of Notre Dame, US
 * \author Michael B. Anderson, University of Wisconsin Madison, US 
 * \author Laurent Millischer,  CEA-Saclay/IRFU, FR
 * \author Vasundhara Chetluru, FNAL, US
 * \author Vladimir Litvin,     Caltech, US
 * \author Yen-Jie Lee,         MIT, US
 * \author Pasquale Musella,    LIP, PT
 * \author Shin-Shan Eiko Yu,   National Central University, TW
 * \author Abe DeBenedetti,     University of Minnesota, US  
 * \version $Id: MultiPhotonAnalyzer.h,v 1.3 2010/08/18 16:59:47 kimy Exp $
 *
 */
// This MultiphotonAnalyzer was modified to fit with Heavy Ion collsion by Yongsun Kim ( MIT)                                                                                                

#ifndef QCDPhotonAnalysis_DataAnalyzers_MultiPhotonAnalyzer_h
#define QCDPhotonAnalysis_DataAnalyzers_MultiPhotonAnalyzer_h

#include "QCDPhotonAnalysis/DataAnalyzers/plugins/SinglePhotonAnalyzer.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"

#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

class MultiPhotonAnalyzer : public SinglePhotonAnalyzer { 

public:
   
   explicit MultiPhotonAnalyzer(const edm::ParameterSet&);
   ~MultiPhotonAnalyzer();
   
 protected:
   
   virtual void analyze(const edm::Event&, const edm::EventSetup&);	
   virtual int selectStorePhotons(const edm::Event&,const edm::EventSetup&,const char* pfx="");
   virtual int storePhotons(const edm::Event&,const edm::EventSetup&  ,pat::PhotonCollection &, reco::PhotonCollection &,const char* pfx="");
   
   const int kMaxPhotons;
   
};

#endif
