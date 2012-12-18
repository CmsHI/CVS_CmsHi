#ifndef CutParameters_
#define CutParameters_

#include <vector>
#include <TString.h>

using namespace std;

class CutParameters {                                                                                  

 public:                                                                                           
   unsigned int runmin;
   unsigned int runmax;
   int     nmin;
   int     nmax;
   int     centmin;
   int     centmax;
   double  etatrgmin;                                                                                     
   double  etatrgmax;
   double  etaassmin;
   double  etaassmax;   
   double  etamultmin;
   double  etamultmax;
   vector<double>  pttrgmin;
   vector<double>  pttrgmax;
   vector<double>  ptassmin;
   vector<double>  ptassmax;
   double  ptmultmin;
   double  ptmultmax;   
   double  xvtxcenter;
   double  yvtxcenter;
   double  zvtxcenter;
   double  rhomin;
   double  rhomax;
   double  zvtxmin;
   double  zvtxmax;
   double  zvtxbin;
   double  vtxsepmin;
   int     nvtxmax;
   bool    istrigger;
   vector<TString> triggernames;
   vector<TString> vetonames;
   int     njetsmin;
   int     njetsmax;
   double  jetetmin;
   double  jetetmax;
   double  jetetfraction;
   double  leadjetetmin;
   double  subjetetmin;
   double  pthard1;
   double  pthard2;
   double  delta;
   TString trgtrackCollection;
   TString asstrackCollection;
   TString vertexCollection;
   TString jetCollection;
   TString genParticleCollection;
   TString chargeCandidateCollection;
   TString superClusterCollection;
   TString superClusterFwdCollection;
};

#endif  // CutParameters_
