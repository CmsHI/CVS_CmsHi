#define TriggerPrimitivesTree_cxx
#include "TriggerPrimitivesTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <stdlib.h>
#include "TMath.h"
#include <fstream>
#include <iostream>
#include <TGraph.h>
#include <TLatex.h>
#include <TProfile.h>

// int compare (float a, float b)
// {
  // return Max(a,b)
// }
 
TH1* TriggerPrimitivesTree::Loop()
// TH2* TriggerPrimitivesTree::Loop()
// void TriggerPrimitivesTree::Loop()
{
   // if (fChain == 0) return;

   // int nentries = fChain->GetEntriesFast();
   int nentries=856;
   int nbytes = 0, nb = 0;
   // ofstream myfile;
   // myfile.open ("indices-corr.txt");
   
   // TH2D *Mean_eta = new TH2D("MeanEtCent","Mean Et distribution for central events;#eta;<Et>_{event}; ",88,0,88,30,0,30);
   // TH2D *Mean_eta = new TH2D("MeanEtMB","Mean Et distribution for minimum bias events;#eta;<Et>_{event}; ",88,0,88,30,0,30);
   // TH2D *Mean_eta = new TH2D("MeanEtJet","Mean Et distribution for jet events;#eta;<Et>_{event}; ",88,0,88,30,0,30);
   // TH2D *Mean_eta = new TH2D("MeanEtCent_z","Mean Et distribution for central events (Et<5);#eta;<Et>_{event}; ",88,0,88,30,0,5);
   // TH2D *Mean_eta = new TH2D("MeanEtMB_z","Mean Et distribution for minimum bias events (Et<5);#eta;<Et>_{event}; ",88,0,88,30,0,5);
   // TH2D *Mean_eta = new TH2D("MeanEtJet_z","Mean Et distribution for jet events (Et<5);#eta;<Et>_{event}; ",88,0,88,30,0,5);
   // TH2D *Mean_eta = new TH2D("Mean Et distribution","Mean Et distribution for jet events;#eta;<Et>_{event}; ",88,0,88,30,0,5);
   TH2D *Jetlocation = new TH2D("Jet location","The location of leading jet;#eta;#phi; ",22,0,22,18,0,18);
   for (int threshind=0; threshind<1; threshind++){//loops over threshold energies
   // for (int threshind=0; (Ethreshlow+threshind*epsilon)<Ethreshhigh; threshind++){//loops over threshold energies

   // TH2D *ETot = new TH2D("ETot","Total Energy;#eta;#phi; ",88,0,88,72,0,72);
   
   int njetevent=0;
   for (int jentry= 855; jentry<nentries;jentry++) {
      int ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      cout<<jentry<<endl;
      //Construct energy matrix
      float ETot_original[88][72];
      float ETot_subtracted[88][72];
      float ECaloRegion_before[22][18];
      float ECaloRegion_after[22][18];
      // TH2D *ETot = new TH2D("ETot","Total Energy;#eta;#phi; ",88,0,88,72,0,72);
      // TH2D *ECalReg_before = new TH2D("ECaloRegion_before","Calo Region Et before background subtraction;#eta;#phi; ",22,0,22,18,0,18);
      // TH2D *ECalReg_after = new TH2D("ECaloRegion_after","Calo Region Et after background subtraction;#eta;#phi; ",22,0,22,18,0,18);
      // TH2D *ETotBkgrnd = new TH2D("ETotBkgrnd","Total Energy after background subtraction;#eta;#phi; ",88,0,88,72,0,72);
      
      TH2D *Et_eta = new TH2D("Etdist","Single minbias event Et before subtraction;#eta;Et; ",22,0,22,100,0,250);
      // TH2D *Et_eta = new TH2D("Etdist","Single jet event Et after subtraction;#eta;Et; ",22,0,22,100,0,250);
      // TH2D *Et_eta = new TH2D("Etdist","Single central event Et after subtraction;#eta;Et; ",22,0,22,100,0,250);
      // TH2D *Et_eta = new TH2D("ECaloRegion_before","Tower Et before background subtraction;#eta;Et; ",88,0,88,100,0,30);
      
      //------Fills in the phi-eta matrix for total Et values using eta and phi indexes------
	    for (int i=0; i<hcalDetectorMapSize;i++){
        if(hcalEtaIndex[i]<0 && hcalEtaIndex[i]>-29){
          for (int j=0;j<ecalDetectorMapSize;j++){
            if(ecalEtaIndex[j]==hcalEtaIndex[i] && ecalPhiIndex[j]==hcalPhiIndex[i]){
              float towertotal=hcalCompressedEt[i]+ecalCompressedEt[j];
              ETot_original[hcalEtaIndex[i]+28+16][hcalPhiIndex[i]-1]=towertotal;
              break;
            }
          }
        }
        if(hcalEtaIndex[i]>0 && hcalEtaIndex[i]<29){
          for (int j=0;j<ecalDetectorMapSize;j++){
            if(ecalEtaIndex[j]==hcalEtaIndex[i] && ecalPhiIndex[j]==hcalPhiIndex[i]){
              float towertotal=hcalCompressedEt[i]+ecalCompressedEt[j];
              ETot_original[hcalEtaIndex[i]+27+16][hcalPhiIndex[i]-1]=towertotal;              
              break;
            }
          }
        }
        if (hcalEtaIndex[i]<-28){
          for (int k=0; k<4; k++){
            for (int l=0; l<4; l++){
              float towertotal=hcalCompressedEt[i]/16.0;
                ETot_original[(hcalEtaIndex[i]+32)*4+k][hcalPhiIndex[i]-1+l]=towertotal;     
            }
          }
        }
        if (hcalEtaIndex[i]>28){
          for (int k=0; k<4; k++){
            for (int l=0; l<4; l++){
              float towertotal=hcalCompressedEt[i]/16.0;
              ETot_original[(hcalEtaIndex[i]-29)*4+72+k][hcalPhiIndex[i]-1+l]=towertotal; 
            }
          }        
        }
      }  
      
      //--------Calculation of mean and histogram fill for the original energies-----------
      for(int i=0; i<88; i++){
        float sum=0;
        int n=0;
        //mean
        for(int j=0; j<72; j++){
            sum= sum + ETot_original[i][j];
          // ETot->Fill(i,j,ETot_original[i][j]);
          // Et_eta->Fill(i,ETot_original[i][j],1);
        }
        float mean=sum/72;
        // Mean_eta->Fill(i,mean,1);

        
        // -------------Calculation of dispersion---------------------------------------------
        float dispersion=0;
        for(int j=0; j<72; j++){
          // if(ETot_original[i][j]<(2*mean)){//2nd iteration to reject the jets from the background
            dispersion= dispersion+sqrt((ETot_original[i][j]-mean)*(ETot_original[i][j]-mean));
          // }
        }
        // dispersion=dispersion/n;//for 2nd iteration
        dispersion=dispersion/72;
        
        //-----Background subtraction and histogram fill for background subtracted energies----
        for(int j=0; j<72; j++){
          ETot_subtracted[i][j]=ETot_original[i][j]-mean-dispersion;
          if(ETot_subtracted[i][j] < 0){
            ETot_subtracted[i][j]=0;
          }
          // ETotBkgrnd->Fill(i,j,ETot_subtracted[i][j]);
          // Et_eta->Fill(i,ETot_subtracted[i][j],1);
        }
      }
      

      
      //----Construction of caloregions before and after the background subtraction --------
      float max=0;
	  int maxi;
	  int maxj;
      for(int i=0; i<22;i++){
        for(int j=0; j<18;j++){
          float sumtowers1=0;
          float sumtowers2=0;
          for(int k=0; k<4;k++){
            for(int l=0;l<4;l++){
              sumtowers1=sumtowers1+ETot_original[i*4+k][j*4+l];
              sumtowers2=sumtowers2+ETot_subtracted[i*4+k][j*4+l];
            }
          }
          ECaloRegion_before[i][j]=sumtowers1;
          ECaloRegion_after[i][j]=sumtowers2;
          if(sumtowers2>max){
            max=sumtowers2;
			maxi=i;
			maxj=j;
          }
          // if(sumtowers1>max){
            // max=sumtowers1;
          // }
          
          // ECalReg_before->Fill(i,j,ECaloRegion_before[i][j]);
          // ECalReg_after->Fill(i,j,ECaloRegion_after[i][j]);
          Et_eta->Fill(i,ECaloRegion_before[i][j],1);
          // Et_eta->Fill(i,ECaloRegion_after[i][j],1);
        }
      }
	  
      Jetlocation->Fill(maxi,maxj,1);
	  
      //------Sliding window to calculate the total energy at 3x3 calo regions-------------
      for(int i=0;i<20;i++){
        for(int j=0;j<16;j++){
        float sumcalos=0;
          for (int k=0; k<3;k++){
            for (int l=0; l<3;l++){
              // sumcalos=sumcalos+ECaloRegion_before[i+l][j+k];
              sumcalos=sumcalos+ECaloRegion_after[i+l][j+k];
            }
          }
          // if (sumcalos>max){
            // max=sumcalos;
          // }
        }
      }
      
      
      //To see which jet events fail
      // if(max<(Ethreshlow+threshind*epsilon)){
        // TCanvas *c1=new TCanvas("c1","",800,600);
        // ECalReg_before->Draw("Lego2");
        // c1->SaveAs(Form("ECaloRegion_before_%d.png",jentry));
        // c1->Delete();
      // }
      
      // TCanvas *c1=new TCanvas("c1","",800,600);
      TCanvas *c1=new TCanvas("c1","",600,600);
      // ETot->Draw("Lego2");
      // ETotBkgrnd->Draw("Lego2");
      // ECalReg_before->Draw("Lego2");
      // ECalReg_after->Draw("Lego2");
      
      Et_eta->Draw("Box2");
      return Et_eta;
      // c1->SaveAs("EtEta_mb_before.png");
      // c1->SaveAs("EtEta_jet_before.png");
      // c1->SaveAs("EtEta_cent_before.png");
      // c1->SaveAs("EtEta_mb_after.png");
      // c1->SaveAs("EtEta_jet_after.png");
      c1->SaveAs("EtEta_cent_after.png");
      
      // c1->SaveAs("ETot.png");
      // c1->SaveAs("ETot_bkg.png");
      // c1->SaveAs("ETot_bkg_sumall.png");
      // c1->SaveAs("ECaloRegion_before.png");
      // c1->SaveAs("ECaloRegion_after-disp.png");
      // c1->SaveAs("ECaloRegion_after_sumallbkgsubt.png");
      

   // cout<<njetevent<<endl;
   
     //calculation for average tower energy 

   
   }

   // myfile.close();
   }
   // TCanvas *c1=new TCanvas("c1","",800,600);
   // Jetlocation->Draw("Lego2");
   // Mean_eta->Draw("Box2");
   // return Mean_eta;
   // c1->SaveAs("MeanEt_box.png");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// void TriggerPrimitivesTree::Loop2()
// TH1* TriggerPrimitivesTree::Loop2()
TH2* TriggerPrimitivesTree::Loop2()
{
   // if (fChain == 0) return;

   int nentries = fChain->GetEntriesFast();
   // int nentries=3000;
   int nbytes = 0, nb = 0;
   // ofstream myfile;
   // myfile.open ("indices-corr.txt");
   
   
   float Ethreshlow=0;
   float Ethreshhigh=101;
   float epsilon=10;
   // TH1D *LargestEt = new TH1D("LargestEt","Largest Jet Et distribution for minimum bias with subtraction;Compressed Et;dN/d(Et) ",1000,0,500);
   // TH1D *LargestEt = new TH1D("LargestEt","Largest Jet Et distribution for jets with subtraction;Compressed Et;dN/d(Et) ",1000,0,500);
   TH1D *LargestEt = new TH1D("LargestEt","Largest Jet Et distribution for central with subtraction;Compressed Et;dN/d(Et) ",1000,0,500);
   // TH1D *LargestEt = new TH1D("LargestEt","Largest Jet Et number distribution for minbias with subtraction;CompressedEt; ",100,0,1500);
   // TH1D *LargestEt = new TH1D("LargestEt","Largest Jet Et number distribution for jets without subtraction;CompressedEt; ",100,0,500);
   // TH1D *LargestEt = new TH1D("LargestEt","Largest Jet Et number distribution for jets with subtraction;CompressedEt; ",100,0,1500);
   // TH1D *LargestEt = new TH1D("LargestEt","Largest Jet Et number distribution for central without subtraction;CompressedEt; ",100,0,1500);
   // TH1D *LargestEt = new TH1D("LargestEt","Largest Jet Et number distribution for central with subtraction;CompressedEt; ",100,0,1500);
   // TH2D *Mean_eta = new TH2D("Mean Et distribution","Mean Et distribution for each eta strip;#eta;Et; ",22,0,88,18,0,5);
   Float_t jetpercent[11], Ecut[11];
   
   TH1D *jetptbefore = new TH1D("jetptbefore","Pt before;jetpt",100,0,500);
   TH2D *jetpteta_b = new TH2D("jetptbefore","pp Jet Data;Leading jet pt(GeV);Leading jet #eta",100,0,350,100,-4,4);
   TH1D *jetptafter = new TH1D("jetptafter","Pt after;jetpt",100,0,500);
   TH2D *jetpteta_a = new TH2D("jetptafter","pp Jet events that pass L1;Leading jet pt(GeV);Leading jet #eta",100,0,350,100,-4,4);
   TH2D *leadingE_cent = new TH2D("JetEt_cent","Turn On Curve for Jet Data;jetpt;IsGood",50,0,350,2,-0.5,1.5);
   TH2D *leadingE_peri = new TH2D("JetEt_peri","Turn On Curve for Jet Data;jetpt;IsGood",50,0,350,2,-0.5,1.5);
   
   int nfill=0;
   int npcoll=0;  
   int npass=0;  
   for (int threshind=0; threshind<1; threshind++){//loops over threshold energies
   // for (int threshind=0; (Ethreshlow+threshind*epsilon)<Ethreshhigh; threshind++){//loops over threshold energies
   // TH2D *ECalReg_before = new TH2D("ECaloRegion_before","Calo Region Et before background subtraction;#eta;#phi; ",22,0,22,18,0,18);
   // TH2D *ETot = new TH2D("ETot","Total Energy;#eta;#phi; ",88,0,88,72,0,72);
   cout<<threshind<<endl;
   int njetevent=0;
   
 
  
   for (int jentry=0; jentry<nentries;jentry++) {
   

      
      int ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      fjet->GetEntry(jentry);
	    fhlt->GetEntry(jentry);
      fhiinfo->GetEntry(jentry);
      fmu->GetEntry(jentry);
      // if (Cut(ientry) < 0) continue;
       
	    if( !(!(fhlt->L1Tech_BSC_halo_beam2_inner_v0 || fhlt->L1Tech_BSC_halo_beam2_outer_v0 || fhlt->L1Tech_BSC_halo_beam1_inner_v0 || fhlt->L1Tech_BSC_halo_beam1_outer_v0 ) && fhiinfo->hiNtracks>0 && fhiinfo->hiHFplus>1 && fhiinfo->hiHFminus>1))
	    // if( !(fhiinfo->hiNtracks>0 && fhiinfo->hiHFplus>0 && fhiinfo->hiHFminus>0))
      continue;
      npcoll++;
      
       
      //Construct energy matrix
      float ETot_original[88][72];
      float ETot_subtracted[88][72];
      float ECaloRegion_before[22][18];
      float ECaloRegion_after[22][18];
      // TH2D *ETot = new TH2D("ETot","Total Energy;#eta;#phi; ",88,0,88,72,0,72);
      // TH2D *ECalReg_before = new TH2D("ECaloRegion_before","Calo Region Et before background subtraction;#eta;#phi; ",22,0,22,18,0,18);
      // TH2D *ECalReg_after = new TH2D("ECaloRegion_after","Calo Region Et after background subtraction;#eta;#phi; ",22,0,22,18,0,18);
      // TH2D *ETotBkgrnd = new TH2D("ETotBkgrnd","Total Energy after background subtraction;#eta;#phi; ",88,0,88,72,0,72);
      
      
      //------Fills in the phi-eta matrix for total Et values using eta and phi indexes------
	    for (int i=0; i<hcalDetectorMapSize;i++){
        if(hcalEtaIndex[i]<0 && hcalEtaIndex[i]>-29){
          for (int j=0;j<ecalDetectorMapSize;j++){
            if(ecalEtaIndex[j]==hcalEtaIndex[i] && ecalPhiIndex[j]==hcalPhiIndex[i]){
              float towertotal=hcalCompressedEt[i]+ecalCompressedEt[j];
              ETot_original[hcalEtaIndex[i]+28+16][hcalPhiIndex[i]-1]=towertotal;
              break;
            }
          }
        }
        if(hcalEtaIndex[i]>0 && hcalEtaIndex[i]<29){
          for (int j=0;j<ecalDetectorMapSize;j++){
            if(ecalEtaIndex[j]==hcalEtaIndex[i] && ecalPhiIndex[j]==hcalPhiIndex[i]){
              float towertotal=hcalCompressedEt[i]+ecalCompressedEt[j];
              ETot_original[hcalEtaIndex[i]+27+16][hcalPhiIndex[i]-1]=towertotal;              
              break;
            }
          }
        }
        if (hcalEtaIndex[i]<-28){
          for (int k=0; k<4; k++){
            for (int l=0; l<4; l++){
              float towertotal=hcalCompressedEt[i]/16;
                ETot_original[(hcalEtaIndex[i]+32)*4+k][hcalPhiIndex[i]-1+l]=towertotal;     
            }
          }
        }
        if (hcalEtaIndex[i]>28){
          for (int k=0; k<4; k++){
            for (int l=0; l<4; l++){
              float towertotal=hcalCompressedEt[i]/16;
              ETot_original[(hcalEtaIndex[i]-29)*4+72+k][hcalPhiIndex[i]-1+l]=towertotal; 
            }
          }        
        }
      }  
      
      
      //--------Calculation of mean and histogram fill for the original energies-----------
      for(int i=0; i<88; i++){
        float sum=0;
        int n=0;
        //mean
        for(int j=0; j<72; j++){
            sum= sum + ETot_original[i][j];
          // ETot->Fill(i,j,ETot_original[i][j]);
        }
        float mean=sum/72;
        // Mean_eta->Fill(i,mean,1);
        // if (mean<0.001){
          // cout<<mean<<"  eta= "<< i<<endl;
        // }
        
        //2nd iteration
        // float sum2=0;
        // for (int j=0; j<72; j++){
          // if(ETot_original[i][j]<(mean*2)){
            // sum2=sum2+ETot_original[i][j];
            // n++;
          // }
        // }
        // mean=sum2/n;
      
        // -------------Calculation of dispersion---------------------------------------------
        float dispersion=0;
        for(int j=0; j<72; j++){
          // if(ETot_original[i][j]<(2*mean)){//2nd iteration to reject the jets from the background
            dispersion= dispersion+sqrt((ETot_original[i][j]-mean)*(ETot_original[i][j]-mean));
          // }
        }
        // dispersion=dispersion/n;//for 2nd iteration
        dispersion=dispersion/72;
        
        //-----Background subtraction and histogram fill for background subtracted energies----
        for(int j=0; j<72; j++){
          ETot_subtracted[i][j]=ETot_original[i][j]-mean-dispersion;
          if(ETot_subtracted[i][j] < 0){
            ETot_subtracted[i][j]=0;
          }
          // ETotBkgrnd->Fill(i,j,ETot_subtracted[i][j]);
        }
      }
      

      
      //----Construction of caloregions before and after the background subtraction --------
      float max=0;
	  int maxi=0;
	  int maxj=0;
      for(int i=0; i<22;i++){
        for(int j=0; j<18;j++){
          float sumtowers1=0;
          float sumtowers2=0;
          for(int k=0; k<4;k++){
            for(int l=0;l<4;l++){
              sumtowers1=sumtowers1+ETot_original[i*4+k][j*4+l];
              sumtowers2=sumtowers2+ETot_subtracted[i*4+k][j*4+l];
            }
          }
          ECaloRegion_before[i][j]=sumtowers1;
          ECaloRegion_after[i][j]=sumtowers2;
		     // if(i==4&&j==6){
		       // sumtowers2=0;
			   // cout<<sumtowers2<<endl;
		     // }
          // if((sumtowers2>max)&& (i!=4 && j!=6)){
		     if(sumtowers2>max){
            max=sumtowers2;
			   // cout<<max<<" i "<< i << " j "<< j <<endl;
          }
		  
          // if(sumtowers1>max){
            // max=sumtowers1;
          // }
          
          // ECalReg_before->Fill(i,j,ECaloRegion_before[i][j]);
          // ECalReg_after->Fill(i,j,ECaloRegion_after[i][j]);
        }
      }
      
      //------Sliding window to calculate the total energy at 3x3 calo regions-------------
      for(int i=0;i<20;i++){
        for(int j=0;j<16;j++){
        float sumcalos=0;
          for (int k=0; k<3;k++){
            for (int l=0; l<3;l++){
              // sumcalos=sumcalos+ECaloRegion_before[i+l][j+k];
              sumcalos=sumcalos+ECaloRegion_after[i+l][j+k];
            }
          }
          // if (sumcalos>max){
            // max=sumcalos;
          // }
        }
      }
      
      int pass=0;
      // if (max>295) pass=1;
      if (max>63.5) pass=1;
      cout<<"nref  "<<fjet->nref<<"pass"<<pass<<endl;
      if(pass) npass++;
	  
      // if (fjet->nref>0&& fabs(fjet->jteta[0])<2){
      if (fjet->nref>0){
        jetptbefore->Fill(fjet->jtpt[0]);
	      jetpteta_b->Fill(fjet->jtpt[0],fjet->jteta[0]);
        if(pass){ 
	        jetptafter->Fill(fjet->jtpt[0]);
          jetpteta_a->Fill(fjet->jtpt[0],fjet->jteta[0]);
	      }
        if (fhiinfo->hiBin<12){
          leadingE_cent->Fill(fjet->jtpt[0],pass);
          nfill++;
        }
        if (fhiinfo->hiBin>19){
          leadingE_peri->Fill(fjet->jtpt[0],pass);
          nfill++;
        }
        
      }
      if(max>(Ethreshlow+threshind*epsilon)){
          njetevent++;
          LargestEt->Fill(max);
          ;
      }
      
      //To see which jet events fail
      // if(max<(Ethreshlow+threshind*epsilon)){
        // TCanvas *c1=new TCanvas("c1","",800,600);
        // ECalReg_before->Draw("Lego2");
        // c1->SaveAs(Form("ECaloRegion_before_%d.png",jentry));
        // c1->Delete();
      // }
      
      // TCanvas *c1=new TCanvas("c1","",800,600);
      // ETot->Draw("Lego2");
      // ETotBkgrnd->Draw("Lego2");
      // ECalReg_before->Draw("Lego2");
      // ECalReg_after->Draw("Lego2");
      
      // c1->SaveAs("ETot.png");
      // c1->SaveAs("ETot_bkg.png");
      // c1->SaveAs("ETot_bkg_sumall.png");
      // c1->SaveAs("ECaloRegion_before.png");
      // c1->SaveAs("ECaloRegion_after-disp.png");
      // c1->SaveAs("ECaloRegion_after_sumallbkgsubt.png");
      
   // cout<<njetevent<<endl;

   }
   cout<<"I am alive"<<endl;
   jetpercent[threshind]=njetevent/30;
   // cout<<njetevent/30<<endl;
   // cout<<(Ethreshlow+threshind*epsilon)<<endl;
   Ecut[threshind]=Ethreshlow+threshind*epsilon;
   cout<<(Ethreshlow+threshind*epsilon)<< " " << (njetevent/30)<<endl;
   // myfile.close();
   }
   // TCanvas *c1=new TCanvas("c1","",800,600);
   TCanvas *c1=new TCanvas("c1","",600,600);
   // LargestEt->Draw();
   // leadingE->Draw("Box");
  
   TProfile* p2=leadingE_cent->ProfileX("p2",0,99);
   p2->SetTitle("Turn On Curve For pp Jet Data After Subtraction");
   p2->GetXaxis()->SetTitle("Leading Jet pt (GeV)");
   p2->GetXaxis()->CenterTitle();
   p2->GetYaxis()->CenterTitle();
   p2->Draw();
   TLatex* t1=new TLatex(250,0.1,"E_{thr}=63.5");
   TLatex* t2=new TLatex(220,0.2,Form("N_{event}=%i",npcoll));
   // TLatex* t3=new TLatex(250,0.3,"|#eta|<2");
   t1->SetTextSize(0.05);
   t2->SetTextSize(0.05);
   // t3->SetTextSize(0.05);
   t1->Draw();
   t2->Draw();
   // t3->Draw();
   
    /*
   jetpteta_b->Draw("colz");
   // TLatex* t2=new TLatex(200,-3.5,Form("N_{event}=%i",npass));
   TLatex* t2=new TLatex(200,-3.5,Form("N_{event}=%i",npcoll));
   t2->SetTextSize(0.05);
   t2->Draw();
   */
   
   // TGraph *Percentage = new TGraph(11,Ecut,jetpercent);
   // Percentage->Draw("AC*");
   // Percentage2->Draw("C*Same");
   // Percentage->SetTitle("Threshold Et cut vs Percentage of Minbias events(1st it-mean and dispersion)");
   // Percentage->GetXaxis()->SetTitle("Threshold energy");
   // Percentage->GetYaxis()->SetTitle("Percentage of events that pass");
   // c1->SaveAs("Percentage.png");
   
   // c1->SaveAs("Threshold0-minbias-before.png");
   // c1->SaveAs("Threshold0-minbias-after.png");
   // c1->SaveAs("Threshold0-jet-before.png");
   // c1->SaveAs("Threshold0-jet-after.png");
   // c1->SaveAs("Threshold0-central-before.png");
   // c1->SaveAs("Threshold0-central-after.png");
   // c1->SaveAs("turnoncent_after.gif");
   // c1->SaveAs("turnoncent_after.png");
   c1->SaveAs("jetpteta_b.png");
   c1->SaveAs("jetpteta_b.gif");
   
   // Mean_eta->Draw("Lego2");
   // c1->SaveAs("Mean.png");
   // return LargestEt;
   cout<<nfill<<endl;
   cout<<"npcoll="<< npcoll<<endl;
   // return jetptbefore;
   jetptafter->Divide(jetptbefore);
   // jetptafter->Draw();
   return leadingE_peri;
   // return jetpteta_b;
}

