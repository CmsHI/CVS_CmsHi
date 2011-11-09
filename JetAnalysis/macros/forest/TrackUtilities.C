#ifndef TrackUtilities_C
#define TrackUtilities_C
// Trk MPT Classes and functions
const int nptrange = 8;
float ptranges[nptrange+1] = {0.5,1,2,4,8,16,32,64,128};

class MPT {
public:
   TString name;
   float dRMin;
   float dRMax;
   float ptMin;
   float etaMax;
   
   float mptx;
   float mpty;
   float mptx_pt[nptrange];
   float mpty_pt[nptrange];
   
   MPT(TString s, float drmin=0, float drmax=1e3, float ptmin=0.5, float etamax=2.4) :
   name(s), dRMin(drmin), dRMax(drmax),ptMin(ptmin), etaMax(etamax) {
      clear();
   }
   void clear() {
      mptx = 0; mpty = 0;
      for (int i=0; i<nptrange; ++i) {
         mptx_pt[i] =0; mpty_pt[i] = 0;
      }      
   }
};

void CalcMPT(const HiForest * c, float geta, float gphi, float jeta, float jphi, MPT & m)
{
   m.clear();
   for (int it=0; it<c->track.nTrk; ++it) {
      float trkPt = c->track.trkPt[it];
      float trkEta = c->track.trkEta[it];
      float trkPhi = c->track.trkPhi[it];
      if (trkPt < m.ptMin) continue;
      if (fabs(trkEta) > m.etaMax) continue;
      float drG = deltaR(trkEta,trkPhi,geta,gphi);
      float drJ = deltaR(trkEta,trkPhi,jeta,jphi);
      if ((drG>=m.dRMin && drG<m.dRMax)
          || (drJ>=m.dRMin && drJ<m.dRMax)) {
         //if (m.name=="OutCone") cout << "pt: " << trkPt << "drG: " << drG << "drJ: " << drJ << endl;
         float ptx = -1* trkPt * cos(deltaPhi(trkPhi,gphi));
         float pty = -1* trkPt * sin(deltaPhi(trkPhi,gphi));
         m.mptx += ptx;
         m.mpty += pty;
         for (int k=0; k<nptrange; ++k) {
            if (trkPt> ptranges[k] && trkPt<ptranges[k+1]) {
               m.mptx_pt[k]+= ptx;
               m.mpty_pt[k]+= pty;
            }
         }
      }
   }  
}

void SetMPTBranches(TTree * t, MPT & m)
{
   t->Branch("mptx"+m.name,&m.mptx,"mptx"+m.name+"/F");
   t->Branch("mpty"+m.name,&m.mpty,"mpty"+m.name+"/F");
   TString sbrxpt = Form("mptx%s[%d]_pt/F",m.name.Data(),nptrange);
   TString sbrypt = Form("mpty%s[%d]_pt/F",m.name.Data(),nptrange);
   //cout << sbrxpt << ", " << sbrypt << endl;
   t->Branch("mptx"+m.name+"_pt",m.mptx_pt,sbrxpt);
   t->Branch("mpty"+m.name+"_pt",m.mpty_pt,sbrypt);
}

// Calo Matching
void HiForest::matchTrackCalo(bool allEvents){

   if(allEvents || currentEvent == 0){
      towerEt = new Float_t[maxEntry];
      towerdR = new Float_t[maxEntry];
      hbheEt = new Float_t[maxEntry];
      hbhedR = new Float_t[maxEntry];
      
      trackTree->Branch("towerEt",towerEt,"towerEt[nTrk]/F");
      trackTree->Branch("towerdR",towerdR,"towerdR[nTrk]/F");
      trackTree->Branch("hbhedR",hbheEt,"hbhedR[nTrk]/F");
      trackTree->Branch("hbheEt",hbheEt,"hbheEt[nTrk]/F");
   }

   for (int i=0; allEvents ? i<GetEntries() : 1;i++){
      if(allEvents) GetEntry(i);
      for (int j=0;j<track.nTrk;j++) {
	 int matchedTower = getMatchedCaloTowerAllowReuse(j);
	 int matchedHBHE  = getMatchedHBHEAllowReuse(j);
	 float matchedTowerdR = deltaR(track.trkEta[j],track.trkPhi[j],tower.eta[matchedTower],tower.phi[matchedTower]);
	 float matchedHbhedR = deltaR(track.trkEta[j],track.trkPhi[j],hbhe.eta[matchedHBHE],hbhe.phi[matchedHBHE]);
	 towerEt[j]=tower.et[matchedTower];
	 towerdR[j]=matchedTowerdR;
	 hbheEt[j]=hbhe.et[matchedHBHE];
	 hbhedR[j]=matchedHbhedR;
      }
      trackTree->Fill();
   }
 
}

int HiForest::getMatchedCaloTowerAllowReuse(int j)
{
   int best=-1;
   float bestDR2 = 1e10;
   float eta = track.trkEta[j];
   float phi = track.trkPhi[j];
   for (int i=0; i<tower.n; i++)
      {
	 float dR2 = deltaR2(eta,phi,tower.eta[i],tower.phi[i]);
	 if (dR2<bestDR2) {
	    bestDR2 = dR2;
	    best = i;
	 }
      }

   return best;
}


int HiForest::getMatchedHBHEAllowReuse(int j)
{
   int best=-1;
   float bestDR2 = 1e10;
   float eta = track.trkEta[j];
   float phi = track.trkPhi[j];
   for (int i=0; i<hbhe.n; i++)
      {
	 float dR2 = deltaR2(eta,phi,hbhe.eta[i],hbhe.phi[i]);
	 if (dR2<bestDR2) {
	    bestDR2 = dR2;
	    best = i;
	 }
      }

   return best;
}

#endif