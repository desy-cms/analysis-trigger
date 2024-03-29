TH1D* ProjectHistogram(TH2F* h, double etamin, double etamax, char name[]);
TGraphAsymmErrors* DivideTGraphsErrors(TGraphAsymmErrors* A, TGraphAsymmErrors* B);
double ErrorDivision(double ea, double eb, double ValueA, double ValueB);
void FillHistogramfromHistogram(TH1D* h1, TH1D* h2,int BinMin,int BinMax);
void FillHistogramfromHistogram_newbinning(TH1D* h1, TH1D* h2,int BinMin,int BinMax);

// USE THIS MACRO TO PLOT THE JET KINEMATIC TRIGGER EFFICIENCY AS FUNCTION OF PT AMONG TWO USER DEFINED PSEUDORAPIDITY VALUES

int JKTE_Data_MC()
{
   
   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms

   //For Scale Factors Data
   Double_t Luminosity_C = 9581; //in pb=^-1
   Double_t Luminosity_D = 4224; //in pb=^-1
   Double_t Luminosity_E = 9261; //in pb=^-1
   Double_t Luminosity_F = 13462; //in pb=^-1
   Double_t Luminosity_Total_CDE = Luminosity_C + Luminosity_D + Luminosity_E; //in pb=^-1
   Double_t Total_Physics_Trigger_Lumi = Luminosity_C + Luminosity_D + Luminosity_E + Luminosity_F;
      
   
   Double_t Luminosity_PFJet40_C = 58.3; //in pb=^-1
   Double_t Luminosity_PFJet40_D = 193.3; //in pb=^-1
   Double_t Luminosity_PFJet40_E = 66.2; //in pb=^-1
   Double_t Luminosity_PFJet40_F = 72.6; //in pb=^-1
   Double_t Luminosity_Total_PFJet40_CDE = Luminosity_PFJet40_C + Luminosity_PFJet40_D + Luminosity_PFJet40_E; //in pb=^-1
   Double_t Total_PFJet40_Trigger_Lumi = Luminosity_PFJet40_C + Luminosity_PFJet40_D + Luminosity_PFJet40_E + Luminosity_PFJet40_F;
   
   Double_t Luminosity_PFJet60_C =232; //in pb=^-1
   Double_t Luminosity_PFJet60_D =357; //in pb=^-1
   Double_t Luminosity_PFJet60_E =277; //in pb=^-1
   Double_t Luminosity_PFJet60_F =259; //in pb=^-1
   Double_t Luminosity_Total_PFJet60_CDE = Luminosity_PFJet60_C+Luminosity_PFJet60_D+Luminosity_PFJet60_E; //in pb=^-1
   Double_t Total_PFJet60_Trigger_Lumi = Luminosity_PFJet60_C + Luminosity_PFJet60_D + Luminosity_PFJet60_E + Luminosity_PFJet60_F;
   
   Double_t ScaleFactor_F_PFJet40, ScaleFactor_F_PFJet60;
   Double_t ScaleFactor_CDE_PFJet40, ScaleFactor_CDE_PFJet60;
   
   ScaleFactor_CDE_PFJet40 = (Luminosity_Total_CDE/Total_Physics_Trigger_Lumi) * (Total_PFJet40_Trigger_Lumi/Luminosity_Total_PFJet40_CDE);
   ScaleFactor_CDE_PFJet60 = (Luminosity_Total_CDE/Total_Physics_Trigger_Lumi) * (Total_PFJet60_Trigger_Lumi/Luminosity_Total_PFJet60_CDE);
   
   ScaleFactor_F_PFJet40 = (Luminosity_F/Total_Physics_Trigger_Lumi) * (Total_PFJet40_Trigger_Lumi/Luminosity_PFJet40_F);
   ScaleFactor_F_PFJet60 = (Luminosity_F/Total_Physics_Trigger_Lumi) * (Total_PFJet60_Trigger_Lumi/Luminosity_PFJet60_F);
   
   
   // set Canvas properties
   //auto C = new TCanvas("C","Canvas",1500,750);
   

   // declare Tfiles
   
   //For MC. The MC are using PFJet40
   TFile * f1 = new TFile("myMC1.root"); 
   TFile * f2 = new TFile("myMC2.root"); 
   TFile * f3 = new TFile("myMC3.root"); 
   TFile * f4 = new TFile("myMC4.root"); 
   TFile * f5 = new TFile("myMC5.root"); 
   TFile * f6 = new TFile("myMC6.root");
   TFile * f7 = new TFile("myMC7.root"); 
   TFile * f8 = new TFile("myMC8.root"); 
   
   //For data
   TFile * fDATA_PFJet40_1 = new TFile("myC_PFJet40.root"); //this is for Data
   TFile * fDATA_PFJet40_2 = new TFile("myD_PFJet40.root"); //this is for Data
   TFile * fDATA_PFJet40_3 = new TFile("myE_PFJet40.root"); //this is for Data
   TFile * fDATA_PFJet40_4 = new TFile("myF_PFJet40.root"); //this is for Data
   
   TFile * fDATA_PFJet60_1 = new TFile("myC_PFJet60.root"); //this is for Data
   TFile * fDATA_PFJet60_2 = new TFile("myD_PFJet60.root"); //this is for Data
   TFile * fDATA_PFJet60_3 = new TFile("myE_PFJet60.root"); //this is for Data
   TFile * fDATA_PFJet60_4 = new TFile("myF_PFJet60.root"); //this is for Data


   // get two pseudorapidity values among whose the efficiency is going to be calculted
   double etamin, etamax;
   cout<<"\nIntroduce the absolute values of the pseudorapidity limits for which the efficiency will be calculated\n";
   cout<<"\n|eta| lower limit:\n";
   cin >> etamin;
   cout<<"\n|eta| upper limit:\n";
   cin >> etamax;
   
   auto C = new TCanvas("C","Canvas",1000,1500);
   C -> Divide (1,2);

   // get DATA denominator histograms
   TH2F * h_denominatorDATA_PFJet40_1 = (TH2F*) fDATA_PFJet40_1 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominatorDATA_PFJet40_2 = (TH2F*) fDATA_PFJet40_2 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominatorDATA_PFJet40_3 = (TH2F*) fDATA_PFJet40_3 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominatorDATA_PFJet40_4 = (TH2F*) fDATA_PFJet40_4 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominatorDATA_PFJet60_1 = (TH2F*) fDATA_PFJet60_1 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominatorDATA_PFJet60_2 = (TH2F*) fDATA_PFJet60_2 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominatorDATA_PFJet60_3 = (TH2F*) fDATA_PFJet60_3 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominatorDATA_PFJet60_4 = (TH2F*) fDATA_PFJet60_4 -> Get("Probes/pt_eta_jet2");
   //MC
   TH2F * h_denominator1_2D = (TH2F*) f1 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominator2_2D = (TH2F*) f2 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominator3_2D = (TH2F*) f3 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominator4_2D = (TH2F*) f4 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominator5_2D = (TH2F*) f5 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominator6_2D = (TH2F*) f6 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominator7_2D = (TH2F*) f7 -> Get("Probes/pt_eta_jet2");
   TH2F * h_denominator8_2D = (TH2F*) f8 -> Get("Probes/pt_eta_jet2");


   // get numerator histograms
   TH2F * h_numeratorDATA_PFJet40_1  = (TH2F*) fDATA_PFJet40_1 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numeratorDATA_PFJet40_2  = (TH2F*) fDATA_PFJet40_2 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numeratorDATA_PFJet40_3  = (TH2F*) fDATA_PFJet40_3 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numeratorDATA_PFJet40_4  = (TH2F*) fDATA_PFJet40_4 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numeratorDATA_PFJet60_1  = (TH2F*) fDATA_PFJet60_1 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numeratorDATA_PFJet60_2  = (TH2F*) fDATA_PFJet60_2 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numeratorDATA_PFJet60_3  = (TH2F*) fDATA_PFJet60_3 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numeratorDATA_PFJet60_4  = (TH2F*) fDATA_PFJet60_4 -> Get("Probes with matching/pt_eta_jet2");
   //MC  
   TH2F * h_numerator1_2D  = (TH2F*) f1 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numerator2_2D  = (TH2F*) f2 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numerator3_2D  = (TH2F*) f3 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numerator4_2D  = (TH2F*) f4 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numerator5_2D  = (TH2F*) f5 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numerator6_2D  = (TH2F*) f6 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numerator7_2D  = (TH2F*) f7 -> Get("Probes with matching/pt_eta_jet2");
   TH2F * h_numerator8_2D  = (TH2F*) f8 -> Get("Probes with matching/pt_eta_jet2");
   

   
   // adding the Data era CDE samples
   TH2F * h_numeratorDATA_CDE_PFJet40   = (TH2F*) h_numeratorDATA_PFJet40_1  ->Clone("h_numeratorDATA_CDEF_PFJet40");
   TH2F * h_denominatorDATA_CDE_PFJet40 = (TH2F*) h_denominatorDATA_PFJet40_1->Clone("h_denominatorDATA_CDEF_PFJet40");
   
   h_numeratorDATA_CDE_PFJet40 -> Add(h_numeratorDATA_PFJet40_2);
   h_numeratorDATA_CDE_PFJet40 -> Add(h_numeratorDATA_PFJet40_3);
   h_denominatorDATA_CDE_PFJet40 -> Add(h_denominatorDATA_PFJet40_2);
   h_denominatorDATA_CDE_PFJet40 -> Add(h_denominatorDATA_PFJet40_3);


   TH2F * h_numeratorDATA_CDE_PFJet60   = (TH2F*) h_numeratorDATA_PFJet60_1  ->Clone("h_numeratorDATA_CDEF_PFJet60");
   TH2F * h_denominatorDATA_CDE_PFJet60 = (TH2F*) h_denominatorDATA_PFJet60_1->Clone("h_denominatorDATA_CDEF_PFJet60");
   
   h_numeratorDATA_CDE_PFJet60 -> Add(h_numeratorDATA_PFJet60_2);
   h_numeratorDATA_CDE_PFJet60 -> Add(h_numeratorDATA_PFJet60_3);
   h_denominatorDATA_CDE_PFJet60 -> Add(h_denominatorDATA_PFJet60_2);
   h_denominatorDATA_CDE_PFJet60 -> Add(h_denominatorDATA_PFJet60_3);
   
   
   // Scale Data samples

   h_numeratorDATA_PFJet40_4   -> Scale (ScaleFactor_F_PFJet40);
   h_denominatorDATA_PFJet40_4 -> Scale (ScaleFactor_F_PFJet40);
   h_numeratorDATA_PFJet60_4   -> Scale (ScaleFactor_F_PFJet60);
   h_denominatorDATA_PFJet60_4 -> Scale (ScaleFactor_F_PFJet60);
   
   h_numeratorDATA_CDE_PFJet40   -> Scale (ScaleFactor_CDE_PFJet40);
   h_denominatorDATA_CDE_PFJet40 -> Scale (ScaleFactor_CDE_PFJet40);
   h_numeratorDATA_CDE_PFJet60   -> Scale (ScaleFactor_CDE_PFJet60);
   h_denominatorDATA_CDE_PFJet60 -> Scale (ScaleFactor_CDE_PFJet60);
   
   //Adding Data samples
   
   TH2F * h_numeratorDATA_PFJet40_2D   = (TH2F*) h_numeratorDATA_CDE_PFJet40->Clone("h_numeratorDATA_PFJet40_2D");
   TH2F * h_denominatorDATA_PFJet40_2D = (TH2F*) h_denominatorDATA_CDE_PFJet40->Clone("h_denominatorDATA_PFJet40_2D");
   
   h_numeratorDATA_PFJet40_2D   -> Add(h_numeratorDATA_PFJet40_4);
   h_denominatorDATA_PFJet40_2D -> Add(h_denominatorDATA_PFJet40_4);
   
   TH2F * h_numeratorDATA_PFJet60_2D   = (TH2F*) h_numeratorDATA_CDE_PFJet60->Clone("h_numeratorDATA_PFJet60_2D");
   TH2F * h_denominatorDATA_PFJet60_2D = (TH2F*) h_denominatorDATA_CDE_PFJet60->Clone("h_denominatorDATA_PFJet60_2D");
   
   h_numeratorDATA_PFJet60_2D   -> Add(h_numeratorDATA_PFJet60_4);
   h_denominatorDATA_PFJet60_2D -> Add(h_denominatorDATA_PFJet60_4);
   
   //Projecting Data Samples
   TH1D* h_numeratorDATA_PFJet40   = ProjectHistogram(h_numeratorDATA_PFJet40_2D, etamin, etamax, "h_numeratorDATA_PFJet40");
   TH1D* h_denominatorDATA_PFJet40 = ProjectHistogram(h_denominatorDATA_PFJet40_2D, etamin, etamax, "h_denominatorDATA_PFJet40");
   TH1D* h_numeratorDATA_PFJet60   = ProjectHistogram(h_numeratorDATA_PFJet60_2D, etamin, etamax, "h_numeratorDATA_PFJet60");
   TH1D* h_denominatorDATA_PFJet60 = ProjectHistogram(h_denominatorDATA_PFJet60_2D, etamin, etamax, "h_denominatorDATA_PFJet60");
      
   
   // projection of each MC histogram   
    
   TH1D* h_denominator1 = ProjectHistogram(h_denominator1_2D, etamin, etamax, "h_denominator1_projected");
   TH1D* h_denominator2 = ProjectHistogram(h_denominator2_2D, etamin, etamax, "h_denominator2_projected");
   TH1D* h_denominator3 = ProjectHistogram(h_denominator3_2D, etamin, etamax, "h_denominator3_projected");
   TH1D* h_denominator4 = ProjectHistogram(h_denominator4_2D, etamin, etamax, "h_denominator4_projected");
   TH1D* h_denominator5 = ProjectHistogram(h_denominator5_2D, etamin, etamax, "h_denominator5_projected");
   TH1D* h_denominator6 = ProjectHistogram(h_denominator6_2D, etamin, etamax, "h_denominator6_projected");
   TH1D* h_denominator7 = ProjectHistogram(h_denominator7_2D, etamin, etamax, "h_denominator7_projected");
   TH1D* h_denominator8 = ProjectHistogram(h_denominator8_2D, etamin, etamax, "h_denominator8_projected");
   
   TH1D* h_numerator1 = ProjectHistogram(h_numerator1_2D, etamin, etamax, "h_numerator1_projected");
   TH1D* h_numerator2 = ProjectHistogram(h_numerator2_2D, etamin, etamax, "h_numerator2_projected");
   TH1D* h_numerator3 = ProjectHistogram(h_numerator3_2D, etamin, etamax, "h_numerator3_projected");
   TH1D* h_numerator4 = ProjectHistogram(h_numerator4_2D, etamin, etamax, "h_numerator4_projected");
   TH1D* h_numerator5 = ProjectHistogram(h_numerator5_2D, etamin, etamax, "h_numerator5_projected");
   TH1D* h_numerator6 = ProjectHistogram(h_numerator6_2D, etamin, etamax, "h_numerator6_projected");
   TH1D* h_numerator7 = ProjectHistogram(h_numerator7_2D, etamin, etamax, "h_numerator7_projected");
   TH1D* h_numerator8 = ProjectHistogram(h_numerator8_2D, etamin, etamax, "h_numerator8_projected");
   
   
   
   int SamplesSizeMC = 8; //How many samples
   int SamplesSizeData = 2; //PFJet40 and PFJet60
   
   TH1D* NumeratorHistogramsMC[8]   = {h_numerator1,h_numerator2,h_numerator3,h_numerator4,h_numerator5,h_numerator6,h_numerator7,h_numerator8};
   TH1D* DenominatorHistogramsMC[8] = {h_denominator1,h_denominator2,h_denominator3,h_denominator4,h_denominator5,h_denominator6,h_denominator7,h_denominator8};
   
   TH1D* NumeratorHistogramsData[2]   = {h_numeratorDATA_PFJet40,h_numeratorDATA_PFJet60};
   TH1D* DenominatorHistogramsData[2] = {h_denominatorDATA_PFJet40,h_denominatorDATA_PFJet60};

   // adding the MC histograms to only one
   int LowerLimitBinMC = 1;
   int UpperLimitBinMC = h_denominator1 -> GetNbinsX();
   int SamplesLimitsMC[9] = {LowerLimitBinMC,72,108,175,271,420,588,850,UpperLimitBinMC+1}; //array to introduce the limits in which the samples will be read and the efficiency calculated
   
   //use histograms below if you want to use default binning
   //TH1D *h_numeratorMC = new TH1D("h_numeratorMC", "h_numeratorMC", UpperLimitBinMC, 0, UpperLimitBinMC);
   //TH1D *h_denominatorMC = new TH1D("h_denominatorMC", "h_denominatorMC", UpperLimitBinMC, 0, UpperLimitBinMC);
   
   Double_t *bineo;
   Double_t bineo_array [21] = {30,35,40,45,50,55,60,65,70,75,80,85,90,95,110,125,140,160,180,200,300};
   bineo = bineo_array;
   
   TH1D *h_numeratorMC = new TH1D("h_numeratorMC", "h_numeratorMC", 20, bineo);
   TH1D *h_denominatorMC = new TH1D("h_denominatorMC", "h_denominatorMC", 20, bineo);
   
   
   for(int i = 0; i < SamplesSizeMC; i++)
   {
       //FillHistogramfromHistogram(h_numeratorMC,NumeratorHistogramsMC[i],SamplesLimitsMC[i],SamplesLimitsMC[i+1]);
       //FillHistogramfromHistogram(h_denominatorMC,DenominatorHistogramsMC[i],SamplesLimitsMC[i],SamplesLimitsMC[i+1]);
       FillHistogramfromHistogram_newbinning(h_numeratorMC,NumeratorHistogramsMC[i],SamplesLimitsMC[i],SamplesLimitsMC[i+1]);
       FillHistogramfromHistogram_newbinning(h_denominatorMC,DenominatorHistogramsMC[i],SamplesLimitsMC[i],SamplesLimitsMC[i+1]);
   }
   
   //h_numeratorMC->Rebin(5);
   //h_denominatorMC->Rebin(5);
   
   // adding the Data histograms to only one
   int LowerLimitBinData = 1;
   int UpperLimitBinData = h_numeratorDATA_PFJet60 -> GetNbinsX();
   int SamplesLimitsData[3] = {LowerLimitBinData,111,UpperLimitBinData+1}; //array to introduce the limits in which the samples will be read and the efficiency calculated
   
   //TH1D *h_numeratorData = new TH1D("h_numeratorData", "h_numeratorData", UpperLimitBinData, 0, UpperLimitBinData);
   //TH1D *h_denominatorData = new TH1D("h_denominatorData", "h_denominatorData", UpperLimitBinData, 0, UpperLimitBinData);
   
   TH1D *h_numeratorData = new TH1D("h_numeratorData", "h_numeratorData", 20, bineo);
   TH1D *h_denominatorData = new TH1D("h_denominatorData", "h_denominatorData", 20, bineo);
   
   for(int i = 0; i < SamplesSizeData; i++)
   {
       //FillHistogramfromHistogram(h_numeratorData,NumeratorHistogramsData[i],SamplesLimitsData[i],SamplesLimitsData[i+1]);
       //FillHistogramfromHistogram(h_denominatorData,DenominatorHistogramsData[i],SamplesLimitsData[i],SamplesLimitsData[i+1]);
       FillHistogramfromHistogram_newbinning(h_numeratorData,NumeratorHistogramsData[i],SamplesLimitsData[i],SamplesLimitsData[i+1]);
       FillHistogramfromHistogram_newbinning(h_denominatorData,DenominatorHistogramsData[i],SamplesLimitsData[i],SamplesLimitsData[i+1]);
   }
   //h_numeratorData->Rebin(5);
   //h_denominatorData->Rebin(5);
   
    
   // calculate the efficiency of MC
   TGraphAsymmErrors* g_effMC = new TGraphAsymmErrors(h_numeratorMC, h_denominatorMC,"cl=0.683 b(1,1) mode");
   g_effMC -> SetMarkerStyle(20);
   g_effMC -> SetTitle("QCD");
   g_effMC -> GetXaxis()->SetRangeUser(0, 300);
   
      // calculate the efficiency of Data
   TGraphAsymmErrors* g_effData = new TGraphAsymmErrors(h_numeratorData, h_denominatorData,"cl=0.683 b(1,1) mode");
   g_effData -> SetMarkerStyle(20);
   g_effData -> SetMarkerColor(kRed);
   g_effData -> SetLineColor(kRed);
   g_effData -> SetTitle("Data CDEF");
   g_effData -> GetXaxis()->SetRangeUser(0, 300);

   C -> cd(1);  
   
   /*->Draw();
   h_denominatorData-> SetMarkerColor(kRed);
   h_denominatorData-> SetLineColor(kRed);
   h_denominatorData->Draw("same");*/
   
   TMultiGraph *mg = new TMultiGraph();
   if (etamax == -1)
   mg->SetTitle(Form("JKTE, %g<|#eta|<Inf",etamin));
   else
   mg->SetTitle(Form("JKTE, %g<|#eta|<%g",etamin,etamax));
   mg->Add(g_effData);
   mg->Add(g_effMC);
   mg->GetHistogram()->GetYaxis()->SetRangeUser(0,1.1);
   mg->GetHistogram()->GetXaxis()->SetRangeUser(30, 300);
   mg->GetHistogram()->GetXaxis()->SetTitle("p_{T}^{probe} [GeV]");
   mg->GetHistogram()->GetYaxis()->SetTitle("efficiency");
   mg->Draw("AP");
   gPad->SetGrid(1,1); 
   gPad->BuildLegend();
   
   //h_denominatorMC->Draw("same");
   //h_numeratorMC->Draw();
   
   C -> cd(2);
   C -> SetGrid();   
   TGraphAsymmErrors *ratioeff = DivideTGraphsErrors(g_effData, g_effMC);
   ratioeff -> GetXaxis() -> SetRangeUser(30,300);
   ratioeff -> GetYaxis() -> SetRangeUser(0.1,1.1);
   ratioeff -> SetMarkerStyle(20);
   ratioeff -> SetTitle ("");
   ratioeff -> GetXaxis() -> SetTitle ("p_{T}^{probe} [GeV]");
   ratioeff -> GetYaxis() -> SetTitle ("scale factor");
   ratioeff -> Draw("AP");
   
   TF1 *fa1 = new TF1("fa1","[0]*erf([1]*x-[2])",50,300);
   fa1 -> SetParameters(1,0.05,1);
   ratioeff -> Fit(fa1,"QNR");
   
   TMultiGraph *mg1 = new TMultiGraph();
   mg1->Add(ratioeff);
   mg1->GetHistogram()->GetYaxis()->SetRangeUser(0.1,1.1);
   mg1->GetHistogram()->GetXaxis()->SetRangeUser(30,300);
   mg1->GetHistogram()->GetXaxis()->SetTitle("p_{T}^{probe} [GeV]");
   mg1->GetHistogram()->GetYaxis()->SetTitle("scale factor");
   //mg1->Draw("AP");
   gPad->SetGrid(1,1);
   fa1 -> Draw("same"); 

   return 0;
}

