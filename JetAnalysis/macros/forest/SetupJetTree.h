#include "commonSetup.h"
#include <TTree.h>

class Jets
{
  public:

  Jets(){};
  ~Jets(){};

  int nref;
  float jtpt[maxEntry];
  float rawpt[maxEntry];
  float jteta[maxEntry];
  float jtphi[maxEntry];
  float refpt[maxEntry];
  float refeta[maxEntry];
  float refphi[maxEntry];
  float refparton_pt[maxEntry];
  float refparton_flavor[maxEntry];
  float smpt[maxEntry];
  
  int ngen;
  int bin;
  float genpt[maxEntry];
  float geneta[maxEntry];
  float genphi[maxEntry];
};

void setupJetTree(TTree *t, Jets &jets)
{
  t->SetBranchAddress("nref",&jets.nref);
  t->SetBranchAddress("bin",&jets.bin);
  t->SetBranchAddress("rawpt",jets.rawpt);
  t->SetBranchAddress("jtpt",jets.jtpt);
  t->SetBranchAddress("jteta",jets.jteta);
  t->SetBranchAddress("jtphi",jets.jtphi);
  t->SetBranchAddress("refpt",jets.refpt);
  t->SetBranchAddress("refphi",jets.refphi);
  t->SetBranchAddress("refparton_pt",jets.refparton_pt);
  t->SetBranchAddress("refparton_flavor",jets.refparton_flavor);

  t->SetBranchAddress("ngen",&jets.ngen);
  t->SetBranchAddress("genpt",jets.genpt);
  t->SetBranchAddress("geneta",jets.geneta);
  t->SetBranchAddress("genphi",jets.genphi);
}
