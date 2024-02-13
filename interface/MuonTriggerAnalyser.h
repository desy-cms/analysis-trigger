#ifndef Analysis_MuonTriggerAnalyser_h
#define Analysis_MuonTriggerAnalyser_h 1

//
//          Author:  Daina Leyva
//         Created:  Aug. 2021
//         Reviwed:  Feb. 2024
//
//


// system include files
#include <memory>
#include <vector>
#include <string>
#include <fstream>
// 
// user include files

#include "Analysis/Tools/interface/Analyser.h"
#include "Analysis/Tools/interface/Analysis.h"

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
            //bool muonsSelection_upsilon();
            bool muonTagsSelection();
            void reconstructJPsi();
            //void reconstruct_upsilon();

            TH1D* TagsPt = new TH1D("Tags_Pt","TagsPt" , 300, 0, 30);
            TH1D* PassedProbesPt = new TH1D("Matched_Probes_Pt","MatchedProbesPt" , 300, 0, 30);
            TH1D* FailedProbesPt = new TH1D("Failed_Probes_Pt","FailedProbesPt" ,300, 0, 30);
            //TH1D* DiMuonMass_afterTagSelection = new TH1D("DiMuonMass","DiMuonMass" , 50, 2.85, 3.35);
            //TH1D* DiMuonMass_afterTagSelection = new TH1D("DiMuonMass","DiMuonMass" , 80, 2.70, 3.50);
            TH1D* DiMuonMass_afterTagSelection = new TH1D("DiMuonMass","DiMuonMass" , 80, 2.80, 3.60);

            //TH2D* PassedDiMuonMass_vs_probespT = new TH2D("DiMuonMass of passing muons 2D","Passing Probes 2D" , 50, 2.85, 3.35, 300, 0, 30);
            //TH2D* FailedDiMuonMass_vs_probespT = new TH2D("DiMuonMass of failing muons 2D","Failing Probes 2D" , 50, 2.85, 3.35, 300, 0, 30);
            TH2D* PassedDiMuonMass_vs_probespT = new TH2D("DiMuonMass of passing muons 2D","Passing Probes 2D" , 80, 2.80, 3.60, 300, 0, 30);
            TH2D* FailedDiMuonMass_vs_probespT = new TH2D("DiMuonMass of failing muons 2D","Failing Probes 2D" , 80, 2.80, 3.60, 300, 0, 30);

            // ----------member data ---------------------------
         protected:
               
         private:
               

      };
   }
}

#endif  
