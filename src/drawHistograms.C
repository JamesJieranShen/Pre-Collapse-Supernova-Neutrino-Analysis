// Draw all histograms. This version works for ROOT 6.
// Author: Mark Schoene, James Shen
#include <vector>
#define EMITTED_PATH "../output/ROOT/kato15sol_emitted.root"
#define DUNE_NORMAL_PATH "../output/ROOT/DUNE_normal.root"
#define DUNE_INVERTED_PATH "../output/ROOT/DUNE_inverted.root"
#define JUNO_NORMAL_PATH "../output/ROOT/JUNO_normal.root"
#define JUNO_INVERTED_PATH "../output/ROOT/JUNO_inverted.root"
#define HYPERK_NORMAL_PATH "../output/ROOT/HYPERK_normal.root"
#define HYPERK_INVERTED_PATH "../output/ROOT/HYPERK_inverted.root"

std::vector<TH1D*> * getHists(TFile * file, const std::string* histNames, int numHists){
    std::vector<TH1D*> * ret = new std::vector<TH1D*>;
    for(int i = 0; i < numHists; i++){
        auto object = file->Get(histNames[i].c_str()); 
        if (!object) { 
            cerr << "object missing\n"; 
            exit(1); 
        } 
        auto histo = dynamic_cast<TH1D*>(object); 
        if (!histo) {
            cerr << "object is not a TH1D\n"; 
            exit(1); 
        }
        ret->push_back(histo);
    }
    return ret;
}

std::vector<Color_t> color;
std::string histNames[10];
TString pathEI;
std::string ylabel;

double emitted_legend[4] = {0.17, 0.6, 0.3, 0.9};
std::vector<TH1D *> * histograms_emitted;
std::vector<std::string> label_emitted;
std::string ylabel_emitted;

double DUNE_legend[4] = {0.17, 0.55, 0.35, 0.9};
std::vector<TH1D *> * histograms_DUNE_normal;
std::vector<std::string> label_DUNE_normal;
std::vector<TH1D *> * histograms_DUNE_inverted;
std::vector<std::string> label_DUNE_inverted;

double JUNO_legend[4] = {0.17, 0.15, 0.33, 0.6};
std::vector<TH1D *> * histograms_JUNO_normal;
std::vector<std::string> label_JUNO_normal;
std::vector<TH1D *> * histograms_JUNO_inverted;
std::vector<std::string> label_JUNO_inverted;

double HYPERK_legend[4] = {0.17, 0.15, 0.33, 0.6};
std::vector<TH1D *> * histograms_HYPERK_normal;
std::vector<std::string> label_HYPERK_normal;
std::vector<TH1D *> * histograms_HYPERK_inverted;
std::vector<std::string> label_HYPERK_inverted;


