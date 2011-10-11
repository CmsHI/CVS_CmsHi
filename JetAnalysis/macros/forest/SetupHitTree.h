#include "commonSetup.h"
#include <TTree.h>

class Hits
{
  public:

  Hits(){};
  ~Hits(){};

   // Declaration of leaf types
   Int_t           n;
   Float_t         e[1850];   //[n]
   Float_t         et[1850];   //[n]
   Float_t         eta[1850];   //[n]
   Float_t         phi[1850];   //[n]
   Bool_t          isjet[1850];   //[n]

   // List of branches
   TBranch        *b_n;   //!
   TBranch        *b_e;   //!
   TBranch        *b_et;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_isjet;   //!
};

void setupHitTree(TTree *t, Hits &hits)
{
   t->SetBranchAddress("n", &hits.n, &hits.b_n);
   t->SetBranchAddress("e", hits.e, &hits.b_e); 
   t->SetBranchAddress("et", hits.et, &hits.b_et);
   t->SetBranchAddress("eta", hits.eta, &hits.b_eta);
   t->SetBranchAddress("phi", hits.phi, &hits.b_phi);
   t->SetBranchAddress("isjet", hits.isjet, &hits.b_isjet);
}
