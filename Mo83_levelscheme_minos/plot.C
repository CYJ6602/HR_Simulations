{
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTextFont(132);

  /*
  const char *dirname="hist/";
  const char *ext=".root";
  TSystemDirectory dir(dirname, dirname);
  
  const int nn = 34;
  TFile *f[nn];
  int j=0;
  
  TList *files2 = dir.GetListOfFiles();
  if (files2)
    {
      TSystemFile *file;
      TString fname;
      TIter next(files2);
      while ((file=(TSystemFile*)next()))
	{
	  fname = file->GetName();
	  f[j] = new TFile("hist/"+fname);
	  if (!file->IsDirectory() && fname.EndsWith(ext))
	    { cout << fname.Data() << endl; }
	  j++;
	}
    }
  */

  const int nn = 34;
  TFile *f[nn];  
  f[0] = new TFile("hist/zr80_289keV_10000evt.root");
  f[1] = new TFile("hist/zr80_770keV_10000evt.root");
  f[2] = new TFile("hist/zr80_826keV_10000evt.root");
  f[3] = new TFile("hist/zr80_1080keV_10000evt.root");
  f[4] = new TFile("hist/zr80_1250keV_10000evt.root");
  f[5] = new TFile("hist/zr80_1300keV_10000evt.root");
  f[6] = new TFile("hist/zr80_1605keV_10000evt.root");
  f[7] = new TFile("hist/zr80_1620keV_10000evt.root");
  f[8] = new TFile("hist/zr80_1630keV_10000evt.root");
  f[9] = new TFile("hist/zr80_1700keV_10000evt.root");
  f[10] = new TFile("hist/zr80_1850keV_10000evt.root");
  f[11] = new TFile("hist/zr80_2020keV_10000evt.root");
  f[12] = new TFile("hist/zr80_2120keV_10000evt.root");
  f[13] = new TFile("hist/zr80_2220keV_10000evt.root");
  f[14] = new TFile("hist/zr80_2380keV_10000evt.root");
  f[15] = new TFile("hist/zr80_2420keV_10000evt.root");
  f[16] = new TFile("hist/zr80_2470keV_10000evt.root");
  f[17] = new TFile("hist/zr80_2600keV_10000evt.root");
  f[18] = new TFile("hist/zr80_2610keV_10000evt.root");
  f[19] = new TFile("hist/zr80_2620keV_10000evt.root");
  f[20] = new TFile("hist/zr80_2850keV_10000evt.root");
  f[21] = new TFile("hist/zr80_2900keV_10000evt.root");
  f[22] = new TFile("hist/zr80_2950keV_10000evt.root");
  f[23] = new TFile("hist/zr80_3180keV_10000evt.root");
  f[24] = new TFile("hist/zr80_3260keV_10000evt.root");
  f[25] = new TFile("hist/zr80_3460keV_10000evt.root");
  f[26] = new TFile("hist/zr80_3610keV_10000evt.root");
  f[27] = new TFile("hist/zr80_3700keV_10000evt.root");
  f[28] = new TFile("hist/zr80_3789keV_10000evt.root");
  f[29] = new TFile("hist/zr80_3790keV_10000evt.root");
  f[30] = new TFile("hist/zr80_3870keV_10000evt.root");
  f[31] = new TFile("hist/zr80_4000keV_10000evt.root");
  f[32] = new TFile("hist/zr80_4200keV_10000evt.root");
  f[33] = new TFile("hist/zr80_4390keV_10000evt.root");
  
  
  TPad *p;
  TCanvas *c = new TCanvas("c","c",700,600);
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
      h[nn] = (TH1F*)f[i]->Get("egamABdc");
      h[nn]->SetName("sum");
    }
    else
      h[nn]->Add((TH1F*)f[i]->Get("egamABdc"));
    h[i] = (TH1F*)f[i]->Get("egamABdc");
  }  
  h[nn]->Rebin(4);
  h[nn]->GetYaxis()->SetTitle("counts / 4 keV");
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
  c->SaveAs("zr80_level.eps");
}
