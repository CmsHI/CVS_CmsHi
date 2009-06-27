#include <iostream>
#include <vector>

#define MAXCENTRALITYBINS 40

//Root macro for using centrality bins in analysis in root.

namespace CmsHi{

  static double hf[MAXCENTRALITYBINS] = {-0.5, 91.2201, 190.066, 289.348, 429.714, 610.668, 769.197, 1003.86, 1295.14, 1714.93, 2019.53, 2580.84, 3110.32, 3851.92, 4842.85, 5763.9, 7031.81, 8352.1, 9838.89, 12019.2, 14406.3, 16375.5, 19378.5, 23245.1, 25952.2, 28804.9, 33745.5, 37747, 42576, 46784.8, 52114.6, 57125.6, 64232.7, 72537.2, 82239.3, 89429.5, 99463.8, 109535, 120721, 136768}; // For 3_1_X. Used 2000 events.

  //static double hf[MAXCENTRALITYBINS] = { -3.79397, 41.8848, 100.592, 164.598, 245.863, 332.547, 425.167, 541.657, 686.035, 883.485, 1100.38, 1353.79, 1674.68, 2111.32, 2626.57, 3204.19, 3882.45, 4705.5, 5618.47, 6718.37, 7847.97, 9183.42, 10710.5, 12352, 14111.4, 15915.1, 18050.8, 20267.3, 22969.3, 25847.9, 29106.6, 32622.2, 36850.7, 41185, 46138.2, 51728.2, 57773.7, 66330.7, 76926.8, 88238.4}; // For 2_2_X. Used 14373 events.


  /*
 static double hfgen[MAXCENTRALITYBINS] = {};
 static double npart[MAXCENTRALITYBINS] = {};
 static double b[MAXCENTRALITYBINS] = {};
  */

class Centrality{
 public:

 Centrality(const char* label, int nbins) : label_(label), nbins_(nbins){
    
    bins_.reserve(nbins_);

    for(int i = 0; i < nbins_; ++i){
      if(label_ == "hf")
	bins_[i] = hf[i*(int)(MAXCENTRALITYBINS/nbins_)];
    }
}

  ~Centrality() {;}

  double getNpart() {return 0;}
  double getNcoll() {return 0;}
  double getNhard(){return 0;}
  double getB(){return 0;}

  int getBin(double value);
  void info();

 private:
  const char* label_;
  vector<double> bins_;
  int nbins_;

};

int Centrality::getBin(double value){

  int bin = -9;
  int ibin = -9;

  for(int i = 0; i< nbins_; i++){
    double min = bins_[i];

    if(value >= min) ibin  = i;
    //    if(value < min ) break;
  }

  if(label_ == "b")bin = ibin+1;
  else bin = nbins_ - ibin;

  if(ibin < 0) cout<<"Warning : Bin not determined correctly - "<<bin<<endl;

  return bin;
}

void Centrality::info(){
  std::cout<<"Centrality is based on "<<label_<<std::endl;
}


}
