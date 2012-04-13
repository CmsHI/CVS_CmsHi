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

   TBranch* cJetEtBranch;
   TBranch* cJetEtaIndexBranch;
   TBranch* cJetPhiIndexBranch;
   TBranch* cJetNumberBranch;

   TBranch* TauEtBranch;
   TBranch* TauEtaIndexBranch;
   TBranch* TauPhiIndexBranch;
   TBranch* TauNumberBranch;

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

   int cJetEt[4];
   int cJetEtaIndex[4];
   int cJetPhiIndex[4];
   int cJetNumber;

   int TauEt[4];
   int TauEtaIndex[4];
   int TauPhiIndex[4];
   int TauNumber;

   int eventnumber;
   int acceptednumber;
   int taunumber;
};

void EventSelector::Init(TTree *tree)
{
   eventnumber=0;
   acceptednumber=0;
   taunumber=0;
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   tree->SetMakeClass(1);
   //tree->SetBranchAddress("caloRegionEta",currentEta, &currentEtaBranch);
   tree->SetBranchAddress("caloRegionEt",currentEt, &currentEtBranch);
   //tree->SetBranchAddress("caloRegionPhi",currentPhi, &currentPhiBranch);
   tree->SetBranchAddress("caloRegionEtaIndex",currentEtaIndex, &currentEtaIndexBranch);
   tree->SetBranchAddress("caloRegionPhiIndex",currentPhiIndex, &currentPhiIndexBranch);
   tree->SetBranchAddress("caloRegionTau",currentTau, &currentTauBranch);

   fJetEtBranch=      tree->Branch("fJetEt",fJetEt,"fJetEt[4]/I");
   fJetEtaIndexBranch=tree->Branch("fJetEta",fJetEtaIndex,"fJetEta[4]/I");
   fJetPhiIndexBranch=tree->Branch("fJetPhi",fJetPhiIndex,"fJetPhi[4]/I");
   fJetNumberBranch=  tree->Branch("fJetNumber",&fJetNumber,"fJetNumber/I");

   cJetEtBranch=      tree->Branch("cJetEt",cJetEt,"cJetEt[4]/I");
   cJetEtaIndexBranch=tree->Branch("cJetEta",cJetEtaIndex,"cJetEta[4]/I");
   cJetPhiIndexBranch=tree->Branch("cJetPhi",cJetPhiIndex,"cJetPhi[4]/I");
   cJetNumberBranch=  tree->Branch("cJetNumber",&cJetNumber,"cJetNumber/I");

   TauEtBranch=      tree->Branch("TauEt",TauEt,"TauEt[4]/I");
   TauEtaIndexBranch=tree->Branch("TauEta",TauEtaIndex,"TauEta[4]/I");
   TauPhiIndexBranch=tree->Branch("TauPhi",TauPhiIndex,"TauPhi[4]/I");
   TauNumberBranch=  tree->Branch("TauNumber",&TauNumber,"TauNumber/I");
}

