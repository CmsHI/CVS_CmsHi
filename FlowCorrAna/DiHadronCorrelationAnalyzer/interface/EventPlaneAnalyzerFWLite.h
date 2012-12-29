#ifndef EventPlaneAnalyzerFWLite_
#define EventPlaneAnalyzerFWLite_

#ifndef DiHadronCorrelationMultiBaseFWLite_
#include "DiHadronCorrelationMultiBaseFWLite.h"
#endif 

#include <vector>
#include <string>

class TH1D;
class TH2D;
class TH3D;
class TTree;
class TList;

class EventPlaneAnalyzerFWLite : public DiHadronCorrelationMultiBaseFWLite {
   
 protected:

   // histograms
   TH2D* hSignal[MAXPTTRGBINS];
   TH1D* hPsi;

   // parameters

   virtual void Process(); 
   virtual void MakeHists();
   virtual void NormalizeHists();
   virtual void DeleteHists();
   virtual void FillHistsSignal(const DiHadronCorrelationEvent& eventcorr);
   virtual TList* GetOutputs();
   
 public:
   EventPlaneAnalyzerFWLite(fwlite::ChainEvent&);
   virtual ~EventPlaneAnalyzerFWLite();

};
#endif  // EventPlaneAnalyzerFWLite_
