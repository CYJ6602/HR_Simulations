void plot_lowlevel2(const char* filename = "histos.root")
{
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTextFont(132);

 
  const char *dirname="/home/cho/Desktop/SimulationPackage/HRArray/examples/Y77_levelscheme/hist/";
  const char *ext="lowlevel.root";
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

  const int nn=5;
  
  if(nn!=j)
    {
      cout << "Something wrong, maybe number of hist files" << endl;
      cout << "Please check the code" << endl;      
    }
  
  TPad *p1;
  TPad *p2;
  TPad *p3;
  TCanvas *c1 = new TCanvas("c1","Miniball hist",800,400);
  TCanvas *c2 = new TCanvas("c2","Tracking hist",800,400);
  TCanvas *c3 = new TCanvas("c3","Total hist",800,400);
  c1->cd();
  p1 = new TPad("p1","p1",0,0,1,1);
  p1->SetTopMargin(0.01);
  p1->SetLeftMargin(0.08);
  p1->SetBottomMargin(0.05);
  p1->SetRightMargin(0.03);
  p1->Draw();
  //p->SetLogy();
  p1->cd();
  
  c2->cd();
  p2 = new TPad("p2","p2",0,0,1,1);
  p2->SetTopMargin(0.01);
  p2->SetLeftMargin(0.08);
  p2->SetBottomMargin(0.05);
  p2->SetRightMargin(0.03);
  p2->Draw();
  //p->SetLogy();
  p2->cd();

  c3->cd();
  p3 = new TPad("p3","p3",0,0,1,1);
  p3->SetTopMargin(0.01);
  p3->SetLeftMargin(0.08);
  p3->SetBottomMargin(0.05);
  p3->SetRightMargin(0.03);
  p3->Draw();
  //p->SetLogy();
  p3->cd();
  

  TH1F* h[nn+1][5];
  for(int i=0;i<nn;i++){
    if(i==0)
      {
	h[nn][0] = (TH1F*)f[i]->Get("egamABdc");
	h[nn][0]->SetName("Total_hist");
	
	h[nn][1] = (TH1F*)f[i]->Get("MBegamABdc");
	h[nn][1]->SetName("MB_hist");
	
	h[nn][2] = (TH1F*)f[i]->Get("MBegamAB");
	h[nn][2]->SetName("MB_hist_nodc");
	
	h[nn][3] = (TH1F*)f[i]->Get("GRegamABdc");
	h[nn][3]->SetName("Tracking_hist");
	
	h[nn][4] = (TH1F*)f[i]->Get("GRegamAB");
	h[nn][4]->SetName("Tracking_hist_nodc");
      }
    else
      {
	h[nn][0]->Add((TH1F*)f[i]->Get("egamABdc"));
	h[nn][1]->Add((TH1F*)f[i]->Get("MBegamABdc"));
	h[nn][2]->Add((TH1F*)f[i]->Get("MBegamAB"));
	h[nn][3]->Add((TH1F*)f[i]->Get("GRegamABdc"));
	h[nn][4]->Add((TH1F*)f[i]->Get("GRegamAB"));
      }
   
   
  }

  for(int i=0 ; i<4; i++)
    {
      h[nn][i]->Rebin(2);
      h[nn][i]->GetYaxis()->SetTitle("counts / 2 keV");
      h[nn][i]->GetYaxis()->SetTitleSize(0.045);
      h[nn][i]->GetYaxis()->SetTitleOffset(0.7);
      h[nn][i]->GetYaxis()->SetLabelSize(0.05);
      h[nn][i]->GetYaxis()->SetLabelOffset(0.01);
      
      h[nn][i]->GetXaxis()->SetTitle("E_{#gamma} (keV)");
      h[nn][i]->GetXaxis()->SetTitleSize(0.045);
      h[nn][i]->GetXaxis()->SetTitleOffset(1.2);
      h[nn][i]->GetXaxis()->SetLabelSize(0.05);
      h[nn][i]->GetXaxis()->SetLabelOffset(0.01);
      
      h[nn][i]->GetXaxis()->SetRangeUser(0,700);
      //h[nn][i]->GetYaxis()->SetRangeUser(0,80);
      
      h[nn][i]->GetXaxis()->SetTitleFont(132);
      h[nn][i]->GetXaxis()->SetLabelFont(132);
      h[nn][i]->GetYaxis()->SetTitleFont(132);
      h[nn][i]->GetYaxis()->SetLabelFont(132);
      //h[nn][i]->Draw();
      
      //h[nn][i]->SetLineColor(i+2);
      //h[nn][i]->Draw("same");
    }

  c1->cd();
  h[nn][1]->Draw();
  c2->cd();
  h[nn][3]->Draw();
  c3->cd();
  h[nn][0]->Draw();

  c1->SaveAs("Y77_Miniball_hist.jpg");
  c2->SaveAs("Y77_Tracking_hist.jpg");
  c3->SaveAs("Y77_Total_hist.jpg");
  
  /*
TH1F* h[nn+1];
  for(int i=0;i<nn;i++){
    if(i==0){
      h[nn] = (TH1F*)f[i]->Get("egamABdc");
      h[nn]->SetName("Total_hist");
    }
    else
      h[nn]->Add((TH1F*)f[i]->Get("egamABdc"));
    h[i] = (TH1F*)f[i]->Get("egamABdc");
  }  
  h[nn]->Rebin(2);
  h[nn]->SetTitle("Total_hist");
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
  // c->SaveAs("zr80_level.eps");
  */

  TFile* f0 = new TFile(filename,"RECREATE");
  for(int i=0 ; i<5 ; i++)
    h[nn][i]->Write();
  f0->Close();
 
  
}