//function for projectiong each MC sample numerator and denominator //ARREGLAR
TH1D* ProjectHistogram(TH2F* h, double etamin, double etamax, char name[])
{
   //declare histograms and variables
   TH1D *hprojected;
   char name1[1000];
   char name2[1000];
   strcpy (name1, name);
   strcpy (name2, name);  
   strcat(name1, "1");
   strcat(name2, "2");  
   double Lowedgeup, Lowedgedown;
   double half_bin_width = 0.5 * (h -> GetYaxis() -> GetBinWidth(1));
   
   if (etamin == 0)
      {
         if (etamax == -1)
         {
            int LowerBin = 1;
            int UpperBin = h -> GetNbinsY();

            hprojected = h -> ProjectionX(name, LowerBin, UpperBin, "e");

         }

         else
         {
            int NbinX = h -> GetNbinsX();
            int LowerBin = int(h -> FindBin(0,-1*etamax + half_bin_width)/NbinX);
            int UpperBin = int(h -> FindBin(0,etamax - half_bin_width)/NbinX);
            
            //Lowedgeup = h -> GetYaxis() -> GetBinLowEdge(UpperBin);
            //Lowedgedown = h -> GetYaxis() -> GetBinLowEdge(LowerBin);
            
            hprojected = h -> ProjectionX(name, LowerBin, UpperBin, "e");
            
            //cout<< name << " Low_Edge_up "<< Lowedgeup << " Low_Edge_down "<< Lowedgedown<<endl;
         }
      }

   else 	
      {
         if (etamax == -1) //revisar signo half_bin_width
         {  
            int NbinX = h -> GetNbinsX();
            int LowerBin1 = h -> FindBin(0,etamin + half_bin_width)/NbinX;
            int UpperBin1 = h -> GetNbinsY();
            int UpperBin2 = h -> FindBin(0,-1*etamin - half_bin_width)/NbinX;
            int LowerBin2 = 1;

            TH1D *hprojected1 = h -> ProjectionX(name1, LowerBin1, UpperBin1, "e");
            TH1D *hprojected2 = h -> ProjectionX(name2, LowerBin2, UpperBin2, "e");

            hprojected = hprojected1;
            hprojected -> Add(hprojected2);
         }
         
         else
         {   
            int NbinX = h -> GetNbinsX();
            int LowerBin1 = int(h -> FindBin(0,etamin+half_bin_width)/NbinX);
            int UpperBin1 = int(h -> FindBin(0,etamax-half_bin_width)/NbinX);
            int UpperBin2 = int(h -> FindBin(0,-1*etamin-half_bin_width)/NbinX);
            int LowerBin2 = int(h -> FindBin(0,-1*etamax+half_bin_width)/NbinX);

            TH1D *hprojected1 = h -> ProjectionX(name1, LowerBin1, UpperBin1, "e");
            TH1D *hprojected2 = h -> ProjectionX(name2, LowerBin2, UpperBin2, "e");

            hprojected = hprojected1;
            hprojected -> Add(hprojected2);
   
         }
      }

   //hprojected -> Rebin(5);
   return hprojected;

}


