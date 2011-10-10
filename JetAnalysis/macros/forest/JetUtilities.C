
class JetIndex{
public:
   double pt;
   int index;
};

bool comparePt(JetIndex a, JetIndex b) {return a.pt > b.pt;}

void HiForest::sortJets(TTree* jetTree, Jets& jets, double etaMax, double ptMin, bool allEvents){

   vector<TBranch*> branches(0);

   if(allEvents || currentEvent == 0){
      branches.push_back(jetTree->Branch("Lead",&jtLead,"Lead/I"));
      branches.push_back(jetTree->Branch("SubLead",&jtSubLead,"SubLead/I"));
      branches.push_back(jetTree->Branch("HasDijet",&jtHasDijet,"HasDijet/O"));
      branches.push_back(jetTree->Branch("HasLeadingJet",&jtHasLeadingJet,"HasLeadingJet/O"));
      jetTree->SetAlias("AJ","(jtpt[Lead]-jtpt[SubLead])/(jtpt[Lead]+jtpt[SubLead])");
   }

   vector<JetIndex> vecs;
   vecs.reserve(maxEntry);

   for (int i=0; allEvents ? i<GetEntries() : 1;i++){
      if(i % 1000 == 0) cout<<"Processing Event : "<<i<<endl;
      if(allEvents) jetTree->GetEntry(i);

      vecs.clear();
      
      for(int j = 0; j < jets.nref; ++j){
         if(jets.jtpt[j] < ptMin) continue;
	 if(fabs(jets.jteta[j]) > etaMax) continue;
	 
	 JetIndex entry;
	 entry.pt = jets.jtpt[j];
	 entry.index = j;
	 
	 vecs.push_back(entry);
      }
      sort(vecs.begin(),vecs.end(),comparePt);

      jtLead=-1;
      jtSubLead=-1;
      jtHasLeadingJet = 0;
      jtHasDijet = 0;

      if(vecs.size() > 0){
	 jtLead = vecs[0].index;
	 if(jets.jtpt[jtLead] > 100) jtHasLeadingJet = 1;
      }
      if(vecs.size() > 1){
	 jtSubLead = vecs[1].index;
	 if(jets.jtpt[jtSubLead] > 40) jtHasDijet = jtHasLeadingJet;
      }

      for(int ib = 0; ib < branches.size(); ++ib){
	 branches[ib]->Fill();
      }

   }
   
   return;
}


