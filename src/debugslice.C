{
gROOT->ProcessLine(".L TwoDtoOneD.cpp");
  
int num = 95;


std::vector<Color_t> color;
color.push_back(1);
color.push_back(2);
color.push_back(3);
color.push_back(4);

// normal ordering
TFile *f = new TFile("../output/ROOT/kato15sol_emitted_normal.root");
TH2D nu = (TH2D)f.Get("nu");
TH2D anu = (TH2D)f.Get("anu");
TH2D mu = (TH2D)f.Get("mu");
TH2D amu = (TH2D)f.Get("amu");

std::vector<TH1D> nuslices = TwoDtoOneDY(nu);

std::vector<TH1D> anuslices = TwoDtoOneDY(anu);

std::vector<TH1D> muslices = TwoDtoOneDY(mu);

std::vector<TH1D> amuslices = TwoDtoOneDY(amu);


std::vector<TH1D*> histograms_emitted_normal;
histograms_emitted_normal.push_back(&amuslices[num]);
histograms_emitted_normal.push_back(&muslices[num]);
histograms_emitted_normal.push_back(&anuslices[num]);
histograms_emitted_normal.push_back(&nuslices[num]);

std::vector<std::string> label_emitted_normal;
label_emitted_normal.push_back("#bar{#nu}_{x}");
label_emitted_normal.push_back("#nu_{x}");
label_emitted_normal.push_back("#bar{#nu}_{e}");
label_emitted_normal.push_back("#nu_{e}");

TString path ("../output/histograms/all_channels/timeslice_emitted_normal_all.png");
gROOT->ProcessLine(".x debugDraw.C(histograms_emitted_normal, color, label_emitted_normal, &path,3, 13)");

// without oscillations
TFile *f = new TFile("../output/ROOT/kato15sol_emitted.root");
TH2D nu = (TH2D)f.Get("nu");
TH2D anu = (TH2D)f.Get("anu");
TH2D mu = (TH2D)f.Get("mu");
TH2D amu = (TH2D)f.Get("amu");

std::vector<TH1D> nuslices = TwoDtoOneDY(nu);

std::vector<TH1D> anuslices = TwoDtoOneDY(anu);

std::vector<TH1D> muslices = TwoDtoOneDY(mu);

std::vector<TH1D> amuslices = TwoDtoOneDY(amu);


std::vector<TH1D*> histograms_emitted;
histograms_emitted.push_back(&amuslices[num]);
histograms_emitted.push_back(&muslices[num]);
histograms_emitted.push_back(&anuslices[num]);
histograms_emitted.push_back(&nuslices[num]);

std::vector<std::string> label_emitted;
label_emitted.push_back("#bar{#nu}_{x}");
label_emitted.push_back("#nu_{x}");
label_emitted.push_back("#bar{#nu}_{e}");
label_emitted.push_back("#nu_{e}");

TString path2 ("../output/histograms/all_channels/timeslice_emitted_all.png");
gROOT->ProcessLine(".x debugDraw.C(histograms_emitted, color, label_emitted, &path2, 3, 13)");

// inverted ordering
TFile *f = new TFile("../output/ROOT/kato15sol_emitted_inverted.root");
nu = (TH2D)f.Get("nu");
anu = (TH2D)f.Get("anu");
mu = (TH2D)f.Get("mu");
amu = (TH2D)f.Get("amu");

nuslices = TwoDtoOneDY(nu);

anuslices = TwoDtoOneDY(anu);

muslices = TwoDtoOneDY(mu);

amuslices = TwoDtoOneDY(amu);


std::vector<TH1D*> histograms_emitted_inverted;
histograms_emitted_inverted.push_back(&amuslices[num]);
histograms_emitted_inverted.push_back(&muslices[num]);
histograms_emitted_inverted.push_back(&anuslices[num]);
histograms_emitted_inverted.push_back(&nuslices[num]);

std::vector<std::string> label_emitted_inverted;
label_emitted_inverted.push_back("#bar{#nu}_{x}");
label_emitted_inverted.push_back("#nu_{x}");
label_emitted_inverted.push_back("#bar{#nu}_{e}");
label_emitted_inverted.push_back("#nu_{e}");

path = "../output/histograms/all_channels/timeslice_emitted_inverted_all.png";
gROOT->ProcessLine(".x debugDraw.C(histograms_emitted_inverted, color, label_emitted_inverted, &path, 3, 13)");
}