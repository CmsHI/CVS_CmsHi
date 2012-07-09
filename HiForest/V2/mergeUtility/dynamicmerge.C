#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <fstream>

void dynamicmerge(string infname, string outfname);


void dynamicmerge(string infname, string outfname) {

  
  string buffer;
  vector<string> listoffiles;
  int nlines = 0;
  ifstream infile(infname.data());

  if (!infile.is_open()) {
    cout << "Error opening file. Exiting." << endl;
    return;
  } else {
    while (!infile.eof()) {
      infile >> buffer;
      listoffiles.push_back(buffer);
      nlines++;
    }
  }
  
  const int N = 47;
  string dir[N] = {
    "hltanalysis",
    "skimanalysis",
    "hcalNoise",
    "icPu5JetAnalyzer",
    "akPu1PFJetAnalyzer",
    "akPu2PFJetAnalyzer",
    "akPu3PFJetAnalyzer",
    "akPu4PFJetAnalyzer",
    "akPu5PFJetAnalyzer",
    "akPu6PFJetAnalyzer",
    "akPu1CaloJetAnalyzer",
    "akPu2CaloJetAnalyzer",
    "akPu3CaloJetAnalyzer",
    "akPu4CaloJetAnalyzer",
    "akPu5CaloJetAnalyzer",
    "akPu6CaloJetAnalyzer",
    "ak1PFJetAnalyzer",
    "ak2PFJetAnalyzer",
    "ak3PFJetAnalyzer",
    "ak4PFJetAnalyzer",
    "ak5PFJetAnalyzer",
    "ak6PFJetAnalyzer",
    "ak1CaloJetAnalyzer",
    "ak2CaloJetAnalyzer",
    "ak3CaloJetAnalyzer",
    "ak4CaloJetAnalyzer",
    "ak5CaloJetAnalyzer",
    "ak6CaloJetAnalyzer",
    "multiPhotonAnalyzer",
    // "anaTrack",
    "mergedTrack",
    "pfcandAnalyzer",
    "anaMET",
    "muonTree",
    "hiEvtAnalyzer",
    "hltMuTree",
    "rechitanalyzer",
    "rechitanalyzer",
    "rechitanalyzer",
    "rechitanalyzer",
    "rechitanalyzer",
    "pfTowers",
    "pfTowers",
    "pfTowers",
    "pfTowers",
    "pfTowers",
    "HiGenParticleAna",
    "genpana"
  };

  string trees[N] = {
    "HltTree",
    "HltTree",
    "hcalNoise",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "t",
    "photon",
    // "trackTree",
    "trackTree",
    "pfTree",
    "metTree",
    "HLTMuTree",
    "HiTree",
    "HLTMuTree",
    "hbhe",
    "hf",
    "ee",
    "eb",
    "tower",
    "hbhe",
    "hf",
    "ee",
    "eb",
    "tower",
    "hi",
    "photon"
  };


  TChain* ch[N];

  for(int i = 0; i < N; ++i){
    ch[i] = new TChain(string(dir[i]+"/"+trees[i]).data());
    for(int j = 0 ; j < listoffiles.size() ; ++j)
    {
      ch[i]->Add(listoffiles[j].data());
    }

    cout<<"Tree loaded : "<<string(dir[i]+"/"+trees[i]).data()<<endl;
    cout<<"Entries : "<<ch[i]->GetEntries()<<endl;

  }


  TFile* file = new TFile(outfname.data(), "RECREATE");

  for(int i = 0; i < N; ++i){
    file->cd();
    cout <<string(dir[i]+"/"+trees[i]).data()<<endl;
    if (i==0) {
      file->mkdir(dir[i].data())->cd();
    } else {
      if (TString(dir[i].data())!=TString(dir[i-1].data()))
      file->mkdir(dir[i].data())->cd();
      else
      file->cd(dir[i].data());
    }
    ch[i]->Merge(file,0,"keep");
  }
  cout <<"Good"<<endl;
  file->Close();

}