//function for proper treatment of errors in division of TGraphs
double ErrorDivision(double ea, double eb, double ValueA, double ValueB)
{
    double err = sqrt((1/(ValueB*ValueB))*(ea*ea+eb*eb*((ValueA*ValueA)/(ValueB*ValueB))));
    return err;
}


//This function divides two TGraphAsymmErrors that have the same number of points A/B
TGraphAsymmErrors* DivideTGraphsErrors(TGraphAsymmErrors* A, TGraphAsymmErrors* B)
{
    int nPoints = A -> GetN(); // number of points in the TGraphs

    double xA [nPoints], yA [nPoints];
    double xB [nPoints], yB [nPoints];
    double X [nPoints], Y[nPoints];
    double xerrlower[nPoints], xerrupper[nPoints], yerrlower[nPoints], yerrupper[nPoints];
    double x1a, x2a, y1a, y2a, x1b, x2b, y1b, y2b; //temporal variables to store the errors

    for(int i=1; i <= nPoints; ++i)
    {
       A -> GetPoint(i, xA[i-1], yA[i-1]);
       B -> GetPoint(i, xB[i-1], yB[i-1]);

       X[i-1] = xA[i-1];

       if (yB[i-1] != 0)
       Y[i-1] = yA[i-1]/yB[i-1];
       if (yB[i-1] == 0)
       Y[i-1] = 0;


       x1a = A -> GetErrorXlow(i);
       x2a = A -> GetErrorXhigh(i);
       y1a = A -> GetErrorYlow(i);
       y2a = A -> GetErrorYhigh(i);

       x1b = B -> GetErrorXlow(i);
       x2b = B -> GetErrorXhigh(i);
       y1b = B -> GetErrorYlow(i);
       y2b = B -> GetErrorYhigh(i);

       xerrlower[i-1] = ErrorDivision(x1a, x1b, xA[i-1], xB[i-1]);
       xerrupper[i-1] = ErrorDivision(x2a, x2b, xA[i-1], xB[i-1]);
       yerrlower[i-1] = ErrorDivision(y1a, y1b, yA[i-1], yB[i-1]);
       yerrupper[i-1] = ErrorDivision(y2a, y2b, yA[i-1], yB[i-1]);

    }

    TGraphAsymmErrors * result = new TGraphAsymmErrors(nPoints, X, Y, xerrlower, xerrupper, yerrlower, yerrupper);
    return result;

}

