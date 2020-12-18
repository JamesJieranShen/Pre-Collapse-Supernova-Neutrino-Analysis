#include <iomanip>
void bgdist(std::string filepath, std::string detector, std::string ordering, double interval)
{
gStyle->SetTitleW(0.5);
//gStyle->SetPadBottomMargin(0.7);
const int thl = 1;
const int distl = 17;
// array of backgrounds [1/s]
const int bgl = 61;
double backgrounds [bgl];
  
double bgup = 6;
double bglow = 0;
  
for ( int i = 0; i < bgl; i++ )
{
  backgrounds[i] = pow(10, bglow + (bgup - bglow) / (bgl-1) * i);
}
  
double thresholds [] = { 0, 2, 4, 6};
  
double distances [] = {200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000};

double integralinterval;

TGraph fits [distl];
  
TFile & file = *(new TFile(filepath.c_str()));

TF1 * pot = new TF1("pot", "[0]*pow(x,[1])", 1,pow(10,6));

for ( int i = 0; i < thl; i++ )
{
  TGraph2D * sigma = new TGraph2D(bgl*distl);
  
  std::stringstream ssi;
  ssi << thresholds[i];
    
  std::string canvasname = std::string("canvas") + detector + ordering + ssi.str();
  TCanvas * canvas = new TCanvas( canvasname.c_str(), canvasname.c_str(), 1800, 1000);
  //canvas->SetLogz();
  //canvas->SetLogy();
  gStyle->SetPalette(1);
  
  std::string graphname = std::string("TGraph2D_") + detector + std::string("_") + ordering + std::string("_th") + ssi.str();
  std::string graphtitle = detector + std::string(" ") + ordering + std::string(" ordering");
  sigma->SetName(graphname.c_str());
  sigma->SetTitle(graphtitle.c_str());
 
  std::string histogramname = std::string("TH2D_") + detector + std::string("_") + ordering + std::string("_th") + ssi.str();
  std::string histogramtitle = detector + std::string(" ") + ordering + std::string(" ordering");
  
  TH2D * histogram = new TH2D(histogramname.c_str(), histogramtitle.c_str(), distl,distances[0],distances[distl-1],bgl,bglow,bgup);
  
  int pointcounter = 0;
  for ( int j = 0; j < bgl; j++ ) 
  {
    std::stringstream ssj;
    ssj << std::setprecision(0) << std::fixed << backgrounds[j];
    
    std::string thstring = std::string("_th") + ssi.str();
    if(thresholds[i] == 0 ) thstring = std::string(""); 
    std::string bgstring = ssj.str();
    
    std::string histname = std::string("sum") + thstring + std::string("_bg") + bgstring + std::string("_energyIntegral");
    //std::cout << histname << std::endl;
    
    std::string bgname = std::string("bg_") + bgstring;
    
    std::string histtitle = detector + std::string(" ") + ordering + std::string(" ordering event rates, threshold: ") + ssi.str() + std::string(" MeV, background: ") + ssj.str() + std::string(" Hz");

    TH1D  * hist = file.Get(histname.c_str());
    TH1D  * bg = file.Get(bgname.c_str());
      
    int limitbin = hist->FindBin( -log10(interval) );
    integralinterval = hist->GetBinLowEdge(limitbin);
    
    double residual = 0.0;
    double backgroundsum = 0.0;
    
    for ( int dist = 0; dist < distl; dist++ )
    {      
      for ( int integral = limitbin; integral <= hist->GetNbinsX(); integral++ )
      {
	residual = residual + hist->GetBinContent(integral);
	backgroundsum = backgroundsum + bg->GetBinContent(integral);
      }
      
      residual = residual * pow((200/distances[dist]),2);
      
      double error = sqrt(2*backgroundsum + residual);
      
      if ( residual / error >= 0 )
      {
	sigma->SetPoint(pointcounter, distances[dist], backgrounds[j], residual / error );     
	pointcounter++;
      }
      
      //fits[dist].SetPoint(j-1, backgrounds[j], residual / error );
	//std::cout << (j-1)*10 + dist << " " <<  distances[dist] << " " << backgrounds[j] << " " << residual / error<<  std::endl;  
      //std::cout << sigma->GetYmin() << std::endl;
      if(residual / error > 0.1) histogram->Fill(distances[dist], log10(backgrounds[j]), residual / error );
    }
    
    delete hist;
    delete bg;
  }
  /*
  sigma->Draw();

  sigma->GetXaxis()->SetTitle("distance / pc");
  sigma->GetXaxis()->SetRangeUser(200., 1000.);
  sigma->GetXaxis()->SetTitleOffset(1.6);
  
  sigma->GetYaxis()->SetTitle("background / Hz");
  sigma->GetYaxis()->SetRangeUser(pow(10,0),pow(10,6));
  sigma->GetYaxis()->SetTitleOffset(1.6);
  
  sigma->GetZaxis()->SetTitle("significance");
  sigma->GetZaxis()->SetRangeUser(0., sigma->GetZmax());
  
  //gDirectory->GetList()->Add(sigma);
  
  sigma->SetMarkerStyle(20);
  sigma->Draw("COLZ");
  */
  
  histogram->GetXaxis()->SetTitle("distance / pc");
  //histogram->GetXaxis()->SetRangeUser(200., 1000.);
  //histogram->GetXaxis()->SetTitleOffset(0.1);
  
  histogram->GetYaxis()->SetTitle("log_{10} of background / Hz");
  //histogram->GetYaxis()->SetRangeUser(pow(10,2),pow(10,5));
  //histogram->GetYaxis()->SetTitleOffset(1.6);
  
  histogram->GetZaxis()->SetTitle("significance / #sigma");
  histogram->GetZaxis()->SetRangeUser(0., 15.);//histogram->GetBinContent(histogram->GetMaximumBin()));
  
  histogram->Draw("COLZ");
  
  std::cout << "Max for " << std::setprecision(2) << std::fixed << pow(10, -integralinterval) << "s: " << histogram->GetBinContent(histogram->GetMaximumBin()) << std::endl;

  std::string savepath = std::string("../output/histograms/background/distances/") + detector + std::string("_") + ordering + std::string("_th") + ssi.str() + std::string("_distances.png");

  canvas->Print(savepath.c_str());
/*
  delete sigma;
  
  TFitResultPtr params [distl];
  
  for ( int i = 0; i < distl; i++ )
  {
    params[i] = fits[i].Fit(pot, "SQ");
    //std::cout << detector << " " << ordering << " " << params[i]->Value(0) << " " << params[i]->Value(1) << std::endl;
    //params[i]->Print("V");
  }*/
}
//file.Close();
}