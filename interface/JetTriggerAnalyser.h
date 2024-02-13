#ifndef Analysis_Trigger_JetTriggerAnalyser_h
#define Analysis_Trigger_JetTriggerAnalyser_h 1

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