//use function if you want to keep default binning
void FillHistogramfromHistogram(TH1D* h1, TH1D* h2,int BinMin,int BinMax) //h1 is the one to be filled and h2 is the one with content. BinMin included, BinMax not included.
{
   Double_t BinContent;
   Double_t BinError;
   
   for (int i=BinMin; i<BinMax; i++)
   {
      BinContent = h2 -> GetBinContent(i);
      BinError = h2 -> GetBinError(i);
      
      h1 -> SetBinContent(i, BinContent);
      h1 -> SetBinError(i, BinError);
   }
   
   return;
}

void FillHistogramfromHistogram_newbinning(TH1D* h1, TH1D* h2,int BinMin,int BinMax) //h1 is the one to be filled and h2 is the one with content. BinMin included, BinMax not included.
{
   Double_t content = 0;
   Double_t newcontent = 0;
   Double_t error;
   Double_t BinContent [20] = {0};
   Double_t BinError [20] = {0};
   
   Double_t b [21] = {30,35,40,45,50,55,60,65,70,75,80,85,90,95,110,125,140,160,180,200,300};
   
   for (int i=BinMin; i<BinMax; i++)
   {
      content = h2 -> GetBinContent(i);
      
      for(int j=0; j<20; j++)
      {
         if (i < b[j+1] && i >= b[j] )
         BinContent[j]+=content;
      }
      
   }
   
   for (int k=0; k<20; k++)
   {
      newcontent = BinContent[k] + h1 -> GetBinContent(k+1);
      error = sqrt(newcontent);
      
      h1 -> SetBinContent(k+1, newcontent);
      h1 -> SetBinError(k+1, error);
   }
   
   return;
}




