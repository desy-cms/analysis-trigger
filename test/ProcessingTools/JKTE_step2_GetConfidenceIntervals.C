void JKTE_step2_GetConfidenceIntervals()
{
   //USE THIS FUNCTION TO GET GRAPHS WITH CONFIDENCE INTERVALS FROM THE FIT PERFORMED TO THE NOMINAL JET KINEMATIC SCALE FACTOR
   //USER PROVIDES ETA RANGE AND SIGMA
   
   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
   TFile * f = new TFile("TGraph_up_nominal_down/TGraphs_scale_factor_2017_SL.root");
   TCanvas * c1 = new TCanvas("c1","",820,820);
   
   int etabin = -1, sigma = 0;
   double etamin, etamax;
   
   cout<<"\nIntroduce the absolute values of the pseudorapidity limits for which the efficiency will be calculated\n";
   cout<<"\n|eta| lower limit:\n";
   cin >> etamin;
   cout<<"\n|eta| upper limit:\n";
   cin >> etamax;
   
   cout<<"\nIntroduce the variation in amounts of sigma\n";
   cin >> sigma;
   
   if (etamin == 0)
   etabin = 1;
   else if (etamin == 1)
   etabin = 2;
   else if (etamin == 1.4)
   etabin = 3;
   
   auto sf = (TGraphAsymmErrors*) f -> Get(Form("scale_factor_2017_SL_eta_%g_to_%g",etamin,etamax));
   
   
   //fitting function
   TF1 *fa1 = new TF1("fa1","[0]*erf([1]*x-[2])",40, 300);
   fa1 -> SetParameters(1,0.05,1);
   
   // Fix correlated parameters
   double param_1fix[3] = {4.09284e-02,3.61857e-02,3.28926e-02};
   double param_2fix[3] = {1.07469e+00,9.54743e-01,8.94030e-01};
   fa1 -> FixParameter(1,param_1fix[etabin - 1]);
   //fa1 -> FixParameter(2,param_2fix[etabin - 1]);
   
   //Fit and plot the SF, EX0 to ignore x axis uncert.
   TFitResultPtr r1 = sf->Fit(fa1,"RS EX0");  
   sf -> GetFunction("fa1") -> SetLineColor(kBlack);
   sf -> Draw("ap");
   //fa1 -> Draw("same");
  
  
//---------------------------------------------
   // print matrices
   cout << endl;
   cout << "*** Correlation Matrix ***" << endl;
   r1 -> GetCorrelationMatrix().Print();
   cout << endl;
   cout << "*** Covariance Matrix ***" << endl;
   r1 -> GetCovarianceMatrix().Print();
//---------------------------------------------

   int bineo = 2600;
   sf -> GetYaxis() -> SetRangeUser(0.6,1.01);
   sf -> GetXaxis() -> SetRangeUser(120,300);
   
   TH1D *h_CI ;
   
   
   if (sigma != 0)
   {
      if(sigma == 1)
      {
         // histogram to hold the confidence intervals
         h_CI = new TH1D("h_CI",
            "Fit with .68 conf.band", bineo, 40, 300);
      
         //Compute the confidence intervals and save in the histogram, 68% CL by default
        (TVirtualFitter::GetFitter())->GetConfidenceIntervals(h_CI, 0.68);
   
     }
      if(sigma == 2)
      {
         // histogram to hold the confidence intervals
         h_CI = new TH1D("h_CI",
            "Fit with .95 conf.band", bineo, 40, 300);
      
         //Compute the confidence intervals and save in the histogram, 95% CL by default
        (TVirtualFitter::GetFitter())->GetConfidenceIntervals(h_CI, 0.95);
   
     }
        h_CI->SetStats(kFALSE);
        h_CI->SetFillColor(2);
        h_CI->SetLineColor(2);
        //Draw the CI, e3 option draws the band
        //h_CI->Draw("e same");
   }
//---------------------------------------------
//Plot - use this section to plot the interval
//---------------------------------------------
  /* 
   sf -> GetYaxis() -> SetTitle ("");
   
   TLatex latex;
   latex.SetTextFont(43);
   latex.SetTextSize(20);
   latex.SetTextAlign(11);
   latex.DrawLatexNDC(gPad->GetLeftMargin(), 1.02-c1->GetTopMargin(),
                (std::string("CMS Work in progress #sqrt{s} = 13 TeV, L = 54.54 fb^{-1}")).c_str());
                
   TLatex latex1;
   latex1.SetTextFont(43);
   latex1.SetTextSize(20);
   latex1.SetTextAlign(11);
   latex1.DrawLatexNDC(0.8-gPad->GetLeftMargin(), 1.02-c1->GetTopMargin(),
                (std::string("HLT_PFJet116_er2p3").c_str()));
                   
   auto legend = new TLegend(0.6,0.25,0.8,0.35);
   legend->SetHeader("0 <|#eta|< 1","c1"); // option "C" allows to center the header
   legend->AddEntry(sf,"Scale Factor","lep");
   legend->Draw();
   
   c1 -> SaveAs("Barrel_SF_1sigma_CI_2.png");
   c1 -> SaveAs("Barrel_SF_1sigma_CI_2.pdf");*/
   
   //sf -> GetYaxis() -> SetRangeUser (0.55,1.05);
   
   //c1 -> SaveAs("Barrel_SF_1sigma_CI_zoom_v2.png");
   //c1 -> SaveAs("Barrel_SF_1sigma_CI_zoom_v2.pdf");
//---------------------------------------------


//--------------------------------------------
//Section to save in graphs nominal and up and down variations
//--------------------------------------------

   Double_t p[3] = {(TVirtualFitter::GetFitter())->GetParameter(0), (TVirtualFitter::GetFitter())->GetParameter(1), (TVirtualFitter::GetFitter())->GetParameter(2)};
   Double_t x[bineo], y_nominal[bineo], y_sigma_up[bineo], y_sigma_down[bineo], CL;
   
   for (int i=0; i < bineo; i++)
   {
      //x[i] = h_CI -> GetBinCenter(i+1);
      x[i] = 40.05 + 0.1*i;
      y_nominal[i] = p[0]*erf(p[1]*x[i]-p[2]);
      
      if(sigma != 0)
      {
         CL = h_CI -> GetBinError(i+1);
         y_sigma_up[i] = p[0]*erf(p[1]*x[i]-p[2]) + CL;
         y_sigma_down[i] = p[0]*erf(p[1]*x[i]-p[2]) - CL;
      }
      //cout <<endl<< "x : "<< x[i] << " y : "<< y_nominal[i];
   }
   
   TGraph * gr_SF_barrel_nominal = new TGraphAsymmErrors(bineo, x, y_nominal);
   TGraph * gr_SF_barrel_sigma_up;
   TGraph * gr_SF_barrel_sigma_down;
   
   if(sigma != 0)
   {
      gr_SF_barrel_sigma_up = new TGraphAsymmErrors(bineo, x, y_sigma_up);
      gr_SF_barrel_sigma_down = new TGraphAsymmErrors(bineo, x, y_sigma_down);
   }
//---------------------------------------------   
   //Draw the three graphs
//---------------------------------------------
   gr_SF_barrel_nominal -> SetLineWidth(2);
   gr_SF_barrel_nominal -> SetLineColor(kBlack);
   gr_SF_barrel_nominal -> Draw("same");
   
   if(sigma != 0)
   {
   gr_SF_barrel_sigma_up -> SetLineColor(kRed);
   gr_SF_barrel_sigma_up -> Draw("same");
   gr_SF_barrel_sigma_down -> SetLineColor(kBlue);
   gr_SF_barrel_sigma_down -> Draw("same");
   }
//---------------------------------------------
//Plot - use this section to plot the nominal and up and down variations of the SF
//---------------------------------------------
   
   sf -> GetYaxis() -> SetTitle ("");
   gr_SF_barrel_nominal -> SetTitle ("");
                   
   auto legend = new TLegend(0.6,0.25,0.8,0.35);
   legend->SetHeader("0 <|#eta|< 1","c1"); // option "C" allows to center the header
   legend->AddEntry(sf,"Scale Factor","lep");
   legend->AddEntry(gr_SF_barrel_nominal,"Scale Factor Fit","lp");
   //legend->AddEntry(gr_SF_barrel_sigma_up,Form("Scale Factor %d#sigma up",sigma),"lp");
   //legend->AddEntry(gr_SF_barrel_sigma_down,Form("Scale Factor %d#sigma down",sigma),"lp");
   legend->Draw();
   
   
   TLatex latex;
   latex.SetTextFont(43);
   latex.SetTextSize(20);
   latex.SetTextAlign(11);
   latex.DrawLatexNDC(gPad->GetLeftMargin(), 1.02-c1->GetTopMargin(),
                (std::string("CMS Work in progress #sqrt{s} = 13 TeV, L = 54.54 fb^{-1}")).c_str());
                
   TLatex latex1;
   latex1.SetTextFont(43);
   latex1.SetTextSize(20);
   latex1.SetTextAlign(11);
   latex1.DrawLatexNDC(0.8-gPad->GetLeftMargin(), 1.02-c1->GetTopMargin(),
                (std::string("HLT_PFJet116_er2p3").c_str()));
   
   sf -> GetXaxis() -> SetRangeUser (40,300);
   sf -> GetYaxis() -> SetRangeUser (0.6,1.05);
  
   if(sigma == 0)
   {
   c1 -> SaveAs(Form("results_fit_nominal/SF_%dsigma_CI_up_nominal_down_eta_%g_to_%g.png",sigma,etamin,etamax));
   c1 -> SaveAs(Form("results_fit_nominal/SF_%dsigma_CI_up_nominal_down_eta_%g_to_%g.pdf",sigma,etamin,etamax));
   }
   
   if(sigma != 0)
   {
   c1 -> SaveAs(Form("TGraph_up_nominal_down/SF_%dsigma_CI_up_nominal_down_eta_%g_to_%g.png",sigma,etamin,etamax));
   c1 -> SaveAs(Form("TGraph_up_nominal_down/SF_%dsigma_CI_up_nominal_down_eta_%g_to_%g.pdf",sigma,etamin,etamax));
   }
//---------------------------------------------


   //save SF in a file for next step (get confidence intervals graphs parametrized)   
   
   
   if(sigma == 0)
   {
   TFile fout("results_fit_nominal/Funct_sf_barrel_nominal.root","UPDATE");
   if(etabin == 1)
   fa1->Write("jetOnlineTriggerScaleFactor_etabin_0p0_to_1p0_nominal");
   if(etabin == 2)
   fa1->Write("jetOnlineTriggerScaleFactor_etabin_1p0_to_1p4_nominal");
   if(etabin == 3)
   fa1->Write("jetOnlineTriggerScaleFactor_etabin_1p4_to_2p2_nominal");
   }
   
   if(sigma == 1)
   {
      TFile fout("TGraph_up_nominal_down/TGraph_scale_factor_2017_SL_1sigma.root","UPDATE");
      gr_SF_barrel_sigma_up   -> Write(Form("jetOnlineTriggerScaleFactor_eta_%g_to_%g_up",etamin,etamax)); 
      gr_SF_barrel_sigma_down -> Write(Form("jetOnlineTriggerScaleFactor_eta_%g_to_%g_down",etamin,etamax));
   }
   
   if(sigma == 2)
   { 
      TFile fout("TGraph_up_nominal_down/TGraph_scale_factor_2017_SL_2sigma.root","UPDATE");
      gr_SF_barrel_sigma_up   -> Write(Form("jetOnlineTriggerScaleFactor_eta_%g_to_%g_up",etamin,etamax)); 
      gr_SF_barrel_sigma_down -> Write(Form("jetOnlineTriggerScaleFactor_eta_%g_to_%g_down",etamin,etamax));
   }

}
