#include "Fit/Fitter.h"
#include "Fit/BinData.h"
#include "Fit/Chi2FCN.h"
#include "TH1.h"
#include "TList.h"
#include "Math/WrappedMultiTF1.h"
#include "HFitInterface.h"
#include "TCanvas.h"
#include "TStyle.h"

Double_t fitting_function_passed       (Double_t *val, Double_t *par);
Double_t fitting_function_failed       (Double_t *val, Double_t *par);

// Passed function parameters 
int iparPassed[5] = { 0,
                      1,
                      2,
                      3,
                      4  
}; 
// Failed function parameters 
int iparFailed[5] = { 0,
                      1,
                      2,
                      3,
                      4  
};
 
// Create the GlobalCHi2 structure
struct GlobalChi2 {
   GlobalChi2(  ROOT::Math::IMultiGenFunction & f1,
                ROOT::Math::IMultiGenFunction & f2) :
      fChi2_1(&f1), fChi2_2(&f2) {}
 
   double operator() (const double *par) const {
      double p1[5];
      for (int i = 0; i < 5; ++i) p1[i] = par[iparPassed[i] ];
 
      double p2[5];
      for (int i = 0; i < 5; ++i) p2[i] = par[iparFailed[i] ];
 
      return (*fChi2_1)(p1) + (*fChi2_2)(p2);
   }
 
   const  ROOT::Math::IMultiGenFunction * fChi2_1;
   const  ROOT::Math::IMultiGenFunction * fChi2_2;
};
 


void MultiFit_JPsiCurve() {


   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms

   TFile * f = new TFile("myCDEF.root");

   // Histograms
   TH1F * DiMuonMass_matched = (TH1F*) f -> Get("DiMuonMass of passing muons pTBin4");
   TH1F * DiMuonMass_failedmatched = (TH1F*) f -> Get("DiMuonMass of failing muons pTBin4");
   DiMuonMass_matched -> Rebin(4);
   DiMuonMass_failedmatched -> Rebin(4);

   // Declaring fitting functions and set parameters names
   TF1* fittingfunction_passed = new TF1 ("fittingfunction_passed", fitting_function_passed, 3, 3.2, 5);
   fittingfunction_passed -> SetParNames ("A","m_{0}","#sigma","k","#epsilon");
   TF1* fittingfunction_failed = new TF1 ("fittingfunction_failed", fitting_function_failed, 3, 3.2, 5);
   fittingfunction_failed -> SetParNames ("A","m_{0}","#sigma","k","#epsilon");
 

   // perform now global fit

   //wrap a function in a IParamMultiFunction interface
   ROOT::Math::WrappedMultiTF1 wfittingfunction_passed(*fittingfunction_passed,1);
   ROOT::Math::WrappedMultiTF1 wfittingfunction_failed(*fittingfunction_failed,1);
   
   //fit properties

   ROOT::Fit::DataOptions opt;

   ROOT::Fit::DataRange rangePassed;
   rangePassed.SetRange(3.,3.2);
   ROOT::Fit::BinData dataPassed(opt,rangePassed);
   ROOT::Fit::FillData(dataPassed, DiMuonMass_matched);

   ROOT::Fit::DataRange rangeFailed;
   rangeFailed.SetRange(3.,3.2);
   ROOT::Fit::BinData dataFailed(opt,rangeFailed);
   ROOT::Fit::FillData(dataFailed, DiMuonMass_failedmatched);

   //individual chi2 functions
   ROOT::Fit::Chi2Function chi2_Passed(dataPassed, wfittingfunction_passed);
   ROOT::Fit::Chi2Function chi2_Failed(dataFailed, wfittingfunction_failed);

   //Pass the individual chi2 to globalChi2
   GlobalChi2 globalChi2(chi2_Passed, chi2_Failed);

   //declare the fitter
   ROOT::Fit::Fitter fitter;
 
   const int Npar = 5;
   double par0[Npar] = { 215.1, 3.097, 0.0297, 78.67, 0.7878}; 
 
   // fix or set range on the parameters
   fitter.Config().SetParamsSettings(5,par0);
   fitter.Config().MinimizerOptions().SetPrintLevel(0);
   fitter.Config().SetMinimizer("Minuit2","Migrad");
 
   //Perform the fit
   fitter.FitFCN(5,globalChi2,0,dataPassed.Size()+dataFailed.Size(),true);
   ROOT::Fit::FitResult result = fitter.Result();
   result.Print(std::cout);
 
   TCanvas * C1 = new TCanvas("C","Canvas",1500,750);
   C1 -> Divide(2,1);
   C1 -> cd(1);
   gStyle->SetOptFit(1111);
 
   fittingfunction_passed -> SetFitResult( result, iparPassed);
   fittingfunction_passed -> SetRange(rangePassed().first, rangePassed().second);
   fittingfunction_passed -> SetLineColor(kBlue);
   DiMuonMass_matched -> GetListOfFunctions() -> Add(fittingfunction_passed);
   DiMuonMass_matched -> SetTitle("Passing Probes 18.5<p_{T}^{probes}<30 GeV");
   DiMuonMass_matched -> GetXaxis() -> SetTitle("m_{#mu#mu}");
   DiMuonMass_matched -> GetYaxis() -> SetTitle("Entries/(0.04 GeV)");
   DiMuonMass_matched -> Draw();
 
   C1 -> cd(2);
   fittingfunction_failed -> SetFitResult( result, iparFailed);
   fittingfunction_failed -> SetRange(rangeFailed().first, rangeFailed().second);
   fittingfunction_failed -> SetLineColor(kRed);
   DiMuonMass_failedmatched -> GetListOfFunctions() -> Add(fittingfunction_failed);
   DiMuonMass_failedmatched -> SetTitle("Failing Probes 18.5<p_{T}^{probes}<30 GeV");
   DiMuonMass_failedmatched -> GetXaxis() -> SetTitle("m_{#mu#mu}");
   DiMuonMass_failedmatched -> GetYaxis() -> SetTitle("Entries/(0.04 GeV)");
   DiMuonMass_failedmatched -> Draw();
}
	

// Fitting function definition for Passed sample
Double_t fitting_function_passed (Double_t *val, Double_t *par)
{
    Double_t exponential = exp(-1*((val[0]-par[1])*(val[0]-par[1])/(2*par[2]*par[2])));
    Double_t f_passed = (par[0] * exponential + par[3])*par[4];
    return f_passed;
}

// Fitting function definition for Failed sample
Double_t fitting_function_failed (Double_t *val, Double_t *par)
{
    Double_t exponential = exp(-1*((val[0]-par[1])*(val[0]-par[1])/(2*par[2]*par[2])));
    Double_t f_passed = (par[0] * exponential + par[3])*(1-par[4]);
    return f_passed;
}
