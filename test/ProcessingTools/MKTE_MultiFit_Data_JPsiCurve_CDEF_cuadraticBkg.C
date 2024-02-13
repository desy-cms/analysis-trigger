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
 

//USE THIS MACRO FOR SIMULTANEOUS FIT OF JPSI CURVE FROM PASSING AND FAILING MUONS
void MKTE_MultiFit_Data_JPsiCurve_CDEF_cuadraticBkg() {


   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms

   TFile * f = new TFile("my_Data_SL_MKTE_Run2017CDEF.root");

   //Lower and upper limits of pTbins
   Double_t Limits[5] = {11.5, 12.5, 13.5, 18.5, 30};
   int pTbin = 3;//select the pT bin [1,2,3,4]
   bool save_in_rootfile = false; //save histograms in rootfiles
   
   // Histograms
   TH2D * DiMuonMass_passedmatching = (TH2D*) f -> Get("DiMuonMass of passing muons 2D");
   TH2D * DiMuonMass_failedmatching = (TH2D*) f -> Get("DiMuonMass of failing muons 2D");
   
   double min = 2.92, max = 3.28;
   // Declaring fitting functions and set parameters names
   TF1* fittingfunction_passed = new TF1 ("fittingfunction_passed", fitting_function_passed, min, max, 7);
   fittingfunction_passed -> SetParNames ("A","m_{0}","#sigma","k_{2}","k_{1}","k_{0}","#epsilon");
   TF1* fittingfunction_failed = new TF1 ("fittingfunction_failed", fitting_function_failed, min, max, 7);
   fittingfunction_failed -> SetParNames ("A","m_{0}","#sigma","k_{2}","k_{1}","k_{0}","#epsilon");
 
      
   //Projecting the 2D histograms
   TH1D* DiMuonMass_passed = ProjectHistogram(DiMuonMass_passedmatching, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_passed_pTbin_%d", pTbin));   
   TH1D* DiMuonMass_failed = ProjectHistogram(DiMuonMass_failedmatching, Limits[pTbin-1], Limits[pTbin], Form("DiMuonMass_failed_pTbin_%d", pTbin));
   
   int bineo = 4;
   
   DiMuonMass_passed -> Rebin(bineo);
   DiMuonMass_failed -> Rebin(bineo);
   
   if (save_in_rootfile)
   {
      TFile j(Form("DiMuonMass_Data_pTbin_%d.root", pTbin),"recreate");
      DiMuonMass_passed->Write();
      DiMuonMass_failed->Write();
      j.Close();
   }
   
   // perform now global fit

   //wrap a function in a IParamMultiFunction interface
   ROOT::Math::WrappedMultiTF1 wfittingfunction_passed(*fittingfunction_passed,1);
   ROOT::Math::WrappedMultiTF1 wfittingfunction_failed(*fittingfunction_failed,1);
   
   //fit properties

   ROOT::Fit::DataOptions opt;

   ROOT::Fit::DataRange rangePassed;
   rangePassed.SetRange(2.92,3.28);
   ROOT::Fit::BinData dataPassed(opt,rangePassed);
   ROOT::Fit::FillData(dataPassed, DiMuonMass_passed);

   ROOT::Fit::DataRange rangeFailed;
   rangeFailed.SetRange(2.92,3.28);
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
   //double par0[Npar] = { 2, 3.0969, 0.0296, -3.16, 10,  -20, 0.4};  //use for bin1,2 bineo 0p4
   double par0[Npar] = { 100, 3.0969, 0.009, -3.16, 10,  -20, 0.9};  //use for bin3 bineo 0p4
 
   // fix or set range on the parameters
   fitter.Config().SetParamsSettings(7,par0);   
   fitter.Config().ParSettings(1).Fix();
   fitter.Config().MinimizerOptions().SetPrintLevel(0);
   fitter.Config().SetMinimizer("Minuit2","Migrad");
 
   //Perform the fit
   fitter.FitFCN(7,globalChi2,0,dataPassed.Size()+dataFailed.Size(),true);
   ROOT::Fit::FitResult result = fitter.Result();
   result.Print(std::cout);
    
   TCanvas * C1 = new TCanvas("C","Canvas",1500,750);
   C1 -> Divide(2,1);
   C1 -> cd(1);
   gStyle->SetOptFit(1111);
   
 
   fittingfunction_passed -> SetFitResult( result, iparPassed);
   fittingfunction_passed -> SetRange(rangePassed().first, rangePassed().second);
   fittingfunction_passed -> SetLineColor(kBlue);
   DiMuonMass_passed -> GetListOfFunctions() -> Add(fittingfunction_passed);
   DiMuonMass_passed -> SetMarkerStyle(20);
   DiMuonMass_passed -> SetTitle("");
   DiMuonMass_passed -> GetXaxis() -> SetTitle("m_{#mu#mu}");
   DiMuonMass_passed -> GetXaxis() -> SetRangeUser(2.85,3.35);
   DiMuonMass_passed -> GetYaxis() -> SetRangeUser(0,fittingfunction_passed->GetMaximum()+20.7);
   DiMuonMass_passed -> GetYaxis() -> SetTitle(Form("Entries/(0.0%d GeV)", bineo));
   DiMuonMass_passed -> Draw();
 
   TLatex latex;
   latex.SetTextFont(43);
   latex.SetTextSize(20);
   latex.SetTextAlign(11);
   latex.DrawLatexNDC(C1 -> cd(1) ->GetLeftMargin(), 1.02-C1 -> cd(1) ->GetTopMargin(),
                (std::string("CMS Work in progress")).c_str());
   
   auto legend_passed = new TLegend(0.11,0.7,0.45,0.85);
   legend_passed->SetBorderSize(0);
   legend_passed->SetHeader(Form("%.1f < p_{T}^{probes} < %.1f GeV", Limits[pTbin-1], Limits[pTbin]),"C"); // option "C" allows to center the header
   legend_passed->AddEntry(DiMuonMass_passed,"Data CDEF","lep");
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
   DiMuonMass_failed -> GetXaxis() -> SetTitle("m_{#mu#mu}");
   DiMuonMass_failed -> GetXaxis() -> SetRangeUser(2.85,3.35);
   DiMuonMass_failed -> GetYaxis() -> SetRangeUser(0,fittingfunction_failed->GetMaximum()+15.7);
   DiMuonMass_failed -> GetYaxis() -> SetTitle(Form("Entries/(0.0%d GeV)", bineo));
   DiMuonMass_failed -> Draw();
   
   
   auto legend_failed = new TLegend(0.11,0.7,0.45,0.85);
   legend_failed->SetBorderSize(0);
   legend_failed->SetHeader(Form("%.1f < p_{T}^{probes} < %.1f GeV", Limits[pTbin-1], Limits[pTbin]),"C"); // option "C" allows to center the header
   legend_failed->AddEntry(DiMuonMass_failed,"Data CDEF","lep");
   TLegendEntry* l_failed_funct = legend_failed->AddEntry(fittingfunction_failed,"failing probe","l");
   l_failed_funct->SetTextColor(kRed);
   legend_failed->Draw();
   
   latex.DrawLatexNDC(C1 -> cd(2) ->GetLeftMargin(), 1.02-C1 -> cd(2) ->GetTopMargin(),
                (std::string("CMS Work in progress")).c_str());
   
   C1 -> SaveAs(Form("plots_data_cuadraticBkg/JPsi_pTbin%d_bineo0p0%dGeV.png",pTbin,bineo));
   C1 -> SaveAs(Form("plots_data_cuadraticBkg/JPsi_pTbin%d_bineo0p0%dGeV.pdf",pTbin,bineo));
   C1 -> SaveAs(Form("plots_data_cuadraticBkg/JPsi_pTbin%d_bineo0p0%dGeV.root",pTbin,bineo));
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
