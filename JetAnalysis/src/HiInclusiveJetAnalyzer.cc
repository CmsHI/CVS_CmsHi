/*
  Based on the jet response analyzer
  Modified by Matt Nguyen, November 2010

*/

#include "CmsHi/JetAnalysis/interface/HiInclusiveJetAnalyzer.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include <Math/DistFunc.h>
#include "TMath.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"

#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
#include "L1Trigger/GlobalTrigger/interface/L1GlobalTrigger.h"

using namespace std;
using namespace edm;
using namespace reco;

HiInclusiveJetAnalyzer::HiInclusiveJetAnalyzer(const edm::ParameterSet& iConfig) {
  

  jetTag_ = iConfig.getParameter<InputTag>("jetTag");
  vtxTag_ = iConfig.getUntrackedParameter<edm::InputTag>("vtxTag",edm::InputTag("hiSelectedVertex"));  

  isMC_ = iConfig.getUntrackedParameter<bool>("isMC",false);
  
  if(isMC_){
    genjetTag_ = iConfig.getParameter<InputTag>("genjetTag");
    eventInfoTag_ = iConfig.getParameter<InputTag>("eventInfoTag");
  }
  verbose_ = iConfig.getUntrackedParameter<bool>("verbose",false);

  useCentrality_ = iConfig.getUntrackedParameter<bool>("useCentrality",false);
  useVtx_ = iConfig.getUntrackedParameter<bool>("useVtx",false);
  useJEC_ = iConfig.getUntrackedParameter<bool>("useJEC",true);
  usePat_ = iConfig.getUntrackedParameter<bool>("usePAT",true);

  doLifeTimeTagging_ = iConfig.getUntrackedParameter<bool>("doLifeTimeTagging",false);
  doLifeTimeTaggingExtras_ = iConfig.getUntrackedParameter<bool>("doLifeTimeTaggingExtras",true);
  pfCandidateLabel_ = iConfig.getUntrackedParameter<edm::InputTag>("pfCandidateLabel",edm::InputTag("particleFlowTmp"));

  if(!isMC_){
    L1gtReadout_ = iConfig.getParameter<edm::InputTag>("L1gtReadout");
    hltResName_ = iConfig.getUntrackedParameter<string>("hltTrgResults","TriggerResults::HLT");
    
    
    if (iConfig.exists("hltTrgNames"))
      hltTrgNames_ = iConfig.getUntrackedParameter<vector<string> >("hltTrgNames");
    
    if (iConfig.exists("hltProcNames"))
      hltProcNames_ = iConfig.getUntrackedParameter<vector<string> >("hltProcNames");
    else {
      hltProcNames_.push_back("FU");
      hltProcNames_.push_back("HLT");
    }
  }

  cout<<" jet collection : "<<jetTag_<<endl;
  if(isMC_){
     cout<<" genjet collection : "<<genjetTag_<<endl;
     genPtMin_ = iConfig.getUntrackedParameter<double>("genPtMin",0);
  }

   
}



HiInclusiveJetAnalyzer::~HiInclusiveJetAnalyzer() { }



void 
HiInclusiveJetAnalyzer::beginRun(const edm::Run& run, 
			      const edm::EventSetup & es) {}

