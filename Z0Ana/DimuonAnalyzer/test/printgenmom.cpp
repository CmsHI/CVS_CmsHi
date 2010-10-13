/*
Print out pid number of all di-muon's mothers.
*/
#include <TROOT.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <map>
#include <iostream>

using namespace std;

int printcountgen ()
{
  TFile fdat("C:\\root\\macros\\0720\\HydjetMBZ0Emb.root");
  if (fdat.IsZombie()) { cout << "cannot open data file\n"; return 1; }
  
  map<float,float> mompair;
  map<float,float>::iterator it;
  
  TNtuple *gendimu = (TNtuple*)fdat->Get("demo/pnDimuGenInfo");
  float mu1c, mu2c, mom1, mom1stat, mom2, mom2stat, dimum, dimupt;
  gendimu->SetBranchAddress("mu1pdgid",&mu1c);
  gendimu->SetBranchAddress("mu2pdgid",&mu2c);
  gendimu->SetBranchAddress("momid1_0",&mom1);
  gendimu->SetBranchAddress("momstat1_0",&mom1stat);
  gendimu->SetBranchAddress("momid2_0",&mom2);
  gendimu->SetBranchAddress("momstat2_0",&mom2stat);
  gendimu->SetBranchAddress("dimum",&dimum);
  gendimu->SetBranchAddress("dimupt",&dimupt);
  int entry = gendimu->GetEntries();
  
  for (int i=0; i<entry; i++)
  {
    gendimu->GetEntry(i);
    if (mu1c * mu2c < 0)  //only opposite sign
    {
      /*if (momid1.size() == 0)
      {
        momid1.push_back(mom1);
        cout << mom1 << " " << mom2 << endl;
      }
      if (momid2.size() == 0)
      {
        momid2.push_back(mom2);
        cout << mom1 << " " << mom2 << endl;
      }

      it = find(momid1.begin(), momid1.end(),mom1);
      if (it == momid1.end()) //new momid
        momid1.push_back(mom1);
      it = find(momid2.begin(), momid2.end(),mom2);
      if (it == momid2.end()) //new momid
        momid2.push_back(mom2);*/
      
      if (mompair.size() == 0)
        mompair.insert(pair<float,float>(mom1,mom2));
      else
      {
        it = mompair.find(mom1);
        if (it == mompair.end()) //new mom1
        {
          mompair.insert(pair<float,float>(mom1,mom2));
        }
        else  //exist mom1
        {
          if (it->second != mom2)  //but new mom2
          {
            mom1 = mom1*0.1;
            mompair.insert(pair<float,float>(mom1,mom2));
          }
        }
      }
    }
  }

  for (it = mompair.begin(); it != mompair.end(); ++it)
    cout << (*it).first << " " << (*it).second << endl;

  return 0;
}
