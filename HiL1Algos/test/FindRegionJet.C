#include "TMath.h"

typedef struct{
  int eta;
  int phi;
  double sumEt;
  double realEta;
  double realPhi;
} RegionJet;

const int NETA_REGIONS = 22;
const int NPHI_REGIONS = 18;

double regionEta(int etaIndex);
double regionPhi(int phiIndex);

RegionJet* findRegionJet(double fulldetector[NETA_REGIONS][NPHI_REGIONS])
{
  RegionJet *highestJet = new RegionJet[2];  
  highestJet[0].sumEt = -1;
  highestJet[0].phi = -1;
  highestJet[0].eta = -1;
  highestJet[1].sumEt = -1;
  highestJet[1].phi = -1;
  highestJet[1].eta = -1;  

  //Find highest jet first
  for(int ieta = 1; ieta < NETA_REGIONS-1; ieta++)
  {
    for(int iphi = 0; iphi < NPHI_REGIONS; iphi++)
    {	
      int plusPhi =  (iphi != NPHI_REGIONS-1) ? iphi + 1: 0;
      int minusPhi =  (iphi != 0) ? iphi - 1: NPHI_REGIONS-1;

      RegionJet cluster;
      cluster.eta = ieta;
      cluster.phi = iphi;
      cluster.sumEt = fulldetector[ieta-1][minusPhi] +
	fulldetector[ieta-1][iphi] +		
	fulldetector[ieta-1][plusPhi] +		
	fulldetector[ieta][minusPhi] +		
	fulldetector[ieta][iphi] +		
	fulldetector[ieta][plusPhi] +		
	fulldetector[ieta+1][minusPhi] +		
	fulldetector[ieta+1][iphi] +		
	fulldetector[ieta+1][plusPhi];

      //if the region is a local maximum...
      if((fulldetector[ieta][iphi] >= fulldetector[ieta-1][minusPhi]) && 
	 (fulldetector[ieta][iphi] >= fulldetector[ieta-1][iphi]) &&	
	 (fulldetector[ieta][iphi] >= fulldetector[ieta-1][plusPhi]) && 
	 (fulldetector[ieta][iphi] >= fulldetector[ieta][minusPhi]) && 
	 (fulldetector[ieta][iphi] >= fulldetector[ieta][plusPhi]) &&	
	 (fulldetector[ieta][iphi] >= fulldetector[ieta+1][minusPhi]) &&
	 (fulldetector[ieta][iphi] >= fulldetector[ieta+1][iphi]) &&	
	 (fulldetector[ieta][iphi] >= fulldetector[ieta+1][plusPhi]))
      {
	// and if the cluster is bigger than one of the jets
	// then add the cluster to the list of jets.
	if(cluster.sumEt >= highestJet[0].sumEt)
	{
	  highestJet[0] = cluster;
	}
      }
    }
  }

  //Find subleading jet (run separately to avoid overlapping jets)
  for(int ieta = 1; ieta < NETA_REGIONS-1; ieta++)
  {
    for(int iphi = 0; iphi < NPHI_REGIONS; iphi++)
    {
      //do not overlap with the largest jet.
      if( (abs(ieta-highestJet[0].eta) <= 2) &&
	  (abs(iphi-highestJet[0].phi) <= 2))
	continue;
	
      int plusPhi =  (iphi != NPHI_REGIONS-1) ? iphi + 1: 0;
      int minusPhi =  (iphi != 0) ? iphi - 1: NPHI_REGIONS-1;

      RegionJet cluster;
      cluster.eta = ieta;
      cluster.phi = iphi;
      cluster.sumEt = (fulldetector[ieta-1][minusPhi] +
		       fulldetector[ieta-1][iphi] +		
		       fulldetector[ieta-1][plusPhi] +		
		       fulldetector[ieta][minusPhi] +		
		       fulldetector[ieta][iphi] +		
		       fulldetector[ieta][plusPhi] +		
		       fulldetector[ieta+1][minusPhi] +		
		       fulldetector[ieta+1][iphi] +		
		       fulldetector[ieta+1][plusPhi]);

      //if the region is a local maximum...
      if((fulldetector[ieta][iphi] >= fulldetector[ieta-1][minusPhi]) && 
	 (fulldetector[ieta][iphi] >= fulldetector[ieta-1][iphi]) &&	
	 (fulldetector[ieta][iphi] >= fulldetector[ieta-1][plusPhi]) && 
	 (fulldetector[ieta][iphi] >= fulldetector[ieta][minusPhi]) && 
	 (fulldetector[ieta][iphi] >= fulldetector[ieta][plusPhi]) &&	
	 (fulldetector[ieta][iphi] >= fulldetector[ieta+1][minusPhi]) &&
	 (fulldetector[ieta][iphi] >= fulldetector[ieta+1][iphi]) &&	
	 (fulldetector[ieta][iphi] >= fulldetector[ieta+1][plusPhi]))
      {
	// and if the cluster is bigger than one of the jets
	// then add the cluster to the list of jets.
	if(cluster.sumEt >= highestJet[1].sumEt)
	{
	  highestJet[1] = cluster;
	}
      }
    }
  }
  
  for(int i = 0; i < 2; i++)
  {
    highestJet[i].realEta = regionEta(highestJet[i].eta);
    highestJet[i].realPhi = regionPhi(highestJet[i].phi);
  }  
    
  return(highestJet);  
}

double regionEta(int etaIndex)
{
  double etaBounds[23]={
    -4.5,
    -4,
    -3.5,
    -3,
    -2.868,
    -2.172,
    -1.74,
    -0.087*16,
    -0.087*12,
    -0.087*8,
    -0.087*4,
    0,
    0.087*4,
    0.087*8,
    0.087*12,
    0.087*16,
    1.74,
    2.172,
    2.868,
    3,
    3.5,
    4,
    4.5
  };
  
  return(etaBounds[etaIndex]);
}

double regionPhi(int phiIndex)
{
  if(phiIndex < 9)
    return(-(9-phiIndex)*TMath::Pi()/9.);
  else
    return((phiIndex-9)*TMath::Pi()/9.);
}