void 
HiInclusiveJetAnalyzer::beginJob() {

  centrality_ = 0;

  //string jetTagName = jetTag_.label()+"_tree"; 
  string jetTagTitle = jetTag_.label()+" Jet Analysis Tree"; 
  t = fs1->make<TTree>("t",jetTagTitle.c_str());

  //  TTree* t= new TTree("t","Jet Response Analyzer");
  //t->Branch("run",&jets_.run,"run/I");
  t->Branch("evt",&jets_.evt,"evt/I");
  //t->Branch("lumi",&jets_.lumi,"lumi/I");
  t->Branch("b",&jets_.b,"b/F");
  if (useVtx_) {
     t->Branch("vx",&jets_.vx,"vx/F");
     t->Branch("vy",&jets_.vy,"vy/F");
     t->Branch("vz",&jets_.vz,"vz/F");
  }
  if (useCentrality_) {
     t->Branch("hf",&jets_.hf,"hf/F");
     t->Branch("bin",&jets_.bin,"bin/I");
  }

  t->Branch("nref",&jets_.nref,"nref/I");
  t->Branch("rawpt",jets_.rawpt,"rawpt[nref]/F");
  t->Branch("jtpt",jets_.jtpt,"jtpt[nref]/F");
  t->Branch("jteta",jets_.jteta,"jteta[nref]/F");
  t->Branch("jty",jets_.jty,"jty[nref]/F");
  t->Branch("jtphi",jets_.jtphi,"jtphi[nref]/F");
  t->Branch("jtpu",jets_.jtpu,"jtpu[nref]/F");

  // b-jet discriminators
  if (doLifeTimeTagging_) {

    t->Branch("discr_csvMva",jets_.discr_csvMva,"discr_csvMva[nref]/F");
    t->Branch("discr_csvSimple",jets_.discr_csvSimple,"discr_csvSimple[nref]/F");
    t->Branch("discr_muByIp3",jets_.discr_muByIp3,"discr_muByIp3[nref]/F");
    t->Branch("discr_muByPt",jets_.discr_muByPt,"discr_muByPt[nref]/F");
    t->Branch("discr_prob",jets_.discr_prob,"discr_prob[nref]/F");
    t->Branch("discr_probb",jets_.discr_probb,"discr_probb[nref]/F");
    t->Branch("discr_tcHighEff",jets_.discr_tcHighEff,"discr_tcHighEff[nref]/F");
    t->Branch("discr_tcHighPur",jets_.discr_tcHighPur,"discr_tcHighPur[nref]/F");
    
    t->Branch("nsvtx",    jets_.nsvtx,    "nsvtx[nref]/I");
    t->Branch("svtxntrk", jets_.svtxntrk, "svtxntrk[nref]/I");
    t->Branch("svtxdl",   jets_.svtxdl,   "svtxdl[nref]/F");
    t->Branch("svtxdls",  jets_.svtxdls,  "svtxdls[nref]/F");
    t->Branch("svtxm",    jets_.svtxm,    "svtxm[nref]/F");
    t->Branch("svtxpt",   jets_.svtxpt,   "svtxpt[nref]/F");
    
    t->Branch("nIPtrk",jets_.nIPtrk,"nIPtrk[nref]/I");
    t->Branch("nselIPtrk",jets_.nselIPtrk,"nselIPtrk[nref]/I");
    
    if (doLifeTimeTaggingExtras_) {
      t->Branch("ipJetIndex",jets_.ipJetIndex,"ipJetIndex[nselIPtrk]/I");
      t->Branch("ipPt",jets_.ipPt,"ipPt[nselIPtrk]/F");
      t->Branch("ipProb0",jets_.ipProb0,"ipProb0[nselIPtrk]/F");
      t->Branch("ipProb1",jets_.ipProb1,"ipProb1[nselIPtrk]/F");
      t->Branch("ip2d",jets_.ip2d,"ip2d[nselIPtrk]/F");
      t->Branch("ip2dSig",jets_.ip2dSig,"ip2dSig[nselIPtrk]/F");
      t->Branch("ip3d",jets_.ip3d,"ip3d[nselIPtrk]/F");
      t->Branch("ip3dSig",jets_.ip3dSig,"ip3dSig[nselIPtrk]/F");
      t->Branch("ipDist2Jet",jets_.ipDist2Jet,"ipDist2Jet[nselIPtrk]/F");
      t->Branch("ipDist2JetSig",jets_.ipDist2JetSig,"ipDist2JetSig[nselIPtrk]/F");
      t->Branch("ipClosest2Jet",jets_.ipClosest2Jet,"ipClosest2Jet[nselIPtrk]/F");
    }      

    t->Branch("mue",     jets_.mue,     "mue[nref]/F");
    t->Branch("mupt",    jets_.mupt,    "mupt[nref]/F");
    t->Branch("mueta",   jets_.mueta,   "mueta[nref]/F");
    t->Branch("muphi",   jets_.muphi,   "muphi[nref]/F");
    t->Branch("mudr",    jets_.mudr,    "mudr[nref]/F");
    t->Branch("muptrel", jets_.muptrel, "muptrel[nref]/F");
    t->Branch("muchg",   jets_.muchg,   "muchg[nref]/I");
  }
  
  if(isMC_){
    t->Branch("beamId1",&jets_.beamId1,"beamId1/I");    
    t->Branch("beamId2",&jets_.beamId2,"beamId2/I");    

    t->Branch("pthat",&jets_.pthat,"pthat/F");    

    // Only matched gen jets
    t->Branch("refpt",jets_.refpt,"refpt[nref]/F");
    t->Branch("refeta",jets_.refeta,"refeta[nref]/F");
    t->Branch("refy",jets_.refy,"refy[nref]/F");
    t->Branch("refphi",jets_.refphi,"refphi[nref]/F");
    t->Branch("refdphijt",jets_.refdphijt,"refdphijt[nref]/F");
    t->Branch("refdrjt",jets_.refdrjt,"refdrjt[nref]/F");
    // matched parton
    t->Branch("refparton_pt",jets_.refparton_pt,"refparton_pt[nref]/F");
    t->Branch("refparton_flavor",jets_.refparton_flavor,"refparton_flavor[nref]/I");
    t->Branch("refparton_flavorForB",jets_.refparton_flavorForB,"refparton_flavorForB[nref]/I");

    // For all gen jets, matched or unmatched
    t->Branch("ngen",&jets_.ngen,"ngen/I");
    t->Branch("genmatchindex",jets_.genmatchindex,"genmatchindex[ngen]/I");
    t->Branch("genpt",jets_.genpt,"genpt[ngen]/F");
    t->Branch("geneta",jets_.geneta,"geneta[ngen]/F");
    t->Branch("geny",jets_.geny,"geny[ngen]/F");
    t->Branch("genphi",jets_.genphi,"genphi[ngen]/F");
    t->Branch("gendphijt",jets_.gendphijt,"gendphijt[ngen]/F");
    t->Branch("gendrjt",jets_.gendrjt,"gendrjt[ngen]/F");
  }
  /*
  if(!isMC_){
    t->Branch("nL1TBit",&jets_.nL1TBit,"nL1TBit/I");
    t->Branch("l1TBit",jets_.l1TBit,"l1TBit[nL1TBit]/O");

    t->Branch("nL1ABit",&jets_.nL1ABit,"nL1ABit/I");
    t->Branch("l1ABit",jets_.l1ABit,"l1ABit[nL1ABit]/O");

    t->Branch("nHLTBit",&jets_.nHLTBit,"nHLTBit/I");
    t->Branch("hltBit",jets_.hltBit,"hltBit[nHLTBit]/O");

  }
  */
  TH1D::SetDefaultSumw2();
  
  
}


