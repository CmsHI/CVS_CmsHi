typedef struct{
  int eta_center;
  int phi_center;
  int sumEt;
} TowerJet;

const int NETA = 88;
const int NPHI = 72;

TowerJet findTowerJet(double fulldetector[NETA][NPHI], bool circularJets, int jetRadius)
{

  int jetCircleDistance2 = (jetRadius-1)*(jetRadius-1) +
    (jetRadius-1)*(jetRadius-1); 
  
  TowerJet highestJet;
    
  highestJet.sumEt = -1;
  highestJet.phi_center = -1;
  highestJet.eta_center = -1;
    
  for(int ieta = jetRadius; ieta < NETA - jetRadius; ieta++){
    for(int iphi = 0; iphi < NPHI; iphi++){

      TowerJet temp;
      temp.sumEt = fulldetector[ieta][iphi];
      temp.eta_center = ieta;
      temp.phi_center = iphi;

      for(int ieta_i = ieta - jetRadius; ieta_i < ieta + jetRadius; ieta_i++)
      {
	for(int iphi_i = iphi - jetRadius; iphi_i < iphi + jetRadius; iphi_i++)
	{
	  //cut the corners off the square
	  if(circularJets)
	  {
	    int distance2 = (iphi-temp.phi_center)*(iphi-temp.phi_center) +
	      (ieta-temp.eta_center)*(ieta-temp.eta_center);
	    if(distance2 >= jetCircleDistance2)
	      continue;
	  }
	    
	  int realiphi_i;
	  (iphi_i < 0) ? realiphi_i = iphi_i + NPHI : realiphi_i = iphi_i;

	  temp.sumEt += fulldetector[ieta_i][realiphi_i];
	}
      }

      if(temp.sumEt > highestJet.sumEt)
	highestJet = temp;
    }
  }

  return(highestJet);
}
