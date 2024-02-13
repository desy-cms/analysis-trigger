#include "Fit/Fitter.h"
#include "Fit/BinData.h"
#include "Fit/Chi2FCN.h"
#include "TH1.h"
#include "TList.h"
#include "TMath.h"
#include "Math/WrappedMultiTF1.h"
#include "HFitInterface.h"
#include "TCanvas.h"
#include "TStyle.h"

Double_t fitting_function_passed       (Double_t *val, Double_t *par);
Double_t fitting_function_failed       (Double_t *val, Double_t *par);
TH1D* ProjectHistogram(TH2D* h, double ptmin, double ptmax, char name[]);

// Passed function parameters 
int iparPassed[7] = { 0,
                      1,
                      2,
                      3,
                      4,
                      5,
                      6  
}; 
// Failed function parameters 
int iparFailed[7] = { 0,
                      1,
                      2,
                      3,
                      4,
                      5,
                      6  
};
 
// Create the GlobalCHi2 structure
struct GlobalChi2 {
   GlobalChi2(  ROOT::Math::IMultiGenFunction & f1,
                ROOT::Math::IMultiGenFunction & f2) :
      fChi2_1(&f1), fChi2_2(&f2) {}
 
   double operator() (const double *par) const {
      double p1[7];
      for (int i = 0; i < 7; ++i) p1[i] = par[iparPassed[i] ];
 
      double p2[7];
      for (int i = 0; i < 7; ++i) p2[i] = par[iparFailed[i] ];
 
      return (*fChi2_1)(p1) + (*fChi2_2)(p2);
   }
 
   const  ROOT::Math::IMultiGenFunction * fChi2_1;
   const  ROOT::Math::IMultiGenFunction * fChi2_2;
};
 


