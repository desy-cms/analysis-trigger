TGraphAsymmErrors* DivideTGraphsErrors(TGraphAsymmErrors* A, TGraphAsymmErrors* B);
double ErrorDivision(double ea, double eb, double ValueA, double ValueB);

int eff1()
{

// USE THIS MACRO TO PLOT THE JET KINEMATIC TRIGGER EFFICIENCY FOR ALL ETA VALUES FROM 0.0 TO 1.0 CORRESPONDING TO THE BARREL REGION
   auto C = new TCanvas("C","Canvas",1000,1000);
   C -> Divide (1,2);

   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
   
   Double_t Luminosity_Total =36.528; //in fb=^-1

   //FOR DATA
   // open the root file corresponding to Data
   TFile * fDATA = new TFile("myData.root");
   // get denominator histograms
   TH1F * h_denominatorDATA = (TH1F*) fDATA -> Get("Probes 0<n<1/pt_jet2");
   // get numerator histograms
   TH1F * h_numeratorDATA  = (TH1F*) fDATA -> Get("Probes with matching 0<n<1/pt_jet2");

   // Rebinning
   h_denominatorDATA -> Rebin(10);
   h_numeratorDATA -> Rebin(10);


   // total eff for Data
   TGraphAsymmErrors * g_effDATA = new TGraphAsymmErrors(h_numeratorDATA, h_denominatorDATA,"cl=0.683 b(1,1) mode");
   
   //Setting properties of Data plots
   g_effDATA -> SetMarkerColor(kRed);
   g_effDATA -> SetLineColor(kRed);
   g_effDATA -> SetTitle("Data");
   g_effDATA -> SetMarkerStyle(kFullTriangleUp);
   g_effDATA -> GetXaxis()->SetRangeUser(0, 300);



   //FOR MONTE CARLO 

   // open the root file corresponding to HT100to200
   TFile * f1 = new TFile("my1.root");
   // get denominator and denominator histograms for total
   TH1F * h_numerator1  = (TH1F*) f1 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_denominator1 = (TH1F*) f1 -> Get("Probes 0<n<1/pt_jet2");
   //get parameters
   Double_t Cross_section_1= 23700000;
   TH1F * Workflow1 = (TH1F*) f1 -> Get("workflow;1/Workflow #1");
   Int_t Nevents1 = Workflow1->GetBinContent(2);
   // Rebinning
   h_numerator1 -> Rebin(10);
   h_denominator1 -> Rebin(10);


   // open the root file corresponding to HT200to300
   TFile * f2 = new TFile("my2.root");
   // get denominator and denominator histograms for total
   TH1F * h_numerator2  = (TH1F*) f2 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_denominator2 = (TH1F*) f2 -> Get("Probes 0<n<1/pt_jet2");
   //get parameters
   Double_t Cross_section_2= 1547000;
   TH1F * Workflow2 = (TH1F*) f2 -> Get("workflow;1/Workflow #1");
   Int_t Nevents2 = Workflow2->GetBinContent(2);
   // Rebinning
   h_numerator2 -> Rebin(10);
   h_denominator2 -> Rebin(10);

   // open the root file corresponding to HT300to500
   TFile * f3 = new TFile("my3.root");
   // get denominator and denominator histograms for total
   TH1F * h_numerator3  = (TH1F*) f3 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_denominator3 = (TH1F*) f3 -> Get("Probes 0<n<1/pt_jet2");
   //get parameters
   Double_t Cross_section_3= 322600;
   TH1F * Workflow3 = (TH1F*) f3 -> Get("workflow;1/Workflow #1");
   Int_t Nevents3 = Workflow3->GetBinContent(2);
   // Rebinning
   h_numerator3 -> Rebin(10);
   h_denominator3 -> Rebin(10);

   // open the root file corresponding to HT500to700
   TFile * f4 = new TFile("my4.root");
   // get denominator and denominator histograms for total
   TH1F * h_numerator4  = (TH1F*) f4 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_denominator4 = (TH1F*) f4 -> Get("Probes 0<n<1/pt_jet2");   
   //get parameters
   Double_t Cross_section_4= 29980;
   TH1F * Workflow4 = (TH1F*) f4 -> Get("workflow;1/Workflow #1");
   Int_t Nevents4 = Workflow4->GetBinContent(2);
   // Rebinning
   h_numerator4 ->  Rebin(10);
   h_denominator4 -> Rebin(10);

   // open the root file corresponding to HT700to1000
   TFile * f5 = new TFile("my5.root");
   // get denominator and denominator histograms for total
   TH1F * h_numerator5  = (TH1F*) f5 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_denominator5 = (TH1F*) f5 -> Get("Probes 0<n<1/pt_jet2");
   // get denominator histograms
   //get parameters
   Double_t Cross_section_5= 6334;
   TH1F * Workflow5 = (TH1F*) f5 -> Get("workflow;1/Workflow #1");
   Int_t Nevents5 = Workflow5->GetBinContent(2);
   // Rebinning
   h_numerator5 -> Rebin(10);
   h_denominator5 -> Rebin(10);

   // open the root file corresponding to HT1000to1500
   TFile * f6 = new TFile("my6.root");
   // get denominator and denominator histograms for total
   TH1F * h_numerator6  = (TH1F*) f6 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_denominator6 = (TH1F*) f6 -> Get("Probes 0<n<1/pt_jet2");
   //get parameters
   Double_t Cross_section_6= 1088;
   TH1F * Workflow6 = (TH1F*) f6 -> Get("workflow;1/Workflow #1");
   Int_t Nevents6 = Workflow6->GetBinContent(2);
   // Rebinning
   h_numerator6 -> Rebin(10);
   h_denominator6 -> Rebin(10);

   // open the root file corresponding to HT1500to2000
   TFile * f7 = new TFile("my7.root");
   // get denominator and denominator histograms for total
   TH1F * h_numerator7  = (TH1F*) f7 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_denominator7 = (TH1F*) f7 -> Get("Probes 0<n<1/pt_jet2");
   //get parameters
   Double_t Cross_section_7= 99.11;
   TH1F * Workflow7 = (TH1F*) f7 -> Get("workflow;1/Workflow #1");
   Int_t Nevents7 = Workflow7->GetBinContent(2);
   // Rebinning
   h_numerator7 -> Rebin(10);
   h_denominator7 -> Rebin(10);
   
   // open the root file corresponding to HT2000toInf
   TFile * f8 = new TFile("my8.root");
   // get denominator and denominator histograms for total
   TH1F * h_numerator8  = (TH1F*) f8 -> Get("Probes with matching 0<n<1/pt_jet2");
   TH1F * h_denominator8 = (TH1F*) f8 -> Get("Probes 0<n<1/pt_jet2");
   //get parameters
   Double_t Cross_section_8= 20.23;
   TH1F * Workflow8 = (TH1F*) f8 -> Get("workflow;1/Workflow #1");
   Int_t Nevents8 = Workflow8->GetBinContent(2);
   // Rebinning
   h_numerator8 -> Rebin(10);
   h_denominator8 -> Rebin(10);
   
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
   h_numerator1 -> Scale(ScaleFactor1);
   h_numerator2 -> Scale(ScaleFactor2);
   h_numerator3 -> Scale(ScaleFactor3);
   h_numerator4 -> Scale(ScaleFactor4);
   h_numerator5 -> Scale(ScaleFactor5);
   h_numerator6 -> Scale(ScaleFactor6);
   h_numerator7 -> Scale(ScaleFactor7);
   h_numerator8 -> Scale(ScaleFactor8);
   h_denominator1 -> Scale(ScaleFactor1);
   h_denominator2 -> Scale(ScaleFactor2);
   h_denominator3 -> Scale(ScaleFactor3);
   h_denominator4 -> Scale(ScaleFactor4);
   h_denominator5 -> Scale(ScaleFactor5);
   h_denominator6 -> Scale(ScaleFactor6);
   h_denominator7 -> Scale(ScaleFactor7);
   h_denominator8 -> Scale(ScaleFactor8);

   //Adding the histograms
   TH1F * h_numeratorMC = h_numerator1;
   TH1F * h_denominatorMC = h_denominator1;
   h_numeratorMC -> Add(h_numerator2);
   h_numeratorMC -> Add(h_numerator3);
   h_numeratorMC -> Add(h_numerator4);
   h_numeratorMC -> Add(h_numerator5);
   h_numeratorMC -> Add(h_numerator6);
   h_numeratorMC -> Add(h_numerator7);
   h_numeratorMC -> Add(h_numerator8);
   h_denominatorMC -> Add(h_denominator2);
   h_denominatorMC -> Add(h_denominator3);
   h_denominatorMC -> Add(h_denominator4);
   h_denominatorMC -> Add(h_denominator5);
   h_denominatorMC -> Add(h_denominator6);
   h_denominatorMC -> Add(h_denominator7);
   h_denominatorMC -> Add(h_denominator8);

   // total eff for MC
   TGraphAsymmErrors * g_effMC = new TGraphAsymmErrors(h_numeratorMC, h_denominatorMC,"cl=0.683 b(1,1) mode");
   
   //Setting properties for MC
   g_effMC -> SetMarkerStyle(20);
   g_effMC -> SetTitle("QCD");
   g_effMC -> GetXaxis()->SetRangeUser(0, 300);

   //Drawing the two JKTE in a same pad
   C -> cd(1);
   TMultiGraph *mg = new TMultiGraph();
   mg->SetTitle("Jet Kinematic Trigger Efficiency 0.0<|#eta|<1.0");
   mg->Add(g_effDATA);
   mg->Add(g_effMC);
   mg->GetHistogram()->GetYaxis()->SetRangeUser(0,1.1);
   mg->GetHistogram()->GetXaxis()->SetRangeUser(30,300);
   mg->Draw("AP");
   gPad->BuildLegend();
   
   

   C -> cd(2);
   TGraphAsymmErrors *ratioeff = DivideTGraphsErrors(g_effDATA, g_effMC);
   ratioeff -> GetXaxis() -> SetRangeUser(30,300);
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

       X[i-1] = xA[i-1];

       //if (yB[i-1] != 0)
       Y[i-1] = yA[i-1]/yB[i-1];

       /*if (yB[i-1] == 0)
       {
           if (yA[i-1] == 0)
               Y[i-1] = 0;
           else
               Y[i-1] = 0;
       }*/

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


