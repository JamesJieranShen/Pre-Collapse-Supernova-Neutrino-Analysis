{
  #include <vector>
  
  double DUNE_normal_integral, DUNE_inverted_integral, JUNO_normal_integral, JUNO_inverted_integral, HYPERK_normal_integral, HYPERK_inverted_integral;
  
// global variables
TGaxis::SetMaxDigits(2);

// 12 solar masses SN no oscillation
TFile katofile15 ("../output/ROOT/kato15sol_emitted.root");

double emitted_legend [4] = {0.17,0.6,0.3,0.9};

std::vector<TH1D*> histograms_emitted;
histograms_emitted.push_back(amu_energyIntegral);
histograms_emitted.push_back(mu_energyIntegral);
histograms_emitted.push_back(anu_energyIntegral);
histograms_emitted.push_back(nu_energyIntegral);

std::vector<Color_t> color;
color.push_back(1);
color.push_back(2);
color.push_back(3);
color.push_back(4);

std::vector<std::string> label_emitted;
label_emitted.push_back("#bar{#nu}_{x}");
label_emitted.push_back("#nu_{x}");
label_emitted.push_back("#bar{#nu}_{e}");
label_emitted.push_back("#nu_{e}");

std::string ylabel_emitted = "Integrated Flux / cm^{-2}s^{-1}";
TString pathEI ("../output/histograms/all_channels/15sol_emitted_all.png");
gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_emitted, color, label_emitted, ylabel_emitted, &pathEI, -2, 5, 50, 56,emitted_legend)");

katofile15.Close();

// DUNE, normal ordering, smeared, 15 solar masses 
TFile file_DUNE_normal ("../output/ROOT/DUNE_normal.root");
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

double DUNE_legend [4] = {0.17,0.55,0.35,0.9};

std::vector<TH1D*> histograms_DUNE_normal;
histograms_DUNE_normal.push_back(sum_bg1_energyIntegral);
histograms_DUNE_normal.push_back(nue_th0_energyIntegral);
histograms_DUNE_normal.push_back(nuebar_th0_energyIntegral);
histograms_DUNE_normal.push_back(es_th0_energyIntegral);

std::vector<std::string> label_DUNE_normal;
label_DUNE_normal.push_back("Ar-40 + ES");
label_DUNE_normal.push_back("Ar-40 #nu_{e}");
label_DUNE_normal.push_back("Ar-40 #bar{#nu}_{e}");
label_DUNE_normal.push_back("ES");

std::string ylabel = "Events";

pathEI = "../output/histograms/all_channels/15sol_DUNE_normal_all.png";
gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_DUNE_normal, color, label_DUNE_normal, ylabel, &pathEI, -2, 4, -3, 3,DUNE_legend)");

DUNE_normal_integral = sum_bg1_energyIntegral.Integral();

file_DUNE_normal.Close();

// DUNE, inverted ordering, smeared, 15 solar masses 
TFile file_DUNE_inverted ("../output/ROOT/DUNE_inverted.root");
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
std::vector<TH1D*> histograms_DUNE_inverted;
histograms_DUNE_inverted.push_back(sum_bg1_energyIntegral);
histograms_DUNE_inverted.push_back(nue_th0_energyIntegral);
histograms_DUNE_inverted.push_back(nuebar_th0_energyIntegral);
histograms_DUNE_inverted.push_back(es_th0_energyIntegral);

std::vector<std::string> label_DUNE_inverted;
label_DUNE_inverted.push_back("Ar-40 + ES");
label_DUNE_inverted.push_back("Ar-40 #nu_{e}");
label_DUNE_inverted.push_back("Ar-40 #bar{#nu}_{e}");
label_DUNE_inverted.push_back("ES");

pathEI = "../output/histograms/all_channels/15sol_DUNE_inverted_all.png";
gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_DUNE_inverted, color, label_DUNE_inverted,ylabel, &pathEI, -2, 4, -2, 3,DUNE_legend)");

DUNE_inverted_integral = sum_bg1_energyIntegral.Integral();

file_DUNE_inverted.Close();

// JUNO, normal ordering, smeared, 15 solar masses 
TFile file_JUNO_normal ("../output/ROOT/JUNO_normal.root");
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

double JUNO_legend [4] = {0.17,0.15,0.33,0.6};

std::vector<TH1D*> histograms_JUNO_normal;
histograms_JUNO_normal.push_back(sum_bg1_energyIntegral);
histograms_JUNO_normal.push_back(nue_th0_energyIntegral);
histograms_JUNO_normal.push_back(nuebar_th0_energyIntegral);
histograms_JUNO_normal.push_back(es_th0_energyIntegral);
histograms_JUNO_normal.push_back(nc_th0_energyIntegral);
histograms_JUNO_normal.push_back(ibd_th0_energyIntegral);

color.push_back(6);
color.push_back(9);

std::vector<std::string> label_JUNO_normal;
label_JUNO_normal.push_back("C-12 + ES + NC");
label_JUNO_normal.push_back("C-12 #nu_{e}");
label_JUNO_normal.push_back("C-12 #bar{#nu}_{e}");
label_JUNO_normal.push_back("ES");
label_JUNO_normal.push_back("NC");
label_JUNO_normal.push_back("IBD");

