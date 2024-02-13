#include "Analysis/Trigger/interface/MuonTriggerAnalyser.h"
#include "Analysis/Tools/interface/Analysis.h"
#include <fstream>
#include <iostream>

using namespace analysis;
using namespace analysis::tools;
using namespace analysis::muontrigger;		

int main(int argc, char ** argv)
{
    TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histogram

    MuonTriggerAnalyser muontrigger(argc,argv);

    for ( int i = 0 ; i < muontrigger.nEvents() ; ++i )
    {
    
        if ( ! muontrigger.event(i)                       )   continue;     // read event, run selection/json
        if ( ! muontrigger.selectionTrigger()             )   continue;     // trigger
        if ( ! muontrigger.muonsSelection()               )   continue;     // muon first selection
        if ( ! muontrigger.muonTagsSelection()            )   continue;     // muon tag selection
        muontrigger.reconstructJPsi();  
    
    }
} // end main
     