void MKTE_MultiFit_MC_JPsiCurve_cuadraticBkg() {


   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
   
   Double_t Luminosity_Total =0.002493*1000; //mult by 1000 to take from /fb to /pb -> lumi of control trigger
   //Double_t Luminosity_Total = 36.67*1000; //mult by 1000 to take from /fb to /pb -> lumi of physics trigger

   TFile * f1 = new TFile("mkte_less-stats_50perc/my_MC_SL_MKTE_QCD_Pt-50To80.root");
   TFile * f2 = new TFile("mkte_less-stats_50perc/my_MC_SL_MKTE_QCD_Pt-80To120.root");
   TFile * f3 = new TFile("mkte_less-stats_50perc/my_MC_SL_MKTE_QCD_Pt-120To170.root");
   TFile * f4 = new TFile("mkte_less-stats_50perc/my_MC_SL_MKTE_QCD_Pt-170To300.root");
   TFile * f5 = new TFile("mkte_less-stats_50perc/my_MC_SL_MKTE_QCD_Pt-300To470.root");
   TFile * f6 = new TFile("mkte_less-stats_50perc/my_MC_SL_MKTE_QCD_Pt-470To600.root");
   TFile * f7 = new TFile("mkte_less-stats_50perc/my_MC_SL_MKTE_QCD_Pt-600To800.root");
   TFile * f8 = new TFile("mkte_less-stats_50perc/my_MC_SL_MKTE_QCD_Pt-800to1000.root");
   TFile * f9 = new TFile("mkte_less-stats_50perc/my_MC_SL_MKTE_QCD_Pt-1000toInf.root");
   
   //Individual Histograms - DiMuon mass
   TH2D * DiMuonMass_passed_2D_1 = (TH2D*) f1 -> Get("DiMuonMass of passing muons 2D");
   TH2D * DiMuonMass_failed_2D_1 = (TH2D*) f1 -> Get("DiMuonMass of failing muons 2D");
   
   TH2D * DiMuonMass_passed_2D_2 = (TH2D*) f2 -> Get("DiMuonMass of passing muons 2D");
   TH2D * DiMuonMass_failed_2D_2 = (TH2D*) f2 -> Get("DiMuonMass of failing muons 2D");
   
   TH2D * DiMuonMass_passed_2D_3 = (TH2D*) f3 -> Get("DiMuonMass of passing muons 2D");
   TH2D * DiMuonMass_failed_2D_3 = (TH2D*) f3 -> Get("DiMuonMass of failing muons 2D");
   
   TH2D * DiMuonMass_passed_2D_4 = (TH2D*) f4 -> Get("DiMuonMass of passing muons 2D");
   TH2D * DiMuonMass_failed_2D_4 = (TH2D*) f4 -> Get("DiMuonMass of failing muons 2D");
   
   TH2D * DiMuonMass_passed_2D_5 = (TH2D*) f5 -> Get("DiMuonMass of passing muons 2D");
   TH2D * DiMuonMass_failed_2D_5 = (TH2D*) f5 -> Get("DiMuonMass of failing muons 2D");
   
   TH2D * DiMuonMass_passed_2D_6 = (TH2D*) f6 -> Get("DiMuonMass of passing muons 2D");
   TH2D * DiMuonMass_failed_2D_6 = (TH2D*) f6 -> Get("DiMuonMass of failing muons 2D");
   
   TH2D * DiMuonMass_passed_2D_7 = (TH2D*) f7 -> Get("DiMuonMass of passing muons 2D");
   TH2D * DiMuonMass_failed_2D_7 = (TH2D*) f7 -> Get("DiMuonMass of failing muons 2D");
   
   TH2D * DiMuonMass_passed_2D_8 = (TH2D*) f8 -> Get("DiMuonMass of passing muons 2D");
   TH2D * DiMuonMass_failed_2D_8 = (TH2D*) f8 -> Get("DiMuonMass of failing muons 2D");
   
   TH2D * DiMuonMass_passed_2D_9 = (TH2D*) f9 -> Get("DiMuonMass of passing muons 2D");
   TH2D * DiMuonMass_failed_2D_9 = (TH2D*) f9 -> Get("DiMuonMass of failing muons 2D");
   
   //Individual Histograms - pT
   TH1D * pT_passed_1 = (TH1D*) f1 -> Get("Matched_Probes_Pt");
   TH1D * pT_failed_1 = (TH1D*) f1 -> Get("Failed_Probes_Pt");
   TH1D * pT_passed_2 = (TH1D*) f2 -> Get("Matched_Probes_Pt");
   TH1D * pT_failed_2 = (TH1D*) f2 -> Get("Failed_Probes_Pt");
   TH1D * pT_passed_3 = (TH1D*) f3 -> Get("Matched_Probes_Pt");
   TH1D * pT_failed_3 = (TH1D*) f3 -> Get("Failed_Probes_Pt");
   TH1D * pT_passed_4 = (TH1D*) f4 -> Get("Matched_Probes_Pt");
   TH1D * pT_failed_4 = (TH1D*) f4 -> Get("Failed_Probes_Pt");
   TH1D * pT_passed_5 = (TH1D*) f5 -> Get("Matched_Probes_Pt");
   TH1D * pT_failed_5 = (TH1D*) f5 -> Get("Failed_Probes_Pt");
   TH1D * pT_passed_6 = (TH1D*) f6 -> Get("Matched_Probes_Pt");
   TH1D * pT_failed_6 = (TH1D*) f6 -> Get("Failed_Probes_Pt");
   TH1D * pT_passed_7 = (TH1D*) f7 -> Get("Matched_Probes_Pt");
   TH1D * pT_failed_7 = (TH1D*) f7 -> Get("Failed_Probes_Pt");
   TH1D * pT_passed_8 = (TH1D*) f8 -> Get("Matched_Probes_Pt");
   TH1D * pT_failed_8 = (TH1D*) f8 -> Get("Failed_Probes_Pt");
   TH1D * pT_passed_9 = (TH1D*) f9 -> Get("Matched_Probes_Pt");
   TH1D * pT_failed_9 = (TH1D*) f9 -> Get("Failed_Probes_Pt");
   
   
   //Lower and upper limits of pTbins
   Double_t Limits[5] = {11.5, 12.5, 13.5, 18.5, 30};
   int pTbin = 4;//select the pT bin [1,2,3,4]
   bool save_in_rootfile = false; //save histograms in rootfiles
   
   //Projecting the 2D histograms
   TH1D* DiMuonMass_passed_1 = ProjectHistogram(DiMuonMass_passed_2D_1, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_passed_pTbin_%d_1", pTbin));   
   TH1D* DiMuonMass_failed_1 = ProjectHistogram(DiMuonMass_failed_2D_1, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_failed_pTbin_%d_1", pTbin));
   
   TH1D* DiMuonMass_passed_2 = ProjectHistogram(DiMuonMass_passed_2D_2, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_passed_pTbin_%d_2", pTbin));   
   TH1D* DiMuonMass_failed_2 = ProjectHistogram(DiMuonMass_failed_2D_2, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_failed_pTbin_%d_2", pTbin));
   
   TH1D* DiMuonMass_passed_3 = ProjectHistogram(DiMuonMass_passed_2D_3, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_passed_pTbin_%d_3", pTbin));   
   TH1D* DiMuonMass_failed_3 = ProjectHistogram(DiMuonMass_failed_2D_3, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_failed_pTbin_%d_3", pTbin));
 
   TH1D* DiMuonMass_passed_4 = ProjectHistogram(DiMuonMass_passed_2D_4, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_passed_pTbin_%d_4", pTbin));   
   TH1D* DiMuonMass_failed_4 = ProjectHistogram(DiMuonMass_failed_2D_4, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_failed_pTbin_%d_4", pTbin));
  
   TH1D* DiMuonMass_passed_5 = ProjectHistogram(DiMuonMass_passed_2D_5, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_passed_pTbin_%d_5", pTbin));   
   TH1D* DiMuonMass_failed_5 = ProjectHistogram(DiMuonMass_failed_2D_5, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_failed_pTbin_%d_5", pTbin));
   
   TH1D* DiMuonMass_passed_6 = ProjectHistogram(DiMuonMass_passed_2D_6, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_passed_pTbin_%d_6", pTbin));   
   TH1D* DiMuonMass_failed_6 = ProjectHistogram(DiMuonMass_failed_2D_6, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_failed_pTbin_%d_6", pTbin));
   
   TH1D* DiMuonMass_passed_7 = ProjectHistogram(DiMuonMass_passed_2D_7, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_passed_pTbin_%d_7", pTbin));   
   TH1D* DiMuonMass_failed_7 = ProjectHistogram(DiMuonMass_failed_2D_7, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_failed_pTbin_%d_7", pTbin));
   
   TH1D* DiMuonMass_passed_8 = ProjectHistogram(DiMuonMass_passed_2D_8, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_passed_pTbin_%d_8", pTbin));   
   TH1D* DiMuonMass_failed_8 = ProjectHistogram(DiMuonMass_failed_2D_8, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_failed_pTbin_%d_8", pTbin));
   
   TH1D* DiMuonMass_passed_9 = ProjectHistogram(DiMuonMass_passed_2D_9, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_passed_pTbin_%d_9", pTbin));   
   TH1D* DiMuonMass_failed_9 = ProjectHistogram(DiMuonMass_failed_2D_9, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_failed_pTbin_%d_9", pTbin));
   
   //get parameters of MC samples (pb)
   //Double_t Cross_section_0= 1362000;
   Double_t Cross_section_1= 376600;
   Double_t Cross_section_2= 88930;
   Double_t Cross_section_3= 21230;
   Double_t Cross_section_4= 7055;
   Double_t Cross_section_5= 619.30;
   Double_t Cross_section_6= 59.24;
   Double_t Cross_section_7= 18.21;
   Double_t Cross_section_8= 3.275;
   Double_t Cross_section_9= 1.078;
   
   TH1F * Workflow1 = (TH1F*) f1 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow2 = (TH1F*) f2 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow3 = (TH1F*) f3 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow4 = (TH1F*) f4 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow5 = (TH1F*) f5 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow6 = (TH1F*) f6 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow7 = (TH1F*) f7 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow8 = (TH1F*) f8 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow9 = (TH1F*) f9 -> Get("workflow;1/Workflow #1");

   Double_t Nevents1 = Workflow1->GetBinContent(2);
   Double_t Nevents2 = Workflow2->GetBinContent(2);
   Double_t Nevents3 = Workflow3->GetBinContent(2);
   Double_t Nevents4 = Workflow4->GetBinContent(2);
   Double_t Nevents5 = Workflow5->GetBinContent(2);
   Double_t Nevents6 = Workflow6->GetBinContent(2);
   Double_t Nevents7 = Workflow7->GetBinContent(2);
   Double_t Nevents8 = Workflow8->GetBinContent(2);
   Double_t Nevents9 = Workflow9->GetBinContent(2);
   
   // calculate Scale Factors for each MC sample
   Double_t ScaleFactor1, ScaleFactor2, ScaleFactor3, ScaleFactor4, ScaleFactor5, ScaleFactor6, ScaleFactor7, ScaleFactor8, ScaleFactor9 ;
   
   //Double_t Luminosity_Total = Nevents1/Cross_section_1 + Nevents2/Cross_section_2 + Nevents3/Cross_section_3 + Nevents4/Cross_section_4 + Nevents5/Cross_section_5 + Nevents6/Cross_section_6 + Nevents7/Cross_section_7 + Nevents8/Cross_section_8 + Nevents9/Cross_section_9; 
   
   cout<<"Luminosity_Total "<<Luminosity_Total;
   
   ScaleFactor1 = Luminosity_Total*Cross_section_1/Nevents1;
   ScaleFactor2 = Luminosity_Total*Cross_section_2/Nevents2;
   ScaleFactor3 = Luminosity_Total*Cross_section_3/Nevents3;
   ScaleFactor4 = Luminosity_Total*Cross_section_4/Nevents4;
   ScaleFactor5 = Luminosity_Total*Cross_section_5/Nevents5;
   ScaleFactor6 = Luminosity_Total*Cross_section_6/Nevents6;
   ScaleFactor7 = Luminosity_Total*Cross_section_7/Nevents7;
   ScaleFactor8 = Luminosity_Total*Cross_section_8/Nevents8;
   ScaleFactor9 = Luminosity_Total*Cross_section_9/Nevents9;
  
   // scale the MC histograms
   DiMuonMass_passed_1 -> Scale(ScaleFactor1);
   DiMuonMass_failed_1 -> Scale(ScaleFactor1);
   
   DiMuonMass_passed_2 -> Scale(ScaleFactor2);
   DiMuonMass_failed_2 -> Scale(ScaleFactor2);
   
   DiMuonMass_passed_3 -> Scale(ScaleFactor3);
   DiMuonMass_failed_3 -> Scale(ScaleFactor3);
   
   DiMuonMass_passed_4 -> Scale(ScaleFactor4);
   DiMuonMass_failed_4 -> Scale(ScaleFactor4);
   
   DiMuonMass_passed_5 -> Scale(ScaleFactor5);
   DiMuonMass_failed_5 -> Scale(ScaleFactor5);
   
   DiMuonMass_passed_6 -> Scale(ScaleFactor6);
   DiMuonMass_failed_6 -> Scale(ScaleFactor6);
   
   DiMuonMass_passed_7 -> Scale(ScaleFactor7);
   DiMuonMass_failed_7 -> Scale(ScaleFactor7);
   
   DiMuonMass_passed_8 -> Scale(ScaleFactor8);
   DiMuonMass_failed_8 -> Scale(ScaleFactor8);
   
   DiMuonMass_passed_9 -> Scale(ScaleFactor9);
   DiMuonMass_failed_9 -> Scale(ScaleFactor9);

   pT_passed_1 -> Scale(ScaleFactor1);
   pT_failed_1 -> Scale(ScaleFactor1);
   pT_passed_2 -> Scale(ScaleFactor2);
   pT_failed_2 -> Scale(ScaleFactor2);
   pT_passed_3 -> Scale(ScaleFactor3);
   pT_failed_3 -> Scale(ScaleFactor3);
   pT_passed_4 -> Scale(ScaleFactor4);
   pT_failed_4 -> Scale(ScaleFactor4);
   pT_passed_5 -> Scale(ScaleFactor5);
   pT_failed_5 -> Scale(ScaleFactor5);
   pT_passed_6 -> Scale(ScaleFactor6);
   pT_failed_6 -> Scale(ScaleFactor6);
   pT_passed_7 -> Scale(ScaleFactor7);
   pT_failed_7 -> Scale(ScaleFactor7);
   pT_passed_8 -> Scale(ScaleFactor8);
   pT_failed_8 -> Scale(ScaleFactor8);
   pT_passed_9 -> Scale(ScaleFactor9);
   pT_failed_9 -> Scale(ScaleFactor9);
   
   
   // adding the MC histograms
   TH1F * DiMuonMass_passed = (TH1F*) DiMuonMass_passed_1->Clone("DiMuonMass_passed");
   TH1F * DiMuonMass_failed = (TH1F*) DiMuonMass_failed_1->Clone("DiMuonMass_failed");
   
   DiMuonMass_passed -> Add(DiMuonMass_passed_2);
   DiMuonMass_passed -> Add(DiMuonMass_passed_3);
   DiMuonMass_passed -> Add(DiMuonMass_passed_4);
   DiMuonMass_passed -> Add(DiMuonMass_passed_5);
   DiMuonMass_passed -> Add(DiMuonMass_passed_6);
   DiMuonMass_passed -> Add(DiMuonMass_passed_7);
   DiMuonMass_passed -> Add(DiMuonMass_passed_8);
   DiMuonMass_passed -> Add(DiMuonMass_passed_9);
   
   DiMuonMass_failed -> Add(DiMuonMass_failed_2);
   DiMuonMass_failed -> Add(DiMuonMass_failed_3);
   DiMuonMass_failed -> Add(DiMuonMass_failed_4);
   DiMuonMass_failed -> Add(DiMuonMass_failed_5);
   DiMuonMass_failed -> Add(DiMuonMass_failed_6);
   DiMuonMass_failed -> Add(DiMuonMass_failed_7);
   DiMuonMass_failed -> Add(DiMuonMass_failed_8);
   DiMuonMass_failed -> Add(DiMuonMass_failed_9);
   
   TH1D * pT_passed = (TH1D*) pT_passed_1->Clone("pT_passed");
   TH1D * pT_failed = (TH1D*) pT_failed_1->Clone("pT_failed");
   pT_passed -> Add(pT_passed_2);
   pT_passed -> Add(pT_passed_3);
   pT_passed -> Add(pT_passed_4);
   pT_passed -> Add(pT_passed_5);
   pT_passed -> Add(pT_passed_6);
   pT_passed -> Add(pT_passed_7);
   pT_passed -> Add(pT_passed_8);
   pT_passed -> Add(pT_passed_9);
   
   pT_failed -> Add(pT_failed_2);
   pT_failed -> Add(pT_failed_3);
   pT_failed -> Add(pT_failed_4);
   pT_failed -> Add(pT_failed_5);
   pT_failed -> Add(pT_failed_6);
   pT_failed -> Add(pT_failed_7);
   pT_failed -> Add(pT_failed_8);
   pT_failed -> Add(pT_failed_9);
   
//-----------
   
   int bineo = 4; // in 10^-2 GeV
   
   DiMuonMass_passed -> Rebin(bineo);
   DiMuonMass_failed -> Rebin(bineo);
   
   double min = 2.92, max = 3.28;
   //double min = 2.92, max = 3.28;
   //double min = 2.92, max = 3.32;

   // Declaring fitting functions and set parameters names
   TF1* fittingfunction_passed = new TF1 ("fittingfunction_passed", fitting_function_passed, min, max, 7);
   fittingfunction_passed -> SetParNames ("A","m_{0}","#sigma","k_{2}","k_{1}","k_{0}","#epsilon");
   TF1* fittingfunction_failed = new TF1 ("fittingfunction_failed", fitting_function_failed, min, max, 7);
   fittingfunction_failed -> SetParNames ("A","m_{0}","#sigma","k_{2}","k_{1}","k_{0}","#epsilon");
 

   // perform now global fit

   //wrap a function in a IParamMultiFunction interface
   ROOT::Math::WrappedMultiTF1 wfittingfunction_passed(*fittingfunction_passed,1);
   ROOT::Math::WrappedMultiTF1 wfittingfunction_failed(*fittingfunction_failed,1);
   
   //fit properties

   ROOT::Fit::DataOptions opt;

   ROOT::Fit::DataRange rangePassed;
   rangePassed.SetRange(min,max);
   ROOT::Fit::BinData dataPassed(opt,rangePassed);
   ROOT::Fit::FillData(dataPassed, DiMuonMass_passed);

   ROOT::Fit::DataRange rangeFailed;
   rangeFailed.SetRange(min,max);
   //rangeFailed.SetRange(3.097-0.12,3.097+0.12);
   ROOT::Fit::BinData dataFailed(opt,rangeFailed);
   ROOT::Fit::FillData(dataFailed, DiMuonMass_failed);

   //individual chi2 functions
   ROOT::Fit::Chi2Function chi2_Passed(dataPassed, wfittingfunction_passed);
   ROOT::Fit::Chi2Function chi2_Failed(dataFailed, wfittingfunction_failed);

   //Pass the individual chi2 to globalChi2
   GlobalChi2 globalChi2(chi2_Passed, chi2_Failed);

   //declare the fitter
   ROOT::Fit::Fitter fitter;
 
   const int Npar = 7;
   //double par0[Npar] = { 6, 3.0969, 0.0296, -3.16, 19,  -28.56, 0.9};  //use for bin2 bineo 0p2
//   double par0[Npar] = { 2, 3.0969, 0.0296, -3.16, 10,  -20, 0.9};  //use for bin2 bineo 0p4
//   double par0[Npar] = { 2, 3.0969, 0.0296, -3.16, 10,  -20, 0.4};  //use for bin1 bineo 0p4
//   double par0[Npar] = { 20, 3.0969, 0.031, -5, 1,  -5, 0.91};  //use for bin3 bineo 0p4
   double par0[Npar] = { 5, 3.0969, 0.031, -5, 33,  -50, 0.91};  //use for bin4 bineo 0p4
   
   // fix or set range on the parameters
   fitter.Config().SetParamsSettings(7,par0);
   fitter.Config().ParSettings(1).Fix();
   //fitter.Config().ParSettings(3).Fix();
   //fitter.Config().ParSettings(5).SetLimits(0,1000); 
   //fitter.Config().ParSettings(3).SetLimits(-100,0); 
   fitter.Config().MinimizerOptions().SetPrintLevel(0);
   fitter.Config().SetMinimizer("Minuit2","Migrad");
 
   //Perform the fit
   fitter.FitFCN(7,globalChi2,0,dataPassed.Size()+dataFailed.Size(),true);
   ROOT::Fit::FitResult result = fitter.Result();
   result.Print(std::cout);
 
   TCanvas * C1 = new TCanvas("C1","Canvas",1500,750);
   gStyle->SetOptFit(1111);
   
   //pT_passed -> Draw();
   //pT_failed -> Draw();
   
   
   C1 -> Divide(2,1);
   C1 -> cd(1);
   fittingfunction_passed -> SetFitResult( result, iparPassed);
   fittingfunction_passed -> SetRange(rangePassed().first, rangePassed().second);
   fittingfunction_passed -> SetLineColor(kBlue);
   DiMuonMass_passed -> GetListOfFunctions() -> Add(fittingfunction_passed);
   DiMuonMass_passed -> SetMarkerStyle(20);
   //DiMuonMass_passed -> SetTitle(Form("Passing Probes %.1f<p_{T}^{probes}<%.1f GeV", Limits[pTbin-1], Limits[pTbin]));
   DiMuonMass_passed -> SetTitle("");
   DiMuonMass_passed -> GetXaxis() -> SetTitle("m_{#mu#mu}");
   DiMuonMass_passed -> GetXaxis() -> SetRangeUser(2.85,3.35);
   DiMuonMass_passed -> GetYaxis() -> SetRangeUser(0,fittingfunction_passed->GetMaximum()+0.7);
   DiMuonMass_passed -> GetYaxis() -> SetTitle(Form("Entries/(0.0%d GeV)", bineo));
   DiMuonMass_passed -> Draw();
   
   TLatex latex;
   latex.SetTextFont(43);
   latex.SetTextSize(20);
   latex.SetTextAlign(11);
   latex.DrawLatexNDC(C1 -> cd(1) ->GetLeftMargin(), 1.02-C1 -> cd(1) ->GetTopMargin(),
                (std::string("CMS Simulation      Work in progress")).c_str());
                
   
   auto legend_passed = new TLegend(0.11,0.7,0.45,0.85);
   legend_passed->SetBorderSize(0);
   legend_passed->SetHeader(Form("%.1f < p_{T}^{probes} < %.1f GeV", Limits[pTbin-1], Limits[pTbin]),"C"); // option "C" allows to center the header
   legend_passed->AddEntry(DiMuonMass_passed,"QCD #mu-enriched","lep");
   TLegendEntry* l_passed_funct = legend_passed->AddEntry(fittingfunction_passed,"passing probe","l");
   l_passed_funct->SetTextColor(kBlue);
   legend_passed->Draw();
 
   C1 -> cd(2);
                
   fittingfunction_failed -> SetFitResult( result, iparFailed);
   fittingfunction_failed -> SetRange(rangeFailed().first, rangeFailed().second);
   fittingfunction_failed -> SetLineColor(kRed);
   DiMuonMass_failed -> GetListOfFunctions() -> Add(fittingfunction_failed);
   DiMuonMass_failed -> SetMarkerStyle(20);
   DiMuonMass_failed -> SetTitle("");
   //DiMuonMass_failed -> SetTitle(Form("Failing Probes %.1f<p_{T}^{probes}<%.1f GeV", Limits[pTbin-1], Limits[pTbin]));
   DiMuonMass_failed -> GetXaxis() -> SetTitle("m_{#mu#mu}");
   DiMuonMass_failed -> GetXaxis() -> SetRangeUser(2.85,3.35);
   DiMuonMass_failed -> GetYaxis() -> SetRangeUser(0,fittingfunction_failed->GetMaximum()+0.2);
   DiMuonMass_failed -> GetYaxis() -> SetTitle(Form("Entries/(0.0%d GeV)",bineo));
   DiMuonMass_failed -> Draw();
   
   auto legend_failed = new TLegend(0.11,0.7,0.45,0.85);
   legend_failed->SetBorderSize(0);
   legend_failed->SetHeader(Form("%.1f < p_{T}^{probes} < %.1f GeV", Limits[pTbin-1], Limits[pTbin]),"C"); // option "C" allows to center the header
   legend_failed->AddEntry(DiMuonMass_failed,"QCD #mu-enriched","lep");
   TLegendEntry* l_failed_funct = legend_failed->AddEntry(fittingfunction_failed,"failing probe","l");
   l_failed_funct->SetTextColor(kRed);
   legend_failed->Draw();
   
   latex.DrawLatexNDC(C1 -> cd(2) ->GetLeftMargin(), 1.02-C1 -> cd(2) ->GetTopMargin(),
                (std::string("CMS Simulation      Work in progress")).c_str());
   
   
   C1 -> SaveAs(Form("plots_MC_cuadraticBkg_less-stats_50p/JPsi_pTbin%d_bineo0p0%dGeV.png",pTbin,bineo));
   C1 -> SaveAs(Form("plots_MC_cuadraticBkg_less-stats_50p/JPsi_pTbin%d_bineo0p0%dGeV.pdf",pTbin,bineo));
   C1 -> SaveAs(Form("plots_MC_cuadraticBkg_less-stats_50p/JPsi_pTbin%d_bineo0p0%dGeV.root",pTbin,bineo));
   
   
   
   
}


// Fitting function definition for Passed sample
Double_t fitting_function_passed (Double_t *val, Double_t *par)
{
    Double_t exponential = exp(-1*((val[0]-par[1])*(val[0]-par[1])/(2*par[2]*par[2])));
    Double_t f_passed = (par[0] * exponential + par[3]*val[0]*val[0] + par[4]*val[0] + par[5])*par[6];
    return f_passed;
}

// Fitting function definition for Failed sample
Double_t fitting_function_failed (Double_t *val, Double_t *par)
{
    Double_t exponential = exp(-1*((val[0]-par[1])*(val[0]-par[1])/(2*par[2]*par[2])));
    Double_t f_failed = (par[0] * exponential + par[3]*val[0]*val[0] + par[4]*val[0] + par[5])*(1-par[6]);
    return f_failed;
}



TH1D* ProjectHistogram(TH2D* h, double ptmin, double ptmax, char name[])
{
   //declare histograms and variables
   TH1D *hprojected;
   double half_bin_width = 0.5 * (h -> GetYaxis() -> GetBinWidth(1));
   double Lowedgeup, Lowedgedown;
   
   if (ptmax == -1)
   {
      int LowerBin = 1;
      int UpperBin = h -> GetNbinsY();

      hprojected = h -> ProjectionX(name, LowerBin, UpperBin, "e");

   }

   else
   {
      int LowerBin = int(h -> GetYaxis() -> FindBin(ptmin + half_bin_width));
      int UpperBin = int(h -> GetYaxis() -> FindBin(ptmax - half_bin_width));
           
      Lowedgeup = h -> GetYaxis() -> GetBinLowEdge(UpperBin);
      Lowedgedown = h -> GetYaxis() -> GetBinLowEdge(LowerBin);
            
      hprojected = h -> ProjectionX(name, LowerBin, UpperBin, "e");
   }
   
   return hprojected;

}
