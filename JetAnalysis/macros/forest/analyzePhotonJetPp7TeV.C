#include "hiForest.h"
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include "TChain.h"
#include "analyzePhotonJet.h"

class DuplicateEvents {
public:
   DuplicateEvents(TString infname) {
      inf = TFile::Open(infname);
      t = (TTree*)inf->Get("hltanalysis/HltTree");
   };
   ~DuplicateEvents() {
      delete inf;
   }
   void MakeList() {
      cout << "Starting Making List to check for duplicate events" << endl;
      evts.clear();
      occurrence.clear();
      int run,evt;
      t->SetBranchAddress("Run",&run);
      t->SetBranchAddress("Event",&evt);
      for (int i=0;i<t->GetEntries();i++) {
         t->GetEntry(i);
         if (i%100000==0) cout <<i<<" / "<<t->GetEntries() << " run: " << run << " evt: " << evt << endl;
         int occur = (int)FindOccurrences(run,evt);
         if (occur==0) occurrence.push_back(1);
         else occurrence.push_back(2);
         evts.push_back(std::make_pair(run,evt));
      }         
   }
   int FindOccurrences(int run, int evt) {
      int noccur = count(evts.begin(), evts.end(), std::make_pair(run,evt));
      return noccur;
   }
   TFile * inf;
   TTree * t;
   vector<pair<int, int> > evts;
   vector<int> occurrence;
};

