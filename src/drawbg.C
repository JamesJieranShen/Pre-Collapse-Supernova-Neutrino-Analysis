#include <iomanip>
#include <string>
void drawbg(std::string filepath, std::string detector, std::string ordering, double sigmaUp, bool include_bg)
{
// array of backgrounds [1/s]
const int bgl = 7;
double backgrounds [] = {0, pow(10,0), pow(10,1), pow(10,2), pow(10,3), pow(10,4), pow(10,5)};
  
int thl = 2;
double thresholds [] = {0, 4};
  
TFile file (filepath.c_str());

gStyle->SetTitleW(1);
gStyle->SetOptStat ( 0 );
gStyle->SetOptTitle ( 1 );
gStyle->SetCanvasColor(0);
gStyle->SetPadLeftMargin(0.1);
gStyle->SetPadRightMargin(0.13);

  TCanvas * canvas = new TCanvas( "canvas", "multipads", 1600, 1000);
  canvas->Divide(3,2);

for ( int i = 0; i < thl; i++ )
{
  std::stringstream ssi;
  ssi << thresholds[i];
  
  std::string thstring;
  std::string bgstring;
  std::string savepath;


  for ( int j = 1; j < bgl; j++ )
  {      
    std::stringstream ssj;
    ssj << std::setprecision(0) << std::fixed << backgrounds[j];
    
    thstring = ssi.str();
    bgstring = ssj.str();
    
    savepath = std::string("../output/histograms/background/") + detector + std::string("_") + ordering + std::string("_th") + thstring ;
    if ( include_bg ) savepath = savepath + std::string("_withbg");
    savepath = savepath + std::string(".png");
    
    std::string histname = std::string("sum_th") + thstring + std::string("_bg") + bgstring + std::string("_energyIntegral");
    if ( include_bg ) histname = histname + std::string("_withbg");
    
    std::string bgname = std::string("bg_") + bgstring;
    
    std::string histtitle = detector + std::string(" ") + ordering + std::string(" ordering event rates, threshold: ") + ssi.str() + std::string(" MeV, background: ") + ssj.str() + std::string(" Hz");
    
    canvas->cd(j);
    
    TH1D * hist = (TH1D*)file.Get(histname.c_str());
    TH1D * bg   = (TH1D*)file.Get(bgname.c_str());

    hist->SetStats(0);
    
    hist->SetTitle(histtitle.c_str());
    
    hist->GetXaxis()->SetTitle("Time to Collapse / s");
    hist->GetXaxis()->SetTitleOffset(1.5);

    hist->GetYaxis()->SetTitle("Events");
    hist->GetYaxis()->SetTitleOffset(1.3);
    hist->GetYaxis()->SetRangeUser(1, pow(10,4));
    gPad->SetLogy();

    // Remove the current axis
    hist->GetXaxis()->SetLabelOffset(999);
    hist->GetXaxis()->SetTickLength(0);
    hist->GetXaxis()->SetRangeUser(-3,1);

    hist->SetLineColor(kBlue);
    hist->SetLineWidth(2);
   
    hist->DrawCopy("EHIST");
    if(include_bg) bg->DrawCopy("SAME");

    // Redraw the new axis
    gPad->Update();

    double xmin = gPad->GetUxmin();
    double xmax = gPad->GetUxmax();
    double ymin = gPad->GetUymin();
    double ymax = gPad->GetUymax();
  
    TGaxis newaxis ( xmax, ymin, xmin, ymin, pow(10,-xmax),pow(10,-xmin),310,"G");
    newaxis.SetLabelOffset(-0.1);
    newaxis.DrawClone();
  
    // create sigma histogram
    std::string sigmaname = histname + std::string("_sigma");
    TH1D * sigma = new TH1D(sigmaname.c_str(), histtitle.c_str(), hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
    
    for ( int k = 1; k <= hist->GetNbinsX(); k++ )
    {
      if ( include_bg )
	sigma->SetBinContent(k, pow(10, (( hist->GetBinContent(k) - bg->GetBinContent(k) )   / hist->GetBinError(k) ) ) );
      else 
	sigma->SetBinContent(k, pow(10,(hist->GetBinContent(k) / hist->GetBinError(k) ) ) );
    }
    
    // draw sigma histogram
    double rightmax = 1*log10(sigma->GetMaximum());
   double scale = gPad->GetUymax()/sigmaUp;
  
   // scale according to log scale
   for ( int k = 1; k <= hist->GetNbinsX(); k++ )
    {
      sigma->SetBinContent(k, pow(sigma->GetBinContent(k), scale)); 
    }
   
   sigma->SetLineColor(kRed);
   sigma->SetLineWidth(2);
   sigma->DrawCopy("same");

   //draw an axis on the right side
   TGaxis axis (xmax, pow(10,ymin), xmax, pow(10,ymax), 0, sigmaUp, 510, "+L");
   axis.SetLineColor(kRed);
   axis.SetTitle("significance / #sigma");
   axis.SetLabelColor(kRed);
   axis.DrawClone(); 
  }
    // create png file
  canvas->Print(savepath.c_str()); 
  std::cout << "Threshold: " << thstring << " MeV" << std::endl;
}     
std::cout << "finished" << std::endl;
file.Close();
}