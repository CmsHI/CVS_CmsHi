#include "UserCode/HafHistogram/interface/HTupleManager.h"
#include "UserCode/HafHistogram/interface/HColumn.h"
#include "UserCode/HafHistogram/interface/HHistID.h"
#include "UserCode/HafHistogram/interface/HHistogram.h"
#include "UserCode/HafHistogram/interface/HTuple.h"


#ifdef __CINT__
// ##################################################
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

//HTupleManager
#pragma link C++ class HTupleManager;
#pragma link C++ function operator << ( ostream &, const HTupleManager & );

//Histograms and Ntuple
#pragma link C++ class HHistogram;
#pragma link C++ class HEnergyHistogram;
#pragma link C++ class HMassHistogram;
#pragma link C++ class HMomentumHistogram;
#pragma link C++ class HEoverPHistogram;
#pragma link C++ class HMoverPHistogram;
#pragma link C++ class HDalitzPlot;
#pragma link C++ class HTuple;
#pragma link C++ class HColumn;
#pragma link C++ class HHistID;
#endif
