#ifndef __FILLHISTOGRAM_H_INCLUDED__
#define __FILLHISTOGRAM_H_INCLUDED__

#include <vector>
#include <cmath> 
#include <memory>

#include "TH2.h"

#include "spectrumRead.h"


void fillHistogram( TH2D &hist, const std::vector<snspectrum> &spectrum, const std::vector<double> &time, const double factor);

#endif