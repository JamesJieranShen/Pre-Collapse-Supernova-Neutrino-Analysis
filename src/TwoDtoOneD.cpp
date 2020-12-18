#include "../include/TwoDtoOneD.h"
#include <iostream>
std::vector< TH1D >  TwoDtoOneD(const TH2D &histogram, const double xminval, const double xmaxval) // returns slices along X
{
  const int binsX = histogram.GetNbinsX(); // reads out X size of histogram
  const int binsY = histogram.GetNbinsY(); // reads out Y size of histogram
  
  std::vector< TH1D >  output_vector;
  for ( int i = 1; i <= binsY; i++)
    {
      std::stringstream stst;
      stst << i;
  
      std::string name (histogram.GetName());
      name = name + "_slice" + stst.str();
      std::string title ( histogram.GetTitle() );
      title = title + " slice " + stst.str();
      
      TH1D appendTH1 (name.c_str(),title.c_str(),binsX,xminval,xmaxval);
           
      for ( int j = 1; j <= binsX; j++)
	{
	   appendTH1.SetBinContent(j,histogram.GetBinContent(j,i) );
	}
      
      output_vector.push_back(appendTH1);
    }
  return output_vector;
}

std::vector< TH1D >  TwoDtoOneD(const TH2D &histogram) // returns slices along X
{
  int binNum = histogram.GetNbinsX();
  
  double xminval = histogram.GetXaxis()->GetBinLowEdge(1);
  double xmaxval = histogram.GetXaxis()->GetBinUpEdge(binNum);
  
  return TwoDtoOneD(histogram, xminval, xmaxval);
}
std::vector< TH1D >  TwoDtoOneDY(const TH2D &histogram, const double yminval, const double ymaxval) // returns slices along Y
{
  
  const int binsX = histogram.GetNbinsX(); // reads out X size of histogram
  const int binsY = histogram.GetNbinsY(); // reads out Y size of histogram
  
  std::vector< TH1D >  output_vector;
  for ( int i = 1; i <= binsX; i++)
    {
      std::stringstream stst;
      stst << i;
  
      std::string name (histogram.GetName());
      name = name + "_slice" + stst.str();
      std::string title ( histogram.GetTitle() );
      title = title + " slice " + stst.str();
      
      TH1D appendTH1 (name.c_str(),title.c_str(),binsY,yminval,ymaxval);
           
      for ( int j = 1; j <= binsY; j++)
	{
	   appendTH1.SetBinContent(j,histogram.GetBinContent(i,j) );
	}
      
      output_vector.push_back(appendTH1);
    }
  return output_vector;
}

std::vector< TH1D >  TwoDtoOneDY(const TH2D &histogram) // returns slices along Y
{
  int binNum = histogram.GetNbinsY();
  
  double yminval = histogram.GetYaxis()->GetBinLowEdge(1);
  double ymaxval = histogram.GetYaxis()->GetBinUpEdge(binNum);
  
  return TwoDtoOneDY(histogram, yminval, ymaxval);
}