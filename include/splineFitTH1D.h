#ifndef __SPLINEFITTH1D_H_INCLUDED__
#define __SPLINEFITTH1D_H_INCLUDED__

#include <vector>
#include <memory>

#include "TH1.h"
#include "TSpline.h"

void spline1FitTH1D(TH1D &hist, const std::vector<int> &whichBinToFit);

void spline3FitTH1D(TH1D &hist, const std::vector<int> &whichBinToFit);

#endif