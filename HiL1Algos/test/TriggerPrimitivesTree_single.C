#define TriggerPrimitivesTree_single_cxx
#include "TriggerPrimitivesTree_single.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <sstream>

typedef struct{
  int eta;
  int phi;
  int et;
} jet;

int sort_func_jet(const void *a, const void *b);

void print_jets(jet *clusters, int jet_length, int threshold);

void TriggerPrimitivesTree_single::Loop(int single_event, 
					int threshold,
					enum CALIBRATION_TYPE calibration,
					enum SUBTRACT_ALGORITHM algorithm,
					bool histo)
{
  //bool histo = false;

  double calibrations[22][18] = {{1.15021,1.1617,1.09255,1.10034,1.05117,1.06726,1.04628,1.06002,1.03023,1.06158,1.04628,1.08327,1.11612,1.0757,1.06116,1.12118,1.11133,1.16334},{0.869181,0.901389,0.860471,0.862766,0.869961,0.851587,0.855589,0.857474,0.860186,0.864442,0.882541,0.884787,0.859993,0.882804,0.889765,0.8835,0.88957,0.897877},{0.710014,0.739819,0.73311,0.730769,0.725103,0.700299,0.727856,0.717856,0.72692,0.715863,0.737418,0.746626,0.724311,0.735,0.733118,0.723094,0.739524,0.746308},{1.39523,1.35101,1.30976,1.3359,1.35835,1.31944,1.37919,1.29388,1.30335,1.38229,1.35357,1.29316,1.32888,1.29345,1.30233,1.34742,1.35393,1.36188},{0.342004,0.333466,0.339501,0.35329,0.335445,0.321501,0.333507,0.302929,0.333562,0.324417,0.335131,0.322134,0.360791,0.381577,0.447483,0.33654,0.349346,0.345128},{1.20258,1.24066,1.21715,1.22134,1.16126,1.23997,1.1695,1.18346,1.21758,1.10675,1.25416,1.22021,1.33201,1.34966,1.36496,1.2752,1.33242,1.28232},{2.15998,2.37688,2.33706,2.30082,2.09611,2.30727,2.26388,2.24047,2.39219,2.23086,2.31064,2.35843,2.55556,2.33311,2.59526,2.33941,2.47076,2.49418},{1.746,1.60612,1.70367,1.71116,1.70264,1.7715,1.74193,1.78395,1.74244,1.72117,1.85885,1.74684,1.76789,1.75871,1.72578,1.87434,1.88395,1.74717},{1.57476,1.43395,1.52489,1.55819,1.56717,1.59286,1.58757,1.60398,1.54942,1.62772,1.61683,1.5708,1.63283,1.6641,1.61671,1.66692,1.64632,1.59669},{1.45387,1.27106,1.36162,1.37916,1.44181,1.39778,1.44274,1.43073,1.37793,1.41611,1.44537,1.39338,1.46244,1.44248,1.41319,1.47118,1.435,1.39099},{1.30422,1.28326,1.27937,1.29314,1.29771,1.23934,1.3269,1.31936,1.29365,1.31204,1.32622,1.28697,1.28618,1.30865,1.30382,1.36299,1.3313,1.27413},{1.30755,1.26631,1.25501,1.31032,1.25131,1.32342,1.29595,1.26107,1.27034,1.34703,1.30818,1.32169,1.34848,1.29121,1.2897,1.31693,1.29628,1.33119},{1.44975,1.39874,1.37304,1.42104,1.34536,1.40497,1.39995,1.35509,1.34862,1.48276,1.37764,1.42079,1.53142,1.47355,1.41359,1.46126,1.4235,1.37391},{1.62337,1.61378,1.54441,1.59321,1.55897,1.59874,1.61214,1.55815,1.63046,1.64987,1.54127,1.63864,1.66058,1.64013,1.61318,1.65129,1.6305,1.57057},{1.7251,1.75056,1.7017,1.76582,1.74034,1.7423,1.73857,1.76953,1.80516,1.76525,1.73043,1.83683,1.82047,1.8758,1.80993,1.82697,1.74689,1.79494},{2.21754,2.48597,2.13515,2.22315,2.22772,2.25102,2.30965,2.04738,2.23947,2.10869,2.43166,2.30482,2.43603,2.44033,2.35569,2.34668,2.51522,2.40645},{1.30108,1.42621,1.22578,1.24068,1.28921,1.22193,1.29481,1.21767,1.25153,1.1856,1.30184,1.27881,1.27949,1.37,1.3486,1.39538,1.28199,1.30757},{0.348159,0.366204,0.331869,0.370462,0.341654,0.324673,0.3868,0.349385,0.333655,0.352277,0.361642,0.329835,0.382107,0.365629,0.360043,0.373804,0.360343,0.354137},{1.4211,1.33596,1.32587,1.35489,1.35266,1.35461,1.36634,1.34083,1.37629,1.41624,1.39508,1.35812,1.31872,1.31016,1.26502,1.36588,1.35151,1.28126},{0.722187,0.691272,0.714942,0.705766,0.698455,0.71473,0.711857,0.706418,0.724642,0.725654,0.729899,0.744266,0.71213,0.710247,0.714753,0.722171,0.728508,0.707433},{0.861474,0.835367,0.857259,0.816674,0.823774,0.849683,0.836981,0.832222,0.835646,0.86055,0.863477,0.861714,0.84387,0.831828,0.856649,0.847833,0.862537,0.843509},{1.0985,1.05472,1.03236,1.00721,1.032,1.06602,1.09489,1.00805,0.967884,1.09048,1.02741,1.04029,1.04993,1.03175,1.05616,1.04726,1.05871,1.05686}};
  
  int digital_calibrations[22] = {2, 2, 2, 2, 4, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 4, 2, 2, 2, 2};   
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();  
  Long64_t nbytes = 0, nb = 0;
  
  TH2I *original_boxplot, *subtracted_boxplot;
  TH2I *original_map, *subtracted_map;
  
  Long64_t ientry = LoadTree(single_event);
  if (ientry < 0) return;    
  nb = fChain->GetEntry(single_event);   nbytes += nb;

  if(histo)
  {
    stringstream maptit1, maptit2;
    maptit1 << "Detector Map before subtraction, event #" << event;
    maptit2 << "Detector Map after subtraction, event #" << event;
    original_map = new TH2I("original_map",maptit1.str().c_str(),22,0,22,18,0,18);
    subtracted_map = new TH2I("subtracted_map",maptit2.str().c_str(),22,0,22,18,0,18);

    stringstream boxplot_title1, boxplot_title2;
    boxplot_title1 << "Region Et distribution before subtraction, event #" << event;
    original_boxplot = new TH2I("boxplot",boxplot_title1.str().c_str(), 22,0,22,100,0,100);
    boxplot_title2 << "Region Et distribution after subtraction, event #" << event;
    subtracted_boxplot = new TH2I("boxplot",boxplot_title2.str().c_str(), 22,0,22,100,0,100);
  }

  int fulldetector[22][18]; //[eta][phi]
  int RCTs[18][11][2]; //[region #][eta][phi]
  for(int i = 0; i < numRegions; i++)
  {
    fulldetector[caloRegionEtaIndex[i]][caloRegionPhiIndex[i]] = caloRegionEt[i];
    int rctnum = (9*(caloRegionEtaIndex[i]/11)) + (caloRegionPhiIndex[i]/2);
    RCTs[rctnum][caloRCTRegionEtaIndex[i]][caloRCTRegionPhiIndex[i]] = caloRegionEt[i];
  }

  if(histo)
  {
    for(int ieta = 0; ieta < 22; ieta++)
      for(int iphi = 0; iphi < 18; iphi++){
	original_map->Fill(ieta,iphi,fulldetector[ieta][iphi]);
	original_boxplot->Fill(ieta,fulldetector[ieta][iphi]);
      }
  }

  switch(calibration)
  {
  case IDEAL:
    for(int ieta = 0; ieta < 22; ieta++)
      for(int iphi = 0; iphi < 18; iphi++){
	fulldetector[ieta][iphi] *= calibrations[ieta][iphi];
      }
    break;
  case DIGITAL:      
    for(int ieta = 0; ieta < 22; ieta++)
      for(int iphi = 0; iphi < 18; iphi++){
	fulldetector[ieta][iphi] /= digital_calibrations[ieta];
      }
    break;
  default:
    break;
  }
  
  int rct_minimums[18];
  double rct_averages[18];
  for(int i = 0; i < 18; i++)
  {
    rct_minimums[i] = 500;
    rct_averages[i] = 0;
    
    for(int ieta = 0; ieta < 11; ieta++)
      for(int iphi = 0; iphi < 2; iphi++){
	if (RCTs[i][ieta][iphi] < rct_minimums[i])
	  rct_minimums[i] = RCTs[i][ieta][iphi];
	
	rct_averages[i] += RCTs[i][ieta][iphi];
      }
    rct_averages[i] /= 22;
  } 
  
  double eta_average[22];
  for(int ieta = 0; ieta < 22; ieta++){
    eta_average[ieta] = 0;
    for(int iphi = 0; iphi < 18; iphi++){
      eta_average[ieta] += fulldetector[ieta][iphi];
    }
    eta_average[ieta] /= 18;
  }
  
  switch(algorithm)
  {
  case RCT_MINIMUM:
    
    for(int ieta = 0; ieta < 22; ieta++)
      for(int iphi = 0; iphi < 18; iphi++){
	int rctnum = (9*(ieta/11))+(iphi/2);
	fulldetector[ieta][iphi] -= rct_minimums[rctnum];
	if(fulldetector[ieta][iphi] < 0)
	  fulldetector[ieta][iphi] = 0;
      }
    break;
    
  case RCT_AVERAGE:
    
    for(int ieta = 0; ieta < 22; ieta++)
      for(int iphi = 0; iphi < 18; iphi++){
	int rctnum = (9*(ieta/11))+(iphi/2);
	fulldetector[ieta][iphi] -= rct_averages[rctnum];
	if(fulldetector[ieta][iphi] < 0)
	  fulldetector[ieta][iphi] = 0;
      }
    break;
    
  case ETA_AVERAGE:
    
    for(int ieta = 0; ieta < 22; ieta++)
      for(int iphi = 0; iphi < 18; iphi++){
	fulldetector[ieta][iphi] -= eta_average[ieta];
	if(fulldetector[ieta][iphi] < 0)
	  fulldetector[ieta][iphi] = 0;
      }
    break;

  default:
    break;
  }

  if(histo)
  {
    for(int ieta = 0; ieta < 22; ieta++)
      for(int iphi = 0; iphi < 18; iphi++){
	subtracted_map->Fill(ieta,iphi,fulldetector[ieta][iphi]);
	subtracted_boxplot->Fill(ieta,fulldetector[ieta][iphi]);
      }
  }
  
  
  jet jets[18][2][3]; //[rct #][phi][jet #]
  int min_3x3[18];    //[rct #]
  
  for(int i = 0; i < 18; i++)
  {
    for(int j = 0; j < 2; j++) 
      for(int k = 0; k < 3; k++)
      {
	jets[i][j][k].et = -1;
	jets[i][j][k].phi = -1;
	jets[i][j][k].eta = -1;
      }
    min_3x3[i] = 65535;
  }
  
  for(int ieta = 1; ieta < 21; ieta++)
    for(int iphi = 0; iphi < 18; iphi++){
      
      int rctnum = (9*(ieta/11))+(iphi/2);
      int rctphi = iphi%2;
      
      int plusPhi =  (iphi != 17) ? iphi + 1: 0;
      int minusPhi =  (iphi != 0) ? iphi - 1: 17;
      
      int cluster = fulldetector[ieta-1][minusPhi] +
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
	if(cluster >= jets[rctnum][rctphi][0].et)
	{
	  jets[rctnum][rctphi][2] = jets[rctnum][rctphi][1];
	  jets[rctnum][rctphi][1] = jets[rctnum][rctphi][0];
	  jets[rctnum][rctphi][0].et = cluster;
	  jets[rctnum][rctphi][0].eta = ieta;
	  jets[rctnum][rctphi][0].phi = iphi;
	}
	else if (cluster >= jets[rctnum][rctphi][1].et)
	{
	  jets[rctnum][rctphi][2] = jets[rctnum][rctphi][1];
	  jets[rctnum][rctphi][1].et = cluster;
	  jets[rctnum][rctphi][1].eta = ieta;
	  jets[rctnum][rctphi][1].phi = iphi;
	}
	else if (cluster >= jets[rctnum][rctphi][2].et)
	{
	  jets[rctnum][rctphi][2].et = cluster;
	  jets[rctnum][rctphi][2].eta = ieta;
	  jets[rctnum][rctphi][2].phi = iphi;
	}	
      }
      
      // however, if the cluster is the smallest in the RCT then save it.
      if(cluster < min_3x3[rctnum])
	min_3x3[rctnum] = cluster;
      
    }
  
  if(algorithm == MIN_3X3)
  {
    for(int i = 0; i < 18; i++)
      for(int j = 0; j < 2; j++) 
	for(int k = 0; k < 3; k++)
	{
	  jets[i][j][k].et -= min_3x3[i];
	  if(jets[i][j][k].et < 0)
	    jets[i][j][k].et = 0;
	}
  }
  
  jet *head = &jets[0][0][0];
  
  qsort(head, 18*2*3, sizeof(jet), sort_func_jet);

  //print_jets(head, 18*2*3, threshold);
    
  if(histo)
  {
    TCanvas *c1 = new TCanvas();
    original_map->SetXTitle("#eta");
    original_map->SetYTitle("#phi");
    original_map->Draw("Lego2");

    TCanvas *c2 = new TCanvas();
    subtracted_map->SetXTitle("#eta");
    subtracted_map->SetYTitle("#phi");
    subtracted_map->Draw("Lego2");

    TCanvas *c3 = new TCanvas();
    original_boxplot->SetXTitle("#eta");
    original_boxplot->SetYTitle("Compressed Et");
    original_boxplot->Draw("box");

    TCanvas *c4 = new TCanvas();
    subtracted_boxplot->SetXTitle("#eta");
    subtracted_boxplot->SetYTitle("Compressed Et");
    subtracted_boxplot->Draw("box");
  }    
}

int sort_func_jet(const void *a, const void *b) 
{ 
  jet *ia = (jet *)a;
  jet *ib = (jet *)b;
  return (int)(ib->et - ia->et);
} 

void print_jets(jet *clusters, int jet_length, int threshold)
{
  cout << "Begin jet list." << endl;
  cout << "num\tet\teta\tphi" << endl;
  int i;
  for(i = 0; i < jet_length; i++)
  {
    if(clusters[i].et <= threshold) break;
    cout << i << ")\t" << clusters[i].et << "\t" << clusters[i].eta << "\t" << clusters[i].phi << endl;
  }
  cout << "Total jets: " << i << endl;
  cout << "End jet list." << endl;
}
