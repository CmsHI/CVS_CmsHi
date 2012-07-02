const int NETA = 22;
const int NPHI = 18;

typedef struct{
  int eta;
  int phi;
  int et;
} RegionJet;

RegionJet findRegionJet(double fulldetector[NETA][NPHI])
{
  RegionJet highestJet;  
  highestJet.et = -1;
  highestJet.eta = -1;
  highestJet.phi = -1;
    
  for(int ieta = 1; ieta < NETA-1; ieta++)
    for(int iphi = 0; iphi < NPHI; iphi++){
	
      int plusPhi =  (iphi != 17) ? iphi + 1: 0;
      int minusPhi =  (iphi != 0) ? iphi - 1: 17;

      RegionJet cluster;
      cluster.eta = ieta;
      cluster.phi = iphi;
      cluster.et = fulldetector[ieta-1][minusPhi] +
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
	if(cluster.et >= highestJet.et)
	{
	  highestJet = cluster;
	}
      }
    }
    
  return(highestJet);  
}
