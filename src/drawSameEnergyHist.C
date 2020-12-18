void drawSameEnergyHist (std::vector<TH1D*> histograms, std::vector<Color_t> color, std::vector<std::string> label, std::string ylabel, TString * path, int xLow, int xUp, int yLow, int yUp, double leg[])
{
  gStyle->SetOptStat ( 0 );
  gStyle->SetOptTitle ( 0 );
  gStyle->SetCanvasColor(0);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadRightMargin(0.1);
  
  TCanvas canvas ( "canvas", "", 1100, 1000);
  
  histograms[0]->GetXaxis()->SetTitle("Time to Collapse / s");
  histograms[0]->GetXaxis()->SetTitleOffset(1.3);
  histograms[0]->GetXaxis()->SetRangeUser(-xUp, -xLow);
  
  histograms[0]->GetYaxis()->SetTitle(ylabel.c_str());
  histograms[0]->GetYaxis()->SetTitleOffset(1.5);
  histograms[0]->GetYaxis()->SetRangeUser(pow(10,yLow),pow(10,yUp));
  gPad->SetLogy();  
  
  // Remove the current axis
  
  histograms[0]->GetXaxis()->SetLabelOffset(999);
  histograms[0]->GetXaxis()->SetTickLength(0);

  histograms[0]->SetLineColor(color[0]);
  
  histograms[0]->Draw("HIST");
  for ( int i = 1; i < histograms.size(); i++)
  {
    histograms[i]->SetLineColor(color[i]);
    histograms[i]->SetLineWidth(3);
    histograms[i]->Draw("SAMEHIST");
  }
  histograms[0]->SetLineWidth(3);
  histograms[0]->Draw("SAMEHIST");
  // Redraw the new axis
  gPad->Update();
  
  double xmin = gPad->GetUxmax();
  double xmax = gPad->GetUxmin();
  double ymin = pow(10, gPad->GetUymin());
  double ymax = pow(10, gPad->GetUymin());
  
  TGaxis *newaxis = new TGaxis( xmin, ymin, xmax, ymax, pow(10,-xmin),pow(10,-xmax),310,"G");
  newaxis->SetLabelOffset(-0.1);
  newaxis->Draw();

  // Legend
   auto legend = new TLegend(leg[0],leg[1],leg[2],leg[3], "");
   legend->SetFillColor(0);
   for ( int i = 0; i < label.size(); i++ )
    legend->AddEntry(histograms[i],label[i].c_str(), "l");
   
   legend->Draw();
  
  // create png file
  canvas.Print(*path);

}