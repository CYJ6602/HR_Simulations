Double_t parabola(Double_t *x, Double_t *p){
  return p[0]*x[0]*x[0] + p[1]*x[0] + p[2];
}
Double_t inverted(Double_t *x, Double_t *p){
  return ( -p[1] - sqrt(p[1]*p[1] - 4*p[0]*(p[2]-x[0])) ) / (2*p[0]);
}
void beta(){
  TFile *f = new TFile("mo83_minos.root");
  TTree* tr = (TTree*)f->Get("caltr");

  tr->Draw("minos.fbetare:minos.fpos.fZ>>h(150,-170,-20,200,0.4,0.55)","","colz");
  TH2F* h = (TH2F*)gROOT->FindObject("h");
  TProfile* p = (TProfile*)h->ProfileX("hp");
  p->Draw("same");
  //h->ProfileY()->Draw();
  TF1* fu = new TF1("fu",inverted,-200,-40,3);
  fu->SetParameters(-3000,2500,-500);
  p->Fit("fu");
  fu->Draw("same");
}
void testbeta(){
  TFile *f = new TFile("mo83_minos.root");
  TTree* tr = (TTree*)f->Get("caltr");

  tr->Draw("minos.fbetare:minos.fpos.fZ>>h(150,-170,-20,200,0.4,0.55)","","colz");
  TEnv* set = new TEnv("mo83_minos.set");
  double fMINOSBetaCoeff[3];
  TF1* fMINOSZett = new TF1("MINOSZett",inverted, -200,  -50, 3);
  for(int i=0;i<3;i++){
    fMINOSBetaCoeff[i] = set->GetValue(Form("MINOS.Beta.Coefficient.%d",i),0.0);
    cout << fMINOSBetaCoeff[i] << endl;
    fMINOSZett->SetParameter(i,fMINOSBetaCoeff[i]);
  }

  fMINOSZett->Draw("same");
}
