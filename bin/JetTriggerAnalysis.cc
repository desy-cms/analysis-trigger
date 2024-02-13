#include "Analysis/Trigger/interface/JetTriggerAnalyser.h"

using namespace analysis;
using namespace analysis::tools;
using namespace analysis::trigger;

int main(int argc, char ** argv)
{
    TH1::SetDefaultSumw2();  // proper treatment of errors when scaling histograms

    JetTriggerAnalyser trigger(argc,argv);
    trigger.jetHistograms("Probes");
    trigger.jetHistograms("Probes with matching");

    for ( int i = 0 ; i < trigger.nEvents() ; ++i )
    {
        if ( ! trigger.event(i)                       )  continue;    // read event, run selection/json
        if ( ! trigger.selectionTrigger()             )  continue;    // trigger
        if ( ! trigger.preselection()                 )  continue;    // preselection
        if ( ! trigger.jetCorrections()               )  continue;    // jet corrections
        if ( ! trigger.jetKTEfirstSelection()         )  continue;    // jet corrections
        trigger.jetKTEtagandprobeSelection();
    }
} // end main
     



