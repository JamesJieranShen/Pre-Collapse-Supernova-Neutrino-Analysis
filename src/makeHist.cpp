#include "../include/makeHist.h"
#include <iomanip>
void makeHist(parameter &params, double background) // background only applies to energy integrals
{
  std::string histname;
  
  std::stringstream ss;
  ss << std::setprecision(0) << std::fixed << background;
  std::string bg = ss.str();
  
  if( background != 0.0 )
    histname = params.name + "_bg" + bg;
  else
    histname = params.name;
  
  TH2D hist (histname.c_str(), params.title.c_str(), params.timeBinNum, params.timeLow, params.timeUp, params.energyBinNum, params.energyLow, params.energyUp);
  
  fillHistogram(hist, params.spectrum, params.time,params.factor);
  spline3FitTH2D(hist);
  clearBins(hist, params.clear);
  
  hist.Write();
  
  energyIntegral(hist, background, true);
  energyIntegral(hist, background, false);
}

void makeHist(parameter &params)
{
  makeHist(params,0.0);
}