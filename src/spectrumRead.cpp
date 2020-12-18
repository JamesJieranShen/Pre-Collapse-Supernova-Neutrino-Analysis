#include "../include/spectrumRead.h"

snspectrum spectrumRead(const std::string & path, double weightEnergy, double weightFlux)
{
  // Reading from spe_sum Spectrum files
  FILE *spe_sum = fopen(path.c_str(), "r");
      
  if(spe_sum == NULL)
    {
      std::string error_str = "File opening failed for " + path;
	perror(error_str.c_str());
    }
  
  snspectrum outspec;
  
  double _energy, _flux;
  
  while (fscanf(spe_sum, "%lG %lG", &_energy, &_flux)==2)
    {
      outspec.energy.push_back(weightEnergy * _energy);
      outspec.flux.push_back(weightFlux * _flux);
    }
  
  fclose(spe_sum);
  
  return outspec;  
}

snspectrum spectrumRead(const std::string & path)
{
  return spectrumRead(path,1.0, 1.0);
}