void HiForest::correlateTracks(TTree* jetTree, Jets& jets, bool allEvents){ 

   vector<TBranch*> branches(0);

   if(allEvents || currentEvent == 0){

      jtChg = new Float_t[maxEntry];
      jtNeut = new Float_t[maxEntry];
      jtEM = new Float_t[maxEntry];

      jtChgGen = new Float_t[maxEntry];
      jtNeutGen = new Float_t[maxEntry];
      jtEMGen = new Float_t[maxEntry];

      jtPtMax = new Float_t[maxEntry];
      jtPtMean = new Float_t[maxEntry];
      jtPtMeanW = new Float_t[maxEntry];

      jtLeadType = new Int_t[maxEntry];

      tjDeltaEtaLead = new Float_t[maxEntryTrack];
      tjDeltaPhiLead = new Float_t[maxEntryTrack];
      zLead = new Float_t[maxEntryTrack];

      tjDeltaEtaSubLead = new Float_t[maxEntryTrack];
      tjDeltaPhiSubLead = new Float_t[maxEntryTrack];
      zSubLead = new Float_t[maxEntryTrack];

      branches.push_back(jetTree->Branch("jtChg",jtChg,"jtChg[nref]/F"));
      branches.push_back(jetTree->Branch("jtNeut",jtNeut,"jtNeut[nref]/F"));
      branches.push_back(jetTree->Branch("jtEM",jtEM,"jtEM[nref]/F"));
      branches.push_back(jetTree->Branch("jtChgGen",jtChgGen,"jtChgGen[nref]/F"));
      branches.push_back(jetTree->Branch("jtNeutGen",jtNeutGen,"jtNeutGen[nref]/F"));
      branches.push_back(jetTree->Branch("jtEMGen",jtEMGen,"jtEMGen[nref]/F"));
      branches.push_back(jetTree->Branch("jtPtMax",jtPtMax,"jtPtMax[nref]/F"));
      branches.push_back(jetTree->Branch("jtPtMean",jtPtMean,"jtPtMean[nref]/F"));
      branches.push_back(jetTree->Branch("jtPtMeanW",jtPtMeanW,"jtPtMeanW[nref]/F"));
      branches.push_back(jetTree->Branch("jtLeadType",jtLeadType,"jtLeadType[nref]/I"));

      branches.push_back(trackTree->Branch("tjDetaLead",tjDeltaEtaLead,"tjDetaLead[nTrk]/F"));
      branches.push_back(trackTree->Branch("tjDphiLead",tjDeltaPhiLead,"tjDphiLead[nTrk]/F"));
      branches.push_back(trackTree->Branch("zLead",zLead,"zLead[nTrk]/F"));
      branches.push_back(trackTree->Branch("tjDetaSubLead",tjDeltaEtaSubLead,"tjDetaSubLead[nTrk]/F"));
      branches.push_back(trackTree->Branch("tjDphiSubLead",tjDeltaPhiSubLead,"tjDphiSubLead[nTrk]/F"));
      branches.push_back(trackTree->Branch("zSubLead",zSubLead,"zSubLead[nTrk]/F"));

      jetTree->SetAlias("jtFracChg","jtChg/jtpt");
      jetTree->SetAlias("jtFracNeut","jtNeut/jtpt");
      jetTree->SetAlias("jtFracEM","jtFracEM/jtpt");
      jetTree->SetAlias("refFracChg","jtChg/refpt");
      jetTree->SetAlias("refFracNeut","jtNeut/refpt");
      jetTree->SetAlias("refFracEM","jtFracEM/refpt");
      jetTree->SetAlias("jtFracChgGen","jtChgGen/jtpt");
      jetTree->SetAlias("jtFracNeutGen","jtNeutGen/refpt");
      jetTree->SetAlias("jtFracEMGen","jtFracEMGen/refpt");

      trackTree->SetAlias("tjDRlead","sqrt(tjDetaLead*tjDetaLead+tjDphiLead*tjDphiLead)");
      trackTree->SetAlias("tjDRsublead","sqrt(tjDetaSubLead*tjDetaSubLead+tjDphiSubLead*tjDphiSubLead)");

   }

   for (int i=0; allEvents ? i<GetEntries() : 1;i++){
      if(i % 1000 == 0) cout<<"Processing Event : "<<i<<endl;
      if(allEvents){
	 jetTree->GetEntry(i);
	 trackTree->GetEntry(i);
      }

      /*
      for (int t = 0; t < track.nTrk; t++) {
	 tjDeltaEtaLead[t] = -999;
         tjDeltaPhiLead[t] = -999;
	 tjDeltaEtaSubLead[t] = -999;
         tjDeltaPhiSubLead[t] = -999;
	 zLead[t] = -999;
         zSubLead[t] = -999;
      }
      */
      
      for(int j = 0; j < jets.nref; ++j){
	 for (int t = 0; t < track.nTrk; ++t) {
	    if(j == jtLead){
	       tjDeltaEtaLead[t] = track.trkEta[t] - jets.jteta[j];
	       tjDeltaPhiLead[t] = deltaPhi(track.trkPhi[t],jets.jtphi[j]);
	       zLead[t] = track.trkPt[t]/jets.jtpt[j];
	    }
	    if(j == jtSubLead){
	       tjDeltaEtaSubLead[t] = track.trkEta[t] - jets.jteta[j];
               tjDeltaPhiSubLead[t] = deltaPhi(track.trkPhi[t],jets.jtphi[j]);
               zSubLead[t] = track.trkPt[t]/jets.jtpt[j];
	    }
	 }
      }
      for(int ib = 0; ib < branches.size(); ++ib){
         branches[ib]->Fill();
      }
   }
  
   return;
}


int HiForest::leadingJet(){ return 0;}
int HiForest::subleadingJet(){ return 0;}
int HiForest::thirdJet(){ return 0;}


double HiForest::jetFracChg(int i){ return 0;}
double HiForest::jetFracNeut(int i){ return 0;}
double HiForest::jetFracEM(int i){ return 0;}




