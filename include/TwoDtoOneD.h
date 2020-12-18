#ifndef __TWODTOONED_H_INCLUDED__
#define __TWODTOONED_H_INCLUDED__

#include <vector>
#include <sstream>
#include <memory>

#include "TH1.h"
#include "TH2.h"

std::vector< TH1D >  TwoDtoOneD(const TH2D &histogram, const double xminval, const double xmaxval);

std::vector< TH1D >  TwoDtoOneD(const TH2D &histogram);

std::vector< TH1D >  TwoDtoOneDY(const TH2D &histogram, const double xminval, const double xmaxval);

std::vector< TH1D >  TwoDtoOneDY(const TH2D &histogram);

#endif