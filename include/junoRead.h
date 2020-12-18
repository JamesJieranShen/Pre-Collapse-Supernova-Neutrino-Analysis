#ifndef __JUNOREAD_H_INCLUDED__
#define __JUNOREAD_H_INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <sstream>

#include "spectrumRead.h"

struct junodata
{
  // from lightcurve files:
  std::vector<double> time;      // time to collapse [s] 
  std::vector<int> id;           // unique identification number for this point of time; data files are named by this id

  // from spe_sum files:
  std::vector< snspectrum > sum; // spectrum of sum over all interaction channels
  std::vector< snspectrum > nue; // spectrum of electron neutrino C12 events
  std::vector< snspectrum > nuebar;  // spectrum of anti-electron neutrino C12 events
  std::vector< snspectrum > es;  // spectrum of electron scattering events
  std::vector< snspectrum > nc;  // spectrum of neutral current events
  std::vector< snspectrum > ibd;  // spectrum of inverse beta decay events
};

junodata junoRead(const std::string & lightcurvePath, const std::string & dataPath, const std::string & option, const double factor);

#endif
