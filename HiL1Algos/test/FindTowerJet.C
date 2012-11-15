typedef struct{
  int eta;
  int phi;
  double sumEt;
  double realEta;
  double realPhi;
} TowerJet;

//const int NETA_TOWERS = 82; //should be declared in calling file
const int NPHI_TOWERS = 72;

double towerEta(int etaIndex);
double towerPhi(int phiIndex, int etaIndex);

TowerJet* findTowerJet(double fulldetector[NETA_TOWERS][NPHI_TOWERS],
		       bool circularJets, int jetDiameter)
{
  int even = (jetDiameter%2 == 0) ? 1 : 0;
  int jetRadius = jetDiameter/2;

  //printf("jet radius: %d, even: %d\n",jetRadius,even);
  
  int jetCircleDistance2 = (jetRadius)*(jetRadius) + 1; 
  
  TowerJet *highestJet = new TowerJet[2];    
  highestJet[0].sumEt = -1;
  highestJet[0].phi = -1;
  highestJet[0].eta = -1;
  highestJet[1].sumEt = -1;
  highestJet[1].phi = -1;
  highestJet[1].eta = -1;

  //Find leading jet
  for(int ieta = jetRadius-even; ieta < NETA_TOWERS - jetRadius; ieta++)
  {
    for(int iphi = 0; iphi < NPHI_TOWERS; iphi++)
    {
      TowerJet temp;
      temp.sumEt = 0;
      temp.eta = ieta;
      temp.phi = iphi;

      for(int ieta_i = ieta - (jetRadius - even);
	  ieta_i <= ieta + jetRadius; ieta_i++)
      {
	for(int iphi_i = iphi - (jetRadius - even);
	    iphi_i <= iphi + jetRadius; iphi_i++)
	{
	  //cut the corners off the square ONLY CORRECT FOR ODD DIAMETER
	  if(circularJets)
	  {
	    int distance2 = (iphi_i-temp.phi)*(iphi_i-temp.phi) +
	      (ieta_i-temp.eta)*(ieta_i-temp.eta);
	    if(distance2 > jetCircleDistance2)
	      continue;
	  }
	    
	  int realiphi_i;
	  if(iphi_i < 0)
	    realiphi_i = iphi_i + NPHI_TOWERS;
	  else if(iphi_i >= NPHI_TOWERS)
	    realiphi_i = iphi_i%NPHI_TOWERS;
	  else
	    realiphi_i = iphi_i;
	  
	  // (iphi_i < 0) ? realiphi_i = iphi_i + NPHI_TOWERS :
	  //   realiphi_i = iphi_i;
	  // (iphi_i >= NPHI_TOWERS) ? realiphi_i = iphi_i%NPHI_TOWERS :
	  //   realiphi_i = iphi_i;

	  temp.sumEt += fulldetector[ieta_i][realiphi_i];
	  //printf("%d %d %lf\n",ieta_i,realiphi_i,fulldetector[ieta_i][realiphi_i]);
	}
      }

      //printf("%lf\n",temp.sumEt);
      if(temp.sumEt > highestJet[0].sumEt)
	highestJet[0] = temp;
    }
  }
  //printf("%lf\n",highestJet[0].sumEt);

  //find subleading jet
  for(int ieta = jetRadius - even; ieta < NETA_TOWERS - jetRadius; ieta++)
  {
    for(int iphi = 0; iphi < NPHI_TOWERS; iphi++)
    {
      //do not overlap with the largest jet.
      if( (abs(ieta-highestJet[0].eta) <= jetRadius*2) &&
	  (abs(iphi-highestJet[0].phi) <= jetRadius*2))
	continue;

      TowerJet temp;
      temp.sumEt = 0;
      temp.eta = ieta;
      temp.phi = iphi;
      
      for(int ieta_i = ieta - (jetRadius - even);
	  ieta_i <= ieta + jetRadius; ieta_i++)
      {
	for(int iphi_i = iphi - (jetRadius - even);
	    iphi_i <= iphi + jetRadius; iphi_i++)
	{
	  //cut the corners off the square ONLY CORRECT FOR ODD DIAMETER
	  if(circularJets)
	  {
	    int distance2 = (iphi_i-temp.phi)*(iphi_i-temp.phi) +
	      (ieta_i-temp.eta)*(ieta_i-temp.eta);
	    if(distance2 > jetCircleDistance2)
	      continue;
	  }

	  	    
	  int realiphi_i;
	  if(iphi_i < 0)
	    realiphi_i = iphi_i + NPHI_TOWERS;
	  else if(iphi_i >= NPHI_TOWERS)
	    realiphi_i = iphi_i%NPHI_TOWERS;
	  else
	    realiphi_i = iphi_i;
	  
	  // int realiphi_i;
	  // (iphi_i < 0) ? realiphi_i = iphi_i + NPHI_TOWERS :
	  //   realiphi_i = iphi_i;
	  // (iphi_i >= NPHI_TOWERS) ? realiphi_i = iphi_i%NPHI_TOWERS :
	  //   realiphi_i = iphi_i;

	  temp.sumEt += fulldetector[ieta_i][realiphi_i];
	}
      }

      if(temp.sumEt > highestJet[1].sumEt)
	highestJet[1] = temp;
    }
  }  
  
  for(int i = 0; i < 2; i++)
  {
    highestJet[i].realEta = towerEta(highestJet[i].eta);
    highestJet[i].realPhi = towerPhi(highestJet[i].phi,highestJet[i].eta);
  }

  //printf("%lf\n",highestJet[0].sumEt);
  return(highestJet);
}