void analyzePhotonJetPp7TeV(
                            TString jetAlgo = "akPu3PF",
                            //TString inname="rfio:/castor/cern.ch/user/y/yjlee/ppData2011/HiForest-pp7TeV-test.root",
                            //TString inname="rfio:/afs/cern.ch/cms/CAF/CMSPHYS/PHYS_HEAVYIONS/prod/pp/process/test.root",
                            //TString outname="output-pp7TeV-test2_v21_jetalgo0.root",
                            TString inname="rfio:/afs/cern.ch/cms/CAF/CMSPHYS/PHYS_HEAVYIONS/prod/pp/process/HiForest-pp-photon-7TeV-v2.root",
                            TString outname="output-pp-photon-7TeV-v2_v22.root",
                            double sampleWeight = 1, // data: 1, mc: s = 0.62, b = 0.38
                            bool doCentReWeight=false,
                            TString mcfname="",
                            TString datafname="output-data-Photon-v7_v21.root"
                            )
{
   outname.ReplaceAll(".root",Form("_%s.root",jetAlgo.Data()));
   double cutphotonPt = 40; // highest photon trigger is 20, also photon correction valid for photon pt > 40
   double cutjetPt = 20;
   double cutphotonEta = 1.44;
   double cutjetEta = 2;
   double cutEtaTrk = 2.4;
   // Centrality reweiting
   CentralityReWeight cw(datafname,mcfname,"offlSel&&photonEt>60");

   // Check for duplicate events
   DuplicateEvents dupEvt(inname);
   dupEvt.MakeList();
   
   // Define the input file and HiForest
   HiForest *c = new HiForest(inname,"forest",0,0,0,jetAlgo);
   c->GetEnergyScaleTable("photonEnergyScaleTable_lowPt_v4.root");
   // intialize jet variables
   Jets * anajet = &(c->akPu3PF);   
   
   // pfid
   TTree * pfTree = (TTree*) c->inf->Get("pfcandAnalyzer/pfTree");
   PFs pfs;
   if (pfTree) {
      c->CheckTree(pfTree,"PfTree");
      setupPFTree(pfTree,pfs,1);
   }
      
   // Output file
   cout << "Output: " << outname << endl;
   TFile *output = new TFile(outname,"recreate");
   TTree * tgj = new TTree("tgj","gamma jet tree");
   if (doCentReWeight&&mcfname!="") {
      cw.Init(); //cw.hCentData->Draw(); cw.hCentMc->Draw("same");
   }
   
   EvtSel evt;
   GammaJet gj;
   Isolation isol;
   tgj->Branch("evt",&evt.run,evt.leaves);
   tgj->Branch("jet",&gj.photonEt,gj.leaves);
   tgj->Branch("isolation",&isol.cc1,isol.leaves);
   tgj->Branch("nTrk",&gj.nTrk,"nTrk/I");
   tgj->Branch("trkPt",gj.trkPt,"trkPt[nTrk]/F");
   tgj->Branch("trkEta",gj.trkEta,"trkEta[nTrk]/F");
   tgj->Branch("trkPhi",gj.trkPhi,"trkPhi[nTrk]/F");
   tgj->Branch("trkJetDr",gj.trkJetDr,"trkJetDr[nTrk]/F");

   // pp triggers
   int HLT_Photon50_CaloIdVL_v3=0;
   int HLT_Photon50_CaloIdVL_IsoL_v6=0;
   c->hltTree->SetBranchAddress("HLT_Photon50_CaloIdVL_v3",&HLT_Photon50_CaloIdVL_v3);
   c->hltTree->SetBranchAddress("HLT_Photon50_CaloIdVL_IsoL_v6",&HLT_Photon50_CaloIdVL_IsoL_v6);
   
   // Main loop
   for (int i=0;i<c->GetEntries();i++)
   {
      c->GetEntry(i);
      if (pfTree) pfTree->GetEntry(i);
      // check if event is duplicate
      evt.nOccur = dupEvt.occurrence[i];
      // Event Info
      evt.run = c->hlt.Run;
      evt.evt = c->hlt.Event;
      evt.cBin = 39;
      evt.nG = c->photon.nPhotons;
      evt.nJ = c->icPu5.nref;
      evt.nT = c->track.nTrk;
      evt.trig = (HLT_Photon50_CaloIdVL_v3>0)||(HLT_Photon50_CaloIdVL_IsoL_v6>0);
      evt.offlSel = (c->skim.phfCoincFilter && c->skim.ppurityFractionFilter);
      evt.noiseFilt = (c->skim.pHBHENoiseFilter > 0);
      evt.anaEvtSel = evt.trig && evt.offlSel && evt.noiseFilt && evt.nOccur==1;
      evt.vz = c->track.vz[1];
      // Get Centrality Weight
      if (doCentReWeight) evt.weight = cw.GetWeight(evt.cBin);
      else evt.weight = 1;
      evt.npart = getNpart(evt.cBin);
      evt.ncoll = getNcoll(evt.cBin);
      evt.sampleWeight = sampleWeight; // for different mc sample, 1 for data

      
      if (i%1000==0) cout <<i<<" / "<<c->GetEntries() << " run: " << evt.run << " evt: " << evt.evt << " bin: " << evt.cBin << " nT: " << evt.nT << " trig: " <<  c->hlt.HLT_HISinglePhoton30_v2 << " anaEvtSel: " << evt.anaEvtSel <<endl;
      
      // initialize
      int leadingIndex=-1;
      int awayIndex=-1;
      gj.clear();
      
      // Loop over jets to look for leading jet candidate in the event
      for (int j=0;j<c->photon.nPhotons;j++) {
         if (c->photon.pt[j]<cutphotonPt||c->photon.pt[j]>1000) continue;          // photon pT cut
         if (fabs(c->photon.eta[j])>cutphotonEta) continue; // |eta|<1.44
         if (c->isSpike(j)) continue;               // spike removal
         if (!c->isLoosePhoton(j)) continue;         // final cuts in final plot macro execpt photon isol and showershape cut
         //if (!c->isLooseEGamma(j)) continue;         // final cuts in final plot macro execpt photon isol and showershape cut, include electrons
         // sort using corrected photon pt
         float corrPt=c->getCorrEt(j);
         if (corrPt>gj.photonEt) {
            gj.photonEt = corrPt;
            leadingIndex = j;
         }
      }
      
      // Found a leading jet which passed basic quality cut!
      if (leadingIndex!=-1) {
         // set leading photon
         gj.isEle=c->photon.isEle[leadingIndex];
         gj.photonRawEt=c->photon.pt[leadingIndex];
         gj.photonEta=c->photon.eta[leadingIndex];
         gj.photonPhi=c->photon.phi[leadingIndex];
         gj.hovere=c->photon.hadronicOverEm[leadingIndex];
         gj.sigmaIetaIeta=c->photon.sigmaIetaIeta[leadingIndex];
         gj.sumIsol=(c->photon.cr4[leadingIndex]+c->photon.cc4[leadingIndex]+c->photon.ct4PtCut20[leadingIndex]);
         isol.Set(c,leadingIndex);
         gj.refPhoPt = c->photon.genMatchedPt[leadingIndex];
         gj.refPhoEta = c->photon.genMatchedEta[leadingIndex];
         gj.refPhoPhi = c->photon.genMatchedPhi[leadingIndex];
         gj.refPhoFlavor = c->photon.genMomId[leadingIndex];
         
         // Loop over jet tree to find a away side leading jet
         for (int j=0;j<anajet->nref;j++) {
            if (anajet->jtpt[j]<cutjetPt) continue;
            if (fabs(anajet->jteta[j])>cutjetEta) continue;
            if (fabs(deltaPhi(anajet->jtphi[j],c->photon.phi[leadingIndex]))>0.5) {
               if (anajet->jtpt[j]>gj.jetEt) {
                  gj.jetEt = anajet->jtpt[j];
                  awayIndex = j;
               }
            } else { // Loop over jet tree to find a photon matching jet
               if (anajet->jtpt[j]>gj.phoMatJetEt) {
                  gj.phoMatJetEt = anajet->jtpt[j];
                  gj.phoMatJetEta = anajet->jteta[j];
                  gj.phoMatJetPhi = anajet->jtphi[j];
               }
            }
         }	 
         
         // Found an away jet!
         if (awayIndex !=-1) {
            double photonEt = c->photon.pt[leadingIndex];
            double jetEt = anajet->jtpt[awayIndex];
            double Agj = (photonEt-jetEt)/(photonEt+jetEt);
            gj.jetEt  = jetEt;
            gj.jetEta = anajet->jteta[awayIndex];
            gj.jetPhi = anajet->jtphi[awayIndex];
            gj.deta = anajet->jteta[awayIndex] - c->photon.eta[leadingIndex];
            gj.dphi = deltaPhi(anajet->jtphi[awayIndex],c->photon.phi[leadingIndex]);
            gj.Aj   = Agj;
            gj.refJetEt = anajet->refpt[awayIndex];
            gj.refJetEta = anajet->refeta[awayIndex];
            gj.refJetPhi = anajet->refphi[awayIndex];
            gj.refPartonPt = anajet->refparton_pt[awayIndex];
            gj.refPartonFlavor = anajet->refparton_flavor[awayIndex];
         }

         // pfid
         for (int it=0; it<pfs.nPFpart; ++it) {
            if (pfs.pfPt[it] < 4) continue;
            if (fabs(pfs.pfEta[it]) > 3) continue;
            // find leading pfcand in jet
            float dr = deltaR(pfs.pfEta[it],pfs.pfPhi[it],gj.jetEta,gj.jetPhi);
            if (dr<0.3 && pfs.pfPt[it]>gj.jlpfPt) {
               gj.jlpfPt = pfs.pfPt[it];
               gj.jlpfEta = pfs.pfEta[it];
               gj.jlpfPhi = pfs.pfPhi[it];
               gj.jlpfId = pfs.pfId[it];
            }
         }
      } // end of if jet
      
      // xcheck with tracks
      gj.nTrk=0;
      for (int it=0; it<c->track.nTrk; ++it) {
         if (c->track.trkPt[it] < 4) continue;
         if (fabs(c->track.trkEta[it]) > cutEtaTrk) continue;
         gj.trkPt[gj.nTrk] = c->track.trkPt[it];
         gj.trkEta[gj.nTrk] = c->track.trkEta[it];
         gj.trkPhi[gj.nTrk] = c->track.trkPhi[it];
         gj.trkJetDr[gj.nTrk] = deltaR(gj.trkEta[gj.nTrk],gj.trkPhi[gj.nTrk],gj.jetEta,gj.jetPhi);
         // find leading track
         if (gj.trkPt[gj.nTrk]>gj.ltrkPt) {
            gj.ltrkPt = gj.trkPt[gj.nTrk];
            gj.ltrkEta = gj.trkEta[gj.nTrk];
            gj.ltrkPhi = gj.trkPhi[gj.nTrk];
            gj.ltrkJetDr = gj.trkJetDr[gj.nTrk];
         }
         // find leading track in jet
         if (gj.trkJetDr[gj.nTrk]<0.3 && gj.trkPt[gj.nTrk]>gj.jltrkPt) {
            gj.jltrkPt = gj.trkPt[gj.nTrk];
            gj.jltrkEta = gj.trkEta[gj.nTrk];
            gj.jltrkPhi = gj.trkPhi[gj.nTrk];
            gj.jltrkJetDr = gj.trkJetDr[gj.nTrk];
         }
         ++gj.nTrk;
      }
      
      // All done
      tgj->Fill();
   }

   // After Event Loop
   tgj->SetAlias("fisherIsol","(4.5536204845644690e-01 +cc5*-1.1621087258504197e-03 +cc4*-1.3139962130657250e-02 +cc3*9.8272534188056666e-03 +cc2*-7.9659880964355362e-02 +cc1*5.6661268034678275e-02 +cr5*-1.2763802967154852e-02 +cr4*-1.2594575465310987e-03 +cr3*-1.3333157740152167e-02 +cr2*-2.5518237583408113e-02 +cr1*-1.3706749407235775e-02 +ct4PtCut20*-7.9844325658248016e-03 +ct3PtCut20*-2.5276510400767658e-03 +ct2PtCut20*-2.0741636383420897e-02 +ct1PtCut20*7.1545293456054884e-04 +ct5PtCut20*7.8080659557798627e-03)");
   tgj->SetAlias("xgj","(jetEt/photonEt)");
   // * cut at 0.3 from Yongsun's studies
   output->Write();
   output->Close();
   delete c;
}
