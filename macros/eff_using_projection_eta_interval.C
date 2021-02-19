TGraphAsymmErrors* EfficiencyProjection(TH2F* h_numerator, TH2F* h_denominator, double etamin, double etamax);

int eff_using_projection_eta_interval()
{

// USE THIS MACRO TO PLOT THE JET KINEMATIC TRIGGER EFFICIENCY AS FUNCTION OF PT AMONG TWO USER DEFINED PSEUDORAPIDITY VALUES
   
   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
   
   //Open the root file
   char rootfile[1000];
   cout<<"\nIntroduce the name of the root file\n";
   cin >> rootfile;
   TFile * fDATA = new TFile(rootfile);

   // get denominator histograms
   TH2F * h_denominator = (TH2F*) fDATA -> Get("Probes/pt_eta_jet2");
   // get numerator histograms
   TH2F * h_numerator  = (TH2F*) fDATA -> Get("Probes with matching/pt_eta_jet2");
   
   // get two pseudorapidity values among whose the efficiency is going to be calculted
   double etamin, etamax;
   cout<<"\nIntroduce the absolute values of the pseudorapidity limits for which the efficiency will be calculated\n";
   cout<<"\n|eta| lower limit:\n";
   cin >> etamin;
   cout<<"\n|eta| upper limit:\n";
   cin >> etamax;
   
   //calculate the efficiency and draw
   TGraphAsymmErrors* g_eff = EfficiencyProjection(h_numerator, h_denominator, etamin, etamax);
   g_eff -> GetXaxis() -> SetRangeUser(30,300);
   g_eff -> GetYaxis() -> SetRangeUser(0.1,1.1);
   g_eff -> SetMarkerStyle(20);
   if (etamax == -1)
   g_eff -> SetTitle (Form("Jet Kinematic Trigger Efficiency %g<|#eta|<Inf",etamin));
   else
   g_eff -> SetTitle (Form("Jet Kinematic Trigger Efficiency %g<|#eta|<%g",etamin,etamax));
   g_eff -> Draw("AP");

   return 0;
}

//Function for calculating the efficiency with pt among two eta values
TGraphAsymmErrors* EfficiencyProjection(TH2F* h_numerator, TH2F* h_denominator, double etamin, double etamax)
{
   //declare histograms
   TH1D *hprojecteddenominator;
   TH1D *hprojectednumerator;
   
  
   if (etamin == 0)
      {
         if (etamax == -1)
         {
            int LowerBin = 1;
            int UpperBin = h_denominator -> GetNbinsY();

            hprojecteddenominator = h_denominator -> ProjectionX("denominator", LowerBin, UpperBin, "e");
            hprojectednumerator = h_numerator -> ProjectionX("numerator", LowerBin, UpperBin, "e");

         }

         else
         {
            int NbinX = h_denominator -> GetNbinsX();
            int LowerBin = h_denominator -> FindBin(0,-1*etamax)/NbinX;
            int UpperBin = h_denominator -> FindBin(0,etamax)/NbinX;

            hprojecteddenominator = h_denominator -> ProjectionX("denominator", LowerBin, UpperBin, "e");
            hprojectednumerator = h_numerator -> ProjectionX("numerator", LowerBin, UpperBin, "e");

         }
      }

   else 
      {
         if (etamax == -1)
         {  
            int NbinX = h_denominator -> GetNbinsX();
            int LowerBin1 = h_denominator -> FindBin(0,etamin)/NbinX;
            int UpperBin1 = h_denominator -> GetNbinsY();
            int LowerBin2 = h_denominator -> FindBin(0,-1*etamin)/NbinX;
            int UpperBin2 = 1;

            TH1D *hdenominator1 = h_denominator -> ProjectionX("denominator1", LowerBin1, UpperBin1, "e");
            TH1D *hnumerator1 = h_numerator -> ProjectionX("numerator1", LowerBin1, UpperBin1, "e");
            TH1D *hdenominator2 = h_denominator -> ProjectionX("denominator2", LowerBin2, UpperBin2, "e");
            TH1D *hnumerator2 = h_numerator -> ProjectionX("numerator2", LowerBin2, UpperBin2, "e");

            hprojecteddenominator = hdenominator1;
            hprojecteddenominator -> Add(hdenominator2);
            hprojectednumerator = hnumerator1;
            hprojectednumerator -> Add(hnumerator2);
         }
         
         else
         {   
            int NbinX = h_denominator -> GetNbinsX();
            int LowerBin1 = h_denominator -> FindBin(0,etamin)/NbinX;
            int UpperBin1 = h_denominator -> FindBin(0,etamax)/NbinX;
            int LowerBin2 = h_denominator -> FindBin(0,-1*etamin)/NbinX;
            int UpperBin2 = h_denominator -> FindBin(0,-1*etamax)/NbinX;

            TH1D *hdenominator1 = h_denominator -> ProjectionX("denominator1", LowerBin1, UpperBin1, "e");
            TH1D *hnumerator1 = h_numerator -> ProjectionX("numerator1", LowerBin1, UpperBin1, "e");
            TH1D *hdenominator2 = h_denominator -> ProjectionX("denominator2", LowerBin2, UpperBin2, "e");
            TH1D *hnumerator2 = h_numerator -> ProjectionX("numerator2", LowerBin2, UpperBin2, "e");

            hprojecteddenominator = hdenominator1;
            hprojecteddenominator -> Add(hdenominator2);
            hprojectednumerator = hnumerator1;
            hprojectednumerator -> Add(hnumerator2);
         }
      }

      hprojectednumerator -> Rebin(10);
      hprojecteddenominator -> Rebin(10);

      TGraphAsymmErrors * g_eff = new TGraphAsymmErrors(hprojectednumerator, hprojecteddenominator,"cl=0.683 b(1,1) mode");
      return g_eff;
}