void 
HiInclusiveJetAnalyzer::analyze(const Event& iEvent, 
			     const EventSetup& iSetup) {
  
  int event = iEvent.id().event();
  int run = iEvent.id().run();
  int lumi = iEvent.id().luminosityBlock();
  
  jets_.run = run;
  jets_.evt = event;
  jets_.lumi = lumi;

  LogDebug("HiInclusiveJetAnalyzer")<<"START event: "<<event<<" in run "<<run<<endl;

 int bin = -1;
  double hf = 0.;
  double b = 999.;

  if(useCentrality_){
      if(!centrality_) centrality_ = new CentralityProvider(iSetup);      
      centrality_->newEvent(iEvent,iSetup); // make sure you do this first in every event
      //double c = centrality_->centralityValue();
      const reco::Centrality *cent = centrality_->raw();
      
      hf = cent->EtHFhitSum();

      bin = centrality_->getBin();
      b = centrality_->bMean();
  }
   



  //double jetPtMin = 35.;


   // loop the events
   
   jets_.bin = bin;
   jets_.hf = hf;
   

	 if (useVtx_) {
      edm::Handle<vector<reco::Vertex> >vertex;
      iEvent.getByLabel(vtxTag_, vertex);

      if(vertex->size()>0) {
        jets_.vx=vertex->begin()->x();
        jets_.vy=vertex->begin()->y();
        jets_.vz=vertex->begin()->z();
      }
	 }
   
   edm::Handle<pat::JetCollection> patjets;
   if(usePat_)iEvent.getByLabel(jetTag_, patjets);
   
   edm::Handle<reco::JetView> jets;
   iEvent.getByLabel(jetTag_, jets);

   edm::Handle<reco::PFCandidateCollection> pfCandidates;
   if(doLifeTimeTagging_){
     iEvent.getByLabel(pfCandidateLabel_,pfCandidates);  
   }
   // FILL JRA TREE

   jets_.b = b;
   jets_.nref = 0;
   
   if(!isMC_){
     fillL1Bits(iEvent);
     fillHLTBits(iEvent);
   }

   for(unsigned int j = 0 ; j < jets->size(); ++j){
     const reco::Jet& jet = (*jets)[j];
     
     //cout<<" jet pt "<<jet.pt()<<endl;
     //if(jet.pt() < jetPtMin) continue;
     if (useJEC_ && usePat_){
       jets_.rawpt[jets_.nref]=(*patjets)[j].correctedJet("Uncorrected").pt();
     }
     
     if(doLifeTimeTagging_){
       
       if(jetTag_.label()=="icPu5patJets"){
	 jets_.discr_csvMva[jets_.nref]    = (*patjets)[j].bDiscriminator("icPu5CombinedSecondaryVertexMVABJetTags");
	 jets_.discr_csvSimple[jets_.nref] = (*patjets)[j].bDiscriminator("icPu5CombinedSecondaryVertexBJetTags");
	 jets_.discr_muByIp3[jets_.nref]   = (*patjets)[j].bDiscriminator("icPu5SoftMuonByIP3dBJetTags");
	 jets_.discr_muByPt[jets_.nref]    = (*patjets)[j].bDiscriminator("icPu5SoftMuonByPtBJetTags");
	 jets_.discr_prob[jets_.nref]      = (*patjets)[j].bDiscriminator("icPu5JetBProbabilityBJetTags");
	 jets_.discr_probb[jets_.nref]     = (*patjets)[j].bDiscriminator("icPu5JetProbabilityBJetTags");
	 jets_.discr_tcHighEff[jets_.nref] = (*patjets)[j].bDiscriminator("icPu5TrackCountingHighEffBJetTags");
	 jets_.discr_tcHighPur[jets_.nref] = (*patjets)[j].bDiscriminator("icPu5TrackCountingHighPurBJetTags");
       }
       else if(jetTag_.label()=="akPu3PFpatJets"){
	 jets_.discr_csvMva[jets_.nref]    = (*patjets)[j].bDiscriminator("akPu3PFCombinedSecondaryVertexMVABJetTags");
	 jets_.discr_csvSimple[jets_.nref] = (*patjets)[j].bDiscriminator("akPu3PFCombinedSecondaryVertexBJetTags");
	 jets_.discr_muByIp3[jets_.nref]   = (*patjets)[j].bDiscriminator("akPu3PFSoftMuonByIP3dBJetTags");
	 jets_.discr_muByPt[jets_.nref]    = (*patjets)[j].bDiscriminator("akPu3PFSoftMuonByPtBJetTags");
	 jets_.discr_prob[jets_.nref]      = (*patjets)[j].bDiscriminator("akPu3PFJetBProbabilityBJetTags");
	 jets_.discr_probb[jets_.nref]     = (*patjets)[j].bDiscriminator("akPu3PFJetProbabilityBJetTags");
	 jets_.discr_tcHighEff[jets_.nref] = (*patjets)[j].bDiscriminator("akPu3PFTrackCountingHighEffBJetTags");
	 jets_.discr_tcHighPur[jets_.nref] = (*patjets)[j].bDiscriminator("akPu3PFTrackCountingHighPurBJetTags");
       }
       else{
	 cout<<" b-tagging variables not filled for this collection, turn of doLifeTimeTagging "<<endl;
       }

       const reco::SecondaryVertexTagInfo& tagInfoSV=*(*patjets)[j].tagInfoSecondaryVertex();
       
       jets_.nsvtx[jets_.nref]     = tagInfoSV.nVertices();	 
       
       if (tagInfoSV.nVertices()>0) {
	 jets_.svtxntrk[jets_.nref]  = tagInfoSV.nVertexTracks(0);
	 // this is the 3d flight distance, for 2-D use (0,true)
	 Measurement1D m1D = tagInfoSV.flightDistance(0);	 
	 jets_.svtxdl[jets_.nref]    = m1D.value();
	 jets_.svtxdls[jets_.nref]   = m1D.significance();
	 
	 const reco::Vertex& svtx = tagInfoSV.secondaryVertex(0);	 
	 jets_.svtxm[jets_.nref]    = svtx.p4().mass();
	 jets_.svtxpt[jets_.nref]   = svtx.p4().pt();	 
       }
       
       const reco::TrackIPTagInfo& tagInfoIP=*(*patjets)[j].tagInfoTrackIP();
       
       jets_.nIPtrk[jets_.nref] = tagInfoIP.tracks().size();
       jets_.nselIPtrk[jets_.nref] = tagInfoIP.selectedTracks().size();

       if (doLifeTimeTaggingExtras_) {

	 TrackRefVector selTracks=tagInfoIP.selectedTracks();
	 
	 GlobalPoint pv(tagInfoIP.primaryVertex()->position().x(),tagInfoIP.primaryVertex()->position().y(),tagInfoIP.primaryVertex()->position().z());
	 
	 for(int it=0;it<jets_.nselIPtrk[jets_.nref] ;it++)
	   {
	     jets_.ipJetIndex[it]= jets_.nref;
	     TrackIPTagInfo::TrackIPData data = tagInfoIP.impactParameterData()[it];  
	     jets_.ipPt[it] = selTracks[it]->pt();
	     jets_.ipProb0[it] = tagInfoIP.probabilities(0)[it];
	     jets_.ipProb1[it] = tagInfoIP.probabilities(1)[it];
	     jets_.ip2d[it] = data.ip2d.value();
	     jets_.ip2dSig[it] = data.ip2d.significance();
	     jets_.ip3d[it] = data.ip3d.value();
	     jets_.ip3dSig[it] = data.ip3d.significance();
	     jets_.ipDist2Jet[it] = data.distanceToJetAxis.value();
	     jets_.ipDist2JetSig[it] = data.distanceToJetAxis.significance();
	     jets_.ipClosest2Jet[it] = (data.closestToJetAxis - pv).mag();	//decay length   
	   }
       }
       
       const reco::PFCandidateCollection *pfCandidateColl = &(*pfCandidates);
       int pfMuonIndex = getPFJetMuon(jet, pfCandidateColl);
       if(pfMuonIndex >=0){
	 const reco::PFCandidate muon = pfCandidateColl->at(pfMuonIndex);
	 jets_.mupt[jets_.nref]    =  muon.pt();
	 jets_.mueta[jets_.nref]   =  muon.eta();
	 jets_.muphi[jets_.nref]   =  muon.phi();   
	 jets_.mue[jets_.nref]     =  muon.energy();
	 jets_.mudr[jets_.nref]    =  reco::deltaR(jet,muon);
	 jets_.muptrel[jets_.nref] =  getPtRel(muon, jet);
	 jets_.muchg[jets_.nref]   =  muon.charge();
       }
     }

     jets_.jtpt[jets_.nref] = jet.pt();                            
     jets_.jteta[jets_.nref] = jet.eta();
     jets_.jtphi[jets_.nref] = jet.phi();
     jets_.jty[jets_.nref] = jet.eta();
     jets_.jtpu[jets_.nref] = jet.pileup();
	 
     if(isMC_ && usePat_){
       jets_.refparton_flavorForB[jets_.nref] = (*patjets)[j].partonFlavour();
       const reco::GenJet* genjet = (*patjets)[j].genJet();
	 
       if(genjet){
	 jets_.refpt[jets_.nref] = genjet->pt();        
	 jets_.refeta[jets_.nref] = genjet->eta();
	 jets_.refphi[jets_.nref] = genjet->phi();
	 jets_.refy[jets_.nref] = genjet->eta();
	 jets_.refdphijt[jets_.nref] = reco::deltaPhi(jet.phi(), genjet->phi());	
	 jets_.refdrjt[jets_.nref] = reco::deltaR(jet.eta(),jet.phi(),genjet->eta(),genjet->phi());	       
       }else{
	 jets_.refpt[jets_.nref] = -999.;
	 jets_.refeta[jets_.nref] = -999.;
	 jets_.refphi[jets_.nref] = -999.;
	 jets_.refy[jets_.nref] = -999.;
	 jets_.refdphijt[jets_.nref] = -999.;
	 jets_.refdrjt[jets_.nref] = -999.;
       }

   // matched partons
       const reco::GenParticle * parton = (*patjets)[j].genParton();
       if(parton){
	 jets_.refparton_pt[jets_.nref] = parton->pt();
	 jets_.refparton_flavor[jets_.nref] = parton->pdgId();
       } else {
       jets_.refparton_pt[jets_.nref] = -999;
       jets_.refparton_flavor[jets_.nref] = -999;
       }
     }
 
     jets_.nref++;
       
       
   }


   if(isMC_){

     edm::Handle<HepMCProduct> hepMCProduct;
     iEvent.getByLabel(eventInfoTag_,hepMCProduct);
     const HepMC::GenEvent* MCEvt = hepMCProduct->GetEvent();
     std::pair<HepMC::GenParticle*,HepMC::GenParticle*> beamParticles = MCEvt->beam_particles();
     jets_.beamId1 = beamParticles.first->pdg_id();
     jets_.beamId2 = beamParticles.second->pdg_id();

     edm::Handle<GenEventInfoProduct> hEventInfo;
     iEvent.getByLabel(eventInfoTag_,hEventInfo);
     //jets_.pthat = hEventInfo->binningValues()[0];

     // binning values and qscale appear to be equivalent, but binning values not always present
     jets_.pthat = hEventInfo->qScale();

     edm::Handle<vector<reco::GenJet> >genjets;
     iEvent.getByLabel(genjetTag_, genjets);

     jets_.ngen = 0;
     for(unsigned int igen = 0 ; igen < genjets->size(); ++igen){
       const reco::GenJet & genjet = (*genjets)[igen];
       
       float genjet_pt = genjet.pt();
       
       // threshold to reduce size of output in minbias PbPb
       if(genjet_pt>genPtMin_){

	 jets_.genpt[jets_.ngen] = genjet_pt;                            
	 jets_.geneta[jets_.ngen] = genjet.eta();
	 jets_.genphi[jets_.ngen] = genjet.phi();
	 jets_.geny[jets_.ngen] = genjet.eta();
	 
	 
	 // find matching patJet if there is one
	 
	 jets_.gendrjt[jets_.ngen] = -1.0;
	 jets_.genmatchindex[jets_.ngen] = -1;
	 
	 for(unsigned int ijet = 0 ; ijet < jets->size(); ++ijet){
	   const pat::Jet& jet = (*jets)[ijet];
	   const reco::GenJet* matchedGenJet = (*patjets)[ijet].genJet();
	   if(matchedGenJet){
	     // poor man's matching, someone fix please
	     if(fabs(genjet.pt()-matchedGenJet->pt())<0.0001 &&
		fabs(genjet.eta()-matchedGenJet->eta())<0.0001 &&
		(fabs(genjet.phi()-matchedGenJet->phi())<0.0001 || fabs(genjet.phi()-matchedGenJet->phi() - 2.0*TMath::Pi()) < 0.0001 )){
	       
	       jets_.genmatchindex[jets_.ngen] = (int)ijet;
	       jets_.gendphijt[jets_.ngen] = reco::deltaPhi(jet.phi(),genjet.phi());	
	       jets_.gendrjt[jets_.ngen] = reco::deltaR(jet,genjet);	
	       
	       break;
	     }            		
	   }
	 }
	 jets_.ngen++;
       }
       
     }
     
   }
   t->Fill();
   memset(&jets_,0,sizeof jets_);
}


  

