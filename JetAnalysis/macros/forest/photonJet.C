#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>

void photonJet(double etCut=40)
{
   // Define the input file and HiForest
   HiForest *c = new HiForest("skim_Photon.root");

   // Don't want to loop over trees which is not used in the analysis
   c->hasHltTree=0;
   c->hasSkimTree=0;
   c->hasTrackTree=0;
   c->hasIcPu5JetTree=0;

   // Output file
   TFile *output = new TFile(Form("output-%.0f.root",etCut),"recreate");

   // Agj histograms for different centralities
   TH1D *h1 = new TH1D("h1","",100,-1,1);
   TH1D *h2 = new TH1D("h2","",100,-1,1);
   TH1D *h3 = new TH1D("h3","",100,-1,1);
   TH1D *h4 = new TH1D("h4","",100,-1,1);

   // A light Ntuple output
   TNtuple *t = new TNtuple("nt","","cBin:photonEt:photonEta:photonPhi:jetEt:jetEta:jetPhi:Agj");

   // Main loop
   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      if (i%1000==0) cout <<i<<" / "<<c->GetEntries()<<endl;

      int leadingPhoton=-1;
      int leadingJet=-1;

      // Loop over photons to look for leading photon candidate in the event
      for (int j=0;j<c->photon.nPhotons;j++) {
         if (c->photon.et[j]<etCut) break;          // photon pT cut, assuming that et is sorted
         if (fabs(c->photon.eta[j])>1.44) continue; // |eta|<1.44
         if (c->isSpike(j)) continue;               // spike removal
         if (!c->isGoodPhoton(j)) continue;         // hiGoodPhoton cut
         leadingPhoton=j;  
         break;  
      }	 

      // Found a leading photon which passed basic quality cut!
      if (leadingPhoton!=-1) {
         Float_t var[100];
         var[0]=c->photon.cBin;
         var[1]=c->photon.et[leadingPhoton];
         var[2]=c->photon.eta[leadingPhoton];
         var[3]=c->photon.phi[leadingPhoton];

         // Loop over jet tree to find a away side leading jet
         for (int j=0;j<c->akPu3PF.nref;j++) {
            if (c->akPu3PF.jtpt[j]<25) break;
            if (fabs(c->akPu3PF.jteta[j])>2) continue;
            if (fabs(deltaPhi(c->akPu3PF.jtphi[j],c->photon.phi[leadingPhoton])<2.5)) continue;
            leadingJet = j;
            break;
         }	 

         // Found a leading jet!
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
   }

   output->Write();
   output->Close();
   delete c;
}
