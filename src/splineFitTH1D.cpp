#include "splineFitTH1D.h"
#include <iostream>
void spline3FitTH1D(TH1D &hist, const std::vector<int> &whichBinToFit)
{
  // definition and initialisation of x and y values
  std::vector<double> xval;
  std::vector<double> yval;

  for ( int i = 0; i < whichBinToFit.size(); i++ )
    {
      xval.push_back(hist.GetBinCenter(whichBinToFit[i]));
      yval.push_back(hist.GetBinContent(whichBinToFit[i]));
    }
        
  TSpline3 spline ( "interpolation", &xval[0], &yval[0], xval.size() );
   // fill the histogram with spline values
  for ( int i = 1; i <= hist.GetNbinsX(); i++ )
    {
      if ( hist.GetBinContent(i) == 0)
	{
	  double px = hist.GetBinCenter(i);
	  hist.SetBinContent(i,spline.Eval(px));
	}
    }
}


void spline1FitTH1D(TH1D &hist, const std::vector<int> &whichBinToFit)
{
  // definition and initialisation of x and y values
  std::vector<double> xval;
  std::vector<double> yval;

  for ( int i = 0; i < whichBinToFit.size(); i++ )
    {
      xval.push_back(hist.GetBinCenter(whichBinToFit[i]));
      yval.push_back(hist.GetBinContent(whichBinToFit[i]));
    }
       
  // fill the histogram with linear interpolated values
  for ( int i = 1; i <= hist.GetNbinsX(); i++ )
    {
      if ( hist.GetBinContent(i) == 0)
	{
	  int j = 0;
	  double pl, pr;
	  double px = hist.GetBinCenter(i);
	  
	  if (px < xval[0])
	    hist.SetBinContent(i,yval[0]);
	  else if (px > xval.back() )
	    hist.SetBinContent(i,yval.back());
	  else
	    {
	      while ( xval[j] < px ) j++;
	      pl = xval[j];
	      pr = xval[j+1];

	      double BinContent = ( yval[j+1] - yval[j] ) / ( pr - pl ) * ( px - pl ) + yval[j];
	      hist.SetBinContent(i,BinContent);
	    }
	}
    }
  
}