//--------------------------------------------------------------------------------------------------
void HiInclusiveJetAnalyzer::fillL1Bits(const edm::Event &iEvent)
{
  edm::Handle< L1GlobalTriggerReadoutRecord >  L1GlobalTrigger;

  iEvent.getByLabel(L1gtReadout_, L1GlobalTrigger); 
  const TechnicalTriggerWord&  technicalTriggerWordBeforeMask = L1GlobalTrigger->technicalTriggerWord();

  for (int i=0; i<64;i++)
    {
      jets_.l1TBit[i] = technicalTriggerWordBeforeMask.at(i);
    }
  jets_.nL1TBit = 64;

  int ntrigs = L1GlobalTrigger->decisionWord().size();
  jets_.nL1ABit = ntrigs;

  for (int i=0; i != ntrigs; i++) {
    bool accept = L1GlobalTrigger->decisionWord()[i];
    //jets_.l1ABit[i] = (accept == true)? 1:0;
    if(accept== true){
      jets_.l1ABit[i] = 1;
    }
    else{
      jets_.l1ABit[i] = 0;
    }
    
  }
}

//--------------------------------------------------------------------------------------------------
void HiInclusiveJetAnalyzer::fillHLTBits(const edm::Event &iEvent)
{
  // Fill HLT trigger bits.
  Handle<TriggerResults> triggerResultsHLT;
  getProduct(hltResName_, triggerResultsHLT, iEvent);

  const TriggerResults *hltResults = triggerResultsHLT.product();
  const TriggerNames & triggerNames = iEvent.triggerNames(*hltResults);

  jets_.nHLTBit = hltTrgNames_.size();

  for(size_t i=0;i<hltTrgNames_.size();i++){
   
    for(size_t j=0;j<triggerNames.size();++j) {
      
      if(triggerNames.triggerName(j) == hltTrgNames_[i]){
	
	//cout <<"hltTrgNames_(i) "<<hltTrgNames_[i]<<endl;
	//cout <<"triggerName(j) "<<triggerNames.triggerName(j)<<endl;
	//cout<<" result "<<triggerResultsHLT->accept(j)<<endl;
	jets_.hltBit[i] = triggerResultsHLT->accept(j);
      }
      
    }
  }
}

