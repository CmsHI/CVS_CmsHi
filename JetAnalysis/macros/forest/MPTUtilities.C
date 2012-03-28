#ifndef MPTUtilities_C
#define MPTUtilities_C
#include "commonSetup.h"

// MPT Ranges
const int nptrange = 6;
float ptranges[nptrange+1]={0.5,1.0,2,4,8,20,180};

class MPT {
public:
   TString name;
   float dRCone;
   int selType;
   int corrType;
   
   float mptx;
   float mpty;
   float mptx_pt[nptrange];
   float mpty_pt[nptrange];
   
   MPT(TString s, int t=0, float dr=0.8, int c=0) :
   name(s), selType(t), dRCone(dr), corrType(c) {
      clear();
   }
   void clear() {
      mptx = 0; mpty = 0;
      for (int i=0; i<nptrange; ++i) {
         mptx_pt[i] =0; mpty_pt[i] = 0;
      }      
   }
};

class MPTCands {
public:
   int n;
   float pt[maxEntryTrack];
   float eta[maxEntryTrack];
   float phi[maxEntryTrack];
   MPTCands() : n(0) {}
   void Set(int i, float currpt, float curreta, float currphi) {
      pt[i]   = currpt;
      eta[i]  = curreta;
      phi[i]  = currphi;
   }
};

class AnaMPT
{
public:
   // parameters
   TString name;
   bool chargedOnly;
   float ptmin, etamax;
   int selPFId;
   bool doTrackingCorr,anaDiJet;
   
   // data members
   MPTCands cands; // input
   vector<MPT> vmpt; // ouput
   
   AnaMPT(TString myname) :
   name(myname),
   chargedOnly(false),
   ptmin(0),etamax(2.4),
   selPFId(0),
   doTrackingCorr(false),
   anaDiJet(false)
   {}
   
   void Init(TTree * t) {
      // default mpt analyses
      vmpt.push_back(MPT(name+"AllAcc",0,-1));
      vmpt.push_back(MPT(name+"InCone",1,0.8));
      vmpt.push_back(MPT(name+"OutCone",2,0.8));
      if (doTrackingCorr) {
         vmpt.push_back(MPT(name+"AllAccCorr",0,-1,1));
         vmpt.push_back(MPT(name+"InConeCorr",1,0.8,1));
         vmpt.push_back(MPT(name+"OutConeCorr",2,0.8,1));
      }
      for (unsigned m=0; m<vmpt.size(); ++m) { 
         cout << "CalcMPT for " << vmpt[m].name << " dRCone: " << vmpt[m].dRCone << endl;
         SetBranches(t,vmpt[m]);
      }      
   }
   
   void InputEvent(int n, float * pt, float * eta, float * phi, int * pfid=0, int * pstat=0, int * pch=0) {
      cands.n = 0;
      for (int i=0; i<n; ++i) {
         // candidate selection
         if (pt[i]<ptmin) continue;
         if (fabs(eta[i])>etamax) continue;
         if (selPFId&&pfid) {
            if (pfid[i]!=selPFId) continue;
         }
         if (pstat) {
            if (pstat[i]!=1) continue;
         }
         if (chargedOnly&&pch[i]==0) continue;
         // now write selected cands
         cands.Set(cands.n,pt[i],eta[i],phi[i]);
         ++cands.n;
      }
   }

   void AnalyzeEvent(float gpt, float geta, float gphi, float jpt, float jeta, float jphi) {
      for (unsigned m=0; m<vmpt.size(); ++m) {
         vmpt[m].clear();
         CalcMPT(gpt,geta,gphi,jpt,jeta,jphi,vmpt[m]);
      }
   }
   
   void CalcMPT(float gpt, float geta, float gphi, float jpt, float jeta, float jphi, MPT & m) {
      // initial setup
      m.clear();
      double correctionFactors[4] = {0,0,0,0};
      float trkweight = 1.;
      
      for (int it=0; it<cands.n; ++it) {
         float candPt  = cands.pt[it];
         float candEta = cands.eta[it];
         float candPhi = cands.phi[it];
         float drG = deltaR(candEta,candPhi,geta,gphi);
         float drJ = deltaR(candEta,candPhi,jeta,jphi);
         bool accept=false;
         if (m.selType==0) accept = true;
         else if (m.selType==1) {
            if (drG<m.dRCone||drJ<m.dRCone) accept=true;
         }
         else if (m.selType==2) {
            if (drG>m.dRCone&&drJ>m.dRCone) accept=true;
         }
         if (accept) {
//            if (drG<0.01) cout << m.name << " pt: " << candPt << " drG: " << drG << " drJ: " << drJ << " photonPt: " << gpt << endl;
            float ptx = candPt * cos(deltaPhi(candPhi,gphi));
            float pty = candPt * sin(deltaPhi(candPhi,gphi));
            if (m.corrType==1) {
//               if (anaDiJet&&drG<0.8) trkweight = c->trackCorrections[0]->GetCorr(candPt,candEta,gpt,c->evt.hiBin,correctionFactors);
//               else if (drJ<0.8) trkweight = c->trackCorrections[1]->GetCorr(candPt,candEta,jpt,c->evt.hiBin,correctionFactors);
//               else trkweight = c->trackCorrections[0]->GetCorr(candPt,candEta,0,c->evt.hiBin,correctionFactors);
//               ptx*=trkweight;
//               pty*=trkweight;
            }
            m.mptx += ptx;
            m.mpty += pty;
            for (int k=0; k<nptrange; ++k) {
               if (candPt> ptranges[k] && candPt<ptranges[k+1]) {
                  m.mptx_pt[k]+= ptx;
                  m.mpty_pt[k]+= pty;
               }
            }
         }
      }
      // finished looping through the candidates, but if included trigger particle in the sum, need to subtract
      if (!chargedOnly) {
         if (gpt>0&&m.selType<2) m.mptx-=gpt;
      }
//      cout << m.name << " mptx = " << m.mptx << " mpty = " << m.mpty << endl;
   }
   
   void SetBranches(TTree * t, MPT & m) {
      t->Branch("mptx"+m.name,&m.mptx,"mptx"+m.name+"/F");
      t->Branch("mpty"+m.name,&m.mpty,"mpty"+m.name+"/F");
      TString sbrxpt = Form("mptx%s[%d]_pt/F",m.name.Data(),nptrange);
      TString sbrypt = Form("mpty%s[%d]_pt/F",m.name.Data(),nptrange);
      //cout << sbrxpt << ", " << sbrypt << endl;
      t->Branch("mptx"+m.name+"_pt",m.mptx_pt,sbrxpt);
      t->Branch("mpty"+m.name+"_pt",m.mpty_pt,sbrypt);
   }
};
#endif