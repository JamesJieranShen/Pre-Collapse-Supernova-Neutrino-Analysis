#include "../include/createGlobesFile.h"
#include <iostream>

extern double katoWidth;// = 0.05; // [MeV] step width of simulation results
extern double snowWidth;// = 0.2;  // [MeV] step width expected by SNOwGLoBES

extern double parsec;// = 3.0857 * pow(10,16); //one parsec is approximately 3.0857e16 meters
extern double distance;// = 200;  // assuming a distance of 200 parsec to the SN
extern double surface;// =  4 * M_PI * pow( (distance * parsec), 2);
extern double solidAngle;// = pow( 0.01,2) / surface; // square meter to square cm


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