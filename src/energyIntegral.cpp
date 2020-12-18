#include "../include/energyIntegral.h"
#include <iostream>
#include <iomanip>
void energyIntegral( const TH2D &hist, double background, bool include_bg)
{
  
  std::string name = (std::string)hist.GetName()  + std::string("_energyIntegral");
  if (include_bg) name = name + std::string("_withbg");
  
  std::string title = (std::string)hist.GetTitle()  + std::string(" (energy integral)");
  
  int timeBinNum = hist.GetNbinsX();
  double timeLow = hist.GetXaxis()->GetBinLowEdge(1);
  double timeUp = hist.GetXaxis()->GetBinUpEdge(timeBinNum);

  std::stringstream ss;
  ss << std::setprecision(0) << std::fixed << background;
  std::string bgname = "bg_" + ss.str();
    
  TH1D BG (bgname.c_str(), "background histogram", timeBinNum, timeLow, timeUp); 
 
  
  TH1D output (name.c_str(), title.c_str(), timeBinNum, timeLow, timeUp);
  output.Sumw2();
  
  double signalcounter [timeBinNum+2];
  double backgroundcounter [timeBinNum+2];
  
  for ( int i = 1; i <= hist.GetNbinsX(); i++ )
  {
    for ( int j = 1; j <= hist.GetNbinsY(); j++ )
    {
      output.Fill( hist.GetBinCenter(i), hist.GetBinContent(i,j));// * ( hist.GetYaxis()->GetBinUpEdge(i) - hist.GetYaxis()->GetBinLowEdge(i) ) );
    }  
    signalcounter[i] = output.GetBinContent(i);
    
    double bg  = background * ( pow(10, -hist.GetBinLowEdge(i)) - pow(10, -hist.GetBinLowEdge(i+1)) ) ;
    
    if ( include_bg ) output.Fill( hist.GetBinCenter(i), bg); 
    
    BG.Fill(hist.GetBinCenter(i), bg);
    
    backgroundcounter[i] = bg;
    
    output.SetBinError(i, sqrt(2*backgroundcounter[i] + signalcounter[i] ) );
  }
  output.Rebin(5)->Write();
  if ( background != 0.0 )
    BG.Rebin(5)->Write();
}

void energyIntegral( const TH2D &hist)
{
  energyIntegral(hist,0,false);
}