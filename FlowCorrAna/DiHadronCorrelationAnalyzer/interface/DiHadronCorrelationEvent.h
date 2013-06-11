#ifndef DiHadronCorrelationEvent_
#define DiHadronCorrelationEvent_

#include <vector>
#include <TVector3.h>

using namespace std;

#define MAXPTTRGBINS 20 
#define MAXPTASSBINS 20

class DiHadronCorrelationEvent {                                                                                  

 public:                                                                                           
   //  vectors for tracks, hits etc
   vector<TVector3>  pVect_all;
   vector<TVector3>  pVect_trg[MAXPTTRGBINS];
   vector<double>    nMultCorrVect_trg;
   vector<double>    chgVect_trg[MAXPTTRGBINS];
   vector<double>    effVect_trg[MAXPTTRGBINS];
//   double            multcorrVect_trg[MAXPTTRGBINS];
   vector<TVector3>  pVect_ass[MAXPTASSBINS];
   vector<double>    nMultCorrVect_ass;
   vector<double>    chgVect_ass[MAXPTASSBINS];
   vector<double>    effVect_ass[MAXPTASSBINS];
//   double            multcorrVect_ass[MAXPTASSBINS];
   int               nmult;
   int               centbin;
   double            zvtx;
   double            epangle;

   bool operator<(const DiHadronCorrelationEvent & b) const{
     if (centbin != b.centbin) return centbin < b.centbin;
     else if (zvtx != b.zvtx) return zvtx < b.zvtx;
     else return false;
   }

   DiHadronCorrelationEvent(){}
   ~DiHadronCorrelationEvent(){}
};

#endif  // DiHadronCorrelationEvent_
