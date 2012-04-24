#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"
#include "TCut.h"

#include "commonUtility.h"
#include "loopPhotonJets.h"
#include "../commonTool.h"

#endif

void loopPhotonJets()
{
   // Define Input
//   TFile * inf1 = new TFile("../output-data-Photon-v7-noDuplicate_v35_mpt_akPu3PF.root");
   TFile * inf1 = new TFile("../output-data-Photon-v7_v35_mpt_akPu3PF_test.root");
   TTree * t1 = (TTree*)inf1->Get("tgj");

//   TFile * inf2 = new TFile("../output-data-Photon-v7-noDuplicate_v35_mpt_icPu5.root");
   TFile * inf2 = new TFile("../output-data-Photon-v7_v35_mpt_icPu5_test.root");
   TTree * t2 = (TTree*)inf2->Get("tgj");
   
   EvtSel evt;
   GammaJet gj1;
   GammaJet gj2;
   
   LoadGJBranches(t1,evt,gj1);
   LoadGJBranches(t2,evt,gj2);
   
   // Define Output
   TFile * fout = new TFile("LoopHists.root","recreate");
   TNtuple * nt = new TNtuple("nt","matched jets","gpt:geta:gphi:jpt:jeta:jphi:dphi:matjpt:matjdr:jlpfpt:jlpfeta:jlpfid");
   TH1D * hJetDr = new TH1D("hJetDr","",500,-1,9);
   TH1D * hMatJetDr = new TH1D("hMatJetDr","",500,-1,9);
   TH1D * hCandJ1Dr = new TH1D("hCandJ1Dr","",500,-1,9);
   TH2D * hPt2D = new TH2D("hPt2D","",50,0,200,50,0,200);
   TH1D * hDPhiJ1G = new TH1D("hDPhiJ1G","",50,0,3.14159);
   TH1D * hDPhiJ2G = new TH1D("hDPhiJ2G","",50,0,3.14159);
   
   for (int i=0; i<t1->GetEntries(); ++i) {
      t1->GetEntry(i);
      t2->GetEntry(i);
      if (i%1000==0) cout << i << " " << evt.evt << " photon: " << gj1.photonEt << " akPu3PF: " << gj1.jetEt << "|" << gj1.jetEta << " icPu5: " << gj2.jetEt << "|" << gj2.jetEta << endl;
      
      // selection
      if (!evt.anaEvtSel) continue;
      if (evt.cBin>=4) continue;
      
      if (gj1.photonEt<60) continue;
      if (gj1.sumIsol/0.9>1) continue;
      if (gj1.sigmaIetaIeta>0.01) continue;
      
      // loop over 1st jet collection
      for (int j=0; j<gj1.nJet; ++j) {
         float pt1=gj1.inclJetPt[j];
         float eta1=gj1.inclJetEta[j];
         float phi1=gj1.inclJetPhi[j];

         if (pt1<30) continue;
         if (fabs(eta1)>1.6) continue;

         float dphij1g = fabs(deltaPhi(phi1,gj1.photonPhi));
         if (dphij1g>0.7) hDPhiJ1G->Fill(dphij1g);
         if (dphij1g<7./8.*3.1415926) continue;
         
         // loop over 2nd jet collection
         float pt1mat=0,eta1mat=-99,phi1mat=-99,jetdrmat=-1;
         for (int k=0; k<gj1.nJet; ++k) {
            float pt2=gj2.inclJetPt[k];
            float eta2=gj2.inclJetEta[k];
            float phi2=gj2.inclJetPhi[k];
            float jetdr = deltaR(eta1,phi1,eta2,phi2);
            hJetDr->Fill(jetdr);
            if (jetdr<0.3&&pt2>pt1mat) {
               pt1mat = pt2;
               eta1mat = eta2;
               phi1mat = phi2;
               jetdrmat = jetdr;
            }
         }
         
         // loop over pf cands
         float jlpfpt=0,jlpfeta=-99,jlpfphi=-99;
         int jlpfid=-1;
         for (int ic=0; ic<gj1.nPf; ++ic) {
            float candPt = gj1.pfPt[ic];
            float candEta = gj1.pfEta[ic];
            float candPhi = gj1.pfPhi[ic];
            int candId = gj1.pfId[ic];
            float candJ1Dr = deltaR(eta1,phi1,candEta,candPhi);
            hCandJ1Dr->Fill(candJ1Dr);
            if (candJ1Dr<0.3&&candPt>jlpfpt) {
               jlpfpt = candPt;
               jlpfeta = candEta;
               jlpfphi = candPhi;
               jlpfid = candId;
            }
         }
         nt->Fill(gj1.photonEt,gj1.photonEta,gj1.photonPhi,pt1,eta1,phi1,dphij1g,pt1mat,jetdrmat,jlpfpt,jlpfeta,jlpfid);
         hMatJetDr->Fill(jetdrmat);
         hPt2D->Fill(pt1,pt1mat);
      }
   }
   
   // Write output
   fout->Write();
}