#ifndef __SNOWREAD_H_INCLUDED__
#define __SNOWREAD_H_INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <sstream>

#include "spectrumRead.h"

struct snowdata
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

snowdata snowRead(const std::string & lightcurvePath, const std::string & dataPath, int specifier);

#endif
