#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include <iomanip>
#include <string.h> 
#include <sys/time.h>
#include <signal.h>

#include"TSystem.h"
#include"TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH2S.h"
#include "TH1S.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TMath.h"
#include "TCutG.h"
#include "TEnv.h"
#include "TKey.h"
#include "TDirectory.h"

#include "CommandLineInterface.hh"
#include "Gretina.hh"
#include "Miniball.hh"
#include "ZeroDeg.hh"
#include "GammaSim.hh"
#include "SimHistograms.hh"

using namespace std;
using namespace TMath;

int main(int argc, char* argv[]){

  vector<char*> InputFiles;
  char* OutputFile = NULL;
  char* TreeName = (char*)"caltr";
  char* SimTreeName = (char*)"simtr";
  CommandLineInterface* interface = new CommandLineInterface();
  
  interface->Add("-i", "inputfiles", &InputFiles);
  interface->Add("-o", "outputfile", &OutputFile);
  interface->CheckFlags(argc, argv);

  if(InputFiles.size() == 0 || OutputFile == NULL){
    cerr<<"You have to provide at least one input file and the output file!"<<endl;
    exit(1);
  }
  cout<<"input file(s):"<<endl;
  for(unsigned int i=0; i<InputFiles.size(); i++){
    cout<<InputFiles[i]<<endl;
  }
  cout<<"output file: "<<OutputFile<< endl;

  TChain* tr  = new TChain(TreeName);
  TChain* str = new TChain(SimTreeName);
  vector<int> events;
  events.resize(InputFiles.size()+1);
  events[0] = 0;
  TFile *dummy;
  for(unsigned int i=0; i<InputFiles.size(); i++){
    dummy = new TFile(InputFiles[i]);
    tr->Add(InputFiles[i]);
    str->Add(InputFiles[i]);
    events[i+1] = tr->GetEntries(); //cumulative!!
    delete dummy;
  }

  if(tr == NULL){
    cout << "could not find tree ctr in file " << endl;
    for(unsigned int i=0; i<InputFiles.size(); i++){
      cout<<InputFiles[i]<<endl;
    }
    return 3;
  }
  GretinaCalc* gr = new GretinaCalc;
  MiniballCalc* mb = new MiniballCalc;
  ZeroDeg* zd = new ZeroDeg;
  tr->SetBranchAddress("gretinacalc",&gr);
  tr->SetBranchAddress("miniballcalc",&mb);
  tr->SetBranchAddress("zerodeg",&zd);

  if(str == NULL){
    cout << "could not find tree str in file " << endl;
    for(unsigned int i=0; i<InputFiles.size(); i++){
      cout<<InputFiles[i]<<endl;
    }
    return 3;
  }
  GammaSim* gs = new GammaSim;
  str->SetBranchAddress("GammaSim",&gs);

  Double_t nentries = tr->GetEntries();
  Double_t nsimentries = str->GetEntries();

  cout << "creating outputfile " << endl;
  TFile* outfile = new TFile(OutputFile,"recreate");
    
  if(outfile->IsZombie()){
    return 4;
  }

  TTree* GRcoin_tree = new TTree("GRcoin_tree","GRcoin_tree");
  TTree* MBcoin_tree = new TTree("MBcoin_tree","MBcoin_tree");
  TTree* Total_coin_tree = new TTree("Total_coin_tree","Total_coin_tree");

  Int_t GRgc_hit;
  Float_t GRgc_E[84];		//[gc_hit]
  Int_t GRgc_matrix;
  Float_t GRgc1_E[7056];	// 84*84=7056
  Float_t GRgc2_E[7056];

  Int_t MBgc_hit;
  Float_t MBgc_E[84];		//[gc_hit]
  Int_t MBgc_matrix;
  Float_t MBgc1_E[7056];	// 84*84=7056
  Float_t MBgc2_E[7056];
    
  Int_t Totalgc_hit;
  Float_t Totalgc_E[100];		//[gc_hit]
  Int_t Totalgc_matrix;
  Float_t Totalgc1_E[10000];	// 84*84=7056
  Float_t Totalgc2_E[10000];

 
  GRcoin_tree->Branch("GRgc_matrix",&GRgc_matrix,"GRgc_matrix/I");
  GRcoin_tree->Branch("GRgc1_E",GRgc1_E,"GRgc1_E[GRgc_matrix]/F");
  GRcoin_tree->Branch("GRgc2_E",GRgc2_E,"GRgc2_E[GRgc_matrix]/F");

  MBcoin_tree->Branch("MBgc_matrix",&MBgc_matrix,"MBgc_matrix/I");
  MBcoin_tree->Branch("MBgc1_E",MBgc1_E,"MBgc1_E[MBgc_matrix]/F");
  MBcoin_tree->Branch("MBgc2_E",MBgc2_E,"MBgc2_E[MBgc_matrix]/F");

  Total_coin_tree->Branch("Totalgc_matrix",&Totalgc_matrix,"Totalgc_matrix/I");
  Total_coin_tree->Branch("Totalgc1_E",Totalgc1_E,"Totalgc1_E[Totalgc_matrix]/F");
  Total_coin_tree->Branch("Totalgc2_E",Totalgc2_E,"Totalgc2_E[Totalgc_matrix]/F");
  
  for(int i=0; i<nentries; i++){
    
    tr->GetEvent(i);
    GRgc_hit = gr->GetMultAB();
    MBgc_hit = mb->GetMultAB();
    Totalgc_hit = GRgc_hit + MBgc_hit;

    if(GRgc_hit >= 1){
      
      for(int j=0 ; j < GRgc_hit ; j++)
	GRgc_E[j] = gr->GetHitAB(j)->GetDCEnergy();
      
      GRgc_matrix = GRgc_hit*GRgc_hit;
      for(int j=0; j<GRgc_hit; j++){
	for(int k=0; k<GRgc_hit; k++){
	  GRgc1_E[j*GRgc_hit+k]=GRgc_E[j];
	  GRgc2_E[j*GRgc_hit+k]=GRgc_E[k];
	}
      }
      GRcoin_tree->Fill();   
    }
    
    
    if(MBgc_hit >= 1){
      
      for(int j=0 ; j < MBgc_hit ; j++)
	MBgc_E[j] = mb->GetHitAB(j)->GetDCEnergy();
      
      MBgc_matrix = MBgc_hit*MBgc_hit;
      for(int j=0; j<MBgc_hit; j++){
	for(int k=0; k<MBgc_hit; k++){
	  MBgc1_E[j*MBgc_hit+k]=MBgc_E[j];
	  MBgc2_E[j*MBgc_hit+k]=MBgc_E[k];
	}
      }
      MBcoin_tree->Fill();
    }
    
    
    if(Totalgc_hit >= 1){
      
      for(int j=0 ; j < GRgc_hit ; j++)
	{Totalgc_E[j] = gr->GetHitAB(j)->GetDCEnergy();
	  cout << "GR : " << Totalgc_E[j] << endl;}
      
      for(int j=GRgc_hit ; j<Totalgc_hit ; j++)
	{Totalgc_E[j] = mb->GetHitAB(j-GRgc_hit)->GetDCEnergy();
	  cout << "MB : " << Totalgc_E[j] << endl;}
      
      Totalgc_matrix = Totalgc_hit*Totalgc_hit;
      
      for(int j=0; j<Totalgc_hit; j++){
	for(int k=0; k<Totalgc_hit; k++){
	  Totalgc1_E[j*Totalgc_hit+k]=Totalgc_E[j]; 
	  Totalgc2_E[j*Totalgc_hit+k]=Totalgc_E[k];
	  
	}
      }
      
      Total_coin_tree->Fill();
    }
        
  }
  
  GRcoin_tree->Write();
  MBcoin_tree->Write();
  Total_coin_tree->Write();
  outfile->Close();
}