pathEI = "../output/histograms/all_channels/15sol_JUNO_normal_all.png";
gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_JUNO_normal, color, label_JUNO_normal,ylabel, &pathEI, -2, 4, -10, 3, JUNO_legend)");

JUNO_normal_integral = sum_bg1_energyIntegral.Integral();

file_JUNO_normal.Close();

// JUNO, inverted ordering, smeared, 15 solar masses 
TFile file_JUNO_inverted ("../output/ROOT/JUNO_inverted.root");
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
std::vector<TH1D*> histograms_JUNO_inverted;
histograms_JUNO_inverted.push_back(sum_bg1_energyIntegral);
histograms_JUNO_inverted.push_back(nue_th0_energyIntegral);
histograms_JUNO_inverted.push_back(nuebar_th0_energyIntegral);
histograms_JUNO_inverted.push_back(es_th0_energyIntegral);
histograms_JUNO_inverted.push_back(nc_th0_energyIntegral);
histograms_JUNO_inverted.push_back(ibd_th0_energyIntegral);

std::vector<std::string> label_JUNO_inverted;
label_JUNO_inverted.push_back("C-12 + ES + NC");
label_JUNO_inverted.push_back("C-12 #nu_{e}");
label_JUNO_inverted.push_back("C-12 #bar{#nu}_{e}");
label_JUNO_inverted.push_back("ES");
label_JUNO_inverted.push_back("NC");
label_JUNO_inverted.push_back("IBD");

pathEI = "../output/histograms/all_channels/15sol_JUNO_inverted_all.png";
gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_JUNO_inverted, color, label_JUNO_inverted,ylabel, &pathEI, -2, 4, -10, 3, JUNO_legend)");

JUNO_inverted_integral = sum_bg1_energyIntegral.Integral();

file_JUNO_inverted.Close();

// Hyper-K, normal ordering, smeared, 15 solar masses 
TFile file_HYPERK_normal ("../output/ROOT/HYPERK_normal.root");
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

double HYPERK_legend [4] = {0.17,0.15,0.33,0.6};

std::vector<TH1D*> histograms_HYPERK_normal;
histograms_HYPERK_normal.push_back(sum_bg1_energyIntegral);
histograms_HYPERK_normal.push_back(nue_th0_energyIntegral);
histograms_HYPERK_normal.push_back(nuebar_th0_energyIntegral);
histograms_HYPERK_normal.push_back(es_th0_energyIntegral);
histograms_HYPERK_normal.push_back(nc_th0_energyIntegral);
histograms_HYPERK_normal.push_back(ibd_th0_energyIntegral);

std::vector<std::string> label_HYPERK_normal;
label_HYPERK_normal.push_back("O-16 + ES + NC");
label_HYPERK_normal.push_back("O-16 #nu_{e}");
label_HYPERK_normal.push_back("O-16 #bar{#nu}_{e}");
label_HYPERK_normal.push_back("ES");
label_HYPERK_normal.push_back("NC");
label_HYPERK_normal.push_back("IBD");

pathEI = "../output/histograms/all_channels/15sol_HYPERK_normal_all.png";
gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_HYPERK_normal, color, label_HYPERK_normal,ylabel, &pathEI, -2, 4, -8, 3, HYPERK_legend)");

HYPERK_normal_integral = sum_bg1_energyIntegral.Integral();

file_HYPERK_normal.Close();

// Hyper-K, inverted ordering, smeared, 15 solar masses 
TFile file_HYPERK_inverted ("../output/ROOT/HYPERK_inverted.root");
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
std::vector<TH1D*> histograms_HYPERK_inverted;
histograms_HYPERK_inverted.push_back(sum_bg1_energyIntegral);
histograms_HYPERK_inverted.push_back(nue_th0_energyIntegral);
histograms_HYPERK_inverted.push_back(nuebar_th0_energyIntegral);
histograms_HYPERK_inverted.push_back(es_th0_energyIntegral);
histograms_HYPERK_inverted.push_back(nc_th0_energyIntegral);
histograms_HYPERK_inverted.push_back(ibd_th0_energyIntegral);

std::vector<std::string> label_HYPERK_inverted;
label_HYPERK_inverted.push_back("O-16 + ES + NC");
label_HYPERK_inverted.push_back("O-16 #nu_{e}");
label_HYPERK_inverted.push_back("O-16 #bar{#nu}_{e}");
label_HYPERK_inverted.push_back("ES");
label_HYPERK_inverted.push_back("NC");
label_HYPERK_inverted.push_back("IBD");

pathEI = "../output/histograms/all_channels/15sol_HYPERK_inverted_all.png";
gROOT->ProcessLine(".x drawSameEnergyHist.C(histograms_HYPERK_inverted, color, label_HYPERK_inverted,ylabel, &pathEI, -2, 4, -8, 3, HYPERK_legend)");

HYPERK_inverted_integral = sum_bg1_energyIntegral.Integral();

file_HYPERK_inverted.Close();

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