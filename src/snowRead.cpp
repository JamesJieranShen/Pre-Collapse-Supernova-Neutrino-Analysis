/********************************
Save data from katos simulation files to a C++ vector
 ********************************/

#include "../include/snowRead.h"

snowdata snowRead(const std::string & lightcurvePath, const std::string & dataPath, const std::string option, const int specifier) // expects lightcurvePath: the path to the 12solar2 or 15solar2, dataPath: path to the snowglobes output, specifier either 12 or 15 depending on solar masses 
{
  // read the times from lightcurve file
  FILE *lightcurve = fopen(lightcurvePath.c_str() , "r");

  if(!lightcurve)
    {
      std::string error_str = "File opening failed for " + lightcurvePath + "lightcurve.dat";
      perror(error_str.c_str());
    }
   
  snowdata data;

  // fill the vector 
  int _id;
  double _time;
  
  fscanf(lightcurve, "%*[^\n]\n"); // skips the first line of the lightcurve file

  while(fscanf(lightcurve, "%i %lG %*lG %*lG %*lG %*lG %*lG %*lG %*lG",&_id, &_time)==2)
    {
      data.id.push_back(_id);
      data.time.push_back(_time);
     }

  // loop over the different file types
  std::string filetype[] = {"_smeared_sum", "_smeared_sum_nue", "_smeared_sum_nuebar", "_smeared_sum_es"};

  if ( specifier == 12 ){
  for ( unsigned int i = 0; i < data.id.size(); i++)
    {
      std::stringstream ss;
      ss << data.id[i];
      std::string identifier = ss.str();

      std::string path_sum = dataPath + "/kato12sol" + identifier + filetype[0] + option + ".dat";
      data.sum.push_back(spectrumRead(path_sum, 1000., 1.));

      std::string path_nue = dataPath + "/kato12sol" + identifier + filetype[1] + option + ".dat";
      data.nue.push_back(spectrumRead(path_nue, 1000., 1.));
      
      std::string path_nuebar = dataPath + "/kato12sol" + identifier + filetype[2] + option + ".dat";
      data.nuebar.push_back(spectrumRead(path_nuebar, 1000., 1.));
      
      std::string path_es = dataPath + "/kato12sol" + identifier + filetype[3] + option + ".dat";
      data.es.push_back(spectrumRead(path_es, 1000., 1.));
    }}
  
  else if ( specifier == 15 ){
  for ( unsigned int i = 0; i < data.id.size(); i++)
    {
      std::stringstream ss;
      ss << data.id[i];
      std::string identifier = ss.str();

      std::string path_sum = dataPath + "/kato15sol" + identifier + filetype[0] + ".dat";
      data.sum.push_back(spectrumRead(path_sum, 1000., 1.));

      std::string path_nue = dataPath + "/kato15sol" + identifier + filetype[1] + ".dat";
      data.nue.push_back(spectrumRead(path_nue, 1000., 1.));
      
      std::string path_nuebar = dataPath + "/kato15sol" + identifier + filetype[2] + ".dat";
      data.nuebar.push_back(spectrumRead(path_nuebar, 1000., 1.));
      
      std::string path_es = dataPath + "/kato15sol" + identifier + filetype[3] + ".dat";
      data.es.push_back(spectrumRead(path_es, 1000., 1.));
    }}
  else { perror("Please enter a valid specifier: 12 or 15"); }
  
  return data;  
}