// main macro starts here
void drawHistograms(){
    double DUNE_normal_integral, DUNE_inverted_integral, JUNO_normal_integral, JUNO_inverted_integral, HYPERK_normal_integral, HYPERK_inverted_integral;
    // global variables
    TGaxis::SetMaxDigits(2);

    // 12 solar masses SN no oscillation
    
    histNames[0] = "amu_energyIntegral";
    histNames[1] = "mu_energyIntegral";
    histNames[2] = "anu_energyIntegral";
    histNames[3] = "nu_energyIntegral";
    TFile * file = new TFile(EMITTED_PATH);
    histograms_emitted = getHists(file, histNames, 4);

    color.push_back(1);
    color.push_back(2);
    color.push_back(3);
    color.push_back(4);

    label_emitted.push_back("#bar{#nu}_{x}");
    label_emitted.push_back("#nu_{x}");
    label_emitted.push_back("#bar{#nu}_{e}");
    label_emitted.push_back("#nu_{e}");

    ylabel_emitted = "Integrated Flux / cm^{-2}s^{-1}";
    pathEI = "../output/histograms/all_channels/15sol_emitted_all.png";
    gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_emitted, color, label_emitted, ylabel_emitted, &pathEI, -2, 5, 50, 56,emitted_legend)");
    file->Close();
    
    /***************************************************************/
    // DUNE, normal ordering, smeared, 15 solar masses
    histNames[0] = "sum_bg1_energyIntegral";
    histNames[1] = "nue_th0_energyIntegral";
    histNames[2] = "nuebar_th0_energyIntegral";
    histNames[3] = "es_th0_energyIntegral";

    file = new TFile(DUNE_NORMAL_PATH);
    histograms_DUNE_normal = getHists(file, histNames, 4);

    /*
    path = ( "../output/histograms/15sol_DUNE_normal_sum.png");
    gROOT->ProcessLine(".x drawSingleSnowHist.C(sum, &path)");
    pathEI = "../output/histograms/15sol_DUNE_normal_sum_bg1_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(sum_bg1_energyIntegral, &pathEI)");

    path = "../output/histograms/15sol_DUNE_normal_nue.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nue, &path)");
    pathEI = "../output/histograms/15sol_DUNE_normal_nue_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nue_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_DUNE_normal_nuebar.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nuebar, &path)");
    pathEI = "../output/histograms/15sol_DUNE_normal_nuebar_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nuebar_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_DUNE_normal_es.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(es, &path)");
    pathEI = "../output/histograms/15sol_DUNE_normal_es_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(es_energyIntegral,&pathEI)");
    */

    label_DUNE_normal.push_back("Ar-40 + ES");
    label_DUNE_normal.push_back("Ar-40 #nu_{e}");
    label_DUNE_normal.push_back("Ar-40 #bar{#nu}_{e}");
    label_DUNE_normal.push_back("ES");

    ylabel = "Events";

    pathEI = "../output/histograms/all_channels/15sol_DUNE_normal_all.png";
    gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_DUNE_normal, color, label_DUNE_normal, ylabel, &pathEI, -2, 4, -3, 3,DUNE_legend)");

    DUNE_normal_integral = (*histograms_DUNE_normal)[0]->Integral();
    file->Close();

    // DUNE, inverted ordering, smeared, 15 solar masses
    // same histogram names as normal ordering
    file = new TFile(DUNE_INVERTED_PATH);
    histograms_DUNE_inverted = getHists(file, histNames, 4);

    /*
    path = ( "../output/histograms/15sol_DUNE_inverted_sum.png");
    gROOT->ProcessLine(".x drawSingleSnowHist.C(sum, &path)");
    pathEI = "../output/histograms/15sol_DUNE_inverted_sum_bg1_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(sum_bg1_energyIntegral, &pathEI)");

    path = "../output/histograms/15sol_DUNE_inverted_nue.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nue, &path)");
    pathEI = "../output/histograms/15sol_DUNE_inverted_nue_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nue_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_DUNE_inverted_nuebar.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nuebar, &path)");
    pathEI = "../output/histograms/15sol_DUNE_inverted_nuebar_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nuebar_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_DUNE_inverted_es.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(es, &path)");
    pathEI = "../output/histograms/15sol_DUNE_inverted_es_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(es_energyIntegral,&pathEI)");
    */

    label_DUNE_inverted.push_back("Ar-40 + ES");
    label_DUNE_inverted.push_back("Ar-40 #nu_{e}");
    label_DUNE_inverted.push_back("Ar-40 #bar{#nu}_{e}");
    label_DUNE_inverted.push_back("ES");

    pathEI = "../output/histograms/all_channels/15sol_DUNE_inverted_all.png";
    gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_DUNE_inverted, color, label_DUNE_inverted,ylabel, &pathEI, -2, 4, -2, 3,DUNE_legend)");

    DUNE_inverted_integral = (*histograms_DUNE_inverted)[0]->Integral();
    file->Close();

    // JUNO, normal ordering, smeared, 15 solar masses
    histNames[0] = "sum_bg1_energyIntegral";
    histNames[1] = "nue_th0_energyIntegral";
    histNames[2] = "nuebar_th0_energyIntegral";
    histNames[3] = "es_th0_energyIntegral";
    histNames[4] = "nc_th0_energyIntegral";
    histNames[5] = "ibd_th0_energyIntegral";

    file = new TFile(JUNO_NORMAL_PATH);
    histograms_JUNO_normal = getHists(file, histNames, 6);

    /*
    path = ( "../output/histograms/15sol_JUNO_normal_sum.png");
    gROOT->ProcessLine(".x drawSingleSnowHist.C(sum, &path)");
    pathEI = "../output/histograms/15sol_JUNO_normal_sum_bg1_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(sum_bg1_energyIntegral, &pathEI)");

    path = "../output/histograms/15sol_JUNO_normal_nue.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nue, &path)");
    pathEI = "../output/histograms/15sol_JUNO_normal_nue_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nue_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_JUNO_normal_nuebar.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nuebar, &path)");
    pathEI = "../output/histograms/15sol_JUNO_normal_nuebar_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nuebar_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_JUNO_normal_es.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(es, &path)");
    pathEI = "../output/histograms/15sol_JUNO_normal_es_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(es_energyIntegral,&pathEI)");
    */

    color.push_back(6);
    color.push_back(9);

    label_JUNO_normal.push_back("C-12 + ES + NC");
    label_JUNO_normal.push_back("C-12 #nu_{e}");
    label_JUNO_normal.push_back("C-12 #bar{#nu}_{e}");
    label_JUNO_normal.push_back("ES");
    label_JUNO_normal.push_back("NC");
    label_JUNO_normal.push_back("IBD");

    pathEI = "../output/histograms/all_channels/15sol_JUNO_normal_all.png";
    gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_JUNO_normal, color, label_JUNO_normal,ylabel, &pathEI, -2, 4, -10, 3, JUNO_legend)");

    JUNO_normal_integral = (*histograms_JUNO_normal)[0]->Integral();
    file->Close();


    // JUNO, inverted ordering, smeared, 15 solar masses
    file = new TFile(JUNO_INVERTED_PATH);
    histograms_JUNO_inverted = getHists(file, histNames, 6);
    /*
    path = ( "../output/histograms/15sol_JUNO_inverted_sum.png");
    gROOT->ProcessLine(".x drawSingleSnowHist.C(sum, &path)");
    pathEI = "../output/histograms/15sol_JUNO_inverted_sum_bg1_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(sum_bg1_energyIntegral, &pathEI)");

    path = "../output/histograms/15sol_JUNO_inverted_nue.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nue, &path)");
    pathEI = "../output/histograms/15sol_JUNO_inverted_nue_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nue_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_JUNO_inverted_nuebar.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nuebar, &path)");
    pathEI = "../output/histograms/15sol_JUNO_inverted_nuebar_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nuebar_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_JUNO_inverted_es.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(es, &path)");
    pathEI = "../output/histograms/15sol_JUNO_inverted_es_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(es_energyIntegral,&pathEI)");
    */

    label_JUNO_inverted.push_back("C-12 + ES + NC");
    label_JUNO_inverted.push_back("C-12 #nu_{e}");
    label_JUNO_inverted.push_back("C-12 #bar{#nu}_{e}");
    label_JUNO_inverted.push_back("ES");
    label_JUNO_inverted.push_back("NC");
    label_JUNO_inverted.push_back("IBD");

    pathEI = "../output/histograms/all_channels/15sol_JUNO_inverted_all.png";
    gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_JUNO_inverted, color, label_JUNO_inverted,ylabel, &pathEI, -2, 4, -10, 3, JUNO_legend)");

    JUNO_inverted_integral = (*histograms_JUNO_inverted)[0]->Integral();
    file->Close();

    // Hyper-K, normal ordering, smeared, 15 solar masses
    file = new TFile("../output/ROOT/HYPERK_normal.root");
    histograms_HYPERK_normal = getHists(file, histNames, 6);
    /*
    path = ( "../output/histograms/15sol_HYPERK_normal_sum.png");
    gROOT->ProcessLine(".x drawSingleSnowHist.C(sum, &path)");
    pathEI = "../output/histograms/15sol_HYPERK_normal_sum_bg1_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(sum_bg1_energyIntegral, &pathEI)");

    path = "../output/histograms/15sol_HYPERK_normal_nue.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nue, &path)");
    pathEI = "../output/histograms/15sol_HYPERK_normal_nue_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nue_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_HYPERK_normal_nuebar.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nuebar, &path)");
    pathEI = "../output/histograms/15sol_HYPERK_normal_nuebar_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nuebar_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_HYPERK_normal_es.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(es, &path)");
    pathEI = "../output/histograms/15sol_HYPERK_normal_es_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(es_energyIntegral,&pathEI)");
    */


    label_HYPERK_normal.push_back("O-16 + ES + NC");
    label_HYPERK_normal.push_back("O-16 #nu_{e}");
    label_HYPERK_normal.push_back("O-16 #bar{#nu}_{e}");
    label_HYPERK_normal.push_back("ES");
    label_HYPERK_normal.push_back("NC");
    label_HYPERK_normal.push_back("IBD");

    pathEI = "../output/histograms/all_channels/15sol_HYPERK_normal_all.png";
    gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_HYPERK_normal, color, label_HYPERK_normal,ylabel, &pathEI, -2, 4, -8, 3, HYPERK_legend)");

    HYPERK_normal_integral = (*histograms_HYPERK_normal)[0]->Integral();
    file->Close();

    // Hyper-K, inverted ordering, smeared, 15 solar masses
    file = new TFile("../output/ROOT/HYPERK_inverted.root");
    histograms_HYPERK_inverted = getHists(file, histNames, 6);

    /*
    path = ( "../output/histograms/15sol_HYPERK_inverted_sum.png");
    gROOT->ProcessLine(".x drawSingleSnowHist.C(sum, &path)");
    pathEI = "../output/histograms/15sol_HYPERK_inverted_sum_bg1_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(sum_bg1_energyIntegral, &pathEI)");

    path = "../output/histograms/15sol_HYPERK_inverted_nue.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nue, &path)");
    pathEI = "../output/histograms/15sol_HYPERK_inverted_nue_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nue_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_HYPERK_inverted_nuebar.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(nuebar, &path)");
    pathEI = "../output/histograms/15sol_HYPERK_inverted_nuebar_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(nuebar_energyIntegral,&pathEI)");

    path = "../output/histograms/15sol_HYPERK_inverted_es.png";
    gROOT->ProcessLine(".x drawSingleSnowHist.C(es, &path)");
    pathEI = "../output/histograms/15sol_HYPERK_inverted_es_energyIntegral.png";
    gROOT->ProcessLine(".x drawSingleSnowEnergyHist.C(es_energyIntegral,&pathEI)");
    */

    label_HYPERK_inverted.push_back("O-16 + ES + NC");
    label_HYPERK_inverted.push_back("O-16 #nu_{e}");
    label_HYPERK_inverted.push_back("O-16 #bar{#nu}_{e}");
    label_HYPERK_inverted.push_back("ES");
    label_HYPERK_inverted.push_back("NC");
    label_HYPERK_inverted.push_back("IBD");

    pathEI = "../output/histograms/all_channels/15sol_HYPERK_inverted_all.png";
    gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_HYPERK_inverted, color, label_HYPERK_inverted,ylabel, &pathEI, -2, 4, -8, 3, HYPERK_legend)");

    HYPERK_inverted_integral = (*histograms_HYPERK_inverted)[0]->Integral();
    file->Close();

    std::cout << " ********************************************* " << std::endl;
    std::cout << "Events for DUNE:" << std::endl;
    std::cout << "Sum normal: " << DUNE_normal_integral << std::endl;
    std::cout << "Sum inverted: " << DUNE_inverted_integral << std::endl;
    std::cout << std::endl;

    std::cout << "Events for JUNO:" << std::endl;
    std::cout << "Sum normal: " << JUNO_normal_integral << std::endl;
    std::cout << "Sum inverted: " << JUNO_inverted_integral << std::endl;
    std::cout << std::endl;

    std::cout << "Events for Hyper-K:" << std::endl;
    std::cout << "Sum normal: " << HYPERK_normal_integral << std::endl;
    std::cout << "Sum inverted: " << HYPERK_inverted_integral << std::endl;
    std::cout << std::endl;
}