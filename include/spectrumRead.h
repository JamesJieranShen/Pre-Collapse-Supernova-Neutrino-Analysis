#ifndef __SPECTRUMREAD_H_INCLUDED__
#define __SPECTRUMREAD_H_INCLUDED__

// load C++ standard libraries
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>

struct snspectrum
{
  std::vector<double> energy; // E[MeV]
  std::vector<double> flux;   // Number[MeV^-1 s^-1]
};

snspectrum spectrumRead(const std::string & path, double weightEnergy, double weightFlux);

snspectrum spectrumRead(const std::string & path);

#endif
