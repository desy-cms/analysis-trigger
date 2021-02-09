TGraphAsymmErrors* DivideTGraphsErrors(TGraphAsymmErrors* A, TGraphAsymmErrors* B);
double ErrorDivision(double ea, double eb, double ValueA, double ValueB);

int eff()
{
   auto C = new TCanvas("C","Canvas",1000,1000);
   C -> Divide (1,2);

   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
   
   Double_t Luminosity_Total =36.528; //in fb=^-1

   // open the root file corresponding to HT100to200
   TFile * f1 = new TFile("my1.root");
   // get denominator histograms
   TH1F * h_denominator1_1 = (TH1F*) f1 -> Get("Probes 0<n<1/pt_jet2");
   TH1F * h_denominator1_2 = (TH1F*) f1 -> Get("Probes 1<n<1.4/pt_jet2");
   TH1F * h_denominator1_3 = (TH1F*) f1 -> Get("Probes 1.4<n<2.2/pt_jet2");
   // get numerator histograms
   TH1F * h_numerator1_1  = (TH1F*) f1 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_numerator1_2  = (TH1F*) f1 -> Get("Probes with matching 1<n<1.4/pt_jet2");
   TH1F * h_numerator1_3  = (TH1F*) f1 -> Get("Probes with matching 1.4<n<2.2/pt_jet2");
   //get parameters
   Double_t Cross_section_1= 23700000;
   TH1F * Workflow1 = (TH1F*) f1 -> Get("workflow;1/Workflow #1");
   Int_t Nevents1 = Workflow1->GetBinContent(2);
   // Rebinning
   h_denominator1_1 -> Rebin(10);
   h_denominator1_2 -> Rebin(10);
   h_denominator1_3 -> Rebin(10);
   h_numerator1_1 -> Rebin(10);
   h_numerator1_2 -> Rebin(10);
   h_numerator1_3 -> Rebin(10);
   // total numerator and denominator for this HT
   TH1F * h_numerator1_total = h_numerator1_1;
   TH1F * h_denominator1_total = h_denominator1_1;
   h_denominator1_total -> Add(h_denominator1_2);
   h_denominator1_total -> Add(h_denominator1_3);
   h_numerator1_total -> Add(h_numerator1_2);
   h_numerator1_total -> Add(h_numerator1_3);
   


   // open the root file corresponding to HT200to300
   TFile * f2 = new TFile("my2.root");
   // get denominator histograms
   TH1F * h_denominator2_1 = (TH1F*) f2 -> Get("Probes 0<n<1/pt_jet2");
   TH1F * h_denominator2_2 = (TH1F*) f2 -> Get("Probes 1<n<1.4/pt_jet2");
   TH1F * h_denominator2_3 = (TH1F*) f2 -> Get("Probes 1.4<n<2.2/pt_jet2");
   // get numerator histograms
   TH1F * h_numerator2_1  = (TH1F*) f2 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_numerator2_2  = (TH1F*) f2 -> Get("Probes with matching 1<n<1.4/pt_jet2");
   TH1F * h_numerator2_3  = (TH1F*) f2 -> Get("Probes with matching 1.4<n<2.2/pt_jet2");
   //get parameters
   Double_t Cross_section_2= 1547000;
   TH1F * Workflow2 = (TH1F*) f2 -> Get("workflow;1/Workflow #1");
   Int_t Nevents2 = Workflow2->GetBinContent(2);
   // Rebinning
   h_denominator2_1 -> Rebin(10);
   h_denominator2_2 -> Rebin(10);
   h_denominator2_3 -> Rebin(10);
   h_numerator2_1 -> Rebin(10);
   h_numerator2_2 -> Rebin(10);
   h_numerator2_3 -> Rebin(10);
   // total numerator and denominator for this HT
   TH1F * h_numerator2_total = h_numerator2_1;
   TH1F * h_denominator2_total = h_denominator2_1;
   h_denominator2_total -> Add(h_denominator2_2);
   h_denominator2_total -> Add(h_denominator2_3);
   h_numerator2_total -> Add(h_numerator2_2);
   h_numerator2_total -> Add(h_numerator2_3);


   // open the root file corresponding to HT300to500
   TFile * f3 = new TFile("my3.root");
   // get denominator histograms
   TH1F * h_denominator3_1 = (TH1F*) f3 -> Get("Probes 0<n<1/pt_jet2");
   TH1F * h_denominator3_2 = (TH1F*) f3 -> Get("Probes 1<n<1.4/pt_jet2");
   TH1F * h_denominator3_3 = (TH1F*) f3 -> Get("Probes 1.4<n<2.2/pt_jet2");
   // get numerator histograms
   TH1F * h_numerator3_1  = (TH1F*) f3 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_numerator3_2  = (TH1F*) f3 -> Get("Probes with matching 1<n<1.4/pt_jet2");
   TH1F * h_numerator3_3  = (TH1F*) f3 -> Get("Probes with matching 1.4<n<2.2/pt_jet2");
   //get parameters
   Double_t Cross_section_3= 322600;
   TH1F * Workflow3 = (TH1F*) f3 -> Get("workflow;1/Workflow #1");
   Int_t Nevents3 = Workflow3->GetBinContent(2);
   // Rebinning
   h_denominator3_1 -> Rebin(10);
   h_denominator3_2 -> Rebin(10);
   h_denominator3_3 -> Rebin(10);
   h_numerator3_1 -> Rebin(10);
   h_numerator3_2 -> Rebin(10);
   h_numerator3_3 -> Rebin(10);
   // total numerator and denominator for this HT
   TH1F * h_numerator3_total = h_numerator3_1;
   TH1F * h_denominator3_total = h_denominator3_1;
   h_denominator3_total -> Add(h_denominator3_2);
   h_denominator3_total -> Add(h_denominator3_3);
   h_numerator3_total -> Add(h_numerator3_2);
   h_numerator3_total -> Add(h_numerator3_3);



   // open the root file corresponding to HT500to700
   TFile * f4 = new TFile("my4.root");
   // get denominator histograms
   TH1F * h_denominator4_1 = (TH1F*) f4 -> Get("Probes 0<n<1/pt_jet2");
   TH1F * h_denominator4_2 = (TH1F*) f4 -> Get("Probes 1<n<1.4/pt_jet2");
   TH1F * h_denominator4_3 = (TH1F*) f4 -> Get("Probes 1.4<n<2.2/pt_jet2");
   // get numerator histograms
   TH1F * h_numerator4_1  = (TH1F*) f4 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_numerator4_2  = (TH1F*) f4 -> Get("Probes with matching 1<n<1.4/pt_jet2");
   TH1F * h_numerator4_3  = (TH1F*) f4 -> Get("Probes with matching 1.4<n<2.2/pt_jet2");
   //get parameters
   Double_t Cross_section_4= 29980;
   TH1F * Workflow4 = (TH1F*) f4 -> Get("workflow;1/Workflow #1");
   Int_t Nevents4 = Workflow4->GetBinContent(2);
   // Rebinning
   h_denominator4_1 -> Rebin(10);
   h_denominator4_2 -> Rebin(10);
   h_denominator4_3 -> Rebin(10);
   h_numerator4_1 -> Rebin(10);
   h_numerator4_2 -> Rebin(10);
   h_numerator4_3 -> Rebin(10);
   // total numerator and denominator for this HT
   TH1F * h_numerator4_total = h_numerator4_1;
   TH1F * h_denominator4_total = h_denominator4_1;
   h_denominator4_total -> Add(h_denominator4_2);
   h_denominator4_total -> Add(h_denominator4_3);
   h_numerator4_total -> Add(h_numerator4_2);
   h_numerator4_total -> Add(h_numerator4_3);


   // open the root file corresponding to HT700to1000
   TFile * f5 = new TFile("my5.root");
   // get denominator histograms
   TH1F * h_denominator5_1 = (TH1F*) f5 -> Get("Probes 0<n<1/pt_jet2");
   TH1F * h_denominator5_2 = (TH1F*) f5 -> Get("Probes 1<n<1.4/pt_jet2");
   TH1F * h_denominator5_3 = (TH1F*) f5 -> Get("Probes 1.4<n<2.2/pt_jet2");
   // get numerator histograms
   TH1F * h_numerator5_1  = (TH1F*) f5 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_numerator5_2  = (TH1F*) f5 -> Get("Probes with matching 1<n<1.4/pt_jet2");
   TH1F * h_numerator5_3  = (TH1F*) f5 -> Get("Probes with matching 1.4<n<2.2/pt_jet2");
   //get parameters
   Double_t Cross_section_5= 6334;
   TH1F * Workflow5 = (TH1F*) f5 -> Get("workflow;1/Workflow #1");
   Int_t Nevents5 = Workflow5->GetBinContent(2);
   // Rebinning
   h_denominator5_1 -> Rebin(10);
   h_denominator5_2 -> Rebin(10);
   h_denominator5_3 -> Rebin(10);
   h_numerator5_1 -> Rebin(10);
   h_numerator5_2 -> Rebin(10);
   h_numerator5_3 -> Rebin(10);
   // total numerator and denominator for this HT
   TH1F * h_numerator5_total = h_numerator5_1;
   TH1F * h_denominator5_total = h_denominator5_1;
   h_denominator5_total -> Add(h_denominator5_2);
   h_denominator5_total -> Add(h_denominator5_3);
   h_numerator5_total -> Add(h_numerator5_2);
   h_numerator5_total -> Add(h_numerator5_3);


   // open the root file corresponding to HT1000to1500
   TFile * f6 = new TFile("my6.root");
   // get denominator histograms
   TH1F * h_denominator6_1 = (TH1F*) f6 -> Get("Probes 0<n<1/pt_jet2");
   TH1F * h_denominator6_2 = (TH1F*) f6 -> Get("Probes 1<n<1.4/pt_jet2");
   TH1F * h_denominator6_3 = (TH1F*) f6 -> Get("Probes 1.4<n<2.2/pt_jet2");
   // get numerator histograms
   TH1F * h_numerator6_1  = (TH1F*) f6 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_numerator6_2  = (TH1F*) f6 -> Get("Probes with matching 1<n<1.4/pt_jet2");
   TH1F * h_numerator6_3  = (TH1F*) f6 -> Get("Probes with matching 1.4<n<2.2/pt_jet2");
   //get parameters
   Double_t Cross_section_6= 1088;
   TH1F * Workflow6 = (TH1F*) f6 -> Get("workflow;1/Workflow #1");
   Int_t Nevents6 = Workflow6->GetBinContent(2);
   // Rebinning
   h_denominator6_1 -> Rebin(10);
   h_denominator6_2 -> Rebin(10);
   h_denominator6_3 -> Rebin(10);
   h_numerator6_1 -> Rebin(10);
   h_numerator6_2 -> Rebin(10);
   h_numerator6_3 -> Rebin(10);
   // total numerator and denominator for this HT
   TH1F * h_numerator6_total = h_numerator6_1;
   TH1F * h_denominator6_total = h_denominator6_1;
   h_denominator6_total -> Add(h_denominator6_2);
   h_denominator6_total -> Add(h_denominator6_3);
   h_numerator6_total -> Add(h_numerator6_2);
   h_numerator6_total -> Add(h_numerator6_3);


   // open the root file corresponding to HT1500to2000
   TFile * f7 = new TFile("my7.root");
   // get denominator histograms
   TH1F * h_denominator7_1 = (TH1F*) f7 -> Get("Probes 0<n<1/pt_jet2");
   TH1F * h_denominator7_2 = (TH1F*) f7 -> Get("Probes 1<n<1.4/pt_jet2");
   TH1F * h_denominator7_3 = (TH1F*) f7 -> Get("Probes 1.4<n<2.2/pt_jet2");
   // get numerator histograms
   TH1F * h_numerator7_1  = (TH1F*) f7 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_numerator7_2  = (TH1F*) f7 -> Get("Probes with matching 1<n<1.4/pt_jet2");
   TH1F * h_numerator7_3  = (TH1F*) f7 -> Get("Probes with matching 1.4<n<2.2/pt_jet2");
   //get parameters
   Double_t Cross_section_7= 99.11;
   TH1F * Workflow7 = (TH1F*) f7 -> Get("workflow;1/Workflow #1");
   Int_t Nevents7 = Workflow7->GetBinContent(2);
   // Rebinning
   h_denominator7_1 -> Rebin(10);
   h_denominator7_2 -> Rebin(10);
   h_denominator7_3 -> Rebin(10);
   h_numerator7_1 -> Rebin(10);
   h_numerator7_2 -> Rebin(10);
   h_numerator7_3 -> Rebin(10);
   // total numerator and denominator for this HT
   TH1F * h_numerator7_total = h_numerator7_1;
   TH1F * h_denominator7_total = h_denominator7_1;
   h_denominator7_total -> Add(h_denominator7_2);
   h_denominator7_total -> Add(h_denominator7_3);
   h_numerator7_total -> Add(h_numerator7_2);
   h_numerator7_total -> Add(h_numerator7_3);


   // open the root file corresponding to HT2000toInf
   TFile * f8 = new TFile("my8.root");
   // get denominator histograms
   TH1F * h_denominator8_1 = (TH1F*) f8 -> Get("Probes 0<n<1/pt_jet2");
   TH1F * h_denominator8_2 = (TH1F*) f8 -> Get("Probes 1<n<1.4/pt_jet2");
   TH1F * h_denominator8_3 = (TH1F*) f8 -> Get("Probes 1.4<n<2.2/pt_jet2");
   // get numerator histograms
   TH1F * h_numerator8_1  = (TH1F*) f8 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_numerator8_2  = (TH1F*) f8 -> Get("Probes with matching 1<n<1.4/pt_jet2");
   TH1F * h_numerator8_3  = (TH1F*) f8 -> Get("Probes with matching 1.4<n<2.2/pt_jet2");
   //get parameters
   Double_t Cross_section_8= 20.23;
   TH1F * Workflow8 = (TH1F*) f8 -> Get("workflow;1/Workflow #1");
   Int_t Nevents8 = Workflow8->GetBinContent(2);
   // Rebinning
   h_denominator8_1 -> Rebin(10);
   h_denominator8_2 -> Rebin(10);
   h_denominator8_3 -> Rebin(10);
   h_numerator8_1 -> Rebin(10);
   h_numerator8_2 -> Rebin(10);
   h_numerator8_3 -> Rebin(10);
   // total numerator and denominator for this HT
   TH1F * h_numerator8_total = h_numerator8_1;
   TH1F * h_denominator8_total = h_denominator8_1;
   h_denominator8_total -> Add(h_denominator8_2);
   h_denominator8_total -> Add(h_denominator8_3);
   h_numerator8_total -> Add(h_numerator8_2);
   h_numerator8_total -> Add(h_numerator8_3);


   //Calculate Scale Factors
   Double_t ScaleFactor1, ScaleFactor2, ScaleFactor3, ScaleFactor4, ScaleFactor5, ScaleFactor6, ScaleFactor7, ScaleFactor8 ;

   ScaleFactor1 = Luminosity_Total*Cross_section_1/Nevents1*1000;//multiply by 1000 to take from pb to fb
   ScaleFactor2 = Luminosity_Total*Cross_section_2/Nevents2*1000;
   ScaleFactor3 = Luminosity_Total*Cross_section_3/Nevents3*1000;
   ScaleFactor4 = Luminosity_Total*Cross_section_4/Nevents4*1000;
   ScaleFactor5 = Luminosity_Total*Cross_section_5/Nevents5*1000;
   ScaleFactor6 = Luminosity_Total*Cross_section_6/Nevents6*1000;
   ScaleFactor7 = Luminosity_Total*Cross_section_7/Nevents7*1000;
   ScaleFactor8 = Luminosity_Total*Cross_section_8/Nevents8*1000;

   //Scale the histograms
   h_numerator1_total -> Scale(ScaleFactor1);
   h_numerator2_total -> Scale(ScaleFactor2);
   h_numerator3_total -> Scale(ScaleFactor3);
   h_numerator4_total -> Scale(ScaleFactor4);
   h_numerator5_total -> Scale(ScaleFactor5);
   h_numerator6_total -> Scale(ScaleFactor6);
   h_numerator7_total -> Scale(ScaleFactor7);
   h_numerator8_total -> Scale(ScaleFactor8);
   h_denominator1_total -> Scale(ScaleFactor1);
   h_denominator2_total -> Scale(ScaleFactor2);
   h_denominator3_total -> Scale(ScaleFactor3);
   h_denominator4_total -> Scale(ScaleFactor4);
   h_denominator5_total -> Scale(ScaleFactor5);
   h_denominator6_total -> Scale(ScaleFactor6);
   h_denominator7_total -> Scale(ScaleFactor7);
   h_denominator8_total -> Scale(ScaleFactor8);

   //Adding the histograms
   TH1F * h_numerator_total = h_numerator1_total;
   TH1F * h_denominator_total = h_denominator1_total;
   h_numerator_total -> Add(h_numerator2_total);
   h_numerator_total -> Add(h_numerator3_total);
   h_numerator_total -> Add(h_numerator4_total);
   h_numerator_total -> Add(h_numerator5_total);
   h_numerator_total -> Add(h_numerator6_total);
   h_numerator_total -> Add(h_numerator7_total);
   h_numerator_total -> Add(h_numerator8_total);
   h_denominator_total -> Add(h_denominator2_total);
   h_denominator_total -> Add(h_denominator3_total);
   h_denominator_total -> Add(h_denominator4_total);
   h_denominator_total -> Add(h_denominator5_total);
   h_denominator_total -> Add(h_denominator6_total);
   h_denominator_total -> Add(h_denominator7_total);
   h_denominator_total -> Add(h_denominator8_total);


   // open the root file corresponding to Data
   TFile * fDATA = new TFile("myDATA.root");
   // get denominator histograms
   TH1F * h_denominatorDATA_1 = (TH1F*) fDATA -> Get("Probes 0<n<1/pt_jet2");
   TH1F * h_denominatorDATA_2 = (TH1F*) fDATA -> Get("Probes 1<n<1.4/pt_jet2");
   TH1F * h_denominatorDATA_3 = (TH1F*) fDATA -> Get("Probes 1.4<n<2.2/pt_jet2");
   // get numerator histograms
   TH1F * h_numeratorDATA_1  = (TH1F*) fDATA -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_numeratorDATA_2  = (TH1F*) fDATA -> Get("Probes with matching 1<n<1.4/pt_jet2");
   TH1F * h_numeratorDATA_3  = (TH1F*) fDATA -> Get("Probes with matching 1.4<n<2.2/pt_jet2");

   // Rebinning
   h_denominatorDATA_1 -> Rebin(10);
   h_denominatorDATA_2 -> Rebin(10);
   h_denominatorDATA_3 -> Rebin(10);
   h_numeratorDATA_1 -> Rebin(10);
   h_numeratorDATA_2 -> Rebin(10);
   h_numeratorDATA_3 -> Rebin(10);

   // total numerator and denominator for DATA
   TH1F * h_numeratorDATA_total = h_numeratorDATA_1; 
   TH1F * h_denominatorDATA_total = h_denominatorDATA_1;
   h_denominatorDATA_total -> Add(h_denominatorDATA_2);
   h_denominatorDATA_total -> Add(h_denominatorDATA_3);
   h_numeratorDATA_total -> Add(h_numeratorDATA_2);
   h_numeratorDATA_total -> Add(h_numeratorDATA_3);
   
   int NbinsA = h_numeratorDATA_total -> GetNbinsX();
   int NbinsB = h_denominatorDATA_total -> GetNbinsX();
   cout <<"\nNbins numerator : "<<NbinsA<<"\n";
   cout <<"\nNbins denominator : "<<NbinsB<<"\n";


   // total eff
   TGraphAsymmErrors * g_eff = new TGraphAsymmErrors(h_numerator_total, h_denominator_total,"cl=0.683 b(1,1) mode");
   TGraphAsymmErrors * g_effDATA = new TGraphAsymmErrors(h_numeratorDATA_total, h_denominatorDATA_total,"cl=0.683 b(1,1) mode");
   
   //Setting properties
   g_eff -> SetMarkerStyle(20);
   g_eff -> SetTitle("QCD");
  // g_eff -> GetXaxis()->SetRangeUser(0, 300);
   g_effDATA -> SetMarkerColor(kRed);
   g_effDATA -> SetLineColor(kRed);
   g_effDATA -> SetTitle("Data");
   g_effDATA -> SetMarkerStyle(kFullTriangleUp);
  // g_effDATA -> GetXaxis()->SetRangeUser(0, 300);
  

   //Drawing the two JKTE in a same plot
   C -> cd(1);
   TMultiGraph *mg = new TMultiGraph();
   mg->SetTitle("Jet Kinematic Trigger Efficiency");
   mg->Add(g_effDATA);
   //mg->Add(g_eff);
   mg->GetHistogram()->GetYaxis()->SetRangeUser(0,1.1);
   mg->GetHistogram()->GetXaxis()->SetRangeUser(30,1000);
   mg->Draw("AP");
   gPad->BuildLegend();
   
   

   C -> cd(2);
   TGraphAsymmErrors *ratioeff = DivideTGraphsErrors(g_effDATA, g_eff);
   ratioeff -> GetXaxis() -> SetRangeUser(30,1000);
   ratioeff -> GetYaxis() -> SetRangeUser(0.1,1.1);
   ratioeff -> SetTitle ("Scale Factor");
   ratioeff -> Draw ("AP");
   
   return 0;
}

//functiom for proper treatment of errors in division of TGraphs
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

       if(xA[i-1] != xB[i-1])
       cout<<"\nERROR XA != XB\n";

       X[i-1] = xA[i-1];

       if (yB[i-1] != 0)
       Y[i-1] = yA[i-1]/yB[i-1];

       if (yB[i-1] == 0)
       {
           if (yA[i-1] == 0)
               Y[i-1] = 0;
           else
               Y[i-1] = 0;
       }

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







