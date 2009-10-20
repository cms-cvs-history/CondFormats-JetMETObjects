#include "TStopwatch.h"
void TestProperties()
{
  TStopwatch t;
  t.Start();
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable(); 
  using namespace reco;
  using namespace edm; 
  using namespace std;
  main();
  t.Stop();
  cout << Form("Total time: %1.3g sec (real), %1.3g sec (cpu)", t.RealTime(), t.CpuTime()) << endl;
}  
////////////////////////////////////////////////
void main()
{
  SmearedJet *tmp = new SmearedJet();
  tmp->setParameters("../data/ResponseParameters.txt"     ,SmearedJet::pResp); 
  tmp->setParameters("../data/PtResolutionParameters.txt" ,SmearedJet::pPtResol);
  tmp->setParameters("../data/EtaResolutionParameters.txt",SmearedJet::pEtaResol); 
  tmp->setParameters("../data/PhiResolutionParameters.txt",SmearedJet::pPhiResol);
  tmp->setParameters("../data/RecoEffParameters.txt"      ,SmearedJet::pRecoEff);
  TH1F *hPt  = new TH1F("hPt" ,"hPt" ,500,0,500);
  TH1F *hEta = new TH1F("hEta","hEta",500,-5,5);
  TH1F *hPhi = new TH1F("hPhi","hPhi",500,-4,4);
  PtEtaPhiELorentzVectorD p4,newP4;
  p4.SetE(100);
  p4.SetEta(2);
  p4.SetPhi(1);
  p4.SetPt(100);
  double r = pow(3000./5.,0.02);
  double vx[1000],vrsp[1000],vrsl[1000],veff[1000];
  for(int i=0;i<50;i++)
    {
      vx[i]   = 5*pow(r,i);
      vrsp[i] = tmp->getValue(vx[i],4,SmearedJet::pResp);
      vrsl[i] = tmp->getValue(vx[i],4,SmearedJet::pPtResol); 
      veff[i] = tmp->getValue(vx[i],0,SmearedJet::pRecoEff);
    }
  TGraph *gRsp = new TGraph(50,vx,vrsp);
  TGraph *gRsl = new TGraph(50,vx,vrsl);
  TGraph *gEff = new TGraph(50,vx,veff);
  //////////////////////////
  TCanvas *cRsp = new TCanvas("cRsp","cRsp");
  gPad->SetLogx();
  gRsp->SetMarkerStyle(20);
  gRsp->Draw("AP");
  //////////////////////////
  TCanvas *cRsl = new TCanvas("cRsl","cRsl");
  gPad->SetLogx();
  gRsl->SetMarkerStyle(20);
  gRsl->Draw("AP");
  //////////////////////////
  TCanvas *cRsl = new TCanvas("cEff","cEff");
  gPad->SetLogx();
  gEff->SetMarkerStyle(20);
  gEff->Draw("AP");
  /*  
  for(int i=0;i<1000000;i++)
    {
      newP4 = tmp->getSmeared(p4,SmearedJet::vRawPt);
      hPt ->Fill(newP4.Pt());
      hEta->Fill(newP4.Eta());
      hPhi->Fill(newP4.Phi());
    }
  //////////////////////////
  TCanvas *cPt = new TCanvas("cPt","cPt");
  hPt->Draw();
  //////////////////////////
  TCanvas *cEta = new TCanvas("cEta","cEta");
  hEta->Draw();
  //////////////////////////
  TCanvas *cPhi = new TCanvas("cPhi","cPhi");
  hPhi->Draw();
  */
}