void EventSelector::SlaveBegin(TTree *tree)
{
  // SlaveBegin() is a good place to create histograms. 
  // For PROOF, this is called for each worker.
  // The TTree* is there for backward compatibility; e.g. PROOF passes 0.
  //Double_t ybins[23] = {-5.,-4.5,-4.,-3.5,-3.,-2.172,-1.74,-0.087*16,-0.087*12,-0.087*8,-0.087*4,0,0.087*4,0.087*8,0.087*12,0.087*16,1.74,2.172,3.,3.5,4.,4.5,5.};
  //histoEt2D=new TH2D("hCaloRegion","histo EtCaloRegion vs Eta,Phi",18,0,6.283,22,ybins);
  //histoEtvsEta=new TH1D("hCaloRegion2","histo EtCaloRegion vs Eta",22,ybins);
  //histoEtvsPhi=new TH1D("hCaloRegion3","histo EtCaloRegion vs Phi",18,0,6.283);
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
   //currentEtaBranch->GetEntry(entry);
   currentEtBranch->GetEntry(entry);
   //currentPhiBranch->GetEntry(entry);
   currentEtaIndexBranch->GetEntry(entry);
   currentPhiIndexBranch->GetEntry(entry);
   currentTauBranch->GetEntry(entry);

   if (eventnumber%1000==0) cout<<eventnumber<<endl;
   eventnumber++;

   int mapEt[22][18];
   int mapTau[22][18];

   int mapCluster[22][18];
   int mapClusterTau[22][18];

   int tfJetEt[40];
   int tfJetEtaIndex[40];
   int tfJetPhiIndex[40];
   fJetNumber=0;

   int tcJetEt[80];
   int tcJetEtaIndex[80];
   int tcJetPhiIndex[80];
   cJetNumber=0;

   int tTauEt[120];
   int tTauEtaIndex[120];
   int tTauPhiIndex[120];
   TauNumber=0;

   int istheretau=0;
   for(int i=0;i<396;i++){
     //histoEt2D->Fill(currentPhi[i],currentEta[i],currentEt[i]);
     //histoEtvsEta->Fill(currentEta[i],currentEt[i]);
     //histoEtvsPhi->Fill(currentPhi[i],currentEt[i]);
     mapEt[currentEtaIndex[i]][currentPhiIndex[i]]=currentEt[i];
     mapTau[currentEtaIndex[i]][currentPhiIndex[i]]=currentTau[i];
     //cout<<currentTau[i]<<" ";
     if (currentTau[i]) istheretau=1;
   }
   //cout<<endl;
   taunumber+=istheretau;

   for(int strip=0;strip<9;strip++){
      for(int i=0;i<2;i++){
         for(int j=0;j<22;j++){
            //cout<<mapEt[j][2*strip+i]<<"  ";
            if ((j>0)&&(j<21)){
	      if((mapEt[j][2*strip+i]>mapEt[j+1][2*strip+i])&&
                  (mapEt[j][2*strip+i]>=mapEt[j-1][2*strip+i])&&
                  ((mapEt[j][2*strip+i]>mapEt[j][2*strip+(i?0:1)])||((i==0)&&(mapEt[j][2*strip+0]==mapEt[j][2*strip+1])))&&
                  (mapEt[j][2*strip+i]>mapEt[j+1][2*strip+(i?0:1)])&&
                  (mapEt[j][2*strip+i]>=mapEt[j-1][2*strip+(i?0:1)])){
                     mapCluster[j][2*strip+i]=mapEt[j][2*strip+i]+mapEt[j+1][2*strip+i]+mapEt[j-1][2*strip+i]+
                                                      mapEt[j][2*strip+(i?0:1)]+mapEt[j+1][2*strip+(i?0:1)]+mapEt[j-1][2*strip+(i?0:1)];
                     //cout<<mapCluster[j][2*strip+i]<<"[]";
                    mapClusterTau[j][2*strip+i]=mapTau[j][2*strip+i]+mapTau[j+1][2*strip+i]+
mapTau[j-1][2*strip+i]+mapTau[j][2*strip+(i?0:1)]+mapTau[j+1][2*strip+(i?0:1)]+mapTau[j-1][2*strip+(i?0:1)]; }
               else {
                  mapCluster[j][2*strip+i]=0;
                  //cout<<mapCluster[j][2*strip+i]<<"[0]";
               }
            }

            if (j==0){
               if((mapEt[j][2*strip+i]>mapEt[j+1][2*strip+i])&&
                  ((mapEt[j][2*strip+i]>mapEt[j][2*strip+(i?0:1)])||((i==0)&&(mapEt[j][2*strip+0]==mapEt[j][2*strip+1])))&&
                  (mapEt[j][2*strip+i]>mapEt[j+1][2*strip+(i?0:1)])){
                     mapCluster[j][2*strip+i]=mapEt[j][2*strip+i]+mapEt[j+1][2*strip+i]+
mapEt[j][2*strip+(i?0:1)]+mapEt[j+1][2*strip+(i?0:1)];
                     //cout<<mapCluster[j][2*strip+i]<<"[]";
                     mapClusterTau[j][2*strip+i]=mapTau[j][2*strip+i]+mapTau[j+1][2*strip+i]+
mapTau[j][2*strip+(i?0:1)]+mapTau[j+1][2*strip+(i?0:1)];}
               else{
                  mapCluster[j][2*strip+i]=0;
                  //cout<<mapCluster[j][2*strip+i]<<"[0]";
               }
            }
            if(j==21){
               if ((mapEt[j][2*strip+i]>=mapEt[j-1][2*strip+i])&&
                  ((mapEt[j][2*strip+i]>mapEt[j][2*strip+(i?0:1)])||((i==0)&&(mapEt[j][2*strip+0]==mapEt[j][2*strip+1])))&&
                  (mapEt[j][2*strip+i]>=mapEt[j-1][2*strip+(i?0:1)])){
                     mapCluster[j][2*strip+i]=mapEt[j][2*strip+i]+mapEt[j-1][2*strip+i]+
mapEt[j][2*strip+(i?0:1)]+mapEt[j-1][2*strip+(i?0:1)];
                     //cout<<mapCluster[j][2*strip+i]<<"[]";
                     mapClusterTau[j][2*strip+i]=mapTau[j][2*strip+i]+mapTau[j-1][2*strip+i]+
mapTau[j][2*strip+(i?0:1)]+mapTau[j-1][2*strip+(i?0:1)];}
               else{
                  mapCluster[j][2*strip+i]=0;
                  //cout<<mapCluster[j][2*strip+i]<<"[0]";
               }
            }
	    //keep only the HB/HE jets
            if ((j<=4)||(j>=17)) mapCluster[j][2*strip+i]=0;
         }
      }
   }


   for(int i=0;i<18;i++) for(int j=0;j<22;j++){
      //cout<<mapCluster[j][i]<<" ";
      if (mapCluster[j][i]){
         int tempi=i+(i%2?1:-1);
         if (tempi>17) tempi=tempi-18;
         if (tempi<0)  tempi=tempi+18;
         if((j>0)&&(j<21)){
            if(((mapCluster[j][i]>mapCluster[j][tempi])||((i%2==0)&&(mapCluster[j][tempi]==mapCluster[j][i])))&&((mapCluster[j][i]>mapCluster[j+1][tempi])||((i%2==0)&&(mapCluster[j+1][tempi]==mapCluster[j][i])))&&((mapCluster[j][i]>mapCluster[j-1][tempi])||((i%2==0)&&(mapCluster[j-1][tempi]==mapCluster[j][i])))){
               mapCluster[j][i]+=mapEt[j][tempi]+mapEt[j+1][tempi]+mapEt[j-1][tempi];
               mapClusterTau[j][i]+=mapTau[j][tempi]+mapTau[j+1][tempi]+mapTau[j-1][tempi];
//               if(mapClusterTau[j][i]){
                  if((j<=3)||(j>=18)){
                     tfJetEt[fJetNumber]=mapCluster[j][i];
                     tfJetEtaIndex[fJetNumber]=j;
                     tfJetPhiIndex[fJetNumber]=i;
                     fJetNumber++;
                  }
                  else{
                    tcJetEt[cJetNumber]=mapCluster[j][i];
                    tcJetEtaIndex[cJetNumber]=j;
                    tcJetPhiIndex[cJetNumber]=i;
                    cJetNumber++;
                  }
//               }
            }
         }
         if (j==0){
            if(((mapCluster[j][i]>mapCluster[j][tempi])||((i%2==0)&&(mapCluster[j][tempi]==mapCluster[j][i])))&&((mapCluster[j][i]>mapCluster[j+1][tempi])||((i%2==0)&&(mapCluster[j+1][tempi]==mapCluster[j][i])))){
               mapCluster[j][i]+=mapEt[j][tempi]+mapEt[j+1][tempi];
               mapClusterTau[j][i]+=mapTau[j][tempi]+mapTau[j+1][tempi];
//               if(mapClusterTau[j][i]){
                  tfJetEt[fJetNumber]=mapCluster[j][i];
                  tfJetEtaIndex[fJetNumber]=j;
                  tfJetPhiIndex[fJetNumber]=i;
                  fJetNumber++;
//               }
            }
         }
         if (j==21){
            if(((mapCluster[j][i]>mapCluster[j][tempi])||((i%2==0)&&(mapCluster[j][tempi]==mapCluster[j][i])))&&((mapCluster[j][i]>mapCluster[j-1][tempi])||((i%2==0)&&(mapCluster[j-1][tempi]==mapCluster[j][i])))){
               mapCluster[j][i]+=mapEt[j][tempi]+mapEt[j-1][tempi];
               mapClusterTau[j][i]+=mapTau[j][tempi]+mapTau[j-1][tempi];
//               if(mapClusterTau[j][i]){
                  tfJetEt[fJetNumber]=mapCluster[j][i];
                  tfJetEtaIndex[fJetNumber]=j;
                  tfJetPhiIndex[fJetNumber]=i;
                  fJetNumber++;
//               }
            }
         }
      }
   }

   //cout<<endl;

   int i;
   int nfJetEt[40];
   int nfJetEtaIndex[40];
   int nfJetPhiIndex[40];

   int ncJetEt[80];
   int ncJetEtaIndex[80];
   int ncJetPhiIndex[80];
 //sort the jets
 for(i=0;i<fJetNumber;i++){
      int max=0,maxj=0;
      for(int j=0;j<fJetNumber;j++) if (tfJetEt[j]>max){
         max=tfJetEt[j];
         maxj=j;
      }
      tfJetEt[maxj]=0;
      nfJetEt[i]=max;
      nfJetEtaIndex[i]=tfJetEtaIndex[maxj];
      nfJetPhiIndex[i]=tfJetPhiIndex[maxj];
      //cout<<max<<"  ";
   }
   //put the empty jets to -400
   for(int j=i;j<40;j++){
      nfJetEt[j]=-400;
      nfJetEtaIndex[j]=-10;
      nfJetPhiIndex[j]=-10;
   }
   //select the 4 highest jets
   for(i=0;i<4;i++){
      fJetEt[i]=nfJetEt[i];
      fJetEtaIndex[i]=nfJetEtaIndex[i];
      fJetPhiIndex[i]=nfJetPhiIndex[i];
   }

   //select only the highest jet
   for(i=1;i<4;i++){
     fJetEt[i]=-400;
     fJetEtaIndex[i]=-10;
     fJetPhiIndex[i]=-10;
   }

   //idem for central jets
   for(i=0;i<cJetNumber;i++){
      int max=0,maxj=0;
      for(int j=0;j<cJetNumber;j++) if (tcJetEt[j]>max){
         max=tcJetEt[j];
         maxj=j;
      }
      tcJetEt[maxj]=0;
      ncJetEt[i]=max;
      ncJetEtaIndex[i]=tcJetEtaIndex[maxj];
      ncJetPhiIndex[i]=tcJetPhiIndex[maxj];
      //cout<<max<<"  ";
   }
   for(int j=i;j<80;j++){
      ncJetEt[j]=-400;
      ncJetEtaIndex[j]=-10;
      ncJetPhiIndex[j]=-10;
   }
   for(i=0;i<4;i++){
      cJetEt[i]=ncJetEt[i];
      cJetEtaIndex[i]=ncJetEtaIndex[i];
      cJetPhiIndex[i]=ncJetPhiIndex[i];
   }

   //select only the highest jet
   for(i=1;i<4;i++){
     cJetEt[i]=-400;
     cJetEtaIndex[i]=-10;
     cJetPhiIndex[i]=-10;
   }



/*   for(i=0;i<4;i++){
      if(i==TauNumber) break;
      int max=0,maxj=0;
      for(int j=0;j<TauNumber;j++) if (tTauEt[j]>max){
         max=tTauEt[j];
         maxj=j;
      }
      tTauEt[maxj]=0;
      TauEt[i]=max;
      TauEtaIndex[i]=tTauEtaIndex[maxj];
      TauPhiIndex[i]=tTauPhiIndex[maxj];
      //cout<<max<<"  ";
   }
   for(int j=i;j<4;j++){
      TauEt[j]=-1000;
      TauEtaIndex[j]=-1000;
      TauPhiIndex[j]=-1000;
      avoid++;
   }
*/
   //cout<<avoid<<" ";
   //cout<<endl<<endl;

   //subtract median :
   for(i=0;i<4;i++) if(cJetEt[i]>0)
      cJetEt[i]-=ncJetEt[cJetNumber/2];

   for(i=0;i<4;i++) if(fJetEt[i]>0)
      fJetEt[i]-=nfJetEt[fJetNumber/2];

   if((fJetEt[0]>40)||(cJetEt[0]>40)) acceptednumber++;

   fJetEtBranch->Fill();
   fJetEtaIndexBranch->Fill();
   fJetPhiIndexBranch->Fill();
   fJetNumberBranch->Fill();

   cJetEtBranch->Fill();
   cJetEtaIndexBranch->Fill();
   cJetPhiIndexBranch->Fill();
   cJetNumberBranch->Fill();

   TauEtBranch->Fill();
   TauEtaIndexBranch->Fill();
   TauPhiIndexBranch->Fill();
   TauNumberBranch->Fill();

//   cout<<"Fill : OK"<<endl;

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

  std::cout<<((float) acceptednumber)/(eventnumber)<<" "<<eventnumber<<" "<<acceptednumber<<" "<<taunumber<<std::endl;
}
