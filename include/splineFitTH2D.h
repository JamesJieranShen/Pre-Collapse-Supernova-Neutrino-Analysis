#ifndef __SPLINEFITTH2D_H_INCLUDED__
#define __SPLINEFITTH2D_H_INCLUDED__

#include <vector>
#include <memory>

#include "TH1.h"
#include "TH2.h"

#include "splineFitTH1D.h"
#include "TwoDtoOneD.h"

std::vector<int> nonzero(const TH2D &hist);

void spline3FitTH2D(TH2D &hist);

void spline1FitTH2D(TH2D &hist);

#endif