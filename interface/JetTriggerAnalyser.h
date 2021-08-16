#ifndef Analysis_Trigger_JetTriggerAnalyser_h
#define Analysis_Trigger_JetTriggerAnalyser_h 1

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
   namespace trigger {

      class JetTriggerAnalyser : public analysis::tools::Analyser {
         
         public:
            JetTriggerAnalyser();
            JetTriggerAnalyser(int argc, char ** argv);
           ~JetTriggerAnalyser();
        
           
            virtual bool event(const int &i);
            bool jetKTEfirstSelection();
            void jetKTEtagandprobeSelection();

            // ----------member data ---------------------------
         protected:
               
         private:
               

      };
   }
}

#endif  
