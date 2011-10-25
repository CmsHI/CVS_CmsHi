#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"


// Example of forest skim

void recorrectJets(const char* fname = "", const char* outname = "", bool pp = 0)
{

   // Define the input file and HiForest
  HiForest *c;

  if(pp){
    c = new HiForest("/d100/yjlee/hiForest/merged_pp2760_AllPhysics_NoPhoyon_Prod02.root","ppForest",1);
    c->SetOutputFile("skim_Dijet_pp2.root");
  }else{
     c = new HiForest(fname);
     c->SetOutputFile(outname);
  }

  string dirName = names::AlgoAnalyzer[names::akPu3PF]+"_recorrected";
  c->outf->cd();
  c->outf->mkdir(dirName.data());
  c->outf->cd(dirName.data());
  TTree* t = new TTree("t","");
  float jtpt[1000];

  t->Branch("nref",&c->akPu3PF.nref,"nref/I");
  t->Branch("jtpt",jtpt,"jtpt[nref]/F");
  t->Branch("rawpt",c->akPu3PF.rawpt,"rawpt[nref]/F");

  t->Branch("jteta",c->akPu3PF.jteta,"jteta[nref]/F");
  t->Branch("jtphi",c->akPu3PF.jtphi,"jtphi[nref]/F");
  t->Branch("refpt",c->akPu3PF.refpt,"refpt[nref]/F");
  t->Branch("refphi",c->akPu3PF.refphi,"refphi[nref]/F");
  t->Branch("refparton_pt",c->akPu3PF.refparton_pt,"refparton_pt[nref]/F");
  t->Branch("refparton_flavor",c->akPu3PF.refparton_flavor,"refparton_flavor[nref]/F");

  t->Branch("ngen",&c->akPu3PF.ngen,"ngen");
  t->Branch("genpt",c->akPu3PF.genpt,"genpt[ngen]/F");
  t->Branch("geneta",c->akPu3PF.geneta,"geneta[ngen]/F");
  t->Branch("genphi",c->akPu3PF.genphi,"genphi[ngen]/F");

  c->cloneForest.push_back(t);
  c->verbose = 1;


   // Main loop
   for (int i=0;i<c->GetEntries();i++)
   {
      if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<endl;
      c->GetEntry(i);

      for(int j = 0; j < c->akPu3PF.nref; ++j){

	 c->_JEC_HI310X->setJetEta(c->akPu3PF.jteta[j]);
	 c->_JEC_HI310X->setJetPt(c->akPu3PF.rawpt[j]);
	 jtpt[j] = c->akPu3PF.rawpt[j]*c->_JEC_HI310X->getCorrection();

      }

      c->FillOutput();
   }

   delete c;
}