//--------------------------------------------------------------------------------------------------
template <typename TYPE>
inline void HiInclusiveJetAnalyzer::getProduct(const std::string name, edm::Handle<TYPE> &prod,
					 const edm::Event &event) const
{
  // Try to access data collection from EDM file. We check if we really get just one
  // product with the given name. If not we throw an exception.

  event.getByLabel(edm::InputTag(name),prod);
  if (!prod.isValid()) 
    throw edm::Exception(edm::errors::Configuration, "HiInclusiveJetAnalyzer::GetProduct()\n")
      << "Collection with label '" << name << "' is not valid" <<  std::endl;
}

//--------------------------------------------------------------------------------------------------
template <typename TYPE>
inline bool HiInclusiveJetAnalyzer::getProductSafe(const std::string name, edm::Handle<TYPE> &prod,
					     const edm::Event &event) const
{
  // Try to safely access data collection from EDM file. We check if we really get just one
  // product with the given name. If not, we return false.

  if (name.size()==0)
    return false;

  try {
    event.getByLabel(edm::InputTag(name),prod);
    if (!prod.isValid()) 
      return false;
  } catch (...) {
    return false;
  }
  return true;
}


int
HiInclusiveJetAnalyzer::getPFJetMuon(const pat::Jet& pfJet, const reco::PFCandidateCollection *pfCandidateColl)
{
  
  int pfMuonIndex = -1;
  float ptMax = 0.;


  for(unsigned icand=0;icand<pfCandidateColl->size(); icand++) {
    const reco::PFCandidate pfCandidate = pfCandidateColl->at(icand);      
    
    int id = pfCandidate.particleId();
    if(abs(id) != 3) continue;

    if(reco::deltaR(pfJet,pfCandidate)>0.5) continue;	    
    
    double pt =  pfCandidate.pt();
    if(pt>ptMax){
      ptMax = pt;
      pfMuonIndex = (int) icand; 
    }
  }

  return pfMuonIndex;   

}


double
HiInclusiveJetAnalyzer::getPtRel(const reco::PFCandidate lep, const pat::Jet& jet )
{
  
  float lj_x = jet.p4().px();
  float lj_y = jet.p4().py();
  float lj_z = jet.p4().pz();
  
  // absolute values squared
  float lj2  = lj_x*lj_x+lj_y*lj_y+lj_z*lj_z;
  float lep2 = lep.px()*lep.px()+lep.py()*lep.py()+lep.pz()*lep.pz();
  
  // projection vec(mu) to lepjet axis
  float lepXlj = lep.px()*lj_x+lep.py()*lj_y+lep.pz()*lj_z;
  
  // absolute value squared and normalized
  float pLrel2 = lepXlj*lepXlj/lj2;
  
  // lep2 = pTrel2 + pLrel2
  float pTrel2 = lep2-pLrel2;
  
  return (pTrel2 > 0) ? std::sqrt(pTrel2) : 0.0;
}
				     					
DEFINE_FWK_MODULE(HiInclusiveJetAnalyzer);
