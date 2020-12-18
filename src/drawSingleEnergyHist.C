void drawSingleEnergyHist (TH1D * hist, TString * path)
{
  gStyle->SetOptStat ( 0 );
  gStyle->SetOptTitle ( 0 );
  gStyle->SetCanvasColor(0);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadRightMargin(0.1);
  
  TCanvas canvas ( "canvas", "", 1100, 1000);
 
  hist->SetStats(0);
  
  hist->GetXaxis()->SetTitle("Time to Bounce / s");
  hist->GetXaxis()->SetTitleOffset(1.3);
  //hist->GetXaxis()->SetRangeUser(-6, 2);
  
  hist->GetYaxis()->SetTitle("Integrated Flux / cm^{-2}s^{-1}");
  hist->GetYaxis()->SetTitleOffset(1.5);
  hist->GetYaxis()->SetRangeUser(pow(10,49),pow(10,56));
  gPad->SetLogy();  
  
  // Remove the current axis
  
  hist->GetXaxis()->SetLabelOffset(999);
  hist->GetXaxis()->SetTickLength(0);

  hist->Draw();
  // Redraw the new axis
  gPad->Update();
  
  double xmin = gPad->GetUxmax();
  double xmax = gPad->GetUxmin();
  double ymin = pow(10, gPad->GetUymin());
  double ymax = pow(10, gPad->GetUymin());
  
  //std::cout << xmin << " " << xmax << " " << ymin << " " << ymax <<std::endl;
  
  TGaxis *newaxis = new TGaxis( /*2, pow(10,49), -6,pow(10,49),*/ xmin, ymin, xmax, ymax, pow(10,-xmin),pow(10,-xmax),310,"G");
  newaxis->SetLabelOffset(-0.1);
  newaxis->Draw();
  
  // create png file
  canvas.Print(*path);
}