/********************************
Save data from katos simulation files to a C++ vector
 ********************************/

#include "../include/katoReadGLoBES.h"

sndata katoReadGLoBES(const std::string & globesfile_path, const std::string & path, const std::string & option) // expects the path to pre_collapse_... folder
{
  sndata data;
  int _id;
  double _time;
  double _Eanu;
  double _Eamu;
  double _Enu;
  double _Emu;
  double _Number_nu;
  double _Number_anu;
  double _Number_mu;
 
  // read nue lightcurve file
  std::string filepath_nue = path + "/total_nue/lightcurve_nue_all.dat";
  FILE *lightcurve_nue = fopen(filepath_nue.c_str() , "r");

  if(!lightcurve_nue)
    {
      std::string error_str = "File opening failed for " + filepath_nue;
      perror(error_str.c_str());
    }
  
  //fscanf(lightcurve_nue, "%*[^\n]\n"); // skips the first line of the lightcurve file

  while(fscanf(lightcurve_nue, "%lG %lG %lG %i",&_time, &_Number_nu, &_Enu, &_id)==4)
    {
      data.id.push_back(_id);
      data.time.push_back(_time);
      data.Number_nu.push_back(_Number_nu);
      data.Enu.push_back(_Enu);
     }
  fclose(lightcurve_nue);

  std::string filepath_nueb = path + "/total_nueb/lightcurve_nueb_all.dat";
  FILE *lightcurve_nueb = fopen(filepath_nueb.c_str() , "r");

  if(!lightcurve_nueb)
    {
      std::string error_str = "File opening failed for " + filepath_nueb;
      perror(error_str.c_str());
    }

  //fscanf(lightcurve_nueb, "%*[^\n]\n"); // skips the first line of the lightcurve file

  int counter = 0;
  while(fscanf(lightcurve_nueb, "%lG %lG %lG %i",&_time, &_Number_anu, &_Eanu, &_id)==4)
    {
      if ( data.id[counter] != _id )
	perror( "inconsistent lightcurve files - id at nueb");
      if( data.time[counter] != _time )
	perror( "inconsistent lightcurve files - time at nueb");
      
      data.Number_anu.push_back(_Number_anu);
      data.Eanu.push_back(_Eanu);
      counter++;
    }
  
  fclose(lightcurve_nueb);

  std::string filepath_nux = path + "/total_nux/lightcurve.dat";
  FILE *lightcurve_nux = fopen(filepath_nux.c_str() , "r");

  if(!lightcurve_nux)
    {
      std::string error_str = "File opening failed for " + filepath_nux;
      perror(error_str.c_str());
    }

  fscanf(lightcurve_nux, "%*[^\n]\n"); // skips the first line of the lightcurve file
  counter = 0;
  while(fscanf(lightcurve_nux, "%i %lG %* %* %lG %lG %* %lG %lG",&_id, &_time, &_Eamu, &_Number_mu, &_Emu)==5)
    {
      if ( data.id[counter] != _id )
	perror( "inconsistent lightcurve files - id at nux");
      if( data.time[counter] != _time )
	perror( "inconsistent lightcurve files - time at nux");
      
      data.Eamu.push_back(_Eamu);
      data.Number_mu.push_back(_Number_mu);
      data.Emu.push_back(_Emu);
     }
  fclose(lightcurve_nux);

  // loop over the different flavors 
  for ( unsigned int i = 0; i < data.id.size(); i++)
    {
      std::stringstream ss;
      ss << data.id[i];
      std::string identifier = ss.str();

      std::string filepath_flux = globesfile_path + "/kato15sol" + identifier + option + ".dat";
      FILE * flux = fopen(filepath_flux.c_str() , "r");

      if(!flux)
      {
	std::string error_str = "File opening failed for " + filepath_flux;
	perror(error_str.c_str());
      }

      double _energy, _nu, _mu, _tau, _anu, _amu, _atau;
      
      snspectrum append_mu, append_nu, append_amu, append_anu;
      
      while(fscanf(flux, "%lG %lG %lG %lG %lG %lG %lG",&_energy, &_nu, &_mu, &_tau, &_anu, &_amu, &_atau)==7)
      {
	_energy = _energy * 1000;
	
	append_mu.energy.push_back(_energy);
	append_mu.flux.push_back(_mu);
	
	append_nu.energy.push_back(_energy);
	append_nu.flux.push_back(_nu);
	
	append_amu.energy.push_back(_energy);
	append_amu.flux.push_back(_amu);
	
	append_anu.energy.push_back(_energy);
	append_anu.flux.push_back(_anu);
      }
      
      data.mu.push_back(append_mu);
      data.nu.push_back(append_nu);
      data.amu.push_back(append_amu);
      data.anu.push_back(append_anu);
      
      
      fclose(flux);

    }
  
  return data;  
}
