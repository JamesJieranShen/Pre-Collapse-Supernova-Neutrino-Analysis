#include "../include/clearBins.h"

void clearBins( TH2D &hist, const double cutValue )
{
  for ( int i = 1; i <= hist.GetNbinsX(); i++)
  {
      for ( int j = 1; j <= hist.GetNbinsY(); j++ )
      {
	if( hist.GetBinContent(i, j) < cutValue) 
	    hist.SetBinContent(i, j, 0);
      }
  }  
}