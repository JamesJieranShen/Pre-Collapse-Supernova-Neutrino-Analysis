/********************************
Save data from summed SNOwGLoBES files to a C++ vector
 ********************************/

#include "../include/junoRead.h"

junodata junoRead(const std::string & lightcurvePath, const std::string & dataPath, const std::string & option, const double factor) 
{
  // read the times from lightcurve file
  FILE *lightcurve = fopen(lightcurvePath.c_str() , "r");

  if(!lightcurve)
    {
      std::string error_str = "File opening failed for " + lightcurvePath;
      perror(error_str.c_str());
    }
   
  junodata data;

  // fill the vector 
  int _id;
  double _time;
  
  fscanf(lightcurve, "%*[^\n]\n"); // skips the first line of the lightcurve file

  while(fscanf(lightcurve, "%i %lG %*lG %*lG %*lG %*lG %*lG %*lG %*lG",&_id, &_time)==2)
    {
      data.id.push_back(_id);
      data.time.push_back(_time);
     }
  fclose(lightcurve);

  // loop over the different file types
  std::string filetype[] = {"_smeared_sum", "_smeared_sum_nue", "_smeared_sum_nuebar", "_smeared_sum_es", "_smeared_sum_nc", "_smeared_sum_ibd"};

  if(option == "normal" || option == "inverted")
  {
  for ( unsigned int i = 0; i < data.id.size(); i++)
    {
      std::stringstream ss;
      ss << data.id[i];
      std::string identifier = ss.str();

      std::string path_sum = dataPath + "/kato15sol" + identifier +  "_" +option + filetype[0] + ".dat";
      data.sum.push_back(spectrumRead(path_sum, 1000., factor));

      std::string path_nue = dataPath + "/kato15sol" + identifier +  "_" +option + filetype[1] + ".dat";
      data.nue.push_back(spectrumRead(path_nue, 1000., factor));
      
      std::string path_nuebar = dataPath + "/kato15sol" + identifier +  "_" +option + filetype[2] + ".dat";
      data.nuebar.push_back(spectrumRead(path_nuebar, 1000., factor));
      
      std::string path_es = dataPath + "/kato15sol" + identifier +  "_" +option + filetype[3] + ".dat";
      data.es.push_back(spectrumRead(path_es, 1000., factor));
    
      std::string path_nc = dataPath + "/kato15sol" + identifier +  "_" + option + filetype[4] + ".dat";
      data.nc.push_back(spectrumRead(path_nc, 1000., factor));

      std::string path_ibd = dataPath + "/kato15sol" + identifier +  "_" + option + filetype[5] + ".dat";
      data.ibd.push_back(spectrumRead(path_ibd, 1000., factor));
    }
  }
  else 
    perror("Valid options: normal, inverted");
  return data;  
}
