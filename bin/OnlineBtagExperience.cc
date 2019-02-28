#include "boost/program_options.hpp"
#include "boost/algorithm/string.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "TFile.h" 
#include "TFileCollection.h"
#include "TChain.h"
#include "TH1.h" 

#include "Analysis/Tools/interface/Analyser.h"

using namespace std;
using namespace analysis;
using namespace analysis::tools;

using TH1s = std::map<std::string, TH1F*>;
using TH2s = std::map<std::string, TH2F*>;
     

// =============================================================================================   
int main(int argc, char ** argv)
{
   TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
   
   Analyser onlinebtag(argc,argv);
   
   onlinebtag.jetHistograms(2,"tag");
   onlinebtag.jetHistograms(2,"probe");
   
   // Analysis of events
   std::cout << "The sample size is " << onlinebtag.analysis()->size() << " events" << std::endl;
   std::cout << "---------------------------" << std::endl;
   
   std::cout << "Workflow index = " << onlinebtag.config()->workflow() << std::endl;
   std::cout << "--------------------" << std::endl;
   
   int seed = onlinebtag.seed();
   
// 
   for ( int i = 0 ; i < onlinebtag.nEvents() ; ++i )
   {
      bool goodEvent = onlinebtag.event(i);

      if ( ! goodEvent ) continue;

      if ( onlinebtag.config()->workflow() == 1 )  // ========== DATA and MC with data-like sequence ========
      {
      
      // trigger selection
         if ( ! onlinebtag.selectionHLT()           )   continue;
         if ( ! onlinebtag.selectionL1 ()           )   continue;  // to be used in case of "OR" of seeds
      
            
      // jet identification selection
         if ( ! onlinebtag.selectionJetId()         )   continue;
         if ( ! onlinebtag.selectionJetPileupId()   )   continue;
         if ( ! onlinebtag.selectionNJets()         )   continue;
         
      // delta Phi
         if ( ! onlinebtag.selectionJetDphi(1,2)    )   continue;
         
      // tag jet selection
         if ( ! onlinebtag.selectionJet(2)          )   continue;
         if ( ! onlinebtag.onlineJetMatching(2)     )   continue;
         if ( ! onlinebtag.selectionBJet(2)         )   continue;
         if ( ! onlinebtag.onlineBJetMatching(2)    )   continue;
         
      // probe jet selection
         if ( ! onlinebtag.selectionJet(1)          )   continue;
         if ( ! onlinebtag.onlineJetMatching(1)     )   continue;
         if ( ! onlinebtag.selectionBJet(1)         )   continue;
         
      // fill tag histograms after selection
         onlinebtag.fillJetHistograms("tag");
         
      // PROBE jet match to online
         if ( ! onlinebtag.onlineBJetMatching(1)    )   continue;
         
      // fill probe histograms after selection
         onlinebtag.fillJetHistograms("probe");
      }
   }
   
} //end main

