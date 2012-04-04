// For more information on the TSelector framework see 
// $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The file for this selector can be found at
// http://lcg-heppkg.web.cern.ch/lcg-heppkg/ROOT/eventdata.root
// i.e run
//   root [0] f = TFile::Open("http://lcg-heppkg.web.cern.ch/lcg-heppkg/ROOT/eventdata.root");
//   root [1] EventTree->Process("EventSelector.C+")

// The following methods are defined in this file:
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers, a convenient place to create your histograms.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("EventSelector.C")
// Root > T->Process("EventSelector.C","some options")
// Root > T->Process("EventSelector.C+")
//

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TSelector.h"

const Int_t kMaxfParticles = 1293;

class EventSelector : public TSelector {
public :

   EventSelector(TTree * = 0) { }
   virtual ~EventSelector() { }

   virtual void    Init(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual Bool_t  Process(Long64_t entry);
   virtual void    Terminate();
   virtual Int_t   Version() const { return 2; }

   ClassDef(EventSelector,0);

   TH2D *histoEt2D;
   TH1D *histoEtvsEta;
   TH1D *histoEtvsPhi;
   TBranch *currentEtaBranch;
   TBranch *currentPhiBranch;
   TBranch *currentEtBranch;

   double currentEta[396];
   int currentEt[396];
   double currentPhi[396];
};

void EventSelector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   tree->SetMakeClass(1);
   tree->SetBranchAddress("caloRegionEta",currentEta, &currentEtaBranch);
   tree->SetBranchAddress("caloRegionEt",currentEt, &currentEtBranch);
   tree->SetBranchAddress("caloRegionPhi",currentPhi, &currentPhiBranch);
}

void EventSelector::SlaveBegin(TTree *tree)
{
   // SlaveBegin() is a good place to create histograms. 
   // For PROOF, this is called for each worker.
   // The TTree* is there for backward compatibility; e.g. PROOF passes 0.
  Double_t ybins[23] = {-5.,-4.5,-4.,-3.5,-3.,-2.172,-1.74,-0.087*16,-0.087*12,-0.087*8,-0.087*4,0,0.087*4,0.087*8,0.087*12,0.087*16,1.74,2.172,3.,3.5,4.,4.5,5.};
  histoEt2D=new TH2D("hCaloRegion","histo EtCaloRegion vs Eta,Phi",18,0,6.283,22,ybins);
  histoEtvsEta=new TH1D("hCaloRegion2","histo EtCaloRegion vs Eta",22,ybins);
  histoEtvsPhi=new TH1D("hCaloRegion3","histo EtCaloRegion vs Phi",18,0,6.283);
}

Bool_t EventSelector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree to be 
   // processed. The entry argument specifies which entry in the currently
   // loaded tree is to be processed.
   // It can be passed to either EventSelector::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the TTree.
   //
   // This function should contain the "body" of the analysis: select relevant
   // tree entries, run algorithms on the tree entry and typically fill histograms.
   currentEtaBranch->GetEntry(entry);
   currentEtBranch->GetEntry(entry);
   currentPhiBranch->GetEntry(entry);
   for(int i=0;i<396;i++){
     histoEt2D->Fill(currentPhi[i],currentEta[i],currentEt[i]);
     histoEtvsEta->Fill(currentEta[i],currentEt[i]);
     histoEtvsPhi->Fill(currentPhi[i],currentEt[i]);
     // std::cout<<currentPhi[i]<<" "<<currentEta[i]<<" "<<currentEt[i]<<std::endl;
   }
   return kTRUE;
}

void EventSelector::Terminate()
{
   // The Terminate() function is the last function to be called during the
   // analysis of a tree with a selector. It always runs on the client, it can
   // be used to present the results graphically or save the results to file.
   histoEt2D->Draw("lego2");
   new TCanvas;
   histoEtvsEta->Draw();
   new TCanvas;
   histoEtvsPhi->Draw();
}


