void Fitting(const char* filename = "zr80_826keV_19200evt_lowlevel.root")
{
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTextFont(132);

  TFile* file = new TFile(filename);

  TH1F* h1 = new TH1F();
  h1 = (TH1F*)file->Get("GRegamABdc");

  h1->Rebin(2);
  
  TF1* f1 = new TF1("f1","exp(-1/(0.014*[0])*13*(0.422-0.906*sqrt(0.221/(0.221-(1-0.801*[1]/x)*(1-0.801*[1]/x))-1)))",500,550);

  // TF1* f2 = new TF1("f2","f1*(-1)/0.",740,800);
  f1->SetParameters(8.7,537);
  
  h1->Fit("f1","","",510,530);
  
}
