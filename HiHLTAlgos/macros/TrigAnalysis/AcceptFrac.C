#include <TGraphAsymmErrors.h>
#include <TFile.h>
#include <TTree.h>
#include "TChain.h"
#include <TH1F.h>
#include <TCut.h>
#include <TLegend.h>
#include <TLine.h>;;
#include <TCanvas.h>
#include <iostream>

#include "commonUtility.h"
#include "tgraphTools.C"

using namespace std;



TChain * AcceptFrac(TString infile="alldatacleaned.root")
//(TString infile="alldatacleaned.root")
//(TString infile="/net/hidsk0001/d00/scratch/frankma/data/HAZS/hazsv2-run152791to152957-unfiltered-jetoh-v1/merge/all.root")
//(TString infile="/net/hidsk0001/d00/scratch/frankma/data/HAZS/hazsv2-run152791to152957-unfiltered-jetoh-v1/merge/all.root")
{ 
  TChain * tree = new TChain("hltanalysis/HltTree");
  tree->Add(infile);
  tree->AddFriend("icPu5JetAnalyzerRelVal/t",infile);
  cout << "Total: " << tree->GetEntries() << endl;

  TCut evtSel("Run==152957&&HLT_HIMinBiasHfOrBSC&&hiBin<40&&abs(jteta[0])<2");

  // cout << "Raw Higher than 35: " << tree->GetEntries(evtSel&&"rawpt[0]>35") << endl;
  // cout << "Jt  Higher than 35: " << tree->GetEntries(evtSel&&"jtpt[0]>35") << endl;
  // cout << "Just Jet 35 U: " << tree->GetEntries(evtSel&&"HLT_HIJet35U") << endl;
  // cout << " Raw & Jet 35 U: " << tree->GetEntries(evtSel&&"rawpt[0]>35"&&"HLT_HIJet35U") << endl;
  // cout << " & Jet 50 U: " << tree->GetEntries(evtSel&&"jtpt[0]>60"&&"HLT_HIJet50U") << endl;
  //  cout << " & Jet 75 U: " << tree->GetEntries(evtSel&&"jtpt[0]>60"&&"HLT_HIJet75U") << endl;
  //	cout << "consitency check: " << tree->GetEntries(evtSel&&"jtpt[0]>60"&&"HLT_HIJet75U"&&"HLT_HIJet50U") << endl;
	
   TH1F * h4 = new TH1F("h4","",50,0,300);
  TH1F * h5 = new TH1F("h5","",50,0,300);
  TH1F * h6 = new TH1F("h6","",50,0,300);
   TH1F * h7 = new TH1F("h7","",50,0,300);
  // TH1F * h8 = new TH1F("h8","",50,0,300);
  // TH1F * h9 = new TH1F("h9","",50,0,300);
  // TH1F * h10 = new TH1F("h10","",50,0,300);
  // TH1F * h11 = new TH1F("h11","",50,0,300);
  // TH1F * h12 = new TH1F("h12","",50,0,300);
  // TH1F * h13 = new TH1F("h13","",50,0,300);
  // TH1F * h14 = new TH1F("h14","",50,0,300);
  // TH1F * h15 = new TH1F("h15","",50,0,300);
  // TH1F * h16 = new TH1F("h16","",50,0,300);
  // TH1F * h17 = new TH1F("h17","",50,0,300);
  // TH1F * h18 = new TH1F("h18","",50,0,300);
  // TH1F * h19 = new TH1F("h19","",50,0,300);

   TCanvas * y1 = new TCanvas("y1","y1", 500, 500);
   tree->Draw("LumiBlock>>h4",evtSel);
   tree->Draw("LumiBlock>>h5",evtSel&&"HLT_HIJet35U");
   tree->Draw("LumiBlock>>h6",evtSel&&"HLT_HIJet50U");
   tree->Draw("LumiBlock>>h7",evtSel&&"HLT_HIJet75U");
  // tree->Draw("LumiBlock>>h8",evtSel&&"HLT_HIPhoton15");
  // tree->Draw("LumiBlock>>h9",evtSel&&"HLT_HIPhoton20");
  // tree->Draw("LumiBlock>>h10",evtSel&&"HLT_HIPhoton30");
  // tree->Draw("LumiBlock>>h11",evtSel&&"HLT_HIL1DoubleMuOpen");
  // tree->Draw("LumiBlock>>h12",evtSel&&"HLT_HIL1SingleMu3");
  // tree->Draw("LumiBlock>>h13",evtSel&&"HLT_HIL1SingleMu5");
  // tree->Draw("LumiBlock>>h14",evtSel&&"HLT_HIL1SingleMu7");
  // tree->Draw("LumiBlock>>h15",evtSel&&"HLT_HIL2DoubleMu0");
  // tree->Draw("LumiBlock>>h16",evtSel&&"HLT_HIL2DoubleMu3");
  // tree->Draw("LumiBlock>>h17",evtSel&&"HLT_HIL2Mu3");  
  // tree->Draw("LumiBlock>>h18",evtSel&&"HLT_HIL2Mu5Tight");
  // tree->Draw("LumiBlock>>h19",evtSel&&"HLT_HIL2Mu20");
  // TCanvas * y1 = new TCanvas("y1", "y1", 500, 500);
  //h4->Draw();
  // cout << "Total Again:" << h4->GetEntries() << endl;
  //  h5->Divide(h4);
  // TCanvas * y2 = new TCanvas("y2", "y2", 500, 500);
  //  h5 ->Draw();
  // cout << "Selected Amount:" << h5->GetEntries() << endl;

  Float_t TA = h4->GetEntries();
  Float_t TB = h5->GetEntries();
  Float_t TC = h6->GetEntries();
  Float_t TD = h7->GetEntries();
 // Float_t TE = h8->GetEntries();
 // Float_t TF = h9->GetEntries();
 // Float_t TG = h10->GetEntries();
 // Float_t TH = h11->GetEntries();
 // Float_t TI = h12->GetEntries();
 // Float_t TJ = h13->GetEntries();
 // Float_t TK = h14->GetEntries();
 // Float_t TL = h15->GetEntries();
 // Float_t TM = h16->GetEntries();
 // Float_t TN = h17->GetEntries();
 // Float_t TO = h18->GetEntries();
 // Float_t TP = h19->GetEntries();

  cout << "What is the Total # of MinBias Events? " << TA << endl;
  cout << "What is the Accept Fraction [%] for: " << endl;
   cout << "What is the Total # of Triggered events? " << TB << endl;
  cout << " HLT_HIJet35U ? => " << TB/TA * 100 << endl;
  cout << " HLT_HIJet50U ? => " << TC/TA * 100 << endl;
  cout << " HLT_HIJet75U  ? => " << TD/TA * 100 << endl;
 // cout << " HLT_HIPhoton15_Cleaned? => " << TE/TA * 100 << endl;
 // cout << " HLT_HIPhoton20_Cleaned?=> " << TF/TA * 100 << endl;
 // cout << " HLT_HIPhoton30_Cleaned? => " << TG/TA * 100 << endl;
 // cout << " HLT_HIL1DoubleMuOpen ? => " << TH/TA * 100 << endl;
 // cout << " HLT_HIL1SingleMu3 ? => " << TI/TA * 100 << endl;
 // cout << " HLT_HIL1SingleMu5 ? => " << TJ/TA * 100 << endl;
 // cout << " HLT_HIL1SingleMu7 ? => " << TK/TA * 100 << endl;
 // cout << " HLT_HIL2DoubleMu0 ? => " << TL/TA * 100 << endl;
 // cout << " HLT_HIL2DoubleMu3 ? => " << TM/TA * 100 << endl;
 // cout << " HLT_HIL2Mu3 ? => " << TN/TA * 100 << endl;
 // cout << " HLT_HIL2Mu5tight ? => " << TO/TA * 100 << endl;
 // cout << " HLT_HIL2Mu20 ? =>" << TP/TA * 100 << endl;
 
  return 0;
     
}
