#ifndef MPTUtilities_C
#define MPTUtilities_C
#include "commonSetup.h"
#include "hiForest.h"

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
      if (dRCone>0) name+=Form("%.0f",dRCone*10);
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
   int excludeTrigCandMode;
   bool chargedOnly;
   float ptmin, etamax;
   int selPFId;
   bool doTrackingCorr,anaDiJet;
   HiForest * c;
   vector<float> drbins;
   vector<float> dphibins;
   
   // data members
   MPTCands cands; // input
   vector<MPT> vmpt; // ouput
   
   AnaMPT(TString myname, int mode=1, int pfid=0) :
   name(myname),
   excludeTrigCandMode(mode),
   chargedOnly(false),
   ptmin(0.5),etamax(2.4),
   selPFId(pfid),
   doTrackingCorr(false),
   anaDiJet(true)
   {
      cout << "dr bins: ";
      for (int i=0; i<3; ++i) {
         drbins.push_back((i+1)*0.4);
         cout << drbins[i] << " ";
      }
      cout << endl;

      cout << "dphi bins: ";
      for (int i=0; i<3; ++i) {
         dphibins.push_back((i+1)*TMath::PiOver2()/4.);
         cout << dphibins[i] << " ";
      }
      cout << endl;
   }
   
   void Init(TTree * t) {
      // default mpt analyses
      vmpt.push_back(MPT(name+"AllAcc",0,-1));
      if (doTrackingCorr) vmpt.push_back(MPT(name+"CorrAllAcc",0,-1,1));
      // dR cones
      for (int ir=0; ir<drbins.size(); ++ir) {
         vmpt.push_back(MPT(name+Form("InCone"),1,drbins[ir]));
         vmpt.push_back(MPT(name+Form("OutCone"),2,drbins[ir]));
         if (doTrackingCorr) {
            vmpt.push_back(MPT(name+Form("CorrInCone"),1,drbins[ir],1));
            vmpt.push_back(MPT(name+Form("CorrOutCone"),2,drbins[ir],1));
         }
      }
      // dphi regions
      for (int ir=0; ir<dphibins.size(); ++ir) {
         vmpt.push_back(MPT(name+Form("InDPhi"),3,dphibins[ir]));
         vmpt.push_back(MPT(name+Form("OutDPhi"),4,dphibins[ir]));
         if (doTrackingCorr) {
            vmpt.push_back(MPT(name+Form("CorrInDPhi"),3,dphibins[ir],1));
            vmpt.push_back(MPT(name+Form("CorrOutDPhi"),4,dphibins[ir],1));
         }
      }
      cout << "Setup mpt study " << name << ": ptmin=" << ptmin << " etamax=" << etamax;
      cout << " excludeTrigCandMode=" << excludeTrigCandMode << " chargedOnly=" << chargedOnly << " selPFId=" << selPFId << " doTrackingCorr=" << doTrackingCorr << " anaDiJet=" << anaDiJet << endl;
      for (unsigned m=0; m<vmpt.size(); ++m) { 
         //         cout << "CalcMPT for " << vmpt[m].name << " dRCone: " << vmpt[m].dRCone << endl;
         SetBranches(t,vmpt[m]);
      }      
   }
   
   void InputEvent(int n, float * pt, float * eta, float * phi, int * pfid=0, int * pstat=0, int * pch=0) {
//      cout << "mpt input size: " << n << endl;
      cands.n = 0;
      for (int i=0; i<n; ++i) {
         // candidate selection
         if (pt[i]<ptmin) continue;
         if (fabs(eta[i])>etamax) continue;
         if (selPFId&&pfid) {
            if (pfid[i]!=selPFId) continue;
         }
         if (pstat) {
//            cout << "stat: " << pstat[i] << endl;
            if (pstat[i]!=1) continue;
         }
         if (chargedOnly&&pch) {
//            cout << "charge: " << pch[i] << endl;
            if (pch[i]==0) continue;
         }
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
      float trkweight = 1.;
      
      for (int it=0; it<cands.n; ++it) {
         float candPt  = cands.pt[it];
         float candEta = cands.eta[it];
         float candPhi = cands.phi[it];
         float drG = deltaR(candEta,candPhi,geta,gphi);
         float drJ = deltaR(candEta,candPhi,jeta,jphi);
         float dphi1 = fabs(deltaPhi(candPhi,gphi));
         float dphipi1 = TMath::Pi()-dphi1;
         if (excludeTrigCandMode==2&&drG<0.05) continue;
         bool accept=false;
         if (m.selType==0) accept = true;
         else if (m.selType==1) {
            if (drG<m.dRCone||drJ<m.dRCone) accept=true;
         } else if (m.selType==2) {
            if (drG>m.dRCone&&drJ>m.dRCone) accept=true;
         } else if (m.selType==3) {
            if (dphi1<m.dRCone||dphipi1<m.dRCone) accept=true;
         } else if (m.selType==4) {
            if (dphi1>m.dRCone&&dphipi1>m.dRCone) accept=true;
         }
         if (accept) {
//            cout << "accepted mpt cand pt|eta|phi: " << candPt << "|" << candEta << "|" << candPhi << endl;
//            if (drG<0.01) cout << m.name << " pt: " << candPt << " drG: " << drG << " drJ: " << drJ << " photonPt: " << gpt << endl;
//            cout << m.name << " pt: " << candPt << " pt1: " << gpt << " dr1: " << drG << " dr2: " << drJ << " dphi1: " << dphi1 << " dphipi1: " << dphipi1 << endl;
            float ptx = candPt * cos(deltaPhi(candPhi,gphi));
            float pty = candPt * sin(deltaPhi(candPhi,gphi));
            if (m.corrType==1) {
               int corrSet=0;
               if (candPt<1) corrSet=1;
               if (anaDiJet&&gpt>40&&drG<0.8) trkweight = c->trackCorrections[corrSet]->GetCorr(candPt,candEta,gpt,c->evt.hiBin);
               else if (jpt>40&&drJ<0.8) trkweight = c->trackCorrections[corrSet]->GetCorr(candPt,candEta,jpt,c->evt.hiBin);
               else trkweight = c->trackCorrections[corrSet]->GetCorr(candPt,candEta,0,c->evt.hiBin);
               ptx*=trkweight;
               pty*=trkweight;
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
      if (excludeTrigCandMode==1) {
         if (gpt>0&&m.selType<2) {
            m.mptx-=gpt;
            for (int k=0; k<nptrange; ++k) {
               if (gpt> ptranges[k] && gpt<ptranges[k+1]) {
                  m.mptx_pt[k]-=gpt;
               }
            }
         }
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
