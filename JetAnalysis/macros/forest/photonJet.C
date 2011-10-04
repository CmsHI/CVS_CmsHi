#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>

double deltaPhi(double phi1, double phi2) {
        double dePhi = fabs(phi1 - phi2);  
        if (dePhi > 3.1415926) dePhi = 2 * 3.1415926 - dePhi;
        return dePhi;
}


void photonJet(double etCut=40)
{

   HiForest *c = new HiForest("merged_HI2010_SD_Jet35_prod05.root");
   c->hasHltTree=0;
   c->hasSkimTree=0;
   c->hasTrackTree=0;
   c->hasIcPu5JetTree=0;
   TFile *output = new TFile(Form("output-%.0f.root",etCut),"recreate");
   TH1D *h1 = new TH1D("h1","",100,-1,1);
   TH1D *h2 = new TH1D("h2","",100,-1,1);
   TH1D *h3 = new TH1D("h3","",100,-1,1);
   TH1D *h4 = new TH1D("h4","",100,-1,1);
   TNtuple *t = new TNtuple("nt","","cBin:photonEt:photonEta:photonPhi:jetEt:jetEta:jetPhi:Agj");


   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      //cout <<"Run number = "<<c->hlt.Run<<endl;
      //cout <<"Event number = "<<c->hlt.Event<<endl;
      // Loop over photons
      if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<endl;

      int leadingPhoton=-1;
      int leadingJet=-1;
      for (int j=0;j<c->photon.nPhotons;j++) {
         if (c->photon.et[j]<etCut) break;
         if (fabs(c->photon.eta[j])>1.44) continue;
         double swiss = 1-(c->photon.eRight[j]+c->photon.eLeft[j]+c->photon.eTop[j]+c->photon.eBottom[j])/c->photon.eMax[j];
         if (swiss>0.9) continue;
         if (fabs(c->photon.seedTime[j])>3) continue;
         if (c->photon.hadronicOverEm[j]>0.2) continue;
         if (c->photon.isEle[j]) continue;
         if ((c->photon.rawEnergy[j]/c->photon.energy[j])<0.5) continue;
         if (c->photon.sigmaIetaIeta[j]>0.011) continue;
         if ((c->photon.cr4[j]+c->photon.cc4[j]+c->photon.ct4PtCut[j])>5) continue;
         if (c->photon.sigmaIetaIeta[j]<0.002) continue;
         if (c->photon.sigmaIphiIphi[j]<0.002) continue;
         leadingPhoton=j;  
         break;  
      }	 

      if (leadingPhoton!=-1) {
         Float_t var[100];
         var[0]=c->photon.cBin;
         var[1]=c->photon.et[leadingPhoton];
         var[2]=c->photon.eta[leadingPhoton];
         var[3]=c->photon.phi[leadingPhoton];
         for (int j=0;j<c->akPu3PF.nref;j++) {
            if (c->akPu3PF.jtpt[j]<25) break;
            if (fabs(c->akPu3PF.jteta[j])>2) continue;
            if (deltaPhi(c->akPu3PF.jtphi[j],c->photon.phi[leadingPhoton])<2.5) continue;
            leadingJet = j;
            break;
         }	 
         if (leadingJet !=-1) {
            double photonEt = c->photon.et[leadingPhoton];
            double jetPt = c->akPu3PF.jtpt[leadingJet];
            double Agj = (photonEt-jetPt)/(photonEt+jetPt);
            if (c->photon.cBin<4) h1->Fill(Agj);
            if (c->photon.cBin>=4&&c->photon.cBin<12) h2->Fill(Agj);
            if (c->photon.cBin>=12&&c->photon.cBin<20) h3->Fill(Agj);
            if (c->photon.cBin>=20) h4->Fill(Agj);
            var[4]=jetPt;
            var[5]=c->akPu3PF.jteta[leadingJet];
            var[6]=c->akPu3PF.jtphi[leadingJet];
            var[7]=Agj;
         } else {
            var[4]=0;
            var[5]=0;
            var[6]=0;
            var[7]=1;

         }
         t->Fill(var);
      }

/*
      // Loop over icPu5 jets
      for (int j=0;j<c->icPu5.nref;j++) {
         cout <<i<<"IcPu5Jet "<<j<<" "<<c->icPu5.jtpt[j]<<endl;
      }	 

      // Loop over akPu3PF jets
      for (int j=0;j<c->akPu3PF.nref;j++) {
         cout <<i<<"AkPu3PFJet "<<j<<" "<<c->akPu3PF.jtpt[j]<<endl;
      }	 

      // Loop over tracks
      for (int j=0;j<c->track.nTrk;j++) {
         cout <<i<<"Track "<<j<<" "<<c->track.trkPt[j]<<endl;
      }	 


      cout <<"icPu5 leading jet "<<c->icPu5.jtpt[0]<<endl;	 
      cout <<"akPu3PF leading jet "<<c->akPu3PF.jtpt[0]<<endl;	 
*/
   }

   output->Write();
   output->Close();
   delete c;
}
