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
#include "TH2D.h"
#include "TTree.h"
#include "TH1D.h"
#include <iostream>
#include "TCanvas.h"



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
   TBranch *currentEtaIndexBranch;
   TBranch *currentPhiIndexBranch;
   TBranch *currentEtBranch;
   TBranch *currentTauBranch;

   TBranch* fJetEtBranch;
   TBranch* fJetEtaIndexBranch;
   TBranch* fJetPhiIndexBranch;
   TBranch* fJetNumberBranch;

   TBranch* fTauEtBranch;
   TBranch* fTauEtaIndexBranch;
   TBranch* fTauPhiIndexBranch;
   TBranch* fTauNumberBranch;

   TBranch* cJetEtBranch;
   TBranch* cJetEtaIndexBranch;
   TBranch* cJetPhiIndexBranch;
   TBranch* cJetNumberBranch;

   TBranch* cTauEtBranch;
   TBranch* cTauEtaIndexBranch;
   TBranch* cTauPhiIndexBranch;
   TBranch* cTauNumberBranch;

   double currentEta[396];
   int currentEt[396];
   double currentPhi[396];
   int currentTau[396];
   int currentEtaIndex[396];
   int currentPhiIndex[396];

   int fJetEt[4];
   int fJetEtaIndex[4];
   int fJetPhiIndex[4];
   int fJetNumber;

   int fTauEt[4];
   int fTauEtaIndex[4];
   int fTauPhiIndex[4];
   int fTauNumber;

   int cJetEt[4];
   int cJetEtaIndex[4];
   int cJetPhiIndex[4];
   int cJetNumber;

   int cTauEt[4];
   int cTauEtaIndex[4];
   int cTauPhiIndex[4];
   int cTauNumber;
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
   tree->SetBranchAddress("caloRegionEtaIndex",currentEtaIndex, &currentEtaIndexBranch);
   tree->SetBranchAddress("caloRegionPhiIndex",currentPhiIndex, &currentPhiIndexBranch);
   tree->SetBranchAddress("caloRegionTau",currentTau, &currentTauBranch);

   fJetEtBranch=      tree->Branch("fJetEt",fJetEt,"fJetEt[4]/I");
   fJetEtaIndexBranch=tree->Branch("fJetEta",fJetEtaIndex,"fJetEta[4]/I");
   fJetPhiIndexBranch=tree->Branch("fJetPhi",fJetPhiIndex,"fJetPhi[4]/I");
   fJetNumberBranch=  tree->Branch("fJetNumber",&fJetNumber,"fJetNumber/I");

   fTauEtBranch=      tree->Branch("fTauEt",fTauEt,"fTauEt[4]/I");
   fTauEtaIndexBranch=tree->Branch("fTauEta",fTauEtaIndex,"fTauEta[4]/I");
   fTauPhiIndexBranch=tree->Branch("fTauPhi",fTauPhiIndex,"fTauPhi[4]/I");
   fTauNumberBranch=  tree->Branch("fTauNumber",&fTauNumber,"fTauNumber/I");

   cJetEtBranch=      tree->Branch("cJetEt",cJetEt,"cJetEt[4]/I");
   cJetEtaIndexBranch=tree->Branch("cJetEta",cJetEtaIndex,"cJetEta[4]/I");
   cJetPhiIndexBranch=tree->Branch("cJetPhi",cJetPhiIndex,"cJetPhi[4]/I");
   cJetNumberBranch=  tree->Branch("cJetNumber",&cJetNumber,"cJetNumber/I");

   cTauEtBranch=      tree->Branch("cTauEt",cTauEt,"cTauEt[4]/I");
   cTauEtaIndexBranch=tree->Branch("cTauEta",cTauEtaIndex,"cTauEta[4]/I");
   cTauPhiIndexBranch=tree->Branch("cTauPhi",cTauPhiIndex,"cTauPhi[4]/I");
   cTauNumberBranch=  tree->Branch("cTauNumber",&cTauNumber,"cTauNumber/I");

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
   currentEtaIndexBranch->GetEntry(entry);
   currentPhiIndexBranch->GetEntry(entry);
   currentTauBranch->GetEntry(entry);

   int mapEt[22][18];
   int mapTau[22][18];

   int tempEt[3][3];
   int tempTau[3][3];

   int tfJetEt[72];
   int tfJetEtaIndex[72];
   int tfJetPhiIndex[72];
   int tfJetTau[252];
   fJetNumber=0;
   fTauNumber=0;

   int tcJetEt[252];
   int tcJetEtaIndex[252];
   int tcJetPhiIndex[252];
   int tcJetTau[252];
   cJetNumber=0;
   cTauNumber=0;

   for(int i=0;i<396;i++){
     histoEt2D->Fill(currentPhi[i],currentEta[i],currentEt[i]);
     histoEtvsEta->Fill(currentEta[i],currentEt[i]);
     histoEtvsPhi->Fill(currentPhi[i],currentEt[i]);
     mapEt[currentEtaIndex[i]][currentPhiIndex[i]]=currentEt[i];
     //std::cout<<currentEtaIndex[i]<<" "<<currentPhiIndex[i]<<" "<<mapEt[currentEtaIndex[i]][currentPhiIndex[i]]<<std::endl;
     mapTau[currentEtaIndex[i]][currentPhiIndex[i]]=currentTau[i];
     // std::cout<<currentPhi[i]<<" "<<currentEta[i]<<" "<<currentEt[i]<<std::endl;
   }
   int isItJet,isItTau,tmpEt;

   for(int ieta=0;ieta<20;ieta++){
     if (ieta==3) ieta=17;
     for(int iphi=0;iphi<18;iphi++){
       for(int itphi=0;itphi<3;itphi++)
         for(int iteta=0;iteta<3;iteta++){
           tempEt[iteta][itphi]=mapEt[ieta+iteta][iphi+itphi>17?iphi+itphi-18:iphi+itphi];
           tempTau[iteta][itphi]=mapTau[ieta+iteta][iphi+itphi>17?iphi+itphi-18:iphi+itphi];
         }
       isItJet=1;isItTau=0;tmpEt=0;
       for(int itphi=0;itphi<3;itphi++)
         for(int iteta=0;iteta<3;iteta++){
           if ((iteta!=1) || (itphi!=1))
             if (tempEt[iteta][itphi]>tempEt[1][1])  isItJet=0;
           isItTau+=tempTau[iteta][itphi];
           tmpEt+=tempEt[iteta][itphi];
         }
       if (tempEt[1][1]==0) isItJet=0;
       if (isItJet==1){
         tfJetEt[fJetNumber]=tmpEt;
         tfJetEtaIndex[fJetNumber]=ieta+1;
         tfJetPhiIndex[fJetNumber]=(iphi+1==18?0:iphi+1);
         tfJetTau[fJetNumber]=(isItTau?0:1);
         fTauNumber+=tfJetTau[fJetNumber];
         fJetNumber++;
       }
     }
   }
  
   for(int ieta=3;ieta<17;ieta++){
     for(int iphi=0;iphi<18;iphi++){
       for(int itphi=0;itphi<3;itphi++)
         for(int iteta=0;iteta<3;iteta++){
           tempEt[iteta][itphi]=mapEt[ieta+iteta][iphi+itphi>17?iphi+itphi-18:iphi+itphi];
           tempTau[iteta][itphi]=mapTau[ieta+iteta][iphi+itphi>17?iphi+itphi-18:iphi+itphi];
         }
       isItJet=1;isItTau=0;tmpEt=0;
       for(int itphi=0;itphi<3;itphi++)
         for(int iteta=0;iteta<3;iteta++){
           if ((iteta!=1) || (itphi!=1))
             if (tempEt[iteta][itphi]>tempEt[1][1]) isItJet=0;
           isItTau+=tempTau[iteta][itphi];
           tmpEt+=tempEt[iteta][itphi];
         }
       if (tempEt[1][1]==0) isItJet=0;
       if (isItJet==1){
         tcJetEt[cJetNumber]=tmpEt;
         tcJetEtaIndex[cJetNumber]=ieta+1;
         tcJetPhiIndex[cJetNumber]=(iphi+1==18?0:iphi+1);
         tcJetTau[cJetNumber]=(isItTau?0:1);
         cTauNumber+=tcJetTau[cJetNumber];
         cout<<tcJetTau[cJetNumber]<<" "<<ieta+1<<" "<<iphi+1<<endl;
         cJetNumber++;
       }
     }
   }
  
   cJetNumber-=cTauNumber;
   fJetNumber-=fTauNumber;

   std::cout<<cJetNumber<<" "<<fJetNumber<<" "<<cTauNumber<<" "<<fTauNumber<<std::endl;

   for(int i=0;i<4;i++){
     if(i==cJetNumber) {
       for(int j=i;j<4;j++){
         cJetEt[j]=-1;
         cJetEtaIndex[j]=-1;
         cJetPhiIndex[j]=-1;
       }
       break;
     }
     else{
       int max=0,jindex=0;
       for(int j=0;j<cJetNumber+cTauNumber;j++)
         if(tcJetEt[j]>max) if (tcJetTau[j]==0) {max=tcJetEt[j]; jindex=j;}
       cJetEt[i]=tcJetEt[jindex];
       tcJetEt[jindex]=0;
       cJetEtaIndex[i]=tcJetEtaIndex[jindex];
       cJetPhiIndex[i]=tcJetPhiIndex[jindex];
     }
   }
   //cout<<"1 : OK"<<endl;
   for(int i=0;i<4;i++){
     if(i==cTauNumber) {
       for(int j=i;j<4;j++){
         cTauEt[j]=-1;
         cTauEtaIndex[j]=-1;
         cTauPhiIndex[j]=-1;
       }
       break;
     }
     else{
       int max=0,jindex=0;
       for(int j=0;j<cTauNumber+cJetNumber;j++)
         if(tcJetEt[j]>max) if (tcJetTau[j]==1) {max=tcJetEt[j];jindex=j;}
       cTauEt[i]=tcJetEt[jindex];
       tcJetEt[jindex]=0;
       cTauEtaIndex[i]=tcJetEtaIndex[jindex];
       cTauPhiIndex[i]=tcJetPhiIndex[jindex];
     }
   }
   //cout<<"2 : OK"<<endl;
   for(int i=0;i<4;i++){
     if(i==fJetNumber) {       
       for(int j=i;j<4;j++){
         fJetEt[j]=-1;
         fJetEtaIndex[j]=-1;
         fJetPhiIndex[j]=-1;
       }
       break;
     }
     else{
       int max=0,jindex=0;
       for(int j=0;j<fJetNumber+fTauNumber;j++)
         if(tfJetEt[j]>max) if(tfJetTau[j]==0) {max=tfJetEt[j];jindex=j;}
       fJetEt[i]=tfJetEt[jindex];
       tfJetEt[jindex]=0;
       fJetEtaIndex[i]=tfJetEtaIndex[jindex];
       fJetPhiIndex[i]=tfJetPhiIndex[jindex];
     }
   }
   //cout<<"3 : OK"<<endl;
   for(int i=0;i<4;i++){
     if(i==fTauNumber) {       
       for(int j=i;j<4;j++){
         fTauEt[j]=-1;
         fTauEtaIndex[j]=-1;
         fTauPhiIndex[j]=-1;
       }
       break;
     }
     else{
       if (i==fTauNumber) break;
       int max=0,jindex=0;
       for(int j=0;j<fTauNumber+fJetNumber;j++)
         if(tfJetEt[j]>max) if(tfJetTau[j]==1) {max=tfJetEt[j];jindex=j;}
       fTauEt[i]=tfJetEt[jindex];
       tfJetEt[jindex]=0;
       fTauEtaIndex[i]=tfJetEtaIndex[jindex];
       fTauPhiIndex[i]=tfJetPhiIndex[jindex];
     }
   }
   //cout<<"4 : OK"<<endl;

   fJetEtBranch->Fill();
   fJetEtaIndexBranch->Fill();
   fJetPhiIndexBranch->Fill();
   fJetNumberBranch->Fill();

   fTauEtBranch->Fill();
   fTauEtaIndexBranch->Fill();
   fTauPhiIndexBranch->Fill();
   fTauNumberBranch->Fill();

   //cout<<"Fill f : OK"<<endl;

   cJetEtBranch->Fill();
   cJetEtaIndexBranch->Fill();
   cJetPhiIndexBranch->Fill();
   cJetNumberBranch->Fill();

   cTauEtBranch->Fill();
   cTauEtaIndexBranch->Fill();
   cTauPhiIndexBranch->Fill();
   cTauNumberBranch->Fill();

   cout<<"Fill : OK"<<endl;

   return kTRUE;
}

void EventSelector::Terminate()
{
   // The Terminate() function is the last function to be called during the
   // analysis of a tree with a selector. It always runs on the client, it can
   // be used to present the results graphically or save the results to file.
   
   //histoEt2D->Draw("lego2");
   //new TCanvas;
   //histoEtvsEta->Draw();
   //new TCanvas;
   //histoEtvsPhi->Draw();
}


