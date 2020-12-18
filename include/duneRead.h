#ifndef __DUNEREAD_H_INCLUDED__
#define __DUNEREAD_H_INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <sstream>

#include "spectrumRead.h"

struct dunedata
{
  // from lightcurve files:
  std::vector<double> time;      // time to collapse [s] 
  std::vector<int> id;           // unique identification number for this point of time; data files are named by this id

  // from spe_sum files:
  std::vector< snspectrum > sum; // spectrum of anti-electron-neutrino
  std::vector< snspectrum > nue; // spectrum of anti-mu/tau-neutrino
  std::vector< snspectrum > nuebar;  // spectrum of electron-neutrino
  std::vector< snspectrum > es;  // spectrum of mu/tau-neutrino
  };

dunedata duneRead(const std::string & lightcurvePath, const std::string & dataPath, const std::string & option, const double factor);

#endif
