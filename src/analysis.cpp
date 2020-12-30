//TODO: FIX DEPENDENCIES

// load C++ standard libraries
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>

// load root libraries
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
//#include "TSpline.h"

// load other functions
#include "../include/katoRead.h"
#include "../include/katoReadGLoBES.h"
#include "../include/duneRead.h"
#include "../include/junoRead.h"
#include "../include/hyperkRead.h"
#include "../include/createGlobesFile.h"
#include "../include/makeHist.h"
#include "../include/variables.h"


const std::string SNOWGLOBE_PATH = secure_getenv("SNOWGLOBES");
// FIXME: cwd should be project directory, fix after compilation fix
// USE getcwd
std::string PROJ_PATH;
int main()
{
    //FIXME: cwd fix
    chdir("../");
    PROJ_PATH = getcwd((char*)malloc(128), 128); 
    chdir("src/");   
    // create parameter template for makeHist
    parameter params;

    params.timeBinNum = 100;
    params.timeLow = -6;
    params.timeUp = 1;

    params.energyBinNum = 25;
    params.energyLow = 0;
    params.energyUp = 25;

    // array of backgrounds [1/s] || if changing this array, make sure to adjust the backgrounds arrays in the .C files 'bgdist.C', 'drawbg.C'
    int bgl = 61;
    double backgrounds[bgl];

    double bgup = 6;
    double bglow = 0;

    for (int i = 0; i < bgl; i++)
    {
        backgrounds[i] = pow(10, bglow + (bgup - bglow) / (bgl - 1) * i);
    }

    // array of thresholds [MeV]
    int thl = 4;
    double thresholds[] = {0, 4};

    /**************************
    **EMITTED**NO OSCILLATION**
    **************************/
    std::cout << "*********************************" << std::endl;

    std::cout << "Emitted neutrinos" << std::endl;

    // read 15 solar masses data from Kato's simulation files
    sndata katoData15 = katoRead("../data/pre_collapse_neutrino_forDune/");
    //sndata katoData15 = katoReadGLoBES( "../data/GLoBES_fluxes/kato15sol/", "../data/pre_collapse_neutrino_forDune/", "" );

    TFile outfile_15sol("../output/ROOT/kato15sol_emitted.root", "recreate", "Neutrino Emissino Rates without oscillations");

    // electron neutrinos
    parameter emitted_nu = params;

    emitted_nu.spectrum = katoData15.nu;
    emitted_nu.time = katoData15.time;
    emitted_nu.name = "nu";
    emitted_nu.title = "Emitted electron neutrinos for M = 15sol";
    emitted_nu.clear = 1000;
    emitted_nu.factor = katoWidth;

    makeHist(emitted_nu);

    // anti-electron neutrino
    parameter emitted_anu = emitted_nu;

    emitted_anu.spectrum = katoData15.anu;
    emitted_anu.name = "anu";
    emitted_anu.title = "Emitted anti-electron neutrinos for M = 15sol";

    makeHist(emitted_anu);

    // tau/mu neutrino
    parameter emitted_mu = emitted_nu;

    emitted_mu.spectrum = katoData15.mu;
    emitted_mu.name = "mu";
    emitted_mu.title = "Emitted tau/mu neutrinos for M = 15sol";

    makeHist(emitted_mu);

    // anti-tau/mu neutrino
    parameter emitted_amu = emitted_nu;

    emitted_amu.spectrum = katoData15.amu;
    emitted_amu.name = "amu";
    emitted_amu.title = "Emitted anti-tau/mu neutrinos for M = 15sol";

    makeHist(emitted_amu);

    // close the file
    outfile_15sol.Close();

    std::cout << "*********************************" << std::endl;

    // create GLoBES formatted flux files from kato's files
    createGlobesFile(katoData15, "../data/GLoBES_fluxes/kato15sol/kato15sol", params.timeBinNum, params.timeLow, params.timeUp);

    // apply MSW oscillations to the GLoBES file
    chdir("../data/GLoBES_fluxes/");
    std::system("perl run_all_oscillations.pl kato15sol");
    chdir("../../src/");

    /********************/
    /***SMEARED RATES****/
    /********************/

    /******************************
  ************DUNE***************
  ******************************/

    std::system("rm ../output/ROOT/DUNE_normal.root");
    std::system("rm ../output/ROOT/DUNE_inverted.root");

    //define the th string and edit the SNOwGLoBES efficiency file
    for (int k = 0; k < thl; k++)
    {
        std::stringstream ss;
        ss << "_th" << std::setprecision(0) << std::fixed << thresholds[k];
        std::string th = ss.str();

        if (thresholds[k] == 0)
            th = std::string("");

        ss.str("");
        ss << std::setprecision(0) << std::fixed << thresholds[k];
        std::string effic = "perl editeffic.pl " + ss.str();

        /******************************
  *****DUNE*****normal***********
  ******************************/

        // run SNOwGLoBES for DUNE
        chdir(SNOWGLOBE_PATH.c_str());
        std::system(effic.c_str());
        std::system(("perl run_pinched_allflav_argon.pl " + PROJ_PATH + "/data/GLoBES_fluxes/kato15sol/ " + PROJ_PATH + "/output/SNOwGLoBES/DUNE/").c_str());
        chdir((PROJ_PATH + "/src/").c_str());

        std::cout << "DUNE normal ordering:" << std::endl;

        // read SNOwGLoBES data
        dunedata DUNE_normal_data = duneRead("../data/pre_collapse_neutrino_forDune/total_nux/lightcurve.dat", "../output/SNOwGLoBES/DUNE", "normal", 2.4);

        // detected neutrinos
        TFile outfile_dune_normal("../output/ROOT/DUNE_normal.root", "update", "Neutrino Detection Rates for normal Ordering in DUNE");

        // sum over all channels
        parameter DUNE_normal_sum = params;
        DUNE_normal_sum.spectrum = DUNE_normal_data.sum;
        DUNE_normal_sum.time = DUNE_normal_data.time;
        DUNE_normal_sum.name = "sum" + th;
        DUNE_normal_sum.title = "Summed event rates in DUNE for normal ordering and M = 15sol";
        DUNE_normal_sum.clear = pow(10, -20);
        DUNE_normal_sum.factor = snowOutFactor;

        // electron neutrino-Ar40
        parameter DUNE_normal_nue = DUNE_normal_sum;
        DUNE_normal_nue.spectrum = DUNE_normal_data.nue;
        DUNE_normal_nue.name = "nue" + th;
        DUNE_normal_nue.title = "electron neutrino-Ar40 event rates in DUNE for normal ordering and M = 15sol";

        // anti-electron neutrino-Ar40
        parameter DUNE_normal_nuebar = DUNE_normal_sum;
        DUNE_normal_nuebar.spectrum = DUNE_normal_data.nuebar;
        DUNE_normal_nuebar.name = "nuebar" + th;
        DUNE_normal_nuebar.title = "anti-electron neutrino-Ar40 event rates in DUNE for normal ordering and M = 15sol";

        // sum over electron scattering channels
        parameter DUNE_normal_es = DUNE_normal_sum;
        DUNE_normal_es.spectrum = DUNE_normal_data.es;
        DUNE_normal_es.name = "es" + th;
        DUNE_normal_es.title = "Summed electron scattering event rates in DUNE for normal ordering and M = 15sol";

        for (int i = 0; i < bgl; i++)
        {
            makeHist(DUNE_normal_sum, backgrounds[i]);
        }

        makeHist(DUNE_normal_nue);
        makeHist(DUNE_normal_nuebar);
        makeHist(DUNE_normal_es);

        // close file
        outfile_dune_normal.Close();

        std::cout << "*********************************" << std::endl;

        /******************************
  *****DUNE*****inverted*********
  ******************************/

        std::cout << "DUNE inverted ordering:" << std::endl;

        // read SNOwGLoBES data
        dunedata DUNE_inverted_data = duneRead("../data/pre_collapse_neutrino_forDune/total_nux/lightcurve.dat", "../output/SNOwGLoBES/DUNE", "inverted", 2.4);

        // detected neutrinos
        TFile outfile_dune_inverted("../output/ROOT/DUNE_inverted.root", "update", "Neutrino Detection Rates for inverted Ordering in DUNE");

        // sum over all channels
        parameter DUNE_inverted_sum = params;
        DUNE_inverted_sum.spectrum = DUNE_inverted_data.sum;
        DUNE_inverted_sum.time = DUNE_inverted_data.time;
        DUNE_inverted_sum.name = "sum" + th;
        DUNE_inverted_sum.title = "Summed event rates in DUNE for normal ordering and M = 15sol";
        DUNE_inverted_sum.clear = pow(10, -20);
        DUNE_inverted_sum.factor = snowOutFactor;

        // electron neutrino-Ar40
        parameter DUNE_inverted_nue = DUNE_inverted_sum;
        DUNE_inverted_nue.spectrum = DUNE_inverted_data.nue;
        DUNE_inverted_nue.name = "nue" + th;
        DUNE_inverted_nue.title = "electron neutrino-Ar40 event rates in DUNE for normal ordering and M = 15sol";

        // anti-electron neutrino-Ar40
        parameter DUNE_inverted_nuebar = DUNE_inverted_sum;
        DUNE_inverted_nuebar.spectrum = DUNE_inverted_data.nuebar;
        DUNE_inverted_nuebar.name = "nuebar" + th;
        DUNE_inverted_nuebar.title = "anti-electron neutrino-Ar40 event rates in DUNE for normal ordering and M = 15sol";

        // sum over electron scattering channels
        parameter DUNE_inverted_es = DUNE_inverted_sum;
        DUNE_inverted_es.spectrum = DUNE_inverted_data.es;
        DUNE_inverted_es.name = "es" + th;
        DUNE_inverted_es.title = "Summed electron scattering event rates in DUNE for normal ordering and M = 15sol";

        for (int i = 0; i < bgl; i++)
        {
            makeHist(DUNE_inverted_sum, backgrounds[i]);
        }
        makeHist(DUNE_inverted_nue);
        makeHist(DUNE_inverted_nuebar);
        makeHist(DUNE_inverted_es);

        // close file
        outfile_dune_inverted.Close();

        std::cout << "*********************************" << std::endl;
    }

    /******************************
  ************JUNO***************
  ******************************/

    std::system("rm ../output/ROOT/JUNO_normal.root");
    std::system("rm ../output/ROOT/JUNO_inverted.root");

    for (int k = 0; k < thl; k++)
    {
        std::stringstream ss;
        ss << "_th" << std::setprecision(0) << std::fixed << thresholds[k];
        std::string th = ss.str();

        if (thresholds[k] == 0)
            th = std::string("");

        ss.str("");
        ss << std::setprecision(0) << std::fixed << thresholds[k];
        std::string effic = std::string("perl editeffic.pl ") + ss.str();

        /******************************
  *****JUNO*****normal***********
  ******************************/

        // run SNOwGLoBES for JUNO
        chdir(SNOWGLOBE_PATH.c_str());
        std::system(effic.c_str());
        std::system(("perl run_pinched_allflav_argon.pl " + PROJ_PATH + "/data/GLoBES_fluxes/kato15sol/ " + PROJ_PATH + "/output/SNOwGLoBES/DUNE/").c_str());
        std::system(("perl run_pinched_allflav_liqscint.pl "+ PROJ_PATH + "/data/GLoBES_fluxes/kato15sol/ " + PROJ_PATH + "/output/SNOwGLoBES/DUNE/").c_str());
        chdir((PROJ_PATH + "/src/").c_str());

        std::cout << "JUNO normal ordering:" << std::endl;

        // read SNOwGLoBES data
        junodata JUNO_normal_data = junoRead("../data/pre_collapse_neutrino_forDune/total_nux/lightcurve.dat", "../output/SNOwGLoBES/JUNO", "normal", 0.4);

        // detected neutrinos
        TFile outfile_juno_normal("../output/ROOT/JUNO_normal.root", "update", "Neutrino Detection Rates for normal Ordering in JUNO");

        // sum over all channels
        parameter JUNO_normal_sum = params;
        JUNO_normal_sum.spectrum = JUNO_normal_data.sum;
        JUNO_normal_sum.time = JUNO_normal_data.time;
        JUNO_normal_sum.name = "sum" + th;
        JUNO_normal_sum.title = "Summed event rates in JUNO for normal ordering and M = 15sol";
        JUNO_normal_sum.clear = pow(10, -20);
        JUNO_normal_sum.factor = snowOutFactor;

        // electron neutrino-Ar40
        parameter JUNO_normal_nue = JUNO_normal_sum;
        JUNO_normal_nue.spectrum = JUNO_normal_data.nue;
        JUNO_normal_nue.name = "nue" + th;
        JUNO_normal_nue.title = "electron neutrino-C12 event rates in JUNO for normal ordering and M = 15sol";
        JUNO_normal_nue.clear = pow(10, -20);

        // anti-electron neutrino-Ar40
        parameter JUNO_normal_nuebar = JUNO_normal_sum;
        JUNO_normal_nuebar.spectrum = JUNO_normal_data.nuebar;
        JUNO_normal_nuebar.name = "nuebar" + th;
        JUNO_normal_nuebar.title = "anti-electron neutrino-C12 event rates in JUNO for normal ordering and M = 15sol";
        JUNO_normal_nuebar.clear = pow(10, -20);

        // sum over electron scattering channels
        parameter JUNO_normal_es = JUNO_normal_sum;
        JUNO_normal_es.spectrum = JUNO_normal_data.es;
        JUNO_normal_es.name = "es" + th;
        JUNO_normal_es.title = "Summed electron scattering event rates in JUNO for normal ordering and M = 15sol";

        makeHist(JUNO_normal_es);

        // sum over neutral current channels
        parameter JUNO_normal_nc = JUNO_normal_sum;
        JUNO_normal_nc.spectrum = JUNO_normal_data.nc;
        JUNO_normal_nc.name = "nc" + th;
        JUNO_normal_nc.title = "Summed neutral current event rates in JUNO for normal ordering and M = 15sol";
        JUNO_normal_nc.clear = pow(10, -20);

        // sum over inverse beta decay channels
        parameter JUNO_normal_ibd = JUNO_normal_sum;
        JUNO_normal_ibd.spectrum = JUNO_normal_data.ibd;
        JUNO_normal_ibd.name = "ibd" + th;
        JUNO_normal_ibd.title = "Summed inverse beta decay event rates in JUNO for normal ordering and M = 15sol";
        JUNO_normal_ibd.clear = pow(10, -20);

        for (int i = 0; i < bgl; i++)
            makeHist(JUNO_normal_sum, backgrounds[i]);

        makeHist(JUNO_normal_nue);
        makeHist(JUNO_normal_nuebar);
        makeHist(JUNO_normal_nc);
        makeHist(JUNO_normal_ibd);

        // close file
        outfile_juno_normal.Close();

        std::cout << "*********************************" << std::endl;

        /******************************
  *****JUNO*****inverted*********
  ******************************/

        std::cout << "JUNO inverted ordering:" << std::endl;

        // read SNOwGLoBES data
        junodata JUNO_inverted_data = junoRead("../data/pre_collapse_neutrino_forDune/total_nux/lightcurve.dat", "../output/SNOwGLoBES/JUNO", "inverted", 0.4);

        // detected neutrinos
        TFile outfile_juno_inverted("../output/ROOT/JUNO_inverted.root", "update", "Neutrino Detection Rates for inverted Ordering in JUNO");

        // sum over all channels
        parameter JUNO_inverted_sum = params;
        JUNO_inverted_sum.spectrum = JUNO_inverted_data.sum;
        JUNO_inverted_sum.time = JUNO_inverted_data.time;
        JUNO_inverted_sum.name = "sum" + th;
        JUNO_inverted_sum.title = "Summed event rates in JUNO for normal ordering and M = 15sol";
        JUNO_inverted_sum.clear = pow(10, -20);
        JUNO_inverted_sum.factor = snowOutFactor;

        // electron neutrino-Ar40
        parameter JUNO_inverted_nue = JUNO_inverted_sum;
        JUNO_inverted_nue.spectrum = JUNO_inverted_data.nue;
        JUNO_inverted_nue.name = "nue" + th;
        JUNO_inverted_nue.title = "electron neutrino-C12 event rates in JUNO for normal ordering and M = 15sol";
        JUNO_inverted_nue.clear = pow(10, -20);

        // anti-electron neutrino-Ar40
        parameter JUNO_inverted_nuebar = JUNO_inverted_sum;
        JUNO_inverted_nuebar.spectrum = JUNO_inverted_data.nuebar;
        JUNO_inverted_nuebar.name = "nuebar" + th;
        JUNO_inverted_nuebar.title = "anti-electron neutrino-C12 event rates in JUNO for normal ordering and M = 15sol";
        JUNO_inverted_nuebar.clear = pow(10, -20);

        // sum over electron scattering channels
        parameter JUNO_inverted_es = JUNO_inverted_sum;
        JUNO_inverted_es.spectrum = JUNO_inverted_data.es;
        JUNO_inverted_es.name = "es" + th;
        JUNO_inverted_es.title = "Summed electron scattering event rates in JUNO for normal ordering and M = 15sol";

        // sum over neutral current channels
        parameter JUNO_inverted_nc = JUNO_inverted_sum;
        JUNO_inverted_nc.spectrum = JUNO_inverted_data.nc;
        JUNO_inverted_nc.name = "nc" + th;
        JUNO_inverted_nc.title = "Summed neutral current event rates in JUNO for inverted ordering and M = 15sol";
        JUNO_inverted_nc.clear = pow(10, -20);

        // sum over inverse beta decay channels
        parameter JUNO_inverted_ibd = JUNO_inverted_sum;
        JUNO_inverted_ibd.spectrum = JUNO_inverted_data.ibd;
        JUNO_inverted_ibd.name = "ibd" + th;
        JUNO_inverted_ibd.title = "Summed inverse beta decay event rates in JUNO for inverted ordering and M = 15sol";
        JUNO_inverted_ibd.clear = pow(10, -20);

        for (int i = 0; i < bgl; i++)
            makeHist(JUNO_inverted_sum, backgrounds[i]);

        makeHist(JUNO_inverted_nue);
        makeHist(JUNO_inverted_nuebar);
        makeHist(JUNO_inverted_es);
        makeHist(JUNO_inverted_nc);
        makeHist(JUNO_inverted_ibd);

        // close file
        outfile_juno_inverted.Close();

        std::cout << "*********************************" << std::endl;
    }

    /******************************
  ***********HYPER-K*************
  ******************************/

    std::system("rm ../output/ROOT/HYPERK_normal.root");
    std::system("rm ../output/ROOT/HYPERK_inverted.root");

    for (int k = 0; k < thl; k++)
    {
        std::stringstream ss;
        ss << "_th" << std::setprecision(0) << std::fixed << thresholds[k];
        std::string th = ss.str();

        if (thresholds[k] == 0)
            th = std::string("");

        ss.str("");
        ss << std::setprecision(0) << std::fixed << thresholds[k];
        std::string effic = "perl editeffic.pl " + ss.str();

        /******************************
  *****HYPER-K***normal*********
  ******************************/

        // run SNOwGLoBES for Hyper-K
        chdir(SNOWGLOBE_PATH.c_str());
        std::system(effic.c_str());
        std::system(("perl run_pinched_allflav_water.pl "+ PROJ_PATH + "/data/GLoBES_fluxes/kato15sol/ " + PROJ_PATH + "/output/SNOwGLoBES/DUNE/").c_str());
        chdir((PROJ_PATH + "/src/").c_str());

        std::cout << "Hyper-K normal ordering:" << std::endl;

        // read SNOwGLoBES data
        hyperkdata HYPERK_normal_data = hyperkRead("../data/pre_collapse_neutrino_forDune/total_nux/lightcurve.dat", "../output/SNOwGLoBES/HyperK", "normal", 1.0);

        // detected neutrinos
        TFile outfile_hyperk_normal("../output/ROOT/HYPERK_normal.root", "update", "Neutrino Detection Rates for normal Ordering in Hyper-K");

        // sum over all channels
        parameter HYPERK_normal_sum = params;
        HYPERK_normal_sum.spectrum = HYPERK_normal_data.sum;
        HYPERK_normal_sum.time = HYPERK_normal_data.time;
        HYPERK_normal_sum.name = "sum" + th;
        HYPERK_normal_sum.title = "Summed event rates in Hyper-K for normal ordering and M = 15sol";
        HYPERK_normal_sum.clear = pow(10, -20);
        HYPERK_normal_sum.factor = snowOutFactor;

        // electron neutrino-Ar40
        parameter HYPERK_normal_nue = HYPERK_normal_sum;
        HYPERK_normal_nue.spectrum = HYPERK_normal_data.nue;
        HYPERK_normal_nue.name = "nue" + th;
        HYPERK_normal_nue.title = "electron neutrino-O16 event rates in Hyper-K for normal ordering and M = 15sol";

        // anti-electron neutrino-Ar40
        parameter HYPERK_normal_nuebar = HYPERK_normal_sum;
        HYPERK_normal_nuebar.spectrum = HYPERK_normal_data.nuebar;
        HYPERK_normal_nuebar.name = "nuebar" + th;
        HYPERK_normal_nuebar.title = "anti-electron neutrino-O16 event rates in Hyper-K for normal ordering and M = 15sol";
        HYPERK_normal_nuebar.clear = pow(10, -20);

        // sum over electron scattering channels
        parameter HYPERK_normal_es = HYPERK_normal_sum;
        HYPERK_normal_es.spectrum = HYPERK_normal_data.es;
        HYPERK_normal_es.name = "es" + th;
        HYPERK_normal_es.title = "Summed electron scattering event rates in Hyper-K for normal ordering and M = 15sol";

        // sum over neutral current channels
        parameter HYPERK_normal_nc = HYPERK_normal_sum;
        HYPERK_normal_nc.spectrum = HYPERK_normal_data.nc;
        HYPERK_normal_nc.name = "nc" + th;
        HYPERK_normal_nc.title = "Summed neutral current event rates in JUNO for normal ordering and M = 15sol";
        HYPERK_normal_nc.clear = pow(10, -20);

        // sum over inverse beta decay channels
        parameter HYPERK_normal_ibd = HYPERK_normal_sum;
        HYPERK_normal_ibd.spectrum = HYPERK_normal_data.ibd;
        HYPERK_normal_ibd.name = "ibd" + th;
        HYPERK_normal_ibd.title = "Summed inverse beta decay event rates in Hyper-K for normal ordering and M = 15sol";
        HYPERK_normal_ibd.clear = pow(10, -20);

        for (int i = 0; i < bgl; i++)
            makeHist(HYPERK_normal_sum, backgrounds[i]);

        makeHist(HYPERK_normal_nue);
        makeHist(HYPERK_normal_nuebar);
        makeHist(HYPERK_normal_es);
        makeHist(HYPERK_normal_nc);
        makeHist(HYPERK_normal_ibd);

        // close file
        outfile_hyperk_normal.Close();

        std::cout << "*********************************" << std::endl;

        /******************************
  *****HYPER-K**inverted*********
  ******************************/

        std::cout << "Hyper-K inverted ordering:" << std::endl;

        // read SNOwGLoBES data
        hyperkdata HYPERK_inverted_data = hyperkRead("../data/pre_collapse_neutrino_forDune/total_nux/lightcurve.dat", "../output/SNOwGLoBES/HyperK", "inverted", 1.0);

        // detected neutrinos
        TFile outfile_hyperk_inverted("../output/ROOT/HYPERK_inverted.root", "update", "Neutrino Detection Rates for inverted Ordering in Hyper-K");

        // sum over all channels
        parameter HYPERK_inverted_sum = params;
        HYPERK_inverted_sum.spectrum = HYPERK_inverted_data.sum;
        HYPERK_inverted_sum.time = HYPERK_inverted_data.time;
        HYPERK_inverted_sum.name = "sum" + th;
        HYPERK_inverted_sum.title = "Summed event rates in Hyper-K for normal ordering and M = 15sol";
        HYPERK_inverted_sum.clear = pow(10, -20);
        HYPERK_inverted_sum.factor = snowOutFactor;

        // electron neutrino-Ar40
        parameter HYPERK_inverted_nue = HYPERK_inverted_sum;
        HYPERK_inverted_nue.spectrum = HYPERK_inverted_data.nue;
        HYPERK_inverted_nue.name = "nue" + th;
        HYPERK_inverted_nue.title = "electron neutrino-O16 event rates in Hyper-K for normal ordering and M = 15sol";

        // anti-electron neutrino-Ar40
        parameter HYPERK_inverted_nuebar = HYPERK_inverted_sum;
        HYPERK_inverted_nuebar.spectrum = HYPERK_inverted_data.nuebar;
        HYPERK_inverted_nuebar.name = "nuebar" + th;
        HYPERK_inverted_nuebar.title = "anti-electron neutrino-O16 event rates in Hyper-K for normal ordering and M = 15sol";
        HYPERK_inverted_nuebar.clear = pow(10, -20);

        // sum over electron scattering channels
        parameter HYPERK_inverted_es = HYPERK_inverted_sum;
        HYPERK_inverted_es.spectrum = HYPERK_inverted_data.es;
        HYPERK_inverted_es.name = "es" + th;
        HYPERK_inverted_es.title = "Summed electron scattering event rates in Hyper-K for normal ordering and M = 15sol";

        // sum over neutral current channels
        parameter HYPERK_inverted_nc = HYPERK_inverted_sum;
        HYPERK_inverted_nc.spectrum = HYPERK_inverted_data.nc;
        HYPERK_inverted_nc.name = "nc" + th;
        HYPERK_inverted_nc.title = "Summed neutral current event rates in JUNO for inverted ordering and M = 15sol";
        HYPERK_inverted_nc.clear = pow(10, -20);

        // sum over inverse beta decay channels
        parameter HYPERK_inverted_ibd = HYPERK_inverted_sum;
        HYPERK_inverted_ibd.spectrum = HYPERK_inverted_data.ibd;
        HYPERK_inverted_ibd.name = "ibd" + th;
        HYPERK_inverted_ibd.title = "Summed inverse beta decay event rates in Hyper-K for inverted ordering and M = 15sol";
        HYPERK_inverted_ibd.clear = pow(10, -20);

        for (int i = 0; i < bgl; i++)
            makeHist(HYPERK_inverted_sum, backgrounds[i]);

        makeHist(HYPERK_inverted_nue);
        makeHist(HYPERK_inverted_nuebar);
        makeHist(HYPERK_inverted_es);
        makeHist(HYPERK_inverted_nc);
        makeHist(HYPERK_inverted_ibd);

        // close file
        outfile_hyperk_inverted.Close();

        std::cout << "*********************************" << std::endl;
    }
    return 0;
}