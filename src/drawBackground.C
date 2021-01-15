{
std::string detectors [] = {"DUNE", "JUNO", "HYPERK"};
std::string ordering [] = {"normal", "inverted"};

double sigmaUp [3][2]; 
sigmaUp[0][0] = 20; 
sigmaUp[0][1] = 30; 
sigmaUp[1][0] = 20; 
sigmaUp[1][1] = 20; 
sigmaUp[2][0] = 20; 
sigmaUp[2][1] = 20;

gStyle->SetOptStat ( 0 );
  gStyle->SetOptTitle ( 0 );
  gStyle->SetCanvasColor(0);
  gStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadRightMargin(0.18);

for ( int i = 0; i < 3; i++ )
{
  for ( int j = 0; j < 2; j++ )
  {
    std::string filepath = std::string("../output/ROOT/") + detectors[i] + std::string("_") + ordering[j] + std::string(".root");
    //gROOT->ProcessLine((std::string(".x drawbg.C(\"")+ filepath + "\", \""+ detectors[i]+ "\", \"" +ordering[j]+"\", " + sigmaUp[i][j]+", true)").Data());
    gROOT->ProcessLine((std::string(".x drawbg.C(\"")+ filepath + "\", \""+ detectors[i]+ "\", \"" +ordering[j]+"\", "+ sigmaUp[i][j]+", false)").Data());
    gROOT->ProcessLine((std::string(".x bgdist.C(\"")+ filepath + "\", \""+ detectors[i]+ "\", \"" +ordering[j]+"\", 10.)").c_str());      
  }
}
}