#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TMath.h"
#include "TF1.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"
#include "TChain.h"

#include "TCut.h"
#include "TNtuple.h"

#include "THStack.h"

using namespace std;

static bool subtract = 0;
static int QID = 3;

static TString weightString;

static bool normLead = 0;

static int mixColor = 2;
static int dataColor = 1;
static int ppColor = 4;

static int centralBin = 8;
static int leadCut = 120;
static int subleadCut = 30;

static double sideMin = 0.1;
static double sideMax = TMath::Pi()/3 + 0.1;

static double sideCorrect = 1;

static const char* LUM = "#int L dt=150";

static bool plotSubtraction = 0;

static bool reweightCentrality = 1;

static const double pi = TMath::Pi();

static TCut lead = Form("pt1>%d",leadCut);
static TCut dijet = Form("pt1>%d && pt2>%d",leadCut,subleadCut);

static TCut deltaPhi = "abs(dphi)>2.0944";
static TCut side = Form("pt1>%d && pt2>%d && abs(dphi)>%f && abs(dphi)<%f",leadCut,subleadCut, sideMin, sideMax);

static TCut jetID = "trkMax1 > 4 || trkMax2 > 4";
static TCut noise = "noise < 0"; // Gplus Pile-Up cut also included
static TCut vtx = "abs(vz)<15";

TCut weight("weight*(pthat > 80)");

