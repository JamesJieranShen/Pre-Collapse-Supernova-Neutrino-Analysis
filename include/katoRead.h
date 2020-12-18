#ifndef __KATOREAD_H_INCLUDED__
#define __KATOREAD_H_INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <sstream>

#include "spectrumRead.h"

struct sndata
{
  // from lightcurve files:
  std::vector<double> time;      // time to collapse [s] 
  std::vector<int> id;           // unique identification number for this point of time; data files are named by this id
  std::vector<double> Eanu;      // energy luminosity of anti-electron-neutrino
  std::vector<double> Eamu;      // energy luminosity of anti-mu/tau-neutrino
  std::vector<double> Enu;       // energy luminosity of electron-neutrino
  std::vector<double> Emu;       // energy luminosity of mu/tau-neutrino
  std::vector<double> Number_nu; // number luminosity of elctron-neutrino
  std::vector<double> Number_anu; // number luminosity of anti-elctron-neutrino
  std::vector<double> Number_mu; // number luminosity of anti-mu/tau- & mu/tau-neutrino

  // from spe_sum files:
  std::vector< snspectrum > anu; // spectrum of anti-electron-neutrino
  std::vector< snspectrum > amu; // spectrum of anti-mu/tau-neutrino
  std::vector< snspectrum > nu;  // spectrum of electron-neutrino
  std::vector< snspectrum > mu;  // spectrum of mu/tau-neutrino
  };

sndata katoRead(const std::string & path);

#endif
