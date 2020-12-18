// load C++ standard libraries
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
// load root libraries
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include <memory>
//#include "TSpline.h"

// load other functions
#include "../include/clearBins.h"
#include "../include/katoRead.h"
#include "../include/splineFitTH2D.h"
#include "../include/fillHistogram.h"
#include "../include/snowRead.h"
#include "../include/fluxToFluence.h"
#include "../include/createGlobesFile.h"
#include "../include/energyIntegral.h"
#include "../include/energyIntegralAlt.h"
/*
double katoWidth = 0.05; // [MeV] step width of simulation results
double snowWidth = 0.2;  // [MeV] step width expected by SNOwGLoBES

double parsec = 3.0857 * pow(10,16); //one parsec is approximately 3.0857e16 meters
double distance = 200;  // assuming a distance of 200 parsec to the SN
double surface =  4 * M_PI * pow( (distance * parsec), 2);
double solidAngle = pow( 0.01,2) / surface; // square meter to square cm
*/
#include "../include/makeHistogram.cpp"

int main()
{
  // read 15 solar masses data from Kato's simulation files
  sndata katoData15 = katoRead ( "../data/pre_collapse_neutrino_forDune" );  
  
  // create logarithmic time bins
  int timeBinNum = 100;
  double timeLow = -6;
  double timeUp = 1;
  
  // create linear energy bins
  int energyBinNum = 50;
  double energyLow = 0;
  double energyUp = 25;

  // emitted neutrinos
  TFile outfile_15sol ("../output/ROOT/katoEmitted_15sol.root", "recreate", "Neutrino Emissino Rates");
  TH2D hist_15sol_anu ("hist_emitted_15sol_anu", "Emitted Anti-Electron Neutrino Flux", timeBinNum, timeLow, timeUp, energyBinNum, energyLow, energyUp) ;
  TH2D hist_15sol_nu  ("hist_emitted_15sol_nu", "Emitted Electron Neutrino Flux", timeBinNum, timeLow, timeUp, energyBinNum, energyLow, energyUp);
  TH2D hist_15sol_amu ("hist_emitted_15sol_amu", "Emitted Anti-Mu/Tau Neutrino Flux", timeBinNum, timeLow, timeUp, energyBinNum, energyLow, energyUp);
  TH2D hist_15sol_mu  ("hist_emitted_15sol_mu", "Emitted Mu/TauNeutrino Flux", timeBinNum, timeLow, timeUp, energyBinNum, energyLow, energyUp);
  
  // Anti-Electron
  fillHistogram(hist_15sol_anu, katoData15.anu, katoData15.time,katoWidth);
  spline3FitTH2D(hist_15sol_anu);
  clearBins(hist_15sol_anu, 1);
  
  energyIntegral(hist_15sol_anu);
  
  // Electron
  fillHistogram(hist_15sol_nu, katoData15.nu, katoData15.time,katoWidth);
  spline3FitTH2D(hist_15sol_nu);
  clearBins(hist_15sol_nu, 1);
  
  energyIntegral(hist_15sol_nu);

  // Anti-Mu/Tau
  fillHistogram(hist_15sol_amu, katoData15.amu, katoData15.time,katoWidth);
  spline3FitTH2D(hist_15sol_amu);
  clearBins(hist_15sol_amu, 1);
  
  energyIntegral(hist_15sol_amu);
  
  // Mu/Tau
  fillHistogram(hist_15sol_mu, katoData15.mu, katoData15.time, katoWidth);
  spline3FitTH2D(hist_15sol_mu);
  clearBins(hist_15sol_mu, 1);
  
  energyIntegral(hist_15sol_mu);
  
  hist_15sol_anu.Write();
  hist_15sol_nu.Write();
  hist_15sol_amu.Write();
  hist_15sol_mu.Write();
  
  outfile_15sol.Close();
  
  /********************/
  /***SMEARED RATES****/
  /********************/
  
  //energyBinNum = 40;
  //energyUp = 25;
  
  // create GLoBES formatted flux files from kato's files
  createGlobesFile(katoData15, "../data/GLoBES_fluxes/kato15sol", timeBinNum, timeLow, timeUp, 2.4);
  
  // apply MSW oscillations to the GLoBES file
  chdir("../data/GLoBES_fluxes/");
  std::system("./run_all_oscillations.pl kato15sol")
  
  // run SNOwGLoBES for DUNE with normal ordering
  chdir("../../snowglobes");
  std::system("perl run_pinched_allflav_argon_normal.pl ../analysis_pre_collapse_forDune/data/GLoBES_fluxes/kato15sol ../analysis_pre_collapse_forDune/output/SNOwGLoBES/DUNE");
  
  // run SNOwGLoBES for DUNE with inverted ordering
  std::system("perl run_pinched_allflav_argon_inverted.pl ../analysis_pre_collapse_forDune/data/GLoBES_fluxes/kato15sol ../analysis_pre_collapse_forDune/output/SNOwGLoBES/DUNE");
  
  // run SNOwGLoBES for JUNO with normal ordering
  std::system("perl run_pinched_allflav_scint_normal.pl ../analysis_pre_collapse_forDune/data/GLoBES_fluxes/kato15s ../analysis_pre_collapse_forDune/output/SNOwGLoBES/JUNO");
  
  // run SNOwGLoBES for JUNO with inverted ordering
  std::system("perl run_pinched_allflav_scint_inverted.pl ../analysis_pre_collapse_forDune/data/GLoBES_fluxes/kato15s ../analysis_pre_collapse_forDune/output/SNOwGLoBES/JUNO");
  
  // run SNOwGLoBES for Hyper-K with normal ordering
  std::system("perl run_pinched_allflav_water_normal.pl ../analysis_pre_collapse_forDune/data/GLoBES_fluxes/kato15s ../analysis_pre_collapse_forDune/output/SNOwGLoBES/HyperK");
  
  // run SNOwGLoBES for Hyper-K with inverted ordering
  std::system("perl run_pinched_allflav_water_inverted.pl ../analysis_pre_collapse_forDune/data/GLoBES_fluxes/kato15s ../analysis_pre_collapse_forDune/output/SNOwGLoBES/HyperK");
  
  chdir("../analysis_pre_collapse_forDune/src/");
  std::cout << "running perl " << std::endl;
  /**/
  std::cout << "finished" << std::endl;
  
  double snowOutFactor = 0.5; // snowglobes output is per 0.5 MeV
  
  /******************************
  *****DUNE*****normal***********
  ******************************/

  // read SNOwGLoBES data
  snowdata snowData15 = snowRead("../data/pre_collapse_neutrino_forDune/total_nux/", "../output/SNOwGLoBES/DUNE", 15);

  /* DEBUG */
  double sum = 0;
  for( int i = 0; i < snowData15.nue.size(); i++)
  {
    for ( int j = 0; j < snowData15.nue[i].flux.size(); j ++)
      sum += snowData15.nue[i].flux[j] * 0.5;
  }
  std::cout << "Nue Sum: " << sum << std::endl;
  
  // detected neutrinos
  TFile outfile_15sol_smeared ("../output/ROOT/snowSmeared_15sol.root", "recreate", "Neutrino Detection Rates");
  TH2D hist_15sol_smeared_sum ("hist_15sol_smeared_sum", "Total sum of detected neutrino rates", timeBinNum, timeLow, timeUp, energyBinNum, energyLow, energyUp);
  TH2D hist_15sol_smeared_nue ("hist_15sol_smeared_nue", "Sum of detected neutrino rates", timeBinNum, timeLow, timeUp, energyBinNum, energyLow, energyUp);
  TH2D hist_15sol_smeared_nuebar ("hist_15sol_smeared_nuebar", "Sum of detected anti neutrino rates", timeBinNum, timeLow, timeUp, energyBinNum, energyLow, energyUp);
  TH2D hist_15sol_smeared_es ("hist_15sol_smeared_es", "Sum of electron scattering rates", timeBinNum, timeLow, timeUp, energyBinNum, energyLow, energyUp);
  
  // Total Sum
  fillHistogram(hist_15sol_smeared_sum, snowData15.sum, snowData15.time,snowOutFactor);
  spline3FitTH2D(hist_15sol_smeared_sum);
  clearBins(hist_15sol_smeared_sum, pow(10,-3));
  
  hist_15sol_smeared_sum.Write();
  energyIntegral(hist_15sol_smeared_sum);

  // neutrino-Ar40 sum
  fillHistogram(hist_15sol_smeared_nue, snowData15.nue, snowData15.time,snowOutFactor);
  spline3FitTH2D(hist_15sol_smeared_nue);
  clearBins(hist_15sol_smeared_nue, pow(10,-3));
  
  hist_15sol_smeared_nue.Write();
  energyIntegral(hist_15sol_smeared_nue);
    
  // anti neutrino-Ar40 sum
  fillHistogram(hist_15sol_smeared_nuebar, snowData15.nuebar, snowData15.time,snowOutFactor);
  spline3FitTH2D(hist_15sol_smeared_nuebar);
  clearBins(hist_15sol_smeared_nuebar, pow(10,-8.5));
  
  hist_15sol_smeared_nuebar.Write();
  energyIntegral(hist_15sol_smeared_nuebar);
    
  // electron scattering sum
  fillHistogram(hist_15sol_smeared_es, snowData15.es, snowData15.time,snowOutFactor);
  spline3FitTH2D(hist_15sol_smeared_es);
  clearBins(hist_15sol_smeared_es, pow(10,-3));
  
  hist_15sol_smeared_es.Write();
  energyIntegral(hist_15sol_smeared_es);
  
  outfile_15sol_smeared.Close();
  
  
  /*****************************
  ************JUNO**************
  *****************************/
  
  
  /*****************************
  **********HYPER-K*************
  *****************************/
    
  return 0;
}

void histogramRoutine(TH2D hist, snowdata data)
{
  
}
