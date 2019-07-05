{
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTextFont(132);

 
  const char *dirname="/home/cho/Desktop/SimulationPackage/HRArray/examples/Zr80_levelscheme/hist/";
  const char *ext="evt.root";
  TSystemDirectory dir(dirname, dirname);
  
  const int mm = 100;
  TFile *f[mm];
  int j=0;
  
  TList *files = dir.GetListOfFiles();
  if (files)
    {
      TSystemFile *file;
      TString fname;
      TIter next(files);
      
      while((file=(TSystemFile*)next()))
	{
	  fname = file->GetName();
	  if (!file->IsDirectory() && fname.EndsWith(ext))
	    {
	      f[j] = new TFile(fname);
	      j++;
	    }
	}

      cout << "Total number of files = " << j << endl;
      /*
      cout << file->GetName() << endl;
      file = (TSystemFile*)next();
      cout << file->GetName() << endl;
      file = (TSystemFile*)next();
      cout << file->GetName() << endl;
      */
      /*
      while((file = (TSystemFile*)next()))
	{
	  fname = file->GetName();
	  if (!file->IsDirectory() && fname.EndsWith(ext))
	    {
	      f[j] = new TFile(fname);
	      cout << fname << endl;
	    }
	  j++;
	}
      */
           
    }

  const int nn=13;
  
  if(nn!=j)
    {
      cout << "Something wrong, maybe number of hist files" << endl;
      cout << "Please check the code" << endl;      
    }
  
  TPad *p;
  TCanvas *c = new TCanvas("c","Miniball_hist_nodc",700,600);
  c->cd();
  p = new TPad("p","p",0,0,1,1);
  p->SetTopMargin(0.01);
  p->SetLeftMargin(0.08);
  p->SetBottomMargin(0.11);
  p->SetRightMargin(0.01);
  p->Draw();
  p->SetLogy();
  p->cd();

  TH1F* h[nn+1];
  for(int i=0;i<nn;i++){
    if(i==0){
      h[nn] = (TH1F*)f[i]->Get("MBegamAB");
      h[nn]->SetName("Miniball_hist_nodc");
    }
    else
      h[nn]->Add((TH1F*)f[i]->Get("MBegamAB"));
    h[i] = (TH1F*)f[i]->Get("MBegamAB");
  }  
  h[nn]->Rebin(2);
  h[nn]->SetTitle("Miniball_hist_nodc");
  h[nn]->GetYaxis()->SetTitle("counts / 2 keV");
  h[nn]->GetYaxis()->SetTitleSize(0.045);
  h[nn]->GetYaxis()->SetTitleOffset(0.9);
  h[nn]->GetYaxis()->SetLabelSize(0.035);
  h[nn]->GetYaxis()->SetLabelOffset(0.01);

  h[nn]->GetXaxis()->SetTitle("E_{#gamma} (keV)");
  h[nn]->GetXaxis()->SetTitleSize(0.045);
  h[nn]->GetXaxis()->SetTitleOffset(1.0);
  h[nn]->GetXaxis()->SetLabelSize(0.035);
  h[nn]->GetXaxis()->SetLabelOffset(0.013);

  h[nn]->GetXaxis()->SetRangeUser(50,4950);
  h[nn]->GetYaxis()->SetRangeUser(1,20000);

  h[nn]->GetXaxis()->SetTitleFont(132);
  h[nn]->GetXaxis()->SetLabelFont(132);
  h[nn]->GetYaxis()->SetTitleFont(132);
  h[nn]->GetYaxis()->SetLabelFont(132);
  h[nn]->Draw();
  
  for(int i=0;i<nn;i++){
    h[i]->SetLineColor(i%5+2);
    h[i]->SetLineStyle(i/5);
    h[i]->Draw("same");
  }
  c->SaveAs("zr80_level_GR.eps");

   TFile* f0 = new TFile("histos.root","UPDATE");
  h[nn]->Write();
  f0->Close();
 
  
}
