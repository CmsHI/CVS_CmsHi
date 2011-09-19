#include <TFile.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TRandom.h>

#include <TNtuple.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>

#define PI 3.14159

static const int MAX = 1000;

double deltaPhi(double phi1, double phi2) {
	double dePhi = fabs(phi1 - phi2);
	if (dePhi > 3.1415926) dePhi = 2 * 3.1415926 - dePhi;
	return dePhi;
}

double deltaR(double eta1, double phi1, double eta2, double phi2) {
	double deta = eta1-eta2;
	double dphi = deltaPhi(phi1,phi2);
	return sqrt(deta*deta+dphi*dphi);
}

class Particles{
public:
	void set(int i, float a, float b, float c){
		pt[i] = a;
		eta[i] = b;
		phi[i] = c;
	}
	float pt[MAX];
	float eta[MAX];
	float phi[MAX];
	int n;
};

class Isolations{
public:
	
	float sigmaIetaIeta[MAX];
	float seedTime[MAX];
	
	float e3x3[MAX];
	float eRight[MAX];
	float eLeft[MAX];
	
	float eTop[MAX];
	float eBottom[MAX];
	float eMax[MAX];
	
	float cr4[MAX];
	float cc4[MAX];
	float ct4PtCut[MAX];
	
	UChar_t isEE[MAX];
	UChar_t isEle[MAX];
	
	bool notSpike(int i){
		double suisse = (1 - (eRight[i]+eLeft[i]+eTop[i]+eBottom[i])/eMax[i]);
		bool spikeCut =
		(suisse < 0.9
		 &&
		 fabs(seedTime[i]) < 3
		 &&
		 sigmaIetaIeta[i]>0.002
		 )||isEE[i];
		return spikeCut;
	}
	
	bool select(int i){
		bool isoCut = (cr4[i]+cc4[i]+ct4PtCut[i])<5;
		return notSpike(i) && isoCut && !isEle[i];
	}
	
	bool id(int i){
		bool sigmaIetaIetaCut = sigmaIetaIeta[i]<0.011;
		return sigmaIetaIetaCut;
	}
};


class GammaJet{
public:
	
	GammaJet(){
		photonpt = 0;
		jetpt = 0;
		id = 0;
		dphi = -99;
		photonjet = 0;
	}
	
	double photonpt;
	double photonjet;
	
	double eta;
	double phi;
	
	double deta;
	double dphi;
	
	double jetpt;
	
	bool id;
	
};


void analyzePhotonJet(){
	
	double cutDeltaPhi = PI/2;
	double cutEtaPhoton = 1.3;
	double cutEtaJet = 2;
	
	double cutPtPhoton = 10;
	double cutPtJet = 0;
	
	double cone = 0.3;
	
	// Tree variables
	Particles photons;
	Particles jets;
	Particles tracks;
	Isolations isolations;
	int cbin;
	
	const char* inname = "superfile.root";
	const char* outname = "results.root";
	
	TFile* inf = new TFile(inname,"read");
	
	TTree* tjet = (TTree*)inf->Get("akPu3PFJetAnalyzer/t");
	TTree* tphoton = (TTree*)inf->Get("NTuples/Analysis");
	TTree* t = (TTree*)inf->Get("hltanalysis/HltTree");
	
	tjet->SetBranchAddress("jtpt",jets.pt);
	tjet->SetBranchAddress("jteta",jets.eta);
	tjet->SetBranchAddress("jtphi",jets.phi);
	tjet->SetBranchAddress("nref",&jets.n);
	
	tphoton->SetBranchAddress("pt",photons.pt);
	tphoton->SetBranchAddress("eta",photons.eta);
	tphoton->SetBranchAddress("phi",photons.phi);
	tphoton->SetBranchAddress("nPhotons",&photons.n);
	
	tphoton->SetBranchAddress("eRight",isolations.eRight);
	tphoton->SetBranchAddress("eLeft",isolations.eLeft);
	tphoton->SetBranchAddress("eTop",isolations.eTop);
	tphoton->SetBranchAddress("eBottom",isolations.eBottom);
	tphoton->SetBranchAddress("eMax",isolations.eMax);
	
	tphoton->SetBranchAddress("seedTime",isolations.seedTime);
	
	tphoton->SetBranchAddress("cr4",isolations.cr4);
	tphoton->SetBranchAddress("cc4",isolations.cc4);
	tphoton->SetBranchAddress("ct4PtCut",isolations.ct4PtCut);
	
	tphoton->SetBranchAddress("sigmaIetaIeta",isolations.sigmaIetaIeta);
	
	tphoton->SetBranchAddress("isEE",isolations.isEE);
	tphoton->SetBranchAddress("isEle",isolations.isEle);
	
	t->SetBranchAddress("hiBin",&cbin);
	
	//   tphoton->SetBranchAddress("pt",photons.pt);
	
	TFile* outf = new TFile(outname,"recreate");
	
	TNtuple* nt = new TNtuple("nt","","phpt:jtpt:phjt:dphi:deta:bin:id");
	TNtuple* tnt = new TNtuple("tnt","","phpt:jtpt:phjt:dphi:deta:bin:id");
	
	TH2D* hPt2D = new TH2D("hPt2D",";p_{T}^{#gamma};p_{T}^{jet}",200,0,100,200,0,100);
	TH1D* hPtJet = new TH1D("hPtJet",";p_{T}^{jet}",200,0,100);
	
	int Nevents = t->GetEntries();
	for(int iev = 0; iev < Nevents; ++iev){
		t->GetEntry(iev);
		tphoton->GetEntry(iev);
		tjet->GetEntry(iev);
		
		GammaJet gj;
		for(int i = 0; i < photons.n; ++i){
			
			if(!isolations.select(i)) continue;
			if(photons.pt[i] < cutPtPhoton) continue;
			if(fabs(photons.eta[i]) > cutEtaPhoton) continue;
			if(photons.pt[i] > gj.photonpt){
				gj.photonpt = photons.pt[i];
				gj.eta = photons.eta[i];
				gj.phi = photons.phi[i];
				gj.id = isolations.id(i);
			}
		}
		
		for(int i = 0; i < jets.n; ++i){
			if(jets.pt[i] < cutPtJet) continue;
			if(fabs(jets.eta[i]) > cutEtaJet) continue;
			
			double dphi = deltaPhi(gj.phi,jets.phi[i]);
			double dr = deltaR(gj.eta,gj.phi,jets.eta[i],jets.phi[i]);
			double deta = jets.eta[i] - gj.eta;
			
			if(dr < cone) gj.photonjet = jets.pt[i];
			if(dphi > cutDeltaPhi){
				gj.jetpt = jets.pt[i];
				gj.dphi = dphi;
				gj.deta = jets.eta[i] - gj.eta;
				tnt->Fill(gj.photonpt,jets.pt[i],gj.photonjet,dphi,gj.deta,cbin,gj.id);
				if(jets.pt[i] > gj.jetpt){
					gj.jetpt = jets.pt[i];
					gj.dphi = dphi;
					gj.deta = deta;
				}
				
			}
		}
		
		nt->Fill(gj.photonpt,gj.jetpt,gj.photonjet,gj.dphi,gj.deta,cbin,gj.id);
		
	}
	
	TCanvas* c1 = new TCanvas("c1","",800,800);
	c1->Divide(2,2);
	c1->cd(1);
	
	
	
	outf->Write();
	
}


