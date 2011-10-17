#include "hiForest.h"

void testLoop()
{
   HiForest *c = new HiForest("pbpbTest.root");
   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      cout <<"Run number = "<<c->hlt.Run<<endl;
      cout <<"Event number = "<<c->hlt.Event<<endl;
      // Loop over photons
      for (int j=0;j<c->photon.nPhotons;j++) {
         cout <<i<<"Photon "<<j<<" "<<c->photon.et[j]<<endl;
      }	 

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
   }
   delete c;
}
