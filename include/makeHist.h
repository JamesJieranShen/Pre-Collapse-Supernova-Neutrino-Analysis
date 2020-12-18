#ifndef __MAKEHIST_H_INCLUDED__
#define __MAKEHIST_H_INCLUDED__

// load C++ standard libraries
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <sstream>
// load root libraries
#include "TFile.h"
#include "TH2.h"
//#include "TSpline.h"

// load other functions
#include "../include/clearBins.h"
#include "../include/splineFitTH2D.h"
#include "../include/fillHistogram.h"
#include "../include/energyIntegral.h"

struct parameter{
  
  // Histogram Bins
  int timeBinNum;
  double timeLow;
  double timeUp;
  
  int energyBinNum;
  double energyLow;
  double energyUp;
  
  // Spectrum that is about to be plotted
  std::vector<snspectrum> spectrum;
  
  // Time steps
  std::vector<double> time;
  
  // Histograms name and title 
  std::string name;
  std::string title;
  
  // clearBins parameter
  double clear;
  
  // multiplication factor, e.g. bin widths or solid angles
  double factor;
};

void makeHist(parameter &params);

void makeHist(parameter &params, double background);

#endif