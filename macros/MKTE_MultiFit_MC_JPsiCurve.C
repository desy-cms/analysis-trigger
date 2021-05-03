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
 


void MultiFit_MC_JPsiCurve() {


   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
   
   Double_t Luminosity_Total =36.528; //in fb^-1

   TFile * f = new TFile("myCDEF.root");
   TFile * f1 = new TFile("my1.root");
   TFile * f2 = new TFile("my2.root");
   TFile * f3 = new TFile("my3.root");
   TFile * f4 = new TFile("my4.root");
   TFile * f5 = new TFile("my5.root");
   TFile * f6 = new TFile("my6.root");
   TFile * f7 = new TFile("my7.root");
   TFile * f8 = new TFile("my8.root");
   TFile * f9 = new TFile("my9.root");
   TFile * f10 = new TFile("my10.root");
   
   //Individual Histograms
   TH1F * DiMuonMass_matched_1 = (TH1F*) f1 -> Get("DiMuonMass of passing muons pTBin1");
   TH1F * DiMuonMass_failedmatched_1 = (TH1F*) f1 -> Get("DiMuonMass of failing muons pTBin1");
   
   TH1F * DiMuonMass_matched_2 = (TH1F*) f2 -> Get("DiMuonMass of passing muons pTBin1");
   TH1F * DiMuonMass_failedmatched_2 = (TH1F*) f2 -> Get("DiMuonMass of failing muons pTBin1");
   
   TH1F * DiMuonMass_matched_3 = (TH1F*) f3 -> Get("DiMuonMass of passing muons pTBin1");
   TH1F * DiMuonMass_failedmatched_3 = (TH1F*) f3 -> Get("DiMuonMass of failing muons pTBin1");
   
   TH1F * DiMuonMass_matched_4 = (TH1F*) f4 -> Get("DiMuonMass of passing muons pTBin1");
   TH1F * DiMuonMass_failedmatched_4 = (TH1F*) f4 -> Get("DiMuonMass of failing muons pTBin1");
   
   TH1F * DiMuonMass_matched_5 = (TH1F*) f5 -> Get("DiMuonMass of passing muons pTBin1");
   TH1F * DiMuonMass_failedmatched_5 = (TH1F*) f5 -> Get("DiMuonMass of failing muons pTBin1");
   
   TH1F * DiMuonMass_matched_6 = (TH1F*) f6 -> Get("DiMuonMass of passing muons pTBin1");
   TH1F * DiMuonMass_failedmatched_6 = (TH1F*) f6 -> Get("DiMuonMass of failing muons pTBin1");
   
   TH1F * DiMuonMass_matched_7 = (TH1F*) f7 -> Get("DiMuonMass of passing muons pTBin1");
   TH1F * DiMuonMass_failedmatched_7 = (TH1F*) f7 -> Get("DiMuonMass of failing muons pTBin1");
   
   TH1F * DiMuonMass_matched_8 = (TH1F*) f8 -> Get("DiMuonMass of passing muons pTBin1");
   TH1F * DiMuonMass_failedmatched_8 = (TH1F*) f8 -> Get("DiMuonMass of failing muons pTBin1");
   
   TH1F * DiMuonMass_matched_9 = (TH1F*) f9 -> Get("DiMuonMass of passing muons pTBin1");
   TH1F * DiMuonMass_failedmatched_9 = (TH1F*) f9 -> Get("DiMuonMass of failing muons pTBin1");
   
   TH1F * DiMuonMass_matched_10 = (TH1F*) f10 -> Get("DiMuonMass of passing muons pTBin1");
   TH1F * DiMuonMass_failedmatched_10 = (TH1F*) f10 -> Get("DiMuonMass of failing muons pTBin1");
   
   
// get parameters of MC samples (pb)
   Double_t Cross_section_1= 1362000;
   Double_t Cross_section_2= 376600;
   Double_t Cross_section_3= 88930;
   Double_t Cross_section_4= 21230;
   Double_t Cross_section_5= 7055;
   Double_t Cross_section_6= 797.30;
   Double_t Cross_section_7= 59.24;
   Double_t Cross_section_8= 25.25;
   Double_t Cross_section_9= 4.723;
   Double_t Cross_section_10= 1.613;

   TH1F * WorkflowCDEF = (TH1F*) f -> Get("workflow;1/Workflow #1");
   
   TH1F * Workflow1 = (TH1F*) f1 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow2 = (TH1F*) f2 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow3 = (TH1F*) f3 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow4 = (TH1F*) f4 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow5 = (TH1F*) f5 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow6 = (TH1F*) f6 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow7 = (TH1F*) f7 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow8 = (TH1F*) f8 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow9 = (TH1F*) f9 -> Get("workflow;1/Workflow #1");
   TH1F * Workflow10 = (TH1F*) f10 -> Get("workflow;1/Workflow #1");

   Double_t Nevents1 = Workflow1->GetBinContent(2);
   Double_t Nevents2 = Workflow2->GetBinContent(2);
   Double_t Nevents3 = Workflow3->GetBinContent(2);
   Double_t Nevents4 = Workflow4->GetBinContent(2);
   Double_t Nevents5 = Workflow5->GetBinContent(2);
   Double_t Nevents6 = Workflow6->GetBinContent(2);
   Double_t Nevents7 = Workflow7->GetBinContent(2);
   Double_t Nevents8 = Workflow8->GetBinContent(2);
   Double_t Nevents9 = Workflow9->GetBinContent(2);
   Double_t Nevents10 = Workflow10->GetBinContent(2);
   
   // calculate Scale Factors for each MC sample
   Double_t ScaleFactor1, ScaleFactor2, ScaleFactor3, ScaleFactor4, ScaleFactor5, ScaleFactor6, ScaleFactor7, ScaleFactor8, ScaleFactor9, ScaleFactor10 ;
   
   ScaleFactor1 = Luminosity_Total*Cross_section_1/Nevents1*1000;//multiply by 1000 to take from pb to fb
   ScaleFactor2 = Luminosity_Total*Cross_section_2/Nevents2*1000;
   ScaleFactor3 = Luminosity_Total*Cross_section_3/Nevents3*1000;
   ScaleFactor4 = Luminosity_Total*Cross_section_4/Nevents4*1000;
   ScaleFactor5 = Luminosity_Total*Cross_section_5/Nevents5*1000;
   ScaleFactor6 = Luminosity_Total*Cross_section_6/Nevents6*1000;
   ScaleFactor7 = Luminosity_Total*Cross_section_7/Nevents7*1000;
   ScaleFactor8 = Luminosity_Total*Cross_section_8/Nevents8*1000;
   ScaleFactor9 = Luminosity_Total*Cross_section_9/Nevents9*1000;
   ScaleFactor10 = Luminosity_Total*Cross_section_10/Nevents10*1000;
  
   // scale the MC histograms
   DiMuonMass_matched_1 -> Scale(ScaleFactor1);
   DiMuonMass_failedmatched_1 -> Scale(ScaleFactor1);
   
   DiMuonMass_matched_2 -> Scale(ScaleFactor2);
   DiMuonMass_failedmatched_2 -> Scale(ScaleFactor2);
   
   DiMuonMass_matched_3 -> Scale(ScaleFactor3);
   DiMuonMass_failedmatched_3 -> Scale(ScaleFactor3);
   
   DiMuonMass_matched_4 -> Scale(ScaleFactor4);
   DiMuonMass_failedmatched_4 -> Scale(ScaleFactor4);
   
   DiMuonMass_matched_5 -> Scale(ScaleFactor5);
   DiMuonMass_failedmatched_5 -> Scale(ScaleFactor5);
   
   DiMuonMass_matched_6 -> Scale(ScaleFactor6);
   DiMuonMass_failedmatched_6 -> Scale(ScaleFactor6);
   
   DiMuonMass_matched_7 -> Scale(ScaleFactor7);
   DiMuonMass_failedmatched_7 -> Scale(ScaleFactor7);
   
   DiMuonMass_matched_8 -> Scale(ScaleFactor8);
   DiMuonMass_failedmatched_8 -> Scale(ScaleFactor8);
   
   DiMuonMass_matched_9 -> Scale(ScaleFactor9);
   DiMuonMass_failedmatched_9 -> Scale(ScaleFactor9);
   
   DiMuonMass_matched_10 -> Scale(ScaleFactor10);
   DiMuonMass_failedmatched_10 -> Scale(ScaleFactor10);

   // adding the MC histograms
   TH1F * DiMuonMass_matched = (TH1F*) DiMuonMass_matched_1->Clone("DiMuonMass_matched");
   TH1F * DiMuonMass_failedmatched = (TH1F*) DiMuonMass_failedmatched_1->Clone("DiMuonMass_failedmatched");
   
   DiMuonMass_matched -> Add(DiMuonMass_matched_2);
   DiMuonMass_matched -> Add(DiMuonMass_matched_3);
   DiMuonMass_matched -> Add(DiMuonMass_matched_4);
   DiMuonMass_matched -> Add(DiMuonMass_matched_5);
   DiMuonMass_matched -> Add(DiMuonMass_matched_6);
   DiMuonMass_matched -> Add(DiMuonMass_matched_7);
   DiMuonMass_matched -> Add(DiMuonMass_matched_8);
   DiMuonMass_matched -> Add(DiMuonMass_matched_9);
   DiMuonMass_matched -> Add(DiMuonMass_matched_10);
   
   DiMuonMass_failedmatched -> Add(DiMuonMass_failedmatched_2);
   DiMuonMass_failedmatched -> Add(DiMuonMass_failedmatched_3);
   DiMuonMass_failedmatched -> Add(DiMuonMass_failedmatched_4);
   DiMuonMass_failedmatched -> Add(DiMuonMass_failedmatched_5);
   DiMuonMass_failedmatched -> Add(DiMuonMass_failedmatched_6);
   DiMuonMass_failedmatched -> Add(DiMuonMass_failedmatched_7);
   DiMuonMass_failedmatched -> Add(DiMuonMass_failedmatched_8);
   DiMuonMass_failedmatched -> Add(DiMuonMass_failedmatched_9);
   DiMuonMass_failedmatched -> Add(DiMuonMass_failedmatched_10);
   
//-----------


   
   //scale MC to be on the same order as data
   
   Double_t HLT_Mu_8_Nevents_Data = WorkflowCDEF -> GetBinContent(4);
   Double_t HLT_Mu_8_Nevents_1    = Workflow1    -> GetBinContent(8) * ScaleFactor1;
   Double_t HLT_Mu_8_Nevents_2    = Workflow2    -> GetBinContent(8) * ScaleFactor2;
   Double_t HLT_Mu_8_Nevents_3    = Workflow3    -> GetBinContent(8) * ScaleFactor3;
   Double_t HLT_Mu_8_Nevents_4    = Workflow4    -> GetBinContent(8) * ScaleFactor4;
   Double_t HLT_Mu_8_Nevents_5    = Workflow5    -> GetBinContent(8) * ScaleFactor5;
   Double_t HLT_Mu_8_Nevents_6    = Workflow6    -> GetBinContent(8) * ScaleFactor6;
   Double_t HLT_Mu_8_Nevents_7    = Workflow7    -> GetBinContent(8) * ScaleFactor7;
   Double_t HLT_Mu_8_Nevents_8    = Workflow8    -> GetBinContent(8) * ScaleFactor8;
   Double_t HLT_Mu_8_Nevents_9    = Workflow9    -> GetBinContent(8) * ScaleFactor9;
   Double_t HLT_Mu_8_Nevents_10   = Workflow10   -> GetBinContent(8) * ScaleFactor10;
   
   //cout <<endl<<"Nevents 1 "<<HLT_Mu_8_Nevents_1<<endl;
   
   Double_t HLT_Mu_8_Nevents_MC = HLT_Mu_8_Nevents_1 + HLT_Mu_8_Nevents_2 + HLT_Mu_8_Nevents_3 + HLT_Mu_8_Nevents_4 + HLT_Mu_8_Nevents_5 + HLT_Mu_8_Nevents_6 + HLT_Mu_8_Nevents_7 + HLT_Mu_8_Nevents_8 + HLT_Mu_8_Nevents_9 + HLT_Mu_8_Nevents_10;
   
   Double_t ScaleFactor_HLT_Mu_8 = HLT_Mu_8_Nevents_Data/HLT_Mu_8_Nevents_MC;
   
   DiMuonMass_matched -> Scale(ScaleFactor_HLT_Mu_8);
   DiMuonMass_failedmatched -> Scale(ScaleFactor_HLT_Mu_8);
   
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
   double par0[Npar] = { 500, 3.097, 0.03, 100, 0.356}; 
 
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
   //DiMuonMass_matched -> SetTitle("Passing Probes 18.5<p_{T}^{probes}<30 GeV");
   DiMuonMass_matched -> GetXaxis() -> SetTitle("m_{#mu#mu}");
   DiMuonMass_matched -> GetYaxis() -> SetTitle("Entries/(0.04 GeV)");
   //DiMuonMass_matched -> GetYaxis() -> SetRangeUser(0,850);
   DiMuonMass_matched -> Draw();
   
   auto legend = new TLegend(0.15,0.75,0.39,0.85);
   legend->AddEntry(DiMuonMass_matched,"QCD #mu-enriched","lep");
   legend->Draw();
 
   C1 -> cd(2);
   fittingfunction_failed -> SetFitResult( result, iparFailed);
   fittingfunction_failed -> SetRange(rangeFailed().first, rangeFailed().second);
   fittingfunction_failed -> SetLineColor(kRed);
   DiMuonMass_failedmatched -> GetListOfFunctions() -> Add(fittingfunction_failed);
   //DiMuonMass_failedmatched -> SetTitle("Failing Probes 18.5<p_{T}^{probes}<30 GeV");
   DiMuonMass_failedmatched -> GetXaxis() -> SetTitle("m_{#mu#mu}");
   DiMuonMass_failedmatched -> GetYaxis() -> SetTitle("Entries/(0.04 GeV)");
   //DiMuonMass_failedmatched -> GetYaxis() -> SetRangeUser(0,30);
   DiMuonMass_failedmatched -> Draw();
   
   auto legend_failed = new TLegend(0.15,0.75,0.39,0.85);
   legend_failed->AddEntry(DiMuonMass_failedmatched,"QCD #mu-enriched","lep");
   legend_failed->Draw();
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
