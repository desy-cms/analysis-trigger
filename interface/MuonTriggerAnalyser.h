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
            bool muonsSelection();
            bool muonTagsSelection();
            void muonPassandFail_MatchingProbesSelection();

            TH1F* TagsPt = new TH1F("Tags_Pt","TagsPt" , 300, 0, 30);
            TH1F* MatchedProbesPt = new TH1F("Matched_Probes_Pt","MatchedProbesPt" , 300, 0, 30);
            TH1F* FailedProbesPt = new TH1F("Failed_Probes_Pt","FailedProbesPt" , 300, 0, 30);

            TH1F* DiMuonMass_afterTagSelection = new TH1F("DiMuonMass","DiMuonMass" , 50, 2.85, 3.35);

            TH1F* MatchedDiMuonMass = new TH1F("DiMuonMass of matched muons","Passing Probe" , 50, 2.85, 3.35);
            TH1F* FailedMatchingDiMuonMass = new TH1F("DiMuonMass of failing muons","Failing Probe" , 50, 2.85, 3.35);

            TH1F* MatchedDiMuonMass_pTBin1 = new TH1F("DiMuonMass of passing muons pTBin1","Passing Probe pTBin1" , 50, 2.85, 3.35);
            TH1F* FailedMatchingDiMuonMass_pTBin1 = new TH1F("DiMuonMass of failing muons pTBin1","Failing Probe pTBin1" , 50, 2.85, 3.35);

            TH1F* MatchedDiMuonMass_pTBin2 = new TH1F("DiMuonMass of passing muons pTBin2","Passing Probe pTBin2" , 50, 2.85, 3.35);
            TH1F* FailedMatchingDiMuonMass_pTBin2 = new TH1F("DiMuonMass of failing muons pTBin2","Failing Probe pTBin2" , 50, 2.85, 3.35);

            TH1F* MatchedDiMuonMass_pTBin3 = new TH1F("DiMuonMass of passing muons pTBin3","Passing Probe pTBin3" , 50, 2.85, 3.35);
            TH1F* FailedMatchingDiMuonMass_pTBin3 = new TH1F("DiMuonMass of failing muons pTBin3","Failing Probe pTBin3" , 50, 2.85, 3.35);

            TH1F* MatchedDiMuonMass_pTBin4 = new TH1F("DiMuonMass of passing muons pTBin4","Passing Probe pTBin4" , 50, 2.85, 3.35);
            TH1F* FailedMatchingDiMuonMass_pTBin4 = new TH1F("DiMuonMass of failing muons pTBin4","Failing Probe pTBin4" , 50, 2.85, 3.35);

            // ----------member data ---------------------------
         protected:
               
         private:
               

      };
   }
}

#endif  
