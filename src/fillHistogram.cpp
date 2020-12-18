#include "../include/fillHistogram.h"
#include <iostream>
extern double parsec;// = 3.0857 * pow(10,16); //one parsec is approximately 3.0857e16 meters
extern double distance;// = 200;  // assuming a distance of 200 parsec to the SN
extern double surface;// =  4 * M_PI * pow( (distance * parsec), 2);
extern double solidAngle;// = pow( 0.01,2) / surface; // square meter to square cm

void fillHistogram( TH2D &hist, const std::vector< snspectrum > &spectrum, const std::vector< double > &time, const double factor)
{
  std::vector< long int > fillnumber (hist.GetNbinsX()+2,0) ;
  
  for ( int i = 0; i < spectrum.size(); i++ )
  { 
    int tbin = hist.GetXaxis()->FindBin(-log10(time[i]));

    for ( int j = 0; j < spectrum[i].energy.size(); j++ )
      {
	double neutrinoFlux = spectrum[i].flux[j] * factor;	
	hist.Fill( -log10(time[i]), spectrum[i].energy[j], neutrinoFlux );
      }
    fillnumber[tbin]++;          
  }  
  
  for ( int i = 1; i <= hist.GetNbinsX(); i++ )
  {
    for ( int j = 1; j<= hist.GetNbinsY(); j++ )
    {
      if (fillnumber[i] != 0 )
	hist.SetBinContent(i,j, hist.GetBinContent(i,j) / fillnumber[i]);
    }
  }
}