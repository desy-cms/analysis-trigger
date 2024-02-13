void JKTE_setp3_FitUncertaintyVariations()
{
   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
   TCanvas * c1 = new TCanvas("c1","",820,820);
   
   int etabin = -1, sigma = 0, sign_var = 0;
   double etamin, etamax;
   
   cout<<"\nIntroduce the absolute values of the pseudorapidity limits for which the efficiency will be calculated\n";
   cout<<"\n|eta| lower limit:\n";
   cin >> etamin;
   cout<<"\n|eta| upper limit:\n";
   cin >> etamax;
   
   cout<<"\nIntroduce the module of the variation in amounts of sigma\n";
   cin >> sigma;
   
   cout<<"\nIntroduce the sign of the variation\n";
   cin >> sign_var;
   
   if (etamin == 0)
   etabin = 1;
   else if (etamin == 1)
   etabin = 2;
   else if (etamin == 1.4)
   etabin = 3;
   
   
   
   TFile * f = new TFile(Form("TGraph_up_nominal_down/TGraph_scale_factor_2017_SL_%dsigma.root",sigma));
     
   auto sf_up = (TGraphAsymmErrors*)   f -> Get(Form("jetOnlineTriggerScaleFactor_eta_%g_to_%g_up",etamin,etamax));
   auto sf_down = (TGraphAsymmErrors*) f -> Get(Form("jetOnlineTriggerScaleFactor_eta_%g_to_%g_down",etamin,etamax));
   TFitResultPtr r1;
   
   //fitting function
   TF1 *fa1 = new TF1("fa1","[0]*erf([1]*x-[2])",40, 300);
   fa1 -> SetParameters(1,0.05,1);
   
   //Fit and plot the SF, EX0 to ignore x axis uncert.
   if (sign_var == 1)
   {
      r1 = sf_up->Fit(fa1,"RS EX0");  
      sf_up->Draw("ap");
   }
   
   if (sign_var == -1)
   {
   r1 = sf_down->Fit(fa1,"RS EX0");  
   sf_down->Draw("ap");
   }
   
   
//---------------------------------------------
   // print matrices
   cout << endl;
   cout << "chi2/ndf = " << r1->Chi2() << "/" << r1->Ndf() << " = " << r1->Chi2()/r1->Ndf() << ", prob = " << r1->Prob() << endl;
   cout << endl;
   cout << "*** Correlation Matrix ***" << endl;
   r1 -> GetCorrelationMatrix().Print();
   cout << endl;
   cout << "*** Covariance Matrix ***" << endl;
   r1 -> GetCovarianceMatrix().Print();
//---------------------------------------------

// Fit results

   TFile fout(Form("results_fit_up_down/Funct_sf_%dsigma.root",sigma),"UPDATE");   
   if(sign_var == 1)
   {
      if(etabin == 1)
      fa1->Write(Form("jetOnlineTriggerScaleFactor_etabin_0p0_to_1p0_%ds_up",sigma));
      if(etabin == 2)
      fa1->Write(Form("jetOnlineTriggerScaleFactor_etabin_1p0_to_1p4_%ds_up",sigma));
      if(etabin == 3)
      fa1->Write(Form("jetOnlineTriggerScaleFactor_etabin_1p4_to_2p2_%ds_up",sigma));
   }

   if(sign_var == -1)
   {
      if(etabin == 1)
      fa1->Write(Form("jetOnlineTriggerScaleFactor_etabin_0p0_to_1p0_%ds_down",sigma));
      if(etabin == 2)
      fa1->Write(Form("jetOnlineTriggerScaleFactor_etabin_1p0_to_1p4_%ds_down",sigma));
      if(etabin == 3)
      fa1->Write(Form("jetOnlineTriggerScaleFactor_etabin_1p4_to_2p2_%ds_down",sigma));
   }

}
