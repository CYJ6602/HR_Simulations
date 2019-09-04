void Merging_coin_trees_1n(const char* filename = "coin_tree.root")
{
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTextFont(132);

 
  const char *dirname="/home/cho/Desktop/SimulationPackage_updated/HrROOT/examples/Zr80_levelscheme/coin/";
  const char *ext="lowlevel_1n.root";
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

  TTree* t[nn+1];
  TH2F* Total_coin_hist = new TH2F("Total_coin_hist","Total_coin_hist",2000,0,2000,2000,0,2000);
  TH2F* temph = new TH2F("temph","temph",2000,0,2000,2000,0,2000);
  
  for(int i=0;i<nn;i++){
    t[i] = (TTree*)f[i]->Get("Total_coin_tree");

    t[i]->Draw("Totalgc2_E:Totalgc1_E>>temph(2000,0,2000,2000,0,2000)","Totalgc2_E!=Totalgc1_E","goff");

    Total_coin_hist->Add(temph);
  }

  TH2F* GR_coin_hist = new TH2F("GR_coin_hist","GR_coin_hist",2000,0,2000,2000,0,2000);
  //TH2F* temph = new TH2F("temph","temph",2000,0,2000,2000,0,2000);
  
  for(int i=0;i<nn;i++){
    t[i] = (TTree*)f[i]->Get("GRcoin_tree");

    t[i]->Draw("GRgc2_E:GRgc1_E>>temph(2000,0,2000,2000,0,2000)","GRgc2_E!=GRgc1_E","goff");

    GR_coin_hist->Add(temph);
  }

  TH2F* MB_coin_hist = new TH2F("MB_coin_hist","MB_coin_hist",2000,0,2000,2000,0,2000);
  //TH2F* temph = new TH2F("temph","temph",2000,0,2000,2000,0,2000);
  
  for(int i=0;i<nn;i++){
    t[i] = (TTree*)f[i]->Get("MBcoin_tree");

    t[i]->Draw("MBgc2_E:MBgc1_E>>temph(2000,0,2000,2000,0,2000)","MBgc2_E!=MBgc1_E","goff");

    MB_coin_hist->Add(temph);
  }

 
  
  //TTree* total_tree = TTree::MergeTrees(tree_list);
  //total_tree->SetName("coin_tree");
  
  
  TFile* f0 = new TFile(filename,"RECREATE");
  //total_tree->Write();
  Total_coin_hist->Write();
  GR_coin_hist->Write();
  MB_coin_hist->Write();
  f0->Close();
 
  
}
