void debugDraw (std::vector<TH1D*> histograms, std::vector<Color_t> color, std::vector<std::string> label, TString * path, int yLow, int yUp)
{
  gStyle->SetOptStat ( 0 );
  gStyle->SetOptTitle ( 0 );
  gStyle->SetCanvasColor(0);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadRightMargin(0.1);
  
  TCanvas canvas ( "canvas", "", 1100, 1000);
  
  histograms[0]->GetXaxis()->SetTitle("Energy / MeV");
  histograms[0]->GetXaxis()->SetTitleOffset(1.3);
  
  histograms[0]->GetYaxis()->SetTitle("Fluence / cm^{-2}");
  histograms[0]->GetYaxis()->SetTitleOffset(1.5);
  histograms[0]->GetYaxis()->SetRangeUser(pow(10,yLow),pow(10,yUp));
  gPad->SetLogy();  
  
  // Remove the current axis
  histograms[0]->SetLineColor(color[0]);
  
  histograms[0]->Draw();
  for ( int i = 1; i < histograms.size(); i++)
  {
    histograms[i]->SetLineColor(color[i]);
    histograms[i]->Draw("SAME");
  }

  // Legend
   auto legend = new TLegend(0.8,0.7,0.9,0.9, "");
   legend->SetFillColor(0);
   for ( int i = 0; i < histograms.size(); i++ )
    legend->AddEntry(histograms[i],label[i].c_str(), "l");
   
   legend->Draw();
  
  // create png file
  canvas.Print(*path);

}