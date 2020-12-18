#include "fluxToFluence.h"

void fluxToFluence( TH2D * hist )
{
  int timeBinNum = hist->GetNbinsX();
  
  for ( int i = 1; i <= timeBinNum; i++ )
  {
    for ( int j = 1; j<= hist->GetNbinsY(); j++ )
    {
      double timeLow = hist->GetXaxis()->GetBinLowEdge(1);
      double timeUp = hist->GetXaxis()->GetBinUpEdge( hist->GetNbinsX() );
      
      double timeWidth = (-timeLow + timeUp) / timeBinNum ;
      double binContent = hist->GetBinContent(i,j) * ( pow(10, timeWidth*(timeBinNum-i+1) - timeUp) - pow( 10, timeWidth*(timeBinNum-i) - timeUp));
      hist->SetBinContent( i, j, binContent );      
    }
  }
}