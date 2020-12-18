void drawSingleSnowHist (TH2D * hist, TString * path)
{
  TCanvas canvas ( "canvas", "", 1100, 1000);
  gStyle->SetOptStat ( 0 );
  gStyle->SetOptTitle ( 0 );
  gStyle->SetCanvasColor(0);
  gStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadRightMargin(0.18);
  hist->SetStats(0);
  
  hist->GetXaxis()->SetTitle("Time to Bounce / s");
  hist->GetXaxis()->SetTitleOffset(1.5);
  
  hist->GetYaxis()->SetTitle("Energy / MeV");
  
  hist->GetZaxis()->SetTitle("Events");
  hist->GetZaxis()->SetTitleOffset(1.3);
  gPad->SetLogz();
  //double max = hist->GetBinContent(h->GetMaximumBin());
  //hist->GetZaxis()->SetRangeUser(1,pow(10,8));
  //gPad->SetLogx();
  //hist->GetXaxis()->SetRangeUser(-pow(10,11),-0.1);
  hist->GetYaxis()->SetRangeUser(0,100);
  //h->GetZaxis()->SetRangeUser(0.1,pow(10,4.5));
  //double xbins[] = {1,2,3,4,5};
  // hist->GetXaxis()->Set(5,xbins);
  gStyle->SetPalette(1);
  hist->Draw("COLZ");
  gPad->Update();
  TPaletteAxis *palette = (TPaletteAxis*)hist->GetListOfFunctions()->FindObject("palette");
  palette->SetY2NDC(0.7);
  
  
  // Remove the current axis
  hist->GetXaxis()->SetLabelOffset(999);
  hist->GetXaxis()->SetTickLength(0);

  // Redraw the new axis
   gPad->Update();
  
  double xmin = gPad->GetUxmax();
  double xmax = gPad->GetUxmin();
  double ymin = gPad->GetUymin();
  double ymax = gPad->GetUymin();
  
  //std::cout << xmin << " " << xmax << " " << ymin << " " << ymax <<std::endl;
  
  TGaxis *newaxis = new TGaxis( /*2, pow(10,49), -6,pow(10,49),*/ xmin, ymin, xmax, ymax, pow(10,-xmin),pow(10,-xmax),310,"G");
  newaxis->SetLabelOffset(-0.1);
  newaxis->Draw();
 canvas.Print(*path);
}