#include "Analysis/Trigger/interface/MuonTriggerAnalyser.h"

using namespace analysis;
using namespace analysis::tools;
using namespace analysis::muontrigger;

int main(int argc, char ** argv)
{
    TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms
  
    MuonTriggerAnalyser muontrigger(argc,argv);

    for ( int i = 0 ; i < muontrigger.nEvents() ; ++i )
    {
        if ( ! muontrigger.event(i)                       )  continue;     // read event, run selection/json
        if ( ! muontrigger.triggerSelection()             )  continue;     // trigger
        if ( ! muontrigger.muonProbesSelection()          )  continue;    // muon first selection
        if ( ! muontrigger.muonTagsSelection()            )  continue;      // muon tag selection
        muontrigger.muonMatchingProbesSelection(); 
        muontrigger.muonFailingProbesSelection();
    }
} // end main
     