double towerEta(int etaIndex)
{
  double etaBounds[42] = {
    0.043500,
    0.130500,
    0.217500,
    0.304500,
    0.391500,
    0.478500,
    0.565500,
    0.652500,
    0.739500,
    0.826500,
    0.913500,
    1.000500,
    1.087500,
    1.174500,
    1.261500,
    1.348500,
    1.435500,
    1.522500,
    1.609500,
    1.696500,

    1.785000,
    1.880000,
    1.986500,
    2.107500,
    2.252000,
    2.416000,
    2.575000,
    2.759000,
    2.934000,
    3.051500,
    3.226500,
    3.401500,
    3.576500,
    3.751500,
    3.926000,
    4.102000,
    4.277000,
    4.450500,
    4.627000,

    4.802500,
    5.040000
  };

  if(etaIndex < 42)
    return(-etaBounds[41-etaIndex]);
  else
    return(etaBounds[etaIndex-42]);

}

double towerPhi(int phiIndex, int etaIndex)
{
  double HBphiBounds[36] = {
    0.043633,
    0.130900,
    0.218166,
    0.305433,
    0.392699,
    0.479966,
    0.567232,
    0.654498,
    0.741765,
    0.829031,
    0.916298,
    1.003564,
    1.090831,
    1.178097,
    1.265364,
    1.352630,
    1.439897,
    1.527163,
    1.614429,
    1.701696,
    1.788962,
    1.876229,
    1.963495,
    2.050762,
    2.138028,
    2.225295,
    2.312561,
    2.399828,
    2.487094,
    2.574361,
    2.661627,
    2.748893,
    2.836160,
    2.923427,
    3.010693,
    3.097960    
  };

  double HEphiBounds[18] = {
    0.087266,
    0.261799,
    0.436332,
    0.610865,
    0.785398,
    0.959931,
    1.134464,
    1.308997,
    1.483530,
    1.658063,
    1.832596,
    2.007129,
    2.181662,
    2.356194,
    2.530727,
    2.705260,
    2.879793,
    3.054326
  };

  double HFphiBounds[18] = {
    -3.141593,
    -2.792527,
    -2.443461,
    -2.094395,
    -1.745329,
    -1.396263,
    -1.047198,
    -0.698132,
    -0.349066,
    -0.000000,   
    0.349066,
    0.698132,
    1.047198,
    1.396263,
    1.745329,
    2.094395,
    2.443461,
    2.792527
  };

  if(etaIndex < 2 || etaIndex > 79)
    return(HFphiBounds[phiIndex/4]);
  else if(etaIndex < 21 || etaIndex > 60)
  {
    if(phiIndex < 36)
      return(-HEphiBounds[(35-phiIndex)/2]);
    else
      return(HEphiBounds[(phiIndex-36)/2]);
  }
  else
  {
    if(phiIndex < 36)
      return(-HBphiBounds[(35-phiIndex)]);
    else
      return(HBphiBounds[(phiIndex-36)]);
  }
}
