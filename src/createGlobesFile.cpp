#include "../include/createGlobesFile.h"
#include "../include/variables.h"
#include <iostream>


void createGlobesFile(const sndata &data, const std::string & writePath, const int timeBinNum, const double timeLow, const double timeUp)
{
  for (unsigned int i = 0; i < data.nu.size(); i++)
    {
      std::stringstream ss;
      ss << data.id[i];
      std::string identifier = ss.str();
      std::string pathforsave = writePath + identifier + ".dat";
      
      FILE * outfile = fopen(pathforsave.c_str(),"w");
           
      // calculate time bin width
      double timeWidth = (-timeLow + timeUp) / timeBinNum ;
      
      int k = 1;
      
      // determine the appropriate time bin k
      while ( data.time[i] < pow(10, timeWidth*(timeBinNum-k) - timeUp ))
      {
	k++;
      }
      double edgeUp = pow(10, timeWidth*(timeBinNum-k+1) - timeUp);
      double edgeLow = pow( 10, timeWidth*(timeBinNum-k) - timeUp);
      double weight = edgeUp - edgeLow;
      //std::cout << "Time " << data.time[i] << " is in range " << edgeLow << " to " << edgeUp << " with weight " << weight << std::endl; 
      for (unsigned int j = 0; j < data.nu[i].energy.size(); j++) 
	{
	  double _energy = data.nu[i].energy[j] / 1000;

	  // calculate fluences from flux data, scalefactor represents the ratio of the detector to SNOwGLoBES implemented detector
	  double _fluence_nu  = data.nu[i].flux[j]  * solidAngle * katoWidth / snowWidth * weight;
	  double _fluence_anu = data.anu[i].flux[j] * solidAngle * katoWidth / snowWidth * weight;
	  double _fluence_mu  = data.mu[i].flux[j]  * solidAngle * katoWidth / snowWidth * weight; 
	  double _fluence_amu = data.amu[i].flux[j] * solidAngle * katoWidth / snowWidth * weight;

	  fprintf(outfile, "%e %e %e %e %e %e %e \n", _energy, _fluence_nu, _fluence_mu , _fluence_mu , _fluence_anu, _fluence_amu , _fluence_amu ); 
	}
		    
      if ( data.nu[i].energy.size() < 501 )  
	{
	  for ( int j = data.nu[i].energy.size(); j < 501; j++)
	    fprintf(outfile, "%e %e %e %e %e %e %e \n",.0,.0,.0,.0,.0,.0,.0);
	}

      fclose(outfile);
    }
}