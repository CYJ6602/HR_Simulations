void plot_lowlevel(const char* filename = "histos.root")
{
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTextFont(132);

 
  const char *dirname="/home/cho/Desktop/SimulationPackage/HRArray/examples/Zr80_levelscheme/hist/";
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

  const int nn=11;
  
  if(nn!=j)
    {
      cout << "Something wrong, maybe number of hist files" << endl;
      cout << "Please check the code" << endl;      
    }
  
  TPad *p1;
  TPad *p2;
  TCanvas *c1 = new TCanvas("c1","Miniball hist",1000,400);
  TCanvas *c2 = new TCanvas("c2","Tracking hist",1000,400);
  c1->cd();
  p1 = new TPad("p1","p1",0.9,0.9,1,1);
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
      //h[nn][i]->Rebin(1);
      h[nn][i]->GetYaxis()->SetTitle("counts / 1 keV");
      h[nn][i]->GetYaxis()->SetTitleSize(0.045);
      h[nn][i]->GetYaxis()->SetTitleOffset(0.7);
      h[nn][i]->GetYaxis()->SetLabelSize(0.05);
      h[nn][i]->GetYaxis()->SetLabelOffset(0.01);
      
      h[nn][i]->GetXaxis()->SetTitle("E_{#gamma} (keV)");
      h[nn][i]->GetXaxis()->SetTitleSize(0.045);
      h[nn][i]->GetXaxis()->SetTitleOffset(1.2);
      h[nn][i]->GetXaxis()->SetLabelSize(0.05);
      h[nn][i]->GetXaxis()->SetLabelOffset(0.01);
      
      h[nn][i]->GetXaxis()->SetRangeUser(0,1500);
      //h[nn][i]->GetYaxis()->SetRangeUser(0,80);
      
      h[nn][i]->GetXaxis()->SetTitleFont(132);
      h[nn][i]->GetXaxis()->SetLabelFont(132);
      h[nn][i]->GetYaxis()->SetTitleFont(132);
      h[nn][i]->GetYaxis()->SetLabelFont(132);
      //h[nn][i]->Draw();
      
      //h[nn][i]->SetLineColor(i+2);
      //h[nn][i]->Draw("same");
    }

  /*
  TF1* f1 = new TF1("f1","pol1(0)+gaus(2)",190,210);
  f1->SetParameters(300.,-0.01,1200.,195.,1.);
  h[nn][3]->Fit("f1","R");

  TF1* f2 = new TF1("f2","pol1(0)+gaus(2)",320,340);
  f2->SetParameters(200.,-0.01,300.,325.,1.);
  h[nn][3]->Fit("f2","R+");

  
  TF1* f3 = new TF1("f3","pol1(0)+gaus(2)",340,360);
  f3->SetParameters(100.,-0.01,100.,345.,1.);
  h[nn][3]->Fit("f3","R+");

  TF1* f4 = new TF1("f4","pol1(0)+gaus(2)",460,500);
  f4->SetParameters(50.,0.01,500.,475.,1.);
  h[nn][3]->Fit("f4","R+");

  TF1* f5 = new TF1("f5","pol1(0)+gaus(2)",510,570);
  f5->SetParameters(50.,0.01,550.,530.,1.);
  h[nn][3]->Fit("f5","R+");

  TF1* f6 = new TF1("f6","pol1(0)+gaus(2)",570,590);
  f6->SetParameters(50.,0.01,50.,575.,1.);
  h[nn][3]->Fit("f6","R+");
  */
  
  /*
  TF1* f7 = new TF1("f7","pol1(0)+gaus(2)",270,310);
  f7->SetParameters(150.,0.1,400.,285.,1.);
  h[nn][3]->Fit("f7","","",283,295);

  TF1* f8 = new TF1("f8","pol1(0)+gaus(2)",270,310);
  f8->SetParameters(150.,0.1,400.,285.,1.);
  h[nn][3]->Fit("f8","","",283,295);

  TF1* f9 = new TF1("f9","pol1(0)+gaus(2)",270,310);
  f9->SetParameters(150.,0.1,400.,285.,1.);
  h[nn][3]->Fit("f9","","",283,295);

  TF1* f10 = new TF1("f10","pol1(0)+gaus(2)",270,310);
  f10->SetParameters(150.,0.1,400.,285.,1.);
  h[nn][3]->Fit("f10","","",283,295);
  */
  

  /*
  TF1* f2 = new TF1("f2","pol(0)+gaus(2)+gaus(5)+gaus(8)",270,310);
  f2->SetParameters(20.,0.001,
		    50.,280.,2.,
		    400.,285.,1.,
		    50.,295.,2.);
  h[nn][3]->Fit("f2","","",270,310);
  */
  
  c1->cd();
  h[nn][1]->Draw();
  c2->cd();
  h[nn][3]->Draw();

  c1->SaveAs("zr80_Miniball_hist.jpg");
  c2->SaveAs("zr80_Tracking_hist.jpg");
  
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
