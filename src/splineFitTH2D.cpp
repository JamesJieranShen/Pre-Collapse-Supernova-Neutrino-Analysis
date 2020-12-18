#include "splineFitTH2D.h"
#include <iostream>
// determine the nonzero columns of a histogram
std::vector<int> nonzero(const TH2D &hist)
{
  std::vector<int> outvector;
  for (int i = 1; i<= hist.GetNbinsX(); i++)
    {
      bool counter = false;
      
      for (int j = 1; j <= hist.GetNbinsY(); j++)
	{
	  if ( hist.GetBinContent( i,j ) !=0 )
	  {
	    counter = true; 
	    break;
	  }
	}
      if ( counter == true ) // i.e. if the slice along Y in i is nonzero append i to nonzero
	{
	  outvector.push_back(i);
	}
    }
  return outvector;
}

// Spline interpolation using Spline3 class
void spline3FitTH2D(TH2D &hist)
{
  std::vector< TH1D > histograms = TwoDtoOneD ( hist );
  
  const std::vector<int> toFit = nonzero( hist );
  
  for ( int i = 1; i <= histograms.size(); i++ )
    { 
      spline3FitTH1D(histograms[i-1],toFit);
      
      for (int j = toFit[0]; j <= toFit.back(); j++ )
        {
	  hist.SetBinContent(j, i, histograms[i-1].GetBinContent(j));
	}
    }
}

// Spline interpolation using linear interpolation
void spline1FitTH2D(TH2D &hist)
{
  std::vector< TH1D > histograms = TwoDtoOneD ( hist );
  
  const std::vector<int> toFit = nonzero( hist );
   
  for ( int i = 1; i <= histograms.size(); i++ )
    {
      spline1FitTH1D(histograms[i-1], toFit);
      
      for ( int j = 1; j <= toFit.back(); j++ )
	{
	  hist.SetBinContent(j,i,histograms[i-1].GetBinContent(j));
	}
    }
}
