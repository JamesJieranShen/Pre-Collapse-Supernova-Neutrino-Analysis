#ifndef __ENERGYINTEGRAL_H_INCLUDED__
#define __ENERGYINTEGRAL_H_INCLUDED__

#include <memory>
#include <string>
#include <cmath>
#include <sstream>

#include "TH2.h"
#include "TH1.h"

void energyIntegral( const TH2D &hist);

void energyIntegral( const TH2D &hist, double background, bool include_bg);


#endif