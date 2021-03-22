#ifndef Analysis_MuonTriggerAnalyser_h
#define Analysis_MuonTriggerAnalyser_h 1

// -*- C++ -*-
//
// Package:    Analysis/MssmHbb
// Class:      Analysis
// 
/**\class Analysis MssmHbbAnalyser.cc Analysis/MssmHbb/src/MssmHbbAnalyser.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Roberval Walsh Bastos Rangel
//         Created:  Mon, 20 Oct 2014 14:24:08 GMT
//
//

// system include files
#include <memory>
#include <vector>
#include <string>
// 
// user include files

#include "Analysis/Tools/interface/Analyser.h"

//
// class declaration
//

namespace analysis {
   namespace muontrigger {

      class MuonTriggerAnalyser : public analysis::tools::Analyser {
         
         public:
            MuonTriggerAnalyser();
            MuonTriggerAnalyser(int argc, char ** argv);
           ~MuonTriggerAnalyser();
        
           
            virtual bool event(const int &i);
            bool muonProbesSelection();
            bool muonTagsSelection();
            void muonMatchingProbesSelection();
            void muonFailingProbesSelection();
            TH1F* DiMuonMass_afterTagSelection = new TH1F("DiMuonMass","DiMuonMass" , 50, 2.85, 3.35);
            TH1F* MatchedDiMuonMass = new TH1F("DiMuonMass of matched muons","Passing Probe" , 50, 2.85, 3.35);
            TH1F* FailedMatchingDiMuonMass = new TH1F("NOTMatchedDiMuonMass","Failing Probe" , 50, 2.85, 3.35);
            // ----------member data ---------------------------
         protected:
               
         private:
               

      };
   }
}

#endif  
